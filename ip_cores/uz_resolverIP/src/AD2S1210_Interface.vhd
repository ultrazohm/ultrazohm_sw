
-- Company: TUM
-- Engineer: Felix Kaiser & Thomas Effenberger
-- 
-- Create Date: 06/14/2020 02:51:13 PM
-- Design Name: 
-- Module Name: AD2S1210_Interface - Behavioral
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

entity AD2S1210_Interface is
	Generic(
		SPI_Datalength     : INTEGER   :=  8;                    -- SPI data length
		SPI_Slavenumber    : INTEGER   :=  1;                    -- number of SPI slaves
		SPI_cpha           : STD_LOGIC := '1';                   -- SPI clock phase
		SPI_cpol           : STD_LOGIC := '0';                   -- SPI clock polarity
		SPI_cont           : STD_LOGIC := '0';                   -- SPI continuous mode
		SPI_clk_div        : INTEGER   :=  4                     -- SPI clock divider (12MHz)
	);
	Port (
		clock              : IN  STD_LOGIC;                      -- system clock
		reset_n            : IN  STD_LOGIC;                      -- synchronous reset
		enable             : IN  STD_LOGIC;                      -- system enable
		go_sig             : IN  STD_LOGIC;                      -- global trigger
		sample             : IN  STD_LOGIC;                      -- pull NSample low when go sig is triggered
		busy               : OUT STD_LOGIC;                      -- busy / data ready signal
		error_flag         : OUT STD_LOGIC;                      -- error occurred, reset needed
		dataMode           : IN  STD_LOGIC;                      -- 0 = position mode, 1 = velocity mode
		configMode         : IN  STD_LOGIC;                      -- if configMode = 1, dataMode is ignored
		register_rw        : IN  STD_LOGIC;                      -- 0 = read register, 1 = write register
		register_adr_in    : IN  STD_LOGIC_VECTOR (7 downto 0);  -- register address
		register_val_in    : IN  STD_LOGIC_VECTOR (7 downto 0);  -- value to write to register
		register_val_out   : OUT STD_LOGIC_VECTOR (7 downto 0);  -- read value from register
		data_out           : OUT STD_LOGIC_VECTOR (15 downto 0); -- read value in normal mode
		--
		SPI_MOSI           : OUT STD_LOGIC;                      -- SPI master out (connect to chip)
		SPI_MISO           : IN  STD_LOGIC;                      -- SPI master in (connect to chip)
		SPI_SCLK           : OUT STD_LOGIC;                      -- SPI clock (connect to chip)
		SPI_SS             : OUT STD_LOGIC;                      -- SPI slave select (connect to chip)
		--
		AD2S1210_n_reset   : OUT STD_LOGIC;                      -- reset (connect to chip)
		AD2S1210_n_sample  : OUT STD_LOGIC;                      -- sample start (connect to chip)
		AD2S1210_n_fsync   : OUT STD_LOGIC;                      -- synchronization signal (connect to chip)
		AD2S1210_mode_A0   : OUT STD_LOGIC;                      -- mode select 0 (connect to chip)
		AD2S1210_mode_A1   : OUT STD_LOGIC                       -- mode select 1 (connect to chip)
	);
end AD2S1210_Interface;

architecture Behavioral of AD2S1210_Interface is

-- Constants ---------------------------------------------------------------------------------------
constant SPI_SEND_DUMMY             : STD_LOGIC_VECTOR  := x"0F";
constant DUMMY_ADR                  : STD_LOGIC_VECTOR  := "11001100";
constant DUMMY_VAL                  : STD_LOGIC_VECTOR  := "01010011";
constant AD2S1210_REG_FAULT         : STD_LOGIC_VECTOR  := x"FF";

-- Create signals ----------------------------------------------------------------------------------
type states_AD2S1210_Interface is
(
	Resolver_Powerup,
	Resolver_Resetcounter,
	Resolver_WaitStabilize,
	Resolver_Ready,
	Resolver_StartNormalRead,
	Resolver_WaitSampleTime,
	Resolver_NormalRead,
	Resolver_SendRegisterAddress,
	Resolver_SendRegisterValue,
	Resolver_ReadRegisterValue,
	Resolver_SPI_Waittransmit1,
	Resolver_SPI_Waittransmit2,
	Resolver_Failstate
);
signal state_Resolver_Interface : states_AD2S1210_Interface;
signal laststate_Resolver_Interface : states_AD2S1210_Interface;

signal SPI_enable           : std_logic;
signal SPI_busy             : std_logic;
signal SPI_TX_Data          : std_logic_vector(SPI_Datalength-1 downto 0);  -- Buffer
signal SPI_RX_Data          : std_logic_vector(SPI_Datalength-1 downto 0);  -- Buffer
signal byte_tx_counter      : unsigned(7 downto 0):=(others => '0');
signal byte_rx_counter      : unsigned(7 downto 0):=(others => '0');

signal wakeup_counter       : unsigned(31 downto 0) :=(others => '0');
signal sample_counter       : unsigned(7 downto 0):=(others => '0');

-- Create component --------------------------------------------------------------------------------
component spi_master_LTC is
	generic(
		slaves  : INTEGER := 1;  --number of spi slaves
		d_width : INTEGER := 8   --data bus width
	);
	port(
		clock   : IN     STD_LOGIC;                             --system clock
		reset_n : IN     STD_LOGIC;                             --synchronous reset
		enable  : IN     STD_LOGIC;                             --initiate transaction
		cpol    : IN     STD_LOGIC;                             --spi clock polarity
		cpha    : IN     STD_LOGIC;                             --spi clock phase
		cont    : IN     STD_LOGIC;                             --continuous mode command
		clk_div : IN     INTEGER;                               --system clock cycles per 1/2 period of sclk
		addr    : IN     INTEGER;                               --address of slave
		tx_data : IN     STD_LOGIC_VECTOR(d_width - 1 DOWNTO 0);--data to transmit
		miso    : IN     STD_LOGIC;                             --master in, slave out
		sclk    : OUT    STD_LOGIC;                             --spi clock
		ss_n    : BUFFER STD_LOGIC_VECTOR(slaves - 1 DOWNTO 0); --slave select
		mosi    : OUT    STD_LOGIC;                             --master out, slave in
		busy    : OUT    STD_LOGIC;                             --busy / data ready signal
		rx_data : OUT    STD_LOGIC_VECTOR(d_width - 1 DOWNTO 0) --data1 received
	); 
end component spi_master_LTC;


begin
	-- Create components ---------------------------------------------------------------------------
	SPI_Core : spi_master_LTC
	generic map(
		slaves  => SPI_Slavenumber,
		d_width => SPI_Datalength
	)
	port map(
		clock   => clock,                   --system clock
		reset_n => reset_n,                 --synchronous reset
		enable  => SPI_enable,              --initiate transaction
		cpol    => SPI_cpol,                --spi clock polarity
		cpha    => SPI_cpha,                --spi clock phase
		cont    => SPI_cont,                --continuous mode command
		clk_div => SPI_clk_div,             --system clock cycles per 1/2 period of sclk
		addr    => (SPI_Slavenumber - 1),   --address of slave
		tx_data => SPI_TX_Data,             --data to transmit
		miso    => SPI_MISO,                --master in, slave out
		sclk    => SPI_SCLK,                --spi clock
		ss_n    => open,                    --slave select
		mosi    => SPI_MOSI,                --master out, slave in
		busy    => SPI_busy,                --busy / data ready signal
		rx_data => SPI_RX_Data              --data received
	);
	
	-- Set A0 and A1 according to mode (see datasheet)
	AD2S1210_mode_A1 <= dataMode OR configMode;
	AD2S1210_mode_A0 <= configMode;
	
	-- State machine process -----------------------------------------------------------------------
	StateMachine : process (clock,reset_n,enable)
	begin
		if (reset_n = '0') then     -- Reset
			
			SPI_TX_Data             <= x"00";
			
			error_flag              <= '0';
			byte_tx_counter         <= (others => '0');
			byte_rx_counter         <= (others => '0');
			wakeup_counter          <= (others => '0');
			sample_counter          <= (others => '0');
			
			SPI_SS                  <= '0';
			SPI_enable              <= '0';
			busy                    <= '1';
			AD2S1210_n_reset        <= '0';
			AD2S1210_n_sample       <= '1';
			AD2S1210_n_fsync        <= '1';
			
			register_val_out        <= (others => '0');
			data_out                <= (others => '0');
			
			state_Resolver_Interface        <= Resolver_Powerup;
			laststate_Resolver_Interface    <= Resolver_Powerup;
			
		elsif (reset_n = '1' ) then
			if (rising_edge (clock) AND enable = '1') then
				case (state_Resolver_Interface) is
				----------------------------------------------------------------------------------------
					when Resolver_Powerup =>                -- Status at power-up
						busy                                <= '1';
						AD2S1210_n_reset                    <= '0';
						
						state_Resolver_Interface            <= Resolver_Resetcounter;
						laststate_Resolver_Interface        <= Resolver_Powerup;
				----------------------------------------------------------------------------------------
					when Resolver_Resetcounter =>           -- Wait 10us in reset after power-up
						if (wakeup_counter >= 1000) then
							AD2S1210_n_reset                <= '1';
							wakeup_counter                  <= (others => '0');
							
							state_Resolver_Interface        <= Resolver_WaitStabilize;
							laststate_Resolver_Interface    <= Resolver_Resetcounter;
						else
							wakeup_counter                  <= wakeup_counter + 1;
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_WaitStabilize =>          -- Wait 60ms after reset for the internal circuitry to stabilize
						if (wakeup_counter >= 6000000) then
							wakeup_counter                  <= (others => '0');
							
							state_Resolver_Interface        <= Resolver_Ready;
							laststate_Resolver_Interface    <= Resolver_WaitStabilize;
						else
							wakeup_counter                  <= wakeup_counter + 1;
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_Ready =>                  -- Ready for samples or configuration
						busy                                <= '0';
						
						if (go_sig = '1') then
							busy                            <= '1';
							
							if (configMode = '0') then
								state_Resolver_Interface    <= Resolver_StartNormalRead;
							else
								state_Resolver_Interface    <= Resolver_SendRegisterAddress;
							end if;
							
							laststate_Resolver_Interface    <= Resolver_Ready;
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_StartNormalRead =>        -- Generate sample pulse
					if (sample = '1') then
							AD2S1210_n_sample               <= '0';
					end if;
					sample_counter                  <= (others => '0');
					byte_tx_counter                 <= (others => '0');
						
							
					state_Resolver_Interface        <= Resolver_WaitSampleTime;
					laststate_Resolver_Interface    <= Resolver_StartNormalRead;
				----------------------------------------------------------------------------------------
					when Resolver_WaitSampleTime =>         -- Wait sample time 1us (t30 in datasheet)
						if (sample_counter >= 100) then
							sample_counter                  <= (others => '0');
							state_Resolver_Interface        <= Resolver_NormalRead;
							laststate_Resolver_Interface    <= Resolver_WaitSampleTime;
						else
							sample_counter                  <= sample_counter + 1;
						end if;
						
						if (sample_counter >= 35) then
							AD2S1210_n_sample               <= '1'; -- Set sample output after 350ns (t16 in datasheet)
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_NormalRead =>             -- Read 16 bits in normal mode
						
						--Save results
						if (byte_tx_counter = 1) then
							data_out(15 downto 8)           <= SPI_RX_Data(7 downto 0);
						elsif (byte_tx_counter = 2) then
							data_out(7 downto 0)            <= SPI_RX_Data(7 downto 0);
						end if;
						
						if (byte_tx_counter < 2) then
							AD2S1210_n_fsync                <= '0';
							SPI_TX_Data                     <= SPI_SEND_DUMMY;
							SPI_enable                      <= '1';
				    		SPI_SS                          <= '0';
							byte_tx_counter                 <= byte_tx_counter + 1;
					       	state_Resolver_Interface        <= Resolver_SPI_Waittransmit1;
							laststate_Resolver_Interface    <= Resolver_NormalRead;

						else
							AD2S1210_n_fsync                <= '1';
							byte_tx_counter                 <= (others => '0');
							state_Resolver_Interface        <= Resolver_Ready;
							laststate_Resolver_Interface    <= Resolver_NormalRead;
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_SendRegisterAddress =>    -- Send Register Address
						if (laststate_Resolver_Interface /= Resolver_SPI_Waittransmit2) then
							AD2S1210_n_fsync                <= '0';
							SPI_TX_Data                     <= register_adr_in;
							SPI_enable                      <= '1';
							SPI_SS                          <= '0';
							
							state_Resolver_Interface        <= Resolver_SPI_Waittransmit1;
							laststate_Resolver_Interface    <= Resolver_SendRegisterAddress;
						else
							AD2S1210_n_fsync                <= '1';
							
							if register_rw = '0' then
								state_Resolver_Interface    <= Resolver_ReadRegisterValue;
							else
								state_Resolver_Interface    <= Resolver_SendRegisterValue;
							end if;
							
							laststate_Resolver_Interface    <= Resolver_SendRegisterAddress;
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_ReadRegisterValue =>      -- Read Register Value
						if (laststate_Resolver_Interface /= Resolver_SPI_Waittransmit2) then
							AD2S1210_n_fsync                <= '0';
							SPI_TX_Data                     <= AD2S1210_REG_FAULT;
							SPI_enable                      <= '1';
							SPI_SS                          <= '0';
							
							state_Resolver_Interface        <= Resolver_SPI_Waittransmit1;
							laststate_Resolver_Interface    <= Resolver_ReadRegisterValue;
						else
							AD2S1210_n_fsync                <= '1';
							register_val_out                <= SPI_RX_Data;
							
							state_Resolver_Interface        <= Resolver_Ready;
							laststate_Resolver_Interface    <= Resolver_ReadRegisterValue;
						end if;
				----------------------------------------------------------------------------------------
					when Resolver_SendRegisterValue =>      -- Send Register Value
						if (laststate_Resolver_Interface /= Resolver_SPI_Waittransmit2) then
							AD2S1210_n_fsync                <= '0';
							SPI_TX_Data                     <= register_val_in;
							SPI_enable                      <= '1';
							SPI_SS                          <= '0';
							
							state_Resolver_Interface        <= Resolver_SPI_Waittransmit1;
							laststate_Resolver_Interface    <= Resolver_SendRegisterValue;
						else
							AD2S1210_n_fsync                <= '1';
							state_Resolver_Interface        <= Resolver_Ready;
							laststate_Resolver_Interface    <= Resolver_SendRegisterValue;
						end if;
				---------------------------------------------------------------------------------------- 
					when Resolver_Failstate =>              -- Failstate
						error_flag                      <= '1';
				---------------------------------------------------------------------------------------- 
					when Resolver_SPI_Waittransmit1 =>      -- Waitstate 1 for SPI-Core
						SPI_enable                          <= '0'; -- Reset SPI-enable
						state_Resolver_Interface            <= Resolver_SPI_Waittransmit2;
				----------------------------------------------------------------------------------------
					when Resolver_SPI_Waittransmit2 =>      -- Waitstate 2 for SPI-Core to finish
						SPI_enable                          <= '0';
						if (SPI_busy = '0') then
							SPI_SS                          <= '0';
							state_Resolver_Interface        <= laststate_Resolver_Interface;
							laststate_Resolver_Interface    <= Resolver_SPI_Waittransmit2;
						end if;
				----------------------------------------------------------------------------------------
					when others =>
						state_Resolver_Interface            <= Resolver_Failstate;
				----------------------------------------------------------------------------------------
				end case;
			end if;
		end if;
	end process;

end Behavioral;