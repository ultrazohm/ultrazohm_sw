library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.ADC_MAX11331_PKG.all;


entity ADC_MAX11331_top is
	generic (
		-- Users to add parameters here
		OUTPUT_WORD_WIDTH : INTEGER := 16;            -- Use 12 for normal operation. Use 16 for debug.
		NUMBER_OF_ADCS	: INTEGER := 1;						-- How many MAX11331 ADCs are connected to this IP Core, maximum is 6!
		DIFFERENTIAL_SAMPLING : boolean := false; 		-- true: 8 differential inputs, false: 16 single-ended inputs
		DEBUG_MESSAGE_INCLUDED: boolean := false;			-- true: adds 4bit ADC register + 12 bit sample result

		SIMULATION_DEBUG : boolean := false;
		-- User parameters ends
		-- Do not modify the parameters beyond this line
		-- Parameters of Axi Slave Bus Interface S_AXI_Lite
		C_S_AXI_Lite_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_Lite_ADDR_WIDTH	: integer	:= 6
	);
	port (
		-- Users to add ports here
		clk 								: in STD_LOGIC;
		reset_n 							: in STD_LOGIC;
		enable_measure 				: in STD_LOGIC;
		sclk 								: out STD_LOGIC;
		mosi 								: out STD_LOGIC;
		miso 								: in STD_LOGIC_VECTOR (NUMBER_OF_ADCS-1 downto 0);
		ss_n 								: out STD_LOGIC;
		init_done 						: out STD_LOGIC;
		meas_done 						: out STD_LOGIC;
		new_data 						: out STD_LOGIC;
		error 							: out STD_LOGIC;
		ch0	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch1	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch2	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch3	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch4	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch5	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch6	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch7	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch8	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch9	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch10: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch11: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch12: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch13: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch14: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		ch15: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);

		-- User ports ends
		-- Do not modify the ports beyond this line


		-- Ports of Axi Slave Bus Interface S_AXI_Lite
		s_axi_lite_aclk	: in std_logic;
		s_axi_lite_aresetn	: in std_logic;
		s_axi_lite_awaddr	: in std_logic_vector(C_S_AXI_Lite_ADDR_WIDTH-1 downto 0);
		s_axi_lite_awprot	: in std_logic_vector(2 downto 0);
		s_axi_lite_awvalid	: in std_logic;
		s_axi_lite_awready	: out std_logic;
		s_axi_lite_wdata	: in std_logic_vector(C_S_AXI_Lite_DATA_WIDTH-1 downto 0);
		s_axi_lite_wstrb	: in std_logic_vector((C_S_AXI_Lite_DATA_WIDTH/8)-1 downto 0);
		s_axi_lite_wvalid	: in std_logic;
		s_axi_lite_wready	: out std_logic;
		s_axi_lite_bresp	: out std_logic_vector(1 downto 0);
		s_axi_lite_bvalid	: out std_logic;
		s_axi_lite_bready	: in std_logic;
		s_axi_lite_araddr	: in std_logic_vector(C_S_AXI_Lite_ADDR_WIDTH-1 downto 0);
		s_axi_lite_arprot	: in std_logic_vector(2 downto 0);
		s_axi_lite_arvalid	: in std_logic;
		s_axi_lite_arready	: out std_logic;
		s_axi_lite_rdata	: out std_logic_vector(C_S_AXI_Lite_DATA_WIDTH-1 downto 0);
		s_axi_lite_rresp	: out std_logic_vector(1 downto 0);
		s_axi_lite_rvalid	: out std_logic;
		s_axi_lite_rready	: in std_logic
	);
end ADC_MAX11331_top;

architecture arch_imp of ADC_MAX11331_top is

	-- component declaration
	component ADC_MAX11331_AXI_Lite is
		generic (
		NUMBER_OF_ADCS	    : INTEGER   := 1;			
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_ADDR_WIDTH	: integer	:= 6
		);
		port (
		init_done 					: in STD_LOGIC;
		meas_done 					: in STD_LOGIC;
		error 						: in STD_LOGIC;		
		error_counter				: in STD_LOGIC_VECTOR (31 downto 0);
		clk_division 				: out STD_LOGIC_VECTOR(3 DOWNTO 0);          --system clock cycles per 1/2 period of sclk	
		
		data_echo_bipolar_1			: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_2			: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_3			: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_4			: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_5			: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_bipolar_6			: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_1		: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_2		: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_3		: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_4		: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_5		: in STD_LOGIC_VECTOR (15 downto 0);
		data_echo_unipolar_6		: in STD_LOGIC_VECTOR (15 downto 0);	
		adc_selector				: out STD_LOGIC_VECTOR (NUMBER_OF_ADCS downto 1);	
		force_init 					: out STD_LOGIC;			
		S_AXI_ACLK	: in std_logic;
		S_AXI_ARESETN	: in std_logic;
		S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
		S_AXI_AWVALID	: in std_logic;
		S_AXI_AWREADY	: out std_logic;
		S_AXI_WDATA	: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_WSTRB	: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		S_AXI_WVALID	: in std_logic;
		S_AXI_WREADY	: out std_logic;
		S_AXI_BRESP	: out std_logic_vector(1 downto 0);
		S_AXI_BVALID	: out std_logic;
		S_AXI_BREADY	: in std_logic;
		S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
		S_AXI_ARVALID	: in std_logic;
		S_AXI_ARREADY	: out std_logic;
		S_AXI_RDATA	: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_RRESP	: out std_logic_vector(1 downto 0);
		S_AXI_RVALID	: out std_logic;
		S_AXI_RREADY	: in std_logic
		);
	end component ADC_MAX11331_AXI_Lite;

	component Slow_ADC_Memory_main is
	GENERIC
	(
		OUTPUT_WORD_WIDTH 	: INTEGER := 12;            -- Use 12 for normal operation. Use 16 for debug.
		DIFFERENTIAL_SAMPLING : boolean := false;			 -- true: 8 differential inputs, false: 16 single-ended inputs
		DEBUG_MESSAGE_INCLUDED : BOOLEAN := false;			-- true: adds 4bit ADC register + 12 bit sample result
		NUMBER_OF_ADCS			: INTEGER := 1					-- How many MAX11331 ADCs are connected to this IP Core
	);
	Port
	(
		clk 								: in STD_LOGIC;
		reset_n 							: in STD_LOGIC;
		enable_measure 				        : in STD_LOGIC;
		clk_division : IN 	STD_LOGIC_VECTOR(3 DOWNTO 0);          --system clock cycles per 1/2 period of sclk				
		sclk 								: out STD_LOGIC;
		mosi 								: out STD_LOGIC;
		miso 								: in STD_LOGIC_VECTOR (NUMBER_OF_ADCS-1 downto 0);
		ss_n 								: out STD_LOGIC;
		init_done 						: out STD_LOGIC;
		meas_done 						: out STD_LOGIC;
		new_data 						: out STD_LOGIC;
		error 							: out STD_LOGIC;
		error_counter				: out STD_LOGIC_VECTOR (31 downto 0);
		adc_selector				: in STD_LOGIC_VECTOR (NUMBER_OF_ADCS downto 1);	
		force_init 					: in STD_LOGIC;		

		data_echo_bipolar       : out t_array_message(NUMBER_OF_ADCS downto 1);
		data_echo_unipolar      : out t_array_message(NUMBER_OF_ADCS downto 1);

		all_differential_channels : out t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0);
		all_single_ended_channels : out t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0);

		data_ch0 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch1 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch2 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch3 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch4 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch5 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch6 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch7 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch8 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch9 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch10	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch11	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch12	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch13	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch14	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch15	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0)
	);
	end component Slow_ADC_Memory_main;
	
	signal	meas_done_S				:	STD_LOGIC := '0';
	signal	init_done_S				:	STD_LOGIC := '0';
	signal	error_S					:	STD_LOGIC := '0';
	signal	error_counter_S			:	STD_LOGIC_VECTOR (31 downto 0) := (others=>'0'); 
	signal	force_init_S			:	STD_LOGIC := '0'; 

	signal  data_echo_bipolar_1_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_bipolar_2_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_bipolar_3_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_bipolar_4_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_bipolar_5_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_bipolar_6_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_unipolar_1_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_unipolar_2_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_unipolar_3_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_unipolar_4_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_unipolar_5_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_echo_unipolar_6_S	:	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	constant data_echo_zero 	    :	STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 


	signal 	data_echo_bipolar       :   t_array_message(NUMBER_OF_ADCS downto 1) := (others => (others => '0'));
	signal 	data_echo_unipolar      :   t_array_message(NUMBER_OF_ADCS downto 1) := (others => (others => '0'));
	
	signal all_differential_channels : t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0) := (others=> (others => (others => '0')));
	signal all_single_ended_channels : t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0) := (others=> (others => (others => '0')));

	signal	clk_division_spi		:	STD_LOGIC_VECTOR (3 downto 0) := (others=>'0'); 
	signal	clk_division_AXI		:	STD_LOGIC_VECTOR (3 downto 0) := (others=>'0'); 
	constant clk_division_debug     :	STD_LOGIC_VECTOR (3 downto 0) := "0010";

	signal	adc_selector_spi		:	STD_LOGIC_VECTOR (NUMBER_OF_ADCS downto 1) := (others=>'0'); 
	signal	adc_selector_AXI		:	STD_LOGIC_VECTOR (NUMBER_OF_ADCS downto 1) := (others=>'0'); 
	constant adc_selector_debug		:	STD_LOGIC_VECTOR (NUMBER_OF_ADCS downto 1) := (others=>'1'); 

begin

	
	-- Add user logic here
	-- Instantiation of max11331 driver	
	Slow_ADC_Memory_main_inst : Slow_ADC_Memory_main
	generic map
	(
		OUTPUT_WORD_WIDTH 		=> OUTPUT_WORD_WIDTH,       
		DIFFERENTIAL_SAMPLING 	=> DIFFERENTIAL_SAMPLING,
		DEBUG_MESSAGE_INCLUDED	=> DEBUG_MESSAGE_INCLUDED,
		NUMBER_OF_ADCS			=> NUMBER_OF_ADCS
	)
	port map
	(
		clk 					=> clk,
		reset_n 				=> reset_n,
		enable_measure			=> enable_measure,
		clk_division 			=> clk_division_spi,          --system clock cycles per 1/2 period of sclk
		sclk					=> sclk,
		mosi					=> mosi,
		miso					=> miso,
		ss_n					=> ss_n,
		init_done 				=> init_done_S,
		meas_done				=> meas_done_S,
		new_data				=> new_data,
		error					=> error_S,
		error_counter			=> error_counter_S,
		force_init				=> force_init_S,
		adc_selector			=> adc_selector_spi,

		data_echo_bipolar		=> data_echo_bipolar,
		data_echo_unipolar		=> data_echo_unipolar,
		
		all_differential_channels => all_differential_channels,
		all_single_ended_channels => all_single_ended_channels,

		data_ch0   => ch0,
		data_ch1   => ch1,
		data_ch2   => ch2,
		data_ch3   => ch3,
		data_ch4   => ch4,
		data_ch5   => ch5,
		data_ch6   => ch6,
		data_ch7   => ch7,
		data_ch8   => ch8,
		data_ch9   => ch9,
		data_ch10  => ch10,
		data_ch11  => ch11,
		data_ch12  => ch12,
		data_ch13  => ch13,
		data_ch14  => ch14,
		data_ch15  => ch15
	  
	  );
	  
	clk_division_spi <= clk_division_debug when(SIMULATION_DEBUG) else clk_division_AXI;
	adc_selector_spi <= adc_selector_debug when(SIMULATION_DEBUG) else adc_selector_AXI;

	init_done			<= init_done_S;
	meas_done			<= meas_done_S;
	error				<= error_S;
	-- User logic ends
	
	-- Instantiation of Axi Bus Interface S_AXI_Lite
	ADC_MAX11331_AXI_Lite_inst : ADC_MAX11331_AXI_Lite
		generic map (
			NUMBER_OF_ADCS      => NUMBER_OF_ADCS, 
			C_S_AXI_DATA_WIDTH	=> C_S_AXI_Lite_DATA_WIDTH,
			C_S_AXI_ADDR_WIDTH	=> C_S_AXI_Lite_ADDR_WIDTH
		)
		port map (
			init_done 				=> init_done_S,
			meas_done 				=> meas_done_S,
			error 					=> error_S,
			error_counter			=> error_counter_S,
			clk_division 			=> clk_division_AXI,          --system clock cycles per 1/2 period of sclk
			data_echo_bipolar_1		=> data_echo_bipolar_1_S,
			data_echo_bipolar_2		=> data_echo_bipolar_2_S,
			data_echo_bipolar_3		=> data_echo_bipolar_3_S,
			data_echo_bipolar_4		=> data_echo_bipolar_4_S,
			data_echo_bipolar_5		=> data_echo_bipolar_5_S,
			data_echo_bipolar_6		=> data_echo_bipolar_6_S,
			data_echo_unipolar_1	=> data_echo_unipolar_1_S,
			data_echo_unipolar_2	=> data_echo_unipolar_2_S,
			data_echo_unipolar_3	=> data_echo_unipolar_3_S,
			data_echo_unipolar_4	=> data_echo_unipolar_4_S,
			data_echo_unipolar_5	=> data_echo_unipolar_5_S,
			data_echo_unipolar_6	=> data_echo_unipolar_6_S,
			adc_selector			=> adc_selector_AXI,
			force_init				=> force_init_S,	
			S_AXI_ACLK	=> s_axi_lite_aclk,
			S_AXI_ARESETN	=> s_axi_lite_aresetn,
			S_AXI_AWADDR	=> s_axi_lite_awaddr,
			S_AXI_AWPROT	=> s_axi_lite_awprot,
			S_AXI_AWVALID	=> s_axi_lite_awvalid,
			S_AXI_AWREADY	=> s_axi_lite_awready,
			S_AXI_WDATA	=> s_axi_lite_wdata,
			S_AXI_WSTRB	=> s_axi_lite_wstrb,
			S_AXI_WVALID	=> s_axi_lite_wvalid,
			S_AXI_WREADY	=> s_axi_lite_wready,
			S_AXI_BRESP	=> s_axi_lite_bresp,
			S_AXI_BVALID	=> s_axi_lite_bvalid,
			S_AXI_BREADY	=> s_axi_lite_bready,
			S_AXI_ARADDR	=> s_axi_lite_araddr,
			S_AXI_ARPROT	=> s_axi_lite_arprot,
			S_AXI_ARVALID	=> s_axi_lite_arvalid,
			S_AXI_ARREADY	=> s_axi_lite_arready,
			S_AXI_RDATA	=> s_axi_lite_rdata,
			S_AXI_RRESP	=> s_axi_lite_rresp,
			S_AXI_RVALID	=> s_axi_lite_rvalid,
			S_AXI_RREADY	=> s_axi_lite_rready
		);
		
	-- assigning echo values to axi ports 
	data_echo_bipolar_1_S  <=  data_echo_bipolar(1);
	data_echo_bipolar_2_S  <=  data_echo_bipolar(2) when(NUMBER_OF_ADCS>1)  else data_echo_zero;
	data_echo_bipolar_3_S  <=  data_echo_bipolar(3) when(NUMBER_OF_ADCS>2)  else data_echo_zero;
	data_echo_bipolar_4_S  <=  data_echo_bipolar(4) when(NUMBER_OF_ADCS>3)  else data_echo_zero;
	data_echo_bipolar_5_S  <=  data_echo_bipolar(5) when(NUMBER_OF_ADCS>4)  else data_echo_zero;
	data_echo_bipolar_6_S  <=  data_echo_bipolar(6) when(NUMBER_OF_ADCS>5)  else data_echo_zero;
	data_echo_unipolar_1_S <= data_echo_unipolar(1);
	data_echo_unipolar_2_S <= data_echo_unipolar(2) when(NUMBER_OF_ADCS>1)  else data_echo_zero;
	data_echo_unipolar_3_S <= data_echo_unipolar(3) when(NUMBER_OF_ADCS>2)  else data_echo_zero;
	data_echo_unipolar_4_S <= data_echo_unipolar(4) when(NUMBER_OF_ADCS>3)  else data_echo_zero;
	data_echo_unipolar_5_S <= data_echo_unipolar(5) when(NUMBER_OF_ADCS>4)  else data_echo_zero;
	data_echo_unipolar_6_S <= data_echo_unipolar(6) when(NUMBER_OF_ADCS>5)  else data_echo_zero;

	end arch_imp;
