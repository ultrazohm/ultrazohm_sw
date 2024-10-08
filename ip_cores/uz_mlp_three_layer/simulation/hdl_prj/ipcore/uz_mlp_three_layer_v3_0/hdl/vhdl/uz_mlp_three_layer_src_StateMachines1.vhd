-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj/hdlsrc/uz_mlp_three_layer/uz_mlp_three_layer_src_StateMachines1.vhd
-- Created: 2021-03-17 16:47:04
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_mlp_three_layer_src_StateMachines1
-- Source Path: uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/StateMachines1
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_mlp_three_layer_src_StateMachines1 IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        triggerCalc                       :   IN    std_logic;
        mac_startOut                      :   IN    std_logic;
        end_out                           :   IN    std_logic;
        number_of_inputs                  :   IN    std_logic_vector(9 DOWNTO 0);  -- ufix10
        mac_counter                       :   OUT   std_logic_vector(9 DOWNTO 0);  -- ufix10
        layer_finished                    :   OUT   std_logic;
        toMac_endin                       :   OUT   std_logic;
        toMac_validIn                     :   OUT   std_logic;
        toMac_startin                     :   OUT   std_logic;
        toMac_mac_counter                 :   OUT   std_logic_vector(9 DOWNTO 0);  -- ufix10
        toMac_write_enable                :   OUT   std_logic;
        toMac_n_perceptron                :   OUT   std_logic_vector(9 DOWNTO 0)  -- ufix10
        );
END uz_mlp_three_layer_src_StateMachines1;


ARCHITECTURE rtl OF uz_mlp_three_layer_src_StateMachines1 IS

  -- Component Declarations
  COMPONENT uz_mlp_three_layer_src_Detect_Rise_Positive_block1
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          U                               :   IN    std_logic;
          Y                               :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_layer_control
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          ext_enable                      :   IN    std_logic;
          mac_ready                       :   IN    std_logic;
          cnt_finished                    :   IN    std_logic;
          enable_mac                      :   OUT   std_logic;
          cnt_enable                      :   OUT   std_logic;
          counter_rest                    :   OUT   std_logic;
          layer_finished                  :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_mac_control
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          external_enable                 :   IN    std_logic;
          counter_finished                :   IN    std_logic;
          end_out                         :   IN    std_logic;
          end_out_delay                   :   IN    std_logic;
          mac_startOut                    :   IN    std_logic;
          index_counter_enb               :   OUT   std_logic;
          mac_startIn                     :   OUT   std_logic;
          mac_endIn                       :   OUT   std_logic;
          mac_validIn                     :   OUT   std_logic;
          index_counter_rst               :   OUT   std_logic;
          write_ram                       :   OUT   std_logic;
          mac_ready                       :   OUT   std_logic
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_mlp_three_layer_src_Detect_Rise_Positive_block1
    USE ENTITY work.uz_mlp_three_layer_src_Detect_Rise_Positive_block1(rtl);

  FOR ALL : uz_mlp_three_layer_src_layer_control
    USE ENTITY work.uz_mlp_three_layer_src_layer_control(rtl);

  FOR ALL : uz_mlp_three_layer_src_mac_control
    USE ENTITY work.uz_mlp_three_layer_src_mac_control(rtl);

  -- Signals
  SIGNAL Detect_Rise_Positive_out1        : std_logic;
  SIGNAL number_of_inputs_unsigned        : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL Delay3_out1                      : std_logic;
  SIGNAL mac_counter_tmp                  : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL Delay2_out1                      : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL Relational_Operator_relop1       : std_logic;
  SIGNAL layer_control_out4               : std_logic;
  SIGNAL layer_control_out3               : std_logic;
  SIGNAL n_perceptron                     : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL Compare_To_Constant1_out1        : std_logic;
  SIGNAL mac_ready                        : std_logic;
  SIGNAL Delay4_out1                      : std_logic;
  SIGNAL layer_control_out1               : std_logic;
  SIGNAL layer_control_out5               : std_logic;
  SIGNAL mac_control_out1                 : std_logic;
  SIGNAL startin                          : std_logic;
  SIGNAL endin                            : std_logic;
  SIGNAL validIn                          : std_logic;
  SIGNAL mac_control_out5                 : std_logic;
  SIGNAL write_enable                     : std_logic;

BEGIN
  u_Detect_Rise_Positive : uz_mlp_three_layer_src_Detect_Rise_Positive_block1
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              U => triggerCalc,
              Y => Detect_Rise_Positive_out1
              );

  u_layer_control : uz_mlp_three_layer_src_layer_control
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              ext_enable => Detect_Rise_Positive_out1,
              mac_ready => Delay4_out1,
              cnt_finished => Compare_To_Constant1_out1,
              enable_mac => layer_control_out1,
              cnt_enable => layer_control_out3,
              counter_rest => layer_control_out4,
              layer_finished => layer_control_out5
              );

  u_mac_control : uz_mlp_three_layer_src_mac_control
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              external_enable => layer_control_out1,
              counter_finished => Relational_Operator_relop1,
              end_out => end_out,
              end_out_delay => Delay3_out1,
              mac_startOut => mac_startOut,
              index_counter_enb => mac_control_out1,
              mac_startIn => startin,
              mac_endIn => endin,
              mac_validIn => validIn,
              index_counter_rst => mac_control_out5,
              write_ram => write_enable,
              mac_ready => mac_ready
              );

  number_of_inputs_unsigned <= unsigned(number_of_inputs);

  Delay3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay3_out1 <= '0';
      ELSIF enb = '1' THEN
        Delay3_out1 <= end_out;
      END IF;
    END IF;
  END PROCESS Delay3_process;


  Delay2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay2_out1 <= to_unsigned(16#000#, 10);
      ELSIF enb = '1' THEN
        Delay2_out1 <= mac_counter_tmp;
      END IF;
    END IF;
  END PROCESS Delay2_process;


  
  Relational_Operator_relop1 <= '1' WHEN number_of_inputs_unsigned = Delay2_out1 ELSE
      '0';

  -- Free running, Unsigned Counter
  --  initial value   = 0
  --  step value      = 1
  perceptron_counter1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        n_perceptron <= to_unsigned(16#000#, 10);
      ELSIF enb = '1' THEN
        IF layer_control_out4 = '1' THEN 
          n_perceptron <= to_unsigned(16#000#, 10);
        ELSIF layer_control_out3 = '1' THEN 
          n_perceptron <= n_perceptron + to_unsigned(16#001#, 10);
        END IF;
      END IF;
    END IF;
  END PROCESS perceptron_counter1_process;


  
  Compare_To_Constant1_out1 <= '1' WHEN n_perceptron = to_unsigned(16#00F#, 10) ELSE
      '0';

  Delay4_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay4_out1 <= '0';
      ELSIF enb = '1' THEN
        Delay4_out1 <= mac_ready;
      END IF;
    END IF;
  END PROCESS Delay4_process;


  -- Free running, Unsigned Counter
  --  initial value   = 1
  --  step value      = 1
  index_counter_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        mac_counter_tmp <= to_unsigned(16#001#, 10);
      ELSIF enb = '1' THEN
        IF mac_control_out5 = '1' THEN 
          mac_counter_tmp <= to_unsigned(16#001#, 10);
        ELSIF mac_control_out1 = '1' THEN 
          mac_counter_tmp <= mac_counter_tmp + to_unsigned(16#001#, 10);
        END IF;
      END IF;
    END IF;
  END PROCESS index_counter_process;


  mac_counter <= std_logic_vector(mac_counter_tmp);

  toMac_mac_counter <= std_logic_vector(mac_counter_tmp);

  toMac_n_perceptron <= std_logic_vector(n_perceptron);

  layer_finished <= layer_control_out5;

  toMac_endin <= endin;

  toMac_validIn <= validIn;

  toMac_startin <= startin;

  toMac_write_enable <= write_enable;

END rtl;

