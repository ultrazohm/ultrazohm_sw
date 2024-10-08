-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\Transformation_V11\Trans_123_dq_V11_ip_src_dq_transformation.vhd
-- Created: 2018-11-22 13:08:54
-- 
-- Generated by MATLAB 9.4 and HDL Coder 3.12
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Trans_123_dq_V11_ip_src_dq_transformation
-- Source Path: Transformation_V11/Trans_123_dq_fix_V11/dq_transformation
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.Trans_123_dq_V11_ip_src_Trans_123_dq_fix_V11_pkg.ALL;

ENTITY Trans_123_dq_V11_ip_src_dq_transformation IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        a                                 :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        b                                 :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        theta                             :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        d                                 :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        q                                 :   OUT   std_logic_vector(17 DOWNTO 0)  -- sfix18_En11
        );
END Trans_123_dq_V11_ip_src_dq_transformation;


ARCHITECTURE rtl OF Trans_123_dq_V11_ip_src_dq_transformation IS

  -- Signals
  SIGNAL a_signed                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL delayMatch_reg                   : vector_of_signed18(0 TO 1);  -- sfix18 [2]
  SIGNAL a_1                              : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b_signed                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL theta_signed                     : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL d_tmp                            : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL q_tmp                            : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL i1                               : std_logic;  -- ufix1
  SIGNAL i2                               : std_logic;  -- ufix1
  SIGNAL i3                               : std_logic;  -- ufix1
  SIGNAL i4                               : std_logic;  -- ufix1
  SIGNAL i5                               : std_logic;  -- ufix1
  SIGNAL i6                               : std_logic;  -- ufix1
  SIGNAL i7                               : std_logic;  -- ufix1
  SIGNAL i8                               : std_logic;  -- ufix1
  SIGNAL i9                               : std_logic;  -- ufix1
  SIGNAL i10                              : std_logic;  -- ufix1
  SIGNAL i11                              : std_logic;  -- ufix1
  SIGNAL i12                              : std_logic;  -- ufix1
  SIGNAL i13                              : std_logic;  -- ufix1
  SIGNAL i14                              : std_logic;  -- ufix1
  SIGNAL i15                              : std_logic;  -- ufix1
  SIGNAL a1                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a2                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a3                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a4                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a5                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a6                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a7                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a8                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a9                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a10                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a11                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a12                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a13                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a14                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL a15                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b1                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b2                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b3                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b4                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b5                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b6                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b7                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b8                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b9                               : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b10                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b11                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b12                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b13                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b14                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL b15                              : signed(17 DOWNTO 0);  -- sfix18
  SIGNAL beta1                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta2                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta3                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta4                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta5                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta6                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta7                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta8                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta9                            : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta10                           : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta11                           : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta12                           : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta13                           : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL beta14                           : signed(23 DOWNTO 0);  -- sfix24
  SIGNAL i1_next                          : std_logic;  -- ufix1
  SIGNAL i2_next                          : std_logic;  -- ufix1
  SIGNAL i3_next                          : std_logic;  -- ufix1
  SIGNAL i4_next                          : std_logic;  -- ufix1
  SIGNAL i5_next                          : std_logic;  -- ufix1
  SIGNAL i6_next                          : std_logic;  -- ufix1
  SIGNAL i7_next                          : std_logic;  -- ufix1
  SIGNAL i8_next                          : std_logic;  -- ufix1
  SIGNAL i9_next                          : std_logic;  -- ufix1
  SIGNAL i10_next                         : std_logic;  -- ufix1
  SIGNAL i11_next                         : std_logic;  -- ufix1
  SIGNAL i12_next                         : std_logic;  -- ufix1
  SIGNAL i13_next                         : std_logic;  -- ufix1
  SIGNAL i14_next                         : std_logic;  -- ufix1
  SIGNAL i15_next                         : std_logic;  -- ufix1
  SIGNAL a1_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a2_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a3_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a4_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a5_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a6_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a7_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a8_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a9_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a10_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a11_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a12_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a13_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a14_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL a15_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b1_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b2_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b3_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b4_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b5_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b6_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b7_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b8_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b9_next                          : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b10_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b11_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b12_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b13_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b14_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL b15_next                         : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL beta1_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta2_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta3_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta4_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta5_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta6_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta7_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta8_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta9_next                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta10_next                      : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta11_next                      : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta12_next                      : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta13_next                      : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL beta14_next                      : signed(23 DOWNTO 0);  -- sfix24_En20

BEGIN
  a_signed <= signed(a);

  delayMatch_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch_reg <= (OTHERS => to_signed(16#00000#, 18));
      ELSIF enb = '1' THEN
        delayMatch_reg(0) <= a_signed;
        delayMatch_reg(1) <= delayMatch_reg(0);
      END IF;
    END IF;
  END PROCESS delayMatch_process;

  a_1 <= delayMatch_reg(1);

  b_signed <= signed(b);

  theta_signed <= signed(theta);

  dq_transformation_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        a1 <= to_signed(16#00000#, 18);
        a2 <= to_signed(16#00000#, 18);
        a3 <= to_signed(16#00000#, 18);
        a4 <= to_signed(16#00000#, 18);
        a5 <= to_signed(16#00000#, 18);
        a6 <= to_signed(16#00000#, 18);
        a7 <= to_signed(16#00000#, 18);
        a8 <= to_signed(16#00000#, 18);
        a9 <= to_signed(16#00000#, 18);
        a10 <= to_signed(16#00000#, 18);
        a11 <= to_signed(16#00000#, 18);
        a12 <= to_signed(16#00000#, 18);
        a13 <= to_signed(16#00000#, 18);
        a14 <= to_signed(16#00000#, 18);
        a15 <= to_signed(16#00000#, 18);
        b1 <= to_signed(16#00000#, 18);
        b2 <= to_signed(16#00000#, 18);
        b3 <= to_signed(16#00000#, 18);
        b4 <= to_signed(16#00000#, 18);
        b5 <= to_signed(16#00000#, 18);
        b6 <= to_signed(16#00000#, 18);
        b7 <= to_signed(16#00000#, 18);
        b8 <= to_signed(16#00000#, 18);
        b9 <= to_signed(16#00000#, 18);
        b10 <= to_signed(16#00000#, 18);
        b11 <= to_signed(16#00000#, 18);
        b12 <= to_signed(16#00000#, 18);
        b13 <= to_signed(16#00000#, 18);
        b14 <= to_signed(16#00000#, 18);
        b15 <= to_signed(16#00000#, 18);
        beta1 <= to_signed(16#000000#, 24);
        beta2 <= to_signed(16#000000#, 24);
        beta3 <= to_signed(16#000000#, 24);
        beta4 <= to_signed(16#000000#, 24);
        beta5 <= to_signed(16#000000#, 24);
        beta6 <= to_signed(16#000000#, 24);
        beta7 <= to_signed(16#000000#, 24);
        beta8 <= to_signed(16#000000#, 24);
        beta9 <= to_signed(16#000000#, 24);
        beta10 <= to_signed(16#000000#, 24);
        beta11 <= to_signed(16#000000#, 24);
        beta12 <= to_signed(16#000000#, 24);
        beta13 <= to_signed(16#000000#, 24);
        beta14 <= to_signed(16#000000#, 24);
        i1 <= '0';
        i2 <= '0';
        i3 <= '0';
        i4 <= '0';
        i5 <= '0';
        i6 <= '0';
        i7 <= '0';
        i8 <= '0';
        i9 <= '0';
        i10 <= '0';
        i11 <= '0';
        i12 <= '0';
        i13 <= '0';
        i14 <= '0';
        i15 <= '0';
      ELSIF enb = '1' THEN
        i1 <= i1_next;
        i2 <= i2_next;
        i3 <= i3_next;
        i4 <= i4_next;
        i5 <= i5_next;
        i6 <= i6_next;
        i7 <= i7_next;
        i8 <= i8_next;
        i9 <= i9_next;
        i10 <= i10_next;
        i11 <= i11_next;
        i12 <= i12_next;
        i13 <= i13_next;
        i14 <= i14_next;
        i15 <= i15_next;
        a1 <= a1_next;
        a2 <= a2_next;
        a3 <= a3_next;
        a4 <= a4_next;
        a5 <= a5_next;
        a6 <= a6_next;
        a7 <= a7_next;
        a8 <= a8_next;
        a9 <= a9_next;
        a10 <= a10_next;
        a11 <= a11_next;
        a12 <= a12_next;
        a13 <= a13_next;
        a14 <= a14_next;
        a15 <= a15_next;
        b1 <= b1_next;
        b2 <= b2_next;
        b3 <= b3_next;
        b4 <= b4_next;
        b5 <= b5_next;
        b6 <= b6_next;
        b7 <= b7_next;
        b8 <= b8_next;
        b9 <= b9_next;
        b10 <= b10_next;
        b11 <= b11_next;
        b12 <= b12_next;
        b13 <= b13_next;
        b14 <= b14_next;
        b15 <= b15_next;
        beta1 <= beta1_next;
        beta2 <= beta2_next;
        beta3 <= beta3_next;
        beta4 <= beta4_next;
        beta5 <= beta5_next;
        beta6 <= beta6_next;
        beta7 <= beta7_next;
        beta8 <= beta8_next;
        beta9 <= beta9_next;
        beta10 <= beta10_next;
        beta11 <= beta11_next;
        beta12 <= beta12_next;
        beta13 <= beta13_next;
        beta14 <= beta14_next;
      END IF;
    END IF;
  END PROCESS dq_transformation_process;

  dq_transformation_output : PROCESS (a_1, b_signed, theta_signed, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12,
       i13, i14, i15, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13,
       a14, a15, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14,
       b15, beta1, beta2, beta3, beta4, beta5, beta6, beta7, beta8, beta9,
       beta10, beta11, beta12, beta13, beta14)
    VARIABLE a16n : signed(17 DOWNTO 0);
    VARIABLE b16n : signed(17 DOWNTO 0);
    VARIABLE c : signed(17 DOWNTO 0);
    VARIABLE c_0 : signed(17 DOWNTO 0);
    VARIABLE c_1 : signed(17 DOWNTO 0);
    VARIABLE c_2 : signed(17 DOWNTO 0);
    VARIABLE c_3 : signed(17 DOWNTO 0);
    VARIABLE c_4 : signed(17 DOWNTO 0);
    VARIABLE c_5 : signed(17 DOWNTO 0);
    VARIABLE c_6 : signed(17 DOWNTO 0);
    VARIABLE c_7 : signed(17 DOWNTO 0);
    VARIABLE c_8 : signed(17 DOWNTO 0);
    VARIABLE c_9 : signed(17 DOWNTO 0);
    VARIABLE c_10 : signed(17 DOWNTO 0);
    VARIABLE c_11 : signed(17 DOWNTO 0);
    VARIABLE c_12 : signed(17 DOWNTO 0);
    VARIABLE c_13 : signed(17 DOWNTO 0);
    VARIABLE c_14 : signed(17 DOWNTO 0);
    VARIABLE c_15 : signed(17 DOWNTO 0);
    VARIABLE c_16 : signed(17 DOWNTO 0);
    VARIABLE c_17 : signed(17 DOWNTO 0);
    VARIABLE c_18 : signed(17 DOWNTO 0);
    VARIABLE c_19 : signed(17 DOWNTO 0);
    VARIABLE c_20 : signed(17 DOWNTO 0);
    VARIABLE c_21 : signed(17 DOWNTO 0);
    VARIABLE c_22 : signed(17 DOWNTO 0);
    VARIABLE c_23 : signed(17 DOWNTO 0);
    VARIABLE c_24 : signed(17 DOWNTO 0);
    VARIABLE c_25 : signed(17 DOWNTO 0);
    VARIABLE c_26 : signed(17 DOWNTO 0);
    VARIABLE c_27 : signed(17 DOWNTO 0);
    VARIABLE c_28 : signed(17 DOWNTO 0);
    VARIABLE c_29 : signed(17 DOWNTO 0);
    VARIABLE c_30 : signed(17 DOWNTO 0);
    VARIABLE c_31 : signed(17 DOWNTO 0);
    VARIABLE c_32 : signed(17 DOWNTO 0);
    VARIABLE c_33 : signed(17 DOWNTO 0);
    VARIABLE c_34 : signed(17 DOWNTO 0);
    VARIABLE c_35 : signed(17 DOWNTO 0);
    VARIABLE c_36 : signed(17 DOWNTO 0);
    VARIABLE c_37 : signed(17 DOWNTO 0);
    VARIABLE c_38 : signed(17 DOWNTO 0);
    VARIABLE c_39 : signed(17 DOWNTO 0);
    VARIABLE c_40 : signed(17 DOWNTO 0);
    VARIABLE c_41 : signed(17 DOWNTO 0);
    VARIABLE c_42 : signed(17 DOWNTO 0);
    VARIABLE c_43 : signed(17 DOWNTO 0);
    VARIABLE c_44 : signed(17 DOWNTO 0);
    VARIABLE c_45 : signed(17 DOWNTO 0);
    VARIABLE c_46 : signed(17 DOWNTO 0);
    VARIABLE c_47 : signed(17 DOWNTO 0);
    VARIABLE c_48 : signed(17 DOWNTO 0);
    VARIABLE c_49 : signed(17 DOWNTO 0);
    VARIABLE c_50 : signed(17 DOWNTO 0);
    VARIABLE mul_temp : signed(35 DOWNTO 0);
    VARIABLE mul_temp_0 : signed(35 DOWNTO 0);
    VARIABLE cast : signed(18 DOWNTO 0);
    VARIABLE cast_0 : signed(18 DOWNTO 0);
    VARIABLE cast_1 : signed(18 DOWNTO 0);
    VARIABLE cast_2 : signed(18 DOWNTO 0);
  BEGIN
    --MATLAB Function 'Trans_123_dq_fix_V11/dq_transformation'
    -- Author : Saeid Saeidi
    -- Modified: Sebastian Wendel
    -- EAL -TUM
    -- MATLAB Version : R2016a
    -- Defining persistent variables
    --In VHDL , persistent variables will appear as Signals
    -- %
    -- %
    -- %
    -- %
    -- %
    -- %
    -- %
    -- %
    -- Initialization of Persistent Variables with the numeric type of the
    -- input variables "a" and "b"
    -- After generating VHDL this part will be located in the RESET
    -------------------------------------------------------------------------%
    -- Definition of Constant Values
    --1.570796
    -- Determining section of the theta -> Check if theta is between -pi/2 and
    -- pi/2
    -- -- ------- # First pipeline stage
    IF theta_signed <= to_signed(-16#1921FC#, 24) THEN 
      beta1_next <= theta_signed + to_signed(16#3243F6#, 24);
      i1_next <= '0';
    ELSIF theta_signed >= to_signed(16#1921FB#, 24) THEN 
      beta1_next <= theta_signed - to_signed(16#3243F6#, 24);
      i1_next <= '0';
    ELSE 
      beta1_next <= theta_signed;
      i1_next <= '1';
    END IF;
    -- -- ------- # Second pipeline stage 0.78539816339745 = pi/4
    IF beta1 < to_signed(16#000000#, 24) THEN 
      a2_next <= a1 + b1;
      b2_next <= b1 - a1;
      beta2_next <= beta1 + to_signed(16#0C90FD#, 24);
    ELSE 
      a2_next <= a1 - b1;
      b2_next <= b1 + a1;
      beta2_next <= beta1 - to_signed(16#0C90FD#, 24);
    END IF;
    -- -- ------- # Third pipeline stage 0.46364760900081 = pi/8 ???
    IF beta2 < to_signed(16#000000#, 24) THEN 
      c_1 := SHIFT_RIGHT(b2, 1);
      a3_next <= a2 + c_1;
      c_2 := SHIFT_RIGHT(a2, 1);
      b3_next <= b2 - c_2;
      beta3_next <= beta2 + to_signed(16#076B19#, 24);
    ELSE 
      c := SHIFT_RIGHT(b2, 1);
      a3_next <= a2 - c;
      c_0 := SHIFT_RIGHT(a2, 1);
      b3_next <= b2 + c_0;
      beta3_next <= beta2 - to_signed(16#076B19#, 24);
    END IF;
    -- -- ------- # Fourth pipeline stage
    IF beta3 < to_signed(16#000000#, 24) THEN 
      c_5 := SHIFT_RIGHT(b3, 2);
      a4_next <= a3 + c_5;
      c_6 := SHIFT_RIGHT(a3, 2);
      b4_next <= b3 - c_6;
      beta4_next <= beta3 + to_signed(16#03EB6E#, 24);
    ELSE 
      c_3 := SHIFT_RIGHT(b3, 2);
      a4_next <= a3 - c_3;
      c_4 := SHIFT_RIGHT(a3, 2);
      b4_next <= b3 + c_4;
      beta4_next <= beta3 - to_signed(16#03EB6E#, 24);
    END IF;
    -- -- ------- # Fifth pipeline stage
    IF beta4 < to_signed(16#000000#, 24) THEN 
      c_9 := SHIFT_RIGHT(b4, 3);
      a5_next <= a4 + c_9;
      c_10 := SHIFT_RIGHT(a4, 3);
      b5_next <= b4 - c_10;
      beta5_next <= beta4 + to_signed(16#01FD5B#, 24);
    ELSE 
      c_7 := SHIFT_RIGHT(b4, 3);
      a5_next <= a4 - c_7;
      c_8 := SHIFT_RIGHT(a4, 3);
      b5_next <= b4 + c_8;
      beta5_next <= beta4 - to_signed(16#01FD5B#, 24);
    END IF;
    -- -- ------- # Sixth pipeline stage
    IF beta5 < to_signed(16#000000#, 24) THEN 
      c_13 := SHIFT_RIGHT(b5, 4);
      a6_next <= a5 + c_13;
      c_14 := SHIFT_RIGHT(a5, 4);
      b6_next <= b5 - c_14;
      beta6_next <= beta5 + to_signed(16#00FFAA#, 24);
    ELSE 
      c_11 := SHIFT_RIGHT(b5, 4);
      a6_next <= a5 - c_11;
      c_12 := SHIFT_RIGHT(a5, 4);
      b6_next <= b5 + c_12;
      beta6_next <= beta5 - to_signed(16#00FFAA#, 24);
    END IF;
    -- -- ------- # Seventh pipeline stage
    IF beta6 < to_signed(16#000000#, 24) THEN 
      c_17 := SHIFT_RIGHT(b6, 5);
      a7_next <= a6 + c_17;
      c_18 := SHIFT_RIGHT(a6, 5);
      b7_next <= b6 - c_18;
      beta7_next <= beta6 + to_signed(16#007FF5#, 24);
    ELSE 
      c_15 := SHIFT_RIGHT(b6, 5);
      a7_next <= a6 - c_15;
      c_16 := SHIFT_RIGHT(a6, 5);
      b7_next <= b6 + c_16;
      beta7_next <= beta6 - to_signed(16#007FF5#, 24);
    END IF;
    -- -- ------- # Eighth pipeline stage
    IF beta7 < to_signed(16#000000#, 24) THEN 
      c_21 := SHIFT_RIGHT(b7, 6);
      a8_next <= a7 + c_21;
      c_22 := SHIFT_RIGHT(a7, 6);
      b8_next <= b7 - c_22;
      beta8_next <= beta7 + to_signed(16#003FFE#, 24);
    ELSE 
      c_19 := SHIFT_RIGHT(b7, 6);
      a8_next <= a7 - c_19;
      c_20 := SHIFT_RIGHT(a7, 6);
      b8_next <= b7 + c_20;
      beta8_next <= beta7 - to_signed(16#003FFE#, 24);
    END IF;
    -- -- ------- # Ninth pipeline stage
    IF beta8 < to_signed(16#000000#, 24) THEN 
      c_25 := SHIFT_RIGHT(b8, 7);
      a9_next <= a8 + c_25;
      c_26 := SHIFT_RIGHT(a8, 7);
      b9_next <= b8 - c_26;
      beta9_next <= beta8 + to_signed(16#001FFF#, 24);
    ELSE 
      c_23 := SHIFT_RIGHT(b8, 7);
      a9_next <= a8 - c_23;
      c_24 := SHIFT_RIGHT(a8, 7);
      b9_next <= b8 + c_24;
      beta9_next <= beta8 - to_signed(16#001FFF#, 24);
    END IF;
    -- -- ------- # Tenth pipeline stage
    IF beta9 < to_signed(16#000000#, 24) THEN 
      c_29 := SHIFT_RIGHT(b9, 8);
      a10_next <= a9 + c_29;
      c_30 := SHIFT_RIGHT(a9, 8);
      b10_next <= b9 - c_30;
      beta10_next <= beta9 + to_signed(16#000FFF#, 24);
    ELSE 
      c_27 := SHIFT_RIGHT(b9, 8);
      a10_next <= a9 - c_27;
      c_28 := SHIFT_RIGHT(a9, 8);
      b10_next <= b9 + c_28;
      beta10_next <= beta9 - to_signed(16#000FFF#, 24);
    END IF;
    -- -- ------- # Eleventh pipeline stage
    IF beta10 < to_signed(16#000000#, 24) THEN 
      c_33 := SHIFT_RIGHT(b10, 9);
      a11_next <= a10 + c_33;
      c_34 := SHIFT_RIGHT(a10, 9);
      b11_next <= b10 - c_34;
      beta11_next <= beta10 + to_signed(16#0007FF#, 24);
    ELSE 
      c_31 := SHIFT_RIGHT(b10, 9);
      a11_next <= a10 - c_31;
      c_32 := SHIFT_RIGHT(a10, 9);
      b11_next <= b10 + c_32;
      beta11_next <= beta10 - to_signed(16#0007FF#, 24);
    END IF;
    -- -- ------- # Twelfth pipeline stage
    IF beta11 < to_signed(16#000000#, 24) THEN 
      c_37 := SHIFT_RIGHT(b11, 10);
      a12_next <= a11 + c_37;
      c_38 := SHIFT_RIGHT(a11, 10);
      b12_next <= b11 - c_38;
      beta12_next <= beta11 + to_signed(16#0003FF#, 24);
    ELSE 
      c_35 := SHIFT_RIGHT(b11, 10);
      a12_next <= a11 - c_35;
      c_36 := SHIFT_RIGHT(a11, 10);
      b12_next <= b11 + c_36;
      beta12_next <= beta11 - to_signed(16#0003FF#, 24);
    END IF;
    -- -- ------- # Thirteenth pipeline stage
    IF beta12 < to_signed(16#000000#, 24) THEN 
      c_41 := SHIFT_RIGHT(b12, 11);
      a13_next <= a12 + c_41;
      c_42 := SHIFT_RIGHT(a12, 11);
      b13_next <= b12 - c_42;
      beta13_next <= beta12 + to_signed(16#0001FF#, 24);
    ELSE 
      c_39 := SHIFT_RIGHT(b12, 11);
      a13_next <= a12 - c_39;
      c_40 := SHIFT_RIGHT(a12, 11);
      b13_next <= b12 + c_40;
      beta13_next <= beta12 - to_signed(16#0001FF#, 24);
    END IF;
    -- -- ------- # Fourteenth pipeline stage
    IF beta13 < to_signed(16#000000#, 24) THEN 
      c_45 := SHIFT_RIGHT(b13, 12);
      a14_next <= a13 + c_45;
      c_46 := SHIFT_RIGHT(a13, 12);
      b14_next <= b13 - c_46;
      beta14_next <= beta13 + to_signed(16#0000FF#, 24);
    ELSE 
      c_43 := SHIFT_RIGHT(b13, 12);
      a14_next <= a13 - c_43;
      c_44 := SHIFT_RIGHT(a13, 12);
      b14_next <= b13 + c_44;
      beta14_next <= beta11 - to_signed(16#0000FF#, 24);
    END IF;
    -- -- ------- # Fifteenth pipeline stage
    IF beta14 < to_signed(16#000000#, 24) THEN 
      c_49 := SHIFT_RIGHT(b14, 13);
      a15_next <= a14 + c_49;
      c_50 := SHIFT_RIGHT(a14, 13);
      b15_next <= b14 - c_50;
    ELSE 
      c_47 := SHIFT_RIGHT(b14, 13);
      a15_next <= a14 - c_47;
      c_48 := SHIFT_RIGHT(a14, 13);
      b15_next <= b14 + c_48;
    END IF;
    -- -- ------- # Sixteenth pipeline stage
    mul_temp := a15 * to_signed(16#136EA#, 18);
    a16n := mul_temp(34 DOWNTO 17);
    mul_temp_0 := b15 * to_signed(16#136EA#, 18);
    b16n := mul_temp_0(34 DOWNTO 17);
    -- Output Update of Registers
    -- %
    a1_next <= a_1;
    -- %
    b1_next <= b_signed;
    -- %
    -- %
    i2_next <= i1;
    i3_next <= i2;
    i4_next <= i3;
    i5_next <= i4;
    i6_next <= i5;
    i7_next <= i6;
    i8_next <= i7;
    i9_next <= i8;
    i10_next <= i9;
    i11_next <= i10;
    i12_next <= i11;
    i13_next <= i12;
    i14_next <= i13;
    i15_next <= i14;
    -- %
    -- Generating output
    IF i15 = '0' THEN 
      cast := resize(a16n, 19);
      cast_0 :=  - (cast);
      a16n := cast_0(17 DOWNTO 0);
      cast_1 := resize(b16n, 19);
      cast_2 :=  - (cast_1);
      b16n := cast_2(17 DOWNTO 0);
    ELSE 
    END IF;
    d_tmp <= a16n;
    q_tmp <= b16n;
  END PROCESS dq_transformation_output;


  d <= std_logic_vector(d_tmp);

  q <= std_logic_vector(q_tmp);

END rtl;

