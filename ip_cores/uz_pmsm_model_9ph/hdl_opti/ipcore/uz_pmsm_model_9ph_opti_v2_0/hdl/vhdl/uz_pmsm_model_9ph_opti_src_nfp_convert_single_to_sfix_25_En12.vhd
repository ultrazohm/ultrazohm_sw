-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_pmsm_model_9ph\hdl_opti\hdlsrc\uz_pmsm_model_9ph\uz_pmsm_model_9ph_opti_src_nfp_convert_single_to_sfix_25_En12.vhd
-- Created: 2022-05-18 16:47:48
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_9ph_opti_src_nfp_convert_single_to_sfix_25_En12
-- Source Path: uz_pmsm_model_9ph/uz_pmsm_model_9ph/nfp_convert_single_to_sfix_25_En12
-- Hierarchy Level: 2
-- 
-- {Latency Strategy = "Max"}
-- 
-- {Rounding Mode = Nearest}
-- {Overflow Mode = Wrap}
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph_pkg.ALL;

ENTITY uz_pmsm_model_9ph_opti_src_nfp_convert_single_to_sfix_25_En12 IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        nfp_in                            :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        nfp_out                           :   OUT   std_logic_vector(24 DOWNTO 0)  -- sfix25_En12
        );
END uz_pmsm_model_9ph_opti_src_nfp_convert_single_to_sfix_25_En12;


ARCHITECTURE rtl OF uz_pmsm_model_9ph_opti_src_nfp_convert_single_to_sfix_25_En12 IS

  -- Signals
  SIGNAL nfp_in_unsigned                  : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL In1                              : std_logic;  -- ufix1
  SIGNAL In2                              : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL In3                              : unsigned(22 DOWNTO 0);  -- ufix23
  SIGNAL Delay10_reg                      : std_logic_vector(0 TO 4);  -- ufix1 [5]
  SIGNAL Delay10_reg_next                 : std_logic_vector(0 TO 4);  -- ufix1 [5]
  SIGNAL Delay10_out1                     : std_logic;
  SIGNAL Delay3_out1                      : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL Compare_To_Zero1_out1            : std_logic;
  SIGNAL Constant3_out1                   : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL Constant2_out1                   : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL Switch2_out1                     : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL Add_sub_cast                     : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Add_sub_cast_1                   : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL alphave                          : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Delay1_reg                       : vector_of_signed9(0 TO 1);  -- sfix9 [2]
  SIGNAL Delay1_reg_next                  : vector_of_signed9(0 TO 1);  -- sfix9 [2]
  SIGNAL Delay1_out1                      : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL equality                         : std_logic;
  SIGNAL Delay5_out1                      : std_logic;
  SIGNAL Compare_To_Zero_out1             : std_logic;
  SIGNAL Delay4_out1                      : unsigned(22 DOWNTO 0);  -- ufix23
  SIGNAL Bit_Concat_out1                  : unsigned(23 DOWNTO 0);  -- ufix24
  SIGNAL Data_Type_Conversion1_out1       : unsigned(23 DOWNTO 0);  -- ufix24_En23
  SIGNAL Delay2_reg                       : vector_of_unsigned24(0 TO 1);  -- ufix24 [2]
  SIGNAL Delay2_reg_next                  : vector_of_unsigned24(0 TO 1);  -- ufix24_En23 [2]
  SIGNAL Delay2_out1                      : unsigned(23 DOWNTO 0);  -- ufix24_En23
  SIGNAL Unary_Minus_in0                  : signed(9 DOWNTO 0);  -- sfix10
  SIGNAL alphave_1                        : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL shift_arithmetic1_zerosig        : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL shift_arithmetic1_selsig         : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Data_Type_Conversion_out1        : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL dynamic_shift_zerosig            : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL dynamic_shift_selsig             : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL dynamic_shift_cast               : signed(15 DOWNTO 0);  -- int16
  SIGNAL Shift_Arithmetic1_out1           : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL Delay4_out1_1                    : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL shift_arithmetic2_zerosig        : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL shift_arithmetic2_selsig         : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Data_Type_Conversion1_out1_1     : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL dynamic_shift_zerosig_1          : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL dynamic_shift_selsig_1           : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL dynamic_shift_cast_1             : signed(15 DOWNTO 0);  -- int16
  SIGNAL Shift_Arithmetic2_out1           : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL Delay6_out1                      : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL Switch1_out1                     : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL Delay9_out1                      : unsigned(36 DOWNTO 0);  -- ufix37_En24
  SIGNAL Data_Type_Conversion1_out1_2     : signed(37 DOWNTO 0);  -- sfix38_En24
  SIGNAL Unary_Minus_cast                 : signed(38 DOWNTO 0);  -- sfix39_En24
  SIGNAL Unary_Minus_cast_1               : signed(38 DOWNTO 0);  -- sfix39_En24
  SIGNAL Unary_Minus_out1                 : signed(37 DOWNTO 0);  -- sfix38_En24
  SIGNAL Switch1_out1_1                   : signed(37 DOWNTO 0);  -- sfix38_En24
  SIGNAL Data_Type_Conversion2_out1       : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Delay8_out1                      : signed(24 DOWNTO 0);  -- sfix25_En12

BEGIN
  nfp_in_unsigned <= unsigned(nfp_in);

  -- Split 32 bit word into FP sign, exponent, mantissa
  In1 <= nfp_in_unsigned(31);
  In2 <= nfp_in_unsigned(30 DOWNTO 23);
  In3 <= nfp_in_unsigned(22 DOWNTO 0);

  Delay10_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay10_reg(0) <= '0';
        Delay10_reg(1) <= '0';
        Delay10_reg(2) <= '0';
        Delay10_reg(3) <= '0';
        Delay10_reg(4) <= '0';
      ELSIF enb = '1' THEN
        Delay10_reg(0) <= Delay10_reg_next(0);
        Delay10_reg(1) <= Delay10_reg_next(1);
        Delay10_reg(2) <= Delay10_reg_next(2);
        Delay10_reg(3) <= Delay10_reg_next(3);
        Delay10_reg(4) <= Delay10_reg_next(4);
      END IF;
    END IF;
  END PROCESS Delay10_process;

  Delay10_out1 <= Delay10_reg(4);
  Delay10_reg_next(0) <= In1;
  Delay10_reg_next(1) <= Delay10_reg(0);
  Delay10_reg_next(2) <= Delay10_reg(1);
  Delay10_reg_next(3) <= Delay10_reg(2);
  Delay10_reg_next(4) <= Delay10_reg(3);

  Delay3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay3_out1 <= to_unsigned(16#00#, 8);
      ELSIF enb = '1' THEN
        Delay3_out1 <= In2;
      END IF;
    END IF;
  END PROCESS Delay3_process;


  
  Compare_To_Zero1_out1 <= '1' WHEN Delay3_out1 /= to_unsigned(16#00#, 8) ELSE
      '0';

  Constant3_out1 <= to_unsigned(16#7E#, 8);

  Constant2_out1 <= to_unsigned(16#7F#, 8);

  
  Switch2_out1 <= Constant3_out1 WHEN Compare_To_Zero1_out1 = '0' ELSE
      Constant2_out1;

  Add_sub_cast <= signed(resize(Delay3_out1, 9));
  Add_sub_cast_1 <= signed(resize(Switch2_out1, 9));
  alphave <= Add_sub_cast - Add_sub_cast_1;

  Delay1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay1_reg(0) <= to_signed(16#000#, 9);
        Delay1_reg(1) <= to_signed(16#000#, 9);
      ELSIF enb = '1' THEN
        Delay1_reg(0) <= Delay1_reg_next(0);
        Delay1_reg(1) <= Delay1_reg_next(1);
      END IF;
    END IF;
  END PROCESS Delay1_process;

  Delay1_out1 <= Delay1_reg(1);
  Delay1_reg_next(0) <= alphave;
  Delay1_reg_next(1) <= Delay1_reg(0);

  
  equality <= '1' WHEN Delay1_out1 >= to_signed(16#000#, 9) ELSE
      '0';

  Delay5_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay5_out1 <= '0';
      ELSIF enb = '1' THEN
        Delay5_out1 <= equality;
      END IF;
    END IF;
  END PROCESS Delay5_process;


  
  Compare_To_Zero_out1 <= '1' WHEN Delay3_out1 /= to_unsigned(16#00#, 8) ELSE
      '0';

  Delay4_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay4_out1 <= to_unsigned(16#000000#, 23);
      ELSIF enb = '1' THEN
        Delay4_out1 <= In3;
      END IF;
    END IF;
  END PROCESS Delay4_process;


  Bit_Concat_out1 <= Compare_To_Zero_out1 & Delay4_out1;

  Data_Type_Conversion1_out1 <= Bit_Concat_out1;

  Delay2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay2_reg(0) <= to_unsigned(16#000000#, 24);
        Delay2_reg(1) <= to_unsigned(16#000000#, 24);
      ELSIF enb = '1' THEN
        Delay2_reg(0) <= Delay2_reg_next(0);
        Delay2_reg(1) <= Delay2_reg_next(1);
      END IF;
    END IF;
  END PROCESS Delay2_process;

  Delay2_out1 <= Delay2_reg(1);
  Delay2_reg_next(0) <= Data_Type_Conversion1_out1;
  Delay2_reg_next(1) <= Delay2_reg(0);

  Unary_Minus_in0 <=  - (resize(Delay1_out1, 10));
  alphave_1 <= Unary_Minus_in0(8 DOWNTO 0);

  shift_arithmetic1_zerosig <= to_signed(16#000#, 9);

  
  shift_arithmetic1_selsig <= alphave_1 WHEN alphave_1 >= shift_arithmetic1_zerosig ELSE
      shift_arithmetic1_zerosig;

  Data_Type_Conversion_out1 <= resize(Delay2_out1 & '0', 37);

  dynamic_shift_zerosig <= to_signed(16#000#, 9);

  
  dynamic_shift_selsig <= shift_arithmetic1_selsig WHEN shift_arithmetic1_selsig >= dynamic_shift_zerosig ELSE
      dynamic_shift_zerosig;

  dynamic_shift_cast <= resize(dynamic_shift_selsig, 16);
  Shift_Arithmetic1_out1 <= SHIFT_RIGHT(Data_Type_Conversion_out1, to_integer(dynamic_shift_cast));

  Delay4_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay4_out1_1 <= to_unsigned(0, 37);
      ELSIF enb = '1' THEN
        Delay4_out1_1 <= Shift_Arithmetic1_out1;
      END IF;
    END IF;
  END PROCESS Delay4_1_process;


  shift_arithmetic2_zerosig <= to_signed(16#000#, 9);

  
  shift_arithmetic2_selsig <= Delay1_out1 WHEN Delay1_out1 >= shift_arithmetic2_zerosig ELSE
      shift_arithmetic2_zerosig;

  Data_Type_Conversion1_out1_1 <= resize(Delay2_out1 & '0', 37);

  dynamic_shift_zerosig_1 <= to_signed(16#000#, 9);

  
  dynamic_shift_selsig_1 <= shift_arithmetic2_selsig WHEN shift_arithmetic2_selsig >= dynamic_shift_zerosig_1 ELSE
      dynamic_shift_zerosig_1;

  dynamic_shift_cast_1 <= resize(dynamic_shift_selsig_1, 16);
  Shift_Arithmetic2_out1 <= Data_Type_Conversion1_out1_1 sll to_integer(dynamic_shift_cast_1);

  Delay6_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay6_out1 <= to_unsigned(0, 37);
      ELSIF enb = '1' THEN
        Delay6_out1 <= Shift_Arithmetic2_out1;
      END IF;
    END IF;
  END PROCESS Delay6_process;


  
  Switch1_out1 <= Delay4_out1_1 WHEN Delay5_out1 = '0' ELSE
      Delay6_out1;

  Delay9_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay9_out1 <= to_unsigned(0, 37);
      ELSIF enb = '1' THEN
        Delay9_out1 <= Switch1_out1;
      END IF;
    END IF;
  END PROCESS Delay9_process;


  Data_Type_Conversion1_out1_2 <= signed(resize(Delay9_out1, 38));

  Unary_Minus_cast <= resize(Data_Type_Conversion1_out1_2, 39);
  Unary_Minus_cast_1 <=  - (Unary_Minus_cast);
  Unary_Minus_out1 <= Unary_Minus_cast_1(37 DOWNTO 0);

  
  Switch1_out1_1 <= Data_Type_Conversion1_out1_2 WHEN Delay10_out1 = '0' ELSE
      Unary_Minus_out1;

  Data_Type_Conversion2_out1 <= Switch1_out1_1(36 DOWNTO 12) + ('0' & Switch1_out1_1(11));

  Delay8_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay8_out1 <= to_signed(16#0000000#, 25);
      ELSIF enb = '1' THEN
        Delay8_out1 <= Data_Type_Conversion2_out1;
      END IF;
    END IF;
  END PROCESS Delay8_process;


  nfp_out <= std_logic_vector(Delay8_out1);

END rtl;
