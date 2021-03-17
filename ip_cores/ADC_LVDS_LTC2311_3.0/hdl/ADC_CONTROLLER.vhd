----------------------------------------------------------------------------------
-- Company: Institut ELSYS
-- Engineer: Thilo Wendt
-- E-Mail: wendtth65566@th-nuernberg.de
-- 
-- Create Date: 03/10/2021 04:39:06 PM
-- Design Name: ADC_LVDS_LTC2311
-- Module Name: ADC_CONTROLLER - Behavioral
-- Project Name: UltraZohm
-- Target Devices: Xilinx UltraScale
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
        DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
        CHANNELS            : natural := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        : natural := 18;    -- Bit width of the offset value
        CONVERSION_WIDTH    : natural := 27;    -- Bit width of the conversion factor
        CONV_DEL            : natural := 4;     -- Number of clock cycles that the multiplaction takes
        RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : natural := 23;    -- MSB in the result vector of the multiplactor output
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
        ENABLE      : in std_logic;
        
        -- SPI config ports
        PRE_DELAY   : in unsigned (DELAY_WIDTH - 1 downto 0);
        POST_DELAY  : in unsigned (DELAY_WIDTH - 1 downto 0);
        CLK_DIV     : in unsigned (CLK_DIV_WIDTH - 1 downto 0);
        
        -- Control Ports
        SET_CONVERSION  : in std_logic;
        SET_OFFSET      : in std_logic;
        READ_DONE       : out std_logic;
        SI_VALID        : out std_logic;
        RAW_VALID       : out std_logic;
        BUSY            : out std_logic;
        
        -- Value Ports
        VALUE_OFF_CONV  : in signed(31 downto 0);           -- input for conversion or offset value
        CHANNEL_SELECT  : in std_logic_vector(31 downto 0); -- selection which channels shall be updated with conversion factor or offset
        SI_VALUE        : out std_logic_vector((CHANNELS * (RES_MSB - RES_LSB + 1)) - 1 downto 0);
        RAW_VALUE       : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
        
    );
end ADC_CONTROLLER;

architecture Behavioral of ADC_CONTROLLER is
    
    -- signal declarations
    signal S_CONVERSION     : signed((CHANNELS * CONVERSION_WIDTH) - 1 downto 0);
    signal S_OFFSET         : signed((CHANNELS * OFFSET_WIDTH) - 1 downto 0);
    
    -- control signals
    signal S_CE_CONVERSION  : std_logic;
    signal S_CONV_DEL       : integer range -1 to CONV_DEL;
    
    -- multiplication pipeline
    signal CHANNEL_COUNTER  : natural range 0 to CHANNELS;
    signal CONV_COUNTER     : natural range 0 to CHANNELS + 1;
    signal RESULT_COUNTER   : natural range 0 to CHANNELS + 2;
    
    -- SPI signals
    signal S_SPI_ENABLE     : std_logic;
    signal S_SPI_BUSY       : std_logic;
    signal S_SPI_BUSY_PIPE  : std_logic_vector(1 downto 0);
    
    
    -- State definition for the FSM
    type state_type is (IDLE,SPI_TRANSFER,CONVERTING);
    signal curstate, nxtstate : state_type := IDLE;
    attribute fsm_encoding : string;
    attribute fsm_encoding of curstate, nxtstate : signal is "auto";
    attribute fsm_safe_state : string;
    attribute fsm_safe_state of curstate, nxtstate : signal is "power_on_state";

    --component declarations
    
    
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
                        case curstate is
                        when CONVERTING =>
                            SI_VALID <= '1';
                            S_CE_CONVERSION <= '0';
                            BUSY <= '0';
                        when others =>
                            -- set conversion value for the selected channels
                            if (SET_CONVERSION = '1') then
                                set_conv: for i in (CHANNELS) downto 1 loop
                                    if(CHANNEL_SELECT(i - 1) = '1') then
                                        S_CONVERSION((i * CONVERSION_WIDTH) - 1 downto (i - 1) * CONVERSION_WIDTH) 
                                        <= VALUE_OFF_CONV(CONVERSION_WIDTH - 1 downto 0);
                                    end if;
                                end loop set_conv;
                                READ_DONE <= '1';
                            
                            -- set offset value for the selected channels
                            elsif (SET_OFFSET = '1') then
                                set_off: for i in (CHANNELS) downto 1 loop
                                    if(CHANNEL_SELECT(i - 1) = '1') then
                                        S_OFFSET((i * OFFSET_WIDTH) - 1 downto (i - 1) * OFFSET_WIDTH) 
                                        <= VALUE_OFF_CONV(OFFSET_WIDTH - 1 downto 0);
                                    end if;
                                end loop set_off;
                                READ_DONE <= '1';
                                
                            else
                                READ_DONE = '0';
                            end if;
                    
                    when SPI_TRANSFER =>
                        case curstate is
                        when IDLE =>
                            BUSY <= '1';
                            RAW_VALID <= '0';
                            S_SPI_ENABLE <= '1';
                            S_SPI_BUSY_PIPE(1 downto 0) <= "00";
                            
                        when others =>
                            if(S_SPI_BUSY = '1') then
                                S_SPI_ENABLE <= '0';
                            end if;
                            S_SPI_BUSY_PIPE(1 downto 0) <= S_SPI_BUSY_PIPE(0) & S_SPI_BUSY;
                        end case;
                    
                    when CONVERTING
                        case curstate is
                        when SPI_TRANSFER =>
                            S_CE_CONVERSION <= '1';
                            S_CONV_DEL <= CONV_DEL;
                            RAW_VALID <= '1';
                            SI_VALID <= '0';
                        when others =>
                            S_CONV_DEL <= S_CONV_DEL - 1;
                        end case;
                        
                    when others => curstate <= IDLE;
                    report "Undecoded State" severity note;
                end case;
            end if;
    end process output_state_mem;
    
    transition: process(curstate, ENABLE, S_CONV_DEL, S_SPI_BUSY_PIPE)
        begin
            case curstate is
                when IDLE =>
                    if (ENABLE = '1') then nxtstate <= SPI_TRANSFER;
                    else                   nxtstate <= IDLE;
                    end if;
                
                when SPI_TRANSFER
                    case S_SPI_BUSY_PIPE is
                    -- falling edge of the SPI_BUSY signal
                    when "10" =>
                        nxtstate <= CONVERTING;
                    when others =>
                        nxtstate <= SPI_TRANSFER;
                    end case;
                    
                when CONVERTING
                    -- conversion to SI value finished
                    if(S_CONV_DEL <= 0)
                        nxtstate <= IDLE;
                    else
                        nxtstate <= CONVERTING;
                    end if;
                    
                when others => nxtstate <= IDLE;
                report "Undecoded State" severity note;
            end case;
    end process transition;
    
    -- instantiation of the SPI master and the multiplicator 

end Behavioral;
