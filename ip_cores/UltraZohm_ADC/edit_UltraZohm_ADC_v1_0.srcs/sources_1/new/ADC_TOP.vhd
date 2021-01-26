----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/30/2020 11:26:33 AM
-- Design Name: 
-- Module Name: ADC_TOP - STRUCTURE
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
use IEEE.std_logic_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADC_TOP is

generic(
        DATA_WIDTH  : integer := 16;    -- Number of bits per SPI frame
        CHANNELS    : integer := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        PRE_DELAY   : integer := 0;     -- Number of system clock cycles between last SCLK cycle and SS_N -> high
        POST_DELAY  : integer := 0;     -- Number of system clock cycles between SS_N -> low and first SCLK cycle
        CLK_DIV     : integer := 1      -- Number of system clock cycles per half SCLK cycle. Highest SCLK is sys_clk/2
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
    
end ADC_TOP;

architecture STRUCTURE of ADC_TOP is

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

    spi: SPI_MASTER
        port map(
            CLK         => CLK,
            RESET_N     => RESET_N,
            RX_DATA     => RX_DATA,
            CPHA        => CPHA,
            CPOL        => CPOL,
            SCLK        => SCLK,
            MISO        => MISO,
            SS_OUT_N    => SS_OUT_N,
            SS_IN_N     => SS_IN_N,
            BUSY        => BUSY,
            ENABLE      => ENABLE
            );


end STRUCTURE;

configuration conf_adc of ADC_TOP is
    for STRUCTURE
    
        for spi : SPI_MASTER use entity work.SPI_MASTER(Behavioral);
        end for;
    end for;
end configuration conf_adc;
