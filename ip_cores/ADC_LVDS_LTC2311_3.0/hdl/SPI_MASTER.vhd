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
        CLK_DIV     : integer := 0      -- Number of system clock cycles per half SCLK cycle. Highest SCLK is sys_clk/2
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        -- This solution does not work see ug901 page 184 version 2020.1
        --RX_DATA     : out std_logic_vector_array(CHANNELS - 1 downto 0)(DATA_WIDTH - 1 downto 0);
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
end SPI_MASTER;

architecture Behavioral of SPI_MASTER is

    signal S_DEL_COUNT     : integer range -1 to maximum(PRE_DELAY, POST_DELAY);
    signal S_DEL_CLK       : integer range -1 to CLK_DIV;
    signal S_BIT_COUNT     : integer range -1 to DATA_WIDTH;
    -- The bits from the SPI slave are clocked into the S_RX_BUFFER 
    signal S_RX_BUFFER     : std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
    -- After the transmission completed, the bits from the RX_BUFFER are copied to the RX_OUT_BUFFER
    -- which is connected to the RX_DATA port, The data is available until a new transmission is initiated
    signal S_RX_OUT_BUFFER : std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
    signal S_SCLK          : std_logic;
    
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
                    -- Transition to IDLE
                    when IDLE =>
                        S_SCLK <= CPOL;
                        BUSY <= '0';
                        -- pull SS high at least for one clock cycle
                        if(curstate = POST_WAIT) then
                            SS_OUT_N <= '1';
                        else
                            SS_OUT_N <= SS_IN_N;
                        end if;
                
                    when PRE_WAIT =>
                        -- Transition from IDLE to PRE_WAIT
                        if (curstate = IDLE) then
                            BUSY <= '1';
                            S_SCLK <= CPOL;
                            S_DEL_COUNT <= PRE_DELAY;
                            S_BIT_COUNT <= (DATA_WIDTH);
                            SS_OUT_N <= '0';
                        else
                        -- Stay in PRE_WAIT
                            S_DEL_COUNT <= (S_DEL_COUNT - 1);
                        end if;
                    
                    when SHIFT_OUT =>
                        -- Transition from PRE_WAIT to SHIFT_OUT
                        if (curstate = PRE_WAIT) then
                            S_SCLK <= not(CPOL);
                            S_DEL_CLK <= CLK_DIV;
                        -- Transition from SAMPLE to SHIFT_OUT
                        elsif (curstate = SAMPLE) then
                            S_SCLK <= not(S_SCLK);
                            S_DEL_CLK <= CLK_DIV;
                        -- Stay in SHIFT_OUT    
                        else
                            S_DEL_CLK <= (S_DEL_CLK - 1);
                        end if;
                    
                    when SAMPLE =>
                        if(curstate = PRE_WAIT) or (curstate = SHIFT_OUT) then
                            S_DEL_CLK <= CLK_DIV;
                            S_BIT_COUNT <= (S_BIT_COUNT - 1);
                            shift_in: for i in (CHANNELS - 1) downto 0 loop
                                S_RX_BUFFER( ((i * DATA_WIDTH) + DATA_WIDTH - 1) downto (i * DATA_WIDTH)) <=
                                S_RX_BUFFER( ((i * DATA_WIDTH) + DATA_WIDTH - 2) downto (i * DATA_WIDTH)) & MISO(i);
                            end loop shift_in;
                            
                            -- transition from PRE_WAIT and SHIFT_OUT to SAMPLE only differ in SCLK behavior
                            if(curstate = PRE_WAIT) then
                                S_SCLK <= not(CPOL);
                            else
                                S_SCLK <= not(S_SCLK);
                            end if;
                                                            
                        else
                            S_DEL_CLK <= (S_DEL_CLK - 1);
                        end if;
                    
                    when POST_WAIT =>
                        if (curstate = SAMPLE) then
                            BUSY <= '0';
                            S_DEL_COUNT <= POST_DELAY;
                            S_RX_OUT_BUFFER <= S_RX_BUFFER;
                        else
                            S_DEL_COUNT <= (S_DEL_COUNT - 1);
                        end if;
                    
                    when others => curstate <= IDLE;
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
                    if    (S_BIT_COUNT <= 0)                       then nxtstate <= POST_WAIT;
                    elsif ((S_DEL_CLK <= 0) and (S_BIT_COUNT > 0)) then nxtstate <= SHIFT_OUT;
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
    
    RX_DATA <= S_RX_OUT_BUFFER;
    SCLK <= S_SCLK;

end Behavioral;
