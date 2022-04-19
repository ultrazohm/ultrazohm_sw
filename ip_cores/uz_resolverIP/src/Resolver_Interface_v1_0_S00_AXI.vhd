
-- Company: TUM
-- Engineer: Felix Kaiser & Thomas Effenberger
-- 
-- Create Date: 06/14/2020 02:51:13 PM
-- Design Name: 
-- Module Name: AD2S1210_Interface - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;




entity Resolver_Interface_v1_0_S00_AXI is
	generic (
		-- Users to add parameters here
		SPI_clk_div			: INTEGER	:=  4 ;    -- SPI clock divider (12MHz)
		-- User parameters ends
		-- Do not modify the parameters beyond this line
		
		C_S_AXI_DATA_WIDTH	: integer	:= 32;-- Width of S_AXI data bus
		
		C_S_AXI_ADDR_WIDTH	: integer	:= 4 -- Width of S_AXI address bus
	);
	port (
		-- Users to add ports here

		SPI_MOSI				: OUT STD_LOGIC;   -- SPI master out (connect to chip)
		SPI_MISO				: IN  STD_LOGIC;   -- SPI master in (connect to chip)
		SPI_SCLK				: OUT STD_LOGIC;   -- SPI clock (connect to chip)
		SPI_SS					: OUT STD_LOGIC;   -- SPI slave select (connect to chip)
		
      
		AD2S1210_n_reset		: OUT STD_LOGIC;   -- reset (connect to chip)
		AD2S1210_n_sample		: OUT STD_LOGIC;   -- sample start (connect to chip)
		AD2S1210_n_fsync		: OUT STD_LOGIC;   -- synchronization signal (connect to chip)
		AD2S1210_mode_A0		: OUT STD_LOGIC;   -- mode select 0 (connect to chip)
		AD2S1210_mode_A1		: OUT STD_LOGIC;   -- mode select 1 (connect to chip)

		busy_m					: OUT STD_LOGIC;   -- busy / data ready signal      
		error_flag_m			: OUT STD_LOGIC;   -- error occurred, reset needed

		sample_trigger			: IN STD_LOGIC;   -- Trigger input from PL
		position_out_m			: OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  
		velocity_out_m 			: OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  
		valid_m					: OUT STD_LOGIC;   -- data at output are valid
        
        -- User ports ends
		-- Do not modify the ports beyond this line

		-- Global Clock Signal
		S_AXI_ACLK	: in std_logic;
		-- Global Reset Signal. This Signal is Active LOW
		S_AXI_ARESETN	: in std_logic;
		-- Write address (issued by master, acceped by Slave)
		S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		-- Write channel Protection type. This signal indicates the
			-- privilege and security level of the transaction, and whether
			-- the transaction is a data access or an instruction access.
		S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
		-- Write address valid. This signal indicates that the master signaling
    		-- valid write address and control information.
		S_AXI_AWVALID	: in std_logic;
		-- Write address ready. This signal indicates that the slave is ready
    		-- to accept an address and associated control signals.
		S_AXI_AWREADY	: out std_logic;
		-- Write data (issued by master, acceped by Slave) 
		S_AXI_WDATA	: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		-- Write strobes. This signal indicates which byte lanes hold
    		-- valid data. There is one write strobe bit for each eight
    		-- bits of the write data bus.    
		S_AXI_WSTRB	: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		-- Write valid. This signal indicates that valid write
    		-- data and strobes are available.
		S_AXI_WVALID	: in std_logic;
		-- Write ready. This signal indicates that the slave
    		-- can accept the write data.
		S_AXI_WREADY	: out std_logic;
		-- Write response. This signal indicates the status
    		-- of the write transaction.
		S_AXI_BRESP	: out std_logic_vector(1 downto 0);
		-- Write response valid. This signal indicates that the channel
    		-- is signaling a valid write response.
		S_AXI_BVALID	: out std_logic;
		-- Response ready. This signal indicates that the master
    		-- can accept a write response.
		S_AXI_BREADY	: in std_logic;
		-- Read address (issued by master, acceped by Slave)
		S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		-- Protection type. This signal indicates the privilege
    		-- and security level of the transaction, and whether the
    		-- transaction is a data access or an instruction access.
		S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
		-- Read address valid. This signal indicates that the channel
    		-- is signaling valid read address and control information.
		S_AXI_ARVALID	: in std_logic;
		-- Read address ready. This signal indicates that the slave is
    		-- ready to accept an address and associated control signals.
		S_AXI_ARREADY	: out std_logic;
		-- Read data (issued by slave)
		S_AXI_RDATA	: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		-- Read response. This signal indicates the status of the
    		-- read transfer.
		S_AXI_RRESP	: out std_logic_vector(1 downto 0);
		-- Read valid. This signal indicates that the channel is
    		-- signaling the required read data.
		S_AXI_RVALID	: out std_logic;
		-- Read ready. This signal indicates that the master can
    		-- accept the read data and response information.
		S_AXI_RREADY	: in std_logic
	);
end Resolver_Interface_v1_0_S00_AXI;

architecture arch_imp of Resolver_Interface_v1_0_S00_AXI is

	-- AXI4LITE signals
	signal axi_awaddr	: std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
	signal axi_awready	: std_logic;
	signal axi_wready	: std_logic;
	signal axi_bresp	: std_logic_vector(1 downto 0);
	signal axi_bvalid	: std_logic;
	signal axi_araddr	: std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
	signal axi_arready	: std_logic;
	signal axi_rdata	: std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal axi_rresp	: std_logic_vector(1 downto 0);
	signal axi_rvalid	: std_logic;

	-- Example-specific design signals
	-- local parameter for addressing 32 bit / 64 bit C_S_AXI_DATA_WIDTH
	-- ADDR_LSB is used for addressing 32/64 bit registers/memories
	-- ADDR_LSB = 2 for 32 bits (n downto 2)
	-- ADDR_LSB = 3 for 64 bits (n downto 3)
	constant ADDR_LSB  : integer := (C_S_AXI_DATA_WIDTH/32)+ 1;
	constant OPT_MEM_ADDR_BITS : integer := 1;
	------------------------------------------------
	---- Signals for user logic register space example
	--------------------------------------------------
constant in_simulation : boolean := false
--pragma synthesis_off
                                    or true
--pragma synthesis_on
;
constant in_synthesis : boolean := not in_simulation;

    signal slv_reg0	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); 

	signal slv_reg1	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg2	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg3	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg_rden	: std_logic;
	signal slv_reg_wren	: std_logic;
	signal reg_data_out	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal byte_index	: integer;
	signal aw_en	: std_logic;
	
	--Signals to map the components--------------------------------------------------------
	signal enable_s  			: STD_LOGIC;					--System enable
    signal go_sig_s				: STD_LOGIC;					--global Trigger
    signal sample_s				: STD_LOGIC;					--activates sampling
    signal reset_n_s            : STD_LOGIC;					--reset
    
    signal busy_s		        : STD_LOGIC;					--busy indicator
    signal error_flag_s		    : STD_LOGIC;					--Error occured, need reset
    
    signal dataMode_s           : STD_LOGIC;					--control signals for A0 / A1, 1 if Velocity Mode
    signal configMode_s         : STD_LOGIC:='1';				--control signals for A0 / A1, 1 if Config Mode, 0 if Position/Velocity Mode
    
    signal register_rw_s        : STD_LOGIC;					-- 0 = read register, 1 = write register
    signal register_adr_in_s    : STD_LOGIC_VECTOR (7 downto 0);-- Register address
    signal register_val_in_s    : STD_LOGIC_VECTOR (7 downto 0);-- Value to write to register
    signal register_val_out_s   : STD_LOGIC_VECTOR (7 downto 0);-- Read value from register
    signal data_out_s           : STD_LOGIC_VECTOR (15 downto 0);-- Read value in normal mode
	
	    -- Local Variables-------------------------------------------------------------------
    signal velocity_bit       : STD_LOGIC:='0';					-- written by AXI, 1 if velocity is to be measured
    signal position_bit       : STD_LOGIC:='0';					-- written by AXI,1 if position is to be measured
    signal velocity_bit_latch : STD_LOGIC:= '0';				-- for change detection
    signal position_bit_latch : STD_LOGIC:= '0';				-- for change detection
    signal go_bit             : STD_LOGIC;						-- written by AXI, for triggering register readout
    signal position_out       : STD_LOGIC_VECTOR(15 DOWNTO 0);	-- data storage for position value
    signal velocity_out       : STD_LOGIC_VECTOR(15 DOWNTO 0);	-- data storage for velocity value
    signal valid              : STD_LOGIC;   					-- data at output are valid

type modes_ResolverIP is 
(
    Config_Mode,
    Position_Mode,
    Velocity_Mode,    
    PositionAndVelocity_Mode
);

signal mode_ResolverIP : modes_ResolverIP;


type states_TopLevel_StateMachine is
(
    Wait_For_Trigger,
    Start_Register_ReadWrite,
    Start_Data_Read,
    Reset_Go_Signal,
    Read_Position,
    Read_Velocity,
    Read_Position_And_Init_Velocity_Read,
    Reset_Second_Go_Signal
); 

signal state_TopLevel_StateMachine : states_TopLevel_StateMachine;

	--Components---------------------------------------------------------------------
	component AD2S1210_Interface is
		Generic(
			SPI_Datalength     : INTEGER   :=  8;                    -- SPI data length
			SPI_Slavenumber    : INTEGER   :=  1;                    -- number of SPI slaves
			SPI_cpha           : STD_LOGIC := '1';                   -- SPI clock phase
			SPI_cpol           : STD_LOGIC := '0';                   -- SPI clock polarity
			SPI_cont           : STD_LOGIC := '0';                   -- SPI continuous mode
			SPI_clk_div        : INTEGER   :=  4                     -- SPI clock divider (12MHz)
		);
		Port (
			clock              : IN  STD_LOGIC;                      -- system clock
			reset_n            : IN  STD_LOGIC;                      -- synchronous reset
			enable             : IN  STD_LOGIC;                      -- system enable
			go_sig             : IN  STD_LOGIC;                      -- global trigger
			sample             : IN  STD_LOGIC;                      -- pull NSample low when go sig is triggered
			busy               : OUT STD_LOGIC;                      -- busy / data ready signal
			error_flag         : OUT STD_LOGIC;                      -- error occured, need reset
			dataMode           : IN  STD_LOGIC;                      -- 0 = position mode, 1 = velocity mode
			configMode         : IN  STD_LOGIC;                      -- if configMode = 1, dataMode is ignored
			register_rw        : IN  STD_LOGIC;                      -- 0 = read register, 1 = write register
			register_adr_in    : IN  STD_LOGIC_VECTOR (7 downto 0);  -- register address
			register_val_in    : IN  STD_LOGIC_VECTOR (7 downto 0);  -- value to write to register
			register_val_out   : OUT STD_LOGIC_VECTOR (7 downto 0);  -- read value from register
			data_out           : OUT STD_LOGIC_VECTOR (15 downto 0); -- read value in normal mode
			--
			SPI_MOSI           : OUT STD_LOGIC;                      -- SPI master out (connect to chip)
			SPI_MISO           : IN  STD_LOGIC;                      -- SPI master in (connect to chip)
			SPI_SCLK           : OUT STD_LOGIC;                      -- SPI clock (connect to chip)
			SPI_SS             : OUT STD_LOGIC;                      -- SPI slave select (connect to chip)
			--
			AD2S1210_n_reset   : OUT STD_LOGIC;                      -- reset (connect to chip)
			AD2S1210_n_sample  : OUT STD_LOGIC;                      -- sample start (connect to chip)
			AD2S1210_n_fsync   : OUT STD_LOGIC;                      -- synchronization signal (connect to chip)
			AD2S1210_mode_A0   : OUT STD_LOGIC;                      -- mode select 0 (connect to chip)
			AD2S1210_mode_A1   : OUT STD_LOGIC                       -- mode select 1 (connect to chip)
		);
	end component AD2S1210_Interface;


begin

    g_SIM_REG_INIT : if in_simulation = true generate
     slv_reg0 <= "00000000000000000000000011110001"; -- INIT for simulation
    end generate g_SIM_REG_INIT;	

	-- I/O Connections assignments

	S_AXI_AWREADY	<= axi_awready;
	S_AXI_WREADY	<= axi_wready;
	S_AXI_BRESP	<= axi_bresp;
	S_AXI_BVALID	<= axi_bvalid;
	S_AXI_ARREADY	<= axi_arready;
	S_AXI_RDATA	<= axi_rdata;
	S_AXI_RRESP	<= axi_rresp;
	S_AXI_RVALID	<= axi_rvalid;
	-- Implement axi_awready generation
	-- axi_awready is asserted for one S_AXI_ACLK clock cycle when both
	-- S_AXI_AWVALID and S_AXI_WVALID are asserted. axi_awready is
	-- de-asserted when reset is low.

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_awready <= '0';
	      aw_en <= '1';
	    else
	      if (axi_awready = '0' and S_AXI_AWVALID = '1' and S_AXI_WVALID = '1' and aw_en = '1') then
	        -- slave is ready to accept write address when
	        -- there is a valid write address and write data
	        -- on the write address and data bus. This design 
	        -- expects no outstanding transactions. 
	           axi_awready <= '1';
	           aw_en <= '0';
	        elsif (S_AXI_BREADY = '1' and axi_bvalid = '1') then
	           aw_en <= '1';
	           axi_awready <= '0';
	      else
	        axi_awready <= '0';
	      end if;
	    end if;
	  end if;
	end process;

	-- Implement axi_awaddr latching
	-- This process is used to latch the address when both 
	-- S_AXI_AWVALID and S_AXI_WVALID are valid. 

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_awaddr <= (others => '0');
	    else
	      if (axi_awready = '0' and S_AXI_AWVALID = '1' and S_AXI_WVALID = '1' and aw_en = '1') then
	        -- Write Address latching
	        axi_awaddr <= S_AXI_AWADDR;
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement axi_wready generation
	-- axi_wready is asserted for one S_AXI_ACLK clock cycle when both
	-- S_AXI_AWVALID and S_AXI_WVALID are asserted. axi_wready is 
	-- de-asserted when reset is low. 

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_wready <= '0';
	    else
	      if (axi_wready = '0' and S_AXI_WVALID = '1' and S_AXI_AWVALID = '1' and aw_en = '1') then
	          -- slave is ready to accept write data when 
	          -- there is a valid write address and write data
	          -- on the write address and data bus. This design 
	          -- expects no outstanding transactions.           
	          axi_wready <= '1';
	      else
	        axi_wready <= '0';
	      end if;
	    end if;
	  end if;
	end process; 

	-- Implement memory mapped register select and write logic generation
	-- The write data is accepted and written to memory mapped registers when
	-- axi_awready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted. Write strobes are used to
	-- select byte enables of slave registers while writing.
	-- These registers are cleared when reset (active low) is applied.
	-- Slave register write enable is asserted when valid address and data are available
	-- and the slave is ready to accept the write address and write data.
	slv_reg_wren <= axi_wready and S_AXI_WVALID and axi_awready and S_AXI_AWVALID ;
g_SYN_REG_RESET : if in_synthesis = true generate	
	process (S_AXI_ACLK)
	variable loc_addr :std_logic_vector(OPT_MEM_ADDR_BITS downto 0); 
	begin
	  if rising_edge(S_AXI_ACLK) then 
	   if S_AXI_ARESETN = '0' then 
		slv_reg0 <= (others => '0');
	      slv_reg1 <= (others => '0');
	      slv_reg2 <= (others => '0');
	      slv_reg3 <= (others => '0');
	    else
	      loc_addr := axi_awaddr(ADDR_LSB + OPT_MEM_ADDR_BITS downto ADDR_LSB);
	      if (slv_reg_wren = '1') then
	        case loc_addr is
	          when b"00" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 0
	                slv_reg0(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	                
	                
	              end if;
	            end loop;
	            
	  
	                
	          when b"01" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 1
	                slv_reg1(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"10" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 2
	                slv_reg2(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"11" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 3
	                slv_reg3(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when others =>
	            slv_reg0 <= slv_reg0;
	            slv_reg1 <= slv_reg1;
	            slv_reg2 <= slv_reg2;
	            slv_reg3 <= slv_reg3;
	        end case;
	      end if;
	    end if;
	  end if;                   
	end process; 
end generate g_SYN_REG_RESET;
	-- Implement write response logic generation
	-- The write response and response valid signals are asserted by the slave 
	-- when axi_wready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted.  
	-- This marks the acceptance of address and indicates the status of 
	-- write transaction.

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_bvalid  <= '0';
	      axi_bresp   <= "00"; --need to work more on the responses
	    else
	      if (axi_awready = '1' and S_AXI_AWVALID = '1' and axi_wready = '1' and S_AXI_WVALID = '1' and axi_bvalid = '0'  ) then
	        axi_bvalid <= '1';
	        axi_bresp  <= "00"; 
	      elsif (S_AXI_BREADY = '1' and axi_bvalid = '1') then   --check if bready is asserted while bvalid is high)
	        axi_bvalid <= '0';                                 -- (there is a possibility that bready is always asserted high)
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement axi_arready generation
	-- axi_arready is asserted for one S_AXI_ACLK clock cycle when
	-- S_AXI_ARVALID is asserted. axi_awready is 
	-- de-asserted when reset (active low) is asserted. 
	-- The read address is also latched when S_AXI_ARVALID is 
	-- asserted. axi_araddr is reset to zero on reset assertion.

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_arready <= '0';
	      axi_araddr  <= (others => '1');
	    else
	      if (axi_arready = '0' and S_AXI_ARVALID = '1') then
	        -- indicates that the slave has acceped the valid read address
	        axi_arready <= '1';
	        -- Read Address latching 
	        axi_araddr  <= S_AXI_ARADDR;           
	      else
	        axi_arready <= '0';
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement axi_arvalid generation
	-- axi_rvalid is asserted for one S_AXI_ACLK clock cycle when both 
	-- S_AXI_ARVALID and axi_arready are asserted. The slave registers 
	-- data are available on the axi_rdata bus at this instance. The 
	-- assertion of axi_rvalid marks the validity of read data on the 
	-- bus and axi_rresp indicates the status of read transaction.axi_rvalid 
	-- is deasserted on reset (active low). axi_rresp and axi_rdata are 
	-- cleared to zero on reset (active low).  
	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then
	    if S_AXI_ARESETN = '0' then
	      axi_rvalid <= '0';
	      axi_rresp  <= "00";
	    else
	      if (axi_arready = '1' and S_AXI_ARVALID = '1' and axi_rvalid = '0') then
	        -- Valid read data is available at the read data bus
	        axi_rvalid <= '1';
	        axi_rresp  <= "00"; -- 'OKAY' response
	      elsif (axi_rvalid = '1' and S_AXI_RREADY = '1') then
	        -- Read data is accepted by the master
	        axi_rvalid <= '0';
	      end if;            
	    end if;
	  end if;
	end process;

	-- Implement memory mapped register select and read logic generation
	-- Slave register read enable is asserted when valid address is available
	-- and the slave is ready to accept the read address.
	slv_reg_rden <= axi_arready and S_AXI_ARVALID and (not axi_rvalid) ;

	process (slv_reg0, slv_reg1, slv_reg2, slv_reg3, axi_araddr, S_AXI_ARESETN, slv_reg_rden,
	enable_s,go_sig_s,busy_s,error_flag_s,velocity_bit,position_bit,register_rw_s,reset_n_s,valid,dataMode_s,configMode_s,
	position_out,velocity_out,register_adr_in_s,register_val_out_s)
	variable loc_addr :std_logic_vector(OPT_MEM_ADDR_BITS downto 0);
	begin
		-- Address decoding for reading registers
		loc_addr := axi_araddr(ADDR_LSB + OPT_MEM_ADDR_BITS downto ADDR_LSB);
		case loc_addr is
		when b"00" =>
			reg_data_out(31 downto 11) <= (others => '0');
			reg_data_out(0) <= enable_s;
			reg_data_out(1) <= go_sig_s;
			reg_data_out(2) <= busy_s;
			reg_data_out(3) <= error_flag_s;

			reg_data_out(4) <= velocity_bit;
			reg_data_out(5) <= position_bit;
			reg_data_out(6) <= register_rw_s;
			reg_data_out(7) <= reset_n_s;
			reg_data_out(8) <= valid;
			
			reg_data_out(9) <= dataMode_s;		-- for debugging
			reg_data_out(10) <= configMode_s;	-- for debugging
		when b"01" =>
			reg_data_out(15 downto 0) <= position_out(15 downto 0);	--write position to first 2 bytes
			reg_data_out(31 downto 16) <= velocity_out(15 downto 0);--write velocity to last 2 bytes
		when b"10" =>
			reg_data_out(31 downto 8) <= (others => '0');
			reg_data_out(7 downto 0) <= register_adr_in_s;
		when b"11" =>
			reg_data_out(31 downto 8) <= (others => '0');
			reg_data_out(7 downto 0) <= register_val_out_s;
		when others =>
			reg_data_out  <= (others => '0');
	    end case;
	end process; 

	-- Output register or memory read data
	process( S_AXI_ACLK ) is
	begin
	  if (rising_edge (S_AXI_ACLK)) then
	    if ( S_AXI_ARESETN = '0' ) then
	      axi_rdata  <= (others => '0');
	    else
	      if (slv_reg_rden = '1') then
	        -- When there is a valid read address (S_AXI_ARVALID) with 
	        -- acceptance of read address by the slave (axi_arready), 
	        -- output the read dada 
	        -- Read address mux
	          axi_rdata <= reg_data_out;     -- register read data
	      end if;   
	    end if;
	  end if;
	end process;


	-- Add user logic here

	AD2S1210_Handler_1 : AD2S1210_Interface
	Generic map(
		SPI_clk_div            => SPI_clk_div
	)
	Port map(
		clock                  => S_AXI_ACLK,
		reset_n                => reset_n_s,
		enable                 => enable_s,
		go_sig                 => go_sig_s,
		sample                =>sample_s,
		busy                   => busy_s,
		error_flag             => error_flag_s,
		dataMode               => dataMode_s,
		configMode             => configMode_s,
		register_rw            => register_rw_s,
		register_adr_in        => register_adr_in_s,
		register_val_in        => register_val_in_s,
		register_val_out       => register_val_out_s,
		data_out               => data_out_s,
		--
		AD2S1210_n_reset       => AD2S1210_n_reset,
		AD2S1210_n_sample      => AD2S1210_n_sample,
		AD2S1210_n_fsync       => AD2S1210_n_fsync,
		AD2S1210_mode_A0       => AD2S1210_mode_A0,
		AD2S1210_mode_A1       => AD2S1210_mode_A1,
		--
		SPI_MOSI               => SPI_MOSI,
		SPI_MISO               => SPI_MISO,
		SPI_SCLK               => SPI_SCLK,
		SPI_SS                 => SPI_SS
	);


	-- Signals from AXI registers to slave
	enable_s			<= slv_reg0(0);
	go_bit				<= slv_reg0(1);
	velocity_bit		<= slv_reg0(4);
	position_bit		<= slv_reg0(5);
	register_rw_s		<= slv_reg0(6);
	reset_n_s			<= S_AXI_ARESETN AND slv_reg0(7);  -- combine two reset sources

	-- Signals from slave to master
	
	busy_m			<= busy_s;
	error_flag_m	<= error_flag_s;
	valid_m			<= valid;
	position_out_m	<= position_out;
	velocity_out_m	<= velocity_out;



	-- State machine process -----------------------------------------------------------------------
	StateMachine : process (S_AXI_ACLK)
	begin
		if (position_bit /= position_bit_latch OR velocity_bit /= velocity_bit_latch) then     -- Reset State Machine if Mode Change
			if (position_bit = '0' AND velocity_bit = '0') then
				mode_ResolverIP <= Config_Mode;
			elsif (position_bit = '1' AND velocity_bit = '0') then
				mode_ResolverIP <= Position_Mode;
			elsif (position_bit = '0' AND velocity_bit = '1') then
				mode_ResolverIP <= Velocity_Mode;
			else
				mode_ResolverIP <= PositionAndVelocity_Mode;
			end if;
			state_TopLevel_StateMachine <= Wait_For_Trigger;
			position_bit_latch <= position_bit;
			velocity_bit_latch <= velocity_bit;
		else
			if (rising_edge (S_AXI_ACLK)) then
				case (state_TopLevel_StateMachine) is
				----------------------------------------------------------------------------------------
				when Wait_For_Trigger =>			-- Status at power-up
				
					case (mode_ResolverIP) is		-- Set A0/A1 signals accordingly, process apllicable trigger signal
					when Config_Mode =>
						configMode_s <= '1'; 
						dataMode_s <= '1';
						
						if (go_bit = '1' AND busy_s = '0') then
							state_TopLevel_StateMachine <= Start_Register_ReadWrite;
						end if;
					when Position_Mode =>
						configMode_s <= '0';
						dataMode_s <= '0';
						
						if (sample_trigger = '1' AND busy_s = '0') then
							state_TopLevel_StateMachine <= Start_Data_Read;
						end if;
					when Velocity_Mode =>
						configMode_s <= '0';
						dataMode_s <= '1';  
						if (sample_trigger = '1' AND busy_s = '0') then
							state_TopLevel_StateMachine <= Start_Data_Read;
						end if;
					when PositionAndVelocity_Mode =>
						configMode_s <= '0'; -- set configMode for lower level state machine
						dataMode_s <= '0';
						if (sample_trigger = '1' AND busy_s = '0') then
							state_TopLevel_StateMachine <= Start_Data_Read;
						end if;
					when others =>
					end case;
					----------------------------------------------------------------------------------------
				when Start_Register_ReadWrite => 			-- Read/Write Register Value
					-- Copy register address
					register_adr_in_s <= slv_reg2(7 downto 0);
					-- If in write mode, copy register value
					if (register_rw_s = '1') then
						register_val_in_s <= slv_reg1(7 downto 0);
					end if;
					-- Start operation by setting go signal
					go_sig_s <= '1';
					if busy_s = '1' then
						state_TopLevel_StateMachine <= Reset_Go_Signal;
					end if;
					----------------------------------------------------------------------------------------
				when Start_Data_Read =>						-- Read Data (Position/Velocity)
					-- Start operation by setting go signal
					go_sig_s <= '1';
					sample_s <= '1';
					valid <= '0';
					
					if busy_s = '1' then
						state_TopLevel_StateMachine <= Reset_Go_Signal;
					end if;
					----------------------------------------------------------------------------------------
				when Reset_Go_Signal =>						-- Reset Go Signal and transition to next state as soon as SPI Com is finished
					go_sig_s <= '0';
					
					if busy_s = '0' then
						case(mode_ResolverIP) is
							when Config_Mode =>
								state_TopLevel_StateMachine <= Wait_for_Trigger;
							when Position_Mode =>
								state_TopLevel_StateMachine <= Read_Position;
							when Velocity_Mode =>
								state_TopLevel_StateMachine <= Read_Velocity;
							when PositionAndVelocity_Mode =>
								state_TopLevel_StateMachine <= Read_Position_And_Init_Velocity_Read;
							when others =>
						end case;
					end if;
					----------------------------------------------------------------------------------------
				when Read_Position =>						-- Read in position value and set valid
					position_out     <= data_out_s;
					valid <= '1';
					
					state_TopLevel_StateMachine <= Wait_for_Trigger;                          
					----------------------------------------------------------------------------------------
				when Read_Velocity =>						-- Read in velocity value and set valid
					velocity_out     <= data_out_s;
					valid <= '1';
					
					state_TopLevel_StateMachine <= Wait_for_Trigger;  
					----------------------------------------------------------------------------------------
				when Read_Position_And_Init_Velocity_Read =>-- Read in position value and start velocity read
					position_out     <= data_out_s;
					configMode_s <= '0'; -- set configMode for lower level state machine
					dataMode_s <= '1'; -- set dataMode for lower level state machine
					sample_s <= '0';
					go_sig_s <= '1';
					
					if busy_s = '1' then
						state_TopLevel_StateMachine <= Reset_Second_Go_Signal;
					end if;
					----------------------------------------------------------------------------------------
				when Reset_Second_Go_Signal =>			-- Handle position read for position and velocity mode
					go_sig_s <= '0';
					if busy_s = '0' then
						state_TopLevel_StateMachine <= Read_Velocity;
					end if;
				end case;
			end if;

        end if;
    end process;


	-- User logic ends

end arch_imp;
