-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\Trans_123_dq_V12_ip\Simulation\hdlsrc\Transformation_V12\Trans_123_alphabeta_dq_V12_ip_addr_decoder.vhd
-- Created: 2022-05-03 14:00:47
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Trans_123_alphabeta_dq_V12_ip_addr_decoder
-- Source Path: Trans_123_alphabeta_dq_V12_ip/Trans_123_alphabeta_dq_V12_ip_axi_lite/Trans_123_alphabeta_dq_V12_ip_addr_decoder
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Trans_123_alphabeta_dq_V12_ip_addr_decoder IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        data_write                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        addr_sel                          :   IN    std_logic_vector(13 DOWNTO 0);  -- ufix14
        wr_enb                            :   IN    std_logic;  -- ufix1
        rd_enb                            :   IN    std_logic;  -- ufix1
        read_ip_timestamp                 :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        read_id_AXI                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        read_iq_AXI                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        read_i1_AXI                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        read_i2_AXI                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        read_i3_AXI                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        read_ialpha_AXI                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        read_ibeta_AXI                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        data_read                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_axi_enable                  :   OUT   std_logic;  -- ufix1
        write_theta_offset_AXI            :   OUT   std_logic_vector(23 DOWNTO 0)  -- sfix24_En20
        );
END Trans_123_alphabeta_dq_V12_ip_addr_decoder;


ARCHITECTURE rtl OF Trans_123_alphabeta_dq_V12_ip_addr_decoder IS

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL addr_sel_unsigned                : unsigned(13 DOWNTO 0);  -- ufix14
  SIGNAL decode_sel_ip_timestamp_1_1      : std_logic;  -- ufix1
  SIGNAL const_0                          : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_ip_timestamp_unsigned       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL const_1_1                        : std_logic;  -- ufix1
  SIGNAL read_id_AXI_signed               : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL read_iq_AXI_signed               : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL read_i1_AXI_signed               : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL read_i2_AXI_signed               : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL read_i3_AXI_signed               : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL read_ialpha_AXI_signed           : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL read_ibeta_AXI_signed            : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL decode_sel_ibeta_AXI_1_1         : std_logic;  -- ufix1
  SIGNAL decode_sel_ialpha_AXI_1_1        : std_logic;  -- ufix1
  SIGNAL decode_sel_i3_AXI_1_1            : std_logic;  -- ufix1
  SIGNAL decode_sel_i2_AXI_1_1            : std_logic;  -- ufix1
  SIGNAL decode_sel_i1_AXI_1_1            : std_logic;  -- ufix1
  SIGNAL decode_sel_iq_AXI_1_1            : std_logic;  -- ufix1
  SIGNAL decode_sel_id_AXI_1_1            : std_logic;  -- ufix1
  SIGNAL read_reg_ip_timestamp            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_ip_timestamp_1_1       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_id_AXI                  : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_id_AXI_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_id_AXI_1_1             : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_iq_AXI                  : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_iq_AXI_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_iq_AXI_1_1             : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_i1_AXI                  : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_i1_AXI_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_i1_AXI_1_1             : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_i2_AXI                  : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_i2_AXI_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_i2_AXI_1_1             : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_i3_AXI                  : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_i3_AXI_1              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_i3_AXI_1_1             : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_ialpha_AXI              : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_ialpha_AXI_1          : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_ialpha_AXI_1_1         : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_ibeta_AXI               : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL data_slice_ibeta_AXI_1           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_ibeta_AXI_1_1          : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_axi_enable_1_1        : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_enable_1_1           : std_logic;  -- ufix1
  SIGNAL data_write_unsigned              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_in_axi_enable               : std_logic;  -- ufix1
  SIGNAL data_reg_axi_enable_1_1          : std_logic;  -- ufix1
  SIGNAL decode_sel_theta_offset_AXI_1_1  : std_logic;  -- ufix1
  SIGNAL reg_enb_theta_offset_AXI_1_1     : std_logic;  -- ufix1
  SIGNAL data_in_theta_offset_AXI         : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL data_reg_theta_offset_AXI_1_1    : signed(23 DOWNTO 0);  -- sfix24_En20

BEGIN
  addr_sel_unsigned <= unsigned(addr_sel);

  
  decode_sel_ip_timestamp_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0002#, 14) ELSE
      '0';

  const_0 <= to_unsigned(0, 32);

  read_ip_timestamp_unsigned <= unsigned(read_ip_timestamp);

  const_1_1 <= '1';

  enb <= const_1_1;

  read_id_AXI_signed <= signed(read_id_AXI);

  read_iq_AXI_signed <= signed(read_iq_AXI);

  read_i1_AXI_signed <= signed(read_i1_AXI);

  read_i2_AXI_signed <= signed(read_i2_AXI);

  read_i3_AXI_signed <= signed(read_i3_AXI);

  read_ialpha_AXI_signed <= signed(read_ialpha_AXI);

  read_ibeta_AXI_signed <= signed(read_ibeta_AXI);

  
  decode_sel_ibeta_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0047#, 14) ELSE
      '0';

  
  decode_sel_ialpha_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0046#, 14) ELSE
      '0';

  
  decode_sel_i3_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0045#, 14) ELSE
      '0';

  
  decode_sel_i2_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0044#, 14) ELSE
      '0';

  
  decode_sel_i1_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0043#, 14) ELSE
      '0';

  
  decode_sel_iq_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0042#, 14) ELSE
      '0';

  
  decode_sel_id_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0041#, 14) ELSE
      '0';

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

  reg_id_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_id_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_id_AXI <= read_id_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_id_AXI_process;


  data_slice_id_AXI_1 <= unsigned(resize(read_reg_id_AXI, 32));

  
  decode_rd_id_AXI_1_1 <= decode_rd_ip_timestamp_1_1 WHEN decode_sel_id_AXI_1_1 = '0' ELSE
      data_slice_id_AXI_1;

  reg_iq_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_iq_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_iq_AXI <= read_iq_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_iq_AXI_process;


  data_slice_iq_AXI_1 <= unsigned(resize(read_reg_iq_AXI, 32));

  
  decode_rd_iq_AXI_1_1 <= decode_rd_id_AXI_1_1 WHEN decode_sel_iq_AXI_1_1 = '0' ELSE
      data_slice_iq_AXI_1;

  reg_i1_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_i1_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_i1_AXI <= read_i1_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_i1_AXI_process;


  data_slice_i1_AXI_1 <= unsigned(resize(read_reg_i1_AXI, 32));

  
  decode_rd_i1_AXI_1_1 <= decode_rd_iq_AXI_1_1 WHEN decode_sel_i1_AXI_1_1 = '0' ELSE
      data_slice_i1_AXI_1;

  reg_i2_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_i2_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_i2_AXI <= read_i2_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_i2_AXI_process;


  data_slice_i2_AXI_1 <= unsigned(resize(read_reg_i2_AXI, 32));

  
  decode_rd_i2_AXI_1_1 <= decode_rd_i1_AXI_1_1 WHEN decode_sel_i2_AXI_1_1 = '0' ELSE
      data_slice_i2_AXI_1;

  reg_i3_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_i3_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_i3_AXI <= read_i3_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_i3_AXI_process;


  data_slice_i3_AXI_1 <= unsigned(resize(read_reg_i3_AXI, 32));

  
  decode_rd_i3_AXI_1_1 <= decode_rd_i2_AXI_1_1 WHEN decode_sel_i3_AXI_1_1 = '0' ELSE
      data_slice_i3_AXI_1;

  reg_ialpha_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_ialpha_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_ialpha_AXI <= read_ialpha_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_ialpha_AXI_process;


  data_slice_ialpha_AXI_1 <= unsigned(resize(read_reg_ialpha_AXI, 32));

  
  decode_rd_ialpha_AXI_1_1 <= decode_rd_i3_AXI_1_1 WHEN decode_sel_ialpha_AXI_1_1 = '0' ELSE
      data_slice_ialpha_AXI_1;

  reg_ibeta_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_ibeta_AXI <= to_signed(16#00000#, 18);
      ELSIF enb = '1' THEN
        read_reg_ibeta_AXI <= read_ibeta_AXI_signed;
      END IF;
    END IF;
  END PROCESS reg_ibeta_AXI_process;


  data_slice_ibeta_AXI_1 <= unsigned(resize(read_reg_ibeta_AXI, 32));

  
  decode_rd_ibeta_AXI_1_1 <= decode_rd_ialpha_AXI_1_1 WHEN decode_sel_ibeta_AXI_1_1 = '0' ELSE
      data_slice_ibeta_AXI_1;

  data_read <= std_logic_vector(decode_rd_ibeta_AXI_1_1);

  
  decode_sel_axi_enable_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0001#, 14) ELSE
      '0';

  reg_enb_axi_enable_1_1 <= decode_sel_axi_enable_1_1 AND wr_enb;

  data_write_unsigned <= unsigned(data_write);

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


  
  decode_sel_theta_offset_AXI_1_1 <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0040#, 14) ELSE
      '0';

  reg_enb_theta_offset_AXI_1_1 <= decode_sel_theta_offset_AXI_1_1 AND wr_enb;

  data_in_theta_offset_AXI <= signed(data_write_unsigned(23 DOWNTO 0));

  reg_theta_offset_AXI_1_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        data_reg_theta_offset_AXI_1_1 <= to_signed(16#000000#, 24);
      ELSIF enb = '1' AND reg_enb_theta_offset_AXI_1_1 = '1' THEN
        data_reg_theta_offset_AXI_1_1 <= data_in_theta_offset_AXI;
      END IF;
    END IF;
  END PROCESS reg_theta_offset_AXI_1_1_process;


  write_theta_offset_AXI <= std_logic_vector(data_reg_theta_offset_AXI_1_1);

  write_axi_enable <= data_reg_axi_enable_1_1;

END rtl;
