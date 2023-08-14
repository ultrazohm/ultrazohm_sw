-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:49:00 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_delay_trigger_0_0/zusys_delay_trigger_0_0_sim_netlist.vhdl
-- Design      : zusys_delay_trigger_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_delay_trigger_0_0_delay_trigger is
  port (
    a_out : out STD_LOGIC;
    a_in : in STD_LOGIC;
    delay_cycles : in STD_LOGIC_VECTOR ( 10 downto 0 );
    clk : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_delay_trigger_0_0_delay_trigger : entity is "delay_trigger";
end zusys_delay_trigger_0_0_delay_trigger;

architecture STRUCTURE of zusys_delay_trigger_0_0_delay_trigger is
  signal a_out0 : STD_LOGIC;
  signal a_out_i_4_n_0 : STD_LOGIC;
  signal a_out_i_5_n_0 : STD_LOGIC;
  signal a_out_i_6_n_0 : STD_LOGIC;
  signal a_out_i_7_n_0 : STD_LOGIC;
  signal a_out_reg_i_2_n_0 : STD_LOGIC;
  signal a_out_reg_i_3_n_0 : STD_LOGIC;
  signal \a_store_reg[0]_mux__0_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__10_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__11_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__12_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__13_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__14_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__15_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__16_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__17_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__18_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__19_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__1_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__20_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__21_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__22_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__23_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__24_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__25_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__26_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__27_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__28_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__29_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__2_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__30_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__31_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__32_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__33_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__34_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__35_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__36_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__37_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__38_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__39_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__3_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__40_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__41_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__42_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__43_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__44_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__45_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__46_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__4_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__5_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__6_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__7_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__8_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux__9_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_mux_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__0_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__0_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__10_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__10_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__11_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__11_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__12_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__12_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__13_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__13_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__14_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__14_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__15_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__15_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__16_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__16_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__17_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__17_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__18_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__18_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__19_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__19_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__1_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__1_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__20_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__20_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__21_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__21_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__22_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__22_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__23_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__23_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__24_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__24_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__25_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__25_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__26_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__26_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__27_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__27_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__28_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__28_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__29_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__29_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__2_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__2_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__30_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__30_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__31_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__31_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__32_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__32_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__33_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__33_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__34_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__34_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__35_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__35_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__36_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__36_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__37_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__37_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__38_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__38_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__39_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__39_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__3_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__3_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__40_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__40_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__41_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__41_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__42_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__42_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__43_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__43_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__44_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__44_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__45_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__45_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__46_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__46_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__47_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__47_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__48_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__48_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__49_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__49_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__4_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__4_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__50_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__50_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__51_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__51_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__52_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__52_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__53_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__53_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__54_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__54_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__55_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__55_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__56_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__56_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__57_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__57_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__58_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__58_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__59_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__59_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__5_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__5_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__60_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__60_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__61_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__61_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__62_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__6_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__6_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__7_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__7_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__8_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__8_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__9_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32__9_n_1\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32_n_0\ : STD_LOGIC;
  signal \a_store_reg[0]_srl32_n_1\ : STD_LOGIC;
  signal \NLW_a_store_reg[0]_srl32__62_Q31_UNCONNECTED\ : STD_LOGIC;
  attribute srl_bus_name : string;
  attribute srl_bus_name of \a_store_reg[0]_srl32\ : label is "\U0/a_store_reg ";
  attribute srl_name : string;
  attribute srl_name of \a_store_reg[0]_srl32\ : label is "\U0/a_store_reg[0]_srl32 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__0\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__0\ : label is "\U0/a_store_reg[0]_srl32__0 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__1\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__1\ : label is "\U0/a_store_reg[0]_srl32__1 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__10\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__10\ : label is "\U0/a_store_reg[0]_srl32__10 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__11\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__11\ : label is "\U0/a_store_reg[0]_srl32__11 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__12\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__12\ : label is "\U0/a_store_reg[0]_srl32__12 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__13\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__13\ : label is "\U0/a_store_reg[0]_srl32__13 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__14\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__14\ : label is "\U0/a_store_reg[0]_srl32__14 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__15\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__15\ : label is "\U0/a_store_reg[0]_srl32__15 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__16\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__16\ : label is "\U0/a_store_reg[0]_srl32__16 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__17\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__17\ : label is "\U0/a_store_reg[0]_srl32__17 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__18\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__18\ : label is "\U0/a_store_reg[0]_srl32__18 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__19\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__19\ : label is "\U0/a_store_reg[0]_srl32__19 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__2\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__2\ : label is "\U0/a_store_reg[0]_srl32__2 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__20\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__20\ : label is "\U0/a_store_reg[0]_srl32__20 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__21\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__21\ : label is "\U0/a_store_reg[0]_srl32__21 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__22\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__22\ : label is "\U0/a_store_reg[0]_srl32__22 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__23\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__23\ : label is "\U0/a_store_reg[0]_srl32__23 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__24\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__24\ : label is "\U0/a_store_reg[0]_srl32__24 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__25\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__25\ : label is "\U0/a_store_reg[0]_srl32__25 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__26\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__26\ : label is "\U0/a_store_reg[0]_srl32__26 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__27\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__27\ : label is "\U0/a_store_reg[0]_srl32__27 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__28\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__28\ : label is "\U0/a_store_reg[0]_srl32__28 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__29\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__29\ : label is "\U0/a_store_reg[0]_srl32__29 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__3\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__3\ : label is "\U0/a_store_reg[0]_srl32__3 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__30\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__30\ : label is "\U0/a_store_reg[0]_srl32__30 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__31\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__31\ : label is "\U0/a_store_reg[0]_srl32__31 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__32\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__32\ : label is "\U0/a_store_reg[0]_srl32__32 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__33\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__33\ : label is "\U0/a_store_reg[0]_srl32__33 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__34\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__34\ : label is "\U0/a_store_reg[0]_srl32__34 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__35\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__35\ : label is "\U0/a_store_reg[0]_srl32__35 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__36\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__36\ : label is "\U0/a_store_reg[0]_srl32__36 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__37\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__37\ : label is "\U0/a_store_reg[0]_srl32__37 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__38\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__38\ : label is "\U0/a_store_reg[0]_srl32__38 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__39\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__39\ : label is "\U0/a_store_reg[0]_srl32__39 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__4\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__4\ : label is "\U0/a_store_reg[0]_srl32__4 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__40\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__40\ : label is "\U0/a_store_reg[0]_srl32__40 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__41\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__41\ : label is "\U0/a_store_reg[0]_srl32__41 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__42\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__42\ : label is "\U0/a_store_reg[0]_srl32__42 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__43\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__43\ : label is "\U0/a_store_reg[0]_srl32__43 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__44\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__44\ : label is "\U0/a_store_reg[0]_srl32__44 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__45\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__45\ : label is "\U0/a_store_reg[0]_srl32__45 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__46\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__46\ : label is "\U0/a_store_reg[0]_srl32__46 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__47\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__47\ : label is "\U0/a_store_reg[0]_srl32__47 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__48\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__48\ : label is "\U0/a_store_reg[0]_srl32__48 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__49\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__49\ : label is "\U0/a_store_reg[0]_srl32__49 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__5\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__5\ : label is "\U0/a_store_reg[0]_srl32__5 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__50\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__50\ : label is "\U0/a_store_reg[0]_srl32__50 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__51\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__51\ : label is "\U0/a_store_reg[0]_srl32__51 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__52\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__52\ : label is "\U0/a_store_reg[0]_srl32__52 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__53\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__53\ : label is "\U0/a_store_reg[0]_srl32__53 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__54\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__54\ : label is "\U0/a_store_reg[0]_srl32__54 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__55\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__55\ : label is "\U0/a_store_reg[0]_srl32__55 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__56\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__56\ : label is "\U0/a_store_reg[0]_srl32__56 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__57\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__57\ : label is "\U0/a_store_reg[0]_srl32__57 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__58\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__58\ : label is "\U0/a_store_reg[0]_srl32__58 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__59\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__59\ : label is "\U0/a_store_reg[0]_srl32__59 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__6\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__6\ : label is "\U0/a_store_reg[0]_srl32__6 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__60\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__60\ : label is "\U0/a_store_reg[0]_srl32__60 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__61\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__61\ : label is "\U0/a_store_reg[0]_srl32__61 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__62\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__62\ : label is "\U0/a_store_reg[0]_srl32__62 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__7\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__7\ : label is "\U0/a_store_reg[0]_srl32__7 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__8\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__8\ : label is "\U0/a_store_reg[0]_srl32__8 ";
  attribute srl_bus_name of \a_store_reg[0]_srl32__9\ : label is "\U0/a_store_reg ";
  attribute srl_name of \a_store_reg[0]_srl32__9\ : label is "\U0/a_store_reg[0]_srl32__9 ";
begin
a_out_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \a_store_reg[0]_mux__34_n_0\,
      I1 => \a_store_reg[0]_mux__33_n_0\,
      I2 => delay_cycles(8),
      I3 => \a_store_reg[0]_mux__32_n_0\,
      I4 => delay_cycles(7),
      I5 => \a_store_reg[0]_mux__31_n_0\,
      O => a_out_i_4_n_0
    );
a_out_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \a_store_reg[0]_mux__38_n_0\,
      I1 => \a_store_reg[0]_mux__37_n_0\,
      I2 => delay_cycles(8),
      I3 => \a_store_reg[0]_mux__36_n_0\,
      I4 => delay_cycles(7),
      I5 => \a_store_reg[0]_mux__35_n_0\,
      O => a_out_i_5_n_0
    );
a_out_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \a_store_reg[0]_mux__42_n_0\,
      I1 => \a_store_reg[0]_mux__41_n_0\,
      I2 => delay_cycles(8),
      I3 => \a_store_reg[0]_mux__40_n_0\,
      I4 => delay_cycles(7),
      I5 => \a_store_reg[0]_mux__39_n_0\,
      O => a_out_i_6_n_0
    );
a_out_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \a_store_reg[0]_mux__46_n_0\,
      I1 => \a_store_reg[0]_mux__45_n_0\,
      I2 => delay_cycles(8),
      I3 => \a_store_reg[0]_mux__44_n_0\,
      I4 => delay_cycles(7),
      I5 => \a_store_reg[0]_mux__43_n_0\,
      O => a_out_i_7_n_0
    );
a_out_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk,
      CE => '1',
      D => a_out0,
      Q => a_out,
      R => '0'
    );
a_out_reg_i_1: unisim.vcomponents.MUXF8
     port map (
      I0 => a_out_reg_i_2_n_0,
      I1 => a_out_reg_i_3_n_0,
      O => a_out0,
      S => delay_cycles(10)
    );
a_out_reg_i_2: unisim.vcomponents.MUXF7
     port map (
      I0 => a_out_i_4_n_0,
      I1 => a_out_i_5_n_0,
      O => a_out_reg_i_2_n_0,
      S => delay_cycles(9)
    );
a_out_reg_i_3: unisim.vcomponents.MUXF7
     port map (
      I0 => a_out_i_6_n_0,
      I1 => a_out_i_7_n_0,
      O => a_out_reg_i_3_n_0,
      S => delay_cycles(9)
    );
\a_store_reg[0]_mux\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32_n_0\,
      I1 => \a_store_reg[0]_srl32__0_n_0\,
      O => \a_store_reg[0]_mux_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__0\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__1_n_0\,
      I1 => \a_store_reg[0]_srl32__2_n_0\,
      O => \a_store_reg[0]_mux__0_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__1\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__3_n_0\,
      I1 => \a_store_reg[0]_srl32__4_n_0\,
      O => \a_store_reg[0]_mux__1_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__10\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__21_n_0\,
      I1 => \a_store_reg[0]_srl32__22_n_0\,
      O => \a_store_reg[0]_mux__10_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__11\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__23_n_0\,
      I1 => \a_store_reg[0]_srl32__24_n_0\,
      O => \a_store_reg[0]_mux__11_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__12\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__25_n_0\,
      I1 => \a_store_reg[0]_srl32__26_n_0\,
      O => \a_store_reg[0]_mux__12_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__13\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__27_n_0\,
      I1 => \a_store_reg[0]_srl32__28_n_0\,
      O => \a_store_reg[0]_mux__13_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__14\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__29_n_0\,
      I1 => \a_store_reg[0]_srl32__30_n_0\,
      O => \a_store_reg[0]_mux__14_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__15\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__31_n_0\,
      I1 => \a_store_reg[0]_srl32__32_n_0\,
      O => \a_store_reg[0]_mux__15_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__16\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__33_n_0\,
      I1 => \a_store_reg[0]_srl32__34_n_0\,
      O => \a_store_reg[0]_mux__16_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__17\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__35_n_0\,
      I1 => \a_store_reg[0]_srl32__36_n_0\,
      O => \a_store_reg[0]_mux__17_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__18\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__37_n_0\,
      I1 => \a_store_reg[0]_srl32__38_n_0\,
      O => \a_store_reg[0]_mux__18_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__19\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__39_n_0\,
      I1 => \a_store_reg[0]_srl32__40_n_0\,
      O => \a_store_reg[0]_mux__19_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__2\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__5_n_0\,
      I1 => \a_store_reg[0]_srl32__6_n_0\,
      O => \a_store_reg[0]_mux__2_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__20\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__41_n_0\,
      I1 => \a_store_reg[0]_srl32__42_n_0\,
      O => \a_store_reg[0]_mux__20_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__21\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__43_n_0\,
      I1 => \a_store_reg[0]_srl32__44_n_0\,
      O => \a_store_reg[0]_mux__21_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__22\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__45_n_0\,
      I1 => \a_store_reg[0]_srl32__46_n_0\,
      O => \a_store_reg[0]_mux__22_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__23\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__47_n_0\,
      I1 => \a_store_reg[0]_srl32__48_n_0\,
      O => \a_store_reg[0]_mux__23_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__24\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__49_n_0\,
      I1 => \a_store_reg[0]_srl32__50_n_0\,
      O => \a_store_reg[0]_mux__24_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__25\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__51_n_0\,
      I1 => \a_store_reg[0]_srl32__52_n_0\,
      O => \a_store_reg[0]_mux__25_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__26\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__53_n_0\,
      I1 => \a_store_reg[0]_srl32__54_n_0\,
      O => \a_store_reg[0]_mux__26_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__27\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__55_n_0\,
      I1 => \a_store_reg[0]_srl32__56_n_0\,
      O => \a_store_reg[0]_mux__27_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__28\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__57_n_0\,
      I1 => \a_store_reg[0]_srl32__58_n_0\,
      O => \a_store_reg[0]_mux__28_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__29\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__59_n_0\,
      I1 => \a_store_reg[0]_srl32__60_n_0\,
      O => \a_store_reg[0]_mux__29_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__3\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__7_n_0\,
      I1 => \a_store_reg[0]_srl32__8_n_0\,
      O => \a_store_reg[0]_mux__3_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__30\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__61_n_0\,
      I1 => \a_store_reg[0]_srl32__62_n_0\,
      O => \a_store_reg[0]_mux__30_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__31\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux_n_0\,
      I1 => \a_store_reg[0]_mux__0_n_0\,
      O => \a_store_reg[0]_mux__31_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__32\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__1_n_0\,
      I1 => \a_store_reg[0]_mux__2_n_0\,
      O => \a_store_reg[0]_mux__32_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__33\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__3_n_0\,
      I1 => \a_store_reg[0]_mux__4_n_0\,
      O => \a_store_reg[0]_mux__33_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__34\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__5_n_0\,
      I1 => \a_store_reg[0]_mux__6_n_0\,
      O => \a_store_reg[0]_mux__34_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__35\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__7_n_0\,
      I1 => \a_store_reg[0]_mux__8_n_0\,
      O => \a_store_reg[0]_mux__35_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__36\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__9_n_0\,
      I1 => \a_store_reg[0]_mux__10_n_0\,
      O => \a_store_reg[0]_mux__36_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__37\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__11_n_0\,
      I1 => \a_store_reg[0]_mux__12_n_0\,
      O => \a_store_reg[0]_mux__37_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__38\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__13_n_0\,
      I1 => \a_store_reg[0]_mux__14_n_0\,
      O => \a_store_reg[0]_mux__38_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__39\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__15_n_0\,
      I1 => \a_store_reg[0]_mux__16_n_0\,
      O => \a_store_reg[0]_mux__39_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__4\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__9_n_0\,
      I1 => \a_store_reg[0]_srl32__10_n_0\,
      O => \a_store_reg[0]_mux__4_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__40\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__17_n_0\,
      I1 => \a_store_reg[0]_mux__18_n_0\,
      O => \a_store_reg[0]_mux__40_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__41\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__19_n_0\,
      I1 => \a_store_reg[0]_mux__20_n_0\,
      O => \a_store_reg[0]_mux__41_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__42\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__21_n_0\,
      I1 => \a_store_reg[0]_mux__22_n_0\,
      O => \a_store_reg[0]_mux__42_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__43\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__23_n_0\,
      I1 => \a_store_reg[0]_mux__24_n_0\,
      O => \a_store_reg[0]_mux__43_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__44\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__25_n_0\,
      I1 => \a_store_reg[0]_mux__26_n_0\,
      O => \a_store_reg[0]_mux__44_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__45\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__27_n_0\,
      I1 => \a_store_reg[0]_mux__28_n_0\,
      O => \a_store_reg[0]_mux__45_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__46\: unisim.vcomponents.MUXF8
     port map (
      I0 => \a_store_reg[0]_mux__29_n_0\,
      I1 => \a_store_reg[0]_mux__30_n_0\,
      O => \a_store_reg[0]_mux__46_n_0\,
      S => delay_cycles(6)
    );
\a_store_reg[0]_mux__5\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__11_n_0\,
      I1 => \a_store_reg[0]_srl32__12_n_0\,
      O => \a_store_reg[0]_mux__5_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__6\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__13_n_0\,
      I1 => \a_store_reg[0]_srl32__14_n_0\,
      O => \a_store_reg[0]_mux__6_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__7\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__15_n_0\,
      I1 => \a_store_reg[0]_srl32__16_n_0\,
      O => \a_store_reg[0]_mux__7_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__8\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__17_n_0\,
      I1 => \a_store_reg[0]_srl32__18_n_0\,
      O => \a_store_reg[0]_mux__8_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_mux__9\: unisim.vcomponents.MUXF7
     port map (
      I0 => \a_store_reg[0]_srl32__19_n_0\,
      I1 => \a_store_reg[0]_srl32__20_n_0\,
      O => \a_store_reg[0]_mux__9_n_0\,
      S => delay_cycles(5)
    );
\a_store_reg[0]_srl32\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => a_in,
      Q => \a_store_reg[0]_srl32_n_0\,
      Q31 => \a_store_reg[0]_srl32_n_1\
    );
\a_store_reg[0]_srl32__0\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32_n_1\,
      Q => \a_store_reg[0]_srl32__0_n_0\,
      Q31 => \a_store_reg[0]_srl32__0_n_1\
    );
\a_store_reg[0]_srl32__1\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__0_n_1\,
      Q => \a_store_reg[0]_srl32__1_n_0\,
      Q31 => \a_store_reg[0]_srl32__1_n_1\
    );
\a_store_reg[0]_srl32__10\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__9_n_1\,
      Q => \a_store_reg[0]_srl32__10_n_0\,
      Q31 => \a_store_reg[0]_srl32__10_n_1\
    );
\a_store_reg[0]_srl32__11\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__10_n_1\,
      Q => \a_store_reg[0]_srl32__11_n_0\,
      Q31 => \a_store_reg[0]_srl32__11_n_1\
    );
\a_store_reg[0]_srl32__12\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__11_n_1\,
      Q => \a_store_reg[0]_srl32__12_n_0\,
      Q31 => \a_store_reg[0]_srl32__12_n_1\
    );
\a_store_reg[0]_srl32__13\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__12_n_1\,
      Q => \a_store_reg[0]_srl32__13_n_0\,
      Q31 => \a_store_reg[0]_srl32__13_n_1\
    );
\a_store_reg[0]_srl32__14\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__13_n_1\,
      Q => \a_store_reg[0]_srl32__14_n_0\,
      Q31 => \a_store_reg[0]_srl32__14_n_1\
    );
\a_store_reg[0]_srl32__15\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__14_n_1\,
      Q => \a_store_reg[0]_srl32__15_n_0\,
      Q31 => \a_store_reg[0]_srl32__15_n_1\
    );
\a_store_reg[0]_srl32__16\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__15_n_1\,
      Q => \a_store_reg[0]_srl32__16_n_0\,
      Q31 => \a_store_reg[0]_srl32__16_n_1\
    );
\a_store_reg[0]_srl32__17\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__16_n_1\,
      Q => \a_store_reg[0]_srl32__17_n_0\,
      Q31 => \a_store_reg[0]_srl32__17_n_1\
    );
\a_store_reg[0]_srl32__18\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__17_n_1\,
      Q => \a_store_reg[0]_srl32__18_n_0\,
      Q31 => \a_store_reg[0]_srl32__18_n_1\
    );
\a_store_reg[0]_srl32__19\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__18_n_1\,
      Q => \a_store_reg[0]_srl32__19_n_0\,
      Q31 => \a_store_reg[0]_srl32__19_n_1\
    );
\a_store_reg[0]_srl32__2\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__1_n_1\,
      Q => \a_store_reg[0]_srl32__2_n_0\,
      Q31 => \a_store_reg[0]_srl32__2_n_1\
    );
\a_store_reg[0]_srl32__20\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__19_n_1\,
      Q => \a_store_reg[0]_srl32__20_n_0\,
      Q31 => \a_store_reg[0]_srl32__20_n_1\
    );
\a_store_reg[0]_srl32__21\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__20_n_1\,
      Q => \a_store_reg[0]_srl32__21_n_0\,
      Q31 => \a_store_reg[0]_srl32__21_n_1\
    );
\a_store_reg[0]_srl32__22\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__21_n_1\,
      Q => \a_store_reg[0]_srl32__22_n_0\,
      Q31 => \a_store_reg[0]_srl32__22_n_1\
    );
\a_store_reg[0]_srl32__23\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__22_n_1\,
      Q => \a_store_reg[0]_srl32__23_n_0\,
      Q31 => \a_store_reg[0]_srl32__23_n_1\
    );
\a_store_reg[0]_srl32__24\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__23_n_1\,
      Q => \a_store_reg[0]_srl32__24_n_0\,
      Q31 => \a_store_reg[0]_srl32__24_n_1\
    );
\a_store_reg[0]_srl32__25\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__24_n_1\,
      Q => \a_store_reg[0]_srl32__25_n_0\,
      Q31 => \a_store_reg[0]_srl32__25_n_1\
    );
\a_store_reg[0]_srl32__26\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__25_n_1\,
      Q => \a_store_reg[0]_srl32__26_n_0\,
      Q31 => \a_store_reg[0]_srl32__26_n_1\
    );
\a_store_reg[0]_srl32__27\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__26_n_1\,
      Q => \a_store_reg[0]_srl32__27_n_0\,
      Q31 => \a_store_reg[0]_srl32__27_n_1\
    );
\a_store_reg[0]_srl32__28\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__27_n_1\,
      Q => \a_store_reg[0]_srl32__28_n_0\,
      Q31 => \a_store_reg[0]_srl32__28_n_1\
    );
\a_store_reg[0]_srl32__29\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__28_n_1\,
      Q => \a_store_reg[0]_srl32__29_n_0\,
      Q31 => \a_store_reg[0]_srl32__29_n_1\
    );
\a_store_reg[0]_srl32__3\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__2_n_1\,
      Q => \a_store_reg[0]_srl32__3_n_0\,
      Q31 => \a_store_reg[0]_srl32__3_n_1\
    );
\a_store_reg[0]_srl32__30\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__29_n_1\,
      Q => \a_store_reg[0]_srl32__30_n_0\,
      Q31 => \a_store_reg[0]_srl32__30_n_1\
    );
\a_store_reg[0]_srl32__31\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__30_n_1\,
      Q => \a_store_reg[0]_srl32__31_n_0\,
      Q31 => \a_store_reg[0]_srl32__31_n_1\
    );
\a_store_reg[0]_srl32__32\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__31_n_1\,
      Q => \a_store_reg[0]_srl32__32_n_0\,
      Q31 => \a_store_reg[0]_srl32__32_n_1\
    );
\a_store_reg[0]_srl32__33\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__32_n_1\,
      Q => \a_store_reg[0]_srl32__33_n_0\,
      Q31 => \a_store_reg[0]_srl32__33_n_1\
    );
\a_store_reg[0]_srl32__34\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__33_n_1\,
      Q => \a_store_reg[0]_srl32__34_n_0\,
      Q31 => \a_store_reg[0]_srl32__34_n_1\
    );
\a_store_reg[0]_srl32__35\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__34_n_1\,
      Q => \a_store_reg[0]_srl32__35_n_0\,
      Q31 => \a_store_reg[0]_srl32__35_n_1\
    );
\a_store_reg[0]_srl32__36\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__35_n_1\,
      Q => \a_store_reg[0]_srl32__36_n_0\,
      Q31 => \a_store_reg[0]_srl32__36_n_1\
    );
\a_store_reg[0]_srl32__37\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__36_n_1\,
      Q => \a_store_reg[0]_srl32__37_n_0\,
      Q31 => \a_store_reg[0]_srl32__37_n_1\
    );
\a_store_reg[0]_srl32__38\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__37_n_1\,
      Q => \a_store_reg[0]_srl32__38_n_0\,
      Q31 => \a_store_reg[0]_srl32__38_n_1\
    );
\a_store_reg[0]_srl32__39\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__38_n_1\,
      Q => \a_store_reg[0]_srl32__39_n_0\,
      Q31 => \a_store_reg[0]_srl32__39_n_1\
    );
\a_store_reg[0]_srl32__4\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__3_n_1\,
      Q => \a_store_reg[0]_srl32__4_n_0\,
      Q31 => \a_store_reg[0]_srl32__4_n_1\
    );
\a_store_reg[0]_srl32__40\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__39_n_1\,
      Q => \a_store_reg[0]_srl32__40_n_0\,
      Q31 => \a_store_reg[0]_srl32__40_n_1\
    );
\a_store_reg[0]_srl32__41\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__40_n_1\,
      Q => \a_store_reg[0]_srl32__41_n_0\,
      Q31 => \a_store_reg[0]_srl32__41_n_1\
    );
\a_store_reg[0]_srl32__42\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__41_n_1\,
      Q => \a_store_reg[0]_srl32__42_n_0\,
      Q31 => \a_store_reg[0]_srl32__42_n_1\
    );
\a_store_reg[0]_srl32__43\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__42_n_1\,
      Q => \a_store_reg[0]_srl32__43_n_0\,
      Q31 => \a_store_reg[0]_srl32__43_n_1\
    );
\a_store_reg[0]_srl32__44\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__43_n_1\,
      Q => \a_store_reg[0]_srl32__44_n_0\,
      Q31 => \a_store_reg[0]_srl32__44_n_1\
    );
\a_store_reg[0]_srl32__45\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__44_n_1\,
      Q => \a_store_reg[0]_srl32__45_n_0\,
      Q31 => \a_store_reg[0]_srl32__45_n_1\
    );
\a_store_reg[0]_srl32__46\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__45_n_1\,
      Q => \a_store_reg[0]_srl32__46_n_0\,
      Q31 => \a_store_reg[0]_srl32__46_n_1\
    );
\a_store_reg[0]_srl32__47\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__46_n_1\,
      Q => \a_store_reg[0]_srl32__47_n_0\,
      Q31 => \a_store_reg[0]_srl32__47_n_1\
    );
\a_store_reg[0]_srl32__48\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__47_n_1\,
      Q => \a_store_reg[0]_srl32__48_n_0\,
      Q31 => \a_store_reg[0]_srl32__48_n_1\
    );
\a_store_reg[0]_srl32__49\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__48_n_1\,
      Q => \a_store_reg[0]_srl32__49_n_0\,
      Q31 => \a_store_reg[0]_srl32__49_n_1\
    );
\a_store_reg[0]_srl32__5\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__4_n_1\,
      Q => \a_store_reg[0]_srl32__5_n_0\,
      Q31 => \a_store_reg[0]_srl32__5_n_1\
    );
\a_store_reg[0]_srl32__50\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__49_n_1\,
      Q => \a_store_reg[0]_srl32__50_n_0\,
      Q31 => \a_store_reg[0]_srl32__50_n_1\
    );
\a_store_reg[0]_srl32__51\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__50_n_1\,
      Q => \a_store_reg[0]_srl32__51_n_0\,
      Q31 => \a_store_reg[0]_srl32__51_n_1\
    );
\a_store_reg[0]_srl32__52\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__51_n_1\,
      Q => \a_store_reg[0]_srl32__52_n_0\,
      Q31 => \a_store_reg[0]_srl32__52_n_1\
    );
\a_store_reg[0]_srl32__53\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__52_n_1\,
      Q => \a_store_reg[0]_srl32__53_n_0\,
      Q31 => \a_store_reg[0]_srl32__53_n_1\
    );
\a_store_reg[0]_srl32__54\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__53_n_1\,
      Q => \a_store_reg[0]_srl32__54_n_0\,
      Q31 => \a_store_reg[0]_srl32__54_n_1\
    );
\a_store_reg[0]_srl32__55\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__54_n_1\,
      Q => \a_store_reg[0]_srl32__55_n_0\,
      Q31 => \a_store_reg[0]_srl32__55_n_1\
    );
\a_store_reg[0]_srl32__56\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__55_n_1\,
      Q => \a_store_reg[0]_srl32__56_n_0\,
      Q31 => \a_store_reg[0]_srl32__56_n_1\
    );
\a_store_reg[0]_srl32__57\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__56_n_1\,
      Q => \a_store_reg[0]_srl32__57_n_0\,
      Q31 => \a_store_reg[0]_srl32__57_n_1\
    );
\a_store_reg[0]_srl32__58\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__57_n_1\,
      Q => \a_store_reg[0]_srl32__58_n_0\,
      Q31 => \a_store_reg[0]_srl32__58_n_1\
    );
\a_store_reg[0]_srl32__59\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__58_n_1\,
      Q => \a_store_reg[0]_srl32__59_n_0\,
      Q31 => \a_store_reg[0]_srl32__59_n_1\
    );
\a_store_reg[0]_srl32__6\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__5_n_1\,
      Q => \a_store_reg[0]_srl32__6_n_0\,
      Q31 => \a_store_reg[0]_srl32__6_n_1\
    );
\a_store_reg[0]_srl32__60\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__59_n_1\,
      Q => \a_store_reg[0]_srl32__60_n_0\,
      Q31 => \a_store_reg[0]_srl32__60_n_1\
    );
\a_store_reg[0]_srl32__61\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__60_n_1\,
      Q => \a_store_reg[0]_srl32__61_n_0\,
      Q31 => \a_store_reg[0]_srl32__61_n_1\
    );
\a_store_reg[0]_srl32__62\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__61_n_1\,
      Q => \a_store_reg[0]_srl32__62_n_0\,
      Q31 => \NLW_a_store_reg[0]_srl32__62_Q31_UNCONNECTED\
    );
\a_store_reg[0]_srl32__7\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__6_n_1\,
      Q => \a_store_reg[0]_srl32__7_n_0\,
      Q31 => \a_store_reg[0]_srl32__7_n_1\
    );
\a_store_reg[0]_srl32__8\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__7_n_1\,
      Q => \a_store_reg[0]_srl32__8_n_0\,
      Q31 => \a_store_reg[0]_srl32__8_n_1\
    );
\a_store_reg[0]_srl32__9\: unisim.vcomponents.SRLC32E
    generic map(
      INIT => X"00000000"
    )
        port map (
      A(4 downto 0) => delay_cycles(4 downto 0),
      CE => '1',
      CLK => clk,
      D => \a_store_reg[0]_srl32__8_n_1\,
      Q => \a_store_reg[0]_srl32__9_n_0\,
      Q31 => \a_store_reg[0]_srl32__9_n_1\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_delay_trigger_0_0 is
  port (
    clk : in STD_LOGIC;
    delay_cycles : in STD_LOGIC_VECTOR ( 10 downto 0 );
    a_in : in STD_LOGIC;
    a_out : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_delay_trigger_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_delay_trigger_0_0 : entity is "zusys_delay_trigger_0_0,delay_trigger,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_delay_trigger_0_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_delay_trigger_0_0 : entity is "module_ref";
  attribute x_core_info : string;
  attribute x_core_info of zusys_delay_trigger_0_0 : entity is "delay_trigger,Vivado 2020.1.1";
end zusys_delay_trigger_0_0;

architecture STRUCTURE of zusys_delay_trigger_0_0 is
  attribute x_interface_info : string;
  attribute x_interface_info of clk : signal is "xilinx.com:signal:clock:1.0 clk CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of clk : signal is "XIL_INTERFACENAME clk, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
begin
U0: entity work.zusys_delay_trigger_0_0_delay_trigger
     port map (
      a_in => a_in,
      a_out => a_out,
      clk => clk,
      delay_cycles(10 downto 0) => delay_cycles(10 downto 0)
    );
end STRUCTURE;
