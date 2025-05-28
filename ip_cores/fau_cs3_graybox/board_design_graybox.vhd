library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity board_design_graybox is
  port (
    CMD_AXI_CLK : in STD_LOGIC;
    CMD_AXI_RSTN : in STD_LOGIC;
    CMD_AXI_araddr : in STD_LOGIC_VECTOR ( 63 downto 0 );
    CMD_AXI_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    CMD_AXI_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CMD_AXI_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    CMD_AXI_arlock : in STD_LOGIC;
    CMD_AXI_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    CMD_AXI_arqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CMD_AXI_arready : out STD_LOGIC;
    CMD_AXI_arregion : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CMD_AXI_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    CMD_AXI_arvalid : in STD_LOGIC;
    CMD_AXI_awaddr : in STD_LOGIC_VECTOR ( 63 downto 0 );
    CMD_AXI_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    CMD_AXI_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CMD_AXI_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    CMD_AXI_awlock : in STD_LOGIC;
    CMD_AXI_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    CMD_AXI_awqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CMD_AXI_awready : out STD_LOGIC;
    CMD_AXI_awregion : in STD_LOGIC_VECTOR ( 3 downto 0 );
    CMD_AXI_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    CMD_AXI_awvalid : in STD_LOGIC;
    CMD_AXI_bready : in STD_LOGIC;
    CMD_AXI_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CMD_AXI_bvalid : out STD_LOGIC;
    CMD_AXI_rdata : out STD_LOGIC_VECTOR ( 63 downto 0 );
    CMD_AXI_rlast : out STD_LOGIC;
    CMD_AXI_rready : in STD_LOGIC;
    CMD_AXI_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CMD_AXI_rvalid : out STD_LOGIC;
    CMD_AXI_wdata : in STD_LOGIC_VECTOR ( 63 downto 0 );
    CMD_AXI_wlast : in STD_LOGIC;
    CMD_AXI_wready : out STD_LOGIC;
    CMD_AXI_wstrb : in STD_LOGIC_VECTOR ( 7 downto 0 );
    CMD_AXI_wvalid : in STD_LOGIC;
    CORE_CLK : in STD_LOGIC;
    CORE_RSTN : in STD_LOGIC;
    DATA_AXI00_araddr : out STD_LOGIC_VECTOR ( 63 downto 0 );
    DATA_AXI00_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    DATA_AXI00_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    DATA_AXI00_arid : out STD_LOGIC_VECTOR ( 5 downto 0 );
    DATA_AXI00_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    DATA_AXI00_arlock : out STD_LOGIC;
    DATA_AXI00_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    DATA_AXI00_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    DATA_AXI00_arready : in STD_LOGIC;
    DATA_AXI00_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    DATA_AXI00_arvalid : out STD_LOGIC;
    DATA_AXI00_awaddr : out STD_LOGIC_VECTOR ( 63 downto 0 );
    DATA_AXI00_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    DATA_AXI00_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    DATA_AXI00_awid : out STD_LOGIC_VECTOR ( 5 downto 0 );
    DATA_AXI00_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    DATA_AXI00_awlock : out STD_LOGIC;
    DATA_AXI00_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    DATA_AXI00_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    DATA_AXI00_awready : in STD_LOGIC;
    DATA_AXI00_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    DATA_AXI00_awvalid : out STD_LOGIC;
    DATA_AXI00_bid : in STD_LOGIC_VECTOR ( 5 downto 0 );
    DATA_AXI00_bready : out STD_LOGIC;
    DATA_AXI00_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    DATA_AXI00_bvalid : in STD_LOGIC;
    DATA_AXI00_rdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    DATA_AXI00_rid : in STD_LOGIC_VECTOR ( 5 downto 0 );
    DATA_AXI00_rlast : in STD_LOGIC;
    DATA_AXI00_rready : out STD_LOGIC;
    DATA_AXI00_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    DATA_AXI00_rvalid : in STD_LOGIC;
    DATA_AXI00_wdata : out STD_LOGIC_VECTOR ( 127 downto 0 );
    DATA_AXI00_wlast : out STD_LOGIC;
    DATA_AXI00_wready : in STD_LOGIC;
    DATA_AXI00_wstrb : out STD_LOGIC_VECTOR ( 15 downto 0 );
    DATA_AXI00_wvalid : out STD_LOGIC;
    DATA_AXI_CLK : in STD_LOGIC;
    DATA_AXI_RSTN : in STD_LOGIC;
    HOST_PP_IRQ : out STD_LOGIC
  );
end board_design_graybox;

architecture STRUCTURE of board_design_graybox is
	signal tmp_val_0        : std_logic;
	signal tmp_val_1        : std_logic;

	type data_array_t is array(natural range <>) of std_logic_vector(127 downto 0);
	signal data_reg_0       : data_array_t(0 to 31);
begin
	-- dummy logic to improve routablility at RP boundaries
	-- especially from partition pins to internal logic
	-- does not need to be functionally correct because it is never used

	tmp_val_0 <= '1' when CMD_AXI_WSTRB = (CMD_AXI_WSTRB'range => '0') else '0';
	tmp_val_1 <= '1' when CMD_AXI_WDATA = (CMD_AXI_WDATA'range => '0') else '0';

	dummy_cmd: process(CMD_AXI_CLK)
	begin
		if(rising_edge(CMD_AXI_CLK)) then
			if(CMD_AXI_RSTN = '0') then
				CMD_AXI_AWREADY <= '0';
				CMD_AXI_WREADY  <= '0';
				CMD_AXI_BVALID  <= '0';
				CMD_AXI_ARREADY <= '0';
				CMD_AXI_RVALID  <= '0';
			else
				CMD_AXI_AWREADY <= CMD_AXI_AWVALID and CMD_AXI_WVALID;
				CMD_AXI_WREADY  <= CMD_AXI_AWVALID and CMD_AXI_WVALID;
				CMD_AXI_BVALID  <= CMD_AXI_AWVALID and CMD_AXI_WVALID and CMD_AXI_BREADY;

				CMD_AXI_ARREADY  <= CMD_AXI_ARVALID;
				CMD_AXI_RVALID   <= CMD_AXI_ARVALID and CMD_AXI_RREADY;
			end if;

			if(CMD_AXI_AWADDR = (CMD_AXI_AWADDR'range => '0')) then
				CMD_AXI_BRESP(0) <= tmp_val_0;
			else
				CMD_AXI_BRESP(0) <= tmp_val_1;
			end if;
			CMD_AXI_BRESP(1) <= CMD_AXI_AWPROT(0) and CMD_AXI_AWPROT(1) and CMD_AXI_AWPROT(2);

			if(CMD_AXI_ARADDR = (CMD_AXI_ARADDR'range => '0')) then
				CMD_AXI_RRESP(0) <= tmp_val_0;
			else
				CMD_AXI_RRESP(0) <= tmp_val_1;
			end if;
			CMD_AXI_RRESP(1) <= CMD_AXI_ARPROT(0) and CMD_AXI_ARPROT(1) and CMD_AXI_ARPROT(2);
		end if;
	end process;

	dummy_data0: process(DATA_AXI_CLK)
	begin
		if(rising_edge(DATA_AXI_CLK)) then
			if(DATA_AXI_RSTN = '0') then
				DATA_AXI00_AWVALID <= '0';
				DATA_AXI00_WLAST   <= '0';
				DATA_AXI00_WVALID  <= '0';
				DATA_AXI00_BREADY  <= '0';
				DATA_AXI00_ARVALID <= '0';
				DATA_AXI00_RREADY  <= '0';
			else
				DATA_AXI00_ARVALID <= DATA_AXI00_ARREADY;
				DATA_AXI00_AWVALID <= DATA_AXI00_AWREADY and DATA_AXI00_WREADY;
				DATA_AXI00_WVALID  <= DATA_AXI00_AWREADY and DATA_AXI00_WREADY;
				DATA_AXI00_WLAST   <= DATA_AXI00_AWREADY and DATA_AXI00_WREADY;
				DATA_AXI00_BREADY  <= DATA_AXI00_BVALID and DATA_AXI00_AWREADY and DATA_AXI00_WREADY;
				DATA_AXI00_RREADY  <= DATA_AXI00_RVALID and DATA_AXI00_RLAST;
			end if;

			DATA_AXI00_ARLOCK <= DATA_AXI00_RRESP(0) and DATA_AXI00_RRESP(1);
			DATA_AXI00_AWLOCK <= DATA_AXI00_BRESP(0) and DATA_AXI00_BRESP(1);

			DATA_AXI00_ARBURST <= DATA_AXI00_RRESP;
			DATA_AXI00_AWBURST <= DATA_AXI00_BRESP;

			DATA_AXI00_ARADDR <= std_logic_vector(resize(unsigned(DATA_AXI00_RDATA),DATA_AXI00_ARADDR'length));
			DATA_AXI00_AWADDR <= std_logic_vector(resize(unsigned(DATA_AXI00_RDATA),DATA_AXI00_AWADDR'length));

			data_reg_0(0) <= DATA_AXI00_RDATA;
			for i in 1 to data_reg_0'high loop
				data_reg_0(i) <= std_logic_vector(shift_left(unsigned(data_reg_0(i-1)),to_integer(unsigned(data_reg_0(0)(i downto i)))));
			end loop;
			DATA_AXI00_WDATA <= data_reg_0(data_reg_0'high);

			for i in 0 to 128/8-1 loop
				if(DATA_AXI00_RDATA((i+1)*8-1 downto i*8) = (7 downto 0 => '0')) then
					DATA_AXI00_WSTRB(i) <= '0';
				else
					DATA_AXI00_WSTRB(i) <= '1';
				end if;
			end loop;
		end if;
	end process;

	DATA_AXI00_AWLEN   <= (others => '0');
	DATA_AXI00_AWSIZE  <= (others => '0');
	DATA_AXI00_AWCACHE <= (others => '0');
	DATA_AXI00_AWPROT  <= (others => '0');
	DATA_AXI00_ARLEN   <= (others => '0');
	DATA_AXI00_ARSIZE  <= (others => '0');
	DATA_AXI00_ARCACHE <= (others => '0');
	DATA_AXI00_ARPROT  <= (others => '0');
end STRUCTURE;
