-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Mon Feb 28 14:42:09 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_pu_con_ip_0_1/zusys_uz_pu_con_ip_0_1_sim_netlist.vhdl
-- Design      : zusys_uz_pu_con_ip_0_1
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder is
  port (
    OPMODE : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in1_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in2_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in3_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in4_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in5_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in6_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in7_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in8_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in9_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in10_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in11_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in12_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in13_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in14_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in15_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in16_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in17_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in18_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in19_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in20_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in21_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in22_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in23_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in24_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in25_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in26_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in27_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in28_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in29_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in30_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in31_1_1_reg[0]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    read_reg_ip_timestamp : out STD_LOGIC_VECTOR ( 0 to 0 );
    reset : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in0_1_1_reg[0]_0\ : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in1_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in2_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in3_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in4_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in5_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in6_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in7_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in8_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in9_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in10_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in11_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in12_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in13_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in14_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in15_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in16_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in17_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in18_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in19_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in20_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in21_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in22_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in23_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in24_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in25_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in26_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in27_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in28_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in29_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in30_1_1_reg[0]_1\ : in STD_LOGIC;
    \data_reg_AXI_pu_conv_in31_1_1_reg[0]_1\ : in STD_LOGIC;
    \read_reg_ip_timestamp_reg[31]_0\ : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder : entity is "uz_pu_con_ip_addr_decoder";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder is
begin
\data_reg_AXI_pu_conv_in0_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in0_1_1_reg[0]_0\,
      Q => OPMODE(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in10_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in10_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in10_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in11_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in11_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in11_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in12_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in12_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in12_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in13_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in13_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in13_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in14_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in14_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in14_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in15_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in15_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in15_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in16_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in16_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in16_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in17_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in17_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in17_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in18_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in18_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in18_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in19_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in19_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in19_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in1_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in1_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in1_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in20_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in20_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in20_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in21_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in21_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in21_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in22_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in22_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in22_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in23_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in23_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in23_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in24_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in24_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in24_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in25_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in25_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in25_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in26_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in26_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in26_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in27_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in27_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in27_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in28_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in28_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in28_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in29_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in29_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in29_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in2_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in2_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in2_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in30_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in30_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in30_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in31_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in31_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in31_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in3_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in3_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in3_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in4_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in4_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in4_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in5_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in5_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in5_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in6_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in6_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in6_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in7_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in7_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in7_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in8_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in8_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in8_1_1_reg[0]_0\(0),
      R => reset
    );
\data_reg_AXI_pu_conv_in9_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \data_reg_AXI_pu_conv_in9_1_1_reg[0]_1\,
      Q => \data_reg_AXI_pu_conv_in9_1_1_reg[0]_0\(0),
      R => reset
    );
\read_reg_ip_timestamp_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \read_reg_ip_timestamp_reg[31]_0\,
      Q => read_reg_ip_timestamp(0),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module is
  port (
    FSM_sequential_axi_lite_rstate_reg_0 : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 0 to 0 );
    soft_reset : out STD_LOGIC;
    CEB2 : out STD_LOGIC;
    AXI4_Lite_ARADDR_8_sp_1 : out STD_LOGIC;
    AXI4_Lite_ARADDR_11_sp_1 : out STD_LOGIC;
    AXI4_Lite_ARADDR_7_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_0\ : out STD_LOGIC;
    AXI4_Lite_ARADDR_4_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_0\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_2\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[4]_0\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_3\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_4\ : out STD_LOGIC;
    AXI4_Lite_ARADDR_3_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_5\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_2\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_6\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[3]_0\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_7\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_3\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_8\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[4]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_9\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_4\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_10\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[4]_2\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_11\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_5\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_12\ : out STD_LOGIC;
    AXI4_Lite_ARADDR_6_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_13\ : out STD_LOGIC;
    wr_enb_1_reg_0 : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    \wdata_reg[0]_0\ : out STD_LOGIC;
    \wdata_reg[0]_1\ : out STD_LOGIC;
    \wdata_reg[0]_2\ : out STD_LOGIC;
    \wdata_reg[0]_3\ : out STD_LOGIC;
    \wdata_reg[0]_4\ : out STD_LOGIC;
    \wdata_reg[0]_5\ : out STD_LOGIC;
    \wdata_reg[0]_6\ : out STD_LOGIC;
    \wdata_reg[0]_7\ : out STD_LOGIC;
    \wdata_reg[0]_8\ : out STD_LOGIC;
    \wdata_reg[0]_9\ : out STD_LOGIC;
    \wdata_reg[0]_10\ : out STD_LOGIC;
    \wdata_reg[0]_11\ : out STD_LOGIC;
    \wdata_reg[0]_12\ : out STD_LOGIC;
    \wdata_reg[0]_13\ : out STD_LOGIC;
    \wdata_reg[0]_14\ : out STD_LOGIC;
    \wdata_reg[0]_15\ : out STD_LOGIC;
    \wdata_reg[0]_16\ : out STD_LOGIC;
    \wdata_reg[0]_17\ : out STD_LOGIC;
    \wdata_reg[0]_18\ : out STD_LOGIC;
    \wdata_reg[0]_19\ : out STD_LOGIC;
    \wdata_reg[0]_20\ : out STD_LOGIC;
    \wdata_reg[0]_21\ : out STD_LOGIC;
    \wdata_reg[0]_22\ : out STD_LOGIC;
    \wdata_reg[0]_23\ : out STD_LOGIC;
    \wdata_reg[0]_24\ : out STD_LOGIC;
    \wdata_reg[0]_25\ : out STD_LOGIC;
    \wdata_reg[0]_26\ : out STD_LOGIC;
    \wdata_reg[0]_27\ : out STD_LOGIC;
    \wdata_reg[0]_28\ : out STD_LOGIC;
    \wdata_reg[0]_29\ : out STD_LOGIC;
    \wdata_reg[0]_30\ : out STD_LOGIC;
    \wdata_reg[0]_31\ : out STD_LOGIC;
    \wdata_reg[17]_0\ : out STD_LOGIC_VECTOR ( 16 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    \data_reg_AXI_pu_conv_in24_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in16_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in8_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in31_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in23_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in15_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in7_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in30_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in22_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in14_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in6_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in29_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in21_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in13_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in5_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in28_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in20_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in12_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in4_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in27_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in19_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in11_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in3_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in26_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in18_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in10_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in2_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in25_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in17_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in9_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in1_1_1_reg[0]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    OPMODE : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 17 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module : entity is "uz_pu_con_ip_axi_lite_module";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module is
  signal AXI4_Lite_ARADDR_11_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_3_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_4_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_6_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_7_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_8_sn_1 : STD_LOGIC;
  signal \^axi4_lite_rdata\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \AXI4_Lite_RDATA_tmp[31]_i_1_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_2_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\ : STD_LOGIC;
  signal \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\ : STD_LOGIC;
  signal \^fsm_sequential_axi_lite_rstate_reg_0\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal aw_transfer : STD_LOGIC;
  signal axi_lite_rstate_next : STD_LOGIC;
  signal axi_lite_wstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal \data_reg_AXI_pu_conv_in0_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in8_1_1[0]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in8_1_1[0]_i_3_n_0\ : STD_LOGIC;
  signal \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_30_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_31_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_32_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_33_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_34_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_35_n_0\ : STD_LOGIC;
  signal \p_1_out__0_i_36_n_0\ : STD_LOGIC;
  signal \p_1_out__15_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__15_i_30_n_0\ : STD_LOGIC;
  signal \p_1_out__1_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__2_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__3_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__4_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__5_i_29_n_0\ : STD_LOGIC;
  signal \p_1_out__6_i_29_n_0\ : STD_LOGIC;
  signal p_1_out_i_29_n_0 : STD_LOGIC;
  signal p_1_out_i_30_n_0 : STD_LOGIC;
  signal p_1_out_i_31_n_0 : STD_LOGIC;
  signal p_1_out_i_32_n_0 : STD_LOGIC;
  signal p_1_out_i_33_n_0 : STD_LOGIC;
  signal p_1_out_i_34_n_0 : STD_LOGIC;
  signal p_1_out_i_35_n_0 : STD_LOGIC;
  signal p_1_out_i_36_n_0 : STD_LOGIC;
  signal reset : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \^soft_reset\ : STD_LOGIC;
  signal soft_reset_i_1_n_0 : STD_LOGIC;
  signal soft_reset_i_2_n_0 : STD_LOGIC;
  signal soft_reset_i_3_n_0 : STD_LOGIC;
  signal soft_reset_i_4_n_0 : STD_LOGIC;
  signal top_wr_enb : STD_LOGIC;
  signal w_transfer : STD_LOGIC;
  signal w_transfer_and_wstrb : STD_LOGIC;
  signal \wdata_reg_n_0_[0]\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of AXI4_Lite_ARREADY_INST_0 : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of AXI4_Lite_AWREADY_INST_0 : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[31]_i_3\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[31]_i_5\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[31]_i_6\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \FSM_onehot_axi_lite_wstate[0]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \FSM_onehot_axi_lite_wstate[1]_i_2\ : label is "soft_lutpair19";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of FSM_sequential_axi_lite_rstate_i_1 : label is "soft_lutpair20";
  attribute FSM_ENCODED_STATES of FSM_sequential_axi_lite_rstate_reg : label is "iSTATE:0,iSTATE0:1";
  attribute SOFT_HLUTNM of \data_reg_AXI_pu_conv_in0_1_1[0]_i_2\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \data_reg_AXI_pu_conv_in1_1_1[0]_i_3\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \data_reg_AXI_pu_conv_in2_1_1[0]_i_3\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \data_reg_AXI_pu_conv_in4_1_1[0]_i_3\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \data_reg_AXI_pu_conv_in6_1_1[0]_i_3\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \data_reg_AXI_pu_conv_in8_1_1[0]_i_4\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \p_1_out__0_i_33\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \p_1_out__0_i_34\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \p_1_out__0_i_35\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \p_1_out__10_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \p_1_out__11_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \p_1_out__12_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \p_1_out__13_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \p_1_out__14_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \p_1_out__17_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \p_1_out__18_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \p_1_out__19_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \p_1_out__1_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \p_1_out__20_i_1\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \p_1_out__21_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \p_1_out__22_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \p_1_out__25_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \p_1_out__26_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \p_1_out__27_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \p_1_out__28_i_1\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \p_1_out__29_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \p_1_out__2_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \p_1_out__30_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \p_1_out__3_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \p_1_out__4_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \p_1_out__5_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \p_1_out__6_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \p_1_out__9_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of p_1_out_i_30 : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of p_1_out_i_31 : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of p_1_out_i_32 : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of p_1_out_i_33 : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of p_1_out_i_35 : label is "soft_lutpair18";
begin
  AXI4_Lite_ARADDR_11_sp_1 <= AXI4_Lite_ARADDR_11_sn_1;
  AXI4_Lite_ARADDR_3_sp_1 <= AXI4_Lite_ARADDR_3_sn_1;
  AXI4_Lite_ARADDR_4_sp_1 <= AXI4_Lite_ARADDR_4_sn_1;
  AXI4_Lite_ARADDR_6_sp_1 <= AXI4_Lite_ARADDR_6_sn_1;
  AXI4_Lite_ARADDR_7_sp_1 <= AXI4_Lite_ARADDR_7_sn_1;
  AXI4_Lite_ARADDR_8_sp_1 <= AXI4_Lite_ARADDR_8_sn_1;
  AXI4_Lite_RDATA(0) <= \^axi4_lite_rdata\(0);
  FSM_sequential_axi_lite_rstate_reg_0 <= \^fsm_sequential_axi_lite_rstate_reg_0\;
  Q(1 downto 0) <= \^q\(1 downto 0);
  soft_reset <= \^soft_reset\;
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
\AXI4_Lite_RDATA_tmp[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFF2F00000020"
    )
        port map (
      I0 => p_1_out_i_29_n_0,
      I1 => \AXI4_Lite_RDATA_tmp[31]_i_2_n_0\,
      I2 => AXI4_Lite_ARVALID,
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\,
      I4 => AXI4_Lite_AWVALID,
      I5 => \^axi4_lite_rdata\(0),
      O => \AXI4_Lite_RDATA_tmp[31]_i_1_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFBFFFF"
    )
        port map (
      I0 => p_1_out_i_33_n_0,
      I1 => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\,
      I4 => read_reg_ip_timestamp(0),
      I5 => p_1_out_i_31_n_0,
      O => \AXI4_Lite_RDATA_tmp[31]_i_2_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      O => \AXI4_Lite_RDATA_tmp[31]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(1),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(1),
      O => \AXI4_Lite_RDATA_tmp[31]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(6),
      I1 => AXI4_Lite_ARADDR(6),
      I2 => sel0(7),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(7),
      O => \AXI4_Lite_RDATA_tmp[31]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[31]_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(2),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(2),
      O => \AXI4_Lite_RDATA_tmp[31]_i_6_n_0\
    );
\AXI4_Lite_RDATA_tmp_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \AXI4_Lite_RDATA_tmp[31]_i_1_n_0\,
      Q => \^axi4_lite_rdata\(0),
      R => reset
    );
\FSM_onehot_axi_lite_wstate[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF8F8888"
    )
        port map (
      I0 => \^q\(1),
      I1 => AXI4_Lite_BREADY,
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
      INIT => X"40FF4040"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => AXI4_Lite_AWVALID,
      I3 => AXI4_Lite_WVALID,
      I4 => \^q\(0),
      O => axi_lite_wstate_next(1)
    );
\FSM_onehot_axi_lite_wstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => \^q\(0),
      I1 => AXI4_Lite_WVALID,
      I2 => AXI4_Lite_BREADY,
      I3 => \^q\(1),
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
      Q => \^q\(0),
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
      Q => \^q\(1),
      R => reset
    );
FSM_sequential_axi_lite_rstate_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"55305500"
    )
        port map (
      I0 => AXI4_Lite_RREADY,
      I1 => AXI4_Lite_AWVALID,
      I2 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I3 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I4 => AXI4_Lite_ARVALID,
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
\data_reg_AXI_pu_conv_in0_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFB00000008"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => p_1_out_i_29_n_0,
      I2 => p_1_out_i_30_n_0,
      I3 => p_1_out_i_31_n_0,
      I4 => \data_reg_AXI_pu_conv_in0_1_1[0]_i_2_n_0\,
      I5 => OPMODE(0),
      O => \wdata_reg[0]_31\
    );
\data_reg_AXI_pu_conv_in0_1_1[0]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FBFFFBBB"
    )
        port map (
      I0 => p_1_out_i_32_n_0,
      I1 => top_wr_enb,
      I2 => AXI4_Lite_ARADDR(12),
      I3 => AXI4_Lite_ARVALID,
      I4 => sel0(12),
      O => \data_reg_AXI_pu_conv_in0_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in10_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in10_1_1_reg[0]\(0),
      O => \wdata_reg[0]_25\
    );
\data_reg_AXI_pu_conv_in11_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in11_1_1_reg[0]\(0),
      O => \wdata_reg[0]_21\
    );
\data_reg_AXI_pu_conv_in12_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in12_1_1_reg[0]\(0),
      O => \wdata_reg[0]_17\
    );
\data_reg_AXI_pu_conv_in13_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in13_1_1_reg[0]\(0),
      O => \wdata_reg[0]_13\
    );
\data_reg_AXI_pu_conv_in14_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in14_1_1_reg[0]\(0),
      O => \wdata_reg[0]_9\
    );
\data_reg_AXI_pu_conv_in15_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in15_1_1_reg[0]\(0),
      O => \wdata_reg[0]_5\
    );
\data_reg_AXI_pu_conv_in16_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in16_1_1_reg[0]\(0),
      O => \wdata_reg[0]_1\
    );
\data_reg_AXI_pu_conv_in16_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000470000"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      I3 => p_1_out_i_32_n_0,
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in17_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in17_1_1_reg[0]\(0),
      O => \wdata_reg[0]_28\
    );
\data_reg_AXI_pu_conv_in17_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000045400000"
    )
        port map (
      I0 => p_1_out_i_32_n_0,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in18_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in18_1_1_reg[0]\(0),
      O => \wdata_reg[0]_24\
    );
\data_reg_AXI_pu_conv_in18_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000202A0000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in19_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in19_1_1_reg[0]\(0),
      O => \wdata_reg[0]_20\
    );
\data_reg_AXI_pu_conv_in19_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000008A800000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in1_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in1_1_1_reg[0]\(0),
      O => \wdata_reg[0]_30\
    );
\data_reg_AXI_pu_conv_in1_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000045400000"
    )
        port map (
      I0 => p_1_out_i_32_n_0,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in1_1_1[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(5),
      I1 => AXI4_Lite_ARADDR(5),
      I2 => sel0(4),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(4),
      O => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\
    );
\data_reg_AXI_pu_conv_in20_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in20_1_1_reg[0]\(0),
      O => \wdata_reg[0]_16\
    );
\data_reg_AXI_pu_conv_in20_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000202A0000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in21_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in21_1_1_reg[0]\(0),
      O => \wdata_reg[0]_12\
    );
\data_reg_AXI_pu_conv_in21_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000008A800000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in22_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in22_1_1_reg[0]\(0),
      O => \wdata_reg[0]_8\
    );
\data_reg_AXI_pu_conv_in22_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000202A0000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in23_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__15_i_29_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in23_1_1_reg[0]\(0),
      O => \wdata_reg[0]_4\
    );
\data_reg_AXI_pu_conv_in23_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000008A800000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0\,
      I1 => AXI4_Lite_ARADDR(0),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(0),
      I4 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      I5 => \p_1_out__0_i_36_n_0\,
      O => \data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in24_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in16_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in24_1_1_reg[0]\(0),
      O => \wdata_reg[0]_0\
    );
\data_reg_AXI_pu_conv_in25_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in17_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in25_1_1_reg[0]\(0),
      O => \wdata_reg[0]_27\
    );
\data_reg_AXI_pu_conv_in26_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in18_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in26_1_1_reg[0]\(0),
      O => \wdata_reg[0]_23\
    );
\data_reg_AXI_pu_conv_in27_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in19_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in27_1_1_reg[0]\(0),
      O => \wdata_reg[0]_19\
    );
\data_reg_AXI_pu_conv_in28_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in20_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in28_1_1_reg[0]\(0),
      O => \wdata_reg[0]_15\
    );
\data_reg_AXI_pu_conv_in29_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in21_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in29_1_1_reg[0]\(0),
      O => \wdata_reg[0]_11\
    );
\data_reg_AXI_pu_conv_in2_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in2_1_1_reg[0]\(0),
      O => \wdata_reg[0]_26\
    );
\data_reg_AXI_pu_conv_in2_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0020000000202020"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I1 => \p_1_out__0_i_36_n_0\,
      I2 => \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0\,
      I3 => AXI4_Lite_ARADDR(0),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(0),
      O => \data_reg_AXI_pu_conv_in2_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in2_1_1[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000ACC0A"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0\
    );
\data_reg_AXI_pu_conv_in30_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in22_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in30_1_1_reg[0]\(0),
      O => \wdata_reg[0]_7\
    );
\data_reg_AXI_pu_conv_in31_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in23_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      I5 => \data_reg_AXI_pu_conv_in31_1_1_reg[0]\(0),
      O => \wdata_reg[0]_3\
    );
\data_reg_AXI_pu_conv_in3_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in3_1_1_reg[0]\(0),
      O => \wdata_reg[0]_22\
    );
\data_reg_AXI_pu_conv_in3_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2000202020000000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I1 => \p_1_out__0_i_36_n_0\,
      I2 => \data_reg_AXI_pu_conv_in2_1_1[0]_i_3_n_0\,
      I3 => AXI4_Lite_ARADDR(0),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(0),
      O => \data_reg_AXI_pu_conv_in3_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in4_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in4_1_1_reg[0]\(0),
      O => \wdata_reg[0]_18\
    );
\data_reg_AXI_pu_conv_in4_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0020000000202020"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I1 => \p_1_out__0_i_36_n_0\,
      I2 => \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0\,
      I3 => AXI4_Lite_ARADDR(0),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(0),
      O => \data_reg_AXI_pu_conv_in4_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in4_1_1[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000ACC0A"
    )
        port map (
      I0 => sel0(2),
      I1 => AXI4_Lite_ARADDR(2),
      I2 => sel0(1),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(1),
      O => \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0\
    );
\data_reg_AXI_pu_conv_in5_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in5_1_1_reg[0]\(0),
      O => \wdata_reg[0]_14\
    );
\data_reg_AXI_pu_conv_in5_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2000202020000000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I1 => \p_1_out__0_i_36_n_0\,
      I2 => \data_reg_AXI_pu_conv_in4_1_1[0]_i_3_n_0\,
      I3 => AXI4_Lite_ARADDR(0),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(0),
      O => \data_reg_AXI_pu_conv_in5_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in6_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in6_1_1_reg[0]\(0),
      O => \wdata_reg[0]_10\
    );
\data_reg_AXI_pu_conv_in6_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0020000000202020"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I1 => \p_1_out__0_i_36_n_0\,
      I2 => \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0\,
      I3 => AXI4_Lite_ARADDR(0),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(0),
      O => \data_reg_AXI_pu_conv_in6_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in6_1_1[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"CCA000A0"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0\
    );
\data_reg_AXI_pu_conv_in7_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0\,
      I5 => \data_reg_AXI_pu_conv_in7_1_1_reg[0]\(0),
      O => \wdata_reg[0]_6\
    );
\data_reg_AXI_pu_conv_in7_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2000202020000000"
    )
        port map (
      I0 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_3_n_0\,
      I1 => \p_1_out__0_i_36_n_0\,
      I2 => \data_reg_AXI_pu_conv_in6_1_1[0]_i_3_n_0\,
      I3 => AXI4_Lite_ARADDR(0),
      I4 => AXI4_Lite_ARVALID,
      I5 => sel0(0),
      O => \data_reg_AXI_pu_conv_in7_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in8_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFB00000008"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \p_1_out__0_i_31_n_0\,
      I2 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_2_n_0\,
      I3 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_3_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      I5 => \data_reg_AXI_pu_conv_in8_1_1_reg[0]\(0),
      O => \wdata_reg[0]_2\
    );
\data_reg_AXI_pu_conv_in8_1_1[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF4700FFFF"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(8),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(8),
      I3 => p_1_out_i_30_n_0,
      I4 => p_1_out_i_36_n_0,
      I5 => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\,
      O => \data_reg_AXI_pu_conv_in8_1_1[0]_i_2_n_0\
    );
\data_reg_AXI_pu_conv_in8_1_1[0]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFBBFCB8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(2),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(2),
      I3 => AXI4_Lite_ARADDR(1),
      I4 => sel0(1),
      I5 => \p_1_out__0_i_33_n_0\,
      O => \data_reg_AXI_pu_conv_in8_1_1[0]_i_3_n_0\
    );
\data_reg_AXI_pu_conv_in8_1_1[0]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000ACC0A"
    )
        port map (
      I0 => sel0(4),
      I1 => AXI4_Lite_ARADDR(4),
      I2 => sel0(5),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(5),
      O => \data_reg_AXI_pu_conv_in8_1_1[0]_i_4_n_0\
    );
\data_reg_AXI_pu_conv_in9_1_1[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFBF00000080"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \data_reg_AXI_pu_conv_in1_1_1[0]_i_2_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      I5 => \data_reg_AXI_pu_conv_in9_1_1_reg[0]\(0),
      O => \wdata_reg[0]_29\
    );
\p_1_out__0_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000400000"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_32_n_0\,
      I4 => \p_1_out__0_i_33_n_0\,
      I5 => p_1_out_i_32_n_0,
      O => \AXI4_Lite_ARADDR[8]_13\
    );
\p_1_out__0_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000FF77CF47"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(6),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(6),
      I3 => AXI4_Lite_ARADDR(7),
      I4 => sel0(7),
      I5 => \p_1_out__0_i_34_n_0\,
      O => \p_1_out__0_i_29_n_0\
    );
\p_1_out__0_i_30\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"47034400FFFFFFFF"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(5),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(5),
      I3 => AXI4_Lite_ARADDR(4),
      I4 => sel0(4),
      I5 => p_1_out_i_36_n_0,
      O => \p_1_out__0_i_30_n_0\
    );
\p_1_out__0_i_31\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000004700"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(9),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(9),
      I3 => p_1_out_i_34_n_0,
      I4 => \p_1_out__0_i_35_n_0\,
      I5 => p_1_out_i_33_n_0,
      O => \p_1_out__0_i_31_n_0\
    );
\p_1_out__0_i_32\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFEFEFFFFAEFEA"
    )
        port map (
      I0 => \p_1_out__0_i_36_n_0\,
      I1 => AXI4_Lite_ARADDR(4),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(4),
      I4 => AXI4_Lite_ARADDR(5),
      I5 => sel0(5),
      O => \p_1_out__0_i_32_n_0\
    );
\p_1_out__0_i_33\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      O => \p_1_out__0_i_33_n_0\
    );
\p_1_out__0_i_34\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(8),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(8),
      O => \p_1_out__0_i_34_n_0\
    );
\p_1_out__0_i_35\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(13),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(13),
      O => \p_1_out__0_i_35_n_0\
    );
\p_1_out__0_i_36\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFBBFCB8FFFFFFFF"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(7),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(7),
      I3 => AXI4_Lite_ARADDR(8),
      I4 => sel0(8),
      I5 => top_wr_enb,
      O => \p_1_out__0_i_36_n_0\
    );
\p_1_out__10_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__2_i_29_n_0\,
      I1 => \p_1_out__0_i_32_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      O => \AXI4_Lite_ARADDR[4]_1\
    );
\p_1_out__11_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__3_i_29_n_0\,
      I1 => \p_1_out__0_i_32_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      O => \AXI4_Lite_ARADDR[3]_0\
    );
\p_1_out__12_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__4_i_29_n_0\,
      I1 => \p_1_out__0_i_32_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      O => AXI4_Lite_ARADDR_3_sn_1
    );
\p_1_out__13_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__5_i_29_n_0\,
      I1 => \p_1_out__0_i_32_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      O => \AXI4_Lite_ARADDR[4]_0\
    );
\p_1_out__14_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__6_i_29_n_0\,
      I1 => \p_1_out__0_i_32_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      O => AXI4_Lite_ARADDR_4_sn_1
    );
\p_1_out__15_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => p_1_out_i_32_n_0,
      I5 => \p_1_out__0_i_33_n_0\,
      O => AXI4_Lite_ARADDR_8_sn_1
    );
\p_1_out__15_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00440347FFFFFFFF"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(4),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(4),
      I3 => AXI4_Lite_ARADDR(5),
      I4 => sel0(5),
      I5 => p_1_out_i_36_n_0,
      O => \p_1_out__15_i_29_n_0\
    );
\p_1_out__15_i_30\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFEAFFFAEFEFFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_36_n_0\,
      I1 => AXI4_Lite_ARADDR(5),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(5),
      I4 => AXI4_Lite_ARADDR(4),
      I5 => sel0(4),
      O => \p_1_out__15_i_30_n_0\
    );
\p_1_out__16_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000400000"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__0_i_33_n_0\,
      I5 => p_1_out_i_32_n_0,
      O => \AXI4_Lite_ARADDR[8]_12\
    );
\p_1_out__17_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__1_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[8]_10\
    );
\p_1_out__18_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__2_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[8]_8\
    );
\p_1_out__19_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__3_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[8]_6\
    );
\p_1_out__1_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__1_i_29_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      O => \AXI4_Lite_ARADDR[8]_11\
    );
\p_1_out__1_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFEAFFFAEFEFFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_33_n_0\,
      I1 => AXI4_Lite_ARADDR(2),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(2),
      I4 => AXI4_Lite_ARADDR(1),
      I5 => sel0(1),
      O => \p_1_out__1_i_29_n_0\
    );
\p_1_out__20_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__4_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[8]_4\
    );
\p_1_out__21_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__5_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[8]_2\
    );
\p_1_out__22_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__15_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__15_i_30_n_0\,
      I4 => \p_1_out__6_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[8]_0\
    );
\p_1_out__23_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000100"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => p_1_out_i_32_n_0,
      I2 => \p_1_out__0_i_33_n_0\,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \p_1_out__0_i_29_n_0\,
      I5 => \p_1_out__15_i_29_n_0\,
      O => CEB2
    );
\p_1_out__24_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000400"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__0_i_33_n_0\,
      I2 => p_1_out_i_32_n_0,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \p_1_out__0_i_29_n_0\,
      I5 => \p_1_out__15_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[7]_5\
    );
\p_1_out__25_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__1_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[7]_4\
    );
\p_1_out__26_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__2_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[7]_3\
    );
\p_1_out__27_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__3_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[7]_2\
    );
\p_1_out__28_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__4_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[7]_1\
    );
\p_1_out__29_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__5_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      O => \AXI4_Lite_ARADDR[7]_0\
    );
\p_1_out__2_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__2_i_29_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      O => \AXI4_Lite_ARADDR[8]_9\
    );
\p_1_out__2_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"DFD5FFF5DFDFFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_33_n_0\,
      I1 => AXI4_Lite_ARADDR(2),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(2),
      I4 => AXI4_Lite_ARADDR(1),
      I5 => sel0(1),
      O => \p_1_out__2_i_29_n_0\
    );
\p_1_out__30_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__15_i_30_n_0\,
      I1 => \p_1_out__6_i_29_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__15_i_29_n_0\,
      O => AXI4_Lite_ARADDR_7_sn_1
    );
\p_1_out__3_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__3_i_29_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      O => \AXI4_Lite_ARADDR[8]_7\
    );
\p_1_out__3_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFEAFFFAEFEFFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_33_n_0\,
      I1 => AXI4_Lite_ARADDR(1),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(1),
      I4 => AXI4_Lite_ARADDR(2),
      I5 => sel0(2),
      O => \p_1_out__3_i_29_n_0\
    );
\p_1_out__4_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__4_i_29_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      O => \AXI4_Lite_ARADDR[8]_5\
    );
\p_1_out__4_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"DFD5FFF5DFDFFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_33_n_0\,
      I1 => AXI4_Lite_ARADDR(1),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(1),
      I4 => AXI4_Lite_ARADDR(2),
      I5 => sel0(2),
      O => \p_1_out__4_i_29_n_0\
    );
\p_1_out__5_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__5_i_29_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      O => \AXI4_Lite_ARADDR[8]_3\
    );
\p_1_out__5_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BABFFAFFBFBFFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_33_n_0\,
      I1 => AXI4_Lite_ARADDR(2),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(2),
      I4 => AXI4_Lite_ARADDR(1),
      I5 => sel0(1),
      O => \p_1_out__5_i_29_n_0\
    );
\p_1_out__6_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000040"
    )
        port map (
      I0 => \p_1_out__0_i_29_n_0\,
      I1 => \p_1_out__0_i_30_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__6_i_29_n_0\,
      I4 => \p_1_out__0_i_32_n_0\,
      O => \AXI4_Lite_ARADDR[8]_1\
    );
\p_1_out__6_i_29\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"757FF5FF7F7FFFFF"
    )
        port map (
      I0 => \p_1_out__0_i_33_n_0\,
      I1 => AXI4_Lite_ARADDR(2),
      I2 => AXI4_Lite_ARVALID,
      I3 => sel0(2),
      I4 => AXI4_Lite_ARADDR(1),
      I5 => sel0(1),
      O => \p_1_out__6_i_29_n_0\
    );
\p_1_out__7_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000002"
    )
        port map (
      I0 => \p_1_out__0_i_31_n_0\,
      I1 => \p_1_out__0_i_29_n_0\,
      I2 => \p_1_out__0_i_30_n_0\,
      I3 => p_1_out_i_32_n_0,
      I4 => \p_1_out__0_i_33_n_0\,
      I5 => \p_1_out__0_i_32_n_0\,
      O => AXI4_Lite_ARADDR_11_sn_1
    );
\p_1_out__8_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000400"
    )
        port map (
      I0 => \p_1_out__0_i_32_n_0\,
      I1 => \p_1_out__0_i_33_n_0\,
      I2 => p_1_out_i_32_n_0,
      I3 => \p_1_out__0_i_31_n_0\,
      I4 => \p_1_out__0_i_29_n_0\,
      I5 => \p_1_out__0_i_30_n_0\,
      O => AXI4_Lite_ARADDR_6_sn_1
    );
\p_1_out__9_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000010"
    )
        port map (
      I0 => \p_1_out__1_i_29_n_0\,
      I1 => \p_1_out__0_i_32_n_0\,
      I2 => \p_1_out__0_i_31_n_0\,
      I3 => \p_1_out__0_i_29_n_0\,
      I4 => \p_1_out__0_i_30_n_0\,
      O => \AXI4_Lite_ARADDR[4]_2\
    );
p_1_out_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000020000"
    )
        port map (
      I0 => p_1_out_i_29_n_0,
      I1 => p_1_out_i_30_n_0,
      I2 => p_1_out_i_31_n_0,
      I3 => p_1_out_i_32_n_0,
      I4 => top_wr_enb,
      I5 => p_1_out_i_33_n_0,
      O => wr_enb_1_reg_0
    );
p_1_out_i_29: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000004700"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(9),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(9),
      I3 => p_1_out_i_34_n_0,
      I4 => p_1_out_i_35_n_0,
      I5 => p_1_out_i_36_n_0,
      O => p_1_out_i_29_n_0
    );
p_1_out_i_30: unisim.vcomponents.LUT5
    generic map(
      INIT => X"CCAFFFAF"
    )
        port map (
      I0 => sel0(7),
      I1 => AXI4_Lite_ARADDR(7),
      I2 => sel0(6),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(6),
      O => p_1_out_i_30_n_0
    );
p_1_out_i_31: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(13),
      I1 => AXI4_Lite_ARADDR(13),
      I2 => sel0(0),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(0),
      O => p_1_out_i_31_n_0
    );
p_1_out_i_32: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(2),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(2),
      O => p_1_out_i_32_n_0
    );
p_1_out_i_33: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(12),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(12),
      O => p_1_out_i_33_n_0
    );
p_1_out_i_34: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(10),
      I1 => AXI4_Lite_ARADDR(10),
      I2 => sel0(11),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(11),
      O => p_1_out_i_34_n_0
    );
p_1_out_i_35: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(8),
      I1 => AXI4_Lite_ARADDR(8),
      I2 => sel0(4),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(4),
      O => p_1_out_i_35_n_0
    );
p_1_out_i_36: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFACCFA"
    )
        port map (
      I0 => sel0(5),
      I1 => AXI4_Lite_ARADDR(5),
      I2 => sel0(3),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(3),
      O => p_1_out_i_36_n_0
    );
reset_pipe_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BF"
    )
        port map (
      I0 => \^soft_reset\,
      I1 => AXI4_Lite_ARESETN,
      I2 => IPCORE_RESETN,
      O => reset_in
    );
soft_reset_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000002"
    )
        port map (
      I0 => soft_reset_i_2_n_0,
      I1 => soft_reset_i_3_n_0,
      I2 => soft_reset_i_4_n_0,
      I3 => sel0(10),
      I4 => sel0(11),
      I5 => sel0(9),
      O => soft_reset_i_1_n_0
    );
soft_reset_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000400000000"
    )
        port map (
      I0 => sel0(2),
      I1 => top_wr_enb,
      I2 => sel0(1),
      I3 => sel0(13),
      I4 => sel0(4),
      I5 => AXI4_Lite_ARESETN,
      O => soft_reset_i_2_n_0
    );
soft_reset_i_3: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFD"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => sel0(3),
      I2 => sel0(12),
      I3 => sel0(7),
      O => soft_reset_i_3_n_0
    );
soft_reset_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => sel0(6),
      I1 => sel0(0),
      I2 => sel0(8),
      I3 => sel0(5),
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
      INIT => X"08"
    )
        port map (
      I0 => AXI4_Lite_AWVALID,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
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
\wdata[17]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => AXI4_Lite_WVALID,
      I1 => \^q\(0),
      O => w_transfer
    );
\wdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(0),
      Q => \wdata_reg_n_0_[0]\,
      R => reset
    );
\wdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(10),
      Q => \wdata_reg[17]_0\(9),
      R => reset
    );
\wdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(11),
      Q => \wdata_reg[17]_0\(10),
      R => reset
    );
\wdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(12),
      Q => \wdata_reg[17]_0\(11),
      R => reset
    );
\wdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(13),
      Q => \wdata_reg[17]_0\(12),
      R => reset
    );
\wdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(14),
      Q => \wdata_reg[17]_0\(13),
      R => reset
    );
\wdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(15),
      Q => \wdata_reg[17]_0\(14),
      R => reset
    );
\wdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(16),
      Q => \wdata_reg[17]_0\(15),
      R => reset
    );
\wdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(17),
      Q => \wdata_reg[17]_0\(16),
      R => reset
    );
\wdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(1),
      Q => \wdata_reg[17]_0\(0),
      R => reset
    );
\wdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(2),
      Q => \wdata_reg[17]_0\(1),
      R => reset
    );
\wdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(3),
      Q => \wdata_reg[17]_0\(2),
      R => reset
    );
\wdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(4),
      Q => \wdata_reg[17]_0\(3),
      R => reset
    );
\wdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(5),
      Q => \wdata_reg[17]_0\(4),
      R => reset
    );
\wdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(6),
      Q => \wdata_reg[17]_0\(5),
      R => reset
    );
\wdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(7),
      Q => \wdata_reg[17]_0\(6),
      R => reset
    );
\wdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(8),
      Q => \wdata_reg[17]_0\(7),
      R => reset
    );
\wdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => w_transfer,
      D => AXI4_Lite_WDATA(9),
      Q => \wdata_reg[17]_0\(8),
      R => reset
    );
wr_enb_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => \^q\(0),
      I1 => AXI4_Lite_WVALID,
      I2 => AXI4_Lite_WSTRB(2),
      I3 => AXI4_Lite_WSTRB(1),
      I4 => AXI4_Lite_WSTRB(0),
      I5 => AXI4_Lite_WSTRB(3),
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
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync is
  port (
    reset : out STD_LOGIC;
    reset_out_reg_0 : out STD_LOGIC;
    reset_in : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    soft_reset : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync : entity is "uz_pu_con_ip_reset_sync";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync is
  signal \^reset\ : STD_LOGIC;
  signal reset_out_i_1_n_0 : STD_LOGIC;
  signal reset_pipe : STD_LOGIC;
begin
  reset <= \^reset\;
\read_reg_ip_timestamp[31]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^reset\,
      O => reset_out_reg_0
    );
reset_out_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFBF"
    )
        port map (
      I0 => reset_pipe,
      I1 => IPCORE_RESETN,
      I2 => AXI4_Lite_ARESETN,
      I3 => soft_reset,
      O => reset_out_i_1_n_0
    );
reset_out_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_out_i_1_n_0,
      Q => \^reset\,
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
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion is
  port (
    out0 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out1 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out2 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out3 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out4 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out5 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out6 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out7 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out8 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out9 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out10 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out11 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out12 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out13 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out14 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out15 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out16 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out17 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out18 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out19 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out20 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out21 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out22 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out23 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out24 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out25 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out26 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out27 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out28 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out29 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out30 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out31 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    reset : in STD_LOGIC;
    adc_trigger : in STD_LOGIC;
    in0 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    IPCORE_CLK : in STD_LOGIC;
    DSP_ALU_INST : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI_pu_conv_in31 : in STD_LOGIC_VECTOR ( 16 downto 0 );
    OPMODE : in STD_LOGIC_VECTOR ( 0 to 0 );
    in1 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_0 : in STD_LOGIC;
    \out1[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in2 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_1 : in STD_LOGIC;
    \out2[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in3 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_2 : in STD_LOGIC;
    \out3[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in4 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_3 : in STD_LOGIC;
    \out4[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in5 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_4 : in STD_LOGIC;
    \out5[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in6 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_5 : in STD_LOGIC;
    \out6[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in7 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_6 : in STD_LOGIC;
    \out7[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in8 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_7 : in STD_LOGIC;
    \out8[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in9 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_8 : in STD_LOGIC;
    \out9[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in10 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_9 : in STD_LOGIC;
    \out10[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in11 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_10 : in STD_LOGIC;
    \out11[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in12 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_11 : in STD_LOGIC;
    \out12[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in13 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_12 : in STD_LOGIC;
    \out13[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in14 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_13 : in STD_LOGIC;
    \out14[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in15 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_14 : in STD_LOGIC;
    \out15[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in16 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_15 : in STD_LOGIC;
    \out16[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in17 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_16 : in STD_LOGIC;
    \out17[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in18 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_17 : in STD_LOGIC;
    \out18[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in19 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_18 : in STD_LOGIC;
    \out19[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in20 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_19 : in STD_LOGIC;
    \out20[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in21 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_20 : in STD_LOGIC;
    \out21[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in22 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_21 : in STD_LOGIC;
    \out22[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in23 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_22 : in STD_LOGIC;
    \out23[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in24 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    CEB2 : in STD_LOGIC;
    \out24[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in25 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_23 : in STD_LOGIC;
    \out25[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in26 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_24 : in STD_LOGIC;
    \out26[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in27 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_25 : in STD_LOGIC;
    \out27[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in28 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_26 : in STD_LOGIC;
    \out28[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in29 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_27 : in STD_LOGIC;
    \out29[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in30 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_28 : in STD_LOGIC;
    \out30[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in31 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_29 : in STD_LOGIC;
    \out31[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion : entity is "uz_pu_con_ip_src_uz_pu_conversion";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion is
  signal A : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__0\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__1\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__10\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__11\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__12\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__13\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__14\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__15\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__16\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__17\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__18\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__19\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__2\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__20\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__21\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__22\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__23\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__24\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__25\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__26\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__27\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__28\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__29\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__3\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__30\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__4\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__5\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__6\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__7\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__8\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal \A__9\ : STD_LOGIC_VECTOR ( 26 downto 1 );
  signal Delay10_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay11_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay12_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay13_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay14_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay15_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay16_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay17_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay18_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay19_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay1_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay20_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay21_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay22_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay23_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay24_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay25_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay26_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay27_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay28_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay29_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay2_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay30_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay31_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay3_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay4_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay5_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay6_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay7_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay8_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay9_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal Delay_out1 : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal \p_1_out__0_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__0_n_100\ : STD_LOGIC;
  signal \p_1_out__0_n_101\ : STD_LOGIC;
  signal \p_1_out__0_n_102\ : STD_LOGIC;
  signal \p_1_out__0_n_103\ : STD_LOGIC;
  signal \p_1_out__0_n_104\ : STD_LOGIC;
  signal \p_1_out__0_n_105\ : STD_LOGIC;
  signal \p_1_out__0_n_61\ : STD_LOGIC;
  signal \p_1_out__0_n_62\ : STD_LOGIC;
  signal \p_1_out__0_n_63\ : STD_LOGIC;
  signal \p_1_out__0_n_64\ : STD_LOGIC;
  signal \p_1_out__0_n_65\ : STD_LOGIC;
  signal \p_1_out__0_n_66\ : STD_LOGIC;
  signal \p_1_out__0_n_67\ : STD_LOGIC;
  signal \p_1_out__0_n_68\ : STD_LOGIC;
  signal \p_1_out__0_n_69\ : STD_LOGIC;
  signal \p_1_out__0_n_70\ : STD_LOGIC;
  signal \p_1_out__0_n_89\ : STD_LOGIC;
  signal \p_1_out__0_n_90\ : STD_LOGIC;
  signal \p_1_out__0_n_91\ : STD_LOGIC;
  signal \p_1_out__0_n_92\ : STD_LOGIC;
  signal \p_1_out__0_n_93\ : STD_LOGIC;
  signal \p_1_out__0_n_94\ : STD_LOGIC;
  signal \p_1_out__0_n_95\ : STD_LOGIC;
  signal \p_1_out__0_n_96\ : STD_LOGIC;
  signal \p_1_out__0_n_97\ : STD_LOGIC;
  signal \p_1_out__0_n_98\ : STD_LOGIC;
  signal \p_1_out__0_n_99\ : STD_LOGIC;
  signal \p_1_out__10_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__10_n_100\ : STD_LOGIC;
  signal \p_1_out__10_n_101\ : STD_LOGIC;
  signal \p_1_out__10_n_102\ : STD_LOGIC;
  signal \p_1_out__10_n_103\ : STD_LOGIC;
  signal \p_1_out__10_n_104\ : STD_LOGIC;
  signal \p_1_out__10_n_105\ : STD_LOGIC;
  signal \p_1_out__10_n_61\ : STD_LOGIC;
  signal \p_1_out__10_n_62\ : STD_LOGIC;
  signal \p_1_out__10_n_63\ : STD_LOGIC;
  signal \p_1_out__10_n_64\ : STD_LOGIC;
  signal \p_1_out__10_n_65\ : STD_LOGIC;
  signal \p_1_out__10_n_66\ : STD_LOGIC;
  signal \p_1_out__10_n_67\ : STD_LOGIC;
  signal \p_1_out__10_n_68\ : STD_LOGIC;
  signal \p_1_out__10_n_69\ : STD_LOGIC;
  signal \p_1_out__10_n_70\ : STD_LOGIC;
  signal \p_1_out__10_n_89\ : STD_LOGIC;
  signal \p_1_out__10_n_90\ : STD_LOGIC;
  signal \p_1_out__10_n_91\ : STD_LOGIC;
  signal \p_1_out__10_n_92\ : STD_LOGIC;
  signal \p_1_out__10_n_93\ : STD_LOGIC;
  signal \p_1_out__10_n_94\ : STD_LOGIC;
  signal \p_1_out__10_n_95\ : STD_LOGIC;
  signal \p_1_out__10_n_96\ : STD_LOGIC;
  signal \p_1_out__10_n_97\ : STD_LOGIC;
  signal \p_1_out__10_n_98\ : STD_LOGIC;
  signal \p_1_out__10_n_99\ : STD_LOGIC;
  signal \p_1_out__11_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__11_n_100\ : STD_LOGIC;
  signal \p_1_out__11_n_101\ : STD_LOGIC;
  signal \p_1_out__11_n_102\ : STD_LOGIC;
  signal \p_1_out__11_n_103\ : STD_LOGIC;
  signal \p_1_out__11_n_104\ : STD_LOGIC;
  signal \p_1_out__11_n_105\ : STD_LOGIC;
  signal \p_1_out__11_n_61\ : STD_LOGIC;
  signal \p_1_out__11_n_62\ : STD_LOGIC;
  signal \p_1_out__11_n_63\ : STD_LOGIC;
  signal \p_1_out__11_n_64\ : STD_LOGIC;
  signal \p_1_out__11_n_65\ : STD_LOGIC;
  signal \p_1_out__11_n_66\ : STD_LOGIC;
  signal \p_1_out__11_n_67\ : STD_LOGIC;
  signal \p_1_out__11_n_68\ : STD_LOGIC;
  signal \p_1_out__11_n_69\ : STD_LOGIC;
  signal \p_1_out__11_n_70\ : STD_LOGIC;
  signal \p_1_out__11_n_89\ : STD_LOGIC;
  signal \p_1_out__11_n_90\ : STD_LOGIC;
  signal \p_1_out__11_n_91\ : STD_LOGIC;
  signal \p_1_out__11_n_92\ : STD_LOGIC;
  signal \p_1_out__11_n_93\ : STD_LOGIC;
  signal \p_1_out__11_n_94\ : STD_LOGIC;
  signal \p_1_out__11_n_95\ : STD_LOGIC;
  signal \p_1_out__11_n_96\ : STD_LOGIC;
  signal \p_1_out__11_n_97\ : STD_LOGIC;
  signal \p_1_out__11_n_98\ : STD_LOGIC;
  signal \p_1_out__11_n_99\ : STD_LOGIC;
  signal \p_1_out__12_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__12_n_100\ : STD_LOGIC;
  signal \p_1_out__12_n_101\ : STD_LOGIC;
  signal \p_1_out__12_n_102\ : STD_LOGIC;
  signal \p_1_out__12_n_103\ : STD_LOGIC;
  signal \p_1_out__12_n_104\ : STD_LOGIC;
  signal \p_1_out__12_n_105\ : STD_LOGIC;
  signal \p_1_out__12_n_61\ : STD_LOGIC;
  signal \p_1_out__12_n_62\ : STD_LOGIC;
  signal \p_1_out__12_n_63\ : STD_LOGIC;
  signal \p_1_out__12_n_64\ : STD_LOGIC;
  signal \p_1_out__12_n_65\ : STD_LOGIC;
  signal \p_1_out__12_n_66\ : STD_LOGIC;
  signal \p_1_out__12_n_67\ : STD_LOGIC;
  signal \p_1_out__12_n_68\ : STD_LOGIC;
  signal \p_1_out__12_n_69\ : STD_LOGIC;
  signal \p_1_out__12_n_70\ : STD_LOGIC;
  signal \p_1_out__12_n_89\ : STD_LOGIC;
  signal \p_1_out__12_n_90\ : STD_LOGIC;
  signal \p_1_out__12_n_91\ : STD_LOGIC;
  signal \p_1_out__12_n_92\ : STD_LOGIC;
  signal \p_1_out__12_n_93\ : STD_LOGIC;
  signal \p_1_out__12_n_94\ : STD_LOGIC;
  signal \p_1_out__12_n_95\ : STD_LOGIC;
  signal \p_1_out__12_n_96\ : STD_LOGIC;
  signal \p_1_out__12_n_97\ : STD_LOGIC;
  signal \p_1_out__12_n_98\ : STD_LOGIC;
  signal \p_1_out__12_n_99\ : STD_LOGIC;
  signal \p_1_out__13_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__13_n_100\ : STD_LOGIC;
  signal \p_1_out__13_n_101\ : STD_LOGIC;
  signal \p_1_out__13_n_102\ : STD_LOGIC;
  signal \p_1_out__13_n_103\ : STD_LOGIC;
  signal \p_1_out__13_n_104\ : STD_LOGIC;
  signal \p_1_out__13_n_105\ : STD_LOGIC;
  signal \p_1_out__13_n_61\ : STD_LOGIC;
  signal \p_1_out__13_n_62\ : STD_LOGIC;
  signal \p_1_out__13_n_63\ : STD_LOGIC;
  signal \p_1_out__13_n_64\ : STD_LOGIC;
  signal \p_1_out__13_n_65\ : STD_LOGIC;
  signal \p_1_out__13_n_66\ : STD_LOGIC;
  signal \p_1_out__13_n_67\ : STD_LOGIC;
  signal \p_1_out__13_n_68\ : STD_LOGIC;
  signal \p_1_out__13_n_69\ : STD_LOGIC;
  signal \p_1_out__13_n_70\ : STD_LOGIC;
  signal \p_1_out__13_n_89\ : STD_LOGIC;
  signal \p_1_out__13_n_90\ : STD_LOGIC;
  signal \p_1_out__13_n_91\ : STD_LOGIC;
  signal \p_1_out__13_n_92\ : STD_LOGIC;
  signal \p_1_out__13_n_93\ : STD_LOGIC;
  signal \p_1_out__13_n_94\ : STD_LOGIC;
  signal \p_1_out__13_n_95\ : STD_LOGIC;
  signal \p_1_out__13_n_96\ : STD_LOGIC;
  signal \p_1_out__13_n_97\ : STD_LOGIC;
  signal \p_1_out__13_n_98\ : STD_LOGIC;
  signal \p_1_out__13_n_99\ : STD_LOGIC;
  signal \p_1_out__14_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__14_n_100\ : STD_LOGIC;
  signal \p_1_out__14_n_101\ : STD_LOGIC;
  signal \p_1_out__14_n_102\ : STD_LOGIC;
  signal \p_1_out__14_n_103\ : STD_LOGIC;
  signal \p_1_out__14_n_104\ : STD_LOGIC;
  signal \p_1_out__14_n_105\ : STD_LOGIC;
  signal \p_1_out__14_n_61\ : STD_LOGIC;
  signal \p_1_out__14_n_62\ : STD_LOGIC;
  signal \p_1_out__14_n_63\ : STD_LOGIC;
  signal \p_1_out__14_n_64\ : STD_LOGIC;
  signal \p_1_out__14_n_65\ : STD_LOGIC;
  signal \p_1_out__14_n_66\ : STD_LOGIC;
  signal \p_1_out__14_n_67\ : STD_LOGIC;
  signal \p_1_out__14_n_68\ : STD_LOGIC;
  signal \p_1_out__14_n_69\ : STD_LOGIC;
  signal \p_1_out__14_n_70\ : STD_LOGIC;
  signal \p_1_out__14_n_89\ : STD_LOGIC;
  signal \p_1_out__14_n_90\ : STD_LOGIC;
  signal \p_1_out__14_n_91\ : STD_LOGIC;
  signal \p_1_out__14_n_92\ : STD_LOGIC;
  signal \p_1_out__14_n_93\ : STD_LOGIC;
  signal \p_1_out__14_n_94\ : STD_LOGIC;
  signal \p_1_out__14_n_95\ : STD_LOGIC;
  signal \p_1_out__14_n_96\ : STD_LOGIC;
  signal \p_1_out__14_n_97\ : STD_LOGIC;
  signal \p_1_out__14_n_98\ : STD_LOGIC;
  signal \p_1_out__14_n_99\ : STD_LOGIC;
  signal \p_1_out__15_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__15_n_100\ : STD_LOGIC;
  signal \p_1_out__15_n_101\ : STD_LOGIC;
  signal \p_1_out__15_n_102\ : STD_LOGIC;
  signal \p_1_out__15_n_103\ : STD_LOGIC;
  signal \p_1_out__15_n_104\ : STD_LOGIC;
  signal \p_1_out__15_n_105\ : STD_LOGIC;
  signal \p_1_out__15_n_61\ : STD_LOGIC;
  signal \p_1_out__15_n_62\ : STD_LOGIC;
  signal \p_1_out__15_n_63\ : STD_LOGIC;
  signal \p_1_out__15_n_64\ : STD_LOGIC;
  signal \p_1_out__15_n_65\ : STD_LOGIC;
  signal \p_1_out__15_n_66\ : STD_LOGIC;
  signal \p_1_out__15_n_67\ : STD_LOGIC;
  signal \p_1_out__15_n_68\ : STD_LOGIC;
  signal \p_1_out__15_n_69\ : STD_LOGIC;
  signal \p_1_out__15_n_70\ : STD_LOGIC;
  signal \p_1_out__15_n_89\ : STD_LOGIC;
  signal \p_1_out__15_n_90\ : STD_LOGIC;
  signal \p_1_out__15_n_91\ : STD_LOGIC;
  signal \p_1_out__15_n_92\ : STD_LOGIC;
  signal \p_1_out__15_n_93\ : STD_LOGIC;
  signal \p_1_out__15_n_94\ : STD_LOGIC;
  signal \p_1_out__15_n_95\ : STD_LOGIC;
  signal \p_1_out__15_n_96\ : STD_LOGIC;
  signal \p_1_out__15_n_97\ : STD_LOGIC;
  signal \p_1_out__15_n_98\ : STD_LOGIC;
  signal \p_1_out__15_n_99\ : STD_LOGIC;
  signal \p_1_out__16_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__16_n_100\ : STD_LOGIC;
  signal \p_1_out__16_n_101\ : STD_LOGIC;
  signal \p_1_out__16_n_102\ : STD_LOGIC;
  signal \p_1_out__16_n_103\ : STD_LOGIC;
  signal \p_1_out__16_n_104\ : STD_LOGIC;
  signal \p_1_out__16_n_105\ : STD_LOGIC;
  signal \p_1_out__16_n_61\ : STD_LOGIC;
  signal \p_1_out__16_n_62\ : STD_LOGIC;
  signal \p_1_out__16_n_63\ : STD_LOGIC;
  signal \p_1_out__16_n_64\ : STD_LOGIC;
  signal \p_1_out__16_n_65\ : STD_LOGIC;
  signal \p_1_out__16_n_66\ : STD_LOGIC;
  signal \p_1_out__16_n_67\ : STD_LOGIC;
  signal \p_1_out__16_n_68\ : STD_LOGIC;
  signal \p_1_out__16_n_69\ : STD_LOGIC;
  signal \p_1_out__16_n_70\ : STD_LOGIC;
  signal \p_1_out__16_n_89\ : STD_LOGIC;
  signal \p_1_out__16_n_90\ : STD_LOGIC;
  signal \p_1_out__16_n_91\ : STD_LOGIC;
  signal \p_1_out__16_n_92\ : STD_LOGIC;
  signal \p_1_out__16_n_93\ : STD_LOGIC;
  signal \p_1_out__16_n_94\ : STD_LOGIC;
  signal \p_1_out__16_n_95\ : STD_LOGIC;
  signal \p_1_out__16_n_96\ : STD_LOGIC;
  signal \p_1_out__16_n_97\ : STD_LOGIC;
  signal \p_1_out__16_n_98\ : STD_LOGIC;
  signal \p_1_out__16_n_99\ : STD_LOGIC;
  signal \p_1_out__17_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__17_n_100\ : STD_LOGIC;
  signal \p_1_out__17_n_101\ : STD_LOGIC;
  signal \p_1_out__17_n_102\ : STD_LOGIC;
  signal \p_1_out__17_n_103\ : STD_LOGIC;
  signal \p_1_out__17_n_104\ : STD_LOGIC;
  signal \p_1_out__17_n_105\ : STD_LOGIC;
  signal \p_1_out__17_n_61\ : STD_LOGIC;
  signal \p_1_out__17_n_62\ : STD_LOGIC;
  signal \p_1_out__17_n_63\ : STD_LOGIC;
  signal \p_1_out__17_n_64\ : STD_LOGIC;
  signal \p_1_out__17_n_65\ : STD_LOGIC;
  signal \p_1_out__17_n_66\ : STD_LOGIC;
  signal \p_1_out__17_n_67\ : STD_LOGIC;
  signal \p_1_out__17_n_68\ : STD_LOGIC;
  signal \p_1_out__17_n_69\ : STD_LOGIC;
  signal \p_1_out__17_n_70\ : STD_LOGIC;
  signal \p_1_out__17_n_89\ : STD_LOGIC;
  signal \p_1_out__17_n_90\ : STD_LOGIC;
  signal \p_1_out__17_n_91\ : STD_LOGIC;
  signal \p_1_out__17_n_92\ : STD_LOGIC;
  signal \p_1_out__17_n_93\ : STD_LOGIC;
  signal \p_1_out__17_n_94\ : STD_LOGIC;
  signal \p_1_out__17_n_95\ : STD_LOGIC;
  signal \p_1_out__17_n_96\ : STD_LOGIC;
  signal \p_1_out__17_n_97\ : STD_LOGIC;
  signal \p_1_out__17_n_98\ : STD_LOGIC;
  signal \p_1_out__17_n_99\ : STD_LOGIC;
  signal \p_1_out__18_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__18_n_100\ : STD_LOGIC;
  signal \p_1_out__18_n_101\ : STD_LOGIC;
  signal \p_1_out__18_n_102\ : STD_LOGIC;
  signal \p_1_out__18_n_103\ : STD_LOGIC;
  signal \p_1_out__18_n_104\ : STD_LOGIC;
  signal \p_1_out__18_n_105\ : STD_LOGIC;
  signal \p_1_out__18_n_61\ : STD_LOGIC;
  signal \p_1_out__18_n_62\ : STD_LOGIC;
  signal \p_1_out__18_n_63\ : STD_LOGIC;
  signal \p_1_out__18_n_64\ : STD_LOGIC;
  signal \p_1_out__18_n_65\ : STD_LOGIC;
  signal \p_1_out__18_n_66\ : STD_LOGIC;
  signal \p_1_out__18_n_67\ : STD_LOGIC;
  signal \p_1_out__18_n_68\ : STD_LOGIC;
  signal \p_1_out__18_n_69\ : STD_LOGIC;
  signal \p_1_out__18_n_70\ : STD_LOGIC;
  signal \p_1_out__18_n_89\ : STD_LOGIC;
  signal \p_1_out__18_n_90\ : STD_LOGIC;
  signal \p_1_out__18_n_91\ : STD_LOGIC;
  signal \p_1_out__18_n_92\ : STD_LOGIC;
  signal \p_1_out__18_n_93\ : STD_LOGIC;
  signal \p_1_out__18_n_94\ : STD_LOGIC;
  signal \p_1_out__18_n_95\ : STD_LOGIC;
  signal \p_1_out__18_n_96\ : STD_LOGIC;
  signal \p_1_out__18_n_97\ : STD_LOGIC;
  signal \p_1_out__18_n_98\ : STD_LOGIC;
  signal \p_1_out__18_n_99\ : STD_LOGIC;
  signal \p_1_out__19_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__19_n_100\ : STD_LOGIC;
  signal \p_1_out__19_n_101\ : STD_LOGIC;
  signal \p_1_out__19_n_102\ : STD_LOGIC;
  signal \p_1_out__19_n_103\ : STD_LOGIC;
  signal \p_1_out__19_n_104\ : STD_LOGIC;
  signal \p_1_out__19_n_105\ : STD_LOGIC;
  signal \p_1_out__19_n_61\ : STD_LOGIC;
  signal \p_1_out__19_n_62\ : STD_LOGIC;
  signal \p_1_out__19_n_63\ : STD_LOGIC;
  signal \p_1_out__19_n_64\ : STD_LOGIC;
  signal \p_1_out__19_n_65\ : STD_LOGIC;
  signal \p_1_out__19_n_66\ : STD_LOGIC;
  signal \p_1_out__19_n_67\ : STD_LOGIC;
  signal \p_1_out__19_n_68\ : STD_LOGIC;
  signal \p_1_out__19_n_69\ : STD_LOGIC;
  signal \p_1_out__19_n_70\ : STD_LOGIC;
  signal \p_1_out__19_n_89\ : STD_LOGIC;
  signal \p_1_out__19_n_90\ : STD_LOGIC;
  signal \p_1_out__19_n_91\ : STD_LOGIC;
  signal \p_1_out__19_n_92\ : STD_LOGIC;
  signal \p_1_out__19_n_93\ : STD_LOGIC;
  signal \p_1_out__19_n_94\ : STD_LOGIC;
  signal \p_1_out__19_n_95\ : STD_LOGIC;
  signal \p_1_out__19_n_96\ : STD_LOGIC;
  signal \p_1_out__19_n_97\ : STD_LOGIC;
  signal \p_1_out__19_n_98\ : STD_LOGIC;
  signal \p_1_out__19_n_99\ : STD_LOGIC;
  signal \p_1_out__1_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__1_n_100\ : STD_LOGIC;
  signal \p_1_out__1_n_101\ : STD_LOGIC;
  signal \p_1_out__1_n_102\ : STD_LOGIC;
  signal \p_1_out__1_n_103\ : STD_LOGIC;
  signal \p_1_out__1_n_104\ : STD_LOGIC;
  signal \p_1_out__1_n_105\ : STD_LOGIC;
  signal \p_1_out__1_n_61\ : STD_LOGIC;
  signal \p_1_out__1_n_62\ : STD_LOGIC;
  signal \p_1_out__1_n_63\ : STD_LOGIC;
  signal \p_1_out__1_n_64\ : STD_LOGIC;
  signal \p_1_out__1_n_65\ : STD_LOGIC;
  signal \p_1_out__1_n_66\ : STD_LOGIC;
  signal \p_1_out__1_n_67\ : STD_LOGIC;
  signal \p_1_out__1_n_68\ : STD_LOGIC;
  signal \p_1_out__1_n_69\ : STD_LOGIC;
  signal \p_1_out__1_n_70\ : STD_LOGIC;
  signal \p_1_out__1_n_89\ : STD_LOGIC;
  signal \p_1_out__1_n_90\ : STD_LOGIC;
  signal \p_1_out__1_n_91\ : STD_LOGIC;
  signal \p_1_out__1_n_92\ : STD_LOGIC;
  signal \p_1_out__1_n_93\ : STD_LOGIC;
  signal \p_1_out__1_n_94\ : STD_LOGIC;
  signal \p_1_out__1_n_95\ : STD_LOGIC;
  signal \p_1_out__1_n_96\ : STD_LOGIC;
  signal \p_1_out__1_n_97\ : STD_LOGIC;
  signal \p_1_out__1_n_98\ : STD_LOGIC;
  signal \p_1_out__1_n_99\ : STD_LOGIC;
  signal \p_1_out__20_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__20_n_100\ : STD_LOGIC;
  signal \p_1_out__20_n_101\ : STD_LOGIC;
  signal \p_1_out__20_n_102\ : STD_LOGIC;
  signal \p_1_out__20_n_103\ : STD_LOGIC;
  signal \p_1_out__20_n_104\ : STD_LOGIC;
  signal \p_1_out__20_n_105\ : STD_LOGIC;
  signal \p_1_out__20_n_61\ : STD_LOGIC;
  signal \p_1_out__20_n_62\ : STD_LOGIC;
  signal \p_1_out__20_n_63\ : STD_LOGIC;
  signal \p_1_out__20_n_64\ : STD_LOGIC;
  signal \p_1_out__20_n_65\ : STD_LOGIC;
  signal \p_1_out__20_n_66\ : STD_LOGIC;
  signal \p_1_out__20_n_67\ : STD_LOGIC;
  signal \p_1_out__20_n_68\ : STD_LOGIC;
  signal \p_1_out__20_n_69\ : STD_LOGIC;
  signal \p_1_out__20_n_70\ : STD_LOGIC;
  signal \p_1_out__20_n_89\ : STD_LOGIC;
  signal \p_1_out__20_n_90\ : STD_LOGIC;
  signal \p_1_out__20_n_91\ : STD_LOGIC;
  signal \p_1_out__20_n_92\ : STD_LOGIC;
  signal \p_1_out__20_n_93\ : STD_LOGIC;
  signal \p_1_out__20_n_94\ : STD_LOGIC;
  signal \p_1_out__20_n_95\ : STD_LOGIC;
  signal \p_1_out__20_n_96\ : STD_LOGIC;
  signal \p_1_out__20_n_97\ : STD_LOGIC;
  signal \p_1_out__20_n_98\ : STD_LOGIC;
  signal \p_1_out__20_n_99\ : STD_LOGIC;
  signal \p_1_out__21_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__21_n_100\ : STD_LOGIC;
  signal \p_1_out__21_n_101\ : STD_LOGIC;
  signal \p_1_out__21_n_102\ : STD_LOGIC;
  signal \p_1_out__21_n_103\ : STD_LOGIC;
  signal \p_1_out__21_n_104\ : STD_LOGIC;
  signal \p_1_out__21_n_105\ : STD_LOGIC;
  signal \p_1_out__21_n_61\ : STD_LOGIC;
  signal \p_1_out__21_n_62\ : STD_LOGIC;
  signal \p_1_out__21_n_63\ : STD_LOGIC;
  signal \p_1_out__21_n_64\ : STD_LOGIC;
  signal \p_1_out__21_n_65\ : STD_LOGIC;
  signal \p_1_out__21_n_66\ : STD_LOGIC;
  signal \p_1_out__21_n_67\ : STD_LOGIC;
  signal \p_1_out__21_n_68\ : STD_LOGIC;
  signal \p_1_out__21_n_69\ : STD_LOGIC;
  signal \p_1_out__21_n_70\ : STD_LOGIC;
  signal \p_1_out__21_n_89\ : STD_LOGIC;
  signal \p_1_out__21_n_90\ : STD_LOGIC;
  signal \p_1_out__21_n_91\ : STD_LOGIC;
  signal \p_1_out__21_n_92\ : STD_LOGIC;
  signal \p_1_out__21_n_93\ : STD_LOGIC;
  signal \p_1_out__21_n_94\ : STD_LOGIC;
  signal \p_1_out__21_n_95\ : STD_LOGIC;
  signal \p_1_out__21_n_96\ : STD_LOGIC;
  signal \p_1_out__21_n_97\ : STD_LOGIC;
  signal \p_1_out__21_n_98\ : STD_LOGIC;
  signal \p_1_out__21_n_99\ : STD_LOGIC;
  signal \p_1_out__22_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__22_n_100\ : STD_LOGIC;
  signal \p_1_out__22_n_101\ : STD_LOGIC;
  signal \p_1_out__22_n_102\ : STD_LOGIC;
  signal \p_1_out__22_n_103\ : STD_LOGIC;
  signal \p_1_out__22_n_104\ : STD_LOGIC;
  signal \p_1_out__22_n_105\ : STD_LOGIC;
  signal \p_1_out__22_n_61\ : STD_LOGIC;
  signal \p_1_out__22_n_62\ : STD_LOGIC;
  signal \p_1_out__22_n_63\ : STD_LOGIC;
  signal \p_1_out__22_n_64\ : STD_LOGIC;
  signal \p_1_out__22_n_65\ : STD_LOGIC;
  signal \p_1_out__22_n_66\ : STD_LOGIC;
  signal \p_1_out__22_n_67\ : STD_LOGIC;
  signal \p_1_out__22_n_68\ : STD_LOGIC;
  signal \p_1_out__22_n_69\ : STD_LOGIC;
  signal \p_1_out__22_n_70\ : STD_LOGIC;
  signal \p_1_out__22_n_89\ : STD_LOGIC;
  signal \p_1_out__22_n_90\ : STD_LOGIC;
  signal \p_1_out__22_n_91\ : STD_LOGIC;
  signal \p_1_out__22_n_92\ : STD_LOGIC;
  signal \p_1_out__22_n_93\ : STD_LOGIC;
  signal \p_1_out__22_n_94\ : STD_LOGIC;
  signal \p_1_out__22_n_95\ : STD_LOGIC;
  signal \p_1_out__22_n_96\ : STD_LOGIC;
  signal \p_1_out__22_n_97\ : STD_LOGIC;
  signal \p_1_out__22_n_98\ : STD_LOGIC;
  signal \p_1_out__22_n_99\ : STD_LOGIC;
  signal \p_1_out__23_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__23_n_100\ : STD_LOGIC;
  signal \p_1_out__23_n_101\ : STD_LOGIC;
  signal \p_1_out__23_n_102\ : STD_LOGIC;
  signal \p_1_out__23_n_103\ : STD_LOGIC;
  signal \p_1_out__23_n_104\ : STD_LOGIC;
  signal \p_1_out__23_n_105\ : STD_LOGIC;
  signal \p_1_out__23_n_61\ : STD_LOGIC;
  signal \p_1_out__23_n_62\ : STD_LOGIC;
  signal \p_1_out__23_n_63\ : STD_LOGIC;
  signal \p_1_out__23_n_64\ : STD_LOGIC;
  signal \p_1_out__23_n_65\ : STD_LOGIC;
  signal \p_1_out__23_n_66\ : STD_LOGIC;
  signal \p_1_out__23_n_67\ : STD_LOGIC;
  signal \p_1_out__23_n_68\ : STD_LOGIC;
  signal \p_1_out__23_n_69\ : STD_LOGIC;
  signal \p_1_out__23_n_70\ : STD_LOGIC;
  signal \p_1_out__23_n_89\ : STD_LOGIC;
  signal \p_1_out__23_n_90\ : STD_LOGIC;
  signal \p_1_out__23_n_91\ : STD_LOGIC;
  signal \p_1_out__23_n_92\ : STD_LOGIC;
  signal \p_1_out__23_n_93\ : STD_LOGIC;
  signal \p_1_out__23_n_94\ : STD_LOGIC;
  signal \p_1_out__23_n_95\ : STD_LOGIC;
  signal \p_1_out__23_n_96\ : STD_LOGIC;
  signal \p_1_out__23_n_97\ : STD_LOGIC;
  signal \p_1_out__23_n_98\ : STD_LOGIC;
  signal \p_1_out__23_n_99\ : STD_LOGIC;
  signal \p_1_out__24_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__24_n_100\ : STD_LOGIC;
  signal \p_1_out__24_n_101\ : STD_LOGIC;
  signal \p_1_out__24_n_102\ : STD_LOGIC;
  signal \p_1_out__24_n_103\ : STD_LOGIC;
  signal \p_1_out__24_n_104\ : STD_LOGIC;
  signal \p_1_out__24_n_105\ : STD_LOGIC;
  signal \p_1_out__24_n_61\ : STD_LOGIC;
  signal \p_1_out__24_n_62\ : STD_LOGIC;
  signal \p_1_out__24_n_63\ : STD_LOGIC;
  signal \p_1_out__24_n_64\ : STD_LOGIC;
  signal \p_1_out__24_n_65\ : STD_LOGIC;
  signal \p_1_out__24_n_66\ : STD_LOGIC;
  signal \p_1_out__24_n_67\ : STD_LOGIC;
  signal \p_1_out__24_n_68\ : STD_LOGIC;
  signal \p_1_out__24_n_69\ : STD_LOGIC;
  signal \p_1_out__24_n_70\ : STD_LOGIC;
  signal \p_1_out__24_n_89\ : STD_LOGIC;
  signal \p_1_out__24_n_90\ : STD_LOGIC;
  signal \p_1_out__24_n_91\ : STD_LOGIC;
  signal \p_1_out__24_n_92\ : STD_LOGIC;
  signal \p_1_out__24_n_93\ : STD_LOGIC;
  signal \p_1_out__24_n_94\ : STD_LOGIC;
  signal \p_1_out__24_n_95\ : STD_LOGIC;
  signal \p_1_out__24_n_96\ : STD_LOGIC;
  signal \p_1_out__24_n_97\ : STD_LOGIC;
  signal \p_1_out__24_n_98\ : STD_LOGIC;
  signal \p_1_out__24_n_99\ : STD_LOGIC;
  signal \p_1_out__25_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__25_n_100\ : STD_LOGIC;
  signal \p_1_out__25_n_101\ : STD_LOGIC;
  signal \p_1_out__25_n_102\ : STD_LOGIC;
  signal \p_1_out__25_n_103\ : STD_LOGIC;
  signal \p_1_out__25_n_104\ : STD_LOGIC;
  signal \p_1_out__25_n_105\ : STD_LOGIC;
  signal \p_1_out__25_n_61\ : STD_LOGIC;
  signal \p_1_out__25_n_62\ : STD_LOGIC;
  signal \p_1_out__25_n_63\ : STD_LOGIC;
  signal \p_1_out__25_n_64\ : STD_LOGIC;
  signal \p_1_out__25_n_65\ : STD_LOGIC;
  signal \p_1_out__25_n_66\ : STD_LOGIC;
  signal \p_1_out__25_n_67\ : STD_LOGIC;
  signal \p_1_out__25_n_68\ : STD_LOGIC;
  signal \p_1_out__25_n_69\ : STD_LOGIC;
  signal \p_1_out__25_n_70\ : STD_LOGIC;
  signal \p_1_out__25_n_89\ : STD_LOGIC;
  signal \p_1_out__25_n_90\ : STD_LOGIC;
  signal \p_1_out__25_n_91\ : STD_LOGIC;
  signal \p_1_out__25_n_92\ : STD_LOGIC;
  signal \p_1_out__25_n_93\ : STD_LOGIC;
  signal \p_1_out__25_n_94\ : STD_LOGIC;
  signal \p_1_out__25_n_95\ : STD_LOGIC;
  signal \p_1_out__25_n_96\ : STD_LOGIC;
  signal \p_1_out__25_n_97\ : STD_LOGIC;
  signal \p_1_out__25_n_98\ : STD_LOGIC;
  signal \p_1_out__25_n_99\ : STD_LOGIC;
  signal \p_1_out__26_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__26_n_100\ : STD_LOGIC;
  signal \p_1_out__26_n_101\ : STD_LOGIC;
  signal \p_1_out__26_n_102\ : STD_LOGIC;
  signal \p_1_out__26_n_103\ : STD_LOGIC;
  signal \p_1_out__26_n_104\ : STD_LOGIC;
  signal \p_1_out__26_n_105\ : STD_LOGIC;
  signal \p_1_out__26_n_61\ : STD_LOGIC;
  signal \p_1_out__26_n_62\ : STD_LOGIC;
  signal \p_1_out__26_n_63\ : STD_LOGIC;
  signal \p_1_out__26_n_64\ : STD_LOGIC;
  signal \p_1_out__26_n_65\ : STD_LOGIC;
  signal \p_1_out__26_n_66\ : STD_LOGIC;
  signal \p_1_out__26_n_67\ : STD_LOGIC;
  signal \p_1_out__26_n_68\ : STD_LOGIC;
  signal \p_1_out__26_n_69\ : STD_LOGIC;
  signal \p_1_out__26_n_70\ : STD_LOGIC;
  signal \p_1_out__26_n_89\ : STD_LOGIC;
  signal \p_1_out__26_n_90\ : STD_LOGIC;
  signal \p_1_out__26_n_91\ : STD_LOGIC;
  signal \p_1_out__26_n_92\ : STD_LOGIC;
  signal \p_1_out__26_n_93\ : STD_LOGIC;
  signal \p_1_out__26_n_94\ : STD_LOGIC;
  signal \p_1_out__26_n_95\ : STD_LOGIC;
  signal \p_1_out__26_n_96\ : STD_LOGIC;
  signal \p_1_out__26_n_97\ : STD_LOGIC;
  signal \p_1_out__26_n_98\ : STD_LOGIC;
  signal \p_1_out__26_n_99\ : STD_LOGIC;
  signal \p_1_out__27_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__27_n_100\ : STD_LOGIC;
  signal \p_1_out__27_n_101\ : STD_LOGIC;
  signal \p_1_out__27_n_102\ : STD_LOGIC;
  signal \p_1_out__27_n_103\ : STD_LOGIC;
  signal \p_1_out__27_n_104\ : STD_LOGIC;
  signal \p_1_out__27_n_105\ : STD_LOGIC;
  signal \p_1_out__27_n_61\ : STD_LOGIC;
  signal \p_1_out__27_n_62\ : STD_LOGIC;
  signal \p_1_out__27_n_63\ : STD_LOGIC;
  signal \p_1_out__27_n_64\ : STD_LOGIC;
  signal \p_1_out__27_n_65\ : STD_LOGIC;
  signal \p_1_out__27_n_66\ : STD_LOGIC;
  signal \p_1_out__27_n_67\ : STD_LOGIC;
  signal \p_1_out__27_n_68\ : STD_LOGIC;
  signal \p_1_out__27_n_69\ : STD_LOGIC;
  signal \p_1_out__27_n_70\ : STD_LOGIC;
  signal \p_1_out__27_n_89\ : STD_LOGIC;
  signal \p_1_out__27_n_90\ : STD_LOGIC;
  signal \p_1_out__27_n_91\ : STD_LOGIC;
  signal \p_1_out__27_n_92\ : STD_LOGIC;
  signal \p_1_out__27_n_93\ : STD_LOGIC;
  signal \p_1_out__27_n_94\ : STD_LOGIC;
  signal \p_1_out__27_n_95\ : STD_LOGIC;
  signal \p_1_out__27_n_96\ : STD_LOGIC;
  signal \p_1_out__27_n_97\ : STD_LOGIC;
  signal \p_1_out__27_n_98\ : STD_LOGIC;
  signal \p_1_out__27_n_99\ : STD_LOGIC;
  signal \p_1_out__28_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__28_n_100\ : STD_LOGIC;
  signal \p_1_out__28_n_101\ : STD_LOGIC;
  signal \p_1_out__28_n_102\ : STD_LOGIC;
  signal \p_1_out__28_n_103\ : STD_LOGIC;
  signal \p_1_out__28_n_104\ : STD_LOGIC;
  signal \p_1_out__28_n_105\ : STD_LOGIC;
  signal \p_1_out__28_n_61\ : STD_LOGIC;
  signal \p_1_out__28_n_62\ : STD_LOGIC;
  signal \p_1_out__28_n_63\ : STD_LOGIC;
  signal \p_1_out__28_n_64\ : STD_LOGIC;
  signal \p_1_out__28_n_65\ : STD_LOGIC;
  signal \p_1_out__28_n_66\ : STD_LOGIC;
  signal \p_1_out__28_n_67\ : STD_LOGIC;
  signal \p_1_out__28_n_68\ : STD_LOGIC;
  signal \p_1_out__28_n_69\ : STD_LOGIC;
  signal \p_1_out__28_n_70\ : STD_LOGIC;
  signal \p_1_out__28_n_89\ : STD_LOGIC;
  signal \p_1_out__28_n_90\ : STD_LOGIC;
  signal \p_1_out__28_n_91\ : STD_LOGIC;
  signal \p_1_out__28_n_92\ : STD_LOGIC;
  signal \p_1_out__28_n_93\ : STD_LOGIC;
  signal \p_1_out__28_n_94\ : STD_LOGIC;
  signal \p_1_out__28_n_95\ : STD_LOGIC;
  signal \p_1_out__28_n_96\ : STD_LOGIC;
  signal \p_1_out__28_n_97\ : STD_LOGIC;
  signal \p_1_out__28_n_98\ : STD_LOGIC;
  signal \p_1_out__28_n_99\ : STD_LOGIC;
  signal \p_1_out__29_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__29_n_100\ : STD_LOGIC;
  signal \p_1_out__29_n_101\ : STD_LOGIC;
  signal \p_1_out__29_n_102\ : STD_LOGIC;
  signal \p_1_out__29_n_103\ : STD_LOGIC;
  signal \p_1_out__29_n_104\ : STD_LOGIC;
  signal \p_1_out__29_n_105\ : STD_LOGIC;
  signal \p_1_out__29_n_61\ : STD_LOGIC;
  signal \p_1_out__29_n_62\ : STD_LOGIC;
  signal \p_1_out__29_n_63\ : STD_LOGIC;
  signal \p_1_out__29_n_64\ : STD_LOGIC;
  signal \p_1_out__29_n_65\ : STD_LOGIC;
  signal \p_1_out__29_n_66\ : STD_LOGIC;
  signal \p_1_out__29_n_67\ : STD_LOGIC;
  signal \p_1_out__29_n_68\ : STD_LOGIC;
  signal \p_1_out__29_n_69\ : STD_LOGIC;
  signal \p_1_out__29_n_70\ : STD_LOGIC;
  signal \p_1_out__29_n_89\ : STD_LOGIC;
  signal \p_1_out__29_n_90\ : STD_LOGIC;
  signal \p_1_out__29_n_91\ : STD_LOGIC;
  signal \p_1_out__29_n_92\ : STD_LOGIC;
  signal \p_1_out__29_n_93\ : STD_LOGIC;
  signal \p_1_out__29_n_94\ : STD_LOGIC;
  signal \p_1_out__29_n_95\ : STD_LOGIC;
  signal \p_1_out__29_n_96\ : STD_LOGIC;
  signal \p_1_out__29_n_97\ : STD_LOGIC;
  signal \p_1_out__29_n_98\ : STD_LOGIC;
  signal \p_1_out__29_n_99\ : STD_LOGIC;
  signal \p_1_out__2_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__2_n_100\ : STD_LOGIC;
  signal \p_1_out__2_n_101\ : STD_LOGIC;
  signal \p_1_out__2_n_102\ : STD_LOGIC;
  signal \p_1_out__2_n_103\ : STD_LOGIC;
  signal \p_1_out__2_n_104\ : STD_LOGIC;
  signal \p_1_out__2_n_105\ : STD_LOGIC;
  signal \p_1_out__2_n_61\ : STD_LOGIC;
  signal \p_1_out__2_n_62\ : STD_LOGIC;
  signal \p_1_out__2_n_63\ : STD_LOGIC;
  signal \p_1_out__2_n_64\ : STD_LOGIC;
  signal \p_1_out__2_n_65\ : STD_LOGIC;
  signal \p_1_out__2_n_66\ : STD_LOGIC;
  signal \p_1_out__2_n_67\ : STD_LOGIC;
  signal \p_1_out__2_n_68\ : STD_LOGIC;
  signal \p_1_out__2_n_69\ : STD_LOGIC;
  signal \p_1_out__2_n_70\ : STD_LOGIC;
  signal \p_1_out__2_n_89\ : STD_LOGIC;
  signal \p_1_out__2_n_90\ : STD_LOGIC;
  signal \p_1_out__2_n_91\ : STD_LOGIC;
  signal \p_1_out__2_n_92\ : STD_LOGIC;
  signal \p_1_out__2_n_93\ : STD_LOGIC;
  signal \p_1_out__2_n_94\ : STD_LOGIC;
  signal \p_1_out__2_n_95\ : STD_LOGIC;
  signal \p_1_out__2_n_96\ : STD_LOGIC;
  signal \p_1_out__2_n_97\ : STD_LOGIC;
  signal \p_1_out__2_n_98\ : STD_LOGIC;
  signal \p_1_out__2_n_99\ : STD_LOGIC;
  signal \p_1_out__30_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__30_n_100\ : STD_LOGIC;
  signal \p_1_out__30_n_101\ : STD_LOGIC;
  signal \p_1_out__30_n_102\ : STD_LOGIC;
  signal \p_1_out__30_n_103\ : STD_LOGIC;
  signal \p_1_out__30_n_104\ : STD_LOGIC;
  signal \p_1_out__30_n_105\ : STD_LOGIC;
  signal \p_1_out__30_n_61\ : STD_LOGIC;
  signal \p_1_out__30_n_62\ : STD_LOGIC;
  signal \p_1_out__30_n_63\ : STD_LOGIC;
  signal \p_1_out__30_n_64\ : STD_LOGIC;
  signal \p_1_out__30_n_65\ : STD_LOGIC;
  signal \p_1_out__30_n_66\ : STD_LOGIC;
  signal \p_1_out__30_n_67\ : STD_LOGIC;
  signal \p_1_out__30_n_68\ : STD_LOGIC;
  signal \p_1_out__30_n_69\ : STD_LOGIC;
  signal \p_1_out__30_n_70\ : STD_LOGIC;
  signal \p_1_out__30_n_89\ : STD_LOGIC;
  signal \p_1_out__30_n_90\ : STD_LOGIC;
  signal \p_1_out__30_n_91\ : STD_LOGIC;
  signal \p_1_out__30_n_92\ : STD_LOGIC;
  signal \p_1_out__30_n_93\ : STD_LOGIC;
  signal \p_1_out__30_n_94\ : STD_LOGIC;
  signal \p_1_out__30_n_95\ : STD_LOGIC;
  signal \p_1_out__30_n_96\ : STD_LOGIC;
  signal \p_1_out__30_n_97\ : STD_LOGIC;
  signal \p_1_out__30_n_98\ : STD_LOGIC;
  signal \p_1_out__30_n_99\ : STD_LOGIC;
  signal \p_1_out__3_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__3_n_100\ : STD_LOGIC;
  signal \p_1_out__3_n_101\ : STD_LOGIC;
  signal \p_1_out__3_n_102\ : STD_LOGIC;
  signal \p_1_out__3_n_103\ : STD_LOGIC;
  signal \p_1_out__3_n_104\ : STD_LOGIC;
  signal \p_1_out__3_n_105\ : STD_LOGIC;
  signal \p_1_out__3_n_61\ : STD_LOGIC;
  signal \p_1_out__3_n_62\ : STD_LOGIC;
  signal \p_1_out__3_n_63\ : STD_LOGIC;
  signal \p_1_out__3_n_64\ : STD_LOGIC;
  signal \p_1_out__3_n_65\ : STD_LOGIC;
  signal \p_1_out__3_n_66\ : STD_LOGIC;
  signal \p_1_out__3_n_67\ : STD_LOGIC;
  signal \p_1_out__3_n_68\ : STD_LOGIC;
  signal \p_1_out__3_n_69\ : STD_LOGIC;
  signal \p_1_out__3_n_70\ : STD_LOGIC;
  signal \p_1_out__3_n_89\ : STD_LOGIC;
  signal \p_1_out__3_n_90\ : STD_LOGIC;
  signal \p_1_out__3_n_91\ : STD_LOGIC;
  signal \p_1_out__3_n_92\ : STD_LOGIC;
  signal \p_1_out__3_n_93\ : STD_LOGIC;
  signal \p_1_out__3_n_94\ : STD_LOGIC;
  signal \p_1_out__3_n_95\ : STD_LOGIC;
  signal \p_1_out__3_n_96\ : STD_LOGIC;
  signal \p_1_out__3_n_97\ : STD_LOGIC;
  signal \p_1_out__3_n_98\ : STD_LOGIC;
  signal \p_1_out__3_n_99\ : STD_LOGIC;
  signal \p_1_out__4_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__4_n_100\ : STD_LOGIC;
  signal \p_1_out__4_n_101\ : STD_LOGIC;
  signal \p_1_out__4_n_102\ : STD_LOGIC;
  signal \p_1_out__4_n_103\ : STD_LOGIC;
  signal \p_1_out__4_n_104\ : STD_LOGIC;
  signal \p_1_out__4_n_105\ : STD_LOGIC;
  signal \p_1_out__4_n_61\ : STD_LOGIC;
  signal \p_1_out__4_n_62\ : STD_LOGIC;
  signal \p_1_out__4_n_63\ : STD_LOGIC;
  signal \p_1_out__4_n_64\ : STD_LOGIC;
  signal \p_1_out__4_n_65\ : STD_LOGIC;
  signal \p_1_out__4_n_66\ : STD_LOGIC;
  signal \p_1_out__4_n_67\ : STD_LOGIC;
  signal \p_1_out__4_n_68\ : STD_LOGIC;
  signal \p_1_out__4_n_69\ : STD_LOGIC;
  signal \p_1_out__4_n_70\ : STD_LOGIC;
  signal \p_1_out__4_n_89\ : STD_LOGIC;
  signal \p_1_out__4_n_90\ : STD_LOGIC;
  signal \p_1_out__4_n_91\ : STD_LOGIC;
  signal \p_1_out__4_n_92\ : STD_LOGIC;
  signal \p_1_out__4_n_93\ : STD_LOGIC;
  signal \p_1_out__4_n_94\ : STD_LOGIC;
  signal \p_1_out__4_n_95\ : STD_LOGIC;
  signal \p_1_out__4_n_96\ : STD_LOGIC;
  signal \p_1_out__4_n_97\ : STD_LOGIC;
  signal \p_1_out__4_n_98\ : STD_LOGIC;
  signal \p_1_out__4_n_99\ : STD_LOGIC;
  signal \p_1_out__5_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__5_n_100\ : STD_LOGIC;
  signal \p_1_out__5_n_101\ : STD_LOGIC;
  signal \p_1_out__5_n_102\ : STD_LOGIC;
  signal \p_1_out__5_n_103\ : STD_LOGIC;
  signal \p_1_out__5_n_104\ : STD_LOGIC;
  signal \p_1_out__5_n_105\ : STD_LOGIC;
  signal \p_1_out__5_n_61\ : STD_LOGIC;
  signal \p_1_out__5_n_62\ : STD_LOGIC;
  signal \p_1_out__5_n_63\ : STD_LOGIC;
  signal \p_1_out__5_n_64\ : STD_LOGIC;
  signal \p_1_out__5_n_65\ : STD_LOGIC;
  signal \p_1_out__5_n_66\ : STD_LOGIC;
  signal \p_1_out__5_n_67\ : STD_LOGIC;
  signal \p_1_out__5_n_68\ : STD_LOGIC;
  signal \p_1_out__5_n_69\ : STD_LOGIC;
  signal \p_1_out__5_n_70\ : STD_LOGIC;
  signal \p_1_out__5_n_89\ : STD_LOGIC;
  signal \p_1_out__5_n_90\ : STD_LOGIC;
  signal \p_1_out__5_n_91\ : STD_LOGIC;
  signal \p_1_out__5_n_92\ : STD_LOGIC;
  signal \p_1_out__5_n_93\ : STD_LOGIC;
  signal \p_1_out__5_n_94\ : STD_LOGIC;
  signal \p_1_out__5_n_95\ : STD_LOGIC;
  signal \p_1_out__5_n_96\ : STD_LOGIC;
  signal \p_1_out__5_n_97\ : STD_LOGIC;
  signal \p_1_out__5_n_98\ : STD_LOGIC;
  signal \p_1_out__5_n_99\ : STD_LOGIC;
  signal \p_1_out__6_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__6_n_100\ : STD_LOGIC;
  signal \p_1_out__6_n_101\ : STD_LOGIC;
  signal \p_1_out__6_n_102\ : STD_LOGIC;
  signal \p_1_out__6_n_103\ : STD_LOGIC;
  signal \p_1_out__6_n_104\ : STD_LOGIC;
  signal \p_1_out__6_n_105\ : STD_LOGIC;
  signal \p_1_out__6_n_61\ : STD_LOGIC;
  signal \p_1_out__6_n_62\ : STD_LOGIC;
  signal \p_1_out__6_n_63\ : STD_LOGIC;
  signal \p_1_out__6_n_64\ : STD_LOGIC;
  signal \p_1_out__6_n_65\ : STD_LOGIC;
  signal \p_1_out__6_n_66\ : STD_LOGIC;
  signal \p_1_out__6_n_67\ : STD_LOGIC;
  signal \p_1_out__6_n_68\ : STD_LOGIC;
  signal \p_1_out__6_n_69\ : STD_LOGIC;
  signal \p_1_out__6_n_70\ : STD_LOGIC;
  signal \p_1_out__6_n_89\ : STD_LOGIC;
  signal \p_1_out__6_n_90\ : STD_LOGIC;
  signal \p_1_out__6_n_91\ : STD_LOGIC;
  signal \p_1_out__6_n_92\ : STD_LOGIC;
  signal \p_1_out__6_n_93\ : STD_LOGIC;
  signal \p_1_out__6_n_94\ : STD_LOGIC;
  signal \p_1_out__6_n_95\ : STD_LOGIC;
  signal \p_1_out__6_n_96\ : STD_LOGIC;
  signal \p_1_out__6_n_97\ : STD_LOGIC;
  signal \p_1_out__6_n_98\ : STD_LOGIC;
  signal \p_1_out__6_n_99\ : STD_LOGIC;
  signal \p_1_out__7_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__7_n_100\ : STD_LOGIC;
  signal \p_1_out__7_n_101\ : STD_LOGIC;
  signal \p_1_out__7_n_102\ : STD_LOGIC;
  signal \p_1_out__7_n_103\ : STD_LOGIC;
  signal \p_1_out__7_n_104\ : STD_LOGIC;
  signal \p_1_out__7_n_105\ : STD_LOGIC;
  signal \p_1_out__7_n_61\ : STD_LOGIC;
  signal \p_1_out__7_n_62\ : STD_LOGIC;
  signal \p_1_out__7_n_63\ : STD_LOGIC;
  signal \p_1_out__7_n_64\ : STD_LOGIC;
  signal \p_1_out__7_n_65\ : STD_LOGIC;
  signal \p_1_out__7_n_66\ : STD_LOGIC;
  signal \p_1_out__7_n_67\ : STD_LOGIC;
  signal \p_1_out__7_n_68\ : STD_LOGIC;
  signal \p_1_out__7_n_69\ : STD_LOGIC;
  signal \p_1_out__7_n_70\ : STD_LOGIC;
  signal \p_1_out__7_n_89\ : STD_LOGIC;
  signal \p_1_out__7_n_90\ : STD_LOGIC;
  signal \p_1_out__7_n_91\ : STD_LOGIC;
  signal \p_1_out__7_n_92\ : STD_LOGIC;
  signal \p_1_out__7_n_93\ : STD_LOGIC;
  signal \p_1_out__7_n_94\ : STD_LOGIC;
  signal \p_1_out__7_n_95\ : STD_LOGIC;
  signal \p_1_out__7_n_96\ : STD_LOGIC;
  signal \p_1_out__7_n_97\ : STD_LOGIC;
  signal \p_1_out__7_n_98\ : STD_LOGIC;
  signal \p_1_out__7_n_99\ : STD_LOGIC;
  signal \p_1_out__8_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__8_n_100\ : STD_LOGIC;
  signal \p_1_out__8_n_101\ : STD_LOGIC;
  signal \p_1_out__8_n_102\ : STD_LOGIC;
  signal \p_1_out__8_n_103\ : STD_LOGIC;
  signal \p_1_out__8_n_104\ : STD_LOGIC;
  signal \p_1_out__8_n_105\ : STD_LOGIC;
  signal \p_1_out__8_n_61\ : STD_LOGIC;
  signal \p_1_out__8_n_62\ : STD_LOGIC;
  signal \p_1_out__8_n_63\ : STD_LOGIC;
  signal \p_1_out__8_n_64\ : STD_LOGIC;
  signal \p_1_out__8_n_65\ : STD_LOGIC;
  signal \p_1_out__8_n_66\ : STD_LOGIC;
  signal \p_1_out__8_n_67\ : STD_LOGIC;
  signal \p_1_out__8_n_68\ : STD_LOGIC;
  signal \p_1_out__8_n_69\ : STD_LOGIC;
  signal \p_1_out__8_n_70\ : STD_LOGIC;
  signal \p_1_out__8_n_89\ : STD_LOGIC;
  signal \p_1_out__8_n_90\ : STD_LOGIC;
  signal \p_1_out__8_n_91\ : STD_LOGIC;
  signal \p_1_out__8_n_92\ : STD_LOGIC;
  signal \p_1_out__8_n_93\ : STD_LOGIC;
  signal \p_1_out__8_n_94\ : STD_LOGIC;
  signal \p_1_out__8_n_95\ : STD_LOGIC;
  signal \p_1_out__8_n_96\ : STD_LOGIC;
  signal \p_1_out__8_n_97\ : STD_LOGIC;
  signal \p_1_out__8_n_98\ : STD_LOGIC;
  signal \p_1_out__8_n_99\ : STD_LOGIC;
  signal \p_1_out__9_i_28_n_0\ : STD_LOGIC;
  signal \p_1_out__9_n_100\ : STD_LOGIC;
  signal \p_1_out__9_n_101\ : STD_LOGIC;
  signal \p_1_out__9_n_102\ : STD_LOGIC;
  signal \p_1_out__9_n_103\ : STD_LOGIC;
  signal \p_1_out__9_n_104\ : STD_LOGIC;
  signal \p_1_out__9_n_105\ : STD_LOGIC;
  signal \p_1_out__9_n_61\ : STD_LOGIC;
  signal \p_1_out__9_n_62\ : STD_LOGIC;
  signal \p_1_out__9_n_63\ : STD_LOGIC;
  signal \p_1_out__9_n_64\ : STD_LOGIC;
  signal \p_1_out__9_n_65\ : STD_LOGIC;
  signal \p_1_out__9_n_66\ : STD_LOGIC;
  signal \p_1_out__9_n_67\ : STD_LOGIC;
  signal \p_1_out__9_n_68\ : STD_LOGIC;
  signal \p_1_out__9_n_69\ : STD_LOGIC;
  signal \p_1_out__9_n_70\ : STD_LOGIC;
  signal \p_1_out__9_n_89\ : STD_LOGIC;
  signal \p_1_out__9_n_90\ : STD_LOGIC;
  signal \p_1_out__9_n_91\ : STD_LOGIC;
  signal \p_1_out__9_n_92\ : STD_LOGIC;
  signal \p_1_out__9_n_93\ : STD_LOGIC;
  signal \p_1_out__9_n_94\ : STD_LOGIC;
  signal \p_1_out__9_n_95\ : STD_LOGIC;
  signal \p_1_out__9_n_96\ : STD_LOGIC;
  signal \p_1_out__9_n_97\ : STD_LOGIC;
  signal \p_1_out__9_n_98\ : STD_LOGIC;
  signal \p_1_out__9_n_99\ : STD_LOGIC;
  signal p_1_out_i_28_n_0 : STD_LOGIC;
  signal p_1_out_n_100 : STD_LOGIC;
  signal p_1_out_n_101 : STD_LOGIC;
  signal p_1_out_n_102 : STD_LOGIC;
  signal p_1_out_n_103 : STD_LOGIC;
  signal p_1_out_n_104 : STD_LOGIC;
  signal p_1_out_n_105 : STD_LOGIC;
  signal p_1_out_n_61 : STD_LOGIC;
  signal p_1_out_n_62 : STD_LOGIC;
  signal p_1_out_n_63 : STD_LOGIC;
  signal p_1_out_n_64 : STD_LOGIC;
  signal p_1_out_n_65 : STD_LOGIC;
  signal p_1_out_n_66 : STD_LOGIC;
  signal p_1_out_n_67 : STD_LOGIC;
  signal p_1_out_n_68 : STD_LOGIC;
  signal p_1_out_n_69 : STD_LOGIC;
  signal p_1_out_n_70 : STD_LOGIC;
  signal p_1_out_n_89 : STD_LOGIC;
  signal p_1_out_n_90 : STD_LOGIC;
  signal p_1_out_n_91 : STD_LOGIC;
  signal p_1_out_n_92 : STD_LOGIC;
  signal p_1_out_n_93 : STD_LOGIC;
  signal p_1_out_n_94 : STD_LOGIC;
  signal p_1_out_n_95 : STD_LOGIC;
  signal p_1_out_n_96 : STD_LOGIC;
  signal p_1_out_n_97 : STD_LOGIC;
  signal p_1_out_n_98 : STD_LOGIC;
  signal p_1_out_n_99 : STD_LOGIC;
  signal NLW_p_1_out_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_p_1_out_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_p_1_out_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_p_1_out_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_p_1_out_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_p_1_out_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_p_1_out_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_p_1_out_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_p_1_out_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_p_1_out_P_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal NLW_p_1_out_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_p_1_out_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__0_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__0_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__0_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__0_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__0_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__0_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__0_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__0_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__0_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__0_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__0_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__0_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__1_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__1_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__1_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__1_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__1_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__1_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__1_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__1_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__1_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__1_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__1_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__1_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__10_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__10_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__10_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__10_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__10_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__10_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__10_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__10_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__10_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__10_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__10_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__10_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__11_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__11_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__11_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__11_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__11_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__11_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__11_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__11_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__11_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__11_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__11_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__11_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__12_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__12_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__12_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__12_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__12_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__12_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__12_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__12_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__12_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__12_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__12_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__12_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__13_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__13_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__13_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__13_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__13_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__13_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__13_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__13_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__13_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__13_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__13_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__13_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__14_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__14_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__14_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__14_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__14_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__14_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__14_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__14_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__14_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__14_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__14_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__14_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__15_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__15_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__15_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__15_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__15_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__15_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__15_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__15_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__15_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__15_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__15_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__15_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__16_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__16_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__16_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__16_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__16_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__16_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__16_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__16_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__16_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__16_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__16_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__16_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__17_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__17_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__17_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__17_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__17_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__17_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__17_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__17_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__17_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__17_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__17_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__17_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__18_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__18_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__18_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__18_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__18_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__18_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__18_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__18_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__18_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__18_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__18_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__18_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__19_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__19_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__19_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__19_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__19_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__19_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__19_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__19_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__19_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__19_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__19_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__19_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__2_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__2_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__2_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__2_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__2_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__2_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__2_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__2_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__2_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__2_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__2_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__2_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__20_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__20_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__20_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__20_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__20_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__20_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__20_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__20_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__20_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__20_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__20_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__20_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__21_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__21_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__21_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__21_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__21_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__21_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__21_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__21_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__21_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__21_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__21_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__21_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__22_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__22_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__22_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__22_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__22_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__22_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__22_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__22_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__22_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__22_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__22_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__22_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__23_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__23_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__23_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__23_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__23_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__23_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__23_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__23_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__23_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__23_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__23_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__23_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__24_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__24_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__24_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__24_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__24_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__24_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__24_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__24_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__24_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__24_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__24_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__24_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__25_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__25_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__25_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__25_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__25_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__25_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__25_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__25_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__25_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__25_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__25_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__25_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__26_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__26_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__26_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__26_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__26_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__26_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__26_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__26_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__26_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__26_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__26_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__26_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__27_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__27_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__27_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__27_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__27_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__27_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__27_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__27_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__27_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__27_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__27_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__27_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__28_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__28_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__28_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__28_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__28_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__28_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__28_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__28_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__28_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__28_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__28_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__28_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__29_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__29_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__29_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__29_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__29_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__29_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__29_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__29_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__29_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__29_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__29_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__29_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__3_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__3_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__3_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__3_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__3_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__3_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__3_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__3_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__3_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__3_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__3_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__3_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__30_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__30_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__30_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__30_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__30_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__30_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__30_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__30_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__30_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__30_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__30_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__30_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__4_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__4_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__4_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__4_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__4_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__4_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__4_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__4_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__4_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__4_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__4_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__4_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__5_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__5_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__5_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__5_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__5_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__5_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__5_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__5_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__5_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__5_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__5_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__5_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__6_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__6_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__6_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__6_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__6_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__6_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__6_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__6_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__6_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__6_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__6_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__6_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__7_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__7_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__7_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__7_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__7_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__7_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__7_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__7_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__7_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__7_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__7_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__7_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__8_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__8_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__8_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__8_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__8_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__8_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__8_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__8_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__8_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__8_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__8_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__8_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_p_1_out__9_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__9_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__9_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__9_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__9_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__9_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_p_1_out__9_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_p_1_out__9_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_p_1_out__9_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_p_1_out__9_P_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 45 );
  signal \NLW_p_1_out__9_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_p_1_out__9_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of p_1_out : label is "yes";
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of p_1_out : label is "{SYNTH-11 {cell *THIS*}}";
  attribute KEEP_HIERARCHY of \p_1_out__0\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__0\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \p_1_out__0_i_10\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \p_1_out__0_i_11\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \p_1_out__0_i_12\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \p_1_out__0_i_13\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \p_1_out__0_i_14\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \p_1_out__0_i_15\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \p_1_out__0_i_16\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \p_1_out__0_i_17\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \p_1_out__0_i_18\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \p_1_out__0_i_19\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \p_1_out__0_i_2\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \p_1_out__0_i_20\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of \p_1_out__0_i_21\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of \p_1_out__0_i_22\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \p_1_out__0_i_23\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \p_1_out__0_i_24\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \p_1_out__0_i_25\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \p_1_out__0_i_26\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \p_1_out__0_i_27\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \p_1_out__0_i_28\ : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of \p_1_out__0_i_3\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \p_1_out__0_i_4\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \p_1_out__0_i_5\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \p_1_out__0_i_6\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \p_1_out__0_i_7\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \p_1_out__0_i_8\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \p_1_out__0_i_9\ : label is "soft_lutpair46";
  attribute KEEP_HIERARCHY of \p_1_out__1\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__1\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute KEEP_HIERARCHY of \p_1_out__10\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__10\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__10_i_10\ : label is "soft_lutpair180";
  attribute SOFT_HLUTNM of \p_1_out__10_i_11\ : label is "soft_lutpair180";
  attribute SOFT_HLUTNM of \p_1_out__10_i_12\ : label is "soft_lutpair179";
  attribute SOFT_HLUTNM of \p_1_out__10_i_13\ : label is "soft_lutpair179";
  attribute SOFT_HLUTNM of \p_1_out__10_i_14\ : label is "soft_lutpair178";
  attribute SOFT_HLUTNM of \p_1_out__10_i_15\ : label is "soft_lutpair178";
  attribute SOFT_HLUTNM of \p_1_out__10_i_16\ : label is "soft_lutpair177";
  attribute SOFT_HLUTNM of \p_1_out__10_i_17\ : label is "soft_lutpair177";
  attribute SOFT_HLUTNM of \p_1_out__10_i_18\ : label is "soft_lutpair176";
  attribute SOFT_HLUTNM of \p_1_out__10_i_19\ : label is "soft_lutpair176";
  attribute SOFT_HLUTNM of \p_1_out__10_i_2\ : label is "soft_lutpair184";
  attribute SOFT_HLUTNM of \p_1_out__10_i_20\ : label is "soft_lutpair175";
  attribute SOFT_HLUTNM of \p_1_out__10_i_21\ : label is "soft_lutpair175";
  attribute SOFT_HLUTNM of \p_1_out__10_i_22\ : label is "soft_lutpair174";
  attribute SOFT_HLUTNM of \p_1_out__10_i_23\ : label is "soft_lutpair174";
  attribute SOFT_HLUTNM of \p_1_out__10_i_24\ : label is "soft_lutpair173";
  attribute SOFT_HLUTNM of \p_1_out__10_i_25\ : label is "soft_lutpair173";
  attribute SOFT_HLUTNM of \p_1_out__10_i_26\ : label is "soft_lutpair172";
  attribute SOFT_HLUTNM of \p_1_out__10_i_27\ : label is "soft_lutpair172";
  attribute SOFT_HLUTNM of \p_1_out__10_i_28\ : label is "soft_lutpair171";
  attribute SOFT_HLUTNM of \p_1_out__10_i_3\ : label is "soft_lutpair184";
  attribute SOFT_HLUTNM of \p_1_out__10_i_4\ : label is "soft_lutpair183";
  attribute SOFT_HLUTNM of \p_1_out__10_i_5\ : label is "soft_lutpair183";
  attribute SOFT_HLUTNM of \p_1_out__10_i_6\ : label is "soft_lutpair182";
  attribute SOFT_HLUTNM of \p_1_out__10_i_7\ : label is "soft_lutpair182";
  attribute SOFT_HLUTNM of \p_1_out__10_i_8\ : label is "soft_lutpair181";
  attribute SOFT_HLUTNM of \p_1_out__10_i_9\ : label is "soft_lutpair181";
  attribute KEEP_HIERARCHY of \p_1_out__11\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__11\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__11_i_10\ : label is "soft_lutpair194";
  attribute SOFT_HLUTNM of \p_1_out__11_i_11\ : label is "soft_lutpair193";
  attribute SOFT_HLUTNM of \p_1_out__11_i_12\ : label is "soft_lutpair193";
  attribute SOFT_HLUTNM of \p_1_out__11_i_13\ : label is "soft_lutpair192";
  attribute SOFT_HLUTNM of \p_1_out__11_i_14\ : label is "soft_lutpair192";
  attribute SOFT_HLUTNM of \p_1_out__11_i_15\ : label is "soft_lutpair191";
  attribute SOFT_HLUTNM of \p_1_out__11_i_16\ : label is "soft_lutpair191";
  attribute SOFT_HLUTNM of \p_1_out__11_i_17\ : label is "soft_lutpair190";
  attribute SOFT_HLUTNM of \p_1_out__11_i_18\ : label is "soft_lutpair190";
  attribute SOFT_HLUTNM of \p_1_out__11_i_19\ : label is "soft_lutpair189";
  attribute SOFT_HLUTNM of \p_1_out__11_i_2\ : label is "soft_lutpair198";
  attribute SOFT_HLUTNM of \p_1_out__11_i_20\ : label is "soft_lutpair189";
  attribute SOFT_HLUTNM of \p_1_out__11_i_21\ : label is "soft_lutpair188";
  attribute SOFT_HLUTNM of \p_1_out__11_i_22\ : label is "soft_lutpair188";
  attribute SOFT_HLUTNM of \p_1_out__11_i_23\ : label is "soft_lutpair187";
  attribute SOFT_HLUTNM of \p_1_out__11_i_24\ : label is "soft_lutpair187";
  attribute SOFT_HLUTNM of \p_1_out__11_i_25\ : label is "soft_lutpair186";
  attribute SOFT_HLUTNM of \p_1_out__11_i_26\ : label is "soft_lutpair186";
  attribute SOFT_HLUTNM of \p_1_out__11_i_27\ : label is "soft_lutpair185";
  attribute SOFT_HLUTNM of \p_1_out__11_i_28\ : label is "soft_lutpair185";
  attribute SOFT_HLUTNM of \p_1_out__11_i_3\ : label is "soft_lutpair197";
  attribute SOFT_HLUTNM of \p_1_out__11_i_4\ : label is "soft_lutpair197";
  attribute SOFT_HLUTNM of \p_1_out__11_i_5\ : label is "soft_lutpair196";
  attribute SOFT_HLUTNM of \p_1_out__11_i_6\ : label is "soft_lutpair196";
  attribute SOFT_HLUTNM of \p_1_out__11_i_7\ : label is "soft_lutpair195";
  attribute SOFT_HLUTNM of \p_1_out__11_i_8\ : label is "soft_lutpair195";
  attribute SOFT_HLUTNM of \p_1_out__11_i_9\ : label is "soft_lutpair194";
  attribute KEEP_HIERARCHY of \p_1_out__12\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__12\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__12_i_10\ : label is "soft_lutpair207";
  attribute SOFT_HLUTNM of \p_1_out__12_i_11\ : label is "soft_lutpair207";
  attribute SOFT_HLUTNM of \p_1_out__12_i_12\ : label is "soft_lutpair206";
  attribute SOFT_HLUTNM of \p_1_out__12_i_13\ : label is "soft_lutpair206";
  attribute SOFT_HLUTNM of \p_1_out__12_i_14\ : label is "soft_lutpair205";
  attribute SOFT_HLUTNM of \p_1_out__12_i_15\ : label is "soft_lutpair205";
  attribute SOFT_HLUTNM of \p_1_out__12_i_16\ : label is "soft_lutpair204";
  attribute SOFT_HLUTNM of \p_1_out__12_i_17\ : label is "soft_lutpair204";
  attribute SOFT_HLUTNM of \p_1_out__12_i_18\ : label is "soft_lutpair203";
  attribute SOFT_HLUTNM of \p_1_out__12_i_19\ : label is "soft_lutpair203";
  attribute SOFT_HLUTNM of \p_1_out__12_i_2\ : label is "soft_lutpair211";
  attribute SOFT_HLUTNM of \p_1_out__12_i_20\ : label is "soft_lutpair202";
  attribute SOFT_HLUTNM of \p_1_out__12_i_21\ : label is "soft_lutpair202";
  attribute SOFT_HLUTNM of \p_1_out__12_i_22\ : label is "soft_lutpair201";
  attribute SOFT_HLUTNM of \p_1_out__12_i_23\ : label is "soft_lutpair201";
  attribute SOFT_HLUTNM of \p_1_out__12_i_24\ : label is "soft_lutpair200";
  attribute SOFT_HLUTNM of \p_1_out__12_i_25\ : label is "soft_lutpair200";
  attribute SOFT_HLUTNM of \p_1_out__12_i_26\ : label is "soft_lutpair199";
  attribute SOFT_HLUTNM of \p_1_out__12_i_27\ : label is "soft_lutpair199";
  attribute SOFT_HLUTNM of \p_1_out__12_i_28\ : label is "soft_lutpair198";
  attribute SOFT_HLUTNM of \p_1_out__12_i_3\ : label is "soft_lutpair211";
  attribute SOFT_HLUTNM of \p_1_out__12_i_4\ : label is "soft_lutpair210";
  attribute SOFT_HLUTNM of \p_1_out__12_i_5\ : label is "soft_lutpair210";
  attribute SOFT_HLUTNM of \p_1_out__12_i_6\ : label is "soft_lutpair209";
  attribute SOFT_HLUTNM of \p_1_out__12_i_7\ : label is "soft_lutpair209";
  attribute SOFT_HLUTNM of \p_1_out__12_i_8\ : label is "soft_lutpair208";
  attribute SOFT_HLUTNM of \p_1_out__12_i_9\ : label is "soft_lutpair208";
  attribute KEEP_HIERARCHY of \p_1_out__13\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__13\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__13_i_10\ : label is "soft_lutpair221";
  attribute SOFT_HLUTNM of \p_1_out__13_i_11\ : label is "soft_lutpair220";
  attribute SOFT_HLUTNM of \p_1_out__13_i_12\ : label is "soft_lutpair220";
  attribute SOFT_HLUTNM of \p_1_out__13_i_13\ : label is "soft_lutpair219";
  attribute SOFT_HLUTNM of \p_1_out__13_i_14\ : label is "soft_lutpair219";
  attribute SOFT_HLUTNM of \p_1_out__13_i_15\ : label is "soft_lutpair218";
  attribute SOFT_HLUTNM of \p_1_out__13_i_16\ : label is "soft_lutpair218";
  attribute SOFT_HLUTNM of \p_1_out__13_i_17\ : label is "soft_lutpair217";
  attribute SOFT_HLUTNM of \p_1_out__13_i_18\ : label is "soft_lutpair217";
  attribute SOFT_HLUTNM of \p_1_out__13_i_19\ : label is "soft_lutpair216";
  attribute SOFT_HLUTNM of \p_1_out__13_i_2\ : label is "soft_lutpair225";
  attribute SOFT_HLUTNM of \p_1_out__13_i_20\ : label is "soft_lutpair216";
  attribute SOFT_HLUTNM of \p_1_out__13_i_21\ : label is "soft_lutpair215";
  attribute SOFT_HLUTNM of \p_1_out__13_i_22\ : label is "soft_lutpair215";
  attribute SOFT_HLUTNM of \p_1_out__13_i_23\ : label is "soft_lutpair214";
  attribute SOFT_HLUTNM of \p_1_out__13_i_24\ : label is "soft_lutpair214";
  attribute SOFT_HLUTNM of \p_1_out__13_i_25\ : label is "soft_lutpair213";
  attribute SOFT_HLUTNM of \p_1_out__13_i_26\ : label is "soft_lutpair213";
  attribute SOFT_HLUTNM of \p_1_out__13_i_27\ : label is "soft_lutpair212";
  attribute SOFT_HLUTNM of \p_1_out__13_i_28\ : label is "soft_lutpair212";
  attribute SOFT_HLUTNM of \p_1_out__13_i_3\ : label is "soft_lutpair224";
  attribute SOFT_HLUTNM of \p_1_out__13_i_4\ : label is "soft_lutpair224";
  attribute SOFT_HLUTNM of \p_1_out__13_i_5\ : label is "soft_lutpair223";
  attribute SOFT_HLUTNM of \p_1_out__13_i_6\ : label is "soft_lutpair223";
  attribute SOFT_HLUTNM of \p_1_out__13_i_7\ : label is "soft_lutpair222";
  attribute SOFT_HLUTNM of \p_1_out__13_i_8\ : label is "soft_lutpair222";
  attribute SOFT_HLUTNM of \p_1_out__13_i_9\ : label is "soft_lutpair221";
  attribute KEEP_HIERARCHY of \p_1_out__14\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__14\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__14_i_10\ : label is "soft_lutpair234";
  attribute SOFT_HLUTNM of \p_1_out__14_i_11\ : label is "soft_lutpair234";
  attribute SOFT_HLUTNM of \p_1_out__14_i_12\ : label is "soft_lutpair233";
  attribute SOFT_HLUTNM of \p_1_out__14_i_13\ : label is "soft_lutpair233";
  attribute SOFT_HLUTNM of \p_1_out__14_i_14\ : label is "soft_lutpair232";
  attribute SOFT_HLUTNM of \p_1_out__14_i_15\ : label is "soft_lutpair232";
  attribute SOFT_HLUTNM of \p_1_out__14_i_16\ : label is "soft_lutpair231";
  attribute SOFT_HLUTNM of \p_1_out__14_i_17\ : label is "soft_lutpair231";
  attribute SOFT_HLUTNM of \p_1_out__14_i_18\ : label is "soft_lutpair230";
  attribute SOFT_HLUTNM of \p_1_out__14_i_19\ : label is "soft_lutpair230";
  attribute SOFT_HLUTNM of \p_1_out__14_i_2\ : label is "soft_lutpair238";
  attribute SOFT_HLUTNM of \p_1_out__14_i_20\ : label is "soft_lutpair229";
  attribute SOFT_HLUTNM of \p_1_out__14_i_21\ : label is "soft_lutpair229";
  attribute SOFT_HLUTNM of \p_1_out__14_i_22\ : label is "soft_lutpair228";
  attribute SOFT_HLUTNM of \p_1_out__14_i_23\ : label is "soft_lutpair228";
  attribute SOFT_HLUTNM of \p_1_out__14_i_24\ : label is "soft_lutpair227";
  attribute SOFT_HLUTNM of \p_1_out__14_i_25\ : label is "soft_lutpair227";
  attribute SOFT_HLUTNM of \p_1_out__14_i_26\ : label is "soft_lutpair226";
  attribute SOFT_HLUTNM of \p_1_out__14_i_27\ : label is "soft_lutpair226";
  attribute SOFT_HLUTNM of \p_1_out__14_i_28\ : label is "soft_lutpair225";
  attribute SOFT_HLUTNM of \p_1_out__14_i_3\ : label is "soft_lutpair238";
  attribute SOFT_HLUTNM of \p_1_out__14_i_4\ : label is "soft_lutpair237";
  attribute SOFT_HLUTNM of \p_1_out__14_i_5\ : label is "soft_lutpair237";
  attribute SOFT_HLUTNM of \p_1_out__14_i_6\ : label is "soft_lutpair236";
  attribute SOFT_HLUTNM of \p_1_out__14_i_7\ : label is "soft_lutpair236";
  attribute SOFT_HLUTNM of \p_1_out__14_i_8\ : label is "soft_lutpair235";
  attribute SOFT_HLUTNM of \p_1_out__14_i_9\ : label is "soft_lutpair235";
  attribute KEEP_HIERARCHY of \p_1_out__15\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__15\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__15_i_10\ : label is "soft_lutpair248";
  attribute SOFT_HLUTNM of \p_1_out__15_i_11\ : label is "soft_lutpair247";
  attribute SOFT_HLUTNM of \p_1_out__15_i_12\ : label is "soft_lutpair247";
  attribute SOFT_HLUTNM of \p_1_out__15_i_13\ : label is "soft_lutpair246";
  attribute SOFT_HLUTNM of \p_1_out__15_i_14\ : label is "soft_lutpair246";
  attribute SOFT_HLUTNM of \p_1_out__15_i_15\ : label is "soft_lutpair245";
  attribute SOFT_HLUTNM of \p_1_out__15_i_16\ : label is "soft_lutpair245";
  attribute SOFT_HLUTNM of \p_1_out__15_i_17\ : label is "soft_lutpair244";
  attribute SOFT_HLUTNM of \p_1_out__15_i_18\ : label is "soft_lutpair244";
  attribute SOFT_HLUTNM of \p_1_out__15_i_19\ : label is "soft_lutpair243";
  attribute SOFT_HLUTNM of \p_1_out__15_i_2\ : label is "soft_lutpair252";
  attribute SOFT_HLUTNM of \p_1_out__15_i_20\ : label is "soft_lutpair243";
  attribute SOFT_HLUTNM of \p_1_out__15_i_21\ : label is "soft_lutpair242";
  attribute SOFT_HLUTNM of \p_1_out__15_i_22\ : label is "soft_lutpair242";
  attribute SOFT_HLUTNM of \p_1_out__15_i_23\ : label is "soft_lutpair241";
  attribute SOFT_HLUTNM of \p_1_out__15_i_24\ : label is "soft_lutpair241";
  attribute SOFT_HLUTNM of \p_1_out__15_i_25\ : label is "soft_lutpair240";
  attribute SOFT_HLUTNM of \p_1_out__15_i_26\ : label is "soft_lutpair240";
  attribute SOFT_HLUTNM of \p_1_out__15_i_27\ : label is "soft_lutpair239";
  attribute SOFT_HLUTNM of \p_1_out__15_i_28\ : label is "soft_lutpair239";
  attribute SOFT_HLUTNM of \p_1_out__15_i_3\ : label is "soft_lutpair251";
  attribute SOFT_HLUTNM of \p_1_out__15_i_4\ : label is "soft_lutpair251";
  attribute SOFT_HLUTNM of \p_1_out__15_i_5\ : label is "soft_lutpair250";
  attribute SOFT_HLUTNM of \p_1_out__15_i_6\ : label is "soft_lutpair250";
  attribute SOFT_HLUTNM of \p_1_out__15_i_7\ : label is "soft_lutpair249";
  attribute SOFT_HLUTNM of \p_1_out__15_i_8\ : label is "soft_lutpair249";
  attribute SOFT_HLUTNM of \p_1_out__15_i_9\ : label is "soft_lutpair248";
  attribute KEEP_HIERARCHY of \p_1_out__16\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__16\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__16_i_10\ : label is "soft_lutpair261";
  attribute SOFT_HLUTNM of \p_1_out__16_i_11\ : label is "soft_lutpair261";
  attribute SOFT_HLUTNM of \p_1_out__16_i_12\ : label is "soft_lutpair260";
  attribute SOFT_HLUTNM of \p_1_out__16_i_13\ : label is "soft_lutpair260";
  attribute SOFT_HLUTNM of \p_1_out__16_i_14\ : label is "soft_lutpair259";
  attribute SOFT_HLUTNM of \p_1_out__16_i_15\ : label is "soft_lutpair259";
  attribute SOFT_HLUTNM of \p_1_out__16_i_16\ : label is "soft_lutpair258";
  attribute SOFT_HLUTNM of \p_1_out__16_i_17\ : label is "soft_lutpair258";
  attribute SOFT_HLUTNM of \p_1_out__16_i_18\ : label is "soft_lutpair257";
  attribute SOFT_HLUTNM of \p_1_out__16_i_19\ : label is "soft_lutpair257";
  attribute SOFT_HLUTNM of \p_1_out__16_i_2\ : label is "soft_lutpair265";
  attribute SOFT_HLUTNM of \p_1_out__16_i_20\ : label is "soft_lutpair256";
  attribute SOFT_HLUTNM of \p_1_out__16_i_21\ : label is "soft_lutpair256";
  attribute SOFT_HLUTNM of \p_1_out__16_i_22\ : label is "soft_lutpair255";
  attribute SOFT_HLUTNM of \p_1_out__16_i_23\ : label is "soft_lutpair255";
  attribute SOFT_HLUTNM of \p_1_out__16_i_24\ : label is "soft_lutpair254";
  attribute SOFT_HLUTNM of \p_1_out__16_i_25\ : label is "soft_lutpair254";
  attribute SOFT_HLUTNM of \p_1_out__16_i_26\ : label is "soft_lutpair253";
  attribute SOFT_HLUTNM of \p_1_out__16_i_27\ : label is "soft_lutpair253";
  attribute SOFT_HLUTNM of \p_1_out__16_i_28\ : label is "soft_lutpair252";
  attribute SOFT_HLUTNM of \p_1_out__16_i_3\ : label is "soft_lutpair265";
  attribute SOFT_HLUTNM of \p_1_out__16_i_4\ : label is "soft_lutpair264";
  attribute SOFT_HLUTNM of \p_1_out__16_i_5\ : label is "soft_lutpair264";
  attribute SOFT_HLUTNM of \p_1_out__16_i_6\ : label is "soft_lutpair263";
  attribute SOFT_HLUTNM of \p_1_out__16_i_7\ : label is "soft_lutpair263";
  attribute SOFT_HLUTNM of \p_1_out__16_i_8\ : label is "soft_lutpair262";
  attribute SOFT_HLUTNM of \p_1_out__16_i_9\ : label is "soft_lutpair262";
  attribute KEEP_HIERARCHY of \p_1_out__17\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__17\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__17_i_10\ : label is "soft_lutpair275";
  attribute SOFT_HLUTNM of \p_1_out__17_i_11\ : label is "soft_lutpair274";
  attribute SOFT_HLUTNM of \p_1_out__17_i_12\ : label is "soft_lutpair274";
  attribute SOFT_HLUTNM of \p_1_out__17_i_13\ : label is "soft_lutpair273";
  attribute SOFT_HLUTNM of \p_1_out__17_i_14\ : label is "soft_lutpair273";
  attribute SOFT_HLUTNM of \p_1_out__17_i_15\ : label is "soft_lutpair272";
  attribute SOFT_HLUTNM of \p_1_out__17_i_16\ : label is "soft_lutpair272";
  attribute SOFT_HLUTNM of \p_1_out__17_i_17\ : label is "soft_lutpair271";
  attribute SOFT_HLUTNM of \p_1_out__17_i_18\ : label is "soft_lutpair271";
  attribute SOFT_HLUTNM of \p_1_out__17_i_19\ : label is "soft_lutpair270";
  attribute SOFT_HLUTNM of \p_1_out__17_i_2\ : label is "soft_lutpair279";
  attribute SOFT_HLUTNM of \p_1_out__17_i_20\ : label is "soft_lutpair270";
  attribute SOFT_HLUTNM of \p_1_out__17_i_21\ : label is "soft_lutpair269";
  attribute SOFT_HLUTNM of \p_1_out__17_i_22\ : label is "soft_lutpair269";
  attribute SOFT_HLUTNM of \p_1_out__17_i_23\ : label is "soft_lutpair268";
  attribute SOFT_HLUTNM of \p_1_out__17_i_24\ : label is "soft_lutpair268";
  attribute SOFT_HLUTNM of \p_1_out__17_i_25\ : label is "soft_lutpair267";
  attribute SOFT_HLUTNM of \p_1_out__17_i_26\ : label is "soft_lutpair267";
  attribute SOFT_HLUTNM of \p_1_out__17_i_27\ : label is "soft_lutpair266";
  attribute SOFT_HLUTNM of \p_1_out__17_i_28\ : label is "soft_lutpair266";
  attribute SOFT_HLUTNM of \p_1_out__17_i_3\ : label is "soft_lutpair278";
  attribute SOFT_HLUTNM of \p_1_out__17_i_4\ : label is "soft_lutpair278";
  attribute SOFT_HLUTNM of \p_1_out__17_i_5\ : label is "soft_lutpair277";
  attribute SOFT_HLUTNM of \p_1_out__17_i_6\ : label is "soft_lutpair277";
  attribute SOFT_HLUTNM of \p_1_out__17_i_7\ : label is "soft_lutpair276";
  attribute SOFT_HLUTNM of \p_1_out__17_i_8\ : label is "soft_lutpair276";
  attribute SOFT_HLUTNM of \p_1_out__17_i_9\ : label is "soft_lutpair275";
  attribute KEEP_HIERARCHY of \p_1_out__18\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__18\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__18_i_10\ : label is "soft_lutpair288";
  attribute SOFT_HLUTNM of \p_1_out__18_i_11\ : label is "soft_lutpair288";
  attribute SOFT_HLUTNM of \p_1_out__18_i_12\ : label is "soft_lutpair287";
  attribute SOFT_HLUTNM of \p_1_out__18_i_13\ : label is "soft_lutpair287";
  attribute SOFT_HLUTNM of \p_1_out__18_i_14\ : label is "soft_lutpair286";
  attribute SOFT_HLUTNM of \p_1_out__18_i_15\ : label is "soft_lutpair286";
  attribute SOFT_HLUTNM of \p_1_out__18_i_16\ : label is "soft_lutpair285";
  attribute SOFT_HLUTNM of \p_1_out__18_i_17\ : label is "soft_lutpair285";
  attribute SOFT_HLUTNM of \p_1_out__18_i_18\ : label is "soft_lutpair284";
  attribute SOFT_HLUTNM of \p_1_out__18_i_19\ : label is "soft_lutpair284";
  attribute SOFT_HLUTNM of \p_1_out__18_i_2\ : label is "soft_lutpair292";
  attribute SOFT_HLUTNM of \p_1_out__18_i_20\ : label is "soft_lutpair283";
  attribute SOFT_HLUTNM of \p_1_out__18_i_21\ : label is "soft_lutpair283";
  attribute SOFT_HLUTNM of \p_1_out__18_i_22\ : label is "soft_lutpair282";
  attribute SOFT_HLUTNM of \p_1_out__18_i_23\ : label is "soft_lutpair282";
  attribute SOFT_HLUTNM of \p_1_out__18_i_24\ : label is "soft_lutpair281";
  attribute SOFT_HLUTNM of \p_1_out__18_i_25\ : label is "soft_lutpair281";
  attribute SOFT_HLUTNM of \p_1_out__18_i_26\ : label is "soft_lutpair280";
  attribute SOFT_HLUTNM of \p_1_out__18_i_27\ : label is "soft_lutpair280";
  attribute SOFT_HLUTNM of \p_1_out__18_i_28\ : label is "soft_lutpair279";
  attribute SOFT_HLUTNM of \p_1_out__18_i_3\ : label is "soft_lutpair292";
  attribute SOFT_HLUTNM of \p_1_out__18_i_4\ : label is "soft_lutpair291";
  attribute SOFT_HLUTNM of \p_1_out__18_i_5\ : label is "soft_lutpair291";
  attribute SOFT_HLUTNM of \p_1_out__18_i_6\ : label is "soft_lutpair290";
  attribute SOFT_HLUTNM of \p_1_out__18_i_7\ : label is "soft_lutpair290";
  attribute SOFT_HLUTNM of \p_1_out__18_i_8\ : label is "soft_lutpair289";
  attribute SOFT_HLUTNM of \p_1_out__18_i_9\ : label is "soft_lutpair289";
  attribute KEEP_HIERARCHY of \p_1_out__19\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__19\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__19_i_10\ : label is "soft_lutpair302";
  attribute SOFT_HLUTNM of \p_1_out__19_i_11\ : label is "soft_lutpair301";
  attribute SOFT_HLUTNM of \p_1_out__19_i_12\ : label is "soft_lutpair301";
  attribute SOFT_HLUTNM of \p_1_out__19_i_13\ : label is "soft_lutpair300";
  attribute SOFT_HLUTNM of \p_1_out__19_i_14\ : label is "soft_lutpair300";
  attribute SOFT_HLUTNM of \p_1_out__19_i_15\ : label is "soft_lutpair299";
  attribute SOFT_HLUTNM of \p_1_out__19_i_16\ : label is "soft_lutpair299";
  attribute SOFT_HLUTNM of \p_1_out__19_i_17\ : label is "soft_lutpair298";
  attribute SOFT_HLUTNM of \p_1_out__19_i_18\ : label is "soft_lutpair298";
  attribute SOFT_HLUTNM of \p_1_out__19_i_19\ : label is "soft_lutpair297";
  attribute SOFT_HLUTNM of \p_1_out__19_i_2\ : label is "soft_lutpair306";
  attribute SOFT_HLUTNM of \p_1_out__19_i_20\ : label is "soft_lutpair297";
  attribute SOFT_HLUTNM of \p_1_out__19_i_21\ : label is "soft_lutpair296";
  attribute SOFT_HLUTNM of \p_1_out__19_i_22\ : label is "soft_lutpair296";
  attribute SOFT_HLUTNM of \p_1_out__19_i_23\ : label is "soft_lutpair295";
  attribute SOFT_HLUTNM of \p_1_out__19_i_24\ : label is "soft_lutpair295";
  attribute SOFT_HLUTNM of \p_1_out__19_i_25\ : label is "soft_lutpair294";
  attribute SOFT_HLUTNM of \p_1_out__19_i_26\ : label is "soft_lutpair294";
  attribute SOFT_HLUTNM of \p_1_out__19_i_27\ : label is "soft_lutpair293";
  attribute SOFT_HLUTNM of \p_1_out__19_i_28\ : label is "soft_lutpair293";
  attribute SOFT_HLUTNM of \p_1_out__19_i_3\ : label is "soft_lutpair305";
  attribute SOFT_HLUTNM of \p_1_out__19_i_4\ : label is "soft_lutpair305";
  attribute SOFT_HLUTNM of \p_1_out__19_i_5\ : label is "soft_lutpair304";
  attribute SOFT_HLUTNM of \p_1_out__19_i_6\ : label is "soft_lutpair304";
  attribute SOFT_HLUTNM of \p_1_out__19_i_7\ : label is "soft_lutpair303";
  attribute SOFT_HLUTNM of \p_1_out__19_i_8\ : label is "soft_lutpair303";
  attribute SOFT_HLUTNM of \p_1_out__19_i_9\ : label is "soft_lutpair302";
  attribute SOFT_HLUTNM of \p_1_out__1_i_10\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \p_1_out__1_i_11\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \p_1_out__1_i_12\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \p_1_out__1_i_13\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \p_1_out__1_i_14\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \p_1_out__1_i_15\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \p_1_out__1_i_16\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \p_1_out__1_i_17\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \p_1_out__1_i_18\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \p_1_out__1_i_19\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \p_1_out__1_i_2\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \p_1_out__1_i_20\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \p_1_out__1_i_21\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \p_1_out__1_i_22\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \p_1_out__1_i_23\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \p_1_out__1_i_24\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \p_1_out__1_i_25\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \p_1_out__1_i_26\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \p_1_out__1_i_27\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \p_1_out__1_i_28\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \p_1_out__1_i_3\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \p_1_out__1_i_4\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \p_1_out__1_i_5\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \p_1_out__1_i_6\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \p_1_out__1_i_7\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \p_1_out__1_i_8\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \p_1_out__1_i_9\ : label is "soft_lutpair59";
  attribute KEEP_HIERARCHY of \p_1_out__2\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__2\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute KEEP_HIERARCHY of \p_1_out__20\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__20\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__20_i_10\ : label is "soft_lutpair315";
  attribute SOFT_HLUTNM of \p_1_out__20_i_11\ : label is "soft_lutpair315";
  attribute SOFT_HLUTNM of \p_1_out__20_i_12\ : label is "soft_lutpair314";
  attribute SOFT_HLUTNM of \p_1_out__20_i_13\ : label is "soft_lutpair314";
  attribute SOFT_HLUTNM of \p_1_out__20_i_14\ : label is "soft_lutpair313";
  attribute SOFT_HLUTNM of \p_1_out__20_i_15\ : label is "soft_lutpair313";
  attribute SOFT_HLUTNM of \p_1_out__20_i_16\ : label is "soft_lutpair312";
  attribute SOFT_HLUTNM of \p_1_out__20_i_17\ : label is "soft_lutpair312";
  attribute SOFT_HLUTNM of \p_1_out__20_i_18\ : label is "soft_lutpair311";
  attribute SOFT_HLUTNM of \p_1_out__20_i_19\ : label is "soft_lutpair311";
  attribute SOFT_HLUTNM of \p_1_out__20_i_2\ : label is "soft_lutpair319";
  attribute SOFT_HLUTNM of \p_1_out__20_i_20\ : label is "soft_lutpair310";
  attribute SOFT_HLUTNM of \p_1_out__20_i_21\ : label is "soft_lutpair310";
  attribute SOFT_HLUTNM of \p_1_out__20_i_22\ : label is "soft_lutpair309";
  attribute SOFT_HLUTNM of \p_1_out__20_i_23\ : label is "soft_lutpair309";
  attribute SOFT_HLUTNM of \p_1_out__20_i_24\ : label is "soft_lutpair308";
  attribute SOFT_HLUTNM of \p_1_out__20_i_25\ : label is "soft_lutpair308";
  attribute SOFT_HLUTNM of \p_1_out__20_i_26\ : label is "soft_lutpair307";
  attribute SOFT_HLUTNM of \p_1_out__20_i_27\ : label is "soft_lutpair307";
  attribute SOFT_HLUTNM of \p_1_out__20_i_28\ : label is "soft_lutpair306";
  attribute SOFT_HLUTNM of \p_1_out__20_i_3\ : label is "soft_lutpair319";
  attribute SOFT_HLUTNM of \p_1_out__20_i_4\ : label is "soft_lutpair318";
  attribute SOFT_HLUTNM of \p_1_out__20_i_5\ : label is "soft_lutpair318";
  attribute SOFT_HLUTNM of \p_1_out__20_i_6\ : label is "soft_lutpair317";
  attribute SOFT_HLUTNM of \p_1_out__20_i_7\ : label is "soft_lutpair317";
  attribute SOFT_HLUTNM of \p_1_out__20_i_8\ : label is "soft_lutpair316";
  attribute SOFT_HLUTNM of \p_1_out__20_i_9\ : label is "soft_lutpair316";
  attribute KEEP_HIERARCHY of \p_1_out__21\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__21\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__21_i_10\ : label is "soft_lutpair329";
  attribute SOFT_HLUTNM of \p_1_out__21_i_11\ : label is "soft_lutpair328";
  attribute SOFT_HLUTNM of \p_1_out__21_i_12\ : label is "soft_lutpair328";
  attribute SOFT_HLUTNM of \p_1_out__21_i_13\ : label is "soft_lutpair327";
  attribute SOFT_HLUTNM of \p_1_out__21_i_14\ : label is "soft_lutpair327";
  attribute SOFT_HLUTNM of \p_1_out__21_i_15\ : label is "soft_lutpair326";
  attribute SOFT_HLUTNM of \p_1_out__21_i_16\ : label is "soft_lutpair326";
  attribute SOFT_HLUTNM of \p_1_out__21_i_17\ : label is "soft_lutpair325";
  attribute SOFT_HLUTNM of \p_1_out__21_i_18\ : label is "soft_lutpair325";
  attribute SOFT_HLUTNM of \p_1_out__21_i_19\ : label is "soft_lutpair324";
  attribute SOFT_HLUTNM of \p_1_out__21_i_2\ : label is "soft_lutpair333";
  attribute SOFT_HLUTNM of \p_1_out__21_i_20\ : label is "soft_lutpair324";
  attribute SOFT_HLUTNM of \p_1_out__21_i_21\ : label is "soft_lutpair323";
  attribute SOFT_HLUTNM of \p_1_out__21_i_22\ : label is "soft_lutpair323";
  attribute SOFT_HLUTNM of \p_1_out__21_i_23\ : label is "soft_lutpair322";
  attribute SOFT_HLUTNM of \p_1_out__21_i_24\ : label is "soft_lutpair322";
  attribute SOFT_HLUTNM of \p_1_out__21_i_25\ : label is "soft_lutpair321";
  attribute SOFT_HLUTNM of \p_1_out__21_i_26\ : label is "soft_lutpair321";
  attribute SOFT_HLUTNM of \p_1_out__21_i_27\ : label is "soft_lutpair320";
  attribute SOFT_HLUTNM of \p_1_out__21_i_28\ : label is "soft_lutpair320";
  attribute SOFT_HLUTNM of \p_1_out__21_i_3\ : label is "soft_lutpair332";
  attribute SOFT_HLUTNM of \p_1_out__21_i_4\ : label is "soft_lutpair332";
  attribute SOFT_HLUTNM of \p_1_out__21_i_5\ : label is "soft_lutpair331";
  attribute SOFT_HLUTNM of \p_1_out__21_i_6\ : label is "soft_lutpair331";
  attribute SOFT_HLUTNM of \p_1_out__21_i_7\ : label is "soft_lutpair330";
  attribute SOFT_HLUTNM of \p_1_out__21_i_8\ : label is "soft_lutpair330";
  attribute SOFT_HLUTNM of \p_1_out__21_i_9\ : label is "soft_lutpair329";
  attribute KEEP_HIERARCHY of \p_1_out__22\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__22\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__22_i_10\ : label is "soft_lutpair342";
  attribute SOFT_HLUTNM of \p_1_out__22_i_11\ : label is "soft_lutpair342";
  attribute SOFT_HLUTNM of \p_1_out__22_i_12\ : label is "soft_lutpair341";
  attribute SOFT_HLUTNM of \p_1_out__22_i_13\ : label is "soft_lutpair341";
  attribute SOFT_HLUTNM of \p_1_out__22_i_14\ : label is "soft_lutpair340";
  attribute SOFT_HLUTNM of \p_1_out__22_i_15\ : label is "soft_lutpair340";
  attribute SOFT_HLUTNM of \p_1_out__22_i_16\ : label is "soft_lutpair339";
  attribute SOFT_HLUTNM of \p_1_out__22_i_17\ : label is "soft_lutpair339";
  attribute SOFT_HLUTNM of \p_1_out__22_i_18\ : label is "soft_lutpair338";
  attribute SOFT_HLUTNM of \p_1_out__22_i_19\ : label is "soft_lutpair338";
  attribute SOFT_HLUTNM of \p_1_out__22_i_2\ : label is "soft_lutpair346";
  attribute SOFT_HLUTNM of \p_1_out__22_i_20\ : label is "soft_lutpair337";
  attribute SOFT_HLUTNM of \p_1_out__22_i_21\ : label is "soft_lutpair337";
  attribute SOFT_HLUTNM of \p_1_out__22_i_22\ : label is "soft_lutpair336";
  attribute SOFT_HLUTNM of \p_1_out__22_i_23\ : label is "soft_lutpair336";
  attribute SOFT_HLUTNM of \p_1_out__22_i_24\ : label is "soft_lutpair335";
  attribute SOFT_HLUTNM of \p_1_out__22_i_25\ : label is "soft_lutpair335";
  attribute SOFT_HLUTNM of \p_1_out__22_i_26\ : label is "soft_lutpair334";
  attribute SOFT_HLUTNM of \p_1_out__22_i_27\ : label is "soft_lutpair334";
  attribute SOFT_HLUTNM of \p_1_out__22_i_28\ : label is "soft_lutpair333";
  attribute SOFT_HLUTNM of \p_1_out__22_i_3\ : label is "soft_lutpair346";
  attribute SOFT_HLUTNM of \p_1_out__22_i_4\ : label is "soft_lutpair345";
  attribute SOFT_HLUTNM of \p_1_out__22_i_5\ : label is "soft_lutpair345";
  attribute SOFT_HLUTNM of \p_1_out__22_i_6\ : label is "soft_lutpair344";
  attribute SOFT_HLUTNM of \p_1_out__22_i_7\ : label is "soft_lutpair344";
  attribute SOFT_HLUTNM of \p_1_out__22_i_8\ : label is "soft_lutpair343";
  attribute SOFT_HLUTNM of \p_1_out__22_i_9\ : label is "soft_lutpair343";
  attribute KEEP_HIERARCHY of \p_1_out__23\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__23\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__23_i_10\ : label is "soft_lutpair356";
  attribute SOFT_HLUTNM of \p_1_out__23_i_11\ : label is "soft_lutpair355";
  attribute SOFT_HLUTNM of \p_1_out__23_i_12\ : label is "soft_lutpair355";
  attribute SOFT_HLUTNM of \p_1_out__23_i_13\ : label is "soft_lutpair354";
  attribute SOFT_HLUTNM of \p_1_out__23_i_14\ : label is "soft_lutpair354";
  attribute SOFT_HLUTNM of \p_1_out__23_i_15\ : label is "soft_lutpair353";
  attribute SOFT_HLUTNM of \p_1_out__23_i_16\ : label is "soft_lutpair353";
  attribute SOFT_HLUTNM of \p_1_out__23_i_17\ : label is "soft_lutpair352";
  attribute SOFT_HLUTNM of \p_1_out__23_i_18\ : label is "soft_lutpair352";
  attribute SOFT_HLUTNM of \p_1_out__23_i_19\ : label is "soft_lutpair351";
  attribute SOFT_HLUTNM of \p_1_out__23_i_2\ : label is "soft_lutpair360";
  attribute SOFT_HLUTNM of \p_1_out__23_i_20\ : label is "soft_lutpair351";
  attribute SOFT_HLUTNM of \p_1_out__23_i_21\ : label is "soft_lutpair350";
  attribute SOFT_HLUTNM of \p_1_out__23_i_22\ : label is "soft_lutpair350";
  attribute SOFT_HLUTNM of \p_1_out__23_i_23\ : label is "soft_lutpair349";
  attribute SOFT_HLUTNM of \p_1_out__23_i_24\ : label is "soft_lutpair349";
  attribute SOFT_HLUTNM of \p_1_out__23_i_25\ : label is "soft_lutpair348";
  attribute SOFT_HLUTNM of \p_1_out__23_i_26\ : label is "soft_lutpair348";
  attribute SOFT_HLUTNM of \p_1_out__23_i_27\ : label is "soft_lutpair347";
  attribute SOFT_HLUTNM of \p_1_out__23_i_28\ : label is "soft_lutpair347";
  attribute SOFT_HLUTNM of \p_1_out__23_i_3\ : label is "soft_lutpair359";
  attribute SOFT_HLUTNM of \p_1_out__23_i_4\ : label is "soft_lutpair359";
  attribute SOFT_HLUTNM of \p_1_out__23_i_5\ : label is "soft_lutpair358";
  attribute SOFT_HLUTNM of \p_1_out__23_i_6\ : label is "soft_lutpair358";
  attribute SOFT_HLUTNM of \p_1_out__23_i_7\ : label is "soft_lutpair357";
  attribute SOFT_HLUTNM of \p_1_out__23_i_8\ : label is "soft_lutpair357";
  attribute SOFT_HLUTNM of \p_1_out__23_i_9\ : label is "soft_lutpair356";
  attribute KEEP_HIERARCHY of \p_1_out__24\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__24\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__24_i_10\ : label is "soft_lutpair369";
  attribute SOFT_HLUTNM of \p_1_out__24_i_11\ : label is "soft_lutpair369";
  attribute SOFT_HLUTNM of \p_1_out__24_i_12\ : label is "soft_lutpair368";
  attribute SOFT_HLUTNM of \p_1_out__24_i_13\ : label is "soft_lutpair368";
  attribute SOFT_HLUTNM of \p_1_out__24_i_14\ : label is "soft_lutpair367";
  attribute SOFT_HLUTNM of \p_1_out__24_i_15\ : label is "soft_lutpair367";
  attribute SOFT_HLUTNM of \p_1_out__24_i_16\ : label is "soft_lutpair366";
  attribute SOFT_HLUTNM of \p_1_out__24_i_17\ : label is "soft_lutpair366";
  attribute SOFT_HLUTNM of \p_1_out__24_i_18\ : label is "soft_lutpair365";
  attribute SOFT_HLUTNM of \p_1_out__24_i_19\ : label is "soft_lutpair365";
  attribute SOFT_HLUTNM of \p_1_out__24_i_2\ : label is "soft_lutpair373";
  attribute SOFT_HLUTNM of \p_1_out__24_i_20\ : label is "soft_lutpair364";
  attribute SOFT_HLUTNM of \p_1_out__24_i_21\ : label is "soft_lutpair364";
  attribute SOFT_HLUTNM of \p_1_out__24_i_22\ : label is "soft_lutpair363";
  attribute SOFT_HLUTNM of \p_1_out__24_i_23\ : label is "soft_lutpair363";
  attribute SOFT_HLUTNM of \p_1_out__24_i_24\ : label is "soft_lutpair362";
  attribute SOFT_HLUTNM of \p_1_out__24_i_25\ : label is "soft_lutpair362";
  attribute SOFT_HLUTNM of \p_1_out__24_i_26\ : label is "soft_lutpair361";
  attribute SOFT_HLUTNM of \p_1_out__24_i_27\ : label is "soft_lutpair361";
  attribute SOFT_HLUTNM of \p_1_out__24_i_28\ : label is "soft_lutpair360";
  attribute SOFT_HLUTNM of \p_1_out__24_i_3\ : label is "soft_lutpair373";
  attribute SOFT_HLUTNM of \p_1_out__24_i_4\ : label is "soft_lutpair372";
  attribute SOFT_HLUTNM of \p_1_out__24_i_5\ : label is "soft_lutpair372";
  attribute SOFT_HLUTNM of \p_1_out__24_i_6\ : label is "soft_lutpair371";
  attribute SOFT_HLUTNM of \p_1_out__24_i_7\ : label is "soft_lutpair371";
  attribute SOFT_HLUTNM of \p_1_out__24_i_8\ : label is "soft_lutpair370";
  attribute SOFT_HLUTNM of \p_1_out__24_i_9\ : label is "soft_lutpair370";
  attribute KEEP_HIERARCHY of \p_1_out__25\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__25\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__25_i_10\ : label is "soft_lutpair383";
  attribute SOFT_HLUTNM of \p_1_out__25_i_11\ : label is "soft_lutpair382";
  attribute SOFT_HLUTNM of \p_1_out__25_i_12\ : label is "soft_lutpair382";
  attribute SOFT_HLUTNM of \p_1_out__25_i_13\ : label is "soft_lutpair381";
  attribute SOFT_HLUTNM of \p_1_out__25_i_14\ : label is "soft_lutpair381";
  attribute SOFT_HLUTNM of \p_1_out__25_i_15\ : label is "soft_lutpair380";
  attribute SOFT_HLUTNM of \p_1_out__25_i_16\ : label is "soft_lutpair380";
  attribute SOFT_HLUTNM of \p_1_out__25_i_17\ : label is "soft_lutpair379";
  attribute SOFT_HLUTNM of \p_1_out__25_i_18\ : label is "soft_lutpair379";
  attribute SOFT_HLUTNM of \p_1_out__25_i_19\ : label is "soft_lutpair378";
  attribute SOFT_HLUTNM of \p_1_out__25_i_2\ : label is "soft_lutpair387";
  attribute SOFT_HLUTNM of \p_1_out__25_i_20\ : label is "soft_lutpair378";
  attribute SOFT_HLUTNM of \p_1_out__25_i_21\ : label is "soft_lutpair377";
  attribute SOFT_HLUTNM of \p_1_out__25_i_22\ : label is "soft_lutpair377";
  attribute SOFT_HLUTNM of \p_1_out__25_i_23\ : label is "soft_lutpair376";
  attribute SOFT_HLUTNM of \p_1_out__25_i_24\ : label is "soft_lutpair376";
  attribute SOFT_HLUTNM of \p_1_out__25_i_25\ : label is "soft_lutpair375";
  attribute SOFT_HLUTNM of \p_1_out__25_i_26\ : label is "soft_lutpair375";
  attribute SOFT_HLUTNM of \p_1_out__25_i_27\ : label is "soft_lutpair374";
  attribute SOFT_HLUTNM of \p_1_out__25_i_28\ : label is "soft_lutpair374";
  attribute SOFT_HLUTNM of \p_1_out__25_i_3\ : label is "soft_lutpair386";
  attribute SOFT_HLUTNM of \p_1_out__25_i_4\ : label is "soft_lutpair386";
  attribute SOFT_HLUTNM of \p_1_out__25_i_5\ : label is "soft_lutpair385";
  attribute SOFT_HLUTNM of \p_1_out__25_i_6\ : label is "soft_lutpair385";
  attribute SOFT_HLUTNM of \p_1_out__25_i_7\ : label is "soft_lutpair384";
  attribute SOFT_HLUTNM of \p_1_out__25_i_8\ : label is "soft_lutpair384";
  attribute SOFT_HLUTNM of \p_1_out__25_i_9\ : label is "soft_lutpair383";
  attribute KEEP_HIERARCHY of \p_1_out__26\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__26\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__26_i_10\ : label is "soft_lutpair396";
  attribute SOFT_HLUTNM of \p_1_out__26_i_11\ : label is "soft_lutpair396";
  attribute SOFT_HLUTNM of \p_1_out__26_i_12\ : label is "soft_lutpair395";
  attribute SOFT_HLUTNM of \p_1_out__26_i_13\ : label is "soft_lutpair395";
  attribute SOFT_HLUTNM of \p_1_out__26_i_14\ : label is "soft_lutpair394";
  attribute SOFT_HLUTNM of \p_1_out__26_i_15\ : label is "soft_lutpair394";
  attribute SOFT_HLUTNM of \p_1_out__26_i_16\ : label is "soft_lutpair393";
  attribute SOFT_HLUTNM of \p_1_out__26_i_17\ : label is "soft_lutpair393";
  attribute SOFT_HLUTNM of \p_1_out__26_i_18\ : label is "soft_lutpair392";
  attribute SOFT_HLUTNM of \p_1_out__26_i_19\ : label is "soft_lutpair392";
  attribute SOFT_HLUTNM of \p_1_out__26_i_2\ : label is "soft_lutpair400";
  attribute SOFT_HLUTNM of \p_1_out__26_i_20\ : label is "soft_lutpair391";
  attribute SOFT_HLUTNM of \p_1_out__26_i_21\ : label is "soft_lutpair391";
  attribute SOFT_HLUTNM of \p_1_out__26_i_22\ : label is "soft_lutpair390";
  attribute SOFT_HLUTNM of \p_1_out__26_i_23\ : label is "soft_lutpair390";
  attribute SOFT_HLUTNM of \p_1_out__26_i_24\ : label is "soft_lutpair389";
  attribute SOFT_HLUTNM of \p_1_out__26_i_25\ : label is "soft_lutpair389";
  attribute SOFT_HLUTNM of \p_1_out__26_i_26\ : label is "soft_lutpair388";
  attribute SOFT_HLUTNM of \p_1_out__26_i_27\ : label is "soft_lutpair388";
  attribute SOFT_HLUTNM of \p_1_out__26_i_28\ : label is "soft_lutpair387";
  attribute SOFT_HLUTNM of \p_1_out__26_i_3\ : label is "soft_lutpair400";
  attribute SOFT_HLUTNM of \p_1_out__26_i_4\ : label is "soft_lutpair399";
  attribute SOFT_HLUTNM of \p_1_out__26_i_5\ : label is "soft_lutpair399";
  attribute SOFT_HLUTNM of \p_1_out__26_i_6\ : label is "soft_lutpair398";
  attribute SOFT_HLUTNM of \p_1_out__26_i_7\ : label is "soft_lutpair398";
  attribute SOFT_HLUTNM of \p_1_out__26_i_8\ : label is "soft_lutpair397";
  attribute SOFT_HLUTNM of \p_1_out__26_i_9\ : label is "soft_lutpair397";
  attribute KEEP_HIERARCHY of \p_1_out__27\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__27\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__27_i_10\ : label is "soft_lutpair410";
  attribute SOFT_HLUTNM of \p_1_out__27_i_11\ : label is "soft_lutpair409";
  attribute SOFT_HLUTNM of \p_1_out__27_i_12\ : label is "soft_lutpair409";
  attribute SOFT_HLUTNM of \p_1_out__27_i_13\ : label is "soft_lutpair408";
  attribute SOFT_HLUTNM of \p_1_out__27_i_14\ : label is "soft_lutpair408";
  attribute SOFT_HLUTNM of \p_1_out__27_i_15\ : label is "soft_lutpair407";
  attribute SOFT_HLUTNM of \p_1_out__27_i_16\ : label is "soft_lutpair407";
  attribute SOFT_HLUTNM of \p_1_out__27_i_17\ : label is "soft_lutpair406";
  attribute SOFT_HLUTNM of \p_1_out__27_i_18\ : label is "soft_lutpair406";
  attribute SOFT_HLUTNM of \p_1_out__27_i_19\ : label is "soft_lutpair405";
  attribute SOFT_HLUTNM of \p_1_out__27_i_2\ : label is "soft_lutpair414";
  attribute SOFT_HLUTNM of \p_1_out__27_i_20\ : label is "soft_lutpair405";
  attribute SOFT_HLUTNM of \p_1_out__27_i_21\ : label is "soft_lutpair404";
  attribute SOFT_HLUTNM of \p_1_out__27_i_22\ : label is "soft_lutpair404";
  attribute SOFT_HLUTNM of \p_1_out__27_i_23\ : label is "soft_lutpair403";
  attribute SOFT_HLUTNM of \p_1_out__27_i_24\ : label is "soft_lutpair403";
  attribute SOFT_HLUTNM of \p_1_out__27_i_25\ : label is "soft_lutpair402";
  attribute SOFT_HLUTNM of \p_1_out__27_i_26\ : label is "soft_lutpair402";
  attribute SOFT_HLUTNM of \p_1_out__27_i_27\ : label is "soft_lutpair401";
  attribute SOFT_HLUTNM of \p_1_out__27_i_28\ : label is "soft_lutpair401";
  attribute SOFT_HLUTNM of \p_1_out__27_i_3\ : label is "soft_lutpair413";
  attribute SOFT_HLUTNM of \p_1_out__27_i_4\ : label is "soft_lutpair413";
  attribute SOFT_HLUTNM of \p_1_out__27_i_5\ : label is "soft_lutpair412";
  attribute SOFT_HLUTNM of \p_1_out__27_i_6\ : label is "soft_lutpair412";
  attribute SOFT_HLUTNM of \p_1_out__27_i_7\ : label is "soft_lutpair411";
  attribute SOFT_HLUTNM of \p_1_out__27_i_8\ : label is "soft_lutpair411";
  attribute SOFT_HLUTNM of \p_1_out__27_i_9\ : label is "soft_lutpair410";
  attribute KEEP_HIERARCHY of \p_1_out__28\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__28\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__28_i_10\ : label is "soft_lutpair423";
  attribute SOFT_HLUTNM of \p_1_out__28_i_11\ : label is "soft_lutpair423";
  attribute SOFT_HLUTNM of \p_1_out__28_i_12\ : label is "soft_lutpair422";
  attribute SOFT_HLUTNM of \p_1_out__28_i_13\ : label is "soft_lutpair422";
  attribute SOFT_HLUTNM of \p_1_out__28_i_14\ : label is "soft_lutpair421";
  attribute SOFT_HLUTNM of \p_1_out__28_i_15\ : label is "soft_lutpair421";
  attribute SOFT_HLUTNM of \p_1_out__28_i_16\ : label is "soft_lutpair420";
  attribute SOFT_HLUTNM of \p_1_out__28_i_17\ : label is "soft_lutpair420";
  attribute SOFT_HLUTNM of \p_1_out__28_i_18\ : label is "soft_lutpair419";
  attribute SOFT_HLUTNM of \p_1_out__28_i_19\ : label is "soft_lutpair419";
  attribute SOFT_HLUTNM of \p_1_out__28_i_2\ : label is "soft_lutpair427";
  attribute SOFT_HLUTNM of \p_1_out__28_i_20\ : label is "soft_lutpair418";
  attribute SOFT_HLUTNM of \p_1_out__28_i_21\ : label is "soft_lutpair418";
  attribute SOFT_HLUTNM of \p_1_out__28_i_22\ : label is "soft_lutpair417";
  attribute SOFT_HLUTNM of \p_1_out__28_i_23\ : label is "soft_lutpair417";
  attribute SOFT_HLUTNM of \p_1_out__28_i_24\ : label is "soft_lutpair416";
  attribute SOFT_HLUTNM of \p_1_out__28_i_25\ : label is "soft_lutpair416";
  attribute SOFT_HLUTNM of \p_1_out__28_i_26\ : label is "soft_lutpair415";
  attribute SOFT_HLUTNM of \p_1_out__28_i_27\ : label is "soft_lutpair415";
  attribute SOFT_HLUTNM of \p_1_out__28_i_28\ : label is "soft_lutpair414";
  attribute SOFT_HLUTNM of \p_1_out__28_i_3\ : label is "soft_lutpair427";
  attribute SOFT_HLUTNM of \p_1_out__28_i_4\ : label is "soft_lutpair426";
  attribute SOFT_HLUTNM of \p_1_out__28_i_5\ : label is "soft_lutpair426";
  attribute SOFT_HLUTNM of \p_1_out__28_i_6\ : label is "soft_lutpair425";
  attribute SOFT_HLUTNM of \p_1_out__28_i_7\ : label is "soft_lutpair425";
  attribute SOFT_HLUTNM of \p_1_out__28_i_8\ : label is "soft_lutpair424";
  attribute SOFT_HLUTNM of \p_1_out__28_i_9\ : label is "soft_lutpair424";
  attribute KEEP_HIERARCHY of \p_1_out__29\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__29\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__29_i_10\ : label is "soft_lutpair437";
  attribute SOFT_HLUTNM of \p_1_out__29_i_11\ : label is "soft_lutpair436";
  attribute SOFT_HLUTNM of \p_1_out__29_i_12\ : label is "soft_lutpair436";
  attribute SOFT_HLUTNM of \p_1_out__29_i_13\ : label is "soft_lutpair435";
  attribute SOFT_HLUTNM of \p_1_out__29_i_14\ : label is "soft_lutpair435";
  attribute SOFT_HLUTNM of \p_1_out__29_i_15\ : label is "soft_lutpair434";
  attribute SOFT_HLUTNM of \p_1_out__29_i_16\ : label is "soft_lutpair434";
  attribute SOFT_HLUTNM of \p_1_out__29_i_17\ : label is "soft_lutpair433";
  attribute SOFT_HLUTNM of \p_1_out__29_i_18\ : label is "soft_lutpair433";
  attribute SOFT_HLUTNM of \p_1_out__29_i_19\ : label is "soft_lutpair432";
  attribute SOFT_HLUTNM of \p_1_out__29_i_2\ : label is "soft_lutpair441";
  attribute SOFT_HLUTNM of \p_1_out__29_i_20\ : label is "soft_lutpair432";
  attribute SOFT_HLUTNM of \p_1_out__29_i_21\ : label is "soft_lutpair431";
  attribute SOFT_HLUTNM of \p_1_out__29_i_22\ : label is "soft_lutpair431";
  attribute SOFT_HLUTNM of \p_1_out__29_i_23\ : label is "soft_lutpair430";
  attribute SOFT_HLUTNM of \p_1_out__29_i_24\ : label is "soft_lutpair430";
  attribute SOFT_HLUTNM of \p_1_out__29_i_25\ : label is "soft_lutpair429";
  attribute SOFT_HLUTNM of \p_1_out__29_i_26\ : label is "soft_lutpair429";
  attribute SOFT_HLUTNM of \p_1_out__29_i_27\ : label is "soft_lutpair428";
  attribute SOFT_HLUTNM of \p_1_out__29_i_28\ : label is "soft_lutpair428";
  attribute SOFT_HLUTNM of \p_1_out__29_i_3\ : label is "soft_lutpair440";
  attribute SOFT_HLUTNM of \p_1_out__29_i_4\ : label is "soft_lutpair440";
  attribute SOFT_HLUTNM of \p_1_out__29_i_5\ : label is "soft_lutpair439";
  attribute SOFT_HLUTNM of \p_1_out__29_i_6\ : label is "soft_lutpair439";
  attribute SOFT_HLUTNM of \p_1_out__29_i_7\ : label is "soft_lutpair438";
  attribute SOFT_HLUTNM of \p_1_out__29_i_8\ : label is "soft_lutpair438";
  attribute SOFT_HLUTNM of \p_1_out__29_i_9\ : label is "soft_lutpair437";
  attribute SOFT_HLUTNM of \p_1_out__2_i_10\ : label is "soft_lutpair72";
  attribute SOFT_HLUTNM of \p_1_out__2_i_11\ : label is "soft_lutpair72";
  attribute SOFT_HLUTNM of \p_1_out__2_i_12\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \p_1_out__2_i_13\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \p_1_out__2_i_14\ : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of \p_1_out__2_i_15\ : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of \p_1_out__2_i_16\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \p_1_out__2_i_17\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \p_1_out__2_i_18\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \p_1_out__2_i_19\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \p_1_out__2_i_2\ : label is "soft_lutpair76";
  attribute SOFT_HLUTNM of \p_1_out__2_i_20\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \p_1_out__2_i_21\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \p_1_out__2_i_22\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \p_1_out__2_i_23\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \p_1_out__2_i_24\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \p_1_out__2_i_25\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \p_1_out__2_i_26\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \p_1_out__2_i_27\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \p_1_out__2_i_28\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \p_1_out__2_i_3\ : label is "soft_lutpair76";
  attribute SOFT_HLUTNM of \p_1_out__2_i_4\ : label is "soft_lutpair75";
  attribute SOFT_HLUTNM of \p_1_out__2_i_5\ : label is "soft_lutpair75";
  attribute SOFT_HLUTNM of \p_1_out__2_i_6\ : label is "soft_lutpair74";
  attribute SOFT_HLUTNM of \p_1_out__2_i_7\ : label is "soft_lutpair74";
  attribute SOFT_HLUTNM of \p_1_out__2_i_8\ : label is "soft_lutpair73";
  attribute SOFT_HLUTNM of \p_1_out__2_i_9\ : label is "soft_lutpair73";
  attribute KEEP_HIERARCHY of \p_1_out__3\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__3\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute KEEP_HIERARCHY of \p_1_out__30\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__30\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__30_i_10\ : label is "soft_lutpair450";
  attribute SOFT_HLUTNM of \p_1_out__30_i_11\ : label is "soft_lutpair450";
  attribute SOFT_HLUTNM of \p_1_out__30_i_12\ : label is "soft_lutpair449";
  attribute SOFT_HLUTNM of \p_1_out__30_i_13\ : label is "soft_lutpair449";
  attribute SOFT_HLUTNM of \p_1_out__30_i_14\ : label is "soft_lutpair448";
  attribute SOFT_HLUTNM of \p_1_out__30_i_15\ : label is "soft_lutpair448";
  attribute SOFT_HLUTNM of \p_1_out__30_i_16\ : label is "soft_lutpair447";
  attribute SOFT_HLUTNM of \p_1_out__30_i_17\ : label is "soft_lutpair447";
  attribute SOFT_HLUTNM of \p_1_out__30_i_18\ : label is "soft_lutpair446";
  attribute SOFT_HLUTNM of \p_1_out__30_i_19\ : label is "soft_lutpair446";
  attribute SOFT_HLUTNM of \p_1_out__30_i_2\ : label is "soft_lutpair454";
  attribute SOFT_HLUTNM of \p_1_out__30_i_20\ : label is "soft_lutpair445";
  attribute SOFT_HLUTNM of \p_1_out__30_i_21\ : label is "soft_lutpair445";
  attribute SOFT_HLUTNM of \p_1_out__30_i_22\ : label is "soft_lutpair444";
  attribute SOFT_HLUTNM of \p_1_out__30_i_23\ : label is "soft_lutpair444";
  attribute SOFT_HLUTNM of \p_1_out__30_i_24\ : label is "soft_lutpair443";
  attribute SOFT_HLUTNM of \p_1_out__30_i_25\ : label is "soft_lutpair443";
  attribute SOFT_HLUTNM of \p_1_out__30_i_26\ : label is "soft_lutpair442";
  attribute SOFT_HLUTNM of \p_1_out__30_i_27\ : label is "soft_lutpair442";
  attribute SOFT_HLUTNM of \p_1_out__30_i_28\ : label is "soft_lutpair441";
  attribute SOFT_HLUTNM of \p_1_out__30_i_3\ : label is "soft_lutpair454";
  attribute SOFT_HLUTNM of \p_1_out__30_i_4\ : label is "soft_lutpair453";
  attribute SOFT_HLUTNM of \p_1_out__30_i_5\ : label is "soft_lutpair453";
  attribute SOFT_HLUTNM of \p_1_out__30_i_6\ : label is "soft_lutpair452";
  attribute SOFT_HLUTNM of \p_1_out__30_i_7\ : label is "soft_lutpair452";
  attribute SOFT_HLUTNM of \p_1_out__30_i_8\ : label is "soft_lutpair451";
  attribute SOFT_HLUTNM of \p_1_out__30_i_9\ : label is "soft_lutpair451";
  attribute SOFT_HLUTNM of \p_1_out__3_i_10\ : label is "soft_lutpair86";
  attribute SOFT_HLUTNM of \p_1_out__3_i_11\ : label is "soft_lutpair85";
  attribute SOFT_HLUTNM of \p_1_out__3_i_12\ : label is "soft_lutpair85";
  attribute SOFT_HLUTNM of \p_1_out__3_i_13\ : label is "soft_lutpair84";
  attribute SOFT_HLUTNM of \p_1_out__3_i_14\ : label is "soft_lutpair84";
  attribute SOFT_HLUTNM of \p_1_out__3_i_15\ : label is "soft_lutpair83";
  attribute SOFT_HLUTNM of \p_1_out__3_i_16\ : label is "soft_lutpair83";
  attribute SOFT_HLUTNM of \p_1_out__3_i_17\ : label is "soft_lutpair82";
  attribute SOFT_HLUTNM of \p_1_out__3_i_18\ : label is "soft_lutpair82";
  attribute SOFT_HLUTNM of \p_1_out__3_i_19\ : label is "soft_lutpair81";
  attribute SOFT_HLUTNM of \p_1_out__3_i_2\ : label is "soft_lutpair90";
  attribute SOFT_HLUTNM of \p_1_out__3_i_20\ : label is "soft_lutpair81";
  attribute SOFT_HLUTNM of \p_1_out__3_i_21\ : label is "soft_lutpair80";
  attribute SOFT_HLUTNM of \p_1_out__3_i_22\ : label is "soft_lutpair80";
  attribute SOFT_HLUTNM of \p_1_out__3_i_23\ : label is "soft_lutpair79";
  attribute SOFT_HLUTNM of \p_1_out__3_i_24\ : label is "soft_lutpair79";
  attribute SOFT_HLUTNM of \p_1_out__3_i_25\ : label is "soft_lutpair78";
  attribute SOFT_HLUTNM of \p_1_out__3_i_26\ : label is "soft_lutpair78";
  attribute SOFT_HLUTNM of \p_1_out__3_i_27\ : label is "soft_lutpair77";
  attribute SOFT_HLUTNM of \p_1_out__3_i_28\ : label is "soft_lutpair77";
  attribute SOFT_HLUTNM of \p_1_out__3_i_3\ : label is "soft_lutpair89";
  attribute SOFT_HLUTNM of \p_1_out__3_i_4\ : label is "soft_lutpair89";
  attribute SOFT_HLUTNM of \p_1_out__3_i_5\ : label is "soft_lutpair88";
  attribute SOFT_HLUTNM of \p_1_out__3_i_6\ : label is "soft_lutpair88";
  attribute SOFT_HLUTNM of \p_1_out__3_i_7\ : label is "soft_lutpair87";
  attribute SOFT_HLUTNM of \p_1_out__3_i_8\ : label is "soft_lutpair87";
  attribute SOFT_HLUTNM of \p_1_out__3_i_9\ : label is "soft_lutpair86";
  attribute KEEP_HIERARCHY of \p_1_out__4\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__4\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__4_i_10\ : label is "soft_lutpair99";
  attribute SOFT_HLUTNM of \p_1_out__4_i_11\ : label is "soft_lutpair99";
  attribute SOFT_HLUTNM of \p_1_out__4_i_12\ : label is "soft_lutpair98";
  attribute SOFT_HLUTNM of \p_1_out__4_i_13\ : label is "soft_lutpair98";
  attribute SOFT_HLUTNM of \p_1_out__4_i_14\ : label is "soft_lutpair97";
  attribute SOFT_HLUTNM of \p_1_out__4_i_15\ : label is "soft_lutpair97";
  attribute SOFT_HLUTNM of \p_1_out__4_i_16\ : label is "soft_lutpair96";
  attribute SOFT_HLUTNM of \p_1_out__4_i_17\ : label is "soft_lutpair96";
  attribute SOFT_HLUTNM of \p_1_out__4_i_18\ : label is "soft_lutpair95";
  attribute SOFT_HLUTNM of \p_1_out__4_i_19\ : label is "soft_lutpair95";
  attribute SOFT_HLUTNM of \p_1_out__4_i_2\ : label is "soft_lutpair103";
  attribute SOFT_HLUTNM of \p_1_out__4_i_20\ : label is "soft_lutpair94";
  attribute SOFT_HLUTNM of \p_1_out__4_i_21\ : label is "soft_lutpair94";
  attribute SOFT_HLUTNM of \p_1_out__4_i_22\ : label is "soft_lutpair93";
  attribute SOFT_HLUTNM of \p_1_out__4_i_23\ : label is "soft_lutpair93";
  attribute SOFT_HLUTNM of \p_1_out__4_i_24\ : label is "soft_lutpair92";
  attribute SOFT_HLUTNM of \p_1_out__4_i_25\ : label is "soft_lutpair92";
  attribute SOFT_HLUTNM of \p_1_out__4_i_26\ : label is "soft_lutpair91";
  attribute SOFT_HLUTNM of \p_1_out__4_i_27\ : label is "soft_lutpair91";
  attribute SOFT_HLUTNM of \p_1_out__4_i_28\ : label is "soft_lutpair90";
  attribute SOFT_HLUTNM of \p_1_out__4_i_3\ : label is "soft_lutpair103";
  attribute SOFT_HLUTNM of \p_1_out__4_i_4\ : label is "soft_lutpair102";
  attribute SOFT_HLUTNM of \p_1_out__4_i_5\ : label is "soft_lutpair102";
  attribute SOFT_HLUTNM of \p_1_out__4_i_6\ : label is "soft_lutpair101";
  attribute SOFT_HLUTNM of \p_1_out__4_i_7\ : label is "soft_lutpair101";
  attribute SOFT_HLUTNM of \p_1_out__4_i_8\ : label is "soft_lutpair100";
  attribute SOFT_HLUTNM of \p_1_out__4_i_9\ : label is "soft_lutpair100";
  attribute KEEP_HIERARCHY of \p_1_out__5\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__5\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__5_i_10\ : label is "soft_lutpair113";
  attribute SOFT_HLUTNM of \p_1_out__5_i_11\ : label is "soft_lutpair112";
  attribute SOFT_HLUTNM of \p_1_out__5_i_12\ : label is "soft_lutpair112";
  attribute SOFT_HLUTNM of \p_1_out__5_i_13\ : label is "soft_lutpair111";
  attribute SOFT_HLUTNM of \p_1_out__5_i_14\ : label is "soft_lutpair111";
  attribute SOFT_HLUTNM of \p_1_out__5_i_15\ : label is "soft_lutpair110";
  attribute SOFT_HLUTNM of \p_1_out__5_i_16\ : label is "soft_lutpair110";
  attribute SOFT_HLUTNM of \p_1_out__5_i_17\ : label is "soft_lutpair109";
  attribute SOFT_HLUTNM of \p_1_out__5_i_18\ : label is "soft_lutpair109";
  attribute SOFT_HLUTNM of \p_1_out__5_i_19\ : label is "soft_lutpair108";
  attribute SOFT_HLUTNM of \p_1_out__5_i_2\ : label is "soft_lutpair117";
  attribute SOFT_HLUTNM of \p_1_out__5_i_20\ : label is "soft_lutpair108";
  attribute SOFT_HLUTNM of \p_1_out__5_i_21\ : label is "soft_lutpair107";
  attribute SOFT_HLUTNM of \p_1_out__5_i_22\ : label is "soft_lutpair107";
  attribute SOFT_HLUTNM of \p_1_out__5_i_23\ : label is "soft_lutpair106";
  attribute SOFT_HLUTNM of \p_1_out__5_i_24\ : label is "soft_lutpair106";
  attribute SOFT_HLUTNM of \p_1_out__5_i_25\ : label is "soft_lutpair105";
  attribute SOFT_HLUTNM of \p_1_out__5_i_26\ : label is "soft_lutpair105";
  attribute SOFT_HLUTNM of \p_1_out__5_i_27\ : label is "soft_lutpair104";
  attribute SOFT_HLUTNM of \p_1_out__5_i_28\ : label is "soft_lutpair104";
  attribute SOFT_HLUTNM of \p_1_out__5_i_3\ : label is "soft_lutpair116";
  attribute SOFT_HLUTNM of \p_1_out__5_i_4\ : label is "soft_lutpair116";
  attribute SOFT_HLUTNM of \p_1_out__5_i_5\ : label is "soft_lutpair115";
  attribute SOFT_HLUTNM of \p_1_out__5_i_6\ : label is "soft_lutpair115";
  attribute SOFT_HLUTNM of \p_1_out__5_i_7\ : label is "soft_lutpair114";
  attribute SOFT_HLUTNM of \p_1_out__5_i_8\ : label is "soft_lutpair114";
  attribute SOFT_HLUTNM of \p_1_out__5_i_9\ : label is "soft_lutpair113";
  attribute KEEP_HIERARCHY of \p_1_out__6\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__6\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__6_i_10\ : label is "soft_lutpair126";
  attribute SOFT_HLUTNM of \p_1_out__6_i_11\ : label is "soft_lutpair126";
  attribute SOFT_HLUTNM of \p_1_out__6_i_12\ : label is "soft_lutpair125";
  attribute SOFT_HLUTNM of \p_1_out__6_i_13\ : label is "soft_lutpair125";
  attribute SOFT_HLUTNM of \p_1_out__6_i_14\ : label is "soft_lutpair124";
  attribute SOFT_HLUTNM of \p_1_out__6_i_15\ : label is "soft_lutpair124";
  attribute SOFT_HLUTNM of \p_1_out__6_i_16\ : label is "soft_lutpair123";
  attribute SOFT_HLUTNM of \p_1_out__6_i_17\ : label is "soft_lutpair123";
  attribute SOFT_HLUTNM of \p_1_out__6_i_18\ : label is "soft_lutpair122";
  attribute SOFT_HLUTNM of \p_1_out__6_i_19\ : label is "soft_lutpair122";
  attribute SOFT_HLUTNM of \p_1_out__6_i_2\ : label is "soft_lutpair130";
  attribute SOFT_HLUTNM of \p_1_out__6_i_20\ : label is "soft_lutpair121";
  attribute SOFT_HLUTNM of \p_1_out__6_i_21\ : label is "soft_lutpair121";
  attribute SOFT_HLUTNM of \p_1_out__6_i_22\ : label is "soft_lutpair120";
  attribute SOFT_HLUTNM of \p_1_out__6_i_23\ : label is "soft_lutpair120";
  attribute SOFT_HLUTNM of \p_1_out__6_i_24\ : label is "soft_lutpair119";
  attribute SOFT_HLUTNM of \p_1_out__6_i_25\ : label is "soft_lutpair119";
  attribute SOFT_HLUTNM of \p_1_out__6_i_26\ : label is "soft_lutpair118";
  attribute SOFT_HLUTNM of \p_1_out__6_i_27\ : label is "soft_lutpair118";
  attribute SOFT_HLUTNM of \p_1_out__6_i_28\ : label is "soft_lutpair117";
  attribute SOFT_HLUTNM of \p_1_out__6_i_3\ : label is "soft_lutpair130";
  attribute SOFT_HLUTNM of \p_1_out__6_i_4\ : label is "soft_lutpair129";
  attribute SOFT_HLUTNM of \p_1_out__6_i_5\ : label is "soft_lutpair129";
  attribute SOFT_HLUTNM of \p_1_out__6_i_6\ : label is "soft_lutpair128";
  attribute SOFT_HLUTNM of \p_1_out__6_i_7\ : label is "soft_lutpair128";
  attribute SOFT_HLUTNM of \p_1_out__6_i_8\ : label is "soft_lutpair127";
  attribute SOFT_HLUTNM of \p_1_out__6_i_9\ : label is "soft_lutpair127";
  attribute KEEP_HIERARCHY of \p_1_out__7\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__7\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__7_i_10\ : label is "soft_lutpair140";
  attribute SOFT_HLUTNM of \p_1_out__7_i_11\ : label is "soft_lutpair139";
  attribute SOFT_HLUTNM of \p_1_out__7_i_12\ : label is "soft_lutpair139";
  attribute SOFT_HLUTNM of \p_1_out__7_i_13\ : label is "soft_lutpair138";
  attribute SOFT_HLUTNM of \p_1_out__7_i_14\ : label is "soft_lutpair138";
  attribute SOFT_HLUTNM of \p_1_out__7_i_15\ : label is "soft_lutpair137";
  attribute SOFT_HLUTNM of \p_1_out__7_i_16\ : label is "soft_lutpair137";
  attribute SOFT_HLUTNM of \p_1_out__7_i_17\ : label is "soft_lutpair136";
  attribute SOFT_HLUTNM of \p_1_out__7_i_18\ : label is "soft_lutpair136";
  attribute SOFT_HLUTNM of \p_1_out__7_i_19\ : label is "soft_lutpair135";
  attribute SOFT_HLUTNM of \p_1_out__7_i_2\ : label is "soft_lutpair144";
  attribute SOFT_HLUTNM of \p_1_out__7_i_20\ : label is "soft_lutpair135";
  attribute SOFT_HLUTNM of \p_1_out__7_i_21\ : label is "soft_lutpair134";
  attribute SOFT_HLUTNM of \p_1_out__7_i_22\ : label is "soft_lutpair134";
  attribute SOFT_HLUTNM of \p_1_out__7_i_23\ : label is "soft_lutpair133";
  attribute SOFT_HLUTNM of \p_1_out__7_i_24\ : label is "soft_lutpair133";
  attribute SOFT_HLUTNM of \p_1_out__7_i_25\ : label is "soft_lutpair132";
  attribute SOFT_HLUTNM of \p_1_out__7_i_26\ : label is "soft_lutpair132";
  attribute SOFT_HLUTNM of \p_1_out__7_i_27\ : label is "soft_lutpair131";
  attribute SOFT_HLUTNM of \p_1_out__7_i_28\ : label is "soft_lutpair131";
  attribute SOFT_HLUTNM of \p_1_out__7_i_3\ : label is "soft_lutpair143";
  attribute SOFT_HLUTNM of \p_1_out__7_i_4\ : label is "soft_lutpair143";
  attribute SOFT_HLUTNM of \p_1_out__7_i_5\ : label is "soft_lutpair142";
  attribute SOFT_HLUTNM of \p_1_out__7_i_6\ : label is "soft_lutpair142";
  attribute SOFT_HLUTNM of \p_1_out__7_i_7\ : label is "soft_lutpair141";
  attribute SOFT_HLUTNM of \p_1_out__7_i_8\ : label is "soft_lutpair141";
  attribute SOFT_HLUTNM of \p_1_out__7_i_9\ : label is "soft_lutpair140";
  attribute KEEP_HIERARCHY of \p_1_out__8\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__8\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__8_i_10\ : label is "soft_lutpair153";
  attribute SOFT_HLUTNM of \p_1_out__8_i_11\ : label is "soft_lutpair153";
  attribute SOFT_HLUTNM of \p_1_out__8_i_12\ : label is "soft_lutpair152";
  attribute SOFT_HLUTNM of \p_1_out__8_i_13\ : label is "soft_lutpair152";
  attribute SOFT_HLUTNM of \p_1_out__8_i_14\ : label is "soft_lutpair151";
  attribute SOFT_HLUTNM of \p_1_out__8_i_15\ : label is "soft_lutpair151";
  attribute SOFT_HLUTNM of \p_1_out__8_i_16\ : label is "soft_lutpair150";
  attribute SOFT_HLUTNM of \p_1_out__8_i_17\ : label is "soft_lutpair150";
  attribute SOFT_HLUTNM of \p_1_out__8_i_18\ : label is "soft_lutpair149";
  attribute SOFT_HLUTNM of \p_1_out__8_i_19\ : label is "soft_lutpair149";
  attribute SOFT_HLUTNM of \p_1_out__8_i_2\ : label is "soft_lutpair157";
  attribute SOFT_HLUTNM of \p_1_out__8_i_20\ : label is "soft_lutpair148";
  attribute SOFT_HLUTNM of \p_1_out__8_i_21\ : label is "soft_lutpair148";
  attribute SOFT_HLUTNM of \p_1_out__8_i_22\ : label is "soft_lutpair147";
  attribute SOFT_HLUTNM of \p_1_out__8_i_23\ : label is "soft_lutpair147";
  attribute SOFT_HLUTNM of \p_1_out__8_i_24\ : label is "soft_lutpair146";
  attribute SOFT_HLUTNM of \p_1_out__8_i_25\ : label is "soft_lutpair146";
  attribute SOFT_HLUTNM of \p_1_out__8_i_26\ : label is "soft_lutpair145";
  attribute SOFT_HLUTNM of \p_1_out__8_i_27\ : label is "soft_lutpair145";
  attribute SOFT_HLUTNM of \p_1_out__8_i_28\ : label is "soft_lutpair144";
  attribute SOFT_HLUTNM of \p_1_out__8_i_3\ : label is "soft_lutpair157";
  attribute SOFT_HLUTNM of \p_1_out__8_i_4\ : label is "soft_lutpair156";
  attribute SOFT_HLUTNM of \p_1_out__8_i_5\ : label is "soft_lutpair156";
  attribute SOFT_HLUTNM of \p_1_out__8_i_6\ : label is "soft_lutpair155";
  attribute SOFT_HLUTNM of \p_1_out__8_i_7\ : label is "soft_lutpair155";
  attribute SOFT_HLUTNM of \p_1_out__8_i_8\ : label is "soft_lutpair154";
  attribute SOFT_HLUTNM of \p_1_out__8_i_9\ : label is "soft_lutpair154";
  attribute KEEP_HIERARCHY of \p_1_out__9\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \p_1_out__9\ : label is "{SYNTH-11 {cell *THIS*}}";
  attribute SOFT_HLUTNM of \p_1_out__9_i_10\ : label is "soft_lutpair167";
  attribute SOFT_HLUTNM of \p_1_out__9_i_11\ : label is "soft_lutpair166";
  attribute SOFT_HLUTNM of \p_1_out__9_i_12\ : label is "soft_lutpair166";
  attribute SOFT_HLUTNM of \p_1_out__9_i_13\ : label is "soft_lutpair165";
  attribute SOFT_HLUTNM of \p_1_out__9_i_14\ : label is "soft_lutpair165";
  attribute SOFT_HLUTNM of \p_1_out__9_i_15\ : label is "soft_lutpair164";
  attribute SOFT_HLUTNM of \p_1_out__9_i_16\ : label is "soft_lutpair164";
  attribute SOFT_HLUTNM of \p_1_out__9_i_17\ : label is "soft_lutpair163";
  attribute SOFT_HLUTNM of \p_1_out__9_i_18\ : label is "soft_lutpair163";
  attribute SOFT_HLUTNM of \p_1_out__9_i_19\ : label is "soft_lutpair162";
  attribute SOFT_HLUTNM of \p_1_out__9_i_2\ : label is "soft_lutpair171";
  attribute SOFT_HLUTNM of \p_1_out__9_i_20\ : label is "soft_lutpair162";
  attribute SOFT_HLUTNM of \p_1_out__9_i_21\ : label is "soft_lutpair161";
  attribute SOFT_HLUTNM of \p_1_out__9_i_22\ : label is "soft_lutpair161";
  attribute SOFT_HLUTNM of \p_1_out__9_i_23\ : label is "soft_lutpair160";
  attribute SOFT_HLUTNM of \p_1_out__9_i_24\ : label is "soft_lutpair160";
  attribute SOFT_HLUTNM of \p_1_out__9_i_25\ : label is "soft_lutpair159";
  attribute SOFT_HLUTNM of \p_1_out__9_i_26\ : label is "soft_lutpair159";
  attribute SOFT_HLUTNM of \p_1_out__9_i_27\ : label is "soft_lutpair158";
  attribute SOFT_HLUTNM of \p_1_out__9_i_28\ : label is "soft_lutpair158";
  attribute SOFT_HLUTNM of \p_1_out__9_i_3\ : label is "soft_lutpair170";
  attribute SOFT_HLUTNM of \p_1_out__9_i_4\ : label is "soft_lutpair170";
  attribute SOFT_HLUTNM of \p_1_out__9_i_5\ : label is "soft_lutpair169";
  attribute SOFT_HLUTNM of \p_1_out__9_i_6\ : label is "soft_lutpair169";
  attribute SOFT_HLUTNM of \p_1_out__9_i_7\ : label is "soft_lutpair168";
  attribute SOFT_HLUTNM of \p_1_out__9_i_8\ : label is "soft_lutpair168";
  attribute SOFT_HLUTNM of \p_1_out__9_i_9\ : label is "soft_lutpair167";
  attribute SOFT_HLUTNM of p_1_out_i_10 : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of p_1_out_i_11 : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of p_1_out_i_12 : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of p_1_out_i_13 : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of p_1_out_i_14 : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of p_1_out_i_15 : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of p_1_out_i_16 : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of p_1_out_i_17 : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of p_1_out_i_18 : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of p_1_out_i_19 : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of p_1_out_i_2 : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of p_1_out_i_20 : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of p_1_out_i_21 : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of p_1_out_i_22 : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of p_1_out_i_23 : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of p_1_out_i_24 : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of p_1_out_i_25 : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of p_1_out_i_26 : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of p_1_out_i_27 : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of p_1_out_i_28 : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of p_1_out_i_3 : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of p_1_out_i_4 : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of p_1_out_i_5 : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of p_1_out_i_6 : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of p_1_out_i_7 : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of p_1_out_i_8 : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of p_1_out_i_9 : label is "soft_lutpair32";
begin
\Delay10_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(0),
      Q => Delay10_out1(0),
      R => reset
    );
\Delay10_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(10),
      Q => Delay10_out1(10),
      R => reset
    );
\Delay10_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(11),
      Q => Delay10_out1(11),
      R => reset
    );
\Delay10_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(12),
      Q => Delay10_out1(12),
      R => reset
    );
\Delay10_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(13),
      Q => Delay10_out1(13),
      R => reset
    );
\Delay10_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(14),
      Q => Delay10_out1(14),
      R => reset
    );
\Delay10_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(15),
      Q => Delay10_out1(15),
      R => reset
    );
\Delay10_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(16),
      Q => Delay10_out1(16),
      R => reset
    );
\Delay10_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(17),
      Q => Delay10_out1(17),
      R => reset
    );
\Delay10_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(18),
      Q => Delay10_out1(18),
      R => reset
    );
\Delay10_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(19),
      Q => Delay10_out1(19),
      R => reset
    );
\Delay10_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(1),
      Q => Delay10_out1(1),
      R => reset
    );
\Delay10_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(20),
      Q => Delay10_out1(20),
      R => reset
    );
\Delay10_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(21),
      Q => Delay10_out1(21),
      R => reset
    );
\Delay10_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(22),
      Q => Delay10_out1(22),
      R => reset
    );
\Delay10_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(23),
      Q => Delay10_out1(23),
      R => reset
    );
\Delay10_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(24),
      Q => Delay10_out1(24),
      R => reset
    );
\Delay10_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(25),
      Q => Delay10_out1(25),
      R => reset
    );
\Delay10_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(26),
      Q => Delay10_out1(26),
      R => reset
    );
\Delay10_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(2),
      Q => Delay10_out1(2),
      R => reset
    );
\Delay10_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(3),
      Q => Delay10_out1(3),
      R => reset
    );
\Delay10_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(4),
      Q => Delay10_out1(4),
      R => reset
    );
\Delay10_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(5),
      Q => Delay10_out1(5),
      R => reset
    );
\Delay10_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(6),
      Q => Delay10_out1(6),
      R => reset
    );
\Delay10_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(7),
      Q => Delay10_out1(7),
      R => reset
    );
\Delay10_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(8),
      Q => Delay10_out1(8),
      R => reset
    );
\Delay10_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in10(9),
      Q => Delay10_out1(9),
      R => reset
    );
\Delay11_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(0),
      Q => Delay11_out1(0),
      R => reset
    );
\Delay11_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(10),
      Q => Delay11_out1(10),
      R => reset
    );
\Delay11_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(11),
      Q => Delay11_out1(11),
      R => reset
    );
\Delay11_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(12),
      Q => Delay11_out1(12),
      R => reset
    );
\Delay11_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(13),
      Q => Delay11_out1(13),
      R => reset
    );
\Delay11_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(14),
      Q => Delay11_out1(14),
      R => reset
    );
\Delay11_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(15),
      Q => Delay11_out1(15),
      R => reset
    );
\Delay11_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(16),
      Q => Delay11_out1(16),
      R => reset
    );
\Delay11_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(17),
      Q => Delay11_out1(17),
      R => reset
    );
\Delay11_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(18),
      Q => Delay11_out1(18),
      R => reset
    );
\Delay11_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(19),
      Q => Delay11_out1(19),
      R => reset
    );
\Delay11_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(1),
      Q => Delay11_out1(1),
      R => reset
    );
\Delay11_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(20),
      Q => Delay11_out1(20),
      R => reset
    );
\Delay11_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(21),
      Q => Delay11_out1(21),
      R => reset
    );
\Delay11_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(22),
      Q => Delay11_out1(22),
      R => reset
    );
\Delay11_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(23),
      Q => Delay11_out1(23),
      R => reset
    );
\Delay11_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(24),
      Q => Delay11_out1(24),
      R => reset
    );
\Delay11_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(25),
      Q => Delay11_out1(25),
      R => reset
    );
\Delay11_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(26),
      Q => Delay11_out1(26),
      R => reset
    );
\Delay11_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(2),
      Q => Delay11_out1(2),
      R => reset
    );
\Delay11_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(3),
      Q => Delay11_out1(3),
      R => reset
    );
\Delay11_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(4),
      Q => Delay11_out1(4),
      R => reset
    );
\Delay11_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(5),
      Q => Delay11_out1(5),
      R => reset
    );
\Delay11_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(6),
      Q => Delay11_out1(6),
      R => reset
    );
\Delay11_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(7),
      Q => Delay11_out1(7),
      R => reset
    );
\Delay11_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(8),
      Q => Delay11_out1(8),
      R => reset
    );
\Delay11_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in11(9),
      Q => Delay11_out1(9),
      R => reset
    );
\Delay12_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(0),
      Q => Delay12_out1(0),
      R => reset
    );
\Delay12_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(10),
      Q => Delay12_out1(10),
      R => reset
    );
\Delay12_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(11),
      Q => Delay12_out1(11),
      R => reset
    );
\Delay12_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(12),
      Q => Delay12_out1(12),
      R => reset
    );
\Delay12_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(13),
      Q => Delay12_out1(13),
      R => reset
    );
\Delay12_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(14),
      Q => Delay12_out1(14),
      R => reset
    );
\Delay12_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(15),
      Q => Delay12_out1(15),
      R => reset
    );
\Delay12_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(16),
      Q => Delay12_out1(16),
      R => reset
    );
\Delay12_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(17),
      Q => Delay12_out1(17),
      R => reset
    );
\Delay12_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(18),
      Q => Delay12_out1(18),
      R => reset
    );
\Delay12_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(19),
      Q => Delay12_out1(19),
      R => reset
    );
\Delay12_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(1),
      Q => Delay12_out1(1),
      R => reset
    );
\Delay12_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(20),
      Q => Delay12_out1(20),
      R => reset
    );
\Delay12_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(21),
      Q => Delay12_out1(21),
      R => reset
    );
\Delay12_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(22),
      Q => Delay12_out1(22),
      R => reset
    );
\Delay12_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(23),
      Q => Delay12_out1(23),
      R => reset
    );
\Delay12_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(24),
      Q => Delay12_out1(24),
      R => reset
    );
\Delay12_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(25),
      Q => Delay12_out1(25),
      R => reset
    );
\Delay12_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(26),
      Q => Delay12_out1(26),
      R => reset
    );
\Delay12_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(2),
      Q => Delay12_out1(2),
      R => reset
    );
\Delay12_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(3),
      Q => Delay12_out1(3),
      R => reset
    );
\Delay12_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(4),
      Q => Delay12_out1(4),
      R => reset
    );
\Delay12_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(5),
      Q => Delay12_out1(5),
      R => reset
    );
\Delay12_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(6),
      Q => Delay12_out1(6),
      R => reset
    );
\Delay12_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(7),
      Q => Delay12_out1(7),
      R => reset
    );
\Delay12_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(8),
      Q => Delay12_out1(8),
      R => reset
    );
\Delay12_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in12(9),
      Q => Delay12_out1(9),
      R => reset
    );
\Delay13_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(0),
      Q => Delay13_out1(0),
      R => reset
    );
\Delay13_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(10),
      Q => Delay13_out1(10),
      R => reset
    );
\Delay13_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(11),
      Q => Delay13_out1(11),
      R => reset
    );
\Delay13_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(12),
      Q => Delay13_out1(12),
      R => reset
    );
\Delay13_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(13),
      Q => Delay13_out1(13),
      R => reset
    );
\Delay13_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(14),
      Q => Delay13_out1(14),
      R => reset
    );
\Delay13_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(15),
      Q => Delay13_out1(15),
      R => reset
    );
\Delay13_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(16),
      Q => Delay13_out1(16),
      R => reset
    );
\Delay13_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(17),
      Q => Delay13_out1(17),
      R => reset
    );
\Delay13_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(18),
      Q => Delay13_out1(18),
      R => reset
    );
\Delay13_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(19),
      Q => Delay13_out1(19),
      R => reset
    );
\Delay13_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(1),
      Q => Delay13_out1(1),
      R => reset
    );
\Delay13_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(20),
      Q => Delay13_out1(20),
      R => reset
    );
\Delay13_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(21),
      Q => Delay13_out1(21),
      R => reset
    );
\Delay13_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(22),
      Q => Delay13_out1(22),
      R => reset
    );
\Delay13_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(23),
      Q => Delay13_out1(23),
      R => reset
    );
\Delay13_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(24),
      Q => Delay13_out1(24),
      R => reset
    );
\Delay13_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(25),
      Q => Delay13_out1(25),
      R => reset
    );
\Delay13_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(26),
      Q => Delay13_out1(26),
      R => reset
    );
\Delay13_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(2),
      Q => Delay13_out1(2),
      R => reset
    );
\Delay13_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(3),
      Q => Delay13_out1(3),
      R => reset
    );
\Delay13_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(4),
      Q => Delay13_out1(4),
      R => reset
    );
\Delay13_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(5),
      Q => Delay13_out1(5),
      R => reset
    );
\Delay13_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(6),
      Q => Delay13_out1(6),
      R => reset
    );
\Delay13_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(7),
      Q => Delay13_out1(7),
      R => reset
    );
\Delay13_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(8),
      Q => Delay13_out1(8),
      R => reset
    );
\Delay13_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in13(9),
      Q => Delay13_out1(9),
      R => reset
    );
\Delay14_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(0),
      Q => Delay14_out1(0),
      R => reset
    );
\Delay14_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(10),
      Q => Delay14_out1(10),
      R => reset
    );
\Delay14_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(11),
      Q => Delay14_out1(11),
      R => reset
    );
\Delay14_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(12),
      Q => Delay14_out1(12),
      R => reset
    );
\Delay14_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(13),
      Q => Delay14_out1(13),
      R => reset
    );
\Delay14_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(14),
      Q => Delay14_out1(14),
      R => reset
    );
\Delay14_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(15),
      Q => Delay14_out1(15),
      R => reset
    );
\Delay14_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(16),
      Q => Delay14_out1(16),
      R => reset
    );
\Delay14_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(17),
      Q => Delay14_out1(17),
      R => reset
    );
\Delay14_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(18),
      Q => Delay14_out1(18),
      R => reset
    );
\Delay14_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(19),
      Q => Delay14_out1(19),
      R => reset
    );
\Delay14_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(1),
      Q => Delay14_out1(1),
      R => reset
    );
\Delay14_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(20),
      Q => Delay14_out1(20),
      R => reset
    );
\Delay14_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(21),
      Q => Delay14_out1(21),
      R => reset
    );
\Delay14_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(22),
      Q => Delay14_out1(22),
      R => reset
    );
\Delay14_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(23),
      Q => Delay14_out1(23),
      R => reset
    );
\Delay14_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(24),
      Q => Delay14_out1(24),
      R => reset
    );
\Delay14_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(25),
      Q => Delay14_out1(25),
      R => reset
    );
\Delay14_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(26),
      Q => Delay14_out1(26),
      R => reset
    );
\Delay14_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(2),
      Q => Delay14_out1(2),
      R => reset
    );
\Delay14_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(3),
      Q => Delay14_out1(3),
      R => reset
    );
\Delay14_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(4),
      Q => Delay14_out1(4),
      R => reset
    );
\Delay14_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(5),
      Q => Delay14_out1(5),
      R => reset
    );
\Delay14_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(6),
      Q => Delay14_out1(6),
      R => reset
    );
\Delay14_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(7),
      Q => Delay14_out1(7),
      R => reset
    );
\Delay14_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(8),
      Q => Delay14_out1(8),
      R => reset
    );
\Delay14_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in14(9),
      Q => Delay14_out1(9),
      R => reset
    );
\Delay15_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(0),
      Q => Delay15_out1(0),
      R => reset
    );
\Delay15_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(10),
      Q => Delay15_out1(10),
      R => reset
    );
\Delay15_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(11),
      Q => Delay15_out1(11),
      R => reset
    );
\Delay15_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(12),
      Q => Delay15_out1(12),
      R => reset
    );
\Delay15_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(13),
      Q => Delay15_out1(13),
      R => reset
    );
\Delay15_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(14),
      Q => Delay15_out1(14),
      R => reset
    );
\Delay15_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(15),
      Q => Delay15_out1(15),
      R => reset
    );
\Delay15_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(16),
      Q => Delay15_out1(16),
      R => reset
    );
\Delay15_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(17),
      Q => Delay15_out1(17),
      R => reset
    );
\Delay15_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(18),
      Q => Delay15_out1(18),
      R => reset
    );
\Delay15_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(19),
      Q => Delay15_out1(19),
      R => reset
    );
\Delay15_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(1),
      Q => Delay15_out1(1),
      R => reset
    );
\Delay15_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(20),
      Q => Delay15_out1(20),
      R => reset
    );
\Delay15_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(21),
      Q => Delay15_out1(21),
      R => reset
    );
\Delay15_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(22),
      Q => Delay15_out1(22),
      R => reset
    );
\Delay15_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(23),
      Q => Delay15_out1(23),
      R => reset
    );
\Delay15_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(24),
      Q => Delay15_out1(24),
      R => reset
    );
\Delay15_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(25),
      Q => Delay15_out1(25),
      R => reset
    );
\Delay15_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(26),
      Q => Delay15_out1(26),
      R => reset
    );
\Delay15_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(2),
      Q => Delay15_out1(2),
      R => reset
    );
\Delay15_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(3),
      Q => Delay15_out1(3),
      R => reset
    );
\Delay15_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(4),
      Q => Delay15_out1(4),
      R => reset
    );
\Delay15_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(5),
      Q => Delay15_out1(5),
      R => reset
    );
\Delay15_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(6),
      Q => Delay15_out1(6),
      R => reset
    );
\Delay15_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(7),
      Q => Delay15_out1(7),
      R => reset
    );
\Delay15_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(8),
      Q => Delay15_out1(8),
      R => reset
    );
\Delay15_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in15(9),
      Q => Delay15_out1(9),
      R => reset
    );
\Delay16_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(0),
      Q => Delay16_out1(0),
      R => reset
    );
\Delay16_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(10),
      Q => Delay16_out1(10),
      R => reset
    );
\Delay16_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(11),
      Q => Delay16_out1(11),
      R => reset
    );
\Delay16_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(12),
      Q => Delay16_out1(12),
      R => reset
    );
\Delay16_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(13),
      Q => Delay16_out1(13),
      R => reset
    );
\Delay16_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(14),
      Q => Delay16_out1(14),
      R => reset
    );
\Delay16_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(15),
      Q => Delay16_out1(15),
      R => reset
    );
\Delay16_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(16),
      Q => Delay16_out1(16),
      R => reset
    );
\Delay16_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(17),
      Q => Delay16_out1(17),
      R => reset
    );
\Delay16_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(18),
      Q => Delay16_out1(18),
      R => reset
    );
\Delay16_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(19),
      Q => Delay16_out1(19),
      R => reset
    );
\Delay16_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(1),
      Q => Delay16_out1(1),
      R => reset
    );
\Delay16_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(20),
      Q => Delay16_out1(20),
      R => reset
    );
\Delay16_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(21),
      Q => Delay16_out1(21),
      R => reset
    );
\Delay16_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(22),
      Q => Delay16_out1(22),
      R => reset
    );
\Delay16_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(23),
      Q => Delay16_out1(23),
      R => reset
    );
\Delay16_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(24),
      Q => Delay16_out1(24),
      R => reset
    );
\Delay16_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(25),
      Q => Delay16_out1(25),
      R => reset
    );
\Delay16_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(26),
      Q => Delay16_out1(26),
      R => reset
    );
\Delay16_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(2),
      Q => Delay16_out1(2),
      R => reset
    );
\Delay16_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(3),
      Q => Delay16_out1(3),
      R => reset
    );
\Delay16_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(4),
      Q => Delay16_out1(4),
      R => reset
    );
\Delay16_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(5),
      Q => Delay16_out1(5),
      R => reset
    );
\Delay16_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(6),
      Q => Delay16_out1(6),
      R => reset
    );
\Delay16_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(7),
      Q => Delay16_out1(7),
      R => reset
    );
\Delay16_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(8),
      Q => Delay16_out1(8),
      R => reset
    );
\Delay16_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in16(9),
      Q => Delay16_out1(9),
      R => reset
    );
\Delay17_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(0),
      Q => Delay17_out1(0),
      R => reset
    );
\Delay17_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(10),
      Q => Delay17_out1(10),
      R => reset
    );
\Delay17_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(11),
      Q => Delay17_out1(11),
      R => reset
    );
\Delay17_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(12),
      Q => Delay17_out1(12),
      R => reset
    );
\Delay17_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(13),
      Q => Delay17_out1(13),
      R => reset
    );
\Delay17_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(14),
      Q => Delay17_out1(14),
      R => reset
    );
\Delay17_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(15),
      Q => Delay17_out1(15),
      R => reset
    );
\Delay17_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(16),
      Q => Delay17_out1(16),
      R => reset
    );
\Delay17_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(17),
      Q => Delay17_out1(17),
      R => reset
    );
\Delay17_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(18),
      Q => Delay17_out1(18),
      R => reset
    );
\Delay17_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(19),
      Q => Delay17_out1(19),
      R => reset
    );
\Delay17_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(1),
      Q => Delay17_out1(1),
      R => reset
    );
\Delay17_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(20),
      Q => Delay17_out1(20),
      R => reset
    );
\Delay17_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(21),
      Q => Delay17_out1(21),
      R => reset
    );
\Delay17_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(22),
      Q => Delay17_out1(22),
      R => reset
    );
\Delay17_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(23),
      Q => Delay17_out1(23),
      R => reset
    );
\Delay17_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(24),
      Q => Delay17_out1(24),
      R => reset
    );
\Delay17_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(25),
      Q => Delay17_out1(25),
      R => reset
    );
\Delay17_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(26),
      Q => Delay17_out1(26),
      R => reset
    );
\Delay17_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(2),
      Q => Delay17_out1(2),
      R => reset
    );
\Delay17_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(3),
      Q => Delay17_out1(3),
      R => reset
    );
\Delay17_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(4),
      Q => Delay17_out1(4),
      R => reset
    );
\Delay17_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(5),
      Q => Delay17_out1(5),
      R => reset
    );
\Delay17_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(6),
      Q => Delay17_out1(6),
      R => reset
    );
\Delay17_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(7),
      Q => Delay17_out1(7),
      R => reset
    );
\Delay17_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(8),
      Q => Delay17_out1(8),
      R => reset
    );
\Delay17_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in17(9),
      Q => Delay17_out1(9),
      R => reset
    );
\Delay18_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(0),
      Q => Delay18_out1(0),
      R => reset
    );
\Delay18_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(10),
      Q => Delay18_out1(10),
      R => reset
    );
\Delay18_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(11),
      Q => Delay18_out1(11),
      R => reset
    );
\Delay18_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(12),
      Q => Delay18_out1(12),
      R => reset
    );
\Delay18_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(13),
      Q => Delay18_out1(13),
      R => reset
    );
\Delay18_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(14),
      Q => Delay18_out1(14),
      R => reset
    );
\Delay18_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(15),
      Q => Delay18_out1(15),
      R => reset
    );
\Delay18_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(16),
      Q => Delay18_out1(16),
      R => reset
    );
\Delay18_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(17),
      Q => Delay18_out1(17),
      R => reset
    );
\Delay18_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(18),
      Q => Delay18_out1(18),
      R => reset
    );
\Delay18_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(19),
      Q => Delay18_out1(19),
      R => reset
    );
\Delay18_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(1),
      Q => Delay18_out1(1),
      R => reset
    );
\Delay18_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(20),
      Q => Delay18_out1(20),
      R => reset
    );
\Delay18_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(21),
      Q => Delay18_out1(21),
      R => reset
    );
\Delay18_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(22),
      Q => Delay18_out1(22),
      R => reset
    );
\Delay18_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(23),
      Q => Delay18_out1(23),
      R => reset
    );
\Delay18_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(24),
      Q => Delay18_out1(24),
      R => reset
    );
\Delay18_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(25),
      Q => Delay18_out1(25),
      R => reset
    );
\Delay18_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(26),
      Q => Delay18_out1(26),
      R => reset
    );
\Delay18_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(2),
      Q => Delay18_out1(2),
      R => reset
    );
\Delay18_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(3),
      Q => Delay18_out1(3),
      R => reset
    );
\Delay18_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(4),
      Q => Delay18_out1(4),
      R => reset
    );
\Delay18_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(5),
      Q => Delay18_out1(5),
      R => reset
    );
\Delay18_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(6),
      Q => Delay18_out1(6),
      R => reset
    );
\Delay18_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(7),
      Q => Delay18_out1(7),
      R => reset
    );
\Delay18_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(8),
      Q => Delay18_out1(8),
      R => reset
    );
\Delay18_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in18(9),
      Q => Delay18_out1(9),
      R => reset
    );
\Delay19_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(0),
      Q => Delay19_out1(0),
      R => reset
    );
\Delay19_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(10),
      Q => Delay19_out1(10),
      R => reset
    );
\Delay19_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(11),
      Q => Delay19_out1(11),
      R => reset
    );
\Delay19_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(12),
      Q => Delay19_out1(12),
      R => reset
    );
\Delay19_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(13),
      Q => Delay19_out1(13),
      R => reset
    );
\Delay19_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(14),
      Q => Delay19_out1(14),
      R => reset
    );
\Delay19_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(15),
      Q => Delay19_out1(15),
      R => reset
    );
\Delay19_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(16),
      Q => Delay19_out1(16),
      R => reset
    );
\Delay19_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(17),
      Q => Delay19_out1(17),
      R => reset
    );
\Delay19_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(18),
      Q => Delay19_out1(18),
      R => reset
    );
\Delay19_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(19),
      Q => Delay19_out1(19),
      R => reset
    );
\Delay19_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(1),
      Q => Delay19_out1(1),
      R => reset
    );
\Delay19_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(20),
      Q => Delay19_out1(20),
      R => reset
    );
\Delay19_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(21),
      Q => Delay19_out1(21),
      R => reset
    );
\Delay19_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(22),
      Q => Delay19_out1(22),
      R => reset
    );
\Delay19_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(23),
      Q => Delay19_out1(23),
      R => reset
    );
\Delay19_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(24),
      Q => Delay19_out1(24),
      R => reset
    );
\Delay19_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(25),
      Q => Delay19_out1(25),
      R => reset
    );
\Delay19_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(26),
      Q => Delay19_out1(26),
      R => reset
    );
\Delay19_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(2),
      Q => Delay19_out1(2),
      R => reset
    );
\Delay19_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(3),
      Q => Delay19_out1(3),
      R => reset
    );
\Delay19_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(4),
      Q => Delay19_out1(4),
      R => reset
    );
\Delay19_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(5),
      Q => Delay19_out1(5),
      R => reset
    );
\Delay19_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(6),
      Q => Delay19_out1(6),
      R => reset
    );
\Delay19_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(7),
      Q => Delay19_out1(7),
      R => reset
    );
\Delay19_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(8),
      Q => Delay19_out1(8),
      R => reset
    );
\Delay19_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in19(9),
      Q => Delay19_out1(9),
      R => reset
    );
\Delay1_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(0),
      Q => Delay1_out1(0),
      R => reset
    );
\Delay1_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(10),
      Q => Delay1_out1(10),
      R => reset
    );
\Delay1_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(11),
      Q => Delay1_out1(11),
      R => reset
    );
\Delay1_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(12),
      Q => Delay1_out1(12),
      R => reset
    );
\Delay1_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(13),
      Q => Delay1_out1(13),
      R => reset
    );
\Delay1_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(14),
      Q => Delay1_out1(14),
      R => reset
    );
\Delay1_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(15),
      Q => Delay1_out1(15),
      R => reset
    );
\Delay1_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(16),
      Q => Delay1_out1(16),
      R => reset
    );
\Delay1_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(17),
      Q => Delay1_out1(17),
      R => reset
    );
\Delay1_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(18),
      Q => Delay1_out1(18),
      R => reset
    );
\Delay1_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(19),
      Q => Delay1_out1(19),
      R => reset
    );
\Delay1_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(1),
      Q => Delay1_out1(1),
      R => reset
    );
\Delay1_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(20),
      Q => Delay1_out1(20),
      R => reset
    );
\Delay1_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(21),
      Q => Delay1_out1(21),
      R => reset
    );
\Delay1_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(22),
      Q => Delay1_out1(22),
      R => reset
    );
\Delay1_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(23),
      Q => Delay1_out1(23),
      R => reset
    );
\Delay1_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(24),
      Q => Delay1_out1(24),
      R => reset
    );
\Delay1_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(25),
      Q => Delay1_out1(25),
      R => reset
    );
\Delay1_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(26),
      Q => Delay1_out1(26),
      R => reset
    );
\Delay1_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(2),
      Q => Delay1_out1(2),
      R => reset
    );
\Delay1_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(3),
      Q => Delay1_out1(3),
      R => reset
    );
\Delay1_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(4),
      Q => Delay1_out1(4),
      R => reset
    );
\Delay1_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(5),
      Q => Delay1_out1(5),
      R => reset
    );
\Delay1_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(6),
      Q => Delay1_out1(6),
      R => reset
    );
\Delay1_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(7),
      Q => Delay1_out1(7),
      R => reset
    );
\Delay1_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(8),
      Q => Delay1_out1(8),
      R => reset
    );
\Delay1_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in1(9),
      Q => Delay1_out1(9),
      R => reset
    );
\Delay20_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(0),
      Q => Delay20_out1(0),
      R => reset
    );
\Delay20_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(10),
      Q => Delay20_out1(10),
      R => reset
    );
\Delay20_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(11),
      Q => Delay20_out1(11),
      R => reset
    );
\Delay20_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(12),
      Q => Delay20_out1(12),
      R => reset
    );
\Delay20_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(13),
      Q => Delay20_out1(13),
      R => reset
    );
\Delay20_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(14),
      Q => Delay20_out1(14),
      R => reset
    );
\Delay20_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(15),
      Q => Delay20_out1(15),
      R => reset
    );
\Delay20_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(16),
      Q => Delay20_out1(16),
      R => reset
    );
\Delay20_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(17),
      Q => Delay20_out1(17),
      R => reset
    );
\Delay20_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(18),
      Q => Delay20_out1(18),
      R => reset
    );
\Delay20_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(19),
      Q => Delay20_out1(19),
      R => reset
    );
\Delay20_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(1),
      Q => Delay20_out1(1),
      R => reset
    );
\Delay20_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(20),
      Q => Delay20_out1(20),
      R => reset
    );
\Delay20_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(21),
      Q => Delay20_out1(21),
      R => reset
    );
\Delay20_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(22),
      Q => Delay20_out1(22),
      R => reset
    );
\Delay20_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(23),
      Q => Delay20_out1(23),
      R => reset
    );
\Delay20_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(24),
      Q => Delay20_out1(24),
      R => reset
    );
\Delay20_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(25),
      Q => Delay20_out1(25),
      R => reset
    );
\Delay20_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(26),
      Q => Delay20_out1(26),
      R => reset
    );
\Delay20_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(2),
      Q => Delay20_out1(2),
      R => reset
    );
\Delay20_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(3),
      Q => Delay20_out1(3),
      R => reset
    );
\Delay20_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(4),
      Q => Delay20_out1(4),
      R => reset
    );
\Delay20_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(5),
      Q => Delay20_out1(5),
      R => reset
    );
\Delay20_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(6),
      Q => Delay20_out1(6),
      R => reset
    );
\Delay20_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(7),
      Q => Delay20_out1(7),
      R => reset
    );
\Delay20_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(8),
      Q => Delay20_out1(8),
      R => reset
    );
\Delay20_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in20(9),
      Q => Delay20_out1(9),
      R => reset
    );
\Delay21_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(0),
      Q => Delay21_out1(0),
      R => reset
    );
\Delay21_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(10),
      Q => Delay21_out1(10),
      R => reset
    );
\Delay21_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(11),
      Q => Delay21_out1(11),
      R => reset
    );
\Delay21_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(12),
      Q => Delay21_out1(12),
      R => reset
    );
\Delay21_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(13),
      Q => Delay21_out1(13),
      R => reset
    );
\Delay21_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(14),
      Q => Delay21_out1(14),
      R => reset
    );
\Delay21_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(15),
      Q => Delay21_out1(15),
      R => reset
    );
\Delay21_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(16),
      Q => Delay21_out1(16),
      R => reset
    );
\Delay21_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(17),
      Q => Delay21_out1(17),
      R => reset
    );
\Delay21_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(18),
      Q => Delay21_out1(18),
      R => reset
    );
\Delay21_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(19),
      Q => Delay21_out1(19),
      R => reset
    );
\Delay21_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(1),
      Q => Delay21_out1(1),
      R => reset
    );
\Delay21_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(20),
      Q => Delay21_out1(20),
      R => reset
    );
\Delay21_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(21),
      Q => Delay21_out1(21),
      R => reset
    );
\Delay21_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(22),
      Q => Delay21_out1(22),
      R => reset
    );
\Delay21_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(23),
      Q => Delay21_out1(23),
      R => reset
    );
\Delay21_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(24),
      Q => Delay21_out1(24),
      R => reset
    );
\Delay21_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(25),
      Q => Delay21_out1(25),
      R => reset
    );
\Delay21_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(26),
      Q => Delay21_out1(26),
      R => reset
    );
\Delay21_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(2),
      Q => Delay21_out1(2),
      R => reset
    );
\Delay21_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(3),
      Q => Delay21_out1(3),
      R => reset
    );
\Delay21_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(4),
      Q => Delay21_out1(4),
      R => reset
    );
\Delay21_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(5),
      Q => Delay21_out1(5),
      R => reset
    );
\Delay21_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(6),
      Q => Delay21_out1(6),
      R => reset
    );
\Delay21_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(7),
      Q => Delay21_out1(7),
      R => reset
    );
\Delay21_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(8),
      Q => Delay21_out1(8),
      R => reset
    );
\Delay21_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in21(9),
      Q => Delay21_out1(9),
      R => reset
    );
\Delay22_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(0),
      Q => Delay22_out1(0),
      R => reset
    );
\Delay22_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(10),
      Q => Delay22_out1(10),
      R => reset
    );
\Delay22_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(11),
      Q => Delay22_out1(11),
      R => reset
    );
\Delay22_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(12),
      Q => Delay22_out1(12),
      R => reset
    );
\Delay22_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(13),
      Q => Delay22_out1(13),
      R => reset
    );
\Delay22_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(14),
      Q => Delay22_out1(14),
      R => reset
    );
\Delay22_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(15),
      Q => Delay22_out1(15),
      R => reset
    );
\Delay22_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(16),
      Q => Delay22_out1(16),
      R => reset
    );
\Delay22_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(17),
      Q => Delay22_out1(17),
      R => reset
    );
\Delay22_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(18),
      Q => Delay22_out1(18),
      R => reset
    );
\Delay22_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(19),
      Q => Delay22_out1(19),
      R => reset
    );
\Delay22_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(1),
      Q => Delay22_out1(1),
      R => reset
    );
\Delay22_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(20),
      Q => Delay22_out1(20),
      R => reset
    );
\Delay22_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(21),
      Q => Delay22_out1(21),
      R => reset
    );
\Delay22_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(22),
      Q => Delay22_out1(22),
      R => reset
    );
\Delay22_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(23),
      Q => Delay22_out1(23),
      R => reset
    );
\Delay22_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(24),
      Q => Delay22_out1(24),
      R => reset
    );
\Delay22_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(25),
      Q => Delay22_out1(25),
      R => reset
    );
\Delay22_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(26),
      Q => Delay22_out1(26),
      R => reset
    );
\Delay22_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(2),
      Q => Delay22_out1(2),
      R => reset
    );
\Delay22_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(3),
      Q => Delay22_out1(3),
      R => reset
    );
\Delay22_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(4),
      Q => Delay22_out1(4),
      R => reset
    );
\Delay22_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(5),
      Q => Delay22_out1(5),
      R => reset
    );
\Delay22_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(6),
      Q => Delay22_out1(6),
      R => reset
    );
\Delay22_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(7),
      Q => Delay22_out1(7),
      R => reset
    );
\Delay22_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(8),
      Q => Delay22_out1(8),
      R => reset
    );
\Delay22_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in22(9),
      Q => Delay22_out1(9),
      R => reset
    );
\Delay23_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(0),
      Q => Delay23_out1(0),
      R => reset
    );
\Delay23_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(10),
      Q => Delay23_out1(10),
      R => reset
    );
\Delay23_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(11),
      Q => Delay23_out1(11),
      R => reset
    );
\Delay23_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(12),
      Q => Delay23_out1(12),
      R => reset
    );
\Delay23_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(13),
      Q => Delay23_out1(13),
      R => reset
    );
\Delay23_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(14),
      Q => Delay23_out1(14),
      R => reset
    );
\Delay23_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(15),
      Q => Delay23_out1(15),
      R => reset
    );
\Delay23_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(16),
      Q => Delay23_out1(16),
      R => reset
    );
\Delay23_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(17),
      Q => Delay23_out1(17),
      R => reset
    );
\Delay23_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(18),
      Q => Delay23_out1(18),
      R => reset
    );
\Delay23_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(19),
      Q => Delay23_out1(19),
      R => reset
    );
\Delay23_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(1),
      Q => Delay23_out1(1),
      R => reset
    );
\Delay23_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(20),
      Q => Delay23_out1(20),
      R => reset
    );
\Delay23_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(21),
      Q => Delay23_out1(21),
      R => reset
    );
\Delay23_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(22),
      Q => Delay23_out1(22),
      R => reset
    );
\Delay23_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(23),
      Q => Delay23_out1(23),
      R => reset
    );
\Delay23_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(24),
      Q => Delay23_out1(24),
      R => reset
    );
\Delay23_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(25),
      Q => Delay23_out1(25),
      R => reset
    );
\Delay23_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(26),
      Q => Delay23_out1(26),
      R => reset
    );
\Delay23_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(2),
      Q => Delay23_out1(2),
      R => reset
    );
\Delay23_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(3),
      Q => Delay23_out1(3),
      R => reset
    );
\Delay23_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(4),
      Q => Delay23_out1(4),
      R => reset
    );
\Delay23_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(5),
      Q => Delay23_out1(5),
      R => reset
    );
\Delay23_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(6),
      Q => Delay23_out1(6),
      R => reset
    );
\Delay23_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(7),
      Q => Delay23_out1(7),
      R => reset
    );
\Delay23_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(8),
      Q => Delay23_out1(8),
      R => reset
    );
\Delay23_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in23(9),
      Q => Delay23_out1(9),
      R => reset
    );
\Delay24_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(0),
      Q => Delay24_out1(0),
      R => reset
    );
\Delay24_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(10),
      Q => Delay24_out1(10),
      R => reset
    );
\Delay24_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(11),
      Q => Delay24_out1(11),
      R => reset
    );
\Delay24_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(12),
      Q => Delay24_out1(12),
      R => reset
    );
\Delay24_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(13),
      Q => Delay24_out1(13),
      R => reset
    );
\Delay24_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(14),
      Q => Delay24_out1(14),
      R => reset
    );
\Delay24_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(15),
      Q => Delay24_out1(15),
      R => reset
    );
\Delay24_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(16),
      Q => Delay24_out1(16),
      R => reset
    );
\Delay24_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(17),
      Q => Delay24_out1(17),
      R => reset
    );
\Delay24_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(18),
      Q => Delay24_out1(18),
      R => reset
    );
\Delay24_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(19),
      Q => Delay24_out1(19),
      R => reset
    );
\Delay24_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(1),
      Q => Delay24_out1(1),
      R => reset
    );
\Delay24_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(20),
      Q => Delay24_out1(20),
      R => reset
    );
\Delay24_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(21),
      Q => Delay24_out1(21),
      R => reset
    );
\Delay24_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(22),
      Q => Delay24_out1(22),
      R => reset
    );
\Delay24_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(23),
      Q => Delay24_out1(23),
      R => reset
    );
\Delay24_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(24),
      Q => Delay24_out1(24),
      R => reset
    );
\Delay24_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(25),
      Q => Delay24_out1(25),
      R => reset
    );
\Delay24_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(26),
      Q => Delay24_out1(26),
      R => reset
    );
\Delay24_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(2),
      Q => Delay24_out1(2),
      R => reset
    );
\Delay24_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(3),
      Q => Delay24_out1(3),
      R => reset
    );
\Delay24_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(4),
      Q => Delay24_out1(4),
      R => reset
    );
\Delay24_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(5),
      Q => Delay24_out1(5),
      R => reset
    );
\Delay24_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(6),
      Q => Delay24_out1(6),
      R => reset
    );
\Delay24_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(7),
      Q => Delay24_out1(7),
      R => reset
    );
\Delay24_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(8),
      Q => Delay24_out1(8),
      R => reset
    );
\Delay24_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in24(9),
      Q => Delay24_out1(9),
      R => reset
    );
\Delay25_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(0),
      Q => Delay25_out1(0),
      R => reset
    );
\Delay25_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(10),
      Q => Delay25_out1(10),
      R => reset
    );
\Delay25_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(11),
      Q => Delay25_out1(11),
      R => reset
    );
\Delay25_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(12),
      Q => Delay25_out1(12),
      R => reset
    );
\Delay25_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(13),
      Q => Delay25_out1(13),
      R => reset
    );
\Delay25_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(14),
      Q => Delay25_out1(14),
      R => reset
    );
\Delay25_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(15),
      Q => Delay25_out1(15),
      R => reset
    );
\Delay25_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(16),
      Q => Delay25_out1(16),
      R => reset
    );
\Delay25_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(17),
      Q => Delay25_out1(17),
      R => reset
    );
\Delay25_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(18),
      Q => Delay25_out1(18),
      R => reset
    );
\Delay25_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(19),
      Q => Delay25_out1(19),
      R => reset
    );
\Delay25_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(1),
      Q => Delay25_out1(1),
      R => reset
    );
\Delay25_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(20),
      Q => Delay25_out1(20),
      R => reset
    );
\Delay25_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(21),
      Q => Delay25_out1(21),
      R => reset
    );
\Delay25_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(22),
      Q => Delay25_out1(22),
      R => reset
    );
\Delay25_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(23),
      Q => Delay25_out1(23),
      R => reset
    );
\Delay25_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(24),
      Q => Delay25_out1(24),
      R => reset
    );
\Delay25_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(25),
      Q => Delay25_out1(25),
      R => reset
    );
\Delay25_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(26),
      Q => Delay25_out1(26),
      R => reset
    );
\Delay25_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(2),
      Q => Delay25_out1(2),
      R => reset
    );
\Delay25_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(3),
      Q => Delay25_out1(3),
      R => reset
    );
\Delay25_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(4),
      Q => Delay25_out1(4),
      R => reset
    );
\Delay25_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(5),
      Q => Delay25_out1(5),
      R => reset
    );
\Delay25_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(6),
      Q => Delay25_out1(6),
      R => reset
    );
\Delay25_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(7),
      Q => Delay25_out1(7),
      R => reset
    );
\Delay25_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(8),
      Q => Delay25_out1(8),
      R => reset
    );
\Delay25_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in25(9),
      Q => Delay25_out1(9),
      R => reset
    );
\Delay26_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(0),
      Q => Delay26_out1(0),
      R => reset
    );
\Delay26_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(10),
      Q => Delay26_out1(10),
      R => reset
    );
\Delay26_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(11),
      Q => Delay26_out1(11),
      R => reset
    );
\Delay26_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(12),
      Q => Delay26_out1(12),
      R => reset
    );
\Delay26_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(13),
      Q => Delay26_out1(13),
      R => reset
    );
\Delay26_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(14),
      Q => Delay26_out1(14),
      R => reset
    );
\Delay26_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(15),
      Q => Delay26_out1(15),
      R => reset
    );
\Delay26_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(16),
      Q => Delay26_out1(16),
      R => reset
    );
\Delay26_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(17),
      Q => Delay26_out1(17),
      R => reset
    );
\Delay26_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(18),
      Q => Delay26_out1(18),
      R => reset
    );
\Delay26_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(19),
      Q => Delay26_out1(19),
      R => reset
    );
\Delay26_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(1),
      Q => Delay26_out1(1),
      R => reset
    );
\Delay26_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(20),
      Q => Delay26_out1(20),
      R => reset
    );
\Delay26_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(21),
      Q => Delay26_out1(21),
      R => reset
    );
\Delay26_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(22),
      Q => Delay26_out1(22),
      R => reset
    );
\Delay26_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(23),
      Q => Delay26_out1(23),
      R => reset
    );
\Delay26_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(24),
      Q => Delay26_out1(24),
      R => reset
    );
\Delay26_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(25),
      Q => Delay26_out1(25),
      R => reset
    );
\Delay26_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(26),
      Q => Delay26_out1(26),
      R => reset
    );
\Delay26_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(2),
      Q => Delay26_out1(2),
      R => reset
    );
\Delay26_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(3),
      Q => Delay26_out1(3),
      R => reset
    );
\Delay26_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(4),
      Q => Delay26_out1(4),
      R => reset
    );
\Delay26_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(5),
      Q => Delay26_out1(5),
      R => reset
    );
\Delay26_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(6),
      Q => Delay26_out1(6),
      R => reset
    );
\Delay26_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(7),
      Q => Delay26_out1(7),
      R => reset
    );
\Delay26_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(8),
      Q => Delay26_out1(8),
      R => reset
    );
\Delay26_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in26(9),
      Q => Delay26_out1(9),
      R => reset
    );
\Delay27_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(0),
      Q => Delay27_out1(0),
      R => reset
    );
\Delay27_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(10),
      Q => Delay27_out1(10),
      R => reset
    );
\Delay27_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(11),
      Q => Delay27_out1(11),
      R => reset
    );
\Delay27_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(12),
      Q => Delay27_out1(12),
      R => reset
    );
\Delay27_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(13),
      Q => Delay27_out1(13),
      R => reset
    );
\Delay27_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(14),
      Q => Delay27_out1(14),
      R => reset
    );
\Delay27_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(15),
      Q => Delay27_out1(15),
      R => reset
    );
\Delay27_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(16),
      Q => Delay27_out1(16),
      R => reset
    );
\Delay27_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(17),
      Q => Delay27_out1(17),
      R => reset
    );
\Delay27_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(18),
      Q => Delay27_out1(18),
      R => reset
    );
\Delay27_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(19),
      Q => Delay27_out1(19),
      R => reset
    );
\Delay27_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(1),
      Q => Delay27_out1(1),
      R => reset
    );
\Delay27_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(20),
      Q => Delay27_out1(20),
      R => reset
    );
\Delay27_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(21),
      Q => Delay27_out1(21),
      R => reset
    );
\Delay27_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(22),
      Q => Delay27_out1(22),
      R => reset
    );
\Delay27_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(23),
      Q => Delay27_out1(23),
      R => reset
    );
\Delay27_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(24),
      Q => Delay27_out1(24),
      R => reset
    );
\Delay27_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(25),
      Q => Delay27_out1(25),
      R => reset
    );
\Delay27_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(26),
      Q => Delay27_out1(26),
      R => reset
    );
\Delay27_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(2),
      Q => Delay27_out1(2),
      R => reset
    );
\Delay27_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(3),
      Q => Delay27_out1(3),
      R => reset
    );
\Delay27_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(4),
      Q => Delay27_out1(4),
      R => reset
    );
\Delay27_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(5),
      Q => Delay27_out1(5),
      R => reset
    );
\Delay27_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(6),
      Q => Delay27_out1(6),
      R => reset
    );
\Delay27_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(7),
      Q => Delay27_out1(7),
      R => reset
    );
\Delay27_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(8),
      Q => Delay27_out1(8),
      R => reset
    );
\Delay27_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in27(9),
      Q => Delay27_out1(9),
      R => reset
    );
\Delay28_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(0),
      Q => Delay28_out1(0),
      R => reset
    );
\Delay28_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(10),
      Q => Delay28_out1(10),
      R => reset
    );
\Delay28_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(11),
      Q => Delay28_out1(11),
      R => reset
    );
\Delay28_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(12),
      Q => Delay28_out1(12),
      R => reset
    );
\Delay28_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(13),
      Q => Delay28_out1(13),
      R => reset
    );
\Delay28_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(14),
      Q => Delay28_out1(14),
      R => reset
    );
\Delay28_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(15),
      Q => Delay28_out1(15),
      R => reset
    );
\Delay28_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(16),
      Q => Delay28_out1(16),
      R => reset
    );
\Delay28_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(17),
      Q => Delay28_out1(17),
      R => reset
    );
\Delay28_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(18),
      Q => Delay28_out1(18),
      R => reset
    );
\Delay28_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(19),
      Q => Delay28_out1(19),
      R => reset
    );
\Delay28_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(1),
      Q => Delay28_out1(1),
      R => reset
    );
\Delay28_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(20),
      Q => Delay28_out1(20),
      R => reset
    );
\Delay28_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(21),
      Q => Delay28_out1(21),
      R => reset
    );
\Delay28_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(22),
      Q => Delay28_out1(22),
      R => reset
    );
\Delay28_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(23),
      Q => Delay28_out1(23),
      R => reset
    );
\Delay28_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(24),
      Q => Delay28_out1(24),
      R => reset
    );
\Delay28_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(25),
      Q => Delay28_out1(25),
      R => reset
    );
\Delay28_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(26),
      Q => Delay28_out1(26),
      R => reset
    );
\Delay28_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(2),
      Q => Delay28_out1(2),
      R => reset
    );
\Delay28_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(3),
      Q => Delay28_out1(3),
      R => reset
    );
\Delay28_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(4),
      Q => Delay28_out1(4),
      R => reset
    );
\Delay28_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(5),
      Q => Delay28_out1(5),
      R => reset
    );
\Delay28_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(6),
      Q => Delay28_out1(6),
      R => reset
    );
\Delay28_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(7),
      Q => Delay28_out1(7),
      R => reset
    );
\Delay28_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(8),
      Q => Delay28_out1(8),
      R => reset
    );
\Delay28_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in28(9),
      Q => Delay28_out1(9),
      R => reset
    );
\Delay29_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(0),
      Q => Delay29_out1(0),
      R => reset
    );
\Delay29_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(10),
      Q => Delay29_out1(10),
      R => reset
    );
\Delay29_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(11),
      Q => Delay29_out1(11),
      R => reset
    );
\Delay29_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(12),
      Q => Delay29_out1(12),
      R => reset
    );
\Delay29_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(13),
      Q => Delay29_out1(13),
      R => reset
    );
\Delay29_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(14),
      Q => Delay29_out1(14),
      R => reset
    );
\Delay29_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(15),
      Q => Delay29_out1(15),
      R => reset
    );
\Delay29_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(16),
      Q => Delay29_out1(16),
      R => reset
    );
\Delay29_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(17),
      Q => Delay29_out1(17),
      R => reset
    );
\Delay29_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(18),
      Q => Delay29_out1(18),
      R => reset
    );
\Delay29_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(19),
      Q => Delay29_out1(19),
      R => reset
    );
\Delay29_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(1),
      Q => Delay29_out1(1),
      R => reset
    );
\Delay29_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(20),
      Q => Delay29_out1(20),
      R => reset
    );
\Delay29_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(21),
      Q => Delay29_out1(21),
      R => reset
    );
\Delay29_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(22),
      Q => Delay29_out1(22),
      R => reset
    );
\Delay29_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(23),
      Q => Delay29_out1(23),
      R => reset
    );
\Delay29_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(24),
      Q => Delay29_out1(24),
      R => reset
    );
\Delay29_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(25),
      Q => Delay29_out1(25),
      R => reset
    );
\Delay29_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(26),
      Q => Delay29_out1(26),
      R => reset
    );
\Delay29_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(2),
      Q => Delay29_out1(2),
      R => reset
    );
\Delay29_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(3),
      Q => Delay29_out1(3),
      R => reset
    );
\Delay29_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(4),
      Q => Delay29_out1(4),
      R => reset
    );
\Delay29_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(5),
      Q => Delay29_out1(5),
      R => reset
    );
\Delay29_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(6),
      Q => Delay29_out1(6),
      R => reset
    );
\Delay29_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(7),
      Q => Delay29_out1(7),
      R => reset
    );
\Delay29_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(8),
      Q => Delay29_out1(8),
      R => reset
    );
\Delay29_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in29(9),
      Q => Delay29_out1(9),
      R => reset
    );
\Delay2_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(0),
      Q => Delay2_out1(0),
      R => reset
    );
\Delay2_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(10),
      Q => Delay2_out1(10),
      R => reset
    );
\Delay2_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(11),
      Q => Delay2_out1(11),
      R => reset
    );
\Delay2_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(12),
      Q => Delay2_out1(12),
      R => reset
    );
\Delay2_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(13),
      Q => Delay2_out1(13),
      R => reset
    );
\Delay2_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(14),
      Q => Delay2_out1(14),
      R => reset
    );
\Delay2_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(15),
      Q => Delay2_out1(15),
      R => reset
    );
\Delay2_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(16),
      Q => Delay2_out1(16),
      R => reset
    );
\Delay2_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(17),
      Q => Delay2_out1(17),
      R => reset
    );
\Delay2_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(18),
      Q => Delay2_out1(18),
      R => reset
    );
\Delay2_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(19),
      Q => Delay2_out1(19),
      R => reset
    );
\Delay2_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(1),
      Q => Delay2_out1(1),
      R => reset
    );
\Delay2_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(20),
      Q => Delay2_out1(20),
      R => reset
    );
\Delay2_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(21),
      Q => Delay2_out1(21),
      R => reset
    );
\Delay2_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(22),
      Q => Delay2_out1(22),
      R => reset
    );
\Delay2_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(23),
      Q => Delay2_out1(23),
      R => reset
    );
\Delay2_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(24),
      Q => Delay2_out1(24),
      R => reset
    );
\Delay2_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(25),
      Q => Delay2_out1(25),
      R => reset
    );
\Delay2_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(26),
      Q => Delay2_out1(26),
      R => reset
    );
\Delay2_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(2),
      Q => Delay2_out1(2),
      R => reset
    );
\Delay2_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(3),
      Q => Delay2_out1(3),
      R => reset
    );
\Delay2_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(4),
      Q => Delay2_out1(4),
      R => reset
    );
\Delay2_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(5),
      Q => Delay2_out1(5),
      R => reset
    );
\Delay2_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(6),
      Q => Delay2_out1(6),
      R => reset
    );
\Delay2_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(7),
      Q => Delay2_out1(7),
      R => reset
    );
\Delay2_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(8),
      Q => Delay2_out1(8),
      R => reset
    );
\Delay2_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in2(9),
      Q => Delay2_out1(9),
      R => reset
    );
\Delay30_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(0),
      Q => Delay30_out1(0),
      R => reset
    );
\Delay30_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(10),
      Q => Delay30_out1(10),
      R => reset
    );
\Delay30_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(11),
      Q => Delay30_out1(11),
      R => reset
    );
\Delay30_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(12),
      Q => Delay30_out1(12),
      R => reset
    );
\Delay30_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(13),
      Q => Delay30_out1(13),
      R => reset
    );
\Delay30_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(14),
      Q => Delay30_out1(14),
      R => reset
    );
\Delay30_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(15),
      Q => Delay30_out1(15),
      R => reset
    );
\Delay30_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(16),
      Q => Delay30_out1(16),
      R => reset
    );
\Delay30_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(17),
      Q => Delay30_out1(17),
      R => reset
    );
\Delay30_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(18),
      Q => Delay30_out1(18),
      R => reset
    );
\Delay30_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(19),
      Q => Delay30_out1(19),
      R => reset
    );
\Delay30_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(1),
      Q => Delay30_out1(1),
      R => reset
    );
\Delay30_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(20),
      Q => Delay30_out1(20),
      R => reset
    );
\Delay30_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(21),
      Q => Delay30_out1(21),
      R => reset
    );
\Delay30_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(22),
      Q => Delay30_out1(22),
      R => reset
    );
\Delay30_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(23),
      Q => Delay30_out1(23),
      R => reset
    );
\Delay30_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(24),
      Q => Delay30_out1(24),
      R => reset
    );
\Delay30_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(25),
      Q => Delay30_out1(25),
      R => reset
    );
\Delay30_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(26),
      Q => Delay30_out1(26),
      R => reset
    );
\Delay30_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(2),
      Q => Delay30_out1(2),
      R => reset
    );
\Delay30_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(3),
      Q => Delay30_out1(3),
      R => reset
    );
\Delay30_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(4),
      Q => Delay30_out1(4),
      R => reset
    );
\Delay30_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(5),
      Q => Delay30_out1(5),
      R => reset
    );
\Delay30_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(6),
      Q => Delay30_out1(6),
      R => reset
    );
\Delay30_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(7),
      Q => Delay30_out1(7),
      R => reset
    );
\Delay30_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(8),
      Q => Delay30_out1(8),
      R => reset
    );
\Delay30_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in30(9),
      Q => Delay30_out1(9),
      R => reset
    );
\Delay31_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(0),
      Q => Delay31_out1(0),
      R => reset
    );
\Delay31_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(10),
      Q => Delay31_out1(10),
      R => reset
    );
\Delay31_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(11),
      Q => Delay31_out1(11),
      R => reset
    );
\Delay31_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(12),
      Q => Delay31_out1(12),
      R => reset
    );
\Delay31_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(13),
      Q => Delay31_out1(13),
      R => reset
    );
\Delay31_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(14),
      Q => Delay31_out1(14),
      R => reset
    );
\Delay31_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(15),
      Q => Delay31_out1(15),
      R => reset
    );
\Delay31_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(16),
      Q => Delay31_out1(16),
      R => reset
    );
\Delay31_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(17),
      Q => Delay31_out1(17),
      R => reset
    );
\Delay31_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(18),
      Q => Delay31_out1(18),
      R => reset
    );
\Delay31_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(19),
      Q => Delay31_out1(19),
      R => reset
    );
\Delay31_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(1),
      Q => Delay31_out1(1),
      R => reset
    );
\Delay31_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(20),
      Q => Delay31_out1(20),
      R => reset
    );
\Delay31_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(21),
      Q => Delay31_out1(21),
      R => reset
    );
\Delay31_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(22),
      Q => Delay31_out1(22),
      R => reset
    );
\Delay31_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(23),
      Q => Delay31_out1(23),
      R => reset
    );
\Delay31_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(24),
      Q => Delay31_out1(24),
      R => reset
    );
\Delay31_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(25),
      Q => Delay31_out1(25),
      R => reset
    );
\Delay31_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(26),
      Q => Delay31_out1(26),
      R => reset
    );
\Delay31_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(2),
      Q => Delay31_out1(2),
      R => reset
    );
\Delay31_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(3),
      Q => Delay31_out1(3),
      R => reset
    );
\Delay31_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(4),
      Q => Delay31_out1(4),
      R => reset
    );
\Delay31_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(5),
      Q => Delay31_out1(5),
      R => reset
    );
\Delay31_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(6),
      Q => Delay31_out1(6),
      R => reset
    );
\Delay31_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(7),
      Q => Delay31_out1(7),
      R => reset
    );
\Delay31_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(8),
      Q => Delay31_out1(8),
      R => reset
    );
\Delay31_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in31(9),
      Q => Delay31_out1(9),
      R => reset
    );
\Delay3_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(0),
      Q => Delay3_out1(0),
      R => reset
    );
\Delay3_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(10),
      Q => Delay3_out1(10),
      R => reset
    );
\Delay3_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(11),
      Q => Delay3_out1(11),
      R => reset
    );
\Delay3_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(12),
      Q => Delay3_out1(12),
      R => reset
    );
\Delay3_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(13),
      Q => Delay3_out1(13),
      R => reset
    );
\Delay3_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(14),
      Q => Delay3_out1(14),
      R => reset
    );
\Delay3_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(15),
      Q => Delay3_out1(15),
      R => reset
    );
\Delay3_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(16),
      Q => Delay3_out1(16),
      R => reset
    );
\Delay3_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(17),
      Q => Delay3_out1(17),
      R => reset
    );
\Delay3_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(18),
      Q => Delay3_out1(18),
      R => reset
    );
\Delay3_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(19),
      Q => Delay3_out1(19),
      R => reset
    );
\Delay3_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(1),
      Q => Delay3_out1(1),
      R => reset
    );
\Delay3_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(20),
      Q => Delay3_out1(20),
      R => reset
    );
\Delay3_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(21),
      Q => Delay3_out1(21),
      R => reset
    );
\Delay3_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(22),
      Q => Delay3_out1(22),
      R => reset
    );
\Delay3_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(23),
      Q => Delay3_out1(23),
      R => reset
    );
\Delay3_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(24),
      Q => Delay3_out1(24),
      R => reset
    );
\Delay3_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(25),
      Q => Delay3_out1(25),
      R => reset
    );
\Delay3_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(26),
      Q => Delay3_out1(26),
      R => reset
    );
\Delay3_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(2),
      Q => Delay3_out1(2),
      R => reset
    );
\Delay3_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(3),
      Q => Delay3_out1(3),
      R => reset
    );
\Delay3_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(4),
      Q => Delay3_out1(4),
      R => reset
    );
\Delay3_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(5),
      Q => Delay3_out1(5),
      R => reset
    );
\Delay3_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(6),
      Q => Delay3_out1(6),
      R => reset
    );
\Delay3_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(7),
      Q => Delay3_out1(7),
      R => reset
    );
\Delay3_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(8),
      Q => Delay3_out1(8),
      R => reset
    );
\Delay3_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in3(9),
      Q => Delay3_out1(9),
      R => reset
    );
\Delay4_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(0),
      Q => Delay4_out1(0),
      R => reset
    );
\Delay4_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(10),
      Q => Delay4_out1(10),
      R => reset
    );
\Delay4_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(11),
      Q => Delay4_out1(11),
      R => reset
    );
\Delay4_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(12),
      Q => Delay4_out1(12),
      R => reset
    );
\Delay4_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(13),
      Q => Delay4_out1(13),
      R => reset
    );
\Delay4_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(14),
      Q => Delay4_out1(14),
      R => reset
    );
\Delay4_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(15),
      Q => Delay4_out1(15),
      R => reset
    );
\Delay4_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(16),
      Q => Delay4_out1(16),
      R => reset
    );
\Delay4_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(17),
      Q => Delay4_out1(17),
      R => reset
    );
\Delay4_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(18),
      Q => Delay4_out1(18),
      R => reset
    );
\Delay4_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(19),
      Q => Delay4_out1(19),
      R => reset
    );
\Delay4_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(1),
      Q => Delay4_out1(1),
      R => reset
    );
\Delay4_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(20),
      Q => Delay4_out1(20),
      R => reset
    );
\Delay4_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(21),
      Q => Delay4_out1(21),
      R => reset
    );
\Delay4_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(22),
      Q => Delay4_out1(22),
      R => reset
    );
\Delay4_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(23),
      Q => Delay4_out1(23),
      R => reset
    );
\Delay4_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(24),
      Q => Delay4_out1(24),
      R => reset
    );
\Delay4_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(25),
      Q => Delay4_out1(25),
      R => reset
    );
\Delay4_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(26),
      Q => Delay4_out1(26),
      R => reset
    );
\Delay4_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(2),
      Q => Delay4_out1(2),
      R => reset
    );
\Delay4_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(3),
      Q => Delay4_out1(3),
      R => reset
    );
\Delay4_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(4),
      Q => Delay4_out1(4),
      R => reset
    );
\Delay4_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(5),
      Q => Delay4_out1(5),
      R => reset
    );
\Delay4_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(6),
      Q => Delay4_out1(6),
      R => reset
    );
\Delay4_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(7),
      Q => Delay4_out1(7),
      R => reset
    );
\Delay4_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(8),
      Q => Delay4_out1(8),
      R => reset
    );
\Delay4_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in4(9),
      Q => Delay4_out1(9),
      R => reset
    );
\Delay5_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(0),
      Q => Delay5_out1(0),
      R => reset
    );
\Delay5_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(10),
      Q => Delay5_out1(10),
      R => reset
    );
\Delay5_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(11),
      Q => Delay5_out1(11),
      R => reset
    );
\Delay5_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(12),
      Q => Delay5_out1(12),
      R => reset
    );
\Delay5_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(13),
      Q => Delay5_out1(13),
      R => reset
    );
\Delay5_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(14),
      Q => Delay5_out1(14),
      R => reset
    );
\Delay5_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(15),
      Q => Delay5_out1(15),
      R => reset
    );
\Delay5_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(16),
      Q => Delay5_out1(16),
      R => reset
    );
\Delay5_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(17),
      Q => Delay5_out1(17),
      R => reset
    );
\Delay5_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(18),
      Q => Delay5_out1(18),
      R => reset
    );
\Delay5_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(19),
      Q => Delay5_out1(19),
      R => reset
    );
\Delay5_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(1),
      Q => Delay5_out1(1),
      R => reset
    );
\Delay5_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(20),
      Q => Delay5_out1(20),
      R => reset
    );
\Delay5_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(21),
      Q => Delay5_out1(21),
      R => reset
    );
\Delay5_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(22),
      Q => Delay5_out1(22),
      R => reset
    );
\Delay5_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(23),
      Q => Delay5_out1(23),
      R => reset
    );
\Delay5_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(24),
      Q => Delay5_out1(24),
      R => reset
    );
\Delay5_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(25),
      Q => Delay5_out1(25),
      R => reset
    );
\Delay5_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(26),
      Q => Delay5_out1(26),
      R => reset
    );
\Delay5_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(2),
      Q => Delay5_out1(2),
      R => reset
    );
\Delay5_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(3),
      Q => Delay5_out1(3),
      R => reset
    );
\Delay5_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(4),
      Q => Delay5_out1(4),
      R => reset
    );
\Delay5_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(5),
      Q => Delay5_out1(5),
      R => reset
    );
\Delay5_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(6),
      Q => Delay5_out1(6),
      R => reset
    );
\Delay5_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(7),
      Q => Delay5_out1(7),
      R => reset
    );
\Delay5_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(8),
      Q => Delay5_out1(8),
      R => reset
    );
\Delay5_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in5(9),
      Q => Delay5_out1(9),
      R => reset
    );
\Delay6_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(0),
      Q => Delay6_out1(0),
      R => reset
    );
\Delay6_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(10),
      Q => Delay6_out1(10),
      R => reset
    );
\Delay6_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(11),
      Q => Delay6_out1(11),
      R => reset
    );
\Delay6_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(12),
      Q => Delay6_out1(12),
      R => reset
    );
\Delay6_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(13),
      Q => Delay6_out1(13),
      R => reset
    );
\Delay6_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(14),
      Q => Delay6_out1(14),
      R => reset
    );
\Delay6_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(15),
      Q => Delay6_out1(15),
      R => reset
    );
\Delay6_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(16),
      Q => Delay6_out1(16),
      R => reset
    );
\Delay6_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(17),
      Q => Delay6_out1(17),
      R => reset
    );
\Delay6_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(18),
      Q => Delay6_out1(18),
      R => reset
    );
\Delay6_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(19),
      Q => Delay6_out1(19),
      R => reset
    );
\Delay6_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(1),
      Q => Delay6_out1(1),
      R => reset
    );
\Delay6_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(20),
      Q => Delay6_out1(20),
      R => reset
    );
\Delay6_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(21),
      Q => Delay6_out1(21),
      R => reset
    );
\Delay6_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(22),
      Q => Delay6_out1(22),
      R => reset
    );
\Delay6_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(23),
      Q => Delay6_out1(23),
      R => reset
    );
\Delay6_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(24),
      Q => Delay6_out1(24),
      R => reset
    );
\Delay6_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(25),
      Q => Delay6_out1(25),
      R => reset
    );
\Delay6_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(26),
      Q => Delay6_out1(26),
      R => reset
    );
\Delay6_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(2),
      Q => Delay6_out1(2),
      R => reset
    );
\Delay6_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(3),
      Q => Delay6_out1(3),
      R => reset
    );
\Delay6_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(4),
      Q => Delay6_out1(4),
      R => reset
    );
\Delay6_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(5),
      Q => Delay6_out1(5),
      R => reset
    );
\Delay6_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(6),
      Q => Delay6_out1(6),
      R => reset
    );
\Delay6_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(7),
      Q => Delay6_out1(7),
      R => reset
    );
\Delay6_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(8),
      Q => Delay6_out1(8),
      R => reset
    );
\Delay6_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in6(9),
      Q => Delay6_out1(9),
      R => reset
    );
\Delay7_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(0),
      Q => Delay7_out1(0),
      R => reset
    );
\Delay7_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(10),
      Q => Delay7_out1(10),
      R => reset
    );
\Delay7_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(11),
      Q => Delay7_out1(11),
      R => reset
    );
\Delay7_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(12),
      Q => Delay7_out1(12),
      R => reset
    );
\Delay7_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(13),
      Q => Delay7_out1(13),
      R => reset
    );
\Delay7_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(14),
      Q => Delay7_out1(14),
      R => reset
    );
\Delay7_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(15),
      Q => Delay7_out1(15),
      R => reset
    );
\Delay7_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(16),
      Q => Delay7_out1(16),
      R => reset
    );
\Delay7_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(17),
      Q => Delay7_out1(17),
      R => reset
    );
\Delay7_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(18),
      Q => Delay7_out1(18),
      R => reset
    );
\Delay7_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(19),
      Q => Delay7_out1(19),
      R => reset
    );
\Delay7_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(1),
      Q => Delay7_out1(1),
      R => reset
    );
\Delay7_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(20),
      Q => Delay7_out1(20),
      R => reset
    );
\Delay7_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(21),
      Q => Delay7_out1(21),
      R => reset
    );
\Delay7_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(22),
      Q => Delay7_out1(22),
      R => reset
    );
\Delay7_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(23),
      Q => Delay7_out1(23),
      R => reset
    );
\Delay7_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(24),
      Q => Delay7_out1(24),
      R => reset
    );
\Delay7_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(25),
      Q => Delay7_out1(25),
      R => reset
    );
\Delay7_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(26),
      Q => Delay7_out1(26),
      R => reset
    );
\Delay7_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(2),
      Q => Delay7_out1(2),
      R => reset
    );
\Delay7_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(3),
      Q => Delay7_out1(3),
      R => reset
    );
\Delay7_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(4),
      Q => Delay7_out1(4),
      R => reset
    );
\Delay7_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(5),
      Q => Delay7_out1(5),
      R => reset
    );
\Delay7_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(6),
      Q => Delay7_out1(6),
      R => reset
    );
\Delay7_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(7),
      Q => Delay7_out1(7),
      R => reset
    );
\Delay7_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(8),
      Q => Delay7_out1(8),
      R => reset
    );
\Delay7_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in7(9),
      Q => Delay7_out1(9),
      R => reset
    );
\Delay8_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(0),
      Q => Delay8_out1(0),
      R => reset
    );
\Delay8_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(10),
      Q => Delay8_out1(10),
      R => reset
    );
\Delay8_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(11),
      Q => Delay8_out1(11),
      R => reset
    );
\Delay8_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(12),
      Q => Delay8_out1(12),
      R => reset
    );
\Delay8_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(13),
      Q => Delay8_out1(13),
      R => reset
    );
\Delay8_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(14),
      Q => Delay8_out1(14),
      R => reset
    );
\Delay8_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(15),
      Q => Delay8_out1(15),
      R => reset
    );
\Delay8_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(16),
      Q => Delay8_out1(16),
      R => reset
    );
\Delay8_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(17),
      Q => Delay8_out1(17),
      R => reset
    );
\Delay8_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(18),
      Q => Delay8_out1(18),
      R => reset
    );
\Delay8_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(19),
      Q => Delay8_out1(19),
      R => reset
    );
\Delay8_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(1),
      Q => Delay8_out1(1),
      R => reset
    );
\Delay8_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(20),
      Q => Delay8_out1(20),
      R => reset
    );
\Delay8_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(21),
      Q => Delay8_out1(21),
      R => reset
    );
\Delay8_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(22),
      Q => Delay8_out1(22),
      R => reset
    );
\Delay8_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(23),
      Q => Delay8_out1(23),
      R => reset
    );
\Delay8_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(24),
      Q => Delay8_out1(24),
      R => reset
    );
\Delay8_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(25),
      Q => Delay8_out1(25),
      R => reset
    );
\Delay8_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(26),
      Q => Delay8_out1(26),
      R => reset
    );
\Delay8_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(2),
      Q => Delay8_out1(2),
      R => reset
    );
\Delay8_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(3),
      Q => Delay8_out1(3),
      R => reset
    );
\Delay8_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(4),
      Q => Delay8_out1(4),
      R => reset
    );
\Delay8_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(5),
      Q => Delay8_out1(5),
      R => reset
    );
\Delay8_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(6),
      Q => Delay8_out1(6),
      R => reset
    );
\Delay8_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(7),
      Q => Delay8_out1(7),
      R => reset
    );
\Delay8_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(8),
      Q => Delay8_out1(8),
      R => reset
    );
\Delay8_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in8(9),
      Q => Delay8_out1(9),
      R => reset
    );
\Delay9_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(0),
      Q => Delay9_out1(0),
      R => reset
    );
\Delay9_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(10),
      Q => Delay9_out1(10),
      R => reset
    );
\Delay9_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(11),
      Q => Delay9_out1(11),
      R => reset
    );
\Delay9_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(12),
      Q => Delay9_out1(12),
      R => reset
    );
\Delay9_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(13),
      Q => Delay9_out1(13),
      R => reset
    );
\Delay9_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(14),
      Q => Delay9_out1(14),
      R => reset
    );
\Delay9_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(15),
      Q => Delay9_out1(15),
      R => reset
    );
\Delay9_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(16),
      Q => Delay9_out1(16),
      R => reset
    );
\Delay9_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(17),
      Q => Delay9_out1(17),
      R => reset
    );
\Delay9_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(18),
      Q => Delay9_out1(18),
      R => reset
    );
\Delay9_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(19),
      Q => Delay9_out1(19),
      R => reset
    );
\Delay9_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(1),
      Q => Delay9_out1(1),
      R => reset
    );
\Delay9_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(20),
      Q => Delay9_out1(20),
      R => reset
    );
\Delay9_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(21),
      Q => Delay9_out1(21),
      R => reset
    );
\Delay9_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(22),
      Q => Delay9_out1(22),
      R => reset
    );
\Delay9_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(23),
      Q => Delay9_out1(23),
      R => reset
    );
\Delay9_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(24),
      Q => Delay9_out1(24),
      R => reset
    );
\Delay9_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(25),
      Q => Delay9_out1(25),
      R => reset
    );
\Delay9_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(26),
      Q => Delay9_out1(26),
      R => reset
    );
\Delay9_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(2),
      Q => Delay9_out1(2),
      R => reset
    );
\Delay9_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(3),
      Q => Delay9_out1(3),
      R => reset
    );
\Delay9_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(4),
      Q => Delay9_out1(4),
      R => reset
    );
\Delay9_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(5),
      Q => Delay9_out1(5),
      R => reset
    );
\Delay9_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(6),
      Q => Delay9_out1(6),
      R => reset
    );
\Delay9_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(7),
      Q => Delay9_out1(7),
      R => reset
    );
\Delay9_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(8),
      Q => Delay9_out1(8),
      R => reset
    );
\Delay9_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in9(9),
      Q => Delay9_out1(9),
      R => reset
    );
\Delay_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(0),
      Q => Delay_out1(0),
      R => reset
    );
\Delay_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(10),
      Q => Delay_out1(10),
      R => reset
    );
\Delay_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(11),
      Q => Delay_out1(11),
      R => reset
    );
\Delay_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(12),
      Q => Delay_out1(12),
      R => reset
    );
\Delay_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(13),
      Q => Delay_out1(13),
      R => reset
    );
\Delay_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(14),
      Q => Delay_out1(14),
      R => reset
    );
\Delay_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(15),
      Q => Delay_out1(15),
      R => reset
    );
\Delay_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(16),
      Q => Delay_out1(16),
      R => reset
    );
\Delay_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(17),
      Q => Delay_out1(17),
      R => reset
    );
\Delay_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(18),
      Q => Delay_out1(18),
      R => reset
    );
\Delay_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(19),
      Q => Delay_out1(19),
      R => reset
    );
\Delay_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(1),
      Q => Delay_out1(1),
      R => reset
    );
\Delay_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(20),
      Q => Delay_out1(20),
      R => reset
    );
\Delay_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(21),
      Q => Delay_out1(21),
      R => reset
    );
\Delay_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(22),
      Q => Delay_out1(22),
      R => reset
    );
\Delay_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(23),
      Q => Delay_out1(23),
      R => reset
    );
\Delay_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(24),
      Q => Delay_out1(24),
      R => reset
    );
\Delay_out1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(25),
      Q => Delay_out1(25),
      R => reset
    );
\Delay_out1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(26),
      Q => Delay_out1(26),
      R => reset
    );
\Delay_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(2),
      Q => Delay_out1(2),
      R => reset
    );
\Delay_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(3),
      Q => Delay_out1(3),
      R => reset
    );
\Delay_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(4),
      Q => Delay_out1(4),
      R => reset
    );
\Delay_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(5),
      Q => Delay_out1(5),
      R => reset
    );
\Delay_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(6),
      Q => Delay_out1(6),
      R => reset
    );
\Delay_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(7),
      Q => Delay_out1(7),
      R => reset
    );
\Delay_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(8),
      Q => Delay_out1(8),
      R => reset
    );
\Delay_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => adc_trigger,
      D => in0(9),
      Q => Delay_out1(9),
      R => reset
    );
p_1_out: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => A(26),
      A(28) => A(26),
      A(27) => A(26),
      A(26 downto 1) => A(26 downto 1),
      A(0) => p_1_out_i_28_n_0,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_p_1_out_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_p_1_out_BCOUT_UNCONNECTED(17 downto 0),
      C(47) => A(26),
      C(46) => A(26),
      C(45) => A(26),
      C(44) => A(26),
      C(43) => A(26),
      C(42) => A(26),
      C(41) => A(26),
      C(40) => A(26),
      C(39) => A(26),
      C(38) => A(26),
      C(37) => A(26),
      C(36) => A(26),
      C(35) => A(26),
      C(34) => A(26),
      C(33) => A(26),
      C(32) => A(26),
      C(31) => A(26),
      C(30) => A(26),
      C(29) => A(26),
      C(28) => A(26),
      C(27) => A(26),
      C(26) => A(26),
      C(25 downto 0) => A(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_p_1_out_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_p_1_out_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_p_1_out_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => OPMODE(0),
      OPMODE(4) => OPMODE(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => NLW_p_1_out_OVERFLOW_UNCONNECTED,
      P(47 downto 45) => NLW_p_1_out_P_UNCONNECTED(47 downto 45),
      P(44) => p_1_out_n_61,
      P(43) => p_1_out_n_62,
      P(42) => p_1_out_n_63,
      P(41) => p_1_out_n_64,
      P(40) => p_1_out_n_65,
      P(39) => p_1_out_n_66,
      P(38) => p_1_out_n_67,
      P(37) => p_1_out_n_68,
      P(36) => p_1_out_n_69,
      P(35) => p_1_out_n_70,
      P(34 downto 17) => out0(17 downto 0),
      P(16) => p_1_out_n_89,
      P(15) => p_1_out_n_90,
      P(14) => p_1_out_n_91,
      P(13) => p_1_out_n_92,
      P(12) => p_1_out_n_93,
      P(11) => p_1_out_n_94,
      P(10) => p_1_out_n_95,
      P(9) => p_1_out_n_96,
      P(8) => p_1_out_n_97,
      P(7) => p_1_out_n_98,
      P(6) => p_1_out_n_99,
      P(5) => p_1_out_n_100,
      P(4) => p_1_out_n_101,
      P(3) => p_1_out_n_102,
      P(2) => p_1_out_n_103,
      P(1) => p_1_out_n_104,
      P(0) => p_1_out_n_105,
      PATTERNBDETECT => NLW_p_1_out_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_p_1_out_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => NLW_p_1_out_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => NLW_p_1_out_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_p_1_out_XOROUT_UNCONNECTED(7 downto 0)
    );
\p_1_out__0\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__0\(26),
      A(28) => \A__0\(26),
      A(27) => \A__0\(26),
      A(26 downto 1) => \A__0\(26 downto 1),
      A(0) => \p_1_out__0_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__0_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__0_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__0\(26),
      C(46) => \A__0\(26),
      C(45) => \A__0\(26),
      C(44) => \A__0\(26),
      C(43) => \A__0\(26),
      C(42) => \A__0\(26),
      C(41) => \A__0\(26),
      C(40) => \A__0\(26),
      C(39) => \A__0\(26),
      C(38) => \A__0\(26),
      C(37) => \A__0\(26),
      C(36) => \A__0\(26),
      C(35) => \A__0\(26),
      C(34) => \A__0\(26),
      C(33) => \A__0\(26),
      C(32) => \A__0\(26),
      C(31) => \A__0\(26),
      C(30) => \A__0\(26),
      C(29) => \A__0\(26),
      C(28) => \A__0\(26),
      C(27) => \A__0\(26),
      C(26) => \A__0\(26),
      C(25 downto 0) => \A__0\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__0_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__0_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_0,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__0_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out1[17]\(0),
      OPMODE(4) => \out1[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__0_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__0_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__0_n_61\,
      P(43) => \p_1_out__0_n_62\,
      P(42) => \p_1_out__0_n_63\,
      P(41) => \p_1_out__0_n_64\,
      P(40) => \p_1_out__0_n_65\,
      P(39) => \p_1_out__0_n_66\,
      P(38) => \p_1_out__0_n_67\,
      P(37) => \p_1_out__0_n_68\,
      P(36) => \p_1_out__0_n_69\,
      P(35) => \p_1_out__0_n_70\,
      P(34 downto 17) => out1(17 downto 0),
      P(16) => \p_1_out__0_n_89\,
      P(15) => \p_1_out__0_n_90\,
      P(14) => \p_1_out__0_n_91\,
      P(13) => \p_1_out__0_n_92\,
      P(12) => \p_1_out__0_n_93\,
      P(11) => \p_1_out__0_n_94\,
      P(10) => \p_1_out__0_n_95\,
      P(9) => \p_1_out__0_n_96\,
      P(8) => \p_1_out__0_n_97\,
      P(7) => \p_1_out__0_n_98\,
      P(6) => \p_1_out__0_n_99\,
      P(5) => \p_1_out__0_n_100\,
      P(4) => \p_1_out__0_n_101\,
      P(3) => \p_1_out__0_n_102\,
      P(2) => \p_1_out__0_n_103\,
      P(1) => \p_1_out__0_n_104\,
      P(0) => \p_1_out__0_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__0_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__0_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__0_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__0_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__0_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__0_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(18),
      I1 => Delay1_out1(18),
      I2 => adc_trigger,
      O => \A__0\(18)
    );
\p_1_out__0_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(17),
      I1 => Delay1_out1(17),
      I2 => adc_trigger,
      O => \A__0\(17)
    );
\p_1_out__0_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(16),
      I1 => Delay1_out1(16),
      I2 => adc_trigger,
      O => \A__0\(16)
    );
\p_1_out__0_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(15),
      I1 => Delay1_out1(15),
      I2 => adc_trigger,
      O => \A__0\(15)
    );
\p_1_out__0_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(14),
      I1 => Delay1_out1(14),
      I2 => adc_trigger,
      O => \A__0\(14)
    );
\p_1_out__0_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(13),
      I1 => Delay1_out1(13),
      I2 => adc_trigger,
      O => \A__0\(13)
    );
\p_1_out__0_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(12),
      I1 => Delay1_out1(12),
      I2 => adc_trigger,
      O => \A__0\(12)
    );
\p_1_out__0_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(11),
      I1 => Delay1_out1(11),
      I2 => adc_trigger,
      O => \A__0\(11)
    );
\p_1_out__0_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(10),
      I1 => Delay1_out1(10),
      I2 => adc_trigger,
      O => \A__0\(10)
    );
\p_1_out__0_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(9),
      I1 => Delay1_out1(9),
      I2 => adc_trigger,
      O => \A__0\(9)
    );
\p_1_out__0_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(26),
      I1 => Delay1_out1(26),
      I2 => adc_trigger,
      O => \A__0\(26)
    );
\p_1_out__0_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(8),
      I1 => Delay1_out1(8),
      I2 => adc_trigger,
      O => \A__0\(8)
    );
\p_1_out__0_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(7),
      I1 => Delay1_out1(7),
      I2 => adc_trigger,
      O => \A__0\(7)
    );
\p_1_out__0_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(6),
      I1 => Delay1_out1(6),
      I2 => adc_trigger,
      O => \A__0\(6)
    );
\p_1_out__0_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(5),
      I1 => Delay1_out1(5),
      I2 => adc_trigger,
      O => \A__0\(5)
    );
\p_1_out__0_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(4),
      I1 => Delay1_out1(4),
      I2 => adc_trigger,
      O => \A__0\(4)
    );
\p_1_out__0_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(3),
      I1 => Delay1_out1(3),
      I2 => adc_trigger,
      O => \A__0\(3)
    );
\p_1_out__0_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(2),
      I1 => Delay1_out1(2),
      I2 => adc_trigger,
      O => \A__0\(2)
    );
\p_1_out__0_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(1),
      I1 => Delay1_out1(1),
      I2 => adc_trigger,
      O => \A__0\(1)
    );
\p_1_out__0_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(0),
      I1 => Delay1_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__0_i_28_n_0\
    );
\p_1_out__0_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(25),
      I1 => Delay1_out1(25),
      I2 => adc_trigger,
      O => \A__0\(25)
    );
\p_1_out__0_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(24),
      I1 => Delay1_out1(24),
      I2 => adc_trigger,
      O => \A__0\(24)
    );
\p_1_out__0_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(23),
      I1 => Delay1_out1(23),
      I2 => adc_trigger,
      O => \A__0\(23)
    );
\p_1_out__0_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(22),
      I1 => Delay1_out1(22),
      I2 => adc_trigger,
      O => \A__0\(22)
    );
\p_1_out__0_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(21),
      I1 => Delay1_out1(21),
      I2 => adc_trigger,
      O => \A__0\(21)
    );
\p_1_out__0_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(20),
      I1 => Delay1_out1(20),
      I2 => adc_trigger,
      O => \A__0\(20)
    );
\p_1_out__0_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in1(19),
      I1 => Delay1_out1(19),
      I2 => adc_trigger,
      O => \A__0\(19)
    );
\p_1_out__1\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__1\(26),
      A(28) => \A__1\(26),
      A(27) => \A__1\(26),
      A(26 downto 1) => \A__1\(26 downto 1),
      A(0) => \p_1_out__1_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__1_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__1_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__1\(26),
      C(46) => \A__1\(26),
      C(45) => \A__1\(26),
      C(44) => \A__1\(26),
      C(43) => \A__1\(26),
      C(42) => \A__1\(26),
      C(41) => \A__1\(26),
      C(40) => \A__1\(26),
      C(39) => \A__1\(26),
      C(38) => \A__1\(26),
      C(37) => \A__1\(26),
      C(36) => \A__1\(26),
      C(35) => \A__1\(26),
      C(34) => \A__1\(26),
      C(33) => \A__1\(26),
      C(32) => \A__1\(26),
      C(31) => \A__1\(26),
      C(30) => \A__1\(26),
      C(29) => \A__1\(26),
      C(28) => \A__1\(26),
      C(27) => \A__1\(26),
      C(26) => \A__1\(26),
      C(25 downto 0) => \A__1\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__1_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__1_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_1,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__1_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out2[17]\(0),
      OPMODE(4) => \out2[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__1_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__1_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__1_n_61\,
      P(43) => \p_1_out__1_n_62\,
      P(42) => \p_1_out__1_n_63\,
      P(41) => \p_1_out__1_n_64\,
      P(40) => \p_1_out__1_n_65\,
      P(39) => \p_1_out__1_n_66\,
      P(38) => \p_1_out__1_n_67\,
      P(37) => \p_1_out__1_n_68\,
      P(36) => \p_1_out__1_n_69\,
      P(35) => \p_1_out__1_n_70\,
      P(34 downto 17) => out2(17 downto 0),
      P(16) => \p_1_out__1_n_89\,
      P(15) => \p_1_out__1_n_90\,
      P(14) => \p_1_out__1_n_91\,
      P(13) => \p_1_out__1_n_92\,
      P(12) => \p_1_out__1_n_93\,
      P(11) => \p_1_out__1_n_94\,
      P(10) => \p_1_out__1_n_95\,
      P(9) => \p_1_out__1_n_96\,
      P(8) => \p_1_out__1_n_97\,
      P(7) => \p_1_out__1_n_98\,
      P(6) => \p_1_out__1_n_99\,
      P(5) => \p_1_out__1_n_100\,
      P(4) => \p_1_out__1_n_101\,
      P(3) => \p_1_out__1_n_102\,
      P(2) => \p_1_out__1_n_103\,
      P(1) => \p_1_out__1_n_104\,
      P(0) => \p_1_out__1_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__1_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__1_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__1_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__1_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__1_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__10\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__10\(26),
      A(28) => \A__10\(26),
      A(27) => \A__10\(26),
      A(26 downto 1) => \A__10\(26 downto 1),
      A(0) => \p_1_out__10_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__10_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__10_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__10\(26),
      C(46) => \A__10\(26),
      C(45) => \A__10\(26),
      C(44) => \A__10\(26),
      C(43) => \A__10\(26),
      C(42) => \A__10\(26),
      C(41) => \A__10\(26),
      C(40) => \A__10\(26),
      C(39) => \A__10\(26),
      C(38) => \A__10\(26),
      C(37) => \A__10\(26),
      C(36) => \A__10\(26),
      C(35) => \A__10\(26),
      C(34) => \A__10\(26),
      C(33) => \A__10\(26),
      C(32) => \A__10\(26),
      C(31) => \A__10\(26),
      C(30) => \A__10\(26),
      C(29) => \A__10\(26),
      C(28) => \A__10\(26),
      C(27) => \A__10\(26),
      C(26) => \A__10\(26),
      C(25 downto 0) => \A__10\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__10_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__10_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_10,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__10_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out11[17]\(0),
      OPMODE(4) => \out11[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__10_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__10_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__10_n_61\,
      P(43) => \p_1_out__10_n_62\,
      P(42) => \p_1_out__10_n_63\,
      P(41) => \p_1_out__10_n_64\,
      P(40) => \p_1_out__10_n_65\,
      P(39) => \p_1_out__10_n_66\,
      P(38) => \p_1_out__10_n_67\,
      P(37) => \p_1_out__10_n_68\,
      P(36) => \p_1_out__10_n_69\,
      P(35) => \p_1_out__10_n_70\,
      P(34 downto 17) => out11(17 downto 0),
      P(16) => \p_1_out__10_n_89\,
      P(15) => \p_1_out__10_n_90\,
      P(14) => \p_1_out__10_n_91\,
      P(13) => \p_1_out__10_n_92\,
      P(12) => \p_1_out__10_n_93\,
      P(11) => \p_1_out__10_n_94\,
      P(10) => \p_1_out__10_n_95\,
      P(9) => \p_1_out__10_n_96\,
      P(8) => \p_1_out__10_n_97\,
      P(7) => \p_1_out__10_n_98\,
      P(6) => \p_1_out__10_n_99\,
      P(5) => \p_1_out__10_n_100\,
      P(4) => \p_1_out__10_n_101\,
      P(3) => \p_1_out__10_n_102\,
      P(2) => \p_1_out__10_n_103\,
      P(1) => \p_1_out__10_n_104\,
      P(0) => \p_1_out__10_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__10_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__10_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__10_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__10_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__10_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__10_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(18),
      I1 => Delay11_out1(18),
      I2 => adc_trigger,
      O => \A__10\(18)
    );
\p_1_out__10_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(17),
      I1 => Delay11_out1(17),
      I2 => adc_trigger,
      O => \A__10\(17)
    );
\p_1_out__10_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(16),
      I1 => Delay11_out1(16),
      I2 => adc_trigger,
      O => \A__10\(16)
    );
\p_1_out__10_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(15),
      I1 => Delay11_out1(15),
      I2 => adc_trigger,
      O => \A__10\(15)
    );
\p_1_out__10_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(14),
      I1 => Delay11_out1(14),
      I2 => adc_trigger,
      O => \A__10\(14)
    );
\p_1_out__10_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(13),
      I1 => Delay11_out1(13),
      I2 => adc_trigger,
      O => \A__10\(13)
    );
\p_1_out__10_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(12),
      I1 => Delay11_out1(12),
      I2 => adc_trigger,
      O => \A__10\(12)
    );
\p_1_out__10_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(11),
      I1 => Delay11_out1(11),
      I2 => adc_trigger,
      O => \A__10\(11)
    );
\p_1_out__10_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(10),
      I1 => Delay11_out1(10),
      I2 => adc_trigger,
      O => \A__10\(10)
    );
\p_1_out__10_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(9),
      I1 => Delay11_out1(9),
      I2 => adc_trigger,
      O => \A__10\(9)
    );
\p_1_out__10_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(26),
      I1 => Delay11_out1(26),
      I2 => adc_trigger,
      O => \A__10\(26)
    );
\p_1_out__10_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(8),
      I1 => Delay11_out1(8),
      I2 => adc_trigger,
      O => \A__10\(8)
    );
\p_1_out__10_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(7),
      I1 => Delay11_out1(7),
      I2 => adc_trigger,
      O => \A__10\(7)
    );
\p_1_out__10_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(6),
      I1 => Delay11_out1(6),
      I2 => adc_trigger,
      O => \A__10\(6)
    );
\p_1_out__10_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(5),
      I1 => Delay11_out1(5),
      I2 => adc_trigger,
      O => \A__10\(5)
    );
\p_1_out__10_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(4),
      I1 => Delay11_out1(4),
      I2 => adc_trigger,
      O => \A__10\(4)
    );
\p_1_out__10_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(3),
      I1 => Delay11_out1(3),
      I2 => adc_trigger,
      O => \A__10\(3)
    );
\p_1_out__10_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(2),
      I1 => Delay11_out1(2),
      I2 => adc_trigger,
      O => \A__10\(2)
    );
\p_1_out__10_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(1),
      I1 => Delay11_out1(1),
      I2 => adc_trigger,
      O => \A__10\(1)
    );
\p_1_out__10_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(0),
      I1 => Delay11_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__10_i_28_n_0\
    );
\p_1_out__10_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(25),
      I1 => Delay11_out1(25),
      I2 => adc_trigger,
      O => \A__10\(25)
    );
\p_1_out__10_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(24),
      I1 => Delay11_out1(24),
      I2 => adc_trigger,
      O => \A__10\(24)
    );
\p_1_out__10_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(23),
      I1 => Delay11_out1(23),
      I2 => adc_trigger,
      O => \A__10\(23)
    );
\p_1_out__10_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(22),
      I1 => Delay11_out1(22),
      I2 => adc_trigger,
      O => \A__10\(22)
    );
\p_1_out__10_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(21),
      I1 => Delay11_out1(21),
      I2 => adc_trigger,
      O => \A__10\(21)
    );
\p_1_out__10_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(20),
      I1 => Delay11_out1(20),
      I2 => adc_trigger,
      O => \A__10\(20)
    );
\p_1_out__10_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in11(19),
      I1 => Delay11_out1(19),
      I2 => adc_trigger,
      O => \A__10\(19)
    );
\p_1_out__11\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__11\(26),
      A(28) => \A__11\(26),
      A(27) => \A__11\(26),
      A(26 downto 1) => \A__11\(26 downto 1),
      A(0) => \p_1_out__11_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__11_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__11_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__11\(26),
      C(46) => \A__11\(26),
      C(45) => \A__11\(26),
      C(44) => \A__11\(26),
      C(43) => \A__11\(26),
      C(42) => \A__11\(26),
      C(41) => \A__11\(26),
      C(40) => \A__11\(26),
      C(39) => \A__11\(26),
      C(38) => \A__11\(26),
      C(37) => \A__11\(26),
      C(36) => \A__11\(26),
      C(35) => \A__11\(26),
      C(34) => \A__11\(26),
      C(33) => \A__11\(26),
      C(32) => \A__11\(26),
      C(31) => \A__11\(26),
      C(30) => \A__11\(26),
      C(29) => \A__11\(26),
      C(28) => \A__11\(26),
      C(27) => \A__11\(26),
      C(26) => \A__11\(26),
      C(25 downto 0) => \A__11\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__11_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__11_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_11,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__11_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out12[17]\(0),
      OPMODE(4) => \out12[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__11_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__11_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__11_n_61\,
      P(43) => \p_1_out__11_n_62\,
      P(42) => \p_1_out__11_n_63\,
      P(41) => \p_1_out__11_n_64\,
      P(40) => \p_1_out__11_n_65\,
      P(39) => \p_1_out__11_n_66\,
      P(38) => \p_1_out__11_n_67\,
      P(37) => \p_1_out__11_n_68\,
      P(36) => \p_1_out__11_n_69\,
      P(35) => \p_1_out__11_n_70\,
      P(34 downto 17) => out12(17 downto 0),
      P(16) => \p_1_out__11_n_89\,
      P(15) => \p_1_out__11_n_90\,
      P(14) => \p_1_out__11_n_91\,
      P(13) => \p_1_out__11_n_92\,
      P(12) => \p_1_out__11_n_93\,
      P(11) => \p_1_out__11_n_94\,
      P(10) => \p_1_out__11_n_95\,
      P(9) => \p_1_out__11_n_96\,
      P(8) => \p_1_out__11_n_97\,
      P(7) => \p_1_out__11_n_98\,
      P(6) => \p_1_out__11_n_99\,
      P(5) => \p_1_out__11_n_100\,
      P(4) => \p_1_out__11_n_101\,
      P(3) => \p_1_out__11_n_102\,
      P(2) => \p_1_out__11_n_103\,
      P(1) => \p_1_out__11_n_104\,
      P(0) => \p_1_out__11_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__11_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__11_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__11_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__11_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__11_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__11_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(18),
      I1 => Delay12_out1(18),
      I2 => adc_trigger,
      O => \A__11\(18)
    );
\p_1_out__11_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(17),
      I1 => Delay12_out1(17),
      I2 => adc_trigger,
      O => \A__11\(17)
    );
\p_1_out__11_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(16),
      I1 => Delay12_out1(16),
      I2 => adc_trigger,
      O => \A__11\(16)
    );
\p_1_out__11_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(15),
      I1 => Delay12_out1(15),
      I2 => adc_trigger,
      O => \A__11\(15)
    );
\p_1_out__11_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(14),
      I1 => Delay12_out1(14),
      I2 => adc_trigger,
      O => \A__11\(14)
    );
\p_1_out__11_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(13),
      I1 => Delay12_out1(13),
      I2 => adc_trigger,
      O => \A__11\(13)
    );
\p_1_out__11_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(12),
      I1 => Delay12_out1(12),
      I2 => adc_trigger,
      O => \A__11\(12)
    );
\p_1_out__11_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(11),
      I1 => Delay12_out1(11),
      I2 => adc_trigger,
      O => \A__11\(11)
    );
\p_1_out__11_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(10),
      I1 => Delay12_out1(10),
      I2 => adc_trigger,
      O => \A__11\(10)
    );
\p_1_out__11_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(9),
      I1 => Delay12_out1(9),
      I2 => adc_trigger,
      O => \A__11\(9)
    );
\p_1_out__11_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(26),
      I1 => Delay12_out1(26),
      I2 => adc_trigger,
      O => \A__11\(26)
    );
\p_1_out__11_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(8),
      I1 => Delay12_out1(8),
      I2 => adc_trigger,
      O => \A__11\(8)
    );
\p_1_out__11_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(7),
      I1 => Delay12_out1(7),
      I2 => adc_trigger,
      O => \A__11\(7)
    );
\p_1_out__11_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(6),
      I1 => Delay12_out1(6),
      I2 => adc_trigger,
      O => \A__11\(6)
    );
\p_1_out__11_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(5),
      I1 => Delay12_out1(5),
      I2 => adc_trigger,
      O => \A__11\(5)
    );
\p_1_out__11_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(4),
      I1 => Delay12_out1(4),
      I2 => adc_trigger,
      O => \A__11\(4)
    );
\p_1_out__11_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(3),
      I1 => Delay12_out1(3),
      I2 => adc_trigger,
      O => \A__11\(3)
    );
\p_1_out__11_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(2),
      I1 => Delay12_out1(2),
      I2 => adc_trigger,
      O => \A__11\(2)
    );
\p_1_out__11_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(1),
      I1 => Delay12_out1(1),
      I2 => adc_trigger,
      O => \A__11\(1)
    );
\p_1_out__11_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(0),
      I1 => Delay12_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__11_i_28_n_0\
    );
\p_1_out__11_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(25),
      I1 => Delay12_out1(25),
      I2 => adc_trigger,
      O => \A__11\(25)
    );
\p_1_out__11_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(24),
      I1 => Delay12_out1(24),
      I2 => adc_trigger,
      O => \A__11\(24)
    );
\p_1_out__11_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(23),
      I1 => Delay12_out1(23),
      I2 => adc_trigger,
      O => \A__11\(23)
    );
\p_1_out__11_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(22),
      I1 => Delay12_out1(22),
      I2 => adc_trigger,
      O => \A__11\(22)
    );
\p_1_out__11_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(21),
      I1 => Delay12_out1(21),
      I2 => adc_trigger,
      O => \A__11\(21)
    );
\p_1_out__11_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(20),
      I1 => Delay12_out1(20),
      I2 => adc_trigger,
      O => \A__11\(20)
    );
\p_1_out__11_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in12(19),
      I1 => Delay12_out1(19),
      I2 => adc_trigger,
      O => \A__11\(19)
    );
\p_1_out__12\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__12\(26),
      A(28) => \A__12\(26),
      A(27) => \A__12\(26),
      A(26 downto 1) => \A__12\(26 downto 1),
      A(0) => \p_1_out__12_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__12_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__12_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__12\(26),
      C(46) => \A__12\(26),
      C(45) => \A__12\(26),
      C(44) => \A__12\(26),
      C(43) => \A__12\(26),
      C(42) => \A__12\(26),
      C(41) => \A__12\(26),
      C(40) => \A__12\(26),
      C(39) => \A__12\(26),
      C(38) => \A__12\(26),
      C(37) => \A__12\(26),
      C(36) => \A__12\(26),
      C(35) => \A__12\(26),
      C(34) => \A__12\(26),
      C(33) => \A__12\(26),
      C(32) => \A__12\(26),
      C(31) => \A__12\(26),
      C(30) => \A__12\(26),
      C(29) => \A__12\(26),
      C(28) => \A__12\(26),
      C(27) => \A__12\(26),
      C(26) => \A__12\(26),
      C(25 downto 0) => \A__12\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__12_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__12_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_12,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__12_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out13[17]\(0),
      OPMODE(4) => \out13[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__12_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__12_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__12_n_61\,
      P(43) => \p_1_out__12_n_62\,
      P(42) => \p_1_out__12_n_63\,
      P(41) => \p_1_out__12_n_64\,
      P(40) => \p_1_out__12_n_65\,
      P(39) => \p_1_out__12_n_66\,
      P(38) => \p_1_out__12_n_67\,
      P(37) => \p_1_out__12_n_68\,
      P(36) => \p_1_out__12_n_69\,
      P(35) => \p_1_out__12_n_70\,
      P(34 downto 17) => out13(17 downto 0),
      P(16) => \p_1_out__12_n_89\,
      P(15) => \p_1_out__12_n_90\,
      P(14) => \p_1_out__12_n_91\,
      P(13) => \p_1_out__12_n_92\,
      P(12) => \p_1_out__12_n_93\,
      P(11) => \p_1_out__12_n_94\,
      P(10) => \p_1_out__12_n_95\,
      P(9) => \p_1_out__12_n_96\,
      P(8) => \p_1_out__12_n_97\,
      P(7) => \p_1_out__12_n_98\,
      P(6) => \p_1_out__12_n_99\,
      P(5) => \p_1_out__12_n_100\,
      P(4) => \p_1_out__12_n_101\,
      P(3) => \p_1_out__12_n_102\,
      P(2) => \p_1_out__12_n_103\,
      P(1) => \p_1_out__12_n_104\,
      P(0) => \p_1_out__12_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__12_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__12_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__12_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__12_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__12_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__12_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(18),
      I1 => Delay13_out1(18),
      I2 => adc_trigger,
      O => \A__12\(18)
    );
\p_1_out__12_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(17),
      I1 => Delay13_out1(17),
      I2 => adc_trigger,
      O => \A__12\(17)
    );
\p_1_out__12_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(16),
      I1 => Delay13_out1(16),
      I2 => adc_trigger,
      O => \A__12\(16)
    );
\p_1_out__12_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(15),
      I1 => Delay13_out1(15),
      I2 => adc_trigger,
      O => \A__12\(15)
    );
\p_1_out__12_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(14),
      I1 => Delay13_out1(14),
      I2 => adc_trigger,
      O => \A__12\(14)
    );
\p_1_out__12_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(13),
      I1 => Delay13_out1(13),
      I2 => adc_trigger,
      O => \A__12\(13)
    );
\p_1_out__12_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(12),
      I1 => Delay13_out1(12),
      I2 => adc_trigger,
      O => \A__12\(12)
    );
\p_1_out__12_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(11),
      I1 => Delay13_out1(11),
      I2 => adc_trigger,
      O => \A__12\(11)
    );
\p_1_out__12_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(10),
      I1 => Delay13_out1(10),
      I2 => adc_trigger,
      O => \A__12\(10)
    );
\p_1_out__12_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(9),
      I1 => Delay13_out1(9),
      I2 => adc_trigger,
      O => \A__12\(9)
    );
\p_1_out__12_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(26),
      I1 => Delay13_out1(26),
      I2 => adc_trigger,
      O => \A__12\(26)
    );
\p_1_out__12_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(8),
      I1 => Delay13_out1(8),
      I2 => adc_trigger,
      O => \A__12\(8)
    );
\p_1_out__12_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(7),
      I1 => Delay13_out1(7),
      I2 => adc_trigger,
      O => \A__12\(7)
    );
\p_1_out__12_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(6),
      I1 => Delay13_out1(6),
      I2 => adc_trigger,
      O => \A__12\(6)
    );
\p_1_out__12_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(5),
      I1 => Delay13_out1(5),
      I2 => adc_trigger,
      O => \A__12\(5)
    );
\p_1_out__12_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(4),
      I1 => Delay13_out1(4),
      I2 => adc_trigger,
      O => \A__12\(4)
    );
\p_1_out__12_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(3),
      I1 => Delay13_out1(3),
      I2 => adc_trigger,
      O => \A__12\(3)
    );
\p_1_out__12_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(2),
      I1 => Delay13_out1(2),
      I2 => adc_trigger,
      O => \A__12\(2)
    );
\p_1_out__12_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(1),
      I1 => Delay13_out1(1),
      I2 => adc_trigger,
      O => \A__12\(1)
    );
\p_1_out__12_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(0),
      I1 => Delay13_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__12_i_28_n_0\
    );
\p_1_out__12_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(25),
      I1 => Delay13_out1(25),
      I2 => adc_trigger,
      O => \A__12\(25)
    );
\p_1_out__12_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(24),
      I1 => Delay13_out1(24),
      I2 => adc_trigger,
      O => \A__12\(24)
    );
\p_1_out__12_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(23),
      I1 => Delay13_out1(23),
      I2 => adc_trigger,
      O => \A__12\(23)
    );
\p_1_out__12_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(22),
      I1 => Delay13_out1(22),
      I2 => adc_trigger,
      O => \A__12\(22)
    );
\p_1_out__12_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(21),
      I1 => Delay13_out1(21),
      I2 => adc_trigger,
      O => \A__12\(21)
    );
\p_1_out__12_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(20),
      I1 => Delay13_out1(20),
      I2 => adc_trigger,
      O => \A__12\(20)
    );
\p_1_out__12_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in13(19),
      I1 => Delay13_out1(19),
      I2 => adc_trigger,
      O => \A__12\(19)
    );
\p_1_out__13\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__13\(26),
      A(28) => \A__13\(26),
      A(27) => \A__13\(26),
      A(26 downto 1) => \A__13\(26 downto 1),
      A(0) => \p_1_out__13_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__13_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__13_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__13\(26),
      C(46) => \A__13\(26),
      C(45) => \A__13\(26),
      C(44) => \A__13\(26),
      C(43) => \A__13\(26),
      C(42) => \A__13\(26),
      C(41) => \A__13\(26),
      C(40) => \A__13\(26),
      C(39) => \A__13\(26),
      C(38) => \A__13\(26),
      C(37) => \A__13\(26),
      C(36) => \A__13\(26),
      C(35) => \A__13\(26),
      C(34) => \A__13\(26),
      C(33) => \A__13\(26),
      C(32) => \A__13\(26),
      C(31) => \A__13\(26),
      C(30) => \A__13\(26),
      C(29) => \A__13\(26),
      C(28) => \A__13\(26),
      C(27) => \A__13\(26),
      C(26) => \A__13\(26),
      C(25 downto 0) => \A__13\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__13_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__13_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_13,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__13_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out14[17]\(0),
      OPMODE(4) => \out14[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__13_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__13_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__13_n_61\,
      P(43) => \p_1_out__13_n_62\,
      P(42) => \p_1_out__13_n_63\,
      P(41) => \p_1_out__13_n_64\,
      P(40) => \p_1_out__13_n_65\,
      P(39) => \p_1_out__13_n_66\,
      P(38) => \p_1_out__13_n_67\,
      P(37) => \p_1_out__13_n_68\,
      P(36) => \p_1_out__13_n_69\,
      P(35) => \p_1_out__13_n_70\,
      P(34 downto 17) => out14(17 downto 0),
      P(16) => \p_1_out__13_n_89\,
      P(15) => \p_1_out__13_n_90\,
      P(14) => \p_1_out__13_n_91\,
      P(13) => \p_1_out__13_n_92\,
      P(12) => \p_1_out__13_n_93\,
      P(11) => \p_1_out__13_n_94\,
      P(10) => \p_1_out__13_n_95\,
      P(9) => \p_1_out__13_n_96\,
      P(8) => \p_1_out__13_n_97\,
      P(7) => \p_1_out__13_n_98\,
      P(6) => \p_1_out__13_n_99\,
      P(5) => \p_1_out__13_n_100\,
      P(4) => \p_1_out__13_n_101\,
      P(3) => \p_1_out__13_n_102\,
      P(2) => \p_1_out__13_n_103\,
      P(1) => \p_1_out__13_n_104\,
      P(0) => \p_1_out__13_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__13_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__13_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__13_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__13_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__13_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__13_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(18),
      I1 => Delay14_out1(18),
      I2 => adc_trigger,
      O => \A__13\(18)
    );
\p_1_out__13_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(17),
      I1 => Delay14_out1(17),
      I2 => adc_trigger,
      O => \A__13\(17)
    );
\p_1_out__13_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(16),
      I1 => Delay14_out1(16),
      I2 => adc_trigger,
      O => \A__13\(16)
    );
\p_1_out__13_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(15),
      I1 => Delay14_out1(15),
      I2 => adc_trigger,
      O => \A__13\(15)
    );
\p_1_out__13_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(14),
      I1 => Delay14_out1(14),
      I2 => adc_trigger,
      O => \A__13\(14)
    );
\p_1_out__13_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(13),
      I1 => Delay14_out1(13),
      I2 => adc_trigger,
      O => \A__13\(13)
    );
\p_1_out__13_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(12),
      I1 => Delay14_out1(12),
      I2 => adc_trigger,
      O => \A__13\(12)
    );
\p_1_out__13_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(11),
      I1 => Delay14_out1(11),
      I2 => adc_trigger,
      O => \A__13\(11)
    );
\p_1_out__13_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(10),
      I1 => Delay14_out1(10),
      I2 => adc_trigger,
      O => \A__13\(10)
    );
\p_1_out__13_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(9),
      I1 => Delay14_out1(9),
      I2 => adc_trigger,
      O => \A__13\(9)
    );
\p_1_out__13_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(26),
      I1 => Delay14_out1(26),
      I2 => adc_trigger,
      O => \A__13\(26)
    );
\p_1_out__13_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(8),
      I1 => Delay14_out1(8),
      I2 => adc_trigger,
      O => \A__13\(8)
    );
\p_1_out__13_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(7),
      I1 => Delay14_out1(7),
      I2 => adc_trigger,
      O => \A__13\(7)
    );
\p_1_out__13_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(6),
      I1 => Delay14_out1(6),
      I2 => adc_trigger,
      O => \A__13\(6)
    );
\p_1_out__13_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(5),
      I1 => Delay14_out1(5),
      I2 => adc_trigger,
      O => \A__13\(5)
    );
\p_1_out__13_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(4),
      I1 => Delay14_out1(4),
      I2 => adc_trigger,
      O => \A__13\(4)
    );
\p_1_out__13_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(3),
      I1 => Delay14_out1(3),
      I2 => adc_trigger,
      O => \A__13\(3)
    );
\p_1_out__13_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(2),
      I1 => Delay14_out1(2),
      I2 => adc_trigger,
      O => \A__13\(2)
    );
\p_1_out__13_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(1),
      I1 => Delay14_out1(1),
      I2 => adc_trigger,
      O => \A__13\(1)
    );
\p_1_out__13_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(0),
      I1 => Delay14_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__13_i_28_n_0\
    );
\p_1_out__13_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(25),
      I1 => Delay14_out1(25),
      I2 => adc_trigger,
      O => \A__13\(25)
    );
\p_1_out__13_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(24),
      I1 => Delay14_out1(24),
      I2 => adc_trigger,
      O => \A__13\(24)
    );
\p_1_out__13_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(23),
      I1 => Delay14_out1(23),
      I2 => adc_trigger,
      O => \A__13\(23)
    );
\p_1_out__13_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(22),
      I1 => Delay14_out1(22),
      I2 => adc_trigger,
      O => \A__13\(22)
    );
\p_1_out__13_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(21),
      I1 => Delay14_out1(21),
      I2 => adc_trigger,
      O => \A__13\(21)
    );
\p_1_out__13_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(20),
      I1 => Delay14_out1(20),
      I2 => adc_trigger,
      O => \A__13\(20)
    );
\p_1_out__13_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in14(19),
      I1 => Delay14_out1(19),
      I2 => adc_trigger,
      O => \A__13\(19)
    );
\p_1_out__14\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__14\(26),
      A(28) => \A__14\(26),
      A(27) => \A__14\(26),
      A(26 downto 1) => \A__14\(26 downto 1),
      A(0) => \p_1_out__14_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__14_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__14_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__14\(26),
      C(46) => \A__14\(26),
      C(45) => \A__14\(26),
      C(44) => \A__14\(26),
      C(43) => \A__14\(26),
      C(42) => \A__14\(26),
      C(41) => \A__14\(26),
      C(40) => \A__14\(26),
      C(39) => \A__14\(26),
      C(38) => \A__14\(26),
      C(37) => \A__14\(26),
      C(36) => \A__14\(26),
      C(35) => \A__14\(26),
      C(34) => \A__14\(26),
      C(33) => \A__14\(26),
      C(32) => \A__14\(26),
      C(31) => \A__14\(26),
      C(30) => \A__14\(26),
      C(29) => \A__14\(26),
      C(28) => \A__14\(26),
      C(27) => \A__14\(26),
      C(26) => \A__14\(26),
      C(25 downto 0) => \A__14\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__14_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__14_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_14,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__14_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out15[17]\(0),
      OPMODE(4) => \out15[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__14_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__14_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__14_n_61\,
      P(43) => \p_1_out__14_n_62\,
      P(42) => \p_1_out__14_n_63\,
      P(41) => \p_1_out__14_n_64\,
      P(40) => \p_1_out__14_n_65\,
      P(39) => \p_1_out__14_n_66\,
      P(38) => \p_1_out__14_n_67\,
      P(37) => \p_1_out__14_n_68\,
      P(36) => \p_1_out__14_n_69\,
      P(35) => \p_1_out__14_n_70\,
      P(34 downto 17) => out15(17 downto 0),
      P(16) => \p_1_out__14_n_89\,
      P(15) => \p_1_out__14_n_90\,
      P(14) => \p_1_out__14_n_91\,
      P(13) => \p_1_out__14_n_92\,
      P(12) => \p_1_out__14_n_93\,
      P(11) => \p_1_out__14_n_94\,
      P(10) => \p_1_out__14_n_95\,
      P(9) => \p_1_out__14_n_96\,
      P(8) => \p_1_out__14_n_97\,
      P(7) => \p_1_out__14_n_98\,
      P(6) => \p_1_out__14_n_99\,
      P(5) => \p_1_out__14_n_100\,
      P(4) => \p_1_out__14_n_101\,
      P(3) => \p_1_out__14_n_102\,
      P(2) => \p_1_out__14_n_103\,
      P(1) => \p_1_out__14_n_104\,
      P(0) => \p_1_out__14_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__14_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__14_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__14_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__14_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__14_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__14_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(18),
      I1 => Delay15_out1(18),
      I2 => adc_trigger,
      O => \A__14\(18)
    );
\p_1_out__14_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(17),
      I1 => Delay15_out1(17),
      I2 => adc_trigger,
      O => \A__14\(17)
    );
\p_1_out__14_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(16),
      I1 => Delay15_out1(16),
      I2 => adc_trigger,
      O => \A__14\(16)
    );
\p_1_out__14_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(15),
      I1 => Delay15_out1(15),
      I2 => adc_trigger,
      O => \A__14\(15)
    );
\p_1_out__14_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(14),
      I1 => Delay15_out1(14),
      I2 => adc_trigger,
      O => \A__14\(14)
    );
\p_1_out__14_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(13),
      I1 => Delay15_out1(13),
      I2 => adc_trigger,
      O => \A__14\(13)
    );
\p_1_out__14_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(12),
      I1 => Delay15_out1(12),
      I2 => adc_trigger,
      O => \A__14\(12)
    );
\p_1_out__14_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(11),
      I1 => Delay15_out1(11),
      I2 => adc_trigger,
      O => \A__14\(11)
    );
\p_1_out__14_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(10),
      I1 => Delay15_out1(10),
      I2 => adc_trigger,
      O => \A__14\(10)
    );
\p_1_out__14_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(9),
      I1 => Delay15_out1(9),
      I2 => adc_trigger,
      O => \A__14\(9)
    );
\p_1_out__14_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(26),
      I1 => Delay15_out1(26),
      I2 => adc_trigger,
      O => \A__14\(26)
    );
\p_1_out__14_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(8),
      I1 => Delay15_out1(8),
      I2 => adc_trigger,
      O => \A__14\(8)
    );
\p_1_out__14_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(7),
      I1 => Delay15_out1(7),
      I2 => adc_trigger,
      O => \A__14\(7)
    );
\p_1_out__14_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(6),
      I1 => Delay15_out1(6),
      I2 => adc_trigger,
      O => \A__14\(6)
    );
\p_1_out__14_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(5),
      I1 => Delay15_out1(5),
      I2 => adc_trigger,
      O => \A__14\(5)
    );
\p_1_out__14_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(4),
      I1 => Delay15_out1(4),
      I2 => adc_trigger,
      O => \A__14\(4)
    );
\p_1_out__14_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(3),
      I1 => Delay15_out1(3),
      I2 => adc_trigger,
      O => \A__14\(3)
    );
\p_1_out__14_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(2),
      I1 => Delay15_out1(2),
      I2 => adc_trigger,
      O => \A__14\(2)
    );
\p_1_out__14_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(1),
      I1 => Delay15_out1(1),
      I2 => adc_trigger,
      O => \A__14\(1)
    );
\p_1_out__14_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(0),
      I1 => Delay15_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__14_i_28_n_0\
    );
\p_1_out__14_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(25),
      I1 => Delay15_out1(25),
      I2 => adc_trigger,
      O => \A__14\(25)
    );
\p_1_out__14_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(24),
      I1 => Delay15_out1(24),
      I2 => adc_trigger,
      O => \A__14\(24)
    );
\p_1_out__14_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(23),
      I1 => Delay15_out1(23),
      I2 => adc_trigger,
      O => \A__14\(23)
    );
\p_1_out__14_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(22),
      I1 => Delay15_out1(22),
      I2 => adc_trigger,
      O => \A__14\(22)
    );
\p_1_out__14_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(21),
      I1 => Delay15_out1(21),
      I2 => adc_trigger,
      O => \A__14\(21)
    );
\p_1_out__14_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(20),
      I1 => Delay15_out1(20),
      I2 => adc_trigger,
      O => \A__14\(20)
    );
\p_1_out__14_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in15(19),
      I1 => Delay15_out1(19),
      I2 => adc_trigger,
      O => \A__14\(19)
    );
\p_1_out__15\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__15\(26),
      A(28) => \A__15\(26),
      A(27) => \A__15\(26),
      A(26 downto 1) => \A__15\(26 downto 1),
      A(0) => \p_1_out__15_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__15_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__15_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__15\(26),
      C(46) => \A__15\(26),
      C(45) => \A__15\(26),
      C(44) => \A__15\(26),
      C(43) => \A__15\(26),
      C(42) => \A__15\(26),
      C(41) => \A__15\(26),
      C(40) => \A__15\(26),
      C(39) => \A__15\(26),
      C(38) => \A__15\(26),
      C(37) => \A__15\(26),
      C(36) => \A__15\(26),
      C(35) => \A__15\(26),
      C(34) => \A__15\(26),
      C(33) => \A__15\(26),
      C(32) => \A__15\(26),
      C(31) => \A__15\(26),
      C(30) => \A__15\(26),
      C(29) => \A__15\(26),
      C(28) => \A__15\(26),
      C(27) => \A__15\(26),
      C(26) => \A__15\(26),
      C(25 downto 0) => \A__15\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__15_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__15_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_15,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__15_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out16[17]\(0),
      OPMODE(4) => \out16[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__15_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__15_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__15_n_61\,
      P(43) => \p_1_out__15_n_62\,
      P(42) => \p_1_out__15_n_63\,
      P(41) => \p_1_out__15_n_64\,
      P(40) => \p_1_out__15_n_65\,
      P(39) => \p_1_out__15_n_66\,
      P(38) => \p_1_out__15_n_67\,
      P(37) => \p_1_out__15_n_68\,
      P(36) => \p_1_out__15_n_69\,
      P(35) => \p_1_out__15_n_70\,
      P(34 downto 17) => out16(17 downto 0),
      P(16) => \p_1_out__15_n_89\,
      P(15) => \p_1_out__15_n_90\,
      P(14) => \p_1_out__15_n_91\,
      P(13) => \p_1_out__15_n_92\,
      P(12) => \p_1_out__15_n_93\,
      P(11) => \p_1_out__15_n_94\,
      P(10) => \p_1_out__15_n_95\,
      P(9) => \p_1_out__15_n_96\,
      P(8) => \p_1_out__15_n_97\,
      P(7) => \p_1_out__15_n_98\,
      P(6) => \p_1_out__15_n_99\,
      P(5) => \p_1_out__15_n_100\,
      P(4) => \p_1_out__15_n_101\,
      P(3) => \p_1_out__15_n_102\,
      P(2) => \p_1_out__15_n_103\,
      P(1) => \p_1_out__15_n_104\,
      P(0) => \p_1_out__15_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__15_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__15_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__15_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__15_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__15_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__15_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(18),
      I1 => Delay16_out1(18),
      I2 => adc_trigger,
      O => \A__15\(18)
    );
\p_1_out__15_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(17),
      I1 => Delay16_out1(17),
      I2 => adc_trigger,
      O => \A__15\(17)
    );
\p_1_out__15_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(16),
      I1 => Delay16_out1(16),
      I2 => adc_trigger,
      O => \A__15\(16)
    );
\p_1_out__15_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(15),
      I1 => Delay16_out1(15),
      I2 => adc_trigger,
      O => \A__15\(15)
    );
\p_1_out__15_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(14),
      I1 => Delay16_out1(14),
      I2 => adc_trigger,
      O => \A__15\(14)
    );
\p_1_out__15_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(13),
      I1 => Delay16_out1(13),
      I2 => adc_trigger,
      O => \A__15\(13)
    );
\p_1_out__15_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(12),
      I1 => Delay16_out1(12),
      I2 => adc_trigger,
      O => \A__15\(12)
    );
\p_1_out__15_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(11),
      I1 => Delay16_out1(11),
      I2 => adc_trigger,
      O => \A__15\(11)
    );
\p_1_out__15_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(10),
      I1 => Delay16_out1(10),
      I2 => adc_trigger,
      O => \A__15\(10)
    );
\p_1_out__15_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(9),
      I1 => Delay16_out1(9),
      I2 => adc_trigger,
      O => \A__15\(9)
    );
\p_1_out__15_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(26),
      I1 => Delay16_out1(26),
      I2 => adc_trigger,
      O => \A__15\(26)
    );
\p_1_out__15_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(8),
      I1 => Delay16_out1(8),
      I2 => adc_trigger,
      O => \A__15\(8)
    );
\p_1_out__15_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(7),
      I1 => Delay16_out1(7),
      I2 => adc_trigger,
      O => \A__15\(7)
    );
\p_1_out__15_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(6),
      I1 => Delay16_out1(6),
      I2 => adc_trigger,
      O => \A__15\(6)
    );
\p_1_out__15_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(5),
      I1 => Delay16_out1(5),
      I2 => adc_trigger,
      O => \A__15\(5)
    );
\p_1_out__15_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(4),
      I1 => Delay16_out1(4),
      I2 => adc_trigger,
      O => \A__15\(4)
    );
\p_1_out__15_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(3),
      I1 => Delay16_out1(3),
      I2 => adc_trigger,
      O => \A__15\(3)
    );
\p_1_out__15_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(2),
      I1 => Delay16_out1(2),
      I2 => adc_trigger,
      O => \A__15\(2)
    );
\p_1_out__15_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(1),
      I1 => Delay16_out1(1),
      I2 => adc_trigger,
      O => \A__15\(1)
    );
\p_1_out__15_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(0),
      I1 => Delay16_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__15_i_28_n_0\
    );
\p_1_out__15_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(25),
      I1 => Delay16_out1(25),
      I2 => adc_trigger,
      O => \A__15\(25)
    );
\p_1_out__15_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(24),
      I1 => Delay16_out1(24),
      I2 => adc_trigger,
      O => \A__15\(24)
    );
\p_1_out__15_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(23),
      I1 => Delay16_out1(23),
      I2 => adc_trigger,
      O => \A__15\(23)
    );
\p_1_out__15_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(22),
      I1 => Delay16_out1(22),
      I2 => adc_trigger,
      O => \A__15\(22)
    );
\p_1_out__15_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(21),
      I1 => Delay16_out1(21),
      I2 => adc_trigger,
      O => \A__15\(21)
    );
\p_1_out__15_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(20),
      I1 => Delay16_out1(20),
      I2 => adc_trigger,
      O => \A__15\(20)
    );
\p_1_out__15_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in16(19),
      I1 => Delay16_out1(19),
      I2 => adc_trigger,
      O => \A__15\(19)
    );
\p_1_out__16\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__16\(26),
      A(28) => \A__16\(26),
      A(27) => \A__16\(26),
      A(26 downto 1) => \A__16\(26 downto 1),
      A(0) => \p_1_out__16_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__16_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__16_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__16\(26),
      C(46) => \A__16\(26),
      C(45) => \A__16\(26),
      C(44) => \A__16\(26),
      C(43) => \A__16\(26),
      C(42) => \A__16\(26),
      C(41) => \A__16\(26),
      C(40) => \A__16\(26),
      C(39) => \A__16\(26),
      C(38) => \A__16\(26),
      C(37) => \A__16\(26),
      C(36) => \A__16\(26),
      C(35) => \A__16\(26),
      C(34) => \A__16\(26),
      C(33) => \A__16\(26),
      C(32) => \A__16\(26),
      C(31) => \A__16\(26),
      C(30) => \A__16\(26),
      C(29) => \A__16\(26),
      C(28) => \A__16\(26),
      C(27) => \A__16\(26),
      C(26) => \A__16\(26),
      C(25 downto 0) => \A__16\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__16_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__16_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_16,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__16_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out17[17]\(0),
      OPMODE(4) => \out17[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__16_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__16_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__16_n_61\,
      P(43) => \p_1_out__16_n_62\,
      P(42) => \p_1_out__16_n_63\,
      P(41) => \p_1_out__16_n_64\,
      P(40) => \p_1_out__16_n_65\,
      P(39) => \p_1_out__16_n_66\,
      P(38) => \p_1_out__16_n_67\,
      P(37) => \p_1_out__16_n_68\,
      P(36) => \p_1_out__16_n_69\,
      P(35) => \p_1_out__16_n_70\,
      P(34 downto 17) => out17(17 downto 0),
      P(16) => \p_1_out__16_n_89\,
      P(15) => \p_1_out__16_n_90\,
      P(14) => \p_1_out__16_n_91\,
      P(13) => \p_1_out__16_n_92\,
      P(12) => \p_1_out__16_n_93\,
      P(11) => \p_1_out__16_n_94\,
      P(10) => \p_1_out__16_n_95\,
      P(9) => \p_1_out__16_n_96\,
      P(8) => \p_1_out__16_n_97\,
      P(7) => \p_1_out__16_n_98\,
      P(6) => \p_1_out__16_n_99\,
      P(5) => \p_1_out__16_n_100\,
      P(4) => \p_1_out__16_n_101\,
      P(3) => \p_1_out__16_n_102\,
      P(2) => \p_1_out__16_n_103\,
      P(1) => \p_1_out__16_n_104\,
      P(0) => \p_1_out__16_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__16_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__16_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__16_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__16_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__16_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__16_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(18),
      I1 => Delay17_out1(18),
      I2 => adc_trigger,
      O => \A__16\(18)
    );
\p_1_out__16_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(17),
      I1 => Delay17_out1(17),
      I2 => adc_trigger,
      O => \A__16\(17)
    );
\p_1_out__16_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(16),
      I1 => Delay17_out1(16),
      I2 => adc_trigger,
      O => \A__16\(16)
    );
\p_1_out__16_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(15),
      I1 => Delay17_out1(15),
      I2 => adc_trigger,
      O => \A__16\(15)
    );
\p_1_out__16_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(14),
      I1 => Delay17_out1(14),
      I2 => adc_trigger,
      O => \A__16\(14)
    );
\p_1_out__16_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(13),
      I1 => Delay17_out1(13),
      I2 => adc_trigger,
      O => \A__16\(13)
    );
\p_1_out__16_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(12),
      I1 => Delay17_out1(12),
      I2 => adc_trigger,
      O => \A__16\(12)
    );
\p_1_out__16_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(11),
      I1 => Delay17_out1(11),
      I2 => adc_trigger,
      O => \A__16\(11)
    );
\p_1_out__16_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(10),
      I1 => Delay17_out1(10),
      I2 => adc_trigger,
      O => \A__16\(10)
    );
\p_1_out__16_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(9),
      I1 => Delay17_out1(9),
      I2 => adc_trigger,
      O => \A__16\(9)
    );
\p_1_out__16_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(26),
      I1 => Delay17_out1(26),
      I2 => adc_trigger,
      O => \A__16\(26)
    );
\p_1_out__16_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(8),
      I1 => Delay17_out1(8),
      I2 => adc_trigger,
      O => \A__16\(8)
    );
\p_1_out__16_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(7),
      I1 => Delay17_out1(7),
      I2 => adc_trigger,
      O => \A__16\(7)
    );
\p_1_out__16_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(6),
      I1 => Delay17_out1(6),
      I2 => adc_trigger,
      O => \A__16\(6)
    );
\p_1_out__16_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(5),
      I1 => Delay17_out1(5),
      I2 => adc_trigger,
      O => \A__16\(5)
    );
\p_1_out__16_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(4),
      I1 => Delay17_out1(4),
      I2 => adc_trigger,
      O => \A__16\(4)
    );
\p_1_out__16_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(3),
      I1 => Delay17_out1(3),
      I2 => adc_trigger,
      O => \A__16\(3)
    );
\p_1_out__16_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(2),
      I1 => Delay17_out1(2),
      I2 => adc_trigger,
      O => \A__16\(2)
    );
\p_1_out__16_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(1),
      I1 => Delay17_out1(1),
      I2 => adc_trigger,
      O => \A__16\(1)
    );
\p_1_out__16_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(0),
      I1 => Delay17_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__16_i_28_n_0\
    );
\p_1_out__16_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(25),
      I1 => Delay17_out1(25),
      I2 => adc_trigger,
      O => \A__16\(25)
    );
\p_1_out__16_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(24),
      I1 => Delay17_out1(24),
      I2 => adc_trigger,
      O => \A__16\(24)
    );
\p_1_out__16_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(23),
      I1 => Delay17_out1(23),
      I2 => adc_trigger,
      O => \A__16\(23)
    );
\p_1_out__16_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(22),
      I1 => Delay17_out1(22),
      I2 => adc_trigger,
      O => \A__16\(22)
    );
\p_1_out__16_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(21),
      I1 => Delay17_out1(21),
      I2 => adc_trigger,
      O => \A__16\(21)
    );
\p_1_out__16_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(20),
      I1 => Delay17_out1(20),
      I2 => adc_trigger,
      O => \A__16\(20)
    );
\p_1_out__16_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in17(19),
      I1 => Delay17_out1(19),
      I2 => adc_trigger,
      O => \A__16\(19)
    );
\p_1_out__17\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__17\(26),
      A(28) => \A__17\(26),
      A(27) => \A__17\(26),
      A(26 downto 1) => \A__17\(26 downto 1),
      A(0) => \p_1_out__17_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__17_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__17_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__17\(26),
      C(46) => \A__17\(26),
      C(45) => \A__17\(26),
      C(44) => \A__17\(26),
      C(43) => \A__17\(26),
      C(42) => \A__17\(26),
      C(41) => \A__17\(26),
      C(40) => \A__17\(26),
      C(39) => \A__17\(26),
      C(38) => \A__17\(26),
      C(37) => \A__17\(26),
      C(36) => \A__17\(26),
      C(35) => \A__17\(26),
      C(34) => \A__17\(26),
      C(33) => \A__17\(26),
      C(32) => \A__17\(26),
      C(31) => \A__17\(26),
      C(30) => \A__17\(26),
      C(29) => \A__17\(26),
      C(28) => \A__17\(26),
      C(27) => \A__17\(26),
      C(26) => \A__17\(26),
      C(25 downto 0) => \A__17\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__17_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__17_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_17,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__17_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out18[17]\(0),
      OPMODE(4) => \out18[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__17_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__17_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__17_n_61\,
      P(43) => \p_1_out__17_n_62\,
      P(42) => \p_1_out__17_n_63\,
      P(41) => \p_1_out__17_n_64\,
      P(40) => \p_1_out__17_n_65\,
      P(39) => \p_1_out__17_n_66\,
      P(38) => \p_1_out__17_n_67\,
      P(37) => \p_1_out__17_n_68\,
      P(36) => \p_1_out__17_n_69\,
      P(35) => \p_1_out__17_n_70\,
      P(34 downto 17) => out18(17 downto 0),
      P(16) => \p_1_out__17_n_89\,
      P(15) => \p_1_out__17_n_90\,
      P(14) => \p_1_out__17_n_91\,
      P(13) => \p_1_out__17_n_92\,
      P(12) => \p_1_out__17_n_93\,
      P(11) => \p_1_out__17_n_94\,
      P(10) => \p_1_out__17_n_95\,
      P(9) => \p_1_out__17_n_96\,
      P(8) => \p_1_out__17_n_97\,
      P(7) => \p_1_out__17_n_98\,
      P(6) => \p_1_out__17_n_99\,
      P(5) => \p_1_out__17_n_100\,
      P(4) => \p_1_out__17_n_101\,
      P(3) => \p_1_out__17_n_102\,
      P(2) => \p_1_out__17_n_103\,
      P(1) => \p_1_out__17_n_104\,
      P(0) => \p_1_out__17_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__17_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__17_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__17_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__17_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__17_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__17_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(18),
      I1 => Delay18_out1(18),
      I2 => adc_trigger,
      O => \A__17\(18)
    );
\p_1_out__17_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(17),
      I1 => Delay18_out1(17),
      I2 => adc_trigger,
      O => \A__17\(17)
    );
\p_1_out__17_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(16),
      I1 => Delay18_out1(16),
      I2 => adc_trigger,
      O => \A__17\(16)
    );
\p_1_out__17_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(15),
      I1 => Delay18_out1(15),
      I2 => adc_trigger,
      O => \A__17\(15)
    );
\p_1_out__17_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(14),
      I1 => Delay18_out1(14),
      I2 => adc_trigger,
      O => \A__17\(14)
    );
\p_1_out__17_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(13),
      I1 => Delay18_out1(13),
      I2 => adc_trigger,
      O => \A__17\(13)
    );
\p_1_out__17_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(12),
      I1 => Delay18_out1(12),
      I2 => adc_trigger,
      O => \A__17\(12)
    );
\p_1_out__17_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(11),
      I1 => Delay18_out1(11),
      I2 => adc_trigger,
      O => \A__17\(11)
    );
\p_1_out__17_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(10),
      I1 => Delay18_out1(10),
      I2 => adc_trigger,
      O => \A__17\(10)
    );
\p_1_out__17_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(9),
      I1 => Delay18_out1(9),
      I2 => adc_trigger,
      O => \A__17\(9)
    );
\p_1_out__17_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(26),
      I1 => Delay18_out1(26),
      I2 => adc_trigger,
      O => \A__17\(26)
    );
\p_1_out__17_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(8),
      I1 => Delay18_out1(8),
      I2 => adc_trigger,
      O => \A__17\(8)
    );
\p_1_out__17_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(7),
      I1 => Delay18_out1(7),
      I2 => adc_trigger,
      O => \A__17\(7)
    );
\p_1_out__17_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(6),
      I1 => Delay18_out1(6),
      I2 => adc_trigger,
      O => \A__17\(6)
    );
\p_1_out__17_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(5),
      I1 => Delay18_out1(5),
      I2 => adc_trigger,
      O => \A__17\(5)
    );
\p_1_out__17_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(4),
      I1 => Delay18_out1(4),
      I2 => adc_trigger,
      O => \A__17\(4)
    );
\p_1_out__17_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(3),
      I1 => Delay18_out1(3),
      I2 => adc_trigger,
      O => \A__17\(3)
    );
\p_1_out__17_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(2),
      I1 => Delay18_out1(2),
      I2 => adc_trigger,
      O => \A__17\(2)
    );
\p_1_out__17_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(1),
      I1 => Delay18_out1(1),
      I2 => adc_trigger,
      O => \A__17\(1)
    );
\p_1_out__17_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(0),
      I1 => Delay18_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__17_i_28_n_0\
    );
\p_1_out__17_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(25),
      I1 => Delay18_out1(25),
      I2 => adc_trigger,
      O => \A__17\(25)
    );
\p_1_out__17_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(24),
      I1 => Delay18_out1(24),
      I2 => adc_trigger,
      O => \A__17\(24)
    );
\p_1_out__17_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(23),
      I1 => Delay18_out1(23),
      I2 => adc_trigger,
      O => \A__17\(23)
    );
\p_1_out__17_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(22),
      I1 => Delay18_out1(22),
      I2 => adc_trigger,
      O => \A__17\(22)
    );
\p_1_out__17_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(21),
      I1 => Delay18_out1(21),
      I2 => adc_trigger,
      O => \A__17\(21)
    );
\p_1_out__17_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(20),
      I1 => Delay18_out1(20),
      I2 => adc_trigger,
      O => \A__17\(20)
    );
\p_1_out__17_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in18(19),
      I1 => Delay18_out1(19),
      I2 => adc_trigger,
      O => \A__17\(19)
    );
\p_1_out__18\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__18\(26),
      A(28) => \A__18\(26),
      A(27) => \A__18\(26),
      A(26 downto 1) => \A__18\(26 downto 1),
      A(0) => \p_1_out__18_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__18_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__18_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__18\(26),
      C(46) => \A__18\(26),
      C(45) => \A__18\(26),
      C(44) => \A__18\(26),
      C(43) => \A__18\(26),
      C(42) => \A__18\(26),
      C(41) => \A__18\(26),
      C(40) => \A__18\(26),
      C(39) => \A__18\(26),
      C(38) => \A__18\(26),
      C(37) => \A__18\(26),
      C(36) => \A__18\(26),
      C(35) => \A__18\(26),
      C(34) => \A__18\(26),
      C(33) => \A__18\(26),
      C(32) => \A__18\(26),
      C(31) => \A__18\(26),
      C(30) => \A__18\(26),
      C(29) => \A__18\(26),
      C(28) => \A__18\(26),
      C(27) => \A__18\(26),
      C(26) => \A__18\(26),
      C(25 downto 0) => \A__18\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__18_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__18_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_18,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__18_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out19[17]\(0),
      OPMODE(4) => \out19[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__18_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__18_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__18_n_61\,
      P(43) => \p_1_out__18_n_62\,
      P(42) => \p_1_out__18_n_63\,
      P(41) => \p_1_out__18_n_64\,
      P(40) => \p_1_out__18_n_65\,
      P(39) => \p_1_out__18_n_66\,
      P(38) => \p_1_out__18_n_67\,
      P(37) => \p_1_out__18_n_68\,
      P(36) => \p_1_out__18_n_69\,
      P(35) => \p_1_out__18_n_70\,
      P(34 downto 17) => out19(17 downto 0),
      P(16) => \p_1_out__18_n_89\,
      P(15) => \p_1_out__18_n_90\,
      P(14) => \p_1_out__18_n_91\,
      P(13) => \p_1_out__18_n_92\,
      P(12) => \p_1_out__18_n_93\,
      P(11) => \p_1_out__18_n_94\,
      P(10) => \p_1_out__18_n_95\,
      P(9) => \p_1_out__18_n_96\,
      P(8) => \p_1_out__18_n_97\,
      P(7) => \p_1_out__18_n_98\,
      P(6) => \p_1_out__18_n_99\,
      P(5) => \p_1_out__18_n_100\,
      P(4) => \p_1_out__18_n_101\,
      P(3) => \p_1_out__18_n_102\,
      P(2) => \p_1_out__18_n_103\,
      P(1) => \p_1_out__18_n_104\,
      P(0) => \p_1_out__18_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__18_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__18_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__18_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__18_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__18_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__18_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(18),
      I1 => Delay19_out1(18),
      I2 => adc_trigger,
      O => \A__18\(18)
    );
\p_1_out__18_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(17),
      I1 => Delay19_out1(17),
      I2 => adc_trigger,
      O => \A__18\(17)
    );
\p_1_out__18_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(16),
      I1 => Delay19_out1(16),
      I2 => adc_trigger,
      O => \A__18\(16)
    );
\p_1_out__18_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(15),
      I1 => Delay19_out1(15),
      I2 => adc_trigger,
      O => \A__18\(15)
    );
\p_1_out__18_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(14),
      I1 => Delay19_out1(14),
      I2 => adc_trigger,
      O => \A__18\(14)
    );
\p_1_out__18_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(13),
      I1 => Delay19_out1(13),
      I2 => adc_trigger,
      O => \A__18\(13)
    );
\p_1_out__18_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(12),
      I1 => Delay19_out1(12),
      I2 => adc_trigger,
      O => \A__18\(12)
    );
\p_1_out__18_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(11),
      I1 => Delay19_out1(11),
      I2 => adc_trigger,
      O => \A__18\(11)
    );
\p_1_out__18_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(10),
      I1 => Delay19_out1(10),
      I2 => adc_trigger,
      O => \A__18\(10)
    );
\p_1_out__18_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(9),
      I1 => Delay19_out1(9),
      I2 => adc_trigger,
      O => \A__18\(9)
    );
\p_1_out__18_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(26),
      I1 => Delay19_out1(26),
      I2 => adc_trigger,
      O => \A__18\(26)
    );
\p_1_out__18_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(8),
      I1 => Delay19_out1(8),
      I2 => adc_trigger,
      O => \A__18\(8)
    );
\p_1_out__18_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(7),
      I1 => Delay19_out1(7),
      I2 => adc_trigger,
      O => \A__18\(7)
    );
\p_1_out__18_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(6),
      I1 => Delay19_out1(6),
      I2 => adc_trigger,
      O => \A__18\(6)
    );
\p_1_out__18_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(5),
      I1 => Delay19_out1(5),
      I2 => adc_trigger,
      O => \A__18\(5)
    );
\p_1_out__18_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(4),
      I1 => Delay19_out1(4),
      I2 => adc_trigger,
      O => \A__18\(4)
    );
\p_1_out__18_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(3),
      I1 => Delay19_out1(3),
      I2 => adc_trigger,
      O => \A__18\(3)
    );
\p_1_out__18_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(2),
      I1 => Delay19_out1(2),
      I2 => adc_trigger,
      O => \A__18\(2)
    );
\p_1_out__18_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(1),
      I1 => Delay19_out1(1),
      I2 => adc_trigger,
      O => \A__18\(1)
    );
\p_1_out__18_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(0),
      I1 => Delay19_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__18_i_28_n_0\
    );
\p_1_out__18_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(25),
      I1 => Delay19_out1(25),
      I2 => adc_trigger,
      O => \A__18\(25)
    );
\p_1_out__18_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(24),
      I1 => Delay19_out1(24),
      I2 => adc_trigger,
      O => \A__18\(24)
    );
\p_1_out__18_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(23),
      I1 => Delay19_out1(23),
      I2 => adc_trigger,
      O => \A__18\(23)
    );
\p_1_out__18_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(22),
      I1 => Delay19_out1(22),
      I2 => adc_trigger,
      O => \A__18\(22)
    );
\p_1_out__18_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(21),
      I1 => Delay19_out1(21),
      I2 => adc_trigger,
      O => \A__18\(21)
    );
\p_1_out__18_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(20),
      I1 => Delay19_out1(20),
      I2 => adc_trigger,
      O => \A__18\(20)
    );
\p_1_out__18_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in19(19),
      I1 => Delay19_out1(19),
      I2 => adc_trigger,
      O => \A__18\(19)
    );
\p_1_out__19\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__19\(26),
      A(28) => \A__19\(26),
      A(27) => \A__19\(26),
      A(26 downto 1) => \A__19\(26 downto 1),
      A(0) => \p_1_out__19_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__19_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__19_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__19\(26),
      C(46) => \A__19\(26),
      C(45) => \A__19\(26),
      C(44) => \A__19\(26),
      C(43) => \A__19\(26),
      C(42) => \A__19\(26),
      C(41) => \A__19\(26),
      C(40) => \A__19\(26),
      C(39) => \A__19\(26),
      C(38) => \A__19\(26),
      C(37) => \A__19\(26),
      C(36) => \A__19\(26),
      C(35) => \A__19\(26),
      C(34) => \A__19\(26),
      C(33) => \A__19\(26),
      C(32) => \A__19\(26),
      C(31) => \A__19\(26),
      C(30) => \A__19\(26),
      C(29) => \A__19\(26),
      C(28) => \A__19\(26),
      C(27) => \A__19\(26),
      C(26) => \A__19\(26),
      C(25 downto 0) => \A__19\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__19_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__19_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_19,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__19_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out20[17]\(0),
      OPMODE(4) => \out20[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__19_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__19_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__19_n_61\,
      P(43) => \p_1_out__19_n_62\,
      P(42) => \p_1_out__19_n_63\,
      P(41) => \p_1_out__19_n_64\,
      P(40) => \p_1_out__19_n_65\,
      P(39) => \p_1_out__19_n_66\,
      P(38) => \p_1_out__19_n_67\,
      P(37) => \p_1_out__19_n_68\,
      P(36) => \p_1_out__19_n_69\,
      P(35) => \p_1_out__19_n_70\,
      P(34 downto 17) => out20(17 downto 0),
      P(16) => \p_1_out__19_n_89\,
      P(15) => \p_1_out__19_n_90\,
      P(14) => \p_1_out__19_n_91\,
      P(13) => \p_1_out__19_n_92\,
      P(12) => \p_1_out__19_n_93\,
      P(11) => \p_1_out__19_n_94\,
      P(10) => \p_1_out__19_n_95\,
      P(9) => \p_1_out__19_n_96\,
      P(8) => \p_1_out__19_n_97\,
      P(7) => \p_1_out__19_n_98\,
      P(6) => \p_1_out__19_n_99\,
      P(5) => \p_1_out__19_n_100\,
      P(4) => \p_1_out__19_n_101\,
      P(3) => \p_1_out__19_n_102\,
      P(2) => \p_1_out__19_n_103\,
      P(1) => \p_1_out__19_n_104\,
      P(0) => \p_1_out__19_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__19_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__19_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__19_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__19_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__19_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__19_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(18),
      I1 => Delay20_out1(18),
      I2 => adc_trigger,
      O => \A__19\(18)
    );
\p_1_out__19_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(17),
      I1 => Delay20_out1(17),
      I2 => adc_trigger,
      O => \A__19\(17)
    );
\p_1_out__19_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(16),
      I1 => Delay20_out1(16),
      I2 => adc_trigger,
      O => \A__19\(16)
    );
\p_1_out__19_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(15),
      I1 => Delay20_out1(15),
      I2 => adc_trigger,
      O => \A__19\(15)
    );
\p_1_out__19_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(14),
      I1 => Delay20_out1(14),
      I2 => adc_trigger,
      O => \A__19\(14)
    );
\p_1_out__19_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(13),
      I1 => Delay20_out1(13),
      I2 => adc_trigger,
      O => \A__19\(13)
    );
\p_1_out__19_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(12),
      I1 => Delay20_out1(12),
      I2 => adc_trigger,
      O => \A__19\(12)
    );
\p_1_out__19_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(11),
      I1 => Delay20_out1(11),
      I2 => adc_trigger,
      O => \A__19\(11)
    );
\p_1_out__19_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(10),
      I1 => Delay20_out1(10),
      I2 => adc_trigger,
      O => \A__19\(10)
    );
\p_1_out__19_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(9),
      I1 => Delay20_out1(9),
      I2 => adc_trigger,
      O => \A__19\(9)
    );
\p_1_out__19_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(26),
      I1 => Delay20_out1(26),
      I2 => adc_trigger,
      O => \A__19\(26)
    );
\p_1_out__19_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(8),
      I1 => Delay20_out1(8),
      I2 => adc_trigger,
      O => \A__19\(8)
    );
\p_1_out__19_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(7),
      I1 => Delay20_out1(7),
      I2 => adc_trigger,
      O => \A__19\(7)
    );
\p_1_out__19_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(6),
      I1 => Delay20_out1(6),
      I2 => adc_trigger,
      O => \A__19\(6)
    );
\p_1_out__19_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(5),
      I1 => Delay20_out1(5),
      I2 => adc_trigger,
      O => \A__19\(5)
    );
\p_1_out__19_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(4),
      I1 => Delay20_out1(4),
      I2 => adc_trigger,
      O => \A__19\(4)
    );
\p_1_out__19_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(3),
      I1 => Delay20_out1(3),
      I2 => adc_trigger,
      O => \A__19\(3)
    );
\p_1_out__19_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(2),
      I1 => Delay20_out1(2),
      I2 => adc_trigger,
      O => \A__19\(2)
    );
\p_1_out__19_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(1),
      I1 => Delay20_out1(1),
      I2 => adc_trigger,
      O => \A__19\(1)
    );
\p_1_out__19_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(0),
      I1 => Delay20_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__19_i_28_n_0\
    );
\p_1_out__19_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(25),
      I1 => Delay20_out1(25),
      I2 => adc_trigger,
      O => \A__19\(25)
    );
\p_1_out__19_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(24),
      I1 => Delay20_out1(24),
      I2 => adc_trigger,
      O => \A__19\(24)
    );
\p_1_out__19_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(23),
      I1 => Delay20_out1(23),
      I2 => adc_trigger,
      O => \A__19\(23)
    );
\p_1_out__19_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(22),
      I1 => Delay20_out1(22),
      I2 => adc_trigger,
      O => \A__19\(22)
    );
\p_1_out__19_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(21),
      I1 => Delay20_out1(21),
      I2 => adc_trigger,
      O => \A__19\(21)
    );
\p_1_out__19_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(20),
      I1 => Delay20_out1(20),
      I2 => adc_trigger,
      O => \A__19\(20)
    );
\p_1_out__19_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in20(19),
      I1 => Delay20_out1(19),
      I2 => adc_trigger,
      O => \A__19\(19)
    );
\p_1_out__1_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(18),
      I1 => Delay2_out1(18),
      I2 => adc_trigger,
      O => \A__1\(18)
    );
\p_1_out__1_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(17),
      I1 => Delay2_out1(17),
      I2 => adc_trigger,
      O => \A__1\(17)
    );
\p_1_out__1_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(16),
      I1 => Delay2_out1(16),
      I2 => adc_trigger,
      O => \A__1\(16)
    );
\p_1_out__1_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(15),
      I1 => Delay2_out1(15),
      I2 => adc_trigger,
      O => \A__1\(15)
    );
\p_1_out__1_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(14),
      I1 => Delay2_out1(14),
      I2 => adc_trigger,
      O => \A__1\(14)
    );
\p_1_out__1_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(13),
      I1 => Delay2_out1(13),
      I2 => adc_trigger,
      O => \A__1\(13)
    );
\p_1_out__1_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(12),
      I1 => Delay2_out1(12),
      I2 => adc_trigger,
      O => \A__1\(12)
    );
\p_1_out__1_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(11),
      I1 => Delay2_out1(11),
      I2 => adc_trigger,
      O => \A__1\(11)
    );
\p_1_out__1_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(10),
      I1 => Delay2_out1(10),
      I2 => adc_trigger,
      O => \A__1\(10)
    );
\p_1_out__1_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(9),
      I1 => Delay2_out1(9),
      I2 => adc_trigger,
      O => \A__1\(9)
    );
\p_1_out__1_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(26),
      I1 => Delay2_out1(26),
      I2 => adc_trigger,
      O => \A__1\(26)
    );
\p_1_out__1_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(8),
      I1 => Delay2_out1(8),
      I2 => adc_trigger,
      O => \A__1\(8)
    );
\p_1_out__1_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(7),
      I1 => Delay2_out1(7),
      I2 => adc_trigger,
      O => \A__1\(7)
    );
\p_1_out__1_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(6),
      I1 => Delay2_out1(6),
      I2 => adc_trigger,
      O => \A__1\(6)
    );
\p_1_out__1_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(5),
      I1 => Delay2_out1(5),
      I2 => adc_trigger,
      O => \A__1\(5)
    );
\p_1_out__1_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(4),
      I1 => Delay2_out1(4),
      I2 => adc_trigger,
      O => \A__1\(4)
    );
\p_1_out__1_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(3),
      I1 => Delay2_out1(3),
      I2 => adc_trigger,
      O => \A__1\(3)
    );
\p_1_out__1_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(2),
      I1 => Delay2_out1(2),
      I2 => adc_trigger,
      O => \A__1\(2)
    );
\p_1_out__1_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(1),
      I1 => Delay2_out1(1),
      I2 => adc_trigger,
      O => \A__1\(1)
    );
\p_1_out__1_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(0),
      I1 => Delay2_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__1_i_28_n_0\
    );
\p_1_out__1_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(25),
      I1 => Delay2_out1(25),
      I2 => adc_trigger,
      O => \A__1\(25)
    );
\p_1_out__1_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(24),
      I1 => Delay2_out1(24),
      I2 => adc_trigger,
      O => \A__1\(24)
    );
\p_1_out__1_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(23),
      I1 => Delay2_out1(23),
      I2 => adc_trigger,
      O => \A__1\(23)
    );
\p_1_out__1_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(22),
      I1 => Delay2_out1(22),
      I2 => adc_trigger,
      O => \A__1\(22)
    );
\p_1_out__1_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(21),
      I1 => Delay2_out1(21),
      I2 => adc_trigger,
      O => \A__1\(21)
    );
\p_1_out__1_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(20),
      I1 => Delay2_out1(20),
      I2 => adc_trigger,
      O => \A__1\(20)
    );
\p_1_out__1_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in2(19),
      I1 => Delay2_out1(19),
      I2 => adc_trigger,
      O => \A__1\(19)
    );
\p_1_out__2\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__2\(26),
      A(28) => \A__2\(26),
      A(27) => \A__2\(26),
      A(26 downto 1) => \A__2\(26 downto 1),
      A(0) => \p_1_out__2_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__2_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__2_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__2\(26),
      C(46) => \A__2\(26),
      C(45) => \A__2\(26),
      C(44) => \A__2\(26),
      C(43) => \A__2\(26),
      C(42) => \A__2\(26),
      C(41) => \A__2\(26),
      C(40) => \A__2\(26),
      C(39) => \A__2\(26),
      C(38) => \A__2\(26),
      C(37) => \A__2\(26),
      C(36) => \A__2\(26),
      C(35) => \A__2\(26),
      C(34) => \A__2\(26),
      C(33) => \A__2\(26),
      C(32) => \A__2\(26),
      C(31) => \A__2\(26),
      C(30) => \A__2\(26),
      C(29) => \A__2\(26),
      C(28) => \A__2\(26),
      C(27) => \A__2\(26),
      C(26) => \A__2\(26),
      C(25 downto 0) => \A__2\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__2_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__2_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_2,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__2_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out3[17]\(0),
      OPMODE(4) => \out3[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__2_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__2_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__2_n_61\,
      P(43) => \p_1_out__2_n_62\,
      P(42) => \p_1_out__2_n_63\,
      P(41) => \p_1_out__2_n_64\,
      P(40) => \p_1_out__2_n_65\,
      P(39) => \p_1_out__2_n_66\,
      P(38) => \p_1_out__2_n_67\,
      P(37) => \p_1_out__2_n_68\,
      P(36) => \p_1_out__2_n_69\,
      P(35) => \p_1_out__2_n_70\,
      P(34 downto 17) => out3(17 downto 0),
      P(16) => \p_1_out__2_n_89\,
      P(15) => \p_1_out__2_n_90\,
      P(14) => \p_1_out__2_n_91\,
      P(13) => \p_1_out__2_n_92\,
      P(12) => \p_1_out__2_n_93\,
      P(11) => \p_1_out__2_n_94\,
      P(10) => \p_1_out__2_n_95\,
      P(9) => \p_1_out__2_n_96\,
      P(8) => \p_1_out__2_n_97\,
      P(7) => \p_1_out__2_n_98\,
      P(6) => \p_1_out__2_n_99\,
      P(5) => \p_1_out__2_n_100\,
      P(4) => \p_1_out__2_n_101\,
      P(3) => \p_1_out__2_n_102\,
      P(2) => \p_1_out__2_n_103\,
      P(1) => \p_1_out__2_n_104\,
      P(0) => \p_1_out__2_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__2_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__2_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__2_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__2_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__2_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__20\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__20\(26),
      A(28) => \A__20\(26),
      A(27) => \A__20\(26),
      A(26 downto 1) => \A__20\(26 downto 1),
      A(0) => \p_1_out__20_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__20_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__20_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__20\(26),
      C(46) => \A__20\(26),
      C(45) => \A__20\(26),
      C(44) => \A__20\(26),
      C(43) => \A__20\(26),
      C(42) => \A__20\(26),
      C(41) => \A__20\(26),
      C(40) => \A__20\(26),
      C(39) => \A__20\(26),
      C(38) => \A__20\(26),
      C(37) => \A__20\(26),
      C(36) => \A__20\(26),
      C(35) => \A__20\(26),
      C(34) => \A__20\(26),
      C(33) => \A__20\(26),
      C(32) => \A__20\(26),
      C(31) => \A__20\(26),
      C(30) => \A__20\(26),
      C(29) => \A__20\(26),
      C(28) => \A__20\(26),
      C(27) => \A__20\(26),
      C(26) => \A__20\(26),
      C(25 downto 0) => \A__20\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__20_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__20_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_20,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__20_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out21[17]\(0),
      OPMODE(4) => \out21[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__20_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__20_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__20_n_61\,
      P(43) => \p_1_out__20_n_62\,
      P(42) => \p_1_out__20_n_63\,
      P(41) => \p_1_out__20_n_64\,
      P(40) => \p_1_out__20_n_65\,
      P(39) => \p_1_out__20_n_66\,
      P(38) => \p_1_out__20_n_67\,
      P(37) => \p_1_out__20_n_68\,
      P(36) => \p_1_out__20_n_69\,
      P(35) => \p_1_out__20_n_70\,
      P(34 downto 17) => out21(17 downto 0),
      P(16) => \p_1_out__20_n_89\,
      P(15) => \p_1_out__20_n_90\,
      P(14) => \p_1_out__20_n_91\,
      P(13) => \p_1_out__20_n_92\,
      P(12) => \p_1_out__20_n_93\,
      P(11) => \p_1_out__20_n_94\,
      P(10) => \p_1_out__20_n_95\,
      P(9) => \p_1_out__20_n_96\,
      P(8) => \p_1_out__20_n_97\,
      P(7) => \p_1_out__20_n_98\,
      P(6) => \p_1_out__20_n_99\,
      P(5) => \p_1_out__20_n_100\,
      P(4) => \p_1_out__20_n_101\,
      P(3) => \p_1_out__20_n_102\,
      P(2) => \p_1_out__20_n_103\,
      P(1) => \p_1_out__20_n_104\,
      P(0) => \p_1_out__20_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__20_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__20_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__20_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__20_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__20_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__20_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(18),
      I1 => Delay21_out1(18),
      I2 => adc_trigger,
      O => \A__20\(18)
    );
\p_1_out__20_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(17),
      I1 => Delay21_out1(17),
      I2 => adc_trigger,
      O => \A__20\(17)
    );
\p_1_out__20_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(16),
      I1 => Delay21_out1(16),
      I2 => adc_trigger,
      O => \A__20\(16)
    );
\p_1_out__20_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(15),
      I1 => Delay21_out1(15),
      I2 => adc_trigger,
      O => \A__20\(15)
    );
\p_1_out__20_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(14),
      I1 => Delay21_out1(14),
      I2 => adc_trigger,
      O => \A__20\(14)
    );
\p_1_out__20_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(13),
      I1 => Delay21_out1(13),
      I2 => adc_trigger,
      O => \A__20\(13)
    );
\p_1_out__20_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(12),
      I1 => Delay21_out1(12),
      I2 => adc_trigger,
      O => \A__20\(12)
    );
\p_1_out__20_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(11),
      I1 => Delay21_out1(11),
      I2 => adc_trigger,
      O => \A__20\(11)
    );
\p_1_out__20_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(10),
      I1 => Delay21_out1(10),
      I2 => adc_trigger,
      O => \A__20\(10)
    );
\p_1_out__20_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(9),
      I1 => Delay21_out1(9),
      I2 => adc_trigger,
      O => \A__20\(9)
    );
\p_1_out__20_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(26),
      I1 => Delay21_out1(26),
      I2 => adc_trigger,
      O => \A__20\(26)
    );
\p_1_out__20_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(8),
      I1 => Delay21_out1(8),
      I2 => adc_trigger,
      O => \A__20\(8)
    );
\p_1_out__20_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(7),
      I1 => Delay21_out1(7),
      I2 => adc_trigger,
      O => \A__20\(7)
    );
\p_1_out__20_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(6),
      I1 => Delay21_out1(6),
      I2 => adc_trigger,
      O => \A__20\(6)
    );
\p_1_out__20_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(5),
      I1 => Delay21_out1(5),
      I2 => adc_trigger,
      O => \A__20\(5)
    );
\p_1_out__20_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(4),
      I1 => Delay21_out1(4),
      I2 => adc_trigger,
      O => \A__20\(4)
    );
\p_1_out__20_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(3),
      I1 => Delay21_out1(3),
      I2 => adc_trigger,
      O => \A__20\(3)
    );
\p_1_out__20_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(2),
      I1 => Delay21_out1(2),
      I2 => adc_trigger,
      O => \A__20\(2)
    );
\p_1_out__20_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(1),
      I1 => Delay21_out1(1),
      I2 => adc_trigger,
      O => \A__20\(1)
    );
\p_1_out__20_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(0),
      I1 => Delay21_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__20_i_28_n_0\
    );
\p_1_out__20_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(25),
      I1 => Delay21_out1(25),
      I2 => adc_trigger,
      O => \A__20\(25)
    );
\p_1_out__20_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(24),
      I1 => Delay21_out1(24),
      I2 => adc_trigger,
      O => \A__20\(24)
    );
\p_1_out__20_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(23),
      I1 => Delay21_out1(23),
      I2 => adc_trigger,
      O => \A__20\(23)
    );
\p_1_out__20_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(22),
      I1 => Delay21_out1(22),
      I2 => adc_trigger,
      O => \A__20\(22)
    );
\p_1_out__20_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(21),
      I1 => Delay21_out1(21),
      I2 => adc_trigger,
      O => \A__20\(21)
    );
\p_1_out__20_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(20),
      I1 => Delay21_out1(20),
      I2 => adc_trigger,
      O => \A__20\(20)
    );
\p_1_out__20_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in21(19),
      I1 => Delay21_out1(19),
      I2 => adc_trigger,
      O => \A__20\(19)
    );
\p_1_out__21\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__21\(26),
      A(28) => \A__21\(26),
      A(27) => \A__21\(26),
      A(26 downto 1) => \A__21\(26 downto 1),
      A(0) => \p_1_out__21_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__21_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__21_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__21\(26),
      C(46) => \A__21\(26),
      C(45) => \A__21\(26),
      C(44) => \A__21\(26),
      C(43) => \A__21\(26),
      C(42) => \A__21\(26),
      C(41) => \A__21\(26),
      C(40) => \A__21\(26),
      C(39) => \A__21\(26),
      C(38) => \A__21\(26),
      C(37) => \A__21\(26),
      C(36) => \A__21\(26),
      C(35) => \A__21\(26),
      C(34) => \A__21\(26),
      C(33) => \A__21\(26),
      C(32) => \A__21\(26),
      C(31) => \A__21\(26),
      C(30) => \A__21\(26),
      C(29) => \A__21\(26),
      C(28) => \A__21\(26),
      C(27) => \A__21\(26),
      C(26) => \A__21\(26),
      C(25 downto 0) => \A__21\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__21_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__21_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_21,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__21_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out22[17]\(0),
      OPMODE(4) => \out22[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__21_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__21_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__21_n_61\,
      P(43) => \p_1_out__21_n_62\,
      P(42) => \p_1_out__21_n_63\,
      P(41) => \p_1_out__21_n_64\,
      P(40) => \p_1_out__21_n_65\,
      P(39) => \p_1_out__21_n_66\,
      P(38) => \p_1_out__21_n_67\,
      P(37) => \p_1_out__21_n_68\,
      P(36) => \p_1_out__21_n_69\,
      P(35) => \p_1_out__21_n_70\,
      P(34 downto 17) => out22(17 downto 0),
      P(16) => \p_1_out__21_n_89\,
      P(15) => \p_1_out__21_n_90\,
      P(14) => \p_1_out__21_n_91\,
      P(13) => \p_1_out__21_n_92\,
      P(12) => \p_1_out__21_n_93\,
      P(11) => \p_1_out__21_n_94\,
      P(10) => \p_1_out__21_n_95\,
      P(9) => \p_1_out__21_n_96\,
      P(8) => \p_1_out__21_n_97\,
      P(7) => \p_1_out__21_n_98\,
      P(6) => \p_1_out__21_n_99\,
      P(5) => \p_1_out__21_n_100\,
      P(4) => \p_1_out__21_n_101\,
      P(3) => \p_1_out__21_n_102\,
      P(2) => \p_1_out__21_n_103\,
      P(1) => \p_1_out__21_n_104\,
      P(0) => \p_1_out__21_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__21_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__21_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__21_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__21_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__21_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__21_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(18),
      I1 => Delay22_out1(18),
      I2 => adc_trigger,
      O => \A__21\(18)
    );
\p_1_out__21_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(17),
      I1 => Delay22_out1(17),
      I2 => adc_trigger,
      O => \A__21\(17)
    );
\p_1_out__21_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(16),
      I1 => Delay22_out1(16),
      I2 => adc_trigger,
      O => \A__21\(16)
    );
\p_1_out__21_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(15),
      I1 => Delay22_out1(15),
      I2 => adc_trigger,
      O => \A__21\(15)
    );
\p_1_out__21_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(14),
      I1 => Delay22_out1(14),
      I2 => adc_trigger,
      O => \A__21\(14)
    );
\p_1_out__21_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(13),
      I1 => Delay22_out1(13),
      I2 => adc_trigger,
      O => \A__21\(13)
    );
\p_1_out__21_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(12),
      I1 => Delay22_out1(12),
      I2 => adc_trigger,
      O => \A__21\(12)
    );
\p_1_out__21_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(11),
      I1 => Delay22_out1(11),
      I2 => adc_trigger,
      O => \A__21\(11)
    );
\p_1_out__21_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(10),
      I1 => Delay22_out1(10),
      I2 => adc_trigger,
      O => \A__21\(10)
    );
\p_1_out__21_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(9),
      I1 => Delay22_out1(9),
      I2 => adc_trigger,
      O => \A__21\(9)
    );
\p_1_out__21_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(26),
      I1 => Delay22_out1(26),
      I2 => adc_trigger,
      O => \A__21\(26)
    );
\p_1_out__21_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(8),
      I1 => Delay22_out1(8),
      I2 => adc_trigger,
      O => \A__21\(8)
    );
\p_1_out__21_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(7),
      I1 => Delay22_out1(7),
      I2 => adc_trigger,
      O => \A__21\(7)
    );
\p_1_out__21_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(6),
      I1 => Delay22_out1(6),
      I2 => adc_trigger,
      O => \A__21\(6)
    );
\p_1_out__21_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(5),
      I1 => Delay22_out1(5),
      I2 => adc_trigger,
      O => \A__21\(5)
    );
\p_1_out__21_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(4),
      I1 => Delay22_out1(4),
      I2 => adc_trigger,
      O => \A__21\(4)
    );
\p_1_out__21_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(3),
      I1 => Delay22_out1(3),
      I2 => adc_trigger,
      O => \A__21\(3)
    );
\p_1_out__21_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(2),
      I1 => Delay22_out1(2),
      I2 => adc_trigger,
      O => \A__21\(2)
    );
\p_1_out__21_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(1),
      I1 => Delay22_out1(1),
      I2 => adc_trigger,
      O => \A__21\(1)
    );
\p_1_out__21_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(0),
      I1 => Delay22_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__21_i_28_n_0\
    );
\p_1_out__21_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(25),
      I1 => Delay22_out1(25),
      I2 => adc_trigger,
      O => \A__21\(25)
    );
\p_1_out__21_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(24),
      I1 => Delay22_out1(24),
      I2 => adc_trigger,
      O => \A__21\(24)
    );
\p_1_out__21_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(23),
      I1 => Delay22_out1(23),
      I2 => adc_trigger,
      O => \A__21\(23)
    );
\p_1_out__21_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(22),
      I1 => Delay22_out1(22),
      I2 => adc_trigger,
      O => \A__21\(22)
    );
\p_1_out__21_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(21),
      I1 => Delay22_out1(21),
      I2 => adc_trigger,
      O => \A__21\(21)
    );
\p_1_out__21_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(20),
      I1 => Delay22_out1(20),
      I2 => adc_trigger,
      O => \A__21\(20)
    );
\p_1_out__21_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in22(19),
      I1 => Delay22_out1(19),
      I2 => adc_trigger,
      O => \A__21\(19)
    );
\p_1_out__22\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__22\(26),
      A(28) => \A__22\(26),
      A(27) => \A__22\(26),
      A(26 downto 1) => \A__22\(26 downto 1),
      A(0) => \p_1_out__22_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__22_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__22_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__22\(26),
      C(46) => \A__22\(26),
      C(45) => \A__22\(26),
      C(44) => \A__22\(26),
      C(43) => \A__22\(26),
      C(42) => \A__22\(26),
      C(41) => \A__22\(26),
      C(40) => \A__22\(26),
      C(39) => \A__22\(26),
      C(38) => \A__22\(26),
      C(37) => \A__22\(26),
      C(36) => \A__22\(26),
      C(35) => \A__22\(26),
      C(34) => \A__22\(26),
      C(33) => \A__22\(26),
      C(32) => \A__22\(26),
      C(31) => \A__22\(26),
      C(30) => \A__22\(26),
      C(29) => \A__22\(26),
      C(28) => \A__22\(26),
      C(27) => \A__22\(26),
      C(26) => \A__22\(26),
      C(25 downto 0) => \A__22\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__22_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__22_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_22,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__22_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out23[17]\(0),
      OPMODE(4) => \out23[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__22_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__22_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__22_n_61\,
      P(43) => \p_1_out__22_n_62\,
      P(42) => \p_1_out__22_n_63\,
      P(41) => \p_1_out__22_n_64\,
      P(40) => \p_1_out__22_n_65\,
      P(39) => \p_1_out__22_n_66\,
      P(38) => \p_1_out__22_n_67\,
      P(37) => \p_1_out__22_n_68\,
      P(36) => \p_1_out__22_n_69\,
      P(35) => \p_1_out__22_n_70\,
      P(34 downto 17) => out23(17 downto 0),
      P(16) => \p_1_out__22_n_89\,
      P(15) => \p_1_out__22_n_90\,
      P(14) => \p_1_out__22_n_91\,
      P(13) => \p_1_out__22_n_92\,
      P(12) => \p_1_out__22_n_93\,
      P(11) => \p_1_out__22_n_94\,
      P(10) => \p_1_out__22_n_95\,
      P(9) => \p_1_out__22_n_96\,
      P(8) => \p_1_out__22_n_97\,
      P(7) => \p_1_out__22_n_98\,
      P(6) => \p_1_out__22_n_99\,
      P(5) => \p_1_out__22_n_100\,
      P(4) => \p_1_out__22_n_101\,
      P(3) => \p_1_out__22_n_102\,
      P(2) => \p_1_out__22_n_103\,
      P(1) => \p_1_out__22_n_104\,
      P(0) => \p_1_out__22_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__22_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__22_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__22_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__22_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__22_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__22_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(18),
      I1 => Delay23_out1(18),
      I2 => adc_trigger,
      O => \A__22\(18)
    );
\p_1_out__22_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(17),
      I1 => Delay23_out1(17),
      I2 => adc_trigger,
      O => \A__22\(17)
    );
\p_1_out__22_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(16),
      I1 => Delay23_out1(16),
      I2 => adc_trigger,
      O => \A__22\(16)
    );
\p_1_out__22_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(15),
      I1 => Delay23_out1(15),
      I2 => adc_trigger,
      O => \A__22\(15)
    );
\p_1_out__22_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(14),
      I1 => Delay23_out1(14),
      I2 => adc_trigger,
      O => \A__22\(14)
    );
\p_1_out__22_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(13),
      I1 => Delay23_out1(13),
      I2 => adc_trigger,
      O => \A__22\(13)
    );
\p_1_out__22_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(12),
      I1 => Delay23_out1(12),
      I2 => adc_trigger,
      O => \A__22\(12)
    );
\p_1_out__22_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(11),
      I1 => Delay23_out1(11),
      I2 => adc_trigger,
      O => \A__22\(11)
    );
\p_1_out__22_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(10),
      I1 => Delay23_out1(10),
      I2 => adc_trigger,
      O => \A__22\(10)
    );
\p_1_out__22_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(9),
      I1 => Delay23_out1(9),
      I2 => adc_trigger,
      O => \A__22\(9)
    );
\p_1_out__22_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(26),
      I1 => Delay23_out1(26),
      I2 => adc_trigger,
      O => \A__22\(26)
    );
\p_1_out__22_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(8),
      I1 => Delay23_out1(8),
      I2 => adc_trigger,
      O => \A__22\(8)
    );
\p_1_out__22_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(7),
      I1 => Delay23_out1(7),
      I2 => adc_trigger,
      O => \A__22\(7)
    );
\p_1_out__22_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(6),
      I1 => Delay23_out1(6),
      I2 => adc_trigger,
      O => \A__22\(6)
    );
\p_1_out__22_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(5),
      I1 => Delay23_out1(5),
      I2 => adc_trigger,
      O => \A__22\(5)
    );
\p_1_out__22_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(4),
      I1 => Delay23_out1(4),
      I2 => adc_trigger,
      O => \A__22\(4)
    );
\p_1_out__22_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(3),
      I1 => Delay23_out1(3),
      I2 => adc_trigger,
      O => \A__22\(3)
    );
\p_1_out__22_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(2),
      I1 => Delay23_out1(2),
      I2 => adc_trigger,
      O => \A__22\(2)
    );
\p_1_out__22_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(1),
      I1 => Delay23_out1(1),
      I2 => adc_trigger,
      O => \A__22\(1)
    );
\p_1_out__22_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(0),
      I1 => Delay23_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__22_i_28_n_0\
    );
\p_1_out__22_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(25),
      I1 => Delay23_out1(25),
      I2 => adc_trigger,
      O => \A__22\(25)
    );
\p_1_out__22_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(24),
      I1 => Delay23_out1(24),
      I2 => adc_trigger,
      O => \A__22\(24)
    );
\p_1_out__22_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(23),
      I1 => Delay23_out1(23),
      I2 => adc_trigger,
      O => \A__22\(23)
    );
\p_1_out__22_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(22),
      I1 => Delay23_out1(22),
      I2 => adc_trigger,
      O => \A__22\(22)
    );
\p_1_out__22_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(21),
      I1 => Delay23_out1(21),
      I2 => adc_trigger,
      O => \A__22\(21)
    );
\p_1_out__22_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(20),
      I1 => Delay23_out1(20),
      I2 => adc_trigger,
      O => \A__22\(20)
    );
\p_1_out__22_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in23(19),
      I1 => Delay23_out1(19),
      I2 => adc_trigger,
      O => \A__22\(19)
    );
\p_1_out__23\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__23\(26),
      A(28) => \A__23\(26),
      A(27) => \A__23\(26),
      A(26 downto 1) => \A__23\(26 downto 1),
      A(0) => \p_1_out__23_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__23_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__23_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__23\(26),
      C(46) => \A__23\(26),
      C(45) => \A__23\(26),
      C(44) => \A__23\(26),
      C(43) => \A__23\(26),
      C(42) => \A__23\(26),
      C(41) => \A__23\(26),
      C(40) => \A__23\(26),
      C(39) => \A__23\(26),
      C(38) => \A__23\(26),
      C(37) => \A__23\(26),
      C(36) => \A__23\(26),
      C(35) => \A__23\(26),
      C(34) => \A__23\(26),
      C(33) => \A__23\(26),
      C(32) => \A__23\(26),
      C(31) => \A__23\(26),
      C(30) => \A__23\(26),
      C(29) => \A__23\(26),
      C(28) => \A__23\(26),
      C(27) => \A__23\(26),
      C(26) => \A__23\(26),
      C(25 downto 0) => \A__23\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__23_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__23_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
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
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__23_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out24[17]\(0),
      OPMODE(4) => \out24[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__23_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__23_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__23_n_61\,
      P(43) => \p_1_out__23_n_62\,
      P(42) => \p_1_out__23_n_63\,
      P(41) => \p_1_out__23_n_64\,
      P(40) => \p_1_out__23_n_65\,
      P(39) => \p_1_out__23_n_66\,
      P(38) => \p_1_out__23_n_67\,
      P(37) => \p_1_out__23_n_68\,
      P(36) => \p_1_out__23_n_69\,
      P(35) => \p_1_out__23_n_70\,
      P(34 downto 17) => out24(17 downto 0),
      P(16) => \p_1_out__23_n_89\,
      P(15) => \p_1_out__23_n_90\,
      P(14) => \p_1_out__23_n_91\,
      P(13) => \p_1_out__23_n_92\,
      P(12) => \p_1_out__23_n_93\,
      P(11) => \p_1_out__23_n_94\,
      P(10) => \p_1_out__23_n_95\,
      P(9) => \p_1_out__23_n_96\,
      P(8) => \p_1_out__23_n_97\,
      P(7) => \p_1_out__23_n_98\,
      P(6) => \p_1_out__23_n_99\,
      P(5) => \p_1_out__23_n_100\,
      P(4) => \p_1_out__23_n_101\,
      P(3) => \p_1_out__23_n_102\,
      P(2) => \p_1_out__23_n_103\,
      P(1) => \p_1_out__23_n_104\,
      P(0) => \p_1_out__23_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__23_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__23_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__23_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__23_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__23_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__23_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(18),
      I1 => Delay24_out1(18),
      I2 => adc_trigger,
      O => \A__23\(18)
    );
\p_1_out__23_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(17),
      I1 => Delay24_out1(17),
      I2 => adc_trigger,
      O => \A__23\(17)
    );
\p_1_out__23_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(16),
      I1 => Delay24_out1(16),
      I2 => adc_trigger,
      O => \A__23\(16)
    );
\p_1_out__23_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(15),
      I1 => Delay24_out1(15),
      I2 => adc_trigger,
      O => \A__23\(15)
    );
\p_1_out__23_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(14),
      I1 => Delay24_out1(14),
      I2 => adc_trigger,
      O => \A__23\(14)
    );
\p_1_out__23_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(13),
      I1 => Delay24_out1(13),
      I2 => adc_trigger,
      O => \A__23\(13)
    );
\p_1_out__23_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(12),
      I1 => Delay24_out1(12),
      I2 => adc_trigger,
      O => \A__23\(12)
    );
\p_1_out__23_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(11),
      I1 => Delay24_out1(11),
      I2 => adc_trigger,
      O => \A__23\(11)
    );
\p_1_out__23_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(10),
      I1 => Delay24_out1(10),
      I2 => adc_trigger,
      O => \A__23\(10)
    );
\p_1_out__23_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(9),
      I1 => Delay24_out1(9),
      I2 => adc_trigger,
      O => \A__23\(9)
    );
\p_1_out__23_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(26),
      I1 => Delay24_out1(26),
      I2 => adc_trigger,
      O => \A__23\(26)
    );
\p_1_out__23_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(8),
      I1 => Delay24_out1(8),
      I2 => adc_trigger,
      O => \A__23\(8)
    );
\p_1_out__23_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(7),
      I1 => Delay24_out1(7),
      I2 => adc_trigger,
      O => \A__23\(7)
    );
\p_1_out__23_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(6),
      I1 => Delay24_out1(6),
      I2 => adc_trigger,
      O => \A__23\(6)
    );
\p_1_out__23_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(5),
      I1 => Delay24_out1(5),
      I2 => adc_trigger,
      O => \A__23\(5)
    );
\p_1_out__23_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(4),
      I1 => Delay24_out1(4),
      I2 => adc_trigger,
      O => \A__23\(4)
    );
\p_1_out__23_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(3),
      I1 => Delay24_out1(3),
      I2 => adc_trigger,
      O => \A__23\(3)
    );
\p_1_out__23_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(2),
      I1 => Delay24_out1(2),
      I2 => adc_trigger,
      O => \A__23\(2)
    );
\p_1_out__23_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(1),
      I1 => Delay24_out1(1),
      I2 => adc_trigger,
      O => \A__23\(1)
    );
\p_1_out__23_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(0),
      I1 => Delay24_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__23_i_28_n_0\
    );
\p_1_out__23_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(25),
      I1 => Delay24_out1(25),
      I2 => adc_trigger,
      O => \A__23\(25)
    );
\p_1_out__23_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(24),
      I1 => Delay24_out1(24),
      I2 => adc_trigger,
      O => \A__23\(24)
    );
\p_1_out__23_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(23),
      I1 => Delay24_out1(23),
      I2 => adc_trigger,
      O => \A__23\(23)
    );
\p_1_out__23_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(22),
      I1 => Delay24_out1(22),
      I2 => adc_trigger,
      O => \A__23\(22)
    );
\p_1_out__23_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(21),
      I1 => Delay24_out1(21),
      I2 => adc_trigger,
      O => \A__23\(21)
    );
\p_1_out__23_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(20),
      I1 => Delay24_out1(20),
      I2 => adc_trigger,
      O => \A__23\(20)
    );
\p_1_out__23_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in24(19),
      I1 => Delay24_out1(19),
      I2 => adc_trigger,
      O => \A__23\(19)
    );
\p_1_out__24\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__24\(26),
      A(28) => \A__24\(26),
      A(27) => \A__24\(26),
      A(26 downto 1) => \A__24\(26 downto 1),
      A(0) => \p_1_out__24_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__24_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__24_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__24\(26),
      C(46) => \A__24\(26),
      C(45) => \A__24\(26),
      C(44) => \A__24\(26),
      C(43) => \A__24\(26),
      C(42) => \A__24\(26),
      C(41) => \A__24\(26),
      C(40) => \A__24\(26),
      C(39) => \A__24\(26),
      C(38) => \A__24\(26),
      C(37) => \A__24\(26),
      C(36) => \A__24\(26),
      C(35) => \A__24\(26),
      C(34) => \A__24\(26),
      C(33) => \A__24\(26),
      C(32) => \A__24\(26),
      C(31) => \A__24\(26),
      C(30) => \A__24\(26),
      C(29) => \A__24\(26),
      C(28) => \A__24\(26),
      C(27) => \A__24\(26),
      C(26) => \A__24\(26),
      C(25 downto 0) => \A__24\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__24_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__24_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_23,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__24_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out25[17]\(0),
      OPMODE(4) => \out25[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__24_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__24_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__24_n_61\,
      P(43) => \p_1_out__24_n_62\,
      P(42) => \p_1_out__24_n_63\,
      P(41) => \p_1_out__24_n_64\,
      P(40) => \p_1_out__24_n_65\,
      P(39) => \p_1_out__24_n_66\,
      P(38) => \p_1_out__24_n_67\,
      P(37) => \p_1_out__24_n_68\,
      P(36) => \p_1_out__24_n_69\,
      P(35) => \p_1_out__24_n_70\,
      P(34 downto 17) => out25(17 downto 0),
      P(16) => \p_1_out__24_n_89\,
      P(15) => \p_1_out__24_n_90\,
      P(14) => \p_1_out__24_n_91\,
      P(13) => \p_1_out__24_n_92\,
      P(12) => \p_1_out__24_n_93\,
      P(11) => \p_1_out__24_n_94\,
      P(10) => \p_1_out__24_n_95\,
      P(9) => \p_1_out__24_n_96\,
      P(8) => \p_1_out__24_n_97\,
      P(7) => \p_1_out__24_n_98\,
      P(6) => \p_1_out__24_n_99\,
      P(5) => \p_1_out__24_n_100\,
      P(4) => \p_1_out__24_n_101\,
      P(3) => \p_1_out__24_n_102\,
      P(2) => \p_1_out__24_n_103\,
      P(1) => \p_1_out__24_n_104\,
      P(0) => \p_1_out__24_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__24_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__24_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__24_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__24_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__24_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__24_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(18),
      I1 => Delay25_out1(18),
      I2 => adc_trigger,
      O => \A__24\(18)
    );
\p_1_out__24_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(17),
      I1 => Delay25_out1(17),
      I2 => adc_trigger,
      O => \A__24\(17)
    );
\p_1_out__24_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(16),
      I1 => Delay25_out1(16),
      I2 => adc_trigger,
      O => \A__24\(16)
    );
\p_1_out__24_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(15),
      I1 => Delay25_out1(15),
      I2 => adc_trigger,
      O => \A__24\(15)
    );
\p_1_out__24_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(14),
      I1 => Delay25_out1(14),
      I2 => adc_trigger,
      O => \A__24\(14)
    );
\p_1_out__24_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(13),
      I1 => Delay25_out1(13),
      I2 => adc_trigger,
      O => \A__24\(13)
    );
\p_1_out__24_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(12),
      I1 => Delay25_out1(12),
      I2 => adc_trigger,
      O => \A__24\(12)
    );
\p_1_out__24_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(11),
      I1 => Delay25_out1(11),
      I2 => adc_trigger,
      O => \A__24\(11)
    );
\p_1_out__24_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(10),
      I1 => Delay25_out1(10),
      I2 => adc_trigger,
      O => \A__24\(10)
    );
\p_1_out__24_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(9),
      I1 => Delay25_out1(9),
      I2 => adc_trigger,
      O => \A__24\(9)
    );
\p_1_out__24_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(26),
      I1 => Delay25_out1(26),
      I2 => adc_trigger,
      O => \A__24\(26)
    );
\p_1_out__24_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(8),
      I1 => Delay25_out1(8),
      I2 => adc_trigger,
      O => \A__24\(8)
    );
\p_1_out__24_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(7),
      I1 => Delay25_out1(7),
      I2 => adc_trigger,
      O => \A__24\(7)
    );
\p_1_out__24_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(6),
      I1 => Delay25_out1(6),
      I2 => adc_trigger,
      O => \A__24\(6)
    );
\p_1_out__24_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(5),
      I1 => Delay25_out1(5),
      I2 => adc_trigger,
      O => \A__24\(5)
    );
\p_1_out__24_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(4),
      I1 => Delay25_out1(4),
      I2 => adc_trigger,
      O => \A__24\(4)
    );
\p_1_out__24_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(3),
      I1 => Delay25_out1(3),
      I2 => adc_trigger,
      O => \A__24\(3)
    );
\p_1_out__24_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(2),
      I1 => Delay25_out1(2),
      I2 => adc_trigger,
      O => \A__24\(2)
    );
\p_1_out__24_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(1),
      I1 => Delay25_out1(1),
      I2 => adc_trigger,
      O => \A__24\(1)
    );
\p_1_out__24_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(0),
      I1 => Delay25_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__24_i_28_n_0\
    );
\p_1_out__24_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(25),
      I1 => Delay25_out1(25),
      I2 => adc_trigger,
      O => \A__24\(25)
    );
\p_1_out__24_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(24),
      I1 => Delay25_out1(24),
      I2 => adc_trigger,
      O => \A__24\(24)
    );
\p_1_out__24_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(23),
      I1 => Delay25_out1(23),
      I2 => adc_trigger,
      O => \A__24\(23)
    );
\p_1_out__24_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(22),
      I1 => Delay25_out1(22),
      I2 => adc_trigger,
      O => \A__24\(22)
    );
\p_1_out__24_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(21),
      I1 => Delay25_out1(21),
      I2 => adc_trigger,
      O => \A__24\(21)
    );
\p_1_out__24_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(20),
      I1 => Delay25_out1(20),
      I2 => adc_trigger,
      O => \A__24\(20)
    );
\p_1_out__24_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in25(19),
      I1 => Delay25_out1(19),
      I2 => adc_trigger,
      O => \A__24\(19)
    );
\p_1_out__25\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__25\(26),
      A(28) => \A__25\(26),
      A(27) => \A__25\(26),
      A(26 downto 1) => \A__25\(26 downto 1),
      A(0) => \p_1_out__25_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__25_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__25_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__25\(26),
      C(46) => \A__25\(26),
      C(45) => \A__25\(26),
      C(44) => \A__25\(26),
      C(43) => \A__25\(26),
      C(42) => \A__25\(26),
      C(41) => \A__25\(26),
      C(40) => \A__25\(26),
      C(39) => \A__25\(26),
      C(38) => \A__25\(26),
      C(37) => \A__25\(26),
      C(36) => \A__25\(26),
      C(35) => \A__25\(26),
      C(34) => \A__25\(26),
      C(33) => \A__25\(26),
      C(32) => \A__25\(26),
      C(31) => \A__25\(26),
      C(30) => \A__25\(26),
      C(29) => \A__25\(26),
      C(28) => \A__25\(26),
      C(27) => \A__25\(26),
      C(26) => \A__25\(26),
      C(25 downto 0) => \A__25\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__25_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__25_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_24,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__25_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out26[17]\(0),
      OPMODE(4) => \out26[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__25_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__25_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__25_n_61\,
      P(43) => \p_1_out__25_n_62\,
      P(42) => \p_1_out__25_n_63\,
      P(41) => \p_1_out__25_n_64\,
      P(40) => \p_1_out__25_n_65\,
      P(39) => \p_1_out__25_n_66\,
      P(38) => \p_1_out__25_n_67\,
      P(37) => \p_1_out__25_n_68\,
      P(36) => \p_1_out__25_n_69\,
      P(35) => \p_1_out__25_n_70\,
      P(34 downto 17) => out26(17 downto 0),
      P(16) => \p_1_out__25_n_89\,
      P(15) => \p_1_out__25_n_90\,
      P(14) => \p_1_out__25_n_91\,
      P(13) => \p_1_out__25_n_92\,
      P(12) => \p_1_out__25_n_93\,
      P(11) => \p_1_out__25_n_94\,
      P(10) => \p_1_out__25_n_95\,
      P(9) => \p_1_out__25_n_96\,
      P(8) => \p_1_out__25_n_97\,
      P(7) => \p_1_out__25_n_98\,
      P(6) => \p_1_out__25_n_99\,
      P(5) => \p_1_out__25_n_100\,
      P(4) => \p_1_out__25_n_101\,
      P(3) => \p_1_out__25_n_102\,
      P(2) => \p_1_out__25_n_103\,
      P(1) => \p_1_out__25_n_104\,
      P(0) => \p_1_out__25_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__25_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__25_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__25_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__25_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__25_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__25_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(18),
      I1 => Delay26_out1(18),
      I2 => adc_trigger,
      O => \A__25\(18)
    );
\p_1_out__25_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(17),
      I1 => Delay26_out1(17),
      I2 => adc_trigger,
      O => \A__25\(17)
    );
\p_1_out__25_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(16),
      I1 => Delay26_out1(16),
      I2 => adc_trigger,
      O => \A__25\(16)
    );
\p_1_out__25_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(15),
      I1 => Delay26_out1(15),
      I2 => adc_trigger,
      O => \A__25\(15)
    );
\p_1_out__25_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(14),
      I1 => Delay26_out1(14),
      I2 => adc_trigger,
      O => \A__25\(14)
    );
\p_1_out__25_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(13),
      I1 => Delay26_out1(13),
      I2 => adc_trigger,
      O => \A__25\(13)
    );
\p_1_out__25_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(12),
      I1 => Delay26_out1(12),
      I2 => adc_trigger,
      O => \A__25\(12)
    );
\p_1_out__25_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(11),
      I1 => Delay26_out1(11),
      I2 => adc_trigger,
      O => \A__25\(11)
    );
\p_1_out__25_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(10),
      I1 => Delay26_out1(10),
      I2 => adc_trigger,
      O => \A__25\(10)
    );
\p_1_out__25_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(9),
      I1 => Delay26_out1(9),
      I2 => adc_trigger,
      O => \A__25\(9)
    );
\p_1_out__25_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(26),
      I1 => Delay26_out1(26),
      I2 => adc_trigger,
      O => \A__25\(26)
    );
\p_1_out__25_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(8),
      I1 => Delay26_out1(8),
      I2 => adc_trigger,
      O => \A__25\(8)
    );
\p_1_out__25_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(7),
      I1 => Delay26_out1(7),
      I2 => adc_trigger,
      O => \A__25\(7)
    );
\p_1_out__25_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(6),
      I1 => Delay26_out1(6),
      I2 => adc_trigger,
      O => \A__25\(6)
    );
\p_1_out__25_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(5),
      I1 => Delay26_out1(5),
      I2 => adc_trigger,
      O => \A__25\(5)
    );
\p_1_out__25_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(4),
      I1 => Delay26_out1(4),
      I2 => adc_trigger,
      O => \A__25\(4)
    );
\p_1_out__25_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(3),
      I1 => Delay26_out1(3),
      I2 => adc_trigger,
      O => \A__25\(3)
    );
\p_1_out__25_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(2),
      I1 => Delay26_out1(2),
      I2 => adc_trigger,
      O => \A__25\(2)
    );
\p_1_out__25_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(1),
      I1 => Delay26_out1(1),
      I2 => adc_trigger,
      O => \A__25\(1)
    );
\p_1_out__25_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(0),
      I1 => Delay26_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__25_i_28_n_0\
    );
\p_1_out__25_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(25),
      I1 => Delay26_out1(25),
      I2 => adc_trigger,
      O => \A__25\(25)
    );
\p_1_out__25_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(24),
      I1 => Delay26_out1(24),
      I2 => adc_trigger,
      O => \A__25\(24)
    );
\p_1_out__25_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(23),
      I1 => Delay26_out1(23),
      I2 => adc_trigger,
      O => \A__25\(23)
    );
\p_1_out__25_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(22),
      I1 => Delay26_out1(22),
      I2 => adc_trigger,
      O => \A__25\(22)
    );
\p_1_out__25_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(21),
      I1 => Delay26_out1(21),
      I2 => adc_trigger,
      O => \A__25\(21)
    );
\p_1_out__25_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(20),
      I1 => Delay26_out1(20),
      I2 => adc_trigger,
      O => \A__25\(20)
    );
\p_1_out__25_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in26(19),
      I1 => Delay26_out1(19),
      I2 => adc_trigger,
      O => \A__25\(19)
    );
\p_1_out__26\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__26\(26),
      A(28) => \A__26\(26),
      A(27) => \A__26\(26),
      A(26 downto 1) => \A__26\(26 downto 1),
      A(0) => \p_1_out__26_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__26_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__26_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__26\(26),
      C(46) => \A__26\(26),
      C(45) => \A__26\(26),
      C(44) => \A__26\(26),
      C(43) => \A__26\(26),
      C(42) => \A__26\(26),
      C(41) => \A__26\(26),
      C(40) => \A__26\(26),
      C(39) => \A__26\(26),
      C(38) => \A__26\(26),
      C(37) => \A__26\(26),
      C(36) => \A__26\(26),
      C(35) => \A__26\(26),
      C(34) => \A__26\(26),
      C(33) => \A__26\(26),
      C(32) => \A__26\(26),
      C(31) => \A__26\(26),
      C(30) => \A__26\(26),
      C(29) => \A__26\(26),
      C(28) => \A__26\(26),
      C(27) => \A__26\(26),
      C(26) => \A__26\(26),
      C(25 downto 0) => \A__26\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__26_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__26_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_25,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__26_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out27[17]\(0),
      OPMODE(4) => \out27[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__26_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__26_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__26_n_61\,
      P(43) => \p_1_out__26_n_62\,
      P(42) => \p_1_out__26_n_63\,
      P(41) => \p_1_out__26_n_64\,
      P(40) => \p_1_out__26_n_65\,
      P(39) => \p_1_out__26_n_66\,
      P(38) => \p_1_out__26_n_67\,
      P(37) => \p_1_out__26_n_68\,
      P(36) => \p_1_out__26_n_69\,
      P(35) => \p_1_out__26_n_70\,
      P(34 downto 17) => out27(17 downto 0),
      P(16) => \p_1_out__26_n_89\,
      P(15) => \p_1_out__26_n_90\,
      P(14) => \p_1_out__26_n_91\,
      P(13) => \p_1_out__26_n_92\,
      P(12) => \p_1_out__26_n_93\,
      P(11) => \p_1_out__26_n_94\,
      P(10) => \p_1_out__26_n_95\,
      P(9) => \p_1_out__26_n_96\,
      P(8) => \p_1_out__26_n_97\,
      P(7) => \p_1_out__26_n_98\,
      P(6) => \p_1_out__26_n_99\,
      P(5) => \p_1_out__26_n_100\,
      P(4) => \p_1_out__26_n_101\,
      P(3) => \p_1_out__26_n_102\,
      P(2) => \p_1_out__26_n_103\,
      P(1) => \p_1_out__26_n_104\,
      P(0) => \p_1_out__26_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__26_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__26_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__26_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__26_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__26_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__26_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(18),
      I1 => Delay27_out1(18),
      I2 => adc_trigger,
      O => \A__26\(18)
    );
\p_1_out__26_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(17),
      I1 => Delay27_out1(17),
      I2 => adc_trigger,
      O => \A__26\(17)
    );
\p_1_out__26_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(16),
      I1 => Delay27_out1(16),
      I2 => adc_trigger,
      O => \A__26\(16)
    );
\p_1_out__26_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(15),
      I1 => Delay27_out1(15),
      I2 => adc_trigger,
      O => \A__26\(15)
    );
\p_1_out__26_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(14),
      I1 => Delay27_out1(14),
      I2 => adc_trigger,
      O => \A__26\(14)
    );
\p_1_out__26_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(13),
      I1 => Delay27_out1(13),
      I2 => adc_trigger,
      O => \A__26\(13)
    );
\p_1_out__26_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(12),
      I1 => Delay27_out1(12),
      I2 => adc_trigger,
      O => \A__26\(12)
    );
\p_1_out__26_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(11),
      I1 => Delay27_out1(11),
      I2 => adc_trigger,
      O => \A__26\(11)
    );
\p_1_out__26_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(10),
      I1 => Delay27_out1(10),
      I2 => adc_trigger,
      O => \A__26\(10)
    );
\p_1_out__26_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(9),
      I1 => Delay27_out1(9),
      I2 => adc_trigger,
      O => \A__26\(9)
    );
\p_1_out__26_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(26),
      I1 => Delay27_out1(26),
      I2 => adc_trigger,
      O => \A__26\(26)
    );
\p_1_out__26_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(8),
      I1 => Delay27_out1(8),
      I2 => adc_trigger,
      O => \A__26\(8)
    );
\p_1_out__26_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(7),
      I1 => Delay27_out1(7),
      I2 => adc_trigger,
      O => \A__26\(7)
    );
\p_1_out__26_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(6),
      I1 => Delay27_out1(6),
      I2 => adc_trigger,
      O => \A__26\(6)
    );
\p_1_out__26_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(5),
      I1 => Delay27_out1(5),
      I2 => adc_trigger,
      O => \A__26\(5)
    );
\p_1_out__26_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(4),
      I1 => Delay27_out1(4),
      I2 => adc_trigger,
      O => \A__26\(4)
    );
\p_1_out__26_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(3),
      I1 => Delay27_out1(3),
      I2 => adc_trigger,
      O => \A__26\(3)
    );
\p_1_out__26_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(2),
      I1 => Delay27_out1(2),
      I2 => adc_trigger,
      O => \A__26\(2)
    );
\p_1_out__26_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(1),
      I1 => Delay27_out1(1),
      I2 => adc_trigger,
      O => \A__26\(1)
    );
\p_1_out__26_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(0),
      I1 => Delay27_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__26_i_28_n_0\
    );
\p_1_out__26_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(25),
      I1 => Delay27_out1(25),
      I2 => adc_trigger,
      O => \A__26\(25)
    );
\p_1_out__26_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(24),
      I1 => Delay27_out1(24),
      I2 => adc_trigger,
      O => \A__26\(24)
    );
\p_1_out__26_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(23),
      I1 => Delay27_out1(23),
      I2 => adc_trigger,
      O => \A__26\(23)
    );
\p_1_out__26_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(22),
      I1 => Delay27_out1(22),
      I2 => adc_trigger,
      O => \A__26\(22)
    );
\p_1_out__26_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(21),
      I1 => Delay27_out1(21),
      I2 => adc_trigger,
      O => \A__26\(21)
    );
\p_1_out__26_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(20),
      I1 => Delay27_out1(20),
      I2 => adc_trigger,
      O => \A__26\(20)
    );
\p_1_out__26_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in27(19),
      I1 => Delay27_out1(19),
      I2 => adc_trigger,
      O => \A__26\(19)
    );
\p_1_out__27\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__27\(26),
      A(28) => \A__27\(26),
      A(27) => \A__27\(26),
      A(26 downto 1) => \A__27\(26 downto 1),
      A(0) => \p_1_out__27_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__27_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__27_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__27\(26),
      C(46) => \A__27\(26),
      C(45) => \A__27\(26),
      C(44) => \A__27\(26),
      C(43) => \A__27\(26),
      C(42) => \A__27\(26),
      C(41) => \A__27\(26),
      C(40) => \A__27\(26),
      C(39) => \A__27\(26),
      C(38) => \A__27\(26),
      C(37) => \A__27\(26),
      C(36) => \A__27\(26),
      C(35) => \A__27\(26),
      C(34) => \A__27\(26),
      C(33) => \A__27\(26),
      C(32) => \A__27\(26),
      C(31) => \A__27\(26),
      C(30) => \A__27\(26),
      C(29) => \A__27\(26),
      C(28) => \A__27\(26),
      C(27) => \A__27\(26),
      C(26) => \A__27\(26),
      C(25 downto 0) => \A__27\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__27_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__27_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_26,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__27_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out28[17]\(0),
      OPMODE(4) => \out28[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__27_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__27_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__27_n_61\,
      P(43) => \p_1_out__27_n_62\,
      P(42) => \p_1_out__27_n_63\,
      P(41) => \p_1_out__27_n_64\,
      P(40) => \p_1_out__27_n_65\,
      P(39) => \p_1_out__27_n_66\,
      P(38) => \p_1_out__27_n_67\,
      P(37) => \p_1_out__27_n_68\,
      P(36) => \p_1_out__27_n_69\,
      P(35) => \p_1_out__27_n_70\,
      P(34 downto 17) => out28(17 downto 0),
      P(16) => \p_1_out__27_n_89\,
      P(15) => \p_1_out__27_n_90\,
      P(14) => \p_1_out__27_n_91\,
      P(13) => \p_1_out__27_n_92\,
      P(12) => \p_1_out__27_n_93\,
      P(11) => \p_1_out__27_n_94\,
      P(10) => \p_1_out__27_n_95\,
      P(9) => \p_1_out__27_n_96\,
      P(8) => \p_1_out__27_n_97\,
      P(7) => \p_1_out__27_n_98\,
      P(6) => \p_1_out__27_n_99\,
      P(5) => \p_1_out__27_n_100\,
      P(4) => \p_1_out__27_n_101\,
      P(3) => \p_1_out__27_n_102\,
      P(2) => \p_1_out__27_n_103\,
      P(1) => \p_1_out__27_n_104\,
      P(0) => \p_1_out__27_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__27_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__27_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__27_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__27_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__27_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__27_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(18),
      I1 => Delay28_out1(18),
      I2 => adc_trigger,
      O => \A__27\(18)
    );
\p_1_out__27_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(17),
      I1 => Delay28_out1(17),
      I2 => adc_trigger,
      O => \A__27\(17)
    );
\p_1_out__27_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(16),
      I1 => Delay28_out1(16),
      I2 => adc_trigger,
      O => \A__27\(16)
    );
\p_1_out__27_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(15),
      I1 => Delay28_out1(15),
      I2 => adc_trigger,
      O => \A__27\(15)
    );
\p_1_out__27_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(14),
      I1 => Delay28_out1(14),
      I2 => adc_trigger,
      O => \A__27\(14)
    );
\p_1_out__27_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(13),
      I1 => Delay28_out1(13),
      I2 => adc_trigger,
      O => \A__27\(13)
    );
\p_1_out__27_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(12),
      I1 => Delay28_out1(12),
      I2 => adc_trigger,
      O => \A__27\(12)
    );
\p_1_out__27_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(11),
      I1 => Delay28_out1(11),
      I2 => adc_trigger,
      O => \A__27\(11)
    );
\p_1_out__27_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(10),
      I1 => Delay28_out1(10),
      I2 => adc_trigger,
      O => \A__27\(10)
    );
\p_1_out__27_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(9),
      I1 => Delay28_out1(9),
      I2 => adc_trigger,
      O => \A__27\(9)
    );
\p_1_out__27_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(26),
      I1 => Delay28_out1(26),
      I2 => adc_trigger,
      O => \A__27\(26)
    );
\p_1_out__27_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(8),
      I1 => Delay28_out1(8),
      I2 => adc_trigger,
      O => \A__27\(8)
    );
\p_1_out__27_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(7),
      I1 => Delay28_out1(7),
      I2 => adc_trigger,
      O => \A__27\(7)
    );
\p_1_out__27_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(6),
      I1 => Delay28_out1(6),
      I2 => adc_trigger,
      O => \A__27\(6)
    );
\p_1_out__27_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(5),
      I1 => Delay28_out1(5),
      I2 => adc_trigger,
      O => \A__27\(5)
    );
\p_1_out__27_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(4),
      I1 => Delay28_out1(4),
      I2 => adc_trigger,
      O => \A__27\(4)
    );
\p_1_out__27_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(3),
      I1 => Delay28_out1(3),
      I2 => adc_trigger,
      O => \A__27\(3)
    );
\p_1_out__27_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(2),
      I1 => Delay28_out1(2),
      I2 => adc_trigger,
      O => \A__27\(2)
    );
\p_1_out__27_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(1),
      I1 => Delay28_out1(1),
      I2 => adc_trigger,
      O => \A__27\(1)
    );
\p_1_out__27_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(0),
      I1 => Delay28_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__27_i_28_n_0\
    );
\p_1_out__27_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(25),
      I1 => Delay28_out1(25),
      I2 => adc_trigger,
      O => \A__27\(25)
    );
\p_1_out__27_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(24),
      I1 => Delay28_out1(24),
      I2 => adc_trigger,
      O => \A__27\(24)
    );
\p_1_out__27_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(23),
      I1 => Delay28_out1(23),
      I2 => adc_trigger,
      O => \A__27\(23)
    );
\p_1_out__27_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(22),
      I1 => Delay28_out1(22),
      I2 => adc_trigger,
      O => \A__27\(22)
    );
\p_1_out__27_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(21),
      I1 => Delay28_out1(21),
      I2 => adc_trigger,
      O => \A__27\(21)
    );
\p_1_out__27_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(20),
      I1 => Delay28_out1(20),
      I2 => adc_trigger,
      O => \A__27\(20)
    );
\p_1_out__27_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in28(19),
      I1 => Delay28_out1(19),
      I2 => adc_trigger,
      O => \A__27\(19)
    );
\p_1_out__28\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__28\(26),
      A(28) => \A__28\(26),
      A(27) => \A__28\(26),
      A(26 downto 1) => \A__28\(26 downto 1),
      A(0) => \p_1_out__28_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__28_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__28_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__28\(26),
      C(46) => \A__28\(26),
      C(45) => \A__28\(26),
      C(44) => \A__28\(26),
      C(43) => \A__28\(26),
      C(42) => \A__28\(26),
      C(41) => \A__28\(26),
      C(40) => \A__28\(26),
      C(39) => \A__28\(26),
      C(38) => \A__28\(26),
      C(37) => \A__28\(26),
      C(36) => \A__28\(26),
      C(35) => \A__28\(26),
      C(34) => \A__28\(26),
      C(33) => \A__28\(26),
      C(32) => \A__28\(26),
      C(31) => \A__28\(26),
      C(30) => \A__28\(26),
      C(29) => \A__28\(26),
      C(28) => \A__28\(26),
      C(27) => \A__28\(26),
      C(26) => \A__28\(26),
      C(25 downto 0) => \A__28\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__28_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__28_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_27,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__28_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out29[17]\(0),
      OPMODE(4) => \out29[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__28_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__28_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__28_n_61\,
      P(43) => \p_1_out__28_n_62\,
      P(42) => \p_1_out__28_n_63\,
      P(41) => \p_1_out__28_n_64\,
      P(40) => \p_1_out__28_n_65\,
      P(39) => \p_1_out__28_n_66\,
      P(38) => \p_1_out__28_n_67\,
      P(37) => \p_1_out__28_n_68\,
      P(36) => \p_1_out__28_n_69\,
      P(35) => \p_1_out__28_n_70\,
      P(34 downto 17) => out29(17 downto 0),
      P(16) => \p_1_out__28_n_89\,
      P(15) => \p_1_out__28_n_90\,
      P(14) => \p_1_out__28_n_91\,
      P(13) => \p_1_out__28_n_92\,
      P(12) => \p_1_out__28_n_93\,
      P(11) => \p_1_out__28_n_94\,
      P(10) => \p_1_out__28_n_95\,
      P(9) => \p_1_out__28_n_96\,
      P(8) => \p_1_out__28_n_97\,
      P(7) => \p_1_out__28_n_98\,
      P(6) => \p_1_out__28_n_99\,
      P(5) => \p_1_out__28_n_100\,
      P(4) => \p_1_out__28_n_101\,
      P(3) => \p_1_out__28_n_102\,
      P(2) => \p_1_out__28_n_103\,
      P(1) => \p_1_out__28_n_104\,
      P(0) => \p_1_out__28_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__28_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__28_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__28_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__28_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__28_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__28_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(18),
      I1 => Delay29_out1(18),
      I2 => adc_trigger,
      O => \A__28\(18)
    );
\p_1_out__28_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(17),
      I1 => Delay29_out1(17),
      I2 => adc_trigger,
      O => \A__28\(17)
    );
\p_1_out__28_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(16),
      I1 => Delay29_out1(16),
      I2 => adc_trigger,
      O => \A__28\(16)
    );
\p_1_out__28_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(15),
      I1 => Delay29_out1(15),
      I2 => adc_trigger,
      O => \A__28\(15)
    );
\p_1_out__28_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(14),
      I1 => Delay29_out1(14),
      I2 => adc_trigger,
      O => \A__28\(14)
    );
\p_1_out__28_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(13),
      I1 => Delay29_out1(13),
      I2 => adc_trigger,
      O => \A__28\(13)
    );
\p_1_out__28_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(12),
      I1 => Delay29_out1(12),
      I2 => adc_trigger,
      O => \A__28\(12)
    );
\p_1_out__28_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(11),
      I1 => Delay29_out1(11),
      I2 => adc_trigger,
      O => \A__28\(11)
    );
\p_1_out__28_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(10),
      I1 => Delay29_out1(10),
      I2 => adc_trigger,
      O => \A__28\(10)
    );
\p_1_out__28_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(9),
      I1 => Delay29_out1(9),
      I2 => adc_trigger,
      O => \A__28\(9)
    );
\p_1_out__28_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(26),
      I1 => Delay29_out1(26),
      I2 => adc_trigger,
      O => \A__28\(26)
    );
\p_1_out__28_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(8),
      I1 => Delay29_out1(8),
      I2 => adc_trigger,
      O => \A__28\(8)
    );
\p_1_out__28_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(7),
      I1 => Delay29_out1(7),
      I2 => adc_trigger,
      O => \A__28\(7)
    );
\p_1_out__28_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(6),
      I1 => Delay29_out1(6),
      I2 => adc_trigger,
      O => \A__28\(6)
    );
\p_1_out__28_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(5),
      I1 => Delay29_out1(5),
      I2 => adc_trigger,
      O => \A__28\(5)
    );
\p_1_out__28_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(4),
      I1 => Delay29_out1(4),
      I2 => adc_trigger,
      O => \A__28\(4)
    );
\p_1_out__28_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(3),
      I1 => Delay29_out1(3),
      I2 => adc_trigger,
      O => \A__28\(3)
    );
\p_1_out__28_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(2),
      I1 => Delay29_out1(2),
      I2 => adc_trigger,
      O => \A__28\(2)
    );
\p_1_out__28_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(1),
      I1 => Delay29_out1(1),
      I2 => adc_trigger,
      O => \A__28\(1)
    );
\p_1_out__28_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(0),
      I1 => Delay29_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__28_i_28_n_0\
    );
\p_1_out__28_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(25),
      I1 => Delay29_out1(25),
      I2 => adc_trigger,
      O => \A__28\(25)
    );
\p_1_out__28_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(24),
      I1 => Delay29_out1(24),
      I2 => adc_trigger,
      O => \A__28\(24)
    );
\p_1_out__28_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(23),
      I1 => Delay29_out1(23),
      I2 => adc_trigger,
      O => \A__28\(23)
    );
\p_1_out__28_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(22),
      I1 => Delay29_out1(22),
      I2 => adc_trigger,
      O => \A__28\(22)
    );
\p_1_out__28_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(21),
      I1 => Delay29_out1(21),
      I2 => adc_trigger,
      O => \A__28\(21)
    );
\p_1_out__28_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(20),
      I1 => Delay29_out1(20),
      I2 => adc_trigger,
      O => \A__28\(20)
    );
\p_1_out__28_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in29(19),
      I1 => Delay29_out1(19),
      I2 => adc_trigger,
      O => \A__28\(19)
    );
\p_1_out__29\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__29\(26),
      A(28) => \A__29\(26),
      A(27) => \A__29\(26),
      A(26 downto 1) => \A__29\(26 downto 1),
      A(0) => \p_1_out__29_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__29_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__29_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__29\(26),
      C(46) => \A__29\(26),
      C(45) => \A__29\(26),
      C(44) => \A__29\(26),
      C(43) => \A__29\(26),
      C(42) => \A__29\(26),
      C(41) => \A__29\(26),
      C(40) => \A__29\(26),
      C(39) => \A__29\(26),
      C(38) => \A__29\(26),
      C(37) => \A__29\(26),
      C(36) => \A__29\(26),
      C(35) => \A__29\(26),
      C(34) => \A__29\(26),
      C(33) => \A__29\(26),
      C(32) => \A__29\(26),
      C(31) => \A__29\(26),
      C(30) => \A__29\(26),
      C(29) => \A__29\(26),
      C(28) => \A__29\(26),
      C(27) => \A__29\(26),
      C(26) => \A__29\(26),
      C(25 downto 0) => \A__29\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__29_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__29_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_28,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__29_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out30[17]\(0),
      OPMODE(4) => \out30[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__29_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__29_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__29_n_61\,
      P(43) => \p_1_out__29_n_62\,
      P(42) => \p_1_out__29_n_63\,
      P(41) => \p_1_out__29_n_64\,
      P(40) => \p_1_out__29_n_65\,
      P(39) => \p_1_out__29_n_66\,
      P(38) => \p_1_out__29_n_67\,
      P(37) => \p_1_out__29_n_68\,
      P(36) => \p_1_out__29_n_69\,
      P(35) => \p_1_out__29_n_70\,
      P(34 downto 17) => out30(17 downto 0),
      P(16) => \p_1_out__29_n_89\,
      P(15) => \p_1_out__29_n_90\,
      P(14) => \p_1_out__29_n_91\,
      P(13) => \p_1_out__29_n_92\,
      P(12) => \p_1_out__29_n_93\,
      P(11) => \p_1_out__29_n_94\,
      P(10) => \p_1_out__29_n_95\,
      P(9) => \p_1_out__29_n_96\,
      P(8) => \p_1_out__29_n_97\,
      P(7) => \p_1_out__29_n_98\,
      P(6) => \p_1_out__29_n_99\,
      P(5) => \p_1_out__29_n_100\,
      P(4) => \p_1_out__29_n_101\,
      P(3) => \p_1_out__29_n_102\,
      P(2) => \p_1_out__29_n_103\,
      P(1) => \p_1_out__29_n_104\,
      P(0) => \p_1_out__29_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__29_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__29_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__29_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__29_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__29_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__29_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(18),
      I1 => Delay30_out1(18),
      I2 => adc_trigger,
      O => \A__29\(18)
    );
\p_1_out__29_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(17),
      I1 => Delay30_out1(17),
      I2 => adc_trigger,
      O => \A__29\(17)
    );
\p_1_out__29_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(16),
      I1 => Delay30_out1(16),
      I2 => adc_trigger,
      O => \A__29\(16)
    );
\p_1_out__29_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(15),
      I1 => Delay30_out1(15),
      I2 => adc_trigger,
      O => \A__29\(15)
    );
\p_1_out__29_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(14),
      I1 => Delay30_out1(14),
      I2 => adc_trigger,
      O => \A__29\(14)
    );
\p_1_out__29_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(13),
      I1 => Delay30_out1(13),
      I2 => adc_trigger,
      O => \A__29\(13)
    );
\p_1_out__29_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(12),
      I1 => Delay30_out1(12),
      I2 => adc_trigger,
      O => \A__29\(12)
    );
\p_1_out__29_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(11),
      I1 => Delay30_out1(11),
      I2 => adc_trigger,
      O => \A__29\(11)
    );
\p_1_out__29_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(10),
      I1 => Delay30_out1(10),
      I2 => adc_trigger,
      O => \A__29\(10)
    );
\p_1_out__29_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(9),
      I1 => Delay30_out1(9),
      I2 => adc_trigger,
      O => \A__29\(9)
    );
\p_1_out__29_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(26),
      I1 => Delay30_out1(26),
      I2 => adc_trigger,
      O => \A__29\(26)
    );
\p_1_out__29_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(8),
      I1 => Delay30_out1(8),
      I2 => adc_trigger,
      O => \A__29\(8)
    );
\p_1_out__29_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(7),
      I1 => Delay30_out1(7),
      I2 => adc_trigger,
      O => \A__29\(7)
    );
\p_1_out__29_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(6),
      I1 => Delay30_out1(6),
      I2 => adc_trigger,
      O => \A__29\(6)
    );
\p_1_out__29_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(5),
      I1 => Delay30_out1(5),
      I2 => adc_trigger,
      O => \A__29\(5)
    );
\p_1_out__29_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(4),
      I1 => Delay30_out1(4),
      I2 => adc_trigger,
      O => \A__29\(4)
    );
\p_1_out__29_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(3),
      I1 => Delay30_out1(3),
      I2 => adc_trigger,
      O => \A__29\(3)
    );
\p_1_out__29_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(2),
      I1 => Delay30_out1(2),
      I2 => adc_trigger,
      O => \A__29\(2)
    );
\p_1_out__29_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(1),
      I1 => Delay30_out1(1),
      I2 => adc_trigger,
      O => \A__29\(1)
    );
\p_1_out__29_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(0),
      I1 => Delay30_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__29_i_28_n_0\
    );
\p_1_out__29_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(25),
      I1 => Delay30_out1(25),
      I2 => adc_trigger,
      O => \A__29\(25)
    );
\p_1_out__29_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(24),
      I1 => Delay30_out1(24),
      I2 => adc_trigger,
      O => \A__29\(24)
    );
\p_1_out__29_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(23),
      I1 => Delay30_out1(23),
      I2 => adc_trigger,
      O => \A__29\(23)
    );
\p_1_out__29_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(22),
      I1 => Delay30_out1(22),
      I2 => adc_trigger,
      O => \A__29\(22)
    );
\p_1_out__29_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(21),
      I1 => Delay30_out1(21),
      I2 => adc_trigger,
      O => \A__29\(21)
    );
\p_1_out__29_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(20),
      I1 => Delay30_out1(20),
      I2 => adc_trigger,
      O => \A__29\(20)
    );
\p_1_out__29_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in30(19),
      I1 => Delay30_out1(19),
      I2 => adc_trigger,
      O => \A__29\(19)
    );
\p_1_out__2_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(18),
      I1 => Delay3_out1(18),
      I2 => adc_trigger,
      O => \A__2\(18)
    );
\p_1_out__2_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(17),
      I1 => Delay3_out1(17),
      I2 => adc_trigger,
      O => \A__2\(17)
    );
\p_1_out__2_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(16),
      I1 => Delay3_out1(16),
      I2 => adc_trigger,
      O => \A__2\(16)
    );
\p_1_out__2_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(15),
      I1 => Delay3_out1(15),
      I2 => adc_trigger,
      O => \A__2\(15)
    );
\p_1_out__2_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(14),
      I1 => Delay3_out1(14),
      I2 => adc_trigger,
      O => \A__2\(14)
    );
\p_1_out__2_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(13),
      I1 => Delay3_out1(13),
      I2 => adc_trigger,
      O => \A__2\(13)
    );
\p_1_out__2_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(12),
      I1 => Delay3_out1(12),
      I2 => adc_trigger,
      O => \A__2\(12)
    );
\p_1_out__2_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(11),
      I1 => Delay3_out1(11),
      I2 => adc_trigger,
      O => \A__2\(11)
    );
\p_1_out__2_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(10),
      I1 => Delay3_out1(10),
      I2 => adc_trigger,
      O => \A__2\(10)
    );
\p_1_out__2_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(9),
      I1 => Delay3_out1(9),
      I2 => adc_trigger,
      O => \A__2\(9)
    );
\p_1_out__2_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(26),
      I1 => Delay3_out1(26),
      I2 => adc_trigger,
      O => \A__2\(26)
    );
\p_1_out__2_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(8),
      I1 => Delay3_out1(8),
      I2 => adc_trigger,
      O => \A__2\(8)
    );
\p_1_out__2_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(7),
      I1 => Delay3_out1(7),
      I2 => adc_trigger,
      O => \A__2\(7)
    );
\p_1_out__2_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(6),
      I1 => Delay3_out1(6),
      I2 => adc_trigger,
      O => \A__2\(6)
    );
\p_1_out__2_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(5),
      I1 => Delay3_out1(5),
      I2 => adc_trigger,
      O => \A__2\(5)
    );
\p_1_out__2_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(4),
      I1 => Delay3_out1(4),
      I2 => adc_trigger,
      O => \A__2\(4)
    );
\p_1_out__2_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(3),
      I1 => Delay3_out1(3),
      I2 => adc_trigger,
      O => \A__2\(3)
    );
\p_1_out__2_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(2),
      I1 => Delay3_out1(2),
      I2 => adc_trigger,
      O => \A__2\(2)
    );
\p_1_out__2_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(1),
      I1 => Delay3_out1(1),
      I2 => adc_trigger,
      O => \A__2\(1)
    );
\p_1_out__2_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(0),
      I1 => Delay3_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__2_i_28_n_0\
    );
\p_1_out__2_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(25),
      I1 => Delay3_out1(25),
      I2 => adc_trigger,
      O => \A__2\(25)
    );
\p_1_out__2_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(24),
      I1 => Delay3_out1(24),
      I2 => adc_trigger,
      O => \A__2\(24)
    );
\p_1_out__2_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(23),
      I1 => Delay3_out1(23),
      I2 => adc_trigger,
      O => \A__2\(23)
    );
\p_1_out__2_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(22),
      I1 => Delay3_out1(22),
      I2 => adc_trigger,
      O => \A__2\(22)
    );
\p_1_out__2_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(21),
      I1 => Delay3_out1(21),
      I2 => adc_trigger,
      O => \A__2\(21)
    );
\p_1_out__2_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(20),
      I1 => Delay3_out1(20),
      I2 => adc_trigger,
      O => \A__2\(20)
    );
\p_1_out__2_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in3(19),
      I1 => Delay3_out1(19),
      I2 => adc_trigger,
      O => \A__2\(19)
    );
\p_1_out__3\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__3\(26),
      A(28) => \A__3\(26),
      A(27) => \A__3\(26),
      A(26 downto 1) => \A__3\(26 downto 1),
      A(0) => \p_1_out__3_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__3_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__3_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__3\(26),
      C(46) => \A__3\(26),
      C(45) => \A__3\(26),
      C(44) => \A__3\(26),
      C(43) => \A__3\(26),
      C(42) => \A__3\(26),
      C(41) => \A__3\(26),
      C(40) => \A__3\(26),
      C(39) => \A__3\(26),
      C(38) => \A__3\(26),
      C(37) => \A__3\(26),
      C(36) => \A__3\(26),
      C(35) => \A__3\(26),
      C(34) => \A__3\(26),
      C(33) => \A__3\(26),
      C(32) => \A__3\(26),
      C(31) => \A__3\(26),
      C(30) => \A__3\(26),
      C(29) => \A__3\(26),
      C(28) => \A__3\(26),
      C(27) => \A__3\(26),
      C(26) => \A__3\(26),
      C(25 downto 0) => \A__3\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__3_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__3_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_3,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__3_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out4[17]\(0),
      OPMODE(4) => \out4[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__3_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__3_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__3_n_61\,
      P(43) => \p_1_out__3_n_62\,
      P(42) => \p_1_out__3_n_63\,
      P(41) => \p_1_out__3_n_64\,
      P(40) => \p_1_out__3_n_65\,
      P(39) => \p_1_out__3_n_66\,
      P(38) => \p_1_out__3_n_67\,
      P(37) => \p_1_out__3_n_68\,
      P(36) => \p_1_out__3_n_69\,
      P(35) => \p_1_out__3_n_70\,
      P(34 downto 17) => out4(17 downto 0),
      P(16) => \p_1_out__3_n_89\,
      P(15) => \p_1_out__3_n_90\,
      P(14) => \p_1_out__3_n_91\,
      P(13) => \p_1_out__3_n_92\,
      P(12) => \p_1_out__3_n_93\,
      P(11) => \p_1_out__3_n_94\,
      P(10) => \p_1_out__3_n_95\,
      P(9) => \p_1_out__3_n_96\,
      P(8) => \p_1_out__3_n_97\,
      P(7) => \p_1_out__3_n_98\,
      P(6) => \p_1_out__3_n_99\,
      P(5) => \p_1_out__3_n_100\,
      P(4) => \p_1_out__3_n_101\,
      P(3) => \p_1_out__3_n_102\,
      P(2) => \p_1_out__3_n_103\,
      P(1) => \p_1_out__3_n_104\,
      P(0) => \p_1_out__3_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__3_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__3_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__3_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__3_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__3_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__30\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__30\(26),
      A(28) => \A__30\(26),
      A(27) => \A__30\(26),
      A(26 downto 1) => \A__30\(26 downto 1),
      A(0) => \p_1_out__30_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__30_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__30_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__30\(26),
      C(46) => \A__30\(26),
      C(45) => \A__30\(26),
      C(44) => \A__30\(26),
      C(43) => \A__30\(26),
      C(42) => \A__30\(26),
      C(41) => \A__30\(26),
      C(40) => \A__30\(26),
      C(39) => \A__30\(26),
      C(38) => \A__30\(26),
      C(37) => \A__30\(26),
      C(36) => \A__30\(26),
      C(35) => \A__30\(26),
      C(34) => \A__30\(26),
      C(33) => \A__30\(26),
      C(32) => \A__30\(26),
      C(31) => \A__30\(26),
      C(30) => \A__30\(26),
      C(29) => \A__30\(26),
      C(28) => \A__30\(26),
      C(27) => \A__30\(26),
      C(26) => \A__30\(26),
      C(25 downto 0) => \A__30\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__30_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__30_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_29,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__30_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out31[17]\(0),
      OPMODE(4) => \out31[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__30_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__30_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__30_n_61\,
      P(43) => \p_1_out__30_n_62\,
      P(42) => \p_1_out__30_n_63\,
      P(41) => \p_1_out__30_n_64\,
      P(40) => \p_1_out__30_n_65\,
      P(39) => \p_1_out__30_n_66\,
      P(38) => \p_1_out__30_n_67\,
      P(37) => \p_1_out__30_n_68\,
      P(36) => \p_1_out__30_n_69\,
      P(35) => \p_1_out__30_n_70\,
      P(34 downto 17) => out31(17 downto 0),
      P(16) => \p_1_out__30_n_89\,
      P(15) => \p_1_out__30_n_90\,
      P(14) => \p_1_out__30_n_91\,
      P(13) => \p_1_out__30_n_92\,
      P(12) => \p_1_out__30_n_93\,
      P(11) => \p_1_out__30_n_94\,
      P(10) => \p_1_out__30_n_95\,
      P(9) => \p_1_out__30_n_96\,
      P(8) => \p_1_out__30_n_97\,
      P(7) => \p_1_out__30_n_98\,
      P(6) => \p_1_out__30_n_99\,
      P(5) => \p_1_out__30_n_100\,
      P(4) => \p_1_out__30_n_101\,
      P(3) => \p_1_out__30_n_102\,
      P(2) => \p_1_out__30_n_103\,
      P(1) => \p_1_out__30_n_104\,
      P(0) => \p_1_out__30_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__30_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__30_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__30_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__30_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__30_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__30_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(18),
      I1 => Delay31_out1(18),
      I2 => adc_trigger,
      O => \A__30\(18)
    );
\p_1_out__30_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(17),
      I1 => Delay31_out1(17),
      I2 => adc_trigger,
      O => \A__30\(17)
    );
\p_1_out__30_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(16),
      I1 => Delay31_out1(16),
      I2 => adc_trigger,
      O => \A__30\(16)
    );
\p_1_out__30_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(15),
      I1 => Delay31_out1(15),
      I2 => adc_trigger,
      O => \A__30\(15)
    );
\p_1_out__30_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(14),
      I1 => Delay31_out1(14),
      I2 => adc_trigger,
      O => \A__30\(14)
    );
\p_1_out__30_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(13),
      I1 => Delay31_out1(13),
      I2 => adc_trigger,
      O => \A__30\(13)
    );
\p_1_out__30_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(12),
      I1 => Delay31_out1(12),
      I2 => adc_trigger,
      O => \A__30\(12)
    );
\p_1_out__30_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(11),
      I1 => Delay31_out1(11),
      I2 => adc_trigger,
      O => \A__30\(11)
    );
\p_1_out__30_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(10),
      I1 => Delay31_out1(10),
      I2 => adc_trigger,
      O => \A__30\(10)
    );
\p_1_out__30_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(9),
      I1 => Delay31_out1(9),
      I2 => adc_trigger,
      O => \A__30\(9)
    );
\p_1_out__30_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(26),
      I1 => Delay31_out1(26),
      I2 => adc_trigger,
      O => \A__30\(26)
    );
\p_1_out__30_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(8),
      I1 => Delay31_out1(8),
      I2 => adc_trigger,
      O => \A__30\(8)
    );
\p_1_out__30_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(7),
      I1 => Delay31_out1(7),
      I2 => adc_trigger,
      O => \A__30\(7)
    );
\p_1_out__30_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(6),
      I1 => Delay31_out1(6),
      I2 => adc_trigger,
      O => \A__30\(6)
    );
\p_1_out__30_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(5),
      I1 => Delay31_out1(5),
      I2 => adc_trigger,
      O => \A__30\(5)
    );
\p_1_out__30_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(4),
      I1 => Delay31_out1(4),
      I2 => adc_trigger,
      O => \A__30\(4)
    );
\p_1_out__30_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(3),
      I1 => Delay31_out1(3),
      I2 => adc_trigger,
      O => \A__30\(3)
    );
\p_1_out__30_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(2),
      I1 => Delay31_out1(2),
      I2 => adc_trigger,
      O => \A__30\(2)
    );
\p_1_out__30_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(1),
      I1 => Delay31_out1(1),
      I2 => adc_trigger,
      O => \A__30\(1)
    );
\p_1_out__30_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(0),
      I1 => Delay31_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__30_i_28_n_0\
    );
\p_1_out__30_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(25),
      I1 => Delay31_out1(25),
      I2 => adc_trigger,
      O => \A__30\(25)
    );
\p_1_out__30_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(24),
      I1 => Delay31_out1(24),
      I2 => adc_trigger,
      O => \A__30\(24)
    );
\p_1_out__30_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(23),
      I1 => Delay31_out1(23),
      I2 => adc_trigger,
      O => \A__30\(23)
    );
\p_1_out__30_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(22),
      I1 => Delay31_out1(22),
      I2 => adc_trigger,
      O => \A__30\(22)
    );
\p_1_out__30_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(21),
      I1 => Delay31_out1(21),
      I2 => adc_trigger,
      O => \A__30\(21)
    );
\p_1_out__30_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(20),
      I1 => Delay31_out1(20),
      I2 => adc_trigger,
      O => \A__30\(20)
    );
\p_1_out__30_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in31(19),
      I1 => Delay31_out1(19),
      I2 => adc_trigger,
      O => \A__30\(19)
    );
\p_1_out__3_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(18),
      I1 => Delay4_out1(18),
      I2 => adc_trigger,
      O => \A__3\(18)
    );
\p_1_out__3_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(17),
      I1 => Delay4_out1(17),
      I2 => adc_trigger,
      O => \A__3\(17)
    );
\p_1_out__3_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(16),
      I1 => Delay4_out1(16),
      I2 => adc_trigger,
      O => \A__3\(16)
    );
\p_1_out__3_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(15),
      I1 => Delay4_out1(15),
      I2 => adc_trigger,
      O => \A__3\(15)
    );
\p_1_out__3_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(14),
      I1 => Delay4_out1(14),
      I2 => adc_trigger,
      O => \A__3\(14)
    );
\p_1_out__3_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(13),
      I1 => Delay4_out1(13),
      I2 => adc_trigger,
      O => \A__3\(13)
    );
\p_1_out__3_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(12),
      I1 => Delay4_out1(12),
      I2 => adc_trigger,
      O => \A__3\(12)
    );
\p_1_out__3_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(11),
      I1 => Delay4_out1(11),
      I2 => adc_trigger,
      O => \A__3\(11)
    );
\p_1_out__3_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(10),
      I1 => Delay4_out1(10),
      I2 => adc_trigger,
      O => \A__3\(10)
    );
\p_1_out__3_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(9),
      I1 => Delay4_out1(9),
      I2 => adc_trigger,
      O => \A__3\(9)
    );
\p_1_out__3_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(26),
      I1 => Delay4_out1(26),
      I2 => adc_trigger,
      O => \A__3\(26)
    );
\p_1_out__3_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(8),
      I1 => Delay4_out1(8),
      I2 => adc_trigger,
      O => \A__3\(8)
    );
\p_1_out__3_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(7),
      I1 => Delay4_out1(7),
      I2 => adc_trigger,
      O => \A__3\(7)
    );
\p_1_out__3_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(6),
      I1 => Delay4_out1(6),
      I2 => adc_trigger,
      O => \A__3\(6)
    );
\p_1_out__3_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(5),
      I1 => Delay4_out1(5),
      I2 => adc_trigger,
      O => \A__3\(5)
    );
\p_1_out__3_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(4),
      I1 => Delay4_out1(4),
      I2 => adc_trigger,
      O => \A__3\(4)
    );
\p_1_out__3_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(3),
      I1 => Delay4_out1(3),
      I2 => adc_trigger,
      O => \A__3\(3)
    );
\p_1_out__3_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(2),
      I1 => Delay4_out1(2),
      I2 => adc_trigger,
      O => \A__3\(2)
    );
\p_1_out__3_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(1),
      I1 => Delay4_out1(1),
      I2 => adc_trigger,
      O => \A__3\(1)
    );
\p_1_out__3_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(0),
      I1 => Delay4_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__3_i_28_n_0\
    );
\p_1_out__3_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(25),
      I1 => Delay4_out1(25),
      I2 => adc_trigger,
      O => \A__3\(25)
    );
\p_1_out__3_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(24),
      I1 => Delay4_out1(24),
      I2 => adc_trigger,
      O => \A__3\(24)
    );
\p_1_out__3_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(23),
      I1 => Delay4_out1(23),
      I2 => adc_trigger,
      O => \A__3\(23)
    );
\p_1_out__3_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(22),
      I1 => Delay4_out1(22),
      I2 => adc_trigger,
      O => \A__3\(22)
    );
\p_1_out__3_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(21),
      I1 => Delay4_out1(21),
      I2 => adc_trigger,
      O => \A__3\(21)
    );
\p_1_out__3_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(20),
      I1 => Delay4_out1(20),
      I2 => adc_trigger,
      O => \A__3\(20)
    );
\p_1_out__3_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in4(19),
      I1 => Delay4_out1(19),
      I2 => adc_trigger,
      O => \A__3\(19)
    );
\p_1_out__4\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__4\(26),
      A(28) => \A__4\(26),
      A(27) => \A__4\(26),
      A(26 downto 1) => \A__4\(26 downto 1),
      A(0) => \p_1_out__4_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__4_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__4_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__4\(26),
      C(46) => \A__4\(26),
      C(45) => \A__4\(26),
      C(44) => \A__4\(26),
      C(43) => \A__4\(26),
      C(42) => \A__4\(26),
      C(41) => \A__4\(26),
      C(40) => \A__4\(26),
      C(39) => \A__4\(26),
      C(38) => \A__4\(26),
      C(37) => \A__4\(26),
      C(36) => \A__4\(26),
      C(35) => \A__4\(26),
      C(34) => \A__4\(26),
      C(33) => \A__4\(26),
      C(32) => \A__4\(26),
      C(31) => \A__4\(26),
      C(30) => \A__4\(26),
      C(29) => \A__4\(26),
      C(28) => \A__4\(26),
      C(27) => \A__4\(26),
      C(26) => \A__4\(26),
      C(25 downto 0) => \A__4\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__4_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__4_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_4,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__4_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out5[17]\(0),
      OPMODE(4) => \out5[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__4_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__4_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__4_n_61\,
      P(43) => \p_1_out__4_n_62\,
      P(42) => \p_1_out__4_n_63\,
      P(41) => \p_1_out__4_n_64\,
      P(40) => \p_1_out__4_n_65\,
      P(39) => \p_1_out__4_n_66\,
      P(38) => \p_1_out__4_n_67\,
      P(37) => \p_1_out__4_n_68\,
      P(36) => \p_1_out__4_n_69\,
      P(35) => \p_1_out__4_n_70\,
      P(34 downto 17) => out5(17 downto 0),
      P(16) => \p_1_out__4_n_89\,
      P(15) => \p_1_out__4_n_90\,
      P(14) => \p_1_out__4_n_91\,
      P(13) => \p_1_out__4_n_92\,
      P(12) => \p_1_out__4_n_93\,
      P(11) => \p_1_out__4_n_94\,
      P(10) => \p_1_out__4_n_95\,
      P(9) => \p_1_out__4_n_96\,
      P(8) => \p_1_out__4_n_97\,
      P(7) => \p_1_out__4_n_98\,
      P(6) => \p_1_out__4_n_99\,
      P(5) => \p_1_out__4_n_100\,
      P(4) => \p_1_out__4_n_101\,
      P(3) => \p_1_out__4_n_102\,
      P(2) => \p_1_out__4_n_103\,
      P(1) => \p_1_out__4_n_104\,
      P(0) => \p_1_out__4_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__4_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__4_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__4_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__4_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__4_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__4_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(18),
      I1 => Delay5_out1(18),
      I2 => adc_trigger,
      O => \A__4\(18)
    );
\p_1_out__4_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(17),
      I1 => Delay5_out1(17),
      I2 => adc_trigger,
      O => \A__4\(17)
    );
\p_1_out__4_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(16),
      I1 => Delay5_out1(16),
      I2 => adc_trigger,
      O => \A__4\(16)
    );
\p_1_out__4_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(15),
      I1 => Delay5_out1(15),
      I2 => adc_trigger,
      O => \A__4\(15)
    );
\p_1_out__4_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(14),
      I1 => Delay5_out1(14),
      I2 => adc_trigger,
      O => \A__4\(14)
    );
\p_1_out__4_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(13),
      I1 => Delay5_out1(13),
      I2 => adc_trigger,
      O => \A__4\(13)
    );
\p_1_out__4_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(12),
      I1 => Delay5_out1(12),
      I2 => adc_trigger,
      O => \A__4\(12)
    );
\p_1_out__4_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(11),
      I1 => Delay5_out1(11),
      I2 => adc_trigger,
      O => \A__4\(11)
    );
\p_1_out__4_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(10),
      I1 => Delay5_out1(10),
      I2 => adc_trigger,
      O => \A__4\(10)
    );
\p_1_out__4_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(9),
      I1 => Delay5_out1(9),
      I2 => adc_trigger,
      O => \A__4\(9)
    );
\p_1_out__4_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(26),
      I1 => Delay5_out1(26),
      I2 => adc_trigger,
      O => \A__4\(26)
    );
\p_1_out__4_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(8),
      I1 => Delay5_out1(8),
      I2 => adc_trigger,
      O => \A__4\(8)
    );
\p_1_out__4_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(7),
      I1 => Delay5_out1(7),
      I2 => adc_trigger,
      O => \A__4\(7)
    );
\p_1_out__4_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(6),
      I1 => Delay5_out1(6),
      I2 => adc_trigger,
      O => \A__4\(6)
    );
\p_1_out__4_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(5),
      I1 => Delay5_out1(5),
      I2 => adc_trigger,
      O => \A__4\(5)
    );
\p_1_out__4_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(4),
      I1 => Delay5_out1(4),
      I2 => adc_trigger,
      O => \A__4\(4)
    );
\p_1_out__4_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(3),
      I1 => Delay5_out1(3),
      I2 => adc_trigger,
      O => \A__4\(3)
    );
\p_1_out__4_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(2),
      I1 => Delay5_out1(2),
      I2 => adc_trigger,
      O => \A__4\(2)
    );
\p_1_out__4_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(1),
      I1 => Delay5_out1(1),
      I2 => adc_trigger,
      O => \A__4\(1)
    );
\p_1_out__4_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(0),
      I1 => Delay5_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__4_i_28_n_0\
    );
\p_1_out__4_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(25),
      I1 => Delay5_out1(25),
      I2 => adc_trigger,
      O => \A__4\(25)
    );
\p_1_out__4_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(24),
      I1 => Delay5_out1(24),
      I2 => adc_trigger,
      O => \A__4\(24)
    );
\p_1_out__4_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(23),
      I1 => Delay5_out1(23),
      I2 => adc_trigger,
      O => \A__4\(23)
    );
\p_1_out__4_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(22),
      I1 => Delay5_out1(22),
      I2 => adc_trigger,
      O => \A__4\(22)
    );
\p_1_out__4_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(21),
      I1 => Delay5_out1(21),
      I2 => adc_trigger,
      O => \A__4\(21)
    );
\p_1_out__4_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(20),
      I1 => Delay5_out1(20),
      I2 => adc_trigger,
      O => \A__4\(20)
    );
\p_1_out__4_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in5(19),
      I1 => Delay5_out1(19),
      I2 => adc_trigger,
      O => \A__4\(19)
    );
\p_1_out__5\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__5\(26),
      A(28) => \A__5\(26),
      A(27) => \A__5\(26),
      A(26 downto 1) => \A__5\(26 downto 1),
      A(0) => \p_1_out__5_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__5_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__5_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__5\(26),
      C(46) => \A__5\(26),
      C(45) => \A__5\(26),
      C(44) => \A__5\(26),
      C(43) => \A__5\(26),
      C(42) => \A__5\(26),
      C(41) => \A__5\(26),
      C(40) => \A__5\(26),
      C(39) => \A__5\(26),
      C(38) => \A__5\(26),
      C(37) => \A__5\(26),
      C(36) => \A__5\(26),
      C(35) => \A__5\(26),
      C(34) => \A__5\(26),
      C(33) => \A__5\(26),
      C(32) => \A__5\(26),
      C(31) => \A__5\(26),
      C(30) => \A__5\(26),
      C(29) => \A__5\(26),
      C(28) => \A__5\(26),
      C(27) => \A__5\(26),
      C(26) => \A__5\(26),
      C(25 downto 0) => \A__5\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__5_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__5_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_5,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__5_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out6[17]\(0),
      OPMODE(4) => \out6[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__5_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__5_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__5_n_61\,
      P(43) => \p_1_out__5_n_62\,
      P(42) => \p_1_out__5_n_63\,
      P(41) => \p_1_out__5_n_64\,
      P(40) => \p_1_out__5_n_65\,
      P(39) => \p_1_out__5_n_66\,
      P(38) => \p_1_out__5_n_67\,
      P(37) => \p_1_out__5_n_68\,
      P(36) => \p_1_out__5_n_69\,
      P(35) => \p_1_out__5_n_70\,
      P(34 downto 17) => out6(17 downto 0),
      P(16) => \p_1_out__5_n_89\,
      P(15) => \p_1_out__5_n_90\,
      P(14) => \p_1_out__5_n_91\,
      P(13) => \p_1_out__5_n_92\,
      P(12) => \p_1_out__5_n_93\,
      P(11) => \p_1_out__5_n_94\,
      P(10) => \p_1_out__5_n_95\,
      P(9) => \p_1_out__5_n_96\,
      P(8) => \p_1_out__5_n_97\,
      P(7) => \p_1_out__5_n_98\,
      P(6) => \p_1_out__5_n_99\,
      P(5) => \p_1_out__5_n_100\,
      P(4) => \p_1_out__5_n_101\,
      P(3) => \p_1_out__5_n_102\,
      P(2) => \p_1_out__5_n_103\,
      P(1) => \p_1_out__5_n_104\,
      P(0) => \p_1_out__5_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__5_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__5_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__5_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__5_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__5_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__5_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(18),
      I1 => Delay6_out1(18),
      I2 => adc_trigger,
      O => \A__5\(18)
    );
\p_1_out__5_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(17),
      I1 => Delay6_out1(17),
      I2 => adc_trigger,
      O => \A__5\(17)
    );
\p_1_out__5_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(16),
      I1 => Delay6_out1(16),
      I2 => adc_trigger,
      O => \A__5\(16)
    );
\p_1_out__5_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(15),
      I1 => Delay6_out1(15),
      I2 => adc_trigger,
      O => \A__5\(15)
    );
\p_1_out__5_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(14),
      I1 => Delay6_out1(14),
      I2 => adc_trigger,
      O => \A__5\(14)
    );
\p_1_out__5_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(13),
      I1 => Delay6_out1(13),
      I2 => adc_trigger,
      O => \A__5\(13)
    );
\p_1_out__5_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(12),
      I1 => Delay6_out1(12),
      I2 => adc_trigger,
      O => \A__5\(12)
    );
\p_1_out__5_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(11),
      I1 => Delay6_out1(11),
      I2 => adc_trigger,
      O => \A__5\(11)
    );
\p_1_out__5_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(10),
      I1 => Delay6_out1(10),
      I2 => adc_trigger,
      O => \A__5\(10)
    );
\p_1_out__5_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(9),
      I1 => Delay6_out1(9),
      I2 => adc_trigger,
      O => \A__5\(9)
    );
\p_1_out__5_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(26),
      I1 => Delay6_out1(26),
      I2 => adc_trigger,
      O => \A__5\(26)
    );
\p_1_out__5_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(8),
      I1 => Delay6_out1(8),
      I2 => adc_trigger,
      O => \A__5\(8)
    );
\p_1_out__5_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(7),
      I1 => Delay6_out1(7),
      I2 => adc_trigger,
      O => \A__5\(7)
    );
\p_1_out__5_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(6),
      I1 => Delay6_out1(6),
      I2 => adc_trigger,
      O => \A__5\(6)
    );
\p_1_out__5_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(5),
      I1 => Delay6_out1(5),
      I2 => adc_trigger,
      O => \A__5\(5)
    );
\p_1_out__5_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(4),
      I1 => Delay6_out1(4),
      I2 => adc_trigger,
      O => \A__5\(4)
    );
\p_1_out__5_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(3),
      I1 => Delay6_out1(3),
      I2 => adc_trigger,
      O => \A__5\(3)
    );
\p_1_out__5_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(2),
      I1 => Delay6_out1(2),
      I2 => adc_trigger,
      O => \A__5\(2)
    );
\p_1_out__5_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(1),
      I1 => Delay6_out1(1),
      I2 => adc_trigger,
      O => \A__5\(1)
    );
\p_1_out__5_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(0),
      I1 => Delay6_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__5_i_28_n_0\
    );
\p_1_out__5_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(25),
      I1 => Delay6_out1(25),
      I2 => adc_trigger,
      O => \A__5\(25)
    );
\p_1_out__5_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(24),
      I1 => Delay6_out1(24),
      I2 => adc_trigger,
      O => \A__5\(24)
    );
\p_1_out__5_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(23),
      I1 => Delay6_out1(23),
      I2 => adc_trigger,
      O => \A__5\(23)
    );
\p_1_out__5_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(22),
      I1 => Delay6_out1(22),
      I2 => adc_trigger,
      O => \A__5\(22)
    );
\p_1_out__5_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(21),
      I1 => Delay6_out1(21),
      I2 => adc_trigger,
      O => \A__5\(21)
    );
\p_1_out__5_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(20),
      I1 => Delay6_out1(20),
      I2 => adc_trigger,
      O => \A__5\(20)
    );
\p_1_out__5_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in6(19),
      I1 => Delay6_out1(19),
      I2 => adc_trigger,
      O => \A__5\(19)
    );
\p_1_out__6\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__6\(26),
      A(28) => \A__6\(26),
      A(27) => \A__6\(26),
      A(26 downto 1) => \A__6\(26 downto 1),
      A(0) => \p_1_out__6_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__6_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__6_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__6\(26),
      C(46) => \A__6\(26),
      C(45) => \A__6\(26),
      C(44) => \A__6\(26),
      C(43) => \A__6\(26),
      C(42) => \A__6\(26),
      C(41) => \A__6\(26),
      C(40) => \A__6\(26),
      C(39) => \A__6\(26),
      C(38) => \A__6\(26),
      C(37) => \A__6\(26),
      C(36) => \A__6\(26),
      C(35) => \A__6\(26),
      C(34) => \A__6\(26),
      C(33) => \A__6\(26),
      C(32) => \A__6\(26),
      C(31) => \A__6\(26),
      C(30) => \A__6\(26),
      C(29) => \A__6\(26),
      C(28) => \A__6\(26),
      C(27) => \A__6\(26),
      C(26) => \A__6\(26),
      C(25 downto 0) => \A__6\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__6_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__6_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_6,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__6_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out7[17]\(0),
      OPMODE(4) => \out7[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__6_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__6_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__6_n_61\,
      P(43) => \p_1_out__6_n_62\,
      P(42) => \p_1_out__6_n_63\,
      P(41) => \p_1_out__6_n_64\,
      P(40) => \p_1_out__6_n_65\,
      P(39) => \p_1_out__6_n_66\,
      P(38) => \p_1_out__6_n_67\,
      P(37) => \p_1_out__6_n_68\,
      P(36) => \p_1_out__6_n_69\,
      P(35) => \p_1_out__6_n_70\,
      P(34 downto 17) => out7(17 downto 0),
      P(16) => \p_1_out__6_n_89\,
      P(15) => \p_1_out__6_n_90\,
      P(14) => \p_1_out__6_n_91\,
      P(13) => \p_1_out__6_n_92\,
      P(12) => \p_1_out__6_n_93\,
      P(11) => \p_1_out__6_n_94\,
      P(10) => \p_1_out__6_n_95\,
      P(9) => \p_1_out__6_n_96\,
      P(8) => \p_1_out__6_n_97\,
      P(7) => \p_1_out__6_n_98\,
      P(6) => \p_1_out__6_n_99\,
      P(5) => \p_1_out__6_n_100\,
      P(4) => \p_1_out__6_n_101\,
      P(3) => \p_1_out__6_n_102\,
      P(2) => \p_1_out__6_n_103\,
      P(1) => \p_1_out__6_n_104\,
      P(0) => \p_1_out__6_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__6_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__6_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__6_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__6_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__6_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__6_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(18),
      I1 => Delay7_out1(18),
      I2 => adc_trigger,
      O => \A__6\(18)
    );
\p_1_out__6_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(17),
      I1 => Delay7_out1(17),
      I2 => adc_trigger,
      O => \A__6\(17)
    );
\p_1_out__6_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(16),
      I1 => Delay7_out1(16),
      I2 => adc_trigger,
      O => \A__6\(16)
    );
\p_1_out__6_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(15),
      I1 => Delay7_out1(15),
      I2 => adc_trigger,
      O => \A__6\(15)
    );
\p_1_out__6_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(14),
      I1 => Delay7_out1(14),
      I2 => adc_trigger,
      O => \A__6\(14)
    );
\p_1_out__6_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(13),
      I1 => Delay7_out1(13),
      I2 => adc_trigger,
      O => \A__6\(13)
    );
\p_1_out__6_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(12),
      I1 => Delay7_out1(12),
      I2 => adc_trigger,
      O => \A__6\(12)
    );
\p_1_out__6_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(11),
      I1 => Delay7_out1(11),
      I2 => adc_trigger,
      O => \A__6\(11)
    );
\p_1_out__6_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(10),
      I1 => Delay7_out1(10),
      I2 => adc_trigger,
      O => \A__6\(10)
    );
\p_1_out__6_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(9),
      I1 => Delay7_out1(9),
      I2 => adc_trigger,
      O => \A__6\(9)
    );
\p_1_out__6_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(26),
      I1 => Delay7_out1(26),
      I2 => adc_trigger,
      O => \A__6\(26)
    );
\p_1_out__6_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(8),
      I1 => Delay7_out1(8),
      I2 => adc_trigger,
      O => \A__6\(8)
    );
\p_1_out__6_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(7),
      I1 => Delay7_out1(7),
      I2 => adc_trigger,
      O => \A__6\(7)
    );
\p_1_out__6_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(6),
      I1 => Delay7_out1(6),
      I2 => adc_trigger,
      O => \A__6\(6)
    );
\p_1_out__6_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(5),
      I1 => Delay7_out1(5),
      I2 => adc_trigger,
      O => \A__6\(5)
    );
\p_1_out__6_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(4),
      I1 => Delay7_out1(4),
      I2 => adc_trigger,
      O => \A__6\(4)
    );
\p_1_out__6_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(3),
      I1 => Delay7_out1(3),
      I2 => adc_trigger,
      O => \A__6\(3)
    );
\p_1_out__6_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(2),
      I1 => Delay7_out1(2),
      I2 => adc_trigger,
      O => \A__6\(2)
    );
\p_1_out__6_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(1),
      I1 => Delay7_out1(1),
      I2 => adc_trigger,
      O => \A__6\(1)
    );
\p_1_out__6_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(0),
      I1 => Delay7_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__6_i_28_n_0\
    );
\p_1_out__6_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(25),
      I1 => Delay7_out1(25),
      I2 => adc_trigger,
      O => \A__6\(25)
    );
\p_1_out__6_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(24),
      I1 => Delay7_out1(24),
      I2 => adc_trigger,
      O => \A__6\(24)
    );
\p_1_out__6_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(23),
      I1 => Delay7_out1(23),
      I2 => adc_trigger,
      O => \A__6\(23)
    );
\p_1_out__6_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(22),
      I1 => Delay7_out1(22),
      I2 => adc_trigger,
      O => \A__6\(22)
    );
\p_1_out__6_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(21),
      I1 => Delay7_out1(21),
      I2 => adc_trigger,
      O => \A__6\(21)
    );
\p_1_out__6_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(20),
      I1 => Delay7_out1(20),
      I2 => adc_trigger,
      O => \A__6\(20)
    );
\p_1_out__6_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in7(19),
      I1 => Delay7_out1(19),
      I2 => adc_trigger,
      O => \A__6\(19)
    );
\p_1_out__7\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__7\(26),
      A(28) => \A__7\(26),
      A(27) => \A__7\(26),
      A(26 downto 1) => \A__7\(26 downto 1),
      A(0) => \p_1_out__7_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__7_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__7_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__7\(26),
      C(46) => \A__7\(26),
      C(45) => \A__7\(26),
      C(44) => \A__7\(26),
      C(43) => \A__7\(26),
      C(42) => \A__7\(26),
      C(41) => \A__7\(26),
      C(40) => \A__7\(26),
      C(39) => \A__7\(26),
      C(38) => \A__7\(26),
      C(37) => \A__7\(26),
      C(36) => \A__7\(26),
      C(35) => \A__7\(26),
      C(34) => \A__7\(26),
      C(33) => \A__7\(26),
      C(32) => \A__7\(26),
      C(31) => \A__7\(26),
      C(30) => \A__7\(26),
      C(29) => \A__7\(26),
      C(28) => \A__7\(26),
      C(27) => \A__7\(26),
      C(26) => \A__7\(26),
      C(25 downto 0) => \A__7\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__7_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__7_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_7,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__7_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out8[17]\(0),
      OPMODE(4) => \out8[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__7_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__7_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__7_n_61\,
      P(43) => \p_1_out__7_n_62\,
      P(42) => \p_1_out__7_n_63\,
      P(41) => \p_1_out__7_n_64\,
      P(40) => \p_1_out__7_n_65\,
      P(39) => \p_1_out__7_n_66\,
      P(38) => \p_1_out__7_n_67\,
      P(37) => \p_1_out__7_n_68\,
      P(36) => \p_1_out__7_n_69\,
      P(35) => \p_1_out__7_n_70\,
      P(34 downto 17) => out8(17 downto 0),
      P(16) => \p_1_out__7_n_89\,
      P(15) => \p_1_out__7_n_90\,
      P(14) => \p_1_out__7_n_91\,
      P(13) => \p_1_out__7_n_92\,
      P(12) => \p_1_out__7_n_93\,
      P(11) => \p_1_out__7_n_94\,
      P(10) => \p_1_out__7_n_95\,
      P(9) => \p_1_out__7_n_96\,
      P(8) => \p_1_out__7_n_97\,
      P(7) => \p_1_out__7_n_98\,
      P(6) => \p_1_out__7_n_99\,
      P(5) => \p_1_out__7_n_100\,
      P(4) => \p_1_out__7_n_101\,
      P(3) => \p_1_out__7_n_102\,
      P(2) => \p_1_out__7_n_103\,
      P(1) => \p_1_out__7_n_104\,
      P(0) => \p_1_out__7_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__7_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__7_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__7_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__7_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__7_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__7_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(18),
      I1 => Delay8_out1(18),
      I2 => adc_trigger,
      O => \A__7\(18)
    );
\p_1_out__7_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(17),
      I1 => Delay8_out1(17),
      I2 => adc_trigger,
      O => \A__7\(17)
    );
\p_1_out__7_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(16),
      I1 => Delay8_out1(16),
      I2 => adc_trigger,
      O => \A__7\(16)
    );
\p_1_out__7_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(15),
      I1 => Delay8_out1(15),
      I2 => adc_trigger,
      O => \A__7\(15)
    );
\p_1_out__7_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(14),
      I1 => Delay8_out1(14),
      I2 => adc_trigger,
      O => \A__7\(14)
    );
\p_1_out__7_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(13),
      I1 => Delay8_out1(13),
      I2 => adc_trigger,
      O => \A__7\(13)
    );
\p_1_out__7_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(12),
      I1 => Delay8_out1(12),
      I2 => adc_trigger,
      O => \A__7\(12)
    );
\p_1_out__7_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(11),
      I1 => Delay8_out1(11),
      I2 => adc_trigger,
      O => \A__7\(11)
    );
\p_1_out__7_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(10),
      I1 => Delay8_out1(10),
      I2 => adc_trigger,
      O => \A__7\(10)
    );
\p_1_out__7_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(9),
      I1 => Delay8_out1(9),
      I2 => adc_trigger,
      O => \A__7\(9)
    );
\p_1_out__7_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(26),
      I1 => Delay8_out1(26),
      I2 => adc_trigger,
      O => \A__7\(26)
    );
\p_1_out__7_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(8),
      I1 => Delay8_out1(8),
      I2 => adc_trigger,
      O => \A__7\(8)
    );
\p_1_out__7_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(7),
      I1 => Delay8_out1(7),
      I2 => adc_trigger,
      O => \A__7\(7)
    );
\p_1_out__7_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(6),
      I1 => Delay8_out1(6),
      I2 => adc_trigger,
      O => \A__7\(6)
    );
\p_1_out__7_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(5),
      I1 => Delay8_out1(5),
      I2 => adc_trigger,
      O => \A__7\(5)
    );
\p_1_out__7_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(4),
      I1 => Delay8_out1(4),
      I2 => adc_trigger,
      O => \A__7\(4)
    );
\p_1_out__7_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(3),
      I1 => Delay8_out1(3),
      I2 => adc_trigger,
      O => \A__7\(3)
    );
\p_1_out__7_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(2),
      I1 => Delay8_out1(2),
      I2 => adc_trigger,
      O => \A__7\(2)
    );
\p_1_out__7_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(1),
      I1 => Delay8_out1(1),
      I2 => adc_trigger,
      O => \A__7\(1)
    );
\p_1_out__7_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(0),
      I1 => Delay8_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__7_i_28_n_0\
    );
\p_1_out__7_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(25),
      I1 => Delay8_out1(25),
      I2 => adc_trigger,
      O => \A__7\(25)
    );
\p_1_out__7_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(24),
      I1 => Delay8_out1(24),
      I2 => adc_trigger,
      O => \A__7\(24)
    );
\p_1_out__7_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(23),
      I1 => Delay8_out1(23),
      I2 => adc_trigger,
      O => \A__7\(23)
    );
\p_1_out__7_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(22),
      I1 => Delay8_out1(22),
      I2 => adc_trigger,
      O => \A__7\(22)
    );
\p_1_out__7_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(21),
      I1 => Delay8_out1(21),
      I2 => adc_trigger,
      O => \A__7\(21)
    );
\p_1_out__7_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(20),
      I1 => Delay8_out1(20),
      I2 => adc_trigger,
      O => \A__7\(20)
    );
\p_1_out__7_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in8(19),
      I1 => Delay8_out1(19),
      I2 => adc_trigger,
      O => \A__7\(19)
    );
\p_1_out__8\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__8\(26),
      A(28) => \A__8\(26),
      A(27) => \A__8\(26),
      A(26 downto 1) => \A__8\(26 downto 1),
      A(0) => \p_1_out__8_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__8_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__8_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__8\(26),
      C(46) => \A__8\(26),
      C(45) => \A__8\(26),
      C(44) => \A__8\(26),
      C(43) => \A__8\(26),
      C(42) => \A__8\(26),
      C(41) => \A__8\(26),
      C(40) => \A__8\(26),
      C(39) => \A__8\(26),
      C(38) => \A__8\(26),
      C(37) => \A__8\(26),
      C(36) => \A__8\(26),
      C(35) => \A__8\(26),
      C(34) => \A__8\(26),
      C(33) => \A__8\(26),
      C(32) => \A__8\(26),
      C(31) => \A__8\(26),
      C(30) => \A__8\(26),
      C(29) => \A__8\(26),
      C(28) => \A__8\(26),
      C(27) => \A__8\(26),
      C(26) => \A__8\(26),
      C(25 downto 0) => \A__8\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__8_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__8_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_8,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__8_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out9[17]\(0),
      OPMODE(4) => \out9[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__8_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__8_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__8_n_61\,
      P(43) => \p_1_out__8_n_62\,
      P(42) => \p_1_out__8_n_63\,
      P(41) => \p_1_out__8_n_64\,
      P(40) => \p_1_out__8_n_65\,
      P(39) => \p_1_out__8_n_66\,
      P(38) => \p_1_out__8_n_67\,
      P(37) => \p_1_out__8_n_68\,
      P(36) => \p_1_out__8_n_69\,
      P(35) => \p_1_out__8_n_70\,
      P(34 downto 17) => out9(17 downto 0),
      P(16) => \p_1_out__8_n_89\,
      P(15) => \p_1_out__8_n_90\,
      P(14) => \p_1_out__8_n_91\,
      P(13) => \p_1_out__8_n_92\,
      P(12) => \p_1_out__8_n_93\,
      P(11) => \p_1_out__8_n_94\,
      P(10) => \p_1_out__8_n_95\,
      P(9) => \p_1_out__8_n_96\,
      P(8) => \p_1_out__8_n_97\,
      P(7) => \p_1_out__8_n_98\,
      P(6) => \p_1_out__8_n_99\,
      P(5) => \p_1_out__8_n_100\,
      P(4) => \p_1_out__8_n_101\,
      P(3) => \p_1_out__8_n_102\,
      P(2) => \p_1_out__8_n_103\,
      P(1) => \p_1_out__8_n_104\,
      P(0) => \p_1_out__8_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__8_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__8_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__8_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__8_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__8_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__8_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(18),
      I1 => Delay9_out1(18),
      I2 => adc_trigger,
      O => \A__8\(18)
    );
\p_1_out__8_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(17),
      I1 => Delay9_out1(17),
      I2 => adc_trigger,
      O => \A__8\(17)
    );
\p_1_out__8_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(16),
      I1 => Delay9_out1(16),
      I2 => adc_trigger,
      O => \A__8\(16)
    );
\p_1_out__8_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(15),
      I1 => Delay9_out1(15),
      I2 => adc_trigger,
      O => \A__8\(15)
    );
\p_1_out__8_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(14),
      I1 => Delay9_out1(14),
      I2 => adc_trigger,
      O => \A__8\(14)
    );
\p_1_out__8_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(13),
      I1 => Delay9_out1(13),
      I2 => adc_trigger,
      O => \A__8\(13)
    );
\p_1_out__8_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(12),
      I1 => Delay9_out1(12),
      I2 => adc_trigger,
      O => \A__8\(12)
    );
\p_1_out__8_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(11),
      I1 => Delay9_out1(11),
      I2 => adc_trigger,
      O => \A__8\(11)
    );
\p_1_out__8_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(10),
      I1 => Delay9_out1(10),
      I2 => adc_trigger,
      O => \A__8\(10)
    );
\p_1_out__8_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(9),
      I1 => Delay9_out1(9),
      I2 => adc_trigger,
      O => \A__8\(9)
    );
\p_1_out__8_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(26),
      I1 => Delay9_out1(26),
      I2 => adc_trigger,
      O => \A__8\(26)
    );
\p_1_out__8_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(8),
      I1 => Delay9_out1(8),
      I2 => adc_trigger,
      O => \A__8\(8)
    );
\p_1_out__8_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(7),
      I1 => Delay9_out1(7),
      I2 => adc_trigger,
      O => \A__8\(7)
    );
\p_1_out__8_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(6),
      I1 => Delay9_out1(6),
      I2 => adc_trigger,
      O => \A__8\(6)
    );
\p_1_out__8_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(5),
      I1 => Delay9_out1(5),
      I2 => adc_trigger,
      O => \A__8\(5)
    );
\p_1_out__8_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(4),
      I1 => Delay9_out1(4),
      I2 => adc_trigger,
      O => \A__8\(4)
    );
\p_1_out__8_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(3),
      I1 => Delay9_out1(3),
      I2 => adc_trigger,
      O => \A__8\(3)
    );
\p_1_out__8_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(2),
      I1 => Delay9_out1(2),
      I2 => adc_trigger,
      O => \A__8\(2)
    );
\p_1_out__8_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(1),
      I1 => Delay9_out1(1),
      I2 => adc_trigger,
      O => \A__8\(1)
    );
\p_1_out__8_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(0),
      I1 => Delay9_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__8_i_28_n_0\
    );
\p_1_out__8_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(25),
      I1 => Delay9_out1(25),
      I2 => adc_trigger,
      O => \A__8\(25)
    );
\p_1_out__8_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(24),
      I1 => Delay9_out1(24),
      I2 => adc_trigger,
      O => \A__8\(24)
    );
\p_1_out__8_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(23),
      I1 => Delay9_out1(23),
      I2 => adc_trigger,
      O => \A__8\(23)
    );
\p_1_out__8_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(22),
      I1 => Delay9_out1(22),
      I2 => adc_trigger,
      O => \A__8\(22)
    );
\p_1_out__8_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(21),
      I1 => Delay9_out1(21),
      I2 => adc_trigger,
      O => \A__8\(21)
    );
\p_1_out__8_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(20),
      I1 => Delay9_out1(20),
      I2 => adc_trigger,
      O => \A__8\(20)
    );
\p_1_out__8_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in9(19),
      I1 => Delay9_out1(19),
      I2 => adc_trigger,
      O => \A__8\(19)
    );
\p_1_out__9\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
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
      A(29) => \A__9\(26),
      A(28) => \A__9\(26),
      A(27) => \A__9\(26),
      A(26 downto 1) => \A__9\(26 downto 1),
      A(0) => \p_1_out__9_i_28_n_0\,
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_p_1_out__9_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_p_1_out__9_BCOUT_UNCONNECTED\(17 downto 0),
      C(47) => \A__9\(26),
      C(46) => \A__9\(26),
      C(45) => \A__9\(26),
      C(44) => \A__9\(26),
      C(43) => \A__9\(26),
      C(42) => \A__9\(26),
      C(41) => \A__9\(26),
      C(40) => \A__9\(26),
      C(39) => \A__9\(26),
      C(38) => \A__9\(26),
      C(37) => \A__9\(26),
      C(36) => \A__9\(26),
      C(35) => \A__9\(26),
      C(34) => \A__9\(26),
      C(33) => \A__9\(26),
      C(32) => \A__9\(26),
      C(31) => \A__9\(26),
      C(30) => \A__9\(26),
      C(29) => \A__9\(26),
      C(28) => \A__9\(26),
      C(27) => \A__9\(26),
      C(26) => \A__9\(26),
      C(25 downto 0) => \A__9\(26 downto 1),
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_p_1_out__9_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_p_1_out__9_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => DSP_ALU_INST_9,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => AXI4_Lite_ACLK,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_p_1_out__9_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \out10[17]\(0),
      OPMODE(4) => \out10[17]\(0),
      OPMODE(3 downto 0) => B"0101",
      OVERFLOW => \NLW_p_1_out__9_OVERFLOW_UNCONNECTED\,
      P(47 downto 45) => \NLW_p_1_out__9_P_UNCONNECTED\(47 downto 45),
      P(44) => \p_1_out__9_n_61\,
      P(43) => \p_1_out__9_n_62\,
      P(42) => \p_1_out__9_n_63\,
      P(41) => \p_1_out__9_n_64\,
      P(40) => \p_1_out__9_n_65\,
      P(39) => \p_1_out__9_n_66\,
      P(38) => \p_1_out__9_n_67\,
      P(37) => \p_1_out__9_n_68\,
      P(36) => \p_1_out__9_n_69\,
      P(35) => \p_1_out__9_n_70\,
      P(34 downto 17) => out10(17 downto 0),
      P(16) => \p_1_out__9_n_89\,
      P(15) => \p_1_out__9_n_90\,
      P(14) => \p_1_out__9_n_91\,
      P(13) => \p_1_out__9_n_92\,
      P(12) => \p_1_out__9_n_93\,
      P(11) => \p_1_out__9_n_94\,
      P(10) => \p_1_out__9_n_95\,
      P(9) => \p_1_out__9_n_96\,
      P(8) => \p_1_out__9_n_97\,
      P(7) => \p_1_out__9_n_98\,
      P(6) => \p_1_out__9_n_99\,
      P(5) => \p_1_out__9_n_100\,
      P(4) => \p_1_out__9_n_101\,
      P(3) => \p_1_out__9_n_102\,
      P(2) => \p_1_out__9_n_103\,
      P(1) => \p_1_out__9_n_104\,
      P(0) => \p_1_out__9_n_105\,
      PATTERNBDETECT => \NLW_p_1_out__9_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_p_1_out__9_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_p_1_out__9_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => reset,
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_p_1_out__9_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_p_1_out__9_XOROUT_UNCONNECTED\(7 downto 0)
    );
\p_1_out__9_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(18),
      I1 => Delay10_out1(18),
      I2 => adc_trigger,
      O => \A__9\(18)
    );
\p_1_out__9_i_11\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(17),
      I1 => Delay10_out1(17),
      I2 => adc_trigger,
      O => \A__9\(17)
    );
\p_1_out__9_i_12\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(16),
      I1 => Delay10_out1(16),
      I2 => adc_trigger,
      O => \A__9\(16)
    );
\p_1_out__9_i_13\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(15),
      I1 => Delay10_out1(15),
      I2 => adc_trigger,
      O => \A__9\(15)
    );
\p_1_out__9_i_14\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(14),
      I1 => Delay10_out1(14),
      I2 => adc_trigger,
      O => \A__9\(14)
    );
\p_1_out__9_i_15\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(13),
      I1 => Delay10_out1(13),
      I2 => adc_trigger,
      O => \A__9\(13)
    );
\p_1_out__9_i_16\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(12),
      I1 => Delay10_out1(12),
      I2 => adc_trigger,
      O => \A__9\(12)
    );
\p_1_out__9_i_17\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(11),
      I1 => Delay10_out1(11),
      I2 => adc_trigger,
      O => \A__9\(11)
    );
\p_1_out__9_i_18\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(10),
      I1 => Delay10_out1(10),
      I2 => adc_trigger,
      O => \A__9\(10)
    );
\p_1_out__9_i_19\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(9),
      I1 => Delay10_out1(9),
      I2 => adc_trigger,
      O => \A__9\(9)
    );
\p_1_out__9_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(26),
      I1 => Delay10_out1(26),
      I2 => adc_trigger,
      O => \A__9\(26)
    );
\p_1_out__9_i_20\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(8),
      I1 => Delay10_out1(8),
      I2 => adc_trigger,
      O => \A__9\(8)
    );
\p_1_out__9_i_21\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(7),
      I1 => Delay10_out1(7),
      I2 => adc_trigger,
      O => \A__9\(7)
    );
\p_1_out__9_i_22\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(6),
      I1 => Delay10_out1(6),
      I2 => adc_trigger,
      O => \A__9\(6)
    );
\p_1_out__9_i_23\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(5),
      I1 => Delay10_out1(5),
      I2 => adc_trigger,
      O => \A__9\(5)
    );
\p_1_out__9_i_24\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(4),
      I1 => Delay10_out1(4),
      I2 => adc_trigger,
      O => \A__9\(4)
    );
\p_1_out__9_i_25\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(3),
      I1 => Delay10_out1(3),
      I2 => adc_trigger,
      O => \A__9\(3)
    );
\p_1_out__9_i_26\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(2),
      I1 => Delay10_out1(2),
      I2 => adc_trigger,
      O => \A__9\(2)
    );
\p_1_out__9_i_27\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(1),
      I1 => Delay10_out1(1),
      I2 => adc_trigger,
      O => \A__9\(1)
    );
\p_1_out__9_i_28\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(0),
      I1 => Delay10_out1(0),
      I2 => adc_trigger,
      O => \p_1_out__9_i_28_n_0\
    );
\p_1_out__9_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(25),
      I1 => Delay10_out1(25),
      I2 => adc_trigger,
      O => \A__9\(25)
    );
\p_1_out__9_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(24),
      I1 => Delay10_out1(24),
      I2 => adc_trigger,
      O => \A__9\(24)
    );
\p_1_out__9_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(23),
      I1 => Delay10_out1(23),
      I2 => adc_trigger,
      O => \A__9\(23)
    );
\p_1_out__9_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(22),
      I1 => Delay10_out1(22),
      I2 => adc_trigger,
      O => \A__9\(22)
    );
\p_1_out__9_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(21),
      I1 => Delay10_out1(21),
      I2 => adc_trigger,
      O => \A__9\(21)
    );
\p_1_out__9_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(20),
      I1 => Delay10_out1(20),
      I2 => adc_trigger,
      O => \A__9\(20)
    );
\p_1_out__9_i_9\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in10(19),
      I1 => Delay10_out1(19),
      I2 => adc_trigger,
      O => \A__9\(19)
    );
p_1_out_i_10: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(18),
      I1 => Delay_out1(18),
      I2 => adc_trigger,
      O => A(18)
    );
p_1_out_i_11: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(17),
      I1 => Delay_out1(17),
      I2 => adc_trigger,
      O => A(17)
    );
p_1_out_i_12: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(16),
      I1 => Delay_out1(16),
      I2 => adc_trigger,
      O => A(16)
    );
p_1_out_i_13: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(15),
      I1 => Delay_out1(15),
      I2 => adc_trigger,
      O => A(15)
    );
p_1_out_i_14: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(14),
      I1 => Delay_out1(14),
      I2 => adc_trigger,
      O => A(14)
    );
p_1_out_i_15: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(13),
      I1 => Delay_out1(13),
      I2 => adc_trigger,
      O => A(13)
    );
p_1_out_i_16: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(12),
      I1 => Delay_out1(12),
      I2 => adc_trigger,
      O => A(12)
    );
p_1_out_i_17: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(11),
      I1 => Delay_out1(11),
      I2 => adc_trigger,
      O => A(11)
    );
p_1_out_i_18: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(10),
      I1 => Delay_out1(10),
      I2 => adc_trigger,
      O => A(10)
    );
p_1_out_i_19: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(9),
      I1 => Delay_out1(9),
      I2 => adc_trigger,
      O => A(9)
    );
p_1_out_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(26),
      I1 => Delay_out1(26),
      I2 => adc_trigger,
      O => A(26)
    );
p_1_out_i_20: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(8),
      I1 => Delay_out1(8),
      I2 => adc_trigger,
      O => A(8)
    );
p_1_out_i_21: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(7),
      I1 => Delay_out1(7),
      I2 => adc_trigger,
      O => A(7)
    );
p_1_out_i_22: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(6),
      I1 => Delay_out1(6),
      I2 => adc_trigger,
      O => A(6)
    );
p_1_out_i_23: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(5),
      I1 => Delay_out1(5),
      I2 => adc_trigger,
      O => A(5)
    );
p_1_out_i_24: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(4),
      I1 => Delay_out1(4),
      I2 => adc_trigger,
      O => A(4)
    );
p_1_out_i_25: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(3),
      I1 => Delay_out1(3),
      I2 => adc_trigger,
      O => A(3)
    );
p_1_out_i_26: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(2),
      I1 => Delay_out1(2),
      I2 => adc_trigger,
      O => A(2)
    );
p_1_out_i_27: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(1),
      I1 => Delay_out1(1),
      I2 => adc_trigger,
      O => A(1)
    );
p_1_out_i_28: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(0),
      I1 => Delay_out1(0),
      I2 => adc_trigger,
      O => p_1_out_i_28_n_0
    );
p_1_out_i_3: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(25),
      I1 => Delay_out1(25),
      I2 => adc_trigger,
      O => A(25)
    );
p_1_out_i_4: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(24),
      I1 => Delay_out1(24),
      I2 => adc_trigger,
      O => A(24)
    );
p_1_out_i_5: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(23),
      I1 => Delay_out1(23),
      I2 => adc_trigger,
      O => A(23)
    );
p_1_out_i_6: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(22),
      I1 => Delay_out1(22),
      I2 => adc_trigger,
      O => A(22)
    );
p_1_out_i_7: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(21),
      I1 => Delay_out1(21),
      I2 => adc_trigger,
      O => A(21)
    );
p_1_out_i_8: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(20),
      I1 => Delay_out1(20),
      I2 => adc_trigger,
      O => A(20)
    );
p_1_out_i_9: unisim.vcomponents.LUT3
    generic map(
      INIT => X"AC"
    )
        port map (
      I0 => in0(19),
      I1 => Delay_out1(19),
      I2 => adc_trigger,
      O => A(19)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite is
  port (
    FSM_sequential_axi_lite_rstate_reg : out STD_LOGIC;
    OPMODE : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in1_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in2_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in3_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in4_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in5_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in6_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in7_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in8_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in9_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in10_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in11_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in12_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in13_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in14_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in15_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in16_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in17_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in18_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in19_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in20_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in21_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in22_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in23_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in24_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in25_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in26_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in27_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in28_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in29_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in30_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_AXI_pu_conv_in31_1_1_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 0 to 0 );
    soft_reset : out STD_LOGIC;
    CEB2 : out STD_LOGIC;
    AXI4_Lite_ARADDR_8_sp_1 : out STD_LOGIC;
    AXI4_Lite_ARADDR_11_sp_1 : out STD_LOGIC;
    AXI4_Lite_ARADDR_7_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_0\ : out STD_LOGIC;
    AXI4_Lite_ARADDR_4_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_0\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_2\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[4]_0\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_3\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_4\ : out STD_LOGIC;
    AXI4_Lite_ARADDR_3_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_5\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_2\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_6\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[3]_0\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_7\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_3\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_8\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[4]_1\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_9\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_4\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_10\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[4]_2\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_11\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[7]_5\ : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_12\ : out STD_LOGIC;
    AXI4_Lite_ARADDR_6_sp_1 : out STD_LOGIC;
    \AXI4_Lite_ARADDR[8]_13\ : out STD_LOGIC;
    wr_enb_1_reg : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    \wdata_reg[17]\ : out STD_LOGIC_VECTOR ( 16 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    reset : in STD_LOGIC;
    \read_reg_ip_timestamp_reg[31]\ : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 17 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite : entity is "uz_pu_con_ip_axi_lite";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite is
  signal AXI4_Lite_ARADDR_11_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_3_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_4_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_6_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_7_sn_1 : STD_LOGIC;
  signal AXI4_Lite_ARADDR_8_sn_1 : STD_LOGIC;
  signal \^opmode\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in10_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in11_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in12_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in13_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in14_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in15_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in16_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in17_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in18_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in19_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in1_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in20_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in21_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in22_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in23_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in24_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in25_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in26_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in27_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in28_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in29_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in2_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in30_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in31_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in3_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in4_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in5_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in6_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in7_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in8_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_reg_axi_pu_conv_in9_1_1_reg[0]\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal read_reg_ip_timestamp : STD_LOGIC_VECTOR ( 31 to 31 );
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_40 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_41 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_42 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_43 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_44 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_45 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_46 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_47 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_48 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_49 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_50 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_51 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_52 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_53 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_54 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_55 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_56 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_57 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_58 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_59 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_60 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_61 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_62 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_63 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_64 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_65 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_66 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_67 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_68 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_69 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_70 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_module_inst_n_71 : STD_LOGIC;
begin
  AXI4_Lite_ARADDR_11_sp_1 <= AXI4_Lite_ARADDR_11_sn_1;
  AXI4_Lite_ARADDR_3_sp_1 <= AXI4_Lite_ARADDR_3_sn_1;
  AXI4_Lite_ARADDR_4_sp_1 <= AXI4_Lite_ARADDR_4_sn_1;
  AXI4_Lite_ARADDR_6_sp_1 <= AXI4_Lite_ARADDR_6_sn_1;
  AXI4_Lite_ARADDR_7_sp_1 <= AXI4_Lite_ARADDR_7_sn_1;
  AXI4_Lite_ARADDR_8_sp_1 <= AXI4_Lite_ARADDR_8_sn_1;
  OPMODE(0) <= \^opmode\(0);
  \data_reg_AXI_pu_conv_in10_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in10_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in11_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in11_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in12_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in12_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in13_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in13_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in14_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in14_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in15_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in15_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in16_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in16_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in17_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in17_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in18_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in18_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in19_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in19_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in1_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in1_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in20_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in20_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in21_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in21_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in22_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in22_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in23_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in23_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in24_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in24_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in25_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in25_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in26_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in26_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in27_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in27_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in28_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in28_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in29_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in29_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in2_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in2_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in30_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in30_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in31_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in31_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in3_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in3_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in4_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in4_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in5_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in5_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in6_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in6_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in7_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in7_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in8_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in8_1_1_reg[0]\(0);
  \data_reg_AXI_pu_conv_in9_1_1_reg[0]\(0) <= \^data_reg_axi_pu_conv_in9_1_1_reg[0]\(0);
u_uz_pu_con_ip_addr_decoder_inst: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_addr_decoder
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      OPMODE(0) => \^opmode\(0),
      \data_reg_AXI_pu_conv_in0_1_1_reg[0]_0\ => u_uz_pu_con_ip_axi_lite_module_inst_n_71,
      \data_reg_AXI_pu_conv_in10_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in10_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in10_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_65,
      \data_reg_AXI_pu_conv_in11_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in11_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in11_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_61,
      \data_reg_AXI_pu_conv_in12_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in12_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in12_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_57,
      \data_reg_AXI_pu_conv_in13_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in13_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in13_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_53,
      \data_reg_AXI_pu_conv_in14_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in14_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in14_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_49,
      \data_reg_AXI_pu_conv_in15_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in15_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in15_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_45,
      \data_reg_AXI_pu_conv_in16_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in16_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in16_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_41,
      \data_reg_AXI_pu_conv_in17_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in17_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in17_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_68,
      \data_reg_AXI_pu_conv_in18_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in18_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in18_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_64,
      \data_reg_AXI_pu_conv_in19_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in19_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in19_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_60,
      \data_reg_AXI_pu_conv_in1_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in1_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in1_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_70,
      \data_reg_AXI_pu_conv_in20_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in20_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in20_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_56,
      \data_reg_AXI_pu_conv_in21_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in21_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in21_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_52,
      \data_reg_AXI_pu_conv_in22_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in22_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in22_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_48,
      \data_reg_AXI_pu_conv_in23_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in23_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in23_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_44,
      \data_reg_AXI_pu_conv_in24_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in24_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in24_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_40,
      \data_reg_AXI_pu_conv_in25_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in25_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in25_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_67,
      \data_reg_AXI_pu_conv_in26_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in26_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in26_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_63,
      \data_reg_AXI_pu_conv_in27_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in27_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in27_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_59,
      \data_reg_AXI_pu_conv_in28_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in28_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in28_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_55,
      \data_reg_AXI_pu_conv_in29_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in29_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in29_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_51,
      \data_reg_AXI_pu_conv_in2_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in2_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in2_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_66,
      \data_reg_AXI_pu_conv_in30_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in30_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in30_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_47,
      \data_reg_AXI_pu_conv_in31_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in31_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in31_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_43,
      \data_reg_AXI_pu_conv_in3_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in3_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in3_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_62,
      \data_reg_AXI_pu_conv_in4_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in4_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in4_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_58,
      \data_reg_AXI_pu_conv_in5_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in5_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in5_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_54,
      \data_reg_AXI_pu_conv_in6_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in6_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in6_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_50,
      \data_reg_AXI_pu_conv_in7_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in7_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in7_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_46,
      \data_reg_AXI_pu_conv_in8_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in8_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in8_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_42,
      \data_reg_AXI_pu_conv_in9_1_1_reg[0]_0\(0) => \^data_reg_axi_pu_conv_in9_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in9_1_1_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_69,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(31),
      \read_reg_ip_timestamp_reg[31]_0\ => \read_reg_ip_timestamp_reg[31]\,
      reset => reset
    );
u_uz_pu_con_ip_axi_lite_module_inst: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite_module
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      \AXI4_Lite_ARADDR[3]_0\ => \AXI4_Lite_ARADDR[3]_0\,
      \AXI4_Lite_ARADDR[4]_0\ => \AXI4_Lite_ARADDR[4]_0\,
      \AXI4_Lite_ARADDR[4]_1\ => \AXI4_Lite_ARADDR[4]_1\,
      \AXI4_Lite_ARADDR[4]_2\ => \AXI4_Lite_ARADDR[4]_2\,
      \AXI4_Lite_ARADDR[7]_0\ => \AXI4_Lite_ARADDR[7]_0\,
      \AXI4_Lite_ARADDR[7]_1\ => \AXI4_Lite_ARADDR[7]_1\,
      \AXI4_Lite_ARADDR[7]_2\ => \AXI4_Lite_ARADDR[7]_2\,
      \AXI4_Lite_ARADDR[7]_3\ => \AXI4_Lite_ARADDR[7]_3\,
      \AXI4_Lite_ARADDR[7]_4\ => \AXI4_Lite_ARADDR[7]_4\,
      \AXI4_Lite_ARADDR[7]_5\ => \AXI4_Lite_ARADDR[7]_5\,
      \AXI4_Lite_ARADDR[8]_0\ => \AXI4_Lite_ARADDR[8]_0\,
      \AXI4_Lite_ARADDR[8]_1\ => \AXI4_Lite_ARADDR[8]_1\,
      \AXI4_Lite_ARADDR[8]_10\ => \AXI4_Lite_ARADDR[8]_10\,
      \AXI4_Lite_ARADDR[8]_11\ => \AXI4_Lite_ARADDR[8]_11\,
      \AXI4_Lite_ARADDR[8]_12\ => \AXI4_Lite_ARADDR[8]_12\,
      \AXI4_Lite_ARADDR[8]_13\ => \AXI4_Lite_ARADDR[8]_13\,
      \AXI4_Lite_ARADDR[8]_2\ => \AXI4_Lite_ARADDR[8]_2\,
      \AXI4_Lite_ARADDR[8]_3\ => \AXI4_Lite_ARADDR[8]_3\,
      \AXI4_Lite_ARADDR[8]_4\ => \AXI4_Lite_ARADDR[8]_4\,
      \AXI4_Lite_ARADDR[8]_5\ => \AXI4_Lite_ARADDR[8]_5\,
      \AXI4_Lite_ARADDR[8]_6\ => \AXI4_Lite_ARADDR[8]_6\,
      \AXI4_Lite_ARADDR[8]_7\ => \AXI4_Lite_ARADDR[8]_7\,
      \AXI4_Lite_ARADDR[8]_8\ => \AXI4_Lite_ARADDR[8]_8\,
      \AXI4_Lite_ARADDR[8]_9\ => \AXI4_Lite_ARADDR[8]_9\,
      AXI4_Lite_ARADDR_11_sp_1 => AXI4_Lite_ARADDR_11_sn_1,
      AXI4_Lite_ARADDR_3_sp_1 => AXI4_Lite_ARADDR_3_sn_1,
      AXI4_Lite_ARADDR_4_sp_1 => AXI4_Lite_ARADDR_4_sn_1,
      AXI4_Lite_ARADDR_6_sp_1 => AXI4_Lite_ARADDR_6_sn_1,
      AXI4_Lite_ARADDR_7_sp_1 => AXI4_Lite_ARADDR_7_sn_1,
      AXI4_Lite_ARADDR_8_sp_1 => AXI4_Lite_ARADDR_8_sn_1,
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(0) => AXI4_Lite_RDATA(0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(17 downto 0) => AXI4_Lite_WDATA(17 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CEB2 => CEB2,
      FSM_sequential_axi_lite_rstate_reg_0 => FSM_sequential_axi_lite_rstate_reg,
      IPCORE_RESETN => IPCORE_RESETN,
      OPMODE(0) => \^opmode\(0),
      Q(1 downto 0) => Q(1 downto 0),
      \data_reg_AXI_pu_conv_in10_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in10_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in11_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in11_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in12_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in12_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in13_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in13_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in14_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in14_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in15_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in15_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in16_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in16_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in17_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in17_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in18_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in18_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in19_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in19_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in1_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in1_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in20_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in20_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in21_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in21_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in22_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in22_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in23_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in23_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in24_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in24_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in25_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in25_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in26_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in26_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in27_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in27_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in28_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in28_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in29_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in29_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in2_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in2_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in30_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in30_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in31_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in31_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in3_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in3_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in4_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in4_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in5_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in5_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in6_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in6_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in7_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in7_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in8_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in8_1_1_reg[0]\(0),
      \data_reg_AXI_pu_conv_in9_1_1_reg[0]\(0) => \^data_reg_axi_pu_conv_in9_1_1_reg[0]\(0),
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(31),
      reset_in => reset_in,
      soft_reset => soft_reset,
      \wdata_reg[0]_0\ => u_uz_pu_con_ip_axi_lite_module_inst_n_40,
      \wdata_reg[0]_1\ => u_uz_pu_con_ip_axi_lite_module_inst_n_41,
      \wdata_reg[0]_10\ => u_uz_pu_con_ip_axi_lite_module_inst_n_50,
      \wdata_reg[0]_11\ => u_uz_pu_con_ip_axi_lite_module_inst_n_51,
      \wdata_reg[0]_12\ => u_uz_pu_con_ip_axi_lite_module_inst_n_52,
      \wdata_reg[0]_13\ => u_uz_pu_con_ip_axi_lite_module_inst_n_53,
      \wdata_reg[0]_14\ => u_uz_pu_con_ip_axi_lite_module_inst_n_54,
      \wdata_reg[0]_15\ => u_uz_pu_con_ip_axi_lite_module_inst_n_55,
      \wdata_reg[0]_16\ => u_uz_pu_con_ip_axi_lite_module_inst_n_56,
      \wdata_reg[0]_17\ => u_uz_pu_con_ip_axi_lite_module_inst_n_57,
      \wdata_reg[0]_18\ => u_uz_pu_con_ip_axi_lite_module_inst_n_58,
      \wdata_reg[0]_19\ => u_uz_pu_con_ip_axi_lite_module_inst_n_59,
      \wdata_reg[0]_2\ => u_uz_pu_con_ip_axi_lite_module_inst_n_42,
      \wdata_reg[0]_20\ => u_uz_pu_con_ip_axi_lite_module_inst_n_60,
      \wdata_reg[0]_21\ => u_uz_pu_con_ip_axi_lite_module_inst_n_61,
      \wdata_reg[0]_22\ => u_uz_pu_con_ip_axi_lite_module_inst_n_62,
      \wdata_reg[0]_23\ => u_uz_pu_con_ip_axi_lite_module_inst_n_63,
      \wdata_reg[0]_24\ => u_uz_pu_con_ip_axi_lite_module_inst_n_64,
      \wdata_reg[0]_25\ => u_uz_pu_con_ip_axi_lite_module_inst_n_65,
      \wdata_reg[0]_26\ => u_uz_pu_con_ip_axi_lite_module_inst_n_66,
      \wdata_reg[0]_27\ => u_uz_pu_con_ip_axi_lite_module_inst_n_67,
      \wdata_reg[0]_28\ => u_uz_pu_con_ip_axi_lite_module_inst_n_68,
      \wdata_reg[0]_29\ => u_uz_pu_con_ip_axi_lite_module_inst_n_69,
      \wdata_reg[0]_3\ => u_uz_pu_con_ip_axi_lite_module_inst_n_43,
      \wdata_reg[0]_30\ => u_uz_pu_con_ip_axi_lite_module_inst_n_70,
      \wdata_reg[0]_31\ => u_uz_pu_con_ip_axi_lite_module_inst_n_71,
      \wdata_reg[0]_4\ => u_uz_pu_con_ip_axi_lite_module_inst_n_44,
      \wdata_reg[0]_5\ => u_uz_pu_con_ip_axi_lite_module_inst_n_45,
      \wdata_reg[0]_6\ => u_uz_pu_con_ip_axi_lite_module_inst_n_46,
      \wdata_reg[0]_7\ => u_uz_pu_con_ip_axi_lite_module_inst_n_47,
      \wdata_reg[0]_8\ => u_uz_pu_con_ip_axi_lite_module_inst_n_48,
      \wdata_reg[0]_9\ => u_uz_pu_con_ip_axi_lite_module_inst_n_49,
      \wdata_reg[17]_0\(16 downto 0) => \wdata_reg[17]\(16 downto 0),
      wr_enb_1_reg_0 => wr_enb_1_reg
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut is
  port (
    out0 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out1 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out2 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out3 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out4 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out5 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out6 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out7 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out8 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out9 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out10 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out11 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out12 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out13 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out14 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out15 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out16 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out17 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out18 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out19 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out20 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out21 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out22 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out23 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out24 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out25 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out26 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out27 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out28 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out29 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out30 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out31 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    reset : in STD_LOGIC;
    adc_trigger : in STD_LOGIC;
    in0 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    IPCORE_CLK : in STD_LOGIC;
    DSP_ALU_INST : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI_pu_conv_in31 : in STD_LOGIC_VECTOR ( 16 downto 0 );
    OPMODE : in STD_LOGIC_VECTOR ( 0 to 0 );
    in1 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_0 : in STD_LOGIC;
    \out1[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in2 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_1 : in STD_LOGIC;
    \out2[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in3 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_2 : in STD_LOGIC;
    \out3[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in4 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_3 : in STD_LOGIC;
    \out4[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in5 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_4 : in STD_LOGIC;
    \out5[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in6 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_5 : in STD_LOGIC;
    \out6[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in7 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_6 : in STD_LOGIC;
    \out7[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in8 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_7 : in STD_LOGIC;
    \out8[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in9 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_8 : in STD_LOGIC;
    \out9[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in10 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_9 : in STD_LOGIC;
    \out10[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in11 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_10 : in STD_LOGIC;
    \out11[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in12 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_11 : in STD_LOGIC;
    \out12[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in13 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_12 : in STD_LOGIC;
    \out13[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in14 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_13 : in STD_LOGIC;
    \out14[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in15 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_14 : in STD_LOGIC;
    \out15[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in16 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_15 : in STD_LOGIC;
    \out16[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in17 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_16 : in STD_LOGIC;
    \out17[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in18 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_17 : in STD_LOGIC;
    \out18[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in19 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_18 : in STD_LOGIC;
    \out19[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in20 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_19 : in STD_LOGIC;
    \out20[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in21 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_20 : in STD_LOGIC;
    \out21[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in22 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_21 : in STD_LOGIC;
    \out22[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in23 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_22 : in STD_LOGIC;
    \out23[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in24 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    CEB2 : in STD_LOGIC;
    \out24[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in25 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_23 : in STD_LOGIC;
    \out25[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in26 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_24 : in STD_LOGIC;
    \out26[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in27 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_25 : in STD_LOGIC;
    \out27[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in28 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_26 : in STD_LOGIC;
    \out28[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in29 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_27 : in STD_LOGIC;
    \out29[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in30 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_28 : in STD_LOGIC;
    \out30[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    in31 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    DSP_ALU_INST_29 : in STD_LOGIC;
    \out31[17]\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut : entity is "uz_pu_con_ip_dut";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut is
begin
u_uz_pu_con_ip_src_uz_pu_conversion: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_src_uz_pu_conversion
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI_pu_conv_in31(16 downto 0) => AXI_pu_conv_in31(16 downto 0),
      CEB2 => CEB2,
      DSP_ALU_INST => DSP_ALU_INST,
      DSP_ALU_INST_0 => DSP_ALU_INST_0,
      DSP_ALU_INST_1 => DSP_ALU_INST_1,
      DSP_ALU_INST_10 => DSP_ALU_INST_10,
      DSP_ALU_INST_11 => DSP_ALU_INST_11,
      DSP_ALU_INST_12 => DSP_ALU_INST_12,
      DSP_ALU_INST_13 => DSP_ALU_INST_13,
      DSP_ALU_INST_14 => DSP_ALU_INST_14,
      DSP_ALU_INST_15 => DSP_ALU_INST_15,
      DSP_ALU_INST_16 => DSP_ALU_INST_16,
      DSP_ALU_INST_17 => DSP_ALU_INST_17,
      DSP_ALU_INST_18 => DSP_ALU_INST_18,
      DSP_ALU_INST_19 => DSP_ALU_INST_19,
      DSP_ALU_INST_2 => DSP_ALU_INST_2,
      DSP_ALU_INST_20 => DSP_ALU_INST_20,
      DSP_ALU_INST_21 => DSP_ALU_INST_21,
      DSP_ALU_INST_22 => DSP_ALU_INST_22,
      DSP_ALU_INST_23 => DSP_ALU_INST_23,
      DSP_ALU_INST_24 => DSP_ALU_INST_24,
      DSP_ALU_INST_25 => DSP_ALU_INST_25,
      DSP_ALU_INST_26 => DSP_ALU_INST_26,
      DSP_ALU_INST_27 => DSP_ALU_INST_27,
      DSP_ALU_INST_28 => DSP_ALU_INST_28,
      DSP_ALU_INST_29 => DSP_ALU_INST_29,
      DSP_ALU_INST_3 => DSP_ALU_INST_3,
      DSP_ALU_INST_4 => DSP_ALU_INST_4,
      DSP_ALU_INST_5 => DSP_ALU_INST_5,
      DSP_ALU_INST_6 => DSP_ALU_INST_6,
      DSP_ALU_INST_7 => DSP_ALU_INST_7,
      DSP_ALU_INST_8 => DSP_ALU_INST_8,
      DSP_ALU_INST_9 => DSP_ALU_INST_9,
      IPCORE_CLK => IPCORE_CLK,
      OPMODE(0) => OPMODE(0),
      adc_trigger => adc_trigger,
      in0(26 downto 0) => in0(26 downto 0),
      in1(26 downto 0) => in1(26 downto 0),
      in10(26 downto 0) => in10(26 downto 0),
      in11(26 downto 0) => in11(26 downto 0),
      in12(26 downto 0) => in12(26 downto 0),
      in13(26 downto 0) => in13(26 downto 0),
      in14(26 downto 0) => in14(26 downto 0),
      in15(26 downto 0) => in15(26 downto 0),
      in16(26 downto 0) => in16(26 downto 0),
      in17(26 downto 0) => in17(26 downto 0),
      in18(26 downto 0) => in18(26 downto 0),
      in19(26 downto 0) => in19(26 downto 0),
      in2(26 downto 0) => in2(26 downto 0),
      in20(26 downto 0) => in20(26 downto 0),
      in21(26 downto 0) => in21(26 downto 0),
      in22(26 downto 0) => in22(26 downto 0),
      in23(26 downto 0) => in23(26 downto 0),
      in24(26 downto 0) => in24(26 downto 0),
      in25(26 downto 0) => in25(26 downto 0),
      in26(26 downto 0) => in26(26 downto 0),
      in27(26 downto 0) => in27(26 downto 0),
      in28(26 downto 0) => in28(26 downto 0),
      in29(26 downto 0) => in29(26 downto 0),
      in3(26 downto 0) => in3(26 downto 0),
      in30(26 downto 0) => in30(26 downto 0),
      in31(26 downto 0) => in31(26 downto 0),
      in4(26 downto 0) => in4(26 downto 0),
      in5(26 downto 0) => in5(26 downto 0),
      in6(26 downto 0) => in6(26 downto 0),
      in7(26 downto 0) => in7(26 downto 0),
      in8(26 downto 0) => in8(26 downto 0),
      in9(26 downto 0) => in9(26 downto 0),
      out0(17 downto 0) => out0(17 downto 0),
      out1(17 downto 0) => out1(17 downto 0),
      out10(17 downto 0) => out10(17 downto 0),
      \out10[17]\(0) => \out10[17]\(0),
      out11(17 downto 0) => out11(17 downto 0),
      \out11[17]\(0) => \out11[17]\(0),
      out12(17 downto 0) => out12(17 downto 0),
      \out12[17]\(0) => \out12[17]\(0),
      out13(17 downto 0) => out13(17 downto 0),
      \out13[17]\(0) => \out13[17]\(0),
      out14(17 downto 0) => out14(17 downto 0),
      \out14[17]\(0) => \out14[17]\(0),
      out15(17 downto 0) => out15(17 downto 0),
      \out15[17]\(0) => \out15[17]\(0),
      out16(17 downto 0) => out16(17 downto 0),
      \out16[17]\(0) => \out16[17]\(0),
      out17(17 downto 0) => out17(17 downto 0),
      \out17[17]\(0) => \out17[17]\(0),
      out18(17 downto 0) => out18(17 downto 0),
      \out18[17]\(0) => \out18[17]\(0),
      out19(17 downto 0) => out19(17 downto 0),
      \out19[17]\(0) => \out19[17]\(0),
      \out1[17]\(0) => \out1[17]\(0),
      out2(17 downto 0) => out2(17 downto 0),
      out20(17 downto 0) => out20(17 downto 0),
      \out20[17]\(0) => \out20[17]\(0),
      out21(17 downto 0) => out21(17 downto 0),
      \out21[17]\(0) => \out21[17]\(0),
      out22(17 downto 0) => out22(17 downto 0),
      \out22[17]\(0) => \out22[17]\(0),
      out23(17 downto 0) => out23(17 downto 0),
      \out23[17]\(0) => \out23[17]\(0),
      out24(17 downto 0) => out24(17 downto 0),
      \out24[17]\(0) => \out24[17]\(0),
      out25(17 downto 0) => out25(17 downto 0),
      \out25[17]\(0) => \out25[17]\(0),
      out26(17 downto 0) => out26(17 downto 0),
      \out26[17]\(0) => \out26[17]\(0),
      out27(17 downto 0) => out27(17 downto 0),
      \out27[17]\(0) => \out27[17]\(0),
      out28(17 downto 0) => out28(17 downto 0),
      \out28[17]\(0) => \out28[17]\(0),
      out29(17 downto 0) => out29(17 downto 0),
      \out29[17]\(0) => \out29[17]\(0),
      \out2[17]\(0) => \out2[17]\(0),
      out3(17 downto 0) => out3(17 downto 0),
      out30(17 downto 0) => out30(17 downto 0),
      \out30[17]\(0) => \out30[17]\(0),
      out31(17 downto 0) => out31(17 downto 0),
      \out31[17]\(0) => \out31[17]\(0),
      \out3[17]\(0) => \out3[17]\(0),
      out4(17 downto 0) => out4(17 downto 0),
      \out4[17]\(0) => \out4[17]\(0),
      out5(17 downto 0) => out5(17 downto 0),
      \out5[17]\(0) => \out5[17]\(0),
      out6(17 downto 0) => out6(17 downto 0),
      \out6[17]\(0) => \out6[17]\(0),
      out7(17 downto 0) => out7(17 downto 0),
      \out7[17]\(0) => \out7[17]\(0),
      out8(17 downto 0) => out8(17 downto 0),
      \out8[17]\(0) => \out8[17]\(0),
      out9(17 downto 0) => out9(17 downto 0),
      \out9[17]\(0) => \out9[17]\(0),
      reset => reset
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_pu_con_ip_0_1_uz_pu_con_ip is
  port (
    AXI4_Lite_RVALID : out STD_LOGIC;
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    out0 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out1 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out2 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out3 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out4 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out5 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out6 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out7 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out8 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out9 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out10 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out11 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out12 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out13 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out14 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out15 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out16 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out17 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out18 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out19 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out20 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out21 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out22 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out23 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out24 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out25 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out26 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out27 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out28 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out29 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out30 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out31 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    adc_trigger : in STD_LOGIC;
    in0 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    IPCORE_CLK : in STD_LOGIC;
    in1 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in2 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in3 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in4 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in5 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in6 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in7 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in8 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in9 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in10 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in11 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in12 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in13 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in14 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in15 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in16 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in17 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in18 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in19 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in20 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in21 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in22 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in23 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in24 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in25 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in26 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in27 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in28 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in29 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in30 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in31 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 17 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip : entity is "uz_pu_con_ip";
end zusys_uz_pu_con_ip_0_1_uz_pu_con_ip;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1_uz_pu_con_ip is
  signal reset : STD_LOGIC;
  signal reset_in : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in0_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in10_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in11_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in12_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in13_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in14_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in15_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in16_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in17_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in18_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in19_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in1_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in20_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in21_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in22_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in23_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in24_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in25_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in26_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in27_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in28_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in29_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in2_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in30_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in31_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in3_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in4_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in5_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in6_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in7_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in8_1_1\ : STD_LOGIC;
  signal \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in9_1_1\ : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_72 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_73 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_74 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_75 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_76 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_77 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_78 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_79 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_80 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_81 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_82 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_83 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_84 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_85 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_86 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_87 : STD_LOGIC;
  signal u_uz_pu_con_ip_axi_lite_inst_n_88 : STD_LOGIC;
  signal \u_uz_pu_con_ip_axi_lite_module_inst/soft_reset\ : STD_LOGIC;
  signal u_uz_pu_con_ip_reset_sync_inst_n_1 : STD_LOGIC;
  signal write_AXI_pu_conv_in0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in10 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in11 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in12 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in13 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in14 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in15 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in16 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in17 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in18 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in19 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in2 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in20 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in21 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in22 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in23 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in24 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in25 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in26 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in27 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in28 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in29 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in3 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in30 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in31 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in4 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in5 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in6 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in7 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in8 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal write_AXI_pu_conv_in9 : STD_LOGIC_VECTOR ( 0 to 0 );
begin
u_uz_pu_con_ip_axi_lite_inst: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_axi_lite
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      \AXI4_Lite_ARADDR[3]_0\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in12_1_1\,
      \AXI4_Lite_ARADDR[4]_0\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in14_1_1\,
      \AXI4_Lite_ARADDR[4]_1\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in11_1_1\,
      \AXI4_Lite_ARADDR[4]_2\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in10_1_1\,
      \AXI4_Lite_ARADDR[7]_0\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in30_1_1\,
      \AXI4_Lite_ARADDR[7]_1\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in29_1_1\,
      \AXI4_Lite_ARADDR[7]_2\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in28_1_1\,
      \AXI4_Lite_ARADDR[7]_3\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in27_1_1\,
      \AXI4_Lite_ARADDR[7]_4\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in26_1_1\,
      \AXI4_Lite_ARADDR[7]_5\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in25_1_1\,
      \AXI4_Lite_ARADDR[8]_0\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in23_1_1\,
      \AXI4_Lite_ARADDR[8]_1\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in7_1_1\,
      \AXI4_Lite_ARADDR[8]_10\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in18_1_1\,
      \AXI4_Lite_ARADDR[8]_11\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in2_1_1\,
      \AXI4_Lite_ARADDR[8]_12\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in17_1_1\,
      \AXI4_Lite_ARADDR[8]_13\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in1_1_1\,
      \AXI4_Lite_ARADDR[8]_2\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in22_1_1\,
      \AXI4_Lite_ARADDR[8]_3\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in6_1_1\,
      \AXI4_Lite_ARADDR[8]_4\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in21_1_1\,
      \AXI4_Lite_ARADDR[8]_5\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in5_1_1\,
      \AXI4_Lite_ARADDR[8]_6\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in20_1_1\,
      \AXI4_Lite_ARADDR[8]_7\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in4_1_1\,
      \AXI4_Lite_ARADDR[8]_8\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in19_1_1\,
      \AXI4_Lite_ARADDR[8]_9\ => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in3_1_1\,
      AXI4_Lite_ARADDR_11_sp_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in8_1_1\,
      AXI4_Lite_ARADDR_3_sp_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in13_1_1\,
      AXI4_Lite_ARADDR_4_sp_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in15_1_1\,
      AXI4_Lite_ARADDR_6_sp_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in9_1_1\,
      AXI4_Lite_ARADDR_7_sp_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in31_1_1\,
      AXI4_Lite_ARADDR_8_sp_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in16_1_1\,
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(0) => AXI4_Lite_RDATA(0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(17 downto 0) => AXI4_Lite_WDATA(17 downto 0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      CEB2 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in24_1_1\,
      FSM_sequential_axi_lite_rstate_reg => AXI4_Lite_RVALID,
      IPCORE_RESETN => IPCORE_RESETN,
      OPMODE(0) => write_AXI_pu_conv_in0(0),
      Q(1) => AXI4_Lite_BVALID,
      Q(0) => AXI4_Lite_WREADY,
      \data_reg_AXI_pu_conv_in10_1_1_reg[0]\(0) => write_AXI_pu_conv_in10(0),
      \data_reg_AXI_pu_conv_in11_1_1_reg[0]\(0) => write_AXI_pu_conv_in11(0),
      \data_reg_AXI_pu_conv_in12_1_1_reg[0]\(0) => write_AXI_pu_conv_in12(0),
      \data_reg_AXI_pu_conv_in13_1_1_reg[0]\(0) => write_AXI_pu_conv_in13(0),
      \data_reg_AXI_pu_conv_in14_1_1_reg[0]\(0) => write_AXI_pu_conv_in14(0),
      \data_reg_AXI_pu_conv_in15_1_1_reg[0]\(0) => write_AXI_pu_conv_in15(0),
      \data_reg_AXI_pu_conv_in16_1_1_reg[0]\(0) => write_AXI_pu_conv_in16(0),
      \data_reg_AXI_pu_conv_in17_1_1_reg[0]\(0) => write_AXI_pu_conv_in17(0),
      \data_reg_AXI_pu_conv_in18_1_1_reg[0]\(0) => write_AXI_pu_conv_in18(0),
      \data_reg_AXI_pu_conv_in19_1_1_reg[0]\(0) => write_AXI_pu_conv_in19(0),
      \data_reg_AXI_pu_conv_in1_1_1_reg[0]\(0) => write_AXI_pu_conv_in1(0),
      \data_reg_AXI_pu_conv_in20_1_1_reg[0]\(0) => write_AXI_pu_conv_in20(0),
      \data_reg_AXI_pu_conv_in21_1_1_reg[0]\(0) => write_AXI_pu_conv_in21(0),
      \data_reg_AXI_pu_conv_in22_1_1_reg[0]\(0) => write_AXI_pu_conv_in22(0),
      \data_reg_AXI_pu_conv_in23_1_1_reg[0]\(0) => write_AXI_pu_conv_in23(0),
      \data_reg_AXI_pu_conv_in24_1_1_reg[0]\(0) => write_AXI_pu_conv_in24(0),
      \data_reg_AXI_pu_conv_in25_1_1_reg[0]\(0) => write_AXI_pu_conv_in25(0),
      \data_reg_AXI_pu_conv_in26_1_1_reg[0]\(0) => write_AXI_pu_conv_in26(0),
      \data_reg_AXI_pu_conv_in27_1_1_reg[0]\(0) => write_AXI_pu_conv_in27(0),
      \data_reg_AXI_pu_conv_in28_1_1_reg[0]\(0) => write_AXI_pu_conv_in28(0),
      \data_reg_AXI_pu_conv_in29_1_1_reg[0]\(0) => write_AXI_pu_conv_in29(0),
      \data_reg_AXI_pu_conv_in2_1_1_reg[0]\(0) => write_AXI_pu_conv_in2(0),
      \data_reg_AXI_pu_conv_in30_1_1_reg[0]\(0) => write_AXI_pu_conv_in30(0),
      \data_reg_AXI_pu_conv_in31_1_1_reg[0]\(0) => write_AXI_pu_conv_in31(0),
      \data_reg_AXI_pu_conv_in3_1_1_reg[0]\(0) => write_AXI_pu_conv_in3(0),
      \data_reg_AXI_pu_conv_in4_1_1_reg[0]\(0) => write_AXI_pu_conv_in4(0),
      \data_reg_AXI_pu_conv_in5_1_1_reg[0]\(0) => write_AXI_pu_conv_in5(0),
      \data_reg_AXI_pu_conv_in6_1_1_reg[0]\(0) => write_AXI_pu_conv_in6(0),
      \data_reg_AXI_pu_conv_in7_1_1_reg[0]\(0) => write_AXI_pu_conv_in7(0),
      \data_reg_AXI_pu_conv_in8_1_1_reg[0]\(0) => write_AXI_pu_conv_in8(0),
      \data_reg_AXI_pu_conv_in9_1_1_reg[0]\(0) => write_AXI_pu_conv_in9(0),
      \read_reg_ip_timestamp_reg[31]\ => u_uz_pu_con_ip_reset_sync_inst_n_1,
      reset => reset,
      reset_in => reset_in,
      soft_reset => \u_uz_pu_con_ip_axi_lite_module_inst/soft_reset\,
      \wdata_reg[17]\(16) => u_uz_pu_con_ip_axi_lite_inst_n_72,
      \wdata_reg[17]\(15) => u_uz_pu_con_ip_axi_lite_inst_n_73,
      \wdata_reg[17]\(14) => u_uz_pu_con_ip_axi_lite_inst_n_74,
      \wdata_reg[17]\(13) => u_uz_pu_con_ip_axi_lite_inst_n_75,
      \wdata_reg[17]\(12) => u_uz_pu_con_ip_axi_lite_inst_n_76,
      \wdata_reg[17]\(11) => u_uz_pu_con_ip_axi_lite_inst_n_77,
      \wdata_reg[17]\(10) => u_uz_pu_con_ip_axi_lite_inst_n_78,
      \wdata_reg[17]\(9) => u_uz_pu_con_ip_axi_lite_inst_n_79,
      \wdata_reg[17]\(8) => u_uz_pu_con_ip_axi_lite_inst_n_80,
      \wdata_reg[17]\(7) => u_uz_pu_con_ip_axi_lite_inst_n_81,
      \wdata_reg[17]\(6) => u_uz_pu_con_ip_axi_lite_inst_n_82,
      \wdata_reg[17]\(5) => u_uz_pu_con_ip_axi_lite_inst_n_83,
      \wdata_reg[17]\(4) => u_uz_pu_con_ip_axi_lite_inst_n_84,
      \wdata_reg[17]\(3) => u_uz_pu_con_ip_axi_lite_inst_n_85,
      \wdata_reg[17]\(2) => u_uz_pu_con_ip_axi_lite_inst_n_86,
      \wdata_reg[17]\(1) => u_uz_pu_con_ip_axi_lite_inst_n_87,
      \wdata_reg[17]\(0) => u_uz_pu_con_ip_axi_lite_inst_n_88,
      wr_enb_1_reg => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in0_1_1\
    );
u_uz_pu_con_ip_dut_inst: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_dut
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI_pu_conv_in31(16) => u_uz_pu_con_ip_axi_lite_inst_n_72,
      AXI_pu_conv_in31(15) => u_uz_pu_con_ip_axi_lite_inst_n_73,
      AXI_pu_conv_in31(14) => u_uz_pu_con_ip_axi_lite_inst_n_74,
      AXI_pu_conv_in31(13) => u_uz_pu_con_ip_axi_lite_inst_n_75,
      AXI_pu_conv_in31(12) => u_uz_pu_con_ip_axi_lite_inst_n_76,
      AXI_pu_conv_in31(11) => u_uz_pu_con_ip_axi_lite_inst_n_77,
      AXI_pu_conv_in31(10) => u_uz_pu_con_ip_axi_lite_inst_n_78,
      AXI_pu_conv_in31(9) => u_uz_pu_con_ip_axi_lite_inst_n_79,
      AXI_pu_conv_in31(8) => u_uz_pu_con_ip_axi_lite_inst_n_80,
      AXI_pu_conv_in31(7) => u_uz_pu_con_ip_axi_lite_inst_n_81,
      AXI_pu_conv_in31(6) => u_uz_pu_con_ip_axi_lite_inst_n_82,
      AXI_pu_conv_in31(5) => u_uz_pu_con_ip_axi_lite_inst_n_83,
      AXI_pu_conv_in31(4) => u_uz_pu_con_ip_axi_lite_inst_n_84,
      AXI_pu_conv_in31(3) => u_uz_pu_con_ip_axi_lite_inst_n_85,
      AXI_pu_conv_in31(2) => u_uz_pu_con_ip_axi_lite_inst_n_86,
      AXI_pu_conv_in31(1) => u_uz_pu_con_ip_axi_lite_inst_n_87,
      AXI_pu_conv_in31(0) => u_uz_pu_con_ip_axi_lite_inst_n_88,
      CEB2 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in24_1_1\,
      DSP_ALU_INST => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in0_1_1\,
      DSP_ALU_INST_0 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in1_1_1\,
      DSP_ALU_INST_1 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in2_1_1\,
      DSP_ALU_INST_10 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in11_1_1\,
      DSP_ALU_INST_11 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in12_1_1\,
      DSP_ALU_INST_12 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in13_1_1\,
      DSP_ALU_INST_13 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in14_1_1\,
      DSP_ALU_INST_14 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in15_1_1\,
      DSP_ALU_INST_15 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in16_1_1\,
      DSP_ALU_INST_16 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in17_1_1\,
      DSP_ALU_INST_17 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in18_1_1\,
      DSP_ALU_INST_18 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in19_1_1\,
      DSP_ALU_INST_19 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in20_1_1\,
      DSP_ALU_INST_2 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in3_1_1\,
      DSP_ALU_INST_20 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in21_1_1\,
      DSP_ALU_INST_21 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in22_1_1\,
      DSP_ALU_INST_22 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in23_1_1\,
      DSP_ALU_INST_23 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in25_1_1\,
      DSP_ALU_INST_24 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in26_1_1\,
      DSP_ALU_INST_25 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in27_1_1\,
      DSP_ALU_INST_26 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in28_1_1\,
      DSP_ALU_INST_27 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in29_1_1\,
      DSP_ALU_INST_28 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in30_1_1\,
      DSP_ALU_INST_29 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in31_1_1\,
      DSP_ALU_INST_3 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in4_1_1\,
      DSP_ALU_INST_4 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in5_1_1\,
      DSP_ALU_INST_5 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in6_1_1\,
      DSP_ALU_INST_6 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in7_1_1\,
      DSP_ALU_INST_7 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in8_1_1\,
      DSP_ALU_INST_8 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in9_1_1\,
      DSP_ALU_INST_9 => \u_uz_pu_con_ip_addr_decoder_inst/reg_enb_AXI_pu_conv_in10_1_1\,
      IPCORE_CLK => IPCORE_CLK,
      OPMODE(0) => write_AXI_pu_conv_in0(0),
      adc_trigger => adc_trigger,
      in0(26 downto 0) => in0(26 downto 0),
      in1(26 downto 0) => in1(26 downto 0),
      in10(26 downto 0) => in10(26 downto 0),
      in11(26 downto 0) => in11(26 downto 0),
      in12(26 downto 0) => in12(26 downto 0),
      in13(26 downto 0) => in13(26 downto 0),
      in14(26 downto 0) => in14(26 downto 0),
      in15(26 downto 0) => in15(26 downto 0),
      in16(26 downto 0) => in16(26 downto 0),
      in17(26 downto 0) => in17(26 downto 0),
      in18(26 downto 0) => in18(26 downto 0),
      in19(26 downto 0) => in19(26 downto 0),
      in2(26 downto 0) => in2(26 downto 0),
      in20(26 downto 0) => in20(26 downto 0),
      in21(26 downto 0) => in21(26 downto 0),
      in22(26 downto 0) => in22(26 downto 0),
      in23(26 downto 0) => in23(26 downto 0),
      in24(26 downto 0) => in24(26 downto 0),
      in25(26 downto 0) => in25(26 downto 0),
      in26(26 downto 0) => in26(26 downto 0),
      in27(26 downto 0) => in27(26 downto 0),
      in28(26 downto 0) => in28(26 downto 0),
      in29(26 downto 0) => in29(26 downto 0),
      in3(26 downto 0) => in3(26 downto 0),
      in30(26 downto 0) => in30(26 downto 0),
      in31(26 downto 0) => in31(26 downto 0),
      in4(26 downto 0) => in4(26 downto 0),
      in5(26 downto 0) => in5(26 downto 0),
      in6(26 downto 0) => in6(26 downto 0),
      in7(26 downto 0) => in7(26 downto 0),
      in8(26 downto 0) => in8(26 downto 0),
      in9(26 downto 0) => in9(26 downto 0),
      out0(17 downto 0) => out0(17 downto 0),
      out1(17 downto 0) => out1(17 downto 0),
      out10(17 downto 0) => out10(17 downto 0),
      \out10[17]\(0) => write_AXI_pu_conv_in10(0),
      out11(17 downto 0) => out11(17 downto 0),
      \out11[17]\(0) => write_AXI_pu_conv_in11(0),
      out12(17 downto 0) => out12(17 downto 0),
      \out12[17]\(0) => write_AXI_pu_conv_in12(0),
      out13(17 downto 0) => out13(17 downto 0),
      \out13[17]\(0) => write_AXI_pu_conv_in13(0),
      out14(17 downto 0) => out14(17 downto 0),
      \out14[17]\(0) => write_AXI_pu_conv_in14(0),
      out15(17 downto 0) => out15(17 downto 0),
      \out15[17]\(0) => write_AXI_pu_conv_in15(0),
      out16(17 downto 0) => out16(17 downto 0),
      \out16[17]\(0) => write_AXI_pu_conv_in16(0),
      out17(17 downto 0) => out17(17 downto 0),
      \out17[17]\(0) => write_AXI_pu_conv_in17(0),
      out18(17 downto 0) => out18(17 downto 0),
      \out18[17]\(0) => write_AXI_pu_conv_in18(0),
      out19(17 downto 0) => out19(17 downto 0),
      \out19[17]\(0) => write_AXI_pu_conv_in19(0),
      \out1[17]\(0) => write_AXI_pu_conv_in1(0),
      out2(17 downto 0) => out2(17 downto 0),
      out20(17 downto 0) => out20(17 downto 0),
      \out20[17]\(0) => write_AXI_pu_conv_in20(0),
      out21(17 downto 0) => out21(17 downto 0),
      \out21[17]\(0) => write_AXI_pu_conv_in21(0),
      out22(17 downto 0) => out22(17 downto 0),
      \out22[17]\(0) => write_AXI_pu_conv_in22(0),
      out23(17 downto 0) => out23(17 downto 0),
      \out23[17]\(0) => write_AXI_pu_conv_in23(0),
      out24(17 downto 0) => out24(17 downto 0),
      \out24[17]\(0) => write_AXI_pu_conv_in24(0),
      out25(17 downto 0) => out25(17 downto 0),
      \out25[17]\(0) => write_AXI_pu_conv_in25(0),
      out26(17 downto 0) => out26(17 downto 0),
      \out26[17]\(0) => write_AXI_pu_conv_in26(0),
      out27(17 downto 0) => out27(17 downto 0),
      \out27[17]\(0) => write_AXI_pu_conv_in27(0),
      out28(17 downto 0) => out28(17 downto 0),
      \out28[17]\(0) => write_AXI_pu_conv_in28(0),
      out29(17 downto 0) => out29(17 downto 0),
      \out29[17]\(0) => write_AXI_pu_conv_in29(0),
      \out2[17]\(0) => write_AXI_pu_conv_in2(0),
      out3(17 downto 0) => out3(17 downto 0),
      out30(17 downto 0) => out30(17 downto 0),
      \out30[17]\(0) => write_AXI_pu_conv_in30(0),
      out31(17 downto 0) => out31(17 downto 0),
      \out31[17]\(0) => write_AXI_pu_conv_in31(0),
      \out3[17]\(0) => write_AXI_pu_conv_in3(0),
      out4(17 downto 0) => out4(17 downto 0),
      \out4[17]\(0) => write_AXI_pu_conv_in4(0),
      out5(17 downto 0) => out5(17 downto 0),
      \out5[17]\(0) => write_AXI_pu_conv_in5(0),
      out6(17 downto 0) => out6(17 downto 0),
      \out6[17]\(0) => write_AXI_pu_conv_in6(0),
      out7(17 downto 0) => out7(17 downto 0),
      \out7[17]\(0) => write_AXI_pu_conv_in7(0),
      out8(17 downto 0) => out8(17 downto 0),
      \out8[17]\(0) => write_AXI_pu_conv_in8(0),
      out9(17 downto 0) => out9(17 downto 0),
      \out9[17]\(0) => write_AXI_pu_conv_in9(0),
      reset => reset
    );
u_uz_pu_con_ip_reset_sync_inst: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip_reset_sync
     port map (
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      reset => reset,
      reset_in => reset_in,
      reset_out_reg_0 => u_uz_pu_con_ip_reset_sync_inst_n_1,
      soft_reset => \u_uz_pu_con_ip_axi_lite_module_inst/soft_reset\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_pu_con_ip_0_1 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    in0 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in1 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in2 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in3 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in4 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in5 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in6 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in7 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in8 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in9 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in10 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in11 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in12 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in13 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in14 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in15 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in16 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in17 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in18 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in19 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in20 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in21 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in22 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in23 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in24 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in25 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in26 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in27 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in28 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in29 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in30 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in31 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    adc_trigger : in STD_LOGIC;
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
    out0 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out1 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out2 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out3 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out4 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out5 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out6 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out7 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out8 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out9 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out10 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out11 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out12 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out13 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out14 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out15 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out16 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out17 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out18 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out19 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out20 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out21 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out22 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out23 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out24 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out25 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out26 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out27 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out28 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out29 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out30 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out31 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out_valid : out STD_LOGIC;
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
  attribute NotValidForBitStream of zusys_uz_pu_con_ip_0_1 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_uz_pu_con_ip_0_1 : entity is "zusys_uz_pu_con_ip_0_1,uz_pu_con_ip,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_uz_pu_con_ip_0_1 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_uz_pu_con_ip_0_1 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of zusys_uz_pu_con_ip_0_1 : entity is "uz_pu_con_ip,Vivado 2020.1.1";
end zusys_uz_pu_con_ip_0_1;

architecture STRUCTURE of zusys_uz_pu_con_ip_0_1 is
  signal \<const0>\ : STD_LOGIC;
  signal \^axi4_lite_rdata\ : STD_LOGIC_VECTOR ( 25 to 25 );
  signal \^adc_trigger\ : STD_LOGIC;
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
  AXI4_Lite_RDATA(31) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(30) <= \<const0>\;
  AXI4_Lite_RDATA(29) <= \<const0>\;
  AXI4_Lite_RDATA(28) <= \<const0>\;
  AXI4_Lite_RDATA(27) <= \<const0>\;
  AXI4_Lite_RDATA(26) <= \<const0>\;
  AXI4_Lite_RDATA(25) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(24) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(23) <= \<const0>\;
  AXI4_Lite_RDATA(22) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(21) <= \<const0>\;
  AXI4_Lite_RDATA(20) <= \<const0>\;
  AXI4_Lite_RDATA(19) <= \<const0>\;
  AXI4_Lite_RDATA(18) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(17) <= \<const0>\;
  AXI4_Lite_RDATA(16) <= \<const0>\;
  AXI4_Lite_RDATA(15) <= \<const0>\;
  AXI4_Lite_RDATA(14) <= \<const0>\;
  AXI4_Lite_RDATA(13) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(12) <= \<const0>\;
  AXI4_Lite_RDATA(11) <= \<const0>\;
  AXI4_Lite_RDATA(10) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(9) <= \<const0>\;
  AXI4_Lite_RDATA(8) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(7) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(6) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(5) <= \<const0>\;
  AXI4_Lite_RDATA(4) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(3) <= \<const0>\;
  AXI4_Lite_RDATA(2) <= \<const0>\;
  AXI4_Lite_RDATA(1) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RDATA(0) <= \^axi4_lite_rdata\(25);
  AXI4_Lite_RRESP(1) <= \<const0>\;
  AXI4_Lite_RRESP(0) <= \<const0>\;
  \^adc_trigger\ <= adc_trigger;
  out_valid <= \^adc_trigger\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_uz_pu_con_ip_0_1_uz_pu_con_ip
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
      AXI4_Lite_RDATA(0) => \^axi4_lite_rdata\(25),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_RVALID => AXI4_Lite_RVALID,
      AXI4_Lite_WDATA(17 downto 0) => AXI4_Lite_WDATA(17 downto 0),
      AXI4_Lite_WREADY => AXI4_Lite_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      adc_trigger => \^adc_trigger\,
      in0(26 downto 0) => in0(26 downto 0),
      in1(26 downto 0) => in1(26 downto 0),
      in10(26 downto 0) => in10(26 downto 0),
      in11(26 downto 0) => in11(26 downto 0),
      in12(26 downto 0) => in12(26 downto 0),
      in13(26 downto 0) => in13(26 downto 0),
      in14(26 downto 0) => in14(26 downto 0),
      in15(26 downto 0) => in15(26 downto 0),
      in16(26 downto 0) => in16(26 downto 0),
      in17(26 downto 0) => in17(26 downto 0),
      in18(26 downto 0) => in18(26 downto 0),
      in19(26 downto 0) => in19(26 downto 0),
      in2(26 downto 0) => in2(26 downto 0),
      in20(26 downto 0) => in20(26 downto 0),
      in21(26 downto 0) => in21(26 downto 0),
      in22(26 downto 0) => in22(26 downto 0),
      in23(26 downto 0) => in23(26 downto 0),
      in24(26 downto 0) => in24(26 downto 0),
      in25(26 downto 0) => in25(26 downto 0),
      in26(26 downto 0) => in26(26 downto 0),
      in27(26 downto 0) => in27(26 downto 0),
      in28(26 downto 0) => in28(26 downto 0),
      in29(26 downto 0) => in29(26 downto 0),
      in3(26 downto 0) => in3(26 downto 0),
      in30(26 downto 0) => in30(26 downto 0),
      in31(26 downto 0) => in31(26 downto 0),
      in4(26 downto 0) => in4(26 downto 0),
      in5(26 downto 0) => in5(26 downto 0),
      in6(26 downto 0) => in6(26 downto 0),
      in7(26 downto 0) => in7(26 downto 0),
      in8(26 downto 0) => in8(26 downto 0),
      in9(26 downto 0) => in9(26 downto 0),
      out0(17 downto 0) => out0(17 downto 0),
      out1(17 downto 0) => out1(17 downto 0),
      out10(17 downto 0) => out10(17 downto 0),
      out11(17 downto 0) => out11(17 downto 0),
      out12(17 downto 0) => out12(17 downto 0),
      out13(17 downto 0) => out13(17 downto 0),
      out14(17 downto 0) => out14(17 downto 0),
      out15(17 downto 0) => out15(17 downto 0),
      out16(17 downto 0) => out16(17 downto 0),
      out17(17 downto 0) => out17(17 downto 0),
      out18(17 downto 0) => out18(17 downto 0),
      out19(17 downto 0) => out19(17 downto 0),
      out2(17 downto 0) => out2(17 downto 0),
      out20(17 downto 0) => out20(17 downto 0),
      out21(17 downto 0) => out21(17 downto 0),
      out22(17 downto 0) => out22(17 downto 0),
      out23(17 downto 0) => out23(17 downto 0),
      out24(17 downto 0) => out24(17 downto 0),
      out25(17 downto 0) => out25(17 downto 0),
      out26(17 downto 0) => out26(17 downto 0),
      out27(17 downto 0) => out27(17 downto 0),
      out28(17 downto 0) => out28(17 downto 0),
      out29(17 downto 0) => out29(17 downto 0),
      out3(17 downto 0) => out3(17 downto 0),
      out30(17 downto 0) => out30(17 downto 0),
      out31(17 downto 0) => out31(17 downto 0),
      out4(17 downto 0) => out4(17 downto 0),
      out5(17 downto 0) => out5(17 downto 0),
      out6(17 downto 0) => out6(17 downto 0),
      out7(17 downto 0) => out7(17 downto 0),
      out8(17 downto 0) => out8(17 downto 0),
      out9(17 downto 0) => out9(17 downto 0)
    );
end STRUCTURE;
