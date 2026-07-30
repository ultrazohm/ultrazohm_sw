--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
--Date        : Wed Jul 29 15:21:17 2026
--Host        : Jonathan-Link running 64-bit major release  (build 9200)
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
    D2_IN : in STD_LOGIC_VECTOR ( 17 downto 0 );
    Dig_00_Ch1 : out STD_LOGIC;
    Dig_00_Ch4 : out STD_LOGIC;
    Dig_01_Ch1 : out STD_LOGIC;
    Dig_01_Ch4 : out STD_LOGIC;
    Dig_02_Ch1 : out STD_LOGIC;
    Dig_02_Ch4 : out STD_LOGIC;
    Dig_03_Ch1 : out STD_LOGIC;
    Dig_03_Ch4 : out STD_LOGIC;
    Dig_04_Ch1 : out STD_LOGIC;
    Dig_04_Ch4 : out STD_LOGIC;
    Dig_05_Ch1 : out STD_LOGIC;
    Dig_05_Ch4 : out STD_LOGIC;
    Dig_06_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch4 : out STD_LOGIC;
    Dig_07_Ch4 : out STD_LOGIC;
    Dig_08_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_08_Ch4 : in STD_LOGIC;
    Dig_09_Ch4 : out STD_LOGIC;
    Dig_10_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_10_Ch4 : out STD_LOGIC;
    Dig_11_Ch4 : out STD_LOGIC;
    Dig_12_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_12_Ch4 : out STD_LOGIC;
    Dig_13_Ch4 : out STD_LOGIC;
    Dig_14_Ch4 : out STD_LOGIC;
    Dig_15_Ch4 : out STD_LOGIC;
    Dig_16_Ch4 : out STD_LOGIC;
    Dig_17_Ch4 : in STD_LOGIC
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
    Dig_01_Ch4 : out STD_LOGIC;
    Dig_00_Ch4 : out STD_LOGIC;
    Dig_03_Ch4 : out STD_LOGIC;
    Dig_07_Ch4 : out STD_LOGIC;
    Dig_02_Ch4 : out STD_LOGIC;
    Dig_04_Ch4 : out STD_LOGIC;
    Dig_06_Ch4 : out STD_LOGIC;
    Dig_05_Ch4 : out STD_LOGIC;
    Dig_15_Ch4 : out STD_LOGIC;
    Dig_14_Ch4 : out STD_LOGIC;
    Dig_16_Ch4 : out STD_LOGIC;
    Dig_11_Ch4 : out STD_LOGIC;
    Dig_13_Ch4 : out STD_LOGIC;
    Dig_09_Ch4 : out STD_LOGIC;
    Dig_12_Ch4 : out STD_LOGIC;
    Dig_10_Ch4 : out STD_LOGIC;
    Dig_08_Ch4 : in STD_LOGIC;
    Dig_17_Ch4 : in STD_LOGIC;
    D2_IN : in STD_LOGIC_VECTOR ( 17 downto 0 );
    Dig_12_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_00_Ch1 : out STD_LOGIC;
    Dig_01_Ch1 : out STD_LOGIC;
    Dig_02_Ch1 : out STD_LOGIC;
    Dig_03_Ch1 : out STD_LOGIC;
    Dig_04_Ch1 : out STD_LOGIC;
    Dig_05_Ch1 : out STD_LOGIC;
    Dig_10_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_08_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_06_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 )
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
      D2_IN(17 downto 0) => D2_IN(17 downto 0),
      Dig_00_Ch1 => Dig_00_Ch1,
      Dig_00_Ch4 => Dig_00_Ch4,
      Dig_01_Ch1 => Dig_01_Ch1,
      Dig_01_Ch4 => Dig_01_Ch4,
      Dig_02_Ch1 => Dig_02_Ch1,
      Dig_02_Ch4 => Dig_02_Ch4,
      Dig_03_Ch1 => Dig_03_Ch1,
      Dig_03_Ch4 => Dig_03_Ch4,
      Dig_04_Ch1 => Dig_04_Ch1,
      Dig_04_Ch4 => Dig_04_Ch4,
      Dig_05_Ch1 => Dig_05_Ch1,
      Dig_05_Ch4 => Dig_05_Ch4,
      Dig_06_Ch1(0) => Dig_06_Ch1(0),
      Dig_06_Ch4 => Dig_06_Ch4,
      Dig_07_Ch4 => Dig_07_Ch4,
      Dig_08_Ch1(0) => Dig_08_Ch1(0),
      Dig_08_Ch4 => Dig_08_Ch4,
      Dig_09_Ch4 => Dig_09_Ch4,
      Dig_10_Ch1(0) => Dig_10_Ch1(0),
      Dig_10_Ch4 => Dig_10_Ch4,
      Dig_11_Ch4 => Dig_11_Ch4,
      Dig_12_Ch1(0) => Dig_12_Ch1(0),
      Dig_12_Ch4 => Dig_12_Ch4,
      Dig_13_Ch4 => Dig_13_Ch4,
      Dig_14_Ch4 => Dig_14_Ch4,
      Dig_15_Ch4 => Dig_15_Ch4,
      Dig_16_Ch4 => Dig_16_Ch4,
      Dig_17_Ch4 => Dig_17_Ch4
    );
end STRUCTURE;
