-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\FCS_MPC_3Phase_SPMSM\hdlsrc\FCS_MPC_3Phase_SPMSM_TEST1\FCS_MPC_3Phase_SPMSM_IP_Core_src_Subsystem1.vhd
-- Created: 2022-06-09 10:23:40
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- 
-- -------------------------------------------------------------
-- Rate and Clocking Details
-- -------------------------------------------------------------
-- Model base rate: 1e-08
-- Target subsystem base rate: 1e-08
-- 
-- 
-- Clock Enable  Sample Time
-- -------------------------------------------------------------
-- ce_out        1e-08
-- -------------------------------------------------------------
-- 
-- 
-- Output Signal                 Clock Enable  Sample Time
-- -------------------------------------------------------------
-- Index                         ce_out        1e-08
-- done_MPC                      ce_out        1e-08
-- -------------------------------------------------------------
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: FCS_MPC_3Phase_SPMSM_IP_Core_src_Subsystem1
-- Source Path: FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.FCS_MPC_3Phase_SPMSM_IP_Core_src_Subsystem1_pkg.ALL;

ENTITY FCS_MPC_3Phase_SPMSM_IP_Core_src_Subsystem1 IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        clk_enable                        :   IN    std_logic;
        dq_Done_123_alphabeta_dq          :   IN    std_logic;
        ialpha                            :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ibeta                             :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        u_dc_link_AXI                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        SampleTime_AXI                    :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        theta_el                          :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        omega_m                           :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        Rs_AXI                            :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Ld_AXI                            :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        Lq_AXI                            :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        psiPM_AXI                         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ialpha_ref                        :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ibeta_ref                         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ce_out                            :   OUT   std_logic;
        Index                             :   OUT   std_logic_vector(31 DOWNTO 0);  -- int32
        done_MPC                          :   OUT   std_logic
        );
END FCS_MPC_3Phase_SPMSM_IP_Core_src_Subsystem1;


ARCHITECTURE rtl OF FCS_MPC_3Phase_SPMSM_IP_Core_src_Subsystem1 IS

  -- Component Declarations
  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT( nfp_in                          :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_48_En31_to_single
    PORT( nfp_in                          :   IN    std_logic_vector(47 DOWNTO 0);  -- sfix48_En31
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_24_En20_to_single
    PORT( nfp_in                          :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double2single
    PORT( nfp_in                          :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function
    PORT( u_dc_link                       :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          i_ph_ctrl_alpha                 :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          i_ph_ctrl_beta                  :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          omega_el                        :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          theta_el                        :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          Rs                              :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          Ls                              :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          psiPM                           :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          ialpha_ref                      :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          ibeta_ref                       :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          SampleTime                      :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          vk                              :   IN    vector_of_std_logic_vector32(0 TO 1);  -- single [2]
          J                               :   OUT   vector_of_std_logic_vector64(0 TO 7);  -- double [8]
          v                               :   OUT   matrix_of_std_logic_vector32(0 TO 1, 0 TO 7)  -- single [2x8]
          );
  END COMPONENT;

  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function1
    PORT( J                               :   IN    vector_of_std_logic_vector64(0 TO 7);  -- double [8]
          v                               :   IN    matrix_of_std_logic_vector32(0 TO 1, 0 TO 7);  -- single [2x8]
          I                               :   OUT   std_logic_vector(63 DOWNTO 0);  -- double
          v_opt                           :   OUT   vector_of_std_logic_vector64(0 TO 1)  -- double [2]
          );
  END COMPONENT;

  COMPONENT FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_32_En0
    PORT( nfp_in                          :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- int32
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single(rtl);

  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_48_En31_to_single
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_48_En31_to_single(rtl);

  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_24_En20_to_single
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_24_En20_to_single(rtl);

  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double2single
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double2single(rtl);

  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function(rtl);

  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function1
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function1(rtl);

  FOR ALL : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_32_En0
    USE ENTITY work.FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_32_En0(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL alpha1_for_one_cycle_if_edge_recognized : signed(7 DOWNTO 0);  -- int8
  SIGNAL reset_old2_out1                  : std_logic;
  SIGNAL reset_old_switch1_out1           : std_logic;
  SIGNAL Detec_edge_sub_cast              : signed(7 DOWNTO 0);  -- sfix8
  SIGNAL Detec_edge_sub_cast_1            : signed(7 DOWNTO 0);  -- sfix8
  SIGNAL dtc_out                          : std_logic;  -- ufix1
  SIGNAL Saturation_out1                  : std_logic;  -- ufix1
  SIGNAL DelayValid_reg                   : std_logic_vector(0 TO 4);  -- ufix1 [5]
  SIGNAL DelayValid_reg_next              : std_logic_vector(0 TO 4);  -- ufix1 [5]
  SIGNAL End_Cycle                        : std_logic;  -- ufix1
  SIGNAL mpc                              : std_logic;
  SIGNAL alpha1_for_one_cycle_if_edge_recognized_1 : signed(7 DOWNTO 0);  -- int8
  SIGNAL reset_old1_out1                  : std_logic;
  SIGNAL reset_old_switch2_out1           : std_logic;
  SIGNAL Detec_edge1_sub_cast             : signed(7 DOWNTO 0);  -- sfix8
  SIGNAL Detec_edge1_sub_cast_1           : signed(7 DOWNTO 0);  -- sfix8
  SIGNAL dtc_out_1                        : std_logic;  -- ufix1
  SIGNAL Saturation1_out1                 : std_logic;  -- ufix1
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL switch_compare_1_1               : std_logic;
  SIGNAL Data_Type_Conversion1_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on2_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay2_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_2               : std_logic;
  SIGNAL nfp_out_1_1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on1_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay1_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_3               : std_logic;
  SIGNAL nfp_out_2_1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on3_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay3_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_4               : std_logic;
  SIGNAL omega_m_signed                   : signed(23 DOWNTO 0);  -- sfix24_En11
  SIGNAL omega_el                         : signed(47 DOWNTO 0);  -- sfix48_En31
  SIGNAL Data_Type_Conversion5_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on4_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay4_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_5               : std_logic;
  SIGNAL Data_Type_Conversion4_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on5_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay5_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_6               : std_logic;
  SIGNAL Data_Type_Conversion6_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on6_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay6_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_7               : std_logic;
  SIGNAL Ld_AXI_signed                    : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL Lq_AXI_signed                    : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL Add_out1                         : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL Gain1_cast                       : signed(47 DOWNTO 0);  -- sfix48_En43
  SIGNAL Gain1_out1                       : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL Data_Type_Conversion7_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on7_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay7_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_8               : std_logic;
  SIGNAL Data_Type_Conversion8_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on9_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay9_out1                      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_9               : std_logic;
  SIGNAL Data_Type_Conversion12_out1      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on10_out1                 : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay10_out1                     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_10              : std_logic;
  SIGNAL Data_Type_Conversion2_out1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on11_out1                 : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay11_out1                     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_11              : std_logic;
  SIGNAL Data_Type_Conversion20_out1      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Switch_on12_out1                 : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Delay12_out1                     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL switch_compare_1_12              : std_logic;
  SIGNAL switch_compare_1_13              : std_logic;
  SIGNAL v                                : matrix_of_std_logic_vector32(0 TO 1, 0 TO 7);  -- ufix32 [2x8]
  SIGNAL c161_v                           : vector_of_std_logic_vector32(0 TO 15);  -- ufix32 [16]
  SIGNAL Switch_on14_out1                 : matrix_of_std_logic_vector32(0 TO 1, 0 TO 7);  -- ufix32 [2x8]
  SIGNAL c73_Switch_on14_out1             : vector_of_std_logic_vector32(0 TO 15);  -- ufix32 [16]
  SIGNAL Delay14_reg                      : vector_of_std_logic_vector32(0 TO 15);  -- ufix32 [16]
  SIGNAL Delay14_reg_next                 : vector_of_std_logic_vector32(0 TO 15);  -- ufix32 [16]
  SIGNAL c73_Delay14_out1                 : vector_of_std_logic_vector32(0 TO 15);  -- ufix32 [16]
  SIGNAL c161_Switch_on14_out1            : vector_of_std_logic_vector32(0 TO 15);  -- ufix32 [16]
  SIGNAL DelayValue1_out1                 : vector_of_std_logic_vector64(0 TO 1);  -- ufix64 [2]
  SIGNAL v_opt                            : vector_of_std_logic_vector64(0 TO 1);  -- ufix64 [2]
  SIGNAL Data_Type_Conversion9_out1       : vector_of_std_logic_vector32(0 TO 1);  -- ufix32 [2]
  SIGNAL Switch_on13_out1                 : vector_of_std_logic_vector32(0 TO 1);  -- ufix32 [2]
  SIGNAL Delay13_out1                     : vector_of_std_logic_vector32(0 TO 1);  -- ufix32 [2]
  SIGNAL J                                : vector_of_std_logic_vector64(0 TO 7);  -- ufix64 [8]
  SIGNAL Switch_on15_out1                 : vector_of_std_logic_vector64(0 TO 7);  -- ufix64 [8]
  SIGNAL Delay15_out1                     : vector_of_std_logic_vector64(0 TO 7);  -- ufix64 [8]
  SIGNAL I                                : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Data_Type_Conversion10_out1      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL DelayValid1_reg                  : std_logic_vector(0 TO 3);  -- ufix1 [4]
  SIGNAL DelayValid1_reg_next             : std_logic_vector(0 TO 3);  -- ufix1 [4]
  SIGNAL End_Cycle_1                      : std_logic;  -- ufix1
  SIGNAL index_1                          : std_logic;

BEGIN
  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => u_dc_link_AXI,  -- sfix18_En11
              nfp_out => Data_Type_Conversion1_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single_1 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => ialpha,  -- sfix18_En11
              nfp_out => nfp_out_1_1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single_2 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => ibeta,  -- sfix18_En11
              nfp_out => nfp_out_2_1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_48_En31_to_single : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_48_En31_to_single
    PORT MAP( nfp_in => std_logic_vector(omega_el),  -- sfix48_En31
              nfp_out => Data_Type_Conversion5_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_24_En20_to_single : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_24_En20_to_single
    PORT MAP( nfp_in => theta_el,  -- sfix24_En20
              nfp_out => Data_Type_Conversion4_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single_3 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => Rs_AXI,  -- sfix18_En11
              nfp_out => Data_Type_Conversion6_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_24_En20_to_single_1 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_24_En20_to_single
    PORT MAP( nfp_in => std_logic_vector(Gain1_out1),  -- sfix24_En20
              nfp_out => Data_Type_Conversion7_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single_4 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => psiPM_AXI,  -- sfix18_En11
              nfp_out => Data_Type_Conversion8_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single_5 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => ialpha_ref,  -- sfix18_En11
              nfp_out => Data_Type_Conversion12_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_18_En11_to_single_6 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_18_En11_to_single
    PORT MAP( nfp_in => ibeta_ref,  -- sfix18_En11
              nfp_out => Data_Type_Conversion2_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_sfix_24_En20_to_single_2 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_sfix_24_En20_to_single
    PORT MAP( nfp_in => SampleTime_AXI,  -- sfix24_En20
              nfp_out => Data_Type_Conversion20_out1  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_double2single : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double2single
    PORT MAP( nfp_in => DelayValue1_out1(1),  -- double
              nfp_out => Data_Type_Conversion9_out1(1)  -- single
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_double2single_1 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double2single
    PORT MAP( nfp_in => DelayValue1_out1(0),  -- double
              nfp_out => Data_Type_Conversion9_out1(0)  -- single
              );

  u_MATLAB_Function : FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function
    PORT MAP( u_dc_link => Switch_on2_out1,  -- single
              i_ph_ctrl_alpha => Switch_on1_out1,  -- single
              i_ph_ctrl_beta => Switch_on3_out1,  -- single
              omega_el => Switch_on4_out1,  -- single
              theta_el => Switch_on5_out1,  -- single
              Rs => Switch_on6_out1,  -- single
              Ls => Switch_on7_out1,  -- single
              psiPM => Switch_on9_out1,  -- single
              ialpha_ref => Switch_on10_out1,  -- single
              ibeta_ref => Switch_on11_out1,  -- single
              SampleTime => Switch_on12_out1,  -- single
              vk => Switch_on13_out1,  -- single [2]
              J => J,  -- double [8]
              v => v  -- single [2x8]
              );

  u_MATLAB_Function1 : FCS_MPC_3Phase_SPMSM_IP_Core_src_MATLAB_Function1
    PORT MAP( J => Switch_on15_out1,  -- double [8]
              v => Switch_on14_out1,  -- single [2x8]
              I => I,  -- double
              v_opt => v_opt  -- double [2]
              );

  u_FCS_MPC_3Phase_SPMSM_TEST1_Microcontroller_Software_Subsystem1_nfp_convert_double_to_fixed_32_En0 : FCS_MPC_3Phase_SPMSM_IP_Core_src_nfp_convert_double_to_fixed_32_En0
    PORT MAP( nfp_in => I,  -- double
              nfp_out => Data_Type_Conversion10_out1  -- int32
              );

  enb <= clk_enable;

  
  reset_old_switch1_out1 <= reset_old2_out1 WHEN alpha1_for_one_cycle_if_edge_recognized = to_signed(16#00#, 8) ELSE
      dq_Done_123_alphabeta_dq;

  reset_old2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        reset_old2_out1 <= '0';
      ELSIF enb = '1' THEN
        reset_old2_out1 <= reset_old_switch1_out1;
      END IF;
    END IF;
  END PROCESS reset_old2_process;


  Detec_edge_sub_cast <= '0' & '0' & '0' & '0' & '0' & '0' & '0' & dq_Done_123_alphabeta_dq;
  Detec_edge_sub_cast_1 <= '0' & '0' & '0' & '0' & '0' & '0' & '0' & reset_old2_out1;
  alpha1_for_one_cycle_if_edge_recognized <= Detec_edge_sub_cast - Detec_edge_sub_cast_1;

  
  dtc_out <= '1' WHEN (alpha1_for_one_cycle_if_edge_recognized(7) = '0') AND (alpha1_for_one_cycle_if_edge_recognized(6 DOWNTO 1) /= "000000") ELSE
      '0' WHEN alpha1_for_one_cycle_if_edge_recognized(7) = '1' ELSE
      alpha1_for_one_cycle_if_edge_recognized(0);

  Saturation_out1 <= dtc_out;

  DelayValid_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        DelayValid_reg(0) <= '0';
        DelayValid_reg(1) <= '0';
        DelayValid_reg(2) <= '0';
        DelayValid_reg(3) <= '0';
        DelayValid_reg(4) <= '0';
      ELSIF enb = '1' THEN
        DelayValid_reg(0) <= DelayValid_reg_next(0);
        DelayValid_reg(1) <= DelayValid_reg_next(1);
        DelayValid_reg(2) <= DelayValid_reg_next(2);
        DelayValid_reg(3) <= DelayValid_reg_next(3);
        DelayValid_reg(4) <= DelayValid_reg_next(4);
      END IF;
    END IF;
  END PROCESS DelayValid_process;

  End_Cycle <= DelayValid_reg(4);
  DelayValid_reg_next(0) <= Saturation_out1;
  DelayValid_reg_next(1) <= DelayValid_reg(0);
  DelayValid_reg_next(2) <= DelayValid_reg(1);
  DelayValid_reg_next(3) <= DelayValid_reg(2);
  DelayValid_reg_next(4) <= DelayValid_reg(3);

  
  mpc <= '1' WHEN End_Cycle /= '0' ELSE
      '0';

  
  reset_old_switch2_out1 <= reset_old1_out1 WHEN alpha1_for_one_cycle_if_edge_recognized_1 = to_signed(16#00#, 8) ELSE
      mpc;

  reset_old1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        reset_old1_out1 <= '0';
      ELSIF enb = '1' THEN
        reset_old1_out1 <= reset_old_switch2_out1;
      END IF;
    END IF;
  END PROCESS reset_old1_process;


  Detec_edge1_sub_cast <= '0' & '0' & '0' & '0' & '0' & '0' & '0' & mpc;
  Detec_edge1_sub_cast_1 <= '0' & '0' & '0' & '0' & '0' & '0' & '0' & reset_old1_out1;
  alpha1_for_one_cycle_if_edge_recognized_1 <= Detec_edge1_sub_cast - Detec_edge1_sub_cast_1;

  
  dtc_out_1 <= '1' WHEN (alpha1_for_one_cycle_if_edge_recognized_1(7) = '0') AND (alpha1_for_one_cycle_if_edge_recognized_1(6 DOWNTO 1) /= "000000") ELSE
      '0' WHEN alpha1_for_one_cycle_if_edge_recognized_1(7) = '1' ELSE
      alpha1_for_one_cycle_if_edge_recognized_1(0);

  Saturation1_out1 <= dtc_out_1;

  
  switch_compare_1 <= '1' WHEN Saturation1_out1 = '1' ELSE
      '0';

  
  switch_compare_1_1 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay2_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay2_out1 <= Switch_on2_out1;
      END IF;
    END IF;
  END PROCESS Delay2_process;


  
  Switch_on2_out1 <= Delay2_out1 WHEN switch_compare_1_1 = '0' ELSE
      Data_Type_Conversion1_out1;

  
  switch_compare_1_2 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay1_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay1_out1 <= Switch_on1_out1;
      END IF;
    END IF;
  END PROCESS Delay1_process;


  
  Switch_on1_out1 <= Delay1_out1 WHEN switch_compare_1_2 = '0' ELSE
      nfp_out_1_1;

  
  switch_compare_1_3 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay3_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay3_out1 <= Switch_on3_out1;
      END IF;
    END IF;
  END PROCESS Delay3_process;


  
  Switch_on3_out1 <= Delay3_out1 WHEN switch_compare_1_3 = '0' ELSE
      nfp_out_2_1;

  
  switch_compare_1_4 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  omega_m_signed <= signed(omega_m);

  omega_el <= to_signed(16#500000#, 24) * omega_m_signed;

  Delay4_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay4_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay4_out1 <= Switch_on4_out1;
      END IF;
    END IF;
  END PROCESS Delay4_process;


  
  Switch_on4_out1 <= Delay4_out1 WHEN switch_compare_1_4 = '0' ELSE
      Data_Type_Conversion5_out1;

  
  switch_compare_1_5 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay5_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay5_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay5_out1 <= Switch_on5_out1;
      END IF;
    END IF;
  END PROCESS Delay5_process;


  
  Switch_on5_out1 <= Delay5_out1 WHEN switch_compare_1_5 = '0' ELSE
      Data_Type_Conversion4_out1;

  
  switch_compare_1_6 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay6_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay6_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay6_out1 <= Switch_on6_out1;
      END IF;
    END IF;
  END PROCESS Delay6_process;


  
  Switch_on6_out1 <= Delay6_out1 WHEN switch_compare_1_6 = '0' ELSE
      Data_Type_Conversion6_out1;

  
  switch_compare_1_7 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Ld_AXI_signed <= signed(Ld_AXI);

  Lq_AXI_signed <= signed(Lq_AXI);

  Add_out1 <= Ld_AXI_signed + Lq_AXI_signed;

  Gain1_cast <= resize(Add_out1 & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0', 48);
  Gain1_out1 <= Gain1_cast(46 DOWNTO 23);

  Delay7_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay7_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay7_out1 <= Switch_on7_out1;
      END IF;
    END IF;
  END PROCESS Delay7_process;


  
  Switch_on7_out1 <= Delay7_out1 WHEN switch_compare_1_7 = '0' ELSE
      Data_Type_Conversion7_out1;

  
  switch_compare_1_8 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay9_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay9_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay9_out1 <= Switch_on9_out1;
      END IF;
    END IF;
  END PROCESS Delay9_process;


  
  Switch_on9_out1 <= Delay9_out1 WHEN switch_compare_1_8 = '0' ELSE
      Data_Type_Conversion8_out1;

  
  switch_compare_1_9 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay10_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay10_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay10_out1 <= Switch_on10_out1;
      END IF;
    END IF;
  END PROCESS Delay10_process;


  
  Switch_on10_out1 <= Delay10_out1 WHEN switch_compare_1_9 = '0' ELSE
      Data_Type_Conversion12_out1;

  
  switch_compare_1_10 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay11_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay11_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay11_out1 <= Switch_on11_out1;
      END IF;
    END IF;
  END PROCESS Delay11_process;


  
  Switch_on11_out1 <= Delay11_out1 WHEN switch_compare_1_10 = '0' ELSE
      Data_Type_Conversion2_out1;

  
  switch_compare_1_11 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  Delay12_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay12_out1 <= X"00000000";
      ELSIF enb = '1' THEN
        Delay12_out1 <= Switch_on12_out1;
      END IF;
    END IF;
  END PROCESS Delay12_process;


  
  Switch_on12_out1 <= Delay12_out1 WHEN switch_compare_1_11 = '0' ELSE
      Data_Type_Conversion20_out1;

  
  switch_compare_1_12 <= '1' WHEN Saturation_out1 = '1' ELSE
      '0';

  
  switch_compare_1_13 <= '1' WHEN Saturation1_out1 = '1' ELSE
      '0';

  c161_vGEN_LABEL1: FOR d1 IN 0 TO 7 GENERATE
    c161_vGEN_LABEL: FOR d0 IN 0 TO 1 GENERATE
      c161_v(d0 + (d1 * 2)) <= v(d0, d1);
    END GENERATE;
  END GENERATE;

  c73_Switch_on14_out1GEN_LABEL1: FOR d1 IN 0 TO 7 GENERATE
    c73_Switch_on14_out1GEN_LABEL: FOR d0 IN 0 TO 1 GENERATE
      c73_Switch_on14_out1(d0 + (d1 * 2)) <= Switch_on14_out1(d0, d1);
    END GENERATE;
  END GENERATE;

  Delay14_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay14_reg(0) <= X"00000000";
        Delay14_reg(1) <= X"00000000";
        Delay14_reg(2) <= X"00000000";
        Delay14_reg(3) <= X"00000000";
        Delay14_reg(4) <= X"00000000";
        Delay14_reg(5) <= X"00000000";
        Delay14_reg(6) <= X"00000000";
        Delay14_reg(7) <= X"00000000";
        Delay14_reg(8) <= X"00000000";
        Delay14_reg(9) <= X"00000000";
        Delay14_reg(10) <= X"00000000";
        Delay14_reg(11) <= X"00000000";
        Delay14_reg(12) <= X"00000000";
        Delay14_reg(13) <= X"00000000";
        Delay14_reg(14) <= X"00000000";
        Delay14_reg(15) <= X"00000000";
      ELSIF enb = '1' THEN
        Delay14_reg(0) <= Delay14_reg_next(0);
        Delay14_reg(1) <= Delay14_reg_next(1);
        Delay14_reg(2) <= Delay14_reg_next(2);
        Delay14_reg(3) <= Delay14_reg_next(3);
        Delay14_reg(4) <= Delay14_reg_next(4);
        Delay14_reg(5) <= Delay14_reg_next(5);
        Delay14_reg(6) <= Delay14_reg_next(6);
        Delay14_reg(7) <= Delay14_reg_next(7);
        Delay14_reg(8) <= Delay14_reg_next(8);
        Delay14_reg(9) <= Delay14_reg_next(9);
        Delay14_reg(10) <= Delay14_reg_next(10);
        Delay14_reg(11) <= Delay14_reg_next(11);
        Delay14_reg(12) <= Delay14_reg_next(12);
        Delay14_reg(13) <= Delay14_reg_next(13);
        Delay14_reg(14) <= Delay14_reg_next(14);
        Delay14_reg(15) <= Delay14_reg_next(15);
      END IF;
    END IF;
  END PROCESS Delay14_process;

  c73_Delay14_out1(0) <= Delay14_reg(0);
  c73_Delay14_out1(1) <= Delay14_reg(1);
  c73_Delay14_out1(2) <= Delay14_reg(2);
  c73_Delay14_out1(3) <= Delay14_reg(3);
  c73_Delay14_out1(4) <= Delay14_reg(4);
  c73_Delay14_out1(5) <= Delay14_reg(5);
  c73_Delay14_out1(6) <= Delay14_reg(6);
  c73_Delay14_out1(7) <= Delay14_reg(7);
  c73_Delay14_out1(8) <= Delay14_reg(8);
  c73_Delay14_out1(9) <= Delay14_reg(9);
  c73_Delay14_out1(10) <= Delay14_reg(10);
  c73_Delay14_out1(11) <= Delay14_reg(11);
  c73_Delay14_out1(12) <= Delay14_reg(12);
  c73_Delay14_out1(13) <= Delay14_reg(13);
  c73_Delay14_out1(14) <= Delay14_reg(14);
  c73_Delay14_out1(15) <= Delay14_reg(15);
  Delay14_reg_next(0) <= c73_Switch_on14_out1(0);
  Delay14_reg_next(1) <= c73_Switch_on14_out1(1);
  Delay14_reg_next(2) <= c73_Switch_on14_out1(2);
  Delay14_reg_next(3) <= c73_Switch_on14_out1(3);
  Delay14_reg_next(4) <= c73_Switch_on14_out1(4);
  Delay14_reg_next(5) <= c73_Switch_on14_out1(5);
  Delay14_reg_next(6) <= c73_Switch_on14_out1(6);
  Delay14_reg_next(7) <= c73_Switch_on14_out1(7);
  Delay14_reg_next(8) <= c73_Switch_on14_out1(8);
  Delay14_reg_next(9) <= c73_Switch_on14_out1(9);
  Delay14_reg_next(10) <= c73_Switch_on14_out1(10);
  Delay14_reg_next(11) <= c73_Switch_on14_out1(11);
  Delay14_reg_next(12) <= c73_Switch_on14_out1(12);
  Delay14_reg_next(13) <= c73_Switch_on14_out1(13);
  Delay14_reg_next(14) <= c73_Switch_on14_out1(14);
  Delay14_reg_next(15) <= c73_Switch_on14_out1(15);

  
  c161_Switch_on14_out1(0) <= c73_Delay14_out1(0) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(0);
  
  c161_Switch_on14_out1(1) <= c73_Delay14_out1(1) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(1);
  
  c161_Switch_on14_out1(2) <= c73_Delay14_out1(2) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(2);
  
  c161_Switch_on14_out1(3) <= c73_Delay14_out1(3) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(3);
  
  c161_Switch_on14_out1(4) <= c73_Delay14_out1(4) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(4);
  
  c161_Switch_on14_out1(5) <= c73_Delay14_out1(5) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(5);
  
  c161_Switch_on14_out1(6) <= c73_Delay14_out1(6) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(6);
  
  c161_Switch_on14_out1(7) <= c73_Delay14_out1(7) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(7);
  
  c161_Switch_on14_out1(8) <= c73_Delay14_out1(8) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(8);
  
  c161_Switch_on14_out1(9) <= c73_Delay14_out1(9) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(9);
  
  c161_Switch_on14_out1(10) <= c73_Delay14_out1(10) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(10);
  
  c161_Switch_on14_out1(11) <= c73_Delay14_out1(11) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(11);
  
  c161_Switch_on14_out1(12) <= c73_Delay14_out1(12) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(12);
  
  c161_Switch_on14_out1(13) <= c73_Delay14_out1(13) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(13);
  
  c161_Switch_on14_out1(14) <= c73_Delay14_out1(14) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(14);
  
  c161_Switch_on14_out1(15) <= c73_Delay14_out1(15) WHEN switch_compare_1_13 = '0' ELSE
      c161_v(15);

  Switch_on14_out1GEN_LABEL1: FOR d1 IN 0 TO 7 GENERATE
    Switch_on14_out1GEN_LABEL: FOR d0 IN 0 TO 1 GENERATE
      Switch_on14_out1(d0, d1) <= c161_Switch_on14_out1(d0 + (d1 * 2));
    END GENERATE;
  END GENERATE;

  DelayValue1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        DelayValue1_out1(0) <= X"0000000000000000";
        DelayValue1_out1(1) <= X"0000000000000000";
      ELSIF enb = '1' THEN
        DelayValue1_out1(0) <= v_opt(0);
        DelayValue1_out1(1) <= v_opt(1);
      END IF;
    END IF;
  END PROCESS DelayValue1_process;



  Delay13_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay13_out1(0) <= X"00000000";
        Delay13_out1(1) <= X"00000000";
      ELSIF enb = '1' THEN
        Delay13_out1(0) <= Switch_on13_out1(0);
        Delay13_out1(1) <= Switch_on13_out1(1);
      END IF;
    END IF;
  END PROCESS Delay13_process;


  
  Switch_on13_out1(0) <= Delay13_out1(0) WHEN switch_compare_1_12 = '0' ELSE
      Data_Type_Conversion9_out1(0);
  
  Switch_on13_out1(1) <= Delay13_out1(1) WHEN switch_compare_1_12 = '0' ELSE
      Data_Type_Conversion9_out1(1);

  Delay15_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay15_out1(0) <= X"0000000000000000";
        Delay15_out1(1) <= X"0000000000000000";
        Delay15_out1(2) <= X"0000000000000000";
        Delay15_out1(3) <= X"0000000000000000";
        Delay15_out1(4) <= X"0000000000000000";
        Delay15_out1(5) <= X"0000000000000000";
        Delay15_out1(6) <= X"0000000000000000";
        Delay15_out1(7) <= X"0000000000000000";
      ELSIF enb = '1' THEN
        Delay15_out1(0) <= Switch_on15_out1(0);
        Delay15_out1(1) <= Switch_on15_out1(1);
        Delay15_out1(2) <= Switch_on15_out1(2);
        Delay15_out1(3) <= Switch_on15_out1(3);
        Delay15_out1(4) <= Switch_on15_out1(4);
        Delay15_out1(5) <= Switch_on15_out1(5);
        Delay15_out1(6) <= Switch_on15_out1(6);
        Delay15_out1(7) <= Switch_on15_out1(7);
      END IF;
    END IF;
  END PROCESS Delay15_process;


  
  Switch_on15_out1(0) <= Delay15_out1(0) WHEN switch_compare_1 = '0' ELSE
      J(0);
  
  Switch_on15_out1(1) <= Delay15_out1(1) WHEN switch_compare_1 = '0' ELSE
      J(1);
  
  Switch_on15_out1(2) <= Delay15_out1(2) WHEN switch_compare_1 = '0' ELSE
      J(2);
  
  Switch_on15_out1(3) <= Delay15_out1(3) WHEN switch_compare_1 = '0' ELSE
      J(3);
  
  Switch_on15_out1(4) <= Delay15_out1(4) WHEN switch_compare_1 = '0' ELSE
      J(4);
  
  Switch_on15_out1(5) <= Delay15_out1(5) WHEN switch_compare_1 = '0' ELSE
      J(5);
  
  Switch_on15_out1(6) <= Delay15_out1(6) WHEN switch_compare_1 = '0' ELSE
      J(6);
  
  Switch_on15_out1(7) <= Delay15_out1(7) WHEN switch_compare_1 = '0' ELSE
      J(7);

  DelayValid1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        DelayValid1_reg(0) <= '0';
        DelayValid1_reg(1) <= '0';
        DelayValid1_reg(2) <= '0';
        DelayValid1_reg(3) <= '0';
      ELSIF enb = '1' THEN
        DelayValid1_reg(0) <= DelayValid1_reg_next(0);
        DelayValid1_reg(1) <= DelayValid1_reg_next(1);
        DelayValid1_reg(2) <= DelayValid1_reg_next(2);
        DelayValid1_reg(3) <= DelayValid1_reg_next(3);
      END IF;
    END IF;
  END PROCESS DelayValid1_process;

  End_Cycle_1 <= DelayValid1_reg(3);
  DelayValid1_reg_next(0) <= Saturation1_out1;
  DelayValid1_reg_next(1) <= DelayValid1_reg(0);
  DelayValid1_reg_next(2) <= DelayValid1_reg(1);
  DelayValid1_reg_next(3) <= DelayValid1_reg(2);

  
  index_1 <= '1' WHEN End_Cycle_1 /= '0' ELSE
      '0';

  done_MPC <= index_1;

  ce_out <= clk_enable;

  Index <= Data_Type_Conversion10_out1;

END rtl;
