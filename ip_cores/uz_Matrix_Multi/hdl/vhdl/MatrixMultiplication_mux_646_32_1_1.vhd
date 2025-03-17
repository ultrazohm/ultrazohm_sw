-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Tool Version Limit: 2019.12
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;

entity MatrixMultiplication_mux_646_32_1_1 is
generic (
    ID            :integer := 0;
    NUM_STAGE     :integer := 1;
    din0_WIDTH       :integer := 32;
    din1_WIDTH       :integer := 32;
    din2_WIDTH       :integer := 32;
    din3_WIDTH       :integer := 32;
    din4_WIDTH       :integer := 32;
    din5_WIDTH       :integer := 32;
    din6_WIDTH       :integer := 32;
    din7_WIDTH       :integer := 32;
    din8_WIDTH       :integer := 32;
    din9_WIDTH       :integer := 32;
    din10_WIDTH       :integer := 32;
    din11_WIDTH       :integer := 32;
    din12_WIDTH       :integer := 32;
    din13_WIDTH       :integer := 32;
    din14_WIDTH       :integer := 32;
    din15_WIDTH       :integer := 32;
    din16_WIDTH       :integer := 32;
    din17_WIDTH       :integer := 32;
    din18_WIDTH       :integer := 32;
    din19_WIDTH       :integer := 32;
    din20_WIDTH       :integer := 32;
    din21_WIDTH       :integer := 32;
    din22_WIDTH       :integer := 32;
    din23_WIDTH       :integer := 32;
    din24_WIDTH       :integer := 32;
    din25_WIDTH       :integer := 32;
    din26_WIDTH       :integer := 32;
    din27_WIDTH       :integer := 32;
    din28_WIDTH       :integer := 32;
    din29_WIDTH       :integer := 32;
    din30_WIDTH       :integer := 32;
    din31_WIDTH       :integer := 32;
    din32_WIDTH       :integer := 32;
    din33_WIDTH       :integer := 32;
    din34_WIDTH       :integer := 32;
    din35_WIDTH       :integer := 32;
    din36_WIDTH       :integer := 32;
    din37_WIDTH       :integer := 32;
    din38_WIDTH       :integer := 32;
    din39_WIDTH       :integer := 32;
    din40_WIDTH       :integer := 32;
    din41_WIDTH       :integer := 32;
    din42_WIDTH       :integer := 32;
    din43_WIDTH       :integer := 32;
    din44_WIDTH       :integer := 32;
    din45_WIDTH       :integer := 32;
    din46_WIDTH       :integer := 32;
    din47_WIDTH       :integer := 32;
    din48_WIDTH       :integer := 32;
    din49_WIDTH       :integer := 32;
    din50_WIDTH       :integer := 32;
    din51_WIDTH       :integer := 32;
    din52_WIDTH       :integer := 32;
    din53_WIDTH       :integer := 32;
    din54_WIDTH       :integer := 32;
    din55_WIDTH       :integer := 32;
    din56_WIDTH       :integer := 32;
    din57_WIDTH       :integer := 32;
    din58_WIDTH       :integer := 32;
    din59_WIDTH       :integer := 32;
    din60_WIDTH       :integer := 32;
    din61_WIDTH       :integer := 32;
    din62_WIDTH       :integer := 32;
    din63_WIDTH       :integer := 32;
    din64_WIDTH       :integer := 32;
    dout_WIDTH        :integer := 32);
port (
    din0   :in  std_logic_vector(31 downto 0);
    din1   :in  std_logic_vector(31 downto 0);
    din2   :in  std_logic_vector(31 downto 0);
    din3   :in  std_logic_vector(31 downto 0);
    din4   :in  std_logic_vector(31 downto 0);
    din5   :in  std_logic_vector(31 downto 0);
    din6   :in  std_logic_vector(31 downto 0);
    din7   :in  std_logic_vector(31 downto 0);
    din8   :in  std_logic_vector(31 downto 0);
    din9   :in  std_logic_vector(31 downto 0);
    din10   :in  std_logic_vector(31 downto 0);
    din11   :in  std_logic_vector(31 downto 0);
    din12   :in  std_logic_vector(31 downto 0);
    din13   :in  std_logic_vector(31 downto 0);
    din14   :in  std_logic_vector(31 downto 0);
    din15   :in  std_logic_vector(31 downto 0);
    din16   :in  std_logic_vector(31 downto 0);
    din17   :in  std_logic_vector(31 downto 0);
    din18   :in  std_logic_vector(31 downto 0);
    din19   :in  std_logic_vector(31 downto 0);
    din20   :in  std_logic_vector(31 downto 0);
    din21   :in  std_logic_vector(31 downto 0);
    din22   :in  std_logic_vector(31 downto 0);
    din23   :in  std_logic_vector(31 downto 0);
    din24   :in  std_logic_vector(31 downto 0);
    din25   :in  std_logic_vector(31 downto 0);
    din26   :in  std_logic_vector(31 downto 0);
    din27   :in  std_logic_vector(31 downto 0);
    din28   :in  std_logic_vector(31 downto 0);
    din29   :in  std_logic_vector(31 downto 0);
    din30   :in  std_logic_vector(31 downto 0);
    din31   :in  std_logic_vector(31 downto 0);
    din32   :in  std_logic_vector(31 downto 0);
    din33   :in  std_logic_vector(31 downto 0);
    din34   :in  std_logic_vector(31 downto 0);
    din35   :in  std_logic_vector(31 downto 0);
    din36   :in  std_logic_vector(31 downto 0);
    din37   :in  std_logic_vector(31 downto 0);
    din38   :in  std_logic_vector(31 downto 0);
    din39   :in  std_logic_vector(31 downto 0);
    din40   :in  std_logic_vector(31 downto 0);
    din41   :in  std_logic_vector(31 downto 0);
    din42   :in  std_logic_vector(31 downto 0);
    din43   :in  std_logic_vector(31 downto 0);
    din44   :in  std_logic_vector(31 downto 0);
    din45   :in  std_logic_vector(31 downto 0);
    din46   :in  std_logic_vector(31 downto 0);
    din47   :in  std_logic_vector(31 downto 0);
    din48   :in  std_logic_vector(31 downto 0);
    din49   :in  std_logic_vector(31 downto 0);
    din50   :in  std_logic_vector(31 downto 0);
    din51   :in  std_logic_vector(31 downto 0);
    din52   :in  std_logic_vector(31 downto 0);
    din53   :in  std_logic_vector(31 downto 0);
    din54   :in  std_logic_vector(31 downto 0);
    din55   :in  std_logic_vector(31 downto 0);
    din56   :in  std_logic_vector(31 downto 0);
    din57   :in  std_logic_vector(31 downto 0);
    din58   :in  std_logic_vector(31 downto 0);
    din59   :in  std_logic_vector(31 downto 0);
    din60   :in  std_logic_vector(31 downto 0);
    din61   :in  std_logic_vector(31 downto 0);
    din62   :in  std_logic_vector(31 downto 0);
    din63   :in  std_logic_vector(31 downto 0);
    din64   :in  std_logic_vector(5 downto 0);
    dout     :out std_logic_vector(31 downto 0));
end entity;

architecture rtl of MatrixMultiplication_mux_646_32_1_1 is
    -- puts internal signals
    signal sel    : std_logic_vector(5 downto 0);
    -- level 1 signals
    signal mux_1_0    : std_logic_vector(31 downto 0);
    signal mux_1_1    : std_logic_vector(31 downto 0);
    signal mux_1_2    : std_logic_vector(31 downto 0);
    signal mux_1_3    : std_logic_vector(31 downto 0);
    signal mux_1_4    : std_logic_vector(31 downto 0);
    signal mux_1_5    : std_logic_vector(31 downto 0);
    signal mux_1_6    : std_logic_vector(31 downto 0);
    signal mux_1_7    : std_logic_vector(31 downto 0);
    signal mux_1_8    : std_logic_vector(31 downto 0);
    signal mux_1_9    : std_logic_vector(31 downto 0);
    signal mux_1_10    : std_logic_vector(31 downto 0);
    signal mux_1_11    : std_logic_vector(31 downto 0);
    signal mux_1_12    : std_logic_vector(31 downto 0);
    signal mux_1_13    : std_logic_vector(31 downto 0);
    signal mux_1_14    : std_logic_vector(31 downto 0);
    signal mux_1_15    : std_logic_vector(31 downto 0);
    signal mux_1_16    : std_logic_vector(31 downto 0);
    signal mux_1_17    : std_logic_vector(31 downto 0);
    signal mux_1_18    : std_logic_vector(31 downto 0);
    signal mux_1_19    : std_logic_vector(31 downto 0);
    signal mux_1_20    : std_logic_vector(31 downto 0);
    signal mux_1_21    : std_logic_vector(31 downto 0);
    signal mux_1_22    : std_logic_vector(31 downto 0);
    signal mux_1_23    : std_logic_vector(31 downto 0);
    signal mux_1_24    : std_logic_vector(31 downto 0);
    signal mux_1_25    : std_logic_vector(31 downto 0);
    signal mux_1_26    : std_logic_vector(31 downto 0);
    signal mux_1_27    : std_logic_vector(31 downto 0);
    signal mux_1_28    : std_logic_vector(31 downto 0);
    signal mux_1_29    : std_logic_vector(31 downto 0);
    signal mux_1_30    : std_logic_vector(31 downto 0);
    signal mux_1_31    : std_logic_vector(31 downto 0);
    -- level 2 signals
    signal mux_2_0    : std_logic_vector(31 downto 0);
    signal mux_2_1    : std_logic_vector(31 downto 0);
    signal mux_2_2    : std_logic_vector(31 downto 0);
    signal mux_2_3    : std_logic_vector(31 downto 0);
    signal mux_2_4    : std_logic_vector(31 downto 0);
    signal mux_2_5    : std_logic_vector(31 downto 0);
    signal mux_2_6    : std_logic_vector(31 downto 0);
    signal mux_2_7    : std_logic_vector(31 downto 0);
    signal mux_2_8    : std_logic_vector(31 downto 0);
    signal mux_2_9    : std_logic_vector(31 downto 0);
    signal mux_2_10    : std_logic_vector(31 downto 0);
    signal mux_2_11    : std_logic_vector(31 downto 0);
    signal mux_2_12    : std_logic_vector(31 downto 0);
    signal mux_2_13    : std_logic_vector(31 downto 0);
    signal mux_2_14    : std_logic_vector(31 downto 0);
    signal mux_2_15    : std_logic_vector(31 downto 0);
    -- level 3 signals
    signal mux_3_0    : std_logic_vector(31 downto 0);
    signal mux_3_1    : std_logic_vector(31 downto 0);
    signal mux_3_2    : std_logic_vector(31 downto 0);
    signal mux_3_3    : std_logic_vector(31 downto 0);
    signal mux_3_4    : std_logic_vector(31 downto 0);
    signal mux_3_5    : std_logic_vector(31 downto 0);
    signal mux_3_6    : std_logic_vector(31 downto 0);
    signal mux_3_7    : std_logic_vector(31 downto 0);
    -- level 4 signals
    signal mux_4_0    : std_logic_vector(31 downto 0);
    signal mux_4_1    : std_logic_vector(31 downto 0);
    signal mux_4_2    : std_logic_vector(31 downto 0);
    signal mux_4_3    : std_logic_vector(31 downto 0);
    -- level 5 signals
    signal mux_5_0    : std_logic_vector(31 downto 0);
    signal mux_5_1    : std_logic_vector(31 downto 0);
    -- level 6 signals
    signal mux_6_0    : std_logic_vector(31 downto 0);
begin

sel <= din64;

-- Generate level 1 logic
mux_1_0 <= din0 when sel(0) = '0' else din1;
mux_1_1 <= din2 when sel(0) = '0' else din3;
mux_1_2 <= din4 when sel(0) = '0' else din5;
mux_1_3 <= din6 when sel(0) = '0' else din7;
mux_1_4 <= din8 when sel(0) = '0' else din9;
mux_1_5 <= din10 when sel(0) = '0' else din11;
mux_1_6 <= din12 when sel(0) = '0' else din13;
mux_1_7 <= din14 when sel(0) = '0' else din15;
mux_1_8 <= din16 when sel(0) = '0' else din17;
mux_1_9 <= din18 when sel(0) = '0' else din19;
mux_1_10 <= din20 when sel(0) = '0' else din21;
mux_1_11 <= din22 when sel(0) = '0' else din23;
mux_1_12 <= din24 when sel(0) = '0' else din25;
mux_1_13 <= din26 when sel(0) = '0' else din27;
mux_1_14 <= din28 when sel(0) = '0' else din29;
mux_1_15 <= din30 when sel(0) = '0' else din31;
mux_1_16 <= din32 when sel(0) = '0' else din33;
mux_1_17 <= din34 when sel(0) = '0' else din35;
mux_1_18 <= din36 when sel(0) = '0' else din37;
mux_1_19 <= din38 when sel(0) = '0' else din39;
mux_1_20 <= din40 when sel(0) = '0' else din41;
mux_1_21 <= din42 when sel(0) = '0' else din43;
mux_1_22 <= din44 when sel(0) = '0' else din45;
mux_1_23 <= din46 when sel(0) = '0' else din47;
mux_1_24 <= din48 when sel(0) = '0' else din49;
mux_1_25 <= din50 when sel(0) = '0' else din51;
mux_1_26 <= din52 when sel(0) = '0' else din53;
mux_1_27 <= din54 when sel(0) = '0' else din55;
mux_1_28 <= din56 when sel(0) = '0' else din57;
mux_1_29 <= din58 when sel(0) = '0' else din59;
mux_1_30 <= din60 when sel(0) = '0' else din61;
mux_1_31 <= din62 when sel(0) = '0' else din63;

-- Generate level 2 logic
mux_2_0 <= mux_1_0 when sel(1) = '0' else mux_1_1;
mux_2_1 <= mux_1_2 when sel(1) = '0' else mux_1_3;
mux_2_2 <= mux_1_4 when sel(1) = '0' else mux_1_5;
mux_2_3 <= mux_1_6 when sel(1) = '0' else mux_1_7;
mux_2_4 <= mux_1_8 when sel(1) = '0' else mux_1_9;
mux_2_5 <= mux_1_10 when sel(1) = '0' else mux_1_11;
mux_2_6 <= mux_1_12 when sel(1) = '0' else mux_1_13;
mux_2_7 <= mux_1_14 when sel(1) = '0' else mux_1_15;
mux_2_8 <= mux_1_16 when sel(1) = '0' else mux_1_17;
mux_2_9 <= mux_1_18 when sel(1) = '0' else mux_1_19;
mux_2_10 <= mux_1_20 when sel(1) = '0' else mux_1_21;
mux_2_11 <= mux_1_22 when sel(1) = '0' else mux_1_23;
mux_2_12 <= mux_1_24 when sel(1) = '0' else mux_1_25;
mux_2_13 <= mux_1_26 when sel(1) = '0' else mux_1_27;
mux_2_14 <= mux_1_28 when sel(1) = '0' else mux_1_29;
mux_2_15 <= mux_1_30 when sel(1) = '0' else mux_1_31;

-- Generate level 3 logic
mux_3_0 <= mux_2_0 when sel(2) = '0' else mux_2_1;
mux_3_1 <= mux_2_2 when sel(2) = '0' else mux_2_3;
mux_3_2 <= mux_2_4 when sel(2) = '0' else mux_2_5;
mux_3_3 <= mux_2_6 when sel(2) = '0' else mux_2_7;
mux_3_4 <= mux_2_8 when sel(2) = '0' else mux_2_9;
mux_3_5 <= mux_2_10 when sel(2) = '0' else mux_2_11;
mux_3_6 <= mux_2_12 when sel(2) = '0' else mux_2_13;
mux_3_7 <= mux_2_14 when sel(2) = '0' else mux_2_15;

-- Generate level 4 logic
mux_4_0 <= mux_3_0 when sel(3) = '0' else mux_3_1;
mux_4_1 <= mux_3_2 when sel(3) = '0' else mux_3_3;
mux_4_2 <= mux_3_4 when sel(3) = '0' else mux_3_5;
mux_4_3 <= mux_3_6 when sel(3) = '0' else mux_3_7;

-- Generate level 5 logic
mux_5_0 <= mux_4_0 when sel(4) = '0' else mux_4_1;
mux_5_1 <= mux_4_2 when sel(4) = '0' else mux_4_3;

-- Generate level 6 logic
mux_6_0 <= mux_5_0 when sel(5) = '0' else mux_5_1;

-- output logic
dout <= mux_6_0;

end architecture;
