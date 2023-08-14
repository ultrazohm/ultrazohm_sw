-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:43:12 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_Counter_f_sw_V2_ip_0_0/zusys_Counter_f_sw_V2_ip_0_0_sim_netlist.vhdl
-- Design      : zusys_Counter_f_sw_V2_ip_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder is
  port (
    read_reg_ip_timestamp : out STD_LOGIC_VECTOR ( 0 to 0 );
    write_axi_enable : out STD_LOGIC;
    bResetAXI : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 24 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    write_reg_axi_enable_reg_0 : in STD_LOGIC;
    write_reg_bResetAXI_reg_0 : in STD_LOGIC;
    switchNumb : in STD_LOGIC_VECTOR ( 24 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder : entity is "Counter_f_sw_V2_ip_addr_decoder";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder is
begin
\read_reg_ip_timestamp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => '1',
      Q => read_reg_ip_timestamp(0),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(0),
      Q => Q(0),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(10),
      Q => Q(10),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(11),
      Q => Q(11),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(12),
      Q => Q(12),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(13),
      Q => Q(13),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(14),
      Q => Q(14),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(15),
      Q => Q(15),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(16),
      Q => Q(16),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(17),
      Q => Q(17),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(18),
      Q => Q(18),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(19),
      Q => Q(19),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(1),
      Q => Q(1),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(20),
      Q => Q(20),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(21),
      Q => Q(21),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(22),
      Q => Q(22),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(23),
      Q => Q(23),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(24),
      Q => Q(24),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(2),
      Q => Q(2),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(3),
      Q => Q(3),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(4),
      Q => Q(4),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(5),
      Q => Q(5),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(6),
      Q => Q(6),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(7),
      Q => Q(7),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(8),
      Q => Q(8),
      R => SR(0)
    );
\read_reg_switchNumb_AXI_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => switchNumb(9),
      Q => Q(9),
      R => SR(0)
    );
write_reg_axi_enable_reg: unisim.vcomponents.FDSE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => write_reg_axi_enable_reg_0,
      Q => write_axi_enable,
      S => SR(0)
    );
write_reg_bResetAXI_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => write_reg_bResetAXI_reg_0,
      Q => bResetAXI,
      R => SR(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module is
  port (
    FSM_sequential_axi_lite_rstate_reg_0 : out STD_LOGIC;
    soft_reset : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \wdata_reg[0]_0\ : out STD_LOGIC;
    \wdata_reg[0]_1\ : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 25 downto 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    bResetAXI : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \AXI4_Lite_RDATA_tmp_reg[24]_0\ : in STD_LOGIC_VECTOR ( 24 downto 0 );
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module : entity is "Counter_f_sw_V2_ip_axi_lite_module";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module is
  signal \AXI4_Lite_RDATA_tmp[30]_i_10_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_11_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_12_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_8_n_0\ : STD_LOGIC;
  signal \AXI4_Lite_RDATA_tmp[30]_i_9_n_0\ : STD_LOGIC;
  signal \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\ : STD_LOGIC;
  signal \^fsm_sequential_axi_lite_rstate_reg_0\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal aw_transfer : STD_LOGIC;
  signal axi_lite_rstate_next : STD_LOGIC;
  signal axi_lite_wstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal data_read : STD_LOGIC_VECTOR ( 30 downto 0 );
  signal reset : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \^soft_reset\ : STD_LOGIC;
  signal soft_reset_i_1_n_0 : STD_LOGIC;
  signal soft_reset_i_2_n_0 : STD_LOGIC;
  signal soft_reset_i_3_n_0 : STD_LOGIC;
  signal soft_reset_i_4_n_0 : STD_LOGIC;
  signal soft_reset_i_5_n_0 : STD_LOGIC;
  signal top_rd_enb : STD_LOGIC;
  signal top_wr_enb : STD_LOGIC;
  signal w_transfer_and_wstrb : STD_LOGIC;
  signal \wdata[0]_i_1_n_0\ : STD_LOGIC;
  signal \wdata_reg_n_0_[0]\ : STD_LOGIC;
  signal write_reg_axi_enable_i_2_n_0 : STD_LOGIC;
  signal write_reg_bResetAXI_i_2_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of AXI4_Lite_ARREADY_INST_0 : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of AXI4_Lite_AWREADY_INST_0 : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_10\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_4\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_5\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \AXI4_Lite_RDATA_tmp[30]_i_6\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \FSM_onehot_axi_lite_wstate[1]_i_2\ : label is "soft_lutpair2";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi_lite_wstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of FSM_sequential_axi_lite_rstate_i_1 : label is "soft_lutpair1";
  attribute FSM_ENCODED_STATES of FSM_sequential_axi_lite_rstate_reg : label is "iSTATE:0,iSTATE0:1";
  attribute SOFT_HLUTNM of write_reg_axi_enable_i_2 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of write_reg_bResetAXI_i_2 : label is "soft_lutpair0";
begin
  FSM_sequential_axi_lite_rstate_reg_0 <= \^fsm_sequential_axi_lite_rstate_reg_0\;
  Q(1 downto 0) <= \^q\(1 downto 0);
  soft_reset <= \^soft_reset\;
AXI4_Lite_ARREADY_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => AXI4_Lite_AWVALID,
      O => AXI4_Lite_ARREADY
    );
AXI4_Lite_AWREADY_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I1 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      O => AXI4_Lite_AWREADY
    );
\AXI4_Lite_RDATA_tmp[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(0),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(0)
    );
\AXI4_Lite_RDATA_tmp[10]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(10),
      O => data_read(10)
    );
\AXI4_Lite_RDATA_tmp[11]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(11),
      O => data_read(11)
    );
\AXI4_Lite_RDATA_tmp[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(12),
      O => data_read(12)
    );
\AXI4_Lite_RDATA_tmp[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(13),
      O => data_read(13)
    );
\AXI4_Lite_RDATA_tmp[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(14),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(14)
    );
\AXI4_Lite_RDATA_tmp[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(15),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(15)
    );
\AXI4_Lite_RDATA_tmp[16]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(16),
      O => data_read(16)
    );
\AXI4_Lite_RDATA_tmp[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(17),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(17)
    );
\AXI4_Lite_RDATA_tmp[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(18),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(18)
    );
\AXI4_Lite_RDATA_tmp[19]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(19),
      O => data_read(19)
    );
\AXI4_Lite_RDATA_tmp[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(1),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(1)
    );
\AXI4_Lite_RDATA_tmp[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(20),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(20)
    );
\AXI4_Lite_RDATA_tmp[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(21),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(21)
    );
\AXI4_Lite_RDATA_tmp[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(22),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(22)
    );
\AXI4_Lite_RDATA_tmp[23]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(23),
      O => data_read(23)
    );
\AXI4_Lite_RDATA_tmp[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(24),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(24)
    );
\AXI4_Lite_RDATA_tmp[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(2),
      O => data_read(2)
    );
\AXI4_Lite_RDATA_tmp[30]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0400"
    )
        port map (
      I0 => AXI4_Lite_AWVALID,
      I1 => AXI4_Lite_ARVALID,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I3 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      O => top_rd_enb
    );
\AXI4_Lite_RDATA_tmp[30]_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(13),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(13),
      O => \AXI4_Lite_RDATA_tmp[30]_i_10_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_11\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"EEFFEEF0"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(9),
      I1 => AXI4_Lite_ARADDR(8),
      I2 => sel0(9),
      I3 => AXI4_Lite_ARVALID,
      I4 => sel0(8),
      O => \AXI4_Lite_RDATA_tmp[30]_i_11_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_12\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(11),
      I1 => AXI4_Lite_ARADDR(11),
      I2 => sel0(10),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(10),
      O => \AXI4_Lite_RDATA_tmp[30]_i_12_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00080000"
    )
        port map (
      I0 => read_reg_ip_timestamp(0),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      O => data_read(30)
    );
\AXI4_Lite_RDATA_tmp[30]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000001000000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_8_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_9_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_10_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_11_n_0\,
      I5 => \AXI4_Lite_RDATA_tmp[30]_i_12_n_0\,
      O => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(6),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(6),
      O => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(0),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(0),
      O => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(1),
      I1 => AXI4_Lite_ARVALID,
      I2 => sel0(1),
      O => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"EEFFEEF0"
    )
        port map (
      I0 => AXI4_Lite_ARADDR(3),
      I1 => AXI4_Lite_ARADDR(2),
      I2 => sel0(3),
      I3 => AXI4_Lite_ARVALID,
      I4 => sel0(2),
      O => \AXI4_Lite_RDATA_tmp[30]_i_7_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEEF0EE"
    )
        port map (
      I0 => sel0(5),
      I1 => sel0(4),
      I2 => AXI4_Lite_ARADDR(5),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(4),
      O => \AXI4_Lite_RDATA_tmp[30]_i_8_n_0\
    );
\AXI4_Lite_RDATA_tmp[30]_i_9\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(7),
      I1 => AXI4_Lite_ARADDR(7),
      I2 => sel0(12),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(12),
      O => \AXI4_Lite_RDATA_tmp[30]_i_9_n_0\
    );
\AXI4_Lite_RDATA_tmp[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(3),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(3)
    );
\AXI4_Lite_RDATA_tmp[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(4),
      O => data_read(4)
    );
\AXI4_Lite_RDATA_tmp[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(5),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(5)
    );
\AXI4_Lite_RDATA_tmp[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(6),
      O => data_read(6)
    );
\AXI4_Lite_RDATA_tmp[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(7),
      O => data_read(7)
    );
\AXI4_Lite_RDATA_tmp[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(8),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(8)
    );
\AXI4_Lite_RDATA_tmp[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"200C000020000000"
    )
        port map (
      I0 => \AXI4_Lite_RDATA_tmp_reg[24]_0\(9),
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_6_n_0\,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_5_n_0\,
      I3 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => read_reg_ip_timestamp(0),
      O => data_read(9)
    );
\AXI4_Lite_RDATA_tmp_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(0),
      Q => AXI4_Lite_RDATA(0),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(10),
      Q => AXI4_Lite_RDATA(10),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(11),
      Q => AXI4_Lite_RDATA(11),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(12),
      Q => AXI4_Lite_RDATA(12),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(13),
      Q => AXI4_Lite_RDATA(13),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(14),
      Q => AXI4_Lite_RDATA(14),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(15),
      Q => AXI4_Lite_RDATA(15),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(16),
      Q => AXI4_Lite_RDATA(16),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(17),
      Q => AXI4_Lite_RDATA(17),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(18),
      Q => AXI4_Lite_RDATA(18),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(19),
      Q => AXI4_Lite_RDATA(19),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(1),
      Q => AXI4_Lite_RDATA(1),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(20),
      Q => AXI4_Lite_RDATA(20),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(21),
      Q => AXI4_Lite_RDATA(21),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(22),
      Q => AXI4_Lite_RDATA(22),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(23),
      Q => AXI4_Lite_RDATA(23),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(24),
      Q => AXI4_Lite_RDATA(24),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(2),
      Q => AXI4_Lite_RDATA(2),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(30),
      Q => AXI4_Lite_RDATA(25),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(3),
      Q => AXI4_Lite_RDATA(3),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(4),
      Q => AXI4_Lite_RDATA(4),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(5),
      Q => AXI4_Lite_RDATA(5),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(6),
      Q => AXI4_Lite_RDATA(6),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(7),
      Q => AXI4_Lite_RDATA(7),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(8),
      Q => AXI4_Lite_RDATA(8),
      R => reset
    );
\AXI4_Lite_RDATA_tmp_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => top_rd_enb,
      D => data_read(9),
      Q => AXI4_Lite_RDATA(9),
      R => reset
    );
\FSM_onehot_axi_lite_wstate[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF8A8A8A"
    )
        port map (
      I0 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I1 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I2 => AXI4_Lite_AWVALID,
      I3 => AXI4_Lite_BREADY,
      I4 => \^q\(1),
      O => axi_lite_wstate_next(0)
    );
\FSM_onehot_axi_lite_wstate[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      O => reset
    );
\FSM_onehot_axi_lite_wstate[1]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"08FF0808"
    )
        port map (
      I0 => AXI4_Lite_AWVALID,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I3 => AXI4_Lite_WVALID,
      I4 => \^q\(0),
      O => axi_lite_wstate_next(1)
    );
\FSM_onehot_axi_lite_wstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F444"
    )
        port map (
      I0 => AXI4_Lite_BREADY,
      I1 => \^q\(1),
      I2 => AXI4_Lite_WVALID,
      I3 => \^q\(0),
      O => axi_lite_wstate_next(2)
    );
\FSM_onehot_axi_lite_wstate_reg[0]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_wstate_next(0),
      Q => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      S => reset
    );
\FSM_onehot_axi_lite_wstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_wstate_next(1),
      Q => \^q\(0),
      R => reset
    );
\FSM_onehot_axi_lite_wstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_wstate_next(2),
      Q => \^q\(1),
      R => reset
    );
FSM_sequential_axi_lite_rstate_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"50505C50"
    )
        port map (
      I0 => AXI4_Lite_RREADY,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_AWVALID,
      O => axi_lite_rstate_next
    );
FSM_sequential_axi_lite_rstate_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => axi_lite_rstate_next,
      Q => \^fsm_sequential_axi_lite_rstate_reg_0\,
      R => reset
    );
soft_reset_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0A020000"
    )
        port map (
      I0 => soft_reset_i_2_n_0,
      I1 => sel0(9),
      I2 => sel0(11),
      I3 => sel0(10),
      I4 => soft_reset_i_3_n_0,
      O => soft_reset_i_1_n_0
    );
soft_reset_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000008"
    )
        port map (
      I0 => soft_reset_i_4_n_0,
      I1 => soft_reset_i_5_n_0,
      I2 => sel0(1),
      I3 => sel0(0),
      I4 => sel0(7),
      I5 => sel0(2),
      O => soft_reset_i_2_n_0
    );
soft_reset_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000230000002323"
    )
        port map (
      I0 => sel0(7),
      I1 => sel0(8),
      I2 => sel0(6),
      I3 => sel0(4),
      I4 => sel0(5),
      I5 => sel0(3),
      O => soft_reset_i_3_n_0
    );
soft_reset_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000002000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => sel0(13),
      I2 => AXI4_Lite_ARESETN,
      I3 => top_wr_enb,
      I4 => sel0(5),
      I5 => sel0(4),
      O => soft_reset_i_4_n_0
    );
soft_reset_i_5: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => sel0(12),
      I1 => sel0(11),
      I2 => sel0(10),
      I3 => sel0(8),
      O => soft_reset_i_5_n_0
    );
soft_reset_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => soft_reset_i_1_n_0,
      Q => \^soft_reset\,
      R => '0'
    );
ss_in_5_1_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => AXI4_Lite_ARESETN,
      I1 => \^soft_reset\,
      I2 => IPCORE_RESETN,
      O => SR(0)
    );
\waddr[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^fsm_sequential_axi_lite_rstate_reg_0\,
      I1 => \FSM_onehot_axi_lite_wstate_reg_n_0_[0]\,
      I2 => AXI4_Lite_AWVALID,
      O => aw_transfer
    );
\waddr_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(8),
      Q => sel0(8),
      R => reset
    );
\waddr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(9),
      Q => sel0(9),
      R => reset
    );
\waddr_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(10),
      Q => sel0(10),
      R => reset
    );
\waddr_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(11),
      Q => sel0(11),
      R => reset
    );
\waddr_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(12),
      Q => sel0(12),
      R => reset
    );
\waddr_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(13),
      Q => sel0(13),
      R => reset
    );
\waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(0),
      Q => sel0(0),
      R => reset
    );
\waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(1),
      Q => sel0(1),
      R => reset
    );
\waddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(2),
      Q => sel0(2),
      R => reset
    );
\waddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(3),
      Q => sel0(3),
      R => reset
    );
\waddr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(4),
      Q => sel0(4),
      R => reset
    );
\waddr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(5),
      Q => sel0(5),
      R => reset
    );
\waddr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(6),
      Q => sel0(6),
      R => reset
    );
\waddr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => aw_transfer,
      D => AXI4_Lite_AWADDR(7),
      Q => sel0(7),
      R => reset
    );
\wdata[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"BF80"
    )
        port map (
      I0 => AXI4_Lite_WDATA(0),
      I1 => \^q\(0),
      I2 => AXI4_Lite_WVALID,
      I3 => \wdata_reg_n_0_[0]\,
      O => \wdata[0]_i_1_n_0\
    );
\wdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => \wdata[0]_i_1_n_0\,
      Q => \wdata_reg_n_0_[0]\,
      R => reset
    );
wr_enb_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => AXI4_Lite_WSTRB(2),
      I1 => AXI4_Lite_WSTRB(3),
      I2 => AXI4_Lite_WSTRB(0),
      I3 => AXI4_Lite_WSTRB(1),
      I4 => \^q\(0),
      I5 => AXI4_Lite_WVALID,
      O => w_transfer_and_wstrb
    );
wr_enb_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_Lite_ACLK,
      CE => '1',
      D => w_transfer_and_wstrb,
      Q => top_wr_enb,
      R => reset
    );
write_reg_axi_enable_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FBFFFFFF08000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => top_wr_enb,
      I2 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I3 => write_reg_axi_enable_i_2_n_0,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => write_axi_enable,
      O => \wdata_reg[0]_0\
    );
write_reg_axi_enable_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000ACC0A"
    )
        port map (
      I0 => sel0(0),
      I1 => AXI4_Lite_ARADDR(0),
      I2 => sel0(1),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(1),
      O => write_reg_axi_enable_i_2_n_0
    );
write_reg_bResetAXI_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BFFFFFFF80000000"
    )
        port map (
      I0 => \wdata_reg_n_0_[0]\,
      I1 => \AXI4_Lite_RDATA_tmp[30]_i_4_n_0\,
      I2 => top_wr_enb,
      I3 => write_reg_bResetAXI_i_2_n_0,
      I4 => \AXI4_Lite_RDATA_tmp[30]_i_3_n_0\,
      I5 => bResetAXI,
      O => \wdata_reg[0]_1\
    );
write_reg_bResetAXI_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00053305"
    )
        port map (
      I0 => sel0(1),
      I1 => AXI4_Lite_ARADDR(1),
      I2 => sel0(0),
      I3 => AXI4_Lite_ARVALID,
      I4 => AXI4_Lite_ARADDR(0),
      O => write_reg_bResetAXI_i_2_n_0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw is
  port (
    switchNumb : out STD_LOGIC_VECTOR ( 24 downto 0 );
    S : in STD_LOGIC_VECTOR ( 0 to 0 );
    reset_old2_out1 : in STD_LOGIC;
    bResetAXI_1 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 5 downto 0 );
    D : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \switchNumb10__0_carry__1_0\ : in STD_LOGIC_VECTOR ( 23 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw : entity is "Counter_f_sw_V2_ip_src_Count_f_sw";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw is
  signal switchNumb1 : STD_LOGIC_VECTOR ( 23 downto 2 );
  signal \switchNumb10__0_carry__0_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_1\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_10\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_11\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_12\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_13\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_14\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_15\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_2\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_3\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_4\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_5\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_6\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_7\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_8\ : STD_LOGIC;
  signal \switchNumb10__0_carry__0_n_9\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_1\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_10\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_11\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_12\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_13\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_14\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_15\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_2\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_3\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_4\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_5\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_6\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_7\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_8\ : STD_LOGIC;
  signal \switchNumb10__0_carry__1_n_9\ : STD_LOGIC;
  signal \switchNumb10__0_carry__2_n_15\ : STD_LOGIC;
  signal \switchNumb10__0_carry_i_10_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry_i_1_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry_i_8_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry_i_9_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_0\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_1\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_10\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_11\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_12\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_13\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_14\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_15\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_2\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_3\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_4\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_5\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_6\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_7\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_8\ : STD_LOGIC;
  signal \switchNumb10__0_carry_n_9\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_0\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_1\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_2\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_3\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_4\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_5\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_6\ : STD_LOGIC;
  signal \switchNumb10__51_carry__0_n_7\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_0\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_1\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_2\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_3\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_4\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_5\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_6\ : STD_LOGIC;
  signal \switchNumb10__51_carry__1_n_7\ : STD_LOGIC;
  signal \switchNumb10__51_carry_i_1_n_0\ : STD_LOGIC;
  signal \switchNumb10__51_carry_i_2_n_0\ : STD_LOGIC;
  signal \switchNumb10__51_carry_i_3_n_0\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_0\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_1\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_2\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_3\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_4\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_5\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_6\ : STD_LOGIC;
  signal \switchNumb10__51_carry_n_7\ : STD_LOGIC;
  signal switchNumb111_out : STD_LOGIC;
  signal switchNumb114_out : STD_LOGIC;
  signal \NLW_switchNumb10__0_carry__2_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_switchNumb10__0_carry__2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal \NLW_switchNumb10__51_carry__2_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_switchNumb10__51_carry__2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 1 );
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \switchNumb10__0_carry\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__0_carry__0\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__0_carry__1\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__0_carry__2\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__51_carry\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__51_carry__0\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__51_carry__1\ : label is 35;
  attribute ADDER_THRESHOLD of \switchNumb10__51_carry__2\ : label is 35;
begin
\switchNumb10__0_carry\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \switchNumb10__0_carry_n_0\,
      CO(6) => \switchNumb10__0_carry_n_1\,
      CO(5) => \switchNumb10__0_carry_n_2\,
      CO(4) => \switchNumb10__0_carry_n_3\,
      CO(3) => \switchNumb10__0_carry_n_4\,
      CO(2) => \switchNumb10__0_carry_n_5\,
      CO(1) => \switchNumb10__0_carry_n_6\,
      CO(0) => \switchNumb10__0_carry_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \switchNumb10__0_carry_i_1_n_0\,
      DI(0) => '0',
      O(7) => \switchNumb10__0_carry_n_8\,
      O(6) => \switchNumb10__0_carry_n_9\,
      O(5) => \switchNumb10__0_carry_n_10\,
      O(4) => \switchNumb10__0_carry_n_11\,
      O(3) => \switchNumb10__0_carry_n_12\,
      O(2) => \switchNumb10__0_carry_n_13\,
      O(1) => \switchNumb10__0_carry_n_14\,
      O(0) => \switchNumb10__0_carry_n_15\,
      S(7 downto 2) => switchNumb1(7 downto 2),
      S(1) => \switchNumb10__0_carry_i_8_n_0\,
      S(0) => \switchNumb10__0_carry_i_9_n_0\
    );
\switchNumb10__0_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__0_carry_n_0\,
      CI_TOP => '0',
      CO(7) => \switchNumb10__0_carry__0_n_0\,
      CO(6) => \switchNumb10__0_carry__0_n_1\,
      CO(5) => \switchNumb10__0_carry__0_n_2\,
      CO(4) => \switchNumb10__0_carry__0_n_3\,
      CO(3) => \switchNumb10__0_carry__0_n_4\,
      CO(2) => \switchNumb10__0_carry__0_n_5\,
      CO(1) => \switchNumb10__0_carry__0_n_6\,
      CO(0) => \switchNumb10__0_carry__0_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \switchNumb10__0_carry__0_n_8\,
      O(6) => \switchNumb10__0_carry__0_n_9\,
      O(5) => \switchNumb10__0_carry__0_n_10\,
      O(4) => \switchNumb10__0_carry__0_n_11\,
      O(3) => \switchNumb10__0_carry__0_n_12\,
      O(2) => \switchNumb10__0_carry__0_n_13\,
      O(1) => \switchNumb10__0_carry__0_n_14\,
      O(0) => \switchNumb10__0_carry__0_n_15\,
      S(7 downto 0) => switchNumb1(15 downto 8)
    );
\switchNumb10__0_carry__0_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(15),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(15)
    );
\switchNumb10__0_carry__0_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(14),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(14)
    );
\switchNumb10__0_carry__0_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(13),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(13)
    );
\switchNumb10__0_carry__0_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(12),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(12)
    );
\switchNumb10__0_carry__0_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(11),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(11)
    );
\switchNumb10__0_carry__0_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(10),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(10)
    );
\switchNumb10__0_carry__0_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(9),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(9)
    );
\switchNumb10__0_carry__0_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(8),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(8)
    );
\switchNumb10__0_carry__1\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__0_carry__0_n_0\,
      CI_TOP => '0',
      CO(7) => \switchNumb10__0_carry__1_n_0\,
      CO(6) => \switchNumb10__0_carry__1_n_1\,
      CO(5) => \switchNumb10__0_carry__1_n_2\,
      CO(4) => \switchNumb10__0_carry__1_n_3\,
      CO(3) => \switchNumb10__0_carry__1_n_4\,
      CO(2) => \switchNumb10__0_carry__1_n_5\,
      CO(1) => \switchNumb10__0_carry__1_n_6\,
      CO(0) => \switchNumb10__0_carry__1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \switchNumb10__0_carry__1_n_8\,
      O(6) => \switchNumb10__0_carry__1_n_9\,
      O(5) => \switchNumb10__0_carry__1_n_10\,
      O(4) => \switchNumb10__0_carry__1_n_11\,
      O(3) => \switchNumb10__0_carry__1_n_12\,
      O(2) => \switchNumb10__0_carry__1_n_13\,
      O(1) => \switchNumb10__0_carry__1_n_14\,
      O(0) => \switchNumb10__0_carry__1_n_15\,
      S(7 downto 0) => switchNumb1(23 downto 16)
    );
\switchNumb10__0_carry__1_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(23),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(23)
    );
\switchNumb10__0_carry__1_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(22),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(22)
    );
\switchNumb10__0_carry__1_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(21),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(21)
    );
\switchNumb10__0_carry__1_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(20),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(20)
    );
\switchNumb10__0_carry__1_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(19),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(19)
    );
\switchNumb10__0_carry__1_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(18),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(18)
    );
\switchNumb10__0_carry__1_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(17),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(17)
    );
\switchNumb10__0_carry__1_i_8\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(16),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(16)
    );
\switchNumb10__0_carry__2\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__0_carry__1_n_0\,
      CI_TOP => '0',
      CO(7 downto 0) => \NLW_switchNumb10__0_carry__2_CO_UNCONNECTED\(7 downto 0),
      DI(7 downto 0) => B"00000000",
      O(7 downto 1) => \NLW_switchNumb10__0_carry__2_O_UNCONNECTED\(7 downto 1),
      O(0) => \switchNumb10__0_carry__2_n_15\,
      S(7 downto 1) => B"0000000",
      S(0) => S(0)
    );
\switchNumb10__0_carry_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"06606FF606600660"
    )
        port map (
      I0 => D(1),
      I1 => Q(1),
      I2 => D(0),
      I3 => Q(0),
      I4 => \switchNumb10__0_carry_i_10_n_0\,
      I5 => \switchNumb10__0_carry__1_0\(0),
      O => \switchNumb10__0_carry_i_1_n_0\
    );
\switchNumb10__0_carry_i_10\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"4"
    )
        port map (
      I0 => reset_old2_out1,
      I1 => bResetAXI_1,
      O => \switchNumb10__0_carry_i_10_n_0\
    );
\switchNumb10__0_carry_i_11\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Q(0),
      I1 => D(0),
      O => switchNumb114_out
    );
\switchNumb10__0_carry_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(7),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(7)
    );
\switchNumb10__0_carry_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(6),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(6)
    );
\switchNumb10__0_carry_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(5),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(5)
    );
\switchNumb10__0_carry_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(4),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(4)
    );
\switchNumb10__0_carry_i_6\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(3),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(3)
    );
\switchNumb10__0_carry_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(2),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(2)
    );
\switchNumb10__0_carry_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0CC071170CC08EE8"
    )
        port map (
      I0 => \switchNumb10__0_carry__1_0\(0),
      I1 => switchNumb114_out,
      I2 => Q(1),
      I3 => D(1),
      I4 => \switchNumb10__0_carry_i_10_n_0\,
      I5 => \switchNumb10__0_carry__1_0\(1),
      O => \switchNumb10__0_carry_i_8_n_0\
    );
\switchNumb10__0_carry_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4BB4B44BB44B4BB4"
    )
        port map (
      I0 => \switchNumb10__0_carry_i_10_n_0\,
      I1 => \switchNumb10__0_carry__1_0\(0),
      I2 => Q(1),
      I3 => D(1),
      I4 => Q(0),
      I5 => D(0),
      O => \switchNumb10__0_carry_i_9_n_0\
    );
\switchNumb10__51_carry\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__51_carry_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \switchNumb10__51_carry_n_0\,
      CO(6) => \switchNumb10__51_carry_n_1\,
      CO(5) => \switchNumb10__51_carry_n_2\,
      CO(4) => \switchNumb10__51_carry_n_3\,
      CO(3) => \switchNumb10__51_carry_n_4\,
      CO(2) => \switchNumb10__51_carry_n_5\,
      CO(1) => \switchNumb10__51_carry_n_6\,
      CO(0) => \switchNumb10__51_carry_n_7\,
      DI(7 downto 2) => B"000000",
      DI(1) => \switchNumb10__0_carry_n_14\,
      DI(0) => \switchNumb10__0_carry_n_15\,
      O(7 downto 0) => switchNumb(7 downto 0),
      S(7) => \switchNumb10__0_carry_n_8\,
      S(6) => \switchNumb10__0_carry_n_9\,
      S(5) => \switchNumb10__0_carry_n_10\,
      S(4) => \switchNumb10__0_carry_n_11\,
      S(3) => \switchNumb10__0_carry_n_12\,
      S(2) => \switchNumb10__0_carry_n_13\,
      S(1) => \switchNumb10__51_carry_i_2_n_0\,
      S(0) => \switchNumb10__51_carry_i_3_n_0\
    );
\switchNumb10__51_carry__0\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__51_carry_n_0\,
      CI_TOP => '0',
      CO(7) => \switchNumb10__51_carry__0_n_0\,
      CO(6) => \switchNumb10__51_carry__0_n_1\,
      CO(5) => \switchNumb10__51_carry__0_n_2\,
      CO(4) => \switchNumb10__51_carry__0_n_3\,
      CO(3) => \switchNumb10__51_carry__0_n_4\,
      CO(2) => \switchNumb10__51_carry__0_n_5\,
      CO(1) => \switchNumb10__51_carry__0_n_6\,
      CO(0) => \switchNumb10__51_carry__0_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => switchNumb(15 downto 8),
      S(7) => \switchNumb10__0_carry__0_n_8\,
      S(6) => \switchNumb10__0_carry__0_n_9\,
      S(5) => \switchNumb10__0_carry__0_n_10\,
      S(4) => \switchNumb10__0_carry__0_n_11\,
      S(3) => \switchNumb10__0_carry__0_n_12\,
      S(2) => \switchNumb10__0_carry__0_n_13\,
      S(1) => \switchNumb10__0_carry__0_n_14\,
      S(0) => \switchNumb10__0_carry__0_n_15\
    );
\switchNumb10__51_carry__1\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__51_carry__0_n_0\,
      CI_TOP => '0',
      CO(7) => \switchNumb10__51_carry__1_n_0\,
      CO(6) => \switchNumb10__51_carry__1_n_1\,
      CO(5) => \switchNumb10__51_carry__1_n_2\,
      CO(4) => \switchNumb10__51_carry__1_n_3\,
      CO(3) => \switchNumb10__51_carry__1_n_4\,
      CO(2) => \switchNumb10__51_carry__1_n_5\,
      CO(1) => \switchNumb10__51_carry__1_n_6\,
      CO(0) => \switchNumb10__51_carry__1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => switchNumb(23 downto 16),
      S(7) => \switchNumb10__0_carry__1_n_8\,
      S(6) => \switchNumb10__0_carry__1_n_9\,
      S(5) => \switchNumb10__0_carry__1_n_10\,
      S(4) => \switchNumb10__0_carry__1_n_11\,
      S(3) => \switchNumb10__0_carry__1_n_12\,
      S(2) => \switchNumb10__0_carry__1_n_13\,
      S(1) => \switchNumb10__0_carry__1_n_14\,
      S(0) => \switchNumb10__0_carry__1_n_15\
    );
\switchNumb10__51_carry__2\: unisim.vcomponents.CARRY8
     port map (
      CI => \switchNumb10__51_carry__1_n_0\,
      CI_TOP => '0',
      CO(7 downto 0) => \NLW_switchNumb10__51_carry__2_CO_UNCONNECTED\(7 downto 0),
      DI(7 downto 0) => B"00000000",
      O(7 downto 1) => \NLW_switchNumb10__51_carry__2_O_UNCONNECTED\(7 downto 1),
      O(0) => switchNumb(24),
      S(7 downto 1) => B"0000000",
      S(0) => \switchNumb10__0_carry__2_n_15\
    );
\switchNumb10__51_carry_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6996966996696996"
    )
        port map (
      I0 => D(2),
      I1 => Q(2),
      I2 => Q(4),
      I3 => D(4),
      I4 => Q(3),
      I5 => D(3),
      O => \switchNumb10__51_carry_i_1_n_0\
    );
\switchNumb10__51_carry_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"96AA5596559696AA"
    )
        port map (
      I0 => \switchNumb10__0_carry_n_14\,
      I1 => Q(2),
      I2 => D(2),
      I3 => switchNumb111_out,
      I4 => Q(4),
      I5 => D(4),
      O => \switchNumb10__51_carry_i_2_n_0\
    );
\switchNumb10__51_carry_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => D(5),
      I1 => Q(5),
      I2 => \switchNumb10__0_carry_n_15\,
      O => \switchNumb10__51_carry_i_3_n_0\
    );
\switchNumb10__51_carry_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => Q(3),
      I1 => D(3),
      O => switchNumb111_out
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite is
  port (
    AXI4_Lite_RVALID : out STD_LOGIC;
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    write_axi_enable : out STD_LOGIC;
    soft_reset : out STD_LOGIC;
    bResetAXI : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 25 downto 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    switchNumb : in STD_LOGIC_VECTOR ( 24 downto 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite : entity is "Counter_f_sw_V2_ip_axi_lite";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite is
  signal \^sr\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^bresetaxi\ : STD_LOGIC;
  signal read_reg_ip_timestamp : STD_LOGIC_VECTOR ( 30 to 30 );
  signal read_reg_switchNumb_AXI : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_4 : STD_LOGIC;
  signal u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_5 : STD_LOGIC;
  signal \^write_axi_enable\ : STD_LOGIC;
begin
  SR(0) <= \^sr\(0);
  bResetAXI <= \^bresetaxi\;
  write_axi_enable <= \^write_axi_enable\;
u_Counter_f_sw_V2_ip_addr_decoder_inst: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_addr_decoder
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      Q(24 downto 0) => read_reg_switchNumb_AXI(24 downto 0),
      SR(0) => \^sr\(0),
      bResetAXI => \^bresetaxi\,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      switchNumb(24 downto 0) => switchNumb(24 downto 0),
      write_axi_enable => \^write_axi_enable\,
      write_reg_axi_enable_reg_0 => u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_4,
      write_reg_bResetAXI_reg_0 => u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_5
    );
u_Counter_f_sw_V2_ip_axi_lite_module_inst: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite_module
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(25 downto 0) => AXI4_Lite_RDATA(25 downto 0),
      \AXI4_Lite_RDATA_tmp_reg[24]_0\(24 downto 0) => read_reg_switchNumb_AXI(24 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_WDATA(0) => AXI4_Lite_WDATA(0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      FSM_sequential_axi_lite_rstate_reg_0 => AXI4_Lite_RVALID,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(1 downto 0) => Q(1 downto 0),
      SR(0) => \^sr\(0),
      bResetAXI => \^bresetaxi\,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(30),
      soft_reset => soft_reset,
      \wdata_reg[0]_0\ => u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_4,
      \wdata_reg[0]_1\ => u_Counter_f_sw_V2_ip_axi_lite_module_inst_n_5,
      write_axi_enable => \^write_axi_enable\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2 is
  port (
    switchNumb : out STD_LOGIC_VECTOR ( 24 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    ss_in_5 : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    ss_in_4 : in STD_LOGIC;
    ss_in_3 : in STD_LOGIC;
    ss_in_2 : in STD_LOGIC;
    ss_in_1 : in STD_LOGIC;
    ss_in_0 : in STD_LOGIC;
    bResetAXI : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    soft_reset : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2 : entity is "Counter_f_sw_V2_ip_src_Counter_f_sw_V2";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2 is
  signal Mux_out1 : STD_LOGIC_VECTOR ( 0 to 5 );
  signal \SS_Old_out1_reg_n_0_[5]\ : STD_LOGIC;
  signal bResetAXI_1 : STD_LOGIC;
  signal delay_out1 : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal reset_old2_out1 : STD_LOGIC;
  signal reset_old2_out1_i_1_n_0 : STD_LOGIC;
  signal ss_v_old_0 : STD_LOGIC;
  signal ss_v_old_1 : STD_LOGIC;
  signal ss_v_old_2 : STD_LOGIC;
  signal ss_v_old_3 : STD_LOGIC;
  signal ss_v_old_4 : STD_LOGIC;
  signal \^switchnumb\ : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal switchNumb1 : STD_LOGIC_VECTOR ( 24 to 24 );
begin
  switchNumb(24 downto 0) <= \^switchnumb\(24 downto 0);
\SS_Old_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Mux_out1(0),
      Q => ss_v_old_0,
      R => SR(0)
    );
\SS_Old_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Mux_out1(1),
      Q => ss_v_old_1,
      R => SR(0)
    );
\SS_Old_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Mux_out1(2),
      Q => ss_v_old_2,
      R => SR(0)
    );
\SS_Old_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Mux_out1(3),
      Q => ss_v_old_3,
      R => SR(0)
    );
\SS_Old_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Mux_out1(4),
      Q => ss_v_old_4,
      R => SR(0)
    );
\SS_Old_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => Mux_out1(5),
      Q => \SS_Old_out1_reg_n_0_[5]\,
      R => SR(0)
    );
bResetAXI_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => bResetAXI,
      Q => bResetAXI_1,
      R => SR(0)
    );
\delay_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(0),
      Q => delay_out1(0),
      R => SR(0)
    );
\delay_out1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(10),
      Q => delay_out1(10),
      R => SR(0)
    );
\delay_out1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(11),
      Q => delay_out1(11),
      R => SR(0)
    );
\delay_out1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(12),
      Q => delay_out1(12),
      R => SR(0)
    );
\delay_out1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(13),
      Q => delay_out1(13),
      R => SR(0)
    );
\delay_out1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(14),
      Q => delay_out1(14),
      R => SR(0)
    );
\delay_out1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(15),
      Q => delay_out1(15),
      R => SR(0)
    );
\delay_out1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(16),
      Q => delay_out1(16),
      R => SR(0)
    );
\delay_out1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(17),
      Q => delay_out1(17),
      R => SR(0)
    );
\delay_out1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(18),
      Q => delay_out1(18),
      R => SR(0)
    );
\delay_out1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(19),
      Q => delay_out1(19),
      R => SR(0)
    );
\delay_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(1),
      Q => delay_out1(1),
      R => SR(0)
    );
\delay_out1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(20),
      Q => delay_out1(20),
      R => SR(0)
    );
\delay_out1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(21),
      Q => delay_out1(21),
      R => SR(0)
    );
\delay_out1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(22),
      Q => delay_out1(22),
      R => SR(0)
    );
\delay_out1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(23),
      Q => delay_out1(23),
      R => SR(0)
    );
\delay_out1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(24),
      Q => delay_out1(24),
      R => SR(0)
    );
\delay_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(2),
      Q => delay_out1(2),
      R => SR(0)
    );
\delay_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(3),
      Q => delay_out1(3),
      R => SR(0)
    );
\delay_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(4),
      Q => delay_out1(4),
      R => SR(0)
    );
\delay_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(5),
      Q => delay_out1(5),
      R => SR(0)
    );
\delay_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(6),
      Q => delay_out1(6),
      R => SR(0)
    );
\delay_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(7),
      Q => delay_out1(7),
      R => SR(0)
    );
\delay_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(8),
      Q => delay_out1(8),
      R => SR(0)
    );
\delay_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \^switchnumb\(9),
      Q => delay_out1(9),
      R => SR(0)
    );
reset_old2_out1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000CA0000000000"
    )
        port map (
      I0 => reset_old2_out1,
      I1 => bResetAXI_1,
      I2 => E(0),
      I3 => IPCORE_RESETN,
      I4 => soft_reset,
      I5 => AXI4_Lite_ARESETN,
      O => reset_old2_out1_i_1_n_0
    );
reset_old2_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_old2_out1_i_1_n_0,
      Q => reset_old2_out1,
      R => '0'
    );
ss_in_0_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => ss_in_0,
      Q => Mux_out1(0),
      R => SR(0)
    );
ss_in_1_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => ss_in_1,
      Q => Mux_out1(1),
      R => SR(0)
    );
ss_in_2_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => ss_in_2,
      Q => Mux_out1(2),
      R => SR(0)
    );
ss_in_3_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => ss_in_3,
      Q => Mux_out1(3),
      R => SR(0)
    );
ss_in_4_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => ss_in_4,
      Q => Mux_out1(4),
      R => SR(0)
    );
ss_in_5_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => ss_in_5,
      Q => Mux_out1(5),
      R => SR(0)
    );
\switchNumb10__0_carry__2_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A2"
    )
        port map (
      I0 => delay_out1(24),
      I1 => bResetAXI_1,
      I2 => reset_old2_out1,
      O => switchNumb1(24)
    );
u_Count_f_sw: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Count_f_sw
     port map (
      D(5) => Mux_out1(0),
      D(4) => Mux_out1(1),
      D(3) => Mux_out1(2),
      D(2) => Mux_out1(3),
      D(1) => Mux_out1(4),
      D(0) => Mux_out1(5),
      Q(5) => ss_v_old_0,
      Q(4) => ss_v_old_1,
      Q(3) => ss_v_old_2,
      Q(2) => ss_v_old_3,
      Q(1) => ss_v_old_4,
      Q(0) => \SS_Old_out1_reg_n_0_[5]\,
      S(0) => switchNumb1(24),
      bResetAXI_1 => bResetAXI_1,
      reset_old2_out1 => reset_old2_out1,
      switchNumb(24 downto 0) => \^switchnumb\(24 downto 0),
      \switchNumb10__0_carry__1_0\(23 downto 0) => delay_out1(23 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut is
  port (
    switchNumb : out STD_LOGIC_VECTOR ( 24 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    ss_in_5 : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    ss_in_4 : in STD_LOGIC;
    ss_in_3 : in STD_LOGIC;
    ss_in_2 : in STD_LOGIC;
    ss_in_1 : in STD_LOGIC;
    ss_in_0 : in STD_LOGIC;
    bResetAXI : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    soft_reset : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut : entity is "Counter_f_sw_V2_ip_dut";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut is
begin
u_Counter_f_sw_V2_ip_src_Counter_f_sw_V2: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_src_Counter_f_sw_V2
     port map (
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      E(0) => E(0),
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      SR(0) => SR(0),
      bResetAXI => bResetAXI,
      soft_reset => soft_reset,
      ss_in_0 => ss_in_0,
      ss_in_1 => ss_in_1,
      ss_in_2 => ss_in_2,
      ss_in_3 => ss_in_3,
      ss_in_4 => ss_in_4,
      ss_in_5 => ss_in_5,
      switchNumb(24 downto 0) => switchNumb(24 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip is
  port (
    AXI4_Lite_RVALID : out STD_LOGIC;
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    switchNumb : out STD_LOGIC_VECTOR ( 24 downto 0 );
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 25 downto 0 );
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    ss_in_5 : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    ss_in_4 : in STD_LOGIC;
    ss_in_3 : in STD_LOGIC;
    ss_in_2 : in STD_LOGIC;
    ss_in_1 : in STD_LOGIC;
    ss_in_0 : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WVALID : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip : entity is "Counter_f_sw_V2_ip";
end zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip is
  signal bResetAXI : STD_LOGIC;
  signal reset : STD_LOGIC;
  signal \^switchnumb\ : STD_LOGIC_VECTOR ( 24 downto 0 );
  signal \u_Counter_f_sw_V2_ip_axi_lite_module_inst/soft_reset\ : STD_LOGIC;
  signal write_axi_enable : STD_LOGIC;
begin
  switchNumb(24 downto 0) <= \^switchnumb\(24 downto 0);
u_Counter_f_sw_V2_ip_axi_lite_inst: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_axi_lite
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(13 downto 0),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(13 downto 0),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_RDATA(25 downto 0) => AXI4_Lite_RDATA(25 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_RVALID => AXI4_Lite_RVALID,
      AXI4_Lite_WDATA(0) => AXI4_Lite_WDATA(0),
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(1) => AXI4_Lite_BVALID,
      Q(0) => AXI4_Lite_WREADY,
      SR(0) => reset,
      bResetAXI => bResetAXI,
      soft_reset => \u_Counter_f_sw_V2_ip_axi_lite_module_inst/soft_reset\,
      switchNumb(24 downto 0) => \^switchnumb\(24 downto 0),
      write_axi_enable => write_axi_enable
    );
u_Counter_f_sw_V2_ip_dut_inst: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip_dut
     port map (
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      E(0) => write_axi_enable,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      SR(0) => reset,
      bResetAXI => bResetAXI,
      soft_reset => \u_Counter_f_sw_V2_ip_axi_lite_module_inst/soft_reset\,
      ss_in_0 => ss_in_0,
      ss_in_1 => ss_in_1,
      ss_in_2 => ss_in_2,
      ss_in_3 => ss_in_3,
      ss_in_4 => ss_in_4,
      ss_in_5 => ss_in_5,
      switchNumb(24 downto 0) => \^switchnumb\(24 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_Counter_f_sw_V2_ip_0_0 is
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
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_Counter_f_sw_V2_ip_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_Counter_f_sw_V2_ip_0_0 : entity is "zusys_Counter_f_sw_V2_ip_0_0,Counter_f_sw_V2_ip,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_Counter_f_sw_V2_ip_0_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_Counter_f_sw_V2_ip_0_0 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of zusys_Counter_f_sw_V2_ip_0_0 : entity is "Counter_f_sw_V2_ip,Vivado 2020.1.1";
end zusys_Counter_f_sw_V2_ip_0_0;

architecture STRUCTURE of zusys_Counter_f_sw_V2_ip_0_0 is
  signal \<const0>\ : STD_LOGIC;
  signal \^axi4_lite_rdata\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  attribute x_interface_info : string;
  attribute x_interface_info of AXI4_Lite_ACLK : signal is "xilinx.com:signal:clock:1.0 AXI4_Lite_signal_clock CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of AXI4_Lite_ACLK : signal is "XIL_INTERFACENAME AXI4_Lite_signal_clock, ASSOCIATED_BUSIF AXI4_Lite, ASSOCIATED_RESET AXI4_Lite_ARESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_ARESETN : signal is "xilinx.com:signal:reset:1.0 AXI4_Lite_signal_reset RST";
  attribute x_interface_parameter of AXI4_Lite_ARESETN : signal is "XIL_INTERFACENAME AXI4_Lite_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_ARREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite ARREADY";
  attribute x_interface_info of AXI4_Lite_ARVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite ARVALID";
  attribute x_interface_info of AXI4_Lite_AWREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite AWREADY";
  attribute x_interface_info of AXI4_Lite_AWVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite AWVALID";
  attribute x_interface_info of AXI4_Lite_BREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite BREADY";
  attribute x_interface_info of AXI4_Lite_BVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite BVALID";
  attribute x_interface_info of AXI4_Lite_RREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RREADY";
  attribute x_interface_info of AXI4_Lite_RVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RVALID";
  attribute x_interface_info of AXI4_Lite_WREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WREADY";
  attribute x_interface_info of AXI4_Lite_WVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WVALID";
  attribute x_interface_info of IPCORE_CLK : signal is "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK";
  attribute x_interface_parameter of IPCORE_CLK : signal is "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of IPCORE_RESETN : signal is "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST";
  attribute x_interface_parameter of IPCORE_RESETN : signal is "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_ARADDR : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite ARADDR";
  attribute x_interface_info of AXI4_Lite_AWADDR : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite AWADDR";
  attribute x_interface_parameter of AXI4_Lite_AWADDR : signal is "XIL_INTERFACENAME AXI4_Lite, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute x_interface_info of AXI4_Lite_BRESP : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite BRESP";
  attribute x_interface_info of AXI4_Lite_RDATA : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RDATA";
  attribute x_interface_info of AXI4_Lite_RRESP : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite RRESP";
  attribute x_interface_info of AXI4_Lite_WDATA : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WDATA";
  attribute x_interface_info of AXI4_Lite_WSTRB : signal is "xilinx.com:interface:aximm:1.0 AXI4_Lite WSTRB";
begin
  AXI4_Lite_BRESP(1) <= \<const0>\;
  AXI4_Lite_BRESP(0) <= \<const0>\;
  AXI4_Lite_RDATA(31) <= \<const0>\;
  AXI4_Lite_RDATA(30) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(29) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(28) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(27) <= \<const0>\;
  AXI4_Lite_RDATA(26) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(25) <= \^axi4_lite_rdata\(29);
  AXI4_Lite_RDATA(24 downto 0) <= \^axi4_lite_rdata\(24 downto 0);
  AXI4_Lite_RRESP(1) <= \<const0>\;
  AXI4_Lite_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_Counter_f_sw_V2_ip_0_0_Counter_f_sw_V2_ip
     port map (
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARADDR(13 downto 0) => AXI4_Lite_ARADDR(15 downto 2),
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_AWADDR(13 downto 0) => AXI4_Lite_AWADDR(15 downto 2),
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_BVALID => AXI4_Lite_BVALID,
      AXI4_Lite_RDATA(25) => \^axi4_lite_rdata\(29),
      AXI4_Lite_RDATA(24 downto 0) => \^axi4_lite_rdata\(24 downto 0),
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      AXI4_Lite_RVALID => AXI4_Lite_RVALID,
      AXI4_Lite_WDATA(0) => AXI4_Lite_WDATA(0),
      AXI4_Lite_WREADY => AXI4_Lite_WREADY,
      AXI4_Lite_WSTRB(3 downto 0) => AXI4_Lite_WSTRB(3 downto 0),
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      ss_in_0 => ss_in_0,
      ss_in_1 => ss_in_1,
      ss_in_2 => ss_in_2,
      ss_in_3 => ss_in_3,
      ss_in_4 => ss_in_4,
      ss_in_5 => ss_in_5,
      switchNumb(24 downto 0) => switchNumb(24 downto 0)
    );
end STRUCTURE;
