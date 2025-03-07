-- -------------------------------------------------------------
-- 
-- File Name: /home/ts/Dokumente/ultrazohm_testbench/ultrazohm_test/ultrazohm_sw/ip_cores/InterlockDeadtime2L/hdlsrc/uz_interlockDeadtime2L/uz_interlockDeadtime2L_addr_decoder.vhd
-- Created: 2021-04-22 14:35:13
-- 
-- Generated by MATLAB 9.9 and HDL Coder 3.17
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_interlockDeadtime2L_addr_decoder
-- Source Path: uz_interlockDeadtime2L/uz_interlockDeadtime2L_axi4/uz_interlockDeadtime2L_addr_decoder
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_interlockDeadtime2L_addr_decoder IS
  PORT( clk                               :   IN    std_logic;
        reset_x                           :   IN    std_logic;
        data_write                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        addr_sel                          :   IN    std_logic_vector(13 DOWNTO 0);  -- ufix14
        wr_enb                            :   IN    std_logic;  -- ufix1
        rd_enb                            :   IN    std_logic;  -- ufix1
        read_ip_timestamp                 :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        read_axi_fb_InverseBotSwitch      :   IN    std_logic;  -- ufix1
        read_axi_fb_DelayCycles           :   IN    std_logic_vector(9 DOWNTO 0);  -- ufix10
        read_axi_fb_enable                :   IN    std_logic;  -- ufix1
        data_read                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_axi_enable                  :   OUT   std_logic;  -- ufix1
        write_axi_InverseBotSwitch        :   OUT   std_logic;  -- ufix1
        write_axi_EnableOutput            :   OUT   std_logic;  -- ufix1
        write_axi_DelayCycles             :   OUT   std_logic_vector(9 DOWNTO 0)  -- ufix10
        );
END uz_interlockDeadtime2L_addr_decoder;


ARCHITECTURE rtl OF uz_interlockDeadtime2L_addr_decoder IS

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL addr_sel_unsigned                : unsigned(13 DOWNTO 0);  -- ufix14
  SIGNAL decode_sel_ip_timestamp_1_1      : std_logic;  -- ufix1
  SIGNAL read_ip_timestamp_unsigned       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL const_1                          : std_logic;  -- ufix1
  SIGNAL read_axi_fb_DelayCycles_unsigned : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL decode_sel_axi_fb_enable_1_1     : std_logic;  -- ufix1
  SIGNAL decode_sel_axi_fb_DelayCycles_1_1 : std_logic;  -- ufix1
  SIGNAL decode_sel_axi_fb_InverseBotSwitch_1_1 : std_logic;  -- ufix1
  SIGNAL const_0                          : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_ip_timestamp            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_ip_timestamp_1_1       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_axi_fb_InverseBotSwitch : std_logic;  -- ufix1
  SIGNAL data_slice_axi_fb_InverseBotSwitch_1 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_axi_fb_InverseBotSwitch_1_1 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_axi_fb_DelayCycles      : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL data_slice_axi_fb_DelayCycles_1  : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_axi_fb_DelayCycles_1_1 : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_axi_fb_enable           : std_logic;  -- ufix1
  SIGNAL data_slice_axi_fb_enable_1       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_axi_fb_enable_1_1      : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_axi_enable_1_1        : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_enable_1_1           : std_logic;  -- ufix1
  SIGNAL data_write_unsigned              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_in_axi_enable               : std_logic;  -- ufix1
  SIGNAL data_reg_axi_enable_1_1          : std_logic;  -- ufix1
  SIGNAL write_concats_axi_enable_1       : std_logic;  -- ufix1
  SIGNAL decode_sel_axi_InverseBotSwitch_1_1 : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_InverseBotSwitch_1_1 : std_logic;  -- ufix1
  SIGNAL data_in_axi_InverseBotSwitch     : std_logic;  -- ufix1
  SIGNAL data_reg_axi_InverseBotSwitch_1_1 : std_logic;  -- ufix1
  SIGNAL write_concats_axi_InverseBotSwitch_1 : std_logic;  -- ufix1
  SIGNAL decode_sel_axi_EnableOutput_1_1  : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_EnableOutput_1_1     : std_logic;  -- ufix1
  SIGNAL data_in_axi_EnableOutput         : std_logic;  -- ufix1
  SIGNAL data_reg_axi_EnableOutput_1_1    : std_logic;  -- ufix1
  SIGNAL write_concats_axi_EnableOutput_1 : std_logic;  -- ufix1
  SIGNAL decode_sel_axi_DelayCycles_1_1   : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_DelayCycles_1_1      : std_logic;  -- ufix1
  SIGNAL data_in_axi_DelayCycles          : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL data_reg_axi_DelayCycles_1_1     : unsigned(9 DOWNTO 0);  -- ufix10

BEGIN
  addr_sel_unsigned <= unsigned(addr_sel);

  
  decode_sel_ip_timestamp_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0002#, 14) ELSE
      '0';

  read_ip_timestamp_unsigned <= unsigned(read_ip_timestamp);

  const_1 <= '1';

  enb <= const_1;

  read_axi_fb_DelayCycles_unsigned <= unsigned(read_axi_fb_DelayCycles);

  
  decode_sel_axi_fb_enable_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0042#, 14) ELSE
      '0';

  
  decode_sel_axi_fb_DelayCycles_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0041#, 14) ELSE
      '0';

  
  decode_sel_axi_fb_InverseBotSwitch_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0040#, 14) ELSE
      '0';

  const_0 <= to_unsigned(0, 32);

  reg_ip_timestamp_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        read_reg_ip_timestamp <= to_unsigned(0, 32);
      ELSIF enb = '1' THEN
        read_reg_ip_timestamp <= read_ip_timestamp_unsigned;
      END IF;
    END IF;
  END PROCESS reg_ip_timestamp_process;


  
  decode_rd_ip_timestamp_1_1 <= const_0 WHEN decode_sel_ip_timestamp_1_1 = '0' ELSE
      read_reg_ip_timestamp;

  reg_axi_fb_InverseBotSwitch_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        read_reg_axi_fb_InverseBotSwitch <= '0';
      ELSIF enb = '1' THEN
        read_reg_axi_fb_InverseBotSwitch <= read_axi_fb_InverseBotSwitch;
      END IF;
    END IF;
  END PROCESS reg_axi_fb_InverseBotSwitch_process;


  data_slice_axi_fb_InverseBotSwitch_1 <= '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & read_reg_axi_fb_InverseBotSwitch;

  
  decode_rd_axi_fb_InverseBotSwitch_1_1 <= decode_rd_ip_timestamp_1_1 WHEN decode_sel_axi_fb_InverseBotSwitch_1_1 = '0' ELSE
      data_slice_axi_fb_InverseBotSwitch_1;

  reg_axi_fb_DelayCycles_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        read_reg_axi_fb_DelayCycles <= to_unsigned(16#000#, 10);
      ELSIF enb = '1' THEN
        read_reg_axi_fb_DelayCycles <= read_axi_fb_DelayCycles_unsigned;
      END IF;
    END IF;
  END PROCESS reg_axi_fb_DelayCycles_process;


  data_slice_axi_fb_DelayCycles_1 <= resize(read_reg_axi_fb_DelayCycles, 32);

  
  decode_rd_axi_fb_DelayCycles_1_1 <= decode_rd_axi_fb_InverseBotSwitch_1_1 WHEN decode_sel_axi_fb_DelayCycles_1_1 = '0' ELSE
      data_slice_axi_fb_DelayCycles_1;

  reg_axi_fb_enable_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        read_reg_axi_fb_enable <= '0';
      ELSIF enb = '1' THEN
        read_reg_axi_fb_enable <= read_axi_fb_enable;
      END IF;
    END IF;
  END PROCESS reg_axi_fb_enable_process;


  data_slice_axi_fb_enable_1 <= '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & read_reg_axi_fb_enable;

  
  decode_rd_axi_fb_enable_1_1 <= decode_rd_axi_fb_DelayCycles_1_1 WHEN decode_sel_axi_fb_enable_1_1 = '0' ELSE
      data_slice_axi_fb_enable_1;

  data_read <= std_logic_vector(decode_rd_axi_fb_enable_1_1);

  
  decode_sel_axi_enable_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0001#, 14) ELSE
      '0';

  reg_enb_axi_enable_1_1 <= decode_sel_axi_enable_1_1 AND wr_enb;

  data_write_unsigned <= unsigned(data_write);

  data_in_axi_enable <= data_write_unsigned(0);

  reg_axi_enable_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        data_reg_axi_enable_1_1 <= '1';
      ELSIF enb = '1' AND reg_enb_axi_enable_1_1 = '1' THEN
        data_reg_axi_enable_1_1 <= data_in_axi_enable;
      END IF;
    END IF;
  END PROCESS reg_axi_enable_1_1_process;


  write_concats_axi_enable_1 <= data_reg_axi_enable_1_1;

  write_axi_enable <= write_concats_axi_enable_1;

  
  decode_sel_axi_InverseBotSwitch_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0043#, 14) ELSE
      '0';

  reg_enb_axi_InverseBotSwitch_1_1 <= decode_sel_axi_InverseBotSwitch_1_1 AND wr_enb;

  data_in_axi_InverseBotSwitch <= data_write_unsigned(0);

  reg_axi_InverseBotSwitch_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        data_reg_axi_InverseBotSwitch_1_1 <= '0';
      ELSIF enb = '1' AND reg_enb_axi_InverseBotSwitch_1_1 = '1' THEN
        data_reg_axi_InverseBotSwitch_1_1 <= data_in_axi_InverseBotSwitch;
      END IF;
    END IF;
  END PROCESS reg_axi_InverseBotSwitch_1_1_process;


  write_concats_axi_InverseBotSwitch_1 <= data_reg_axi_InverseBotSwitch_1_1;

  write_axi_InverseBotSwitch <= write_concats_axi_InverseBotSwitch_1;

  
  decode_sel_axi_EnableOutput_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0044#, 14) ELSE
      '0';

  reg_enb_axi_EnableOutput_1_1 <= decode_sel_axi_EnableOutput_1_1 AND wr_enb;

  data_in_axi_EnableOutput <= data_write_unsigned(0);

  reg_axi_EnableOutput_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        data_reg_axi_EnableOutput_1_1 <= '0';
      ELSIF enb = '1' AND reg_enb_axi_EnableOutput_1_1 = '1' THEN
        data_reg_axi_EnableOutput_1_1 <= data_in_axi_EnableOutput;
      END IF;
    END IF;
  END PROCESS reg_axi_EnableOutput_1_1_process;


  write_concats_axi_EnableOutput_1 <= data_reg_axi_EnableOutput_1_1;

  write_axi_EnableOutput <= write_concats_axi_EnableOutput_1;

  
  decode_sel_axi_DelayCycles_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0045#, 14) ELSE
      '0';

  reg_enb_axi_DelayCycles_1_1 <= decode_sel_axi_DelayCycles_1_1 AND wr_enb;

  data_in_axi_DelayCycles <= data_write_unsigned(9 DOWNTO 0);

  reg_axi_DelayCycles_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset_x = '1' THEN
        data_reg_axi_DelayCycles_1_1 <= to_unsigned(16#000#, 10);
      ELSIF enb = '1' AND reg_enb_axi_DelayCycles_1_1 = '1' THEN
        data_reg_axi_DelayCycles_1_1 <= data_in_axi_DelayCycles;
      END IF;
    END IF;
  END PROCESS reg_axi_DelayCycles_1_1_process;


  write_axi_DelayCycles <= std_logic_vector(data_reg_axi_DelayCycles_1_1);

END rtl;

