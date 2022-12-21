--Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
--Date        : Wed Dec 21 12:32:41 2022
--Host        : enc177112 running 64-bit major release  (build 9200)
--Command     : generate_target interface_mon_wrapper.bd
--Design      : interface_mon_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity interface_mon_wrapper is
  port (
    H1_FAULT : in STD_LOGIC;
    H1_FAULT_mon : out STD_LOGIC;
    H2_FAULT : in STD_LOGIC;
    H2_FAULT_mon : out STD_LOGIC;
    H3_FAULT : in STD_LOGIC;
    H3_FAULT_mon : out STD_LOGIC;
    L1_FAULT : in STD_LOGIC;
    L1_FAULT_mon : out STD_LOGIC;
    L2_FAULT : in STD_LOGIC;
    L2_FAULT_mon : out STD_LOGIC;
    L3_FAULT : in STD_LOGIC;
    L3_FAULT_mon : out STD_LOGIC
  );
end interface_mon_wrapper;

architecture STRUCTURE of interface_mon_wrapper is
  component interface_mon is
  port (
    H1_FAULT_mon : out STD_LOGIC;
    L1_FAULT_mon : out STD_LOGIC;
    H2_FAULT_mon : out STD_LOGIC;
    L2_FAULT_mon : out STD_LOGIC;
    H3_FAULT_mon : out STD_LOGIC;
    L3_FAULT_mon : out STD_LOGIC;
    H1_FAULT : in STD_LOGIC;
    L1_FAULT : in STD_LOGIC;
    H2_FAULT : in STD_LOGIC;
    L2_FAULT : in STD_LOGIC;
    H3_FAULT : in STD_LOGIC;
    L3_FAULT : in STD_LOGIC
  );
  end component interface_mon;
begin
interface_mon_i: component interface_mon
     port map (
      H1_FAULT => H1_FAULT,
      H1_FAULT_mon => H1_FAULT_mon,
      H2_FAULT => H2_FAULT,
      H2_FAULT_mon => H2_FAULT_mon,
      H3_FAULT => H3_FAULT,
      H3_FAULT_mon => H3_FAULT_mon,
      L1_FAULT => L1_FAULT,
      L1_FAULT_mon => L1_FAULT_mon,
      L2_FAULT => L2_FAULT,
      L2_FAULT_mon => L2_FAULT_mon,
      L3_FAULT => L3_FAULT,
      L3_FAULT_mon => L3_FAULT_mon
    );
end STRUCTURE;
