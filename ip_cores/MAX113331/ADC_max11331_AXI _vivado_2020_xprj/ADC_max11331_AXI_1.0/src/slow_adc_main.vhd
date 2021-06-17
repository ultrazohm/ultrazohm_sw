----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.11.2018 09:16:14
-- Design Name: 
-- Module Name: slow_adc_main - Behavioral
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

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;


entity Slow_ADC_Memory_main is
	GENERIC
	(
		clk_div 			: INTEGER := 3;                   -- System clock cycles per 1/2 period of sclk
		OUTPUT_WORD_WIDTH 	: INTEGER := 12                  -- Use 12 for normal operation. Use 16 for debug.
	);
	Port
	(
		clk 								: in STD_LOGIC;
		reset_n 							: in STD_LOGIC;
		enable_measure 				        : in STD_LOGIC;
		clk_division : IN 	STD_LOGIC_VECTOR(3 DOWNTO 0);          --system clock cycles per 1/2 period of sclk					
		sclk 								: out STD_LOGIC;
		mosi 								: out STD_LOGIC;
		miso 								: in STD_LOGIC_VECTOR (5 downto 0);
		ss_n 								: out STD_LOGIC;
		init_done 						: out STD_LOGIC;
		meas_done 						: out STD_LOGIC;
		new_data 						: out STD_LOGIC;
		error 							: out STD_LOGIC;
		error_counter				: out STD_LOGIC_VECTOR (31 downto 0);
		adc_selector				: in STD_LOGIC_VECTOR (6 downto 1);
		force_init 					: in STD_LOGIC;
		data_echo_bipolar_1			: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_2			: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_3			: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_4			: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_5			: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_6			: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_1		: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_2		: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_3		: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_4		: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_5		: out STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_6		: out STD_LOGIC_VECTOR (15 downto 0);		
		data_board_1_input_1_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_1_ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_1_ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_1_ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_2_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_2_ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_2_ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_2_ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_3_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_3_ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_3_ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_3_ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_4_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_4_ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_4_ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_4_ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_5_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_5_ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_5_ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_5_ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_6_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_6_ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_6_ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_board_1_input_6_ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);

        data_board_2_input_1_ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_1_ch2    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_1_ch3    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_1_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_2_ch1    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_2_ch2    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_2_ch3    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_2_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_3_ch1    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_3_ch2    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_3_ch3    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_3_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_4_ch1    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_4_ch2    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_4_ch3    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_4_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_5_ch1    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_5_ch2    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_5_ch3    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_5_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_6_ch1    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_6_ch2    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_6_ch3    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
        data_board_2_input_6_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0)
	);
end Slow_ADC_Memory_main;


architecture Behavioral of Slow_ADC_Memory_main is
	signal	counter			: integer := 0;
	signal  enable_spi_S :   std_logic := '0';
	signal  busy_spi_S :   std_logic := '0';
	signal	error_counter_S :	std_logic_vector(31 downto 0) := (others=>'0'); 
	signal  error_S :   		std_logic := '0';
	signal  meas_done_S :   	std_logic := '0';
	signal  init_done_S :	std_logic := '0';
	signal	new_data_S	:	std_logic := '0';
	signal  tx_data_S  :   std_logic_vector(15 downto 0) := (others=>'0'); 
	signal  rx_data_1_S  :   std_logic_vector(15 downto 0) := (others=>'0');
	signal  rx_data_2_S  :   std_logic_vector(15 downto 0) := (others=>'0');
	signal  rx_data_3_S  :   std_logic_vector(15 downto 0) := (others=>'0');
	signal  rx_data_4_S  :   std_logic_vector(15 downto 0) := (others=>'0');
	signal  rx_data_5_S  :   std_logic_vector(15 downto 0) := (others=>'0');
	signal  rx_data_6_S  :   std_logic_vector(15 downto 0) := (others=>'0');
	
	signal  data_b1_i1_ch1_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i1_ch2_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i1_ch3_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i1_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i2_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i2_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i2_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i2_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i3_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i3_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i3_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i3_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i4_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i4_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i4_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i4_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i5_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i5_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i5_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i5_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i6_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i6_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i6_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b1_i6_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 

	signal  data_b2_i1_ch1_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i1_ch2_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i1_ch3_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i1_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i2_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i2_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i2_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i2_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i3_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i3_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i3_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i3_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i4_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i4_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i4_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i4_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i5_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i5_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i5_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i5_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i6_ch1_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i6_ch2_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i6_ch3_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_b2_i6_ch4_S	:  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	
	
	type state_t is (INIT_START, INIT_ADC_REG, INIT_DELAY_0, INIT_BIPOLAR_REG, INIT_DELAY_1, INIT_UNIPOLAR_REG, INIT_DELAY_2, INIT_RANGE_REG, INIT_DELAY_3,
						IDLE, MEAS_DELAY_IDLE, MEAS_ASK_0, MEAS_DELAY_ASK_0, MEAS_ASK_2, MEAS_DELAY_ASK_2, MEAS_ASK_4, MEAS_DELAY_ASK_4, MEAS_ASK_6, MEAS_DELAY_ASK_6,
						MEAS_ASK_8, MEAS_DELAY_ASK_8, MEAS_ASK_10, MEAS_DELAY_ASK_10, MEAS_ASK_12, MEAS_DELAY_ASK_12, MEAS_ASK_14, MEAS_DELAY_ASK_14, MEAS_ASK_EXTRA, MEAS_DELAY_ASK_EXTRA,
						ERROR_STATE, INIT_RESET, INIT_DELAY_RESET);
	signal state                    : state_t := IDLE;  

	type memory_echo_t is array (1 to 6) of STD_LOGIC_VECTOR(15 downto 0);
	SIGNAL data_echo_bipolar_S : memory_echo_t := (others => (others => '0'));
	SIGNAL data_echo_unipolar_S : memory_echo_t := (others => (others => '0'));
	SIGNAL verify_echo_bipolar_detail	: STD_LOGIC_VECTOR(6 downto 1) := (others => '0');
	SIGNAL verify_echo_unipolar_detail	: STD_LOGIC_VECTOR(6 downto 1) := (others => '0');
	SIGNAL verify_echo_bipolar	: STD_LOGIC;
	SIGNAL verify_echo_unipolar	: STD_LOGIC;
	
	SIGNAL adc_echoed_bipolar_S : STD_LOGIC_VECTOR(6 downto 1) := (others => '0');
	SIGNAL adc_echoed_unipolar_S : STD_LOGIC_VECTOR(6 downto 1) := (others => '0');
	type memory_t is array (0 to 7) of STD_LOGIC_VECTOR(15 downto 0);
	SIGNAL board_1_adc_1_array_S : memory_t := (others => (others => '0'));
	SIGNAL board_1_adc_2_array_S : memory_t := (others => (others => '0'));	
	SIGNAL board_1_adc_3_array_S : memory_t := (others => (others => '0'));	
	SIGNAL board_2_adc_1_array_S : memory_t := (others => (others => '0'));
	SIGNAL board_2_adc_2_array_S : memory_t := (others => (others => '0'));	
	SIGNAL board_2_adc_3_array_S : memory_t := (others => (others => '0'));	
 
	--CONSTANT DELAY 				: integer := clk_div-2	;-- Delay count from main clock (100MHz) between SPI transfers. Consider delay + 1.
	CONSTANT DELAY 				: integer := clk_div + 2	;-- Delay count from main clock (100MHz) between SPI transfers. Consider delay + 2.
	CONSTANT DELAY_ERROR       : INTEGER := 49;	-- delay count from main clock (100MHz) between error state and restart initialization. Consider delay - 1.
	CONSTANT MSG_RESET	       : STD_LOGIC_VECTOR(15 downto 0) := "0000000001000000";	-- ADC Mode Control: Reset entire chip
	CONSTANT MSG_INIT_1	       : STD_LOGIC_VECTOR(15 downto 0) := "1000000000000100";	-- ADC Configuration: activate echo
	CONSTANT MSG_INIT_2	       : STD_LOGIC_VECTOR(15 downto 0) := "1001011111111000";	-- Bipolar register
	CONSTANT MSG_INIT_3	       : STD_LOGIC_VECTOR(15 downto 0) := "1000100000000000";	-- Unipolar register
	CONSTANT MSG_INIT_4	       : STD_LOGIC_VECTOR(15 downto 0) := "1001111111111000";	-- Range register
    CONSTANT MSG_MEAS_ASK_0 	: STD_LOGIC_VECTOR(15 downto 0) := "0000100000000100";
	CONSTANT MSG_MEAS_ASK_2		: STD_LOGIC_VECTOR(15 downto 0) := "0000100100000100";
	CONSTANT MSG_MEAS_ASK_4		: STD_LOGIC_VECTOR(15 downto 0) := "0000101000000100";
	CONSTANT MSG_MEAS_ASK_6		: STD_LOGIC_VECTOR(15 downto 0) := "0000101100000100";
	CONSTANT MSG_MEAS_ASK_8		: STD_LOGIC_VECTOR(15 downto 0) := "0000110000000100";
	CONSTANT MSG_MEAS_ASK_10	: STD_LOGIC_VECTOR(15 downto 0) := "0000110100000100";
	CONSTANT MSG_MEAS_ASK_12	: STD_LOGIC_VECTOR(15 downto 0) := "0000111000000100";
	CONSTANT MSG_MEAS_ASK_14	: STD_LOGIC_VECTOR(15 downto 0) := "0000111100000100";
	
	 
	COMPONENT spi_master_multi_slave IS
		GENERIC
		(
			clk_div : INTEGER := 3          --system clock cycles per 1/2 period of sclk
		);
		PORT
		(
			clock   : IN     STD_LOGIC;                             --system clock
			reset_n : IN     STD_LOGIC;                             --asynchronous reset
			enable  : IN     STD_LOGIC;                             --initiate transaction
			clk_division : IN 	STD_LOGIC_VECTOR(3 DOWNTO 0);          --system clock cycles per 1/2 period of sclk			
			tx_data : IN     STD_LOGIC_VECTOR(15 DOWNTO 0);  --data to transmit
			miso1   : IN     STD_LOGIC;                             --master in, slave out
			miso2   : IN     STD_LOGIC;                             --master in, slave out
			miso3   : IN     STD_LOGIC;                             --master in, slave out
			miso4   : IN     STD_LOGIC;                             --master in, slave out
			miso5   : IN     STD_LOGIC;                             --master in, slave out
			miso6   : IN     STD_LOGIC;                             --master in, slave out
			sclk    : OUT STD_LOGIC;                             --spi clock
			ss_n    : OUT STD_LOGIC;   --slave select
			mosi    : OUT    STD_LOGIC;                             --master out, slave in
			busy    : OUT    STD_LOGIC;                             --busy / data ready signal
			rx_data1 : OUT    STD_LOGIC_VECTOR(15 DOWNTO 0);   --data received
			rx_data2 : OUT    STD_LOGIC_VECTOR(15 DOWNTO 0);   --data received
			rx_data3 : OUT    STD_LOGIC_VECTOR(15 DOWNTO 0);   --data received
			rx_data4 : OUT    STD_LOGIC_VECTOR(15 DOWNTO 0);   --data received
			rx_data5 : OUT    STD_LOGIC_VECTOR(15 DOWNTO 0);   --data received
			rx_data6 : OUT    STD_LOGIC_VECTOR(15 DOWNTO 0)   --data received
		);
	END COMPONENT spi_master_multi_slave;

begin

	spi_master_multi_slave_0 : spi_master_multi_slave
	PORT MAP
   (
		clock   => clk,                --system clock
		reset_n => reset_n,              --asynchronous reset
		enable  => enable_spi_S,             --initiate transaction
		clk_division => clk_division,          --system clock cycles per 1/2 period of sclk
		tx_data => tx_data_S(15 downto 0),                  --data to transmit
		miso1    => miso(0),               --master in, slave out
		miso2    => miso(1),               --master in, slave out
		miso3    => miso(2),               --master in, slave out
		miso4    => miso(3),               --master in, slave out
		miso5    => miso(4),               --master in, slave out
		miso6    => miso(5),               --master in, slave out
		sclk    => sclk,                --spi clock
		ss_n    => ss_n,                   --slave select
		mosi    => mosi,               --master out, slave in
		busy    => busy_spi_S,              --busy / data ready signal
		rx_data1 => rx_data_1_S,		--data received
		rx_data2 => rx_data_2_S,		--data received
		rx_data3 => rx_data_3_S,		--data received
		rx_data4 => rx_data_4_S,		--data received
		rx_data5 => rx_data_5_S,		--data received
		rx_data6 => rx_data_6_S			--data received
    );
    
    -- Slow ADC State Machine - Mealy / Moore
	State_Machine : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			state <= INIT_START;                      --return to initial state
			tx_data_S <= (others => '0'); 
			enable_spi_S <= '0';
			counter <= 0;
            
		ELSIF rising_edge(clk) THEN
			CASE state IS
			--Start the initialization sending the first word via SPI.
			WHEN INIT_START =>
				IF counter = DELAY THEN				
					tx_data_S <= MSG_INIT_1;
					enable_spi_S <= '1';
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_START;
					ELSE
						state <= INIT_ADC_REG;
					END IF;					
				ELSE
					state <= INIT_START;
					tx_data_S <= (others => '0'); 
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
				END IF;				
 
			--Initializing ADC Register 
			WHEN INIT_ADC_REG =>
				tx_data_S <= MSG_INIT_1;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_0;
				ELSE
					state <= INIT_ADC_REG;
				END IF;

			--Delay after ADC Register write
			WHEN INIT_DELAY_0 =>	
				IF counter = DELAY THEN
					tx_data_S <= MSG_INIT_2;
					enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_DELAY_0;
					ELSE
						state <= INIT_BIPOLAR_REG;
					END IF;
				ELSE
					state <= INIT_DELAY_0;
					tx_data_S <= MSG_INIT_1;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
				END IF;			

			--Initializing BIPOLAR Register 
			WHEN INIT_BIPOLAR_REG =>
				tx_data_S <= MSG_INIT_2;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_1;
				ELSE
					state <= INIT_BIPOLAR_REG;
				END IF;

			--Delay after BIPOLAR Register write
			WHEN INIT_DELAY_1 =>
				IF counter = DELAY THEN
					tx_data_S <= MSG_INIT_3;
					enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends				
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_DELAY_1;
					ELSE
						state <= INIT_UNIPOLAR_REG;
					END IF;
				ELSE
					state <= INIT_DELAY_1;
					tx_data_S <= MSG_INIT_2;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
				END IF;	
				
			--Initializing UNIPOLAR Register 
			WHEN INIT_UNIPOLAR_REG =>
				tx_data_S <= MSG_INIT_3;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_2;
				ELSE
					state <= INIT_UNIPOLAR_REG;
				END IF;

			--Delay after UNIPOLAR Register write
			WHEN INIT_DELAY_2 =>
				IF counter = DELAY THEN
					tx_data_S <= MSG_INIT_4;
					enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends				
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_DELAY_2;
					ELSE
						state <= INIT_RANGE_REG;
					END IF;				
				ELSE
					tx_data_S <= MSG_INIT_3;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
					IF verify_echo_bipolar = '1' THEN	--check for echoed data
						state <= INIT_DELAY_2;
					ELSE
						state <= ERROR_STATE;
					END IF;					
				END IF;	

			--Initializing RANGE Register 
			WHEN INIT_RANGE_REG =>
				tx_data_S <= MSG_INIT_4;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_3;
				ELSE
					state <= INIT_RANGE_REG;
				END IF;

			--Delay after RANGE Register write
			WHEN INIT_DELAY_3 =>				
				IF counter = DELAY THEN
					tx_data_S <= MSG_MEAS_ASK_0;	
					counter <= DELAY;
					if force_init = '1' then
						state <= MEAS_DELAY_IDLE;					
						enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends
					else
						state <= IDLE;		
						enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends						
					end if;
				ELSE
					state <= INIT_DELAY_3;
					tx_data_S <= MSG_INIT_4;
					counter <= counter + 1;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					IF verify_echo_unipolar = '1' THEN	--check for echoed data
						state <= INIT_DELAY_3;
					ELSE
						state <= ERROR_STATE;
					END IF;						
				END IF;	
	
			WHEN IDLE =>
				counter <= 0;
				IF enable_measure = '1' THEN
					if force_init = '1' then
						state <= INIT_START;		
						tx_data_S <= MSG_INIT_1;						
						enable_spi_S <= '0';			-- Send the ask for channel 0 to the adc's
					else
						state <= MEAS_DELAY_IDLE;					
						tx_data_S <= MSG_MEAS_ASK_0;
						enable_spi_S <= '1';			-- Send the ask for channel 0 to the adc's
					end if;
				ELSE
					state <= IDLE;
					enable_spi_S <= '0';
					tx_data_S <= MSG_MEAS_ASK_0;
				END IF;	

			WHEN MEAS_DELAY_IDLE =>					-- Delay after enable measure
				tx_data_S <= MSG_MEAS_ASK_0;		-- Prepare tx_data for the next message. Ask for ch2
				enable_spi_S <= '1';			-- After delay, latch data into SPI.						
				counter <= 0;
				IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
					state <= MEAS_ASK_0;
				ELSE
					state <= MEAS_DELAY_IDLE;
				END IF;				
				
			WHEN MEAS_ASK_0 =>					-- Asked ch0 to be measured. Wait until SPI transfer finish. Receive nothing usefull from SPI data
				tx_data_S <= MSG_MEAS_ASK_0;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					-- storage rx_data into the internal memory !!!!!!!!!!!. Do nothing here
					state <= MEAS_DELAY_ASK_0;
				ELSE
					state <= MEAS_ASK_0;
				END IF;
				
			WHEN MEAS_DELAY_ASK_0 =>				-- Delay after asked ch0 message
				tx_data_S <= MSG_MEAS_ASK_2;		-- Prepare tx_data for the next message. Ask for ch2
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_0;
					ELSE
						state <= MEAS_ASK_2;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_0;
				END IF;	
				
			WHEN MEAS_ASK_2 =>					-- Asked ch2 to be measured. Wait until SPI transfer finish. Receive ch0 data
				tx_data_S <= MSG_MEAS_ASK_2;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(0) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(0) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(0) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(0) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(0) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(0) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_2;
				ELSE
					state <= MEAS_ASK_2;
				END IF;
				
			WHEN MEAS_DELAY_ASK_2 =>				-- Delay after asked ch2 message
				tx_data_S <= MSG_MEAS_ASK_4;		-- Prepare tx_data for the next message. Ask for ch4
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_2;
					ELSE
						state <= MEAS_ASK_4;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_2;
				END IF;	

			WHEN MEAS_ASK_4 =>					-- Asked ch4 to be measured. Wait until SPI transfer finish. Receive ch2 data
				tx_data_S <= MSG_MEAS_ASK_4;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(1) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(1) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(1) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(1) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(1) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(1) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_4;
				ELSE
					state <= MEAS_ASK_4;
				END IF;
				
			WHEN MEAS_DELAY_ASK_4 =>				-- Delay after asked ch4 message
				tx_data_S <= MSG_MEAS_ASK_6;		-- Prepare tx_data for the next message. Ask for ch6
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_4;
					ELSE
						state <= MEAS_ASK_6;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_4;
				END IF;	
				
			WHEN MEAS_ASK_6 =>					-- Asked ch6 to be measured. Wait until SPI transfer finish. Receive ch4 data
				tx_data_S <= MSG_MEAS_ASK_6;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(2) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(2) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(2) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(2) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(2) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(2) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_6;
				ELSE
					state <= MEAS_ASK_6;
				END IF;
				
			WHEN MEAS_DELAY_ASK_6 =>				-- Delay after asked ch6 message
				tx_data_S <= MSG_MEAS_ASK_8;		-- Prepare tx_data for the next message. Ask for ch8
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_6;
					ELSE
						state <= MEAS_ASK_8;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_6;
				END IF;					
				
			WHEN MEAS_ASK_8 =>					-- Asked ch8 to be measured. Wait until SPI transfer finish. Receive ch6 data
				tx_data_S <= MSG_MEAS_ASK_8;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(3) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(3) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(3) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(3) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(3) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(3) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_8;
				ELSE
					state <= MEAS_ASK_8;
				END IF;
				
			WHEN MEAS_DELAY_ASK_8 =>				-- Delay after asked ch8 message
				tx_data_S <= MSG_MEAS_ASK_10;		-- Prepare tx_data for the next message. Ask for ch10
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_8;
					ELSE
						state <= MEAS_ASK_10;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_8;
				END IF;					

			WHEN MEAS_ASK_10 =>					-- Asked ch10 to be measured. Wait until SPI transfer finish. Receive ch8 data
				tx_data_S <= MSG_MEAS_ASK_10;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(4) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(4) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(4) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(4) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(4) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(4) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_10;
				ELSE
					state <= MEAS_ASK_10;
				END IF;
				
			WHEN MEAS_DELAY_ASK_10 =>				-- Delay after asked ch10 message
				tx_data_S <= MSG_MEAS_ASK_12;		-- Prepare tx_data for the next message. Ask for ch12
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_10;
					ELSE
						state <= MEAS_ASK_12;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_10;
				END IF;					

			WHEN MEAS_ASK_12 =>					-- Asked ch12 to be measured. Wait until SPI transfer finish. Receive ch10 data
				tx_data_S <= MSG_MEAS_ASK_12;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(5) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(5) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(5) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(5) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(5) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(5) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_12;
				ELSE
					state <= MEAS_ASK_12;
				END IF;
				
			WHEN MEAS_DELAY_ASK_12 =>				-- Delay after asked ch12 message
				tx_data_S <= MSG_MEAS_ASK_14;		-- Prepare tx_data for the next message. Ask for ch14
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_12;
					ELSE
						state <= MEAS_ASK_14;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_12;
				END IF;	
				
			WHEN MEAS_ASK_14 =>					-- Asked ch14 to be measured. Wait until SPI transfer finish. Receive ch12 data
				tx_data_S <= MSG_MEAS_ASK_14;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(6) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(6) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(6) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(6) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(6) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(6) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_14;
				ELSE
					state <= MEAS_ASK_14;
				END IF;
				
			WHEN MEAS_DELAY_ASK_14 =>				-- Delay after asked ch14 message
				tx_data_S <= MSG_MEAS_ASK_0;		-- Prepare tx_data for the next message. Ask for ch0 in case of continuous sampling
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_14;
					ELSE
						state <= MEAS_ASK_EXTRA;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_14;
				END IF;					

			WHEN MEAS_ASK_EXTRA =>					-- Asked ch0 to be measured. Wait until SPI transfer finish. Receive ch14 data
				tx_data_S <= MSG_MEAS_ASK_0;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					board_1_adc_1_array_S(7) <= rx_data_1_S; -- storage rx_data into the internal memory
					board_1_adc_2_array_S(7) <= rx_data_2_S; -- storage rx_data into the internal memory
					board_1_adc_3_array_S(7) <= rx_data_3_S; -- storage rx_data into the internal memory
					board_2_adc_1_array_S(7) <= rx_data_4_S; -- storage rx_data into the internal memory
					board_2_adc_2_array_S(7) <= rx_data_5_S; -- storage rx_data into the internal memory
					board_2_adc_3_array_S(7) <= rx_data_6_S; -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_EXTRA;
				ELSE
					state <= MEAS_ASK_EXTRA;
				END IF;
				
			WHEN MEAS_DELAY_ASK_EXTRA =>			-- Delay after asked extra ch0 message
				tx_data_S <= MSG_MEAS_ASK_0;		-- Prepare tx_data for the next message. Ask for ch0 in case of continuous sampling
				enable_spi_S <= '0';				-- Do not start a new SPI transfer because IDLE state is coming next
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					counter <= DELAY;
					state <= IDLE;		
				ELSE
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_EXTRA;
				END IF;	

			WHEN ERROR_STATE =>						-- Error state rise the error flag to 1 and stop the state machine
				tx_data_S <= MSG_RESET;				-- Prepare tx_data for the next message. Reset adc chip register to defaults
				IF counter = DELAY_ERROR THEN		-- Extra delay added.
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY_ERROR;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= ERROR_STATE;
					ELSE
						state <= INIT_RESET;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= ERROR_STATE;
				END IF;		

			WHEN INIT_RESET =>					-- Initializing ADC mode register to reset chip registers to defaults
				tx_data_S <= MSG_RESET;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_RESET;
				ELSE
					state <= INIT_RESET;
				END IF;

			WHEN INIT_DELAY_RESET =>			-- Wait a long delay after reset chips
				tx_data_S <= (others => '0');
				enable_spi_S <= '0';			
				IF counter = DELAY_ERROR THEN
					state <= INIT_START;
					counter <= 0;
				ELSE
					state <= INIT_DELAY_RESET;
					counter <= counter + 1;
				END IF;						
			
			END CASE;
		END IF;
	END PROCESS;


    -- Assign meas done signal process
	meas_done_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			meas_done_S <= '0';
		ELSIF rising_edge(clk) THEN
			IF state = IDLE THEN
				meas_done_S <= '1';
			ELSE
				meas_done_S <= '0';
			END IF;
		END IF;
	END PROCESS;	

    -- Assign init done signal process
	init_done_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			init_done_S <= '0';
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_START) or (state = INIT_ADC_REG) or (state = INIT_DELAY_0) or (state = INIT_BIPOLAR_REG) or (state = INIT_DELAY_1) or (state = INIT_UNIPOLAR_REG) or (state = INIT_DELAY_2) or (state = INIT_RANGE_REG) or (state = INIT_DELAY_3) or (state = ERROR_STATE) or (state = INIT_RESET) or (state = INIT_DELAY_RESET)) THEN
				init_done_S <= '0';
			ELSE
				init_done_S <= '1';
			END IF;
		END IF;
	END PROCESS;	
	
    -- Assign echoed bipolar arrays process
	Echoed_bipolar_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			data_echo_bipolar_S <= (others => (others => '0'));
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_UNIPOLAR_REG) AND (busy_spi_S = '0')) THEN
				data_echo_bipolar_S(1) <= rx_data_1_S;
				data_echo_bipolar_S(2) <= rx_data_2_S;
				data_echo_bipolar_S(3) <= rx_data_3_S;
				data_echo_bipolar_S(4) <= rx_data_4_S;
				data_echo_bipolar_S(5) <= rx_data_5_S;
				data_echo_bipolar_S(6) <= rx_data_6_S;
			ELSE
				data_echo_bipolar_S <= data_echo_bipolar_S;
			END IF;
		END IF;
	END PROCESS;

    -- Assign echoed unipolar arrays process
	Echoed_unipolar_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			data_echo_unipolar_S <= (others => (others => '0'));
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_RANGE_REG) AND (busy_spi_S = '0')) THEN
				data_echo_unipolar_S(1) <= rx_data_1_S;
				data_echo_unipolar_S(2) <= rx_data_2_S;
				data_echo_unipolar_S(3) <= rx_data_3_S;
				data_echo_unipolar_S(4) <= rx_data_4_S;
				data_echo_unipolar_S(5) <= rx_data_5_S;
				data_echo_unipolar_S(6) <= rx_data_6_S;
			ELSE
				data_echo_unipolar_S <= data_echo_unipolar_S;
			END IF;
		END IF;
	END PROCESS;			
    
    -- Verify echoed bipolar message
	Verify_echoed_bipolar : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			adc_echoed_bipolar_S <= (others => '0');
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_UNIPOLAR_REG) AND (busy_spi_S = '0')) THEN
				IF (rx_data_1_S = MSG_INIT_2)  THEN	-- check echo on adc chip 1
					adc_echoed_bipolar_S(1) <= '1';
				ELSE 
					adc_echoed_bipolar_S(1) <= '0';
				END IF;
				IF (rx_data_2_S = MSG_INIT_2)  THEN	-- check echo on adc chip 2
					adc_echoed_bipolar_S(2) <= '1';
				ELSE 
					adc_echoed_bipolar_S(2) <= '0';
				END IF;
				IF (rx_data_3_S = MSG_INIT_2)  THEN	-- check echo on adc chip 3
					adc_echoed_bipolar_S(3) <= '1';
				ELSE 
					adc_echoed_bipolar_S(3) <= '0';
				END IF;
				IF (rx_data_4_S = MSG_INIT_2)  THEN	-- check echo on adc chip 4
					adc_echoed_bipolar_S(4) <= '1';
				ELSE 
					adc_echoed_bipolar_S(4) <= '0';
				END IF;
				IF (rx_data_5_S = MSG_INIT_2)  THEN	-- check echo on adc chip 5
					adc_echoed_bipolar_S(5) <= '1';
				ELSE 
					adc_echoed_bipolar_S(5) <= '0';
				END IF;
				IF (rx_data_6_S = MSG_INIT_2)  THEN	-- check echo on adc chip 6
					adc_echoed_bipolar_S(6) <= '1';
				ELSE 
					adc_echoed_bipolar_S(6) <= '0';
				END IF;
			ELSIF state = INIT_START THEN
				adc_echoed_bipolar_S <= (others => '0');
			ELSE
				adc_echoed_bipolar_S <= adc_echoed_bipolar_S;
			END IF;
		END IF;
	END PROCESS;	

    -- Verify echoed unipolar message
	Verify_echoed_unipolar : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			adc_echoed_unipolar_S <= (others => '0');
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_RANGE_REG) AND (busy_spi_S = '0')) THEN
				IF (rx_data_1_S = MSG_INIT_3)  THEN	-- check echo on adc chip 1
					adc_echoed_unipolar_S(1) <= '1';
				ELSE 
					adc_echoed_unipolar_S(1) <= '0';
				END IF;
				IF (rx_data_2_S = MSG_INIT_3)  THEN	-- check echo on adc chip 2
					adc_echoed_unipolar_S(2) <= '1';
				ELSE 
					adc_echoed_unipolar_S(2) <= '0';
				END IF;
				IF (rx_data_3_S = MSG_INIT_3)  THEN	-- check echo on adc chip 3
					adc_echoed_unipolar_S(3) <= '1';
				ELSE 
					adc_echoed_unipolar_S(3) <= '0';
				END IF;
				IF (rx_data_4_S = MSG_INIT_3)  THEN	-- check echo on adc chip 4
					adc_echoed_unipolar_S(4) <= '1';
				ELSE 
					adc_echoed_unipolar_S(4) <= '0';
				END IF;
				IF (rx_data_5_S = MSG_INIT_3)  THEN	-- check echo on adc chip 5
					adc_echoed_unipolar_S(5) <= '1';
				ELSE 
					adc_echoed_unipolar_S(5) <= '0';
				END IF;
				IF (rx_data_6_S = MSG_INIT_3)  THEN	-- check echo on adc chip 6
					adc_echoed_unipolar_S(6) <= '1';
				ELSE 
					adc_echoed_unipolar_S(6) <= '0';
				END IF;
			ELSIF state = INIT_START THEN
				adc_echoed_unipolar_S <= (others => '0');				
			ELSE
				adc_echoed_unipolar_S <= adc_echoed_unipolar_S;
			END IF;
		END IF;
	END PROCESS;	
	
    -- Error signal process
	error_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			error_S <= '0';
		ELSIF rising_edge(clk) THEN
			IF (state = ERROR_STATE) THEN
				error_S <= '1';
			ELSE
				error_S <= '0';
			END IF;
		END IF;
	END PROCESS;

    -- Error counter signal process
	error_counter_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			error_counter_S <= (others => '0');
		ELSIF rising_edge(clk) THEN
			IF ((state = ERROR_STATE) AND (counter = 1)) THEN
				error_counter_S <= std_logic_vector(to_unsigned(to_integer(unsigned( error_counter_S )) + 1, 32));
			ELSE
				error_counter_S <= error_counter_S;
			END IF;
		END IF;
	END PROCESS;
	
	-- Assign output measurement arrays process
	Output_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			data_b1_i1_ch1_S <= (OTHERS => '0');
			data_b1_i1_ch2_S <= (OTHERS => '0');
			data_b1_i1_ch3_S <= (OTHERS => '0');
			data_b1_i1_ch4_S <= (OTHERS => '0');
			data_b1_i2_ch1_S <= (OTHERS => '0');
			data_b1_i2_ch2_S <= (OTHERS => '0');
			data_b1_i2_ch3_S <= (OTHERS => '0');
			data_b1_i2_ch4_S <= (OTHERS => '0');
			data_b1_i3_ch1_S <= (OTHERS => '0');
			data_b1_i3_ch2_S <= (OTHERS => '0');
			data_b1_i3_ch3_S <= (OTHERS => '0');
			data_b1_i3_ch4_S <= (OTHERS => '0');
			data_b1_i4_ch1_S <= (OTHERS => '0');
			data_b1_i4_ch2_S <= (OTHERS => '0');
			data_b1_i4_ch3_S <= (OTHERS => '0');
			data_b1_i4_ch4_S <= (OTHERS => '0');
			data_b1_i5_ch1_S <= (OTHERS => '0');
			data_b1_i5_ch2_S <= (OTHERS => '0');
			data_b1_i5_ch3_S <= (OTHERS => '0');
			data_b1_i5_ch4_S <= (OTHERS => '0');
			data_b1_i6_ch1_S <= (OTHERS => '0');
			data_b1_i6_ch2_S <= (OTHERS => '0');
			data_b1_i6_ch3_S <= (OTHERS => '0');
			data_b1_i6_ch4_S <= (OTHERS => '0');
			data_b2_i1_ch1_S <= (OTHERS => '0');
			data_b2_i1_ch2_S <= (OTHERS => '0');
			data_b2_i1_ch3_S <= (OTHERS => '0');
			data_b2_i1_ch4_S <= (OTHERS => '0');
			data_b2_i2_ch1_S <= (OTHERS => '0');
			data_b2_i2_ch2_S <= (OTHERS => '0');
			data_b2_i2_ch3_S <= (OTHERS => '0');
			data_b2_i2_ch4_S <= (OTHERS => '0');
			data_b2_i3_ch1_S <= (OTHERS => '0');
			data_b2_i3_ch2_S <= (OTHERS => '0');
			data_b2_i3_ch3_S <= (OTHERS => '0');
			data_b2_i3_ch4_S <= (OTHERS => '0');
			data_b2_i4_ch1_S <= (OTHERS => '0');
			data_b2_i4_ch2_S <= (OTHERS => '0');
			data_b2_i4_ch3_S <= (OTHERS => '0');
			data_b2_i4_ch4_S <= (OTHERS => '0');
			data_b2_i5_ch1_S <= (OTHERS => '0');
			data_b2_i5_ch2_S <= (OTHERS => '0');
			data_b2_i5_ch3_S <= (OTHERS => '0');
			data_b2_i5_ch4_S <= (OTHERS => '0');
			data_b2_i6_ch1_S <= (OTHERS => '0');
			data_b2_i6_ch2_S <= (OTHERS => '0');
			data_b2_i6_ch3_S <= (OTHERS => '0');
			data_b2_i6_ch4_S <= (OTHERS => '0');
			new_data_S <= '0';
			
			ELSIF rising_edge(clk) THEN
				IF meas_done_S = '1' THEN
					data_b1_i1_ch1_S <= board_1_adc_1_array_S(6);	-- ADC CH 12, input 1, board 1-- Fix this! in every input
					data_b1_i1_ch2_S <= board_1_adc_1_array_S(4);	-- ADC CH 8, input 1, board 1
					data_b1_i1_ch3_S <= board_1_adc_1_array_S(2);	-- ADC CH 4, input 1, board 1
					data_b1_i1_ch4_S <= board_1_adc_1_array_S(0);	-- ADC CH 0, input 1, board 1-- Fix this! in every input
					data_b1_i2_ch1_S <= board_1_adc_1_array_S(7);	-- ADC CH 14, input 2, board 1
					data_b1_i2_ch2_S <= board_1_adc_1_array_S(5);	-- ADC CH 10, input 2, board 1
					data_b1_i2_ch3_S <= board_1_adc_1_array_S(3);	-- ADC CH 6, input 2, board 1
					data_b1_i2_ch4_S <= board_1_adc_1_array_S(1);	-- ADC CH 2, input 2, board 1
					data_b1_i3_ch1_S <= board_1_adc_2_array_S(6);	-- ADC CH 12, input 3, board 1
					data_b1_i3_ch2_S <= board_1_adc_2_array_S(4);	-- ADC CH 8, input 3, board 1
					data_b1_i3_ch3_S <= board_1_adc_2_array_S(2);	-- ADC CH 4, input 3, board 1
					data_b1_i3_ch4_S <= board_1_adc_2_array_S(0);	-- ADC CH 0, input 3, board 1
					data_b1_i4_ch1_S <= board_1_adc_2_array_S(7);	-- ADC CH 14, input 4, board 1
					data_b1_i4_ch2_S <= board_1_adc_2_array_S(5);	-- ADC CH 10, input 4, board 1
					data_b1_i4_ch3_S <= board_1_adc_2_array_S(3);	-- ADC CH 6, input 4, board 1
					data_b1_i4_ch4_S <= board_1_adc_2_array_S(1);	-- ADC CH 2	, input 4, board 1
					data_b1_i5_ch1_S <= board_1_adc_3_array_S(6);	-- ADC CH 12, input 5, board 1
					data_b1_i5_ch2_S <= board_1_adc_3_array_S(4);	-- ADC CH 8, input 5, board 1
					data_b1_i5_ch3_S <= board_1_adc_3_array_S(2);	-- ADC CH 4, input 5, board 1
					data_b1_i5_ch4_S <= board_1_adc_3_array_S(0);	-- ADC CH 0, input 5, board 1
					data_b1_i6_ch1_S <= board_1_adc_3_array_S(7);	-- ADC CH 14, input 6, board 1
					data_b1_i6_ch2_S <= board_1_adc_3_array_S(5);	-- ADC CH 10, input 6, board 1
					data_b1_i6_ch3_S <= board_1_adc_3_array_S(3);	-- ADC CH 6, input 6, board 1
					data_b1_i6_ch4_S <= board_1_adc_3_array_S(1);	-- ADC CH 2	, input 6, board 1
					data_b2_i1_ch1_S <= board_2_adc_1_array_S(6);	-- ADC CH 12, input 1, board 2
                    data_b2_i1_ch2_S <= board_2_adc_1_array_S(4);    -- ADC CH 8, input 1, board 2
                    data_b2_i1_ch3_S <= board_2_adc_1_array_S(2);    -- ADC CH 4, input 1, board 2
                    data_b2_i1_ch4_S <= board_2_adc_1_array_S(0);    -- ADC CH 0, input 1, board 2
                    data_b2_i2_ch1_S <= board_2_adc_1_array_S(7);    -- ADC CH 14, input 2, board 2
                    data_b2_i2_ch2_S <= board_2_adc_1_array_S(5);    -- ADC CH 10, input 2, board 2
                    data_b2_i2_ch3_S <= board_2_adc_1_array_S(3);    -- ADC CH 6, input 2, board 2
                    data_b2_i2_ch4_S <= board_2_adc_1_array_S(1);    -- ADC CH 2, input 2, board 1
                    data_b2_i3_ch1_S <= board_2_adc_2_array_S(6);    -- ADC CH 12, input 3, board 1
                    data_b2_i3_ch2_S <= board_2_adc_2_array_S(4);    -- ADC CH 8, input 3, board 1
                    data_b2_i3_ch3_S <= board_2_adc_2_array_S(2);    -- ADC CH 4, input 3, board 1
                    data_b2_i3_ch4_S <= board_2_adc_2_array_S(0);    -- ADC CH 0, input 3, board 1
                    data_b2_i4_ch1_S <= board_2_adc_2_array_S(7);    -- ADC CH 14, input 4, board 1
                    data_b2_i4_ch2_S <= board_2_adc_2_array_S(5);    -- ADC CH 10, input 4, board 1
                    data_b2_i4_ch3_S <= board_2_adc_2_array_S(3);    -- ADC CH 6, input 4, board 1
                    data_b2_i4_ch4_S <= board_2_adc_2_array_S(1);    -- ADC CH 2    , input 4, board 1
                    data_b2_i5_ch1_S <= board_2_adc_3_array_S(6);    -- ADC CH 12, input 5, board 1
                    data_b2_i5_ch2_S <= board_2_adc_3_array_S(4);    -- ADC CH 8, input 5, board 1
                    data_b2_i5_ch3_S <= board_2_adc_3_array_S(2);    -- ADC CH 4, input 5, board 1
                    data_b2_i5_ch4_S <= board_2_adc_3_array_S(0);    -- ADC CH 0, input 5, board 1
                    data_b2_i6_ch1_S <= board_2_adc_3_array_S(7);    -- ADC CH 14, input 6, board 1
                    data_b2_i6_ch2_S <= board_2_adc_3_array_S(5);    -- ADC CH 10, input 6, board 1
                    data_b2_i6_ch3_S <= board_2_adc_3_array_S(3);    -- ADC CH 6, input 6, board 1
                    data_b2_i6_ch4_S <= board_2_adc_3_array_S(1);    -- ADC CH 2    , input 6, board 1					
					new_data_S <= '1';
				ELSE
					data_b1_i1_ch1_S <= data_b1_i1_ch1_S;
					data_b1_i1_ch2_S <= data_b1_i1_ch2_S;
					data_b1_i1_ch3_S <= data_b1_i1_ch3_S;
					data_b1_i1_ch4_S <= data_b1_i1_ch4_S;
					data_b1_i2_ch1_S <= data_b1_i2_ch1_S;
					data_b1_i2_ch2_S <= data_b1_i2_ch2_S;
					data_b1_i2_ch3_S <= data_b1_i2_ch3_S;
					data_b1_i2_ch4_S <= data_b1_i2_ch4_S;
					data_b1_i3_ch1_S <= data_b1_i3_ch1_S;
					data_b1_i3_ch2_S <= data_b1_i3_ch2_S;
					data_b1_i3_ch3_S <= data_b1_i3_ch3_S;
					data_b1_i3_ch4_S <= data_b1_i3_ch4_S;
					data_b1_i4_ch1_S <= data_b1_i4_ch1_S;
					data_b1_i4_ch2_S <= data_b1_i4_ch2_S;
					data_b1_i4_ch3_S <= data_b1_i4_ch3_S;
					data_b1_i4_ch4_S <= data_b1_i4_ch4_S;
					data_b1_i5_ch1_S <= data_b1_i5_ch1_S;
					data_b1_i5_ch2_S <= data_b1_i5_ch2_S;
					data_b1_i5_ch3_S <= data_b1_i5_ch3_S;
					data_b1_i5_ch4_S <= data_b1_i5_ch4_S;
					data_b1_i6_ch1_S <= data_b1_i6_ch1_S;
					data_b1_i6_ch2_S <= data_b1_i6_ch2_S;
					data_b1_i6_ch3_S <= data_b1_i6_ch3_S;
					data_b1_i6_ch4_S <= data_b1_i6_ch4_S;
					data_b2_i1_ch1_S <= data_b2_i1_ch1_S;
                    data_b2_i1_ch2_S <= data_b2_i1_ch2_S;
                    data_b2_i1_ch3_S <= data_b2_i1_ch3_S;
                    data_b2_i1_ch4_S <= data_b2_i1_ch4_S;
                    data_b2_i2_ch1_S <= data_b2_i2_ch1_S;
                    data_b2_i2_ch2_S <= data_b2_i2_ch2_S;
                    data_b2_i2_ch3_S <= data_b2_i2_ch3_S;
                    data_b2_i2_ch4_S <= data_b2_i2_ch4_S;
                    data_b2_i3_ch1_S <= data_b2_i3_ch1_S;
                    data_b2_i3_ch2_S <= data_b2_i3_ch2_S;
                    data_b2_i3_ch3_S <= data_b2_i3_ch3_S;
                    data_b2_i3_ch4_S <= data_b2_i3_ch4_S;
                    data_b2_i4_ch1_S <= data_b2_i4_ch1_S;
                    data_b2_i4_ch2_S <= data_b2_i4_ch2_S;
                    data_b2_i4_ch3_S <= data_b2_i4_ch3_S;
                    data_b2_i4_ch4_S <= data_b2_i4_ch4_S;
                    data_b2_i5_ch1_S <= data_b2_i5_ch1_S;
                    data_b2_i5_ch2_S <= data_b2_i5_ch2_S;
                    data_b2_i5_ch3_S <= data_b2_i5_ch3_S;
                    data_b2_i5_ch4_S <= data_b2_i5_ch4_S;
                    data_b2_i6_ch1_S <= data_b2_i6_ch1_S;
                    data_b2_i6_ch2_S <= data_b2_i6_ch2_S;
                    data_b2_i6_ch3_S <= data_b2_i6_ch3_S;
                    data_b2_i6_ch4_S <= data_b2_i6_ch4_S;
					new_data_S <= '0';
				END IF;
			END IF;
	END PROCESS;

	error <= error_S;
	error_counter <= error_counter_S;
	new_data <= new_data_S;
	init_done <= init_done_S;
	meas_done <= meas_done_S;

	verify_echo_bipolar <= verify_echo_bipolar_detail(1) AND verify_echo_bipolar_detail(2) AND verify_echo_bipolar_detail(3) AND verify_echo_bipolar_detail(4) AND verify_echo_bipolar_detail(5) AND verify_echo_bipolar_detail(6);
	verify_echo_unipolar <= verify_echo_unipolar_detail(1) AND verify_echo_unipolar_detail(2) AND verify_echo_unipolar_detail(3) AND verify_echo_unipolar_detail(4) AND verify_echo_unipolar_detail(5) AND verify_echo_unipolar_detail(6);
	
	verify_echo_bipolar_detail(1) <= '0' when ((adc_selector(1) = '1') AND (adc_echoed_bipolar_S(1) = '0')) else '1';
	verify_echo_bipolar_detail(2) <= '0' when ((adc_selector(2) = '1') AND (adc_echoed_bipolar_S(2) = '0')) else '1';
	verify_echo_bipolar_detail(3) <= '0' when ((adc_selector(3) = '1') AND (adc_echoed_bipolar_S(3) = '0')) else '1';
	verify_echo_bipolar_detail(4) <= '0' when ((adc_selector(4) = '1') AND (adc_echoed_bipolar_S(4) = '0')) else '1';
	verify_echo_bipolar_detail(5) <= '0' when ((adc_selector(5) = '1') AND (adc_echoed_bipolar_S(5) = '0')) else '1';
	verify_echo_bipolar_detail(6) <= '0' when ((adc_selector(6) = '1') AND (adc_echoed_bipolar_S(6) = '0')) else '1';

	verify_echo_unipolar_detail(1) <= '0' when ((adc_selector(1) = '1') AND (adc_echoed_unipolar_S(1) = '0')) else '1';
	verify_echo_unipolar_detail(2) <= '0' when ((adc_selector(2) = '1') AND (adc_echoed_unipolar_S(2) = '0')) else '1';
	verify_echo_unipolar_detail(3) <= '0' when ((adc_selector(3) = '1') AND (adc_echoed_unipolar_S(3) = '0')) else '1';
	verify_echo_unipolar_detail(4) <= '0' when ((adc_selector(4) = '1') AND (adc_echoed_unipolar_S(4) = '0')) else '1';
	verify_echo_unipolar_detail(5) <= '0' when ((adc_selector(5) = '1') AND (adc_echoed_unipolar_S(5) = '0')) else '1';
	verify_echo_unipolar_detail(6) <= '0' when ((adc_selector(6) = '1') AND (adc_echoed_unipolar_S(6) = '0')) else '1';
	
	data_echo_bipolar_1 <= data_echo_bipolar_S(1);
	data_echo_bipolar_2 <= data_echo_bipolar_S(2);
	data_echo_bipolar_3 <= data_echo_bipolar_S(3);
	data_echo_bipolar_4 <= data_echo_bipolar_S(4);
	data_echo_bipolar_5 <= data_echo_bipolar_S(5);
	data_echo_bipolar_6 <= data_echo_bipolar_S(6);
	data_echo_unipolar_1 <= data_echo_unipolar_S(1);
	data_echo_unipolar_2 <= data_echo_unipolar_S(2);
	data_echo_unipolar_3 <= data_echo_unipolar_S(3);
	data_echo_unipolar_4 <= data_echo_unipolar_S(4);
	data_echo_unipolar_5 <= data_echo_unipolar_S(5);
	data_echo_unipolar_6 <= data_echo_unipolar_S(6);

	data_board_1_input_1_ch1 <= data_b1_i1_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_1_ch2 <= data_b1_i1_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_1_ch3 <= data_b1_i1_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_1_ch4 <= data_b1_i1_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_2_ch1 <= data_b1_i2_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_2_ch2 <= data_b1_i2_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_2_ch3 <= data_b1_i2_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_2_ch4 <= data_b1_i2_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_3_ch1 <= data_b1_i3_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_3_ch2 <= data_b1_i3_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_3_ch3 <= data_b1_i3_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_3_ch4 <= data_b1_i3_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_4_ch1 <= data_b1_i4_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_4_ch2 <= data_b1_i4_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_4_ch3 <= data_b1_i4_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_4_ch4 <= data_b1_i4_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_5_ch1 <= data_b1_i5_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_5_ch2 <= data_b1_i5_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_5_ch3 <= data_b1_i5_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_5_ch4 <= data_b1_i5_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_6_ch1 <= data_b1_i6_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_6_ch2 <= data_b1_i6_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_6_ch3 <= data_b1_i6_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_1_input_6_ch4 <= data_b1_i6_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_1_ch1 <= data_b2_i1_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
    data_board_2_input_1_ch2 <= data_b2_i1_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_1_ch3 <= data_b2_i1_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_1_ch4 <= data_b2_i1_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_2_ch1 <= data_b2_i2_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_2_ch2 <= data_b2_i2_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_2_ch3 <= data_b2_i2_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_2_ch4 <= data_b2_i2_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
    data_board_2_input_3_ch1 <= data_b2_i3_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_3_ch2 <= data_b2_i3_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_3_ch3 <= data_b2_i3_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_3_ch4 <= data_b2_i3_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_4_ch1 <= data_b2_i4_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_4_ch2 <= data_b2_i4_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_4_ch3 <= data_b2_i4_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_4_ch4 <= data_b2_i4_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_5_ch1 <= data_b2_i5_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_5_ch2 <= data_b2_i5_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_5_ch3 <= data_b2_i5_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_5_ch4 <= data_b2_i5_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_6_ch1 <= data_b2_i6_ch1_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_6_ch2 <= data_b2_i6_ch2_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_6_ch3 <= data_b2_i6_ch3_S(OUTPUT_WORD_WIDTH-1 downto 0);
	data_board_2_input_6_ch4 <= data_b2_i6_ch4_S(OUTPUT_WORD_WIDTH-1 downto 0);
end Behavioral;
