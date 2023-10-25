-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Tool Version Limit: 2019.12
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity MatrixMultiplication_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 9;
    C_S_AXI_DATA_WIDTH    : INTEGER := 32);
port (
    ACLK                  :in   STD_LOGIC;
    ARESET                :in   STD_LOGIC;
    ACLK_EN               :in   STD_LOGIC;
    AWADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    AWVALID               :in   STD_LOGIC;
    AWREADY               :out  STD_LOGIC;
    WDATA                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    WSTRB                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH/8-1 downto 0);
    WVALID                :in   STD_LOGIC;
    WREADY                :out  STD_LOGIC;
    BRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    BVALID                :out  STD_LOGIC;
    BREADY                :in   STD_LOGIC;
    ARADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    ARVALID               :in   STD_LOGIC;
    ARREADY               :out  STD_LOGIC;
    RDATA                 :out  STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    RRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    RVALID                :out  STD_LOGIC;
    RREADY                :in   STD_LOGIC;
    A_rows                :out  STD_LOGIC_VECTOR(63 downto 0);
    A_address0            :in   STD_LOGIC_VECTOR(2 downto 0);
    A_ce0                 :in   STD_LOGIC;
    A_q0                  :out  STD_LOGIC_VECTOR(31 downto 0);
    C_out_address0        :in   STD_LOGIC_VECTOR(2 downto 0);
    C_out_ce0             :in   STD_LOGIC;
    C_out_we0             :in   STD_LOGIC;
    C_out_d0              :in   STD_LOGIC_VECTOR(31 downto 0);
    C_out_q0              :out  STD_LOGIC_VECTOR(31 downto 0);
    B_rows                :out  STD_LOGIC_VECTOR(63 downto 0);
    B_columns             :out  STD_LOGIC_VECTOR(63 downto 0);
    trigger               :out  STD_LOGIC_VECTOR(0 downto 0);
    B_address0            :in   STD_LOGIC_VECTOR(4 downto 0);
    B_ce0                 :in   STD_LOGIC;
    B_q0                  :out  STD_LOGIC_VECTOR(31 downto 0);
    is_done_i             :out  STD_LOGIC_VECTOR(0 downto 0);
    is_done_o             :in   STD_LOGIC_VECTOR(0 downto 0);
    is_done_o_ap_vld      :in   STD_LOGIC
);
end entity MatrixMultiplication_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x000 : reserved
-- 0x004 : reserved
-- 0x008 : reserved
-- 0x00c : reserved
-- 0x010 : Data signal of A_rows
--         bit 31~0 - A_rows[31:0] (Read/Write)
-- 0x014 : Data signal of A_rows
--         bit 31~0 - A_rows[63:32] (Read/Write)
-- 0x018 : reserved
-- 0x060 : Data signal of B_rows
--         bit 31~0 - B_rows[31:0] (Read/Write)
-- 0x064 : Data signal of B_rows
--         bit 31~0 - B_rows[63:32] (Read/Write)
-- 0x068 : reserved
-- 0x06c : Data signal of B_columns
--         bit 31~0 - B_columns[31:0] (Read/Write)
-- 0x070 : Data signal of B_columns
--         bit 31~0 - B_columns[63:32] (Read/Write)
-- 0x074 : reserved
-- 0x078 : Data signal of trigger
--         bit 0  - trigger[0] (Read/Write)
--         others - reserved
-- 0x07c : reserved
-- 0x100 : Data signal of is_done_i
--         bit 0  - is_done_i[0] (Read/Write)
--         others - reserved
-- 0x104 : reserved
-- 0x108 : Data signal of is_done_o
--         bit 0  - is_done_o[0] (Read)
--         others - reserved
-- 0x10c : Control signal of is_done_o
--         bit 0  - is_done_o_ap_vld (Read/COR)
--         others - reserved
-- 0x020 ~
-- 0x03f : Memory 'A' (5 * 32b)
--         Word n : bit [31:0] - A[n]
-- 0x040 ~
-- 0x05f : Memory 'C_out' (5 * 32b)
--         Word n : bit [31:0] - C_out[n]
-- 0x080 ~
-- 0x0ff : Memory 'B' (25 * 32b)
--         Word n : bit [31:0] - B[n]
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of MatrixMultiplication_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_A_ROWS_DATA_0    : INTEGER := 16#010#;
    constant ADDR_A_ROWS_DATA_1    : INTEGER := 16#014#;
    constant ADDR_A_ROWS_CTRL      : INTEGER := 16#018#;
    constant ADDR_B_ROWS_DATA_0    : INTEGER := 16#060#;
    constant ADDR_B_ROWS_DATA_1    : INTEGER := 16#064#;
    constant ADDR_B_ROWS_CTRL      : INTEGER := 16#068#;
    constant ADDR_B_COLUMNS_DATA_0 : INTEGER := 16#06c#;
    constant ADDR_B_COLUMNS_DATA_1 : INTEGER := 16#070#;
    constant ADDR_B_COLUMNS_CTRL   : INTEGER := 16#074#;
    constant ADDR_TRIGGER_DATA_0   : INTEGER := 16#078#;
    constant ADDR_TRIGGER_CTRL     : INTEGER := 16#07c#;
    constant ADDR_IS_DONE_I_DATA_0 : INTEGER := 16#100#;
    constant ADDR_IS_DONE_I_CTRL   : INTEGER := 16#104#;
    constant ADDR_IS_DONE_O_DATA_0 : INTEGER := 16#108#;
    constant ADDR_IS_DONE_O_CTRL   : INTEGER := 16#10c#;
    constant ADDR_A_BASE           : INTEGER := 16#020#;
    constant ADDR_A_HIGH           : INTEGER := 16#03f#;
    constant ADDR_C_OUT_BASE       : INTEGER := 16#040#;
    constant ADDR_C_OUT_HIGH       : INTEGER := 16#05f#;
    constant ADDR_B_BASE           : INTEGER := 16#080#;
    constant ADDR_B_HIGH           : INTEGER := 16#0ff#;
    constant ADDR_BITS         : INTEGER := 9;

    signal waddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal wmask               : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal aw_hs               : STD_LOGIC;
    signal w_hs                : STD_LOGIC;
    signal rdata_data          : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal ar_hs               : STD_LOGIC;
    signal raddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal AWREADY_t           : STD_LOGIC;
    signal WREADY_t            : STD_LOGIC;
    signal ARREADY_t           : STD_LOGIC;
    signal RVALID_t            : STD_LOGIC;
    -- internal registers
    signal int_A_rows          : UNSIGNED(63 downto 0) := (others => '0');
    signal int_B_rows          : UNSIGNED(63 downto 0) := (others => '0');
    signal int_B_columns       : UNSIGNED(63 downto 0) := (others => '0');
    signal int_trigger         : UNSIGNED(0 downto 0) := (others => '0');
    signal int_is_done_i       : UNSIGNED(0 downto 0) := (others => '0');
    signal int_is_done_o_ap_vld : STD_LOGIC;
    signal int_is_done_o       : UNSIGNED(0 downto 0) := (others => '0');
    -- memory signals
    signal int_A_address0      : UNSIGNED(2 downto 0);
    signal int_A_ce0           : STD_LOGIC;
    signal int_A_q0            : UNSIGNED(31 downto 0);
    signal int_A_address1      : UNSIGNED(2 downto 0);
    signal int_A_ce1           : STD_LOGIC;
    signal int_A_we1           : STD_LOGIC;
    signal int_A_be1           : UNSIGNED(3 downto 0);
    signal int_A_d1            : UNSIGNED(31 downto 0);
    signal int_A_q1            : UNSIGNED(31 downto 0);
    signal int_A_read          : STD_LOGIC;
    signal int_A_write         : STD_LOGIC;
    signal int_C_out_address0  : UNSIGNED(2 downto 0);
    signal int_C_out_ce0       : STD_LOGIC;
    signal int_C_out_be0       : UNSIGNED(3 downto 0);
    signal int_C_out_d0        : UNSIGNED(31 downto 0);
    signal int_C_out_q0        : UNSIGNED(31 downto 0);
    signal int_C_out_address1  : UNSIGNED(2 downto 0);
    signal int_C_out_ce1       : STD_LOGIC;
    signal int_C_out_we1       : STD_LOGIC;
    signal int_C_out_be1       : UNSIGNED(3 downto 0);
    signal int_C_out_d1        : UNSIGNED(31 downto 0);
    signal int_C_out_q1        : UNSIGNED(31 downto 0);
    signal int_C_out_read      : STD_LOGIC;
    signal int_C_out_write     : STD_LOGIC;
    signal int_B_address0      : UNSIGNED(4 downto 0);
    signal int_B_ce0           : STD_LOGIC;
    signal int_B_q0            : UNSIGNED(31 downto 0);
    signal int_B_address1      : UNSIGNED(4 downto 0);
    signal int_B_ce1           : STD_LOGIC;
    signal int_B_we1           : STD_LOGIC;
    signal int_B_be1           : UNSIGNED(3 downto 0);
    signal int_B_d1            : UNSIGNED(31 downto 0);
    signal int_B_q1            : UNSIGNED(31 downto 0);
    signal int_B_read          : STD_LOGIC;
    signal int_B_write         : STD_LOGIC;

    component MatrixMultiplication_control_s_axi_ram is
        generic (
            MEM_STYLE : STRING :="auto";
            MEM_TYPE  : STRING :="S2P";
            BYTES   : INTEGER :=4;
            DEPTH   : INTEGER :=256;
            AWIDTH  : INTEGER :=8);
        port (
            clk0    : in  STD_LOGIC;
            address0: in  UNSIGNED(AWIDTH-1 downto 0);
            ce0     : in  STD_LOGIC;
            we0     : in  UNSIGNED(BYTES-1 downto 0);
            d0      : in  UNSIGNED(BYTES*8-1 downto 0);
            q0      : out UNSIGNED(BYTES*8-1 downto 0);
            clk1    : in  STD_LOGIC;
            address1: in  UNSIGNED(AWIDTH-1 downto 0);
            ce1     : in  STD_LOGIC;
            we1     : in  UNSIGNED(BYTES-1 downto 0);
            d1      : in  UNSIGNED(BYTES*8-1 downto 0);
            q1      : out UNSIGNED(BYTES*8-1 downto 0));
    end component MatrixMultiplication_control_s_axi_ram;

    function log2 (x : INTEGER) return INTEGER is
        variable n, m : INTEGER;
    begin
        n := 1;
        m := 2;
        while m < x loop
            n := n + 1;
            m := m * 2;
        end loop;
        return n;
    end function log2;

begin
-- ----------------------- Instantiation------------------
-- int_A
int_A : MatrixMultiplication_control_s_axi_ram
generic map (
     MEM_STYLE => "auto",
     MEM_TYPE  => "2P",
     BYTES     => 4,
     DEPTH     => 5,
     AWIDTH    => log2(5))
port map (
     clk0      => ACLK,
     address0  => int_A_address0,
     ce0       => int_A_ce0,
     we0       => (others=>'0'),
     d0        => (others=>'0'),
     q0        => int_A_q0,
     clk1      => ACLK,
     address1  => int_A_address1,
     ce1       => int_A_ce1,
     we1       => int_A_be1,
     d1        => int_A_d1,
     q1        => int_A_q1);
-- int_C_out
int_C_out : MatrixMultiplication_control_s_axi_ram
generic map (
     MEM_STYLE => "auto",
     MEM_TYPE  => "T2P",
     BYTES     => 4,
     DEPTH     => 5,
     AWIDTH    => log2(5))
port map (
     clk0      => ACLK,
     address0  => int_C_out_address0,
     ce0       => int_C_out_ce0,
     we0       => int_C_out_be0,
     d0        => int_C_out_d0,
     q0        => int_C_out_q0,
     clk1      => ACLK,
     address1  => int_C_out_address1,
     ce1       => int_C_out_ce1,
     we1       => int_C_out_be1,
     d1        => int_C_out_d1,
     q1        => int_C_out_q1);
-- int_B
int_B : MatrixMultiplication_control_s_axi_ram
generic map (
     MEM_STYLE => "auto",
     MEM_TYPE  => "2P",
     BYTES     => 4,
     DEPTH     => 25,
     AWIDTH    => log2(25))
port map (
     clk0      => ACLK,
     address0  => int_B_address0,
     ce0       => int_B_ce0,
     we0       => (others=>'0'),
     d0        => (others=>'0'),
     q0        => int_B_q0,
     clk1      => ACLK,
     address1  => int_B_address1,
     ce1       => int_B_ce1,
     we1       => int_B_be1,
     d1        => int_B_d1,
     q1        => int_B_q1);


-- ----------------------- AXI WRITE ---------------------
    AWREADY_t <=  '1' when wstate = wridle else '0';
    AWREADY   <=  AWREADY_t;
    WREADY_t  <=  '1' when wstate = wrdata and ar_hs = '0' else '0';
    WREADY    <=  WREADY_t;
    BRESP     <=  "00";  -- OKAY
    BVALID    <=  '1' when wstate = wrresp else '0';
    wmask     <=  (31 downto 24 => WSTRB(3), 23 downto 16 => WSTRB(2), 15 downto 8 => WSTRB(1), 7 downto 0 => WSTRB(0));
    aw_hs     <=  AWVALID and AWREADY_t;
    w_hs      <=  WVALID and WREADY_t;

    -- write FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                wstate <= wrreset;
            elsif (ACLK_EN = '1') then
                wstate <= wnext;
            end if;
        end if;
    end process;

    process (wstate, AWVALID, w_hs, BREADY)
    begin
        case (wstate) is
        when wridle =>
            if (AWVALID = '1') then
                wnext <= wrdata;
            else
                wnext <= wridle;
            end if;
        when wrdata =>
            if (w_hs = '1') then
                wnext <= wrresp;
            else
                wnext <= wrdata;
            end if;
        when wrresp =>
            if (BREADY = '1') then
                wnext <= wridle;
            else
                wnext <= wrresp;
            end if;
        when others =>
            wnext <= wridle;
        end case;
    end process;

    waddr_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (aw_hs = '1') then
                    waddr <= UNSIGNED(AWADDR(ADDR_BITS-1 downto 0));
                end if;
            end if;
        end if;
    end process;

-- ----------------------- AXI READ ----------------------
    ARREADY_t <= '1' when (rstate = rdidle) else '0';
    ARREADY <= ARREADY_t;
    RDATA   <= STD_LOGIC_VECTOR(rdata_data);
    RRESP   <= "00";  -- OKAY
    RVALID_t  <= '1' when (rstate = rddata) and (int_A_read = '0') and (int_C_out_read = '0') and (int_B_read = '0') else '0';
    RVALID    <= RVALID_t;
    ar_hs   <= ARVALID and ARREADY_t;
    raddr   <= UNSIGNED(ARADDR(ADDR_BITS-1 downto 0));

    -- read FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                rstate <= rdreset;
            elsif (ACLK_EN = '1') then
                rstate <= rnext;
            end if;
        end if;
    end process;

    process (rstate, ARVALID, RREADY, RVALID_t)
    begin
        case (rstate) is
        when rdidle =>
            if (ARVALID = '1') then
                rnext <= rddata;
            else
                rnext <= rdidle;
            end if;
        when rddata =>
            if (RREADY = '1' and RVALID_t = '1') then
                rnext <= rdidle;
            else
                rnext <= rddata;
            end if;
        when others =>
            rnext <= rdidle;
        end case;
    end process;

    rdata_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (ar_hs = '1') then
                    rdata_data <= (others => '0');
                    case (TO_INTEGER(raddr)) is
                    when ADDR_A_ROWS_DATA_0 =>
                        rdata_data <= RESIZE(int_A_rows(31 downto 0), 32);
                    when ADDR_A_ROWS_DATA_1 =>
                        rdata_data <= RESIZE(int_A_rows(63 downto 32), 32);
                    when ADDR_B_ROWS_DATA_0 =>
                        rdata_data <= RESIZE(int_B_rows(31 downto 0), 32);
                    when ADDR_B_ROWS_DATA_1 =>
                        rdata_data <= RESIZE(int_B_rows(63 downto 32), 32);
                    when ADDR_B_COLUMNS_DATA_0 =>
                        rdata_data <= RESIZE(int_B_columns(31 downto 0), 32);
                    when ADDR_B_COLUMNS_DATA_1 =>
                        rdata_data <= RESIZE(int_B_columns(63 downto 32), 32);
                    when ADDR_TRIGGER_DATA_0 =>
                        rdata_data <= RESIZE(int_trigger(0 downto 0), 32);
                    when ADDR_IS_DONE_I_DATA_0 =>
                        rdata_data <= RESIZE(int_is_done_i(0 downto 0), 32);
                    when ADDR_IS_DONE_O_DATA_0 =>
                        rdata_data <= RESIZE(int_is_done_o(0 downto 0), 32);
                    when ADDR_IS_DONE_O_CTRL =>
                        rdata_data(0) <= int_is_done_o_ap_vld;
                    when others =>
                        NULL;
                    end case;
                elsif (int_A_read = '1') then
                    rdata_data <= int_A_q1;
                elsif (int_C_out_read = '1') then
                    rdata_data <= int_C_out_q1;
                elsif (int_B_read = '1') then
                    rdata_data <= int_B_q1;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    A_rows               <= STD_LOGIC_VECTOR(int_A_rows);
    B_rows               <= STD_LOGIC_VECTOR(int_B_rows);
    B_columns            <= STD_LOGIC_VECTOR(int_B_columns);
    trigger              <= STD_LOGIC_VECTOR(int_trigger);
    is_done_i            <= STD_LOGIC_VECTOR(int_is_done_i);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_A_ROWS_DATA_0) then
                    int_A_rows(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_A_rows(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_A_ROWS_DATA_1) then
                    int_A_rows(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_A_rows(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B_ROWS_DATA_0) then
                    int_B_rows(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B_rows(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B_ROWS_DATA_1) then
                    int_B_rows(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B_rows(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B_COLUMNS_DATA_0) then
                    int_B_columns(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B_columns(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B_COLUMNS_DATA_1) then
                    int_B_columns(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B_columns(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_TRIGGER_DATA_0) then
                    int_trigger(0 downto 0) <= (UNSIGNED(WDATA(0 downto 0)) and wmask(0 downto 0)) or ((not wmask(0 downto 0)) and int_trigger(0 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IS_DONE_I_DATA_0) then
                    int_is_done_i(0 downto 0) <= (UNSIGNED(WDATA(0 downto 0)) and wmask(0 downto 0)) or ((not wmask(0 downto 0)) and int_is_done_i(0 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_is_done_o <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (is_done_o_ap_vld = '1') then
                    int_is_done_o <= UNSIGNED(is_done_o);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_is_done_o_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (is_done_o_ap_vld = '1') then
                    int_is_done_o_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_IS_DONE_O_CTRL) then
                    int_is_done_o_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------
    -- A
    int_A_address0       <= UNSIGNED(A_address0);
    int_A_ce0            <= A_ce0;
    A_q0                 <= STD_LOGIC_VECTOR(RESIZE(int_A_q0, 32));
    int_A_address1       <= raddr(4 downto 2) when ar_hs = '1' else waddr(4 downto 2);
    int_A_ce1            <= '1' when ar_hs = '1' or (int_A_write = '1' and WVALID  = '1') else '0';
    int_A_we1            <= '1' when int_A_write = '1' and w_hs = '1' else '0';
    int_A_be1            <= UNSIGNED(WSTRB) when int_A_we1 = '1' else (others=>'0');
    int_A_d1             <= UNSIGNED(WDATA);
    -- C_out
    int_C_out_address0   <= UNSIGNED(C_out_address0);
    int_C_out_ce0        <= C_out_ce0;
    int_C_out_be0        <= (others => C_out_we0);
    int_C_out_d0         <= RESIZE(UNSIGNED(C_out_d0), 32);
    C_out_q0             <= STD_LOGIC_VECTOR(RESIZE(int_C_out_q0, 32));
    int_C_out_address1   <= raddr(4 downto 2) when ar_hs = '1' else waddr(4 downto 2);
    int_C_out_ce1        <= '1' when ar_hs = '1' or (int_C_out_write = '1' and WVALID  = '1') else '0';
    int_C_out_we1        <= '1' when int_C_out_write = '1' and w_hs = '1' else '0';
    int_C_out_be1        <= UNSIGNED(WSTRB) when int_C_out_we1 = '1' else (others=>'0');
    int_C_out_d1         <= UNSIGNED(WDATA);
    -- B
    int_B_address0       <= UNSIGNED(B_address0);
    int_B_ce0            <= B_ce0;
    B_q0                 <= STD_LOGIC_VECTOR(RESIZE(int_B_q0, 32));
    int_B_address1       <= raddr(6 downto 2) when ar_hs = '1' else waddr(6 downto 2);
    int_B_ce1            <= '1' when ar_hs = '1' or (int_B_write = '1' and WVALID  = '1') else '0';
    int_B_we1            <= '1' when int_B_write = '1' and w_hs = '1' else '0';
    int_B_be1            <= UNSIGNED(WSTRB) when int_B_we1 = '1' else (others=>'0');
    int_B_d1             <= UNSIGNED(WDATA);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_A_read <= '0';
            elsif (ACLK_EN = '1') then
                if (ar_hs = '1' and raddr >= ADDR_A_BASE and raddr <= ADDR_A_HIGH) then
                    int_A_read <= '1';
                else
                    int_A_read <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_A_write <= '0';
            elsif (ACLK_EN = '1') then
                if (aw_hs = '1' and UNSIGNED(AWADDR(ADDR_BITS-1 downto 0)) >= ADDR_A_BASE and UNSIGNED(AWADDR(ADDR_BITS-1 downto 0)) <= ADDR_A_HIGH) then
                    int_A_write <= '1';
                elsif (w_hs = '1') then
                    int_A_write <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_C_out_read <= '0';
            elsif (ACLK_EN = '1') then
                if (ar_hs = '1' and raddr >= ADDR_C_OUT_BASE and raddr <= ADDR_C_OUT_HIGH) then
                    int_C_out_read <= '1';
                else
                    int_C_out_read <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_C_out_write <= '0';
            elsif (ACLK_EN = '1') then
                if (aw_hs = '1' and UNSIGNED(AWADDR(ADDR_BITS-1 downto 0)) >= ADDR_C_OUT_BASE and UNSIGNED(AWADDR(ADDR_BITS-1 downto 0)) <= ADDR_C_OUT_HIGH) then
                    int_C_out_write <= '1';
                elsif (w_hs = '1') then
                    int_C_out_write <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_B_read <= '0';
            elsif (ACLK_EN = '1') then
                if (ar_hs = '1' and raddr >= ADDR_B_BASE and raddr <= ADDR_B_HIGH) then
                    int_B_read <= '1';
                else
                    int_B_read <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_B_write <= '0';
            elsif (ACLK_EN = '1') then
                if (aw_hs = '1' and UNSIGNED(AWADDR(ADDR_BITS-1 downto 0)) >= ADDR_B_BASE and UNSIGNED(AWADDR(ADDR_BITS-1 downto 0)) <= ADDR_B_HIGH) then
                    int_B_write <= '1';
                elsif (w_hs = '1') then
                    int_B_write <= '0';
                end if;
            end if;
        end if;
    end process;


end architecture behave;

library IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.all;

entity MatrixMultiplication_control_s_axi_ram is
    generic (
        MEM_STYLE : STRING :="auto";
        MEM_TYPE  : STRING :="S2P";
        BYTES   : INTEGER :=4;
        DEPTH   : INTEGER :=256;
        AWIDTH  : INTEGER :=8);
    port (
        clk0    : in  STD_LOGIC;
        address0: in  UNSIGNED(AWIDTH-1 downto 0);
        ce0     : in  STD_LOGIC;
        we0     : in  UNSIGNED(BYTES-1 downto 0);
        d0      : in  UNSIGNED(BYTES*8-1 downto 0);
        q0      : out UNSIGNED(BYTES*8-1 downto 0);
        clk1    : in  STD_LOGIC;
        address1: in  UNSIGNED(AWIDTH-1 downto 0);
        ce1     : in  STD_LOGIC;
        we1     : in  UNSIGNED(BYTES-1 downto 0);
        d1      : in  UNSIGNED(BYTES*8-1 downto 0);
        q1      : out UNSIGNED(BYTES*8-1 downto 0));

end entity MatrixMultiplication_control_s_axi_ram;

architecture behave of MatrixMultiplication_control_s_axi_ram is
    signal address0_tmp : UNSIGNED(AWIDTH-1 downto 0);
    signal address1_tmp : UNSIGNED(AWIDTH-1 downto 0);
    type RAM_T is array (0 to DEPTH - 1) of UNSIGNED(BYTES*8 - 1 downto 0);
    shared variable mem : RAM_T := (others => (others => '0'));
    attribute ram_style: string;
    attribute ram_style of mem: variable is MEM_STYLE;
    constant BYTE_WIDTH :INTEGER := 8;

    function port_type_gen( MEM_TYPE: STRING; MEM_STYLE: STRING; PORT_NAME: STRING) return STRING is
    begin
        if (MEM_TYPE = "S2P") and (PORT_NAME = "PORT0") then
            return "WO";
        elsif((MEM_TYPE = "S2P") and (PORT_NAME = "PORT1")) or ((MEM_TYPE = "2P") and (PORT_NAME = "PORT0")) then
            return "RO";
        elsif (MEM_STYLE = "hls_ultra") then
            return "RWNC";
        else
            return "RWRF";
        end if;
    end port_type_gen;
    constant PORT0 :STRING := port_type_gen(MEM_TYPE, MEM_STYLE, "PORT0");
    constant PORT1 :STRING := port_type_gen(MEM_TYPE, MEM_STYLE, "PORT1");

    function or_reduce( V: UNSIGNED) return std_logic is
    variable result: std_logic;
    begin
        for i in V'range loop
            if i = V'left then
                result := V(i);
            else
                result := result OR V(i);
            end if;
            exit when result = '1';
        end loop;
        return result;
    end or_reduce;

begin

    process (address0)
    begin
    address0_tmp <= address0;
    --synthesis translate_off
        if (address0 > DEPTH-1) then
            address0_tmp <= (others => '0');
        else
            address0_tmp <= address0;
        end if;
    --synthesis translate_on
    end process;

    process (address1)
    begin
    address1_tmp <= address1;
    --synthesis translate_off
        if (address1 > DEPTH-1) then
            address1_tmp <= (others => '0');
        else
            address1_tmp <= address1;
        end if;
    --synthesis translate_on
    end process;

    --read port 0
    read_p0_rf : if (PORT0 = "RO" or PORT0 = "RWRF") generate
        process (clk0) begin
            if (clk0'event and clk0 = '1') then
                if (ce0 = '1') then
                    q0 <= mem(to_integer(address0_tmp));
                end if;
            end if;
        end process;
    end generate read_p0_rf;

    read_p0_nc : if (PORT0 = "RWNC") generate
        process (clk0) begin
            if (clk0'event and clk0 = '1') then
                if (ce0 = '1') then
                    if (we0 = (we0'range => '0')) then
                        q0 <= mem(to_integer(address0_tmp));
                    end if;
                end if;
            end if;
        end process;
    end generate read_p0_nc;

    --read port 1
    read_p1_rf : if (PORT1 = "RO" or PORT1 = "RWRF") generate
        process (clk1) begin
            if (clk1'event and clk1 = '1') then
                if (ce1 = '1') then
                    q1 <= mem(to_integer(address1_tmp));
                end if;
            end if;
        end process;
    end generate read_p1_rf;

    read_p1_nc : if (PORT1 = "RWNC") generate
        process (clk1) begin
            if (clk1'event and clk1 = '1') then
                if (ce1 = '1') then
                    if (we1 = (we1'range => '0')) then
                        q1 <= mem(to_integer(address1_tmp));
                    end if;
                end if;
            end if;
        end process;
    end generate read_p1_nc;

    --write port 0
    write_p0 : if (PORT0 /= "RO") generate
        process (clk0)
        begin
            if (clk0'event and clk0 = '1') then
                if (ce0 = '1') then
                for i in 0 to BYTES - 1 loop
                    if (we0(i) = '1') then
                        mem(to_integer(address0_tmp))((i+1)*BYTE_WIDTH-1 downto i*BYTE_WIDTH) := d0((i+1)*BYTE_WIDTH-1 downto i*BYTE_WIDTH);
                    end if;
                end loop;
                end if;
            end if;
        end process;
    end generate write_p0;

    --write port 1
    write_p1 : if (PORT1 /= "RO") generate
        process (clk1)
        begin
            if (clk1'event and clk1 = '1') then
                if (ce1 = '1') then
                for i in 0 to BYTES - 1 loop
                    if (we1(i) = '1') then
                        mem(to_integer(address1_tmp))((i+1)*BYTE_WIDTH-1 downto i*BYTE_WIDTH) := d1((i+1)*BYTE_WIDTH-1 downto i*BYTE_WIDTH);
                    end if;
                end loop;
                end if;
            end if;
        end process;
    end generate write_p1;

end architecture behave;


