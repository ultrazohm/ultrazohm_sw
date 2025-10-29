--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
--Date        : Fri Oct 24 19:06:17 2025
--Host        : NB-GEIGER running 64-bit major release  (build 9200)
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
    D1_06_OUT_RESET_UVW : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_22_OUT_KL15 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_23_IN_KL15_PG : in STD_LOGIC;
    D1_24_OUT_PYRO_TRIGGER : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_25_IN_IGNITION_SUCCESS : in STD_LOGIC;
    D1_26_OUT_RELAY2_CLOSE : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_27_IN_RELAY2_NOT_CLOSED : in STD_LOGIC;
    D1_28_OUT_RELAY3_CLOSE : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_29_IN_RELAY3_NOT_CLOSED : in STD_LOGIC;
    D1_IN_FLT : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_IN_NTC : in STD_LOGIC_VECTOR ( 2 downto 0 );
    D1_IN_RDY : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_OUT_PWM : out STD_LOGIC_VECTOR ( 5 downto 0 );
    D2_06_OUT_RESET_UVW : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_22_OUT_PYRO_RESET : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_23_OUT_PYRO_ENABLE : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_24_IN_IGNITION_SUCCESS2 : in STD_LOGIC;
    D2_25_IN_IGNITION_SUCCESS3 : in STD_LOGIC;
    D2_26_OUT_CS_SQUIB1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_27_OUT_CS_SQUIB2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_28_OUT_CS_SQUIB3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_IN_FLT : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D2_IN_NTC : in STD_LOGIC_VECTOR ( 2 downto 0 );
    D2_IN_RDY : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D2_OUT_PWM : out STD_LOGIC_VECTOR ( 5 downto 0 );
    D3_OUT_PWM : out STD_LOGIC_VECTOR ( 5 downto 0 );
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
    D1_OUT_PWM : out STD_LOGIC_VECTOR ( 5 downto 0 );
    D2_OUT_PWM : out STD_LOGIC_VECTOR ( 5 downto 0 );
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
    D1_06_OUT_RESET_UVW : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_IN_FLT : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_IN_RDY : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_IN_NTC : in STD_LOGIC_VECTOR ( 2 downto 0 );
    D1_22_OUT_KL15 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_23_IN_KL15_PG : in STD_LOGIC;
    D1_24_OUT_PYRO_TRIGGER : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_25_IN_IGNITION_SUCCESS : in STD_LOGIC;
    D1_26_OUT_RELAY2_CLOSE : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_27_IN_RELAY2_NOT_CLOSED : in STD_LOGIC;
    D1_28_OUT_RELAY3_CLOSE : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_29_IN_RELAY3_NOT_CLOSED : in STD_LOGIC;
    D2_06_OUT_RESET_UVW : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_IN_FLT : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D2_IN_RDY : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D2_IN_NTC : in STD_LOGIC_VECTOR ( 2 downto 0 );
    D2_22_OUT_PYRO_RESET : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_23_OUT_PYRO_ENABLE : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_24_IN_IGNITION_SUCCESS2 : in STD_LOGIC;
    D2_25_IN_IGNITION_SUCCESS3 : in STD_LOGIC;
    D2_26_OUT_CS_SQUIB1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_27_OUT_CS_SQUIB2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_28_OUT_CS_SQUIB3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_PWM : out STD_LOGIC_VECTOR ( 5 downto 0 )
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
      D1_06_OUT_RESET_UVW(0) => D1_06_OUT_RESET_UVW(0),
      D1_22_OUT_KL15(0) => D1_22_OUT_KL15(0),
      D1_23_IN_KL15_PG => D1_23_IN_KL15_PG,
      D1_24_OUT_PYRO_TRIGGER(0) => D1_24_OUT_PYRO_TRIGGER(0),
      D1_25_IN_IGNITION_SUCCESS => D1_25_IN_IGNITION_SUCCESS,
      D1_26_OUT_RELAY2_CLOSE(0) => D1_26_OUT_RELAY2_CLOSE(0),
      D1_27_IN_RELAY2_NOT_CLOSED => D1_27_IN_RELAY2_NOT_CLOSED,
      D1_28_OUT_RELAY3_CLOSE(0) => D1_28_OUT_RELAY3_CLOSE(0),
      D1_29_IN_RELAY3_NOT_CLOSED => D1_29_IN_RELAY3_NOT_CLOSED,
      D1_IN_FLT(5 downto 0) => D1_IN_FLT(5 downto 0),
      D1_IN_NTC(2 downto 0) => D1_IN_NTC(2 downto 0),
      D1_IN_RDY(5 downto 0) => D1_IN_RDY(5 downto 0),
      D1_OUT_PWM(5 downto 0) => D1_OUT_PWM(5 downto 0),
      D2_06_OUT_RESET_UVW(0) => D2_06_OUT_RESET_UVW(0),
      D2_22_OUT_PYRO_RESET(0) => D2_22_OUT_PYRO_RESET(0),
      D2_23_OUT_PYRO_ENABLE(0) => D2_23_OUT_PYRO_ENABLE(0),
      D2_24_IN_IGNITION_SUCCESS2 => D2_24_IN_IGNITION_SUCCESS2,
      D2_25_IN_IGNITION_SUCCESS3 => D2_25_IN_IGNITION_SUCCESS3,
      D2_26_OUT_CS_SQUIB1(0) => D2_26_OUT_CS_SQUIB1(0),
      D2_27_OUT_CS_SQUIB2(0) => D2_27_OUT_CS_SQUIB2(0),
      D2_28_OUT_CS_SQUIB3(0) => D2_28_OUT_CS_SQUIB3(0),
      D2_IN_FLT(5 downto 0) => D2_IN_FLT(5 downto 0),
      D2_IN_NTC(2 downto 0) => D2_IN_NTC(2 downto 0),
      D2_IN_RDY(5 downto 0) => D2_IN_RDY(5 downto 0),
      D2_OUT_PWM(5 downto 0) => D2_OUT_PWM(5 downto 0),
      D3_OUT_PWM(5 downto 0) => D3_OUT_PWM(5 downto 0),
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
