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

architecture Behavioral of SPI_MASTER is

    signal S_DEL_COUNT    : integer range 0 to maximum(PRE_DELAY, POST_DELAY);
    signal S_DEL_CLK      : integer range 0 to CLK_DIV;
    signal S_BIT_COUNT    : integer range 0 to DATA_WIDTH;
    
    -- State definition for the FSM
    type state_type is (IDLE,PRE_WAIT,SHIFT_OUT,SAMPLE,POST_WAIT);
    signal curstate, nxtstate : state_type := IDLE;
    attribute fsm_encoding : string;
    attribute fsm_encoding of curstate, nxtstate : signal is "auto";
    attribute fsm_safe_state : string;
    attribute fsm_safe_state of curstate, nxtstate : signal is "power_on_state";

begin

    output_state_mem: process(CLK)
        begin
            if (reset_n = '0') then
                curstate <= IDLE;
            elsif rising_edge(CLK) then
                curstate <= nxtstate;
                case nxtstate is
                    when IDLE =>
                
                    when PRE_WAIT =>
                    
                    when SHIFT_OUT =>
                    
                    when SAMPLE =>
                    
                    when POST_WAIT =>
                    
                    when others => nxtstate <= IDLE;
                    report "Undecoded State" severity note;
                end case;
            end if;
    end process output_state_mem;
    
    transition: process(curstate, ENABLE, CPHA, S_DEL_COUNT, S_DEL_CLK, S_BIT_COUNT)
        begin
            case curstate is
                when IDLE =>
                    if (ENABLE = '1') then nxtstate <= PRE_WAIT;
                    else                   nxtstate <= IDLE;
                    end if;
                
                when PRE_WAIT =>
                    if    ((S_DEL_COUNT <= 0) and (CPHA = '1')) then nxtstate <= SHIFT_OUT;
                    elsif ((S_DEL_COUNT <= 0) and (CPHA = '0')) then nxtstate <= SAMPLE;
                    else                                             nxtstate <= PRE_WAIT;
                    end if;
                
                when SHIFT_OUT =>
                    if  (S_DEL_CLK <= 0) then nxtstate <= SAMPLE;
                    else                      nxtstate <= SHIFT_OUT;
                    end if;
                
                when SAMPLE =>
                    if    ((S_DEL_CLK <= 0) and (S_BIT_COUNT > 0)) then nxtstate <= SHIFT_OUT;
                    elsif (S_BIT_COUNT <= 0)                       then nxtstate <= POST_WAIT;
                    else                                                nxtstate <= SAMPLE;
                    end if;
                
                when POST_WAIT =>
                    if (S_DEL_COUNT <= 0) then nxtstate <= IDLE;
                    else                       nxtstate <= POST_WAIT;
                    end if;
                
                when others => nxtstate <= IDLE;
                report "Undecoded State" severity note;
            end case;
    end process transition;

end Behavioral;
