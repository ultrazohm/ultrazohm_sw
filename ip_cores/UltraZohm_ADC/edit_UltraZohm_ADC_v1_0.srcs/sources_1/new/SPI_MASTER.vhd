----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/10/2020 05:07:38 PM
-- Design Name: 
-- Module Name: SPI_MASTER - Behavioral
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
library work;
use work.ULTRAZOHM_ADC_PKG.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SPI_MASTER is
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
        RX_DATA     : out std_logic_vector_array(CHANNELS - 1 downto 0)(DATA_WIDTH - 1 downto 0);
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        SS_N        : out std_logic;
        BUSY        : out std_logic;
        ENABLE      : in std_logic
    );
end SPI_MASTER;

architecture RTL of SPI_MASTER is

    signal S_DEL_COUNT    : integer range 0 to maximum(PRE_DELAY, POST_DELAY);
    signal S_DEL_CLK      : integer range 0 to CLK_DIV;
    signal S_BIT_COUNT    : integer range 0 to DATA_WIDTH;

begin


end RTL;
