--Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
--Date        : Mon May  8 17:31:19 2023
--Host        : enc177112 running 64-bit major release  (build 9200)
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
    A1_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A1_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A1_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A2_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A2_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A3_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A3_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT : out STD_LOGIC_VECTOR ( 25 downto 0 );
    Dig_00_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_02_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_03_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_04_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_05_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch5 : out STD_LOGIC;
    Dig_07_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_07_Ch5 : out STD_LOGIC;
    Dig_08_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_08_Ch5 : out STD_LOGIC;
    Dig_09_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch5 : out STD_LOGIC;
    Dig_10_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_10_Ch5 : out STD_LOGIC;
    Dig_11_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_11_Ch5 : out STD_LOGIC;
    Dig_12_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_12_Ch5 : out STD_LOGIC;
    Dig_13_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_13_Ch5 : out STD_LOGIC;
    Dig_14_Ch1 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch1 : in STD_LOGIC;
    Dig_16_Ch1 : in STD_LOGIC;
    Dig_17_Ch1 : in STD_LOGIC;
    Dig_23_Ch5 : in STD_LOGIC
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    A1_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A1_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A1_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A2_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A2_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A3_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A3_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT : out STD_LOGIC_VECTOR ( 25 downto 0 );
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_23_Ch5 : in STD_LOGIC;
    Dig_14_Ch1 : in STD_LOGIC;
    Dig_15_Ch1 : in STD_LOGIC;
    Dig_16_Ch1 : in STD_LOGIC;
    Dig_17_Ch1 : in STD_LOGIC;
    Dig_00_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_02_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_04_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_08_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_10_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_12_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_13_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_03_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_05_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_07_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_11_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_07_Ch5 : out STD_LOGIC;
    Dig_09_Ch5 : out STD_LOGIC;
    Dig_13_Ch5 : out STD_LOGIC;
    Dig_06_Ch5 : out STD_LOGIC;
    Dig_10_Ch5 : out STD_LOGIC;
    Dig_08_Ch5 : out STD_LOGIC;
    Dig_12_Ch5 : out STD_LOGIC;
    Dig_11_Ch5 : out STD_LOGIC
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      A1_IN(15 downto 0) => A1_IN(15 downto 0),
      A1_OUT_CLK(1 downto 0) => A1_OUT_CLK(1 downto 0),
      A1_OUT_CNV_0(0) => A1_OUT_CNV_0(0),
      A1_OUT_CNV_1(0) => A1_OUT_CNV_1(0),
      A2_IN(15 downto 0) => A2_IN(15 downto 0),
      A2_OUT_CLK(1 downto 0) => A2_OUT_CLK(1 downto 0),
      A2_OUT_CNV_0(0) => A2_OUT_CNV_0(0),
      A2_OUT_CNV_1(0) => A2_OUT_CNV_1(0),
      A3_IN(15 downto 0) => A3_IN(15 downto 0),
      A3_OUT_CLK(1 downto 0) => A3_OUT_CLK(1 downto 0),
      A3_OUT_CNV_0(0) => A3_OUT_CNV_0(0),
      A3_OUT_CNV_1(0) => A3_OUT_CNV_1(0),
      D3_OUT(25 downto 0) => D3_OUT(25 downto 0),
      Dig_00_Ch1(0) => Dig_00_Ch1(0),
      Dig_01_Ch1(0) => Dig_01_Ch1(0),
      Dig_02_Ch1(0) => Dig_02_Ch1(0),
      Dig_03_Ch1(0) => Dig_03_Ch1(0),
      Dig_04_Ch1(0) => Dig_04_Ch1(0),
      Dig_05_Ch1(0) => Dig_05_Ch1(0),
      Dig_06_Ch1(0) => Dig_06_Ch1(0),
      Dig_06_Ch5 => Dig_06_Ch5,
      Dig_07_Ch1(0) => Dig_07_Ch1(0),
      Dig_07_Ch5 => Dig_07_Ch5,
      Dig_08_Ch1(0) => Dig_08_Ch1(0),
      Dig_08_Ch5 => Dig_08_Ch5,
      Dig_09_Ch1(0) => Dig_09_Ch1(0),
      Dig_09_Ch5 => Dig_09_Ch5,
      Dig_10_Ch1(0) => Dig_10_Ch1(0),
      Dig_10_Ch5 => Dig_10_Ch5,
      Dig_11_Ch1(0) => Dig_11_Ch1(0),
      Dig_11_Ch5 => Dig_11_Ch5,
      Dig_12_Ch1(0) => Dig_12_Ch1(0),
      Dig_12_Ch5 => Dig_12_Ch5,
      Dig_13_Ch1(0) => Dig_13_Ch1(0),
      Dig_13_Ch5 => Dig_13_Ch5,
      Dig_14_Ch1 => Dig_14_Ch1,
      Dig_14_Ch5 => Dig_14_Ch5,
      Dig_15_Ch1 => Dig_15_Ch1,
      Dig_16_Ch1 => Dig_16_Ch1,
      Dig_17_Ch1 => Dig_17_Ch1,
      Dig_23_Ch5 => Dig_23_Ch5
    );
end STRUCTURE;
