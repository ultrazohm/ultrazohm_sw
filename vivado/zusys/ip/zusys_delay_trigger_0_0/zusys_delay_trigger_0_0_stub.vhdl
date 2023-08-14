-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:49:00 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_delay_trigger_0_0/zusys_delay_trigger_0_0_stub.vhdl
-- Design      : zusys_delay_trigger_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity zusys_delay_trigger_0_0 is
  Port ( 
    clk : in STD_LOGIC;
    delay_cycles : in STD_LOGIC_VECTOR ( 10 downto 0 );
    a_in : in STD_LOGIC;
    a_out : out STD_LOGIC
  );

end zusys_delay_trigger_0_0;

architecture stub of zusys_delay_trigger_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk,delay_cycles[10:0],a_in,a_out";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "delay_trigger,Vivado 2020.1.1";
begin
end;
