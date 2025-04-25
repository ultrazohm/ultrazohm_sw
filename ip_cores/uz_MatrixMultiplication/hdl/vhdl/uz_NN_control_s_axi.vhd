-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Tool Version Limit: 2019.12
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity uz_NN_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 8;
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
    interrupt             :out  STD_LOGIC;
    A_input               :out  STD_LOGIC_VECTOR(63 downto 0);
    B1_input              :out  STD_LOGIC_VECTOR(63 downto 0);
    B2_input              :out  STD_LOGIC_VECTOR(63 downto 0);
    B3_input              :out  STD_LOGIC_VECTOR(63 downto 0);
    B4_input              :out  STD_LOGIC_VECTOR(63 downto 0);
    C_output              :out  STD_LOGIC_VECTOR(63 downto 0);
    Bias1_input           :out  STD_LOGIC_VECTOR(63 downto 0);
    Bias2_input           :out  STD_LOGIC_VECTOR(63 downto 0);
    Bias3_input           :out  STD_LOGIC_VECTOR(63 downto 0);
    Bias4_input           :out  STD_LOGIC_VECTOR(63 downto 0);
    copy_mats_flag        :out  STD_LOGIC_VECTOR(0 downto 0);
    A_rows                :out  STD_LOGIC_VECTOR(31 downto 0);
    B1_rows               :out  STD_LOGIC_VECTOR(31 downto 0);
    B1_columns            :out  STD_LOGIC_VECTOR(31 downto 0);
    B2_columns            :out  STD_LOGIC_VECTOR(31 downto 0);
    copy_flag_out         :in   STD_LOGIC_VECTOR(0 downto 0);
    matrices_updated_out  :in   STD_LOGIC_VECTOR(0 downto 0);
    ap_start              :out  STD_LOGIC;
    ap_done               :in   STD_LOGIC;
    ap_ready              :in   STD_LOGIC;
    ap_idle               :in   STD_LOGIC
);
end entity uz_NN_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x00 : Control signals
--        bit 0  - ap_start (Read/Write/COH)
--        bit 1  - ap_done (Read/COR)
--        bit 2  - ap_idle (Read)
--        bit 3  - ap_ready (Read/COR)
--        bit 7  - auto_restart (Read/Write)
--        bit 9  - interrupt (Read)
--        others - reserved
-- 0x04 : Global Interrupt Enable Register
--        bit 0  - Global Interrupt Enable (Read/Write)
--        others - reserved
-- 0x08 : IP Interrupt Enable Register (Read/Write)
--        bit 0 - enable ap_done interrupt (Read/Write)
--        bit 1 - enable ap_ready interrupt (Read/Write)
--        others - reserved
-- 0x0c : IP Interrupt Status Register (Read/TOW)
--        bit 0 - ap_done (Read/TOW)
--        bit 1 - ap_ready (Read/TOW)
--        others - reserved
-- 0x10 : Data signal of A_input
--        bit 31~0 - A_input[31:0] (Read/Write)
-- 0x14 : Data signal of A_input
--        bit 31~0 - A_input[63:32] (Read/Write)
-- 0x18 : reserved
-- 0x1c : Data signal of B1_input
--        bit 31~0 - B1_input[31:0] (Read/Write)
-- 0x20 : Data signal of B1_input
--        bit 31~0 - B1_input[63:32] (Read/Write)
-- 0x24 : reserved
-- 0x28 : Data signal of B2_input
--        bit 31~0 - B2_input[31:0] (Read/Write)
-- 0x2c : Data signal of B2_input
--        bit 31~0 - B2_input[63:32] (Read/Write)
-- 0x30 : reserved
-- 0x34 : Data signal of B3_input
--        bit 31~0 - B3_input[31:0] (Read/Write)
-- 0x38 : Data signal of B3_input
--        bit 31~0 - B3_input[63:32] (Read/Write)
-- 0x3c : reserved
-- 0x40 : Data signal of B4_input
--        bit 31~0 - B4_input[31:0] (Read/Write)
-- 0x44 : Data signal of B4_input
--        bit 31~0 - B4_input[63:32] (Read/Write)
-- 0x48 : reserved
-- 0x4c : Data signal of C_output
--        bit 31~0 - C_output[31:0] (Read/Write)
-- 0x50 : Data signal of C_output
--        bit 31~0 - C_output[63:32] (Read/Write)
-- 0x54 : reserved
-- 0x58 : Data signal of Bias1_input
--        bit 31~0 - Bias1_input[31:0] (Read/Write)
-- 0x5c : Data signal of Bias1_input
--        bit 31~0 - Bias1_input[63:32] (Read/Write)
-- 0x60 : reserved
-- 0x64 : Data signal of Bias2_input
--        bit 31~0 - Bias2_input[31:0] (Read/Write)
-- 0x68 : Data signal of Bias2_input
--        bit 31~0 - Bias2_input[63:32] (Read/Write)
-- 0x6c : reserved
-- 0x70 : Data signal of Bias3_input
--        bit 31~0 - Bias3_input[31:0] (Read/Write)
-- 0x74 : Data signal of Bias3_input
--        bit 31~0 - Bias3_input[63:32] (Read/Write)
-- 0x78 : reserved
-- 0x7c : Data signal of Bias4_input
--        bit 31~0 - Bias4_input[31:0] (Read/Write)
-- 0x80 : Data signal of Bias4_input
--        bit 31~0 - Bias4_input[63:32] (Read/Write)
-- 0x84 : reserved
-- 0x88 : Data signal of copy_mats_flag
--        bit 0  - copy_mats_flag[0] (Read/Write)
--        others - reserved
-- 0x8c : reserved
-- 0x90 : Data signal of A_rows
--        bit 31~0 - A_rows[31:0] (Read/Write)
-- 0x94 : reserved
-- 0x98 : Data signal of B1_rows
--        bit 31~0 - B1_rows[31:0] (Read/Write)
-- 0x9c : reserved
-- 0xa0 : Data signal of B1_columns
--        bit 31~0 - B1_columns[31:0] (Read/Write)
-- 0xa4 : reserved
-- 0xa8 : Data signal of B2_columns
--        bit 31~0 - B2_columns[31:0] (Read/Write)
-- 0xac : reserved
-- 0xb0 : Data signal of copy_flag_out
--        bit 0  - copy_flag_out[0] (Read)
--        others - reserved
-- 0xb4 : reserved
-- 0xc0 : Data signal of matrices_updated_out
--        bit 0  - matrices_updated_out[0] (Read)
--        others - reserved
-- 0xc4 : reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of uz_NN_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_AP_CTRL                     : INTEGER := 16#00#;
    constant ADDR_GIE                         : INTEGER := 16#04#;
    constant ADDR_IER                         : INTEGER := 16#08#;
    constant ADDR_ISR                         : INTEGER := 16#0c#;
    constant ADDR_A_INPUT_DATA_0              : INTEGER := 16#10#;
    constant ADDR_A_INPUT_DATA_1              : INTEGER := 16#14#;
    constant ADDR_A_INPUT_CTRL                : INTEGER := 16#18#;
    constant ADDR_B1_INPUT_DATA_0             : INTEGER := 16#1c#;
    constant ADDR_B1_INPUT_DATA_1             : INTEGER := 16#20#;
    constant ADDR_B1_INPUT_CTRL               : INTEGER := 16#24#;
    constant ADDR_B2_INPUT_DATA_0             : INTEGER := 16#28#;
    constant ADDR_B2_INPUT_DATA_1             : INTEGER := 16#2c#;
    constant ADDR_B2_INPUT_CTRL               : INTEGER := 16#30#;
    constant ADDR_B3_INPUT_DATA_0             : INTEGER := 16#34#;
    constant ADDR_B3_INPUT_DATA_1             : INTEGER := 16#38#;
    constant ADDR_B3_INPUT_CTRL               : INTEGER := 16#3c#;
    constant ADDR_B4_INPUT_DATA_0             : INTEGER := 16#40#;
    constant ADDR_B4_INPUT_DATA_1             : INTEGER := 16#44#;
    constant ADDR_B4_INPUT_CTRL               : INTEGER := 16#48#;
    constant ADDR_C_OUTPUT_DATA_0             : INTEGER := 16#4c#;
    constant ADDR_C_OUTPUT_DATA_1             : INTEGER := 16#50#;
    constant ADDR_C_OUTPUT_CTRL               : INTEGER := 16#54#;
    constant ADDR_BIAS1_INPUT_DATA_0          : INTEGER := 16#58#;
    constant ADDR_BIAS1_INPUT_DATA_1          : INTEGER := 16#5c#;
    constant ADDR_BIAS1_INPUT_CTRL            : INTEGER := 16#60#;
    constant ADDR_BIAS2_INPUT_DATA_0          : INTEGER := 16#64#;
    constant ADDR_BIAS2_INPUT_DATA_1          : INTEGER := 16#68#;
    constant ADDR_BIAS2_INPUT_CTRL            : INTEGER := 16#6c#;
    constant ADDR_BIAS3_INPUT_DATA_0          : INTEGER := 16#70#;
    constant ADDR_BIAS3_INPUT_DATA_1          : INTEGER := 16#74#;
    constant ADDR_BIAS3_INPUT_CTRL            : INTEGER := 16#78#;
    constant ADDR_BIAS4_INPUT_DATA_0          : INTEGER := 16#7c#;
    constant ADDR_BIAS4_INPUT_DATA_1          : INTEGER := 16#80#;
    constant ADDR_BIAS4_INPUT_CTRL            : INTEGER := 16#84#;
    constant ADDR_COPY_MATS_FLAG_DATA_0       : INTEGER := 16#88#;
    constant ADDR_COPY_MATS_FLAG_CTRL         : INTEGER := 16#8c#;
    constant ADDR_A_ROWS_DATA_0               : INTEGER := 16#90#;
    constant ADDR_A_ROWS_CTRL                 : INTEGER := 16#94#;
    constant ADDR_B1_ROWS_DATA_0              : INTEGER := 16#98#;
    constant ADDR_B1_ROWS_CTRL                : INTEGER := 16#9c#;
    constant ADDR_B1_COLUMNS_DATA_0           : INTEGER := 16#a0#;
    constant ADDR_B1_COLUMNS_CTRL             : INTEGER := 16#a4#;
    constant ADDR_B2_COLUMNS_DATA_0           : INTEGER := 16#a8#;
    constant ADDR_B2_COLUMNS_CTRL             : INTEGER := 16#ac#;
    constant ADDR_COPY_FLAG_OUT_DATA_0        : INTEGER := 16#b0#;
    constant ADDR_COPY_FLAG_OUT_CTRL          : INTEGER := 16#b4#;
    constant ADDR_MATRICES_UPDATED_OUT_DATA_0 : INTEGER := 16#c0#;
    constant ADDR_MATRICES_UPDATED_OUT_CTRL   : INTEGER := 16#c4#;
    constant ADDR_BITS         : INTEGER := 8;

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
    signal int_ap_idle         : STD_LOGIC := '0';
    signal int_ap_ready        : STD_LOGIC := '0';
    signal task_ap_ready       : STD_LOGIC;
    signal int_ap_done         : STD_LOGIC := '0';
    signal task_ap_done        : STD_LOGIC;
    signal int_task_ap_done    : STD_LOGIC := '0';
    signal int_ap_start        : STD_LOGIC := '0';
    signal int_interrupt       : STD_LOGIC := '0';
    signal int_auto_restart    : STD_LOGIC := '0';
    signal auto_restart_status : STD_LOGIC := '0';
    signal auto_restart_done   : STD_LOGIC;
    signal int_gie             : STD_LOGIC := '0';
    signal int_ier             : UNSIGNED(1 downto 0) := (others => '0');
    signal int_isr             : UNSIGNED(1 downto 0) := (others => '0');
    signal int_A_input         : UNSIGNED(63 downto 0) := (others => '0');
    signal int_B1_input        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_B2_input        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_B3_input        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_B4_input        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_C_output        : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Bias1_input     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Bias2_input     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Bias3_input     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_Bias4_input     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_copy_mats_flag  : UNSIGNED(0 downto 0) := (others => '0');
    signal int_A_rows          : UNSIGNED(31 downto 0) := (others => '0');
    signal int_B1_rows         : UNSIGNED(31 downto 0) := (others => '0');
    signal int_B1_columns      : UNSIGNED(31 downto 0) := (others => '0');
    signal int_B2_columns      : UNSIGNED(31 downto 0) := (others => '0');
    signal int_copy_flag_out   : UNSIGNED(0 downto 0) := (others => '0');
    signal int_matrices_updated_out : UNSIGNED(0 downto 0) := (others => '0');


begin
-- ----------------------- Instantiation------------------


-- ----------------------- AXI WRITE ---------------------
    AWREADY_t <=  '1' when wstate = wridle else '0';
    AWREADY   <=  AWREADY_t;
    WREADY_t  <=  '1' when wstate = wrdata else '0';
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

    process (wstate, AWVALID, WVALID, BREADY)
    begin
        case (wstate) is
        when wridle =>
            if (AWVALID = '1') then
                wnext <= wrdata;
            else
                wnext <= wridle;
            end if;
        when wrdata =>
            if (WVALID = '1') then
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
    RVALID_t  <= '1' when (rstate = rddata) else '0';
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
                    when ADDR_AP_CTRL =>
                        rdata_data(9) <= int_interrupt;
                        rdata_data(7) <= int_auto_restart;
                        rdata_data(3) <= int_ap_ready;
                        rdata_data(2) <= int_ap_idle;
                        rdata_data(1) <= int_task_ap_done;
                        rdata_data(0) <= int_ap_start;
                    when ADDR_GIE =>
                        rdata_data(0) <= int_gie;
                    when ADDR_IER =>
                        rdata_data(1 downto 0) <= int_ier;
                    when ADDR_ISR =>
                        rdata_data(1 downto 0) <= int_isr;
                    when ADDR_A_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_A_input(31 downto 0), 32);
                    when ADDR_A_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_A_input(63 downto 32), 32);
                    when ADDR_B1_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_B1_input(31 downto 0), 32);
                    when ADDR_B1_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_B1_input(63 downto 32), 32);
                    when ADDR_B2_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_B2_input(31 downto 0), 32);
                    when ADDR_B2_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_B2_input(63 downto 32), 32);
                    when ADDR_B3_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_B3_input(31 downto 0), 32);
                    when ADDR_B3_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_B3_input(63 downto 32), 32);
                    when ADDR_B4_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_B4_input(31 downto 0), 32);
                    when ADDR_B4_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_B4_input(63 downto 32), 32);
                    when ADDR_C_OUTPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_C_output(31 downto 0), 32);
                    when ADDR_C_OUTPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_C_output(63 downto 32), 32);
                    when ADDR_BIAS1_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_Bias1_input(31 downto 0), 32);
                    when ADDR_BIAS1_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_Bias1_input(63 downto 32), 32);
                    when ADDR_BIAS2_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_Bias2_input(31 downto 0), 32);
                    when ADDR_BIAS2_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_Bias2_input(63 downto 32), 32);
                    when ADDR_BIAS3_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_Bias3_input(31 downto 0), 32);
                    when ADDR_BIAS3_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_Bias3_input(63 downto 32), 32);
                    when ADDR_BIAS4_INPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_Bias4_input(31 downto 0), 32);
                    when ADDR_BIAS4_INPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_Bias4_input(63 downto 32), 32);
                    when ADDR_COPY_MATS_FLAG_DATA_0 =>
                        rdata_data <= RESIZE(int_copy_mats_flag(0 downto 0), 32);
                    when ADDR_A_ROWS_DATA_0 =>
                        rdata_data <= RESIZE(int_A_rows(31 downto 0), 32);
                    when ADDR_B1_ROWS_DATA_0 =>
                        rdata_data <= RESIZE(int_B1_rows(31 downto 0), 32);
                    when ADDR_B1_COLUMNS_DATA_0 =>
                        rdata_data <= RESIZE(int_B1_columns(31 downto 0), 32);
                    when ADDR_B2_COLUMNS_DATA_0 =>
                        rdata_data <= RESIZE(int_B2_columns(31 downto 0), 32);
                    when ADDR_COPY_FLAG_OUT_DATA_0 =>
                        rdata_data <= RESIZE(int_copy_flag_out(0 downto 0), 32);
                    when ADDR_MATRICES_UPDATED_OUT_DATA_0 =>
                        rdata_data <= RESIZE(int_matrices_updated_out(0 downto 0), 32);
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    interrupt            <= int_interrupt;
    ap_start             <= int_ap_start;
    task_ap_done         <= (ap_done and not auto_restart_status) or auto_restart_done;
    task_ap_ready        <= ap_ready and not int_auto_restart;
    auto_restart_done    <= auto_restart_status and (ap_idle and not int_ap_idle);
    A_input              <= STD_LOGIC_VECTOR(int_A_input);
    B1_input             <= STD_LOGIC_VECTOR(int_B1_input);
    B2_input             <= STD_LOGIC_VECTOR(int_B2_input);
    B3_input             <= STD_LOGIC_VECTOR(int_B3_input);
    B4_input             <= STD_LOGIC_VECTOR(int_B4_input);
    C_output             <= STD_LOGIC_VECTOR(int_C_output);
    Bias1_input          <= STD_LOGIC_VECTOR(int_Bias1_input);
    Bias2_input          <= STD_LOGIC_VECTOR(int_Bias2_input);
    Bias3_input          <= STD_LOGIC_VECTOR(int_Bias3_input);
    Bias4_input          <= STD_LOGIC_VECTOR(int_Bias4_input);
    copy_mats_flag       <= STD_LOGIC_VECTOR(int_copy_mats_flag);
    A_rows               <= STD_LOGIC_VECTOR(int_A_rows);
    B1_rows              <= STD_LOGIC_VECTOR(int_B1_rows);
    B1_columns           <= STD_LOGIC_VECTOR(int_B1_columns);
    B2_columns           <= STD_LOGIC_VECTOR(int_B2_columns);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_interrupt <= '0';
            elsif (ACLK_EN = '1') then
                if (int_gie = '1' and (int_isr(0) or int_isr(1)) = '1') then
                    int_interrupt <= '1';
                else
                    int_interrupt <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_start <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AP_CTRL and WSTRB(0) = '1' and WDATA(0) = '1') then
                    int_ap_start <= '1';
                elsif (ap_ready = '1') then
                    int_ap_start <= int_auto_restart; -- clear on handshake/auto restart
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_done <= '0';
            elsif (ACLK_EN = '1') then
                if (true) then
                    int_ap_done <= ap_done;
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_task_ap_done <= '0';
            elsif (ACLK_EN = '1') then
                if (task_ap_done = '1') then
                    int_task_ap_done <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AP_CTRL) then
                    int_task_ap_done <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_idle <= '0';
            elsif (ACLK_EN = '1') then
                if (true) then
                    int_ap_idle <= ap_idle;
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_ready <= '0';
            elsif (ACLK_EN = '1') then
                if (task_ap_ready = '1') then
                    int_ap_ready <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AP_CTRL) then
                    int_ap_ready <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_auto_restart <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AP_CTRL and WSTRB(0) = '1') then
                    int_auto_restart <= WDATA(7);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                auto_restart_status <= '0';
            elsif (ACLK_EN = '1') then
                if (int_auto_restart = '1') then
                    auto_restart_status <= '1';
                elsif (ap_idle = '1') then
                    auto_restart_status <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_gie <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_GIE and WSTRB(0) = '1') then
                    int_gie <= WDATA(0);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ier <= (others=>'0');
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IER and WSTRB(0) = '1') then
                    int_ier <= UNSIGNED(WDATA(1 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_isr(0) <= '0';
            elsif (ACLK_EN = '1') then
                if (int_ier(0) = '1' and ap_done = '1') then
                    int_isr(0) <= '1';
                elsif (w_hs = '1' and waddr = ADDR_ISR and WSTRB(0) = '1') then
                    int_isr(0) <= int_isr(0) xor WDATA(0); -- toggle on write
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_isr(1) <= '0';
            elsif (ACLK_EN = '1') then
                if (int_ier(1) = '1' and ap_ready = '1') then
                    int_isr(1) <= '1';
                elsif (w_hs = '1' and waddr = ADDR_ISR and WSTRB(0) = '1') then
                    int_isr(1) <= int_isr(1) xor WDATA(1); -- toggle on write
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_A_INPUT_DATA_0) then
                    int_A_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_A_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_A_INPUT_DATA_1) then
                    int_A_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_A_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B1_INPUT_DATA_0) then
                    int_B1_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B1_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B1_INPUT_DATA_1) then
                    int_B1_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B1_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B2_INPUT_DATA_0) then
                    int_B2_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B2_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B2_INPUT_DATA_1) then
                    int_B2_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B2_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B3_INPUT_DATA_0) then
                    int_B3_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B3_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B3_INPUT_DATA_1) then
                    int_B3_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B3_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B4_INPUT_DATA_0) then
                    int_B4_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B4_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B4_INPUT_DATA_1) then
                    int_B4_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B4_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_C_OUTPUT_DATA_0) then
                    int_C_output(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_C_output(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_C_OUTPUT_DATA_1) then
                    int_C_output(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_C_output(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS1_INPUT_DATA_0) then
                    int_Bias1_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias1_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS1_INPUT_DATA_1) then
                    int_Bias1_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias1_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS2_INPUT_DATA_0) then
                    int_Bias2_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias2_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS2_INPUT_DATA_1) then
                    int_Bias2_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias2_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS3_INPUT_DATA_0) then
                    int_Bias3_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias3_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS3_INPUT_DATA_1) then
                    int_Bias3_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias3_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS4_INPUT_DATA_0) then
                    int_Bias4_input(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias4_input(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BIAS4_INPUT_DATA_1) then
                    int_Bias4_input(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Bias4_input(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_COPY_MATS_FLAG_DATA_0) then
                    int_copy_mats_flag(0 downto 0) <= (UNSIGNED(WDATA(0 downto 0)) and wmask(0 downto 0)) or ((not wmask(0 downto 0)) and int_copy_mats_flag(0 downto 0));
                end if;
            end if;
        end if;
    end process;

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
                if (w_hs = '1' and waddr = ADDR_B1_ROWS_DATA_0) then
                    int_B1_rows(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B1_rows(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B1_COLUMNS_DATA_0) then
                    int_B1_columns(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B1_columns(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_B2_COLUMNS_DATA_0) then
                    int_B2_columns(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_B2_columns(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_copy_flag_out <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (ap_done = '1') then
                    int_copy_flag_out <= UNSIGNED(copy_flag_out);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_matrices_updated_out <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (ap_done = '1') then
                    int_matrices_updated_out <= UNSIGNED(matrices_updated_out);
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
