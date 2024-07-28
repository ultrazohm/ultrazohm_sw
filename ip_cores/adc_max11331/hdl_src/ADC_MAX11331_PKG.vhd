----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/20/2022 03:29:03 PM
-- Design Name: 
-- Module Name: ADC_MAX11331_PKG
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

package ADC_MAX11331_PKG is

    -- unconstrained array  -- type t_Integer_Array is array (integer range <>) of integer;
    
    -- constants
    CONSTANT C_ADC_MESSAGE_LENGTH	: INTEGER := 16;
    CONSTANT C_ADC_DATA_BITS 		: INTEGER := 12;


    -- subtype definitions 
    subtype t_message is STD_LOGIC_VECTOR (C_ADC_MESSAGE_LENGTH-1 downto 0);
    
    -- type definitions
    type t_array_message is array (natural range <>) of STD_LOGIC_VECTOR(C_ADC_MESSAGE_LENGTH-1 downto 0);
    type t_array_data    is array (natural range <>) of STD_LOGIC_VECTOR(C_ADC_DATA_BITS-1 downto 0);
    

    
end package ADC_MAX11331_PKG;

package body ADC_MAX11331_PKG is



end package body ADC_MAX11331_PKG;