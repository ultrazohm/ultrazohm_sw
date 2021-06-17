library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ADC_MAX11331_AXI_v3_0 is
	generic (
		-- Users to add parameters here
		clk_div 			: INTEGER := 3;                   -- System clock cycles per 1/2 period of sclk
		OUTPUT_WORD_WIDTH 	: INTEGER := 12;                  -- Use 12 for normal operation. Use 16 for debug.
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
		enable_measure 				        : in STD_LOGIC;
		sclk 								: out STD_LOGIC;
		mosi 								: out STD_LOGIC;
		miso 								: in STD_LOGIC_VECTOR (5 downto 0);
		ss_n 								: out STD_LOGIC;
		init_done 						: out STD_LOGIC;
		meas_done 						: out STD_LOGIC;
		new_data 						: out STD_LOGIC;
		error 							: out STD_LOGIC;
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
        data_board_2_input_6_ch4    : out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
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
end ADC_MAX11331_AXI_v3_0;

architecture arch_imp of ADC_MAX11331_AXI_v3_0 is

	-- component declaration
	component ADC_MAX11331_AXI_v3_0_S_AXI_Lite is
		generic (
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
		adc_selector				: out STD_LOGIC_VECTOR (6 downto 1);	
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
	end component ADC_MAX11331_AXI_v3_0_S_AXI_Lite;

	component Slow_ADC_Memory_main is
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
		force_init 					: in STD_LOGIC;		
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
	end component Slow_ADC_Memory_main;
	
	signal	meas_done_S				:	STD_LOGIC := '0';
	signal	init_done_S				:	STD_LOGIC := '0';
	signal	error_S					:	STD_LOGIC := '0';
	signal	error_counter_S			:	STD_LOGIC_VECTOR (31 downto 0) := (others=>'0'); 
	signal	adc_selector_S			:	STD_LOGIC_VECTOR (6 downto 1) := (others=>'0'); 
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
	signal	clk_division_S			:	STD_LOGIC_VECTOR (3 downto 0) := (others=>'0'); 
	
begin

-- Instantiation of Axi Bus Interface S_AXI_Lite
ADC_MAX11331_AXI_v3_0_S_AXI_Lite_inst : ADC_MAX11331_AXI_v3_0_S_AXI_Lite
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S_AXI_Lite_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S_AXI_Lite_ADDR_WIDTH
	)
	port map (
		init_done 				=> init_done_S,
		meas_done 				=> meas_done_S,
		error 					=> error_S,
		error_counter			=> error_counter_S,
		clk_division 			=> clk_division_S,          --system clock cycles per 1/2 period of sclk
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
		adc_selector			=> adc_selector_S,
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

	-- Add user logic here
-- Instantiation of max11331 driver	
Slow_ADC_Memory_main_inst : Slow_ADC_Memory_main
	generic map
	(
		clk_div 			=> clk_div,                 -- System clock cycles per 1/2 period of sclk
		OUTPUT_WORD_WIDTH 	=> OUTPUT_WORD_WIDTH       -- Use 12 for normal operation. Use 16 for debug.
	)
	port map
	(
		clk 						=> clk,
		reset_n 					=> reset_n,
		enable_measure				=> enable_measure,
		clk_division 				=> clk_division_S,          --system clock cycles per 1/2 period of sclk		
		sclk						=> sclk,
		mosi						=> mosi,
		miso						=> miso,
		ss_n						=> ss_n,
		init_done 					=> init_done_S,
		meas_done					=> meas_done_S,
		new_data					=> new_data,
		error						=> error_S,
		error_counter				=> error_counter_S,
		force_init				=> force_init_S,
		adc_selector			=> adc_selector_S,
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
		data_board_1_input_1_ch1	=> data_board_1_input_1_ch1,
		data_board_1_input_1_ch2 	=> data_board_1_input_1_ch2,
		data_board_1_input_1_ch3 	=> data_board_1_input_1_ch3,
		data_board_1_input_1_ch4 	=> data_board_1_input_1_ch4,
		data_board_1_input_2_ch1	=> data_board_1_input_2_ch1,
		data_board_1_input_2_ch2 	=> data_board_1_input_2_ch2,
		data_board_1_input_2_ch3 	=> data_board_1_input_2_ch3,
		data_board_1_input_2_ch4 	=> data_board_1_input_2_ch4,
		data_board_1_input_3_ch1 	=> data_board_1_input_3_ch1,
		data_board_1_input_3_ch2 	=> data_board_1_input_3_ch2,
		data_board_1_input_3_ch3 	=> data_board_1_input_3_ch3,
		data_board_1_input_3_ch4 	=> data_board_1_input_3_ch4,
		data_board_1_input_4_ch1 	=> data_board_1_input_4_ch1,
		data_board_1_input_4_ch2 	=> data_board_1_input_4_ch2,
		data_board_1_input_4_ch3 	=> data_board_1_input_4_ch3,
		data_board_1_input_4_ch4 	=> data_board_1_input_4_ch4,
		data_board_1_input_5_ch1 	=> data_board_1_input_5_ch1,
		data_board_1_input_5_ch2 	=> data_board_1_input_5_ch2,
		data_board_1_input_5_ch3 	=> data_board_1_input_5_ch3,
		data_board_1_input_5_ch4 	=> data_board_1_input_5_ch4,
		data_board_1_input_6_ch1 	=> data_board_1_input_6_ch1,
		data_board_1_input_6_ch2 	=> data_board_1_input_6_ch2,
		data_board_1_input_6_ch3 	=> data_board_1_input_6_ch3,
		data_board_1_input_6_ch4 	=> data_board_1_input_6_ch4,

        data_board_2_input_1_ch1	=> data_board_2_input_1_ch1,
        data_board_2_input_1_ch2	=> data_board_2_input_1_ch2,
        data_board_2_input_1_ch3	=> data_board_2_input_1_ch3,
        data_board_2_input_1_ch4	=> data_board_2_input_1_ch4,
        data_board_2_input_2_ch1	=> data_board_2_input_2_ch1,
        data_board_2_input_2_ch2	=> data_board_2_input_2_ch2,
        data_board_2_input_2_ch3	=> data_board_2_input_2_ch3,
        data_board_2_input_2_ch4	=> data_board_2_input_2_ch4,
        data_board_2_input_3_ch1	=> data_board_2_input_3_ch1,
        data_board_2_input_3_ch2	=> data_board_2_input_3_ch2,
        data_board_2_input_3_ch3	=> data_board_2_input_3_ch3,
        data_board_2_input_3_ch4	=> data_board_2_input_3_ch4,
        data_board_2_input_4_ch1	=> data_board_2_input_4_ch1,
        data_board_2_input_4_ch2	=> data_board_2_input_4_ch2,
        data_board_2_input_4_ch3	=> data_board_2_input_4_ch3,
        data_board_2_input_4_ch4	=> data_board_2_input_4_ch4,
        data_board_2_input_5_ch1	=> data_board_2_input_5_ch1,
        data_board_2_input_5_ch2	=> data_board_2_input_5_ch2,
        data_board_2_input_5_ch3	=> data_board_2_input_5_ch3,
        data_board_2_input_5_ch4	=> data_board_2_input_5_ch4,
        data_board_2_input_6_ch1	=> data_board_2_input_6_ch1,
        data_board_2_input_6_ch2	=> data_board_2_input_6_ch2,
        data_board_2_input_6_ch3	=> data_board_2_input_6_ch3,
        data_board_2_input_6_ch4	=> data_board_2_input_6_ch4
	);


	init_done			<= init_done_S;
	meas_done			<= meas_done_S;
	error				<= error_S;
	-- User logic ends

end arch_imp;
