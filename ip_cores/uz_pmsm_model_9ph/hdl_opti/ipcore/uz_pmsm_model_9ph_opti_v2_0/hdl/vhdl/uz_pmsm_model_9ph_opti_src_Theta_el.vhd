-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_pmsm_model_9ph\hdl_opti\hdlsrc\uz_pmsm_model_9ph\uz_pmsm_model_9ph_opti_src_Theta_el.vhd
-- Created: 2022-05-18 16:47:48
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_9ph_opti_src_Theta_el
-- Source Path: uz_pmsm_model_9ph/uz_pmsm_model_9ph/Theta_el
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph_pkg.ALL;

ENTITY uz_pmsm_model_9ph_opti_src_Theta_el IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb_1_200_1                       :   IN    std_logic;
        enb                               :   IN    std_logic;
        w_mech                            :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        polepairs                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        reset_1                           :   IN    std_logic;
        theta_el                          :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
        );
END uz_pmsm_model_9ph_opti_src_Theta_el;


ARCHITECTURE rtl OF uz_pmsm_model_9ph_opti_src_Theta_el IS

  -- Component Declarations
  COMPONENT uz_pmsm_model_9ph_opti_src_nfp_mul_single
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_in2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph_opti_src_nfp_convert_single2double
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in                          :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_out                         :   OUT   std_logic_vector(63 DOWNTO 0)  -- double
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph_opti_src_nfp_mul_double
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in1                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_in2                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(63 DOWNTO 0)  -- double
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph_opti_src_nfp_add_double
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in1                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_in2                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(63 DOWNTO 0)  -- double
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph_opti_src_nfp_convert_double2single
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in                          :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_pmsm_model_9ph_opti_src_nfp_mul_single
    USE ENTITY work.uz_pmsm_model_9ph_opti_src_nfp_mul_single(rtl);

  FOR ALL : uz_pmsm_model_9ph_opti_src_nfp_convert_single2double
    USE ENTITY work.uz_pmsm_model_9ph_opti_src_nfp_convert_single2double(rtl);

  FOR ALL : uz_pmsm_model_9ph_opti_src_nfp_mul_double
    USE ENTITY work.uz_pmsm_model_9ph_opti_src_nfp_mul_double(rtl);

  FOR ALL : uz_pmsm_model_9ph_opti_src_nfp_add_double
    USE ENTITY work.uz_pmsm_model_9ph_opti_src_nfp_add_double(rtl);

  FOR ALL : uz_pmsm_model_9ph_opti_src_nfp_convert_double2single
    USE ENTITY work.uz_pmsm_model_9ph_opti_src_nfp_convert_double2single(rtl);

  -- Signals
  SIGNAL kconst                           : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Divide_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Data_Type_Conversion2_out1       : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Gain_out1                        : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_iv                        : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_out1                      : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Sum3_out1                        : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_toDel                     : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_toDel_1                   : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_lowered_bypass_reg        : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_toDel_2                   : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Delay1_delOut                    : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL delayMatch1_reg                  : vector_of_std_logic_vector64(0 TO 159);  -- ufix64 [160]
  SIGNAL delayMatch1_reg_next             : vector_of_std_logic_vector64(0 TO 159);  -- ufix64 [160]
  SIGNAL Delay1_delOut_1                  : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL theta_el_1                       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL delayMatch2_reg                  : vector_of_std_logic_vector32(0 TO 18);  -- ufix32 [19]
  SIGNAL delayMatch2_reg_next             : vector_of_std_logic_vector32(0 TO 18);  -- ufix32 [19]

BEGIN
  u_nfp_mul_comp : uz_pmsm_model_9ph_opti_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              nfp_in1 => w_mech,  -- single
              nfp_in2 => polepairs,  -- single
              nfp_out => Divide_out1  -- single
              );

  u_uz_pmsm_model_9ph_uz_pmsm_model_9ph_nfp_convert_single2double : uz_pmsm_model_9ph_opti_src_nfp_convert_single2double
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              nfp_in => Divide_out1,  -- single
              nfp_out => Data_Type_Conversion2_out1  -- double
              );

  u_nfp_mul_comp_1 : uz_pmsm_model_9ph_opti_src_nfp_mul_double
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              nfp_in1 => kconst,  -- double
              nfp_in2 => Data_Type_Conversion2_out1,  -- double
              nfp_out => Gain_out1  -- double
              );

  u_nfp_add_comp : uz_pmsm_model_9ph_opti_src_nfp_add_double
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              nfp_in1 => Gain_out1,  -- double
              nfp_in2 => Delay1_out1,  -- double
              nfp_out => Sum3_out1  -- double
              );

  u_uz_pmsm_model_9ph_uz_pmsm_model_9ph_nfp_convert_double2single : uz_pmsm_model_9ph_opti_src_nfp_convert_double2single
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              nfp_in => Delay1_out1,  -- double
              nfp_out => theta_el_1  -- single
              );

  kconst <= X"3eb0c6f7a0b5ed8d";

  Delay1_iv <= X"0000000000000000";

  
  Delay1_toDel <= Sum3_out1 WHEN reset_1 = '0' ELSE
      Delay1_iv;

  crp_out_delay_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay1_toDel_1 <= X"0000000000000000";
      ELSIF enb = '1' THEN
        Delay1_toDel_1 <= Delay1_toDel;
      END IF;
    END IF;
  END PROCESS crp_out_delay_process;


  Delay1_lowered_bypass_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay1_lowered_bypass_reg <= X"0000000000000000";
      ELSIF enb_1_200_1 = '1' THEN
        Delay1_lowered_bypass_reg <= Delay1_toDel_1;
      END IF;
    END IF;
  END PROCESS Delay1_lowered_bypass_process;

  
  Delay1_toDel_2 <= Delay1_toDel_1 WHEN enb_1_200_1 = '1' ELSE
      Delay1_lowered_bypass_reg;

  Delay1_delOut <= Delay1_toDel_2;

  delayMatch1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch1_reg(0) <= X"0000000000000000";
        delayMatch1_reg(1) <= X"0000000000000000";
        delayMatch1_reg(2) <= X"0000000000000000";
        delayMatch1_reg(3) <= X"0000000000000000";
        delayMatch1_reg(4) <= X"0000000000000000";
        delayMatch1_reg(5) <= X"0000000000000000";
        delayMatch1_reg(6) <= X"0000000000000000";
        delayMatch1_reg(7) <= X"0000000000000000";
        delayMatch1_reg(8) <= X"0000000000000000";
        delayMatch1_reg(9) <= X"0000000000000000";
        delayMatch1_reg(10) <= X"0000000000000000";
        delayMatch1_reg(11) <= X"0000000000000000";
        delayMatch1_reg(12) <= X"0000000000000000";
        delayMatch1_reg(13) <= X"0000000000000000";
        delayMatch1_reg(14) <= X"0000000000000000";
        delayMatch1_reg(15) <= X"0000000000000000";
        delayMatch1_reg(16) <= X"0000000000000000";
        delayMatch1_reg(17) <= X"0000000000000000";
        delayMatch1_reg(18) <= X"0000000000000000";
        delayMatch1_reg(19) <= X"0000000000000000";
        delayMatch1_reg(20) <= X"0000000000000000";
        delayMatch1_reg(21) <= X"0000000000000000";
        delayMatch1_reg(22) <= X"0000000000000000";
        delayMatch1_reg(23) <= X"0000000000000000";
        delayMatch1_reg(24) <= X"0000000000000000";
        delayMatch1_reg(25) <= X"0000000000000000";
        delayMatch1_reg(26) <= X"0000000000000000";
        delayMatch1_reg(27) <= X"0000000000000000";
        delayMatch1_reg(28) <= X"0000000000000000";
        delayMatch1_reg(29) <= X"0000000000000000";
        delayMatch1_reg(30) <= X"0000000000000000";
        delayMatch1_reg(31) <= X"0000000000000000";
        delayMatch1_reg(32) <= X"0000000000000000";
        delayMatch1_reg(33) <= X"0000000000000000";
        delayMatch1_reg(34) <= X"0000000000000000";
        delayMatch1_reg(35) <= X"0000000000000000";
        delayMatch1_reg(36) <= X"0000000000000000";
        delayMatch1_reg(37) <= X"0000000000000000";
        delayMatch1_reg(38) <= X"0000000000000000";
        delayMatch1_reg(39) <= X"0000000000000000";
        delayMatch1_reg(40) <= X"0000000000000000";
        delayMatch1_reg(41) <= X"0000000000000000";
        delayMatch1_reg(42) <= X"0000000000000000";
        delayMatch1_reg(43) <= X"0000000000000000";
        delayMatch1_reg(44) <= X"0000000000000000";
        delayMatch1_reg(45) <= X"0000000000000000";
        delayMatch1_reg(46) <= X"0000000000000000";
        delayMatch1_reg(47) <= X"0000000000000000";
        delayMatch1_reg(48) <= X"0000000000000000";
        delayMatch1_reg(49) <= X"0000000000000000";
        delayMatch1_reg(50) <= X"0000000000000000";
        delayMatch1_reg(51) <= X"0000000000000000";
        delayMatch1_reg(52) <= X"0000000000000000";
        delayMatch1_reg(53) <= X"0000000000000000";
        delayMatch1_reg(54) <= X"0000000000000000";
        delayMatch1_reg(55) <= X"0000000000000000";
        delayMatch1_reg(56) <= X"0000000000000000";
        delayMatch1_reg(57) <= X"0000000000000000";
        delayMatch1_reg(58) <= X"0000000000000000";
        delayMatch1_reg(59) <= X"0000000000000000";
        delayMatch1_reg(60) <= X"0000000000000000";
        delayMatch1_reg(61) <= X"0000000000000000";
        delayMatch1_reg(62) <= X"0000000000000000";
        delayMatch1_reg(63) <= X"0000000000000000";
        delayMatch1_reg(64) <= X"0000000000000000";
        delayMatch1_reg(65) <= X"0000000000000000";
        delayMatch1_reg(66) <= X"0000000000000000";
        delayMatch1_reg(67) <= X"0000000000000000";
        delayMatch1_reg(68) <= X"0000000000000000";
        delayMatch1_reg(69) <= X"0000000000000000";
        delayMatch1_reg(70) <= X"0000000000000000";
        delayMatch1_reg(71) <= X"0000000000000000";
        delayMatch1_reg(72) <= X"0000000000000000";
        delayMatch1_reg(73) <= X"0000000000000000";
        delayMatch1_reg(74) <= X"0000000000000000";
        delayMatch1_reg(75) <= X"0000000000000000";
        delayMatch1_reg(76) <= X"0000000000000000";
        delayMatch1_reg(77) <= X"0000000000000000";
        delayMatch1_reg(78) <= X"0000000000000000";
        delayMatch1_reg(79) <= X"0000000000000000";
        delayMatch1_reg(80) <= X"0000000000000000";
        delayMatch1_reg(81) <= X"0000000000000000";
        delayMatch1_reg(82) <= X"0000000000000000";
        delayMatch1_reg(83) <= X"0000000000000000";
        delayMatch1_reg(84) <= X"0000000000000000";
        delayMatch1_reg(85) <= X"0000000000000000";
        delayMatch1_reg(86) <= X"0000000000000000";
        delayMatch1_reg(87) <= X"0000000000000000";
        delayMatch1_reg(88) <= X"0000000000000000";
        delayMatch1_reg(89) <= X"0000000000000000";
        delayMatch1_reg(90) <= X"0000000000000000";
        delayMatch1_reg(91) <= X"0000000000000000";
        delayMatch1_reg(92) <= X"0000000000000000";
        delayMatch1_reg(93) <= X"0000000000000000";
        delayMatch1_reg(94) <= X"0000000000000000";
        delayMatch1_reg(95) <= X"0000000000000000";
        delayMatch1_reg(96) <= X"0000000000000000";
        delayMatch1_reg(97) <= X"0000000000000000";
        delayMatch1_reg(98) <= X"0000000000000000";
        delayMatch1_reg(99) <= X"0000000000000000";
        delayMatch1_reg(100) <= X"0000000000000000";
        delayMatch1_reg(101) <= X"0000000000000000";
        delayMatch1_reg(102) <= X"0000000000000000";
        delayMatch1_reg(103) <= X"0000000000000000";
        delayMatch1_reg(104) <= X"0000000000000000";
        delayMatch1_reg(105) <= X"0000000000000000";
        delayMatch1_reg(106) <= X"0000000000000000";
        delayMatch1_reg(107) <= X"0000000000000000";
        delayMatch1_reg(108) <= X"0000000000000000";
        delayMatch1_reg(109) <= X"0000000000000000";
        delayMatch1_reg(110) <= X"0000000000000000";
        delayMatch1_reg(111) <= X"0000000000000000";
        delayMatch1_reg(112) <= X"0000000000000000";
        delayMatch1_reg(113) <= X"0000000000000000";
        delayMatch1_reg(114) <= X"0000000000000000";
        delayMatch1_reg(115) <= X"0000000000000000";
        delayMatch1_reg(116) <= X"0000000000000000";
        delayMatch1_reg(117) <= X"0000000000000000";
        delayMatch1_reg(118) <= X"0000000000000000";
        delayMatch1_reg(119) <= X"0000000000000000";
        delayMatch1_reg(120) <= X"0000000000000000";
        delayMatch1_reg(121) <= X"0000000000000000";
        delayMatch1_reg(122) <= X"0000000000000000";
        delayMatch1_reg(123) <= X"0000000000000000";
        delayMatch1_reg(124) <= X"0000000000000000";
        delayMatch1_reg(125) <= X"0000000000000000";
        delayMatch1_reg(126) <= X"0000000000000000";
        delayMatch1_reg(127) <= X"0000000000000000";
        delayMatch1_reg(128) <= X"0000000000000000";
        delayMatch1_reg(129) <= X"0000000000000000";
        delayMatch1_reg(130) <= X"0000000000000000";
        delayMatch1_reg(131) <= X"0000000000000000";
        delayMatch1_reg(132) <= X"0000000000000000";
        delayMatch1_reg(133) <= X"0000000000000000";
        delayMatch1_reg(134) <= X"0000000000000000";
        delayMatch1_reg(135) <= X"0000000000000000";
        delayMatch1_reg(136) <= X"0000000000000000";
        delayMatch1_reg(137) <= X"0000000000000000";
        delayMatch1_reg(138) <= X"0000000000000000";
        delayMatch1_reg(139) <= X"0000000000000000";
        delayMatch1_reg(140) <= X"0000000000000000";
        delayMatch1_reg(141) <= X"0000000000000000";
        delayMatch1_reg(142) <= X"0000000000000000";
        delayMatch1_reg(143) <= X"0000000000000000";
        delayMatch1_reg(144) <= X"0000000000000000";
        delayMatch1_reg(145) <= X"0000000000000000";
        delayMatch1_reg(146) <= X"0000000000000000";
        delayMatch1_reg(147) <= X"0000000000000000";
        delayMatch1_reg(148) <= X"0000000000000000";
        delayMatch1_reg(149) <= X"0000000000000000";
        delayMatch1_reg(150) <= X"0000000000000000";
        delayMatch1_reg(151) <= X"0000000000000000";
        delayMatch1_reg(152) <= X"0000000000000000";
        delayMatch1_reg(153) <= X"0000000000000000";
        delayMatch1_reg(154) <= X"0000000000000000";
        delayMatch1_reg(155) <= X"0000000000000000";
        delayMatch1_reg(156) <= X"0000000000000000";
        delayMatch1_reg(157) <= X"0000000000000000";
        delayMatch1_reg(158) <= X"0000000000000000";
        delayMatch1_reg(159) <= X"0000000000000000";
      ELSIF enb = '1' THEN
        delayMatch1_reg(0) <= delayMatch1_reg_next(0);
        delayMatch1_reg(1) <= delayMatch1_reg_next(1);
        delayMatch1_reg(2) <= delayMatch1_reg_next(2);
        delayMatch1_reg(3) <= delayMatch1_reg_next(3);
        delayMatch1_reg(4) <= delayMatch1_reg_next(4);
        delayMatch1_reg(5) <= delayMatch1_reg_next(5);
        delayMatch1_reg(6) <= delayMatch1_reg_next(6);
        delayMatch1_reg(7) <= delayMatch1_reg_next(7);
        delayMatch1_reg(8) <= delayMatch1_reg_next(8);
        delayMatch1_reg(9) <= delayMatch1_reg_next(9);
        delayMatch1_reg(10) <= delayMatch1_reg_next(10);
        delayMatch1_reg(11) <= delayMatch1_reg_next(11);
        delayMatch1_reg(12) <= delayMatch1_reg_next(12);
        delayMatch1_reg(13) <= delayMatch1_reg_next(13);
        delayMatch1_reg(14) <= delayMatch1_reg_next(14);
        delayMatch1_reg(15) <= delayMatch1_reg_next(15);
        delayMatch1_reg(16) <= delayMatch1_reg_next(16);
        delayMatch1_reg(17) <= delayMatch1_reg_next(17);
        delayMatch1_reg(18) <= delayMatch1_reg_next(18);
        delayMatch1_reg(19) <= delayMatch1_reg_next(19);
        delayMatch1_reg(20) <= delayMatch1_reg_next(20);
        delayMatch1_reg(21) <= delayMatch1_reg_next(21);
        delayMatch1_reg(22) <= delayMatch1_reg_next(22);
        delayMatch1_reg(23) <= delayMatch1_reg_next(23);
        delayMatch1_reg(24) <= delayMatch1_reg_next(24);
        delayMatch1_reg(25) <= delayMatch1_reg_next(25);
        delayMatch1_reg(26) <= delayMatch1_reg_next(26);
        delayMatch1_reg(27) <= delayMatch1_reg_next(27);
        delayMatch1_reg(28) <= delayMatch1_reg_next(28);
        delayMatch1_reg(29) <= delayMatch1_reg_next(29);
        delayMatch1_reg(30) <= delayMatch1_reg_next(30);
        delayMatch1_reg(31) <= delayMatch1_reg_next(31);
        delayMatch1_reg(32) <= delayMatch1_reg_next(32);
        delayMatch1_reg(33) <= delayMatch1_reg_next(33);
        delayMatch1_reg(34) <= delayMatch1_reg_next(34);
        delayMatch1_reg(35) <= delayMatch1_reg_next(35);
        delayMatch1_reg(36) <= delayMatch1_reg_next(36);
        delayMatch1_reg(37) <= delayMatch1_reg_next(37);
        delayMatch1_reg(38) <= delayMatch1_reg_next(38);
        delayMatch1_reg(39) <= delayMatch1_reg_next(39);
        delayMatch1_reg(40) <= delayMatch1_reg_next(40);
        delayMatch1_reg(41) <= delayMatch1_reg_next(41);
        delayMatch1_reg(42) <= delayMatch1_reg_next(42);
        delayMatch1_reg(43) <= delayMatch1_reg_next(43);
        delayMatch1_reg(44) <= delayMatch1_reg_next(44);
        delayMatch1_reg(45) <= delayMatch1_reg_next(45);
        delayMatch1_reg(46) <= delayMatch1_reg_next(46);
        delayMatch1_reg(47) <= delayMatch1_reg_next(47);
        delayMatch1_reg(48) <= delayMatch1_reg_next(48);
        delayMatch1_reg(49) <= delayMatch1_reg_next(49);
        delayMatch1_reg(50) <= delayMatch1_reg_next(50);
        delayMatch1_reg(51) <= delayMatch1_reg_next(51);
        delayMatch1_reg(52) <= delayMatch1_reg_next(52);
        delayMatch1_reg(53) <= delayMatch1_reg_next(53);
        delayMatch1_reg(54) <= delayMatch1_reg_next(54);
        delayMatch1_reg(55) <= delayMatch1_reg_next(55);
        delayMatch1_reg(56) <= delayMatch1_reg_next(56);
        delayMatch1_reg(57) <= delayMatch1_reg_next(57);
        delayMatch1_reg(58) <= delayMatch1_reg_next(58);
        delayMatch1_reg(59) <= delayMatch1_reg_next(59);
        delayMatch1_reg(60) <= delayMatch1_reg_next(60);
        delayMatch1_reg(61) <= delayMatch1_reg_next(61);
        delayMatch1_reg(62) <= delayMatch1_reg_next(62);
        delayMatch1_reg(63) <= delayMatch1_reg_next(63);
        delayMatch1_reg(64) <= delayMatch1_reg_next(64);
        delayMatch1_reg(65) <= delayMatch1_reg_next(65);
        delayMatch1_reg(66) <= delayMatch1_reg_next(66);
        delayMatch1_reg(67) <= delayMatch1_reg_next(67);
        delayMatch1_reg(68) <= delayMatch1_reg_next(68);
        delayMatch1_reg(69) <= delayMatch1_reg_next(69);
        delayMatch1_reg(70) <= delayMatch1_reg_next(70);
        delayMatch1_reg(71) <= delayMatch1_reg_next(71);
        delayMatch1_reg(72) <= delayMatch1_reg_next(72);
        delayMatch1_reg(73) <= delayMatch1_reg_next(73);
        delayMatch1_reg(74) <= delayMatch1_reg_next(74);
        delayMatch1_reg(75) <= delayMatch1_reg_next(75);
        delayMatch1_reg(76) <= delayMatch1_reg_next(76);
        delayMatch1_reg(77) <= delayMatch1_reg_next(77);
        delayMatch1_reg(78) <= delayMatch1_reg_next(78);
        delayMatch1_reg(79) <= delayMatch1_reg_next(79);
        delayMatch1_reg(80) <= delayMatch1_reg_next(80);
        delayMatch1_reg(81) <= delayMatch1_reg_next(81);
        delayMatch1_reg(82) <= delayMatch1_reg_next(82);
        delayMatch1_reg(83) <= delayMatch1_reg_next(83);
        delayMatch1_reg(84) <= delayMatch1_reg_next(84);
        delayMatch1_reg(85) <= delayMatch1_reg_next(85);
        delayMatch1_reg(86) <= delayMatch1_reg_next(86);
        delayMatch1_reg(87) <= delayMatch1_reg_next(87);
        delayMatch1_reg(88) <= delayMatch1_reg_next(88);
        delayMatch1_reg(89) <= delayMatch1_reg_next(89);
        delayMatch1_reg(90) <= delayMatch1_reg_next(90);
        delayMatch1_reg(91) <= delayMatch1_reg_next(91);
        delayMatch1_reg(92) <= delayMatch1_reg_next(92);
        delayMatch1_reg(93) <= delayMatch1_reg_next(93);
        delayMatch1_reg(94) <= delayMatch1_reg_next(94);
        delayMatch1_reg(95) <= delayMatch1_reg_next(95);
        delayMatch1_reg(96) <= delayMatch1_reg_next(96);
        delayMatch1_reg(97) <= delayMatch1_reg_next(97);
        delayMatch1_reg(98) <= delayMatch1_reg_next(98);
        delayMatch1_reg(99) <= delayMatch1_reg_next(99);
        delayMatch1_reg(100) <= delayMatch1_reg_next(100);
        delayMatch1_reg(101) <= delayMatch1_reg_next(101);
        delayMatch1_reg(102) <= delayMatch1_reg_next(102);
        delayMatch1_reg(103) <= delayMatch1_reg_next(103);
        delayMatch1_reg(104) <= delayMatch1_reg_next(104);
        delayMatch1_reg(105) <= delayMatch1_reg_next(105);
        delayMatch1_reg(106) <= delayMatch1_reg_next(106);
        delayMatch1_reg(107) <= delayMatch1_reg_next(107);
        delayMatch1_reg(108) <= delayMatch1_reg_next(108);
        delayMatch1_reg(109) <= delayMatch1_reg_next(109);
        delayMatch1_reg(110) <= delayMatch1_reg_next(110);
        delayMatch1_reg(111) <= delayMatch1_reg_next(111);
        delayMatch1_reg(112) <= delayMatch1_reg_next(112);
        delayMatch1_reg(113) <= delayMatch1_reg_next(113);
        delayMatch1_reg(114) <= delayMatch1_reg_next(114);
        delayMatch1_reg(115) <= delayMatch1_reg_next(115);
        delayMatch1_reg(116) <= delayMatch1_reg_next(116);
        delayMatch1_reg(117) <= delayMatch1_reg_next(117);
        delayMatch1_reg(118) <= delayMatch1_reg_next(118);
        delayMatch1_reg(119) <= delayMatch1_reg_next(119);
        delayMatch1_reg(120) <= delayMatch1_reg_next(120);
        delayMatch1_reg(121) <= delayMatch1_reg_next(121);
        delayMatch1_reg(122) <= delayMatch1_reg_next(122);
        delayMatch1_reg(123) <= delayMatch1_reg_next(123);
        delayMatch1_reg(124) <= delayMatch1_reg_next(124);
        delayMatch1_reg(125) <= delayMatch1_reg_next(125);
        delayMatch1_reg(126) <= delayMatch1_reg_next(126);
        delayMatch1_reg(127) <= delayMatch1_reg_next(127);
        delayMatch1_reg(128) <= delayMatch1_reg_next(128);
        delayMatch1_reg(129) <= delayMatch1_reg_next(129);
        delayMatch1_reg(130) <= delayMatch1_reg_next(130);
        delayMatch1_reg(131) <= delayMatch1_reg_next(131);
        delayMatch1_reg(132) <= delayMatch1_reg_next(132);
        delayMatch1_reg(133) <= delayMatch1_reg_next(133);
        delayMatch1_reg(134) <= delayMatch1_reg_next(134);
        delayMatch1_reg(135) <= delayMatch1_reg_next(135);
        delayMatch1_reg(136) <= delayMatch1_reg_next(136);
        delayMatch1_reg(137) <= delayMatch1_reg_next(137);
        delayMatch1_reg(138) <= delayMatch1_reg_next(138);
        delayMatch1_reg(139) <= delayMatch1_reg_next(139);
        delayMatch1_reg(140) <= delayMatch1_reg_next(140);
        delayMatch1_reg(141) <= delayMatch1_reg_next(141);
        delayMatch1_reg(142) <= delayMatch1_reg_next(142);
        delayMatch1_reg(143) <= delayMatch1_reg_next(143);
        delayMatch1_reg(144) <= delayMatch1_reg_next(144);
        delayMatch1_reg(145) <= delayMatch1_reg_next(145);
        delayMatch1_reg(146) <= delayMatch1_reg_next(146);
        delayMatch1_reg(147) <= delayMatch1_reg_next(147);
        delayMatch1_reg(148) <= delayMatch1_reg_next(148);
        delayMatch1_reg(149) <= delayMatch1_reg_next(149);
        delayMatch1_reg(150) <= delayMatch1_reg_next(150);
        delayMatch1_reg(151) <= delayMatch1_reg_next(151);
        delayMatch1_reg(152) <= delayMatch1_reg_next(152);
        delayMatch1_reg(153) <= delayMatch1_reg_next(153);
        delayMatch1_reg(154) <= delayMatch1_reg_next(154);
        delayMatch1_reg(155) <= delayMatch1_reg_next(155);
        delayMatch1_reg(156) <= delayMatch1_reg_next(156);
        delayMatch1_reg(157) <= delayMatch1_reg_next(157);
        delayMatch1_reg(158) <= delayMatch1_reg_next(158);
        delayMatch1_reg(159) <= delayMatch1_reg_next(159);
      END IF;
    END IF;
  END PROCESS delayMatch1_process;

  Delay1_delOut_1 <= delayMatch1_reg(159);
  delayMatch1_reg_next(0) <= Delay1_delOut;
  delayMatch1_reg_next(1) <= delayMatch1_reg(0);
  delayMatch1_reg_next(2) <= delayMatch1_reg(1);
  delayMatch1_reg_next(3) <= delayMatch1_reg(2);
  delayMatch1_reg_next(4) <= delayMatch1_reg(3);
  delayMatch1_reg_next(5) <= delayMatch1_reg(4);
  delayMatch1_reg_next(6) <= delayMatch1_reg(5);
  delayMatch1_reg_next(7) <= delayMatch1_reg(6);
  delayMatch1_reg_next(8) <= delayMatch1_reg(7);
  delayMatch1_reg_next(9) <= delayMatch1_reg(8);
  delayMatch1_reg_next(10) <= delayMatch1_reg(9);
  delayMatch1_reg_next(11) <= delayMatch1_reg(10);
  delayMatch1_reg_next(12) <= delayMatch1_reg(11);
  delayMatch1_reg_next(13) <= delayMatch1_reg(12);
  delayMatch1_reg_next(14) <= delayMatch1_reg(13);
  delayMatch1_reg_next(15) <= delayMatch1_reg(14);
  delayMatch1_reg_next(16) <= delayMatch1_reg(15);
  delayMatch1_reg_next(17) <= delayMatch1_reg(16);
  delayMatch1_reg_next(18) <= delayMatch1_reg(17);
  delayMatch1_reg_next(19) <= delayMatch1_reg(18);
  delayMatch1_reg_next(20) <= delayMatch1_reg(19);
  delayMatch1_reg_next(21) <= delayMatch1_reg(20);
  delayMatch1_reg_next(22) <= delayMatch1_reg(21);
  delayMatch1_reg_next(23) <= delayMatch1_reg(22);
  delayMatch1_reg_next(24) <= delayMatch1_reg(23);
  delayMatch1_reg_next(25) <= delayMatch1_reg(24);
  delayMatch1_reg_next(26) <= delayMatch1_reg(25);
  delayMatch1_reg_next(27) <= delayMatch1_reg(26);
  delayMatch1_reg_next(28) <= delayMatch1_reg(27);
  delayMatch1_reg_next(29) <= delayMatch1_reg(28);
  delayMatch1_reg_next(30) <= delayMatch1_reg(29);
  delayMatch1_reg_next(31) <= delayMatch1_reg(30);
  delayMatch1_reg_next(32) <= delayMatch1_reg(31);
  delayMatch1_reg_next(33) <= delayMatch1_reg(32);
  delayMatch1_reg_next(34) <= delayMatch1_reg(33);
  delayMatch1_reg_next(35) <= delayMatch1_reg(34);
  delayMatch1_reg_next(36) <= delayMatch1_reg(35);
  delayMatch1_reg_next(37) <= delayMatch1_reg(36);
  delayMatch1_reg_next(38) <= delayMatch1_reg(37);
  delayMatch1_reg_next(39) <= delayMatch1_reg(38);
  delayMatch1_reg_next(40) <= delayMatch1_reg(39);
  delayMatch1_reg_next(41) <= delayMatch1_reg(40);
  delayMatch1_reg_next(42) <= delayMatch1_reg(41);
  delayMatch1_reg_next(43) <= delayMatch1_reg(42);
  delayMatch1_reg_next(44) <= delayMatch1_reg(43);
  delayMatch1_reg_next(45) <= delayMatch1_reg(44);
  delayMatch1_reg_next(46) <= delayMatch1_reg(45);
  delayMatch1_reg_next(47) <= delayMatch1_reg(46);
  delayMatch1_reg_next(48) <= delayMatch1_reg(47);
  delayMatch1_reg_next(49) <= delayMatch1_reg(48);
  delayMatch1_reg_next(50) <= delayMatch1_reg(49);
  delayMatch1_reg_next(51) <= delayMatch1_reg(50);
  delayMatch1_reg_next(52) <= delayMatch1_reg(51);
  delayMatch1_reg_next(53) <= delayMatch1_reg(52);
  delayMatch1_reg_next(54) <= delayMatch1_reg(53);
  delayMatch1_reg_next(55) <= delayMatch1_reg(54);
  delayMatch1_reg_next(56) <= delayMatch1_reg(55);
  delayMatch1_reg_next(57) <= delayMatch1_reg(56);
  delayMatch1_reg_next(58) <= delayMatch1_reg(57);
  delayMatch1_reg_next(59) <= delayMatch1_reg(58);
  delayMatch1_reg_next(60) <= delayMatch1_reg(59);
  delayMatch1_reg_next(61) <= delayMatch1_reg(60);
  delayMatch1_reg_next(62) <= delayMatch1_reg(61);
  delayMatch1_reg_next(63) <= delayMatch1_reg(62);
  delayMatch1_reg_next(64) <= delayMatch1_reg(63);
  delayMatch1_reg_next(65) <= delayMatch1_reg(64);
  delayMatch1_reg_next(66) <= delayMatch1_reg(65);
  delayMatch1_reg_next(67) <= delayMatch1_reg(66);
  delayMatch1_reg_next(68) <= delayMatch1_reg(67);
  delayMatch1_reg_next(69) <= delayMatch1_reg(68);
  delayMatch1_reg_next(70) <= delayMatch1_reg(69);
  delayMatch1_reg_next(71) <= delayMatch1_reg(70);
  delayMatch1_reg_next(72) <= delayMatch1_reg(71);
  delayMatch1_reg_next(73) <= delayMatch1_reg(72);
  delayMatch1_reg_next(74) <= delayMatch1_reg(73);
  delayMatch1_reg_next(75) <= delayMatch1_reg(74);
  delayMatch1_reg_next(76) <= delayMatch1_reg(75);
  delayMatch1_reg_next(77) <= delayMatch1_reg(76);
  delayMatch1_reg_next(78) <= delayMatch1_reg(77);
  delayMatch1_reg_next(79) <= delayMatch1_reg(78);
  delayMatch1_reg_next(80) <= delayMatch1_reg(79);
  delayMatch1_reg_next(81) <= delayMatch1_reg(80);
  delayMatch1_reg_next(82) <= delayMatch1_reg(81);
  delayMatch1_reg_next(83) <= delayMatch1_reg(82);
  delayMatch1_reg_next(84) <= delayMatch1_reg(83);
  delayMatch1_reg_next(85) <= delayMatch1_reg(84);
  delayMatch1_reg_next(86) <= delayMatch1_reg(85);
  delayMatch1_reg_next(87) <= delayMatch1_reg(86);
  delayMatch1_reg_next(88) <= delayMatch1_reg(87);
  delayMatch1_reg_next(89) <= delayMatch1_reg(88);
  delayMatch1_reg_next(90) <= delayMatch1_reg(89);
  delayMatch1_reg_next(91) <= delayMatch1_reg(90);
  delayMatch1_reg_next(92) <= delayMatch1_reg(91);
  delayMatch1_reg_next(93) <= delayMatch1_reg(92);
  delayMatch1_reg_next(94) <= delayMatch1_reg(93);
  delayMatch1_reg_next(95) <= delayMatch1_reg(94);
  delayMatch1_reg_next(96) <= delayMatch1_reg(95);
  delayMatch1_reg_next(97) <= delayMatch1_reg(96);
  delayMatch1_reg_next(98) <= delayMatch1_reg(97);
  delayMatch1_reg_next(99) <= delayMatch1_reg(98);
  delayMatch1_reg_next(100) <= delayMatch1_reg(99);
  delayMatch1_reg_next(101) <= delayMatch1_reg(100);
  delayMatch1_reg_next(102) <= delayMatch1_reg(101);
  delayMatch1_reg_next(103) <= delayMatch1_reg(102);
  delayMatch1_reg_next(104) <= delayMatch1_reg(103);
  delayMatch1_reg_next(105) <= delayMatch1_reg(104);
  delayMatch1_reg_next(106) <= delayMatch1_reg(105);
  delayMatch1_reg_next(107) <= delayMatch1_reg(106);
  delayMatch1_reg_next(108) <= delayMatch1_reg(107);
  delayMatch1_reg_next(109) <= delayMatch1_reg(108);
  delayMatch1_reg_next(110) <= delayMatch1_reg(109);
  delayMatch1_reg_next(111) <= delayMatch1_reg(110);
  delayMatch1_reg_next(112) <= delayMatch1_reg(111);
  delayMatch1_reg_next(113) <= delayMatch1_reg(112);
  delayMatch1_reg_next(114) <= delayMatch1_reg(113);
  delayMatch1_reg_next(115) <= delayMatch1_reg(114);
  delayMatch1_reg_next(116) <= delayMatch1_reg(115);
  delayMatch1_reg_next(117) <= delayMatch1_reg(116);
  delayMatch1_reg_next(118) <= delayMatch1_reg(117);
  delayMatch1_reg_next(119) <= delayMatch1_reg(118);
  delayMatch1_reg_next(120) <= delayMatch1_reg(119);
  delayMatch1_reg_next(121) <= delayMatch1_reg(120);
  delayMatch1_reg_next(122) <= delayMatch1_reg(121);
  delayMatch1_reg_next(123) <= delayMatch1_reg(122);
  delayMatch1_reg_next(124) <= delayMatch1_reg(123);
  delayMatch1_reg_next(125) <= delayMatch1_reg(124);
  delayMatch1_reg_next(126) <= delayMatch1_reg(125);
  delayMatch1_reg_next(127) <= delayMatch1_reg(126);
  delayMatch1_reg_next(128) <= delayMatch1_reg(127);
  delayMatch1_reg_next(129) <= delayMatch1_reg(128);
  delayMatch1_reg_next(130) <= delayMatch1_reg(129);
  delayMatch1_reg_next(131) <= delayMatch1_reg(130);
  delayMatch1_reg_next(132) <= delayMatch1_reg(131);
  delayMatch1_reg_next(133) <= delayMatch1_reg(132);
  delayMatch1_reg_next(134) <= delayMatch1_reg(133);
  delayMatch1_reg_next(135) <= delayMatch1_reg(134);
  delayMatch1_reg_next(136) <= delayMatch1_reg(135);
  delayMatch1_reg_next(137) <= delayMatch1_reg(136);
  delayMatch1_reg_next(138) <= delayMatch1_reg(137);
  delayMatch1_reg_next(139) <= delayMatch1_reg(138);
  delayMatch1_reg_next(140) <= delayMatch1_reg(139);
  delayMatch1_reg_next(141) <= delayMatch1_reg(140);
  delayMatch1_reg_next(142) <= delayMatch1_reg(141);
  delayMatch1_reg_next(143) <= delayMatch1_reg(142);
  delayMatch1_reg_next(144) <= delayMatch1_reg(143);
  delayMatch1_reg_next(145) <= delayMatch1_reg(144);
  delayMatch1_reg_next(146) <= delayMatch1_reg(145);
  delayMatch1_reg_next(147) <= delayMatch1_reg(146);
  delayMatch1_reg_next(148) <= delayMatch1_reg(147);
  delayMatch1_reg_next(149) <= delayMatch1_reg(148);
  delayMatch1_reg_next(150) <= delayMatch1_reg(149);
  delayMatch1_reg_next(151) <= delayMatch1_reg(150);
  delayMatch1_reg_next(152) <= delayMatch1_reg(151);
  delayMatch1_reg_next(153) <= delayMatch1_reg(152);
  delayMatch1_reg_next(154) <= delayMatch1_reg(153);
  delayMatch1_reg_next(155) <= delayMatch1_reg(154);
  delayMatch1_reg_next(156) <= delayMatch1_reg(155);
  delayMatch1_reg_next(157) <= delayMatch1_reg(156);
  delayMatch1_reg_next(158) <= delayMatch1_reg(157);
  delayMatch1_reg_next(159) <= delayMatch1_reg(158);

  
  Delay1_out1 <= Delay1_delOut_1 WHEN reset_1 = '0' ELSE
      Delay1_iv;

  delayMatch2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch2_reg(0) <= X"00000000";
        delayMatch2_reg(1) <= X"00000000";
        delayMatch2_reg(2) <= X"00000000";
        delayMatch2_reg(3) <= X"00000000";
        delayMatch2_reg(4) <= X"00000000";
        delayMatch2_reg(5) <= X"00000000";
        delayMatch2_reg(6) <= X"00000000";
        delayMatch2_reg(7) <= X"00000000";
        delayMatch2_reg(8) <= X"00000000";
        delayMatch2_reg(9) <= X"00000000";
        delayMatch2_reg(10) <= X"00000000";
        delayMatch2_reg(11) <= X"00000000";
        delayMatch2_reg(12) <= X"00000000";
        delayMatch2_reg(13) <= X"00000000";
        delayMatch2_reg(14) <= X"00000000";
        delayMatch2_reg(15) <= X"00000000";
        delayMatch2_reg(16) <= X"00000000";
        delayMatch2_reg(17) <= X"00000000";
        delayMatch2_reg(18) <= X"00000000";
      ELSIF enb = '1' THEN
        delayMatch2_reg(0) <= delayMatch2_reg_next(0);
        delayMatch2_reg(1) <= delayMatch2_reg_next(1);
        delayMatch2_reg(2) <= delayMatch2_reg_next(2);
        delayMatch2_reg(3) <= delayMatch2_reg_next(3);
        delayMatch2_reg(4) <= delayMatch2_reg_next(4);
        delayMatch2_reg(5) <= delayMatch2_reg_next(5);
        delayMatch2_reg(6) <= delayMatch2_reg_next(6);
        delayMatch2_reg(7) <= delayMatch2_reg_next(7);
        delayMatch2_reg(8) <= delayMatch2_reg_next(8);
        delayMatch2_reg(9) <= delayMatch2_reg_next(9);
        delayMatch2_reg(10) <= delayMatch2_reg_next(10);
        delayMatch2_reg(11) <= delayMatch2_reg_next(11);
        delayMatch2_reg(12) <= delayMatch2_reg_next(12);
        delayMatch2_reg(13) <= delayMatch2_reg_next(13);
        delayMatch2_reg(14) <= delayMatch2_reg_next(14);
        delayMatch2_reg(15) <= delayMatch2_reg_next(15);
        delayMatch2_reg(16) <= delayMatch2_reg_next(16);
        delayMatch2_reg(17) <= delayMatch2_reg_next(17);
        delayMatch2_reg(18) <= delayMatch2_reg_next(18);
      END IF;
    END IF;
  END PROCESS delayMatch2_process;

  theta_el <= delayMatch2_reg(18);
  delayMatch2_reg_next(0) <= theta_el_1;
  delayMatch2_reg_next(1) <= delayMatch2_reg(0);
  delayMatch2_reg_next(2) <= delayMatch2_reg(1);
  delayMatch2_reg_next(3) <= delayMatch2_reg(2);
  delayMatch2_reg_next(4) <= delayMatch2_reg(3);
  delayMatch2_reg_next(5) <= delayMatch2_reg(4);
  delayMatch2_reg_next(6) <= delayMatch2_reg(5);
  delayMatch2_reg_next(7) <= delayMatch2_reg(6);
  delayMatch2_reg_next(8) <= delayMatch2_reg(7);
  delayMatch2_reg_next(9) <= delayMatch2_reg(8);
  delayMatch2_reg_next(10) <= delayMatch2_reg(9);
  delayMatch2_reg_next(11) <= delayMatch2_reg(10);
  delayMatch2_reg_next(12) <= delayMatch2_reg(11);
  delayMatch2_reg_next(13) <= delayMatch2_reg(12);
  delayMatch2_reg_next(14) <= delayMatch2_reg(13);
  delayMatch2_reg_next(15) <= delayMatch2_reg(14);
  delayMatch2_reg_next(16) <= delayMatch2_reg(15);
  delayMatch2_reg_next(17) <= delayMatch2_reg(16);
  delayMatch2_reg_next(18) <= delayMatch2_reg(17);

END rtl;
