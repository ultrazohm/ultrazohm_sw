--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
--Date        : Mon Nov 12 08:48:25 2018
--Host        : TUEIEAL-TM01 running 64-bit major release  (build 9200)
--Command     : generate_target design_1.bd
--Design      : design_1
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1 is
  port (
    DATA_IN : in STD_LOGIC_VECTOR ( 143 downto 0 );
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    axi_error_0 : out STD_LOGIC;
    axi_txn_done_0 : out STD_LOGIC;
    m00_axi_init_axi_txn : in STD_LOGIC;
    write_done_0 : out STD_LOGIC
  );
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of design_1 : entity is "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=2,numReposBlks=2,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=1,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of design_1 : entity is "design_1.hwdef";
end design_1;

architecture STRUCTURE of design_1 is
  component design_1_axi_vip_0_0 is
  port (
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    s_axi_awid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_awlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awuser : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wlast : in STD_LOGIC;
    s_axi_wuser : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bid : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_buser : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_arid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_araddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_arlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_aruser : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rid : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rlast : out STD_LOGIC;
    s_axi_ruser : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC
  );
  end component design_1_axi_vip_0_0;
  component design_1_AXI2TCM_v1_0_0_0 is
  port (
    DATA_IN : in STD_LOGIC_VECTOR ( 143 downto 0 );
    write_done : out STD_LOGIC;
    init_axi_txn : in STD_LOGIC;
    axi_txn_done : out STD_LOGIC;
    axi_error : out STD_LOGIC;
    m00_axi_aclk : in STD_LOGIC;
    m00_axi_aresetn : in STD_LOGIC;
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
    m00_axi_rready : out STD_LOGIC
  );
  end component design_1_AXI2TCM_v1_0_0_0;
  signal AXI2TCM_v1_0_0_axi_error : STD_LOGIC;
  signal AXI2TCM_v1_0_0_axi_txn_done : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_ARADDR : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARLOCK : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_ARPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARREADY : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_ARSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_ARVALID : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_AWADDR : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWBURST : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWCACHE : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWLEN : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWLOCK : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_AWPROT : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWQOS : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWREADY : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_AWSIZE : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_AWVALID : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_BID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_BREADY : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_BRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_BUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_BVALID : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_RDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_RID : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_RLAST : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_RREADY : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_RRESP : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_RUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_RVALID : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_WDATA : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_WLAST : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_WREADY : STD_LOGIC;
  signal AXI2TCM_v1_0_0_m00_axi_WSTRB : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal AXI2TCM_v1_0_0_m00_axi_WUSER : STD_LOGIC_VECTOR ( 0 to 0 );
  signal AXI2TCM_v1_0_0_m00_axi_WVALID : STD_LOGIC;
  signal AXI2TCM_v1_0_0_write_done : STD_LOGIC;
  signal DATA_IN_1 : STD_LOGIC_VECTOR ( 143 downto 0 );
  signal aclk_0_1 : STD_LOGIC;
  signal aresetn_0_1 : STD_LOGIC;
  signal m00_axi_init_axi_txn_1 : STD_LOGIC;
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of aclk : signal is "xilinx.com:signal:clock:1.0 CLK.ACLK CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of aclk : signal is "XIL_INTERFACENAME CLK.ACLK, ASSOCIATED_BUSIF M_AXI_0, ASSOCIATED_RESET aresetn, CLK_DOMAIN design_1_aclk_0, FREQ_HZ 100000000, PHASE 0.000";
  attribute X_INTERFACE_INFO of aresetn : signal is "xilinx.com:signal:reset:1.0 RST.ARESETN RST";
  attribute X_INTERFACE_PARAMETER of aresetn : signal is "XIL_INTERFACENAME RST.ARESETN, POLARITY ACTIVE_LOW";
begin
  DATA_IN_1(143 downto 0) <= DATA_IN(143 downto 0);
  aclk_0_1 <= aclk;
  aresetn_0_1 <= aresetn;
  axi_error_0 <= AXI2TCM_v1_0_0_axi_error;
  axi_txn_done_0 <= AXI2TCM_v1_0_0_axi_txn_done;
  m00_axi_init_axi_txn_1 <= m00_axi_init_axi_txn;
  write_done_0 <= AXI2TCM_v1_0_0_write_done;
AXI2TCM: component design_1_AXI2TCM_v1_0_0_0
     port map (
      DATA_IN(143 downto 0) => DATA_IN_1(143 downto 0),
      axi_error => AXI2TCM_v1_0_0_axi_error,
      axi_txn_done => AXI2TCM_v1_0_0_axi_txn_done,
      init_axi_txn => m00_axi_init_axi_txn_1,
      m00_axi_aclk => aclk_0_1,
      m00_axi_araddr(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARADDR(31 downto 0),
      m00_axi_arburst(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARBURST(1 downto 0),
      m00_axi_arcache(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARCACHE(3 downto 0),
      m00_axi_aresetn => aresetn_0_1,
      m00_axi_arid(0) => AXI2TCM_v1_0_0_m00_axi_ARID(0),
      m00_axi_arlen(7 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARLEN(7 downto 0),
      m00_axi_arlock => AXI2TCM_v1_0_0_m00_axi_ARLOCK,
      m00_axi_arprot(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARPROT(2 downto 0),
      m00_axi_arqos(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARQOS(3 downto 0),
      m00_axi_arready => AXI2TCM_v1_0_0_m00_axi_ARREADY,
      m00_axi_arsize(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARSIZE(2 downto 0),
      m00_axi_aruser(0) => AXI2TCM_v1_0_0_m00_axi_ARUSER(0),
      m00_axi_arvalid => AXI2TCM_v1_0_0_m00_axi_ARVALID,
      m00_axi_awaddr(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWADDR(31 downto 0),
      m00_axi_awburst(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWBURST(1 downto 0),
      m00_axi_awcache(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWCACHE(3 downto 0),
      m00_axi_awid(0) => AXI2TCM_v1_0_0_m00_axi_AWID(0),
      m00_axi_awlen(7 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWLEN(7 downto 0),
      m00_axi_awlock => AXI2TCM_v1_0_0_m00_axi_AWLOCK,
      m00_axi_awprot(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWPROT(2 downto 0),
      m00_axi_awqos(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWQOS(3 downto 0),
      m00_axi_awready => AXI2TCM_v1_0_0_m00_axi_AWREADY,
      m00_axi_awsize(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWSIZE(2 downto 0),
      m00_axi_awuser(0) => AXI2TCM_v1_0_0_m00_axi_AWUSER(0),
      m00_axi_awvalid => AXI2TCM_v1_0_0_m00_axi_AWVALID,
      m00_axi_bid(0) => AXI2TCM_v1_0_0_m00_axi_BID(0),
      m00_axi_bready => AXI2TCM_v1_0_0_m00_axi_BREADY,
      m00_axi_bresp(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_BRESP(1 downto 0),
      m00_axi_buser(0) => AXI2TCM_v1_0_0_m00_axi_BUSER(0),
      m00_axi_bvalid => AXI2TCM_v1_0_0_m00_axi_BVALID,
      m00_axi_rdata(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_RDATA(31 downto 0),
      m00_axi_rid(0) => AXI2TCM_v1_0_0_m00_axi_RID(0),
      m00_axi_rlast => AXI2TCM_v1_0_0_m00_axi_RLAST,
      m00_axi_rready => AXI2TCM_v1_0_0_m00_axi_RREADY,
      m00_axi_rresp(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_RRESP(1 downto 0),
      m00_axi_ruser(0) => AXI2TCM_v1_0_0_m00_axi_RUSER(0),
      m00_axi_rvalid => AXI2TCM_v1_0_0_m00_axi_RVALID,
      m00_axi_wdata(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_WDATA(31 downto 0),
      m00_axi_wlast => AXI2TCM_v1_0_0_m00_axi_WLAST,
      m00_axi_wready => AXI2TCM_v1_0_0_m00_axi_WREADY,
      m00_axi_wstrb(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_WSTRB(3 downto 0),
      m00_axi_wuser(0) => AXI2TCM_v1_0_0_m00_axi_WUSER(0),
      m00_axi_wvalid => AXI2TCM_v1_0_0_m00_axi_WVALID,
      write_done => AXI2TCM_v1_0_0_write_done
    );
axi_vip_0: component design_1_axi_vip_0_0
     port map (
      aclk => aclk_0_1,
      aresetn => aresetn_0_1,
      s_axi_araddr(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARADDR(31 downto 0),
      s_axi_arburst(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARBURST(1 downto 0),
      s_axi_arcache(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARCACHE(3 downto 0),
      s_axi_arid(0) => AXI2TCM_v1_0_0_m00_axi_ARID(0),
      s_axi_arlen(7 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARLEN(7 downto 0),
      s_axi_arlock(0) => AXI2TCM_v1_0_0_m00_axi_ARLOCK,
      s_axi_arprot(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARPROT(2 downto 0),
      s_axi_arqos(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARQOS(3 downto 0),
      s_axi_arready => AXI2TCM_v1_0_0_m00_axi_ARREADY,
      s_axi_arsize(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_ARSIZE(2 downto 0),
      s_axi_aruser(0) => AXI2TCM_v1_0_0_m00_axi_ARUSER(0),
      s_axi_arvalid => AXI2TCM_v1_0_0_m00_axi_ARVALID,
      s_axi_awaddr(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWADDR(31 downto 0),
      s_axi_awburst(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWBURST(1 downto 0),
      s_axi_awcache(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWCACHE(3 downto 0),
      s_axi_awid(0) => AXI2TCM_v1_0_0_m00_axi_AWID(0),
      s_axi_awlen(7 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWLEN(7 downto 0),
      s_axi_awlock(0) => AXI2TCM_v1_0_0_m00_axi_AWLOCK,
      s_axi_awprot(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWPROT(2 downto 0),
      s_axi_awqos(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWQOS(3 downto 0),
      s_axi_awready => AXI2TCM_v1_0_0_m00_axi_AWREADY,
      s_axi_awsize(2 downto 0) => AXI2TCM_v1_0_0_m00_axi_AWSIZE(2 downto 0),
      s_axi_awuser(0) => AXI2TCM_v1_0_0_m00_axi_AWUSER(0),
      s_axi_awvalid => AXI2TCM_v1_0_0_m00_axi_AWVALID,
      s_axi_bid(0) => AXI2TCM_v1_0_0_m00_axi_BID(0),
      s_axi_bready => AXI2TCM_v1_0_0_m00_axi_BREADY,
      s_axi_bresp(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_BRESP(1 downto 0),
      s_axi_buser(0) => AXI2TCM_v1_0_0_m00_axi_BUSER(0),
      s_axi_bvalid => AXI2TCM_v1_0_0_m00_axi_BVALID,
      s_axi_rdata(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_RDATA(31 downto 0),
      s_axi_rid(0) => AXI2TCM_v1_0_0_m00_axi_RID(0),
      s_axi_rlast => AXI2TCM_v1_0_0_m00_axi_RLAST,
      s_axi_rready => AXI2TCM_v1_0_0_m00_axi_RREADY,
      s_axi_rresp(1 downto 0) => AXI2TCM_v1_0_0_m00_axi_RRESP(1 downto 0),
      s_axi_ruser(0) => AXI2TCM_v1_0_0_m00_axi_RUSER(0),
      s_axi_rvalid => AXI2TCM_v1_0_0_m00_axi_RVALID,
      s_axi_wdata(31 downto 0) => AXI2TCM_v1_0_0_m00_axi_WDATA(31 downto 0),
      s_axi_wlast => AXI2TCM_v1_0_0_m00_axi_WLAST,
      s_axi_wready => AXI2TCM_v1_0_0_m00_axi_WREADY,
      s_axi_wstrb(3 downto 0) => AXI2TCM_v1_0_0_m00_axi_WSTRB(3 downto 0),
      s_axi_wuser(0) => AXI2TCM_v1_0_0_m00_axi_WUSER(0),
      s_axi_wvalid => AXI2TCM_v1_0_0_m00_axi_WVALID
    );
end STRUCTURE;
