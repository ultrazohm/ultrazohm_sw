----------------------------------------------------------------------------------
-- Company:     Univeristät Kassel - Elektrische Maschinen und Antriebe
-- Engineer:    Robert Zipprich
-- 
-- Create Date: 02.02.2023 11:12:33
-- Design Name: LinearRegressionIP
-- Module Name: Valid_Geenrator
-- Project Name: Diss
-- Target Devices: UZ
-- Tool Versions: 2020.1
-- Description: AWESOME
-- 
-- Dependencies: Nope
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments: 
--      
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Valid_Generator is
Generic(
    Wait_Cycles	    : integer	:= 11
);
Port (
    clk             : in    std_logic;
    rst_n           : in    std_logic;
    Trigger_Calc    : in    std_logic;
    Data_valid      : out   std_logic
);
end Valid_Generator;

architecture Behavioral of Valid_Generator is

type states is(Validcounter_start, Validcounter_Counting);
signal state : states; 
signal  counter_reg_s   : unsigned (7 downto 0);

begin

process(clk)                                                          
begin                                                                             
    if (rising_edge (clk)) then                                                
        if (rst_n = '0' ) then                                                
            Data_valid      <= '0';
            counter_reg_s   <= (others =>'0');
            state           <= Validcounter_start;
        else                                                                                       
            case (state) is
            ----------------------------------------------------------------------------------------
             when Validcounter_start =>
                 if (Trigger_Calc = '1')then
                    state           <= Validcounter_Counting;
                    Data_valid      <= '0';
                 else   
                    state           <= Validcounter_start;
                    Data_valid      <= '1';
                 end if;
            ----------------------------------------------------------------------------------------
             when Validcounter_Counting =>
                  if(counter_reg_s >= to_unsigned(Wait_Cycles-2,counter_reg_s'length)) then
                     counter_reg_s  <= (others =>'0');
                     state          <= Validcounter_start;
                 else
                     counter_reg_s  <= counter_reg_s+1;
                     state          <= Validcounter_Counting;
                 end if;
            ---------------------------------------------------------------------------------------
             when others => 
             -- TRAP
            ----------------------------------------------------------------------------------------	
            end case;
        end if;                                                                       
    end if;                                                                         
end process; 



end Behavioral;
