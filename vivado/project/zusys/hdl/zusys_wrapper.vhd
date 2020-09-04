--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
--Date        : Fri Apr  3 16:00:15 2020
--Host        : TUEIEAL-TM01 running 64-bit major release  (build 9200)
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
    ADC_ConvStart : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_01_N_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_01_P_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_N_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_P_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_01_Ch1 : out STD_LOGIC;
    Dig_02_Ch1 : out STD_LOGIC;
    Dig_03_Ch1 : out STD_LOGIC;
    Dig_04_Ch1 : out STD_LOGIC;
    Dig_05_Ch1 : out STD_LOGIC;
    Dig_06_Ch1 : out STD_LOGIC;
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
    Dig_20_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_20_Ch5 : in STD_LOGIC;
    Dig_21_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_21_Ch5 : in STD_LOGIC;
    Dig_22_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_22_Ch5 : in STD_LOGIC;
    Dig_23_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_23_Ch5 : in STD_LOGIC;
    Dig_24_Ch1 : out STD_LOGIC;
    Dig_24_Ch5 : in STD_LOGIC;
    Dig_25_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_26_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_27_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_28_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_29_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_30_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Reserve : out STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_CS : out STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_MOSI : out STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_SCK : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    SPI_SCK : out STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_MOSI : out STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_CS : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch5 : in STD_LOGIC;
    Dig_10_Ch5 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_20_Ch5 : in STD_LOGIC;
    Dig_21_Ch5 : in STD_LOGIC;
    Dig_22_Ch5 : in STD_LOGIC;
    Dig_23_Ch5 : in STD_LOGIC;
    Dig_24_Ch5 : in STD_LOGIC;
    ANL_09_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_09_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_07_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_03_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_05_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC;
    Dig_29_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_25_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_28_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_27_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_30_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_24_Ch1 : out STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_01_Ch1 : out STD_LOGIC;
    Dig_02_Ch1 : out STD_LOGIC;
    Dig_03_Ch1 : out STD_LOGIC;
    Dig_04_Ch1 : out STD_LOGIC;
    Dig_05_Ch1 : out STD_LOGIC;
    Dig_06_Ch1 : out STD_LOGIC;
    Dig_26_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ADC_ConvStart : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_01_P_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_01_N_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_P_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_02_N_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_N_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_04_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_06_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_08_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    ANL_10_P_Ch1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_23_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_22_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_21_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_20_Ch1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Reserve : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      ADC_ConvStart(0) => ADC_ConvStart(0),
      ANL_01_N_Ch1(0) => ANL_01_N_Ch1(0),
      ANL_01_P_Ch1(0) => ANL_01_P_Ch1(0),
      ANL_02_N_Ch1(0) => ANL_02_N_Ch1(0),
      ANL_02_P_Ch1(0) => ANL_02_P_Ch1(0),
      ANL_03_N_Ch1(0) => ANL_03_N_Ch1(0),
      ANL_03_P_Ch1(0) => ANL_03_P_Ch1(0),
      ANL_04_N_Ch1(0) => ANL_04_N_Ch1(0),
      ANL_04_P_Ch1(0) => ANL_04_P_Ch1(0),
      ANL_05_N_Ch1(0) => ANL_05_N_Ch1(0),
      ANL_05_P_Ch1(0) => ANL_05_P_Ch1(0),
      ANL_06_N_Ch1(0) => ANL_06_N_Ch1(0),
      ANL_06_P_Ch1(0) => ANL_06_P_Ch1(0),
      ANL_07_N_Ch1(0) => ANL_07_N_Ch1(0),
      ANL_07_P_Ch1(0) => ANL_07_P_Ch1(0),
      ANL_08_N_Ch1(0) => ANL_08_N_Ch1(0),
      ANL_08_P_Ch1(0) => ANL_08_P_Ch1(0),
      ANL_09_N_Ch1(0) => ANL_09_N_Ch1(0),
      ANL_09_P_Ch1(0) => ANL_09_P_Ch1(0),
      ANL_10_N_Ch1(0) => ANL_10_N_Ch1(0),
      ANL_10_P_Ch1(0) => ANL_10_P_Ch1(0),
      Dig_01_Ch1 => Dig_01_Ch1,
      Dig_02_Ch1 => Dig_02_Ch1,
      Dig_03_Ch1 => Dig_03_Ch1,
      Dig_04_Ch1 => Dig_04_Ch1,
      Dig_05_Ch1 => Dig_05_Ch1,
      Dig_06_Ch1 => Dig_06_Ch1,
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
      Dig_20_Ch1(0) => Dig_20_Ch1(0),
      Dig_20_Ch5 => Dig_20_Ch5,
      Dig_21_Ch1(0) => Dig_21_Ch1(0),
      Dig_21_Ch5 => Dig_21_Ch5,
      Dig_22_Ch1(0) => Dig_22_Ch1(0),
      Dig_22_Ch5 => Dig_22_Ch5,
      Dig_23_Ch1(0) => Dig_23_Ch1(0),
      Dig_23_Ch5 => Dig_23_Ch5,
      Dig_24_Ch1 => Dig_24_Ch1,
      Dig_24_Ch5 => Dig_24_Ch5,
      Dig_25_Ch1(0) => Dig_25_Ch1(0),
      Dig_26_Ch1(0) => Dig_26_Ch1(0),
      Dig_27_Ch1(0) => Dig_27_Ch1(0),
      Dig_28_Ch1(0) => Dig_28_Ch1(0),
      Dig_29_Ch1(0) => Dig_29_Ch1(0),
      Dig_30_Ch1(0) => Dig_30_Ch1(0),
      Reserve(0) => Reserve(0),
      SPI_CS(0) => SPI_CS(0),
      SPI_MOSI(0) => SPI_MOSI(0),
      SPI_SCK(0) => SPI_SCK(0)
    );
end STRUCTURE;
