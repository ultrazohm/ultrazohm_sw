library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Resolver_Interface_v1_0 is
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
end Resolver_Interface_v1_0;

architecture arch_imp of Resolver_Interface_v1_0 is

	-- component declaration
	component Resolver_Interface_v1_0_S00_AXI is
		generic (
			SPI_clk_div         : integer   := 4;      -- SPI clock divider (12MHz)
			C_S_AXI_DATA_WIDTH	: integer	:= 32;
			C_S_AXI_ADDR_WIDTH	: integer	:= 4
		);
		port (
			SPI_MOSI                : OUT STD_LOGIC;   -- SPI master out (connect to chip)
			SPI_MISO                : IN  STD_LOGIC;   -- SPI master in (connect to chip)
			SPI_SCLK                : OUT STD_LOGIC;   -- SPI clock (connect to chip)
			SPI_SS                  : OUT STD_LOGIC;   -- SPI slave select (connect to chip)
			busy_m                  : OUT STD_LOGIC;   -- busy / data ready signal
			error_flag_m            : OUT STD_LOGIC;   -- error occurred, reset needed
			AD2S1210_n_reset        : OUT STD_LOGIC;   -- reset (connect to chip)
			AD2S1210_n_sample       : OUT STD_LOGIC;   -- sample start (connect to chip)
			AD2S1210_n_fsync        : OUT STD_LOGIC;   -- synchronization signal (connect to chip)
			AD2S1210_mode_A0        : OUT STD_LOGIC;   -- mode select 0 (connect to chip)
			AD2S1210_mode_A1        : OUT STD_LOGIC;   -- mode select 1 (connect to chip)
			sample_trigger          : IN STD_LOGIC;   -- Trigger input from PL  sample_trigger          : IN STD_LOGIC;   -- Trigger input from PL
            position_out_m          : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  
            velocity_out_m          : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  
            valid_m                 : OUT STD_LOGIC;   -- data at output are valid
  
			S_AXI_ACLK		: in std_logic;
			S_AXI_ARESETN	: in std_logic;
			S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
			S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
			S_AXI_AWVALID	: in std_logic;
			S_AXI_AWREADY	: out std_logic;
			S_AXI_WDATA		: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
			S_AXI_WSTRB		: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
			S_AXI_WVALID	: in std_logic;
			S_AXI_WREADY	: out std_logic;
			S_AXI_BRESP		: out std_logic_vector(1 downto 0);
			S_AXI_BVALID	: out std_logic;
			S_AXI_BREADY	: in std_logic;
			S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
			S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
			S_AXI_ARVALID	: in std_logic;
			S_AXI_ARREADY	: out std_logic;
			S_AXI_RDATA		: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
			S_AXI_RRESP		: out std_logic_vector(1 downto 0);
			S_AXI_RVALID	: out std_logic;
			S_AXI_RREADY	: in std_logic
		);
	end component Resolver_Interface_v1_0_S00_AXI;

begin

-- Instantiation of Axi Bus Interface S00_AXI
Resolver_Interface_v1_0_S00_AXI_inst : Resolver_Interface_v1_0_S00_AXI
	generic map (
	    SPI_clk_div         => SPI_clk_div,
		C_S_AXI_DATA_WIDTH	=> C_S00_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S00_AXI_ADDR_WIDTH
	)
	port map (
        SPI_MOSI            => SPI_MOSI,
		SPI_MISO            => SPI_MISO,
		SPI_SCLK            => SPI_SCLK,
		SPI_SS              => SPI_SS,
		busy_m              => busy,
		error_flag_m        => error,
        AD2S1210_n_reset    => AD2S1210_n_reset,
        AD2S1210_n_sample   => AD2S1210_n_sample,
        AD2S1210_n_fsync    => AD2S1210_n_fsync,
        AD2S1210_mode_A0    => AD2S1210_mode_A0,
        AD2S1210_mode_A1    => AD2S1210_mode_A1,
		sample_trigger      => sample_trigger,
        position_out_m  => position_out_m, 
        velocity_out_m  => velocity_out_m,
        valid_m         => valid_m, 
           
		S_AXI_ACLK		=> s00_axi_aclk,
		S_AXI_ARESETN	=> s00_axi_aresetn,
		S_AXI_AWADDR	=> s00_axi_awaddr,
		S_AXI_AWPROT	=> s00_axi_awprot,
		S_AXI_AWVALID	=> s00_axi_awvalid,
		S_AXI_AWREADY	=> s00_axi_awready,
		S_AXI_WDATA		=> s00_axi_wdata,
		S_AXI_WSTRB		=> s00_axi_wstrb,
		S_AXI_WVALID	=> s00_axi_wvalid,
		S_AXI_WREADY	=> s00_axi_wready,
		S_AXI_BRESP		=> s00_axi_bresp,
		S_AXI_BVALID	=> s00_axi_bvalid,
		S_AXI_BREADY	=> s00_axi_bready,
		S_AXI_ARADDR	=> s00_axi_araddr,
		S_AXI_ARPROT	=> s00_axi_arprot,
		S_AXI_ARVALID	=> s00_axi_arvalid,
		S_AXI_ARREADY	=> s00_axi_arready,
		S_AXI_RDATA		=> s00_axi_rdata,
		S_AXI_RRESP		=> s00_axi_rresp,
		S_AXI_RVALID	=> s00_axi_rvalid,
		S_AXI_RREADY	=> s00_axi_rready
	);

	-- Add user logic here

	-- User logic ends

end arch_imp;
