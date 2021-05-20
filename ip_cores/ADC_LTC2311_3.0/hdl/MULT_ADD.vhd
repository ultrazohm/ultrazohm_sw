----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/17/2021 04:35:54 PM
-- Design Name: 
-- Module Name: MULT_ADD - Behavioral
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
-- DWITDH must be <= AWIDTH otherwise the MSBs will be truncated
-- In order to fit in one DSP Block AWIDTH must not be bigger than 26
-- because the carry bit needs to be considered (expansion of one bit)
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity MULT_ADD is
generic(  
    AWIDTH : natural := 26;
    BWIDTH : natural := 18;  
    DWIDTH : natural := 26
    ); 
port(  
    CLK     : in  std_logic;
    RESET_N : in std_logic;
    SUBADD  : in  std_logic;
    ENABLE  : in  std_logic;
    AIN     : in  std_logic_vector(AWIDTH - 1 downto 0);  -- first operand
    BIN     : in  std_logic_vector(BWIDTH - 1 downto 0);  -- factor
    DIN     : in  std_logic_vector(DWIDTH - 1 downto 0);  -- second operand
    POUT    : out std_logic_vector(AWIDTH + BWIDTH downto 0) 
    );
    
    attribute use_dsp : string;
end MULT_ADD;

architecture Behavioral of MULT_ADD is
    signal S_A          : signed(AWIDTH - 1 downto 0);
    signal S_B          : signed(BWIDTH - 1 downto 0);
    signal S_D          : signed(DWIDTH - 1 downto 0);
    signal S_ADD        : signed(AWIDTH downto 0);
    signal S_MULT       : signed(AWIDTH + BWIDTH downto 0);
    
    -- make sure a DSP block is used instead of slice logic
    attribute use_dsp of Behavioral : architecture is "yes";
begin

    -- Multiplier with pre adder
    -- Latency: 3 clk cycles
    -- In pipelined operation the multiplication factor needs to be placed on port B
    -- one clk cycle after A and D have been placed
    multadd: process(clk) 
    begin  
    if rising_edge(clk) then
        if (RESET_N = '0') then
            S_A     <= (others => '0');
            S_B     <= (others => '0');
            S_D     <= (others => '0');
            S_ADD   <= (others => '0');
            S_MULT  <= (others => '0');
        elsif (ENABLE = '1') then
           S_A <= signed(AIN);
           S_B <= signed(BIN);   
           S_D <= signed(DIN);   
           if SUBADD = '1' then
               S_ADD <= resize(S_A, AWIDTH + 1) - resize(S_D, AWIDTH + 1);   
           else
               S_ADD <= resize(S_A, AWIDTH + 1) + resize(S_D, AWIDTH + 1);   
           end if;   
           
           S_MULT <= S_ADD * S_B;  
        end if;
    end if;
    end process multadd;

    POUT <= std_logic_vector(S_MULT);
end Behavioral;
