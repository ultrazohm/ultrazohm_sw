----------------------------------------------------------------------------------
-- Company: Institut ELSYS
-- Engineer: Thilo Wendt
-- E-Mail: wendtth65566@th-nuernberg.de
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
use IEEE.NUMERIC_STD.ALL;

library work;
use work.ADC_LTC2311_PKG.all;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SPI_MASTER is
    generic(
        DATA_WIDTH      : natural := 16;    -- Number of bits per SPI frame
        CHANNELS        : natural := 1     -- Number of slaves that are controlled with the same SS_N and SCLK
        
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        -- SPI ports
        RX_DATA     : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        SCLK_IN     : in std_logic;
        MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
        SS_OUT_N    : out std_logic;
        SS_IN_N     : in std_logic;
        MANUAL      : in std_logic;
        -- Control Ports
        BUSY        : out std_logic;
        ENABLE      : in std_logic;
        PRE_DELAY   : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
        POST_DELAY  : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
        CLK_DIV     : in std_logic_vector(C_CLK_DIV_WIDTH - 1 downto 0)
    );
end SPI_MASTER;

architecture Behavioral of SPI_MASTER is
    
    signal S_PRE_DELAY     : std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
    signal S_POST_DELAY    : std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
    signal S_CLK_DIV       : std_logic_vector(C_CLK_DIV_WIDTH - 1 downto 0);
    signal S_DEL_COUNT     : integer range -1 to 255;
    signal S_DEL_CLK       : integer range -1 to 65535;
    signal S_BIT_COUNT     : integer range -1 to DATA_WIDTH + 1;
    -- The bits from the SPI slave are clocked into the S_RX_BUFFER 
    signal S_RX_BUFFER     : std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
    -- After the transmission completed, the bits from the RX_BUFFER are copied to the RX_OUT_BUFFER
    -- which is connected to the RX_DATA port, The data is available until a new transmission is initiated
    signal S_RX_OUT_BUFFER : std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
    signal S_SCLK          : std_logic;
    signal S_CPOL          : std_logic;
    signal S_CPHA          : std_logic;
    
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
            if rising_edge(CLK) then
            if (reset_n = '0') then
                curstate            <= IDLE;
                S_DEL_COUNT         <= 0;
                S_DEL_CLK           <= 0;
                S_BIT_COUNT         <= 0;
                S_RX_OUT_BUFFER     <= (others => '0');
                S_RX_BUFFER         <= (others => '0');
                S_PRE_DELAY         <= (others => '0');
                S_POST_DELAY        <= (others => '0');
                S_CLK_DIV           <= (others => '0');
                S_SCLK              <= CPOL;
            else
                curstate <= nxtstate;
                case nxtstate is
                    -- Transition to IDLE
                    when IDLE =>
                        BUSY <= '0';
                        -- latch in SPI config
                        S_PRE_DELAY <= PRE_DELAY;
                        S_POST_DELAY <= POST_DELAY;
                        S_CLK_DIV <= CLK_DIV;
                        S_CPOL <= CPOL;
                        S_CPHA <= CPHA;
                        -- pull SS high at least for one clock cycle
                        case curstate is
                        when POST_WAIT =>
                            SS_OUT_N <= '1';
                        
                        when others =>
                            if (MANUAL = '1') then
                                SS_OUT_N <= SS_IN_N;
                                S_SCLK <= SCLK_IN;
                            else
                                SS_OUT_N <= '1';
                                S_SCLK <= S_CPOL;
                            end if;
                        end case;
                
                    when PRE_WAIT =>
                        -- Transition from IDLE to PRE_WAIT
                        case curstate is
                        when IDLE =>
                            BUSY <= '1';
                            S_SCLK <= S_CPOL;
                            S_DEL_COUNT <= TO_INTEGER(unsigned(S_PRE_DELAY));
                            S_BIT_COUNT <= (DATA_WIDTH + 1);
                            SS_OUT_N <= '0';
                        when others =>
                            S_DEL_COUNT <= (S_DEL_COUNT - 1);
                        end case;
                    
                    when SHIFT_OUT =>
                        -- Transition from PRE_WAIT to SHIFT_OUT
                        
                        case curstate is
                        when PRE_WAIT =>
                            S_SCLK <= not(S_CPOL);
                            S_DEL_CLK <= TO_INTEGER(unsigned(S_CLK_DIV));
                            
                        -- Transition from SAMPLE to SHIFT_OUT
                        when SAMPLE =>
                            S_SCLK <= not(S_SCLK);
                            S_DEL_CLK <= TO_INTEGER(unsigned(CLK_DIV));
                            
                        -- Stay in SHIFT_OUT 
                        when others =>
                            S_DEL_CLK <= (S_DEL_CLK - 1);
                        end case;
                    
                    when SAMPLE =>
                        if(curstate = PRE_WAIT) or (curstate = SHIFT_OUT) then
                            S_DEL_CLK <= TO_INTEGER(unsigned(CLK_DIV));
                            S_BIT_COUNT <= (S_BIT_COUNT - 1);
                            shift_in: for i in (CHANNELS - 1) downto 0 loop
                                S_RX_BUFFER( ((i * DATA_WIDTH) + DATA_WIDTH - 1) downto (i * DATA_WIDTH)) <=
                                S_RX_BUFFER( ((i * DATA_WIDTH) + DATA_WIDTH - 2) downto (i * DATA_WIDTH)) & MISO(i);
                            end loop shift_in;
                            
                            -- transition from PRE_WAIT and SHIFT_OUT to SAMPLE only differ in SCLK behavior
                            if(curstate = PRE_WAIT) then
                                S_SCLK <= not(S_CPOL);
                            else
                                S_SCLK <= not(S_SCLK);
                            end if;
                                                            
                        else
                            S_DEL_CLK <= (S_DEL_CLK - 1);
                        end if;
                    
                    when POST_WAIT =>
                        case curstate is
                        when SAMPLE =>
                            BUSY <= '0';
                            S_DEL_COUNT <= TO_INTEGER(unsigned(POST_DELAY));
                            S_RX_OUT_BUFFER <= S_RX_BUFFER;
                        when others =>
                            S_DEL_COUNT <= (S_DEL_COUNT - 1);
                        end case;
                    
                    when others => curstate <= IDLE;
                    report "Undecoded State" severity note;
                end case;
            end if;
            end if;
    end process output_state_mem;
    
    transition: process(curstate, ENABLE, S_CPHA, S_DEL_COUNT, S_DEL_CLK, S_BIT_COUNT)
        begin
            case curstate is
                when IDLE =>
                    if (ENABLE = '1') then nxtstate <= PRE_WAIT;
                    else                   nxtstate <= IDLE;
                    end if;
                
                when PRE_WAIT =>
                    if    ((S_DEL_COUNT <= 0) and (S_CPHA = '1')) then nxtstate <= SHIFT_OUT;
                    elsif ((S_DEL_COUNT <= 0) and (S_CPHA = '0')) then nxtstate <= SAMPLE;
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
