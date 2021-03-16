----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/10/2021 04:39:06 PM
-- Design Name: 
-- Module Name: ADC_CONTROLLER - Behavioral
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

entity ADC_CONTROLLER is
    generic(
        DATA_WIDTH          : integer := 16;    -- Number of bits per SPI frame
        CHANNELS            : integer := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        : integer := 18;    -- Bit width of the offset value
        CONVERSION_WIDTH    : integer := 27;    -- Bit width of the conversion factor
        CONV_DEL            : integer := 4;     -- Number of clock cycles that the multiplaction takes
        RES_LSB             : integer := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : integer := 23;    -- MSB in the result vector of the multiplactor output
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        
        -- SPI ports
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
        SS_OUT_N    : out std_logic;
        SS_IN_N     : in std_logic;
        BUSY        : out std_logic;
        ENABLE      : in std_logic;
        
        -- Control Ports
        SET_CONVERSION  : in std_logic;
        SET_OFFSET      : in std_logic;
        READ_DONE       : out std_logic;
        SI_VALID        : out std_logic;
        RAW_VALID       : out std_logic;
        
        -- Value Ports
        VALUE_OFF_CONV  : in std_logic_vector(31 downto 0);     -- input for conversion or offset value 
        SI_VALUE        : out std_logic_vector((CHANNELS * (RES_MSB - RES_LSB + 1)) - 1 downto 0);
        RX_DATA         : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
        
    );
end ADC_CONTROLLER;

architecture Behavioral of ADC_CONTROLLER is

begin


end Behavioral;
