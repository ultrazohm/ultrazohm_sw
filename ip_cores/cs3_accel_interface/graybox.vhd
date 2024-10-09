library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity graybox is
   generic(
	C_CMD_AXI_DATA_WIDTH  : integer := 64;
	C_DATA_AXI_DATA_WIDTH : integer := 256;
	C_ANSWER_DELAY        : integer := 4096;
	C_DUMMY_LOGIC_FACTOR  : integer := 32
   );
   port(
	clk                : in  std_logic;
	rstn               : in  std_logic;

	start_irq          : in  std_logic;
	start_irq_ack      : out std_logic;
	finished_irq       : out std_logic;
	finished_irq_ack   : in  std_logic;

	-- config axi interface
	CMD_AXI_ACLK       : in  std_logic;
	CMD_AXI_ARESETN    : in  std_logic;
	CMD_AXI_AWADDR     : in  std_logic_vector(63 downto 0);
	CMD_AXI_AWPROT     : in  std_logic_vector(2 downto 0);
	CMD_AXI_AWVALID    : in  std_logic;
	CMD_AXI_AWREADY    : out std_logic;
	CMD_AXI_WDATA      : in  std_logic_vector(C_CMD_AXI_DATA_WIDTH-1 downto 0);
	CMD_AXI_WSTRB      : in  std_logic_vector((C_CMD_AXI_DATA_WIDTH/8)-1 downto 0);
	CMD_AXI_WVALID     : in  std_logic;
	CMD_AXI_WREADY     : out std_logic;
	CMD_AXI_BRESP      : out std_logic_vector(1 downto 0);
	CMD_AXI_BVALID     : out std_logic;
	CMD_AXI_BREADY     : in  std_logic;

	-- data axi interface
	DATA_AXI_ACLK      : in  std_logic;
	DATA_AXI_ARESETN   : in  std_logic;
	DATA_AXI00_AWADDR  : out std_logic_vector(63 downto 0);
	DATA_AXI00_AWLEN   : out std_logic_vector(7 downto 0);
	DATA_AXI00_AWSIZE  : out std_logic_vector(2 downto 0);
	DATA_AXI00_AWBURST : out std_logic_vector(1 downto 0);
	DATA_AXI00_AWLOCK  : out std_logic;
	DATA_AXI00_AWCACHE : out std_logic_vector(3 downto 0);
	DATA_AXI00_AWPROT  : out std_logic_vector(2 downto 0);
	DATA_AXI00_AWVALID : out std_logic;
	DATA_AXI00_AWREADY : in  std_logic;
	DATA_AXI00_WDATA   : out std_logic_vector(C_DATA_AXI_DATA_WIDTH-1 downto 0);
	DATA_AXI00_WSTRB   : out std_logic_vector(C_DATA_AXI_DATA_WIDTH/8-1 downto 0);
	DATA_AXI00_WLAST   : out std_logic;
	DATA_AXI00_WVALID  : out std_logic;
	DATA_AXI00_WREADY  : in  std_logic;
	DATA_AXI00_BRESP   : in  std_logic_vector(1 downto 0);
	DATA_AXI00_BVALID  : in  std_logic;
	DATA_AXI00_BREADY  : out std_logic;
	DATA_AXI00_ARADDR  : out std_logic_vector(63 downto 0);
	DATA_AXI00_ARLEN   : out std_logic_vector(7 downto 0);
	DATA_AXI00_ARSIZE  : out std_logic_vector(2 downto 0);
	DATA_AXI00_ARBURST : out std_logic_vector(1 downto 0);
	DATA_AXI00_ARLOCK  : out std_logic;
	DATA_AXI00_ARCACHE : out std_logic_vector(3 downto 0);
	DATA_AXI00_ARPROT  : out std_logic_vector(2 downto 0);
	DATA_AXI00_ARVALID : out std_logic;
	DATA_AXI00_ARREADY : in  std_logic;
	DATA_AXI00_RDATA   : in  std_logic_vector(C_DATA_AXI_DATA_WIDTH-1 downto 0);
	DATA_AXI00_RRESP   : in  std_logic_vector(1 downto 0);
	DATA_AXI00_RLAST   : in  std_logic;
	DATA_AXI00_RVALID  : in  std_logic;
	DATA_AXI00_RREADY  : out std_logic
);
end entity;

architecture behav of graybox is
	signal start_irq_reg    : std_logic;
	signal start_irq_delay  : std_logic_vector(C_ANSWER_DELAY-1 downto 0);
	signal finished_irq_reg : std_logic;
	signal tmp_val_0        : std_logic;
	signal tmp_val_1        : std_logic;

	type data_array_t is array(natural range <>) of std_logic_vector(C_DATA_AXI_DATA_WIDTH-1 downto 0);
	signal data_reg_0       : data_array_t(0 to C_DUMMY_LOGIC_FACTOR-1);
begin
	-- dummy logic to improve routablility at RP boundaries
	-- especially from partition pins to internal logic
	-- does not need to be functionally correct because it is never used

	dummy_irq: process(clk)
	begin
		if(rising_edge(clk)) then
			if(rstn = '0') then
				start_irq_reg    <= '0';
				start_irq_delay  <= (others => '0');
				finished_irq_reg <= '0';
			else
				start_irq_reg    <= start_irq;
				start_irq_delay  <= start_irq_delay(start_irq_delay'high-1 downto 0) & (start_irq_reg and (not start_irq));
				finished_irq_reg <= (finished_irq_reg and (not finished_irq_ack)) or start_irq_delay(start_irq_delay'high);
			end if;
		end if;
	end process;

	start_irq_ack <= start_irq_reg;
	finished_irq  <= finished_irq_reg;

	tmp_val_0 <= '1' when CMD_AXI_WSTRB = (CMD_AXI_WSTRB'range => '0') else '0';
	tmp_val_1 <= '1' when CMD_AXI_WDATA = (CMD_AXI_WDATA'range => '0') else '0';

	dummy_cmd: process(CMD_AXI_ACLK)
	begin
		if(rising_edge(CMD_AXI_ACLK)) then
			if(CMD_AXI_ARESETN = '0') then
				CMD_AXI_AWREADY <= '0';
				CMD_AXI_WREADY  <= '0';
				CMD_AXI_BVALID  <= '0';
			else
				CMD_AXI_AWREADY <= CMD_AXI_AWVALID and CMD_AXI_WVALID;
				CMD_AXI_WREADY  <= CMD_AXI_AWVALID and CMD_AXI_WVALID;
				CMD_AXI_BVALID  <= CMD_AXI_AWVALID and CMD_AXI_WVALID and CMD_AXI_BREADY;
			end if;

			if(CMD_AXI_AWADDR = (CMD_AXI_AWADDR'range => '0')) then
				CMD_AXI_BRESP(0) <= tmp_val_0;
			else
				CMD_AXI_BRESP(0) <= tmp_val_1;
			end if;
			CMD_AXI_BRESP(1) <= CMD_AXI_AWPROT(0) and CMD_AXI_AWPROT(1) and CMD_AXI_AWPROT(2);
		end if;
	end process;

	dummy_data0: process(DATA_AXI_ACLK)
	begin
		if(rising_edge(DATA_AXI_ACLK)) then
			if(DATA_AXI_ARESETN = '0') then
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

			for i in 0 to C_DATA_AXI_DATA_WIDTH/8-1 loop
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
end architecture;

