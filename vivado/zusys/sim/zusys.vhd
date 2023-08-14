--Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
--Date        : Mon Feb 28 14:40:42 2022
--Host        : enc177112 running 64-bit major release  (build 9200)
--Command     : generate_target zusys.bd
--Design      : zusys
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity DataMover_imp_1A1U27G is
  port (
    ADC_A1 : in STD_LOGIC_VECTOR ( 127 downto 0 );
    ADC_A2 : in STD_LOGIC_VECTOR ( 127 downto 0 );
    ADC_A3 : in STD_LOGIC_VECTOR ( 127 downto 0 );
    Enable_AXI2TCM : in STD_LOGIC_VECTOR ( 0 to 0 );
    M00_AXI_araddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_arid : out STD_LOGIC_VECTOR ( 0 to 0 );
    M00_AXI_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M00_AXI_arlock : out STD_LOGIC;
    M00_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_arready : in STD_LOGIC;
    M00_AXI_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_aruser : out STD_LOGIC;
    M00_AXI_arvalid : out STD_LOGIC;
    M00_AXI_awaddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_awid : out STD_LOGIC_VECTOR ( 0 to 0 );
    M00_AXI_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M00_AXI_awlock : out STD_LOGIC;
    M00_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_awready : in STD_LOGIC;
    M00_AXI_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_awuser : out STD_LOGIC;
    M00_AXI_awvalid : out STD_LOGIC;
    M00_AXI_bid : in STD_LOGIC_VECTOR ( 5 downto 0 );
    M00_AXI_bready : out STD_LOGIC;
    M00_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_bvalid : in STD_LOGIC;
    M00_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_rid : in STD_LOGIC_VECTOR ( 5 downto 0 );
    M00_AXI_rlast : in STD_LOGIC;
    M00_AXI_rready : out STD_LOGIC;
    M00_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_rvalid : in STD_LOGIC;
    M00_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_wlast : out STD_LOGIC;
    M00_AXI_wready : in STD_LOGIC;
    M00_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_wvalid : out STD_LOGIC;
    Trigger_AXI2TCM : in STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_aclk : in STD_LOGIC;
    m00_axi_aresetn : in STD_LOGIC
  );
end DataMover_imp_1A1U27G;

architecture STRUCTURE of DataMover_imp_1A1U27G is
  component zusys_util_vector_logic_0_1 is
  port (
    Op1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Op2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Res : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_util_vector_logic_0_1;
  component zusys_AXI2TCM_0_0 is
  port (
    DATA_IN : in STD_LOGIC_VECTOR ( 383 downto 0 );
    write_done : out STD_LOGIC;
    init_axi_txn : in STD_LOGIC;
    axi_txn_done : out STD_LOGIC;
    axi_error : out STD_LOGIC;
    m00_axi_awid : out STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_awaddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m00_axi_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m00_axi_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m00_axi_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m00_axi_awlock : out STD_LOGIC;
    m00_axi_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m00_axi_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m00_axi_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m00_axi_awuser : out STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_awvalid : out STD_LOGIC;
    m00_axi_awready : in STD_LOGIC;
    m00_axi_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m00_axi_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m00_axi_wlast : out STD_LOGIC;
    m00_axi_wuser : out STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_wvalid : out STD_LOGIC;
    m00_axi_wready : in STD_LOGIC;
    m00_axi_bid : in STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m00_axi_buser : in STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_bvalid : in STD_LOGIC;
    m00_axi_bready : out STD_LOGIC;
    m00_axi_arid : out STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_araddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m00_axi_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m00_axi_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m00_axi_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m00_axi_arlock : out STD_LOGIC;
    m00_axi_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m00_axi_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m00_axi_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m00_axi_aruser : out STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_arvalid : out STD_LOGIC;
    m00_axi_arready : in STD_LOGIC;
    m00_axi_rid : in STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m00_axi_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m00_axi_rlast : in STD_LOGIC;
    m00_axi_ruser : in STD_LOGIC_VECTOR ( 0 to 0 );
    m00_axi_rvalid : in STD_LOGIC;
    m00_axi_rready : out STD_LOGIC;
    m00_axi_aclk : in STD_LOGIC;
    m00_axi_aresetn : in STD_LOGIC
  );
  end component zusys_AXI2TCM_0_0;
  component zusys_xlconcat_0_1 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 127 downto 0 );
    In1 : in STD_LOGIC_VECTOR ( 127 downto 0 );
    In2 : in STD_LOGIC_VECTOR ( 127 downto 0 );
    dout : out STD_LOGIC_VECTOR ( 383 downto 0 )
  );
  end component zusys_xlconcat_0_1;
  component zusys_ila_0_0 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 383 downto 0 );
    probe1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_ila_0_0;
  signal ADC_A1_1 : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal ADC_A2_1 : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal ADC_A3_1 : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal ADCs_ADC_values_raw : STD_LOGIC_VECTOR ( 383 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARADDR : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARLOCK : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_ARVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWADDR : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWLOCK : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_AWVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_BID : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal AXI2TCM_0_M00_AXI_BREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_BVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_RID : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal AXI2TCM_0_M00_AXI_RLAST : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_RREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_RVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_WLAST : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_WREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_WVALID : STD_LOGIC;
  signal AXI2TCM_0_axi_error : STD_LOGIC;
  signal AXI2TCM_0_write_done : STD_LOGIC;
  signal DATA_IN1_1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal DATA_IN2_1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal init_axi2tcm : STD_LOGIC_VECTOR ( 0 to 0 );
  signal proc_sys_reset_1_peripheral_aresetn : STD_LOGIC;
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
  signal NLW_AXI2TCM_0_axi_txn_done_UNCONNECTED : STD_LOGIC;
  signal NLW_AXI2TCM_0_m00_axi_wuser_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
begin
  ADC_A1_1(127 downto 0) <= ADC_A1(127 downto 0);
  ADC_A2_1(127 downto 0) <= ADC_A2(127 downto 0);
  ADC_A3_1(127 downto 0) <= ADC_A3(127 downto 0);
  AXI2TCM_0_M00_AXI_ARREADY <= M00_AXI_arready;
  AXI2TCM_0_M00_AXI_AWREADY <= M00_AXI_awready;
  AXI2TCM_0_M00_AXI_BID(5 downto 0) <= M00_AXI_bid(5 downto 0);
  AXI2TCM_0_M00_AXI_BRESP(1 downto 0) <= M00_AXI_bresp(1 downto 0);
  AXI2TCM_0_M00_AXI_BVALID <= M00_AXI_bvalid;
  AXI2TCM_0_M00_AXI_RDATA(31 downto 0) <= M00_AXI_rdata(31 downto 0);
  AXI2TCM_0_M00_AXI_RID(5 downto 0) <= M00_AXI_rid(5 downto 0);
  AXI2TCM_0_M00_AXI_RLAST <= M00_AXI_rlast;
  AXI2TCM_0_M00_AXI_RRESP(1 downto 0) <= M00_AXI_rresp(1 downto 0);
  AXI2TCM_0_M00_AXI_RVALID <= M00_AXI_rvalid;
  AXI2TCM_0_M00_AXI_WREADY <= M00_AXI_wready;
  DATA_IN1_1(0) <= Trigger_AXI2TCM(0);
  DATA_IN2_1(0) <= Enable_AXI2TCM(0);
  M00_AXI_araddr(31 downto 0) <= AXI2TCM_0_M00_AXI_ARADDR(31 downto 0);
  M00_AXI_arburst(1 downto 0) <= AXI2TCM_0_M00_AXI_ARBURST(1 downto 0);
  M00_AXI_arcache(3 downto 0) <= AXI2TCM_0_M00_AXI_ARCACHE(3 downto 0);
  M00_AXI_arid(0) <= AXI2TCM_0_M00_AXI_ARID(0);
  M00_AXI_arlen(7 downto 0) <= AXI2TCM_0_M00_AXI_ARLEN(7 downto 0);
  M00_AXI_arlock <= AXI2TCM_0_M00_AXI_ARLOCK;
  M00_AXI_arprot(2 downto 0) <= AXI2TCM_0_M00_AXI_ARPROT(2 downto 0);
  M00_AXI_arqos(3 downto 0) <= AXI2TCM_0_M00_AXI_ARQOS(3 downto 0);
  M00_AXI_arsize(2 downto 0) <= AXI2TCM_0_M00_AXI_ARSIZE(2 downto 0);
  M00_AXI_aruser <= AXI2TCM_0_M00_AXI_ARUSER(0);
  M00_AXI_arvalid <= AXI2TCM_0_M00_AXI_ARVALID;
  M00_AXI_awaddr(31 downto 0) <= AXI2TCM_0_M00_AXI_AWADDR(31 downto 0);
  M00_AXI_awburst(1 downto 0) <= AXI2TCM_0_M00_AXI_AWBURST(1 downto 0);
  M00_AXI_awcache(3 downto 0) <= AXI2TCM_0_M00_AXI_AWCACHE(3 downto 0);
  M00_AXI_awid(0) <= AXI2TCM_0_M00_AXI_AWID(0);
  M00_AXI_awlen(7 downto 0) <= AXI2TCM_0_M00_AXI_AWLEN(7 downto 0);
  M00_AXI_awlock <= AXI2TCM_0_M00_AXI_AWLOCK;
  M00_AXI_awprot(2 downto 0) <= AXI2TCM_0_M00_AXI_AWPROT(2 downto 0);
  M00_AXI_awqos(3 downto 0) <= AXI2TCM_0_M00_AXI_AWQOS(3 downto 0);
  M00_AXI_awsize(2 downto 0) <= AXI2TCM_0_M00_AXI_AWSIZE(2 downto 0);
  M00_AXI_awuser <= AXI2TCM_0_M00_AXI_AWUSER(0);
  M00_AXI_awvalid <= AXI2TCM_0_M00_AXI_AWVALID;
  M00_AXI_bready <= AXI2TCM_0_M00_AXI_BREADY;
  M00_AXI_rready <= AXI2TCM_0_M00_AXI_RREADY;
  M00_AXI_wdata(31 downto 0) <= AXI2TCM_0_M00_AXI_WDATA(31 downto 0);
  M00_AXI_wlast <= AXI2TCM_0_M00_AXI_WLAST;
  M00_AXI_wstrb(3 downto 0) <= AXI2TCM_0_M00_AXI_WSTRB(3 downto 0);
  M00_AXI_wvalid <= AXI2TCM_0_M00_AXI_WVALID;
  proc_sys_reset_1_peripheral_aresetn <= m00_axi_aresetn;
  zynq_ultra_ps_e_0_pl_clk1 <= m00_axi_aclk;
AXI2TCM_0: component zusys_AXI2TCM_0_0
     port map (
      DATA_IN(383 downto 0) => ADCs_ADC_values_raw(383 downto 0),
      axi_error => AXI2TCM_0_axi_error,
      axi_txn_done => NLW_AXI2TCM_0_axi_txn_done_UNCONNECTED,
      init_axi_txn => init_axi2tcm(0),
      m00_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      m00_axi_araddr(31 downto 0) => AXI2TCM_0_M00_AXI_ARADDR(31 downto 0),
      m00_axi_arburst(1 downto 0) => AXI2TCM_0_M00_AXI_ARBURST(1 downto 0),
      m00_axi_arcache(3 downto 0) => AXI2TCM_0_M00_AXI_ARCACHE(3 downto 0),
      m00_axi_aresetn => proc_sys_reset_1_peripheral_aresetn,
      m00_axi_arid(0) => AXI2TCM_0_M00_AXI_ARID(0),
      m00_axi_arlen(7 downto 0) => AXI2TCM_0_M00_AXI_ARLEN(7 downto 0),
      m00_axi_arlock => AXI2TCM_0_M00_AXI_ARLOCK,
      m00_axi_arprot(2 downto 0) => AXI2TCM_0_M00_AXI_ARPROT(2 downto 0),
      m00_axi_arqos(3 downto 0) => AXI2TCM_0_M00_AXI_ARQOS(3 downto 0),
      m00_axi_arready => AXI2TCM_0_M00_AXI_ARREADY,
      m00_axi_arsize(2 downto 0) => AXI2TCM_0_M00_AXI_ARSIZE(2 downto 0),
      m00_axi_aruser(0) => AXI2TCM_0_M00_AXI_ARUSER(0),
      m00_axi_arvalid => AXI2TCM_0_M00_AXI_ARVALID,
      m00_axi_awaddr(31 downto 0) => AXI2TCM_0_M00_AXI_AWADDR(31 downto 0),
      m00_axi_awburst(1 downto 0) => AXI2TCM_0_M00_AXI_AWBURST(1 downto 0),
      m00_axi_awcache(3 downto 0) => AXI2TCM_0_M00_AXI_AWCACHE(3 downto 0),
      m00_axi_awid(0) => AXI2TCM_0_M00_AXI_AWID(0),
      m00_axi_awlen(7 downto 0) => AXI2TCM_0_M00_AXI_AWLEN(7 downto 0),
      m00_axi_awlock => AXI2TCM_0_M00_AXI_AWLOCK,
      m00_axi_awprot(2 downto 0) => AXI2TCM_0_M00_AXI_AWPROT(2 downto 0),
      m00_axi_awqos(3 downto 0) => AXI2TCM_0_M00_AXI_AWQOS(3 downto 0),
      m00_axi_awready => AXI2TCM_0_M00_AXI_AWREADY,
      m00_axi_awsize(2 downto 0) => AXI2TCM_0_M00_AXI_AWSIZE(2 downto 0),
      m00_axi_awuser(0) => AXI2TCM_0_M00_AXI_AWUSER(0),
      m00_axi_awvalid => AXI2TCM_0_M00_AXI_AWVALID,
      m00_axi_bid(0) => AXI2TCM_0_M00_AXI_BID(0),
      m00_axi_bready => AXI2TCM_0_M00_AXI_BREADY,
      m00_axi_bresp(1 downto 0) => AXI2TCM_0_M00_AXI_BRESP(1 downto 0),
      m00_axi_buser(0) => '0',
      m00_axi_bvalid => AXI2TCM_0_M00_AXI_BVALID,
      m00_axi_rdata(31 downto 0) => AXI2TCM_0_M00_AXI_RDATA(31 downto 0),
      m00_axi_rid(0) => AXI2TCM_0_M00_AXI_RID(0),
      m00_axi_rlast => AXI2TCM_0_M00_AXI_RLAST,
      m00_axi_rready => AXI2TCM_0_M00_AXI_RREADY,
      m00_axi_rresp(1 downto 0) => AXI2TCM_0_M00_AXI_RRESP(1 downto 0),
      m00_axi_ruser(0) => '0',
      m00_axi_rvalid => AXI2TCM_0_M00_AXI_RVALID,
      m00_axi_wdata(31 downto 0) => AXI2TCM_0_M00_AXI_WDATA(31 downto 0),
      m00_axi_wlast => AXI2TCM_0_M00_AXI_WLAST,
      m00_axi_wready => AXI2TCM_0_M00_AXI_WREADY,
      m00_axi_wstrb(3 downto 0) => AXI2TCM_0_M00_AXI_WSTRB(3 downto 0),
      m00_axi_wuser(0) => NLW_AXI2TCM_0_m00_axi_wuser_UNCONNECTED(0),
      m00_axi_wvalid => AXI2TCM_0_M00_AXI_WVALID,
      write_done => AXI2TCM_0_write_done
    );
ila_0: component zusys_ila_0_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(383 downto 0) => ADCs_ADC_values_raw(383 downto 0),
      probe1(0) => init_axi2tcm(0),
      probe2(0) => AXI2TCM_0_write_done,
      probe3(0) => AXI2TCM_0_axi_error,
      probe4(0) => DATA_IN1_1(0)
    );
util_vector_logic_0: component zusys_util_vector_logic_0_1
     port map (
      Op1(0) => DATA_IN1_1(0),
      Op2(0) => DATA_IN2_1(0),
      Res(0) => init_axi2tcm(0)
    );
xlconcat_0: component zusys_xlconcat_0_1
     port map (
      In0(127 downto 0) => ADC_A1_1(127 downto 0),
      In1(127 downto 0) => ADC_A2_1(127 downto 0),
      In2(127 downto 0) => ADC_A3_1(127 downto 0),
      dout(383 downto 0) => ADCs_ADC_values_raw(383 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity Gates_3L_imp_TK8CX6 is
  port (
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_arready : out STD_LOGIC;
    AXI4_Lite_arvalid : in STD_LOGIC;
    AXI4_Lite_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_awready : out STD_LOGIC;
    AXI4_Lite_awvalid : in STD_LOGIC;
    AXI4_Lite_bready : in STD_LOGIC;
    AXI4_Lite_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_bvalid : out STD_LOGIC;
    AXI4_Lite_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_rready : in STD_LOGIC;
    AXI4_Lite_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_rvalid : out STD_LOGIC;
    AXI4_Lite_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_wready : out STD_LOGIC;
    AXI4_Lite_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_wvalid : in STD_LOGIC;
    Enable_Gates : in STD_LOGIC;
    Gate_Signals_3L : out STD_LOGIC_VECTOR ( 11 downto 0 );
    Interrupt_Center : out STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt_Start : out STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt_Start_Center : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
end Gates_3L_imp_TK8CX6;

architecture STRUCTURE of Gates_3L_imp_TK8CX6 is
  component zusys_PWM_SS_3L_ip_0_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SSa1_IN_External : in STD_LOGIC;
    SSa2_IN_External : in STD_LOGIC;
    SSb1_IN_External : in STD_LOGIC;
    SSb2_IN_External : in STD_LOGIC;
    SSc1_IN_External : in STD_LOGIC;
    SSc2_IN_External : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    SSa1_OUT : out STD_LOGIC;
    SSa2_OUT : out STD_LOGIC;
    SSb1_OUT : out STD_LOGIC;
    SSb2_OUT : out STD_LOGIC;
    SSc1_OUT : out STD_LOGIC;
    SSc2_OUT : out STD_LOGIC;
    Period_Center : out STD_LOGIC;
    Period_Start : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  end component zusys_PWM_SS_3L_ip_0_0;
  component zusys_top_npc_state_machine_0_0 is
  port (
    clock : in STD_LOGIC;
    enable : in STD_LOGIC;
    switching_signals : in STD_LOGIC_VECTOR ( 5 downto 0 );
    deadtime : in STD_LOGIC_VECTOR ( 9 downto 0 );
    A_S1 : out STD_LOGIC;
    A_S2 : out STD_LOGIC;
    A_S3 : out STD_LOGIC;
    A_S4 : out STD_LOGIC;
    B_S1 : out STD_LOGIC;
    B_S2 : out STD_LOGIC;
    B_S3 : out STD_LOGIC;
    B_S4 : out STD_LOGIC;
    C_S1 : out STD_LOGIC;
    C_S2 : out STD_LOGIC;
    C_S3 : out STD_LOGIC;
    C_S4 : out STD_LOGIC;
    A_phase_off : out STD_LOGIC;
    B_phase_off : out STD_LOGIC;
    C_phase_off : out STD_LOGIC
  );
  end component zusys_top_npc_state_machine_0_0;
  component zusys_Gates_Vector_0 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 5 downto 0 )
  );
  end component zusys_Gates_Vector_0;
  component zusys_xlconcat_0_2 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In8 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In9 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In10 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In11 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 11 downto 0 )
  );
  end component zusys_xlconcat_0_2;
  component zusys_Interrupt_Start_Center_0 is
  port (
    Op1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Op2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Res : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_Interrupt_Start_Center_0;
  component zusys_ila_0_1 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe8 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe9 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe10 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe11 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe12 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe13 : in STD_LOGIC_VECTOR ( 5 downto 0 );
    probe14 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe15 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe16 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe17 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe18 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe19 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe20 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe21 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe22 : in STD_LOGIC_VECTOR ( 9 downto 0 )
  );
  end component zusys_ila_0_1;
  component zusys_Set_Deadtime_3L_0 is
  port (
    clk : in STD_LOGIC;
    probe_out0 : out STD_LOGIC_VECTOR ( 9 downto 0 )
  );
  end component zusys_Set_Deadtime_3L_0;
  component zusys_vio_Gates_3L_0 is
  port (
    clk : in STD_LOGIC;
    probe_out0 : out STD_LOGIC_VECTOR ( 13 downto 0 );
    probe_out1 : out STD_LOGIC_VECTOR ( 13 downto 0 );
    probe_out2 : out STD_LOGIC_VECTOR ( 13 downto 0 );
    probe_out3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out8 : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_vio_Gates_3L_0;
  signal Enable_Gates_1 : STD_LOGIC;
  signal Gates_Vector_dout : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal Interrupt_Start_Center_Res : STD_LOGIC_VECTOR ( 0 to 0 );
  signal PWM_SS_3L_ip_0_Period_Center : STD_LOGIC;
  signal PWM_SS_3L_ip_0_Period_Start : STD_LOGIC;
  signal PWM_SS_3L_ip_0_SSa1_OUT : STD_LOGIC;
  signal PWM_SS_3L_ip_0_SSa2_OUT : STD_LOGIC;
  signal PWM_SS_3L_ip_0_SSb1_OUT : STD_LOGIC;
  signal PWM_SS_3L_ip_0_SSb2_OUT : STD_LOGIC;
  signal PWM_SS_3L_ip_0_SSc1_OUT : STD_LOGIC;
  signal PWM_SS_3L_ip_0_SSc2_OUT : STD_LOGIC;
  signal Set_Deadtime_3L_probe_out0 : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal proc_sys_reset_1_peripheral_aresetn : STD_LOGIC;
  signal smartconnect_0_M12_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M12_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M12_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M12_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M12_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M12_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M12_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M12_AXI_WVALID : STD_LOGIC;
  signal top_npc_state_machine_0_A_S1 : STD_LOGIC;
  signal top_npc_state_machine_0_A_S2 : STD_LOGIC;
  signal top_npc_state_machine_0_A_S3 : STD_LOGIC;
  signal top_npc_state_machine_0_A_S4 : STD_LOGIC;
  signal top_npc_state_machine_0_B_S1 : STD_LOGIC;
  signal top_npc_state_machine_0_B_S2 : STD_LOGIC;
  signal top_npc_state_machine_0_B_S3 : STD_LOGIC;
  signal top_npc_state_machine_0_B_S4 : STD_LOGIC;
  signal top_npc_state_machine_0_C_S1 : STD_LOGIC;
  signal top_npc_state_machine_0_C_S2 : STD_LOGIC;
  signal top_npc_state_machine_0_C_S3 : STD_LOGIC;
  signal top_npc_state_machine_0_C_S4 : STD_LOGIC;
  signal vio_Gates_3L_probe_out0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal vio_Gates_3L_probe_out1 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal vio_Gates_3L_probe_out2 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal vio_Gates_3L_probe_out3 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal vio_Gates_3L_probe_out4 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal vio_Gates_3L_probe_out5 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal vio_Gates_3L_probe_out6 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal vio_Gates_3L_probe_out7 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal vio_Gates_3L_probe_out8 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal xlconcat_0_dout : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
  signal NLW_top_npc_state_machine_0_A_phase_off_UNCONNECTED : STD_LOGIC;
  signal NLW_top_npc_state_machine_0_B_phase_off_UNCONNECTED : STD_LOGIC;
  signal NLW_top_npc_state_machine_0_C_phase_off_UNCONNECTED : STD_LOGIC;
begin
  AXI4_Lite_arready <= smartconnect_0_M12_AXI_ARREADY;
  AXI4_Lite_awready <= smartconnect_0_M12_AXI_AWREADY;
  AXI4_Lite_bresp(1 downto 0) <= smartconnect_0_M12_AXI_BRESP(1 downto 0);
  AXI4_Lite_bvalid <= smartconnect_0_M12_AXI_BVALID;
  AXI4_Lite_rdata(31 downto 0) <= smartconnect_0_M12_AXI_RDATA(31 downto 0);
  AXI4_Lite_rresp(1 downto 0) <= smartconnect_0_M12_AXI_RRESP(1 downto 0);
  AXI4_Lite_rvalid <= smartconnect_0_M12_AXI_RVALID;
  AXI4_Lite_wready <= smartconnect_0_M12_AXI_WREADY;
  Enable_Gates_1 <= Enable_Gates;
  Gate_Signals_3L(11 downto 0) <= xlconcat_0_dout(11 downto 0);
  Interrupt_Center(0) <= PWM_SS_3L_ip_0_Period_Center;
  Interrupt_Start(0) <= PWM_SS_3L_ip_0_Period_Start;
  Interrupt_Start_Center(0) <= Interrupt_Start_Center_Res(0);
  proc_sys_reset_1_peripheral_aresetn <= AXI4_Lite_ARESETN;
  smartconnect_0_M12_AXI_ARADDR(15 downto 0) <= AXI4_Lite_araddr(15 downto 0);
  smartconnect_0_M12_AXI_ARVALID <= AXI4_Lite_arvalid;
  smartconnect_0_M12_AXI_AWADDR(15 downto 0) <= AXI4_Lite_awaddr(15 downto 0);
  smartconnect_0_M12_AXI_AWVALID <= AXI4_Lite_awvalid;
  smartconnect_0_M12_AXI_BREADY <= AXI4_Lite_bready;
  smartconnect_0_M12_AXI_RREADY <= AXI4_Lite_rready;
  smartconnect_0_M12_AXI_WDATA(31 downto 0) <= AXI4_Lite_wdata(31 downto 0);
  smartconnect_0_M12_AXI_WSTRB(3 downto 0) <= AXI4_Lite_wstrb(3 downto 0);
  smartconnect_0_M12_AXI_WVALID <= AXI4_Lite_wvalid;
  zynq_ultra_ps_e_0_pl_clk1 <= AXI4_Lite_ACLK;
Gates_Vector: component zusys_Gates_Vector_0
     port map (
      In0(0) => PWM_SS_3L_ip_0_SSa1_OUT,
      In1(0) => PWM_SS_3L_ip_0_SSa2_OUT,
      In2(0) => PWM_SS_3L_ip_0_SSb1_OUT,
      In3(0) => PWM_SS_3L_ip_0_SSb2_OUT,
      In4(0) => PWM_SS_3L_ip_0_SSc1_OUT,
      In5(0) => PWM_SS_3L_ip_0_SSc2_OUT,
      dout(5 downto 0) => Gates_Vector_dout(5 downto 0)
    );
interrupt_start_center_RnM: component zusys_Interrupt_Start_Center_0
     port map (
      Op1(0) => PWM_SS_3L_ip_0_Period_Center,
      Op2(0) => PWM_SS_3L_ip_0_Period_Start,
      Res(0) => Interrupt_Start_Center_Res(0)
    );
PWM_SS_3L_ip_0: component zusys_PWM_SS_3L_ip_0_0
     port map (
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARADDR(15 downto 0) => smartconnect_0_M12_AXI_ARADDR(15 downto 0),
      AXI4_Lite_ARESETN => proc_sys_reset_1_peripheral_aresetn,
      AXI4_Lite_ARREADY => smartconnect_0_M12_AXI_ARREADY,
      AXI4_Lite_ARVALID => smartconnect_0_M12_AXI_ARVALID,
      AXI4_Lite_AWADDR(15 downto 0) => smartconnect_0_M12_AXI_AWADDR(15 downto 0),
      AXI4_Lite_AWREADY => smartconnect_0_M12_AXI_AWREADY,
      AXI4_Lite_AWVALID => smartconnect_0_M12_AXI_AWVALID,
      AXI4_Lite_BREADY => smartconnect_0_M12_AXI_BREADY,
      AXI4_Lite_BRESP(1 downto 0) => smartconnect_0_M12_AXI_BRESP(1 downto 0),
      AXI4_Lite_BVALID => smartconnect_0_M12_AXI_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => smartconnect_0_M12_AXI_RDATA(31 downto 0),
      AXI4_Lite_RREADY => smartconnect_0_M12_AXI_RREADY,
      AXI4_Lite_RRESP(1 downto 0) => smartconnect_0_M12_AXI_RRESP(1 downto 0),
      AXI4_Lite_RVALID => smartconnect_0_M12_AXI_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => smartconnect_0_M12_AXI_WDATA(31 downto 0),
      AXI4_Lite_WREADY => smartconnect_0_M12_AXI_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => smartconnect_0_M12_AXI_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => smartconnect_0_M12_AXI_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => proc_sys_reset_1_peripheral_aresetn,
      Period_Center => PWM_SS_3L_ip_0_Period_Center,
      Period_Start => PWM_SS_3L_ip_0_Period_Start,
      SSa1_IN_External => vio_Gates_3L_probe_out3(0),
      SSa1_OUT => PWM_SS_3L_ip_0_SSa1_OUT,
      SSa2_IN_External => vio_Gates_3L_probe_out4(0),
      SSa2_OUT => PWM_SS_3L_ip_0_SSa2_OUT,
      SSb1_IN_External => vio_Gates_3L_probe_out5(0),
      SSb1_OUT => PWM_SS_3L_ip_0_SSb1_OUT,
      SSb2_IN_External => vio_Gates_3L_probe_out6(0),
      SSb2_OUT => PWM_SS_3L_ip_0_SSb2_OUT,
      SSc1_IN_External => vio_Gates_3L_probe_out7(0),
      SSc1_OUT => PWM_SS_3L_ip_0_SSc1_OUT,
      SSc2_IN_External => vio_Gates_3L_probe_out8(0),
      SSc2_OUT => PWM_SS_3L_ip_0_SSc2_OUT,
      m_u1_norm(13 downto 0) => vio_Gates_3L_probe_out0(13 downto 0),
      m_u2_norm(13 downto 0) => vio_Gates_3L_probe_out1(13 downto 0),
      m_u3_norm(13 downto 0) => vio_Gates_3L_probe_out2(13 downto 0)
    );
Set_Deadtime_3L: component zusys_Set_Deadtime_3L_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_out0(9 downto 0) => Set_Deadtime_3L_probe_out0(9 downto 0)
    );
ila_0: component zusys_ila_0_1
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(0) => top_npc_state_machine_0_A_S1,
      probe1(0) => top_npc_state_machine_0_A_S2,
      probe10(0) => top_npc_state_machine_0_C_S3,
      probe11(0) => top_npc_state_machine_0_C_S4,
      probe12(0) => Interrupt_Start_Center_Res(0),
      probe13(5 downto 0) => Gates_Vector_dout(5 downto 0),
      probe14(0) => PWM_SS_3L_ip_0_SSa1_OUT,
      probe15(0) => PWM_SS_3L_ip_0_SSa2_OUT,
      probe16(0) => PWM_SS_3L_ip_0_SSb1_OUT,
      probe17(0) => PWM_SS_3L_ip_0_SSb2_OUT,
      probe18(0) => PWM_SS_3L_ip_0_SSc1_OUT,
      probe19(0) => PWM_SS_3L_ip_0_SSc2_OUT,
      probe2(0) => top_npc_state_machine_0_A_S3,
      probe20(0) => PWM_SS_3L_ip_0_Period_Center,
      probe21(0) => PWM_SS_3L_ip_0_Period_Start,
      probe22(9 downto 0) => Set_Deadtime_3L_probe_out0(9 downto 0),
      probe3(0) => top_npc_state_machine_0_A_S4,
      probe4(0) => top_npc_state_machine_0_B_S1,
      probe5(0) => top_npc_state_machine_0_B_S2,
      probe6(0) => top_npc_state_machine_0_B_S3,
      probe7(0) => top_npc_state_machine_0_B_S4,
      probe8(0) => top_npc_state_machine_0_C_S1,
      probe9(0) => top_npc_state_machine_0_C_S2
    );
top_npc_state_machine_0: component zusys_top_npc_state_machine_0_0
     port map (
      A_S1 => top_npc_state_machine_0_A_S1,
      A_S2 => top_npc_state_machine_0_A_S2,
      A_S3 => top_npc_state_machine_0_A_S3,
      A_S4 => top_npc_state_machine_0_A_S4,
      A_phase_off => NLW_top_npc_state_machine_0_A_phase_off_UNCONNECTED,
      B_S1 => top_npc_state_machine_0_B_S1,
      B_S2 => top_npc_state_machine_0_B_S2,
      B_S3 => top_npc_state_machine_0_B_S3,
      B_S4 => top_npc_state_machine_0_B_S4,
      B_phase_off => NLW_top_npc_state_machine_0_B_phase_off_UNCONNECTED,
      C_S1 => top_npc_state_machine_0_C_S1,
      C_S2 => top_npc_state_machine_0_C_S2,
      C_S3 => top_npc_state_machine_0_C_S3,
      C_S4 => top_npc_state_machine_0_C_S4,
      C_phase_off => NLW_top_npc_state_machine_0_C_phase_off_UNCONNECTED,
      clock => zynq_ultra_ps_e_0_pl_clk1,
      deadtime(9 downto 0) => Set_Deadtime_3L_probe_out0(9 downto 0),
      enable => Enable_Gates_1,
      switching_signals(5 downto 0) => Gates_Vector_dout(5 downto 0)
    );
vio_Gates_3L: component zusys_vio_Gates_3L_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_out0(13 downto 0) => vio_Gates_3L_probe_out0(13 downto 0),
      probe_out1(13 downto 0) => vio_Gates_3L_probe_out1(13 downto 0),
      probe_out2(13 downto 0) => vio_Gates_3L_probe_out2(13 downto 0),
      probe_out3(0) => vio_Gates_3L_probe_out3(0),
      probe_out4(0) => vio_Gates_3L_probe_out4(0),
      probe_out5(0) => vio_Gates_3L_probe_out5(0),
      probe_out6(0) => vio_Gates_3L_probe_out6(0),
      probe_out7(0) => vio_Gates_3L_probe_out7(0),
      probe_out8(0) => vio_Gates_3L_probe_out8(0)
    );
xlconcat_0: component zusys_xlconcat_0_2
     port map (
      In0(0) => top_npc_state_machine_0_A_S1,
      In1(0) => top_npc_state_machine_0_A_S2,
      In10(0) => top_npc_state_machine_0_C_S3,
      In11(0) => top_npc_state_machine_0_C_S4,
      In2(0) => top_npc_state_machine_0_A_S3,
      In3(0) => top_npc_state_machine_0_A_S4,
      In4(0) => top_npc_state_machine_0_B_S1,
      In5(0) => top_npc_state_machine_0_B_S2,
      In6(0) => top_npc_state_machine_0_B_S3,
      In7(0) => top_npc_state_machine_0_B_S4,
      In8(0) => top_npc_state_machine_0_C_S1,
      In9(0) => top_npc_state_machine_0_C_S2,
      dout(11 downto 0) => xlconcat_0_dout(11 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity Gates_imp_1G0NY44 is
  port (
    AXI4_Lite1_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite1_arready : out STD_LOGIC;
    AXI4_Lite1_arvalid : in STD_LOGIC;
    AXI4_Lite1_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite1_awready : out STD_LOGIC;
    AXI4_Lite1_awvalid : in STD_LOGIC;
    AXI4_Lite1_bready : in STD_LOGIC;
    AXI4_Lite1_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite1_bvalid : out STD_LOGIC;
    AXI4_Lite1_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite1_rready : in STD_LOGIC;
    AXI4_Lite1_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite1_rvalid : out STD_LOGIC;
    AXI4_Lite1_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite1_wready : out STD_LOGIC;
    AXI4_Lite1_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite1_wvalid : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_arready : out STD_LOGIC;
    AXI4_Lite_arvalid : in STD_LOGIC;
    AXI4_Lite_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_awready : out STD_LOGIC;
    AXI4_Lite_awvalid : in STD_LOGIC;
    AXI4_Lite_bready : in STD_LOGIC;
    AXI4_Lite_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_bvalid : out STD_LOGIC;
    AXI4_Lite_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_rready : in STD_LOGIC;
    AXI4_Lite_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_rvalid : out STD_LOGIC;
    AXI4_Lite_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_wready : out STD_LOGIC;
    AXI4_Lite_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_wvalid : in STD_LOGIC;
    Carrier_triangular_max : out STD_LOGIC_VECTOR ( 0 to 0 );
    Carrier_triangular_max_min : out STD_LOGIC_VECTOR ( 0 to 0 );
    Carrier_triangular_min : out STD_LOGIC_VECTOR ( 0 to 0 );
    Enable_Gate : in STD_LOGIC_VECTOR ( 0 to 0 );
    Gate_Signals_2L : out STD_LOGIC_VECTOR ( 5 downto 0 );
    S00_AXI_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S00_AXI_arlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    S00_AXI_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_arready : out STD_LOGIC;
    S00_AXI_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_arvalid : in STD_LOGIC;
    S00_AXI_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S00_AXI_awlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    S00_AXI_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awready : out STD_LOGIC;
    S00_AXI_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awvalid : in STD_LOGIC;
    S00_AXI_bready : in STD_LOGIC;
    S00_AXI_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_bvalid : out STD_LOGIC;
    S00_AXI_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    S00_AXI_rlast : out STD_LOGIC;
    S00_AXI_rready : in STD_LOGIC;
    S00_AXI_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_rvalid : out STD_LOGIC;
    S00_AXI_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    S00_AXI_wlast : in STD_LOGIC;
    S00_AXI_wready : out STD_LOGIC;
    S00_AXI_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_wvalid : in STD_LOGIC;
    s00_axi_aclk : in STD_LOGIC;
    s00_axi_aresetn : in STD_LOGIC
  );
end Gates_imp_1G0NY44;

architecture STRUCTURE of Gates_imp_1G0NY44 is
  component zusys_PWM_and_SS_control_V_0_2 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SS0_IN_External : in STD_LOGIC;
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    SS5_IN_External : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  end component zusys_PWM_and_SS_control_V_0_2;
  component zusys_ila_GateSignal_0 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe8 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe9 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe10 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe11 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe12 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe13 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe14 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe15 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe16 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe17 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe18 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe19 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe20 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe21 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe22 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe23 : in STD_LOGIC_VECTOR ( 24 downto 0 )
  );
  end component zusys_ila_GateSignal_0;
  component zusys_xlconstant_0_0 is
  port (
    dout : out STD_LOGIC_VECTOR ( 13 downto 0 )
  );
  end component zusys_xlconstant_0_0;
  component zusys_util_vector_logic_0_0 is
  port (
    Op1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Op2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Res : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_util_vector_logic_0_0;
  component zusys_Counter_f_sw_V2_ip_0_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    ss_in_0 : in STD_LOGIC;
    ss_in_1 : in STD_LOGIC;
    ss_in_2 : in STD_LOGIC;
    ss_in_3 : in STD_LOGIC;
    ss_in_4 : in STD_LOGIC;
    ss_in_5 : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    switchNumb : out STD_LOGIC_VECTOR ( 24 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  end component zusys_Counter_f_sw_V2_ip_0_0;
  component zusys_xlconcat_0_0 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 5 downto 0 )
  );
  end component zusys_xlconcat_0_0;
  component zusys_vio_Gates_2L_0 is
  port (
    clk : in STD_LOGIC;
    probe_out0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    probe_out5 : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_vio_Gates_2L_0;
  component zusys_uz_interlockDeadtime_0_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    S0 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    AXI4_ACLK : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    AXI4_AWID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_AWLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_AWSIZE : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_AWBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_AWLOCK : in STD_LOGIC;
    AXI4_AWCACHE : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_AWPROT : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_WLAST : in STD_LOGIC;
    AXI4_WVALID : in STD_LOGIC;
    AXI4_BREADY : in STD_LOGIC;
    AXI4_ARID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_ARLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_ARSIZE : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_ARBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_ARLOCK : in STD_LOGIC;
    AXI4_ARCACHE : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_ARPROT : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_ARVALID : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    s0_out : out STD_LOGIC;
    s1_out : out STD_LOGIC;
    s2_out : out STD_LOGIC;
    s3_out : out STD_LOGIC;
    s4_out : out STD_LOGIC;
    s5_out : out STD_LOGIC;
    enableFB : out STD_LOGIC;
    AXI4_AWREADY : out STD_LOGIC;
    AXI4_WREADY : out STD_LOGIC;
    AXI4_BID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_BVALID : out STD_LOGIC;
    AXI4_ARREADY : out STD_LOGIC;
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_RLAST : out STD_LOGIC;
    AXI4_RVALID : out STD_LOGIC
  );
  end component zusys_uz_interlockDeadtime_0_0;
  signal AXI4_Lite_1_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite_1_ARREADY : STD_LOGIC;
  signal AXI4_Lite_1_ARVALID : STD_LOGIC;
  signal AXI4_Lite_1_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite_1_AWREADY : STD_LOGIC;
  signal AXI4_Lite_1_AWVALID : STD_LOGIC;
  signal AXI4_Lite_1_BREADY : STD_LOGIC;
  signal AXI4_Lite_1_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite_1_BVALID : STD_LOGIC;
  signal AXI4_Lite_1_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite_1_RREADY : STD_LOGIC;
  signal AXI4_Lite_1_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite_1_RVALID : STD_LOGIC;
  signal AXI4_Lite_1_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite_1_WREADY : STD_LOGIC;
  signal AXI4_Lite_1_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI4_Lite_1_WVALID : STD_LOGIC;
  signal AXI4_Lite_ARESETN_1 : STD_LOGIC;
  signal Conn1_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal Conn1_ARREADY : STD_LOGIC;
  signal Conn1_ARVALID : STD_LOGIC;
  signal Conn1_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal Conn1_AWREADY : STD_LOGIC;
  signal Conn1_AWVALID : STD_LOGIC;
  signal Conn1_BREADY : STD_LOGIC;
  signal Conn1_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal Conn1_BVALID : STD_LOGIC;
  signal Conn1_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal Conn1_RREADY : STD_LOGIC;
  signal Conn1_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal Conn1_RVALID : STD_LOGIC;
  signal Conn1_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal Conn1_WREADY : STD_LOGIC;
  signal Conn1_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal Conn1_WVALID : STD_LOGIC;
  signal Counter_f_sw_V2_ip_0_switchNumb : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal FCS_SPMSM_Np1_i_V46_ip_0_ss_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal FCS_SPMSM_Np1_i_V46_ip_0_ss_1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal FCS_SPMSM_Np1_i_V46_ip_0_ss_2 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal FCS_SPMSM_Np1_i_V46_ip_0_ss_3 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal FCS_SPMSM_Np1_i_V46_ip_0_ss_4 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal FCS_SPMSM_Np1_i_V46_ip_0_ss_5 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal InterLock_Module_0_S0_OUT : STD_LOGIC;
  signal InterLock_Module_0_S1_OUT : STD_LOGIC;
  signal InterLock_Module_0_S2_OUT : STD_LOGIC;
  signal InterLock_Module_0_S3_OUT : STD_LOGIC;
  signal InterLock_Module_0_S4_OUT : STD_LOGIC;
  signal InterLock_Module_0_S5_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_PWM_enb_out : STD_LOGIC;
  signal PWM_and_SS_control_V_0_SS0_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_SS1_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_SS2_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_SS3_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_SS4_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_SS5_OUT : STD_LOGIC;
  signal PWM_and_SS_control_V_0_Triangular_Max : STD_LOGIC;
  signal PWM_and_SS_control_V_0_Triangular_Min : STD_LOGIC;
  signal S00_AXI_1_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal S00_AXI_1_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal S00_AXI_1_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal S00_AXI_1_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal S00_AXI_1_ARLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal S00_AXI_1_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal S00_AXI_1_ARREADY : STD_LOGIC;
  signal S00_AXI_1_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal S00_AXI_1_ARVALID : STD_LOGIC;
  signal S00_AXI_1_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal S00_AXI_1_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal S00_AXI_1_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal S00_AXI_1_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal S00_AXI_1_AWLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal S00_AXI_1_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal S00_AXI_1_AWREADY : STD_LOGIC;
  signal S00_AXI_1_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal S00_AXI_1_AWVALID : STD_LOGIC;
  signal S00_AXI_1_BREADY : STD_LOGIC;
  signal S00_AXI_1_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal S00_AXI_1_BVALID : STD_LOGIC;
  signal S00_AXI_1_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal S00_AXI_1_RLAST : STD_LOGIC;
  signal S00_AXI_1_RREADY : STD_LOGIC;
  signal S00_AXI_1_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal S00_AXI_1_RVALID : STD_LOGIC;
  signal S00_AXI_1_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal S00_AXI_1_WLAST : STD_LOGIC;
  signal S00_AXI_1_WREADY : STD_LOGIC;
  signal S00_AXI_1_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal S00_AXI_1_WVALID : STD_LOGIC;
  signal util_vector_logic_0_Res : STD_LOGIC_VECTOR ( 0 to 0 );
  signal xlconcat_0_dout : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal xlconstant_0_dout : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal xlslice_Enable_Inverter_Dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
  signal NLW_uz_interlockDeadtime_0_enableFB_UNCONNECTED : STD_LOGIC;
  signal NLW_uz_interlockDeadtime_0_AXI4_BID_UNCONNECTED : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal NLW_uz_interlockDeadtime_0_AXI4_RID_UNCONNECTED : STD_LOGIC_VECTOR ( 11 downto 0 );
begin
  AXI4_Lite1_arready <= Conn1_ARREADY;
  AXI4_Lite1_awready <= Conn1_AWREADY;
  AXI4_Lite1_bresp(1 downto 0) <= Conn1_BRESP(1 downto 0);
  AXI4_Lite1_bvalid <= Conn1_BVALID;
  AXI4_Lite1_rdata(31 downto 0) <= Conn1_RDATA(31 downto 0);
  AXI4_Lite1_rresp(1 downto 0) <= Conn1_RRESP(1 downto 0);
  AXI4_Lite1_rvalid <= Conn1_RVALID;
  AXI4_Lite1_wready <= Conn1_WREADY;
  AXI4_Lite_1_ARADDR(15 downto 0) <= AXI4_Lite_araddr(15 downto 0);
  AXI4_Lite_1_ARVALID <= AXI4_Lite_arvalid;
  AXI4_Lite_1_AWADDR(15 downto 0) <= AXI4_Lite_awaddr(15 downto 0);
  AXI4_Lite_1_AWVALID <= AXI4_Lite_awvalid;
  AXI4_Lite_1_BREADY <= AXI4_Lite_bready;
  AXI4_Lite_1_RREADY <= AXI4_Lite_rready;
  AXI4_Lite_1_WDATA(31 downto 0) <= AXI4_Lite_wdata(31 downto 0);
  AXI4_Lite_1_WSTRB(3 downto 0) <= AXI4_Lite_wstrb(3 downto 0);
  AXI4_Lite_1_WVALID <= AXI4_Lite_wvalid;
  AXI4_Lite_ARESETN_1 <= AXI4_Lite_ARESETN;
  AXI4_Lite_arready <= AXI4_Lite_1_ARREADY;
  AXI4_Lite_awready <= AXI4_Lite_1_AWREADY;
  AXI4_Lite_bresp(1 downto 0) <= AXI4_Lite_1_BRESP(1 downto 0);
  AXI4_Lite_bvalid <= AXI4_Lite_1_BVALID;
  AXI4_Lite_rdata(31 downto 0) <= AXI4_Lite_1_RDATA(31 downto 0);
  AXI4_Lite_rresp(1 downto 0) <= AXI4_Lite_1_RRESP(1 downto 0);
  AXI4_Lite_rvalid <= AXI4_Lite_1_RVALID;
  AXI4_Lite_wready <= AXI4_Lite_1_WREADY;
  Carrier_triangular_max(0) <= PWM_and_SS_control_V_0_Triangular_Max;
  Carrier_triangular_max_min(0) <= util_vector_logic_0_Res(0);
  Carrier_triangular_min(0) <= PWM_and_SS_control_V_0_Triangular_Min;
  Conn1_ARADDR(15 downto 0) <= AXI4_Lite1_araddr(15 downto 0);
  Conn1_ARVALID <= AXI4_Lite1_arvalid;
  Conn1_AWADDR(15 downto 0) <= AXI4_Lite1_awaddr(15 downto 0);
  Conn1_AWVALID <= AXI4_Lite1_awvalid;
  Conn1_BREADY <= AXI4_Lite1_bready;
  Conn1_RREADY <= AXI4_Lite1_rready;
  Conn1_WDATA(31 downto 0) <= AXI4_Lite1_wdata(31 downto 0);
  Conn1_WSTRB(3 downto 0) <= AXI4_Lite1_wstrb(3 downto 0);
  Conn1_WVALID <= AXI4_Lite1_wvalid;
  Gate_Signals_2L(5 downto 0) <= xlconcat_0_dout(5 downto 0);
  S00_AXI_1_ARADDR(15 downto 0) <= S00_AXI_araddr(15 downto 0);
  S00_AXI_1_ARBURST(1 downto 0) <= S00_AXI_arburst(1 downto 0);
  S00_AXI_1_ARCACHE(3 downto 0) <= S00_AXI_arcache(3 downto 0);
  S00_AXI_1_ARLEN(7 downto 0) <= S00_AXI_arlen(7 downto 0);
  S00_AXI_1_ARLOCK(0) <= S00_AXI_arlock(0);
  S00_AXI_1_ARPROT(2 downto 0) <= S00_AXI_arprot(2 downto 0);
  S00_AXI_1_ARSIZE(2 downto 0) <= S00_AXI_arsize(2 downto 0);
  S00_AXI_1_ARVALID <= S00_AXI_arvalid;
  S00_AXI_1_AWADDR(15 downto 0) <= S00_AXI_awaddr(15 downto 0);
  S00_AXI_1_AWBURST(1 downto 0) <= S00_AXI_awburst(1 downto 0);
  S00_AXI_1_AWCACHE(3 downto 0) <= S00_AXI_awcache(3 downto 0);
  S00_AXI_1_AWLEN(7 downto 0) <= S00_AXI_awlen(7 downto 0);
  S00_AXI_1_AWLOCK(0) <= S00_AXI_awlock(0);
  S00_AXI_1_AWPROT(2 downto 0) <= S00_AXI_awprot(2 downto 0);
  S00_AXI_1_AWSIZE(2 downto 0) <= S00_AXI_awsize(2 downto 0);
  S00_AXI_1_AWVALID <= S00_AXI_awvalid;
  S00_AXI_1_BREADY <= S00_AXI_bready;
  S00_AXI_1_RREADY <= S00_AXI_rready;
  S00_AXI_1_WDATA(31 downto 0) <= S00_AXI_wdata(31 downto 0);
  S00_AXI_1_WLAST <= S00_AXI_wlast;
  S00_AXI_1_WSTRB(3 downto 0) <= S00_AXI_wstrb(3 downto 0);
  S00_AXI_1_WVALID <= S00_AXI_wvalid;
  S00_AXI_arready <= S00_AXI_1_ARREADY;
  S00_AXI_awready <= S00_AXI_1_AWREADY;
  S00_AXI_bresp(1 downto 0) <= S00_AXI_1_BRESP(1 downto 0);
  S00_AXI_bvalid <= S00_AXI_1_BVALID;
  S00_AXI_rdata(31 downto 0) <= S00_AXI_1_RDATA(31 downto 0);
  S00_AXI_rlast <= S00_AXI_1_RLAST;
  S00_AXI_rresp(1 downto 0) <= S00_AXI_1_RRESP(1 downto 0);
  S00_AXI_rvalid <= S00_AXI_1_RVALID;
  S00_AXI_wready <= S00_AXI_1_WREADY;
  xlslice_Enable_Inverter_Dout(0) <= Enable_Gate(0);
  zynq_ultra_ps_e_0_pl_clk1 <= AXI4_Lite_ACLK;
Counter_f_sw_V2_ip_0: component zusys_Counter_f_sw_V2_ip_0_0
     port map (
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARADDR(15 downto 0) => Conn1_ARADDR(15 downto 0),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN_1,
      AXI4_Lite_ARREADY => Conn1_ARREADY,
      AXI4_Lite_ARVALID => Conn1_ARVALID,
      AXI4_Lite_AWADDR(15 downto 0) => Conn1_AWADDR(15 downto 0),
      AXI4_Lite_AWREADY => Conn1_AWREADY,
      AXI4_Lite_AWVALID => Conn1_AWVALID,
      AXI4_Lite_BREADY => Conn1_BREADY,
      AXI4_Lite_BRESP(1 downto 0) => Conn1_BRESP(1 downto 0),
      AXI4_Lite_BVALID => Conn1_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => Conn1_RDATA(31 downto 0),
      AXI4_Lite_RREADY => Conn1_RREADY,
      AXI4_Lite_RRESP(1 downto 0) => Conn1_RRESP(1 downto 0),
      AXI4_Lite_RVALID => Conn1_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => Conn1_WDATA(31 downto 0),
      AXI4_Lite_WREADY => Conn1_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => Conn1_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => Conn1_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => AXI4_Lite_ARESETN_1,
      ss_in_0 => InterLock_Module_0_S0_OUT,
      ss_in_1 => InterLock_Module_0_S1_OUT,
      ss_in_2 => InterLock_Module_0_S2_OUT,
      ss_in_3 => InterLock_Module_0_S3_OUT,
      ss_in_4 => InterLock_Module_0_S4_OUT,
      ss_in_5 => InterLock_Module_0_S5_OUT,
      switchNumb(24 downto 0) => Counter_f_sw_V2_ip_0_switchNumb(24 downto 0)
    );
PWM_and_SS_control_V_0: component zusys_PWM_and_SS_control_V_0_2
     port map (
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARADDR(15 downto 0) => AXI4_Lite_1_ARADDR(15 downto 0),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN_1,
      AXI4_Lite_ARREADY => AXI4_Lite_1_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_1_ARVALID,
      AXI4_Lite_AWADDR(15 downto 0) => AXI4_Lite_1_AWADDR(15 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_1_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_1_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_1_BREADY,
      AXI4_Lite_BRESP(1 downto 0) => AXI4_Lite_1_BRESP(1 downto 0),
      AXI4_Lite_BVALID => AXI4_Lite_1_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => AXI4_Lite_1_RDATA(31 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_1_RREADY,
      AXI4_Lite_RRESP(1 downto 0) => AXI4_Lite_1_RRESP(1 downto 0),
      AXI4_Lite_RVALID => AXI4_Lite_1_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => AXI4_Lite_1_WDATA(31 downto 0),
      AXI4_Lite_WREADY => AXI4_Lite_1_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_1_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_1_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => AXI4_Lite_ARESETN_1,
      PWM_enb_out => PWM_and_SS_control_V_0_PWM_enb_out,
      SS0_IN_External => FCS_SPMSM_Np1_i_V46_ip_0_ss_0(0),
      SS0_OUT => PWM_and_SS_control_V_0_SS0_OUT,
      SS1_IN_External => FCS_SPMSM_Np1_i_V46_ip_0_ss_1(0),
      SS1_OUT => PWM_and_SS_control_V_0_SS1_OUT,
      SS2_IN_External => FCS_SPMSM_Np1_i_V46_ip_0_ss_2(0),
      SS2_OUT => PWM_and_SS_control_V_0_SS2_OUT,
      SS3_IN_External => FCS_SPMSM_Np1_i_V46_ip_0_ss_3(0),
      SS3_OUT => PWM_and_SS_control_V_0_SS3_OUT,
      SS4_IN_External => FCS_SPMSM_Np1_i_V46_ip_0_ss_4(0),
      SS4_OUT => PWM_and_SS_control_V_0_SS4_OUT,
      SS5_IN_External => FCS_SPMSM_Np1_i_V46_ip_0_ss_5(0),
      SS5_OUT => PWM_and_SS_control_V_0_SS5_OUT,
      Triangular_Max => PWM_and_SS_control_V_0_Triangular_Max,
      Triangular_Min => PWM_and_SS_control_V_0_Triangular_Min,
      m_u1_norm(13 downto 0) => xlconstant_0_dout(13 downto 0),
      m_u2_norm(13 downto 0) => xlconstant_0_dout(13 downto 0),
      m_u3_norm(13 downto 0) => xlconstant_0_dout(13 downto 0)
    );
ila_GateSignal: component zusys_ila_GateSignal_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_0(0),
      probe1(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_1(0),
      probe10(0) => InterLock_Module_0_S4_OUT,
      probe11(0) => InterLock_Module_0_S5_OUT,
      probe12(0) => xlslice_Enable_Inverter_Dout(0),
      probe13(0) => util_vector_logic_0_Res(0),
      probe14(0) => PWM_and_SS_control_V_0_SS0_OUT,
      probe15(0) => PWM_and_SS_control_V_0_SS1_OUT,
      probe16(0) => PWM_and_SS_control_V_0_SS2_OUT,
      probe17(0) => PWM_and_SS_control_V_0_SS3_OUT,
      probe18(0) => PWM_and_SS_control_V_0_SS4_OUT,
      probe19(0) => PWM_and_SS_control_V_0_SS5_OUT,
      probe2(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_2(0),
      probe20(0) => PWM_and_SS_control_V_0_PWM_enb_out,
      probe21(0) => PWM_and_SS_control_V_0_Triangular_Max,
      probe22(0) => PWM_and_SS_control_V_0_Triangular_Min,
      probe23(24 downto 0) => Counter_f_sw_V2_ip_0_switchNumb(24 downto 0),
      probe3(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_3(0),
      probe4(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_4(0),
      probe5(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_5(0),
      probe6(0) => InterLock_Module_0_S0_OUT,
      probe7(0) => InterLock_Module_0_S1_OUT,
      probe8(0) => InterLock_Module_0_S2_OUT,
      probe9(0) => InterLock_Module_0_S3_OUT
    );
util_vector_logic_0: component zusys_util_vector_logic_0_0
     port map (
      Op1(0) => PWM_and_SS_control_V_0_Triangular_Max,
      Op2(0) => PWM_and_SS_control_V_0_Triangular_Min,
      Res(0) => util_vector_logic_0_Res(0)
    );
uz_interlockDeadtime_0: component zusys_uz_interlockDeadtime_0_0
     port map (
      AXI4_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_ARADDR(15 downto 0) => S00_AXI_1_ARADDR(15 downto 0),
      AXI4_ARBURST(1 downto 0) => S00_AXI_1_ARBURST(1 downto 0),
      AXI4_ARCACHE(3 downto 0) => S00_AXI_1_ARCACHE(3 downto 0),
      AXI4_ARESETN => AXI4_Lite_ARESETN_1,
      AXI4_ARID(11 downto 0) => B"000000000000",
      AXI4_ARLEN(7 downto 0) => S00_AXI_1_ARLEN(7 downto 0),
      AXI4_ARLOCK => S00_AXI_1_ARLOCK(0),
      AXI4_ARPROT(2 downto 0) => S00_AXI_1_ARPROT(2 downto 0),
      AXI4_ARREADY => S00_AXI_1_ARREADY,
      AXI4_ARSIZE(2 downto 0) => S00_AXI_1_ARSIZE(2 downto 0),
      AXI4_ARVALID => S00_AXI_1_ARVALID,
      AXI4_AWADDR(15 downto 0) => S00_AXI_1_AWADDR(15 downto 0),
      AXI4_AWBURST(1 downto 0) => S00_AXI_1_AWBURST(1 downto 0),
      AXI4_AWCACHE(3 downto 0) => S00_AXI_1_AWCACHE(3 downto 0),
      AXI4_AWID(11 downto 0) => B"000000000000",
      AXI4_AWLEN(7 downto 0) => S00_AXI_1_AWLEN(7 downto 0),
      AXI4_AWLOCK => S00_AXI_1_AWLOCK(0),
      AXI4_AWPROT(2 downto 0) => S00_AXI_1_AWPROT(2 downto 0),
      AXI4_AWREADY => S00_AXI_1_AWREADY,
      AXI4_AWSIZE(2 downto 0) => S00_AXI_1_AWSIZE(2 downto 0),
      AXI4_AWVALID => S00_AXI_1_AWVALID,
      AXI4_BID(11 downto 0) => NLW_uz_interlockDeadtime_0_AXI4_BID_UNCONNECTED(11 downto 0),
      AXI4_BREADY => S00_AXI_1_BREADY,
      AXI4_BRESP(1 downto 0) => S00_AXI_1_BRESP(1 downto 0),
      AXI4_BVALID => S00_AXI_1_BVALID,
      AXI4_RDATA(31 downto 0) => S00_AXI_1_RDATA(31 downto 0),
      AXI4_RID(11 downto 0) => NLW_uz_interlockDeadtime_0_AXI4_RID_UNCONNECTED(11 downto 0),
      AXI4_RLAST => S00_AXI_1_RLAST,
      AXI4_RREADY => S00_AXI_1_RREADY,
      AXI4_RRESP(1 downto 0) => S00_AXI_1_RRESP(1 downto 0),
      AXI4_RVALID => S00_AXI_1_RVALID,
      AXI4_WDATA(31 downto 0) => S00_AXI_1_WDATA(31 downto 0),
      AXI4_WLAST => S00_AXI_1_WLAST,
      AXI4_WREADY => S00_AXI_1_WREADY,
      AXI4_WSTRB(3 downto 0) => S00_AXI_1_WSTRB(3 downto 0),
      AXI4_WVALID => S00_AXI_1_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => AXI4_Lite_ARESETN_1,
      S0 => PWM_and_SS_control_V_0_SS0_OUT,
      S1 => PWM_and_SS_control_V_0_SS1_OUT,
      S2 => PWM_and_SS_control_V_0_SS2_OUT,
      S3 => PWM_and_SS_control_V_0_SS3_OUT,
      S4 => PWM_and_SS_control_V_0_SS4_OUT,
      S5 => PWM_and_SS_control_V_0_SS5_OUT,
      enableFB => NLW_uz_interlockDeadtime_0_enableFB_UNCONNECTED,
      s0_out => InterLock_Module_0_S0_OUT,
      s1_out => InterLock_Module_0_S1_OUT,
      s2_out => InterLock_Module_0_S2_OUT,
      s3_out => InterLock_Module_0_S3_OUT,
      s4_out => InterLock_Module_0_S4_OUT,
      s5_out => InterLock_Module_0_S5_OUT
    );
vio_Gates_2L: component zusys_vio_Gates_2L_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_out0(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_0(0),
      probe_out1(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_1(0),
      probe_out2(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_2(0),
      probe_out3(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_3(0),
      probe_out4(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_4(0),
      probe_out5(0) => FCS_SPMSM_Np1_i_V46_ip_0_ss_5(0)
    );
xlconcat_0: component zusys_xlconcat_0_0
     port map (
      In0(0) => InterLock_Module_0_S0_OUT,
      In1(0) => InterLock_Module_0_S1_OUT,
      In2(0) => InterLock_Module_0_S2_OUT,
      In3(0) => InterLock_Module_0_S3_OUT,
      In4(0) => InterLock_Module_0_S4_OUT,
      In5(0) => InterLock_Module_0_S5_OUT,
      dout(5 downto 0) => xlconcat_0_dout(5 downto 0)
    );
xlconstant_0: component zusys_xlconstant_0_0
     port map (
      dout(13 downto 0) => xlconstant_0_dout(13 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity Interrupt_imp_CGQCLG is
  port (
    AXI4_Lite_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_arready : out STD_LOGIC;
    AXI4_Lite_arvalid : in STD_LOGIC;
    AXI4_Lite_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_awready : out STD_LOGIC;
    AXI4_Lite_awvalid : in STD_LOGIC;
    AXI4_Lite_bready : in STD_LOGIC;
    AXI4_Lite_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_bvalid : out STD_LOGIC;
    AXI4_Lite_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_rready : in STD_LOGIC;
    AXI4_Lite_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_rvalid : out STD_LOGIC;
    AXI4_Lite_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_wready : out STD_LOGIC;
    AXI4_Lite_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_wvalid : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    Interrupt0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    Interrupt_vector : out STD_LOGIC_VECTOR ( 7 downto 0 );
    S_AXI_araddr : in STD_LOGIC_VECTOR ( 4 downto 0 );
    S_AXI_arready : out STD_LOGIC;
    S_AXI_arvalid : in STD_LOGIC;
    S_AXI_awaddr : in STD_LOGIC_VECTOR ( 4 downto 0 );
    S_AXI_awready : out STD_LOGIC;
    S_AXI_awvalid : in STD_LOGIC;
    S_AXI_bready : in STD_LOGIC;
    S_AXI_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S_AXI_bvalid : out STD_LOGIC;
    S_AXI_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    S_AXI_rready : in STD_LOGIC;
    S_AXI_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S_AXI_rvalid : out STD_LOGIC;
    S_AXI_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    S_AXI_wready : out STD_LOGIC;
    S_AXI_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S_AXI_wvalid : in STD_LOGIC;
    clk : in STD_LOGIC;
    trigger_converesions : out STD_LOGIC
  );
end Interrupt_imp_CGQCLG;

architecture STRUCTURE of Interrupt_imp_CGQCLG is
  component zusys_Concat_interrupts_0 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    In7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  end component zusys_Concat_interrupts_0;
  component zusys_Trigger_f_cc_0 is
  port (
    capturetrig0 : in STD_LOGIC;
    capturetrig1 : in STD_LOGIC;
    generateout0 : out STD_LOGIC;
    generateout1 : out STD_LOGIC;
    pwm0 : out STD_LOGIC;
    interrupt : out STD_LOGIC;
    freeze : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC
  );
  end component zusys_Trigger_f_cc_0;
  component zusys_ila_0_2 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe8 : in STD_LOGIC_VECTOR ( 3 downto 0 );
    probe9 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_ila_0_2;
  component zusys_adc_delay_0 is
  port (
    clk : in STD_LOGIC;
    probe_out0 : out STD_LOGIC_VECTOR ( 10 downto 0 )
  );
  end component zusys_adc_delay_0;
  component zusys_delay_trigger_0_0 is
  port (
    clk : in STD_LOGIC;
    delay_cycles : in STD_LOGIC_VECTOR ( 10 downto 0 );
    a_in : in STD_LOGIC;
    a_out : out STD_LOGIC
  );
  end component zusys_delay_trigger_0_0;
  component zusys_vio_interrupt_0 is
  port (
    clk : in STD_LOGIC;
    probe_out0 : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_vio_interrupt_0;
  component zusys_mux_axi_ip_1_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    interrupts_in : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    interrupt_out_adc : out STD_LOGIC;
    interrupt_out_isr : out STD_LOGIC_VECTOR ( 7 downto 0 );
    select_out : out STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  end component zusys_mux_axi_ip_1_0;
  signal AXI4_Lite_1_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite_1_ARREADY : STD_LOGIC;
  signal AXI4_Lite_1_ARVALID : STD_LOGIC;
  signal AXI4_Lite_1_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite_1_AWREADY : STD_LOGIC;
  signal AXI4_Lite_1_AWVALID : STD_LOGIC;
  signal AXI4_Lite_1_BREADY : STD_LOGIC;
  signal AXI4_Lite_1_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite_1_BVALID : STD_LOGIC;
  signal AXI4_Lite_1_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite_1_RREADY : STD_LOGIC;
  signal AXI4_Lite_1_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite_1_RVALID : STD_LOGIC;
  signal AXI4_Lite_1_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite_1_WREADY : STD_LOGIC;
  signal AXI4_Lite_1_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI4_Lite_1_WVALID : STD_LOGIC;
  signal Concat_interrupts_dout : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal Gates_3L_Interrupt_Center : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_3L_Interrupt_Start : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_3L_Interrupt_Start_Center : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_Carrier_triangular_max1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_Carrier_triangular_max_min : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_Carrier_triangular_min1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Trigger_f_cc_interrupt : STD_LOGIC;
  signal adc_delay_probe_out0 : STD_LOGIC_VECTOR ( 10 downto 0 );
  signal delay_trigger_0_a_out : STD_LOGIC;
  signal mux_axi_ip_1_interrupt_out_adc : STD_LOGIC;
  signal mux_axi_ip_1_interrupt_out_isr : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal mux_axi_ip_1_select_out : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal proc_sys_reset_1_peripheral_aresetn : STD_LOGIC;
  signal smartconnect_0_M11_AXI_ARADDR : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal smartconnect_0_M11_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_AWADDR : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal smartconnect_0_M11_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M11_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M11_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M11_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M11_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M11_AXI_WVALID : STD_LOGIC;
  signal vio_0_probe_out0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
  signal NLW_Trigger_f_cc_generateout0_UNCONNECTED : STD_LOGIC;
  signal NLW_Trigger_f_cc_generateout1_UNCONNECTED : STD_LOGIC;
  signal NLW_Trigger_f_cc_pwm0_UNCONNECTED : STD_LOGIC;
begin
  AXI4_Lite_1_ARADDR(15 downto 0) <= AXI4_Lite_araddr(15 downto 0);
  AXI4_Lite_1_ARVALID <= AXI4_Lite_arvalid;
  AXI4_Lite_1_AWADDR(15 downto 0) <= AXI4_Lite_awaddr(15 downto 0);
  AXI4_Lite_1_AWVALID <= AXI4_Lite_awvalid;
  AXI4_Lite_1_BREADY <= AXI4_Lite_bready;
  AXI4_Lite_1_RREADY <= AXI4_Lite_rready;
  AXI4_Lite_1_WDATA(31 downto 0) <= AXI4_Lite_wdata(31 downto 0);
  AXI4_Lite_1_WSTRB(3 downto 0) <= AXI4_Lite_wstrb(3 downto 0);
  AXI4_Lite_1_WVALID <= AXI4_Lite_wvalid;
  AXI4_Lite_arready <= AXI4_Lite_1_ARREADY;
  AXI4_Lite_awready <= AXI4_Lite_1_AWREADY;
  AXI4_Lite_bresp(1 downto 0) <= AXI4_Lite_1_BRESP(1 downto 0);
  AXI4_Lite_bvalid <= AXI4_Lite_1_BVALID;
  AXI4_Lite_rdata(31 downto 0) <= AXI4_Lite_1_RDATA(31 downto 0);
  AXI4_Lite_rresp(1 downto 0) <= AXI4_Lite_1_RRESP(1 downto 0);
  AXI4_Lite_rvalid <= AXI4_Lite_1_RVALID;
  AXI4_Lite_wready <= AXI4_Lite_1_WREADY;
  Gates_3L_Interrupt_Center(0) <= Interrupt5(0);
  Gates_3L_Interrupt_Start(0) <= Interrupt4(0);
  Gates_3L_Interrupt_Start_Center(0) <= Interrupt3(0);
  Gates_Carrier_triangular_max1(0) <= Interrupt2(0);
  Gates_Carrier_triangular_max_min(0) <= Interrupt0(0);
  Gates_Carrier_triangular_min1(0) <= Interrupt1(0);
  Interrupt_vector(7 downto 0) <= mux_axi_ip_1_interrupt_out_isr(7 downto 0);
  S_AXI_arready <= smartconnect_0_M11_AXI_ARREADY;
  S_AXI_awready <= smartconnect_0_M11_AXI_AWREADY;
  S_AXI_bresp(1 downto 0) <= smartconnect_0_M11_AXI_BRESP(1 downto 0);
  S_AXI_bvalid <= smartconnect_0_M11_AXI_BVALID;
  S_AXI_rdata(31 downto 0) <= smartconnect_0_M11_AXI_RDATA(31 downto 0);
  S_AXI_rresp(1 downto 0) <= smartconnect_0_M11_AXI_RRESP(1 downto 0);
  S_AXI_rvalid <= smartconnect_0_M11_AXI_RVALID;
  S_AXI_wready <= smartconnect_0_M11_AXI_WREADY;
  proc_sys_reset_1_peripheral_aresetn <= IPCORE_RESETN;
  smartconnect_0_M11_AXI_ARADDR(4 downto 0) <= S_AXI_araddr(4 downto 0);
  smartconnect_0_M11_AXI_ARVALID <= S_AXI_arvalid;
  smartconnect_0_M11_AXI_AWADDR(4 downto 0) <= S_AXI_awaddr(4 downto 0);
  smartconnect_0_M11_AXI_AWVALID <= S_AXI_awvalid;
  smartconnect_0_M11_AXI_BREADY <= S_AXI_bready;
  smartconnect_0_M11_AXI_RREADY <= S_AXI_rready;
  smartconnect_0_M11_AXI_WDATA(31 downto 0) <= S_AXI_wdata(31 downto 0);
  smartconnect_0_M11_AXI_WSTRB(3 downto 0) <= S_AXI_wstrb(3 downto 0);
  smartconnect_0_M11_AXI_WVALID <= S_AXI_wvalid;
  trigger_converesions <= delay_trigger_0_a_out;
  zynq_ultra_ps_e_0_pl_clk1 <= clk;
Concat_interrupts: component zusys_Concat_interrupts_0
     port map (
      In0(0) => Gates_Carrier_triangular_max_min(0),
      In1(0) => Gates_Carrier_triangular_min1(0),
      In2(0) => Gates_Carrier_triangular_max1(0),
      In3(0) => Gates_3L_Interrupt_Start_Center(0),
      In4(0) => Gates_3L_Interrupt_Start(0),
      In5(0) => Gates_3L_Interrupt_Center(0),
      In6(0) => Trigger_f_cc_interrupt,
      In7(0) => vio_0_probe_out0(0),
      dout(7 downto 0) => Concat_interrupts_dout(7 downto 0)
    );
Trigger_f_cc: component zusys_Trigger_f_cc_0
     port map (
      capturetrig0 => '0',
      capturetrig1 => '0',
      freeze => '0',
      generateout0 => NLW_Trigger_f_cc_generateout0_UNCONNECTED,
      generateout1 => NLW_Trigger_f_cc_generateout1_UNCONNECTED,
      interrupt => Trigger_f_cc_interrupt,
      pwm0 => NLW_Trigger_f_cc_pwm0_UNCONNECTED,
      s_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      s_axi_araddr(4 downto 0) => smartconnect_0_M11_AXI_ARADDR(4 downto 0),
      s_axi_aresetn => proc_sys_reset_1_peripheral_aresetn,
      s_axi_arready => smartconnect_0_M11_AXI_ARREADY,
      s_axi_arvalid => smartconnect_0_M11_AXI_ARVALID,
      s_axi_awaddr(4 downto 0) => smartconnect_0_M11_AXI_AWADDR(4 downto 0),
      s_axi_awready => smartconnect_0_M11_AXI_AWREADY,
      s_axi_awvalid => smartconnect_0_M11_AXI_AWVALID,
      s_axi_bready => smartconnect_0_M11_AXI_BREADY,
      s_axi_bresp(1 downto 0) => smartconnect_0_M11_AXI_BRESP(1 downto 0),
      s_axi_bvalid => smartconnect_0_M11_AXI_BVALID,
      s_axi_rdata(31 downto 0) => smartconnect_0_M11_AXI_RDATA(31 downto 0),
      s_axi_rready => smartconnect_0_M11_AXI_RREADY,
      s_axi_rresp(1 downto 0) => smartconnect_0_M11_AXI_RRESP(1 downto 0),
      s_axi_rvalid => smartconnect_0_M11_AXI_RVALID,
      s_axi_wdata(31 downto 0) => smartconnect_0_M11_AXI_WDATA(31 downto 0),
      s_axi_wready => smartconnect_0_M11_AXI_WREADY,
      s_axi_wstrb(3 downto 0) => smartconnect_0_M11_AXI_WSTRB(3 downto 0),
      s_axi_wvalid => smartconnect_0_M11_AXI_WVALID
    );
adc_delay: component zusys_adc_delay_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_out0(10 downto 0) => adc_delay_probe_out0(10 downto 0)
    );
delay_trigger_0: component zusys_delay_trigger_0_0
     port map (
      a_in => mux_axi_ip_1_interrupt_out_adc,
      a_out => delay_trigger_0_a_out,
      clk => zynq_ultra_ps_e_0_pl_clk1,
      delay_cycles(10 downto 0) => adc_delay_probe_out0(10 downto 0)
    );
ila_0: component zusys_ila_0_2
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(0) => Gates_Carrier_triangular_max_min(0),
      probe1(0) => Gates_Carrier_triangular_min1(0),
      probe2(0) => Gates_Carrier_triangular_max1(0),
      probe3(0) => Gates_3L_Interrupt_Start_Center(0),
      probe4(0) => Gates_3L_Interrupt_Start(0),
      probe5(0) => Gates_3L_Interrupt_Center(0),
      probe6(0) => Trigger_f_cc_interrupt,
      probe7(0) => mux_axi_ip_1_interrupt_out_adc,
      probe8(3 downto 0) => mux_axi_ip_1_select_out(3 downto 0),
      probe9(0) => delay_trigger_0_a_out
    );
mux_axi_ip_1: component zusys_mux_axi_ip_1_0
     port map (
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARADDR(15 downto 0) => AXI4_Lite_1_ARADDR(15 downto 0),
      AXI4_Lite_ARESETN => proc_sys_reset_1_peripheral_aresetn,
      AXI4_Lite_ARREADY => AXI4_Lite_1_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_1_ARVALID,
      AXI4_Lite_AWADDR(15 downto 0) => AXI4_Lite_1_AWADDR(15 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_1_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_1_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_1_BREADY,
      AXI4_Lite_BRESP(1 downto 0) => AXI4_Lite_1_BRESP(1 downto 0),
      AXI4_Lite_BVALID => AXI4_Lite_1_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => AXI4_Lite_1_RDATA(31 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_1_RREADY,
      AXI4_Lite_RRESP(1 downto 0) => AXI4_Lite_1_RRESP(1 downto 0),
      AXI4_Lite_RVALID => AXI4_Lite_1_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => AXI4_Lite_1_WDATA(31 downto 0),
      AXI4_Lite_WREADY => AXI4_Lite_1_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_1_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_1_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => proc_sys_reset_1_peripheral_aresetn,
      interrupt_out_adc => mux_axi_ip_1_interrupt_out_adc,
      interrupt_out_isr(7 downto 0) => mux_axi_ip_1_interrupt_out_isr(7 downto 0),
      interrupts_in(7 downto 0) => Concat_interrupts_dout(7 downto 0),
      select_out(3 downto 0) => mux_axi_ip_1_select_out(3 downto 0)
    );
vio_interrupt: component zusys_vio_interrupt_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_out0(0) => vio_0_probe_out0(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity adc_debug_imp_76DXHS is
  port (
    Din : in STD_LOGIC_VECTOR ( 127 downto 0 );
    Din1 : in STD_LOGIC_VECTOR ( 279 downto 0 );
    clk : in STD_LOGIC;
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 31 downto 0 );
    probe7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    pu_valid : in STD_LOGIC
  );
end adc_debug_imp_76DXHS;

architecture STRUCTURE of adc_debug_imp_76DXHS is
  component zusys_xlslice_2_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 127 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );
  end component zusys_xlslice_2_0;
  component zusys_ila_0_3 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 15 downto 0 );
    probe1 : in STD_LOGIC_VECTOR ( 15 downto 0 );
    probe2 : in STD_LOGIC_VECTOR ( 15 downto 0 );
    probe3 : in STD_LOGIC_VECTOR ( 15 downto 0 );
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 31 downto 0 );
    probe7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe8 : in STD_LOGIC_VECTOR ( 34 downto 0 );
    probe9 : in STD_LOGIC_VECTOR ( 34 downto 0 );
    probe10 : in STD_LOGIC_VECTOR ( 34 downto 0 );
    probe11 : in STD_LOGIC_VECTOR ( 34 downto 0 )
  );
  end component zusys_ila_0_3;
  component zusys_xlslice_3_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 127 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );
  end component zusys_xlslice_3_0;
  component zusys_xlslice_4_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 127 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );
  end component zusys_xlslice_4_0;
  component zusys_xlslice_5_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 127 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );
  end component zusys_xlslice_5_0;
  component zusys_xlslice_7_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 34 downto 0 )
  );
  end component zusys_xlslice_7_0;
  component zusys_xlslice_8_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 34 downto 0 )
  );
  end component zusys_xlslice_8_0;
  component zusys_xlslice_9_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 34 downto 0 )
  );
  end component zusys_xlslice_9_0;
  component zusys_xlslice_6_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 34 downto 0 )
  );
  end component zusys_xlslice_6_0;
  signal A1_ADC_LTC2311_SAMPLE_COUNTER : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal A1_ADC_LTC2311_SI_VALID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal A1_ADC_LTC2311_SI_VALUE : STD_LOGIC_VECTOR ( 279 downto 0 );
  signal ADC_LTC2311_1_RAW_VALUE : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal Current_Valid_0_Dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Interrupt_muxed : STD_LOGIC_VECTOR ( 0 to 0 );
  signal pu_valid_1 : STD_LOGIC;
  signal xlslice_2_Dout : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal xlslice_3_Dout : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal xlslice_4_Dout : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal xlslice_5_Dout : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal xlslice_6_Dout : STD_LOGIC_VECTOR ( 34 downto 0 );
  signal xlslice_7_Dout : STD_LOGIC_VECTOR ( 34 downto 0 );
  signal xlslice_8_Dout : STD_LOGIC_VECTOR ( 34 downto 0 );
  signal xlslice_9_Dout : STD_LOGIC_VECTOR ( 34 downto 0 );
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
begin
  A1_ADC_LTC2311_SAMPLE_COUNTER(31 downto 0) <= probe6(31 downto 0);
  A1_ADC_LTC2311_SI_VALID(0) <= probe7(0);
  A1_ADC_LTC2311_SI_VALUE(279 downto 0) <= Din1(279 downto 0);
  ADC_LTC2311_1_RAW_VALUE(127 downto 0) <= Din(127 downto 0);
  Current_Valid_0_Dout(0) <= probe4(0);
  Interrupt_muxed(0) <= probe5(0);
  pu_valid_1 <= pu_valid;
  zynq_ultra_ps_e_0_pl_clk1 <= clk;
ila_0: component zusys_ila_0_3
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(15 downto 0) => xlslice_2_Dout(15 downto 0),
      probe1(15 downto 0) => xlslice_3_Dout(15 downto 0),
      probe10(34 downto 0) => xlslice_8_Dout(34 downto 0),
      probe11(34 downto 0) => xlslice_9_Dout(34 downto 0),
      probe2(15 downto 0) => xlslice_4_Dout(15 downto 0),
      probe3(15 downto 0) => xlslice_5_Dout(15 downto 0),
      probe4(0) => Current_Valid_0_Dout(0),
      probe5(0) => Interrupt_muxed(0),
      probe6(31 downto 0) => A1_ADC_LTC2311_SAMPLE_COUNTER(31 downto 0),
      probe7(0) => A1_ADC_LTC2311_SI_VALID(0),
      probe8(34 downto 0) => xlslice_7_Dout(34 downto 0),
      probe9(34 downto 0) => xlslice_6_Dout(34 downto 0)
    );
xlslice_2: component zusys_xlslice_2_0
     port map (
      Din(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      Dout(15 downto 0) => xlslice_2_Dout(15 downto 0)
    );
xlslice_3: component zusys_xlslice_3_0
     port map (
      Din(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      Dout(15 downto 0) => xlslice_3_Dout(15 downto 0)
    );
xlslice_4: component zusys_xlslice_4_0
     port map (
      Din(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      Dout(15 downto 0) => xlslice_4_Dout(15 downto 0)
    );
xlslice_5: component zusys_xlslice_5_0
     port map (
      Din(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      Dout(15 downto 0) => xlslice_5_Dout(15 downto 0)
    );
xlslice_6: component zusys_xlslice_6_0
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(34 downto 0) => xlslice_6_Dout(34 downto 0)
    );
xlslice_7: component zusys_xlslice_7_0
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(34 downto 0) => xlslice_7_Dout(34 downto 0)
    );
xlslice_8: component zusys_xlslice_8_0
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(34 downto 0) => xlslice_8_Dout(34 downto 0)
    );
xlslice_9: component zusys_xlslice_9_0
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(34 downto 0) => xlslice_9_Dout(34 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys is
  port (
    A1_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A1_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A1_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A1_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A2_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A2_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A2_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_IN : in STD_LOGIC_VECTOR ( 15 downto 0 );
    A3_OUT_CLK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    A3_OUT_CNV_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    A3_OUT_CNV_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT : out STD_LOGIC_VECTOR ( 5 downto 0 );
    D1_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D1_OUT_30 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT : out STD_LOGIC_VECTOR ( 11 downto 0 );
    D2_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D2_OUT_30 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT : out STD_LOGIC_VECTOR ( 25 downto 0 );
    D3_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D3_OUT_30 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT : out STD_LOGIC_VECTOR ( 7 downto 0 );
    D4_OUT_27 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_28 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_29 : out STD_LOGIC_VECTOR ( 0 to 0 );
    D4_OUT_30 : out STD_LOGIC_VECTOR ( 0 to 0 );
    Dig_09_Ch5 : in STD_LOGIC;
    Dig_10_Ch5 : in STD_LOGIC;
    Dig_11_Ch5 : in STD_LOGIC;
    Dig_12_Ch5 : in STD_LOGIC;
    Dig_13_Ch5 : in STD_LOGIC;
    Dig_14_Ch5 : in STD_LOGIC;
    Dig_15_Ch5 : in STD_LOGIC;
    Dig_16_Ch5 : in STD_LOGIC;
    Dig_17_Ch5 : in STD_LOGIC;
    Dig_18_Ch5 : in STD_LOGIC;
    Dig_19_Ch5 : in STD_LOGIC;
    Dig_20_Ch5 : in STD_LOGIC;
    Dig_21_Ch5 : in STD_LOGIC;
    Dig_22_Ch5 : in STD_LOGIC;
    Dig_23_Ch5 : in STD_LOGIC;
    Dig_24_Ch5 : in STD_LOGIC
  );
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of zusys : entity is "zusys,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=zusys,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=69,numReposBlks=64,numNonXlnxBlks=7,numHierBlks=5,maxHierDepth=1,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=2,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of zusys : entity is "zusys.hwdef";
end zusys;

architecture STRUCTURE of zusys is
  component zusys_proc_sys_reset_25MHz_0 is
  port (
    slowest_sync_clk : in STD_LOGIC;
    ext_reset_in : in STD_LOGIC;
    aux_reset_in : in STD_LOGIC;
    mb_debug_sys_rst : in STD_LOGIC;
    dcm_locked : in STD_LOGIC;
    mb_reset : out STD_LOGIC;
    bus_struct_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    interconnect_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_proc_sys_reset_25MHz_0;
  component zusys_proc_sys_reset_10MHz_0 is
  port (
    slowest_sync_clk : in STD_LOGIC;
    ext_reset_in : in STD_LOGIC;
    aux_reset_in : in STD_LOGIC;
    mb_debug_sys_rst : in STD_LOGIC;
    dcm_locked : in STD_LOGIC;
    mb_reset : out STD_LOGIC;
    bus_struct_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    interconnect_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_proc_sys_reset_10MHz_0;
  component zusys_proc_sys_reset_50MHz_0 is
  port (
    slowest_sync_clk : in STD_LOGIC;
    ext_reset_in : in STD_LOGIC;
    aux_reset_in : in STD_LOGIC;
    mb_debug_sys_rst : in STD_LOGIC;
    dcm_locked : in STD_LOGIC;
    mb_reset : out STD_LOGIC;
    bus_struct_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    interconnect_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_proc_sys_reset_50MHz_0;
  component zusys_proc_sys_reset_100MHz_0 is
  port (
    slowest_sync_clk : in STD_LOGIC;
    ext_reset_in : in STD_LOGIC;
    aux_reset_in : in STD_LOGIC;
    mb_debug_sys_rst : in STD_LOGIC;
    dcm_locked : in STD_LOGIC;
    mb_reset : out STD_LOGIC;
    bus_struct_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_reset : out STD_LOGIC_VECTOR ( 0 to 0 );
    interconnect_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 );
    peripheral_aresetn : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_proc_sys_reset_100MHz_0;
  component zusys_xlslice_Enable_Inverter_Bit0_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 7 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_xlslice_Enable_Inverter_Bit0_0;
  component zusys_xlslice_Enable_Gate_Bit1_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 7 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_xlslice_Enable_Gate_Bit1_0;
  component zusys_xlslice_Enable_AXI2TCM_Bit4_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 7 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_xlslice_Enable_AXI2TCM_Bit4_0;
  component zusys_vio_D34_test_0 is
  port (
    clk : in STD_LOGIC;
    probe_out0 : out STD_LOGIC_VECTOR ( 25 downto 0 )
  );
  end component zusys_vio_D34_test_0;
  component zusys_Enable_Gates_CPLD_High_0 is
  port (
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_Enable_Gates_CPLD_High_0;
  component zusys_Enable_Gates_CPLD_Low_0 is
  port (
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_Enable_Gates_CPLD_Low_0;
  component zusys_axi_gpio_2_0 is
  port (
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 8 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 8 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    gpio_io_i : in STD_LOGIC_VECTOR ( 7 downto 0 );
    gpio_io_o : out STD_LOGIC_VECTOR ( 7 downto 0 );
    gpio_io_t : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  end component zusys_axi_gpio_2_0;
  component zusys_clk_wiz_0_0 is
  port (
    resetn : in STD_LOGIC;
    clk_in1 : in STD_LOGIC;
    clk_50MHz : out STD_LOGIC;
    clk_10MHz : out STD_LOGIC;
    clk_25MHz : out STD_LOGIC
  );
  end component zusys_clk_wiz_0_0;
  component zusys_ila_Encoder_0 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe3 : in STD_LOGIC_VECTOR ( 23 downto 0 );
    probe4 : in STD_LOGIC_VECTOR ( 23 downto 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 15 downto 0 );
    probe7 : in STD_LOGIC_VECTOR ( 15 downto 0 )
  );
  end component zusys_ila_Encoder_0;
  component zusys_smartconnect_0_0 is
  port (
    aclk : in STD_LOGIC;
    aclk1 : in STD_LOGIC;
    aclk2 : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    S00_AXI_awid : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_awaddr : in STD_LOGIC_VECTOR ( 39 downto 0 );
    S00_AXI_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S00_AXI_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_awlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    S00_AXI_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_awuser : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_awvalid : in STD_LOGIC;
    S00_AXI_awready : out STD_LOGIC;
    S00_AXI_wdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    S00_AXI_wstrb : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_wlast : in STD_LOGIC;
    S00_AXI_wvalid : in STD_LOGIC;
    S00_AXI_wready : out STD_LOGIC;
    S00_AXI_bid : out STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_bvalid : out STD_LOGIC;
    S00_AXI_bready : in STD_LOGIC;
    S00_AXI_arid : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_araddr : in STD_LOGIC_VECTOR ( 39 downto 0 );
    S00_AXI_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S00_AXI_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_arlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    S00_AXI_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_arqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_aruser : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_arvalid : in STD_LOGIC;
    S00_AXI_arready : out STD_LOGIC;
    S00_AXI_rid : out STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_rdata : out STD_LOGIC_VECTOR ( 127 downto 0 );
    S00_AXI_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_rlast : out STD_LOGIC;
    S00_AXI_rvalid : out STD_LOGIC;
    S00_AXI_rready : in STD_LOGIC;
    M00_AXI_awaddr : out STD_LOGIC_VECTOR ( 5 downto 0 );
    M00_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_awvalid : out STD_LOGIC;
    M00_AXI_awready : in STD_LOGIC;
    M00_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_wvalid : out STD_LOGIC;
    M00_AXI_wready : in STD_LOGIC;
    M00_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_bvalid : in STD_LOGIC;
    M00_AXI_bready : out STD_LOGIC;
    M00_AXI_araddr : out STD_LOGIC_VECTOR ( 5 downto 0 );
    M00_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_arvalid : out STD_LOGIC;
    M00_AXI_arready : in STD_LOGIC;
    M00_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_rvalid : in STD_LOGIC;
    M00_AXI_rready : out STD_LOGIC;
    M01_AXI_awaddr : out STD_LOGIC_VECTOR ( 5 downto 0 );
    M01_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M01_AXI_awvalid : out STD_LOGIC;
    M01_AXI_awready : in STD_LOGIC;
    M01_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M01_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M01_AXI_wvalid : out STD_LOGIC;
    M01_AXI_wready : in STD_LOGIC;
    M01_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M01_AXI_bvalid : in STD_LOGIC;
    M01_AXI_bready : out STD_LOGIC;
    M01_AXI_araddr : out STD_LOGIC_VECTOR ( 5 downto 0 );
    M01_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M01_AXI_arvalid : out STD_LOGIC;
    M01_AXI_arready : in STD_LOGIC;
    M01_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M01_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M01_AXI_rvalid : in STD_LOGIC;
    M01_AXI_rready : out STD_LOGIC;
    M02_AXI_awaddr : out STD_LOGIC_VECTOR ( 5 downto 0 );
    M02_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M02_AXI_awvalid : out STD_LOGIC;
    M02_AXI_awready : in STD_LOGIC;
    M02_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M02_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M02_AXI_wvalid : out STD_LOGIC;
    M02_AXI_wready : in STD_LOGIC;
    M02_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M02_AXI_bvalid : in STD_LOGIC;
    M02_AXI_bready : out STD_LOGIC;
    M02_AXI_araddr : out STD_LOGIC_VECTOR ( 5 downto 0 );
    M02_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M02_AXI_arvalid : out STD_LOGIC;
    M02_AXI_arready : in STD_LOGIC;
    M02_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M02_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M02_AXI_rvalid : in STD_LOGIC;
    M02_AXI_rready : out STD_LOGIC;
    M03_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M03_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M03_AXI_awvalid : out STD_LOGIC;
    M03_AXI_awready : in STD_LOGIC;
    M03_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M03_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M03_AXI_wvalid : out STD_LOGIC;
    M03_AXI_wready : in STD_LOGIC;
    M03_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M03_AXI_bvalid : in STD_LOGIC;
    M03_AXI_bready : out STD_LOGIC;
    M03_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M03_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M03_AXI_arvalid : out STD_LOGIC;
    M03_AXI_arready : in STD_LOGIC;
    M03_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M03_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M03_AXI_rvalid : in STD_LOGIC;
    M03_AXI_rready : out STD_LOGIC;
    M04_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M04_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M04_AXI_awvalid : out STD_LOGIC;
    M04_AXI_awready : in STD_LOGIC;
    M04_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M04_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M04_AXI_wvalid : out STD_LOGIC;
    M04_AXI_wready : in STD_LOGIC;
    M04_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M04_AXI_bvalid : in STD_LOGIC;
    M04_AXI_bready : out STD_LOGIC;
    M04_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M04_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M04_AXI_arvalid : out STD_LOGIC;
    M04_AXI_arready : in STD_LOGIC;
    M04_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M04_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M04_AXI_rvalid : in STD_LOGIC;
    M04_AXI_rready : out STD_LOGIC;
    M05_AXI_awaddr : out STD_LOGIC_VECTOR ( 4 downto 0 );
    M05_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M05_AXI_awvalid : out STD_LOGIC;
    M05_AXI_awready : in STD_LOGIC;
    M05_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M05_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M05_AXI_wvalid : out STD_LOGIC;
    M05_AXI_wready : in STD_LOGIC;
    M05_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M05_AXI_bvalid : in STD_LOGIC;
    M05_AXI_bready : out STD_LOGIC;
    M05_AXI_araddr : out STD_LOGIC_VECTOR ( 4 downto 0 );
    M05_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M05_AXI_arvalid : out STD_LOGIC;
    M05_AXI_arready : in STD_LOGIC;
    M05_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M05_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M05_AXI_rvalid : in STD_LOGIC;
    M05_AXI_rready : out STD_LOGIC;
    M06_AXI_awaddr : out STD_LOGIC_VECTOR ( 8 downto 0 );
    M06_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M06_AXI_awvalid : out STD_LOGIC;
    M06_AXI_awready : in STD_LOGIC;
    M06_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M06_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M06_AXI_wvalid : out STD_LOGIC;
    M06_AXI_wready : in STD_LOGIC;
    M06_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M06_AXI_bvalid : in STD_LOGIC;
    M06_AXI_bready : out STD_LOGIC;
    M06_AXI_araddr : out STD_LOGIC_VECTOR ( 8 downto 0 );
    M06_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M06_AXI_arvalid : out STD_LOGIC;
    M06_AXI_arready : in STD_LOGIC;
    M06_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M06_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M06_AXI_rvalid : in STD_LOGIC;
    M06_AXI_rready : out STD_LOGIC;
    M07_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M07_AXI_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M07_AXI_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M07_AXI_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M07_AXI_awlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    M07_AXI_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M07_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M07_AXI_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M07_AXI_awuser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M07_AXI_awvalid : out STD_LOGIC;
    M07_AXI_awready : in STD_LOGIC;
    M07_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M07_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M07_AXI_wlast : out STD_LOGIC;
    M07_AXI_wvalid : out STD_LOGIC;
    M07_AXI_wready : in STD_LOGIC;
    M07_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M07_AXI_bvalid : in STD_LOGIC;
    M07_AXI_bready : out STD_LOGIC;
    M07_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M07_AXI_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M07_AXI_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M07_AXI_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M07_AXI_arlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    M07_AXI_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M07_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M07_AXI_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M07_AXI_aruser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M07_AXI_arvalid : out STD_LOGIC;
    M07_AXI_arready : in STD_LOGIC;
    M07_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M07_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M07_AXI_rlast : in STD_LOGIC;
    M07_AXI_rvalid : in STD_LOGIC;
    M07_AXI_rready : out STD_LOGIC;
    M08_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M08_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M08_AXI_awvalid : out STD_LOGIC;
    M08_AXI_awready : in STD_LOGIC;
    M08_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M08_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M08_AXI_wvalid : out STD_LOGIC;
    M08_AXI_wready : in STD_LOGIC;
    M08_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M08_AXI_bvalid : in STD_LOGIC;
    M08_AXI_bready : out STD_LOGIC;
    M08_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M08_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M08_AXI_arvalid : out STD_LOGIC;
    M08_AXI_arready : in STD_LOGIC;
    M08_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M08_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M08_AXI_rvalid : in STD_LOGIC;
    M08_AXI_rready : out STD_LOGIC;
    M09_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M09_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M09_AXI_awvalid : out STD_LOGIC;
    M09_AXI_awready : in STD_LOGIC;
    M09_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M09_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M09_AXI_wvalid : out STD_LOGIC;
    M09_AXI_wready : in STD_LOGIC;
    M09_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M09_AXI_bvalid : in STD_LOGIC;
    M09_AXI_bready : out STD_LOGIC;
    M09_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M09_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M09_AXI_arvalid : out STD_LOGIC;
    M09_AXI_arready : in STD_LOGIC;
    M09_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M09_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M09_AXI_rvalid : in STD_LOGIC;
    M09_AXI_rready : out STD_LOGIC;
    M10_AXI_awid : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_awaddr : out STD_LOGIC_VECTOR ( 39 downto 0 );
    M10_AXI_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M10_AXI_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M10_AXI_awlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    M10_AXI_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M10_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M10_AXI_awuser : out STD_LOGIC_VECTOR ( 129 downto 0 );
    M10_AXI_awvalid : out STD_LOGIC;
    M10_AXI_awready : in STD_LOGIC;
    M10_AXI_wdata : out STD_LOGIC_VECTOR ( 127 downto 0 );
    M10_AXI_wstrb : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M10_AXI_wlast : out STD_LOGIC;
    M10_AXI_wuser : out STD_LOGIC_VECTOR ( 13 downto 0 );
    M10_AXI_wvalid : out STD_LOGIC;
    M10_AXI_wready : in STD_LOGIC;
    M10_AXI_bid : in STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M10_AXI_buser : in STD_LOGIC_VECTOR ( 113 downto 0 );
    M10_AXI_bvalid : in STD_LOGIC;
    M10_AXI_bready : out STD_LOGIC;
    M10_AXI_arid : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_araddr : out STD_LOGIC_VECTOR ( 39 downto 0 );
    M10_AXI_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M10_AXI_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M10_AXI_arlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    M10_AXI_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M10_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M10_AXI_aruser : out STD_LOGIC_VECTOR ( 129 downto 0 );
    M10_AXI_arvalid : out STD_LOGIC;
    M10_AXI_arready : in STD_LOGIC;
    M10_AXI_rid : in STD_LOGIC_VECTOR ( 2 downto 0 );
    M10_AXI_rdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    M10_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M10_AXI_rlast : in STD_LOGIC;
    M10_AXI_ruser : in STD_LOGIC_VECTOR ( 13 downto 0 );
    M10_AXI_rvalid : in STD_LOGIC;
    M10_AXI_rready : out STD_LOGIC;
    M11_AXI_awaddr : out STD_LOGIC_VECTOR ( 4 downto 0 );
    M11_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M11_AXI_awvalid : out STD_LOGIC;
    M11_AXI_awready : in STD_LOGIC;
    M11_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M11_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M11_AXI_wvalid : out STD_LOGIC;
    M11_AXI_wready : in STD_LOGIC;
    M11_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M11_AXI_bvalid : in STD_LOGIC;
    M11_AXI_bready : out STD_LOGIC;
    M11_AXI_araddr : out STD_LOGIC_VECTOR ( 4 downto 0 );
    M11_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M11_AXI_arvalid : out STD_LOGIC;
    M11_AXI_arready : in STD_LOGIC;
    M11_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M11_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M11_AXI_rvalid : in STD_LOGIC;
    M11_AXI_rready : out STD_LOGIC;
    M12_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M12_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M12_AXI_awvalid : out STD_LOGIC;
    M12_AXI_awready : in STD_LOGIC;
    M12_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M12_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M12_AXI_wvalid : out STD_LOGIC;
    M12_AXI_wready : in STD_LOGIC;
    M12_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M12_AXI_bvalid : in STD_LOGIC;
    M12_AXI_bready : out STD_LOGIC;
    M12_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M12_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M12_AXI_arvalid : out STD_LOGIC;
    M12_AXI_arready : in STD_LOGIC;
    M12_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M12_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M12_AXI_rvalid : in STD_LOGIC;
    M12_AXI_rready : out STD_LOGIC;
    M13_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M13_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M13_AXI_awvalid : out STD_LOGIC;
    M13_AXI_awready : in STD_LOGIC;
    M13_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M13_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M13_AXI_wvalid : out STD_LOGIC;
    M13_AXI_wready : in STD_LOGIC;
    M13_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M13_AXI_bvalid : in STD_LOGIC;
    M13_AXI_bready : out STD_LOGIC;
    M13_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M13_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M13_AXI_arvalid : out STD_LOGIC;
    M13_AXI_arready : in STD_LOGIC;
    M13_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M13_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M13_AXI_rvalid : in STD_LOGIC;
    M13_AXI_rready : out STD_LOGIC;
    M14_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M14_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M14_AXI_awvalid : out STD_LOGIC;
    M14_AXI_awready : in STD_LOGIC;
    M14_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M14_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M14_AXI_wvalid : out STD_LOGIC;
    M14_AXI_wready : in STD_LOGIC;
    M14_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M14_AXI_bvalid : in STD_LOGIC;
    M14_AXI_bready : out STD_LOGIC;
    M14_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M14_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M14_AXI_arvalid : out STD_LOGIC;
    M14_AXI_arready : in STD_LOGIC;
    M14_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M14_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M14_AXI_rvalid : in STD_LOGIC;
    M14_AXI_rready : out STD_LOGIC
  );
  end component zusys_smartconnect_0_0;
  component zusys_zynq_ultra_ps_e_0_0 is
  port (
    maxihpm0_lpd_aclk : in STD_LOGIC;
    maxigp2_awid : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_awaddr : out STD_LOGIC_VECTOR ( 39 downto 0 );
    maxigp2_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    maxigp2_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_awlock : out STD_LOGIC;
    maxigp2_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_awvalid : out STD_LOGIC;
    maxigp2_awuser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_awready : in STD_LOGIC;
    maxigp2_wdata : out STD_LOGIC_VECTOR ( 127 downto 0 );
    maxigp2_wstrb : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_wlast : out STD_LOGIC;
    maxigp2_wvalid : out STD_LOGIC;
    maxigp2_wready : in STD_LOGIC;
    maxigp2_bid : in STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_bvalid : in STD_LOGIC;
    maxigp2_bready : out STD_LOGIC;
    maxigp2_arid : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_araddr : out STD_LOGIC_VECTOR ( 39 downto 0 );
    maxigp2_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    maxigp2_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_arlock : out STD_LOGIC;
    maxigp2_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_arvalid : out STD_LOGIC;
    maxigp2_aruser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_arready : in STD_LOGIC;
    maxigp2_rid : in STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_rdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    maxigp2_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_rlast : in STD_LOGIC;
    maxigp2_rvalid : in STD_LOGIC;
    maxigp2_rready : out STD_LOGIC;
    maxigp2_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    saxi_lpd_aclk : in STD_LOGIC;
    saxigp6_aruser : in STD_LOGIC;
    saxigp6_awuser : in STD_LOGIC;
    saxigp6_awid : in STD_LOGIC_VECTOR ( 5 downto 0 );
    saxigp6_awaddr : in STD_LOGIC_VECTOR ( 48 downto 0 );
    saxigp6_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    saxigp6_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    saxigp6_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    saxigp6_awlock : in STD_LOGIC;
    saxigp6_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    saxigp6_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    saxigp6_awvalid : in STD_LOGIC;
    saxigp6_awready : out STD_LOGIC;
    saxigp6_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    saxigp6_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    saxigp6_wlast : in STD_LOGIC;
    saxigp6_wvalid : in STD_LOGIC;
    saxigp6_wready : out STD_LOGIC;
    saxigp6_bid : out STD_LOGIC_VECTOR ( 5 downto 0 );
    saxigp6_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    saxigp6_bvalid : out STD_LOGIC;
    saxigp6_bready : in STD_LOGIC;
    saxigp6_arid : in STD_LOGIC_VECTOR ( 5 downto 0 );
    saxigp6_araddr : in STD_LOGIC_VECTOR ( 48 downto 0 );
    saxigp6_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    saxigp6_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    saxigp6_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    saxigp6_arlock : in STD_LOGIC;
    saxigp6_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    saxigp6_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    saxigp6_arvalid : in STD_LOGIC;
    saxigp6_arready : out STD_LOGIC;
    saxigp6_rid : out STD_LOGIC_VECTOR ( 5 downto 0 );
    saxigp6_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    saxigp6_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    saxigp6_rlast : out STD_LOGIC;
    saxigp6_rvalid : out STD_LOGIC;
    saxigp6_rready : in STD_LOGIC;
    saxigp6_awqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    saxigp6_arqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    pl_ps_irq0 : in STD_LOGIC_VECTOR ( 7 downto 0 );
    pl_resetn0 : out STD_LOGIC;
    pl_clk0 : out STD_LOGIC
  );
  end component zusys_zynq_ultra_ps_e_0_0;
  component zusys_IncreEncoder_V24_ip_0_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    A : in STD_LOGIC;
    B : in STD_LOGIC;
    I : in STD_LOGIC;
    PeriodEnd : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    omega : out STD_LOGIC_VECTOR ( 23 downto 0 );
    theta_el : out STD_LOGIC_VECTOR ( 23 downto 0 );
    position : out STD_LOGIC_VECTOR ( 15 downto 0 );
    edge_rsvd : out STD_LOGIC;
    count : out STD_LOGIC;
    OverSamplFactor : out STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  end component zusys_IncreEncoder_V24_ip_0_0;
  component zusys_timer_uptime_64bit_0 is
  port (
    capturetrig0 : in STD_LOGIC;
    capturetrig1 : in STD_LOGIC;
    generateout0 : out STD_LOGIC;
    generateout1 : out STD_LOGIC;
    pwm0 : out STD_LOGIC;
    interrupt : out STD_LOGIC;
    freeze : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC
  );
  end component zusys_timer_uptime_64bit_0;
  component zusys_uz_axi_testIP_0_0 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_ACLK : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    AXI4_AWID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_AWLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_AWSIZE : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_AWBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_AWLOCK : in STD_LOGIC;
    AXI4_AWCACHE : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_AWPROT : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_WLAST : in STD_LOGIC;
    AXI4_WVALID : in STD_LOGIC;
    AXI4_BREADY : in STD_LOGIC;
    AXI4_ARID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_ARLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_ARSIZE : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_ARBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_ARLOCK : in STD_LOGIC;
    AXI4_ARCACHE : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_ARPROT : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_ARVALID : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    AXI4_AWREADY : out STD_LOGIC;
    AXI4_WREADY : out STD_LOGIC;
    AXI4_BID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_BVALID : out STD_LOGIC;
    AXI4_ARREADY : out STD_LOGIC;
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_RLAST : out STD_LOGIC;
    AXI4_RVALID : out STD_LOGIC
  );
  end component zusys_uz_axi_testIP_0_0;
  component zusys_A1_ADC_LTC2311_0 is
  port (
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    RAW_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALUE : out STD_LOGIC_VECTOR ( 279 downto 0 );
    SI_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    TRIGGER_CNV : in STD_LOGIC_VECTOR ( 0 to 0 );
    SAMPLE_COUNTER : out STD_LOGIC_VECTOR ( 31 downto 0 );
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    SCLK_DIFF : out STD_LOGIC_VECTOR ( 1 downto 0 );
    MISO_DIFF : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_axi_aclk : in STD_LOGIC;
    s00_axi_aresetn : in STD_LOGIC;
    s00_axi_awaddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_awvalid : in STD_LOGIC;
    s00_axi_awready : out STD_LOGIC;
    s00_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_wvalid : in STD_LOGIC;
    s00_axi_wready : out STD_LOGIC;
    s00_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_bvalid : out STD_LOGIC;
    s00_axi_bready : in STD_LOGIC;
    s00_axi_araddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_arvalid : in STD_LOGIC;
    s00_axi_arready : out STD_LOGIC;
    s00_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_rvalid : out STD_LOGIC;
    s00_axi_rready : in STD_LOGIC
  );
  end component zusys_A1_ADC_LTC2311_0;
  component zusys_A2_ADC_LTC2311_0 is
  port (
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    RAW_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALUE : out STD_LOGIC_VECTOR ( 279 downto 0 );
    SI_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    TRIGGER_CNV : in STD_LOGIC_VECTOR ( 0 to 0 );
    SAMPLE_COUNTER : out STD_LOGIC_VECTOR ( 31 downto 0 );
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    SCLK_DIFF : out STD_LOGIC_VECTOR ( 1 downto 0 );
    MISO_DIFF : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_axi_aclk : in STD_LOGIC;
    s00_axi_aresetn : in STD_LOGIC;
    s00_axi_awaddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_awvalid : in STD_LOGIC;
    s00_axi_awready : out STD_LOGIC;
    s00_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_wvalid : in STD_LOGIC;
    s00_axi_wready : out STD_LOGIC;
    s00_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_bvalid : out STD_LOGIC;
    s00_axi_bready : in STD_LOGIC;
    s00_axi_araddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_arvalid : in STD_LOGIC;
    s00_axi_arready : out STD_LOGIC;
    s00_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_rvalid : out STD_LOGIC;
    s00_axi_rready : in STD_LOGIC
  );
  end component zusys_A2_ADC_LTC2311_0;
  component zusys_A3_ADC_LTC2311_0 is
  port (
    RAW_VALUE : out STD_LOGIC_VECTOR ( 127 downto 0 );
    RAW_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    SI_VALUE : out STD_LOGIC_VECTOR ( 279 downto 0 );
    SI_VALID : out STD_LOGIC_VECTOR ( 0 to 0 );
    TRIGGER_CNV : in STD_LOGIC_VECTOR ( 0 to 0 );
    SAMPLE_COUNTER : out STD_LOGIC_VECTOR ( 31 downto 0 );
    SS_N : out STD_LOGIC_VECTOR ( 0 to 0 );
    SCLK_DIFF : out STD_LOGIC_VECTOR ( 1 downto 0 );
    MISO_DIFF : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_axi_aclk : in STD_LOGIC;
    s00_axi_aresetn : in STD_LOGIC;
    s00_axi_awaddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_awvalid : in STD_LOGIC;
    s00_axi_awready : out STD_LOGIC;
    s00_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s00_axi_wvalid : in STD_LOGIC;
    s00_axi_wready : out STD_LOGIC;
    s00_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_bvalid : out STD_LOGIC;
    s00_axi_bready : in STD_LOGIC;
    s00_axi_araddr : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s00_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s00_axi_arvalid : in STD_LOGIC;
    s00_axi_arready : out STD_LOGIC;
    s00_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s00_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s00_axi_rvalid : out STD_LOGIC;
    s00_axi_rready : in STD_LOGIC
  );
  end component zusys_A3_ADC_LTC2311_0;
  component zusys_smartconnect_1_0 is
  port (
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    S00_AXI_awid : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awaddr : in STD_LOGIC_VECTOR ( 39 downto 0 );
    S00_AXI_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S00_AXI_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_awlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    S00_AXI_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_awqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_awuser : in STD_LOGIC_VECTOR ( 129 downto 0 );
    S00_AXI_awvalid : in STD_LOGIC;
    S00_AXI_awready : out STD_LOGIC;
    S00_AXI_wdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    S00_AXI_wstrb : in STD_LOGIC_VECTOR ( 15 downto 0 );
    S00_AXI_wlast : in STD_LOGIC;
    S00_AXI_wuser : in STD_LOGIC_VECTOR ( 13 downto 0 );
    S00_AXI_wvalid : in STD_LOGIC;
    S00_AXI_wready : out STD_LOGIC;
    S00_AXI_bid : out STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_buser : out STD_LOGIC_VECTOR ( 113 downto 0 );
    S00_AXI_bvalid : out STD_LOGIC;
    S00_AXI_bready : in STD_LOGIC;
    S00_AXI_arid : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_araddr : in STD_LOGIC_VECTOR ( 39 downto 0 );
    S00_AXI_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S00_AXI_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_arlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    S00_AXI_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_arqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    S00_AXI_aruser : in STD_LOGIC_VECTOR ( 129 downto 0 );
    S00_AXI_arvalid : in STD_LOGIC;
    S00_AXI_arready : out STD_LOGIC;
    S00_AXI_rid : out STD_LOGIC_VECTOR ( 2 downto 0 );
    S00_AXI_rdata : out STD_LOGIC_VECTOR ( 127 downto 0 );
    S00_AXI_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    S00_AXI_rlast : out STD_LOGIC;
    S00_AXI_ruser : out STD_LOGIC_VECTOR ( 13 downto 0 );
    S00_AXI_rvalid : out STD_LOGIC;
    S00_AXI_rready : in STD_LOGIC;
    M00_AXI_awaddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M00_AXI_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M00_AXI_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_awlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    M00_AXI_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_awuser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M00_AXI_awvalid : out STD_LOGIC;
    M00_AXI_awready : in STD_LOGIC;
    M00_AXI_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_wlast : out STD_LOGIC;
    M00_AXI_wvalid : out STD_LOGIC;
    M00_AXI_wready : in STD_LOGIC;
    M00_AXI_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_bvalid : in STD_LOGIC;
    M00_AXI_bready : out STD_LOGIC;
    M00_AXI_araddr : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M00_AXI_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    M00_AXI_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_arlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    M00_AXI_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    M00_AXI_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    M00_AXI_aruser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    M00_AXI_arvalid : out STD_LOGIC;
    M00_AXI_arready : in STD_LOGIC;
    M00_AXI_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M00_AXI_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    M00_AXI_rlast : in STD_LOGIC;
    M00_AXI_rvalid : in STD_LOGIC;
    M00_AXI_rready : out STD_LOGIC
  );
  end component zusys_smartconnect_1_0;
  component zusys_ila_puconv_0 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe1 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe2 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe3 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe4 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe5 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe6 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe7 : in STD_LOGIC_VECTOR ( 17 downto 0 );
    probe8 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe9 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_ila_puconv_0;
  component zusys_xlslice_0_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 26 downto 0 )
  );
  end component zusys_xlslice_0_0;
  component zusys_xlslice_1_0 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 26 downto 0 )
  );
  end component zusys_xlslice_1_0;
  component zusys_xlslice_2_1 is
  port (
    Din : in STD_LOGIC_VECTOR ( 279 downto 0 );
    Dout : out STD_LOGIC_VECTOR ( 26 downto 0 )
  );
  end component zusys_xlslice_2_1;
  component zusys_xlconstant_0_1 is
  port (
    dout : out STD_LOGIC_VECTOR ( 26 downto 0 )
  );
  end component zusys_xlconstant_0_1;
  component zusys_uz_pu_con_ip_0_1 is
  port (
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    in0 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in1 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in2 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in3 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in4 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in5 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in6 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in7 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in8 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in9 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in10 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in11 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in12 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in13 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in14 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in15 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in16 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in17 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in18 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in19 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in20 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in21 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in22 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in23 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in24 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in25 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in26 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in27 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in28 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in29 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in30 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in31 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    adc_trigger : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    out0 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out1 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out2 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out3 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out4 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out5 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out6 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out7 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out8 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out9 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out10 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out11 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out12 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out13 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out14 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out15 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out16 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out17 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out18 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out19 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out20 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out21 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out22 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out23 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out24 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out25 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out26 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out27 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out28 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out29 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out30 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out31 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out_valid : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );
  end component zusys_uz_pu_con_ip_0_1;
  signal A1_ADC_LTC2311_SAMPLE_COUNTER : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal A1_ADC_LTC2311_SCLK_DIFF : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal A1_ADC_LTC2311_SI_VALID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal A1_ADC_LTC2311_SI_VALUE : STD_LOGIC_VECTOR ( 279 downto 0 );
  signal A1_IN_1 : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal A2_IN_1 : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal A3_IN_1 : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal ADC_LTC2311_0_RAW_VALUE : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal ADC_LTC2311_0_SCLK_DIFF : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal ADC_LTC2311_0_SS_N : STD_LOGIC_VECTOR ( 0 to 0 );
  signal ADC_LTC2311_1_RAW_VALUE : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal ADC_LTC2311_1_SS_N : STD_LOGIC_VECTOR ( 0 to 0 );
  signal ADC_LTC2311_2_RAW_VALUE : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal ADC_LTC2311_2_SCLK_DIFF : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal ADC_LTC2311_2_SS_N : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_ARADDR : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARLOCK : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_ARUSER : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_ARVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWADDR : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_0_M00_AXI_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWLOCK : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_0_M00_AXI_AWUSER : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_AWVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_BID : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal AXI2TCM_0_M00_AXI_BREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_BVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_RID : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal AXI2TCM_0_M00_AXI_RLAST : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_RREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_0_M00_AXI_RVALID : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_0_M00_AXI_WLAST : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_WREADY : STD_LOGIC;
  signal AXI2TCM_0_M00_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_0_M00_AXI_WVALID : STD_LOGIC;
  signal AXI4_Lite1_1_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite1_1_ARREADY : STD_LOGIC;
  signal AXI4_Lite1_1_ARVALID : STD_LOGIC;
  signal AXI4_Lite1_1_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite1_1_AWREADY : STD_LOGIC;
  signal AXI4_Lite1_1_AWVALID : STD_LOGIC;
  signal AXI4_Lite1_1_BREADY : STD_LOGIC;
  signal AXI4_Lite1_1_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite1_1_BVALID : STD_LOGIC;
  signal AXI4_Lite1_1_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite1_1_RREADY : STD_LOGIC;
  signal AXI4_Lite1_1_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite1_1_RVALID : STD_LOGIC;
  signal AXI4_Lite1_1_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite1_1_WREADY : STD_LOGIC;
  signal AXI4_Lite1_1_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI4_Lite1_1_WVALID : STD_LOGIC;
  signal AXI4_Lite_1_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite_1_ARREADY : STD_LOGIC;
  signal AXI4_Lite_1_ARVALID : STD_LOGIC;
  signal AXI4_Lite_1_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal AXI4_Lite_1_AWREADY : STD_LOGIC;
  signal AXI4_Lite_1_AWVALID : STD_LOGIC;
  signal AXI4_Lite_1_BREADY : STD_LOGIC;
  signal AXI4_Lite_1_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite_1_BVALID : STD_LOGIC;
  signal AXI4_Lite_1_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite_1_RREADY : STD_LOGIC;
  signal AXI4_Lite_1_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI4_Lite_1_RVALID : STD_LOGIC;
  signal AXI4_Lite_1_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI4_Lite_1_WREADY : STD_LOGIC;
  signal AXI4_Lite_1_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI4_Lite_1_WVALID : STD_LOGIC;
  signal A_1 : STD_LOGIC;
  signal B_1 : STD_LOGIC;
  signal Current_Valid_0_Dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Enable_Gates_CPLD_High_dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Enable_Gates_CPLD_Low_dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_3L_Gate_Signals_3L : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal Gates_3L_Interrupt_Center : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_3L_Interrupt_Start : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_3L_Interrupt_Start_Center : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_Carrier_triangular_max1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_Carrier_triangular_max_min : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_Carrier_triangular_min1 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal Gates_dout_0 : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal I_1 : STD_LOGIC;
  signal IncreEncoder_V24_ip_0_OverSamplFactor : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal IncreEncoder_V24_ip_0_omega : STD_LOGIC_VECTOR ( 23 downto 0 );
  signal IncreEncoder_V24_ip_0_position : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal IncreEncoder_ip_0_theta_el : STD_LOGIC_VECTOR ( 23 downto 0 );
  signal Interrupt_muxed : STD_LOGIC;
  signal axi_gpio_2_gpio_io_o : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal clk_wiz_0_clk_25MHz : STD_LOGIC;
  signal proc_sys_reset_10MHz_peripheral_aresetn : STD_LOGIC_VECTOR ( 0 to 0 );
  signal proc_sys_reset_1_peripheral_aresetn : STD_LOGIC_VECTOR ( 0 to 0 );
  signal proc_sys_reset_50MHz_peripheral_aresetn : STD_LOGIC_VECTOR ( 0 to 0 );
  signal pu_valid_1 : STD_LOGIC;
  signal smartconnect_0_M00_AXI_ARADDR : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal smartconnect_0_M00_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M00_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M00_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M00_AXI_AWADDR : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal smartconnect_0_M00_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M00_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M00_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M00_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M00_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M00_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M00_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M00_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M00_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M00_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M00_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M00_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M00_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M00_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M01_AXI_ARADDR : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal smartconnect_0_M01_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M01_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M01_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M01_AXI_AWADDR : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal smartconnect_0_M01_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M01_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M01_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M01_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M01_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M01_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M01_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M01_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M01_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M01_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M01_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M01_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M01_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M01_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M02_AXI_ARADDR : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal smartconnect_0_M02_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M02_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M02_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M02_AXI_AWADDR : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal smartconnect_0_M02_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M02_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M02_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M02_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M02_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M02_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M02_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M02_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M02_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M02_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M02_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M02_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M02_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M02_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M05_AXI_ARADDR : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal smartconnect_0_M05_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M05_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M05_AXI_AWADDR : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal smartconnect_0_M05_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M05_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M05_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M05_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M05_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M05_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M05_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M05_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M05_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M05_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M05_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M05_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M05_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M06_AXI_ARADDR : STD_LOGIC_VECTOR ( 8 downto 0 );
  signal smartconnect_0_M06_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M06_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M06_AXI_AWADDR : STD_LOGIC_VECTOR ( 8 downto 0 );
  signal smartconnect_0_M06_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M06_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M06_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M06_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M06_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M06_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M06_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M06_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M06_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M06_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M06_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M06_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M06_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M07_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M07_AXI_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M07_AXI_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M07_AXI_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal smartconnect_0_M07_AXI_ARLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal smartconnect_0_M07_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M07_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M07_AXI_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M07_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M07_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M07_AXI_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M07_AXI_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M07_AXI_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal smartconnect_0_M07_AXI_AWLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal smartconnect_0_M07_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M07_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M07_AXI_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M07_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M07_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M07_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M07_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M07_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M07_AXI_RLAST : STD_LOGIC;
  signal smartconnect_0_M07_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M07_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M07_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M07_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M07_AXI_WLAST : STD_LOGIC;
  signal smartconnect_0_M07_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M07_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M07_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M08_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M08_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M08_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M08_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M08_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M08_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M08_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M08_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M08_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M08_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M08_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M08_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M08_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M08_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M08_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M08_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M08_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M09_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M09_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M09_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M09_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M09_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M09_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M09_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M09_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M09_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M09_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M09_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M09_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M09_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M09_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M09_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M09_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M09_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M10_AXI_ARADDR : STD_LOGIC_VECTOR ( 39 downto 0 );
  signal smartconnect_0_M10_AXI_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M10_AXI_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M10_AXI_ARID : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal smartconnect_0_M10_AXI_ARLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal smartconnect_0_M10_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_ARQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M10_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M10_AXI_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_ARUSER : STD_LOGIC_VECTOR ( 129 downto 0 );
  signal smartconnect_0_M10_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M10_AXI_AWADDR : STD_LOGIC_VECTOR ( 39 downto 0 );
  signal smartconnect_0_M10_AXI_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M10_AXI_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M10_AXI_AWID : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal smartconnect_0_M10_AXI_AWLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal smartconnect_0_M10_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_AWQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M10_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M10_AXI_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_AWUSER : STD_LOGIC_VECTOR ( 129 downto 0 );
  signal smartconnect_0_M10_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M10_AXI_BID : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M10_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M10_AXI_BUSER : STD_LOGIC_VECTOR ( 113 downto 0 );
  signal smartconnect_0_M10_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M10_AXI_RDATA : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal smartconnect_0_M10_AXI_RID : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_0_M10_AXI_RLAST : STD_LOGIC;
  signal smartconnect_0_M10_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M10_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M10_AXI_RUSER : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal smartconnect_0_M10_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M10_AXI_WDATA : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal smartconnect_0_M10_AXI_WLAST : STD_LOGIC;
  signal smartconnect_0_M10_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M10_AXI_WSTRB : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M10_AXI_WUSER : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal smartconnect_0_M10_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_ARADDR : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal smartconnect_0_M11_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_AWADDR : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal smartconnect_0_M11_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M11_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M11_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M11_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M11_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M11_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M11_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M11_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M12_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M12_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M12_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M12_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M12_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M12_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M12_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M12_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M12_AXI_WVALID : STD_LOGIC;
  signal smartconnect_0_M13_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M13_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_0_M13_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_0_M13_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_0_M13_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_0_M13_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_0_M13_AXI_BREADY : STD_LOGIC;
  signal smartconnect_0_M13_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M13_AXI_BVALID : STD_LOGIC;
  signal smartconnect_0_M13_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M13_AXI_RREADY : STD_LOGIC;
  signal smartconnect_0_M13_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_0_M13_AXI_RVALID : STD_LOGIC;
  signal smartconnect_0_M13_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_0_M13_AXI_WREADY : STD_LOGIC;
  signal smartconnect_0_M13_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_0_M13_AXI_WVALID : STD_LOGIC;
  signal smartconnect_1_M00_AXI_ARADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_1_M00_AXI_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_1_M00_AXI_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_1_M00_AXI_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal smartconnect_1_M00_AXI_ARLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal smartconnect_1_M00_AXI_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_1_M00_AXI_ARREADY : STD_LOGIC;
  signal smartconnect_1_M00_AXI_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_1_M00_AXI_ARVALID : STD_LOGIC;
  signal smartconnect_1_M00_AXI_AWADDR : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal smartconnect_1_M00_AXI_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_1_M00_AXI_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_1_M00_AXI_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal smartconnect_1_M00_AXI_AWLOCK : STD_LOGIC_VECTOR ( 0 to 0 );
  signal smartconnect_1_M00_AXI_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_1_M00_AXI_AWREADY : STD_LOGIC;
  signal smartconnect_1_M00_AXI_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal smartconnect_1_M00_AXI_AWVALID : STD_LOGIC;
  signal smartconnect_1_M00_AXI_BREADY : STD_LOGIC;
  signal smartconnect_1_M00_AXI_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_1_M00_AXI_BVALID : STD_LOGIC;
  signal smartconnect_1_M00_AXI_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_1_M00_AXI_RLAST : STD_LOGIC;
  signal smartconnect_1_M00_AXI_RREADY : STD_LOGIC;
  signal smartconnect_1_M00_AXI_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal smartconnect_1_M00_AXI_RVALID : STD_LOGIC;
  signal smartconnect_1_M00_AXI_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal smartconnect_1_M00_AXI_WLAST : STD_LOGIC;
  signal smartconnect_1_M00_AXI_WREADY : STD_LOGIC;
  signal smartconnect_1_M00_AXI_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal smartconnect_1_M00_AXI_WVALID : STD_LOGIC;
  signal uz_pu_con_ip_0_out0 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out1 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out2 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out3 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out4 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out5 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out6 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal uz_pu_con_ip_0_out7 : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal vio_D2_test_probe_out0 : STD_LOGIC_VECTOR ( 25 downto 0 );
  signal xlconcat_0_dout : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal xlconstant_0_dout : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal xlslice_0_Dout : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal xlslice_1_Dout : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal xlslice_2_Dout : STD_LOGIC_VECTOR ( 26 downto 0 );
  signal xlslice_Enable_AXI2TCM_Bit4_Dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal xlslice_Enable_Gate_Dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal xlslice_Enable_Inverter_Dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARADDR : STD_LOGIC_VECTOR ( 39 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARID : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARLOCK : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARREADY : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARUSER : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARVALID : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWADDR : STD_LOGIC_VECTOR ( 39 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWID : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWLOCK : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWREADY : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWUSER : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWVALID : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BID : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BREADY : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BVALID : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RDATA : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RID : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RLAST : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RREADY : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RVALID : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WDATA : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WLAST : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WREADY : STD_LOGIC;
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WSTRB : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WVALID : STD_LOGIC;
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
  signal zynq_ultra_ps_e_0_pl_clk2 : STD_LOGIC;
  signal zynq_ultra_ps_e_0_pl_clk3 : STD_LOGIC;
  signal zynq_ultra_ps_e_0_pl_resetn0 : STD_LOGIC;
  signal NLW_A2_ADC_LTC2311_RAW_VALID_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_A2_ADC_LTC2311_SAMPLE_COUNTER_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_A2_ADC_LTC2311_SI_VALID_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_A2_ADC_LTC2311_SI_VALUE_UNCONNECTED : STD_LOGIC_VECTOR ( 279 downto 0 );
  signal NLW_A3_ADC_LTC2311_RAW_VALID_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_A3_ADC_LTC2311_SAMPLE_COUNTER_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_A3_ADC_LTC2311_SI_VALID_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_A3_ADC_LTC2311_SI_VALUE_UNCONNECTED : STD_LOGIC_VECTOR ( 279 downto 0 );
  signal NLW_IncreEncoder_V24_ip_0_count_UNCONNECTED : STD_LOGIC;
  signal NLW_IncreEncoder_V24_ip_0_edge_rsvd_UNCONNECTED : STD_LOGIC;
  signal NLW_axi_gpio_2_gpio_io_t_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_proc_sys_reset_100MHz_mb_reset_UNCONNECTED : STD_LOGIC;
  signal NLW_proc_sys_reset_100MHz_bus_struct_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_100MHz_interconnect_aresetn_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_100MHz_peripheral_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_10MHz_mb_reset_UNCONNECTED : STD_LOGIC;
  signal NLW_proc_sys_reset_10MHz_bus_struct_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_10MHz_interconnect_aresetn_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_10MHz_peripheral_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_25MHz_mb_reset_UNCONNECTED : STD_LOGIC;
  signal NLW_proc_sys_reset_25MHz_bus_struct_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_25MHz_interconnect_aresetn_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_25MHz_peripheral_aresetn_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_25MHz_peripheral_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_50MHz_mb_reset_UNCONNECTED : STD_LOGIC;
  signal NLW_proc_sys_reset_50MHz_bus_struct_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_50MHz_interconnect_aresetn_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_proc_sys_reset_50MHz_peripheral_reset_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_smartconnect_0_M14_AXI_arvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_smartconnect_0_M14_AXI_awvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_smartconnect_0_M14_AXI_bready_UNCONNECTED : STD_LOGIC;
  signal NLW_smartconnect_0_M14_AXI_rready_UNCONNECTED : STD_LOGIC;
  signal NLW_smartconnect_0_M14_AXI_wvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_smartconnect_0_M03_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M03_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M04_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M04_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M05_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M05_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M06_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M06_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M07_AXI_arqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_smartconnect_0_M07_AXI_aruser_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_smartconnect_0_M07_AXI_awqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_smartconnect_0_M07_AXI_awuser_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_smartconnect_0_M08_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M08_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M09_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M09_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M11_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M11_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M12_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M12_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M13_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M13_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M14_AXI_araddr_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_smartconnect_0_M14_AXI_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M14_AXI_awaddr_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_smartconnect_0_M14_AXI_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_smartconnect_0_M14_AXI_wdata_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_smartconnect_0_M14_AXI_wstrb_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_smartconnect_1_M00_AXI_arqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_smartconnect_1_M00_AXI_aruser_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_smartconnect_1_M00_AXI_awqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_smartconnect_1_M00_AXI_awuser_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_timer_uptime_64bit_generateout0_UNCONNECTED : STD_LOGIC;
  signal NLW_timer_uptime_64bit_generateout1_UNCONNECTED : STD_LOGIC;
  signal NLW_timer_uptime_64bit_interrupt_UNCONNECTED : STD_LOGIC;
  signal NLW_timer_uptime_64bit_pwm0_UNCONNECTED : STD_LOGIC;
  signal NLW_uz_axi_testIP_0_AXI4_BID_UNCONNECTED : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal NLW_uz_axi_testIP_0_AXI4_RID_UNCONNECTED : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal NLW_uz_pu_con_ip_0_out10_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out11_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out12_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out13_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out14_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out15_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out16_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out17_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out18_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out19_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out20_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out21_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out22_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out23_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out24_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out25_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out26_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out27_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out28_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out29_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out30_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out31_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out8_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_uz_pu_con_ip_0_out9_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
begin
  A1_IN_1(15 downto 0) <= A1_IN(15 downto 0);
  A1_OUT_CLK(1 downto 0) <= A1_ADC_LTC2311_SCLK_DIFF(1 downto 0);
  A1_OUT_CNV_0(0) <= ADC_LTC2311_1_SS_N(0);
  A1_OUT_CNV_1(0) <= ADC_LTC2311_1_SS_N(0);
  A2_IN_1(15 downto 0) <= A2_IN(15 downto 0);
  A2_OUT_CLK(1 downto 0) <= ADC_LTC2311_0_SCLK_DIFF(1 downto 0);
  A2_OUT_CNV_0(0) <= ADC_LTC2311_0_SS_N(0);
  A2_OUT_CNV_1(0) <= ADC_LTC2311_0_SS_N(0);
  A3_IN_1(15 downto 0) <= A3_IN(15 downto 0);
  A3_OUT_CLK(1 downto 0) <= ADC_LTC2311_2_SCLK_DIFF(1 downto 0);
  A3_OUT_CNV_0(0) <= ADC_LTC2311_2_SS_N(0);
  A3_OUT_CNV_1(0) <= ADC_LTC2311_2_SS_N(0);
  A_1 <= Dig_13_Ch5;
  B_1 <= Dig_14_Ch5;
  D1_OUT(5 downto 0) <= Gates_dout_0(5 downto 0);
  D1_OUT_27(0) <= Enable_Gates_CPLD_Low_dout(0);
  D1_OUT_28(0) <= Enable_Gates_CPLD_Low_dout(0);
  D1_OUT_29(0) <= Enable_Gates_CPLD_High_dout(0);
  D1_OUT_30(0) <= xlslice_Enable_Gate_Dout(0);
  D2_OUT(11 downto 0) <= Gates_3L_Gate_Signals_3L(11 downto 0);
  D2_OUT_27(0) <= Enable_Gates_CPLD_Low_dout(0);
  D2_OUT_28(0) <= Enable_Gates_CPLD_Low_dout(0);
  D2_OUT_29(0) <= Enable_Gates_CPLD_High_dout(0);
  D2_OUT_30(0) <= xlslice_Enable_Gate_Dout(0);
  D3_OUT(25 downto 0) <= vio_D2_test_probe_out0(25 downto 0);
  D3_OUT_27(0) <= Enable_Gates_CPLD_Low_dout(0);
  D3_OUT_28(0) <= Enable_Gates_CPLD_Low_dout(0);
  D3_OUT_29(0) <= Enable_Gates_CPLD_High_dout(0);
  D3_OUT_30(0) <= xlslice_Enable_Gate_Dout(0);
  D4_OUT(7 downto 0) <= xlconcat_0_dout(7 downto 0);
  D4_OUT_27(0) <= Enable_Gates_CPLD_Low_dout(0);
  D4_OUT_28(0) <= Enable_Gates_CPLD_Low_dout(0);
  D4_OUT_29(0) <= Enable_Gates_CPLD_High_dout(0);
  D4_OUT_30(0) <= xlslice_Enable_Gate_Dout(0);
  I_1 <= Dig_12_Ch5;
A1_ADC_LTC2311: component zusys_A1_ADC_LTC2311_0
     port map (
      MISO_DIFF(15 downto 0) => A1_IN_1(15 downto 0),
      RAW_VALID(0) => Current_Valid_0_Dout(0),
      RAW_VALUE(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      SAMPLE_COUNTER(31 downto 0) => A1_ADC_LTC2311_SAMPLE_COUNTER(31 downto 0),
      SCLK_DIFF(1 downto 0) => A1_ADC_LTC2311_SCLK_DIFF(1 downto 0),
      SI_VALID(0) => A1_ADC_LTC2311_SI_VALID(0),
      SI_VALUE(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      SS_N(0) => ADC_LTC2311_1_SS_N(0),
      TRIGGER_CNV(0) => Interrupt_muxed,
      s00_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      s00_axi_araddr(5 downto 0) => smartconnect_0_M00_AXI_ARADDR(5 downto 0),
      s00_axi_aresetn => proc_sys_reset_1_peripheral_aresetn(0),
      s00_axi_arprot(2 downto 0) => smartconnect_0_M00_AXI_ARPROT(2 downto 0),
      s00_axi_arready => smartconnect_0_M00_AXI_ARREADY,
      s00_axi_arvalid => smartconnect_0_M00_AXI_ARVALID,
      s00_axi_awaddr(5 downto 0) => smartconnect_0_M00_AXI_AWADDR(5 downto 0),
      s00_axi_awprot(2 downto 0) => smartconnect_0_M00_AXI_AWPROT(2 downto 0),
      s00_axi_awready => smartconnect_0_M00_AXI_AWREADY,
      s00_axi_awvalid => smartconnect_0_M00_AXI_AWVALID,
      s00_axi_bready => smartconnect_0_M00_AXI_BREADY,
      s00_axi_bresp(1 downto 0) => smartconnect_0_M00_AXI_BRESP(1 downto 0),
      s00_axi_bvalid => smartconnect_0_M00_AXI_BVALID,
      s00_axi_rdata(31 downto 0) => smartconnect_0_M00_AXI_RDATA(31 downto 0),
      s00_axi_rready => smartconnect_0_M00_AXI_RREADY,
      s00_axi_rresp(1 downto 0) => smartconnect_0_M00_AXI_RRESP(1 downto 0),
      s00_axi_rvalid => smartconnect_0_M00_AXI_RVALID,
      s00_axi_wdata(31 downto 0) => smartconnect_0_M00_AXI_WDATA(31 downto 0),
      s00_axi_wready => smartconnect_0_M00_AXI_WREADY,
      s00_axi_wstrb(3 downto 0) => smartconnect_0_M00_AXI_WSTRB(3 downto 0),
      s00_axi_wvalid => smartconnect_0_M00_AXI_WVALID
    );
A2_ADC_LTC2311: component zusys_A2_ADC_LTC2311_0
     port map (
      MISO_DIFF(15 downto 0) => A2_IN_1(15 downto 0),
      RAW_VALID(0) => NLW_A2_ADC_LTC2311_RAW_VALID_UNCONNECTED(0),
      RAW_VALUE(127 downto 0) => ADC_LTC2311_0_RAW_VALUE(127 downto 0),
      SAMPLE_COUNTER(31 downto 0) => NLW_A2_ADC_LTC2311_SAMPLE_COUNTER_UNCONNECTED(31 downto 0),
      SCLK_DIFF(1 downto 0) => ADC_LTC2311_0_SCLK_DIFF(1 downto 0),
      SI_VALID(0) => NLW_A2_ADC_LTC2311_SI_VALID_UNCONNECTED(0),
      SI_VALUE(279 downto 0) => NLW_A2_ADC_LTC2311_SI_VALUE_UNCONNECTED(279 downto 0),
      SS_N(0) => ADC_LTC2311_0_SS_N(0),
      TRIGGER_CNV(0) => Interrupt_muxed,
      s00_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      s00_axi_araddr(5 downto 0) => smartconnect_0_M01_AXI_ARADDR(5 downto 0),
      s00_axi_aresetn => proc_sys_reset_1_peripheral_aresetn(0),
      s00_axi_arprot(2 downto 0) => smartconnect_0_M01_AXI_ARPROT(2 downto 0),
      s00_axi_arready => smartconnect_0_M01_AXI_ARREADY,
      s00_axi_arvalid => smartconnect_0_M01_AXI_ARVALID,
      s00_axi_awaddr(5 downto 0) => smartconnect_0_M01_AXI_AWADDR(5 downto 0),
      s00_axi_awprot(2 downto 0) => smartconnect_0_M01_AXI_AWPROT(2 downto 0),
      s00_axi_awready => smartconnect_0_M01_AXI_AWREADY,
      s00_axi_awvalid => smartconnect_0_M01_AXI_AWVALID,
      s00_axi_bready => smartconnect_0_M01_AXI_BREADY,
      s00_axi_bresp(1 downto 0) => smartconnect_0_M01_AXI_BRESP(1 downto 0),
      s00_axi_bvalid => smartconnect_0_M01_AXI_BVALID,
      s00_axi_rdata(31 downto 0) => smartconnect_0_M01_AXI_RDATA(31 downto 0),
      s00_axi_rready => smartconnect_0_M01_AXI_RREADY,
      s00_axi_rresp(1 downto 0) => smartconnect_0_M01_AXI_RRESP(1 downto 0),
      s00_axi_rvalid => smartconnect_0_M01_AXI_RVALID,
      s00_axi_wdata(31 downto 0) => smartconnect_0_M01_AXI_WDATA(31 downto 0),
      s00_axi_wready => smartconnect_0_M01_AXI_WREADY,
      s00_axi_wstrb(3 downto 0) => smartconnect_0_M01_AXI_WSTRB(3 downto 0),
      s00_axi_wvalid => smartconnect_0_M01_AXI_WVALID
    );
A3_ADC_LTC2311: component zusys_A3_ADC_LTC2311_0
     port map (
      MISO_DIFF(15 downto 0) => A3_IN_1(15 downto 0),
      RAW_VALID(0) => NLW_A3_ADC_LTC2311_RAW_VALID_UNCONNECTED(0),
      RAW_VALUE(127 downto 0) => ADC_LTC2311_2_RAW_VALUE(127 downto 0),
      SAMPLE_COUNTER(31 downto 0) => NLW_A3_ADC_LTC2311_SAMPLE_COUNTER_UNCONNECTED(31 downto 0),
      SCLK_DIFF(1 downto 0) => ADC_LTC2311_2_SCLK_DIFF(1 downto 0),
      SI_VALID(0) => NLW_A3_ADC_LTC2311_SI_VALID_UNCONNECTED(0),
      SI_VALUE(279 downto 0) => NLW_A3_ADC_LTC2311_SI_VALUE_UNCONNECTED(279 downto 0),
      SS_N(0) => ADC_LTC2311_2_SS_N(0),
      TRIGGER_CNV(0) => Interrupt_muxed,
      s00_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      s00_axi_araddr(5 downto 0) => smartconnect_0_M02_AXI_ARADDR(5 downto 0),
      s00_axi_aresetn => proc_sys_reset_1_peripheral_aresetn(0),
      s00_axi_arprot(2 downto 0) => smartconnect_0_M02_AXI_ARPROT(2 downto 0),
      s00_axi_arready => smartconnect_0_M02_AXI_ARREADY,
      s00_axi_arvalid => smartconnect_0_M02_AXI_ARVALID,
      s00_axi_awaddr(5 downto 0) => smartconnect_0_M02_AXI_AWADDR(5 downto 0),
      s00_axi_awprot(2 downto 0) => smartconnect_0_M02_AXI_AWPROT(2 downto 0),
      s00_axi_awready => smartconnect_0_M02_AXI_AWREADY,
      s00_axi_awvalid => smartconnect_0_M02_AXI_AWVALID,
      s00_axi_bready => smartconnect_0_M02_AXI_BREADY,
      s00_axi_bresp(1 downto 0) => smartconnect_0_M02_AXI_BRESP(1 downto 0),
      s00_axi_bvalid => smartconnect_0_M02_AXI_BVALID,
      s00_axi_rdata(31 downto 0) => smartconnect_0_M02_AXI_RDATA(31 downto 0),
      s00_axi_rready => smartconnect_0_M02_AXI_RREADY,
      s00_axi_rresp(1 downto 0) => smartconnect_0_M02_AXI_RRESP(1 downto 0),
      s00_axi_rvalid => smartconnect_0_M02_AXI_RVALID,
      s00_axi_wdata(31 downto 0) => smartconnect_0_M02_AXI_WDATA(31 downto 0),
      s00_axi_wready => smartconnect_0_M02_AXI_WREADY,
      s00_axi_wstrb(3 downto 0) => smartconnect_0_M02_AXI_WSTRB(3 downto 0),
      s00_axi_wvalid => smartconnect_0_M02_AXI_WVALID
    );
DataMover: entity work.DataMover_imp_1A1U27G
     port map (
      ADC_A1(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      ADC_A2(127 downto 0) => ADC_LTC2311_0_RAW_VALUE(127 downto 0),
      ADC_A3(127 downto 0) => ADC_LTC2311_2_RAW_VALUE(127 downto 0),
      Enable_AXI2TCM(0) => xlslice_Enable_AXI2TCM_Bit4_Dout(0),
      M00_AXI_araddr(31 downto 0) => AXI2TCM_0_M00_AXI_ARADDR(31 downto 0),
      M00_AXI_arburst(1 downto 0) => AXI2TCM_0_M00_AXI_ARBURST(1 downto 0),
      M00_AXI_arcache(3 downto 0) => AXI2TCM_0_M00_AXI_ARCACHE(3 downto 0),
      M00_AXI_arid(0) => AXI2TCM_0_M00_AXI_ARID(0),
      M00_AXI_arlen(7 downto 0) => AXI2TCM_0_M00_AXI_ARLEN(7 downto 0),
      M00_AXI_arlock => AXI2TCM_0_M00_AXI_ARLOCK,
      M00_AXI_arprot(2 downto 0) => AXI2TCM_0_M00_AXI_ARPROT(2 downto 0),
      M00_AXI_arqos(3 downto 0) => AXI2TCM_0_M00_AXI_ARQOS(3 downto 0),
      M00_AXI_arready => AXI2TCM_0_M00_AXI_ARREADY,
      M00_AXI_arsize(2 downto 0) => AXI2TCM_0_M00_AXI_ARSIZE(2 downto 0),
      M00_AXI_aruser => AXI2TCM_0_M00_AXI_ARUSER,
      M00_AXI_arvalid => AXI2TCM_0_M00_AXI_ARVALID,
      M00_AXI_awaddr(31 downto 0) => AXI2TCM_0_M00_AXI_AWADDR(31 downto 0),
      M00_AXI_awburst(1 downto 0) => AXI2TCM_0_M00_AXI_AWBURST(1 downto 0),
      M00_AXI_awcache(3 downto 0) => AXI2TCM_0_M00_AXI_AWCACHE(3 downto 0),
      M00_AXI_awid(0) => AXI2TCM_0_M00_AXI_AWID(0),
      M00_AXI_awlen(7 downto 0) => AXI2TCM_0_M00_AXI_AWLEN(7 downto 0),
      M00_AXI_awlock => AXI2TCM_0_M00_AXI_AWLOCK,
      M00_AXI_awprot(2 downto 0) => AXI2TCM_0_M00_AXI_AWPROT(2 downto 0),
      M00_AXI_awqos(3 downto 0) => AXI2TCM_0_M00_AXI_AWQOS(3 downto 0),
      M00_AXI_awready => AXI2TCM_0_M00_AXI_AWREADY,
      M00_AXI_awsize(2 downto 0) => AXI2TCM_0_M00_AXI_AWSIZE(2 downto 0),
      M00_AXI_awuser => AXI2TCM_0_M00_AXI_AWUSER,
      M00_AXI_awvalid => AXI2TCM_0_M00_AXI_AWVALID,
      M00_AXI_bid(5 downto 0) => AXI2TCM_0_M00_AXI_BID(5 downto 0),
      M00_AXI_bready => AXI2TCM_0_M00_AXI_BREADY,
      M00_AXI_bresp(1 downto 0) => AXI2TCM_0_M00_AXI_BRESP(1 downto 0),
      M00_AXI_bvalid => AXI2TCM_0_M00_AXI_BVALID,
      M00_AXI_rdata(31 downto 0) => AXI2TCM_0_M00_AXI_RDATA(31 downto 0),
      M00_AXI_rid(5 downto 0) => AXI2TCM_0_M00_AXI_RID(5 downto 0),
      M00_AXI_rlast => AXI2TCM_0_M00_AXI_RLAST,
      M00_AXI_rready => AXI2TCM_0_M00_AXI_RREADY,
      M00_AXI_rresp(1 downto 0) => AXI2TCM_0_M00_AXI_RRESP(1 downto 0),
      M00_AXI_rvalid => AXI2TCM_0_M00_AXI_RVALID,
      M00_AXI_wdata(31 downto 0) => AXI2TCM_0_M00_AXI_WDATA(31 downto 0),
      M00_AXI_wlast => AXI2TCM_0_M00_AXI_WLAST,
      M00_AXI_wready => AXI2TCM_0_M00_AXI_WREADY,
      M00_AXI_wstrb(3 downto 0) => AXI2TCM_0_M00_AXI_WSTRB(3 downto 0),
      M00_AXI_wvalid => AXI2TCM_0_M00_AXI_WVALID,
      Trigger_AXI2TCM(0) => Current_Valid_0_Dout(0),
      m00_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      m00_axi_aresetn => proc_sys_reset_1_peripheral_aresetn(0)
    );
Enable_Gates_CPLD_High: component zusys_Enable_Gates_CPLD_High_0
     port map (
      dout(0) => Enable_Gates_CPLD_High_dout(0)
    );
Enable_Gates_CPLD_Low: component zusys_Enable_Gates_CPLD_Low_0
     port map (
      dout(0) => Enable_Gates_CPLD_Low_dout(0)
    );
Gates: entity work.Gates_imp_1G0NY44
     port map (
      AXI4_Lite1_araddr(15 downto 0) => AXI4_Lite1_1_ARADDR(15 downto 0),
      AXI4_Lite1_arready => AXI4_Lite1_1_ARREADY,
      AXI4_Lite1_arvalid => AXI4_Lite1_1_ARVALID,
      AXI4_Lite1_awaddr(15 downto 0) => AXI4_Lite1_1_AWADDR(15 downto 0),
      AXI4_Lite1_awready => AXI4_Lite1_1_AWREADY,
      AXI4_Lite1_awvalid => AXI4_Lite1_1_AWVALID,
      AXI4_Lite1_bready => AXI4_Lite1_1_BREADY,
      AXI4_Lite1_bresp(1 downto 0) => AXI4_Lite1_1_BRESP(1 downto 0),
      AXI4_Lite1_bvalid => AXI4_Lite1_1_BVALID,
      AXI4_Lite1_rdata(31 downto 0) => AXI4_Lite1_1_RDATA(31 downto 0),
      AXI4_Lite1_rready => AXI4_Lite1_1_RREADY,
      AXI4_Lite1_rresp(1 downto 0) => AXI4_Lite1_1_RRESP(1 downto 0),
      AXI4_Lite1_rvalid => AXI4_Lite1_1_RVALID,
      AXI4_Lite1_wdata(31 downto 0) => AXI4_Lite1_1_WDATA(31 downto 0),
      AXI4_Lite1_wready => AXI4_Lite1_1_WREADY,
      AXI4_Lite1_wstrb(3 downto 0) => AXI4_Lite1_1_WSTRB(3 downto 0),
      AXI4_Lite1_wvalid => AXI4_Lite1_1_WVALID,
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARESETN => proc_sys_reset_1_peripheral_aresetn(0),
      AXI4_Lite_araddr(15 downto 0) => smartconnect_0_M08_AXI_ARADDR(15 downto 0),
      AXI4_Lite_arready => smartconnect_0_M08_AXI_ARREADY,
      AXI4_Lite_arvalid => smartconnect_0_M08_AXI_ARVALID,
      AXI4_Lite_awaddr(15 downto 0) => smartconnect_0_M08_AXI_AWADDR(15 downto 0),
      AXI4_Lite_awready => smartconnect_0_M08_AXI_AWREADY,
      AXI4_Lite_awvalid => smartconnect_0_M08_AXI_AWVALID,
      AXI4_Lite_bready => smartconnect_0_M08_AXI_BREADY,
      AXI4_Lite_bresp(1 downto 0) => smartconnect_0_M08_AXI_BRESP(1 downto 0),
      AXI4_Lite_bvalid => smartconnect_0_M08_AXI_BVALID,
      AXI4_Lite_rdata(31 downto 0) => smartconnect_0_M08_AXI_RDATA(31 downto 0),
      AXI4_Lite_rready => smartconnect_0_M08_AXI_RREADY,
      AXI4_Lite_rresp(1 downto 0) => smartconnect_0_M08_AXI_RRESP(1 downto 0),
      AXI4_Lite_rvalid => smartconnect_0_M08_AXI_RVALID,
      AXI4_Lite_wdata(31 downto 0) => smartconnect_0_M08_AXI_WDATA(31 downto 0),
      AXI4_Lite_wready => smartconnect_0_M08_AXI_WREADY,
      AXI4_Lite_wstrb(3 downto 0) => smartconnect_0_M08_AXI_WSTRB(3 downto 0),
      AXI4_Lite_wvalid => smartconnect_0_M08_AXI_WVALID,
      Carrier_triangular_max(0) => Gates_Carrier_triangular_max1(0),
      Carrier_triangular_max_min(0) => Gates_Carrier_triangular_max_min(0),
      Carrier_triangular_min(0) => Gates_Carrier_triangular_min1(0),
      Enable_Gate(0) => xlslice_Enable_Inverter_Dout(0),
      Gate_Signals_2L(5 downto 0) => Gates_dout_0(5 downto 0),
      S00_AXI_araddr(15 downto 0) => smartconnect_0_M07_AXI_ARADDR(15 downto 0),
      S00_AXI_arburst(1 downto 0) => smartconnect_0_M07_AXI_ARBURST(1 downto 0),
      S00_AXI_arcache(3 downto 0) => smartconnect_0_M07_AXI_ARCACHE(3 downto 0),
      S00_AXI_arlen(7 downto 0) => smartconnect_0_M07_AXI_ARLEN(7 downto 0),
      S00_AXI_arlock(0) => smartconnect_0_M07_AXI_ARLOCK(0),
      S00_AXI_arprot(2 downto 0) => smartconnect_0_M07_AXI_ARPROT(2 downto 0),
      S00_AXI_arready => smartconnect_0_M07_AXI_ARREADY,
      S00_AXI_arsize(2 downto 0) => smartconnect_0_M07_AXI_ARSIZE(2 downto 0),
      S00_AXI_arvalid => smartconnect_0_M07_AXI_ARVALID,
      S00_AXI_awaddr(15 downto 0) => smartconnect_0_M07_AXI_AWADDR(15 downto 0),
      S00_AXI_awburst(1 downto 0) => smartconnect_0_M07_AXI_AWBURST(1 downto 0),
      S00_AXI_awcache(3 downto 0) => smartconnect_0_M07_AXI_AWCACHE(3 downto 0),
      S00_AXI_awlen(7 downto 0) => smartconnect_0_M07_AXI_AWLEN(7 downto 0),
      S00_AXI_awlock(0) => smartconnect_0_M07_AXI_AWLOCK(0),
      S00_AXI_awprot(2 downto 0) => smartconnect_0_M07_AXI_AWPROT(2 downto 0),
      S00_AXI_awready => smartconnect_0_M07_AXI_AWREADY,
      S00_AXI_awsize(2 downto 0) => smartconnect_0_M07_AXI_AWSIZE(2 downto 0),
      S00_AXI_awvalid => smartconnect_0_M07_AXI_AWVALID,
      S00_AXI_bready => smartconnect_0_M07_AXI_BREADY,
      S00_AXI_bresp(1 downto 0) => smartconnect_0_M07_AXI_BRESP(1 downto 0),
      S00_AXI_bvalid => smartconnect_0_M07_AXI_BVALID,
      S00_AXI_rdata(31 downto 0) => smartconnect_0_M07_AXI_RDATA(31 downto 0),
      S00_AXI_rlast => smartconnect_0_M07_AXI_RLAST,
      S00_AXI_rready => smartconnect_0_M07_AXI_RREADY,
      S00_AXI_rresp(1 downto 0) => smartconnect_0_M07_AXI_RRESP(1 downto 0),
      S00_AXI_rvalid => smartconnect_0_M07_AXI_RVALID,
      S00_AXI_wdata(31 downto 0) => smartconnect_0_M07_AXI_WDATA(31 downto 0),
      S00_AXI_wlast => smartconnect_0_M07_AXI_WLAST,
      S00_AXI_wready => smartconnect_0_M07_AXI_WREADY,
      S00_AXI_wstrb(3 downto 0) => smartconnect_0_M07_AXI_WSTRB(3 downto 0),
      S00_AXI_wvalid => smartconnect_0_M07_AXI_WVALID,
      s00_axi_aclk => zynq_ultra_ps_e_0_pl_clk2,
      s00_axi_aresetn => proc_sys_reset_10MHz_peripheral_aresetn(0)
    );
Gates_3L: entity work.Gates_3L_imp_TK8CX6
     port map (
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARESETN => proc_sys_reset_1_peripheral_aresetn(0),
      AXI4_Lite_araddr(15 downto 0) => smartconnect_0_M12_AXI_ARADDR(15 downto 0),
      AXI4_Lite_arready => smartconnect_0_M12_AXI_ARREADY,
      AXI4_Lite_arvalid => smartconnect_0_M12_AXI_ARVALID,
      AXI4_Lite_awaddr(15 downto 0) => smartconnect_0_M12_AXI_AWADDR(15 downto 0),
      AXI4_Lite_awready => smartconnect_0_M12_AXI_AWREADY,
      AXI4_Lite_awvalid => smartconnect_0_M12_AXI_AWVALID,
      AXI4_Lite_bready => smartconnect_0_M12_AXI_BREADY,
      AXI4_Lite_bresp(1 downto 0) => smartconnect_0_M12_AXI_BRESP(1 downto 0),
      AXI4_Lite_bvalid => smartconnect_0_M12_AXI_BVALID,
      AXI4_Lite_rdata(31 downto 0) => smartconnect_0_M12_AXI_RDATA(31 downto 0),
      AXI4_Lite_rready => smartconnect_0_M12_AXI_RREADY,
      AXI4_Lite_rresp(1 downto 0) => smartconnect_0_M12_AXI_RRESP(1 downto 0),
      AXI4_Lite_rvalid => smartconnect_0_M12_AXI_RVALID,
      AXI4_Lite_wdata(31 downto 0) => smartconnect_0_M12_AXI_WDATA(31 downto 0),
      AXI4_Lite_wready => smartconnect_0_M12_AXI_WREADY,
      AXI4_Lite_wstrb(3 downto 0) => smartconnect_0_M12_AXI_WSTRB(3 downto 0),
      AXI4_Lite_wvalid => smartconnect_0_M12_AXI_WVALID,
      Enable_Gates => xlslice_Enable_Inverter_Dout(0),
      Gate_Signals_3L(11 downto 0) => Gates_3L_Gate_Signals_3L(11 downto 0),
      Interrupt_Center(0) => Gates_3L_Interrupt_Center(0),
      Interrupt_Start(0) => Gates_3L_Interrupt_Start(0),
      Interrupt_Start_Center(0) => Gates_3L_Interrupt_Start_Center(0)
    );
IncreEncoder_V24_ip_0: component zusys_IncreEncoder_V24_ip_0_0
     port map (
      A => A_1,
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk3,
      AXI4_Lite_ARADDR(15 downto 0) => smartconnect_0_M09_AXI_ARADDR(15 downto 0),
      AXI4_Lite_ARESETN => proc_sys_reset_50MHz_peripheral_aresetn(0),
      AXI4_Lite_ARREADY => smartconnect_0_M09_AXI_ARREADY,
      AXI4_Lite_ARVALID => smartconnect_0_M09_AXI_ARVALID,
      AXI4_Lite_AWADDR(15 downto 0) => smartconnect_0_M09_AXI_AWADDR(15 downto 0),
      AXI4_Lite_AWREADY => smartconnect_0_M09_AXI_AWREADY,
      AXI4_Lite_AWVALID => smartconnect_0_M09_AXI_AWVALID,
      AXI4_Lite_BREADY => smartconnect_0_M09_AXI_BREADY,
      AXI4_Lite_BRESP(1 downto 0) => smartconnect_0_M09_AXI_BRESP(1 downto 0),
      AXI4_Lite_BVALID => smartconnect_0_M09_AXI_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => smartconnect_0_M09_AXI_RDATA(31 downto 0),
      AXI4_Lite_RREADY => smartconnect_0_M09_AXI_RREADY,
      AXI4_Lite_RRESP(1 downto 0) => smartconnect_0_M09_AXI_RRESP(1 downto 0),
      AXI4_Lite_RVALID => smartconnect_0_M09_AXI_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => smartconnect_0_M09_AXI_WDATA(31 downto 0),
      AXI4_Lite_WREADY => smartconnect_0_M09_AXI_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => smartconnect_0_M09_AXI_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => smartconnect_0_M09_AXI_WVALID,
      B => B_1,
      I => I_1,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk3,
      IPCORE_RESETN => proc_sys_reset_50MHz_peripheral_aresetn(0),
      OverSamplFactor(15 downto 0) => IncreEncoder_V24_ip_0_OverSamplFactor(15 downto 0),
      PeriodEnd => Interrupt_muxed,
      count => NLW_IncreEncoder_V24_ip_0_count_UNCONNECTED,
      edge_rsvd => NLW_IncreEncoder_V24_ip_0_edge_rsvd_UNCONNECTED,
      omega(23 downto 0) => IncreEncoder_V24_ip_0_omega(23 downto 0),
      position(15 downto 0) => IncreEncoder_V24_ip_0_position(15 downto 0),
      theta_el(23 downto 0) => IncreEncoder_ip_0_theta_el(23 downto 0)
    );
Interrupt: entity work.Interrupt_imp_CGQCLG
     port map (
      AXI4_Lite_araddr(15 downto 0) => AXI4_Lite_1_ARADDR(15 downto 0),
      AXI4_Lite_arready => AXI4_Lite_1_ARREADY,
      AXI4_Lite_arvalid => AXI4_Lite_1_ARVALID,
      AXI4_Lite_awaddr(15 downto 0) => AXI4_Lite_1_AWADDR(15 downto 0),
      AXI4_Lite_awready => AXI4_Lite_1_AWREADY,
      AXI4_Lite_awvalid => AXI4_Lite_1_AWVALID,
      AXI4_Lite_bready => AXI4_Lite_1_BREADY,
      AXI4_Lite_bresp(1 downto 0) => AXI4_Lite_1_BRESP(1 downto 0),
      AXI4_Lite_bvalid => AXI4_Lite_1_BVALID,
      AXI4_Lite_rdata(31 downto 0) => AXI4_Lite_1_RDATA(31 downto 0),
      AXI4_Lite_rready => AXI4_Lite_1_RREADY,
      AXI4_Lite_rresp(1 downto 0) => AXI4_Lite_1_RRESP(1 downto 0),
      AXI4_Lite_rvalid => AXI4_Lite_1_RVALID,
      AXI4_Lite_wdata(31 downto 0) => AXI4_Lite_1_WDATA(31 downto 0),
      AXI4_Lite_wready => AXI4_Lite_1_WREADY,
      AXI4_Lite_wstrb(3 downto 0) => AXI4_Lite_1_WSTRB(3 downto 0),
      AXI4_Lite_wvalid => AXI4_Lite_1_WVALID,
      IPCORE_RESETN => proc_sys_reset_1_peripheral_aresetn(0),
      Interrupt0(0) => Gates_Carrier_triangular_max_min(0),
      Interrupt1(0) => Gates_Carrier_triangular_min1(0),
      Interrupt2(0) => Gates_Carrier_triangular_max1(0),
      Interrupt3(0) => Gates_3L_Interrupt_Start_Center(0),
      Interrupt4(0) => Gates_3L_Interrupt_Start(0),
      Interrupt5(0) => Gates_3L_Interrupt_Center(0),
      Interrupt_vector(7 downto 0) => xlconcat_0_dout(7 downto 0),
      S_AXI_araddr(4 downto 0) => smartconnect_0_M11_AXI_ARADDR(4 downto 0),
      S_AXI_arready => smartconnect_0_M11_AXI_ARREADY,
      S_AXI_arvalid => smartconnect_0_M11_AXI_ARVALID,
      S_AXI_awaddr(4 downto 0) => smartconnect_0_M11_AXI_AWADDR(4 downto 0),
      S_AXI_awready => smartconnect_0_M11_AXI_AWREADY,
      S_AXI_awvalid => smartconnect_0_M11_AXI_AWVALID,
      S_AXI_bready => smartconnect_0_M11_AXI_BREADY,
      S_AXI_bresp(1 downto 0) => smartconnect_0_M11_AXI_BRESP(1 downto 0),
      S_AXI_bvalid => smartconnect_0_M11_AXI_BVALID,
      S_AXI_rdata(31 downto 0) => smartconnect_0_M11_AXI_RDATA(31 downto 0),
      S_AXI_rready => smartconnect_0_M11_AXI_RREADY,
      S_AXI_rresp(1 downto 0) => smartconnect_0_M11_AXI_RRESP(1 downto 0),
      S_AXI_rvalid => smartconnect_0_M11_AXI_RVALID,
      S_AXI_wdata(31 downto 0) => smartconnect_0_M11_AXI_WDATA(31 downto 0),
      S_AXI_wready => smartconnect_0_M11_AXI_WREADY,
      S_AXI_wstrb(3 downto 0) => smartconnect_0_M11_AXI_WSTRB(3 downto 0),
      S_AXI_wvalid => smartconnect_0_M11_AXI_WVALID,
      clk => zynq_ultra_ps_e_0_pl_clk1,
      trigger_converesions => Interrupt_muxed
    );
adc_debug: entity work.adc_debug_imp_76DXHS
     port map (
      Din(127 downto 0) => ADC_LTC2311_1_RAW_VALUE(127 downto 0),
      Din1(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe4(0) => Current_Valid_0_Dout(0),
      probe5(0) => Interrupt_muxed,
      probe6(31 downto 0) => A1_ADC_LTC2311_SAMPLE_COUNTER(31 downto 0),
      probe7(0) => A1_ADC_LTC2311_SI_VALID(0),
      pu_valid => pu_valid_1
    );
axi_gpio_2: component zusys_axi_gpio_2_0
     port map (
      gpio_io_i(7 downto 0) => B"00000000",
      gpio_io_o(7 downto 0) => axi_gpio_2_gpio_io_o(7 downto 0),
      gpio_io_t(7 downto 0) => NLW_axi_gpio_2_gpio_io_t_UNCONNECTED(7 downto 0),
      s_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      s_axi_araddr(8 downto 0) => smartconnect_0_M06_AXI_ARADDR(8 downto 0),
      s_axi_aresetn => proc_sys_reset_1_peripheral_aresetn(0),
      s_axi_arready => smartconnect_0_M06_AXI_ARREADY,
      s_axi_arvalid => smartconnect_0_M06_AXI_ARVALID,
      s_axi_awaddr(8 downto 0) => smartconnect_0_M06_AXI_AWADDR(8 downto 0),
      s_axi_awready => smartconnect_0_M06_AXI_AWREADY,
      s_axi_awvalid => smartconnect_0_M06_AXI_AWVALID,
      s_axi_bready => smartconnect_0_M06_AXI_BREADY,
      s_axi_bresp(1 downto 0) => smartconnect_0_M06_AXI_BRESP(1 downto 0),
      s_axi_bvalid => smartconnect_0_M06_AXI_BVALID,
      s_axi_rdata(31 downto 0) => smartconnect_0_M06_AXI_RDATA(31 downto 0),
      s_axi_rready => smartconnect_0_M06_AXI_RREADY,
      s_axi_rresp(1 downto 0) => smartconnect_0_M06_AXI_RRESP(1 downto 0),
      s_axi_rvalid => smartconnect_0_M06_AXI_RVALID,
      s_axi_wdata(31 downto 0) => smartconnect_0_M06_AXI_WDATA(31 downto 0),
      s_axi_wready => smartconnect_0_M06_AXI_WREADY,
      s_axi_wstrb(3 downto 0) => smartconnect_0_M06_AXI_WSTRB(3 downto 0),
      s_axi_wvalid => smartconnect_0_M06_AXI_WVALID
    );
clk_wiz_0: component zusys_clk_wiz_0_0
     port map (
      clk_10MHz => zynq_ultra_ps_e_0_pl_clk2,
      clk_25MHz => clk_wiz_0_clk_25MHz,
      clk_50MHz => zynq_ultra_ps_e_0_pl_clk3,
      clk_in1 => zynq_ultra_ps_e_0_pl_clk1,
      resetn => zynq_ultra_ps_e_0_pl_resetn0
    );
ila_Encoder: component zusys_ila_Encoder_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(0) => A_1,
      probe1(0) => B_1,
      probe2(0) => I_1,
      probe3(23 downto 0) => IncreEncoder_V24_ip_0_omega(23 downto 0),
      probe4(23 downto 0) => IncreEncoder_ip_0_theta_el(23 downto 0),
      probe5(0) => Interrupt_muxed,
      probe6(15 downto 0) => IncreEncoder_V24_ip_0_position(15 downto 0),
      probe7(15 downto 0) => IncreEncoder_V24_ip_0_OverSamplFactor(15 downto 0)
    );
ila_puconv: component zusys_ila_puconv_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe0(17 downto 0) => uz_pu_con_ip_0_out0(17 downto 0),
      probe1(17 downto 0) => uz_pu_con_ip_0_out1(17 downto 0),
      probe2(17 downto 0) => uz_pu_con_ip_0_out2(17 downto 0),
      probe3(17 downto 0) => uz_pu_con_ip_0_out3(17 downto 0),
      probe4(17 downto 0) => uz_pu_con_ip_0_out4(17 downto 0),
      probe5(17 downto 0) => uz_pu_con_ip_0_out5(17 downto 0),
      probe6(17 downto 0) => uz_pu_con_ip_0_out6(17 downto 0),
      probe7(17 downto 0) => uz_pu_con_ip_0_out7(17 downto 0),
      probe8(0) => A1_ADC_LTC2311_SI_VALID(0),
      probe9(0) => pu_valid_1
    );
proc_sys_reset_100MHz: component zusys_proc_sys_reset_100MHz_0
     port map (
      aux_reset_in => '1',
      bus_struct_reset(0) => NLW_proc_sys_reset_100MHz_bus_struct_reset_UNCONNECTED(0),
      dcm_locked => '1',
      ext_reset_in => zynq_ultra_ps_e_0_pl_resetn0,
      interconnect_aresetn(0) => NLW_proc_sys_reset_100MHz_interconnect_aresetn_UNCONNECTED(0),
      mb_debug_sys_rst => '0',
      mb_reset => NLW_proc_sys_reset_100MHz_mb_reset_UNCONNECTED,
      peripheral_aresetn(0) => proc_sys_reset_1_peripheral_aresetn(0),
      peripheral_reset(0) => NLW_proc_sys_reset_100MHz_peripheral_reset_UNCONNECTED(0),
      slowest_sync_clk => zynq_ultra_ps_e_0_pl_clk1
    );
proc_sys_reset_10MHz: component zusys_proc_sys_reset_10MHz_0
     port map (
      aux_reset_in => '1',
      bus_struct_reset(0) => NLW_proc_sys_reset_10MHz_bus_struct_reset_UNCONNECTED(0),
      dcm_locked => '1',
      ext_reset_in => zynq_ultra_ps_e_0_pl_resetn0,
      interconnect_aresetn(0) => NLW_proc_sys_reset_10MHz_interconnect_aresetn_UNCONNECTED(0),
      mb_debug_sys_rst => '0',
      mb_reset => NLW_proc_sys_reset_10MHz_mb_reset_UNCONNECTED,
      peripheral_aresetn(0) => proc_sys_reset_10MHz_peripheral_aresetn(0),
      peripheral_reset(0) => NLW_proc_sys_reset_10MHz_peripheral_reset_UNCONNECTED(0),
      slowest_sync_clk => zynq_ultra_ps_e_0_pl_clk2
    );
proc_sys_reset_25MHz: component zusys_proc_sys_reset_25MHz_0
     port map (
      aux_reset_in => '1',
      bus_struct_reset(0) => NLW_proc_sys_reset_25MHz_bus_struct_reset_UNCONNECTED(0),
      dcm_locked => '1',
      ext_reset_in => zynq_ultra_ps_e_0_pl_resetn0,
      interconnect_aresetn(0) => NLW_proc_sys_reset_25MHz_interconnect_aresetn_UNCONNECTED(0),
      mb_debug_sys_rst => '0',
      mb_reset => NLW_proc_sys_reset_25MHz_mb_reset_UNCONNECTED,
      peripheral_aresetn(0) => NLW_proc_sys_reset_25MHz_peripheral_aresetn_UNCONNECTED(0),
      peripheral_reset(0) => NLW_proc_sys_reset_25MHz_peripheral_reset_UNCONNECTED(0),
      slowest_sync_clk => clk_wiz_0_clk_25MHz
    );
proc_sys_reset_50MHz: component zusys_proc_sys_reset_50MHz_0
     port map (
      aux_reset_in => '1',
      bus_struct_reset(0) => NLW_proc_sys_reset_50MHz_bus_struct_reset_UNCONNECTED(0),
      dcm_locked => '1',
      ext_reset_in => zynq_ultra_ps_e_0_pl_resetn0,
      interconnect_aresetn(0) => NLW_proc_sys_reset_50MHz_interconnect_aresetn_UNCONNECTED(0),
      mb_debug_sys_rst => '0',
      mb_reset => NLW_proc_sys_reset_50MHz_mb_reset_UNCONNECTED,
      peripheral_aresetn(0) => proc_sys_reset_50MHz_peripheral_aresetn(0),
      peripheral_reset(0) => NLW_proc_sys_reset_50MHz_peripheral_reset_UNCONNECTED(0),
      slowest_sync_clk => zynq_ultra_ps_e_0_pl_clk3
    );
smartconnect_0: component zusys_smartconnect_0_0
     port map (
      M00_AXI_araddr(5 downto 0) => smartconnect_0_M00_AXI_ARADDR(5 downto 0),
      M00_AXI_arprot(2 downto 0) => smartconnect_0_M00_AXI_ARPROT(2 downto 0),
      M00_AXI_arready => smartconnect_0_M00_AXI_ARREADY,
      M00_AXI_arvalid => smartconnect_0_M00_AXI_ARVALID,
      M00_AXI_awaddr(5 downto 0) => smartconnect_0_M00_AXI_AWADDR(5 downto 0),
      M00_AXI_awprot(2 downto 0) => smartconnect_0_M00_AXI_AWPROT(2 downto 0),
      M00_AXI_awready => smartconnect_0_M00_AXI_AWREADY,
      M00_AXI_awvalid => smartconnect_0_M00_AXI_AWVALID,
      M00_AXI_bready => smartconnect_0_M00_AXI_BREADY,
      M00_AXI_bresp(1 downto 0) => smartconnect_0_M00_AXI_BRESP(1 downto 0),
      M00_AXI_bvalid => smartconnect_0_M00_AXI_BVALID,
      M00_AXI_rdata(31 downto 0) => smartconnect_0_M00_AXI_RDATA(31 downto 0),
      M00_AXI_rready => smartconnect_0_M00_AXI_RREADY,
      M00_AXI_rresp(1 downto 0) => smartconnect_0_M00_AXI_RRESP(1 downto 0),
      M00_AXI_rvalid => smartconnect_0_M00_AXI_RVALID,
      M00_AXI_wdata(31 downto 0) => smartconnect_0_M00_AXI_WDATA(31 downto 0),
      M00_AXI_wready => smartconnect_0_M00_AXI_WREADY,
      M00_AXI_wstrb(3 downto 0) => smartconnect_0_M00_AXI_WSTRB(3 downto 0),
      M00_AXI_wvalid => smartconnect_0_M00_AXI_WVALID,
      M01_AXI_araddr(5 downto 0) => smartconnect_0_M01_AXI_ARADDR(5 downto 0),
      M01_AXI_arprot(2 downto 0) => smartconnect_0_M01_AXI_ARPROT(2 downto 0),
      M01_AXI_arready => smartconnect_0_M01_AXI_ARREADY,
      M01_AXI_arvalid => smartconnect_0_M01_AXI_ARVALID,
      M01_AXI_awaddr(5 downto 0) => smartconnect_0_M01_AXI_AWADDR(5 downto 0),
      M01_AXI_awprot(2 downto 0) => smartconnect_0_M01_AXI_AWPROT(2 downto 0),
      M01_AXI_awready => smartconnect_0_M01_AXI_AWREADY,
      M01_AXI_awvalid => smartconnect_0_M01_AXI_AWVALID,
      M01_AXI_bready => smartconnect_0_M01_AXI_BREADY,
      M01_AXI_bresp(1 downto 0) => smartconnect_0_M01_AXI_BRESP(1 downto 0),
      M01_AXI_bvalid => smartconnect_0_M01_AXI_BVALID,
      M01_AXI_rdata(31 downto 0) => smartconnect_0_M01_AXI_RDATA(31 downto 0),
      M01_AXI_rready => smartconnect_0_M01_AXI_RREADY,
      M01_AXI_rresp(1 downto 0) => smartconnect_0_M01_AXI_RRESP(1 downto 0),
      M01_AXI_rvalid => smartconnect_0_M01_AXI_RVALID,
      M01_AXI_wdata(31 downto 0) => smartconnect_0_M01_AXI_WDATA(31 downto 0),
      M01_AXI_wready => smartconnect_0_M01_AXI_WREADY,
      M01_AXI_wstrb(3 downto 0) => smartconnect_0_M01_AXI_WSTRB(3 downto 0),
      M01_AXI_wvalid => smartconnect_0_M01_AXI_WVALID,
      M02_AXI_araddr(5 downto 0) => smartconnect_0_M02_AXI_ARADDR(5 downto 0),
      M02_AXI_arprot(2 downto 0) => smartconnect_0_M02_AXI_ARPROT(2 downto 0),
      M02_AXI_arready => smartconnect_0_M02_AXI_ARREADY,
      M02_AXI_arvalid => smartconnect_0_M02_AXI_ARVALID,
      M02_AXI_awaddr(5 downto 0) => smartconnect_0_M02_AXI_AWADDR(5 downto 0),
      M02_AXI_awprot(2 downto 0) => smartconnect_0_M02_AXI_AWPROT(2 downto 0),
      M02_AXI_awready => smartconnect_0_M02_AXI_AWREADY,
      M02_AXI_awvalid => smartconnect_0_M02_AXI_AWVALID,
      M02_AXI_bready => smartconnect_0_M02_AXI_BREADY,
      M02_AXI_bresp(1 downto 0) => smartconnect_0_M02_AXI_BRESP(1 downto 0),
      M02_AXI_bvalid => smartconnect_0_M02_AXI_BVALID,
      M02_AXI_rdata(31 downto 0) => smartconnect_0_M02_AXI_RDATA(31 downto 0),
      M02_AXI_rready => smartconnect_0_M02_AXI_RREADY,
      M02_AXI_rresp(1 downto 0) => smartconnect_0_M02_AXI_RRESP(1 downto 0),
      M02_AXI_rvalid => smartconnect_0_M02_AXI_RVALID,
      M02_AXI_wdata(31 downto 0) => smartconnect_0_M02_AXI_WDATA(31 downto 0),
      M02_AXI_wready => smartconnect_0_M02_AXI_WREADY,
      M02_AXI_wstrb(3 downto 0) => smartconnect_0_M02_AXI_WSTRB(3 downto 0),
      M02_AXI_wvalid => smartconnect_0_M02_AXI_WVALID,
      M03_AXI_araddr(15 downto 0) => AXI4_Lite1_1_ARADDR(15 downto 0),
      M03_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M03_AXI_arprot_UNCONNECTED(2 downto 0),
      M03_AXI_arready => AXI4_Lite1_1_ARREADY,
      M03_AXI_arvalid => AXI4_Lite1_1_ARVALID,
      M03_AXI_awaddr(15 downto 0) => AXI4_Lite1_1_AWADDR(15 downto 0),
      M03_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M03_AXI_awprot_UNCONNECTED(2 downto 0),
      M03_AXI_awready => AXI4_Lite1_1_AWREADY,
      M03_AXI_awvalid => AXI4_Lite1_1_AWVALID,
      M03_AXI_bready => AXI4_Lite1_1_BREADY,
      M03_AXI_bresp(1 downto 0) => AXI4_Lite1_1_BRESP(1 downto 0),
      M03_AXI_bvalid => AXI4_Lite1_1_BVALID,
      M03_AXI_rdata(31 downto 0) => AXI4_Lite1_1_RDATA(31 downto 0),
      M03_AXI_rready => AXI4_Lite1_1_RREADY,
      M03_AXI_rresp(1 downto 0) => AXI4_Lite1_1_RRESP(1 downto 0),
      M03_AXI_rvalid => AXI4_Lite1_1_RVALID,
      M03_AXI_wdata(31 downto 0) => AXI4_Lite1_1_WDATA(31 downto 0),
      M03_AXI_wready => AXI4_Lite1_1_WREADY,
      M03_AXI_wstrb(3 downto 0) => AXI4_Lite1_1_WSTRB(3 downto 0),
      M03_AXI_wvalid => AXI4_Lite1_1_WVALID,
      M04_AXI_araddr(15 downto 0) => AXI4_Lite_1_ARADDR(15 downto 0),
      M04_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M04_AXI_arprot_UNCONNECTED(2 downto 0),
      M04_AXI_arready => AXI4_Lite_1_ARREADY,
      M04_AXI_arvalid => AXI4_Lite_1_ARVALID,
      M04_AXI_awaddr(15 downto 0) => AXI4_Lite_1_AWADDR(15 downto 0),
      M04_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M04_AXI_awprot_UNCONNECTED(2 downto 0),
      M04_AXI_awready => AXI4_Lite_1_AWREADY,
      M04_AXI_awvalid => AXI4_Lite_1_AWVALID,
      M04_AXI_bready => AXI4_Lite_1_BREADY,
      M04_AXI_bresp(1 downto 0) => AXI4_Lite_1_BRESP(1 downto 0),
      M04_AXI_bvalid => AXI4_Lite_1_BVALID,
      M04_AXI_rdata(31 downto 0) => AXI4_Lite_1_RDATA(31 downto 0),
      M04_AXI_rready => AXI4_Lite_1_RREADY,
      M04_AXI_rresp(1 downto 0) => AXI4_Lite_1_RRESP(1 downto 0),
      M04_AXI_rvalid => AXI4_Lite_1_RVALID,
      M04_AXI_wdata(31 downto 0) => AXI4_Lite_1_WDATA(31 downto 0),
      M04_AXI_wready => AXI4_Lite_1_WREADY,
      M04_AXI_wstrb(3 downto 0) => AXI4_Lite_1_WSTRB(3 downto 0),
      M04_AXI_wvalid => AXI4_Lite_1_WVALID,
      M05_AXI_araddr(4 downto 0) => smartconnect_0_M05_AXI_ARADDR(4 downto 0),
      M05_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M05_AXI_arprot_UNCONNECTED(2 downto 0),
      M05_AXI_arready => smartconnect_0_M05_AXI_ARREADY,
      M05_AXI_arvalid => smartconnect_0_M05_AXI_ARVALID,
      M05_AXI_awaddr(4 downto 0) => smartconnect_0_M05_AXI_AWADDR(4 downto 0),
      M05_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M05_AXI_awprot_UNCONNECTED(2 downto 0),
      M05_AXI_awready => smartconnect_0_M05_AXI_AWREADY,
      M05_AXI_awvalid => smartconnect_0_M05_AXI_AWVALID,
      M05_AXI_bready => smartconnect_0_M05_AXI_BREADY,
      M05_AXI_bresp(1 downto 0) => smartconnect_0_M05_AXI_BRESP(1 downto 0),
      M05_AXI_bvalid => smartconnect_0_M05_AXI_BVALID,
      M05_AXI_rdata(31 downto 0) => smartconnect_0_M05_AXI_RDATA(31 downto 0),
      M05_AXI_rready => smartconnect_0_M05_AXI_RREADY,
      M05_AXI_rresp(1 downto 0) => smartconnect_0_M05_AXI_RRESP(1 downto 0),
      M05_AXI_rvalid => smartconnect_0_M05_AXI_RVALID,
      M05_AXI_wdata(31 downto 0) => smartconnect_0_M05_AXI_WDATA(31 downto 0),
      M05_AXI_wready => smartconnect_0_M05_AXI_WREADY,
      M05_AXI_wstrb(3 downto 0) => smartconnect_0_M05_AXI_WSTRB(3 downto 0),
      M05_AXI_wvalid => smartconnect_0_M05_AXI_WVALID,
      M06_AXI_araddr(8 downto 0) => smartconnect_0_M06_AXI_ARADDR(8 downto 0),
      M06_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M06_AXI_arprot_UNCONNECTED(2 downto 0),
      M06_AXI_arready => smartconnect_0_M06_AXI_ARREADY,
      M06_AXI_arvalid => smartconnect_0_M06_AXI_ARVALID,
      M06_AXI_awaddr(8 downto 0) => smartconnect_0_M06_AXI_AWADDR(8 downto 0),
      M06_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M06_AXI_awprot_UNCONNECTED(2 downto 0),
      M06_AXI_awready => smartconnect_0_M06_AXI_AWREADY,
      M06_AXI_awvalid => smartconnect_0_M06_AXI_AWVALID,
      M06_AXI_bready => smartconnect_0_M06_AXI_BREADY,
      M06_AXI_bresp(1 downto 0) => smartconnect_0_M06_AXI_BRESP(1 downto 0),
      M06_AXI_bvalid => smartconnect_0_M06_AXI_BVALID,
      M06_AXI_rdata(31 downto 0) => smartconnect_0_M06_AXI_RDATA(31 downto 0),
      M06_AXI_rready => smartconnect_0_M06_AXI_RREADY,
      M06_AXI_rresp(1 downto 0) => smartconnect_0_M06_AXI_RRESP(1 downto 0),
      M06_AXI_rvalid => smartconnect_0_M06_AXI_RVALID,
      M06_AXI_wdata(31 downto 0) => smartconnect_0_M06_AXI_WDATA(31 downto 0),
      M06_AXI_wready => smartconnect_0_M06_AXI_WREADY,
      M06_AXI_wstrb(3 downto 0) => smartconnect_0_M06_AXI_WSTRB(3 downto 0),
      M06_AXI_wvalid => smartconnect_0_M06_AXI_WVALID,
      M07_AXI_araddr(15 downto 0) => smartconnect_0_M07_AXI_ARADDR(15 downto 0),
      M07_AXI_arburst(1 downto 0) => smartconnect_0_M07_AXI_ARBURST(1 downto 0),
      M07_AXI_arcache(3 downto 0) => smartconnect_0_M07_AXI_ARCACHE(3 downto 0),
      M07_AXI_arlen(7 downto 0) => smartconnect_0_M07_AXI_ARLEN(7 downto 0),
      M07_AXI_arlock(0) => smartconnect_0_M07_AXI_ARLOCK(0),
      M07_AXI_arprot(2 downto 0) => smartconnect_0_M07_AXI_ARPROT(2 downto 0),
      M07_AXI_arqos(3 downto 0) => NLW_smartconnect_0_M07_AXI_arqos_UNCONNECTED(3 downto 0),
      M07_AXI_arready => smartconnect_0_M07_AXI_ARREADY,
      M07_AXI_arsize(2 downto 0) => smartconnect_0_M07_AXI_ARSIZE(2 downto 0),
      M07_AXI_aruser(15 downto 0) => NLW_smartconnect_0_M07_AXI_aruser_UNCONNECTED(15 downto 0),
      M07_AXI_arvalid => smartconnect_0_M07_AXI_ARVALID,
      M07_AXI_awaddr(15 downto 0) => smartconnect_0_M07_AXI_AWADDR(15 downto 0),
      M07_AXI_awburst(1 downto 0) => smartconnect_0_M07_AXI_AWBURST(1 downto 0),
      M07_AXI_awcache(3 downto 0) => smartconnect_0_M07_AXI_AWCACHE(3 downto 0),
      M07_AXI_awlen(7 downto 0) => smartconnect_0_M07_AXI_AWLEN(7 downto 0),
      M07_AXI_awlock(0) => smartconnect_0_M07_AXI_AWLOCK(0),
      M07_AXI_awprot(2 downto 0) => smartconnect_0_M07_AXI_AWPROT(2 downto 0),
      M07_AXI_awqos(3 downto 0) => NLW_smartconnect_0_M07_AXI_awqos_UNCONNECTED(3 downto 0),
      M07_AXI_awready => smartconnect_0_M07_AXI_AWREADY,
      M07_AXI_awsize(2 downto 0) => smartconnect_0_M07_AXI_AWSIZE(2 downto 0),
      M07_AXI_awuser(15 downto 0) => NLW_smartconnect_0_M07_AXI_awuser_UNCONNECTED(15 downto 0),
      M07_AXI_awvalid => smartconnect_0_M07_AXI_AWVALID,
      M07_AXI_bready => smartconnect_0_M07_AXI_BREADY,
      M07_AXI_bresp(1 downto 0) => smartconnect_0_M07_AXI_BRESP(1 downto 0),
      M07_AXI_bvalid => smartconnect_0_M07_AXI_BVALID,
      M07_AXI_rdata(31 downto 0) => smartconnect_0_M07_AXI_RDATA(31 downto 0),
      M07_AXI_rlast => smartconnect_0_M07_AXI_RLAST,
      M07_AXI_rready => smartconnect_0_M07_AXI_RREADY,
      M07_AXI_rresp(1 downto 0) => smartconnect_0_M07_AXI_RRESP(1 downto 0),
      M07_AXI_rvalid => smartconnect_0_M07_AXI_RVALID,
      M07_AXI_wdata(31 downto 0) => smartconnect_0_M07_AXI_WDATA(31 downto 0),
      M07_AXI_wlast => smartconnect_0_M07_AXI_WLAST,
      M07_AXI_wready => smartconnect_0_M07_AXI_WREADY,
      M07_AXI_wstrb(3 downto 0) => smartconnect_0_M07_AXI_WSTRB(3 downto 0),
      M07_AXI_wvalid => smartconnect_0_M07_AXI_WVALID,
      M08_AXI_araddr(15 downto 0) => smartconnect_0_M08_AXI_ARADDR(15 downto 0),
      M08_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M08_AXI_arprot_UNCONNECTED(2 downto 0),
      M08_AXI_arready => smartconnect_0_M08_AXI_ARREADY,
      M08_AXI_arvalid => smartconnect_0_M08_AXI_ARVALID,
      M08_AXI_awaddr(15 downto 0) => smartconnect_0_M08_AXI_AWADDR(15 downto 0),
      M08_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M08_AXI_awprot_UNCONNECTED(2 downto 0),
      M08_AXI_awready => smartconnect_0_M08_AXI_AWREADY,
      M08_AXI_awvalid => smartconnect_0_M08_AXI_AWVALID,
      M08_AXI_bready => smartconnect_0_M08_AXI_BREADY,
      M08_AXI_bresp(1 downto 0) => smartconnect_0_M08_AXI_BRESP(1 downto 0),
      M08_AXI_bvalid => smartconnect_0_M08_AXI_BVALID,
      M08_AXI_rdata(31 downto 0) => smartconnect_0_M08_AXI_RDATA(31 downto 0),
      M08_AXI_rready => smartconnect_0_M08_AXI_RREADY,
      M08_AXI_rresp(1 downto 0) => smartconnect_0_M08_AXI_RRESP(1 downto 0),
      M08_AXI_rvalid => smartconnect_0_M08_AXI_RVALID,
      M08_AXI_wdata(31 downto 0) => smartconnect_0_M08_AXI_WDATA(31 downto 0),
      M08_AXI_wready => smartconnect_0_M08_AXI_WREADY,
      M08_AXI_wstrb(3 downto 0) => smartconnect_0_M08_AXI_WSTRB(3 downto 0),
      M08_AXI_wvalid => smartconnect_0_M08_AXI_WVALID,
      M09_AXI_araddr(15 downto 0) => smartconnect_0_M09_AXI_ARADDR(15 downto 0),
      M09_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M09_AXI_arprot_UNCONNECTED(2 downto 0),
      M09_AXI_arready => smartconnect_0_M09_AXI_ARREADY,
      M09_AXI_arvalid => smartconnect_0_M09_AXI_ARVALID,
      M09_AXI_awaddr(15 downto 0) => smartconnect_0_M09_AXI_AWADDR(15 downto 0),
      M09_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M09_AXI_awprot_UNCONNECTED(2 downto 0),
      M09_AXI_awready => smartconnect_0_M09_AXI_AWREADY,
      M09_AXI_awvalid => smartconnect_0_M09_AXI_AWVALID,
      M09_AXI_bready => smartconnect_0_M09_AXI_BREADY,
      M09_AXI_bresp(1 downto 0) => smartconnect_0_M09_AXI_BRESP(1 downto 0),
      M09_AXI_bvalid => smartconnect_0_M09_AXI_BVALID,
      M09_AXI_rdata(31 downto 0) => smartconnect_0_M09_AXI_RDATA(31 downto 0),
      M09_AXI_rready => smartconnect_0_M09_AXI_RREADY,
      M09_AXI_rresp(1 downto 0) => smartconnect_0_M09_AXI_RRESP(1 downto 0),
      M09_AXI_rvalid => smartconnect_0_M09_AXI_RVALID,
      M09_AXI_wdata(31 downto 0) => smartconnect_0_M09_AXI_WDATA(31 downto 0),
      M09_AXI_wready => smartconnect_0_M09_AXI_WREADY,
      M09_AXI_wstrb(3 downto 0) => smartconnect_0_M09_AXI_WSTRB(3 downto 0),
      M09_AXI_wvalid => smartconnect_0_M09_AXI_WVALID,
      M10_AXI_araddr(39 downto 0) => smartconnect_0_M10_AXI_ARADDR(39 downto 0),
      M10_AXI_arburst(1 downto 0) => smartconnect_0_M10_AXI_ARBURST(1 downto 0),
      M10_AXI_arcache(3 downto 0) => smartconnect_0_M10_AXI_ARCACHE(3 downto 0),
      M10_AXI_arid(2 downto 0) => smartconnect_0_M10_AXI_ARID(2 downto 0),
      M10_AXI_arlen(7 downto 0) => smartconnect_0_M10_AXI_ARLEN(7 downto 0),
      M10_AXI_arlock(0) => smartconnect_0_M10_AXI_ARLOCK(0),
      M10_AXI_arprot(2 downto 0) => smartconnect_0_M10_AXI_ARPROT(2 downto 0),
      M10_AXI_arqos(3 downto 0) => smartconnect_0_M10_AXI_ARQOS(3 downto 0),
      M10_AXI_arready => smartconnect_0_M10_AXI_ARREADY,
      M10_AXI_arsize(2 downto 0) => smartconnect_0_M10_AXI_ARSIZE(2 downto 0),
      M10_AXI_aruser(129 downto 0) => smartconnect_0_M10_AXI_ARUSER(129 downto 0),
      M10_AXI_arvalid => smartconnect_0_M10_AXI_ARVALID,
      M10_AXI_awaddr(39 downto 0) => smartconnect_0_M10_AXI_AWADDR(39 downto 0),
      M10_AXI_awburst(1 downto 0) => smartconnect_0_M10_AXI_AWBURST(1 downto 0),
      M10_AXI_awcache(3 downto 0) => smartconnect_0_M10_AXI_AWCACHE(3 downto 0),
      M10_AXI_awid(2 downto 0) => smartconnect_0_M10_AXI_AWID(2 downto 0),
      M10_AXI_awlen(7 downto 0) => smartconnect_0_M10_AXI_AWLEN(7 downto 0),
      M10_AXI_awlock(0) => smartconnect_0_M10_AXI_AWLOCK(0),
      M10_AXI_awprot(2 downto 0) => smartconnect_0_M10_AXI_AWPROT(2 downto 0),
      M10_AXI_awqos(3 downto 0) => smartconnect_0_M10_AXI_AWQOS(3 downto 0),
      M10_AXI_awready => smartconnect_0_M10_AXI_AWREADY,
      M10_AXI_awsize(2 downto 0) => smartconnect_0_M10_AXI_AWSIZE(2 downto 0),
      M10_AXI_awuser(129 downto 0) => smartconnect_0_M10_AXI_AWUSER(129 downto 0),
      M10_AXI_awvalid => smartconnect_0_M10_AXI_AWVALID,
      M10_AXI_bid(2 downto 0) => smartconnect_0_M10_AXI_BID(2 downto 0),
      M10_AXI_bready => smartconnect_0_M10_AXI_BREADY,
      M10_AXI_bresp(1 downto 0) => smartconnect_0_M10_AXI_BRESP(1 downto 0),
      M10_AXI_buser(113 downto 0) => smartconnect_0_M10_AXI_BUSER(113 downto 0),
      M10_AXI_bvalid => smartconnect_0_M10_AXI_BVALID,
      M10_AXI_rdata(127 downto 0) => smartconnect_0_M10_AXI_RDATA(127 downto 0),
      M10_AXI_rid(2 downto 0) => smartconnect_0_M10_AXI_RID(2 downto 0),
      M10_AXI_rlast => smartconnect_0_M10_AXI_RLAST,
      M10_AXI_rready => smartconnect_0_M10_AXI_RREADY,
      M10_AXI_rresp(1 downto 0) => smartconnect_0_M10_AXI_RRESP(1 downto 0),
      M10_AXI_ruser(13 downto 0) => smartconnect_0_M10_AXI_RUSER(13 downto 0),
      M10_AXI_rvalid => smartconnect_0_M10_AXI_RVALID,
      M10_AXI_wdata(127 downto 0) => smartconnect_0_M10_AXI_WDATA(127 downto 0),
      M10_AXI_wlast => smartconnect_0_M10_AXI_WLAST,
      M10_AXI_wready => smartconnect_0_M10_AXI_WREADY,
      M10_AXI_wstrb(15 downto 0) => smartconnect_0_M10_AXI_WSTRB(15 downto 0),
      M10_AXI_wuser(13 downto 0) => smartconnect_0_M10_AXI_WUSER(13 downto 0),
      M10_AXI_wvalid => smartconnect_0_M10_AXI_WVALID,
      M11_AXI_araddr(4 downto 0) => smartconnect_0_M11_AXI_ARADDR(4 downto 0),
      M11_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M11_AXI_arprot_UNCONNECTED(2 downto 0),
      M11_AXI_arready => smartconnect_0_M11_AXI_ARREADY,
      M11_AXI_arvalid => smartconnect_0_M11_AXI_ARVALID,
      M11_AXI_awaddr(4 downto 0) => smartconnect_0_M11_AXI_AWADDR(4 downto 0),
      M11_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M11_AXI_awprot_UNCONNECTED(2 downto 0),
      M11_AXI_awready => smartconnect_0_M11_AXI_AWREADY,
      M11_AXI_awvalid => smartconnect_0_M11_AXI_AWVALID,
      M11_AXI_bready => smartconnect_0_M11_AXI_BREADY,
      M11_AXI_bresp(1 downto 0) => smartconnect_0_M11_AXI_BRESP(1 downto 0),
      M11_AXI_bvalid => smartconnect_0_M11_AXI_BVALID,
      M11_AXI_rdata(31 downto 0) => smartconnect_0_M11_AXI_RDATA(31 downto 0),
      M11_AXI_rready => smartconnect_0_M11_AXI_RREADY,
      M11_AXI_rresp(1 downto 0) => smartconnect_0_M11_AXI_RRESP(1 downto 0),
      M11_AXI_rvalid => smartconnect_0_M11_AXI_RVALID,
      M11_AXI_wdata(31 downto 0) => smartconnect_0_M11_AXI_WDATA(31 downto 0),
      M11_AXI_wready => smartconnect_0_M11_AXI_WREADY,
      M11_AXI_wstrb(3 downto 0) => smartconnect_0_M11_AXI_WSTRB(3 downto 0),
      M11_AXI_wvalid => smartconnect_0_M11_AXI_WVALID,
      M12_AXI_araddr(15 downto 0) => smartconnect_0_M12_AXI_ARADDR(15 downto 0),
      M12_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M12_AXI_arprot_UNCONNECTED(2 downto 0),
      M12_AXI_arready => smartconnect_0_M12_AXI_ARREADY,
      M12_AXI_arvalid => smartconnect_0_M12_AXI_ARVALID,
      M12_AXI_awaddr(15 downto 0) => smartconnect_0_M12_AXI_AWADDR(15 downto 0),
      M12_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M12_AXI_awprot_UNCONNECTED(2 downto 0),
      M12_AXI_awready => smartconnect_0_M12_AXI_AWREADY,
      M12_AXI_awvalid => smartconnect_0_M12_AXI_AWVALID,
      M12_AXI_bready => smartconnect_0_M12_AXI_BREADY,
      M12_AXI_bresp(1 downto 0) => smartconnect_0_M12_AXI_BRESP(1 downto 0),
      M12_AXI_bvalid => smartconnect_0_M12_AXI_BVALID,
      M12_AXI_rdata(31 downto 0) => smartconnect_0_M12_AXI_RDATA(31 downto 0),
      M12_AXI_rready => smartconnect_0_M12_AXI_RREADY,
      M12_AXI_rresp(1 downto 0) => smartconnect_0_M12_AXI_RRESP(1 downto 0),
      M12_AXI_rvalid => smartconnect_0_M12_AXI_RVALID,
      M12_AXI_wdata(31 downto 0) => smartconnect_0_M12_AXI_WDATA(31 downto 0),
      M12_AXI_wready => smartconnect_0_M12_AXI_WREADY,
      M12_AXI_wstrb(3 downto 0) => smartconnect_0_M12_AXI_WSTRB(3 downto 0),
      M12_AXI_wvalid => smartconnect_0_M12_AXI_WVALID,
      M13_AXI_araddr(15 downto 0) => smartconnect_0_M13_AXI_ARADDR(15 downto 0),
      M13_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M13_AXI_arprot_UNCONNECTED(2 downto 0),
      M13_AXI_arready => smartconnect_0_M13_AXI_ARREADY,
      M13_AXI_arvalid => smartconnect_0_M13_AXI_ARVALID,
      M13_AXI_awaddr(15 downto 0) => smartconnect_0_M13_AXI_AWADDR(15 downto 0),
      M13_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M13_AXI_awprot_UNCONNECTED(2 downto 0),
      M13_AXI_awready => smartconnect_0_M13_AXI_AWREADY,
      M13_AXI_awvalid => smartconnect_0_M13_AXI_AWVALID,
      M13_AXI_bready => smartconnect_0_M13_AXI_BREADY,
      M13_AXI_bresp(1 downto 0) => smartconnect_0_M13_AXI_BRESP(1 downto 0),
      M13_AXI_bvalid => smartconnect_0_M13_AXI_BVALID,
      M13_AXI_rdata(31 downto 0) => smartconnect_0_M13_AXI_RDATA(31 downto 0),
      M13_AXI_rready => smartconnect_0_M13_AXI_RREADY,
      M13_AXI_rresp(1 downto 0) => smartconnect_0_M13_AXI_RRESP(1 downto 0),
      M13_AXI_rvalid => smartconnect_0_M13_AXI_RVALID,
      M13_AXI_wdata(31 downto 0) => smartconnect_0_M13_AXI_WDATA(31 downto 0),
      M13_AXI_wready => smartconnect_0_M13_AXI_WREADY,
      M13_AXI_wstrb(3 downto 0) => smartconnect_0_M13_AXI_WSTRB(3 downto 0),
      M13_AXI_wvalid => smartconnect_0_M13_AXI_WVALID,
      M14_AXI_araddr(15 downto 0) => NLW_smartconnect_0_M14_AXI_araddr_UNCONNECTED(15 downto 0),
      M14_AXI_arprot(2 downto 0) => NLW_smartconnect_0_M14_AXI_arprot_UNCONNECTED(2 downto 0),
      M14_AXI_arready => '0',
      M14_AXI_arvalid => NLW_smartconnect_0_M14_AXI_arvalid_UNCONNECTED,
      M14_AXI_awaddr(15 downto 0) => NLW_smartconnect_0_M14_AXI_awaddr_UNCONNECTED(15 downto 0),
      M14_AXI_awprot(2 downto 0) => NLW_smartconnect_0_M14_AXI_awprot_UNCONNECTED(2 downto 0),
      M14_AXI_awready => '0',
      M14_AXI_awvalid => NLW_smartconnect_0_M14_AXI_awvalid_UNCONNECTED,
      M14_AXI_bready => NLW_smartconnect_0_M14_AXI_bready_UNCONNECTED,
      M14_AXI_bresp(1 downto 0) => B"00",
      M14_AXI_bvalid => '0',
      M14_AXI_rdata(31 downto 0) => B"00000000000000000000000000000000",
      M14_AXI_rready => NLW_smartconnect_0_M14_AXI_rready_UNCONNECTED,
      M14_AXI_rresp(1 downto 0) => B"00",
      M14_AXI_rvalid => '0',
      M14_AXI_wdata(31 downto 0) => NLW_smartconnect_0_M14_AXI_wdata_UNCONNECTED(31 downto 0),
      M14_AXI_wready => '0',
      M14_AXI_wstrb(3 downto 0) => NLW_smartconnect_0_M14_AXI_wstrb_UNCONNECTED(3 downto 0),
      M14_AXI_wvalid => NLW_smartconnect_0_M14_AXI_wvalid_UNCONNECTED,
      S00_AXI_araddr(39 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARADDR(39 downto 0),
      S00_AXI_arburst(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARBURST(1 downto 0),
      S00_AXI_arcache(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARCACHE(3 downto 0),
      S00_AXI_arid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARID(15 downto 0),
      S00_AXI_arlen(7 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARLEN(7 downto 0),
      S00_AXI_arlock(0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARLOCK,
      S00_AXI_arprot(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARPROT(2 downto 0),
      S00_AXI_arqos(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARQOS(3 downto 0),
      S00_AXI_arready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARREADY,
      S00_AXI_arsize(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARSIZE(2 downto 0),
      S00_AXI_aruser(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARUSER(15 downto 0),
      S00_AXI_arvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARVALID,
      S00_AXI_awaddr(39 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWADDR(39 downto 0),
      S00_AXI_awburst(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWBURST(1 downto 0),
      S00_AXI_awcache(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWCACHE(3 downto 0),
      S00_AXI_awid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWID(15 downto 0),
      S00_AXI_awlen(7 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWLEN(7 downto 0),
      S00_AXI_awlock(0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWLOCK,
      S00_AXI_awprot(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWPROT(2 downto 0),
      S00_AXI_awqos(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWQOS(3 downto 0),
      S00_AXI_awready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWREADY,
      S00_AXI_awsize(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWSIZE(2 downto 0),
      S00_AXI_awuser(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWUSER(15 downto 0),
      S00_AXI_awvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWVALID,
      S00_AXI_bid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BID(15 downto 0),
      S00_AXI_bready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BREADY,
      S00_AXI_bresp(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BRESP(1 downto 0),
      S00_AXI_bvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BVALID,
      S00_AXI_rdata(127 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RDATA(127 downto 0),
      S00_AXI_rid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RID(15 downto 0),
      S00_AXI_rlast => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RLAST,
      S00_AXI_rready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RREADY,
      S00_AXI_rresp(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RRESP(1 downto 0),
      S00_AXI_rvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RVALID,
      S00_AXI_wdata(127 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WDATA(127 downto 0),
      S00_AXI_wlast => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WLAST,
      S00_AXI_wready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WREADY,
      S00_AXI_wstrb(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WSTRB(15 downto 0),
      S00_AXI_wvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WVALID,
      aclk => zynq_ultra_ps_e_0_pl_clk1,
      aclk1 => zynq_ultra_ps_e_0_pl_clk2,
      aclk2 => zynq_ultra_ps_e_0_pl_clk3,
      aresetn => proc_sys_reset_1_peripheral_aresetn(0)
    );
smartconnect_1: component zusys_smartconnect_1_0
     port map (
      M00_AXI_araddr(15 downto 0) => smartconnect_1_M00_AXI_ARADDR(15 downto 0),
      M00_AXI_arburst(1 downto 0) => smartconnect_1_M00_AXI_ARBURST(1 downto 0),
      M00_AXI_arcache(3 downto 0) => smartconnect_1_M00_AXI_ARCACHE(3 downto 0),
      M00_AXI_arlen(7 downto 0) => smartconnect_1_M00_AXI_ARLEN(7 downto 0),
      M00_AXI_arlock(0) => smartconnect_1_M00_AXI_ARLOCK(0),
      M00_AXI_arprot(2 downto 0) => smartconnect_1_M00_AXI_ARPROT(2 downto 0),
      M00_AXI_arqos(3 downto 0) => NLW_smartconnect_1_M00_AXI_arqos_UNCONNECTED(3 downto 0),
      M00_AXI_arready => smartconnect_1_M00_AXI_ARREADY,
      M00_AXI_arsize(2 downto 0) => smartconnect_1_M00_AXI_ARSIZE(2 downto 0),
      M00_AXI_aruser(15 downto 0) => NLW_smartconnect_1_M00_AXI_aruser_UNCONNECTED(15 downto 0),
      M00_AXI_arvalid => smartconnect_1_M00_AXI_ARVALID,
      M00_AXI_awaddr(15 downto 0) => smartconnect_1_M00_AXI_AWADDR(15 downto 0),
      M00_AXI_awburst(1 downto 0) => smartconnect_1_M00_AXI_AWBURST(1 downto 0),
      M00_AXI_awcache(3 downto 0) => smartconnect_1_M00_AXI_AWCACHE(3 downto 0),
      M00_AXI_awlen(7 downto 0) => smartconnect_1_M00_AXI_AWLEN(7 downto 0),
      M00_AXI_awlock(0) => smartconnect_1_M00_AXI_AWLOCK(0),
      M00_AXI_awprot(2 downto 0) => smartconnect_1_M00_AXI_AWPROT(2 downto 0),
      M00_AXI_awqos(3 downto 0) => NLW_smartconnect_1_M00_AXI_awqos_UNCONNECTED(3 downto 0),
      M00_AXI_awready => smartconnect_1_M00_AXI_AWREADY,
      M00_AXI_awsize(2 downto 0) => smartconnect_1_M00_AXI_AWSIZE(2 downto 0),
      M00_AXI_awuser(15 downto 0) => NLW_smartconnect_1_M00_AXI_awuser_UNCONNECTED(15 downto 0),
      M00_AXI_awvalid => smartconnect_1_M00_AXI_AWVALID,
      M00_AXI_bready => smartconnect_1_M00_AXI_BREADY,
      M00_AXI_bresp(1 downto 0) => smartconnect_1_M00_AXI_BRESP(1 downto 0),
      M00_AXI_bvalid => smartconnect_1_M00_AXI_BVALID,
      M00_AXI_rdata(31 downto 0) => smartconnect_1_M00_AXI_RDATA(31 downto 0),
      M00_AXI_rlast => smartconnect_1_M00_AXI_RLAST,
      M00_AXI_rready => smartconnect_1_M00_AXI_RREADY,
      M00_AXI_rresp(1 downto 0) => smartconnect_1_M00_AXI_RRESP(1 downto 0),
      M00_AXI_rvalid => smartconnect_1_M00_AXI_RVALID,
      M00_AXI_wdata(31 downto 0) => smartconnect_1_M00_AXI_WDATA(31 downto 0),
      M00_AXI_wlast => smartconnect_1_M00_AXI_WLAST,
      M00_AXI_wready => smartconnect_1_M00_AXI_WREADY,
      M00_AXI_wstrb(3 downto 0) => smartconnect_1_M00_AXI_WSTRB(3 downto 0),
      M00_AXI_wvalid => smartconnect_1_M00_AXI_WVALID,
      S00_AXI_araddr(39 downto 0) => smartconnect_0_M10_AXI_ARADDR(39 downto 0),
      S00_AXI_arburst(1 downto 0) => smartconnect_0_M10_AXI_ARBURST(1 downto 0),
      S00_AXI_arcache(3 downto 0) => smartconnect_0_M10_AXI_ARCACHE(3 downto 0),
      S00_AXI_arid(2 downto 0) => smartconnect_0_M10_AXI_ARID(2 downto 0),
      S00_AXI_arlen(7 downto 0) => smartconnect_0_M10_AXI_ARLEN(7 downto 0),
      S00_AXI_arlock(0) => smartconnect_0_M10_AXI_ARLOCK(0),
      S00_AXI_arprot(2 downto 0) => smartconnect_0_M10_AXI_ARPROT(2 downto 0),
      S00_AXI_arqos(3 downto 0) => smartconnect_0_M10_AXI_ARQOS(3 downto 0),
      S00_AXI_arready => smartconnect_0_M10_AXI_ARREADY,
      S00_AXI_arsize(2 downto 0) => smartconnect_0_M10_AXI_ARSIZE(2 downto 0),
      S00_AXI_aruser(129 downto 0) => smartconnect_0_M10_AXI_ARUSER(129 downto 0),
      S00_AXI_arvalid => smartconnect_0_M10_AXI_ARVALID,
      S00_AXI_awaddr(39 downto 0) => smartconnect_0_M10_AXI_AWADDR(39 downto 0),
      S00_AXI_awburst(1 downto 0) => smartconnect_0_M10_AXI_AWBURST(1 downto 0),
      S00_AXI_awcache(3 downto 0) => smartconnect_0_M10_AXI_AWCACHE(3 downto 0),
      S00_AXI_awid(2 downto 0) => smartconnect_0_M10_AXI_AWID(2 downto 0),
      S00_AXI_awlen(7 downto 0) => smartconnect_0_M10_AXI_AWLEN(7 downto 0),
      S00_AXI_awlock(0) => smartconnect_0_M10_AXI_AWLOCK(0),
      S00_AXI_awprot(2 downto 0) => smartconnect_0_M10_AXI_AWPROT(2 downto 0),
      S00_AXI_awqos(3 downto 0) => smartconnect_0_M10_AXI_AWQOS(3 downto 0),
      S00_AXI_awready => smartconnect_0_M10_AXI_AWREADY,
      S00_AXI_awsize(2 downto 0) => smartconnect_0_M10_AXI_AWSIZE(2 downto 0),
      S00_AXI_awuser(129 downto 0) => smartconnect_0_M10_AXI_AWUSER(129 downto 0),
      S00_AXI_awvalid => smartconnect_0_M10_AXI_AWVALID,
      S00_AXI_bid(2 downto 0) => smartconnect_0_M10_AXI_BID(2 downto 0),
      S00_AXI_bready => smartconnect_0_M10_AXI_BREADY,
      S00_AXI_bresp(1 downto 0) => smartconnect_0_M10_AXI_BRESP(1 downto 0),
      S00_AXI_buser(113 downto 0) => smartconnect_0_M10_AXI_BUSER(113 downto 0),
      S00_AXI_bvalid => smartconnect_0_M10_AXI_BVALID,
      S00_AXI_rdata(127 downto 0) => smartconnect_0_M10_AXI_RDATA(127 downto 0),
      S00_AXI_rid(2 downto 0) => smartconnect_0_M10_AXI_RID(2 downto 0),
      S00_AXI_rlast => smartconnect_0_M10_AXI_RLAST,
      S00_AXI_rready => smartconnect_0_M10_AXI_RREADY,
      S00_AXI_rresp(1 downto 0) => smartconnect_0_M10_AXI_RRESP(1 downto 0),
      S00_AXI_ruser(13 downto 0) => smartconnect_0_M10_AXI_RUSER(13 downto 0),
      S00_AXI_rvalid => smartconnect_0_M10_AXI_RVALID,
      S00_AXI_wdata(127 downto 0) => smartconnect_0_M10_AXI_WDATA(127 downto 0),
      S00_AXI_wlast => smartconnect_0_M10_AXI_WLAST,
      S00_AXI_wready => smartconnect_0_M10_AXI_WREADY,
      S00_AXI_wstrb(15 downto 0) => smartconnect_0_M10_AXI_WSTRB(15 downto 0),
      S00_AXI_wuser(13 downto 0) => smartconnect_0_M10_AXI_WUSER(13 downto 0),
      S00_AXI_wvalid => smartconnect_0_M10_AXI_WVALID,
      aclk => zynq_ultra_ps_e_0_pl_clk1,
      aresetn => proc_sys_reset_1_peripheral_aresetn(0)
    );
timer_uptime_64bit: component zusys_timer_uptime_64bit_0
     port map (
      capturetrig0 => '0',
      capturetrig1 => '0',
      freeze => '0',
      generateout0 => NLW_timer_uptime_64bit_generateout0_UNCONNECTED,
      generateout1 => NLW_timer_uptime_64bit_generateout1_UNCONNECTED,
      interrupt => NLW_timer_uptime_64bit_interrupt_UNCONNECTED,
      pwm0 => NLW_timer_uptime_64bit_pwm0_UNCONNECTED,
      s_axi_aclk => zynq_ultra_ps_e_0_pl_clk1,
      s_axi_araddr(4 downto 0) => smartconnect_0_M05_AXI_ARADDR(4 downto 0),
      s_axi_aresetn => proc_sys_reset_1_peripheral_aresetn(0),
      s_axi_arready => smartconnect_0_M05_AXI_ARREADY,
      s_axi_arvalid => smartconnect_0_M05_AXI_ARVALID,
      s_axi_awaddr(4 downto 0) => smartconnect_0_M05_AXI_AWADDR(4 downto 0),
      s_axi_awready => smartconnect_0_M05_AXI_AWREADY,
      s_axi_awvalid => smartconnect_0_M05_AXI_AWVALID,
      s_axi_bready => smartconnect_0_M05_AXI_BREADY,
      s_axi_bresp(1 downto 0) => smartconnect_0_M05_AXI_BRESP(1 downto 0),
      s_axi_bvalid => smartconnect_0_M05_AXI_BVALID,
      s_axi_rdata(31 downto 0) => smartconnect_0_M05_AXI_RDATA(31 downto 0),
      s_axi_rready => smartconnect_0_M05_AXI_RREADY,
      s_axi_rresp(1 downto 0) => smartconnect_0_M05_AXI_RRESP(1 downto 0),
      s_axi_rvalid => smartconnect_0_M05_AXI_RVALID,
      s_axi_wdata(31 downto 0) => smartconnect_0_M05_AXI_WDATA(31 downto 0),
      s_axi_wready => smartconnect_0_M05_AXI_WREADY,
      s_axi_wstrb(3 downto 0) => smartconnect_0_M05_AXI_WSTRB(3 downto 0),
      s_axi_wvalid => smartconnect_0_M05_AXI_WVALID
    );
uz_axi_testIP_0: component zusys_uz_axi_testIP_0_0
     port map (
      AXI4_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_ARADDR(15 downto 0) => smartconnect_1_M00_AXI_ARADDR(15 downto 0),
      AXI4_ARBURST(1 downto 0) => smartconnect_1_M00_AXI_ARBURST(1 downto 0),
      AXI4_ARCACHE(3 downto 0) => smartconnect_1_M00_AXI_ARCACHE(3 downto 0),
      AXI4_ARESETN => proc_sys_reset_1_peripheral_aresetn(0),
      AXI4_ARID(11 downto 0) => B"000000000000",
      AXI4_ARLEN(7 downto 0) => smartconnect_1_M00_AXI_ARLEN(7 downto 0),
      AXI4_ARLOCK => smartconnect_1_M00_AXI_ARLOCK(0),
      AXI4_ARPROT(2 downto 0) => smartconnect_1_M00_AXI_ARPROT(2 downto 0),
      AXI4_ARREADY => smartconnect_1_M00_AXI_ARREADY,
      AXI4_ARSIZE(2 downto 0) => smartconnect_1_M00_AXI_ARSIZE(2 downto 0),
      AXI4_ARVALID => smartconnect_1_M00_AXI_ARVALID,
      AXI4_AWADDR(15 downto 0) => smartconnect_1_M00_AXI_AWADDR(15 downto 0),
      AXI4_AWBURST(1 downto 0) => smartconnect_1_M00_AXI_AWBURST(1 downto 0),
      AXI4_AWCACHE(3 downto 0) => smartconnect_1_M00_AXI_AWCACHE(3 downto 0),
      AXI4_AWID(11 downto 0) => B"000000000000",
      AXI4_AWLEN(7 downto 0) => smartconnect_1_M00_AXI_AWLEN(7 downto 0),
      AXI4_AWLOCK => smartconnect_1_M00_AXI_AWLOCK(0),
      AXI4_AWPROT(2 downto 0) => smartconnect_1_M00_AXI_AWPROT(2 downto 0),
      AXI4_AWREADY => smartconnect_1_M00_AXI_AWREADY,
      AXI4_AWSIZE(2 downto 0) => smartconnect_1_M00_AXI_AWSIZE(2 downto 0),
      AXI4_AWVALID => smartconnect_1_M00_AXI_AWVALID,
      AXI4_BID(11 downto 0) => NLW_uz_axi_testIP_0_AXI4_BID_UNCONNECTED(11 downto 0),
      AXI4_BREADY => smartconnect_1_M00_AXI_BREADY,
      AXI4_BRESP(1 downto 0) => smartconnect_1_M00_AXI_BRESP(1 downto 0),
      AXI4_BVALID => smartconnect_1_M00_AXI_BVALID,
      AXI4_RDATA(31 downto 0) => smartconnect_1_M00_AXI_RDATA(31 downto 0),
      AXI4_RID(11 downto 0) => NLW_uz_axi_testIP_0_AXI4_RID_UNCONNECTED(11 downto 0),
      AXI4_RLAST => smartconnect_1_M00_AXI_RLAST,
      AXI4_RREADY => smartconnect_1_M00_AXI_RREADY,
      AXI4_RRESP(1 downto 0) => smartconnect_1_M00_AXI_RRESP(1 downto 0),
      AXI4_RVALID => smartconnect_1_M00_AXI_RVALID,
      AXI4_WDATA(31 downto 0) => smartconnect_1_M00_AXI_WDATA(31 downto 0),
      AXI4_WLAST => smartconnect_1_M00_AXI_WLAST,
      AXI4_WREADY => smartconnect_1_M00_AXI_WREADY,
      AXI4_WSTRB(3 downto 0) => smartconnect_1_M00_AXI_WSTRB(3 downto 0),
      AXI4_WVALID => smartconnect_1_M00_AXI_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => proc_sys_reset_1_peripheral_aresetn(0)
    );
uz_pu_con_ip_0: component zusys_uz_pu_con_ip_0_1
     port map (
      AXI4_Lite_ACLK => zynq_ultra_ps_e_0_pl_clk1,
      AXI4_Lite_ARADDR(15 downto 0) => smartconnect_0_M13_AXI_ARADDR(15 downto 0),
      AXI4_Lite_ARESETN => proc_sys_reset_1_peripheral_aresetn(0),
      AXI4_Lite_ARREADY => smartconnect_0_M13_AXI_ARREADY,
      AXI4_Lite_ARVALID => smartconnect_0_M13_AXI_ARVALID,
      AXI4_Lite_AWADDR(15 downto 0) => smartconnect_0_M13_AXI_AWADDR(15 downto 0),
      AXI4_Lite_AWREADY => smartconnect_0_M13_AXI_AWREADY,
      AXI4_Lite_AWVALID => smartconnect_0_M13_AXI_AWVALID,
      AXI4_Lite_BREADY => smartconnect_0_M13_AXI_BREADY,
      AXI4_Lite_BRESP(1 downto 0) => smartconnect_0_M13_AXI_BRESP(1 downto 0),
      AXI4_Lite_BVALID => smartconnect_0_M13_AXI_BVALID,
      AXI4_Lite_RDATA(31 downto 0) => smartconnect_0_M13_AXI_RDATA(31 downto 0),
      AXI4_Lite_RREADY => smartconnect_0_M13_AXI_RREADY,
      AXI4_Lite_RRESP(1 downto 0) => smartconnect_0_M13_AXI_RRESP(1 downto 0),
      AXI4_Lite_RVALID => smartconnect_0_M13_AXI_RVALID,
      AXI4_Lite_WDATA(31 downto 0) => smartconnect_0_M13_AXI_WDATA(31 downto 0),
      AXI4_Lite_WREADY => smartconnect_0_M13_AXI_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => smartconnect_0_M13_AXI_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => smartconnect_0_M13_AXI_WVALID,
      IPCORE_CLK => zynq_ultra_ps_e_0_pl_clk1,
      IPCORE_RESETN => proc_sys_reset_1_peripheral_aresetn(0),
      adc_trigger => A1_ADC_LTC2311_SI_VALID(0),
      in0(26 downto 0) => xlslice_0_Dout(26 downto 0),
      in1(26 downto 0) => xlslice_1_Dout(26 downto 0),
      in10(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in11(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in12(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in13(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in14(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in15(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in16(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in17(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in18(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in19(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in2(26 downto 0) => xlslice_2_Dout(26 downto 0),
      in20(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in21(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in22(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in23(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in24(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in25(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in26(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in27(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in28(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in29(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in3(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in30(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in31(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in4(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in5(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in6(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in7(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in8(26 downto 0) => xlconstant_0_dout(26 downto 0),
      in9(26 downto 0) => xlconstant_0_dout(26 downto 0),
      out0(17 downto 0) => uz_pu_con_ip_0_out0(17 downto 0),
      out1(17 downto 0) => uz_pu_con_ip_0_out1(17 downto 0),
      out10(17 downto 0) => NLW_uz_pu_con_ip_0_out10_UNCONNECTED(17 downto 0),
      out11(17 downto 0) => NLW_uz_pu_con_ip_0_out11_UNCONNECTED(17 downto 0),
      out12(17 downto 0) => NLW_uz_pu_con_ip_0_out12_UNCONNECTED(17 downto 0),
      out13(17 downto 0) => NLW_uz_pu_con_ip_0_out13_UNCONNECTED(17 downto 0),
      out14(17 downto 0) => NLW_uz_pu_con_ip_0_out14_UNCONNECTED(17 downto 0),
      out15(17 downto 0) => NLW_uz_pu_con_ip_0_out15_UNCONNECTED(17 downto 0),
      out16(17 downto 0) => NLW_uz_pu_con_ip_0_out16_UNCONNECTED(17 downto 0),
      out17(17 downto 0) => NLW_uz_pu_con_ip_0_out17_UNCONNECTED(17 downto 0),
      out18(17 downto 0) => NLW_uz_pu_con_ip_0_out18_UNCONNECTED(17 downto 0),
      out19(17 downto 0) => NLW_uz_pu_con_ip_0_out19_UNCONNECTED(17 downto 0),
      out2(17 downto 0) => uz_pu_con_ip_0_out2(17 downto 0),
      out20(17 downto 0) => NLW_uz_pu_con_ip_0_out20_UNCONNECTED(17 downto 0),
      out21(17 downto 0) => NLW_uz_pu_con_ip_0_out21_UNCONNECTED(17 downto 0),
      out22(17 downto 0) => NLW_uz_pu_con_ip_0_out22_UNCONNECTED(17 downto 0),
      out23(17 downto 0) => NLW_uz_pu_con_ip_0_out23_UNCONNECTED(17 downto 0),
      out24(17 downto 0) => NLW_uz_pu_con_ip_0_out24_UNCONNECTED(17 downto 0),
      out25(17 downto 0) => NLW_uz_pu_con_ip_0_out25_UNCONNECTED(17 downto 0),
      out26(17 downto 0) => NLW_uz_pu_con_ip_0_out26_UNCONNECTED(17 downto 0),
      out27(17 downto 0) => NLW_uz_pu_con_ip_0_out27_UNCONNECTED(17 downto 0),
      out28(17 downto 0) => NLW_uz_pu_con_ip_0_out28_UNCONNECTED(17 downto 0),
      out29(17 downto 0) => NLW_uz_pu_con_ip_0_out29_UNCONNECTED(17 downto 0),
      out3(17 downto 0) => uz_pu_con_ip_0_out3(17 downto 0),
      out30(17 downto 0) => NLW_uz_pu_con_ip_0_out30_UNCONNECTED(17 downto 0),
      out31(17 downto 0) => NLW_uz_pu_con_ip_0_out31_UNCONNECTED(17 downto 0),
      out4(17 downto 0) => uz_pu_con_ip_0_out4(17 downto 0),
      out5(17 downto 0) => uz_pu_con_ip_0_out5(17 downto 0),
      out6(17 downto 0) => uz_pu_con_ip_0_out6(17 downto 0),
      out7(17 downto 0) => uz_pu_con_ip_0_out7(17 downto 0),
      out8(17 downto 0) => NLW_uz_pu_con_ip_0_out8_UNCONNECTED(17 downto 0),
      out9(17 downto 0) => NLW_uz_pu_con_ip_0_out9_UNCONNECTED(17 downto 0),
      out_valid => pu_valid_1
    );
vio_D34_test: component zusys_vio_D34_test_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_out0(25 downto 0) => vio_D2_test_probe_out0(25 downto 0)
    );
xlconstant_0: component zusys_xlconstant_0_1
     port map (
      dout(26 downto 0) => xlconstant_0_dout(26 downto 0)
    );
xlslice_0: component zusys_xlslice_0_0
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(26 downto 0) => xlslice_0_Dout(26 downto 0)
    );
xlslice_1: component zusys_xlslice_1_0
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(26 downto 0) => xlslice_1_Dout(26 downto 0)
    );
xlslice_2: component zusys_xlslice_2_1
     port map (
      Din(279 downto 0) => A1_ADC_LTC2311_SI_VALUE(279 downto 0),
      Dout(26 downto 0) => xlslice_2_Dout(26 downto 0)
    );
xlslice_Enable_AXI2TCM_Bit4: component zusys_xlslice_Enable_AXI2TCM_Bit4_0
     port map (
      Din(7 downto 0) => axi_gpio_2_gpio_io_o(7 downto 0),
      Dout(0) => xlslice_Enable_AXI2TCM_Bit4_Dout(0)
    );
xlslice_Enable_Gate_Bit1: component zusys_xlslice_Enable_Gate_Bit1_0
     port map (
      Din(7 downto 0) => axi_gpio_2_gpio_io_o(7 downto 0),
      Dout(0) => xlslice_Enable_Gate_Dout(0)
    );
xlslice_Enable_Inverter_Bit0: component zusys_xlslice_Enable_Inverter_Bit0_0
     port map (
      Din(7 downto 0) => axi_gpio_2_gpio_io_o(7 downto 0),
      Dout(0) => xlslice_Enable_Inverter_Dout(0)
    );
zynq_ultra_ps_e_0: component zusys_zynq_ultra_ps_e_0_0
     port map (
      maxigp2_araddr(39 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARADDR(39 downto 0),
      maxigp2_arburst(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARBURST(1 downto 0),
      maxigp2_arcache(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARCACHE(3 downto 0),
      maxigp2_arid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARID(15 downto 0),
      maxigp2_arlen(7 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARLEN(7 downto 0),
      maxigp2_arlock => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARLOCK,
      maxigp2_arprot(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARPROT(2 downto 0),
      maxigp2_arqos(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARQOS(3 downto 0),
      maxigp2_arready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARREADY,
      maxigp2_arsize(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARSIZE(2 downto 0),
      maxigp2_aruser(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARUSER(15 downto 0),
      maxigp2_arvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_ARVALID,
      maxigp2_awaddr(39 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWADDR(39 downto 0),
      maxigp2_awburst(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWBURST(1 downto 0),
      maxigp2_awcache(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWCACHE(3 downto 0),
      maxigp2_awid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWID(15 downto 0),
      maxigp2_awlen(7 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWLEN(7 downto 0),
      maxigp2_awlock => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWLOCK,
      maxigp2_awprot(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWPROT(2 downto 0),
      maxigp2_awqos(3 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWQOS(3 downto 0),
      maxigp2_awready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWREADY,
      maxigp2_awsize(2 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWSIZE(2 downto 0),
      maxigp2_awuser(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWUSER(15 downto 0),
      maxigp2_awvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_AWVALID,
      maxigp2_bid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BID(15 downto 0),
      maxigp2_bready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BREADY,
      maxigp2_bresp(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BRESP(1 downto 0),
      maxigp2_bvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_BVALID,
      maxigp2_rdata(127 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RDATA(127 downto 0),
      maxigp2_rid(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RID(15 downto 0),
      maxigp2_rlast => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RLAST,
      maxigp2_rready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RREADY,
      maxigp2_rresp(1 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RRESP(1 downto 0),
      maxigp2_rvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_RVALID,
      maxigp2_wdata(127 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WDATA(127 downto 0),
      maxigp2_wlast => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WLAST,
      maxigp2_wready => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WREADY,
      maxigp2_wstrb(15 downto 0) => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WSTRB(15 downto 0),
      maxigp2_wvalid => zynq_ultra_ps_e_0_M_AXI_HPM0_LPD_WVALID,
      maxihpm0_lpd_aclk => zynq_ultra_ps_e_0_pl_clk1,
      pl_clk0 => zynq_ultra_ps_e_0_pl_clk1,
      pl_ps_irq0(7 downto 0) => xlconcat_0_dout(7 downto 0),
      pl_resetn0 => zynq_ultra_ps_e_0_pl_resetn0,
      saxi_lpd_aclk => zynq_ultra_ps_e_0_pl_clk1,
      saxigp6_araddr(48 downto 32) => B"00000000000000000",
      saxigp6_araddr(31 downto 0) => AXI2TCM_0_M00_AXI_ARADDR(31 downto 0),
      saxigp6_arburst(1 downto 0) => AXI2TCM_0_M00_AXI_ARBURST(1 downto 0),
      saxigp6_arcache(3 downto 0) => AXI2TCM_0_M00_AXI_ARCACHE(3 downto 0),
      saxigp6_arid(5 downto 1) => B"00000",
      saxigp6_arid(0) => AXI2TCM_0_M00_AXI_ARID(0),
      saxigp6_arlen(7 downto 0) => AXI2TCM_0_M00_AXI_ARLEN(7 downto 0),
      saxigp6_arlock => AXI2TCM_0_M00_AXI_ARLOCK,
      saxigp6_arprot(2 downto 0) => AXI2TCM_0_M00_AXI_ARPROT(2 downto 0),
      saxigp6_arqos(3 downto 0) => AXI2TCM_0_M00_AXI_ARQOS(3 downto 0),
      saxigp6_arready => AXI2TCM_0_M00_AXI_ARREADY,
      saxigp6_arsize(2 downto 0) => AXI2TCM_0_M00_AXI_ARSIZE(2 downto 0),
      saxigp6_aruser => AXI2TCM_0_M00_AXI_ARUSER,
      saxigp6_arvalid => AXI2TCM_0_M00_AXI_ARVALID,
      saxigp6_awaddr(48 downto 32) => B"00000000000000000",
      saxigp6_awaddr(31 downto 0) => AXI2TCM_0_M00_AXI_AWADDR(31 downto 0),
      saxigp6_awburst(1 downto 0) => AXI2TCM_0_M00_AXI_AWBURST(1 downto 0),
      saxigp6_awcache(3 downto 0) => AXI2TCM_0_M00_AXI_AWCACHE(3 downto 0),
      saxigp6_awid(5 downto 1) => B"00000",
      saxigp6_awid(0) => AXI2TCM_0_M00_AXI_AWID(0),
      saxigp6_awlen(7 downto 0) => AXI2TCM_0_M00_AXI_AWLEN(7 downto 0),
      saxigp6_awlock => AXI2TCM_0_M00_AXI_AWLOCK,
      saxigp6_awprot(2 downto 0) => AXI2TCM_0_M00_AXI_AWPROT(2 downto 0),
      saxigp6_awqos(3 downto 0) => AXI2TCM_0_M00_AXI_AWQOS(3 downto 0),
      saxigp6_awready => AXI2TCM_0_M00_AXI_AWREADY,
      saxigp6_awsize(2 downto 0) => AXI2TCM_0_M00_AXI_AWSIZE(2 downto 0),
      saxigp6_awuser => AXI2TCM_0_M00_AXI_AWUSER,
      saxigp6_awvalid => AXI2TCM_0_M00_AXI_AWVALID,
      saxigp6_bid(5 downto 0) => AXI2TCM_0_M00_AXI_BID(5 downto 0),
      saxigp6_bready => AXI2TCM_0_M00_AXI_BREADY,
      saxigp6_bresp(1 downto 0) => AXI2TCM_0_M00_AXI_BRESP(1 downto 0),
      saxigp6_bvalid => AXI2TCM_0_M00_AXI_BVALID,
      saxigp6_rdata(31 downto 0) => AXI2TCM_0_M00_AXI_RDATA(31 downto 0),
      saxigp6_rid(5 downto 0) => AXI2TCM_0_M00_AXI_RID(5 downto 0),
      saxigp6_rlast => AXI2TCM_0_M00_AXI_RLAST,
      saxigp6_rready => AXI2TCM_0_M00_AXI_RREADY,
      saxigp6_rresp(1 downto 0) => AXI2TCM_0_M00_AXI_RRESP(1 downto 0),
      saxigp6_rvalid => AXI2TCM_0_M00_AXI_RVALID,
      saxigp6_wdata(31 downto 0) => AXI2TCM_0_M00_AXI_WDATA(31 downto 0),
      saxigp6_wlast => AXI2TCM_0_M00_AXI_WLAST,
      saxigp6_wready => AXI2TCM_0_M00_AXI_WREADY,
      saxigp6_wstrb(3 downto 0) => AXI2TCM_0_M00_AXI_WSTRB(3 downto 0),
      saxigp6_wvalid => AXI2TCM_0_M00_AXI_WVALID
    );
end STRUCTURE;
