--Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2.2 (lin64) Build 3788238 Tue Feb 21 19:59:23 MST 2023
--Date        : Wed Aug 12 14:00:16 2026
--Host        : lin1 running 64-bit Ubuntu 22.04.5 LTS
--Command     : generate_target zusys_wrapper.bd
--Design      : zusys_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_wrapper is
  port (
    Dig_00_Ch3 : out STD_LOGIC;
    Dig_00_Ch4 : out STD_LOGIC;
    Dig_01_Ch3 : out STD_LOGIC;
    Dig_01_Ch4 : out STD_LOGIC;
    Dig_02_Ch3 : in STD_LOGIC;
    Dig_02_Ch4 : in STD_LOGIC;
    Dig_03_Ch3 : out STD_LOGIC;
    Dig_03_Ch4 : out STD_LOGIC;
    Dig_04_Ch3 : in STD_LOGIC;
    Dig_04_Ch4 : in STD_LOGIC;
    Dig_06_Ch3 : out STD_LOGIC;
    Dig_06_Ch4 : out STD_LOGIC;
    Dig_07_Ch3 : out STD_LOGIC;
    Dig_07_Ch4 : out STD_LOGIC;
    Dig_08_Ch3 : in STD_LOGIC;
    Dig_08_Ch4 : in STD_LOGIC;
    Dig_09_Ch3 : out STD_LOGIC;
    Dig_09_Ch4 : out STD_LOGIC;
    Dig_10_Ch3 : in STD_LOGIC;
    Dig_10_Ch4 : in STD_LOGIC;
    Dig_12_Ch3 : out STD_LOGIC;
    Dig_12_Ch4 : out STD_LOGIC;
    Dig_13_Ch3 : out STD_LOGIC;
    Dig_13_Ch4 : out STD_LOGIC;
    Dig_14_Ch3 : in STD_LOGIC;
    Dig_14_Ch4 : in STD_LOGIC;
    Dig_15_Ch3 : out STD_LOGIC;
    Dig_15_Ch4 : out STD_LOGIC;
    Dig_16_Ch3 : in STD_LOGIC;
    Dig_16_Ch4 : in STD_LOGIC;
    Dig_18_Ch3 : out STD_LOGIC;
    Dig_18_Ch4 : out STD_LOGIC
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    Dig_00_Ch3 : out STD_LOGIC;
    Dig_01_Ch3 : out STD_LOGIC;
    Dig_02_Ch3 : in STD_LOGIC;
    Dig_03_Ch3 : out STD_LOGIC;
    Dig_04_Ch3 : in STD_LOGIC;
    Dig_06_Ch3 : out STD_LOGIC;
    Dig_07_Ch3 : out STD_LOGIC;
    Dig_08_Ch3 : in STD_LOGIC;
    Dig_09_Ch3 : out STD_LOGIC;
    Dig_10_Ch3 : in STD_LOGIC;
    Dig_12_Ch3 : out STD_LOGIC;
    Dig_13_Ch3 : out STD_LOGIC;
    Dig_14_Ch3 : in STD_LOGIC;
    Dig_15_Ch3 : out STD_LOGIC;
    Dig_16_Ch3 : in STD_LOGIC;
    Dig_18_Ch3 : out STD_LOGIC;
    Dig_00_Ch4 : out STD_LOGIC;
    Dig_01_Ch4 : out STD_LOGIC;
    Dig_02_Ch4 : in STD_LOGIC;
    Dig_03_Ch4 : out STD_LOGIC;
    Dig_04_Ch4 : in STD_LOGIC;
    Dig_06_Ch4 : out STD_LOGIC;
    Dig_07_Ch4 : out STD_LOGIC;
    Dig_08_Ch4 : in STD_LOGIC;
    Dig_09_Ch4 : out STD_LOGIC;
    Dig_10_Ch4 : in STD_LOGIC;
    Dig_12_Ch4 : out STD_LOGIC;
    Dig_13_Ch4 : out STD_LOGIC;
    Dig_14_Ch4 : in STD_LOGIC;
    Dig_15_Ch4 : out STD_LOGIC;
    Dig_16_Ch4 : in STD_LOGIC;
    Dig_18_Ch4 : out STD_LOGIC
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      Dig_00_Ch3 => Dig_00_Ch3,
      Dig_00_Ch4 => Dig_00_Ch4,
      Dig_01_Ch3 => Dig_01_Ch3,
      Dig_01_Ch4 => Dig_01_Ch4,
      Dig_02_Ch3 => Dig_02_Ch3,
      Dig_02_Ch4 => Dig_02_Ch4,
      Dig_03_Ch3 => Dig_03_Ch3,
      Dig_03_Ch4 => Dig_03_Ch4,
      Dig_04_Ch3 => Dig_04_Ch3,
      Dig_04_Ch4 => Dig_04_Ch4,
      Dig_06_Ch3 => Dig_06_Ch3,
      Dig_06_Ch4 => Dig_06_Ch4,
      Dig_07_Ch3 => Dig_07_Ch3,
      Dig_07_Ch4 => Dig_07_Ch4,
      Dig_08_Ch3 => Dig_08_Ch3,
      Dig_08_Ch4 => Dig_08_Ch4,
      Dig_09_Ch3 => Dig_09_Ch3,
      Dig_09_Ch4 => Dig_09_Ch4,
      Dig_10_Ch3 => Dig_10_Ch3,
      Dig_10_Ch4 => Dig_10_Ch4,
      Dig_12_Ch3 => Dig_12_Ch3,
      Dig_12_Ch4 => Dig_12_Ch4,
      Dig_13_Ch3 => Dig_13_Ch3,
      Dig_13_Ch4 => Dig_13_Ch4,
      Dig_14_Ch3 => Dig_14_Ch3,
      Dig_14_Ch4 => Dig_14_Ch4,
      Dig_15_Ch3 => Dig_15_Ch3,
      Dig_15_Ch4 => Dig_15_Ch4,
      Dig_16_Ch3 => Dig_16_Ch3,
      Dig_16_Ch4 => Dig_16_Ch4,
      Dig_18_Ch3 => Dig_18_Ch3,
      Dig_18_Ch4 => Dig_18_Ch4
    );
end STRUCTURE;
