-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_3ph_dq\hdl_prj\hdlsrc\uz_pmsm_model_3ph_dq\uz_pmsm_model_3ph_dq_addr_decoder.vhd
-- Created: 2023-01-09 11:01:41
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_3ph_dq_addr_decoder
-- Source Path: uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq_axi4/uz_pmsm_model_3ph_dq_addr_decoder
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.uz_pmsm_model_3ph_dq_pkg.ALL;

ENTITY uz_pmsm_model_3ph_dq_addr_decoder IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        data_write                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        addr_sel                          :   IN    std_logic_vector(13 DOWNTO 0);  -- ufix14
        wr_enb                            :   IN    std_logic;  -- ufix1
        rd_enb                            :   IN    std_logic;  -- ufix1
        read_ip_timestamp                 :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        read_outputs                      :   IN    vector_of_std_logic_vector32(0 TO 4);  -- ufix32 [5]
        read_voltage_input_dq_out_axi_fb  :   IN    vector_of_std_logic_vector32(0 TO 1);  -- ufix32 [2]
        data_read                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_axi_enable                  :   OUT   std_logic;  -- ufix1
        write_reset_integrators           :   OUT   std_logic;  -- ufix1
        write_simulate_mechanical         :   OUT   std_logic;  -- ufix1
        write_reciprocal_J                :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_mu                          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_M_n0                        :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_reciprocal_L_d              :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_reciprocal_L_q              :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_R1                          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_polepairs                   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_psi_pm                      :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_use_axi_input               :   OUT   std_logic;  -- ufix1
        write_inputs                      :   OUT   vector_of_std_logic_vector32(0 TO 3)  -- ufix32 [4]
        );
END uz_pmsm_model_3ph_dq_addr_decoder;


ARCHITECTURE rtl OF uz_pmsm_model_3ph_dq_addr_decoder IS

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL addr_sel_unsigned                : unsigned(13 DOWNTO 0);  -- ufix14
  SIGNAL decode_sel_ip_timestamp_1_1      : std_logic;  -- ufix1
  SIGNAL read_ip_timestamp_unsigned       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL const_1                          : std_logic;  -- ufix1
  SIGNAL decode_sel_outputs_1_1           : std_logic;  -- ufix1
  SIGNAL const_0                          : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_ip_timestamp            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_ip_timestamp_1_1       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_outputs               : std_logic;  -- ufix1
  SIGNAL strobe_sel_outputs               : std_logic;  -- ufix1
  SIGNAL const_zero                       : std_logic;  -- ufix1
  SIGNAL data_write_unsigned              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL strobe_in_outputs                : std_logic;  -- ufix1
  SIGNAL strobe_sw_outputs                : std_logic;  -- ufix1
  SIGNAL strobe_reg_outputs               : std_logic;  -- ufix1
  SIGNAL read_outputs_unsigned            : vector_of_unsigned32(0 TO 4);  -- ufix32 [5]
  SIGNAL sync_reg_outputs                 : vector_of_unsigned32(0 TO 4);  -- ufix32 [5]
  SIGNAL data_slice_outputs_1             : vector_of_unsigned32(0 TO 4);  -- ufix32 [5]
  SIGNAL decode_sel_outputs_1_2           : std_logic;  -- ufix1
  SIGNAL data_slice_outputs_1_0           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_outputs_1_1            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_outputs_1_3           : std_logic;  -- ufix1
  SIGNAL data_slice_outputs_1_1           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_outputs_1_2            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_outputs_1_4           : std_logic;  -- ufix1
  SIGNAL data_slice_outputs_1_2           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_outputs_1_3            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_outputs_1_5           : std_logic;  -- ufix1
  SIGNAL data_slice_outputs_1_3           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_outputs_1_4            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_voltage_input_dq_out_axi_fb_1_1 : std_logic;  -- ufix1
  SIGNAL data_slice_outputs_1_4           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_outputs_1_5            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_voltage_input_dq_out_axi_fb : std_logic;  -- ufix1
  SIGNAL strobe_sel_voltage_input_dq_out_axi_fb : std_logic;  -- ufix1
  SIGNAL const_zero_1                     : std_logic;  -- ufix1
  SIGNAL strobe_in_voltage_input_dq_out_axi_fb : std_logic;  -- ufix1
  SIGNAL strobe_sw_voltage_input_dq_out_axi_fb : std_logic;  -- ufix1
  SIGNAL strobe_reg_voltage_input_dq_out_axi_fb : std_logic;  -- ufix1
  SIGNAL read_voltage_input_dq_out_axi_fb_unsigned : vector_of_unsigned32(0 TO 1);  -- ufix32 [2]
  SIGNAL sync_reg_voltage_input_dq_out_axi_fb : vector_of_unsigned32(0 TO 1);  -- ufix32 [2]
  SIGNAL data_slice_voltage_input_dq_out_axi_fb_1 : vector_of_unsigned32(0 TO 1);  -- ufix32 [2]
  SIGNAL decode_sel_voltage_input_dq_out_axi_fb_1_2 : std_logic;  -- ufix1
  SIGNAL data_slice_voltage_input_dq_out_axi_fb_1_0 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_voltage_input_dq_out_axi_fb_1_1 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_slice_voltage_input_dq_out_axi_fb_1_1 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_voltage_input_dq_out_axi_fb_1_2 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_axi_enable_1_1        : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_enable_1_1           : std_logic;  -- ufix1
  SIGNAL data_in_axi_enable               : std_logic;  -- ufix1
  SIGNAL data_reg_axi_enable_1_1          : std_logic;  -- ufix1
  SIGNAL write_concats_axi_enable_1       : std_logic;  -- ufix1
  SIGNAL decode_sel_reset_integrators_1_1 : std_logic;  -- ufix1
  SIGNAL reg_enb_reset_integrators_1_1    : std_logic;  -- ufix1
  SIGNAL data_in_reset_integrators        : std_logic;  -- ufix1
  SIGNAL data_reg_reset_integrators_1_1   : std_logic;  -- ufix1
  SIGNAL write_concats_reset_integrators_1 : std_logic;  -- ufix1
  SIGNAL decode_sel_simulate_mechanical_1_1 : std_logic;  -- ufix1
  SIGNAL reg_enb_simulate_mechanical_1_1  : std_logic;  -- ufix1
  SIGNAL data_in_simulate_mechanical      : std_logic;  -- ufix1
  SIGNAL data_reg_simulate_mechanical_1_1 : std_logic;  -- ufix1
  SIGNAL write_concats_simulate_mechanical_1 : std_logic;  -- ufix1
  SIGNAL decode_sel_reciprocal_J_1_1      : std_logic;  -- ufix1
  SIGNAL reg_enb_reciprocal_J_1_1         : std_logic;  -- ufix1
  SIGNAL data_reg_reciprocal_J_1_1        : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_mu_1_1                : std_logic;  -- ufix1
  SIGNAL reg_enb_mu_1_1                   : std_logic;  -- ufix1
  SIGNAL data_reg_mu_1_1                  : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_M_n0_1_1              : std_logic;  -- ufix1
  SIGNAL reg_enb_M_n0_1_1                 : std_logic;  -- ufix1
  SIGNAL data_reg_M_n0_1_1                : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_reciprocal_L_d_1_1    : std_logic;  -- ufix1
  SIGNAL reg_enb_reciprocal_L_d_1_1       : std_logic;  -- ufix1
  SIGNAL data_reg_reciprocal_L_d_1_1      : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_reciprocal_L_q_1_1    : std_logic;  -- ufix1
  SIGNAL reg_enb_reciprocal_L_q_1_1       : std_logic;  -- ufix1
  SIGNAL data_reg_reciprocal_L_q_1_1      : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_R1_1_1                : std_logic;  -- ufix1
  SIGNAL reg_enb_R1_1_1                   : std_logic;  -- ufix1
  SIGNAL data_reg_R1_1_1                  : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_polepairs_1_1         : std_logic;  -- ufix1
  SIGNAL reg_enb_polepairs_1_1            : std_logic;  -- ufix1
  SIGNAL data_reg_polepairs_1_1           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_psi_pm_1_1            : std_logic;  -- ufix1
  SIGNAL reg_enb_psi_pm_1_1               : std_logic;  -- ufix1
  SIGNAL data_reg_psi_pm_1_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_use_axi_input_1_1     : std_logic;  -- ufix1
  SIGNAL reg_enb_use_axi_input_1_1        : std_logic;  -- ufix1
  SIGNAL data_in_use_axi_input            : std_logic;  -- ufix1
  SIGNAL data_reg_use_axi_input_1_1       : std_logic;  -- ufix1
  SIGNAL write_concats_use_axi_input_1    : std_logic;  -- ufix1
  SIGNAL decode_sel_inputs                : std_logic;  -- ufix1
  SIGNAL strobe_sel_inputs                : std_logic;  -- ufix1
  SIGNAL const_zero_2                     : std_logic;  -- ufix1
  SIGNAL strobe_in_inputs                 : std_logic;  -- ufix1
  SIGNAL strobe_sw_inputs                 : std_logic;  -- ufix1
  SIGNAL decode_sel_inputs_1_1            : std_logic;  -- ufix1
  SIGNAL reg_enb_inputs_1_1               : std_logic;  -- ufix1
  SIGNAL decode_sel_inputs_2_1            : std_logic;  -- ufix1
  SIGNAL reg_enb_inputs_2_1               : std_logic;  -- ufix1
  SIGNAL decode_sel_inputs_3_1            : std_logic;  -- ufix1
  SIGNAL reg_enb_inputs_3_1               : std_logic;  -- ufix1
  SIGNAL decode_sel_inputs_4_1            : std_logic;  -- ufix1
  SIGNAL reg_enb_inputs_4_1               : std_logic;  -- ufix1
  SIGNAL strobe_reg_inputs                : std_logic;  -- ufix1
  SIGNAL data_reg_inputs_1_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_reg_inputs_2_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_reg_inputs_3_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_reg_inputs_4_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL write_reg_inputs                 : vector_of_unsigned32(0 TO 3);  -- ufix32 [4]
  SIGNAL sync_reg_inputs_1                : vector_of_unsigned32(0 TO 3);  -- ufix32 [4]

BEGIN
  addr_sel_unsigned <= unsigned(addr_sel);

  
  decode_sel_ip_timestamp_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0002#, 14) ELSE
      '0';

  read_ip_timestamp_unsigned <= unsigned(read_ip_timestamp);

  const_1 <= '1';

  enb <= const_1;

  
  decode_sel_outputs_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0068#, 14) ELSE
      '0';

  const_0 <= to_unsigned(0, 32);

  reg_ip_timestamp_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_ip_timestamp <= to_unsigned(0, 32);
      ELSIF enb = '1' THEN
        read_reg_ip_timestamp <= read_ip_timestamp_unsigned;
      END IF;
    END IF;
  END PROCESS reg_ip_timestamp_process;


  
  decode_rd_ip_timestamp_1_1 <= const_0 WHEN decode_sel_ip_timestamp_1_1 = '0' ELSE
      read_reg_ip_timestamp;

  
  decode_sel_outputs <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0070#, 14) ELSE
      '0';

  strobe_sel_outputs <= decode_sel_outputs AND wr_enb;

  const_zero <= '0';

  data_write_unsigned <= unsigned(data_write);

  strobe_in_outputs <= data_write_unsigned(0);

  
  strobe_sw_outputs <= const_zero WHEN strobe_sel_outputs = '0' ELSE
      strobe_in_outputs;

  reg_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        strobe_reg_outputs <= '0';
      ELSIF enb = '1' THEN
        strobe_reg_outputs <= strobe_sw_outputs;
      END IF;
    END IF;
  END PROCESS reg_process;


  outputgen2: FOR k IN 0 TO 4 GENERATE
    read_outputs_unsigned(k) <= unsigned(read_outputs(k));
  END GENERATE;

  reg_outputs_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        sync_reg_outputs(0) <= to_unsigned(0, 32);
        sync_reg_outputs(1) <= to_unsigned(0, 32);
        sync_reg_outputs(2) <= to_unsigned(0, 32);
        sync_reg_outputs(3) <= to_unsigned(0, 32);
        sync_reg_outputs(4) <= to_unsigned(0, 32);
      ELSIF enb = '1' AND strobe_reg_outputs = '1' THEN
        sync_reg_outputs(0) <= read_outputs_unsigned(0);
        sync_reg_outputs(1) <= read_outputs_unsigned(1);
        sync_reg_outputs(2) <= read_outputs_unsigned(2);
        sync_reg_outputs(3) <= read_outputs_unsigned(3);
        sync_reg_outputs(4) <= read_outputs_unsigned(4);
      END IF;
    END IF;
  END PROCESS reg_outputs_process;


  data_slice_outputs_1(0) <= sync_reg_outputs(0);
  data_slice_outputs_1(1) <= sync_reg_outputs(1);
  data_slice_outputs_1(2) <= sync_reg_outputs(2);
  data_slice_outputs_1(3) <= sync_reg_outputs(3);
  data_slice_outputs_1(4) <= sync_reg_outputs(4);

  
  decode_sel_outputs_1_2 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0069#, 14) ELSE
      '0';

  data_slice_outputs_1_0 <= data_slice_outputs_1(0);

  
  decode_rd_outputs_1_1 <= decode_rd_ip_timestamp_1_1 WHEN decode_sel_outputs_1_1 = '0' ELSE
      data_slice_outputs_1_0;

  
  decode_sel_outputs_1_3 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#006A#, 14) ELSE
      '0';

  data_slice_outputs_1_1 <= data_slice_outputs_1(1);

  
  decode_rd_outputs_1_2 <= decode_rd_outputs_1_1 WHEN decode_sel_outputs_1_2 = '0' ELSE
      data_slice_outputs_1_1;

  
  decode_sel_outputs_1_4 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#006B#, 14) ELSE
      '0';

  data_slice_outputs_1_2 <= data_slice_outputs_1(2);

  
  decode_rd_outputs_1_3 <= decode_rd_outputs_1_2 WHEN decode_sel_outputs_1_3 = '0' ELSE
      data_slice_outputs_1_2;

  
  decode_sel_outputs_1_5 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#006C#, 14) ELSE
      '0';

  data_slice_outputs_1_3 <= data_slice_outputs_1(3);

  
  decode_rd_outputs_1_4 <= decode_rd_outputs_1_3 WHEN decode_sel_outputs_1_4 = '0' ELSE
      data_slice_outputs_1_3;

  
  decode_sel_voltage_input_dq_out_axi_fb_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#00A0#, 14) ELSE
      '0';

  data_slice_outputs_1_4 <= data_slice_outputs_1(4);

  
  decode_rd_outputs_1_5 <= decode_rd_outputs_1_4 WHEN decode_sel_outputs_1_5 = '0' ELSE
      data_slice_outputs_1_4;

  
  decode_sel_voltage_input_dq_out_axi_fb <= '1' WHEN addr_sel_unsigned = to_unsigned(16#00A2#, 14) ELSE
      '0';

  strobe_sel_voltage_input_dq_out_axi_fb <= decode_sel_voltage_input_dq_out_axi_fb AND wr_enb;

  const_zero_1 <= '0';

  strobe_in_voltage_input_dq_out_axi_fb <= data_write_unsigned(0);

  
  strobe_sw_voltage_input_dq_out_axi_fb <= const_zero_1 WHEN strobe_sel_voltage_input_dq_out_axi_fb = '0' ELSE
      strobe_in_voltage_input_dq_out_axi_fb;

  reg_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        strobe_reg_voltage_input_dq_out_axi_fb <= '0';
      ELSIF enb = '1' THEN
        strobe_reg_voltage_input_dq_out_axi_fb <= strobe_sw_voltage_input_dq_out_axi_fb;
      END IF;
    END IF;
  END PROCESS reg_1_process;


  outputgen1: FOR k IN 0 TO 1 GENERATE
    read_voltage_input_dq_out_axi_fb_unsigned(k) <= unsigned(read_voltage_input_dq_out_axi_fb(k));
  END GENERATE;

  reg_voltage_input_dq_out_axi_fb_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        sync_reg_voltage_input_dq_out_axi_fb(0) <= to_unsigned(0, 32);
        sync_reg_voltage_input_dq_out_axi_fb(1) <= to_unsigned(0, 32);
      ELSIF enb = '1' AND strobe_reg_voltage_input_dq_out_axi_fb = '1' THEN
        sync_reg_voltage_input_dq_out_axi_fb(0) <= read_voltage_input_dq_out_axi_fb_unsigned(0);
        sync_reg_voltage_input_dq_out_axi_fb(1) <= read_voltage_input_dq_out_axi_fb_unsigned(1);
      END IF;
    END IF;
  END PROCESS reg_voltage_input_dq_out_axi_fb_process;


  data_slice_voltage_input_dq_out_axi_fb_1(0) <= sync_reg_voltage_input_dq_out_axi_fb(0);
  data_slice_voltage_input_dq_out_axi_fb_1(1) <= sync_reg_voltage_input_dq_out_axi_fb(1);

  
  decode_sel_voltage_input_dq_out_axi_fb_1_2 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#00A1#, 14) ELSE
      '0';

  data_slice_voltage_input_dq_out_axi_fb_1_0 <= data_slice_voltage_input_dq_out_axi_fb_1(0);

  
  decode_rd_voltage_input_dq_out_axi_fb_1_1 <= decode_rd_outputs_1_5 WHEN decode_sel_voltage_input_dq_out_axi_fb_1_1 = '0' ELSE
      data_slice_voltage_input_dq_out_axi_fb_1_0;

  data_slice_voltage_input_dq_out_axi_fb_1_1 <= data_slice_voltage_input_dq_out_axi_fb_1(1);

  
  decode_rd_voltage_input_dq_out_axi_fb_1_2 <= decode_rd_voltage_input_dq_out_axi_fb_1_1 WHEN decode_sel_voltage_input_dq_out_axi_fb_1_2 = '0' ELSE
      data_slice_voltage_input_dq_out_axi_fb_1_1;

  data_read <= std_logic_vector(decode_rd_voltage_input_dq_out_axi_fb_1_2);

  
  decode_sel_axi_enable_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0001#, 14) ELSE
      '0';

  reg_enb_axi_enable_1_1 <= decode_sel_axi_enable_1_1 AND wr_enb;

  data_in_axi_enable <= data_write_unsigned(0);

  reg_axi_enable_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_axi_enable_1_1 <= '1';
      ELSIF enb = '1' AND reg_enb_axi_enable_1_1 = '1' THEN
        data_reg_axi_enable_1_1 <= data_in_axi_enable;
      END IF;
    END IF;
  END PROCESS reg_axi_enable_1_1_process;


  write_concats_axi_enable_1 <= data_reg_axi_enable_1_1;

  write_axi_enable <= write_concats_axi_enable_1;

  
  decode_sel_reset_integrators_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0040#, 14) ELSE
      '0';

  reg_enb_reset_integrators_1_1 <= decode_sel_reset_integrators_1_1 AND wr_enb;

  data_in_reset_integrators <= data_write_unsigned(0);

  reg_reset_integrators_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_reset_integrators_1_1 <= '0';
      ELSIF enb = '1' AND reg_enb_reset_integrators_1_1 = '1' THEN
        data_reg_reset_integrators_1_1 <= data_in_reset_integrators;
      END IF;
    END IF;
  END PROCESS reg_reset_integrators_1_1_process;


  write_concats_reset_integrators_1 <= data_reg_reset_integrators_1_1;

  write_reset_integrators <= write_concats_reset_integrators_1;

  
  decode_sel_simulate_mechanical_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0041#, 14) ELSE
      '0';

  reg_enb_simulate_mechanical_1_1 <= decode_sel_simulate_mechanical_1_1 AND wr_enb;

  data_in_simulate_mechanical <= data_write_unsigned(0);

  reg_simulate_mechanical_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_simulate_mechanical_1_1 <= '0';
      ELSIF enb = '1' AND reg_enb_simulate_mechanical_1_1 = '1' THEN
        data_reg_simulate_mechanical_1_1 <= data_in_simulate_mechanical;
      END IF;
    END IF;
  END PROCESS reg_simulate_mechanical_1_1_process;


  write_concats_simulate_mechanical_1 <= data_reg_simulate_mechanical_1_1;

  write_simulate_mechanical <= write_concats_simulate_mechanical_1;

  
  decode_sel_reciprocal_J_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0042#, 14) ELSE
      '0';

  reg_enb_reciprocal_J_1_1 <= decode_sel_reciprocal_J_1_1 AND wr_enb;

  reg_reciprocal_J_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_reciprocal_J_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_reciprocal_J_1_1 = '1' THEN
        data_reg_reciprocal_J_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_reciprocal_J_1_1_process;


  write_reciprocal_J <= std_logic_vector(data_reg_reciprocal_J_1_1);

  
  decode_sel_mu_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0043#, 14) ELSE
      '0';

  reg_enb_mu_1_1 <= decode_sel_mu_1_1 AND wr_enb;

  reg_mu_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_mu_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_mu_1_1 = '1' THEN
        data_reg_mu_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_mu_1_1_process;


  write_mu <= std_logic_vector(data_reg_mu_1_1);

  
  decode_sel_M_n0_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0044#, 14) ELSE
      '0';

  reg_enb_M_n0_1_1 <= decode_sel_M_n0_1_1 AND wr_enb;

  reg_M_n0_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_M_n0_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_M_n0_1_1 = '1' THEN
        data_reg_M_n0_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_M_n0_1_1_process;


  write_M_n0 <= std_logic_vector(data_reg_M_n0_1_1);

  
  decode_sel_reciprocal_L_d_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0045#, 14) ELSE
      '0';

  reg_enb_reciprocal_L_d_1_1 <= decode_sel_reciprocal_L_d_1_1 AND wr_enb;

  reg_reciprocal_L_d_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_reciprocal_L_d_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_reciprocal_L_d_1_1 = '1' THEN
        data_reg_reciprocal_L_d_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_reciprocal_L_d_1_1_process;


  write_reciprocal_L_d <= std_logic_vector(data_reg_reciprocal_L_d_1_1);

  
  decode_sel_reciprocal_L_q_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0046#, 14) ELSE
      '0';

  reg_enb_reciprocal_L_q_1_1 <= decode_sel_reciprocal_L_q_1_1 AND wr_enb;

  reg_reciprocal_L_q_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_reciprocal_L_q_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_reciprocal_L_q_1_1 = '1' THEN
        data_reg_reciprocal_L_q_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_reciprocal_L_q_1_1_process;


  write_reciprocal_L_q <= std_logic_vector(data_reg_reciprocal_L_q_1_1);

  
  decode_sel_R1_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0047#, 14) ELSE
      '0';

  reg_enb_R1_1_1 <= decode_sel_R1_1_1 AND wr_enb;

  reg_R1_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_R1_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_R1_1_1 = '1' THEN
        data_reg_R1_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_R1_1_1_process;


  write_R1 <= std_logic_vector(data_reg_R1_1_1);

  
  decode_sel_polepairs_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0048#, 14) ELSE
      '0';

  reg_enb_polepairs_1_1 <= decode_sel_polepairs_1_1 AND wr_enb;

  reg_polepairs_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_polepairs_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_polepairs_1_1 = '1' THEN
        data_reg_polepairs_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_polepairs_1_1_process;


  write_polepairs <= std_logic_vector(data_reg_polepairs_1_1);

  
  decode_sel_psi_pm_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0049#, 14) ELSE
      '0';

  reg_enb_psi_pm_1_1 <= decode_sel_psi_pm_1_1 AND wr_enb;

  reg_psi_pm_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_psi_pm_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_psi_pm_1_1 = '1' THEN
        data_reg_psi_pm_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_psi_pm_1_1_process;


  write_psi_pm <= std_logic_vector(data_reg_psi_pm_1_1);

  
  decode_sel_use_axi_input_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#004A#, 14) ELSE
      '0';

  reg_enb_use_axi_input_1_1 <= decode_sel_use_axi_input_1_1 AND wr_enb;

  data_in_use_axi_input <= data_write_unsigned(0);

  reg_use_axi_input_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_use_axi_input_1_1 <= '0';
      ELSIF enb = '1' AND reg_enb_use_axi_input_1_1 = '1' THEN
        data_reg_use_axi_input_1_1 <= data_in_use_axi_input;
      END IF;
    END IF;
  END PROCESS reg_use_axi_input_1_1_process;


  write_concats_use_axi_input_1 <= data_reg_use_axi_input_1_1;

  write_use_axi_input <= write_concats_use_axi_input_1;

  
  decode_sel_inputs <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0050#, 14) ELSE
      '0';

  strobe_sel_inputs <= decode_sel_inputs AND wr_enb;

  const_zero_2 <= '0';

  strobe_in_inputs <= data_write_unsigned(0);

  
  strobe_sw_inputs <= const_zero_2 WHEN strobe_sel_inputs = '0' ELSE
      strobe_in_inputs;

  
  decode_sel_inputs_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#004C#, 14) ELSE
      '0';

  reg_enb_inputs_1_1 <= decode_sel_inputs_1_1 AND wr_enb;

  
  decode_sel_inputs_2_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#004D#, 14) ELSE
      '0';

  reg_enb_inputs_2_1 <= decode_sel_inputs_2_1 AND wr_enb;

  
  decode_sel_inputs_3_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#004E#, 14) ELSE
      '0';

  reg_enb_inputs_3_1 <= decode_sel_inputs_3_1 AND wr_enb;

  
  decode_sel_inputs_4_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#004F#, 14) ELSE
      '0';

  reg_enb_inputs_4_1 <= decode_sel_inputs_4_1 AND wr_enb;

  reg_2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        strobe_reg_inputs <= '0';
      ELSIF enb = '1' THEN
        strobe_reg_inputs <= strobe_sw_inputs;
      END IF;
    END IF;
  END PROCESS reg_2_process;


  reg_inputs_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_inputs_1_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_inputs_1_1 = '1' THEN
        data_reg_inputs_1_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_inputs_1_1_process;


  reg_inputs_2_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_inputs_2_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_inputs_2_1 = '1' THEN
        data_reg_inputs_2_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_inputs_2_1_process;


  reg_inputs_3_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_inputs_3_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_inputs_3_1 = '1' THEN
        data_reg_inputs_3_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_inputs_3_1_process;


  reg_inputs_4_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_inputs_4_1 <= to_unsigned(0, 32);
      ELSIF enb = '1' AND reg_enb_inputs_4_1 = '1' THEN
        data_reg_inputs_4_1 <= data_write_unsigned;
      END IF;
    END IF;
  END PROCESS reg_inputs_4_1_process;


  write_reg_inputs(0) <= data_reg_inputs_1_1;
  write_reg_inputs(1) <= data_reg_inputs_2_1;
  write_reg_inputs(2) <= data_reg_inputs_3_1;
  write_reg_inputs(3) <= data_reg_inputs_4_1;

  sync_reg_inputs_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        sync_reg_inputs_1(0) <= to_unsigned(0, 32);
        sync_reg_inputs_1(1) <= to_unsigned(0, 32);
        sync_reg_inputs_1(2) <= to_unsigned(0, 32);
        sync_reg_inputs_1(3) <= to_unsigned(0, 32);
      ELSIF enb = '1' AND strobe_reg_inputs = '1' THEN
        sync_reg_inputs_1(0) <= write_reg_inputs(0);
        sync_reg_inputs_1(1) <= write_reg_inputs(1);
        sync_reg_inputs_1(2) <= write_reg_inputs(2);
        sync_reg_inputs_1(3) <= write_reg_inputs(3);
      END IF;
    END IF;
  END PROCESS sync_reg_inputs_process;


  outputgen: FOR k IN 0 TO 3 GENERATE
    write_inputs(k) <= std_logic_vector(sync_reg_inputs_1(k));
  END GENERATE;

END rtl;
