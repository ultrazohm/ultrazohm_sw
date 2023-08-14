-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:48:01 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_top_npc_state_machine_0_0/zusys_top_npc_state_machine_0_0_sim_netlist.vhdl
-- Design      : zusys_top_npc_state_machine_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_top_npc_state_machine_0_0_npc_phase_state_machine is
  port (
    Q : out STD_LOGIC_VECTOR ( 2 downto 0 );
    A_S2 : out STD_LOGIC;
    A_S3 : out STD_LOGIC;
    switching_signals : in STD_LOGIC_VECTOR ( 1 downto 0 );
    enable : in STD_LOGIC;
    deadtime : in STD_LOGIC_VECTOR ( 9 downto 0 );
    clock : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_top_npc_state_machine_0_0_npc_phase_state_machine : entity is "npc_phase_state_machine";
end zusys_top_npc_state_machine_0_0_npc_phase_state_machine;

architecture STRUCTURE of zusys_top_npc_state_machine_0_0_npc_phase_state_machine is
  signal \FSM_onehot_phase_state[0]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[0]_i_2_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[1]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[1]_i_2_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[2]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[2]_i_2_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_2_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_3_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[4]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[5]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[5]_i_2_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state_reg_n_0_[0]\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal counter : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \counter[0]_i_1_n_0\ : STD_LOGIC;
  signal \counter[1]_i_1_n_0\ : STD_LOGIC;
  signal \counter[2]_i_1_n_0\ : STD_LOGIC;
  signal \counter[3]_i_1_n_0\ : STD_LOGIC;
  signal \counter[3]_i_2_n_0\ : STD_LOGIC;
  signal \counter[4]_i_1_n_0\ : STD_LOGIC;
  signal \counter[4]_i_2_n_0\ : STD_LOGIC;
  signal \counter[5]_i_1_n_0\ : STD_LOGIC;
  signal \counter[5]_i_2_n_0\ : STD_LOGIC;
  signal \counter[6]_i_1_n_0\ : STD_LOGIC;
  signal \counter[6]_i_2_n_0\ : STD_LOGIC;
  signal \counter[7]_i_1_n_0\ : STD_LOGIC;
  signal \counter[7]_i_2_n_0\ : STD_LOGIC;
  signal \counter[8]_i_1_n_0\ : STD_LOGIC;
  signal \counter[8]_i_2_n_0\ : STD_LOGIC;
  signal \counter[9]_i_2_n_0\ : STD_LOGIC;
  signal \counter[9]_i_3_n_0\ : STD_LOGIC;
  signal \counter[9]_i_4_n_0\ : STD_LOGIC;
  signal \counter[9]_i_5_n_0\ : STD_LOGIC;
  signal \counter[9]_i_6_n_0\ : STD_LOGIC;
  signal \counter[9]_i_7_n_0\ : STD_LOGIC;
  signal counter_0 : STD_LOGIC;
  signal p_1_in : STD_LOGIC;
  signal p_2_in : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of A_S2_INST_0 : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of A_S3_INST_0 : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[0]_i_2\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[1]_i_2\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[2]_i_2\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[3]_i_2\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[3]_i_3\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[5]_i_2\ : label is "soft_lutpair2";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[0]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[1]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[2]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[3]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[4]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[5]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute SOFT_HLUTNM of \counter[3]_i_2\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \counter[4]_i_2\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \counter[5]_i_2\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \counter[6]_i_2\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \counter[8]_i_2\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \counter[9]_i_3\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \counter[9]_i_6\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \counter[9]_i_7\ : label is "soft_lutpair5";
begin
  Q(2 downto 0) <= \^q\(2 downto 0);
A_S2_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(2),
      I1 => p_1_in,
      I2 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      O => A_S2
    );
A_S3_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(1),
      I1 => p_1_in,
      I2 => p_2_in,
      O => A_S3
    );
\FSM_onehot_phase_state[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFD8D8D8"
    )
        port map (
      I0 => \FSM_onehot_phase_state[0]_i_2_n_0\,
      I1 => \^q\(2),
      I2 => \FSM_onehot_phase_state[3]_i_3_n_0\,
      I3 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I4 => \FSM_onehot_phase_state[5]_i_2_n_0\,
      O => \FSM_onehot_phase_state[0]_i_1_n_0\
    );
\FSM_onehot_phase_state[0]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => enable,
      O => \FSM_onehot_phase_state[0]_i_2_n_0\
    );
\FSM_onehot_phase_state[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFD8D8D8"
    )
        port map (
      I0 => \FSM_onehot_phase_state[1]_i_2_n_0\,
      I1 => \^q\(1),
      I2 => \FSM_onehot_phase_state[3]_i_3_n_0\,
      I3 => p_2_in,
      I4 => \FSM_onehot_phase_state[5]_i_2_n_0\,
      O => \FSM_onehot_phase_state[1]_i_1_n_0\
    );
\FSM_onehot_phase_state[1]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => enable,
      O => \FSM_onehot_phase_state[1]_i_2_n_0\
    );
\FSM_onehot_phase_state[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"44F4F44444444444"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2_n_0\,
      I1 => \FSM_onehot_phase_state[2]_i_2_n_0\,
      I2 => \FSM_onehot_phase_state[3]_i_3_n_0\,
      I3 => switching_signals(1),
      I4 => switching_signals(0),
      I5 => enable,
      O => \FSM_onehot_phase_state[2]_i_1_n_0\
    );
\FSM_onehot_phase_state[2]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F7E00000"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => p_2_in,
      I3 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I4 => enable,
      O => \FSM_onehot_phase_state[2]_i_2_n_0\
    );
\FSM_onehot_phase_state[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFFF00004440"
    )
        port map (
      I0 => \FSM_onehot_phase_state[3]_i_2_n_0\,
      I1 => counter(0),
      I2 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I3 => p_2_in,
      I4 => enable,
      I5 => \FSM_onehot_phase_state[3]_i_3_n_0\,
      O => \FSM_onehot_phase_state[3]_i_1_n_0\
    );
\FSM_onehot_phase_state[3]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => counter(8),
      I1 => \counter[7]_i_2_n_0\,
      I2 => counter(7),
      I3 => counter(9),
      O => \FSM_onehot_phase_state[3]_i_2_n_0\
    );
\FSM_onehot_phase_state[3]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF0001"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(0),
      O => \FSM_onehot_phase_state[3]_i_3_n_0\
    );
\FSM_onehot_phase_state[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000F000000040000"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2_n_0\,
      I1 => p_2_in,
      I2 => switching_signals(1),
      I3 => switching_signals(0),
      I4 => enable,
      I5 => \^q\(1),
      O => \FSM_onehot_phase_state[4]_i_1_n_0\
    );
\FSM_onehot_phase_state[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F000000040000000"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2_n_0\,
      I1 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I2 => switching_signals(1),
      I3 => switching_signals(0),
      I4 => enable,
      I5 => \^q\(2),
      O => \FSM_onehot_phase_state[5]_i_1_n_0\
    );
\FSM_onehot_phase_state[5]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEFFFF"
    )
        port map (
      I0 => counter(9),
      I1 => counter(7),
      I2 => \counter[7]_i_2_n_0\,
      I3 => counter(8),
      I4 => counter(0),
      O => \FSM_onehot_phase_state[5]_i_2_n_0\
    );
\FSM_onehot_phase_state_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[0]_i_1_n_0\,
      Q => \FSM_onehot_phase_state_reg_n_0_[0]\,
      R => '0'
    );
\FSM_onehot_phase_state_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[1]_i_1_n_0\,
      Q => p_2_in,
      R => '0'
    );
\FSM_onehot_phase_state_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[2]_i_1_n_0\,
      Q => p_1_in,
      R => '0'
    );
\FSM_onehot_phase_state_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[3]_i_1_n_0\,
      Q => \^q\(0),
      R => '0'
    );
\FSM_onehot_phase_state_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[4]_i_1_n_0\,
      Q => \^q\(1),
      R => '0'
    );
\FSM_onehot_phase_state_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[5]_i_1_n_0\,
      Q => \^q\(2),
      R => '0'
    );
\counter[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAA8FFFFAAAAAAAA"
    )
        port map (
      I0 => deadtime(0),
      I1 => \^q\(0),
      I2 => \^q\(2),
      I3 => \^q\(1),
      I4 => counter(0),
      I5 => \counter[9]_i_4_n_0\,
      O => \counter[0]_i_1_n_0\
    );
\counter[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F8F8F8888F8F8F88"
    )
        port map (
      I0 => \counter[9]_i_6_n_0\,
      I1 => deadtime(1),
      I2 => counter(1),
      I3 => p_2_in,
      I4 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I5 => counter(0),
      O => \counter[1]_i_1_n_0\
    );
\counter[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF888888F8888F88"
    )
        port map (
      I0 => \counter[9]_i_6_n_0\,
      I1 => deadtime(2),
      I2 => counter(0),
      I3 => \counter[9]_i_4_n_0\,
      I4 => counter(2),
      I5 => counter(1),
      O => \counter[2]_i_1_n_0\
    );
\counter[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF88888888F8888"
    )
        port map (
      I0 => \counter[9]_i_6_n_0\,
      I1 => deadtime(3),
      I2 => counter(0),
      I3 => \counter[3]_i_2_n_0\,
      I4 => \counter[9]_i_4_n_0\,
      I5 => counter(3),
      O => \counter[3]_i_1_n_0\
    );
\counter[3]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => counter(1),
      I1 => counter(2),
      O => \counter[3]_i_2_n_0\
    );
\counter[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF88888888F8888"
    )
        port map (
      I0 => \counter[9]_i_6_n_0\,
      I1 => deadtime(4),
      I2 => counter(0),
      I3 => \counter[4]_i_2_n_0\,
      I4 => \counter[9]_i_4_n_0\,
      I5 => counter(4),
      O => \counter[4]_i_1_n_0\
    );
\counter[4]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => counter(2),
      I1 => counter(1),
      I2 => counter(3),
      O => \counter[4]_i_2_n_0\
    );
\counter[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => counter(0),
      I1 => \counter[9]_i_4_n_0\,
      I2 => counter(5),
      I3 => deadtime(5),
      I4 => \counter[9]_i_6_n_0\,
      I5 => \counter[5]_i_2_n_0\,
      O => \counter[5]_i_1_n_0\
    );
\counter[5]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => counter(3),
      I1 => counter(1),
      I2 => counter(2),
      I3 => counter(4),
      O => \counter[5]_i_2_n_0\
    );
\counter[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => counter(0),
      I1 => \counter[9]_i_4_n_0\,
      I2 => counter(6),
      I3 => deadtime(6),
      I4 => \counter[9]_i_6_n_0\,
      I5 => \counter[6]_i_2_n_0\,
      O => \counter[6]_i_1_n_0\
    );
\counter[6]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => counter(4),
      I1 => counter(2),
      I2 => counter(1),
      I3 => counter(3),
      I4 => counter(5),
      O => \counter[6]_i_2_n_0\
    );
\counter[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => counter(0),
      I1 => \counter[9]_i_4_n_0\,
      I2 => counter(7),
      I3 => deadtime(7),
      I4 => \counter[9]_i_6_n_0\,
      I5 => \counter[7]_i_2_n_0\,
      O => \counter[7]_i_1_n_0\
    );
\counter[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => counter(5),
      I1 => counter(3),
      I2 => counter(1),
      I3 => counter(2),
      I4 => counter(4),
      I5 => counter(6),
      O => \counter[7]_i_2_n_0\
    );
\counter[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => counter(0),
      I1 => \counter[9]_i_4_n_0\,
      I2 => counter(8),
      I3 => deadtime(8),
      I4 => \counter[9]_i_6_n_0\,
      I5 => \counter[8]_i_2_n_0\,
      O => \counter[8]_i_1_n_0\
    );
\counter[8]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \counter[7]_i_2_n_0\,
      I1 => counter(7),
      O => \counter[8]_i_2_n_0\
    );
\counter[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFF808"
    )
        port map (
      I0 => \^q\(0),
      I1 => enable,
      I2 => \counter[9]_i_3_n_0\,
      I3 => \^q\(1),
      I4 => \counter[9]_i_4_n_0\,
      I5 => \counter[9]_i_5_n_0\,
      O => counter_0
    );
\counter[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => counter(0),
      I1 => \counter[9]_i_4_n_0\,
      I2 => counter(9),
      I3 => deadtime(9),
      I4 => \counter[9]_i_6_n_0\,
      I5 => \counter[9]_i_7_n_0\,
      O => \counter[9]_i_2_n_0\
    );
\counter[9]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => switching_signals(0),
      I1 => switching_signals(1),
      O => \counter[9]_i_3_n_0\
    );
\counter[9]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      O => \counter[9]_i_4_n_0\
    );
\counter[9]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EAFF6AFFEBAA6BAA"
    )
        port map (
      I0 => \^q\(2),
      I1 => switching_signals(1),
      I2 => switching_signals(0),
      I3 => enable,
      I4 => \^q\(0),
      I5 => \^q\(1),
      O => \counter[9]_i_5_n_0\
    );
\counter[9]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFF1"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      I2 => \^q\(0),
      I3 => \^q\(2),
      I4 => \^q\(1),
      O => \counter[9]_i_6_n_0\
    );
\counter[9]_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => counter(7),
      I1 => \counter[7]_i_2_n_0\,
      I2 => counter(8),
      O => \counter[9]_i_7_n_0\
    );
\counter_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[0]_i_1_n_0\,
      Q => counter(0),
      R => '0'
    );
\counter_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[1]_i_1_n_0\,
      Q => counter(1),
      R => '0'
    );
\counter_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[2]_i_1_n_0\,
      Q => counter(2),
      R => '0'
    );
\counter_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[3]_i_1_n_0\,
      Q => counter(3),
      R => '0'
    );
\counter_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[4]_i_1_n_0\,
      Q => counter(4),
      R => '0'
    );
\counter_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[5]_i_1_n_0\,
      Q => counter(5),
      R => '0'
    );
\counter_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[6]_i_1_n_0\,
      Q => counter(6),
      R => '0'
    );
\counter_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[7]_i_1_n_0\,
      Q => counter(7),
      R => '0'
    );
\counter_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[8]_i_1_n_0\,
      Q => counter(8),
      R => '0'
    );
\counter_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter_0,
      D => \counter[9]_i_2_n_0\,
      Q => counter(9),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0 is
  port (
    Q : out STD_LOGIC_VECTOR ( 2 downto 0 );
    B_S2 : out STD_LOGIC;
    B_S3 : out STD_LOGIC;
    switching_signals : in STD_LOGIC_VECTOR ( 1 downto 0 );
    enable : in STD_LOGIC;
    deadtime : in STD_LOGIC_VECTOR ( 9 downto 0 );
    clock : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0 : entity is "npc_phase_state_machine";
end zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0;

architecture STRUCTURE of zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0 is
  signal \FSM_onehot_phase_state[0]_i_1__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[0]_i_2__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[1]_i_1__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[1]_i_2__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[2]_i_1__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[2]_i_2__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_1__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_2__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_3__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[4]_i_1__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[5]_i_1__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[5]_i_2__0_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state_reg_n_0_[0]\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal counter : STD_LOGIC;
  signal \counter[0]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[1]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[2]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[3]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[3]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[4]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[4]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[5]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[5]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[6]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[6]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[7]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[7]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[8]_i_1__0_n_0\ : STD_LOGIC;
  signal \counter[8]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[9]_i_2__0_n_0\ : STD_LOGIC;
  signal \counter[9]_i_3__0_n_0\ : STD_LOGIC;
  signal \counter[9]_i_4__0_n_0\ : STD_LOGIC;
  signal \counter[9]_i_5__0_n_0\ : STD_LOGIC;
  signal \counter[9]_i_6__0_n_0\ : STD_LOGIC;
  signal \counter[9]_i_7__0_n_0\ : STD_LOGIC;
  signal \counter_reg_n_0_[0]\ : STD_LOGIC;
  signal \counter_reg_n_0_[1]\ : STD_LOGIC;
  signal \counter_reg_n_0_[2]\ : STD_LOGIC;
  signal \counter_reg_n_0_[3]\ : STD_LOGIC;
  signal \counter_reg_n_0_[4]\ : STD_LOGIC;
  signal \counter_reg_n_0_[5]\ : STD_LOGIC;
  signal \counter_reg_n_0_[6]\ : STD_LOGIC;
  signal \counter_reg_n_0_[7]\ : STD_LOGIC;
  signal \counter_reg_n_0_[8]\ : STD_LOGIC;
  signal \counter_reg_n_0_[9]\ : STD_LOGIC;
  signal p_1_in : STD_LOGIC;
  signal p_2_in : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of B_S2_INST_0 : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of B_S3_INST_0 : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[0]_i_2__0\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[1]_i_2__0\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[2]_i_2__0\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[3]_i_2__0\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[3]_i_3__0\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[5]_i_2__0\ : label is "soft_lutpair10";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[0]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[1]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[2]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[3]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[4]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[5]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute SOFT_HLUTNM of \counter[3]_i_2__0\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \counter[4]_i_2__0\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \counter[5]_i_2__0\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \counter[6]_i_2__0\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \counter[8]_i_2__0\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \counter[9]_i_3__0\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \counter[9]_i_6__0\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \counter[9]_i_7__0\ : label is "soft_lutpair13";
begin
  Q(2 downto 0) <= \^q\(2 downto 0);
B_S2_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(2),
      I1 => p_1_in,
      I2 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      O => B_S2
    );
B_S3_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(1),
      I1 => p_1_in,
      I2 => p_2_in,
      O => B_S3
    );
\FSM_onehot_phase_state[0]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFD8D8D8"
    )
        port map (
      I0 => \FSM_onehot_phase_state[0]_i_2__0_n_0\,
      I1 => \^q\(2),
      I2 => \FSM_onehot_phase_state[3]_i_3__0_n_0\,
      I3 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I4 => \FSM_onehot_phase_state[5]_i_2__0_n_0\,
      O => \FSM_onehot_phase_state[0]_i_1__0_n_0\
    );
\FSM_onehot_phase_state[0]_i_2__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => enable,
      O => \FSM_onehot_phase_state[0]_i_2__0_n_0\
    );
\FSM_onehot_phase_state[1]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFD8D8D8"
    )
        port map (
      I0 => \FSM_onehot_phase_state[1]_i_2__0_n_0\,
      I1 => \^q\(1),
      I2 => \FSM_onehot_phase_state[3]_i_3__0_n_0\,
      I3 => p_2_in,
      I4 => \FSM_onehot_phase_state[5]_i_2__0_n_0\,
      O => \FSM_onehot_phase_state[1]_i_1__0_n_0\
    );
\FSM_onehot_phase_state[1]_i_2__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => enable,
      O => \FSM_onehot_phase_state[1]_i_2__0_n_0\
    );
\FSM_onehot_phase_state[2]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"44F4F44444444444"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2__0_n_0\,
      I1 => \FSM_onehot_phase_state[2]_i_2__0_n_0\,
      I2 => \FSM_onehot_phase_state[3]_i_3__0_n_0\,
      I3 => switching_signals(1),
      I4 => switching_signals(0),
      I5 => enable,
      O => \FSM_onehot_phase_state[2]_i_1__0_n_0\
    );
\FSM_onehot_phase_state[2]_i_2__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F7E00000"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => p_2_in,
      I3 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I4 => enable,
      O => \FSM_onehot_phase_state[2]_i_2__0_n_0\
    );
\FSM_onehot_phase_state[3]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFFF00004440"
    )
        port map (
      I0 => \FSM_onehot_phase_state[3]_i_2__0_n_0\,
      I1 => \counter_reg_n_0_[0]\,
      I2 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I3 => p_2_in,
      I4 => enable,
      I5 => \FSM_onehot_phase_state[3]_i_3__0_n_0\,
      O => \FSM_onehot_phase_state[3]_i_1__0_n_0\
    );
\FSM_onehot_phase_state[3]_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[8]\,
      I1 => \counter[7]_i_2__0_n_0\,
      I2 => \counter_reg_n_0_[7]\,
      I3 => \counter_reg_n_0_[9]\,
      O => \FSM_onehot_phase_state[3]_i_2__0_n_0\
    );
\FSM_onehot_phase_state[3]_i_3__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF0001"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(0),
      O => \FSM_onehot_phase_state[3]_i_3__0_n_0\
    );
\FSM_onehot_phase_state[4]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000F000000040000"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2__0_n_0\,
      I1 => p_2_in,
      I2 => switching_signals(1),
      I3 => switching_signals(0),
      I4 => enable,
      I5 => \^q\(1),
      O => \FSM_onehot_phase_state[4]_i_1__0_n_0\
    );
\FSM_onehot_phase_state[5]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F000000040000000"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2__0_n_0\,
      I1 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I2 => switching_signals(1),
      I3 => switching_signals(0),
      I4 => enable,
      I5 => \^q\(2),
      O => \FSM_onehot_phase_state[5]_i_1__0_n_0\
    );
\FSM_onehot_phase_state[5]_i_2__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEFFFF"
    )
        port map (
      I0 => \counter_reg_n_0_[9]\,
      I1 => \counter_reg_n_0_[7]\,
      I2 => \counter[7]_i_2__0_n_0\,
      I3 => \counter_reg_n_0_[8]\,
      I4 => \counter_reg_n_0_[0]\,
      O => \FSM_onehot_phase_state[5]_i_2__0_n_0\
    );
\FSM_onehot_phase_state_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[0]_i_1__0_n_0\,
      Q => \FSM_onehot_phase_state_reg_n_0_[0]\,
      R => '0'
    );
\FSM_onehot_phase_state_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[1]_i_1__0_n_0\,
      Q => p_2_in,
      R => '0'
    );
\FSM_onehot_phase_state_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[2]_i_1__0_n_0\,
      Q => p_1_in,
      R => '0'
    );
\FSM_onehot_phase_state_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[3]_i_1__0_n_0\,
      Q => \^q\(0),
      R => '0'
    );
\FSM_onehot_phase_state_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[4]_i_1__0_n_0\,
      Q => \^q\(1),
      R => '0'
    );
\FSM_onehot_phase_state_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[5]_i_1__0_n_0\,
      Q => \^q\(2),
      R => '0'
    );
\counter[0]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAA8FFFFAAAAAAAA"
    )
        port map (
      I0 => deadtime(0),
      I1 => \^q\(0),
      I2 => \^q\(2),
      I3 => \^q\(1),
      I4 => \counter_reg_n_0_[0]\,
      I5 => \counter[9]_i_4__0_n_0\,
      O => \counter[0]_i_1__0_n_0\
    );
\counter[1]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F8F8F8888F8F8F88"
    )
        port map (
      I0 => \counter[9]_i_6__0_n_0\,
      I1 => deadtime(1),
      I2 => \counter_reg_n_0_[1]\,
      I3 => p_2_in,
      I4 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I5 => \counter_reg_n_0_[0]\,
      O => \counter[1]_i_1__0_n_0\
    );
\counter[2]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF888888F8888F88"
    )
        port map (
      I0 => \counter[9]_i_6__0_n_0\,
      I1 => deadtime(2),
      I2 => \counter_reg_n_0_[0]\,
      I3 => \counter[9]_i_4__0_n_0\,
      I4 => \counter_reg_n_0_[2]\,
      I5 => \counter_reg_n_0_[1]\,
      O => \counter[2]_i_1__0_n_0\
    );
\counter[3]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF88888888F8888"
    )
        port map (
      I0 => \counter[9]_i_6__0_n_0\,
      I1 => deadtime(3),
      I2 => \counter_reg_n_0_[0]\,
      I3 => \counter[3]_i_2__0_n_0\,
      I4 => \counter[9]_i_4__0_n_0\,
      I5 => \counter_reg_n_0_[3]\,
      O => \counter[3]_i_1__0_n_0\
    );
\counter[3]_i_2__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \counter_reg_n_0_[1]\,
      I1 => \counter_reg_n_0_[2]\,
      O => \counter[3]_i_2__0_n_0\
    );
\counter[4]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF88888888F8888"
    )
        port map (
      I0 => \counter[9]_i_6__0_n_0\,
      I1 => deadtime(4),
      I2 => \counter_reg_n_0_[0]\,
      I3 => \counter[4]_i_2__0_n_0\,
      I4 => \counter[9]_i_4__0_n_0\,
      I5 => \counter_reg_n_0_[4]\,
      O => \counter[4]_i_1__0_n_0\
    );
\counter[4]_i_2__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \counter_reg_n_0_[2]\,
      I1 => \counter_reg_n_0_[1]\,
      I2 => \counter_reg_n_0_[3]\,
      O => \counter[4]_i_2__0_n_0\
    );
\counter[5]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__0_n_0\,
      I2 => \counter_reg_n_0_[5]\,
      I3 => deadtime(5),
      I4 => \counter[9]_i_6__0_n_0\,
      I5 => \counter[5]_i_2__0_n_0\,
      O => \counter[5]_i_1__0_n_0\
    );
\counter[5]_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[3]\,
      I1 => \counter_reg_n_0_[1]\,
      I2 => \counter_reg_n_0_[2]\,
      I3 => \counter_reg_n_0_[4]\,
      O => \counter[5]_i_2__0_n_0\
    );
\counter[6]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__0_n_0\,
      I2 => \counter_reg_n_0_[6]\,
      I3 => deadtime(6),
      I4 => \counter[9]_i_6__0_n_0\,
      I5 => \counter[6]_i_2__0_n_0\,
      O => \counter[6]_i_1__0_n_0\
    );
\counter[6]_i_2__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[4]\,
      I1 => \counter_reg_n_0_[2]\,
      I2 => \counter_reg_n_0_[1]\,
      I3 => \counter_reg_n_0_[3]\,
      I4 => \counter_reg_n_0_[5]\,
      O => \counter[6]_i_2__0_n_0\
    );
\counter[7]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__0_n_0\,
      I2 => \counter_reg_n_0_[7]\,
      I3 => deadtime(7),
      I4 => \counter[9]_i_6__0_n_0\,
      I5 => \counter[7]_i_2__0_n_0\,
      O => \counter[7]_i_1__0_n_0\
    );
\counter[7]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[5]\,
      I1 => \counter_reg_n_0_[3]\,
      I2 => \counter_reg_n_0_[1]\,
      I3 => \counter_reg_n_0_[2]\,
      I4 => \counter_reg_n_0_[4]\,
      I5 => \counter_reg_n_0_[6]\,
      O => \counter[7]_i_2__0_n_0\
    );
\counter[8]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__0_n_0\,
      I2 => \counter_reg_n_0_[8]\,
      I3 => deadtime(8),
      I4 => \counter[9]_i_6__0_n_0\,
      I5 => \counter[8]_i_2__0_n_0\,
      O => \counter[8]_i_1__0_n_0\
    );
\counter[8]_i_2__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \counter[7]_i_2__0_n_0\,
      I1 => \counter_reg_n_0_[7]\,
      O => \counter[8]_i_2__0_n_0\
    );
\counter[9]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFF808"
    )
        port map (
      I0 => \^q\(0),
      I1 => enable,
      I2 => \counter[9]_i_3__0_n_0\,
      I3 => \^q\(1),
      I4 => \counter[9]_i_4__0_n_0\,
      I5 => \counter[9]_i_5__0_n_0\,
      O => counter
    );
\counter[9]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__0_n_0\,
      I2 => \counter_reg_n_0_[9]\,
      I3 => deadtime(9),
      I4 => \counter[9]_i_6__0_n_0\,
      I5 => \counter[9]_i_7__0_n_0\,
      O => \counter[9]_i_2__0_n_0\
    );
\counter[9]_i_3__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => switching_signals(0),
      I1 => switching_signals(1),
      O => \counter[9]_i_3__0_n_0\
    );
\counter[9]_i_4__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      O => \counter[9]_i_4__0_n_0\
    );
\counter[9]_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EAFF6AFFEBAA6BAA"
    )
        port map (
      I0 => \^q\(2),
      I1 => switching_signals(1),
      I2 => switching_signals(0),
      I3 => enable,
      I4 => \^q\(0),
      I5 => \^q\(1),
      O => \counter[9]_i_5__0_n_0\
    );
\counter[9]_i_6__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFF1"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      I2 => \^q\(0),
      I3 => \^q\(2),
      I4 => \^q\(1),
      O => \counter[9]_i_6__0_n_0\
    );
\counter[9]_i_7__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \counter_reg_n_0_[7]\,
      I1 => \counter[7]_i_2__0_n_0\,
      I2 => \counter_reg_n_0_[8]\,
      O => \counter[9]_i_7__0_n_0\
    );
\counter_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[0]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[0]\,
      R => '0'
    );
\counter_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[1]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[1]\,
      R => '0'
    );
\counter_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[2]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[2]\,
      R => '0'
    );
\counter_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[3]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[3]\,
      R => '0'
    );
\counter_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[4]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[4]\,
      R => '0'
    );
\counter_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[5]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[5]\,
      R => '0'
    );
\counter_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[6]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[6]\,
      R => '0'
    );
\counter_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[7]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[7]\,
      R => '0'
    );
\counter_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[8]_i_1__0_n_0\,
      Q => \counter_reg_n_0_[8]\,
      R => '0'
    );
\counter_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[9]_i_2__0_n_0\,
      Q => \counter_reg_n_0_[9]\,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1 is
  port (
    Q : out STD_LOGIC_VECTOR ( 2 downto 0 );
    C_S2 : out STD_LOGIC;
    C_S3 : out STD_LOGIC;
    switching_signals : in STD_LOGIC_VECTOR ( 1 downto 0 );
    enable : in STD_LOGIC;
    deadtime : in STD_LOGIC_VECTOR ( 9 downto 0 );
    clock : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1 : entity is "npc_phase_state_machine";
end zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1;

architecture STRUCTURE of zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1 is
  signal \FSM_onehot_phase_state[0]_i_1__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[0]_i_2__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[1]_i_1__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[1]_i_2__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[2]_i_1__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[2]_i_2__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_1__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_2__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[3]_i_3__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[4]_i_1__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[5]_i_1__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state[5]_i_2__1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_phase_state_reg_n_0_[0]\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal counter : STD_LOGIC;
  signal \counter[0]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[1]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[2]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[3]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[3]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[4]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[4]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[5]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[5]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[6]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[6]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[7]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[7]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[8]_i_1__1_n_0\ : STD_LOGIC;
  signal \counter[8]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[9]_i_2__1_n_0\ : STD_LOGIC;
  signal \counter[9]_i_3__1_n_0\ : STD_LOGIC;
  signal \counter[9]_i_4__1_n_0\ : STD_LOGIC;
  signal \counter[9]_i_5__1_n_0\ : STD_LOGIC;
  signal \counter[9]_i_6__1_n_0\ : STD_LOGIC;
  signal \counter[9]_i_7__1_n_0\ : STD_LOGIC;
  signal \counter_reg_n_0_[0]\ : STD_LOGIC;
  signal \counter_reg_n_0_[1]\ : STD_LOGIC;
  signal \counter_reg_n_0_[2]\ : STD_LOGIC;
  signal \counter_reg_n_0_[3]\ : STD_LOGIC;
  signal \counter_reg_n_0_[4]\ : STD_LOGIC;
  signal \counter_reg_n_0_[5]\ : STD_LOGIC;
  signal \counter_reg_n_0_[6]\ : STD_LOGIC;
  signal \counter_reg_n_0_[7]\ : STD_LOGIC;
  signal \counter_reg_n_0_[8]\ : STD_LOGIC;
  signal \counter_reg_n_0_[9]\ : STD_LOGIC;
  signal p_1_in : STD_LOGIC;
  signal p_2_in : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of C_S2_INST_0 : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of C_S3_INST_0 : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[0]_i_2__1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[1]_i_2__1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[2]_i_2__1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[3]_i_2__1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[3]_i_3__1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \FSM_onehot_phase_state[5]_i_2__1\ : label is "soft_lutpair18";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[0]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[1]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[2]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[3]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[4]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute FSM_ENCODED_STATES of \FSM_onehot_phase_state_reg[5]\ : label is "pos_state:100000,neg_state:010000,int_low:000010,int_high:000001,off_state:001000,iSTATE:000100";
  attribute SOFT_HLUTNM of \counter[3]_i_2__1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \counter[4]_i_2__1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \counter[5]_i_2__1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \counter[6]_i_2__1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \counter[8]_i_2__1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \counter[9]_i_3__1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \counter[9]_i_6__1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \counter[9]_i_7__1\ : label is "soft_lutpair21";
begin
  Q(2 downto 0) <= \^q\(2 downto 0);
C_S2_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(2),
      I1 => p_1_in,
      I2 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      O => C_S2
    );
C_S3_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(1),
      I1 => p_1_in,
      I2 => p_2_in,
      O => C_S3
    );
\FSM_onehot_phase_state[0]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFD8D8D8"
    )
        port map (
      I0 => \FSM_onehot_phase_state[0]_i_2__1_n_0\,
      I1 => \^q\(2),
      I2 => \FSM_onehot_phase_state[3]_i_3__1_n_0\,
      I3 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I4 => \FSM_onehot_phase_state[5]_i_2__1_n_0\,
      O => \FSM_onehot_phase_state[0]_i_1__1_n_0\
    );
\FSM_onehot_phase_state[0]_i_2__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => enable,
      O => \FSM_onehot_phase_state[0]_i_2__1_n_0\
    );
\FSM_onehot_phase_state[1]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFD8D8D8"
    )
        port map (
      I0 => \FSM_onehot_phase_state[1]_i_2__1_n_0\,
      I1 => \^q\(1),
      I2 => \FSM_onehot_phase_state[3]_i_3__1_n_0\,
      I3 => p_2_in,
      I4 => \FSM_onehot_phase_state[5]_i_2__1_n_0\,
      O => \FSM_onehot_phase_state[1]_i_1__1_n_0\
    );
\FSM_onehot_phase_state[1]_i_2__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EF"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => enable,
      O => \FSM_onehot_phase_state[1]_i_2__1_n_0\
    );
\FSM_onehot_phase_state[2]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"44F4F44444444444"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2__1_n_0\,
      I1 => \FSM_onehot_phase_state[2]_i_2__1_n_0\,
      I2 => \FSM_onehot_phase_state[3]_i_3__1_n_0\,
      I3 => switching_signals(1),
      I4 => switching_signals(0),
      I5 => enable,
      O => \FSM_onehot_phase_state[2]_i_1__1_n_0\
    );
\FSM_onehot_phase_state[2]_i_2__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F7E00000"
    )
        port map (
      I0 => switching_signals(1),
      I1 => switching_signals(0),
      I2 => p_2_in,
      I3 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I4 => enable,
      O => \FSM_onehot_phase_state[2]_i_2__1_n_0\
    );
\FSM_onehot_phase_state[3]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFFF00004440"
    )
        port map (
      I0 => \FSM_onehot_phase_state[3]_i_2__1_n_0\,
      I1 => \counter_reg_n_0_[0]\,
      I2 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I3 => p_2_in,
      I4 => enable,
      I5 => \FSM_onehot_phase_state[3]_i_3__1_n_0\,
      O => \FSM_onehot_phase_state[3]_i_1__1_n_0\
    );
\FSM_onehot_phase_state[3]_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[8]\,
      I1 => \counter[7]_i_2__1_n_0\,
      I2 => \counter_reg_n_0_[7]\,
      I3 => \counter_reg_n_0_[9]\,
      O => \FSM_onehot_phase_state[3]_i_2__1_n_0\
    );
\FSM_onehot_phase_state[3]_i_3__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF0001"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(0),
      O => \FSM_onehot_phase_state[3]_i_3__1_n_0\
    );
\FSM_onehot_phase_state[4]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000F000000040000"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2__1_n_0\,
      I1 => p_2_in,
      I2 => switching_signals(1),
      I3 => switching_signals(0),
      I4 => enable,
      I5 => \^q\(1),
      O => \FSM_onehot_phase_state[4]_i_1__1_n_0\
    );
\FSM_onehot_phase_state[5]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F000000040000000"
    )
        port map (
      I0 => \FSM_onehot_phase_state[5]_i_2__1_n_0\,
      I1 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I2 => switching_signals(1),
      I3 => switching_signals(0),
      I4 => enable,
      I5 => \^q\(2),
      O => \FSM_onehot_phase_state[5]_i_1__1_n_0\
    );
\FSM_onehot_phase_state[5]_i_2__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEFFFF"
    )
        port map (
      I0 => \counter_reg_n_0_[9]\,
      I1 => \counter_reg_n_0_[7]\,
      I2 => \counter[7]_i_2__1_n_0\,
      I3 => \counter_reg_n_0_[8]\,
      I4 => \counter_reg_n_0_[0]\,
      O => \FSM_onehot_phase_state[5]_i_2__1_n_0\
    );
\FSM_onehot_phase_state_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[0]_i_1__1_n_0\,
      Q => \FSM_onehot_phase_state_reg_n_0_[0]\,
      R => '0'
    );
\FSM_onehot_phase_state_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[1]_i_1__1_n_0\,
      Q => p_2_in,
      R => '0'
    );
\FSM_onehot_phase_state_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[2]_i_1__1_n_0\,
      Q => p_1_in,
      R => '0'
    );
\FSM_onehot_phase_state_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[3]_i_1__1_n_0\,
      Q => \^q\(0),
      R => '0'
    );
\FSM_onehot_phase_state_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[4]_i_1__1_n_0\,
      Q => \^q\(1),
      R => '0'
    );
\FSM_onehot_phase_state_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => '1',
      D => \FSM_onehot_phase_state[5]_i_1__1_n_0\,
      Q => \^q\(2),
      R => '0'
    );
\counter[0]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAA8FFFFAAAAAAAA"
    )
        port map (
      I0 => deadtime(0),
      I1 => \^q\(0),
      I2 => \^q\(2),
      I3 => \^q\(1),
      I4 => \counter_reg_n_0_[0]\,
      I5 => \counter[9]_i_4__1_n_0\,
      O => \counter[0]_i_1__1_n_0\
    );
\counter[1]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F8F8F8888F8F8F88"
    )
        port map (
      I0 => \counter[9]_i_6__1_n_0\,
      I1 => deadtime(1),
      I2 => \counter_reg_n_0_[1]\,
      I3 => p_2_in,
      I4 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I5 => \counter_reg_n_0_[0]\,
      O => \counter[1]_i_1__1_n_0\
    );
\counter[2]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF888888F8888F88"
    )
        port map (
      I0 => \counter[9]_i_6__1_n_0\,
      I1 => deadtime(2),
      I2 => \counter_reg_n_0_[0]\,
      I3 => \counter[9]_i_4__1_n_0\,
      I4 => \counter_reg_n_0_[2]\,
      I5 => \counter_reg_n_0_[1]\,
      O => \counter[2]_i_1__1_n_0\
    );
\counter[3]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF88888888F8888"
    )
        port map (
      I0 => \counter[9]_i_6__1_n_0\,
      I1 => deadtime(3),
      I2 => \counter_reg_n_0_[0]\,
      I3 => \counter[3]_i_2__1_n_0\,
      I4 => \counter[9]_i_4__1_n_0\,
      I5 => \counter_reg_n_0_[3]\,
      O => \counter[3]_i_1__1_n_0\
    );
\counter[3]_i_2__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \counter_reg_n_0_[1]\,
      I1 => \counter_reg_n_0_[2]\,
      O => \counter[3]_i_2__1_n_0\
    );
\counter[4]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF88888888F8888"
    )
        port map (
      I0 => \counter[9]_i_6__1_n_0\,
      I1 => deadtime(4),
      I2 => \counter_reg_n_0_[0]\,
      I3 => \counter[4]_i_2__1_n_0\,
      I4 => \counter[9]_i_4__1_n_0\,
      I5 => \counter_reg_n_0_[4]\,
      O => \counter[4]_i_1__1_n_0\
    );
\counter[4]_i_2__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \counter_reg_n_0_[2]\,
      I1 => \counter_reg_n_0_[1]\,
      I2 => \counter_reg_n_0_[3]\,
      O => \counter[4]_i_2__1_n_0\
    );
\counter[5]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__1_n_0\,
      I2 => \counter_reg_n_0_[5]\,
      I3 => deadtime(5),
      I4 => \counter[9]_i_6__1_n_0\,
      I5 => \counter[5]_i_2__1_n_0\,
      O => \counter[5]_i_1__1_n_0\
    );
\counter[5]_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[3]\,
      I1 => \counter_reg_n_0_[1]\,
      I2 => \counter_reg_n_0_[2]\,
      I3 => \counter_reg_n_0_[4]\,
      O => \counter[5]_i_2__1_n_0\
    );
\counter[6]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__1_n_0\,
      I2 => \counter_reg_n_0_[6]\,
      I3 => deadtime(6),
      I4 => \counter[9]_i_6__1_n_0\,
      I5 => \counter[6]_i_2__1_n_0\,
      O => \counter[6]_i_1__1_n_0\
    );
\counter[6]_i_2__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[4]\,
      I1 => \counter_reg_n_0_[2]\,
      I2 => \counter_reg_n_0_[1]\,
      I3 => \counter_reg_n_0_[3]\,
      I4 => \counter_reg_n_0_[5]\,
      O => \counter[6]_i_2__1_n_0\
    );
\counter[7]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__1_n_0\,
      I2 => \counter_reg_n_0_[7]\,
      I3 => deadtime(7),
      I4 => \counter[9]_i_6__1_n_0\,
      I5 => \counter[7]_i_2__1_n_0\,
      O => \counter[7]_i_1__1_n_0\
    );
\counter[7]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \counter_reg_n_0_[5]\,
      I1 => \counter_reg_n_0_[3]\,
      I2 => \counter_reg_n_0_[1]\,
      I3 => \counter_reg_n_0_[2]\,
      I4 => \counter_reg_n_0_[4]\,
      I5 => \counter_reg_n_0_[6]\,
      O => \counter[7]_i_2__1_n_0\
    );
\counter[8]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__1_n_0\,
      I2 => \counter_reg_n_0_[8]\,
      I3 => deadtime(8),
      I4 => \counter[9]_i_6__1_n_0\,
      I5 => \counter[8]_i_2__1_n_0\,
      O => \counter[8]_i_1__1_n_0\
    );
\counter[8]_i_2__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \counter[7]_i_2__1_n_0\,
      I1 => \counter_reg_n_0_[7]\,
      O => \counter[8]_i_2__1_n_0\
    );
\counter[9]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFF808"
    )
        port map (
      I0 => \^q\(0),
      I1 => enable,
      I2 => \counter[9]_i_3__1_n_0\,
      I3 => \^q\(1),
      I4 => \counter[9]_i_4__1_n_0\,
      I5 => \counter[9]_i_5__1_n_0\,
      O => counter
    );
\counter[9]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFC0C0C0FF848484"
    )
        port map (
      I0 => \counter_reg_n_0_[0]\,
      I1 => \counter[9]_i_4__1_n_0\,
      I2 => \counter_reg_n_0_[9]\,
      I3 => deadtime(9),
      I4 => \counter[9]_i_6__1_n_0\,
      I5 => \counter[9]_i_7__1_n_0\,
      O => \counter[9]_i_2__1_n_0\
    );
\counter[9]_i_3__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => switching_signals(0),
      I1 => switching_signals(1),
      O => \counter[9]_i_3__1_n_0\
    );
\counter[9]_i_4__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      O => \counter[9]_i_4__1_n_0\
    );
\counter[9]_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EAFF6AFFEBAA6BAA"
    )
        port map (
      I0 => \^q\(2),
      I1 => switching_signals(1),
      I2 => switching_signals(0),
      I3 => enable,
      I4 => \^q\(0),
      I5 => \^q\(1),
      O => \counter[9]_i_5__1_n_0\
    );
\counter[9]_i_6__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFF1"
    )
        port map (
      I0 => \FSM_onehot_phase_state_reg_n_0_[0]\,
      I1 => p_2_in,
      I2 => \^q\(0),
      I3 => \^q\(2),
      I4 => \^q\(1),
      O => \counter[9]_i_6__1_n_0\
    );
\counter[9]_i_7__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \counter_reg_n_0_[7]\,
      I1 => \counter[7]_i_2__1_n_0\,
      I2 => \counter_reg_n_0_[8]\,
      O => \counter[9]_i_7__1_n_0\
    );
\counter_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[0]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[0]\,
      R => '0'
    );
\counter_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[1]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[1]\,
      R => '0'
    );
\counter_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[2]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[2]\,
      R => '0'
    );
\counter_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[3]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[3]\,
      R => '0'
    );
\counter_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[4]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[4]\,
      R => '0'
    );
\counter_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[5]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[5]\,
      R => '0'
    );
\counter_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[6]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[6]\,
      R => '0'
    );
\counter_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[7]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[7]\,
      R => '0'
    );
\counter_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[8]_i_1__1_n_0\,
      Q => \counter_reg_n_0_[8]\,
      R => '0'
    );
\counter_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clock,
      CE => counter,
      D => \counter[9]_i_2__1_n_0\,
      Q => \counter_reg_n_0_[9]\,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_top_npc_state_machine_0_0_top_npc_state_machine is
  port (
    A_S1 : out STD_LOGIC;
    A_S4 : out STD_LOGIC;
    A_phase_off : out STD_LOGIC;
    B_S1 : out STD_LOGIC;
    B_S4 : out STD_LOGIC;
    B_phase_off : out STD_LOGIC;
    C_S1 : out STD_LOGIC;
    C_S4 : out STD_LOGIC;
    C_phase_off : out STD_LOGIC;
    A_S2 : out STD_LOGIC;
    A_S3 : out STD_LOGIC;
    B_S2 : out STD_LOGIC;
    B_S3 : out STD_LOGIC;
    C_S2 : out STD_LOGIC;
    C_S3 : out STD_LOGIC;
    clock : in STD_LOGIC;
    switching_signals : in STD_LOGIC_VECTOR ( 5 downto 0 );
    enable : in STD_LOGIC;
    deadtime : in STD_LOGIC_VECTOR ( 9 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_top_npc_state_machine_0_0_top_npc_state_machine : entity is "top_npc_state_machine";
end zusys_top_npc_state_machine_0_0_top_npc_state_machine;

architecture STRUCTURE of zusys_top_npc_state_machine_0_0_top_npc_state_machine is
begin
npc_FCM_phase_A: entity work.zusys_top_npc_state_machine_0_0_npc_phase_state_machine
     port map (
      A_S2 => A_S2,
      A_S3 => A_S3,
      Q(2) => A_S1,
      Q(1) => A_S4,
      Q(0) => A_phase_off,
      clock => clock,
      deadtime(9 downto 0) => deadtime(9 downto 0),
      enable => enable,
      switching_signals(1 downto 0) => switching_signals(1 downto 0)
    );
npc_FCM_phase_B: entity work.zusys_top_npc_state_machine_0_0_npc_phase_state_machine_0
     port map (
      B_S2 => B_S2,
      B_S3 => B_S3,
      Q(2) => B_S1,
      Q(1) => B_S4,
      Q(0) => B_phase_off,
      clock => clock,
      deadtime(9 downto 0) => deadtime(9 downto 0),
      enable => enable,
      switching_signals(1 downto 0) => switching_signals(3 downto 2)
    );
npc_FCM_phase_C: entity work.zusys_top_npc_state_machine_0_0_npc_phase_state_machine_1
     port map (
      C_S2 => C_S2,
      C_S3 => C_S3,
      Q(2) => C_S1,
      Q(1) => C_S4,
      Q(0) => C_phase_off,
      clock => clock,
      deadtime(9 downto 0) => deadtime(9 downto 0),
      enable => enable,
      switching_signals(1 downto 0) => switching_signals(5 downto 4)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_top_npc_state_machine_0_0 is
  port (
    clock : in STD_LOGIC;
    enable : in STD_LOGIC;
    switching_signals : in STD_LOGIC_VECTOR ( 5 downto 0 );
    deadtime : in STD_LOGIC_VECTOR ( 9 downto 0 );
    A_S1 : out STD_LOGIC;
    A_S2 : out STD_LOGIC;
    A_S3 : out STD_LOGIC;
    A_S4 : out STD_LOGIC;
    B_S1 : out STD_LOGIC;
    B_S2 : out STD_LOGIC;
    B_S3 : out STD_LOGIC;
    B_S4 : out STD_LOGIC;
    C_S1 : out STD_LOGIC;
    C_S2 : out STD_LOGIC;
    C_S3 : out STD_LOGIC;
    C_S4 : out STD_LOGIC;
    A_phase_off : out STD_LOGIC;
    B_phase_off : out STD_LOGIC;
    C_phase_off : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_top_npc_state_machine_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_top_npc_state_machine_0_0 : entity is "zusys_top_npc_state_machine_0_0,top_npc_state_machine,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_top_npc_state_machine_0_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_top_npc_state_machine_0_0 : entity is "module_ref";
  attribute x_core_info : string;
  attribute x_core_info of zusys_top_npc_state_machine_0_0 : entity is "top_npc_state_machine,Vivado 2020.1.1";
end zusys_top_npc_state_machine_0_0;

architecture STRUCTURE of zusys_top_npc_state_machine_0_0 is
  attribute x_interface_info : string;
  attribute x_interface_info of clock : signal is "xilinx.com:signal:clock:1.0 clock CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of clock : signal is "XIL_INTERFACENAME clock, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
begin
U0: entity work.zusys_top_npc_state_machine_0_0_top_npc_state_machine
     port map (
      A_S1 => A_S1,
      A_S2 => A_S2,
      A_S3 => A_S3,
      A_S4 => A_S4,
      A_phase_off => A_phase_off,
      B_S1 => B_S1,
      B_S2 => B_S2,
      B_S3 => B_S3,
      B_S4 => B_S4,
      B_phase_off => B_phase_off,
      C_S1 => C_S1,
      C_S2 => C_S2,
      C_S3 => C_S3,
      C_S4 => C_S4,
      C_phase_off => C_phase_off,
      clock => clock,
      deadtime(9 downto 0) => deadtime(9 downto 0),
      enable => enable,
      switching_signals(5 downto 0) => switching_signals(5 downto 0)
    );
end STRUCTURE;
