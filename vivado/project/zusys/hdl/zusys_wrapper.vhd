--Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2.2 (lin64) Build 3788238 Tue Feb 21 19:59:23 MST 2023
--Date        : Fri Jun 19 11:46:09 2026
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
    D1_OUT : out STD_LOGIC_VECTOR ( 23 downto 0 );
    D1_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT : out STD_LOGIC_VECTOR ( 11 downto 0 );
    D2_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT : out STD_LOGIC_VECTOR ( 25 downto 0 );
    D3_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
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
    Dig_00_Ch4 : out STD_LOGIC;
    Dig_01_Ch4 : out STD_LOGIC;
    Dig_02_Ch4 : in STD_LOGIC;
    Dig_03_Ch4 : out STD_LOGIC;
    Dig_04_Ch4 : in STD_LOGIC;
    Dig_06_Ch4 : out STD_LOGIC;
    Dig_06_Ch5 : in STD_LOGIC;
    Dig_07_Ch4 : out STD_LOGIC;
    Dig_07_Ch5 : in STD_LOGIC;
    Dig_08_Ch4 : in STD_LOGIC;
    Dig_08_Ch5 : out STD_LOGIC;
    Dig_09_Ch4 : out STD_LOGIC;
    Dig_10_Ch4 : in STD_LOGIC;
    Dig_10_Ch5 : out STD_LOGIC;
    Dig_11_Ch5 : out STD_LOGIC;
    Dig_12_Ch4 : out STD_LOGIC;
    Dig_13_Ch4 : out STD_LOGIC;
    Dig_14_Ch4 : in STD_LOGIC;
    Dig_14_Ch5 : out STD_LOGIC;
    Dig_15_Ch4 : out STD_LOGIC;
    Dig_15_Ch5 : out STD_LOGIC;
    Dig_16_Ch4 : in STD_LOGIC;
    Dig_16_Ch5 : out STD_LOGIC;
    Dig_17_Ch5 : out STD_LOGIC;
    Dig_18_Ch4 : out STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_20_Ch5 : out STD_LOGIC;
    Dig_22_Ch5 : out STD_LOGIC;
    Dig_23_Ch5 : out STD_LOGIC
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    D1_OUT : out STD_LOGIC_VECTOR ( 23 downto 0 );
    D1_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT : out STD_LOGIC_VECTOR ( 11 downto 0 );
    D2_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT : out STD_LOGIC_VECTOR ( 25 downto 0 );
    D3_OUT_26 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
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
    Dig_18_Ch4 : out STD_LOGIC;
    Dig_15_Ch5 : out STD_LOGIC;
    Dig_08_Ch5 : out STD_LOGIC;
    Dig_17_Ch5 : out STD_LOGIC;
    Dig_11_Ch5 : out STD_LOGIC;
    Dig_07_Ch5 : in STD_LOGIC;
    Dig_14_Ch5 : out STD_LOGIC;
    Dig_16_Ch5 : out STD_LOGIC;
    Dig_10_Ch5 : out STD_LOGIC;
    Dig_06_Ch5 : in STD_LOGIC;
    Dig_22_Ch5 : out STD_LOGIC;
    Dig_23_Ch5 : out STD_LOGIC;
    Dig_20_Ch5 : out STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC
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
      D1_OUT(23 downto 0) => D1_OUT(23 downto 0),
      D1_OUT_26(0) => D1_OUT_26(0),
      D1_OUT_27(0) => D1_OUT_27(0),
      D1_OUT_28(0) => D1_OUT_28(0),
      D1_OUT_29(0) => D1_OUT_29(0),
      D2_OUT(11 downto 0) => D2_OUT(11 downto 0),
      D2_OUT_26(0) => D2_OUT_26(0),
      D2_OUT_27(0) => D2_OUT_27(0),
      D2_OUT_28(0) => D2_OUT_28(0),
      D2_OUT_29(0) => D2_OUT_29(0),
      D3_OUT(25 downto 0) => D3_OUT(25 downto 0),
      D3_OUT_26(0) => D3_OUT_26(0),
      D3_OUT_27(0) => D3_OUT_27(0),
      D3_OUT_28(0) => D3_OUT_28(0),
      D3_OUT_29(0) => D3_OUT_29(0),
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
      Dig_00_Ch4 => Dig_00_Ch4,
      Dig_01_Ch4 => Dig_01_Ch4,
      Dig_02_Ch4 => Dig_02_Ch4,
      Dig_03_Ch4 => Dig_03_Ch4,
      Dig_04_Ch4 => Dig_04_Ch4,
      Dig_06_Ch4 => Dig_06_Ch4,
      Dig_06_Ch5 => Dig_06_Ch5,
      Dig_07_Ch4 => Dig_07_Ch4,
      Dig_07_Ch5 => Dig_07_Ch5,
      Dig_08_Ch4 => Dig_08_Ch4,
      Dig_08_Ch5 => Dig_08_Ch5,
      Dig_09_Ch4 => Dig_09_Ch4,
      Dig_10_Ch4 => Dig_10_Ch4,
      Dig_10_Ch5 => Dig_10_Ch5,
      Dig_11_Ch5 => Dig_11_Ch5,
      Dig_12_Ch4 => Dig_12_Ch4,
      Dig_13_Ch4 => Dig_13_Ch4,
      Dig_14_Ch4 => Dig_14_Ch4,
      Dig_14_Ch5 => Dig_14_Ch5,
      Dig_15_Ch4 => Dig_15_Ch4,
      Dig_15_Ch5 => Dig_15_Ch5,
      Dig_16_Ch4 => Dig_16_Ch4,
      Dig_16_Ch5 => Dig_16_Ch5,
      Dig_17_Ch5 => Dig_17_Ch5,
      Dig_18_Ch4 => Dig_18_Ch4,
      Dig_18_Ch5 => Dig_18_Ch5,
      Dig_20_Ch5 => Dig_20_Ch5,
      Dig_22_Ch5 => Dig_22_Ch5,
      Dig_23_Ch5 => Dig_23_Ch5
    );
end STRUCTURE;
