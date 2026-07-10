--Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2.2 (lin64) Build 3788238 Tue Feb 21 19:59:23 MST 2023
--Date        : Mon Jul  6 11:52:28 2026
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
    A3_CS : out STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_EOC : in STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_MISO : in STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_MOSI : out STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_SCKL : out STD_LOGIC_VECTOR ( 2 downto 0 );
    DAC_CLK_N_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_CLK_P_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_CVN_N_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_CVN_P_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N1_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N2_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N3_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N4_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N5_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N6_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N7_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N8_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P1_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P2_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P3_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P4_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P5_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P6_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P7_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P8_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
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
    Dig_17_Ch1 : in STD_LOGIC
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    A1_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A1_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    DAC_CLK_P_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_CLK_N_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_CVN_P_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_CVN_N_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P1_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N1_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P2_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N2_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P3_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N3_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P4_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N4_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P5_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N5_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P6_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N6_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P7_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N7_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_P8_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_IN_N8_A2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_SCKL : out STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_CS : out STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_MOSI : out STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_MISO : in STD_LOGIC_VECTOR ( 2 downto 0 );
    A3_EOC : in STD_LOGIC_VECTOR ( 2 downto 0 );
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
    Dig_17_Ch1 : in STD_LOGIC
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      A1_IN(15 downto 0) => A1_IN(15 downto 0),
      A1_OUT_CLK(1 downto 0) => A1_OUT_CLK(1 downto 0),
      A1_OUT_CNV_0(0) => A1_OUT_CNV_0(0),
      A1_OUT_CNV_1(0) => A1_OUT_CNV_1(0),
      A3_CS(2 downto 0) => A3_CS(2 downto 0),
      A3_EOC(2 downto 0) => A3_EOC(2 downto 0),
      A3_MISO(2 downto 0) => A3_MISO(2 downto 0),
      A3_MOSI(2 downto 0) => A3_MOSI(2 downto 0),
      A3_SCKL(2 downto 0) => A3_SCKL(2 downto 0),
      DAC_CLK_N_A2(0) => DAC_CLK_N_A2(0),
      DAC_CLK_P_A2(0) => DAC_CLK_P_A2(0),
      DAC_CVN_N_A2(0) => DAC_CVN_N_A2(0),
      DAC_CVN_P_A2(0) => DAC_CVN_P_A2(0),
      DAC_IN_N1_A2(0) => DAC_IN_N1_A2(0),
      DAC_IN_N2_A2(0) => DAC_IN_N2_A2(0),
      DAC_IN_N3_A2(0) => DAC_IN_N3_A2(0),
      DAC_IN_N4_A2(0) => DAC_IN_N4_A2(0),
      DAC_IN_N5_A2(0) => DAC_IN_N5_A2(0),
      DAC_IN_N6_A2(0) => DAC_IN_N6_A2(0),
      DAC_IN_N7_A2(0) => DAC_IN_N7_A2(0),
      DAC_IN_N8_A2(0) => DAC_IN_N8_A2(0),
      DAC_IN_P1_A2(0) => DAC_IN_P1_A2(0),
      DAC_IN_P2_A2(0) => DAC_IN_P2_A2(0),
      DAC_IN_P3_A2(0) => DAC_IN_P3_A2(0),
      DAC_IN_P4_A2(0) => DAC_IN_P4_A2(0),
      DAC_IN_P5_A2(0) => DAC_IN_P5_A2(0),
      DAC_IN_P6_A2(0) => DAC_IN_P6_A2(0),
      DAC_IN_P7_A2(0) => DAC_IN_P7_A2(0),
      DAC_IN_P8_A2(0) => DAC_IN_P8_A2(0),
      Dig_00_Ch1(0) => Dig_00_Ch1(0),
      Dig_01_Ch1(0) => Dig_01_Ch1(0),
      Dig_02_Ch1(0) => Dig_02_Ch1(0),
      Dig_03_Ch1(0) => Dig_03_Ch1(0),
      Dig_04_Ch1(0) => Dig_04_Ch1(0),
      Dig_05_Ch1(0) => Dig_05_Ch1(0),
      Dig_06_Ch1(0) => Dig_06_Ch1(0),
      Dig_07_Ch1(0) => Dig_07_Ch1(0),
      Dig_08_Ch1(0) => Dig_08_Ch1(0),
      Dig_09_Ch1(0) => Dig_09_Ch1(0),
      Dig_10_Ch1(0) => Dig_10_Ch1(0),
      Dig_11_Ch1(0) => Dig_11_Ch1(0),
      Dig_12_Ch1(0) => Dig_12_Ch1(0),
      Dig_13_Ch1(0) => Dig_13_Ch1(0),
      Dig_14_Ch1 => Dig_14_Ch1,
      Dig_15_Ch1 => Dig_15_Ch1,
      Dig_16_Ch1 => Dig_16_Ch1,
      Dig_17_Ch1 => Dig_17_Ch1
    );
end STRUCTURE;
