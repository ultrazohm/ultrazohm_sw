-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\FCS_MPC_3Phase_SPMSM\hdlsrc\FCS_MPC_3Phase_SPMSM_TEST1\FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_8_En0.vhd
-- Created: 2022-06-27 11:28:55
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_8_En0
-- Source Path: FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/MATLAB Function1/nfp_convert_double_to_fixed_8_En0
-- Hierarchy Level: 2
-- 
-- {Latency Strategy = "Zero"}
-- 
-- {Rounding Mode = Floor}
-- {Overflow Mode = Wrap}
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_8_En0 IS
  PORT( nfp_in                            :   IN    std_logic_vector(63 DOWNTO 0);  -- ufix64
        nfp_out                           :   OUT   std_logic_vector(7 DOWNTO 0)  -- uint8
        );
END FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_8_En0;


ARCHITECTURE rtl OF FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_8_En0 IS

  -- Signals
  SIGNAL nfp_in_unsigned                  : unsigned(63 DOWNTO 0);  -- ufix64
  SIGNAL In1                              : std_logic;  -- ufix1
  SIGNAL In2                              : unsigned(10 DOWNTO 0);  -- ufix11
  SIGNAL In3                              : unsigned(51 DOWNTO 0);  -- ufix52
  SIGNAL Constant3_out1                   : unsigned(15 DOWNTO 0);  -- uint16
  SIGNAL Constant2_out1                   : unsigned(15 DOWNTO 0);  -- uint16
  SIGNAL Switch2_out1                     : unsigned(15 DOWNTO 0);  -- uint16
  SIGNAL Add_sub_cast                     : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL Add_sub_cast_1                   : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL alphave                          : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL Compare_To_Zero_out1             : std_logic;  -- ufix1
  SIGNAL Bit_Concat_out1                  : unsigned(52 DOWNTO 0);  -- ufix53
  SIGNAL Data_Type_Conversion1_out1       : unsigned(52 DOWNTO 0);  -- ufix53_En52
  SIGNAL Data_Type_Conversion1_out1_1     : unsigned(60 DOWNTO 0);  -- ufix61_En53
  SIGNAL Unary_Minus_in0                  : signed(12 DOWNTO 0);  -- sfix13
  SIGNAL alphave_1                        : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic1_zerosig        : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic1_selsig         : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic1_zerosig_1      : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic1_selsig_1       : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic1_cast           : signed(15 DOWNTO 0);  -- int16
  SIGNAL Shift_Arithmetic1_out1           : unsigned(60 DOWNTO 0);  -- ufix61_En53
  SIGNAL Compare_To_Zero1_out1            : std_logic;  -- ufix1
  SIGNAL Compare_To_Zero_out1_1           : std_logic;  -- ufix1
  SIGNAL Logical_Operator_out1            : std_logic;  -- ufix1
  SIGNAL Bit_Set_out1                     : unsigned(60 DOWNTO 0);  -- ufix61_En53
  SIGNAL Switch2_out1_1                   : unsigned(60 DOWNTO 0);  -- ufix61_En53
  SIGNAL shift_arithmetic2_zerosig        : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic2_selsig         : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic2_zerosig_1      : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic2_selsig_1       : signed(11 DOWNTO 0);  -- sfix12
  SIGNAL shift_arithmetic2_cast           : signed(15 DOWNTO 0);  -- int16
  SIGNAL Shift_Arithmetic2_out1           : unsigned(60 DOWNTO 0);  -- ufix61_En53
  SIGNAL Switch1_out1                     : unsigned(60 DOWNTO 0);  -- ufix61_En53
  SIGNAL Data_Type_Conversion3_out1       : signed(61 DOWNTO 0);  -- sfix62_En53
  SIGNAL Unary_Minus_cast                 : signed(62 DOWNTO 0);  -- sfix63_En53
  SIGNAL Unary_Minus_cast_1               : signed(62 DOWNTO 0);  -- sfix63_En53
  SIGNAL Unary_Minus_out1                 : signed(61 DOWNTO 0);  -- sfix62_En53
  SIGNAL Switch1_out1_1                   : signed(61 DOWNTO 0);  -- sfix62_En53
  SIGNAL Data_Type_Conversion2_out1       : unsigned(7 DOWNTO 0);  -- ufix8

BEGIN
  nfp_in_unsigned <= unsigned(nfp_in);

  -- Split 64 bit word into FP sign, exponent, mantissa
  In1 <= nfp_in_unsigned(63);
  In2 <= nfp_in_unsigned(62 DOWNTO 52);
  In3 <= nfp_in_unsigned(51 DOWNTO 0);

  Constant3_out1 <= to_unsigned(16#03FE#, 16);

  Constant2_out1 <= to_unsigned(16#03FF#, 16);

  
  Switch2_out1 <= Constant3_out1 WHEN In2 = to_unsigned(16#000#, 11) ELSE
      Constant2_out1;

  Add_sub_cast <= signed(resize(In2, 12));
  Add_sub_cast_1 <= signed(Switch2_out1(11 DOWNTO 0));
  alphave <= Add_sub_cast - Add_sub_cast_1;

  
  switch_compare_1 <= '1' WHEN alphave >= to_signed(16#000#, 12) ELSE
      '0';

  
  Compare_To_Zero_out1 <= '1' WHEN In2 /= to_unsigned(16#000#, 11) ELSE
      '0';

  Bit_Concat_out1 <= Compare_To_Zero_out1 & In3;

  Data_Type_Conversion1_out1 <= Bit_Concat_out1;

  Data_Type_Conversion1_out1_1 <= resize(Data_Type_Conversion1_out1 & '0', 61);

  Unary_Minus_in0 <=  - (resize(alphave, 13));
  alphave_1 <= Unary_Minus_in0(11 DOWNTO 0);

  shift_arithmetic1_zerosig <= to_signed(16#000#, 12);

  
  shift_arithmetic1_selsig <= alphave_1 WHEN alphave_1 >= shift_arithmetic1_zerosig ELSE
      shift_arithmetic1_zerosig;

  shift_arithmetic1_zerosig_1 <= to_signed(16#000#, 12);

  
  shift_arithmetic1_selsig_1 <= shift_arithmetic1_selsig WHEN shift_arithmetic1_selsig >= shift_arithmetic1_zerosig_1 ELSE
      shift_arithmetic1_zerosig_1;

  shift_arithmetic1_cast <= resize(shift_arithmetic1_selsig_1, 16);
  Shift_Arithmetic1_out1 <= SHIFT_RIGHT(Data_Type_Conversion1_out1_1, to_integer(shift_arithmetic1_cast));

  
  Compare_To_Zero1_out1 <= '1' WHEN Shift_Arithmetic1_out1 = to_unsigned(0, 61) ELSE
      '0';

  
  Compare_To_Zero_out1_1 <= '1' WHEN Data_Type_Conversion1_out1_1 /= to_unsigned(0, 61) ELSE
      '0';

  Logical_Operator_out1 <= Compare_To_Zero1_out1 AND Compare_To_Zero_out1_1;

  Bit_Set_out1 <= Shift_Arithmetic1_out1 OR to_unsigned(1, 61);

  
  Switch2_out1_1 <= Shift_Arithmetic1_out1 WHEN Logical_Operator_out1 = '0' ELSE
      Bit_Set_out1;

  shift_arithmetic2_zerosig <= to_signed(16#000#, 12);

  
  shift_arithmetic2_selsig <= alphave WHEN alphave >= shift_arithmetic2_zerosig ELSE
      shift_arithmetic2_zerosig;

  shift_arithmetic2_zerosig_1 <= to_signed(16#000#, 12);

  
  shift_arithmetic2_selsig_1 <= shift_arithmetic2_selsig WHEN shift_arithmetic2_selsig >= shift_arithmetic2_zerosig_1 ELSE
      shift_arithmetic2_zerosig_1;

  shift_arithmetic2_cast <= resize(shift_arithmetic2_selsig_1, 16);
  Shift_Arithmetic2_out1 <= Data_Type_Conversion1_out1_1 sll to_integer(shift_arithmetic2_cast);

  
  Switch1_out1 <= Switch2_out1_1 WHEN switch_compare_1 = '0' ELSE
      Shift_Arithmetic2_out1;

  Data_Type_Conversion3_out1 <= signed(resize(Switch1_out1, 62));

  Unary_Minus_cast <= resize(Data_Type_Conversion3_out1, 63);
  Unary_Minus_cast_1 <=  - (Unary_Minus_cast);
  Unary_Minus_out1 <= Unary_Minus_cast_1(61 DOWNTO 0);

  
  Switch1_out1_1 <= Data_Type_Conversion3_out1 WHEN In1 = '0' ELSE
      Unary_Minus_out1;

  Data_Type_Conversion2_out1 <= unsigned(Switch1_out1_1(60 DOWNTO 53));

  nfp_out <= std_logic_vector(Data_Type_Conversion2_out1);

END rtl;
