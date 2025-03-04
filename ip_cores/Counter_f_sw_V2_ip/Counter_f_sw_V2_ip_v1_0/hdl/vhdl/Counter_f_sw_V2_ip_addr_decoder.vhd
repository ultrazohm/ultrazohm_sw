-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\PMSM_Flux_NonLinear_FCS_FixPoint_Np1_V7\Counter_f_sw_V2_ip_addr_decoder.vhd
-- Created: 2020-04-27 19:16:02
-- 
-- Generated by MATLAB 9.4 and HDL Coder 3.12
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Counter_f_sw_V2_ip_addr_decoder
-- Source Path: Counter_f_sw_V2_ip/Counter_f_sw_V2_ip_axi_lite/Counter_f_sw_V2_ip_addr_decoder
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Counter_f_sw_V2_ip_addr_decoder IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        data_write                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        addr_sel                          :   IN    std_logic_vector(13 DOWNTO 0);  -- ufix14
        wr_enb                            :   IN    std_logic;  -- ufix1
        rd_enb                            :   IN    std_logic;  -- ufix1
        read_ip_timestamp                 :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        read_switchNumb_AXI               :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25
        data_read                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        write_axi_enable                  :   OUT   std_logic;  -- ufix1
        write_bResetAXI                   :   OUT   std_logic  -- ufix1
        );
END Counter_f_sw_V2_ip_addr_decoder;


ARCHITECTURE rtl OF Counter_f_sw_V2_ip_addr_decoder IS

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL addr_sel_unsigned                : unsigned(13 DOWNTO 0);  -- ufix14
  SIGNAL decode_sel_ip_timestamp          : std_logic;  -- ufix1
  SIGNAL read_ip_timestamp_unsigned       : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL const_1                          : std_logic;  -- ufix1
  SIGNAL read_switchNumb_AXI_unsigned     : unsigned(24 DOWNTO 0);  -- ufix25
  SIGNAL decode_sel_switchNumb_AXI        : std_logic;  -- ufix1
  SIGNAL const_0                          : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_ip_timestamp            : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_ip_timestamp           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL read_reg_switchNumb_AXI          : unsigned(24 DOWNTO 0);  -- ufix25
  SIGNAL data_in_switchNumb_AXI           : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_rd_switchNumb_AXI         : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL decode_sel_axi_enable            : std_logic;  -- ufix1
  SIGNAL reg_enb_axi_enable               : std_logic;  -- ufix1
  SIGNAL data_write_unsigned              : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL data_in_axi_enable               : std_logic;  -- ufix1
  SIGNAL write_reg_axi_enable             : std_logic;  -- ufix1
  SIGNAL decode_sel_bResetAXI             : std_logic;  -- ufix1
  SIGNAL reg_enb_bResetAXI                : std_logic;  -- ufix1
  SIGNAL data_in_bResetAXI                : std_logic;  -- ufix1
  SIGNAL write_reg_bResetAXI              : std_logic;  -- ufix1

BEGIN
  addr_sel_unsigned <= unsigned(addr_sel);

  
  decode_sel_ip_timestamp <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0002#, 14) ELSE
      '0';

  read_ip_timestamp_unsigned <= unsigned(read_ip_timestamp);

  const_1 <= '1';

  enb <= const_1;

  read_switchNumb_AXI_unsigned <= unsigned(read_switchNumb_AXI);

  
  decode_sel_switchNumb_AXI <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0041#, 14) ELSE
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


  
  decode_rd_ip_timestamp <= const_0 WHEN decode_sel_ip_timestamp = '0' ELSE
      read_reg_ip_timestamp;

  reg_switchNumb_AXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        read_reg_switchNumb_AXI <= to_unsigned(16#0000000#, 25);
      ELSIF enb = '1' THEN
        read_reg_switchNumb_AXI <= read_switchNumb_AXI_unsigned;
      END IF;
    END IF;
  END PROCESS reg_switchNumb_AXI_process;


  data_in_switchNumb_AXI <= resize(read_reg_switchNumb_AXI, 32);

  
  decode_rd_switchNumb_AXI <= decode_rd_ip_timestamp WHEN decode_sel_switchNumb_AXI = '0' ELSE
      data_in_switchNumb_AXI;

  data_read <= std_logic_vector(decode_rd_switchNumb_AXI);

  
  decode_sel_axi_enable <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0001#, 14) ELSE
      '0';

  reg_enb_axi_enable <= decode_sel_axi_enable AND wr_enb;

  data_write_unsigned <= unsigned(data_write);

  data_in_axi_enable <= data_write_unsigned(0);

  reg_axi_enable_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        write_reg_axi_enable <= '1';
      ELSIF enb = '1' AND reg_enb_axi_enable = '1' THEN
        write_reg_axi_enable <= data_in_axi_enable;
      END IF;
    END IF;
  END PROCESS reg_axi_enable_process;


  write_axi_enable <= write_reg_axi_enable;

  
  decode_sel_bResetAXI <= '1' WHEN addr_sel_unsigned = to_unsigned(16#0040#, 14) ELSE
      '0';

  reg_enb_bResetAXI <= decode_sel_bResetAXI AND wr_enb;

  data_in_bResetAXI <= data_write_unsigned(0);

  reg_bResetAXI_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        write_reg_bResetAXI <= '0';
      ELSIF enb = '1' AND reg_enb_bResetAXI = '1' THEN
        write_reg_bResetAXI <= data_in_bResetAXI;
      END IF;
    END IF;
  END PROCESS reg_bResetAXI_process;


  write_bResetAXI <= write_reg_bResetAXI;

END rtl;

