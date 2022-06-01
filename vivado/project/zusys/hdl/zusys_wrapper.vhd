--Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
--Date        : Wed Jun  1 19:44:49 2022
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
    D1_dig_io_17 : in STD_LOGIC;
    D1_h1_fault : in STD_LOGIC;
    D1_h1_oc : in STD_LOGIC;
    D1_h1_temp : in STD_LOGIC;
    D1_h2_fault : in STD_LOGIC;
    D1_h2_oc : in STD_LOGIC;
    D1_h2_temp : in STD_LOGIC;
    D1_h3_fault : in STD_LOGIC;
    D1_h3_oc : in STD_LOGIC;
    D1_h3_temp : in STD_LOGIC;
    D1_i1_diag : in STD_LOGIC;
    D1_i2_diag : in STD_LOGIC;
    D1_i3_diag : in STD_LOGIC;
    D1_i_diag : in STD_LOGIC;
    D1_l1_fault : in STD_LOGIC;
    D1_l1_oc : in STD_LOGIC;
    D1_l1_temp : in STD_LOGIC;
    D1_l2_fault : in STD_LOGIC;
    D1_l2_oc : in STD_LOGIC;
    D1_l2_temp : in STD_LOGIC;
    D1_l3_fault : in STD_LOGIC;
    D1_l3_oc : in STD_LOGIC;
    D1_l3_temp : in STD_LOGIC;
    D1_pwm_en : out STD_LOGIC;
    D1_pwm_h1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_h2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_h3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_l1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_l2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_l3 : out STD_LOGIC_VECTOR ( 0 to 0 );
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
    A3_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A3_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A3_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
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
    D1_l1_fault : in STD_LOGIC;
    D1_h2_oc : in STD_LOGIC;
    D1_h3_fault : in STD_LOGIC;
    D1_dig_io_17 : in STD_LOGIC;
    D1_i3_diag : in STD_LOGIC;
    D1_h3_temp : in STD_LOGIC;
    D1_l3_fault : in STD_LOGIC;
    D1_i_diag : in STD_LOGIC;
    D1_l3_temp : in STD_LOGIC;
    D1_pwm_h1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_en : out STD_LOGIC;
    D1_pwm_h2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_l3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_pwm_h3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_l1_oc : in STD_LOGIC;
    D1_l3_oc : in STD_LOGIC;
    D1_h1_fault : in STD_LOGIC;
    D1_i1_diag : in STD_LOGIC;
    D1_h2_temp : in STD_LOGIC;
    D1_h1_oc : in STD_LOGIC;
    D1_h3_oc : in STD_LOGIC;
    D1_l1_temp : in STD_LOGIC;
    D1_pwm_l1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_l2_fault : in STD_LOGIC;
    D1_h2_fault : in STD_LOGIC;
    D1_pwm_l2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_i2_diag : in STD_LOGIC;
    D1_h1_temp : in STD_LOGIC;
    D1_l2_oc : in STD_LOGIC;
    D1_l2_temp : in STD_LOGIC
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
      D1_dig_io_17 => D1_dig_io_17,
      D1_h1_fault => D1_h1_fault,
      D1_h1_oc => D1_h1_oc,
      D1_h1_temp => D1_h1_temp,
      D1_h2_fault => D1_h2_fault,
      D1_h2_oc => D1_h2_oc,
      D1_h2_temp => D1_h2_temp,
      D1_h3_fault => D1_h3_fault,
      D1_h3_oc => D1_h3_oc,
      D1_h3_temp => D1_h3_temp,
      D1_i1_diag => D1_i1_diag,
      D1_i2_diag => D1_i2_diag,
      D1_i3_diag => D1_i3_diag,
      D1_i_diag => D1_i_diag,
      D1_l1_fault => D1_l1_fault,
      D1_l1_oc => D1_l1_oc,
      D1_l1_temp => D1_l1_temp,
      D1_l2_fault => D1_l2_fault,
      D1_l2_oc => D1_l2_oc,
      D1_l2_temp => D1_l2_temp,
      D1_l3_fault => D1_l3_fault,
      D1_l3_oc => D1_l3_oc,
      D1_l3_temp => D1_l3_temp,
      D1_pwm_en => D1_pwm_en,
      D1_pwm_h1(0) => D1_pwm_h1(0),
      D1_pwm_h2(0) => D1_pwm_h2(0),
      D1_pwm_h3(0) => D1_pwm_h3(0),
      D1_pwm_l1(0) => D1_pwm_l1(0),
      D1_pwm_l2(0) => D1_pwm_l2(0),
      D1_pwm_l3(0) => D1_pwm_l3(0),
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
