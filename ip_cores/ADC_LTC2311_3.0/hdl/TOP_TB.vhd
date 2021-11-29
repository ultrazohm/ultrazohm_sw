----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/29/2021 12:23:50 PM
-- Design Name: 
-- Module Name: TOP_TB - Behavioral
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

library work;
use work.ADC_LTC2311_PKG.all;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
Library UNISIM;
use UNISIM.vcomponents.all;

entity TOP_TB is
--  Port ( );
end TOP_TB;

architecture Behavioral of TOP_TB is

-- settings with constants
constant CLOCK_PERIOD               : TIME := 10 ns;
constant TEST_DATA_WIDTH            : natural := 16;
constant TEST_CHANNELS              : natural := 2;
constant TEST_OFFSET_WIDTH          : natural := 16;
constant TEST_CONVERSION_WIDTH      : natural := 18;
constant TEST_DELAY_WIDTH           : natural := 8;
constant TEST_CLK_DIV_WIDTH         : natural := 16;
constant TEST_RES_MSB               : natural := 34;
constant TEST_RES_LSB               : natural := 0;
constant TEST_CLK_DIV               : integer := 0;
constant TEST_DELAY                 : integer := 2;
constant TEST_SAMPLE_TIME           : integer := 0;

-- values
constant RAW_VALUE      : integer := 200;
constant OFFSET_0       : integer := 150;
constant CONVERSION_0   : integer := 10;

constant OFFSET_1       : integer := 120;
constant CONVERSION_1   : integer := -5;

constant SAMPLES        : natural := 4;

signal S_RX_DATA        : std_logic_vector((TEST_CHANNELS * TEST_DATA_WIDTH) - 1 downto 0) := (others => '0');
signal S_RESULT         : std_logic_vector((TEST_CHANNELS * (TEST_RES_MSB - TEST_RES_LSB + 1)) - 1 downto 0);
signal S_OFF_CONV       : std_logic_vector(31 downto 0);
signal S_SAMPLE_COUNTER : std_logic_vector(31 downto 0);

signal S_SCLK, S_SS_N : std_logic_vector(0 downto 0);
signal S_MISO_DIFF : std_logic_vector(3 downto 0) := (others => '0');
signal S_SCLK_DIFF : std_logic_vector(1 downto 0) := (others => '0');

signal S_MISO                           : std_logic_vector(TEST_CHANNELS - 1 downto 0) := (others => '0');

-- control signals
signal S_SET_CONVERSION, S_SET_OFFSET, S_MANUAL, S_SET_SAMPLES, S_SET_SAMPLE_TIME : std_logic := '0';
signal S_RESET_N : std_logic := '1';
signal S_CLK     : std_logic := '1';
signal S_CHANNEL_SELECT : std_logic_vector(31 downto 0);
signal S_TRIGGER_CNV, S_RAW_VALID, S_SI_VALID : std_logic_vector(0 downto 0);


-- SPI slave simulation
constant DCNVSDOV : time := 5 ns;
constant HSDO     : time := 2 ns;
constant DSCKSDOV : time := 7400 ps;
constant PCB_DEL  : time := 1 ns;

signal S_TX_DATA : std_logic_vector(TEST_DATA_WIDTH downto 0) := (others => '0');
signal S_TX_BIT_COUNT : integer := TEST_DATA_WIDTH;

-- AXI Signals:

signal s_axi_awready, s_axi_wready, s_axi_bvalid, s_axi_arready, s_axi_rvalid : std_logic;
signal s_axi_bresp, s_axi_rresp : std_logic_vector(1 downto 0);
signal s_axi_rdata : std_logic_vector(31 downto 0);

-- components


component ADC_LTC2311_v3_0 is
	generic (
		-- Users to add parameters here
        DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
        CHANNELS_PER_MASTER : natural := 8;     -- Number of slaves that are controlled with the same SS_N and SCLK
        SPI_MASTER          : natural := 1;     -- Number of independent SPI Masters
        OFFSET_WIDTH        : natural := 16;    -- Bit width of the offset value
        CONVERSION_WIDTH    : natural := 18;    -- Bit width of the conversion factor
        RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : natural := 23;    -- MSB in the result vector of the multiplactor output
        DIFFERENTIAL        : boolean := true;
		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 6
	);
	port (
		-- Users to add ports here
		
        RAW_VALUE       : out std_logic_vector(DATA_WIDTH * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
        RAW_VALID       : out std_logic_vector(SPI_MASTER - 1 downto 0);
        SI_VALUE        : out std_logic_vector((SPI_MASTER * CHANNELS_PER_MASTER * (RES_MSB - RES_LSB + 1) ) - 1  downto 0);
        SI_VALID        : out std_logic_vector(SPI_MASTER - 1 downto 0);
        TRIGGER_CNV     : in std_logic_vector(SPI_MASTER - 1 downto 0);
        SAMPLE_COUNTER  : out std_logic_vector((SPI_MASTER * C_S00_AXI_DATA_WIDTH) - 1 downto 0);
        
        -- SPI ports
        SCLK            : out std_logic_vector(SPI_MASTER - 1 downto 0);
        MISO            : in std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
        SS_N            : out std_logic_vector(SPI_MASTER - 1 downto 0);
        
        -- Differential SPI Ports
        SCLK_DIFF       : out std_logic_vector(2 * SPI_MASTER - 1 downto 0);
        MISO_DIFF       : in std_logic_vector(2 * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
        
        
		-- User ports ends
		-- Do not modify the ports beyond this line


		-- Ports of Axi Slave Bus Interface S00_AXI
		s00_axi_aclk	: in std_logic;
		s00_axi_aresetn	: in std_logic;
		s00_axi_awaddr	: in std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		s00_axi_awprot	: in std_logic_vector(2 downto 0);
		s00_axi_awvalid	: in std_logic;
		s00_axi_awready	: out std_logic;
		s00_axi_wdata	: in std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		s00_axi_wstrb	: in std_logic_vector((C_S00_AXI_DATA_WIDTH/8)-1 downto 0);
		s00_axi_wvalid	: in std_logic;
		s00_axi_wready	: out std_logic;
		s00_axi_bresp	: out std_logic_vector(1 downto 0);
		s00_axi_bvalid	: out std_logic;
		s00_axi_bready	: in std_logic;
		s00_axi_araddr	: in std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		s00_axi_arprot	: in std_logic_vector(2 downto 0);
		s00_axi_arvalid	: in std_logic;
		s00_axi_arready	: out std_logic;
		s00_axi_rdata	: out std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		s00_axi_rresp	: out std_logic_vector(1 downto 0);
		s00_axi_rvalid	: out std_logic;
		s00_axi_rready	: in std_logic
	);
end component ADC_LTC2311_v3_0;


begin

S_CLK <= not S_CLK after CLOCK_PERIOD / 2;

dut: ADC_LTC2311_v3_0 
        generic map (
		-- Users to add parameters here
        DATA_WIDTH          => TEST_DATA_WIDTH,    -- Number of bits per SPI frame
        CHANNELS_PER_MASTER => TEST_CHANNELS,     -- Number of slaves that are controlled with the same SS_N and SCLK
        SPI_MASTER          => 1,     -- Number of independent SPI Masters
        OFFSET_WIDTH        => TEST_OFFSET_WIDTH,    -- Bit width of the offset value
        CONVERSION_WIDTH    => TEST_CONVERSION_WIDTH,    -- Bit width of the conversion factor
        RES_LSB             => TEST_RES_LSB,     -- LSB in the result vector of the multiplactor output
        RES_MSB             => TEST_RES_MSB,    -- MSB in the result vector of the multiplactor output
        DIFFERENTIAL        => false,
		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	=> 32,
		C_S00_AXI_ADDR_WIDTH	=> 6
	)
	port map (
		-- Users to add ports here
		
        RAW_VALUE       => S_RX_DATA,
        RAW_VALID       => S_RAW_VALID,
        SI_VALUE        => S_RESULT,
        SI_VALID        => S_SI_VALID,
        TRIGGER_CNV     => S_TRIGGER_CNV,
        SAMPLE_COUNTER  => S_SAMPLE_COUNTER,
        
        -- SPI ports
        SCLK            => S_SCLK,
        MISO            => S_MISO,
        SS_N            => S_SS_N,
        
        -- Differential SPI Ports
        SCLK_DIFF       => S_SCLK_DIFF,
        MISO_DIFF       => S_MISO_DIFF,
        
        
		-- User ports ends
		-- Do not modify the ports beyond this line


		-- Ports of Axi Slave Bus Interface S00_AXI
		s00_axi_aclk	=> S_CLK,
		s00_axi_aresetn	=> S_RESET_N,
		s00_axi_awaddr	=> (others => '0'),
		s00_axi_awprot	=> (others => '0'),
		s00_axi_awvalid	=> '0',
		s00_axi_awready	=> s_axi_awready,
		s00_axi_wdata	=> (others => '0'),
		s00_axi_wstrb	=> (others => '0'),
		s00_axi_wvalid	=> '0',
		s00_axi_wready	=> s_axi_wready,
		s00_axi_bresp	=> s_axi_bresp,
		s00_axi_bvalid	=> s_axi_bvalid,
		s00_axi_bready	=> '0',
		s00_axi_araddr	=> (others => '0'),
		s00_axi_arprot	=> (others => '0'),
		s00_axi_arvalid	=> '0',
		s00_axi_arready	=> s_axi_arready,
		s00_axi_rdata	=> s_axi_rdata,
		s00_axi_rresp	=> s_axi_rresp,
		s00_axi_rvalid	=> s_axi_rvalid,
		s00_axi_rready	=> '0'
	);

-- init signals
stimulus : process begin
    S_RESET_N <= '0';
    -- init test tx vector
    S_TX_DATA <= std_logic_vector(to_signed(RAW_VALUE, S_TX_DATA'length));
    wait for 2 * CLOCK_PERIOD;
    S_TX_DATA <= S_TX_DATA(TEST_DATA_WIDTH - 1) & S_TX_DATA(TEST_DATA_WIDTH - 1 downto 0);
    
    wait for 2 * CLOCK_PERIOD;
    S_RESET_N <= '1';
    wait for CLOCK_PERIOD;
    
    -- set offset and conversion for channel 0
    S_CHANNEL_SELECT <= (0 => '1', others => '0');
    S_OFF_CONV <= std_logic_vector(to_signed(OFFSET_0, S_OFF_CONV'length));
    S_SET_OFFSET <= '1';
    wait for CLOCK_PERIOD;
    S_SET_OFFSET <= '0';
    
    -- set conversion 0
    S_OFF_CONV <= std_logic_vector(to_signed(CONVERSION_0, S_OFF_CONV'length));
    S_SET_CONVERSION <= '1';
    wait for CLOCK_PERIOD;
    S_SET_CONVERSION <= '0';
    
    -- set offset and conversion for channel 1
    S_CHANNEL_SELECT <= (1 => '1', others => '0');
    S_OFF_CONV <= std_logic_vector(to_signed(OFFSET_1, S_OFF_CONV'length));
    S_SET_OFFSET <= '1';
    wait for CLOCK_PERIOD;
    S_SET_OFFSET <= '0';
    
    S_OFF_CONV <= std_logic_vector(to_signed(CONVERSION_1, S_OFF_CONV'length));
    S_SET_CONVERSION <= '1';
    wait for CLOCK_PERIOD;
    S_SET_CONVERSION <= '0';
    
    -- set number of samples
    S_OFF_CONV <= std_logic_vector(to_signed(SAMPLES, S_OFF_CONV'length));
    S_SET_SAMPLES <= '1';
    wait for CLOCK_PERIOD;
    S_SET_SAMPLES <= '0';
    
    -- set minimum sample time
    S_OFF_CONV <= std_logic_vector(to_signed(TEST_SAMPLE_TIME, S_OFF_CONV'length));
    S_SET_SAMPLE_TIME <= '1';
    wait for CLOCK_PERIOD;
    S_SET_SAMPLES <= '0';
    
    wait for CLOCK_PERIOD;
    -- start transfer
    S_TRIGGER_CNV <= (others => '1');
--    wait for CLOCK_PERIOD;
--    S_ENABLE <= '0';
--    wait for 4 * (CLOCK_PERIOD * (TEST_CLK_DIV + 2) * TEST_DATA_WIDTH
--           + CLOCK_PERIOD * (TEST_DELAY + 1));
--    -- check if SS_N signal can not be controlled manually during transfer
--    S_SS_IN_N <= '0';
--    wait for CLOCK_PERIOD;
--    -- start transfer
--    S_ENABLE <= '1';
--    wait for CLOCK_PERIOD;
--    S_ENABLE <= '0';
--    wait for CLOCK_PERIOD * 2;
--    S_SS_IN_N <= '1';
--    wait for 8 * (CLOCK_PERIOD * (TEST_CLK_DIV + 2) * TEST_DATA_WIDTH
--           + CLOCK_PERIOD * (TEST_DELAY + 1));
      wait for 20us;
--     test if SS_N signal can be controlled manually
--    S_MANUAL <= '1';
--    S_SS_IN_N <= '0';
--    wait for CLOCK_PERIOD * 2;
--    S_SS_IN_N <= '1';
--    wait for CLOCK_PERIOD * 2;
--    S_MANUAL <= '0';
--    wait for CLOCK_PERIOD * 2;
    report "Simulation ended" severity error;

end process stimulus;


spi_slave : process (S_SCLK, S_SS_N, S_MISO)
            begin
    if falling_edge(S_SS_N(0)) then
        S_MISO <= (others => S_TX_DATA(S_TX_BIT_COUNT)) after (DCNVSDOV + 2 * PCB_DEL);
    end if;
    
    -- generate new output value on falling edge
    if falling_edge(S_SCLK(0)) then
        S_MISO <= (others => 'X') after (HSDO + 2 * PCB_DEL);
        if (S_TX_BIT_COUNT > 0) then
            S_TX_BIT_COUNT <= S_TX_BIT_COUNT - 1;
        end if;
    end if;
    if S_MISO(0) = 'X' then
        S_MISO <= (others => S_TX_DATA(S_TX_BIT_COUNT)) after (DSCKSDOV - HSDO);
    end if;
    
    -- reset bit counter for next transmission
    if rising_edge(S_SS_N(0)) then
        S_TX_BIT_COUNT <= TEST_DATA_WIDTH;
    end if;
end process spi_slave;

end Behavioral;
