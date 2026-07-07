--Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2.2 (lin64) Build 3788238 Tue Feb 21 19:59:23 MST 2023
--Date        : Tue Jul  7 15:35:49 2026
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
    Dig_11_Ch1 : in STD_LOGIC;
    Dig_11_Ch2 : in STD_LOGIC;
    Dig_11_Ch3 : in STD_LOGIC;
    Dig_11_Ch4 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_12_Ch1 : in STD_LOGIC;
    Dig_12_Ch2 : in STD_LOGIC;
    Dig_12_Ch3 : in STD_LOGIC;
    Dig_12_Ch4 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_13_Ch1 : in STD_LOGIC;
    Dig_13_Ch2 : in STD_LOGIC;
    Dig_13_Ch3 : in STD_LOGIC;
    Dig_13_Ch4 : in STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch1 : in STD_LOGIC;
    Dig_14_Ch2 : in STD_LOGIC;
    Dig_14_Ch3 : in STD_LOGIC;
    Dig_14_Ch4 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch1 : in STD_LOGIC;
    Dig_15_Ch2 : in STD_LOGIC;
    Dig_15_Ch3 : in STD_LOGIC;
    Dig_15_Ch4 : in STD_LOGIC;
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_16_Ch1 : in STD_LOGIC;
    Dig_16_Ch2 : in STD_LOGIC;
    Dig_16_Ch3 : in STD_LOGIC;
    Dig_16_Ch4 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_17_Ch1 : in STD_LOGIC;
    Dig_17_Ch2 : in STD_LOGIC;
    Dig_17_Ch3 : in STD_LOGIC;
    Dig_17_Ch4 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_18_Ch1 : in STD_LOGIC;
    Dig_18_Ch2 : in STD_LOGIC;
    Dig_18_Ch3 : in STD_LOGIC;
    Dig_18_Ch4 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_19_Ch1 : in STD_LOGIC;
    Dig_19_Ch2 : in STD_LOGIC;
    Dig_19_Ch3 : in STD_LOGIC;
    Dig_19_Ch4 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    Dig_11_Ch1 : in STD_LOGIC;
    Dig_12_Ch1 : in STD_LOGIC;
    Dig_13_Ch1 : in STD_LOGIC;
    Dig_14_Ch1 : in STD_LOGIC;
    Dig_15_Ch1 : in STD_LOGIC;
    Dig_16_Ch1 : in STD_LOGIC;
    Dig_17_Ch1 : in STD_LOGIC;
    Dig_18_Ch1 : in STD_LOGIC;
    Dig_19_Ch1 : in STD_LOGIC;
    Dig_11_Ch2 : in STD_LOGIC;
    Dig_12_Ch2 : in STD_LOGIC;
    Dig_13_Ch2 : in STD_LOGIC;
    Dig_14_Ch2 : in STD_LOGIC;
    Dig_15_Ch2 : in STD_LOGIC;
    Dig_16_Ch2 : in STD_LOGIC;
    Dig_17_Ch2 : in STD_LOGIC;
    Dig_18_Ch2 : in STD_LOGIC;
    Dig_19_Ch2 : in STD_LOGIC;
    Dig_11_Ch3 : in STD_LOGIC;
    Dig_12_Ch3 : in STD_LOGIC;
    Dig_13_Ch3 : in STD_LOGIC;
    Dig_14_Ch3 : in STD_LOGIC;
    Dig_15_Ch3 : in STD_LOGIC;
    Dig_16_Ch3 : in STD_LOGIC;
    Dig_17_Ch3 : in STD_LOGIC;
    Dig_18_Ch3 : in STD_LOGIC;
    Dig_19_Ch3 : in STD_LOGIC;
    Dig_11_Ch4 : in STD_LOGIC;
    Dig_12_Ch4 : in STD_LOGIC;
    Dig_13_Ch4 : in STD_LOGIC;
    Dig_14_Ch4 : in STD_LOGIC;
    Dig_15_Ch4 : in STD_LOGIC;
    Dig_16_Ch4 : in STD_LOGIC;
    Dig_17_Ch4 : in STD_LOGIC;
    Dig_18_Ch4 : in STD_LOGIC;
    Dig_19_Ch4 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      Dig_11_Ch1 => Dig_11_Ch1,
      Dig_11_Ch2 => Dig_11_Ch2,
      Dig_11_Ch3 => Dig_11_Ch3,
      Dig_11_Ch4 => Dig_11_Ch4,
      Dig_11_Ch5 => Dig_11_Ch5,
      Dig_12_Ch1 => Dig_12_Ch1,
      Dig_12_Ch2 => Dig_12_Ch2,
      Dig_12_Ch3 => Dig_12_Ch3,
      Dig_12_Ch4 => Dig_12_Ch4,
      Dig_12_Ch5 => Dig_12_Ch5,
      Dig_13_Ch1 => Dig_13_Ch1,
      Dig_13_Ch2 => Dig_13_Ch2,
      Dig_13_Ch3 => Dig_13_Ch3,
      Dig_13_Ch4 => Dig_13_Ch4,
      Dig_13_Ch5 => Dig_13_Ch5,
      Dig_14_Ch1 => Dig_14_Ch1,
      Dig_14_Ch2 => Dig_14_Ch2,
      Dig_14_Ch3 => Dig_14_Ch3,
      Dig_14_Ch4 => Dig_14_Ch4,
      Dig_14_Ch5 => Dig_14_Ch5,
      Dig_15_Ch1 => Dig_15_Ch1,
      Dig_15_Ch2 => Dig_15_Ch2,
      Dig_15_Ch3 => Dig_15_Ch3,
      Dig_15_Ch4 => Dig_15_Ch4,
      Dig_15_Ch5 => Dig_15_Ch5,
      Dig_16_Ch1 => Dig_16_Ch1,
      Dig_16_Ch2 => Dig_16_Ch2,
      Dig_16_Ch3 => Dig_16_Ch3,
      Dig_16_Ch4 => Dig_16_Ch4,
      Dig_16_Ch5 => Dig_16_Ch5,
      Dig_17_Ch1 => Dig_17_Ch1,
      Dig_17_Ch2 => Dig_17_Ch2,
      Dig_17_Ch3 => Dig_17_Ch3,
      Dig_17_Ch4 => Dig_17_Ch4,
      Dig_17_Ch5 => Dig_17_Ch5,
      Dig_18_Ch1 => Dig_18_Ch1,
      Dig_18_Ch2 => Dig_18_Ch2,
      Dig_18_Ch3 => Dig_18_Ch3,
      Dig_18_Ch4 => Dig_18_Ch4,
      Dig_18_Ch5 => Dig_18_Ch5,
      Dig_19_Ch1 => Dig_19_Ch1,
      Dig_19_Ch2 => Dig_19_Ch2,
      Dig_19_Ch3 => Dig_19_Ch3,
      Dig_19_Ch4 => Dig_19_Ch4,
      Dig_19_Ch5 => Dig_19_Ch5
    );
end STRUCTURE;
