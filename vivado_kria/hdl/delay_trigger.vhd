----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Liegmann
-- 
-- Create Date: 23.05.2019 17:23:03
-- Design Name: 
-- Module Name: delay_diff - Behavioral
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


entity delay_trigger is
port(   clk : in std_logic;
    --    data_in_p : in std_logic; -- the data input
    --    data_in_n : in std_logic; -- the data input
        delay_cycles : in unsigned(10 downto 0);   --delay to be generated.
     --   data_out_p : out std_logic := '0'; --the delayed input data.
     --   data_out_n : out std_logic := '1'; --the delayed input data.
        a_in:      in std_logic;
        a_out : out std_logic := '0'
        );
end delay_trigger;

architecture Behavioral of delay_trigger is

signal a_store : std_logic_vector(2047 downto 0);
--signal data_p_store : std_logic_vector(2047 downto 0);
--signal data_n_store : std_logic_vector(2047 downto 0);


begin
process(clk)
begin
     if rising_edge(clk) then
        -- a_in 
        a_store <= a_store(a_store'high-1 downto 0) & a_in;
        a_out <= a_store( to_integer(delay_cycles));
        -- data_p_in
  --      data_p_store <= data_p_store(data_p_store'high-1 downto 0) & data_in_p;
  --      data_out_p <= data_p_store( to_integer(delay_cycles));
        -- data_n_in            
 --       data_n_store <= data_n_store(data_n_store'high-1 downto 0) & data_in_n;
 --       data_out_n <= data_n_store( to_integer(delay_cycles));
      
    end if;
end process;

end Behavioral;
