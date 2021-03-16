----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/01/2020 11:08:03 AM
-- Design Name: 
-- Module Name: ADC_TESTBENCH - Behavioral
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADC_TESTBENCH is
--  Port ( );
end ADC_TESTBENCH;

architecture Behavioral of ADC_TESTBENCH is

-- signals and constants

constant CLOCK_PERIOD : TIME := 10 ns;
constant TEST_DATA_WIDTH : integer := 16;
constant TEST_CHANNELS : integer := 2;
constant TEST_DELAY : integer := 0;
constant TEST_CLK_DIV : integer := 0;
signal S_RESET_N, S_CPHA, S_CPOL, S_SCLK, S_SS_OUT_N, S_SS_IN_N, S_BUSY, S_ENABLE : std_logic := '0';
signal S_CLK : std_logic := '0';
signal S_RX_DATA : std_logic_vector((TEST_CHANNELS * TEST_DATA_WIDTH) - 1 downto 0) := (others => '0');
signal S_MISO : std_logic_vector(TEST_CHANNELS - 1 downto 0) := (others => '0');

-- SPI slave simulation

constant DCNVSDOV : time := 5 ns;
constant HSDO     : time := 2 ns;
constant DSCKSDOV : time := 7400 ps;
constant PCB_DEL  : time := 1 ns;

signal S_NEW_MISO : std_logic := '0';

signal S_TX_DATA : std_logic_vector(TEST_DATA_WIDTH - 1 downto 0) := (others => '0');
signal S_TX_BIT_COUNT : integer := TEST_DATA_WIDTH - 1;


-- components

component SPI_MASTER

    generic(
        DATA_WIDTH  : integer := 16;    -- Number of bits per SPI frame
        CHANNELS    : integer := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        PRE_DELAY   : integer := 0;     -- Number of system clock cycles between last SCLK cycle and SS_N -> high
        POST_DELAY  : integer := 0;     -- Number of system clock cycles between SS_N -> low and first SCLK cycle
        CLK_DIV     : integer := 0      -- Number of system clock cycles per half SCLK cycle. Highest SCLK is sys_clk/2
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        RX_DATA     : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
        SS_OUT_N    : out std_logic;
        SS_IN_N     : in std_logic;
        BUSY        : out std_logic;
        ENABLE      : in std_logic
    );
end component;

begin

dut: SPI_MASTER
        generic map(
            DATA_WIDTH  => TEST_DATA_WIDTH,
            CHANNELS    => TEST_CHANNELS,
            PRE_DELAY   => TEST_DELAY,
            POST_DELAY  => TEST_DELAY,
            CLK_DIV     => TEST_CLK_DIV
            )
        port map(
            CLK         => S_CLK,
            RESET_N     => S_RESET_N,
            RX_DATA     => S_RX_DATA,
            CPHA        => S_CPHA,
            CPOL        => S_CPOL,
            SCLK        => S_SCLK,
            MISO        => S_MISO,
            SS_OUT_N    => S_SS_OUT_N,
            SS_IN_N     => S_SS_IN_N,
            BUSY        => S_BUSY,
            ENABLE      => S_ENABLE
            );

-- init signals


S_CLK <= not S_CLK after CLOCK_PERIOD / 2;


stimulus : process begin
    S_RESET_N <= '0';
    S_CPOL <= '1';
    S_CPHA <= '0';
    S_SS_IN_N <= '1';
    -- init test tx vector
    S_TX_DATA(TEST_DATA_WIDTH - 1) <= '1';
    wait for 0 ns;
    tx_data: for i in TEST_DATA_WIDTH - 2 downto 0 loop
        S_TX_DATA(i) <= not S_TX_DATA(i + 1);
        wait for 0 ns;
    end loop tx_data;
    wait for 100 ns;
    S_RESET_N <= '1';
    wait for CLOCK_PERIOD;
    -- test if SS_N signal can be controlled manually
    S_SS_IN_N <= '0';
    wait for CLOCK_PERIOD * 2;
    S_SS_IN_N <= '1';
    wait for CLOCK_PERIOD * 2;
    -- start transfer
    S_ENABLE <= '1';
    wait for CLOCK_PERIOD;
    S_ENABLE <= '0';
    wait for CLOCK_PERIOD * (TEST_CLK_DIV + 2) * TEST_DATA_WIDTH
           + CLOCK_PERIOD * (TEST_DELAY + 1);
    -- check if SS_N signal can not be controlled manually during transfer
    S_SS_IN_N <= '0';
    wait for CLOCK_PERIOD * 2;
    S_SS_IN_N <= '1';
    wait for CLOCK_PERIOD * (TEST_CLK_DIV + 2) * TEST_DATA_WIDTH
           + CLOCK_PERIOD * (TEST_DELAY + 1);
    report "Simulation ended" severity error;

end process stimulus;


spi_slave : process (S_SCLK, S_SS_OUT_N, S_MISO)
            begin
    -- generate new output value on falling edge
    if falling_edge(S_SS_OUT_N) then
        S_MISO <= (others => S_TX_DATA(S_TX_BIT_COUNT)) after (DCNVSDOV + 2 * PCB_DEL);
    end if;
    
    if falling_edge(S_SCLK) then
        S_MISO <= (others => 'X') after (HSDO + 2 * PCB_DEL);
        S_TX_BIT_COUNT <= S_TX_BIT_COUNT - 1;
    end if;
    
    if S_MISO(0) = 'X' then
        S_MISO <= (others => S_TX_DATA(S_TX_BIT_COUNT)) after (DSCKSDOV - HSDO);
    if S_TX_BIT_COUNT <= 0 then
        S_TX_BIT_COUNT <= TEST_DATA_WIDTH - 1;
    end if;
    end if;
    
end process spi_slave;

end Behavioral;

configuration conf_adc of ADC_TESTBENCH is
    for Behavioral
    
        for dut : SPI_MASTER use entity work.SPI_MASTER(Behavioral);
        end for;
    end for;
end configuration conf_adc;
