
library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;
-- use work.ADC_MAX11331_PKG.all;

entity ADC_max11331_tb is
end;

architecture bench of ADC_max11331_tb is

  component ADC_MAX11331_top
  	generic (
  		OUTPUT_WORD_WIDTH : INTEGER;            -- Use 12 for normal operation. Use 16 for debug.
		NUMBER_OF_ADCS	: INTEGER ;						-- How many MAX11331 ADCs are connected to this IP Core
		DIFFERENTIAL_SAMPLING : boolean ; 		-- true: 8 differential inputs, false: 16 single-ended inputs
		DEBUG_MESSAGE_INCLUDED: boolean ;			-- true: adds 4bit ADC register + 12 bit sample result
		SIMULATION_DEBUG : boolean ;			-- simulates AXI inputs during simulation
  		C_S_AXI_Lite_DATA_WIDTH	: integer;
  		C_S_AXI_Lite_ADDR_WIDTH	: integer
  	);
  	port (
  		clk 				: in  STD_LOGIC;
		reset_n 			: in  STD_LOGIC;
		enable_measure 		: in  STD_LOGIC;
		sclk 				: out STD_LOGIC;
		mosi 				: out STD_LOGIC;
		miso 				: in  STD_LOGIC_VECTOR (NUMBER_OF_ADCS-1 downto 0);
		ss_n 				: out STD_LOGIC;
		init_done 			: out STD_LOGIC;
		meas_done 			: out STD_LOGIC;
		new_data 			: out STD_LOGIC;
		error 				: out STD_LOGIC;
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
		
  		s_axi_lite_aclk		: in std_logic;
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
  end component;
	
  constant NUMBER_OF_ADCS : integer := 2; 
  constant OUTPUT_WORD_WIDTH : integer := 16;
  constant DIFFERENTIAL_SAMPLING  : boolean := true;
  constant DEBUG_MESSAGE_INCLUDED : boolean := false;
  constant SIMULATION_DEBUG		  : boolean := true;
  constant C_S_AXI_Lite_ADDR_WIDTH : integer := 6;
  constant C_S_AXI_Lite_DATA_WIDTH : integer := 32;
  
  signal clk: STD_LOGIC;
  signal reset_n: STD_LOGIC;
  signal enable_measure: STD_LOGIC;
  signal sclk: STD_LOGIC;
  signal mosi: STD_LOGIC;
  signal miso: STD_LOGIC_VECTOR (NUMBER_OF_ADCS-1 downto 0);
  signal ss_n: STD_LOGIC;
  signal init_done: STD_LOGIC;
  signal meas_done: STD_LOGIC;
  signal new_data: STD_LOGIC;
  signal error: STD_LOGIC;
  signal ch0: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch1: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch2: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch3: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch4: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch5: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch6: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch7: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch8: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch9: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch10: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch11: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch12: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch13: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch14: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal ch15: STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
  signal s_axi_lite_aclk: std_logic;
  signal s_axi_lite_aresetn: std_logic;
  signal s_axi_lite_awaddr: std_logic_vector(C_S_AXI_Lite_ADDR_WIDTH-1 downto 0);
  signal s_axi_lite_awprot: std_logic_vector(2 downto 0);
  signal s_axi_lite_awvalid: std_logic;
  signal s_axi_lite_awready: std_logic;
  signal s_axi_lite_wdata: std_logic_vector(C_S_AXI_Lite_DATA_WIDTH-1 downto 0);
  signal s_axi_lite_wstrb: std_logic_vector((C_S_AXI_Lite_DATA_WIDTH/8)-1 downto 0);
  signal s_axi_lite_wvalid: std_logic;
  signal s_axi_lite_wready: std_logic;
  signal s_axi_lite_bresp: std_logic_vector(1 downto 0);
  signal s_axi_lite_bvalid: std_logic;
  signal s_axi_lite_bready: std_logic;
  signal s_axi_lite_araddr: std_logic_vector(C_S_AXI_Lite_ADDR_WIDTH-1 downto 0);
  signal s_axi_lite_arprot: std_logic_vector(2 downto 0);
  signal s_axi_lite_arvalid: std_logic;
  signal s_axi_lite_arready: std_logic;
  signal s_axi_lite_rdata: std_logic_vector(C_S_AXI_Lite_DATA_WIDTH-1 downto 0);
  signal s_axi_lite_rresp: std_logic_vector(1 downto 0);
  signal s_axi_lite_rvalid: std_logic;
  signal s_axi_lite_rready: std_logic ;
  

  constant clock_period: time := 10 ns;
  constant enable_measure_period: time := 10 us;
  signal stop_the_clock: boolean;
  
CONSTANT MSG_INIT_1        : STD_LOGIC_VECTOR(15 downto 0) := "1000000000000100";	-- ADC Configuration: activate echo

SIGNAL MSG_INIT_2 	       : STD_LOGIC_VECTOR(15 downto 0) := (others => '0'); -- assigned DIFF or SING depending on acquisition mode
CONSTANT MSG_INIT_2_DIFF   : STD_LOGIC_VECTOR(15 downto 0) := "1001011111111000";	-- Bipolar register: 	1 bipolar fully-differential (Table 11)
CONSTANT MSG_INIT_2_SING   : STD_LOGIC_VECTOR(15 downto 0) := "1001000000000000";	-- Bipolar register: 	0 unipolar (= single-ended) (Table 11)

CONSTANT MSG_INIT_3        : STD_LOGIC_VECTOR(15 downto 0) := "1000100000000000";	-- Unipolar register
CONSTANT MSG_INIT_4        : STD_LOGIC_VECTOR(15 downto 0) := "1001111111111000";	-- Range register  

CONSTANT MSG_MEAS_0        : STD_LOGIC_VECTOR(15 downto 0) := X"0F2F";	-- Ch0 response
CONSTANT MSG_MEAS_2        : STD_LOGIC_VECTOR(15 downto 0) := X"2002";	-- Ch2 response
CONSTANT MSG_MEAS_4        : STD_LOGIC_VECTOR(15 downto 0) := X"4004";	-- Ch4 response
CONSTANT MSG_MEAS_6        : STD_LOGIC_VECTOR(15 downto 0) := X"6006";	-- Ch6 response
CONSTANT MSG_MEAS_8        : STD_LOGIC_VECTOR(15 downto 0) := X"8008";	-- Ch8 response
CONSTANT MSG_MEAS_10       : STD_LOGIC_VECTOR(15 downto 0) := X"A00A";	-- Ch10 response
CONSTANT MSG_MEAS_12       : STD_LOGIC_VECTOR(15 downto 0) := X"C00C";	-- Ch12 response
CONSTANT MSG_MEAS_14       : STD_LOGIC_VECTOR(15 downto 0) := X"E00E";	-- Ch14 response

CONSTANT MSG_MEAS_1        : STD_LOGIC_VECTOR(15 downto 0) := X"1001";	-- Ch1 response
CONSTANT MSG_MEAS_3        : STD_LOGIC_VECTOR(15 downto 0) := X"3003";	-- Ch3  response
CONSTANT MSG_MEAS_5        : STD_LOGIC_VECTOR(15 downto 0) := X"5005";	-- Ch5  response
CONSTANT MSG_MEAS_7        : STD_LOGIC_VECTOR(15 downto 0) := X"7007";	-- Ch7  response
CONSTANT MSG_MEAS_9        : STD_LOGIC_VECTOR(15 downto 0) := X"9009";	-- Ch9  response
CONSTANT MSG_MEAS_11       : STD_LOGIC_VECTOR(15 downto 0) := X"B00B";	-- Ch11 response
CONSTANT MSG_MEAS_13       : STD_LOGIC_VECTOR(15 downto 0) := X"D00D";	-- Ch13 response
CONSTANT MSG_MEAS_15       : STD_LOGIC_VECTOR(15 downto 0) := X"F00F";	-- Ch15 response


begin

  -- Insert values for generic parameters !!
  uut: ADC_MAX11331_top 	
  	generic map (	OUTPUT_WORD_WIDTH        => OUTPUT_WORD_WIDTH,
					NUMBER_OF_ADCS	       => NUMBER_OF_ADCS,
					DIFFERENTIAL_SAMPLING   => DIFFERENTIAL_SAMPLING, 
					DEBUG_MESSAGE_INCLUDED  => DEBUG_MESSAGE_INCLUDED,
					SIMULATION_DEBUG  	   => SIMULATION_DEBUG,
					C_S_AXI_Lite_DATA_WIDTH => C_S_AXI_Lite_DATA_WIDTH,
					C_S_AXI_Lite_ADDR_WIDTH => C_S_AXI_Lite_ADDR_WIDTH 
					)
	port map ( clk                      => clk,
				reset_n                  => reset_n,
				enable_measure           => enable_measure,
				sclk                     => sclk,
				mosi                     => mosi,
				miso                     => miso,
				ss_n                     => ss_n,
				init_done                => init_done,
				meas_done                => meas_done,
				new_data                 => new_data,
				error                    => error,
				ch0   => ch0, 
				ch1   => ch1, 
				ch2   => ch2, 
				ch3   => ch3, 
				ch4   => ch4, 
				ch5   => ch5, 
				ch6   => ch6, 
				ch7   => ch7, 
				ch8   => ch8, 
				ch9   => ch9, 
				ch10  => ch10, 
				ch11  => ch11, 
				ch12  => ch12, 
				ch13  => ch13, 
				ch14  => ch14, 
				ch15  => ch15, 

				s_axi_lite_aclk         => s_axi_lite_aclk,
				s_axi_lite_aresetn      => s_axi_lite_aresetn,
				s_axi_lite_awaddr       => s_axi_lite_awaddr,
				s_axi_lite_awprot       => s_axi_lite_awprot,
				s_axi_lite_awvalid      => s_axi_lite_awvalid,
				s_axi_lite_awready      => s_axi_lite_awready,
				s_axi_lite_wdata        => s_axi_lite_wdata,
				s_axi_lite_wstrb        => s_axi_lite_wstrb,
				s_axi_lite_wvalid       => s_axi_lite_wvalid,
				s_axi_lite_wready       => s_axi_lite_wready,
				s_axi_lite_bresp        => s_axi_lite_bresp,
				s_axi_lite_bvalid       => s_axi_lite_bvalid,
				s_axi_lite_bready       => s_axi_lite_bready,
				s_axi_lite_araddr       => s_axi_lite_araddr,
				s_axi_lite_arprot       => s_axi_lite_arprot,
				s_axi_lite_arvalid      => s_axi_lite_arvalid,
				s_axi_lite_arready      => s_axi_lite_arready,
				s_axi_lite_rdata        => s_axi_lite_rdata,
				s_axi_lite_rresp        => s_axi_lite_rresp,
				s_axi_lite_rvalid       => s_axi_lite_rvalid,
				s_axi_lite_rready       => s_axi_lite_rready );

MSG_INIT_2 <= MSG_INIT_2_DIFF when(DIFFERENTIAL_SAMPLING) else MSG_INIT_2_SING;

timulus: process
  begin

    -- Put initialisation code here
	stop_the_clock <= false;
	reset_n <= '0';
    wait for 20 ns;
    reset_n <= '1';
	
    wait;
  end process;
  
  
	miso1: process
	variable count_miso			: integer;
	begin
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			miso <= (others=>'0');
		end loop;
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			miso <= (others=>'0');
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
                miso(ii) <= MSG_INIT_2(15-count_miso);
			end loop;			
			  --  miso(0) <= MSG_INIT_2(15-count_miso);	
              --  miso(1) <= MSG_INIT_2(15-count_miso);
              --  miso(2) <= MSG_INIT_2(15-count_miso);
              --  miso(3) <= MSG_INIT_2(15-count_miso);
              --  miso(4) <= MSG_INIT_2(15-count_miso);
              --  miso(5) <= MSG_INIT_2(15-count_miso);             
		end loop;		
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				-- miso(ii) <= MSG_INIT_3(15-count_miso);					
				miso(ii) <= '1'; -- inject failure
			end loop;
		end loop;	
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_INIT_4(15-count_miso);					
			end loop;
		end loop;		
		
		--First Failure. Start Again
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			miso <= (others=>'0');
		end loop;
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			miso <= (others=>'0');
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_INIT_2(15-count_miso);					
			end loop;
		end loop;		
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_INIT_3(15-count_miso);					
			end loop;
		end loop;			

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_INIT_4(15-count_miso);					
			end loop;
		end loop;
		
		--Init done. Start measurements
		--wait until ss_n = '0';	
		wait until meas_done = '1';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= '1';--MSG_MEAS_0(15-count_miso);
			end loop;
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_0(15-count_miso);
			end loop;
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_2(15-count_miso);
			end loop;
		end loop;		
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_4(15-count_miso);
			end loop;
		end loop;		

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_6(15-count_miso);
			end loop;
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_8(15-count_miso);
			end loop;
		end loop;
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_10(15-count_miso);
			end loop;
		end loop;		

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_12(15-count_miso);
			end loop;
		end loop;
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_14(15-count_miso);
			end loop;
		end loop;

		--Single-ended data/new set
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_1(15-count_miso);
			end loop;
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_3(15-count_miso);
			end loop;
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_5(15-count_miso);
			end loop;
		end loop;		
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_7(15-count_miso);
			end loop;
		end loop;		

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_9(15-count_miso);
			end loop;
		end loop;

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_11(15-count_miso);
			end loop;
		end loop;
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_13(15-count_miso);
			end loop;
		end loop;		

		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_15(15-count_miso);
			end loop;
		end loop;
		
		wait until ss_n = '0';	
		for count_miso in 0 to 15 loop
			wait until sclk = '0';
			for ii in 0 to (NUMBER_OF_ADCS-1) loop
				miso(ii) <= MSG_MEAS_14(15-count_miso);
			end loop;
		end loop;
		
		wait;
	end process;
	
	clocking: process
	begin
		while not stop_the_clock loop
		  clk <= '1', '0' after clock_period / 2;
		  wait for clock_period;
		end loop;
		wait;
	end process;

	enable_meas_proc: process
	begin
		while not stop_the_clock loop
		  enable_measure <= '0', '1' after enable_measure_period/2;
		  wait for enable_measure_period;
		end loop;
		wait;
	end process;

end;