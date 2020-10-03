----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Liegmann
-- 
-- Create Date: 17.12.2018 13:18:17
-- Design Name: 
-- Module Name: design_top - Behavioral
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
use ieee.numeric_std.all;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
--type dutycycle_array is array(0 to 5) of integer range 0 to 4095;

entity extend_interrupt is
    port(
            clock :         in STD_LOGIC;
            interrupt_in :  in STD_LOGIC;
            interrupt_out: out STD_LOGIC  := '0' -- ;
          --  interrupt_active_counter_out: out STD_LOGIC_VECTOR (7 downto 0)
    );
end extend_interrupt;

architecture Behavioral of extend_interrupt is
    

begin

    interrupt_hold: process(clock) -- give out a longer interrupt pulse to trigger ISRs
            variable interrupt_active_counter : integer range 0 to 127 :=0;
            constant count_stop : integer := 60;
        begin 
            if rising_edge(clock) then
                if (interrupt_in = '1' AND interrupt_active_counter = 0) then
                    interrupt_active_counter :=1;
                end if;
                
                if(interrupt_active_counter> 0 and interrupt_active_counter < count_stop) then
                    interrupt_out <= '1';
                    interrupt_active_counter := interrupt_active_counter + 1;
                else
                    interrupt_out <= '0';
                    interrupt_active_counter := 0;
                end if;     
         --     interrupt_active_counter_out <=  std_logic_vector(to_unsigned(interrupt_active_counter, interrupt_active_counter_out'length));
             end if;
        end process interrupt_hold;

end Behavioral;
