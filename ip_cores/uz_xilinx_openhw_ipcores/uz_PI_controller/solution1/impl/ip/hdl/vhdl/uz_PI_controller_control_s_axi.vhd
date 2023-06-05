-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Tool Version Limit: 2019.12
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity uz_PI_controller_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 7;
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
    referenceValue        :out  STD_LOGIC_VECTOR(31 downto 0);
    sampletime            :out  STD_LOGIC_VECTOR(31 downto 0);
    KI                    :out  STD_LOGIC_VECTOR(31 downto 0);
    KP                    :out  STD_LOGIC_VECTOR(31 downto 0);
    limit                 :out  STD_LOGIC_VECTOR(31 downto 0);
    reset                 :out  STD_LOGIC_VECTOR(0 downto 0);
    axi_referenceValue    :in   STD_LOGIC_VECTOR(31 downto 0);
    axi_referenceValue_ap_vld :in   STD_LOGIC;
    axi_actualValue       :in   STD_LOGIC_VECTOR(31 downto 0);
    axi_actualValue_ap_vld :in   STD_LOGIC;
    error                 :in   STD_LOGIC_VECTOR(31 downto 0);
    error_ap_vld          :in   STD_LOGIC;
    P_sum                 :in   STD_LOGIC_VECTOR(31 downto 0);
    P_sum_ap_vld          :in   STD_LOGIC
);
end entity uz_PI_controller_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x00 : reserved
-- 0x04 : reserved
-- 0x08 : reserved
-- 0x0c : reserved
-- 0x10 : Data signal of referenceValue
--        bit 31~0 - referenceValue[31:0] (Read/Write)
-- 0x14 : reserved
-- 0x18 : Data signal of sampletime
--        bit 31~0 - sampletime[31:0] (Read/Write)
-- 0x1c : reserved
-- 0x20 : Data signal of KI
--        bit 31~0 - KI[31:0] (Read/Write)
-- 0x24 : reserved
-- 0x28 : Data signal of KP
--        bit 31~0 - KP[31:0] (Read/Write)
-- 0x2c : reserved
-- 0x30 : Data signal of limit
--        bit 31~0 - limit[31:0] (Read/Write)
-- 0x34 : reserved
-- 0x38 : Data signal of reset
--        bit 0  - reset[0] (Read/Write)
--        others - reserved
-- 0x3c : reserved
-- 0x40 : Data signal of axi_referenceValue
--        bit 31~0 - axi_referenceValue[31:0] (Read)
-- 0x44 : Control signal of axi_referenceValue
--        bit 0  - axi_referenceValue_ap_vld (Read/COR)
--        others - reserved
-- 0x50 : Data signal of axi_actualValue
--        bit 31~0 - axi_actualValue[31:0] (Read)
-- 0x54 : Control signal of axi_actualValue
--        bit 0  - axi_actualValue_ap_vld (Read/COR)
--        others - reserved
-- 0x60 : Data signal of error
--        bit 31~0 - error[31:0] (Read)
-- 0x64 : Control signal of error
--        bit 0  - error_ap_vld (Read/COR)
--        others - reserved
-- 0x70 : Data signal of P_sum
--        bit 31~0 - P_sum[31:0] (Read)
-- 0x74 : Control signal of P_sum
--        bit 0  - P_sum_ap_vld (Read/COR)
--        others - reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of uz_PI_controller_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_REFERENCEVALUE_DATA_0     : INTEGER := 16#10#;
    constant ADDR_REFERENCEVALUE_CTRL       : INTEGER := 16#14#;
    constant ADDR_SAMPLETIME_DATA_0         : INTEGER := 16#18#;
    constant ADDR_SAMPLETIME_CTRL           : INTEGER := 16#1c#;
    constant ADDR_KI_DATA_0                 : INTEGER := 16#20#;
    constant ADDR_KI_CTRL                   : INTEGER := 16#24#;
    constant ADDR_KP_DATA_0                 : INTEGER := 16#28#;
    constant ADDR_KP_CTRL                   : INTEGER := 16#2c#;
    constant ADDR_LIMIT_DATA_0              : INTEGER := 16#30#;
    constant ADDR_LIMIT_CTRL                : INTEGER := 16#34#;
    constant ADDR_RESET_DATA_0              : INTEGER := 16#38#;
    constant ADDR_RESET_CTRL                : INTEGER := 16#3c#;
    constant ADDR_AXI_REFERENCEVALUE_DATA_0 : INTEGER := 16#40#;
    constant ADDR_AXI_REFERENCEVALUE_CTRL   : INTEGER := 16#44#;
    constant ADDR_AXI_ACTUALVALUE_DATA_0    : INTEGER := 16#50#;
    constant ADDR_AXI_ACTUALVALUE_CTRL      : INTEGER := 16#54#;
    constant ADDR_ERROR_DATA_0              : INTEGER := 16#60#;
    constant ADDR_ERROR_CTRL                : INTEGER := 16#64#;
    constant ADDR_P_SUM_DATA_0              : INTEGER := 16#70#;
    constant ADDR_P_SUM_CTRL                : INTEGER := 16#74#;
    constant ADDR_BITS         : INTEGER := 7;

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
    signal int_referenceValue  : UNSIGNED(31 downto 0) := (others => '0');
    signal int_sampletime      : UNSIGNED(31 downto 0) := (others => '0');
    signal int_KI              : UNSIGNED(31 downto 0) := (others => '0');
    signal int_KP              : UNSIGNED(31 downto 0) := (others => '0');
    signal int_limit           : UNSIGNED(31 downto 0) := (others => '0');
    signal int_reset           : UNSIGNED(0 downto 0) := (others => '0');
    signal int_axi_referenceValue_ap_vld : STD_LOGIC;
    signal int_axi_referenceValue : UNSIGNED(31 downto 0) := (others => '0');
    signal int_axi_actualValue_ap_vld : STD_LOGIC;
    signal int_axi_actualValue : UNSIGNED(31 downto 0) := (others => '0');
    signal int_error_ap_vld    : STD_LOGIC;
    signal int_error           : UNSIGNED(31 downto 0) := (others => '0');
    signal int_P_sum_ap_vld    : STD_LOGIC;
    signal int_P_sum           : UNSIGNED(31 downto 0) := (others => '0');


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
                    when ADDR_REFERENCEVALUE_DATA_0 =>
                        rdata_data <= RESIZE(int_referenceValue(31 downto 0), 32);
                    when ADDR_SAMPLETIME_DATA_0 =>
                        rdata_data <= RESIZE(int_sampletime(31 downto 0), 32);
                    when ADDR_KI_DATA_0 =>
                        rdata_data <= RESIZE(int_KI(31 downto 0), 32);
                    when ADDR_KP_DATA_0 =>
                        rdata_data <= RESIZE(int_KP(31 downto 0), 32);
                    when ADDR_LIMIT_DATA_0 =>
                        rdata_data <= RESIZE(int_limit(31 downto 0), 32);
                    when ADDR_RESET_DATA_0 =>
                        rdata_data <= RESIZE(int_reset(0 downto 0), 32);
                    when ADDR_AXI_REFERENCEVALUE_DATA_0 =>
                        rdata_data <= RESIZE(int_axi_referenceValue(31 downto 0), 32);
                    when ADDR_AXI_REFERENCEVALUE_CTRL =>
                        rdata_data(0) <= int_axi_referenceValue_ap_vld;
                    when ADDR_AXI_ACTUALVALUE_DATA_0 =>
                        rdata_data <= RESIZE(int_axi_actualValue(31 downto 0), 32);
                    when ADDR_AXI_ACTUALVALUE_CTRL =>
                        rdata_data(0) <= int_axi_actualValue_ap_vld;
                    when ADDR_ERROR_DATA_0 =>
                        rdata_data <= RESIZE(int_error(31 downto 0), 32);
                    when ADDR_ERROR_CTRL =>
                        rdata_data(0) <= int_error_ap_vld;
                    when ADDR_P_SUM_DATA_0 =>
                        rdata_data <= RESIZE(int_P_sum(31 downto 0), 32);
                    when ADDR_P_SUM_CTRL =>
                        rdata_data(0) <= int_P_sum_ap_vld;
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    referenceValue       <= STD_LOGIC_VECTOR(int_referenceValue);
    sampletime           <= STD_LOGIC_VECTOR(int_sampletime);
    KI                   <= STD_LOGIC_VECTOR(int_KI);
    KP                   <= STD_LOGIC_VECTOR(int_KP);
    limit                <= STD_LOGIC_VECTOR(int_limit);
    reset                <= STD_LOGIC_VECTOR(int_reset);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_REFERENCEVALUE_DATA_0) then
                    int_referenceValue(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_referenceValue(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SAMPLETIME_DATA_0) then
                    int_sampletime(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_sampletime(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KI_DATA_0) then
                    int_KI(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_KI(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KP_DATA_0) then
                    int_KP(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_KP(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_LIMIT_DATA_0) then
                    int_limit(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_limit(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_RESET_DATA_0) then
                    int_reset(0 downto 0) <= (UNSIGNED(WDATA(0 downto 0)) and wmask(0 downto 0)) or ((not wmask(0 downto 0)) and int_reset(0 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_axi_referenceValue <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (axi_referenceValue_ap_vld = '1') then
                    int_axi_referenceValue <= UNSIGNED(axi_referenceValue);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_axi_referenceValue_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (axi_referenceValue_ap_vld = '1') then
                    int_axi_referenceValue_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AXI_REFERENCEVALUE_CTRL) then
                    int_axi_referenceValue_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_axi_actualValue <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (axi_actualValue_ap_vld = '1') then
                    int_axi_actualValue <= UNSIGNED(axi_actualValue);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_axi_actualValue_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (axi_actualValue_ap_vld = '1') then
                    int_axi_actualValue_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AXI_ACTUALVALUE_CTRL) then
                    int_axi_actualValue_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_error <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (error_ap_vld = '1') then
                    int_error <= UNSIGNED(error);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_error_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (error_ap_vld = '1') then
                    int_error_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_ERROR_CTRL) then
                    int_error_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_P_sum <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (P_sum_ap_vld = '1') then
                    int_P_sum <= UNSIGNED(P_sum);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_P_sum_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (P_sum_ap_vld = '1') then
                    int_P_sum_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_P_SUM_CTRL) then
                    int_P_sum_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
