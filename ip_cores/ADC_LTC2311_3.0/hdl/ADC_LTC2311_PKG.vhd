----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/15/2021 03:29:03 PM
-- Design Name: 
-- Module Name: ADC_LTC2311_PKG
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

package ADC_LTC2311_PKG is

    -- constant declarations
    constant C_DELAY_WIDTH      : natural := 8;
    constant C_CLK_DIV_WIDTH    : natural := 16;
    constant C_C_S_AXI_DATA_WIDTH   : integer := 32;
    
    -- bit positions in the config register
    -- ADC_CR
    constant C_MODE               : natural := 0;
    constant C_SW_TRIGGER         : natural := 1;
    constant C_TRIGGER            : natural := 2;
    constant C_SW_RESET           : natural := 3;
    constant C_CONV_VALUE_VALID   : natural := 4;
    constant C_CONFIG_VALUE_LSB   : natural := 5;
    constant C_CONFIG_VALUE_MSB   : natural := 7;
    
    -- ADC_SPI_CR
    constant C_SPI_SS_N           : natural := 0;
    constant C_SPI_SS_N_STATUS    : natural := 1;
    constant C_SPI_SCLK           : natural := 2;
    constant C_SPI_SCLK_STATUS    : natural := 3;
    constant C_SPI_CONTROL        : natural := 4;
    constant C_SPI_CONTROL_STATUS : natural := 5;
    constant C_SPI_CPOL           : natural := 6;
    constant C_SPI_CPHA           : natural := 7;
    
    -- reset values
    constant C_RESET_CPOL         : std_logic := '1';
    constant C_RESET_CPHA         : std_logic := '0';
    
    -- functions

end package ADC_LTC2311_PKG;

package body ADC_LTC2311_PKG is



end package body ADC_LTC2311_PKG;