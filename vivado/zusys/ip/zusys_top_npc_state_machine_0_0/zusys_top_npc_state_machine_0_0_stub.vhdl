-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:48:00 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_top_npc_state_machine_0_0/zusys_top_npc_state_machine_0_0_stub.vhdl
-- Design      : zusys_top_npc_state_machine_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity zusys_top_npc_state_machine_0_0 is
  Port ( 
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

end zusys_top_npc_state_machine_0_0;

architecture stub of zusys_top_npc_state_machine_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clock,enable,switching_signals[5:0],deadtime[9:0],A_S1,A_S2,A_S3,A_S4,B_S1,B_S2,B_S3,B_S4,C_S1,C_S2,C_S3,C_S4,A_phase_off,B_phase_off,C_phase_off";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "top_npc_state_machine,Vivado 2020.1.1";
begin
end;
