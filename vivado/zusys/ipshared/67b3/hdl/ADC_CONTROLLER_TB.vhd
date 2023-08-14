----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/30/2021 01:03:46 PM
-- Design Name: 
-- Module Name: ADC_CONTROLLER_TB - Behavioral
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
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADC_CONTROLLER_TB is
--  Port ( );
end ADC_CONTROLLER_TB;

architecture Behavioral of ADC_CONTROLLER_TB is

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

signal S_CPHA, S_CPOL, S_SCLK, S_SCLK_IN, S_SS_OUT_N, S_SS_IN_N, S_BUSY : std_logic := '0';

signal S_MISO                           : std_logic_vector(TEST_CHANNELS - 1 downto 0) := (others => '0');
signal S_CLK_DIV                        : std_logic_vector(TEST_CLK_DIV_WIDTH - 1 downto 0);
signal S_PRE_DELAY, S_POST_DELAY        : std_logic_vector(TEST_DELAY_WIDTH - 1 downto 0);

-- control signals
signal S_SET_CONVERSION, S_SET_OFFSET, S_ENABLE, S_SI_VALID, S_RAW_VALID, S_MANUAL, S_SET_SAMPLES, S_SET_SAMPLE_TIME : std_logic := '0';
signal S_RESET_N : std_logic := '1';
signal S_CLK     : std_logic := '1';
signal S_CHANNEL_SELECT : std_logic_vector(31 downto 0);

-- SPI slave simulation
constant DCNVSDOV : time := 5 ns;
constant HSDO     : time := 2 ns;
constant DSCKSDOV : time := 7400 ps;
constant PCB_DEL  : time := 1 ns;

signal S_TX_DATA : std_logic_vector(TEST_DATA_WIDTH downto 0) := (others => '0');
signal S_TX_BIT_COUNT : integer := TEST_DATA_WIDTH;


-- components


component ADC_CONTROLLER is
    generic(
        DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
        CHANNELS            : natural := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        : natural := 16;    -- Bit width of the offset value
        CONVERSION_WIDTH    : natural := 18;    -- Bit width of the conversion factor
        RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : natural := 23    -- MSB in the result vector of the multiplactor output
        
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        
        -- SPI ports
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        SCLK_IN     : in std_logic;
        MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
        SS_OUT_N    : out std_logic;
        SS_IN_N     : in std_logic;
        MANUAL      : in std_logic;
        ENABLE      : in std_logic;
        
        -- SPI config ports
        PRE_DELAY   : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
        POST_DELAY  : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
        CLK_DIV     : in std_logic_vector(C_CLK_DIV_WIDTH - 1 downto 0);
        
        -- Control Ports
        SET_CONVERSION  : in std_logic;
        SET_OFFSET      : in std_logic;
        SET_SAMPLES     : in std_logic;
        SET_SAMPLE_TIME : in std_logic;
        SI_VALID        : out std_logic;
        RAW_VALID       : out std_logic;
        BUSY            : out std_logic;
        
        -- Value Ports
        VALUE           : in std_logic_vector(31 downto 0);           -- input for conversion or offset value
        CHANNEL_SELECT  : in std_logic_vector(31 downto 0); -- selection which channels shall be updated with conversion factor or offset
        SI_VALUE        : out std_logic_vector((CHANNELS * (RES_MSB - RES_LSB + 1)) - 1 downto 0);
        RAW_VALUE       : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
        SAMPLE_COUNTER  : out std_logic_vector(31 downto 0)
        
    );
end component ADC_CONTROLLER;


begin

S_CLK <= not S_CLK after CLOCK_PERIOD / 2;

dut: ADC_CONTROLLER
    generic map(
        DATA_WIDTH          => TEST_DATA_WIDTH,         -- Number of bits per SPI frame
        CHANNELS            => TEST_CHANNELS,           -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        => TEST_OFFSET_WIDTH,       -- Bit width of the offset value
        CONVERSION_WIDTH    => TEST_CONVERSION_WIDTH,   -- Bit width of the conversion factor
        RES_LSB             => TEST_RES_LSB,            -- LSB in the result vector of the multiplactor output
        RES_MSB             => TEST_RES_MSB            -- MSB in the result vector of the multiplactor output
    )
    port map(
        CLK                 => S_CLK,
        RESET_N             => S_RESET_N,
        
        -- SPI ports
        CPHA                => S_CPHA,
        CPOL                => S_CPOL,
        SCLK                => S_SCLK,
        SCLK_IN             => S_SCLK_IN,
        MISO                => S_MISO,
        SS_OUT_N            => S_SS_OUT_N,
        SS_IN_N             => S_SS_IN_N,
        MANUAL              => S_MANUAL,
        ENABLE              => S_ENABLE,
        
        -- SPI config ports
        PRE_DELAY           => S_PRE_DELAY,
        POST_DELAY          => S_POST_DELAY,
        CLK_DIV             => S_CLK_DIV,
        
        -- Control Ports
        SET_CONVERSION      => S_SET_CONVERSION,
        SET_OFFSET          => S_SET_OFFSET,
        SET_SAMPLES         => S_SET_SAMPLES,
        SET_SAMPLE_TIME     => S_SET_SAMPLE_TIME,
        SI_VALID            => S_SI_VALID,
        RAW_VALID           => S_RAW_VALID,
        BUSY                => S_BUSY,
        
        -- Value Ports
        VALUE               => S_OFF_CONV,
        CHANNEL_SELECT      => S_CHANNEL_SELECT,
        SI_VALUE            => S_RESULT,
        RAW_VALUE           => S_RX_DATA,
        SAMPLE_COUNTER      => S_SAMPLE_COUNTER
        
    );

-- init signals
stimulus : process begin
    S_RESET_N <= '0';
    S_CPOL <= '1';
    S_CPHA <= '0';
    S_SS_IN_N <= '1';
    S_PRE_DELAY <= std_logic_vector(to_unsigned(TEST_DELAY, S_PRE_DELAY'length));
    S_POST_DELAY <= std_logic_vector(to_unsigned(TEST_DELAY, S_POST_DELAY'length));
    S_CLK_DIV <= std_logic_vector(to_unsigned(TEST_CLK_DIV, S_CLK_DIV'length));
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
    S_ENABLE <= '1';
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


spi_slave : process (S_SCLK, S_SS_OUT_N, S_MISO)
            begin
    if falling_edge(S_SS_OUT_N) then
        S_MISO <= (others => S_TX_DATA(S_TX_BIT_COUNT)) after (DCNVSDOV + 2 * PCB_DEL);
    end if;
    
    -- generate new output value on falling edge
    if falling_edge(S_SCLK) then
        S_MISO <= (others => 'X') after (HSDO + 2 * PCB_DEL);
        if (S_TX_BIT_COUNT > 0) then
            S_TX_BIT_COUNT <= S_TX_BIT_COUNT - 1;
        end if;
    end if;
    if S_MISO(0) = 'X' then
        S_MISO <= (others => S_TX_DATA(S_TX_BIT_COUNT)) after (DSCKSDOV - HSDO);
    end if;
    
    -- reset bit counter for next transmission
    if rising_edge(S_SS_OUT_N) then
        S_TX_BIT_COUNT <= TEST_DATA_WIDTH;
    end if;
end process spi_slave;

end Behavioral;

configuration conf_adc_controller_tb of ADC_CONTROLLER_TB is
    for Behavioral
    
        for dut : ADC_CONTROLLER use entity work.ADC_CONTROLLER(Behavioral);
        end for;
    end for;
end configuration conf_adc_controller_tb;