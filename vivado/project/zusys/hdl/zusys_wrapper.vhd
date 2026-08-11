--Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2.2 (lin64) Build 3788238 Tue Feb 21 19:59:23 MST 2023
--Date        : Tue Aug 11 16:03:51 2026
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
    A1_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A1_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A1_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A2_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A2_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_00_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_00_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_02_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_02_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_03_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_03_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_04_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_04_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_05_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_05_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch2 : in STD_LOGIC;
    Dig_07_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_07_Ch2 : in STD_LOGIC;
    Dig_08_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_08_Ch2 : in STD_LOGIC;
    Dig_09_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch2 : in STD_LOGIC;
    Dig_10_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_10_Ch2 : in STD_LOGIC;
    Dig_11_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_11_Ch2 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_12_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_12_Ch2 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_13_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_13_Ch2 : in STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch1 : in STD_LOGIC;
    Dig_14_Ch2 : out STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch1 : in STD_LOGIC;
    Dig_15_Ch2 : in STD_LOGIC;
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_16_Ch1 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_17_Ch1 : in STD_LOGIC;
    Dig_17_Ch2 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_18_Ch2 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_19_Ch2 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC;
    Dig_20_Ch2 : in STD_LOGIC;
    Dig_21_Ch2 : in STD_LOGIC;
    Dig_22_Ch2 : in STD_LOGIC;
    Dig_23_Ch2 : in STD_LOGIC;
    Dig_24_Ch2 : in STD_LOGIC;
    Dig_25_Ch2 : in STD_LOGIC;
    Dig_26_Ch2 : in STD_LOGIC;
    Dig_27_Ch2 : in STD_LOGIC;
    Dig_28_Ch2 : in STD_LOGIC;
    Dig_29_Ch2 : in STD_LOGIC
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    A1_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A1_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A2_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A2_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    Dig_00_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_02_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_03_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_04_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_05_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_07_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_08_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_10_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_11_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_12_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_13_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_14_Ch1 : in STD_LOGIC;
    Dig_15_Ch1 : in STD_LOGIC;
    Dig_16_Ch1 : in STD_LOGIC;
    Dig_17_Ch1 : in STD_LOGIC;
    Dig_00_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_02_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_03_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_04_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_05_Ch2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_14_Ch2 : out STD_LOGIC;
    Dig_06_Ch2 : in STD_LOGIC;
    Dig_07_Ch2 : in STD_LOGIC;
    Dig_08_Ch2 : in STD_LOGIC;
    Dig_09_Ch2 : in STD_LOGIC;
    Dig_10_Ch2 : in STD_LOGIC;
    Dig_11_Ch2 : in STD_LOGIC;
    Dig_12_Ch2 : in STD_LOGIC;
    Dig_13_Ch2 : in STD_LOGIC;
    Dig_15_Ch2 : in STD_LOGIC;
    Dig_17_Ch2 : in STD_LOGIC;
    Dig_18_Ch2 : in STD_LOGIC;
    Dig_19_Ch2 : in STD_LOGIC;
    Dig_20_Ch2 : in STD_LOGIC;
    Dig_21_Ch2 : in STD_LOGIC;
    Dig_22_Ch2 : in STD_LOGIC;
    Dig_23_Ch2 : in STD_LOGIC;
    Dig_24_Ch2 : in STD_LOGIC;
    Dig_25_Ch2 : in STD_LOGIC;
    Dig_26_Ch2 : in STD_LOGIC;
    Dig_27_Ch2 : in STD_LOGIC;
    Dig_28_Ch2 : in STD_LOGIC;
    Dig_29_Ch2 : in STD_LOGIC;
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
      A1_IN(15 downto 0) => A1_IN(15 downto 0),
      A1_OUT_CLK(1 downto 0) => A1_OUT_CLK(1 downto 0),
      A1_OUT_CNV_0(0) => A1_OUT_CNV_0(0),
      A1_OUT_CNV_1(0) => A1_OUT_CNV_1(0),
      A2_IN(15 downto 0) => A2_IN(15 downto 0),
      A2_OUT_CLK(1 downto 0) => A2_OUT_CLK(1 downto 0),
      A2_OUT_CNV_0(0) => A2_OUT_CNV_0(0),
      A2_OUT_CNV_1(0) => A2_OUT_CNV_1(0),
      Dig_00_Ch1(0) => Dig_00_Ch1(0),
      Dig_00_Ch2(0) => Dig_00_Ch2(0),
      Dig_01_Ch1(0) => Dig_01_Ch1(0),
      Dig_01_Ch2(0) => Dig_01_Ch2(0),
      Dig_02_Ch1(0) => Dig_02_Ch1(0),
      Dig_02_Ch2(0) => Dig_02_Ch2(0),
      Dig_03_Ch1(0) => Dig_03_Ch1(0),
      Dig_03_Ch2(0) => Dig_03_Ch2(0),
      Dig_04_Ch1(0) => Dig_04_Ch1(0),
      Dig_04_Ch2(0) => Dig_04_Ch2(0),
      Dig_05_Ch1(0) => Dig_05_Ch1(0),
      Dig_05_Ch2(0) => Dig_05_Ch2(0),
      Dig_06_Ch1(0) => Dig_06_Ch1(0),
      Dig_06_Ch2 => Dig_06_Ch2,
      Dig_07_Ch1(0) => Dig_07_Ch1(0),
      Dig_07_Ch2 => Dig_07_Ch2,
      Dig_08_Ch1(0) => Dig_08_Ch1(0),
      Dig_08_Ch2 => Dig_08_Ch2,
      Dig_09_Ch1(0) => Dig_09_Ch1(0),
      Dig_09_Ch2 => Dig_09_Ch2,
      Dig_10_Ch1(0) => Dig_10_Ch1(0),
      Dig_10_Ch2 => Dig_10_Ch2,
      Dig_11_Ch1(0) => Dig_11_Ch1(0),
      Dig_11_Ch2 => Dig_11_Ch2,
      Dig_11_Ch5 => Dig_11_Ch5,
      Dig_12_Ch1(0) => Dig_12_Ch1(0),
      Dig_12_Ch2 => Dig_12_Ch2,
      Dig_12_Ch5 => Dig_12_Ch5,
      Dig_13_Ch1(0) => Dig_13_Ch1(0),
      Dig_13_Ch2 => Dig_13_Ch2,
      Dig_13_Ch5 => Dig_13_Ch5,
      Dig_14_Ch1 => Dig_14_Ch1,
      Dig_14_Ch2 => Dig_14_Ch2,
      Dig_14_Ch5 => Dig_14_Ch5,
      Dig_15_Ch1 => Dig_15_Ch1,
      Dig_15_Ch2 => Dig_15_Ch2,
      Dig_15_Ch5 => Dig_15_Ch5,
      Dig_16_Ch1 => Dig_16_Ch1,
      Dig_16_Ch5 => Dig_16_Ch5,
      Dig_17_Ch1 => Dig_17_Ch1,
      Dig_17_Ch2 => Dig_17_Ch2,
      Dig_17_Ch5 => Dig_17_Ch5,
      Dig_18_Ch2 => Dig_18_Ch2,
      Dig_18_Ch5 => Dig_18_Ch5,
      Dig_19_Ch2 => Dig_19_Ch2,
      Dig_19_Ch5 => Dig_19_Ch5,
      Dig_20_Ch2 => Dig_20_Ch2,
      Dig_21_Ch2 => Dig_21_Ch2,
      Dig_22_Ch2 => Dig_22_Ch2,
      Dig_23_Ch2 => Dig_23_Ch2,
      Dig_24_Ch2 => Dig_24_Ch2,
      Dig_25_Ch2 => Dig_25_Ch2,
      Dig_26_Ch2 => Dig_26_Ch2,
      Dig_27_Ch2 => Dig_27_Ch2,
      Dig_28_Ch2 => Dig_28_Ch2,
      Dig_29_Ch2 => Dig_29_Ch2
    );
end STRUCTURE;
