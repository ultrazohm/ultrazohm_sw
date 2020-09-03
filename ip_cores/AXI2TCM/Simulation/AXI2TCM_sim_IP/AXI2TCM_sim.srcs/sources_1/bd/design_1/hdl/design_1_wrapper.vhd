--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
--Date        : Tue Nov 13 14:43:10 2018
--Host        : TUEIEAL-TM01 running 64-bit major release  (build 9200)
--Command     : generate_target design_1_wrapper.bd
--Design      : design_1_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_wrapper is
  port (
    DATA_IN : in STD_LOGIC_VECTOR ( 143 downto 0 );
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    axi_error_0 : out STD_LOGIC;
    axi_txn_done_0 : out STD_LOGIC;
    m00_axi_init_axi_txn : in STD_LOGIC;
    write_done_0 : out STD_LOGIC
  );
end design_1_wrapper;

architecture STRUCTURE of design_1_wrapper is
  component design_1 is
  port (
    aresetn : in STD_LOGIC;
    aclk : in STD_LOGIC;
    m00_axi_init_axi_txn : in STD_LOGIC;
    DATA_IN : in STD_LOGIC_VECTOR ( 143 downto 0 );
    write_done_0 : out STD_LOGIC;
    axi_txn_done_0 : out STD_LOGIC;
    axi_error_0 : out STD_LOGIC
  );
  end component design_1;
begin
design_1_i: component design_1
     port map (
      DATA_IN(143 downto 0) => DATA_IN(143 downto 0),
      aclk => aclk,
      aresetn => aresetn,
      axi_error_0 => axi_error_0,
      axi_txn_done_0 => axi_txn_done_0,
      m00_axi_init_axi_txn => m00_axi_init_axi_txn,
      write_done_0 => write_done_0
    );
end STRUCTURE;
