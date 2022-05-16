--Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
--Date        : Mon May 16 15:55:51 2022
--Host        : TS-WS running 64-bit Ubuntu 20.04.4 LTS
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
    ANL_01_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_01_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT : out STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT : out STD_LOGIC_VECTOR ( 11 downto 0 );
    D2_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT : out STD_LOGIC_VECTOR ( 7 downto 0 );
    D4_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch5 : in STD_LOGIC;
    Dig_10_Ch5 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC;
    Dig_20_Ch5 : in STD_LOGIC;
    Dig_21_Ch5 : in STD_LOGIC;
    Dig_22_Ch5 : in STD_LOGIC;
    Dig_23_Ch5 : in STD_LOGIC;
    Dig_8_Ch5 : in STD_LOGIC
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
    D1_OUT : out STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT : out STD_LOGIC_VECTOR ( 11 downto 0 );
    D2_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT : out STD_LOGIC_VECTOR ( 7 downto 0 );
    D4_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch5 : in STD_LOGIC;
    Dig_10_Ch5 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC;
    Dig_20_Ch5 : in STD_LOGIC;
    Dig_21_Ch5 : in STD_LOGIC;
    Dig_22_Ch5 : in STD_LOGIC;
    Dig_23_Ch5 : in STD_LOGIC;
    Dig_8_Ch5 : in STD_LOGIC;
    ANL_01_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_01_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_P_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_N_Ch3 : out STD_LOGIC_VECTOR ( 0 to 0 )
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
      ANL_01_N_Ch3(0) => ANL_01_N_Ch3(0),
      ANL_01_P_Ch3(0) => ANL_01_P_Ch3(0),
      ANL_02_N_Ch3(0) => ANL_02_N_Ch3(0),
      ANL_02_P_Ch3(0) => ANL_02_P_Ch3(0),
      ANL_03_N_Ch3(0) => ANL_03_N_Ch3(0),
      ANL_03_P_Ch3(0) => ANL_03_P_Ch3(0),
      ANL_04_N_Ch3(0) => ANL_04_N_Ch3(0),
      ANL_04_P_Ch3(0) => ANL_04_P_Ch3(0),
      ANL_05_N_Ch3(0) => ANL_05_N_Ch3(0),
      ANL_05_P_Ch3(0) => ANL_05_P_Ch3(0),
      ANL_06_N_Ch3(0) => ANL_06_N_Ch3(0),
      ANL_06_P_Ch3(0) => ANL_06_P_Ch3(0),
      ANL_07_N_Ch3(0) => ANL_07_N_Ch3(0),
      ANL_07_P_Ch3(0) => ANL_07_P_Ch3(0),
      ANL_08_N_Ch3(0) => ANL_08_N_Ch3(0),
      ANL_08_P_Ch3(0) => ANL_08_P_Ch3(0),
      ANL_09_N_Ch3(0) => ANL_09_N_Ch3(0),
      ANL_09_P_Ch3(0) => ANL_09_P_Ch3(0),
      ANL_10_N_Ch3(0) => ANL_10_N_Ch3(0),
      ANL_10_P_Ch3(0) => ANL_10_P_Ch3(0),
      D1_OUT(5 downto 0) => D1_OUT(5 downto 0),
      D1_OUT_26(0) => D1_OUT_26(0),
      D1_OUT_27(0) => D1_OUT_27(0),
      D1_OUT_28(0) => D1_OUT_28(0),
      D1_OUT_29(0) => D1_OUT_29(0),
      D2_OUT(11 downto 0) => D2_OUT(11 downto 0),
      D2_OUT_26(0) => D2_OUT_26(0),
      D2_OUT_27(0) => D2_OUT_27(0),
      D2_OUT_28(0) => D2_OUT_28(0),
      D2_OUT_29(0) => D2_OUT_29(0),
      D3_OUT_26(0) => D3_OUT_26(0),
      D3_OUT_27(0) => D3_OUT_27(0),
      D3_OUT_28(0) => D3_OUT_28(0),
      D3_OUT_29(0) => D3_OUT_29(0),
      D4_OUT(7 downto 0) => D4_OUT(7 downto 0),
      D4_OUT_26(0) => D4_OUT_26(0),
      D4_OUT_27(0) => D4_OUT_27(0),
      D4_OUT_28(0) => D4_OUT_28(0),
      D4_OUT_29(0) => D4_OUT_29(0),
      Dig_09_Ch5 => Dig_09_Ch5,
      Dig_10_Ch5 => Dig_10_Ch5,
      Dig_11_Ch5 => Dig_11_Ch5,
      Dig_12_Ch5 => Dig_12_Ch5,
      Dig_13_Ch5 => Dig_13_Ch5,
      Dig_14_Ch5 => Dig_14_Ch5,
      Dig_15_Ch5 => Dig_15_Ch5,
      Dig_16_Ch5 => Dig_16_Ch5,
      Dig_17_Ch5 => Dig_17_Ch5,
      Dig_18_Ch5 => Dig_18_Ch5,
      Dig_19_Ch5 => Dig_19_Ch5,
      Dig_20_Ch5 => Dig_20_Ch5,
      Dig_21_Ch5 => Dig_21_Ch5,
      Dig_22_Ch5 => Dig_22_Ch5,
      Dig_23_Ch5 => Dig_23_Ch5,
      Dig_8_Ch5 => Dig_8_Ch5
    );
end STRUCTURE;
