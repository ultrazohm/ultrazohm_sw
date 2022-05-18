----------------------------------------------------------------------------------
-- Company: Institut ELSYS
-- Engineer: Thilo Wendt
-- E-Mail: wendtth65566@th-nuernberg.de
-- 
-- Create Date: 03/10/2021 04:39:06 PM
-- Design Name: ADC_LTC2311
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
use IEEE.NUMERIC_STD.ALL;

library work;
use work.ADC_LTC2311_PKG.all;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADC_CONTROLLER is
    generic(
        DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
        CHANNELS            : natural := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        : natural := 16;    -- Bit width of the offset value
        CONVERSION_WIDTH    : natural := 18;    -- Bit width of the conversion factor
        RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : natural := 23    -- MSB in the result vector of the multiplactor output
        
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        
        -- SPI ports
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        SCLK_IN     : in std_logic;
        MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
        SS_OUT_N    : out std_logic;
        SS_IN_N     : in std_logic;
        MANUAL      : in std_logic;
        ENABLE      : in std_logic;
        
        -- SPI config ports
        PRE_DELAY   : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
        POST_DELAY  : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
        CLK_DIV     : in std_logic_vector(C_CLK_DIV_WIDTH - 1 downto 0);
        
        -- Control Ports
        SET_CONVERSION  : in std_logic;
        SET_OFFSET      : in std_logic;
        SET_SAMPLES     : in std_logic;
        SET_SAMPLE_TIME : in std_logic;
        SI_VALID        : out std_logic;
        RAW_VALID       : out std_logic;
        BUSY            : out std_logic;
        
        -- Value Ports
        VALUE           : in std_logic_vector(31 downto 0);           -- input for conversion or offset value
        CHANNEL_SELECT  : in std_logic_vector(31 downto 0); -- selection which channels shall be updated with conversion factor or offset
        SI_VALUE        : out std_logic_vector((CHANNELS * (RES_MSB - RES_LSB + 1)) - 1 downto 0);
        RAW_VALUE       : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
        SAMPLE_COUNTER  : out std_logic_vector(31 downto 0)
        
    );
end ADC_CONTROLLER;

architecture Behavioral of ADC_CONTROLLER is
    -- settings
    constant C_SAMPLE_COUNT_LIMIT : natural := 2147483647;
    
    -- signal declarations
    signal S_CONVERSION     : std_logic_vector((CHANNELS * CONVERSION_WIDTH) - 1 downto 0);
    signal S_OFFSET         : std_logic_vector((CHANNELS * OFFSET_WIDTH) - 1 downto 0);
    
    -- control signals
    signal S_CE_CONVERSION          : std_logic;
    signal S_DUMMY_SAMPLE           : std_logic;
    signal S_SAMPLES                : natural range 0 to C_SAMPLE_COUNT_LIMIT;
    signal S_SAMPLE_COUNTER         : integer;
    signal S_SAMPLE_TIME            : natural range 0 to C_SAMPLE_COUNT_LIMIT;
    signal S_SAMPLE_TIME_COUNTER    : natural range 0 to C_SAMPLE_COUNT_LIMIT;
    signal S_MANUAL                 : std_logic;
    
    -- multiplication pipeline
    signal S_CHANNEL_COUNTER    : integer range 0 to CHANNELS;
    signal S_CONV_COUNTER       : integer range 0 to CHANNELS + 1;
    signal S_RESULT_COUNTER     : integer range 0 to CHANNELS + 3;
    
    -- single channel signals (inputs for the multiplier)
    signal S_CONVERSION_S_C : std_logic_vector(CONVERSION_WIDTH - 1 downto 0);
    signal S_OFFSET_S_C     : std_logic_vector(OFFSET_WIDTH - 1 downto 0);
    signal S_RESULT_S_C     : std_logic_vector(DATA_WIDTH + CONVERSION_WIDTH downto 0);
    signal S_RAW_VALUE_S_C  : std_logic_vector(DATA_WIDTH - 1 downto 0);
    
    -- SPI signals
    signal S_SPI_ENABLE     : std_logic;
    signal S_SPI_BUSY       : std_logic;
    signal S_SPI_BUSY_PIPE  : std_logic_vector(1 downto 0);
    signal S_SPI_RAW_VALUE  : std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
    signal S_SS_OUT_N       : std_logic;
    
    -- State definition for the FSM
    type state_type is (IDLE,OCCUPIED,SPI_TRANSFER,CONVERTING);
    signal curstate, nxtstate : state_type := IDLE;
    attribute fsm_encoding : string;
    attribute fsm_encoding of curstate, nxtstate : signal is "auto";
    attribute fsm_safe_state : string;
    attribute fsm_safe_state of curstate, nxtstate : signal is "power_on_state";

    --component declarations
    
    component SPI_MASTER is
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
    end component SPI_MASTER;
    
    component MULT_ADD is
    generic(  
        AWIDTH : natural := 26;
        BWIDTH : natural := 18;  
        DWIDTH : natural := 26
        ); 
    port(  
        CLK     : in  std_logic;
        RESET_N : in  std_logic;
        SUBADD  : in  std_logic;
        ENABLE  : in  std_logic;
        AIN     : in  std_logic_vector(AWIDTH - 1 downto 0);  -- first operand
        BIN     : in  std_logic_vector(BWIDTH - 1 downto 0);  -- factor
        DIN     : in  std_logic_vector(DWIDTH - 1 downto 0);  -- second operand
        POUT    : out std_logic_vector(AWIDTH + BWIDTH downto 0) 
        );
    end component MULT_ADD;
begin


    output_state_mem: process(CLK)
        variable V_SAMPLE_COUNTER : integer := 0;
        begin
            if rising_edge(CLK) then
            if (reset_n = '0') then
                curstate <= IDLE;
                S_CE_CONVERSION <= '0';
                
                S_RAW_VALUE_S_C  <= (others => '0');
                S_CONVERSION_S_C <= (others => '0');
                S_OFFSET_S_C     <= (others => '0');
                
                S_CHANNEL_COUNTER <= 0;
                S_CONV_COUNTER    <= 0;
                S_RESULT_COUNTER  <= 0;
                S_SAMPLE_TIME_COUNTER <= 0;
                
                S_SPI_ENABLE     <= '0';
                S_SPI_BUSY_PIPE  <= (others => '0');
                
                --RAW_VALUE        <= (others => '0');
                SI_VALUE         <= (others => '0');
                SI_VALID         <= '0';
                RAW_VALID        <= '0';
                --SCLK             <= '0';
                --SS_OUT_N         <= '1';
                BUSY             <= '0';
                S_DUMMY_SAMPLE <= '1';
                
            else
                curstate <= nxtstate;
                case nxtstate is
                    -- Transition to IDLE
                    when IDLE =>
                        S_MANUAL <= MANUAL;
                        case curstate is
                        when OCCUPIED =>
                            BUSY <= '0';
                        when others =>
                            
                        end case;
                        
                    when OCCUPIED =>
                        
                        S_MANUAL <= '0';
                        
                        -- Minimum sample time
                        -- decrement counter as soon as SS_N is high
                        if (S_SS_OUT_N = '1') and (S_SAMPLE_TIME_COUNTER > 0) then
                            S_SAMPLE_TIME_COUNTER <= S_SAMPLE_TIME_COUNTER - 1;
                        end if;
                        
                        case curstate is
                        when IDLE =>
                            BUSY <= '1';
                            S_DUMMY_SAMPLE <= '1';
                            S_SAMPLE_COUNTER <= -1;
                            S_SAMPLE_TIME_COUNTER <= S_SAMPLE_TIME;
                        when CONVERTING =>
                            SI_VALID <= '1';
                            S_CE_CONVERSION <= '0';
                            
                            -- transfer last value to output vector
                            SI_VALUE( ((S_RESULT_COUNTER + 1) * (RES_MSB - RES_LSB + 1)) - 1 downto (S_RESULT_COUNTER) * (RES_MSB - RES_LSB + 1)) 
                            <= S_RESULT_S_C(RES_MSB downto RES_LSB);
                        
                        when SPI_TRANSFER =>
                            S_DUMMY_SAMPLE <= '0';
                        
                        when others =>
                        
                        end case;
                    
                    when SPI_TRANSFER =>
                        case curstate is
                        when OCCUPIED =>
                            
                            RAW_VALID <= '0';
                            S_SPI_ENABLE <= '1';
                            S_SPI_BUSY_PIPE(1 downto 0) <= "00";
                            S_SAMPLE_TIME_COUNTER <= S_SAMPLE_TIME;
                            
                            -- preparation for multiplication
                            S_CHANNEL_COUNTER <= CHANNELS;
                            S_CONV_COUNTER    <= CHANNELS + 1;
                            S_RESULT_COUNTER  <= CHANNELS + 3;
                            
                            
                        when others =>
                            if(S_SPI_BUSY = '1') then
                                S_SPI_ENABLE <= '0';
                            end if;
                            S_SPI_BUSY_PIPE(1 downto 0) <= S_SPI_BUSY_PIPE(0) & S_SPI_BUSY;
                        end case;
                    
                    when CONVERTING =>
                        S_CE_CONVERSION <= '1';
                        RAW_VALID <= '1';
                        SI_VALID <= '0';
                        
                        -- increment the sample counter on transition from SPI_TRANSFER
                        -- Prevent overflow by reseting S_SAMPLE_COUNTER to 0 in case of overflow
                        if (curstate = SPI_TRANSFER) then
                            V_SAMPLE_COUNTER := S_SAMPLE_COUNTER;
                            V_SAMPLE_COUNTER := V_SAMPLE_COUNTER + 1;
                            -- V_SAMPLE_COUNTER is < 0 in case of overflow
                            if (V_SAMPLE_COUNTER < 0) then
                                V_SAMPLE_COUNTER := 0;
                            end if;
                            S_SAMPLE_COUNTER <= V_SAMPLE_COUNTER;
                        end if;
                        
                        
                        -- Minimum sample time
                        -- decrement counter as soon as SS_N is high
                        if (S_SS_OUT_N = '1') and (S_SAMPLE_TIME_COUNTER > 0) then
                            S_SAMPLE_TIME_COUNTER <= S_SAMPLE_TIME_COUNTER - 1;
                        end if;
                            
                        -- input signal formation for the multiplier
                        
                        -- first clock cycle: raw ADC value and offset to the pre adder
                        if (S_CHANNEL_COUNTER > 0) then
                            S_RAW_VALUE_S_C <= S_SPI_RAW_VALUE( (S_CHANNEL_COUNTER * DATA_WIDTH) - 1 downto (S_CHANNEL_COUNTER - 1) * DATA_WIDTH);
                            S_OFFSET_S_C    <= S_OFFSET( (S_CHANNEL_COUNTER * OFFSET_WIDTH) - 1 downto (S_CHANNEL_COUNTER - 1) * OFFSET_WIDTH );
                            S_CHANNEL_COUNTER <= S_CHANNEL_COUNTER - 1; 
                        end if;
                        
                        -- second clock cycle: conversion factor to the multiplier
                        if (S_CONV_COUNTER > 0) and (S_CONV_COUNTER <= CHANNELS) then
                            S_CONVERSION_S_C <= S_CONVERSION( (S_CONV_COUNTER * CONVERSION_WIDTH) - 1 downto (S_CONV_COUNTER - 1) * CONVERSION_WIDTH );
                        end if;
                        
                        if (S_CONV_COUNTER > 0) then
                            S_CONV_COUNTER <= S_CONV_COUNTER - 1;
                        end if;
                        
                        -- AFTER the third clock cycle the result is available. It is sampled on the fourth edge
                        
                        -- fourth clock cycle: read the result to the appropriate slice of the result vector
                        if (S_RESULT_COUNTER > 0) and (S_RESULT_COUNTER < CHANNELS) then
                            SI_VALUE( ((S_RESULT_COUNTER + 1) * (RES_MSB - RES_LSB + 1)) - 1 downto (S_RESULT_COUNTER) * (RES_MSB - RES_LSB + 1)) <= S_RESULT_S_C(RES_MSB downto RES_LSB);
                        end if;
                        
                        if (S_RESULT_COUNTER > 0) then
                            S_RESULT_COUNTER <= S_RESULT_COUNTER - 1;
                        end if;
                        
                    when others => curstate <= IDLE;
                    report "Undecoded State" severity note;
                end case;
            end if;
            end if;
    end process output_state_mem;
    
    transition: process(curstate, ENABLE, S_RESULT_COUNTER, S_SPI_BUSY_PIPE, S_DUMMY_SAMPLE, S_SAMPLE_COUNTER, S_SAMPLE_TIME_COUNTER)
        begin
            case curstate is
                when IDLE =>
                    if (ENABLE = '1') then nxtstate <= OCCUPIED;
                    else                   nxtstate <= IDLE;
                    end if;
                    
                when OCCUPIED =>
                    if (S_SAMPLE_COUNTER >= (S_SAMPLES - 1)) and (ENABLE = '0') then nxtstate <= IDLE;
                    elsif (S_SAMPLE_TIME_COUNTER <= 0)            then nxtstate <= SPI_TRANSFER;
                    else                                               nxtstate <= OCCUPIED;
                    end if;
                
                when SPI_TRANSFER =>
                    case S_SPI_BUSY_PIPE is
                    -- falling edge of the SPI_BUSY signal
                    when "10" =>
                        if (S_DUMMY_SAMPLE = '1') then nxtstate <= OCCUPIED;
                        else                           nxtstate <= CONVERTING;
                        end if; 
                        
                    when others =>
                        nxtstate <= SPI_TRANSFER;
                    end case;
                    
                when CONVERTING =>
                    -- conversion to SI value finished
                    if(S_RESULT_COUNTER <= 0) then
                        nxtstate <= OCCUPIED;
                    else
                        nxtstate <= CONVERTING;
                    end if;
                    
                when others => nxtstate <= IDLE;
                report "Undecoded State" severity note;
            end case;
    end process transition;
    
    proc_set_conversion: process(CLK)
    begin
        if rising_edge(CLK) then
            if (reset_n = '0') then
                S_CONVERSION    <= (others => '0');
                S_OFFSET        <= (others => '0');
                S_SAMPLES       <= 1;
            -- set conversion value for the selected channels
            elsif (SET_CONVERSION = '1') then
                set_conv: for i in (CHANNELS) downto 1 loop
                    if(CHANNEL_SELECT(i - 1) = '1') then
                        S_CONVERSION((i * CONVERSION_WIDTH) - 1 downto (i - 1) * CONVERSION_WIDTH) 
                        <= VALUE(CONVERSION_WIDTH - 1 downto 0);
                    end if;
                end loop set_conv;
            
            -- set offset value for the selected channels
            elsif (SET_OFFSET = '1') then
                set_off: for i in (CHANNELS) downto 1 loop
                    if(CHANNEL_SELECT(i - 1) = '1') then
                        S_OFFSET((i * OFFSET_WIDTH) - 1 downto (i - 1) * OFFSET_WIDTH) 
                        <= VALUE(OFFSET_WIDTH - 1 downto 0);
                    end if;
                end loop set_off;
            elsif (SET_SAMPLES = '1') then
                S_SAMPLES <= TO_INTEGER(unsigned(VALUE(30 downto 0)));
            elsif (SET_SAMPLE_TIME = '1') then
                S_SAMPLE_TIME <= TO_INTEGER(unsigned(VALUE(30 downto 0)));
            end if;
         end if;
        
    end process proc_set_conversion;

    
    -- instantiation of the SPI master and the multiplicator
    
    spi: SPI_MASTER
    generic map (
        DATA_WIDTH      => DATA_WIDTH,
        CHANNELS        => CHANNELS
        )
    port map (
        CLK         => CLK,
        RESET_N     => RESET_N,
        -- SPI ports
        RX_DATA     => S_SPI_RAW_VALUE,
        CPHA        => CPHA,
        CPOL        => CPOL,
        SCLK        => SCLK,
        SCLK_IN     => SCLK_IN,
        MISO        => MISO,
        SS_OUT_N    => S_SS_OUT_N,
        SS_IN_N     => SS_IN_N,
        MANUAL      => S_MANUAL,
        -- Control Ports
        BUSY        => S_SPI_BUSY,
        ENABLE      => S_SPI_ENABLE,
        PRE_DELAY   => PRE_DELAY,
        POST_DELAY  => POST_DELAY,
        CLK_DIV     => CLK_DIV
        );
            
     -- OFFSET_WIDHT must be less or equal to DATA_WIDTH. During the multiplication the offset vector is resized to the size of the A vector
     raw_to_si: MULT_ADD
     generic map (  
        AWIDTH      => DATA_WIDTH,
        BWIDTH      => CONVERSION_WIDTH,
        DWIDTH      => OFFSET_WIDTH
        )
     port map (  
        CLK         => CLK,
        RESET_N     => RESET_N,
        SUBADD      => '0',
        ENABLE      => S_CE_CONVERSION,
        AIN         => S_RAW_VALUE_S_C,     -- first operand
        BIN         => S_CONVERSION_S_C,    -- factor
        DIN         => S_OFFSET_S_C,        -- second operand
        POUT        => S_RESULT_S_C
        );
        
     -- concurrent signal assigenments
     
     RAW_VALUE <= S_SPI_RAW_VALUE;
     SS_OUT_N  <= S_SS_OUT_N;
     SAMPLE_COUNTER <= std_logic_vector(TO_UNSIGNED(S_SAMPLE_COUNTER, SAMPLE_COUNTER'length));
    

end Behavioral;
