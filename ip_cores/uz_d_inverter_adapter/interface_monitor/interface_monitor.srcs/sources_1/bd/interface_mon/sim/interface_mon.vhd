--Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
--Date        : Wed Dec 21 12:32:41 2022
--Host        : enc177112 running 64-bit major release  (build 9200)
--Command     : generate_target interface_mon.bd
--Design      : interface_mon
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity interface_mon is
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
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of interface_mon : entity is "interface_mon,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=interface_mon,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=0,numReposBlks=0,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of interface_mon : entity is "interface_mon.hwdef";
end interface_mon;

architecture STRUCTURE of interface_mon is
  signal H1_FAULT_1 : STD_LOGIC;
  signal H2_FAULT_1 : STD_LOGIC;
  signal H3_FAULT_1 : STD_LOGIC;
  signal L1_FAULT_1 : STD_LOGIC;
  signal L2_FAULT_1 : STD_LOGIC;
  signal L3_FAULT_1 : STD_LOGIC;
begin
  H1_FAULT_1 <= H1_FAULT;
  H1_FAULT_mon <= H1_FAULT_1;
  H2_FAULT_1 <= H2_FAULT;
  H2_FAULT_mon <= H2_FAULT_1;
  H3_FAULT_1 <= H3_FAULT;
  H3_FAULT_mon <= H3_FAULT_1;
  L1_FAULT_1 <= L1_FAULT;
  L1_FAULT_mon <= L1_FAULT_1;
  L2_FAULT_1 <= L2_FAULT;
  L2_FAULT_mon <= L2_FAULT_1;
  L3_FAULT_1 <= L3_FAULT;
  L3_FAULT_mon <= L3_FAULT_1;
end STRUCTURE;
