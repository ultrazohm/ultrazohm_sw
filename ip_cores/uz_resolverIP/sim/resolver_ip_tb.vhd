
library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity resolver_ip_tb is
end;

architecture bench of resolver_ip_tb is

  component Resolver_Interface_v1_0 is
	generic (
		-- Users to add parameters here
        SPI_clk_div			: INTEGER	:= 4;      -- SPI clock divider (12MHz)
		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 4
	);
	port (
		-- Users to add ports here

        SPI_MOSI				: OUT STD_LOGIC;   -- SPI master out (connect to chip)
		SPI_MISO				: IN  STD_LOGIC;   -- SPI master in (connect to chip)
		SPI_SCLK				: OUT STD_LOGIC;   -- SPI clock (connect to chip)
		SPI_SS					: OUT STD_LOGIC;   -- SPI slave select (connect to chip)
        busy	                : OUT STD_LOGIC;   -- busy / data ready signal
		error                   : OUT STD_LOGIC;   -- error occurred, reset needed
        AD2S1210_n_reset        : OUT STD_LOGIC;   -- reset (connect to chip)
        AD2S1210_n_sample       : OUT STD_LOGIC;   -- sample start (connect to chip)
        AD2S1210_n_fsync        : OUT STD_LOGIC;   -- synchronization signal (connect to chip)
        AD2S1210_mode_A0        : OUT STD_LOGIC;   -- mode select 0 (connect to chip)
        AD2S1210_mode_A1        : OUT STD_LOGIC;   -- mode select 1 (connect to chip)
        sample_trigger          : IN STD_LOGIC;   -- Trigger input from PL
        position_out_m          : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  
        velocity_out_m          : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  
        valid_m                 : OUT STD_LOGIC;   -- data at output are valid
  
		-- User ports ends
		-- Do not modify the ports beyond this line


		-- Ports of Axi Slave Bus Interface S00_AXI
		s00_axi_aclk	: in std_logic;
		s00_axi_aresetn	: in std_logic;
		s00_axi_awaddr	: in std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		s00_axi_awprot	: in std_logic_vector(2 downto 0);
		s00_axi_awvalid	: in std_logic;
		s00_axi_awready	: out std_logic;
		s00_axi_wdata	: in std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		s00_axi_wstrb	: in std_logic_vector((C_S00_AXI_DATA_WIDTH/8)-1 downto 0);
		s00_axi_wvalid	: in std_logic;
		s00_axi_wready	: out std_logic;
		s00_axi_bresp	: out std_logic_vector(1 downto 0);
		s00_axi_bvalid	: out std_logic;
		s00_axi_bready	: in std_logic;
		s00_axi_araddr	: in std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		s00_axi_arprot	: in std_logic_vector(2 downto 0);
		s00_axi_arvalid	: in std_logic;
		s00_axi_arready	: out std_logic;
		s00_axi_rdata	: out std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		s00_axi_rresp	: out std_logic_vector(1 downto 0);
		s00_axi_rvalid	: out std_logic;
		s00_axi_rready	: in std_logic
	);
end component;
	

  constant C_S_AXI_Lite_ADDR_WIDTH : integer := 6;
  constant C_S_AXI_Lite_DATA_WIDTH : integer := 32;
  
signal     SPI_MOSI				:  STD_LOGIC;   -- SPI master out (connect to chip)
signal		SPI_MISO				:  STD_LOGIC;   -- SPI master in (connect to chip)
signal		SPI_SCLK				:  STD_LOGIC;   -- SPI clock (connect to chip)
signal		SPI_SS					   :  STD_LOGIC;   -- SPI slave select (connect to chip)
signal        busy	               :  STD_LOGIC;   -- busy / data ready signal
signal		error                   :  STD_LOGIC;   -- error occurred, reset needed
signal        AD2S1210_n_reset      :  STD_LOGIC;   -- reset (connect to chip)
signal        AD2S1210_n_sample     :  STD_LOGIC;   -- sample start (connect to chip)
signal        AD2S1210_n_fsync      :  STD_LOGIC;   -- synchronization signal (connect to chip)
signal        AD2S1210_mode_A0      :  STD_LOGIC;   -- mode select 0 (connect to chip)
signal        AD2S1210_mode_A1      :  STD_LOGIC;   -- mode select 1 (connect to chip)
signal        sample_trigger        : STD_LOGIC;   -- Trigger input from PL
signal        position_out_m        :  STD_LOGIC_VECTOR(15 DOWNTO 0);  
signal        velocity_out_m        :  STD_LOGIC_VECTOR(15 DOWNTO 0);  
signal        valid_m               :  STD_LOGIC;   -- data at output are valid
  

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
	CONSTANT MSG_INIT_2        : STD_LOGIC_VECTOR(15 downto 0) := "1001011111111000";	-- Bipolar register


begin

  -- Insert values for generic parameters !!
  uut: Resolver_Interface_v1_0 generic map (
                                           C_S00_AXI_DATA_WIDTH  => C_S_AXI_Lite_DATA_WIDTH,
                                           C_S00_AXI_ADDR_WIDTH  => C_S_AXI_Lite_ADDR_WIDTH 
                                           )
                                port map ( 
                                               SPI_MOSI			 => SPI_MOSI			,
                                               SPI_MISO			=>  SPI_MISO			,
                                               SPI_SCLK			=>  SPI_SCLK			,
                                               SPI_SS				 => SPI_SS				,
                                               busy	          => busy	            ,
                                               error            => error            , 
                                               AD2S1210_n_reset => AD2S1210_n_reset ,
                                               AD2S1210_n_sample=> AD2S1210_n_sample,
                                               AD2S1210_n_fsync => AD2S1210_n_fsync ,
                                               AD2S1210_mode_A0 => AD2S1210_mode_A0 ,
                                               AD2S1210_mode_A1 => AD2S1210_mode_A1 ,
                                               sample_trigger   => sample_trigger   ,
                                               position_out_m   => position_out_m   ,
                                               velocity_out_m   => velocity_out_m   ,
                                               valid_m          => valid_m          ,
                                           s00_axi_aclk         => s_axi_lite_aclk,
                                           s00_axi_aresetn      => s_axi_lite_aresetn,
                                           s00_axi_awaddr       => s_axi_lite_awaddr,
                                           s00_axi_awprot       => s_axi_lite_awprot,
                                           s00_axi_awvalid      => s_axi_lite_awvalid,
                                           s00_axi_awready      => s_axi_lite_awready,
                                           s00_axi_wdata        => s_axi_lite_wdata,
                                           s00_axi_wstrb        => s_axi_lite_wstrb,
                                           s00_axi_wvalid       => s_axi_lite_wvalid,
                                           s00_axi_wready       => s_axi_lite_wready,
                                           s00_axi_bresp        => s_axi_lite_bresp,
                                           s00_axi_bvalid       => s_axi_lite_bvalid,
                                           s00_axi_bready       => s_axi_lite_bready,
                                           s00_axi_araddr       => s_axi_lite_araddr,
                                           s00_axi_arprot       => s_axi_lite_arprot,
                                           s00_axi_arvalid      => s_axi_lite_arvalid,
                                           s00_axi_arready      => s_axi_lite_arready,
                                           s00_axi_rdata        => s_axi_lite_rdata,
                                           s00_axi_rresp        => s_axi_lite_rresp,
                                           s00_axi_rvalid       => s_axi_lite_rvalid,
                                           s00_axi_rready       => s_axi_lite_rready );

  stimulus: process
  begin
  
    -- Put initialisation code here
	stop_the_clock <= false;
	s_axi_lite_aresetn <= '0'; -- avoid initial reset to avoid interference with axi interface
    wait for 200 ns;
    s_axi_lite_aresetn <= '1';
	
    wait;
  end process;
  
  
	miso1: process
	variable count_miso			: integer;
	begin
		wait until SPI_SS = '0';	
		for count_miso in 0 to 15 loop
			wait until SPI_SCLK = '0';
			SPI_MISO <= '0';
		end loop;
		
		wait until SPI_SS = '0';	
		for count_miso in 0 to 15 loop
			wait until SPI_SCLK = '0';
			SPI_MISO <= '0';
		end loop;

		wait until SPI_SS = '0';	
		for count_miso in 0 to 15 loop
			wait until SPI_SCLK = '0';
			SPI_MISO <= MSG_INIT_2(15-count_miso);
		end loop;		

		wait;
	end process;
	
	clocking: process
	begin
		while not stop_the_clock loop
		  s_axi_lite_aclk <= '1', '0' after clock_period / 2;
		  wait for clock_period;
		end loop;
		wait;
	end process;

	enable_meas_proc: process
	begin
		while not stop_the_clock loop
		  sample_trigger <= '1', '0' after clock_period;
		  wait for enable_measure_period;
		end loop;
		wait;
	end process;

end;