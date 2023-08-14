-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:44:28 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_interlockDeadtime_0_0/zusys_uz_interlockDeadtime_0_0_sim_netlist.vhdl
-- Design      : zusys_uz_interlockDeadtime_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic is
  port (
    axi4_rd_active_reg : out STD_LOGIC;
    axi4_rd_active_reg_0 : out STD_LOGIC;
    \axi4_raddr_reg[8]\ : out STD_LOGIC;
    \waddr_reg[15]\ : out STD_LOGIC;
    \waddr_reg[11]\ : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    D : out STD_LOGIC_VECTOR ( 31 downto 0 );
    data_int : out STD_LOGIC_VECTOR ( 31 downto 0 );
    w_d1_reg : out STD_LOGIC_VECTOR ( 31 downto 0 );
    \data_int_reg[1]_0\ : in STD_LOGIC_VECTOR ( 9 downto 0 );
    Q : in STD_LOGIC_VECTOR ( 13 downto 0 );
    read_reg_axi_fb_enable : in STD_LOGIC;
    read_reg_axi_fb_InverseBotSwitch : in STD_LOGIC;
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_axi_DelayCycles_1_1_reg[9]\ : in STD_LOGIC_VECTOR ( 5 downto 0 );
    rd_active : in STD_LOGIC;
    data_reg_axi_enable_1_1_i_2 : in STD_LOGIC;
    data_reg_axi_enable_1_1_i_2_0 : in STD_LOGIC;
    \fifo_back_indx_reg[3]\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    top_rd_enb : in STD_LOGIC;
    \cache_data_reg[31]\ : in STD_LOGIC;
    \cache_data_reg[31]_0\ : in STD_LOGIC_VECTOR ( 31 downto 0 );
    cache_valid : in STD_LOGIC;
    \Out_tmp_reg[31]\ : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_ACLK : in STD_LOGIC;
    \data_int_reg[29]_0\ : in STD_LOGIC_VECTOR ( 3 downto 0 );
    \data_int_reg[29]_1\ : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic : entity is "uz_interlockDeadtime2L_SimpleDualPortRAM_generic";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic is
  signal \^e\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^axi4_raddr_reg[8]\ : STD_LOGIC;
  signal \^axi4_rd_active_reg\ : STD_LOGIC;
  signal \^axi4_rd_active_reg_0\ : STD_LOGIC;
  signal \^data_int\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal p_1_out : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal ram_reg_0_15_0_13_i_13_n_0 : STD_LOGIC;
  signal ram_reg_0_15_0_13_i_14_n_0 : STD_LOGIC;
  signal ram_reg_0_15_0_13_i_15_n_0 : STD_LOGIC;
  signal ram_reg_0_15_0_13_i_16_n_0 : STD_LOGIC;
  signal ram_reg_0_15_0_13_i_18_n_0 : STD_LOGIC;
  signal ram_reg_0_15_0_13_i_20_n_0 : STD_LOGIC;
  signal \^waddr_reg[11]\ : STD_LOGIC;
  signal \^waddr_reg[15]\ : STD_LOGIC;
  signal wr_din : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_ram_reg_0_15_0_13_DOH_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_14_27_DOH_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_28_31_DOC_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_28_31_DOD_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_28_31_DOE_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_28_31_DOF_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_28_31_DOG_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_28_31_DOH_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Out_tmp[0]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \Out_tmp[10]_i_1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \Out_tmp[11]_i_1__0\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \Out_tmp[12]_i_1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \Out_tmp[13]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \Out_tmp[14]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \Out_tmp[15]_i_1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \Out_tmp[16]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \Out_tmp[17]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \Out_tmp[18]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \Out_tmp[19]_i_1\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \Out_tmp[1]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \Out_tmp[20]_i_1\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \Out_tmp[21]_i_1\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \Out_tmp[22]_i_1\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \Out_tmp[23]_i_1\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \Out_tmp[24]_i_1\ : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of \Out_tmp[25]_i_1\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \Out_tmp[26]_i_1\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \Out_tmp[27]_i_1\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \Out_tmp[28]_i_1\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \Out_tmp[29]_i_1\ : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of \Out_tmp[2]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \Out_tmp[30]_i_1\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \Out_tmp[31]_i_2\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \Out_tmp[3]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \Out_tmp[4]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \Out_tmp[5]_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \Out_tmp[6]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \Out_tmp[7]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \Out_tmp[8]_i_1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \Out_tmp[9]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \cache_data[0]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \cache_data[10]_i_1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \cache_data[11]_i_1__0\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \cache_data[12]_i_1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \cache_data[13]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \cache_data[14]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \cache_data[15]_i_1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \cache_data[16]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \cache_data[17]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \cache_data[18]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \cache_data[19]_i_1\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \cache_data[1]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \cache_data[20]_i_1\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \cache_data[21]_i_1\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \cache_data[22]_i_1\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \cache_data[23]_i_1\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \cache_data[24]_i_1\ : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of \cache_data[25]_i_1\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \cache_data[26]_i_1\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \cache_data[27]_i_1\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \cache_data[28]_i_1\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \cache_data[29]_i_1\ : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of \cache_data[2]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \cache_data[30]_i_1\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \cache_data[31]_i_2\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \cache_data[3]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \cache_data[4]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \cache_data[5]_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \cache_data[6]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \cache_data[7]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \cache_data[8]_i_1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \cache_data[9]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \data_reg_axi_DelayCycles_1_1[9]_i_3\ : label is "soft_lutpair43";
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of ram_reg_0_15_0_13 : label is "";
  attribute RTL_RAM_BITS : integer;
  attribute RTL_RAM_BITS of ram_reg_0_15_0_13 : label is 512;
  attribute RTL_RAM_NAME : string;
  attribute RTL_RAM_NAME of ram_reg_0_15_0_13 : label is "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_data_inst/u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic/ram";
  attribute RTL_RAM_TYPE : string;
  attribute RTL_RAM_TYPE of ram_reg_0_15_0_13 : label is "RAM_SDP";
  attribute ram_addr_begin : integer;
  attribute ram_addr_begin of ram_reg_0_15_0_13 : label is 0;
  attribute ram_addr_end : integer;
  attribute ram_addr_end of ram_reg_0_15_0_13 : label is 15;
  attribute ram_offset : integer;
  attribute ram_offset of ram_reg_0_15_0_13 : label is 0;
  attribute ram_slice_begin : integer;
  attribute ram_slice_begin of ram_reg_0_15_0_13 : label is 0;
  attribute ram_slice_end : integer;
  attribute ram_slice_end of ram_reg_0_15_0_13 : label is 13;
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_10 : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_16 : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_18 : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_2 : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_20 : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_4 : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_5 : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_6 : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_7 : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_8 : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of ram_reg_0_15_0_13_i_9 : label is "soft_lutpair39";
  attribute METHODOLOGY_DRC_VIOS of ram_reg_0_15_14_27 : label is "";
  attribute RTL_RAM_BITS of ram_reg_0_15_14_27 : label is 512;
  attribute RTL_RAM_NAME of ram_reg_0_15_14_27 : label is "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_data_inst/u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic/ram";
  attribute RTL_RAM_TYPE of ram_reg_0_15_14_27 : label is "RAM_SDP";
  attribute ram_addr_begin of ram_reg_0_15_14_27 : label is 0;
  attribute ram_addr_end of ram_reg_0_15_14_27 : label is 15;
  attribute ram_offset of ram_reg_0_15_14_27 : label is 0;
  attribute ram_slice_begin of ram_reg_0_15_14_27 : label is 14;
  attribute ram_slice_end of ram_reg_0_15_14_27 : label is 27;
  attribute METHODOLOGY_DRC_VIOS of ram_reg_0_15_28_31 : label is "";
  attribute RTL_RAM_BITS of ram_reg_0_15_28_31 : label is 512;
  attribute RTL_RAM_NAME of ram_reg_0_15_28_31 : label is "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_data_inst/u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic/ram";
  attribute RTL_RAM_TYPE of ram_reg_0_15_28_31 : label is "RAM_SDP";
  attribute ram_addr_begin of ram_reg_0_15_28_31 : label is 0;
  attribute ram_addr_end of ram_reg_0_15_28_31 : label is 15;
  attribute ram_offset of ram_reg_0_15_28_31 : label is 0;
  attribute ram_slice_begin of ram_reg_0_15_28_31 : label is 28;
  attribute ram_slice_end of ram_reg_0_15_28_31 : label is 31;
begin
  E(0) <= \^e\(0);
  \axi4_raddr_reg[8]\ <= \^axi4_raddr_reg[8]\;
  axi4_rd_active_reg <= \^axi4_rd_active_reg\;
  axi4_rd_active_reg_0 <= \^axi4_rd_active_reg_0\;
  data_int(31 downto 0) <= \^data_int\(31 downto 0);
  \waddr_reg[11]\ <= \^waddr_reg[11]\;
  \waddr_reg[15]\ <= \^waddr_reg[15]\;
\Out_tmp[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(0),
      I2 => \^data_int\(0),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(0),
      O => w_d1_reg(0)
    );
\Out_tmp[10]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(10),
      I2 => \^data_int\(10),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(10),
      O => w_d1_reg(10)
    );
\Out_tmp[11]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(11),
      I2 => \^data_int\(11),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(11),
      O => w_d1_reg(11)
    );
\Out_tmp[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(12),
      I2 => \^data_int\(12),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(12),
      O => w_d1_reg(12)
    );
\Out_tmp[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(13),
      I2 => \^data_int\(13),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(13),
      O => w_d1_reg(13)
    );
\Out_tmp[14]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(14),
      I2 => \^data_int\(14),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(14),
      O => w_d1_reg(14)
    );
\Out_tmp[15]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(15),
      I2 => \^data_int\(15),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(15),
      O => w_d1_reg(15)
    );
\Out_tmp[16]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(16),
      I2 => \^data_int\(16),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(16),
      O => w_d1_reg(16)
    );
\Out_tmp[17]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(17),
      I2 => \^data_int\(17),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(17),
      O => w_d1_reg(17)
    );
\Out_tmp[18]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(18),
      I2 => \^data_int\(18),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(18),
      O => w_d1_reg(18)
    );
\Out_tmp[19]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(19),
      I2 => \^data_int\(19),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(19),
      O => w_d1_reg(19)
    );
\Out_tmp[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(1),
      I2 => \^data_int\(1),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(1),
      O => w_d1_reg(1)
    );
\Out_tmp[20]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(20),
      I2 => \^data_int\(20),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(20),
      O => w_d1_reg(20)
    );
\Out_tmp[21]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(21),
      I2 => \^data_int\(21),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(21),
      O => w_d1_reg(21)
    );
\Out_tmp[22]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(22),
      I2 => \^data_int\(22),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(22),
      O => w_d1_reg(22)
    );
\Out_tmp[23]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(23),
      I2 => \^data_int\(23),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(23),
      O => w_d1_reg(23)
    );
\Out_tmp[24]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(24),
      I2 => \^data_int\(24),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(24),
      O => w_d1_reg(24)
    );
\Out_tmp[25]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(25),
      I2 => \^data_int\(25),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(25),
      O => w_d1_reg(25)
    );
\Out_tmp[26]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(26),
      I2 => \^data_int\(26),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(26),
      O => w_d1_reg(26)
    );
\Out_tmp[27]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(27),
      I2 => \^data_int\(27),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(27),
      O => w_d1_reg(27)
    );
\Out_tmp[28]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(28),
      I2 => \^data_int\(28),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(28),
      O => w_d1_reg(28)
    );
\Out_tmp[29]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(29),
      I2 => \^data_int\(29),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(29),
      O => w_d1_reg(29)
    );
\Out_tmp[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(2),
      I2 => \^data_int\(2),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(2),
      O => w_d1_reg(2)
    );
\Out_tmp[30]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(30),
      I2 => \^data_int\(30),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(30),
      O => w_d1_reg(30)
    );
\Out_tmp[31]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(31),
      I2 => \^data_int\(31),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(31),
      O => w_d1_reg(31)
    );
\Out_tmp[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(3),
      I2 => \^data_int\(3),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(3),
      O => w_d1_reg(3)
    );
\Out_tmp[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(4),
      I2 => \^data_int\(4),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(4),
      O => w_d1_reg(4)
    );
\Out_tmp[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(5),
      I2 => \^data_int\(5),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(5),
      O => w_d1_reg(5)
    );
\Out_tmp[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(6),
      I2 => \^data_int\(6),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(6),
      O => w_d1_reg(6)
    );
\Out_tmp[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(7),
      I2 => \^data_int\(7),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(7),
      O => w_d1_reg(7)
    );
\Out_tmp[8]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(8),
      I2 => \^data_int\(8),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(8),
      O => w_d1_reg(8)
    );
\Out_tmp[9]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[31]\,
      I1 => \cache_data_reg[31]_0\(9),
      I2 => \^data_int\(9),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[31]\(9),
      O => w_d1_reg(9)
    );
\cache_data[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(0),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(0),
      O => D(0)
    );
\cache_data[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(10),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(10),
      O => D(10)
    );
\cache_data[11]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(11),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(11),
      O => D(11)
    );
\cache_data[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(12),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(12),
      O => D(12)
    );
\cache_data[13]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(13),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(13),
      O => D(13)
    );
\cache_data[14]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(14),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(14),
      O => D(14)
    );
\cache_data[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(15),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(15),
      O => D(15)
    );
\cache_data[16]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(16),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(16),
      O => D(16)
    );
\cache_data[17]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(17),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(17),
      O => D(17)
    );
\cache_data[18]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(18),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(18),
      O => D(18)
    );
\cache_data[19]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(19),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(19),
      O => D(19)
    );
\cache_data[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(1),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(1),
      O => D(1)
    );
\cache_data[20]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(20),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(20),
      O => D(20)
    );
\cache_data[21]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(21),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(21),
      O => D(21)
    );
\cache_data[22]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(22),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(22),
      O => D(22)
    );
\cache_data[23]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(23),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(23),
      O => D(23)
    );
\cache_data[24]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(24),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(24),
      O => D(24)
    );
\cache_data[25]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(25),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(25),
      O => D(25)
    );
\cache_data[26]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(26),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(26),
      O => D(26)
    );
\cache_data[27]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(27),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(27),
      O => D(27)
    );
\cache_data[28]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(28),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(28),
      O => D(28)
    );
\cache_data[29]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(29),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(29),
      O => D(29)
    );
\cache_data[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(2),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(2),
      O => D(2)
    );
\cache_data[30]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(30),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(30),
      O => D(30)
    );
\cache_data[31]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(31),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(31),
      O => D(31)
    );
\cache_data[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(3),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(3),
      O => D(3)
    );
\cache_data[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(4),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(4),
      O => D(4)
    );
\cache_data[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(5),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(5),
      O => D(5)
    );
\cache_data[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(6),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(6),
      O => D(6)
    );
\cache_data[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(7),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(7),
      O => D(7)
    );
\cache_data[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(8),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(8),
      O => D(8)
    );
\cache_data[9]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(9),
      I1 => \cache_data_reg[31]\,
      I2 => \cache_data_reg[31]_0\(9),
      O => D(9)
    );
\data_int_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(0),
      Q => \^data_int\(0),
      R => '0'
    );
\data_int_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(10),
      Q => \^data_int\(10),
      R => '0'
    );
\data_int_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(11),
      Q => \^data_int\(11),
      R => '0'
    );
\data_int_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(12),
      Q => \^data_int\(12),
      R => '0'
    );
\data_int_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(13),
      Q => \^data_int\(13),
      R => '0'
    );
\data_int_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(14),
      Q => \^data_int\(14),
      R => '0'
    );
\data_int_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(15),
      Q => \^data_int\(15),
      R => '0'
    );
\data_int_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(16),
      Q => \^data_int\(16),
      R => '0'
    );
\data_int_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(17),
      Q => \^data_int\(17),
      R => '0'
    );
\data_int_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(18),
      Q => \^data_int\(18),
      R => '0'
    );
\data_int_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(19),
      Q => \^data_int\(19),
      R => '0'
    );
\data_int_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(1),
      Q => \^data_int\(1),
      R => '0'
    );
\data_int_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(20),
      Q => \^data_int\(20),
      R => '0'
    );
\data_int_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(21),
      Q => \^data_int\(21),
      R => '0'
    );
\data_int_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(22),
      Q => \^data_int\(22),
      R => '0'
    );
\data_int_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(23),
      Q => \^data_int\(23),
      R => '0'
    );
\data_int_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(24),
      Q => \^data_int\(24),
      R => '0'
    );
\data_int_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(25),
      Q => \^data_int\(25),
      R => '0'
    );
\data_int_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(26),
      Q => \^data_int\(26),
      R => '0'
    );
\data_int_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(27),
      Q => \^data_int\(27),
      R => '0'
    );
\data_int_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(28),
      Q => \^data_int\(28),
      R => '0'
    );
\data_int_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(29),
      Q => \^data_int\(29),
      R => '0'
    );
\data_int_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(2),
      Q => \^data_int\(2),
      R => '0'
    );
\data_int_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(30),
      Q => \^data_int\(30),
      R => '0'
    );
\data_int_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(31),
      Q => \^data_int\(31),
      R => '0'
    );
\data_int_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(3),
      Q => \^data_int\(3),
      R => '0'
    );
\data_int_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(4),
      Q => \^data_int\(4),
      R => '0'
    );
\data_int_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(5),
      Q => \^data_int\(5),
      R => '0'
    );
\data_int_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(6),
      Q => \^data_int\(6),
      R => '0'
    );
\data_int_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(7),
      Q => \^data_int\(7),
      R => '0'
    );
\data_int_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(8),
      Q => \^data_int\(8),
      R => '0'
    );
\data_int_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => p_1_out(9),
      Q => \^data_int\(9),
      R => '0'
    );
\data_reg_axi_DelayCycles_1_1[9]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \data_reg_axi_DelayCycles_1_1_reg[9]\(5),
      I1 => \data_reg_axi_DelayCycles_1_1_reg[9]\(1),
      O => \^axi4_raddr_reg[8]\
    );
ram_reg_0_15_0_13: unisim.vcomponents.RAM32M16
    generic map(
      INIT_A => X"0000000000000000",
      INIT_B => X"0000000000000000",
      INIT_C => X"0000000000000000",
      INIT_D => X"0000000000000000",
      INIT_E => X"0000000000000000",
      INIT_F => X"0000000000000000",
      INIT_G => X"0000000000000000",
      INIT_H => X"0000000000000000"
    )
        port map (
      ADDRA(4) => '0',
      ADDRA(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRB(4) => '0',
      ADDRB(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRC(4) => '0',
      ADDRC(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRD(4) => '0',
      ADDRD(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRE(4) => '0',
      ADDRE(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRF(4) => '0',
      ADDRF(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRG(4) => '0',
      ADDRG(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRH(4) => '0',
      ADDRH(3 downto 0) => \data_int_reg[29]_1\(3 downto 0),
      DIA(1 downto 0) => wr_din(1 downto 0),
      DIB(1 downto 0) => wr_din(3 downto 2),
      DIC(1 downto 0) => wr_din(5 downto 4),
      DID(1 downto 0) => wr_din(7 downto 6),
      DIE(1 downto 0) => wr_din(9 downto 8),
      DIF(1) => wr_din(29),
      DIF(0) => wr_din(29),
      DIG(1) => '0',
      DIG(0) => wr_din(29),
      DIH(1 downto 0) => B"00",
      DOA(1 downto 0) => p_1_out(1 downto 0),
      DOB(1 downto 0) => p_1_out(3 downto 2),
      DOC(1 downto 0) => p_1_out(5 downto 4),
      DOD(1 downto 0) => p_1_out(7 downto 6),
      DOE(1 downto 0) => p_1_out(9 downto 8),
      DOF(1 downto 0) => p_1_out(11 downto 10),
      DOG(1 downto 0) => p_1_out(13 downto 12),
      DOH(1 downto 0) => NLW_ram_reg_0_15_0_13_DOH_UNCONNECTED(1 downto 0),
      WCLK => AXI4_ACLK,
      WE => \^e\(0)
    );
ram_reg_0_15_0_13_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFD00000000"
    )
        port map (
      I0 => \fifo_back_indx_reg[3]\(4),
      I1 => \fifo_back_indx_reg[3]\(2),
      I2 => \fifo_back_indx_reg[3]\(0),
      I3 => \fifo_back_indx_reg[3]\(1),
      I4 => \fifo_back_indx_reg[3]\(3),
      I5 => top_rd_enb,
      O => \^e\(0)
    );
ram_reg_0_15_0_13_i_10: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(9),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(9)
    );
ram_reg_0_15_0_13_i_11: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => ram_reg_0_15_0_13_i_13_n_0,
      I1 => \data_int_reg[1]_0\(8),
      O => wr_din(8)
    );
ram_reg_0_15_0_13_i_12: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F8880000"
    )
        port map (
      I0 => ram_reg_0_15_0_13_i_16_n_0,
      I1 => \^axi4_rd_active_reg\,
      I2 => ram_reg_0_15_0_13_i_18_n_0,
      I3 => \^axi4_rd_active_reg_0\,
      I4 => read_reg_ip_timestamp(0),
      O => wr_din(29)
    );
ram_reg_0_15_0_13_i_13: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF80808080808080"
    )
        port map (
      I0 => ram_reg_0_15_0_13_i_20_n_0,
      I1 => \^axi4_rd_active_reg\,
      I2 => Q(0),
      I3 => \^axi4_raddr_reg[8]\,
      I4 => \^axi4_rd_active_reg_0\,
      I5 => \data_reg_axi_DelayCycles_1_1_reg[9]\(0),
      O => ram_reg_0_15_0_13_i_13_n_0
    );
ram_reg_0_15_0_13_i_14: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4400500000000000"
    )
        port map (
      I0 => \data_reg_axi_DelayCycles_1_1_reg[9]\(0),
      I1 => read_reg_axi_fb_enable,
      I2 => read_reg_axi_fb_InverseBotSwitch,
      I3 => \data_reg_axi_DelayCycles_1_1_reg[9]\(5),
      I4 => \data_reg_axi_DelayCycles_1_1_reg[9]\(1),
      I5 => \^axi4_rd_active_reg_0\,
      O => ram_reg_0_15_0_13_i_14_n_0
    );
ram_reg_0_15_0_13_i_15: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4400500000000000"
    )
        port map (
      I0 => Q(0),
      I1 => read_reg_axi_fb_enable,
      I2 => read_reg_axi_fb_InverseBotSwitch,
      I3 => Q(6),
      I4 => Q(1),
      I5 => \^axi4_rd_active_reg\,
      O => ram_reg_0_15_0_13_i_15_n_0
    );
ram_reg_0_15_0_13_i_16: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => Q(6),
      I1 => Q(1),
      I2 => Q(0),
      O => ram_reg_0_15_0_13_i_16_n_0
    );
ram_reg_0_15_0_13_i_17: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000040"
    )
        port map (
      I0 => rd_active,
      I1 => \^waddr_reg[15]\,
      I2 => \^waddr_reg[11]\,
      I3 => Q(4),
      I4 => Q(3),
      I5 => Q(2),
      O => \^axi4_rd_active_reg\
    );
ram_reg_0_15_0_13_i_18: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => \data_reg_axi_DelayCycles_1_1_reg[9]\(5),
      I1 => \data_reg_axi_DelayCycles_1_1_reg[9]\(1),
      I2 => \data_reg_axi_DelayCycles_1_1_reg[9]\(0),
      O => ram_reg_0_15_0_13_i_18_n_0
    );
ram_reg_0_15_0_13_i_19: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000080000"
    )
        port map (
      I0 => data_reg_axi_enable_1_1_i_2,
      I1 => rd_active,
      I2 => \data_reg_axi_DelayCycles_1_1_reg[9]\(3),
      I3 => \data_reg_axi_DelayCycles_1_1_reg[9]\(4),
      I4 => data_reg_axi_enable_1_1_i_2_0,
      I5 => \data_reg_axi_DelayCycles_1_1_reg[9]\(2),
      O => \^axi4_rd_active_reg_0\
    );
ram_reg_0_15_0_13_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(1),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(1)
    );
ram_reg_0_15_0_13_i_20: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Q(6),
      I1 => Q(1),
      O => ram_reg_0_15_0_13_i_20_n_0
    );
ram_reg_0_15_0_13_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFEFEFE"
    )
        port map (
      I0 => wr_din(29),
      I1 => ram_reg_0_15_0_13_i_14_n_0,
      I2 => ram_reg_0_15_0_13_i_15_n_0,
      I3 => \data_int_reg[1]_0\(0),
      I4 => ram_reg_0_15_0_13_i_13_n_0,
      O => wr_din(0)
    );
ram_reg_0_15_0_13_i_4: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(3),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(3)
    );
ram_reg_0_15_0_13_i_5: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => ram_reg_0_15_0_13_i_13_n_0,
      I1 => \data_int_reg[1]_0\(2),
      O => wr_din(2)
    );
ram_reg_0_15_0_13_i_6: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(5),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(5)
    );
ram_reg_0_15_0_13_i_7: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(4),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(4)
    );
ram_reg_0_15_0_13_i_8: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(7),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(7)
    );
ram_reg_0_15_0_13_i_9: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \data_int_reg[1]_0\(6),
      I1 => ram_reg_0_15_0_13_i_13_n_0,
      I2 => wr_din(29),
      O => wr_din(6)
    );
ram_reg_0_15_14_27: unisim.vcomponents.RAM32M16
    generic map(
      INIT_A => X"0000000000000000",
      INIT_B => X"0000000000000000",
      INIT_C => X"0000000000000000",
      INIT_D => X"0000000000000000",
      INIT_E => X"0000000000000000",
      INIT_F => X"0000000000000000",
      INIT_G => X"0000000000000000",
      INIT_H => X"0000000000000000"
    )
        port map (
      ADDRA(4) => '0',
      ADDRA(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRB(4) => '0',
      ADDRB(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRC(4) => '0',
      ADDRC(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRD(4) => '0',
      ADDRD(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRE(4) => '0',
      ADDRE(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRF(4) => '0',
      ADDRF(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRG(4) => '0',
      ADDRG(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRH(4) => '0',
      ADDRH(3 downto 0) => \data_int_reg[29]_1\(3 downto 0),
      DIA(1) => wr_din(29),
      DIA(0) => wr_din(29),
      DIB(1) => wr_din(29),
      DIB(0) => wr_din(29),
      DIC(1) => wr_din(29),
      DIC(0) => '0',
      DID(1) => wr_din(29),
      DID(0) => '0',
      DIE(1) => '0',
      DIE(0) => wr_din(29),
      DIF(1) => '0',
      DIF(0) => wr_din(29),
      DIG(1) => wr_din(29),
      DIG(0) => wr_din(29),
      DIH(1 downto 0) => B"00",
      DOA(1 downto 0) => p_1_out(15 downto 14),
      DOB(1 downto 0) => p_1_out(17 downto 16),
      DOC(1 downto 0) => p_1_out(19 downto 18),
      DOD(1 downto 0) => p_1_out(21 downto 20),
      DOE(1 downto 0) => p_1_out(23 downto 22),
      DOF(1 downto 0) => p_1_out(25 downto 24),
      DOG(1 downto 0) => p_1_out(27 downto 26),
      DOH(1 downto 0) => NLW_ram_reg_0_15_14_27_DOH_UNCONNECTED(1 downto 0),
      WCLK => AXI4_ACLK,
      WE => \^e\(0)
    );
ram_reg_0_15_28_31: unisim.vcomponents.RAM32M16
    generic map(
      INIT_A => X"0000000000000000",
      INIT_B => X"0000000000000000",
      INIT_C => X"0000000000000000",
      INIT_D => X"0000000000000000",
      INIT_E => X"0000000000000000",
      INIT_F => X"0000000000000000",
      INIT_G => X"0000000000000000",
      INIT_H => X"0000000000000000"
    )
        port map (
      ADDRA(4) => '0',
      ADDRA(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRB(4) => '0',
      ADDRB(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRC(4) => '0',
      ADDRC(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRD(4) => '0',
      ADDRD(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRE(4) => '0',
      ADDRE(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRF(4) => '0',
      ADDRF(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRG(4) => '0',
      ADDRG(3 downto 0) => \data_int_reg[29]_0\(3 downto 0),
      ADDRH(4) => '0',
      ADDRH(3 downto 0) => \data_int_reg[29]_1\(3 downto 0),
      DIA(1) => wr_din(29),
      DIA(0) => wr_din(29),
      DIB(1) => '0',
      DIB(0) => wr_din(29),
      DIC(1 downto 0) => B"00",
      DID(1 downto 0) => B"00",
      DIE(1 downto 0) => B"00",
      DIF(1 downto 0) => B"00",
      DIG(1 downto 0) => B"00",
      DIH(1 downto 0) => B"00",
      DOA(1 downto 0) => p_1_out(29 downto 28),
      DOB(1 downto 0) => p_1_out(31 downto 30),
      DOC(1 downto 0) => NLW_ram_reg_0_15_28_31_DOC_UNCONNECTED(1 downto 0),
      DOD(1 downto 0) => NLW_ram_reg_0_15_28_31_DOD_UNCONNECTED(1 downto 0),
      DOE(1 downto 0) => NLW_ram_reg_0_15_28_31_DOE_UNCONNECTED(1 downto 0),
      DOF(1 downto 0) => NLW_ram_reg_0_15_28_31_DOF_UNCONNECTED(1 downto 0),
      DOG(1 downto 0) => NLW_ram_reg_0_15_28_31_DOG_UNCONNECTED(1 downto 0),
      DOH(1 downto 0) => NLW_ram_reg_0_15_28_31_DOH_UNCONNECTED(1 downto 0),
      WCLK => AXI4_ACLK,
      WE => \^e\(0)
    );
soft_reset_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => Q(13),
      I1 => Q(12),
      I2 => Q(11),
      I3 => Q(10),
      O => \^waddr_reg[15]\
    );
soft_reset_i_3: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => Q(9),
      I1 => Q(8),
      I2 => Q(7),
      I3 => Q(5),
      O => \^waddr_reg[11]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1\ is
  port (
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    D : out STD_LOGIC_VECTOR ( 11 downto 0 );
    data_int : out STD_LOGIC_VECTOR ( 11 downto 0 );
    w_d1_reg : out STD_LOGIC_VECTOR ( 11 downto 0 );
    Q : in STD_LOGIC_VECTOR ( 4 downto 0 );
    top_rd_enb : in STD_LOGIC;
    \cache_data_reg[11]\ : in STD_LOGIC;
    \cache_data_reg[11]_0\ : in STD_LOGIC_VECTOR ( 11 downto 0 );
    cache_valid : in STD_LOGIC;
    \Out_tmp_reg[11]\ : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_ACLK : in STD_LOGIC;
    \data_int_reg[1]_0\ : in STD_LOGIC_VECTOR ( 11 downto 0 );
    \data_int_reg[1]_1\ : in STD_LOGIC_VECTOR ( 3 downto 0 );
    \data_int_reg[1]_2\ : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1\ : entity is "uz_interlockDeadtime2L_SimpleDualPortRAM_generic";
end \zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1\;

architecture STRUCTURE of \zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1\ is
  signal \^e\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^data_int\ : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal \p_1_out__0\ : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal NLW_ram_reg_0_15_0_11_DOG_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_ram_reg_0_15_0_11_DOH_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Out_tmp[0]_i_1__0\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \Out_tmp[10]_i_1__0\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \Out_tmp[11]_i_2\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \Out_tmp[1]_i_1__0\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \Out_tmp[2]_i_1__0\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \Out_tmp[3]_i_1__0\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \Out_tmp[4]_i_1__0\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \Out_tmp[5]_i_1__0\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \Out_tmp[6]_i_1__0\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \Out_tmp[7]_i_1__0\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \Out_tmp[8]_i_1__0\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \Out_tmp[9]_i_1__0\ : label is "soft_lutpair70";
  attribute SOFT_HLUTNM of \cache_data[0]_i_1__0\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \cache_data[10]_i_1__0\ : label is "soft_lutpair71";
  attribute SOFT_HLUTNM of \cache_data[11]_i_2\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \cache_data[1]_i_1__0\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \cache_data[2]_i_1__0\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \cache_data[3]_i_1__0\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \cache_data[4]_i_1__0\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \cache_data[5]_i_1__0\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \cache_data[6]_i_1__0\ : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of \cache_data[7]_i_1__0\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \cache_data[8]_i_1__0\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \cache_data[9]_i_1__0\ : label is "soft_lutpair70";
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of ram_reg_0_15_0_11 : label is "";
  attribute RTL_RAM_BITS : integer;
  attribute RTL_RAM_BITS of ram_reg_0_15_0_11 : label is 192;
  attribute RTL_RAM_NAME : string;
  attribute RTL_RAM_NAME of ram_reg_0_15_0_11 : label is "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_rid_inst/u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram/ram";
  attribute RTL_RAM_TYPE : string;
  attribute RTL_RAM_TYPE of ram_reg_0_15_0_11 : label is "RAM_SDP";
  attribute ram_addr_begin : integer;
  attribute ram_addr_begin of ram_reg_0_15_0_11 : label is 0;
  attribute ram_addr_end : integer;
  attribute ram_addr_end of ram_reg_0_15_0_11 : label is 15;
  attribute ram_offset : integer;
  attribute ram_offset of ram_reg_0_15_0_11 : label is 0;
  attribute ram_slice_begin : integer;
  attribute ram_slice_begin of ram_reg_0_15_0_11 : label is 0;
  attribute ram_slice_end : integer;
  attribute ram_slice_end of ram_reg_0_15_0_11 : label is 11;
begin
  E(0) <= \^e\(0);
  data_int(11 downto 0) <= \^data_int\(11 downto 0);
\Out_tmp[0]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(0),
      I2 => \^data_int\(0),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(0),
      O => w_d1_reg(0)
    );
\Out_tmp[10]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(10),
      I2 => \^data_int\(10),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(10),
      O => w_d1_reg(10)
    );
\Out_tmp[11]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(11),
      I2 => \^data_int\(11),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(11),
      O => w_d1_reg(11)
    );
\Out_tmp[1]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(1),
      I2 => \^data_int\(1),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(1),
      O => w_d1_reg(1)
    );
\Out_tmp[2]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(2),
      I2 => \^data_int\(2),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(2),
      O => w_d1_reg(2)
    );
\Out_tmp[3]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(3),
      I2 => \^data_int\(3),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(3),
      O => w_d1_reg(3)
    );
\Out_tmp[4]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(4),
      I2 => \^data_int\(4),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(4),
      O => w_d1_reg(4)
    );
\Out_tmp[5]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(5),
      I2 => \^data_int\(5),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(5),
      O => w_d1_reg(5)
    );
\Out_tmp[6]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(6),
      I2 => \^data_int\(6),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(6),
      O => w_d1_reg(6)
    );
\Out_tmp[7]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(7),
      I2 => \^data_int\(7),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(7),
      O => w_d1_reg(7)
    );
\Out_tmp[8]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(8),
      I2 => \^data_int\(8),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(8),
      O => w_d1_reg(8)
    );
\Out_tmp[9]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFE400E4"
    )
        port map (
      I0 => \cache_data_reg[11]\,
      I1 => \cache_data_reg[11]_0\(9),
      I2 => \^data_int\(9),
      I3 => cache_valid,
      I4 => \Out_tmp_reg[11]\(9),
      O => w_d1_reg(9)
    );
\cache_data[0]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(0),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(0),
      O => D(0)
    );
\cache_data[10]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(10),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(10),
      O => D(10)
    );
\cache_data[11]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(11),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(11),
      O => D(11)
    );
\cache_data[1]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(1),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(1),
      O => D(1)
    );
\cache_data[2]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(2),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(2),
      O => D(2)
    );
\cache_data[3]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(3),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(3),
      O => D(3)
    );
\cache_data[4]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(4),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(4),
      O => D(4)
    );
\cache_data[5]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(5),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(5),
      O => D(5)
    );
\cache_data[6]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(6),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(6),
      O => D(6)
    );
\cache_data[7]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(7),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(7),
      O => D(7)
    );
\cache_data[8]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(8),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(8),
      O => D(8)
    );
\cache_data[9]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \^data_int\(9),
      I1 => \cache_data_reg[11]\,
      I2 => \cache_data_reg[11]_0\(9),
      O => D(9)
    );
\data_int_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(0),
      Q => \^data_int\(0),
      R => '0'
    );
\data_int_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(10),
      Q => \^data_int\(10),
      R => '0'
    );
\data_int_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(11),
      Q => \^data_int\(11),
      R => '0'
    );
\data_int_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(1),
      Q => \^data_int\(1),
      R => '0'
    );
\data_int_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(2),
      Q => \^data_int\(2),
      R => '0'
    );
\data_int_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(3),
      Q => \^data_int\(3),
      R => '0'
    );
\data_int_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(4),
      Q => \^data_int\(4),
      R => '0'
    );
\data_int_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(5),
      Q => \^data_int\(5),
      R => '0'
    );
\data_int_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(6),
      Q => \^data_int\(6),
      R => '0'
    );
\data_int_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(7),
      Q => \^data_int\(7),
      R => '0'
    );
\data_int_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(8),
      Q => \^data_int\(8),
      R => '0'
    );
\data_int_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__0\(9),
      Q => \^data_int\(9),
      R => '0'
    );
ram_reg_0_15_0_11: unisim.vcomponents.RAM32M16
    generic map(
      INIT_A => X"0000000000000000",
      INIT_B => X"0000000000000000",
      INIT_C => X"0000000000000000",
      INIT_D => X"0000000000000000",
      INIT_E => X"0000000000000000",
      INIT_F => X"0000000000000000",
      INIT_G => X"0000000000000000",
      INIT_H => X"0000000000000000"
    )
        port map (
      ADDRA(4) => '0',
      ADDRA(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRB(4) => '0',
      ADDRB(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRC(4) => '0',
      ADDRC(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRD(4) => '0',
      ADDRD(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRE(4) => '0',
      ADDRE(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRF(4) => '0',
      ADDRF(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRG(4) => '0',
      ADDRG(3 downto 0) => \data_int_reg[1]_1\(3 downto 0),
      ADDRH(4) => '0',
      ADDRH(3 downto 0) => \data_int_reg[1]_2\(3 downto 0),
      DIA(1 downto 0) => \data_int_reg[1]_0\(1 downto 0),
      DIB(1 downto 0) => \data_int_reg[1]_0\(3 downto 2),
      DIC(1 downto 0) => \data_int_reg[1]_0\(5 downto 4),
      DID(1 downto 0) => \data_int_reg[1]_0\(7 downto 6),
      DIE(1 downto 0) => \data_int_reg[1]_0\(9 downto 8),
      DIF(1 downto 0) => \data_int_reg[1]_0\(11 downto 10),
      DIG(1 downto 0) => B"00",
      DIH(1 downto 0) => B"00",
      DOA(1 downto 0) => \p_1_out__0\(1 downto 0),
      DOB(1 downto 0) => \p_1_out__0\(3 downto 2),
      DOC(1 downto 0) => \p_1_out__0\(5 downto 4),
      DOD(1 downto 0) => \p_1_out__0\(7 downto 6),
      DOE(1 downto 0) => \p_1_out__0\(9 downto 8),
      DOF(1 downto 0) => \p_1_out__0\(11 downto 10),
      DOG(1 downto 0) => NLW_ram_reg_0_15_0_11_DOG_UNCONNECTED(1 downto 0),
      DOH(1 downto 0) => NLW_ram_reg_0_15_0_11_DOH_UNCONNECTED(1 downto 0),
      WCLK => AXI4_ACLK,
      WE => \^e\(0)
    );
ram_reg_0_15_0_11_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFD00000000"
    )
        port map (
      I0 => Q(4),
      I1 => Q(2),
      I2 => Q(0),
      I3 => Q(1),
      I4 => Q(3),
      I5 => top_rd_enb,
      O => \^e\(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit is
  port (
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_RREADY_0 : out STD_LOGIC;
    w_out : out STD_LOGIC;
    cache_data_reg : out STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 4 downto 0 );
    top_rd_enb : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    out_valid : in STD_LOGIC;
    fifo_valid : in STD_LOGIC;
    cache_valid : in STD_LOGIC;
    cache_data_reg_0 : in STD_LOGIC;
    Out_rsvd_reg : in STD_LOGIC;
    AXI4_RLAST : in STD_LOGIC;
    w_d2_reg : in STD_LOGIC;
    w_d2 : in STD_LOGIC;
    AXI4_ACLK : in STD_LOGIC;
    axi4_rlast_1 : in STD_LOGIC;
    data_int_reg_0 : in STD_LOGIC_VECTOR ( 3 downto 0 );
    data_int_reg_1 : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit : entity is "uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit is
  signal \^e\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \p_1_out__1\ : STD_LOGIC;
  signal \^w_out\ : STD_LOGIC;
  signal w_waddr_1 : STD_LOGIC;
  signal NLW_ram_reg_0_15_0_0_SPO_UNCONNECTED : STD_LOGIC;
  attribute RTL_RAM_BITS : integer;
  attribute RTL_RAM_BITS of ram_reg_0_15_0_0 : label is 16;
  attribute RTL_RAM_NAME : string;
  attribute RTL_RAM_NAME of ram_reg_0_15_0_0 : label is "U0/u_uz_interlockDeadtime2L_axi4_inst/u_uz_interlockDeadtime2L_axi4_module_inst/u_uz_interlockDeadtime2L_rdfifo_last_inst/u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit/ram";
  attribute RTL_RAM_TYPE : string;
  attribute RTL_RAM_TYPE of ram_reg_0_15_0_0 : label is "RAM_TDP";
  attribute XILINX_LEGACY_PRIM : string;
  attribute XILINX_LEGACY_PRIM of ram_reg_0_15_0_0 : label is "RAM16X1D";
  attribute ram_addr_begin : integer;
  attribute ram_addr_begin of ram_reg_0_15_0_0 : label is 0;
  attribute ram_addr_end : integer;
  attribute ram_addr_end of ram_reg_0_15_0_0 : label is 15;
  attribute ram_offset : integer;
  attribute ram_offset of ram_reg_0_15_0_0 : label is 0;
  attribute ram_slice_begin : integer;
  attribute ram_slice_begin of ram_reg_0_15_0_0 : label is 0;
  attribute ram_slice_end : integer;
  attribute ram_slice_end of ram_reg_0_15_0_0 : label is 0;
begin
  E(0) <= \^e\(0);
  w_out <= \^w_out\;
Out_rsvd_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AACFFFFFAAC00000"
    )
        port map (
      I0 => cache_data_reg_0,
      I1 => \^w_out\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => Out_rsvd_reg,
      I5 => AXI4_RLAST,
      O => cache_data_reg
    );
cache_data_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BAFFEFFF8A002000"
    )
        port map (
      I0 => \^w_out\,
      I1 => AXI4_RREADY,
      I2 => out_valid,
      I3 => fifo_valid,
      I4 => cache_valid,
      I5 => cache_data_reg_0,
      O => AXI4_RREADY_0
    );
data_int_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \p_1_out__1\,
      Q => w_waddr_1,
      R => '0'
    );
ram_reg_0_15_0_0: unisim.vcomponents.RAM32X1D
    generic map(
      INIT => X"00000000"
    )
        port map (
      A0 => data_int_reg_0(0),
      A1 => data_int_reg_0(1),
      A2 => data_int_reg_0(2),
      A3 => data_int_reg_0(3),
      A4 => '0',
      D => axi4_rlast_1,
      DPO => \p_1_out__1\,
      DPRA0 => data_int_reg_1(0),
      DPRA1 => data_int_reg_1(1),
      DPRA2 => data_int_reg_1(2),
      DPRA3 => data_int_reg_1(3),
      DPRA4 => '0',
      SPO => NLW_ram_reg_0_15_0_0_SPO_UNCONNECTED,
      WCLK => AXI4_ACLK,
      WE => \^e\(0)
    );
ram_reg_0_15_0_0_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFD00000000"
    )
        port map (
      I0 => Q(4),
      I1 => Q(2),
      I2 => Q(0),
      I3 => Q(1),
      I4 => Q(3),
      I5 => top_rd_enb,
      O => \^e\(0)
    );
w_d2_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => w_waddr_1,
      I1 => w_d2_reg,
      I2 => w_d2,
      O => \^w_out\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder is
  port (
    read_reg_ip_timestamp : out STD_LOGIC_VECTOR ( 0 to 0 );
    read_reg_axi_fb_InverseBotSwitch : out STD_LOGIC;
    read_reg_axi_fb_enable : out STD_LOGIC;
    data_reg_axi_enable_1_1_reg_0 : out STD_LOGIC;
    axi_EnableOutput : out STD_LOGIC;
    axi_InverseBotSwitch : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_6 : out STD_LOGIC;
    data_reg_axi_enable_1_1_reg_7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_8 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_9 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_10 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_11 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_axi_DelayCycles_1_1_reg[9]_0\ : out STD_LOGIC_VECTOR ( 9 downto 0 );
    \read_reg_axi_fb_DelayCycles_reg[9]_0\ : out STD_LOGIC_VECTOR ( 9 downto 0 );
    reset_x : in STD_LOGIC;
    AXI4_ACLK : in STD_LOGIC;
    Delay3_out1 : in STD_LOGIC;
    read_reg_axi_fb_enable_reg_0 : in STD_LOGIC;
    data_reg_axi_enable_1_1_reg_12 : in STD_LOGIC;
    data_reg_axi_EnableOutput_1_1_reg_0 : in STD_LOGIC;
    data_reg_axi_InverseBotSwitch_1_1_reg_0 : in STD_LOGIC;
    S0 : in STD_LOGIC;
    PipelineDelay1_out1 : in STD_LOGIC;
    PipelineDelay1_out1_0 : in STD_LOGIC;
    PipelineDelay1_out1_1 : in STD_LOGIC;
    PipelineDelay1_out1_2 : in STD_LOGIC;
    PipelineDelay1_out1_3 : in STD_LOGIC;
    PipelineDelay1_out1_4 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    \data_reg_axi_DelayCycles_1_1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \read_reg_axi_fb_DelayCycles_reg[9]_1\ : in STD_LOGIC_VECTOR ( 9 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder : entity is "uz_interlockDeadtime2L_addr_decoder";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder is
  signal \^data_reg_axi_enable_1_1_reg_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Delay2_delOut_i_1 : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_1__0\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_1__1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_1__2\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_1__3\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_1__4\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_2\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_2__0\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_2__1\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_2__2\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_2__3\ : label is "soft_lutpair5";
begin
  data_reg_axi_enable_1_1_reg_0 <= \^data_reg_axi_enable_1_1_reg_0\;
Delay2_delOut_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => reset_x,
      O => data_reg_axi_enable_1_1_reg_6
    );
\HDL_Counter_out1[9]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EC"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => reset_x,
      I2 => PipelineDelay1_out1,
      O => SR(0)
    );
\HDL_Counter_out1[9]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => PipelineDelay1_out1_0,
      I2 => reset_x,
      O => data_reg_axi_enable_1_1_reg_1(0)
    );
\HDL_Counter_out1[9]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => PipelineDelay1_out1_1,
      I2 => reset_x,
      O => data_reg_axi_enable_1_1_reg_2(0)
    );
\HDL_Counter_out1[9]_i_1__2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => PipelineDelay1_out1_2,
      I2 => reset_x,
      O => data_reg_axi_enable_1_1_reg_3(0)
    );
\HDL_Counter_out1[9]_i_1__3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => PipelineDelay1_out1_3,
      I2 => reset_x,
      O => data_reg_axi_enable_1_1_reg_4(0)
    );
\HDL_Counter_out1[9]_i_1__4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => PipelineDelay1_out1_4,
      I2 => reset_x,
      O => data_reg_axi_enable_1_1_reg_5(0)
    );
\HDL_Counter_out1[9]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => S0,
      I1 => \^data_reg_axi_enable_1_1_reg_0\,
      O => E(0)
    );
\HDL_Counter_out1[9]_i_2__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => S1,
      O => data_reg_axi_enable_1_1_reg_7(0)
    );
\HDL_Counter_out1[9]_i_2__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => S2,
      O => data_reg_axi_enable_1_1_reg_8(0)
    );
\HDL_Counter_out1[9]_i_2__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => S3,
      O => data_reg_axi_enable_1_1_reg_9(0)
    );
\HDL_Counter_out1[9]_i_2__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => S4,
      O => data_reg_axi_enable_1_1_reg_10(0)
    );
\HDL_Counter_out1[9]_i_2__4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^data_reg_axi_enable_1_1_reg_0\,
      I1 => S5,
      O => data_reg_axi_enable_1_1_reg_11(0)
    );
\data_reg_axi_DelayCycles_1_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(0),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(0),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(1),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(1),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(2),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(2),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(3),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(3),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(4),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(4),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(5),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(5),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(6),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(6),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(7),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(7),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(8),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(8),
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0),
      D => Q(9),
      Q => \data_reg_axi_DelayCycles_1_1_reg[9]_0\(9),
      R => reset_x
    );
data_reg_axi_EnableOutput_1_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => data_reg_axi_EnableOutput_1_1_reg_0,
      Q => axi_EnableOutput,
      R => reset_x
    );
data_reg_axi_InverseBotSwitch_1_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => data_reg_axi_InverseBotSwitch_1_1_reg_0,
      Q => axi_InverseBotSwitch,
      R => reset_x
    );
data_reg_axi_enable_1_1_reg: unisim.vcomponents.FDSE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => data_reg_axi_enable_1_1_reg_12,
      Q => \^data_reg_axi_enable_1_1_reg_0\,
      S => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(0),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(0),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(1),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(1),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(2),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(2),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(3),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(3),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(4),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(4),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(5),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(5),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(6),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(6),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(7),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(7),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(8),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(8),
      R => reset_x
    );
\read_reg_axi_fb_DelayCycles_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \read_reg_axi_fb_DelayCycles_reg[9]_1\(9),
      Q => \read_reg_axi_fb_DelayCycles_reg[9]_0\(9),
      R => reset_x
    );
read_reg_axi_fb_InverseBotSwitch_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Delay3_out1,
      Q => read_reg_axi_fb_InverseBotSwitch,
      R => reset_x
    );
read_reg_axi_fb_enable_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => read_reg_axi_fb_enable_reg_0,
      Q => read_reg_axi_fb_enable,
      R => reset_x
    );
\read_reg_ip_timestamp_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => '1',
      Q => read_reg_ip_timestamp(0),
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync is
  port (
    reset_x : out STD_LOGIC;
    reset_in : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    soft_reset : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync : entity is "uz_interlockDeadtime2L_reset_sync";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync is
  signal reset_out_i_1_n_0 : STD_LOGIC;
  signal reset_pipe : STD_LOGIC;
begin
reset_out_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFDF"
    )
        port map (
      I0 => AXI4_ARESETN,
      I1 => reset_pipe,
      I2 => IPCORE_RESETN,
      I3 => soft_reset,
      O => reset_out_i_1_n_0
    );
reset_out_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_out_i_1_n_0,
      Q => reset_x,
      R => '0'
    );
reset_pipe_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => '1',
      D => reset_in,
      Q => reset_pipe,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2 is
  port (
    Detect_Fall_Nonpositive2_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    S5 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2 : entity is "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2 is
  signal U_k_1 : STD_LOGIC;
  signal \U_k_1_i_1__4_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \PipelineDelay1_out1_i_1__4\ : label is "soft_lutpair116";
  attribute SOFT_HLUTNM of \U_k_1_i_1__4\ : label is "soft_lutpair116";
begin
\PipelineDelay1_out1_i_1__4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => U_k_1,
      I1 => S5,
      O => Detect_Fall_Nonpositive2_out1
    );
\U_k_1_i_1__4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S5,
      O => \U_k_1_i_1__4_n_0\
    );
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => \U_k_1_i_1__4_n_0\,
      Q => U_k_1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5 is
  port (
    Detect_Fall_Nonpositive2_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    S4 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5 : entity is "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5 is
  signal U_k_1 : STD_LOGIC;
  signal \U_k_1_i_1__3_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \PipelineDelay1_out1_i_1__3\ : label is "soft_lutpair110";
  attribute SOFT_HLUTNM of \U_k_1_i_1__3\ : label is "soft_lutpair110";
begin
\PipelineDelay1_out1_i_1__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => U_k_1,
      I1 => S4,
      O => Detect_Fall_Nonpositive2_out1
    );
\U_k_1_i_1__3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S4,
      O => \U_k_1_i_1__3_n_0\
    );
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => \U_k_1_i_1__3_n_0\,
      Q => U_k_1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6 is
  port (
    Detect_Fall_Nonpositive2_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    S3 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6 : entity is "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6 is
  signal U_k_1 : STD_LOGIC;
  signal \U_k_1_i_1__2_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \PipelineDelay1_out1_i_1__2\ : label is "soft_lutpair104";
  attribute SOFT_HLUTNM of \U_k_1_i_1__2\ : label is "soft_lutpair104";
begin
\PipelineDelay1_out1_i_1__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => U_k_1,
      I1 => S3,
      O => Detect_Fall_Nonpositive2_out1
    );
\U_k_1_i_1__2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S3,
      O => \U_k_1_i_1__2_n_0\
    );
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => \U_k_1_i_1__2_n_0\,
      Q => U_k_1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7 is
  port (
    Detect_Fall_Nonpositive2_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    S2 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7 : entity is "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7 is
  signal U_k_1 : STD_LOGIC;
  signal \U_k_1_i_1__1_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \PipelineDelay1_out1_i_1__1\ : label is "soft_lutpair98";
  attribute SOFT_HLUTNM of \U_k_1_i_1__1\ : label is "soft_lutpair98";
begin
\PipelineDelay1_out1_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => U_k_1,
      I1 => S2,
      O => Detect_Fall_Nonpositive2_out1
    );
\U_k_1_i_1__1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S2,
      O => \U_k_1_i_1__1_n_0\
    );
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => \U_k_1_i_1__1_n_0\,
      Q => U_k_1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8 is
  port (
    Detect_Fall_Nonpositive2_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    S1 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8 : entity is "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8 is
  signal U_k_1 : STD_LOGIC;
  signal \U_k_1_i_1__0_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \PipelineDelay1_out1_i_1__0\ : label is "soft_lutpair92";
  attribute SOFT_HLUTNM of \U_k_1_i_1__0\ : label is "soft_lutpair92";
begin
\PipelineDelay1_out1_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => U_k_1,
      I1 => S1,
      O => Detect_Fall_Nonpositive2_out1
    );
\U_k_1_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S1,
      O => \U_k_1_i_1__0_n_0\
    );
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => \U_k_1_i_1__0_n_0\,
      Q => U_k_1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9 is
  port (
    Detect_Fall_Nonpositive2_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    S0 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9 : entity is "uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9 is
  signal U_k_1 : STD_LOGIC;
  signal U_k_1_i_1_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of PipelineDelay1_out1_i_1 : label is "soft_lutpair86";
  attribute SOFT_HLUTNM of U_k_1_i_1 : label is "soft_lutpair86";
begin
PipelineDelay1_out1_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => U_k_1,
      I1 => S0,
      O => Detect_Fall_Nonpositive2_out1
    );
U_k_1_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => S0,
      O => U_k_1_i_1_n_0
    );
U_k_1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => U_k_1_i_1_n_0,
      Q => U_k_1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule is
  port (
    PipeDelay_out1 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    Delay3_out1 : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule : entity is "uz_interlockDeadtime2L_src_InverseBotSwitchModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule is
begin
PipeDelay_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Delay3_out1,
      Q => PipeDelay_out1,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data is
  port (
    out_valid_reg_0 : out STD_LOGIC;
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    axi4_rd_active_reg : out STD_LOGIC;
    axi4_rd_active_reg_0 : out STD_LOGIC;
    \axi4_raddr_reg[8]\ : out STD_LOGIC;
    \waddr_reg[15]\ : out STD_LOGIC;
    \waddr_reg[11]\ : out STD_LOGIC;
    D : out STD_LOGIC_VECTOR ( 1 downto 0 );
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    \FSM_onehot_axi4_rstate_reg[1]\ : out STD_LOGIC;
    axi4_rlast_1_reg : out STD_LOGIC;
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_ACLK : in STD_LOGIC;
    \data_int_reg[1]\ : in STD_LOGIC_VECTOR ( 9 downto 0 );
    Q : in STD_LOGIC_VECTOR ( 13 downto 0 );
    read_reg_axi_fb_enable : in STD_LOGIC;
    read_reg_axi_fb_InverseBotSwitch : in STD_LOGIC;
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_axi_DelayCycles_1_1_reg[9]\ : in STD_LOGIC_VECTOR ( 5 downto 0 );
    rd_active : in STD_LOGIC;
    data_reg_axi_enable_1_1_i_2 : in STD_LOGIC;
    data_reg_axi_enable_1_1_i_2_0 : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    top_rd_enb : in STD_LOGIC;
    \FSM_onehot_axi4_rstate_reg[0]\ : in STD_LOGIC_VECTOR ( 2 downto 0 );
    \FSM_onehot_axi4_rstate_reg[0]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_ARVALID : in STD_LOGIC;
    axi4_rlast_1 : in STD_LOGIC;
    axi4_rlast_1_reg_0 : in STD_LOGIC;
    axi4_rlast_1_reg_1 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data : entity is "uz_interlockDeadtime2L_rdfifo_data";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data is
  signal \FSM_onehot_axi4_rstate[2]_i_2_n_0\ : STD_LOGIC;
  signal Q_next : STD_LOGIC;
  signal Q_next_1 : STD_LOGIC;
  signal Q_next_2 : STD_LOGIC;
  signal \^sr\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal cache_data : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal cache_valid : STD_LOGIC;
  signal cache_wr_en : STD_LOGIC;
  signal data_int : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal data_out_next : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal fifo_back_indx0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal fifo_front_indx0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \fifo_front_indx[3]_i_3_n_0\ : STD_LOGIC;
  signal fifo_read_enable : STD_LOGIC;
  signal \fifo_sample_count[0]_i_1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[1]_i_1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_3_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_4_n_0\ : STD_LOGIC;
  signal fifo_sample_count_next : STD_LOGIC_VECTOR ( 4 downto 2 );
  signal \fifo_sample_count_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[3]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[4]\ : STD_LOGIC;
  signal fifo_valid : STD_LOGIC;
  signal \^out_valid_reg_0\ : STD_LOGIC;
  signal out_wr_en : STD_LOGIC;
  signal rd_addr : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal w_d1_i_1_n_0 : STD_LOGIC;
  signal w_d1_reg_n_0 : STD_LOGIC;
  signal w_d2 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal w_out : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal wr_addr : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal wr_en : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \FSM_onehot_axi4_rstate[2]_i_2\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of cache_valid_i_1 : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \fifo_back_indx[0]_i_1\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \fifo_back_indx[1]_i_1\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \fifo_back_indx[2]_i_1\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \fifo_back_indx[3]_i_1\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \fifo_front_indx[0]_i_1\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \fifo_front_indx[1]_i_1\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \fifo_front_indx[2]_i_1\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \fifo_front_indx[3]_i_2\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \fifo_sample_count[0]_i_1\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \fifo_sample_count[1]_i_1\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \fifo_sample_count[2]_i_1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \fifo_sample_count[3]_i_1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \fifo_sample_count[4]_i_3\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of out_valid_i_1 : label is "soft_lutpair45";
begin
  SR(0) <= \^sr\(0);
  out_valid_reg_0 <= \^out_valid_reg_0\;
\FSM_onehot_axi4_rstate[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F4F444F4F4F4F4F4"
    )
        port map (
      I0 => \FSM_onehot_axi4_rstate[2]_i_2_n_0\,
      I1 => \FSM_onehot_axi4_rstate_reg[0]\(2),
      I2 => \FSM_onehot_axi4_rstate_reg[0]\(0),
      I3 => \FSM_onehot_axi4_rstate_reg[0]_0\(0),
      I4 => AXI4_AWVALID,
      I5 => AXI4_ARVALID,
      O => D(0)
    );
\FSM_onehot_axi4_rstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => \FSM_onehot_axi4_rstate_reg[0]\(2),
      I1 => \FSM_onehot_axi4_rstate[2]_i_2_n_0\,
      I2 => axi4_rlast_1,
      I3 => \FSM_onehot_axi4_rstate_reg[0]\(1),
      O => D(1)
    );
\FSM_onehot_axi4_rstate[2]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EAAA"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count_reg_n_0_[3]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      O => \FSM_onehot_axi4_rstate[2]_i_2_n_0\
    );
\FSM_onehot_axi4_wstate[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => AXI4_ARESETN,
      O => \^sr\(0)
    );
\Out_tmp[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EE0E"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => \^out_valid_reg_0\,
      I3 => AXI4_RREADY,
      O => out_wr_en
    );
\Out_tmp_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(0),
      Q => AXI4_RDATA(0),
      R => \^sr\(0)
    );
\Out_tmp_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(10),
      Q => AXI4_RDATA(10),
      R => \^sr\(0)
    );
\Out_tmp_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(11),
      Q => AXI4_RDATA(11),
      R => \^sr\(0)
    );
\Out_tmp_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(12),
      Q => AXI4_RDATA(12),
      R => \^sr\(0)
    );
\Out_tmp_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(13),
      Q => AXI4_RDATA(13),
      R => \^sr\(0)
    );
\Out_tmp_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(14),
      Q => AXI4_RDATA(14),
      R => \^sr\(0)
    );
\Out_tmp_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(15),
      Q => AXI4_RDATA(15),
      R => \^sr\(0)
    );
\Out_tmp_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(16),
      Q => AXI4_RDATA(16),
      R => \^sr\(0)
    );
\Out_tmp_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(17),
      Q => AXI4_RDATA(17),
      R => \^sr\(0)
    );
\Out_tmp_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(18),
      Q => AXI4_RDATA(18),
      R => \^sr\(0)
    );
\Out_tmp_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(19),
      Q => AXI4_RDATA(19),
      R => \^sr\(0)
    );
\Out_tmp_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(1),
      Q => AXI4_RDATA(1),
      R => \^sr\(0)
    );
\Out_tmp_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(20),
      Q => AXI4_RDATA(20),
      R => \^sr\(0)
    );
\Out_tmp_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(21),
      Q => AXI4_RDATA(21),
      R => \^sr\(0)
    );
\Out_tmp_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(22),
      Q => AXI4_RDATA(22),
      R => \^sr\(0)
    );
\Out_tmp_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(23),
      Q => AXI4_RDATA(23),
      R => \^sr\(0)
    );
\Out_tmp_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(24),
      Q => AXI4_RDATA(24),
      R => \^sr\(0)
    );
\Out_tmp_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(25),
      Q => AXI4_RDATA(25),
      R => \^sr\(0)
    );
\Out_tmp_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(26),
      Q => AXI4_RDATA(26),
      R => \^sr\(0)
    );
\Out_tmp_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(27),
      Q => AXI4_RDATA(27),
      R => \^sr\(0)
    );
\Out_tmp_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(28),
      Q => AXI4_RDATA(28),
      R => \^sr\(0)
    );
\Out_tmp_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(29),
      Q => AXI4_RDATA(29),
      R => \^sr\(0)
    );
\Out_tmp_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(2),
      Q => AXI4_RDATA(2),
      R => \^sr\(0)
    );
\Out_tmp_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(30),
      Q => AXI4_RDATA(30),
      R => \^sr\(0)
    );
\Out_tmp_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(31),
      Q => AXI4_RDATA(31),
      R => \^sr\(0)
    );
\Out_tmp_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(3),
      Q => AXI4_RDATA(3),
      R => \^sr\(0)
    );
\Out_tmp_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(4),
      Q => AXI4_RDATA(4),
      R => \^sr\(0)
    );
\Out_tmp_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(5),
      Q => AXI4_RDATA(5),
      R => \^sr\(0)
    );
\Out_tmp_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(6),
      Q => AXI4_RDATA(6),
      R => \^sr\(0)
    );
\Out_tmp_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(7),
      Q => AXI4_RDATA(7),
      R => \^sr\(0)
    );
\Out_tmp_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(8),
      Q => AXI4_RDATA(8),
      R => \^sr\(0)
    );
\Out_tmp_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => data_out_next(9),
      Q => AXI4_RDATA(9),
      R => \^sr\(0)
    );
axi4_ar_transfer_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"101F1010"
    )
        port map (
      I0 => axi4_rlast_1,
      I1 => \FSM_onehot_axi4_rstate[2]_i_2_n_0\,
      I2 => \FSM_onehot_axi4_rstate_reg[0]\(1),
      I3 => \FSM_onehot_axi4_rstate_reg[0]\(0),
      I4 => top_rd_enb,
      O => axi4_rlast_1_reg
    );
axi4_rlast_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFCF00AA0020"
    )
        port map (
      I0 => \FSM_onehot_axi4_rstate_reg[0]\(1),
      I1 => axi4_rlast_1_reg_0,
      I2 => axi4_rlast_1_reg_1,
      I3 => \FSM_onehot_axi4_rstate[2]_i_2_n_0\,
      I4 => \FSM_onehot_axi4_rstate_reg[0]\(0),
      I5 => axi4_rlast_1,
      O => \FSM_onehot_axi4_rstate_reg[1]\
    );
\axi4_rlen[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF15550000"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count_reg_n_0_[3]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      I4 => \FSM_onehot_axi4_rstate_reg[0]\(1),
      I5 => \FSM_onehot_axi4_rstate_reg[0]\(0),
      O => E(0)
    );
\cache_data[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"B040"
    )
        port map (
      I0 => AXI4_RREADY,
      I1 => \^out_valid_reg_0\,
      I2 => fifo_valid,
      I3 => cache_valid,
      O => cache_wr_en
    );
\cache_data_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(0),
      Q => cache_data(0),
      R => \^sr\(0)
    );
\cache_data_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(10),
      Q => cache_data(10),
      R => \^sr\(0)
    );
\cache_data_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(11),
      Q => cache_data(11),
      R => \^sr\(0)
    );
\cache_data_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(12),
      Q => cache_data(12),
      R => \^sr\(0)
    );
\cache_data_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(13),
      Q => cache_data(13),
      R => \^sr\(0)
    );
\cache_data_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(14),
      Q => cache_data(14),
      R => \^sr\(0)
    );
\cache_data_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(15),
      Q => cache_data(15),
      R => \^sr\(0)
    );
\cache_data_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(16),
      Q => cache_data(16),
      R => \^sr\(0)
    );
\cache_data_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(17),
      Q => cache_data(17),
      R => \^sr\(0)
    );
\cache_data_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(18),
      Q => cache_data(18),
      R => \^sr\(0)
    );
\cache_data_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(19),
      Q => cache_data(19),
      R => \^sr\(0)
    );
\cache_data_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(1),
      Q => cache_data(1),
      R => \^sr\(0)
    );
\cache_data_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(20),
      Q => cache_data(20),
      R => \^sr\(0)
    );
\cache_data_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(21),
      Q => cache_data(21),
      R => \^sr\(0)
    );
\cache_data_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(22),
      Q => cache_data(22),
      R => \^sr\(0)
    );
\cache_data_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(23),
      Q => cache_data(23),
      R => \^sr\(0)
    );
\cache_data_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(24),
      Q => cache_data(24),
      R => \^sr\(0)
    );
\cache_data_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(25),
      Q => cache_data(25),
      R => \^sr\(0)
    );
\cache_data_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(26),
      Q => cache_data(26),
      R => \^sr\(0)
    );
\cache_data_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(27),
      Q => cache_data(27),
      R => \^sr\(0)
    );
\cache_data_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(28),
      Q => cache_data(28),
      R => \^sr\(0)
    );
\cache_data_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(29),
      Q => cache_data(29),
      R => \^sr\(0)
    );
\cache_data_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(2),
      Q => cache_data(2),
      R => \^sr\(0)
    );
\cache_data_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(30),
      Q => cache_data(30),
      R => \^sr\(0)
    );
\cache_data_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(31),
      Q => cache_data(31),
      R => \^sr\(0)
    );
\cache_data_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(3),
      Q => cache_data(3),
      R => \^sr\(0)
    );
\cache_data_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(4),
      Q => cache_data(4),
      R => \^sr\(0)
    );
\cache_data_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(5),
      Q => cache_data(5),
      R => \^sr\(0)
    );
\cache_data_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(6),
      Q => cache_data(6),
      R => \^sr\(0)
    );
\cache_data_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(7),
      Q => cache_data(7),
      R => \^sr\(0)
    );
\cache_data_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(8),
      Q => cache_data(8),
      R => \^sr\(0)
    );
\cache_data_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => w_out(9),
      Q => cache_data(9),
      R => \^sr\(0)
    );
cache_valid_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F440"
    )
        port map (
      I0 => AXI4_RREADY,
      I1 => \^out_valid_reg_0\,
      I2 => fifo_valid,
      I3 => cache_valid,
      O => Q_next
    );
cache_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next,
      Q => cache_valid,
      R => \^sr\(0)
    );
\fifo_back_indx[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => wr_addr(0),
      O => fifo_back_indx0(0)
    );
\fifo_back_indx[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => wr_addr(0),
      I1 => wr_addr(1),
      O => fifo_back_indx0(1)
    );
\fifo_back_indx[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => wr_addr(1),
      I1 => wr_addr(0),
      I2 => wr_addr(2),
      O => fifo_back_indx0(2)
    );
\fifo_back_indx[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => wr_addr(0),
      I1 => wr_addr(1),
      I2 => wr_addr(2),
      I3 => wr_addr(3),
      O => fifo_back_indx0(3)
    );
\fifo_back_indx_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => fifo_back_indx0(0),
      Q => wr_addr(0),
      R => \^sr\(0)
    );
\fifo_back_indx_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => fifo_back_indx0(1),
      Q => wr_addr(1),
      R => \^sr\(0)
    );
\fifo_back_indx_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => fifo_back_indx0(2),
      Q => wr_addr(2),
      R => \^sr\(0)
    );
\fifo_back_indx_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => fifo_back_indx0(3),
      Q => wr_addr(3),
      R => \^sr\(0)
    );
\fifo_front_indx[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => rd_addr(0),
      O => fifo_front_indx0(0)
    );
\fifo_front_indx[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => rd_addr(0),
      I1 => rd_addr(1),
      O => fifo_front_indx0(1)
    );
\fifo_front_indx[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => rd_addr(1),
      I1 => rd_addr(0),
      I2 => rd_addr(2),
      O => fifo_front_indx0(2)
    );
\fifo_front_indx[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFE00000000"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count_reg_n_0_[2]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      I3 => \fifo_sample_count_reg_n_0_[1]\,
      I4 => \fifo_sample_count_reg_n_0_[3]\,
      I5 => \fifo_front_indx[3]_i_3_n_0\,
      O => fifo_read_enable
    );
\fifo_front_indx[3]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => rd_addr(0),
      I1 => rd_addr(1),
      I2 => rd_addr(2),
      I3 => rd_addr(3),
      O => fifo_front_indx0(3)
    );
\fifo_front_indx[3]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => \^out_valid_reg_0\,
      O => \fifo_front_indx[3]_i_3_n_0\
    );
\fifo_front_indx_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => fifo_front_indx0(0),
      Q => rd_addr(0),
      R => \^sr\(0)
    );
\fifo_front_indx_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => fifo_front_indx0(1),
      Q => rd_addr(1),
      R => \^sr\(0)
    );
\fifo_front_indx_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => fifo_front_indx0(2),
      Q => rd_addr(2),
      R => \^sr\(0)
    );
\fifo_front_indx_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => fifo_front_indx0(3),
      Q => rd_addr(3),
      R => \^sr\(0)
    );
\fifo_sample_count[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[0]\,
      O => \fifo_sample_count[0]_i_1_n_0\
    );
\fifo_sample_count[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[1]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      O => \fifo_sample_count[1]_i_1_n_0\
    );
\fifo_sample_count[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"BD42"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[1]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      O => fifo_sample_count_next(2)
    );
\fifo_sample_count[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BFFD4002"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[1]\,
      I2 => \fifo_sample_count_reg_n_0_[2]\,
      I3 => \fifo_sample_count_reg_n_0_[0]\,
      I4 => \fifo_sample_count_reg_n_0_[3]\,
      O => fifo_sample_count_next(3)
    );
\fifo_sample_count[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8A76767676767676"
    )
        port map (
      I0 => top_rd_enb,
      I1 => \fifo_sample_count[4]_i_3_n_0\,
      I2 => \fifo_sample_count_reg_n_0_[4]\,
      I3 => fifo_valid,
      I4 => cache_valid,
      I5 => \^out_valid_reg_0\,
      O => \fifo_sample_count[4]_i_1_n_0\
    );
\fifo_sample_count[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BFFFFFFD40000002"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[2]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[3]\,
      I4 => \fifo_sample_count_reg_n_0_[0]\,
      I5 => \fifo_sample_count_reg_n_0_[4]\,
      O => fifo_sample_count_next(4)
    );
\fifo_sample_count[4]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[2]\,
      I1 => \fifo_sample_count_reg_n_0_[0]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[3]\,
      O => \fifo_sample_count[4]_i_3_n_0\
    );
\fifo_sample_count[4]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2EEEEEEEFFFFFFFF"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count[4]_i_3_n_0\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => \^out_valid_reg_0\,
      I5 => top_rd_enb,
      O => \fifo_sample_count[4]_i_4_n_0\
    );
\fifo_sample_count_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1_n_0\,
      D => \fifo_sample_count[0]_i_1_n_0\,
      Q => \fifo_sample_count_reg_n_0_[0]\,
      R => \^sr\(0)
    );
\fifo_sample_count_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1_n_0\,
      D => \fifo_sample_count[1]_i_1_n_0\,
      Q => \fifo_sample_count_reg_n_0_[1]\,
      R => \^sr\(0)
    );
\fifo_sample_count_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1_n_0\,
      D => fifo_sample_count_next(2),
      Q => \fifo_sample_count_reg_n_0_[2]\,
      R => \^sr\(0)
    );
\fifo_sample_count_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1_n_0\,
      D => fifo_sample_count_next(3),
      Q => \fifo_sample_count_reg_n_0_[3]\,
      R => \^sr\(0)
    );
\fifo_sample_count_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1_n_0\,
      D => fifo_sample_count_next(4),
      Q => \fifo_sample_count_reg_n_0_[4]\,
      R => \^sr\(0)
    );
fifo_valid_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0EEEEEEEFEEEEEEE"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_3_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[4]\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => \^out_valid_reg_0\,
      I5 => AXI4_RREADY,
      O => Q_next_1
    );
fifo_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next_1,
      Q => fifo_valid,
      R => \^sr\(0)
    );
out_valid_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EEFE"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => \^out_valid_reg_0\,
      I3 => AXI4_RREADY,
      O => Q_next_2
    );
out_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next_2,
      Q => \^out_valid_reg_0\,
      R => \^sr\(0)
    );
u_uz_interlockDeadtime2L_rdfifo_data_classic_ram_generic: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic
     port map (
      AXI4_ACLK => AXI4_ACLK,
      D(31 downto 0) => w_out(31 downto 0),
      E(0) => wr_en,
      \Out_tmp_reg[31]\(31 downto 0) => cache_data(31 downto 0),
      Q(13 downto 0) => Q(13 downto 0),
      \axi4_raddr_reg[8]\ => \axi4_raddr_reg[8]\,
      axi4_rd_active_reg => axi4_rd_active_reg,
      axi4_rd_active_reg_0 => axi4_rd_active_reg_0,
      \cache_data_reg[31]\ => w_d1_reg_n_0,
      \cache_data_reg[31]_0\(31 downto 0) => w_d2(31 downto 0),
      cache_valid => cache_valid,
      data_int(31 downto 0) => data_int(31 downto 0),
      \data_int_reg[1]_0\(9 downto 0) => \data_int_reg[1]\(9 downto 0),
      \data_int_reg[29]_0\(3 downto 0) => rd_addr(3 downto 0),
      \data_int_reg[29]_1\(3 downto 0) => wr_addr(3 downto 0),
      \data_reg_axi_DelayCycles_1_1_reg[9]\(5 downto 0) => \data_reg_axi_DelayCycles_1_1_reg[9]\(5 downto 0),
      data_reg_axi_enable_1_1_i_2 => data_reg_axi_enable_1_1_i_2,
      data_reg_axi_enable_1_1_i_2_0 => data_reg_axi_enable_1_1_i_2_0,
      \fifo_back_indx_reg[3]\(4) => \fifo_sample_count_reg_n_0_[4]\,
      \fifo_back_indx_reg[3]\(3) => \fifo_sample_count_reg_n_0_[3]\,
      \fifo_back_indx_reg[3]\(2) => \fifo_sample_count_reg_n_0_[2]\,
      \fifo_back_indx_reg[3]\(1) => \fifo_sample_count_reg_n_0_[1]\,
      \fifo_back_indx_reg[3]\(0) => \fifo_sample_count_reg_n_0_[0]\,
      rd_active => rd_active,
      read_reg_axi_fb_InverseBotSwitch => read_reg_axi_fb_InverseBotSwitch,
      read_reg_axi_fb_enable => read_reg_axi_fb_enable,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(0),
      top_rd_enb => top_rd_enb,
      w_d1_reg(31 downto 0) => data_out_next(31 downto 0),
      \waddr_reg[11]\ => \waddr_reg[11]\,
      \waddr_reg[15]\ => \waddr_reg[15]\
    );
w_d1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2AAA2AAA2AAA0000"
    )
        port map (
      I0 => AXI4_ARESETN,
      I1 => fifo_valid,
      I2 => cache_valid,
      I3 => \^out_valid_reg_0\,
      I4 => \fifo_sample_count_reg_n_0_[4]\,
      I5 => \fifo_sample_count[4]_i_3_n_0\,
      O => w_d1_i_1_n_0
    );
w_d1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => w_d1_i_1_n_0,
      Q => w_d1_reg_n_0,
      R => '0'
    );
\w_d2_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(0),
      Q => w_d2(0),
      R => \^sr\(0)
    );
\w_d2_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(10),
      Q => w_d2(10),
      R => \^sr\(0)
    );
\w_d2_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(11),
      Q => w_d2(11),
      R => \^sr\(0)
    );
\w_d2_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(12),
      Q => w_d2(12),
      R => \^sr\(0)
    );
\w_d2_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(13),
      Q => w_d2(13),
      R => \^sr\(0)
    );
\w_d2_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(14),
      Q => w_d2(14),
      R => \^sr\(0)
    );
\w_d2_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(15),
      Q => w_d2(15),
      R => \^sr\(0)
    );
\w_d2_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(16),
      Q => w_d2(16),
      R => \^sr\(0)
    );
\w_d2_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(17),
      Q => w_d2(17),
      R => \^sr\(0)
    );
\w_d2_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(18),
      Q => w_d2(18),
      R => \^sr\(0)
    );
\w_d2_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(19),
      Q => w_d2(19),
      R => \^sr\(0)
    );
\w_d2_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(1),
      Q => w_d2(1),
      R => \^sr\(0)
    );
\w_d2_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(20),
      Q => w_d2(20),
      R => \^sr\(0)
    );
\w_d2_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(21),
      Q => w_d2(21),
      R => \^sr\(0)
    );
\w_d2_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(22),
      Q => w_d2(22),
      R => \^sr\(0)
    );
\w_d2_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(23),
      Q => w_d2(23),
      R => \^sr\(0)
    );
\w_d2_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(24),
      Q => w_d2(24),
      R => \^sr\(0)
    );
\w_d2_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(25),
      Q => w_d2(25),
      R => \^sr\(0)
    );
\w_d2_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(26),
      Q => w_d2(26),
      R => \^sr\(0)
    );
\w_d2_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(27),
      Q => w_d2(27),
      R => \^sr\(0)
    );
\w_d2_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(28),
      Q => w_d2(28),
      R => \^sr\(0)
    );
\w_d2_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(29),
      Q => w_d2(29),
      R => \^sr\(0)
    );
\w_d2_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(2),
      Q => w_d2(2),
      R => \^sr\(0)
    );
\w_d2_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(30),
      Q => w_d2(30),
      R => \^sr\(0)
    );
\w_d2_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(31),
      Q => w_d2(31),
      R => \^sr\(0)
    );
\w_d2_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(3),
      Q => w_d2(3),
      R => \^sr\(0)
    );
\w_d2_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(4),
      Q => w_d2(4),
      R => \^sr\(0)
    );
\w_d2_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(5),
      Q => w_d2(5),
      R => \^sr\(0)
    );
\w_d2_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(6),
      Q => w_d2(6),
      R => \^sr\(0)
    );
\w_d2_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(7),
      Q => w_d2(7),
      R => \^sr\(0)
    );
\w_d2_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(8),
      Q => w_d2(8),
      R => \^sr\(0)
    );
\w_d2_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => data_int(9),
      Q => w_d2(9),
      R => \^sr\(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last is
  port (
    AXI4_RLAST : out STD_LOGIC;
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_ACLK : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    top_rd_enb : in STD_LOGIC;
    axi4_rlast_1 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last : entity is "uz_interlockDeadtime2L_rdfifo_last";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last is
  signal \^axi4_rlast\ : STD_LOGIC;
  signal Out_rsvd_i_2_n_0 : STD_LOGIC;
  signal Q_next : STD_LOGIC;
  signal Q_next_1 : STD_LOGIC;
  signal Q_next_2 : STD_LOGIC;
  signal cache_data_reg_n_0 : STD_LOGIC;
  signal cache_valid : STD_LOGIC;
  signal \fifo_back_indx0__1\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \fifo_back_indx_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_back_indx_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_back_indx_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_back_indx_reg_n_0_[3]\ : STD_LOGIC;
  signal \fifo_front_indx0__1\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \fifo_front_indx[3]_i_3__0_n_0\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[3]\ : STD_LOGIC;
  signal fifo_read_enable : STD_LOGIC;
  signal \fifo_sample_count[0]_i_1__1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[1]_i_1__1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_1__1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_3__1_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_4__1_n_0\ : STD_LOGIC;
  signal fifo_sample_count_next : STD_LOGIC_VECTOR ( 4 downto 2 );
  signal \fifo_sample_count_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[3]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[4]\ : STD_LOGIC;
  signal fifo_valid : STD_LOGIC;
  signal out_valid : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_1 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_3 : STD_LOGIC;
  signal \w_d1_i_1__1_n_0\ : STD_LOGIC;
  signal w_d1_reg_n_0 : STD_LOGIC;
  signal w_d2 : STD_LOGIC;
  signal w_out : STD_LOGIC;
  signal wr_en : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Out_rsvd_i_2 : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \cache_valid_i_1__1\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \fifo_back_indx[0]_i_1__1\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \fifo_back_indx[1]_i_1__1\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \fifo_back_indx[2]_i_1__1\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \fifo_back_indx[3]_i_1__1\ : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \fifo_front_indx[0]_i_1__1\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \fifo_front_indx[1]_i_1__1\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \fifo_front_indx[2]_i_1__1\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \fifo_front_indx[3]_i_2__1\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \fifo_front_indx[3]_i_3__0\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \fifo_sample_count[1]_i_1__1\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \fifo_sample_count[2]_i_1__1\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \fifo_sample_count[3]_i_1__1\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \fifo_sample_count[4]_i_3__1\ : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \out_valid_i_1__1\ : label is "soft_lutpair53";
begin
  AXI4_RLAST <= \^axi4_rlast\;
Out_rsvd_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => AXI4_RREADY,
      I1 => out_valid,
      O => Out_rsvd_i_2_n_0
    );
Out_rsvd_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_3,
      Q => \^axi4_rlast\,
      R => SR(0)
    );
cache_data_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_1,
      Q => cache_data_reg_n_0,
      R => SR(0)
    );
\cache_valid_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F440"
    )
        port map (
      I0 => AXI4_RREADY,
      I1 => out_valid,
      I2 => fifo_valid,
      I3 => cache_valid,
      O => Q_next
    );
cache_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next,
      Q => cache_valid,
      R => SR(0)
    );
\fifo_back_indx[0]_i_1__1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[0]\,
      O => \fifo_back_indx0__1\(0)
    );
\fifo_back_indx[1]_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[0]\,
      I1 => \fifo_back_indx_reg_n_0_[1]\,
      O => \fifo_back_indx0__1\(1)
    );
\fifo_back_indx[2]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[1]\,
      I1 => \fifo_back_indx_reg_n_0_[0]\,
      I2 => \fifo_back_indx_reg_n_0_[2]\,
      O => \fifo_back_indx0__1\(2)
    );
\fifo_back_indx[3]_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[0]\,
      I1 => \fifo_back_indx_reg_n_0_[1]\,
      I2 => \fifo_back_indx_reg_n_0_[2]\,
      I3 => \fifo_back_indx_reg_n_0_[3]\,
      O => \fifo_back_indx0__1\(3)
    );
\fifo_back_indx_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__1\(0),
      Q => \fifo_back_indx_reg_n_0_[0]\,
      R => SR(0)
    );
\fifo_back_indx_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__1\(1),
      Q => \fifo_back_indx_reg_n_0_[1]\,
      R => SR(0)
    );
\fifo_back_indx_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__1\(2),
      Q => \fifo_back_indx_reg_n_0_[2]\,
      R => SR(0)
    );
\fifo_back_indx_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__1\(3),
      Q => \fifo_back_indx_reg_n_0_[3]\,
      R => SR(0)
    );
\fifo_front_indx[0]_i_1__1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[0]\,
      O => \fifo_front_indx0__1\(0)
    );
\fifo_front_indx[1]_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[0]\,
      I1 => \fifo_front_indx_reg_n_0_[1]\,
      O => \fifo_front_indx0__1\(1)
    );
\fifo_front_indx[2]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[1]\,
      I1 => \fifo_front_indx_reg_n_0_[0]\,
      I2 => \fifo_front_indx_reg_n_0_[2]\,
      O => \fifo_front_indx0__1\(2)
    );
\fifo_front_indx[3]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFE00000000"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count_reg_n_0_[2]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      I3 => \fifo_sample_count_reg_n_0_[1]\,
      I4 => \fifo_sample_count_reg_n_0_[3]\,
      I5 => \fifo_front_indx[3]_i_3__0_n_0\,
      O => fifo_read_enable
    );
\fifo_front_indx[3]_i_2__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[0]\,
      I1 => \fifo_front_indx_reg_n_0_[1]\,
      I2 => \fifo_front_indx_reg_n_0_[2]\,
      I3 => \fifo_front_indx_reg_n_0_[3]\,
      O => \fifo_front_indx0__1\(3)
    );
\fifo_front_indx[3]_i_3__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => out_valid,
      O => \fifo_front_indx[3]_i_3__0_n_0\
    );
\fifo_front_indx_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__1\(0),
      Q => \fifo_front_indx_reg_n_0_[0]\,
      R => SR(0)
    );
\fifo_front_indx_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__1\(1),
      Q => \fifo_front_indx_reg_n_0_[1]\,
      R => SR(0)
    );
\fifo_front_indx_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__1\(2),
      Q => \fifo_front_indx_reg_n_0_[2]\,
      R => SR(0)
    );
\fifo_front_indx_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__1\(3),
      Q => \fifo_front_indx_reg_n_0_[3]\,
      R => SR(0)
    );
\fifo_sample_count[0]_i_1__1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[0]\,
      O => \fifo_sample_count[0]_i_1__1_n_0\
    );
\fifo_sample_count[1]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__1_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[1]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      O => \fifo_sample_count[1]_i_1__1_n_0\
    );
\fifo_sample_count[2]_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"BD42"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__1_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[1]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      O => fifo_sample_count_next(2)
    );
\fifo_sample_count[3]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BFFD4002"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__1_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[0]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      I4 => \fifo_sample_count_reg_n_0_[3]\,
      O => fifo_sample_count_next(3)
    );
\fifo_sample_count[4]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8A76767676767676"
    )
        port map (
      I0 => top_rd_enb,
      I1 => \fifo_sample_count[4]_i_3__1_n_0\,
      I2 => \fifo_sample_count_reg_n_0_[4]\,
      I3 => fifo_valid,
      I4 => cache_valid,
      I5 => out_valid,
      O => \fifo_sample_count[4]_i_1__1_n_0\
    );
\fifo_sample_count[4]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BFFFFFFD40000002"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__1_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[2]\,
      I2 => \fifo_sample_count_reg_n_0_[3]\,
      I3 => \fifo_sample_count_reg_n_0_[0]\,
      I4 => \fifo_sample_count_reg_n_0_[1]\,
      I5 => \fifo_sample_count_reg_n_0_[4]\,
      O => fifo_sample_count_next(4)
    );
\fifo_sample_count[4]_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[2]\,
      I1 => \fifo_sample_count_reg_n_0_[0]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[3]\,
      O => \fifo_sample_count[4]_i_3__1_n_0\
    );
\fifo_sample_count[4]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2EEEEEEEFFFFFFFF"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count[4]_i_3__1_n_0\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => out_valid,
      I5 => top_rd_enb,
      O => \fifo_sample_count[4]_i_4__1_n_0\
    );
\fifo_sample_count_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__1_n_0\,
      D => \fifo_sample_count[0]_i_1__1_n_0\,
      Q => \fifo_sample_count_reg_n_0_[0]\,
      R => SR(0)
    );
\fifo_sample_count_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__1_n_0\,
      D => \fifo_sample_count[1]_i_1__1_n_0\,
      Q => \fifo_sample_count_reg_n_0_[1]\,
      R => SR(0)
    );
\fifo_sample_count_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__1_n_0\,
      D => fifo_sample_count_next(2),
      Q => \fifo_sample_count_reg_n_0_[2]\,
      R => SR(0)
    );
\fifo_sample_count_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__1_n_0\,
      D => fifo_sample_count_next(3),
      Q => \fifo_sample_count_reg_n_0_[3]\,
      R => SR(0)
    );
\fifo_sample_count_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__1_n_0\,
      D => fifo_sample_count_next(4),
      Q => \fifo_sample_count_reg_n_0_[4]\,
      R => SR(0)
    );
\fifo_valid_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0EEEEEEEFEEEEEEE"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_3__1_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[4]\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => out_valid,
      I5 => AXI4_RREADY,
      O => Q_next_1
    );
fifo_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next_1,
      Q => fifo_valid,
      R => SR(0)
    );
\out_valid_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EEFE"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => out_valid,
      I3 => AXI4_RREADY,
      O => Q_next_2
    );
out_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next_2,
      Q => out_valid,
      R => SR(0)
    );
u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_singlebit
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_RLAST => \^axi4_rlast\,
      AXI4_RREADY => AXI4_RREADY,
      AXI4_RREADY_0 => u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_1,
      E(0) => wr_en,
      Out_rsvd_reg => Out_rsvd_i_2_n_0,
      Q(4) => \fifo_sample_count_reg_n_0_[4]\,
      Q(3) => \fifo_sample_count_reg_n_0_[3]\,
      Q(2) => \fifo_sample_count_reg_n_0_[2]\,
      Q(1) => \fifo_sample_count_reg_n_0_[1]\,
      Q(0) => \fifo_sample_count_reg_n_0_[0]\,
      axi4_rlast_1 => axi4_rlast_1,
      cache_data_reg => u_uz_interlockDeadtime2L_rdfifo_last_classic_ram_singlebit_n_3,
      cache_data_reg_0 => cache_data_reg_n_0,
      cache_valid => cache_valid,
      data_int_reg_0(3) => \fifo_back_indx_reg_n_0_[3]\,
      data_int_reg_0(2) => \fifo_back_indx_reg_n_0_[2]\,
      data_int_reg_0(1) => \fifo_back_indx_reg_n_0_[1]\,
      data_int_reg_0(0) => \fifo_back_indx_reg_n_0_[0]\,
      data_int_reg_1(3) => \fifo_front_indx_reg_n_0_[3]\,
      data_int_reg_1(2) => \fifo_front_indx_reg_n_0_[2]\,
      data_int_reg_1(1) => \fifo_front_indx_reg_n_0_[1]\,
      data_int_reg_1(0) => \fifo_front_indx_reg_n_0_[0]\,
      fifo_valid => fifo_valid,
      out_valid => out_valid,
      top_rd_enb => top_rd_enb,
      w_d2 => w_d2,
      w_d2_reg => w_d1_reg_n_0,
      w_out => w_out
    );
\w_d1_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2AAA2AAA2AAA0000"
    )
        port map (
      I0 => AXI4_ARESETN,
      I1 => fifo_valid,
      I2 => cache_valid,
      I3 => out_valid,
      I4 => \fifo_sample_count_reg_n_0_[4]\,
      I5 => \fifo_sample_count[4]_i_3__1_n_0\,
      O => \w_d1_i_1__1_n_0\
    );
w_d1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \w_d1_i_1__1_n_0\,
      Q => w_d1_reg_n_0,
      R => '0'
    );
w_d2_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => w_out,
      Q => w_d2,
      R => SR(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid is
  port (
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_ACLK : in STD_LOGIC;
    top_rd_enb : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 11 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid : entity is "uz_interlockDeadtime2L_rdfifo_rid";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid is
  signal Q_next : STD_LOGIC;
  signal Q_next_1 : STD_LOGIC;
  signal Q_next_2 : STD_LOGIC;
  signal \cache_data_reg_n_0_[0]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[10]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[11]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[1]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[2]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[3]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[4]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[5]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[6]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[7]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[8]\ : STD_LOGIC;
  signal \cache_data_reg_n_0_[9]\ : STD_LOGIC;
  signal cache_valid : STD_LOGIC;
  signal cache_wr_en : STD_LOGIC;
  signal \fifo_back_indx0__0\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \fifo_back_indx_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_back_indx_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_back_indx_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_back_indx_reg_n_0_[3]\ : STD_LOGIC;
  signal \fifo_front_indx0__0\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \fifo_front_indx_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_front_indx_reg_n_0_[3]\ : STD_LOGIC;
  signal fifo_read_enable : STD_LOGIC;
  signal \fifo_sample_count[0]_i_1__0_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[1]_i_1__0_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[1]_i_2_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_1__0_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_3__0_n_0\ : STD_LOGIC;
  signal \fifo_sample_count[4]_i_4__0_n_0\ : STD_LOGIC;
  signal fifo_sample_count_next : STD_LOGIC_VECTOR ( 4 downto 2 );
  signal \fifo_sample_count_reg_n_0_[0]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[1]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[2]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[3]\ : STD_LOGIC;
  signal \fifo_sample_count_reg_n_0_[4]\ : STD_LOGIC;
  signal fifo_valid : STD_LOGIC;
  signal out_valid : STD_LOGIC;
  signal out_wr_en : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_1 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_10 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_11 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_12 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_13 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_14 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_15 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_16 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_17 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_18 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_19 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_2 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_20 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_21 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_22 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_23 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_24 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_25 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_26 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_27 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_28 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_29 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_3 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_30 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_31 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_32 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_33 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_34 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_35 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_36 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_4 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_5 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_6 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_7 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_8 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_9 : STD_LOGIC;
  signal \w_d1_i_1__0_n_0\ : STD_LOGIC;
  signal w_d1_reg_n_0 : STD_LOGIC;
  signal \w_d2_reg_n_0_[0]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[10]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[11]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[1]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[2]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[3]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[4]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[5]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[6]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[7]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[8]\ : STD_LOGIC;
  signal \w_d2_reg_n_0_[9]\ : STD_LOGIC;
  signal wr_en : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \cache_valid_i_1__0\ : label is "soft_lutpair73";
  attribute SOFT_HLUTNM of \fifo_back_indx[0]_i_1__0\ : label is "soft_lutpair77";
  attribute SOFT_HLUTNM of \fifo_back_indx[1]_i_1__0\ : label is "soft_lutpair77";
  attribute SOFT_HLUTNM of \fifo_back_indx[2]_i_1__0\ : label is "soft_lutpair75";
  attribute SOFT_HLUTNM of \fifo_back_indx[3]_i_1__0\ : label is "soft_lutpair75";
  attribute SOFT_HLUTNM of \fifo_front_indx[0]_i_1__0\ : label is "soft_lutpair78";
  attribute SOFT_HLUTNM of \fifo_front_indx[1]_i_1__0\ : label is "soft_lutpair78";
  attribute SOFT_HLUTNM of \fifo_front_indx[2]_i_1__0\ : label is "soft_lutpair76";
  attribute SOFT_HLUTNM of \fifo_front_indx[3]_i_2__0\ : label is "soft_lutpair76";
  attribute SOFT_HLUTNM of \fifo_sample_count[0]_i_1__0\ : label is "soft_lutpair74";
  attribute SOFT_HLUTNM of \fifo_sample_count[2]_i_1__0\ : label is "soft_lutpair72";
  attribute SOFT_HLUTNM of \fifo_sample_count[3]_i_1__0\ : label is "soft_lutpair72";
  attribute SOFT_HLUTNM of \fifo_sample_count[4]_i_3__0\ : label is "soft_lutpair74";
  attribute SOFT_HLUTNM of \out_valid_i_1__0\ : label is "soft_lutpair73";
begin
\Out_tmp[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EE0E"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => out_valid,
      I3 => AXI4_RREADY,
      O => out_wr_en
    );
\Out_tmp_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_36,
      Q => AXI4_RID(0),
      R => SR(0)
    );
\Out_tmp_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_26,
      Q => AXI4_RID(10),
      R => SR(0)
    );
\Out_tmp_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_25,
      Q => AXI4_RID(11),
      R => SR(0)
    );
\Out_tmp_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_35,
      Q => AXI4_RID(1),
      R => SR(0)
    );
\Out_tmp_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_34,
      Q => AXI4_RID(2),
      R => SR(0)
    );
\Out_tmp_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_33,
      Q => AXI4_RID(3),
      R => SR(0)
    );
\Out_tmp_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_32,
      Q => AXI4_RID(4),
      R => SR(0)
    );
\Out_tmp_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_31,
      Q => AXI4_RID(5),
      R => SR(0)
    );
\Out_tmp_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_30,
      Q => AXI4_RID(6),
      R => SR(0)
    );
\Out_tmp_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_29,
      Q => AXI4_RID(7),
      R => SR(0)
    );
\Out_tmp_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_28,
      Q => AXI4_RID(8),
      R => SR(0)
    );
\Out_tmp_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => out_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_27,
      Q => AXI4_RID(9),
      R => SR(0)
    );
\cache_data[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"B040"
    )
        port map (
      I0 => AXI4_RREADY,
      I1 => out_valid,
      I2 => fifo_valid,
      I3 => cache_valid,
      O => cache_wr_en
    );
\cache_data_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_12,
      Q => \cache_data_reg_n_0_[0]\,
      R => SR(0)
    );
\cache_data_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_2,
      Q => \cache_data_reg_n_0_[10]\,
      R => SR(0)
    );
\cache_data_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_1,
      Q => \cache_data_reg_n_0_[11]\,
      R => SR(0)
    );
\cache_data_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_11,
      Q => \cache_data_reg_n_0_[1]\,
      R => SR(0)
    );
\cache_data_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_10,
      Q => \cache_data_reg_n_0_[2]\,
      R => SR(0)
    );
\cache_data_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_9,
      Q => \cache_data_reg_n_0_[3]\,
      R => SR(0)
    );
\cache_data_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_8,
      Q => \cache_data_reg_n_0_[4]\,
      R => SR(0)
    );
\cache_data_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_7,
      Q => \cache_data_reg_n_0_[5]\,
      R => SR(0)
    );
\cache_data_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_6,
      Q => \cache_data_reg_n_0_[6]\,
      R => SR(0)
    );
\cache_data_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_5,
      Q => \cache_data_reg_n_0_[7]\,
      R => SR(0)
    );
\cache_data_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_4,
      Q => \cache_data_reg_n_0_[8]\,
      R => SR(0)
    );
\cache_data_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => cache_wr_en,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_3,
      Q => \cache_data_reg_n_0_[9]\,
      R => SR(0)
    );
\cache_valid_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F440"
    )
        port map (
      I0 => AXI4_RREADY,
      I1 => out_valid,
      I2 => fifo_valid,
      I3 => cache_valid,
      O => Q_next
    );
cache_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next,
      Q => cache_valid,
      R => SR(0)
    );
\fifo_back_indx[0]_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[0]\,
      O => \fifo_back_indx0__0\(0)
    );
\fifo_back_indx[1]_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[0]\,
      I1 => \fifo_back_indx_reg_n_0_[1]\,
      O => \fifo_back_indx0__0\(1)
    );
\fifo_back_indx[2]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[1]\,
      I1 => \fifo_back_indx_reg_n_0_[0]\,
      I2 => \fifo_back_indx_reg_n_0_[2]\,
      O => \fifo_back_indx0__0\(2)
    );
\fifo_back_indx[3]_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => \fifo_back_indx_reg_n_0_[0]\,
      I1 => \fifo_back_indx_reg_n_0_[1]\,
      I2 => \fifo_back_indx_reg_n_0_[2]\,
      I3 => \fifo_back_indx_reg_n_0_[3]\,
      O => \fifo_back_indx0__0\(3)
    );
\fifo_back_indx_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__0\(0),
      Q => \fifo_back_indx_reg_n_0_[0]\,
      R => SR(0)
    );
\fifo_back_indx_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__0\(1),
      Q => \fifo_back_indx_reg_n_0_[1]\,
      R => SR(0)
    );
\fifo_back_indx_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__0\(2),
      Q => \fifo_back_indx_reg_n_0_[2]\,
      R => SR(0)
    );
\fifo_back_indx_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => wr_en,
      D => \fifo_back_indx0__0\(3),
      Q => \fifo_back_indx_reg_n_0_[3]\,
      R => SR(0)
    );
\fifo_front_indx[0]_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[0]\,
      O => \fifo_front_indx0__0\(0)
    );
\fifo_front_indx[1]_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[0]\,
      I1 => \fifo_front_indx_reg_n_0_[1]\,
      O => \fifo_front_indx0__0\(1)
    );
\fifo_front_indx[2]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[1]\,
      I1 => \fifo_front_indx_reg_n_0_[0]\,
      I2 => \fifo_front_indx_reg_n_0_[2]\,
      O => \fifo_front_indx0__0\(2)
    );
\fifo_front_indx[3]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFE00000000"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count_reg_n_0_[2]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      I3 => \fifo_sample_count_reg_n_0_[1]\,
      I4 => \fifo_sample_count_reg_n_0_[3]\,
      I5 => \fifo_sample_count[1]_i_2_n_0\,
      O => fifo_read_enable
    );
\fifo_front_indx[3]_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => \fifo_front_indx_reg_n_0_[0]\,
      I1 => \fifo_front_indx_reg_n_0_[1]\,
      I2 => \fifo_front_indx_reg_n_0_[2]\,
      I3 => \fifo_front_indx_reg_n_0_[3]\,
      O => \fifo_front_indx0__0\(3)
    );
\fifo_front_indx_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__0\(0),
      Q => \fifo_front_indx_reg_n_0_[0]\,
      R => SR(0)
    );
\fifo_front_indx_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__0\(1),
      Q => \fifo_front_indx_reg_n_0_[1]\,
      R => SR(0)
    );
\fifo_front_indx_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__0\(2),
      Q => \fifo_front_indx_reg_n_0_[2]\,
      R => SR(0)
    );
\fifo_front_indx_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => fifo_read_enable,
      D => \fifo_front_indx0__0\(3),
      Q => \fifo_front_indx_reg_n_0_[3]\,
      R => SR(0)
    );
\fifo_sample_count[0]_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[0]\,
      O => \fifo_sample_count[0]_i_1__0_n_0\
    );
\fifo_sample_count[1]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"DFD5202A202ADFD5"
    )
        port map (
      I0 => top_rd_enb,
      I1 => \fifo_sample_count[1]_i_2_n_0\,
      I2 => \fifo_sample_count[4]_i_3__0_n_0\,
      I3 => \fifo_sample_count_reg_n_0_[4]\,
      I4 => \fifo_sample_count_reg_n_0_[1]\,
      I5 => \fifo_sample_count_reg_n_0_[0]\,
      O => \fifo_sample_count[1]_i_1__0_n_0\
    );
\fifo_sample_count[1]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => out_valid,
      O => \fifo_sample_count[1]_i_2_n_0\
    );
\fifo_sample_count[2]_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"BD42"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__0_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[1]\,
      I2 => \fifo_sample_count_reg_n_0_[0]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      O => fifo_sample_count_next(2)
    );
\fifo_sample_count[3]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BFFD4002"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__0_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[0]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[2]\,
      I4 => \fifo_sample_count_reg_n_0_[3]\,
      O => fifo_sample_count_next(3)
    );
\fifo_sample_count[4]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"807F807F7F7FFF00"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => out_valid,
      I3 => top_rd_enb,
      I4 => \fifo_sample_count_reg_n_0_[4]\,
      I5 => \fifo_sample_count[4]_i_3__0_n_0\,
      O => \fifo_sample_count[4]_i_1__0_n_0\
    );
\fifo_sample_count[4]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BFFFFFFD40000002"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_4__0_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[2]\,
      I2 => \fifo_sample_count_reg_n_0_[3]\,
      I3 => \fifo_sample_count_reg_n_0_[0]\,
      I4 => \fifo_sample_count_reg_n_0_[1]\,
      I5 => \fifo_sample_count_reg_n_0_[4]\,
      O => fifo_sample_count_next(4)
    );
\fifo_sample_count[4]_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[2]\,
      I1 => \fifo_sample_count_reg_n_0_[0]\,
      I2 => \fifo_sample_count_reg_n_0_[1]\,
      I3 => \fifo_sample_count_reg_n_0_[3]\,
      O => \fifo_sample_count[4]_i_3__0_n_0\
    );
\fifo_sample_count[4]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2EEEEEEEFFFFFFFF"
    )
        port map (
      I0 => \fifo_sample_count_reg_n_0_[4]\,
      I1 => \fifo_sample_count[4]_i_3__0_n_0\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => out_valid,
      I5 => top_rd_enb,
      O => \fifo_sample_count[4]_i_4__0_n_0\
    );
\fifo_sample_count_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__0_n_0\,
      D => \fifo_sample_count[0]_i_1__0_n_0\,
      Q => \fifo_sample_count_reg_n_0_[0]\,
      R => SR(0)
    );
\fifo_sample_count_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__0_n_0\,
      D => \fifo_sample_count[1]_i_1__0_n_0\,
      Q => \fifo_sample_count_reg_n_0_[1]\,
      R => SR(0)
    );
\fifo_sample_count_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__0_n_0\,
      D => fifo_sample_count_next(2),
      Q => \fifo_sample_count_reg_n_0_[2]\,
      R => SR(0)
    );
\fifo_sample_count_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__0_n_0\,
      D => fifo_sample_count_next(3),
      Q => \fifo_sample_count_reg_n_0_[3]\,
      R => SR(0)
    );
\fifo_sample_count_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \fifo_sample_count[4]_i_1__0_n_0\,
      D => fifo_sample_count_next(4),
      Q => \fifo_sample_count_reg_n_0_[4]\,
      R => SR(0)
    );
\fifo_valid_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0EEEEEEEFEEEEEEE"
    )
        port map (
      I0 => \fifo_sample_count[4]_i_3__0_n_0\,
      I1 => \fifo_sample_count_reg_n_0_[4]\,
      I2 => fifo_valid,
      I3 => cache_valid,
      I4 => out_valid,
      I5 => AXI4_RREADY,
      O => Q_next_1
    );
fifo_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next_1,
      Q => fifo_valid,
      R => SR(0)
    );
\out_valid_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EEFE"
    )
        port map (
      I0 => fifo_valid,
      I1 => cache_valid,
      I2 => out_valid,
      I3 => AXI4_RREADY,
      O => Q_next_2
    );
out_valid_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => Q_next_2,
      Q => out_valid,
      R => SR(0)
    );
u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram: entity work.\zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_SimpleDualPortRAM_generic__parameterized1\
     port map (
      AXI4_ACLK => AXI4_ACLK,
      D(11) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_1,
      D(10) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_2,
      D(9) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_3,
      D(8) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_4,
      D(7) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_5,
      D(6) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_6,
      D(5) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_7,
      D(4) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_8,
      D(3) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_9,
      D(2) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_10,
      D(1) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_11,
      D(0) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_12,
      E(0) => wr_en,
      \Out_tmp_reg[11]\(11) => \cache_data_reg_n_0_[11]\,
      \Out_tmp_reg[11]\(10) => \cache_data_reg_n_0_[10]\,
      \Out_tmp_reg[11]\(9) => \cache_data_reg_n_0_[9]\,
      \Out_tmp_reg[11]\(8) => \cache_data_reg_n_0_[8]\,
      \Out_tmp_reg[11]\(7) => \cache_data_reg_n_0_[7]\,
      \Out_tmp_reg[11]\(6) => \cache_data_reg_n_0_[6]\,
      \Out_tmp_reg[11]\(5) => \cache_data_reg_n_0_[5]\,
      \Out_tmp_reg[11]\(4) => \cache_data_reg_n_0_[4]\,
      \Out_tmp_reg[11]\(3) => \cache_data_reg_n_0_[3]\,
      \Out_tmp_reg[11]\(2) => \cache_data_reg_n_0_[2]\,
      \Out_tmp_reg[11]\(1) => \cache_data_reg_n_0_[1]\,
      \Out_tmp_reg[11]\(0) => \cache_data_reg_n_0_[0]\,
      Q(4) => \fifo_sample_count_reg_n_0_[4]\,
      Q(3) => \fifo_sample_count_reg_n_0_[3]\,
      Q(2) => \fifo_sample_count_reg_n_0_[2]\,
      Q(1) => \fifo_sample_count_reg_n_0_[1]\,
      Q(0) => \fifo_sample_count_reg_n_0_[0]\,
      \cache_data_reg[11]\ => w_d1_reg_n_0,
      \cache_data_reg[11]_0\(11) => \w_d2_reg_n_0_[11]\,
      \cache_data_reg[11]_0\(10) => \w_d2_reg_n_0_[10]\,
      \cache_data_reg[11]_0\(9) => \w_d2_reg_n_0_[9]\,
      \cache_data_reg[11]_0\(8) => \w_d2_reg_n_0_[8]\,
      \cache_data_reg[11]_0\(7) => \w_d2_reg_n_0_[7]\,
      \cache_data_reg[11]_0\(6) => \w_d2_reg_n_0_[6]\,
      \cache_data_reg[11]_0\(5) => \w_d2_reg_n_0_[5]\,
      \cache_data_reg[11]_0\(4) => \w_d2_reg_n_0_[4]\,
      \cache_data_reg[11]_0\(3) => \w_d2_reg_n_0_[3]\,
      \cache_data_reg[11]_0\(2) => \w_d2_reg_n_0_[2]\,
      \cache_data_reg[11]_0\(1) => \w_d2_reg_n_0_[1]\,
      \cache_data_reg[11]_0\(0) => \w_d2_reg_n_0_[0]\,
      cache_valid => cache_valid,
      data_int(11) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_13,
      data_int(10) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_14,
      data_int(9) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_15,
      data_int(8) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_16,
      data_int(7) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_17,
      data_int(6) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_18,
      data_int(5) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_19,
      data_int(4) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_20,
      data_int(3) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_21,
      data_int(2) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_22,
      data_int(1) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_23,
      data_int(0) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_24,
      \data_int_reg[1]_0\(11 downto 0) => Q(11 downto 0),
      \data_int_reg[1]_1\(3) => \fifo_front_indx_reg_n_0_[3]\,
      \data_int_reg[1]_1\(2) => \fifo_front_indx_reg_n_0_[2]\,
      \data_int_reg[1]_1\(1) => \fifo_front_indx_reg_n_0_[1]\,
      \data_int_reg[1]_1\(0) => \fifo_front_indx_reg_n_0_[0]\,
      \data_int_reg[1]_2\(3) => \fifo_back_indx_reg_n_0_[3]\,
      \data_int_reg[1]_2\(2) => \fifo_back_indx_reg_n_0_[2]\,
      \data_int_reg[1]_2\(1) => \fifo_back_indx_reg_n_0_[1]\,
      \data_int_reg[1]_2\(0) => \fifo_back_indx_reg_n_0_[0]\,
      top_rd_enb => top_rd_enb,
      w_d1_reg(11) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_25,
      w_d1_reg(10) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_26,
      w_d1_reg(9) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_27,
      w_d1_reg(8) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_28,
      w_d1_reg(7) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_29,
      w_d1_reg(6) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_30,
      w_d1_reg(5) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_31,
      w_d1_reg(4) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_32,
      w_d1_reg(3) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_33,
      w_d1_reg(2) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_34,
      w_d1_reg(1) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_35,
      w_d1_reg(0) => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_36
    );
\w_d1_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2AAA2AAA2AAA0000"
    )
        port map (
      I0 => AXI4_ARESETN,
      I1 => fifo_valid,
      I2 => cache_valid,
      I3 => out_valid,
      I4 => \fifo_sample_count_reg_n_0_[4]\,
      I5 => \fifo_sample_count[4]_i_3__0_n_0\,
      O => \w_d1_i_1__0_n_0\
    );
w_d1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \w_d1_i_1__0_n_0\,
      Q => w_d1_reg_n_0,
      R => '0'
    );
\w_d2_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_24,
      Q => \w_d2_reg_n_0_[0]\,
      R => SR(0)
    );
\w_d2_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_14,
      Q => \w_d2_reg_n_0_[10]\,
      R => SR(0)
    );
\w_d2_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_13,
      Q => \w_d2_reg_n_0_[11]\,
      R => SR(0)
    );
\w_d2_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_23,
      Q => \w_d2_reg_n_0_[1]\,
      R => SR(0)
    );
\w_d2_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_22,
      Q => \w_d2_reg_n_0_[2]\,
      R => SR(0)
    );
\w_d2_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_21,
      Q => \w_d2_reg_n_0_[3]\,
      R => SR(0)
    );
\w_d2_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_20,
      Q => \w_d2_reg_n_0_[4]\,
      R => SR(0)
    );
\w_d2_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_19,
      Q => \w_d2_reg_n_0_[5]\,
      R => SR(0)
    );
\w_d2_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_18,
      Q => \w_d2_reg_n_0_[6]\,
      R => SR(0)
    );
\w_d2_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_17,
      Q => \w_d2_reg_n_0_[7]\,
      R => SR(0)
    );
\w_d2_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_16,
      Q => \w_d2_reg_n_0_[8]\,
      R => SR(0)
    );
\w_d2_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => w_d1_reg_n_0,
      D => u_uz_interlockDeadtime2L_rdfifo_rid_classic_ram_n_15,
      Q => \w_d2_reg_n_0_[9]\,
      R => SR(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule is
  port (
    PipelineDelay1_out1 : out STD_LOGIC;
    s0_out : out STD_LOGIC;
    PipelineDelay1_out1_reg_0 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Delay2_delOut_reg_0 : in STD_LOGIC;
    S0 : in STD_LOGIC;
    s0_out_0 : in STD_LOGIC;
    s0_out_1 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule : entity is "uz_interlockDeadtime2L_src_DeadtimeModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule is
  signal Delay2_delOut : STD_LOGIC;
  signal Delay2_delOut2_out : STD_LOGIC;
  signal Detect_Fall_Nonpositive2_out1 : STD_LOGIC;
  signal \HDL_Counter_out1[6]_i_1__2_n_0\ : STD_LOGIC;
  signal \HDL_Counter_out1[9]_i_4_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^pipelinedelay1_out1\ : STD_LOGIC;
  signal \^pipelinedelay1_out1_reg_0\ : STD_LOGIC;
  signal p_0_in : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal s0_out_INST_0_i_3_n_0 : STD_LOGIC;
  signal s0_out_INST_0_i_5_n_0 : STD_LOGIC;
  signal s0_out_INST_0_i_6_n_0 : STD_LOGIC;
  signal s0_out_INST_0_i_7_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Delay2_delOut_i_2 : label is "soft_lutpair87";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1\ : label is "soft_lutpair90";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1\ : label is "soft_lutpair90";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1\ : label is "soft_lutpair88";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1\ : label is "soft_lutpair88";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1__2\ : label is "soft_lutpair91";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1\ : label is "soft_lutpair91";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[8]_i_1\ : label is "soft_lutpair89";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_3\ : label is "soft_lutpair89";
  attribute SOFT_HLUTNM of s0_out_INST_0_i_1 : label is "soft_lutpair87";
begin
  PipelineDelay1_out1 <= \^pipelinedelay1_out1\;
  PipelineDelay1_out1_reg_0 <= \^pipelinedelay1_out1_reg_0\;
Delay2_delOut_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00220030"
    )
        port map (
      I0 => S0,
      I1 => reset_x,
      I2 => Delay2_delOut,
      I3 => \^pipelinedelay1_out1\,
      I4 => s0_out_INST_0_i_3_n_0,
      O => Delay2_delOut2_out
    );
Delay2_delOut_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => Delay2_delOut_reg_0,
      D => Delay2_delOut2_out,
      Q => Delay2_delOut,
      R => '0'
    );
\HDL_Counter_out1[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => p_0_in(0)
    );
\HDL_Counter_out1[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => p_0_in(1)
    );
\HDL_Counter_out1[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      O => p_0_in(2)
    );
\HDL_Counter_out1[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      O => p_0_in(3)
    );
\HDL_Counter_out1[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      O => p_0_in(4)
    );
\HDL_Counter_out1[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6AAAAAAAAAAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(5),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(1),
      I3 => HDL_Counter_out1_reg(0),
      I4 => HDL_Counter_out1_reg(2),
      I5 => HDL_Counter_out1_reg(4),
      O => p_0_in(5)
    );
\HDL_Counter_out1[6]_i_1__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[9]_i_4_n_0\,
      O => \HDL_Counter_out1[6]_i_1__2_n_0\
    );
\HDL_Counter_out1[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"9A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => \HDL_Counter_out1[9]_i_4_n_0\,
      I2 => HDL_Counter_out1_reg(6),
      O => p_0_in(7)
    );
\HDL_Counter_out1[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"A6AA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(8),
      I1 => HDL_Counter_out1_reg(6),
      I2 => \HDL_Counter_out1[9]_i_4_n_0\,
      I3 => HDL_Counter_out1_reg(7),
      O => p_0_in(8)
    );
\HDL_Counter_out1[9]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A6AAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(9),
      I1 => HDL_Counter_out1_reg(7),
      I2 => \HDL_Counter_out1[9]_i_4_n_0\,
      I3 => HDL_Counter_out1_reg(6),
      I4 => HDL_Counter_out1_reg(8),
      O => p_0_in(9)
    );
\HDL_Counter_out1[9]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFFFFFFFFFF"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      I5 => HDL_Counter_out1_reg(5),
      O => \HDL_Counter_out1[9]_i_4_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(0),
      Q => HDL_Counter_out1_reg(0),
      R => SR(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(1),
      Q => HDL_Counter_out1_reg(1),
      R => SR(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(2),
      Q => HDL_Counter_out1_reg(2),
      R => SR(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(3),
      Q => HDL_Counter_out1_reg(3),
      R => SR(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(4),
      Q => HDL_Counter_out1_reg(4),
      R => SR(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(5),
      Q => HDL_Counter_out1_reg(5),
      R => SR(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => \HDL_Counter_out1[6]_i_1__2_n_0\,
      Q => HDL_Counter_out1_reg(6),
      R => SR(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(7),
      Q => HDL_Counter_out1_reg(7),
      R => SR(0)
    );
\HDL_Counter_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(8),
      Q => HDL_Counter_out1_reg(8),
      R => SR(0)
    );
\HDL_Counter_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => E(0),
      D => p_0_in(9),
      Q => HDL_Counter_out1_reg(9),
      R => SR(0)
    );
PipelineDelay1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Detect_Fall_Nonpositive2_out1,
      Q => \^pipelinedelay1_out1\,
      R => reset_x
    );
s0_out_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"08000808"
    )
        port map (
      I0 => s0_out_0,
      I1 => S0,
      I2 => \^pipelinedelay1_out1_reg_0\,
      I3 => s0_out_1,
      I4 => S1,
      O => s0_out
    );
s0_out_INST_0_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"45"
    )
        port map (
      I0 => s0_out_INST_0_i_3_n_0,
      I1 => \^pipelinedelay1_out1\,
      I2 => Delay2_delOut,
      O => \^pipelinedelay1_out1_reg_0\
    );
s0_out_INST_0_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04000004"
    )
        port map (
      I0 => s0_out_INST_0_i_5_n_0,
      I1 => s0_out_INST_0_i_6_n_0,
      I2 => s0_out_INST_0_i_7_n_0,
      I3 => HDL_Counter_out1_reg(9),
      I4 => Q(9),
      O => s0_out_INST_0_i_3_n_0
    );
s0_out_INST_0_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(3),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(5),
      I3 => Q(5),
      I4 => HDL_Counter_out1_reg(4),
      I5 => Q(4),
      O => s0_out_INST_0_i_5_n_0
    );
s0_out_INST_0_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => Q(6),
      I1 => HDL_Counter_out1_reg(6),
      I2 => HDL_Counter_out1_reg(8),
      I3 => Q(8),
      I4 => HDL_Counter_out1_reg(7),
      I5 => Q(7),
      O => s0_out_INST_0_i_6_n_0
    );
s0_out_INST_0_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(0),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => Q(1),
      I4 => HDL_Counter_out1_reg(2),
      I5 => Q(2),
      O => s0_out_INST_0_i_7_n_0
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_9
     port map (
      Detect_Fall_Nonpositive2_out1 => Detect_Fall_Nonpositive2_out1,
      IPCORE_CLK => IPCORE_CLK,
      S0 => S0,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0 is
  port (
    PipelineDelay1_out1_0 : out STD_LOGIC;
    s1_out : out STD_LOGIC;
    PipelineDelay1_out1_reg_0 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Delay2_delOut_reg_0 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    s1_out_0 : in STD_LOGIC;
    s1_out_1 : in STD_LOGIC;
    S0 : in STD_LOGIC;
    PipeDelay_out1 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0 : entity is "uz_interlockDeadtime2L_src_DeadtimeModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0 is
  signal Delay2_delOut : STD_LOGIC;
  signal Delay2_delOut2_out : STD_LOGIC;
  signal Detect_Fall_Nonpositive2_out1 : STD_LOGIC;
  signal \HDL_Counter_out1[6]_i_1__3_n_0\ : STD_LOGIC;
  signal \HDL_Counter_out1[9]_i_4__0_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^pipelinedelay1_out1_0\ : STD_LOGIC;
  signal \^pipelinedelay1_out1_reg_0\ : STD_LOGIC;
  signal \p_0_in__0\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal s0_out_INST_0_i_10_n_0 : STD_LOGIC;
  signal s0_out_INST_0_i_4_n_0 : STD_LOGIC;
  signal s0_out_INST_0_i_8_n_0 : STD_LOGIC;
  signal s0_out_INST_0_i_9_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Delay2_delOut_i_1__0\ : label is "soft_lutpair93";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1__0\ : label is "soft_lutpair96";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1__0\ : label is "soft_lutpair96";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1__0\ : label is "soft_lutpair94";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1__0\ : label is "soft_lutpair94";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1__3\ : label is "soft_lutpair97";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1__0\ : label is "soft_lutpair97";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[8]_i_1__0\ : label is "soft_lutpair95";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_3__0\ : label is "soft_lutpair95";
  attribute SOFT_HLUTNM of s0_out_INST_0_i_2 : label is "soft_lutpair93";
begin
  PipelineDelay1_out1_0 <= \^pipelinedelay1_out1_0\;
  PipelineDelay1_out1_reg_0 <= \^pipelinedelay1_out1_reg_0\;
\Delay2_delOut_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00220030"
    )
        port map (
      I0 => S1,
      I1 => reset_x,
      I2 => Delay2_delOut,
      I3 => \^pipelinedelay1_out1_0\,
      I4 => s0_out_INST_0_i_4_n_0,
      O => Delay2_delOut2_out
    );
Delay2_delOut_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => Delay2_delOut_reg_0,
      D => Delay2_delOut2_out,
      Q => Delay2_delOut,
      R => '0'
    );
\HDL_Counter_out1[0]_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => \p_0_in__0\(0)
    );
\HDL_Counter_out1[1]_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => \p_0_in__0\(1)
    );
\HDL_Counter_out1[2]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      O => \p_0_in__0\(2)
    );
\HDL_Counter_out1[3]_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      O => \p_0_in__0\(3)
    );
\HDL_Counter_out1[4]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      O => \p_0_in__0\(4)
    );
\HDL_Counter_out1[5]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6AAAAAAAAAAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(5),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(1),
      I3 => HDL_Counter_out1_reg(0),
      I4 => HDL_Counter_out1_reg(2),
      I5 => HDL_Counter_out1_reg(4),
      O => \p_0_in__0\(5)
    );
\HDL_Counter_out1[6]_i_1__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[9]_i_4__0_n_0\,
      O => \HDL_Counter_out1[6]_i_1__3_n_0\
    );
\HDL_Counter_out1[7]_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"9A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => \HDL_Counter_out1[9]_i_4__0_n_0\,
      I2 => HDL_Counter_out1_reg(6),
      O => \p_0_in__0\(7)
    );
\HDL_Counter_out1[8]_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"A6AA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(8),
      I1 => HDL_Counter_out1_reg(6),
      I2 => \HDL_Counter_out1[9]_i_4__0_n_0\,
      I3 => HDL_Counter_out1_reg(7),
      O => \p_0_in__0\(8)
    );
\HDL_Counter_out1[9]_i_3__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A6AAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(9),
      I1 => HDL_Counter_out1_reg(7),
      I2 => \HDL_Counter_out1[9]_i_4__0_n_0\,
      I3 => HDL_Counter_out1_reg(6),
      I4 => HDL_Counter_out1_reg(8),
      O => \p_0_in__0\(9)
    );
\HDL_Counter_out1[9]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFFFFFFFFFF"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      I5 => HDL_Counter_out1_reg(5),
      O => \HDL_Counter_out1[9]_i_4__0_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(0),
      Q => HDL_Counter_out1_reg(0),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(1),
      Q => HDL_Counter_out1_reg(1),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(2),
      Q => HDL_Counter_out1_reg(2),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(3),
      Q => HDL_Counter_out1_reg(3),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(4),
      Q => HDL_Counter_out1_reg(4),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(5),
      Q => HDL_Counter_out1_reg(5),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \HDL_Counter_out1[6]_i_1__3_n_0\,
      Q => HDL_Counter_out1_reg(6),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(7),
      Q => HDL_Counter_out1_reg(7),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(8),
      Q => HDL_Counter_out1_reg(8),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__0\(9),
      Q => HDL_Counter_out1_reg(9),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
PipelineDelay1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Detect_Fall_Nonpositive2_out1,
      Q => \^pipelinedelay1_out1_0\,
      R => reset_x
    );
s0_out_INST_0_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(0),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => Q(1),
      I4 => HDL_Counter_out1_reg(2),
      I5 => Q(2),
      O => s0_out_INST_0_i_10_n_0
    );
s0_out_INST_0_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"45"
    )
        port map (
      I0 => s0_out_INST_0_i_4_n_0,
      I1 => \^pipelinedelay1_out1_0\,
      I2 => Delay2_delOut,
      O => \^pipelinedelay1_out1_reg_0\
    );
s0_out_INST_0_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04000004"
    )
        port map (
      I0 => s0_out_INST_0_i_8_n_0,
      I1 => s0_out_INST_0_i_9_n_0,
      I2 => s0_out_INST_0_i_10_n_0,
      I3 => HDL_Counter_out1_reg(9),
      I4 => Q(9),
      O => s0_out_INST_0_i_4_n_0
    );
s0_out_INST_0_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(3),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(4),
      I3 => Q(4),
      I4 => HDL_Counter_out1_reg(5),
      I5 => Q(5),
      O => s0_out_INST_0_i_8_n_0
    );
s0_out_INST_0_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => Q(6),
      I1 => HDL_Counter_out1_reg(6),
      I2 => HDL_Counter_out1_reg(8),
      I3 => Q(8),
      I4 => HDL_Counter_out1_reg(7),
      I5 => Q(7),
      O => s0_out_INST_0_i_9_n_0
    );
s1_out_INST_0: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8AAA8A8A20002020"
    )
        port map (
      I0 => s1_out_0,
      I1 => \^pipelinedelay1_out1_reg_0\,
      I2 => S1,
      I3 => s1_out_1,
      I4 => S0,
      I5 => PipeDelay_out1,
      O => s1_out
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_8
     port map (
      Detect_Fall_Nonpositive2_out1 => Detect_Fall_Nonpositive2_out1,
      IPCORE_CLK => IPCORE_CLK,
      S1 => S1,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1 is
  port (
    PipelineDelay1_out1_1 : out STD_LOGIC;
    s2_out : out STD_LOGIC;
    PipelineDelay1_out1_reg_0 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Delay2_delOut_reg_0 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    s2_out_0 : in STD_LOGIC;
    s2_out_1 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1 : entity is "uz_interlockDeadtime2L_src_DeadtimeModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1 is
  signal Delay2_delOut : STD_LOGIC;
  signal Delay2_delOut2_out : STD_LOGIC;
  signal Detect_Fall_Nonpositive2_out1 : STD_LOGIC;
  signal \HDL_Counter_out1[9]_i_4__1_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^pipelinedelay1_out1_1\ : STD_LOGIC;
  signal \^pipelinedelay1_out1_reg_0\ : STD_LOGIC;
  signal \p_0_in__1\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal s2_out_INST_0_i_3_n_0 : STD_LOGIC;
  signal s2_out_INST_0_i_5_n_0 : STD_LOGIC;
  signal s2_out_INST_0_i_6_n_0 : STD_LOGIC;
  signal s2_out_INST_0_i_7_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Delay2_delOut_i_1__1\ : label is "soft_lutpair99";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1__1\ : label is "soft_lutpair102";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1__1\ : label is "soft_lutpair102";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1__1\ : label is "soft_lutpair100";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1__1\ : label is "soft_lutpair100";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1\ : label is "soft_lutpair103";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1__1\ : label is "soft_lutpair103";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[8]_i_1__1\ : label is "soft_lutpair101";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_3__1\ : label is "soft_lutpair101";
  attribute SOFT_HLUTNM of s2_out_INST_0_i_1 : label is "soft_lutpair99";
begin
  PipelineDelay1_out1_1 <= \^pipelinedelay1_out1_1\;
  PipelineDelay1_out1_reg_0 <= \^pipelinedelay1_out1_reg_0\;
\Delay2_delOut_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00220030"
    )
        port map (
      I0 => S2,
      I1 => reset_x,
      I2 => Delay2_delOut,
      I3 => \^pipelinedelay1_out1_1\,
      I4 => s2_out_INST_0_i_3_n_0,
      O => Delay2_delOut2_out
    );
Delay2_delOut_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => Delay2_delOut_reg_0,
      D => Delay2_delOut2_out,
      Q => Delay2_delOut,
      R => '0'
    );
\HDL_Counter_out1[0]_i_1__1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => \p_0_in__1\(0)
    );
\HDL_Counter_out1[1]_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => \p_0_in__1\(1)
    );
\HDL_Counter_out1[2]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      O => \p_0_in__1\(2)
    );
\HDL_Counter_out1[3]_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      O => \p_0_in__1\(3)
    );
\HDL_Counter_out1[4]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      O => \p_0_in__1\(4)
    );
\HDL_Counter_out1[5]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFF80000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      I4 => HDL_Counter_out1_reg(4),
      I5 => HDL_Counter_out1_reg(5),
      O => \p_0_in__1\(5)
    );
\HDL_Counter_out1[6]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[9]_i_4__1_n_0\,
      O => \p_0_in__1\(6)
    );
\HDL_Counter_out1[7]_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => \HDL_Counter_out1[9]_i_4__1_n_0\,
      I2 => HDL_Counter_out1_reg(6),
      O => \p_0_in__1\(7)
    );
\HDL_Counter_out1[8]_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(8),
      I1 => HDL_Counter_out1_reg(6),
      I2 => \HDL_Counter_out1[9]_i_4__1_n_0\,
      I3 => HDL_Counter_out1_reg(7),
      O => \p_0_in__1\(8)
    );
\HDL_Counter_out1[9]_i_3__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(9),
      I1 => HDL_Counter_out1_reg(7),
      I2 => \HDL_Counter_out1[9]_i_4__1_n_0\,
      I3 => HDL_Counter_out1_reg(6),
      I4 => HDL_Counter_out1_reg(8),
      O => \p_0_in__1\(9)
    );
\HDL_Counter_out1[9]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(5),
      I1 => HDL_Counter_out1_reg(4),
      I2 => HDL_Counter_out1_reg(2),
      I3 => HDL_Counter_out1_reg(0),
      I4 => HDL_Counter_out1_reg(1),
      I5 => HDL_Counter_out1_reg(3),
      O => \HDL_Counter_out1[9]_i_4__1_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(0),
      Q => HDL_Counter_out1_reg(0),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(1),
      Q => HDL_Counter_out1_reg(1),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(2),
      Q => HDL_Counter_out1_reg(2),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(3),
      Q => HDL_Counter_out1_reg(3),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(4),
      Q => HDL_Counter_out1_reg(4),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(5),
      Q => HDL_Counter_out1_reg(5),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(6),
      Q => HDL_Counter_out1_reg(6),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(7),
      Q => HDL_Counter_out1_reg(7),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(8),
      Q => HDL_Counter_out1_reg(8),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__1\(9),
      Q => HDL_Counter_out1_reg(9),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
PipelineDelay1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Detect_Fall_Nonpositive2_out1,
      Q => \^pipelinedelay1_out1_1\,
      R => reset_x
    );
s2_out_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"08000808"
    )
        port map (
      I0 => s2_out_0,
      I1 => S2,
      I2 => \^pipelinedelay1_out1_reg_0\,
      I3 => s2_out_1,
      I4 => S3,
      O => s2_out
    );
s2_out_INST_0_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"45"
    )
        port map (
      I0 => s2_out_INST_0_i_3_n_0,
      I1 => \^pipelinedelay1_out1_1\,
      I2 => Delay2_delOut,
      O => \^pipelinedelay1_out1_reg_0\
    );
s2_out_INST_0_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04000004"
    )
        port map (
      I0 => s2_out_INST_0_i_5_n_0,
      I1 => s2_out_INST_0_i_6_n_0,
      I2 => s2_out_INST_0_i_7_n_0,
      I3 => HDL_Counter_out1_reg(9),
      I4 => Q(9),
      O => s2_out_INST_0_i_3_n_0
    );
s2_out_INST_0_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(3),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(4),
      I3 => Q(4),
      I4 => HDL_Counter_out1_reg(5),
      I5 => Q(5),
      O => s2_out_INST_0_i_5_n_0
    );
s2_out_INST_0_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => Q(7),
      I2 => HDL_Counter_out1_reg(8),
      I3 => Q(8),
      I4 => Q(6),
      I5 => HDL_Counter_out1_reg(6),
      O => s2_out_INST_0_i_6_n_0
    );
s2_out_INST_0_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(0),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => Q(1),
      I4 => HDL_Counter_out1_reg(2),
      I5 => Q(2),
      O => s2_out_INST_0_i_7_n_0
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_7
     port map (
      Detect_Fall_Nonpositive2_out1 => Detect_Fall_Nonpositive2_out1,
      IPCORE_CLK => IPCORE_CLK,
      S2 => S2,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2 is
  port (
    PipelineDelay1_out1_2 : out STD_LOGIC;
    s3_out : out STD_LOGIC;
    PipelineDelay1_out1_reg_0 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Delay2_delOut_reg_0 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    s3_out_0 : in STD_LOGIC;
    s3_out_1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    PipeDelay_out1 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2 : entity is "uz_interlockDeadtime2L_src_DeadtimeModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2 is
  signal Delay2_delOut : STD_LOGIC;
  signal Delay2_delOut2_out : STD_LOGIC;
  signal Detect_Fall_Nonpositive2_out1 : STD_LOGIC;
  signal \HDL_Counter_out1[9]_i_4__2_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^pipelinedelay1_out1_2\ : STD_LOGIC;
  signal \^pipelinedelay1_out1_reg_0\ : STD_LOGIC;
  signal \p_0_in__2\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal s2_out_INST_0_i_10_n_0 : STD_LOGIC;
  signal s2_out_INST_0_i_4_n_0 : STD_LOGIC;
  signal s2_out_INST_0_i_8_n_0 : STD_LOGIC;
  signal s2_out_INST_0_i_9_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Delay2_delOut_i_1__2\ : label is "soft_lutpair105";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1__2\ : label is "soft_lutpair108";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1__2\ : label is "soft_lutpair108";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1__2\ : label is "soft_lutpair106";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1__2\ : label is "soft_lutpair106";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1__0\ : label is "soft_lutpair109";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1__2\ : label is "soft_lutpair109";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[8]_i_1__2\ : label is "soft_lutpair107";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_3__2\ : label is "soft_lutpair107";
  attribute SOFT_HLUTNM of s2_out_INST_0_i_2 : label is "soft_lutpair105";
begin
  PipelineDelay1_out1_2 <= \^pipelinedelay1_out1_2\;
  PipelineDelay1_out1_reg_0 <= \^pipelinedelay1_out1_reg_0\;
\Delay2_delOut_i_1__2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00220030"
    )
        port map (
      I0 => S3,
      I1 => reset_x,
      I2 => Delay2_delOut,
      I3 => \^pipelinedelay1_out1_2\,
      I4 => s2_out_INST_0_i_4_n_0,
      O => Delay2_delOut2_out
    );
Delay2_delOut_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => Delay2_delOut_reg_0,
      D => Delay2_delOut2_out,
      Q => Delay2_delOut,
      R => '0'
    );
\HDL_Counter_out1[0]_i_1__2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => \p_0_in__2\(0)
    );
\HDL_Counter_out1[1]_i_1__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => \p_0_in__2\(1)
    );
\HDL_Counter_out1[2]_i_1__2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      O => \p_0_in__2\(2)
    );
\HDL_Counter_out1[3]_i_1__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      O => \p_0_in__2\(3)
    );
\HDL_Counter_out1[4]_i_1__2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      O => \p_0_in__2\(4)
    );
\HDL_Counter_out1[5]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFF80000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      I4 => HDL_Counter_out1_reg(4),
      I5 => HDL_Counter_out1_reg(5),
      O => \p_0_in__2\(5)
    );
\HDL_Counter_out1[6]_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[9]_i_4__2_n_0\,
      O => \p_0_in__2\(6)
    );
\HDL_Counter_out1[7]_i_1__2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => \HDL_Counter_out1[9]_i_4__2_n_0\,
      I2 => HDL_Counter_out1_reg(6),
      O => \p_0_in__2\(7)
    );
\HDL_Counter_out1[8]_i_1__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(8),
      I1 => HDL_Counter_out1_reg(6),
      I2 => \HDL_Counter_out1[9]_i_4__2_n_0\,
      I3 => HDL_Counter_out1_reg(7),
      O => \p_0_in__2\(8)
    );
\HDL_Counter_out1[9]_i_3__2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(9),
      I1 => HDL_Counter_out1_reg(7),
      I2 => \HDL_Counter_out1[9]_i_4__2_n_0\,
      I3 => HDL_Counter_out1_reg(6),
      I4 => HDL_Counter_out1_reg(8),
      O => \p_0_in__2\(9)
    );
\HDL_Counter_out1[9]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(5),
      I1 => HDL_Counter_out1_reg(4),
      I2 => HDL_Counter_out1_reg(2),
      I3 => HDL_Counter_out1_reg(0),
      I4 => HDL_Counter_out1_reg(1),
      I5 => HDL_Counter_out1_reg(3),
      O => \HDL_Counter_out1[9]_i_4__2_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(0),
      Q => HDL_Counter_out1_reg(0),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(1),
      Q => HDL_Counter_out1_reg(1),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(2),
      Q => HDL_Counter_out1_reg(2),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(3),
      Q => HDL_Counter_out1_reg(3),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(4),
      Q => HDL_Counter_out1_reg(4),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(5),
      Q => HDL_Counter_out1_reg(5),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(6),
      Q => HDL_Counter_out1_reg(6),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(7),
      Q => HDL_Counter_out1_reg(7),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(8),
      Q => HDL_Counter_out1_reg(8),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__2\(9),
      Q => HDL_Counter_out1_reg(9),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
PipelineDelay1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Detect_Fall_Nonpositive2_out1,
      Q => \^pipelinedelay1_out1_2\,
      R => reset_x
    );
s2_out_INST_0_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(0),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => Q(1),
      I4 => HDL_Counter_out1_reg(2),
      I5 => Q(2),
      O => s2_out_INST_0_i_10_n_0
    );
s2_out_INST_0_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"45"
    )
        port map (
      I0 => s2_out_INST_0_i_4_n_0,
      I1 => \^pipelinedelay1_out1_2\,
      I2 => Delay2_delOut,
      O => \^pipelinedelay1_out1_reg_0\
    );
s2_out_INST_0_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04000004"
    )
        port map (
      I0 => s2_out_INST_0_i_8_n_0,
      I1 => s2_out_INST_0_i_9_n_0,
      I2 => s2_out_INST_0_i_10_n_0,
      I3 => HDL_Counter_out1_reg(9),
      I4 => Q(9),
      O => s2_out_INST_0_i_4_n_0
    );
s2_out_INST_0_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(3),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(4),
      I3 => Q(4),
      I4 => HDL_Counter_out1_reg(5),
      I5 => Q(5),
      O => s2_out_INST_0_i_8_n_0
    );
s2_out_INST_0_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => Q(7),
      I2 => HDL_Counter_out1_reg(8),
      I3 => Q(8),
      I4 => Q(6),
      I5 => HDL_Counter_out1_reg(6),
      O => s2_out_INST_0_i_9_n_0
    );
s3_out_INST_0: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8AAA8A8A20002020"
    )
        port map (
      I0 => s3_out_0,
      I1 => \^pipelinedelay1_out1_reg_0\,
      I2 => S3,
      I3 => s3_out_1,
      I4 => S2,
      I5 => PipeDelay_out1,
      O => s3_out
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_6
     port map (
      Detect_Fall_Nonpositive2_out1 => Detect_Fall_Nonpositive2_out1,
      IPCORE_CLK => IPCORE_CLK,
      S3 => S3,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3 is
  port (
    PipelineDelay1_out1_3 : out STD_LOGIC;
    s4_out : out STD_LOGIC;
    PipelineDelay1_out1_reg_0 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Delay2_delOut_reg_0 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    s4_out_0 : in STD_LOGIC;
    s4_out_1 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3 : entity is "uz_interlockDeadtime2L_src_DeadtimeModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3 is
  signal Delay2_delOut : STD_LOGIC;
  signal Delay2_delOut2_out : STD_LOGIC;
  signal Detect_Fall_Nonpositive2_out1 : STD_LOGIC;
  signal \HDL_Counter_out1[6]_i_1__4_n_0\ : STD_LOGIC;
  signal \HDL_Counter_out1[9]_i_4__3_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^pipelinedelay1_out1_3\ : STD_LOGIC;
  signal \^pipelinedelay1_out1_reg_0\ : STD_LOGIC;
  signal \p_0_in__3\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal s4_out_INST_0_i_3_n_0 : STD_LOGIC;
  signal s4_out_INST_0_i_5_n_0 : STD_LOGIC;
  signal s4_out_INST_0_i_6_n_0 : STD_LOGIC;
  signal s4_out_INST_0_i_7_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Delay2_delOut_i_1__3\ : label is "soft_lutpair111";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1__3\ : label is "soft_lutpair114";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1__3\ : label is "soft_lutpair114";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1__3\ : label is "soft_lutpair112";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1__3\ : label is "soft_lutpair112";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1__4\ : label is "soft_lutpair115";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1__3\ : label is "soft_lutpair115";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[8]_i_1__3\ : label is "soft_lutpair113";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_3__3\ : label is "soft_lutpair113";
  attribute SOFT_HLUTNM of s4_out_INST_0_i_1 : label is "soft_lutpair111";
begin
  PipelineDelay1_out1_3 <= \^pipelinedelay1_out1_3\;
  PipelineDelay1_out1_reg_0 <= \^pipelinedelay1_out1_reg_0\;
\Delay2_delOut_i_1__3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00220030"
    )
        port map (
      I0 => S4,
      I1 => reset_x,
      I2 => Delay2_delOut,
      I3 => \^pipelinedelay1_out1_3\,
      I4 => s4_out_INST_0_i_3_n_0,
      O => Delay2_delOut2_out
    );
Delay2_delOut_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => Delay2_delOut_reg_0,
      D => Delay2_delOut2_out,
      Q => Delay2_delOut,
      R => '0'
    );
\HDL_Counter_out1[0]_i_1__3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => \p_0_in__3\(0)
    );
\HDL_Counter_out1[1]_i_1__3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => \p_0_in__3\(1)
    );
\HDL_Counter_out1[2]_i_1__3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      O => \p_0_in__3\(2)
    );
\HDL_Counter_out1[3]_i_1__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      O => \p_0_in__3\(3)
    );
\HDL_Counter_out1[4]_i_1__3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      O => \p_0_in__3\(4)
    );
\HDL_Counter_out1[5]_i_1__3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6AAAAAAAAAAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(5),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(1),
      I3 => HDL_Counter_out1_reg(0),
      I4 => HDL_Counter_out1_reg(2),
      I5 => HDL_Counter_out1_reg(4),
      O => \p_0_in__3\(5)
    );
\HDL_Counter_out1[6]_i_1__4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[9]_i_4__3_n_0\,
      O => \HDL_Counter_out1[6]_i_1__4_n_0\
    );
\HDL_Counter_out1[7]_i_1__3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"9A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => \HDL_Counter_out1[9]_i_4__3_n_0\,
      I2 => HDL_Counter_out1_reg(6),
      O => \p_0_in__3\(7)
    );
\HDL_Counter_out1[8]_i_1__3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"A6AA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(8),
      I1 => HDL_Counter_out1_reg(6),
      I2 => \HDL_Counter_out1[9]_i_4__3_n_0\,
      I3 => HDL_Counter_out1_reg(7),
      O => \p_0_in__3\(8)
    );
\HDL_Counter_out1[9]_i_3__3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A6AAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(9),
      I1 => HDL_Counter_out1_reg(7),
      I2 => \HDL_Counter_out1[9]_i_4__3_n_0\,
      I3 => HDL_Counter_out1_reg(6),
      I4 => HDL_Counter_out1_reg(8),
      O => \p_0_in__3\(9)
    );
\HDL_Counter_out1[9]_i_4__3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFFFFFFFFFF"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      I5 => HDL_Counter_out1_reg(5),
      O => \HDL_Counter_out1[9]_i_4__3_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(0),
      Q => HDL_Counter_out1_reg(0),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(1),
      Q => HDL_Counter_out1_reg(1),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(2),
      Q => HDL_Counter_out1_reg(2),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(3),
      Q => HDL_Counter_out1_reg(3),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(4),
      Q => HDL_Counter_out1_reg(4),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(5),
      Q => HDL_Counter_out1_reg(5),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \HDL_Counter_out1[6]_i_1__4_n_0\,
      Q => HDL_Counter_out1_reg(6),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(7),
      Q => HDL_Counter_out1_reg(7),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(8),
      Q => HDL_Counter_out1_reg(8),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__3\(9),
      Q => HDL_Counter_out1_reg(9),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
PipelineDelay1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Detect_Fall_Nonpositive2_out1,
      Q => \^pipelinedelay1_out1_3\,
      R => reset_x
    );
s4_out_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"08000808"
    )
        port map (
      I0 => s4_out_0,
      I1 => S4,
      I2 => \^pipelinedelay1_out1_reg_0\,
      I3 => s4_out_1,
      I4 => S5,
      O => s4_out
    );
s4_out_INST_0_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"45"
    )
        port map (
      I0 => s4_out_INST_0_i_3_n_0,
      I1 => \^pipelinedelay1_out1_3\,
      I2 => Delay2_delOut,
      O => \^pipelinedelay1_out1_reg_0\
    );
s4_out_INST_0_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04000004"
    )
        port map (
      I0 => s4_out_INST_0_i_5_n_0,
      I1 => s4_out_INST_0_i_6_n_0,
      I2 => s4_out_INST_0_i_7_n_0,
      I3 => HDL_Counter_out1_reg(9),
      I4 => Q(9),
      O => s4_out_INST_0_i_3_n_0
    );
s4_out_INST_0_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(3),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(5),
      I3 => Q(5),
      I4 => HDL_Counter_out1_reg(4),
      I5 => Q(4),
      O => s4_out_INST_0_i_5_n_0
    );
s4_out_INST_0_i_6: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => Q(6),
      I1 => HDL_Counter_out1_reg(6),
      I2 => HDL_Counter_out1_reg(7),
      I3 => Q(7),
      I4 => HDL_Counter_out1_reg(8),
      I5 => Q(8),
      O => s4_out_INST_0_i_6_n_0
    );
s4_out_INST_0_i_7: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(0),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => Q(1),
      I4 => HDL_Counter_out1_reg(2),
      I5 => Q(2),
      O => s4_out_INST_0_i_7_n_0
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2_5
     port map (
      Detect_Fall_Nonpositive2_out1 => Detect_Fall_Nonpositive2_out1,
      IPCORE_CLK => IPCORE_CLK,
      S4 => S4,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4 is
  port (
    PipelineDelay1_out1_4 : out STD_LOGIC;
    s5_out : out STD_LOGIC;
    PipelineDelay1_out1_reg_0 : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    Delay2_delOut_reg_0 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    s5_out_0 : in STD_LOGIC;
    s5_out_1 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    PipeDelay_out1 : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4 : entity is "uz_interlockDeadtime2L_src_DeadtimeModule";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4 is
  signal Delay2_delOut : STD_LOGIC;
  signal Delay2_delOut2_out : STD_LOGIC;
  signal Detect_Fall_Nonpositive2_out1 : STD_LOGIC;
  signal \HDL_Counter_out1[9]_i_4__4_n_0\ : STD_LOGIC;
  signal HDL_Counter_out1_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^pipelinedelay1_out1_4\ : STD_LOGIC;
  signal \^pipelinedelay1_out1_reg_0\ : STD_LOGIC;
  signal \p_0_in__4\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal s4_out_INST_0_i_10_n_0 : STD_LOGIC;
  signal s4_out_INST_0_i_4_n_0 : STD_LOGIC;
  signal s4_out_INST_0_i_8_n_0 : STD_LOGIC;
  signal s4_out_INST_0_i_9_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \Delay2_delOut_i_1__4\ : label is "soft_lutpair117";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[1]_i_1__4\ : label is "soft_lutpair120";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[2]_i_1__4\ : label is "soft_lutpair120";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[3]_i_1__4\ : label is "soft_lutpair118";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[4]_i_1__4\ : label is "soft_lutpair118";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[6]_i_1__1\ : label is "soft_lutpair121";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[7]_i_1__4\ : label is "soft_lutpair121";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[8]_i_1__4\ : label is "soft_lutpair119";
  attribute SOFT_HLUTNM of \HDL_Counter_out1[9]_i_3__4\ : label is "soft_lutpair119";
  attribute SOFT_HLUTNM of s4_out_INST_0_i_2 : label is "soft_lutpair117";
begin
  PipelineDelay1_out1_4 <= \^pipelinedelay1_out1_4\;
  PipelineDelay1_out1_reg_0 <= \^pipelinedelay1_out1_reg_0\;
\Delay2_delOut_i_1__4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00220030"
    )
        port map (
      I0 => S5,
      I1 => reset_x,
      I2 => Delay2_delOut,
      I3 => \^pipelinedelay1_out1_4\,
      I4 => s4_out_INST_0_i_4_n_0,
      O => Delay2_delOut2_out
    );
Delay2_delOut_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => Delay2_delOut_reg_0,
      D => Delay2_delOut2_out,
      Q => Delay2_delOut,
      R => '0'
    );
\HDL_Counter_out1[0]_i_1__4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      O => \p_0_in__4\(0)
    );
\HDL_Counter_out1[1]_i_1__4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(0),
      I1 => HDL_Counter_out1_reg(1),
      O => \p_0_in__4\(1)
    );
\HDL_Counter_out1[2]_i_1__4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(2),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      O => \p_0_in__4\(2)
    );
\HDL_Counter_out1[3]_i_1__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      O => \p_0_in__4\(3)
    );
\HDL_Counter_out1[4]_i_1__4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(4),
      I1 => HDL_Counter_out1_reg(2),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(1),
      I4 => HDL_Counter_out1_reg(3),
      O => \p_0_in__4\(4)
    );
\HDL_Counter_out1[5]_i_1__4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFF80000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(3),
      I1 => HDL_Counter_out1_reg(1),
      I2 => HDL_Counter_out1_reg(0),
      I3 => HDL_Counter_out1_reg(2),
      I4 => HDL_Counter_out1_reg(4),
      I5 => HDL_Counter_out1_reg(5),
      O => \p_0_in__4\(5)
    );
\HDL_Counter_out1[6]_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => HDL_Counter_out1_reg(6),
      I1 => \HDL_Counter_out1[9]_i_4__4_n_0\,
      O => \p_0_in__4\(6)
    );
\HDL_Counter_out1[7]_i_1__4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => \HDL_Counter_out1[9]_i_4__4_n_0\,
      I2 => HDL_Counter_out1_reg(6),
      O => \p_0_in__4\(7)
    );
\HDL_Counter_out1[8]_i_1__4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(8),
      I1 => HDL_Counter_out1_reg(6),
      I2 => \HDL_Counter_out1[9]_i_4__4_n_0\,
      I3 => HDL_Counter_out1_reg(7),
      O => \p_0_in__4\(8)
    );
\HDL_Counter_out1[9]_i_3__4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => HDL_Counter_out1_reg(9),
      I1 => HDL_Counter_out1_reg(7),
      I2 => \HDL_Counter_out1[9]_i_4__4_n_0\,
      I3 => HDL_Counter_out1_reg(6),
      I4 => HDL_Counter_out1_reg(8),
      O => \p_0_in__4\(9)
    );
\HDL_Counter_out1[9]_i_4__4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => HDL_Counter_out1_reg(5),
      I1 => HDL_Counter_out1_reg(4),
      I2 => HDL_Counter_out1_reg(2),
      I3 => HDL_Counter_out1_reg(0),
      I4 => HDL_Counter_out1_reg(1),
      I5 => HDL_Counter_out1_reg(3),
      O => \HDL_Counter_out1[9]_i_4__4_n_0\
    );
\HDL_Counter_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(0),
      Q => HDL_Counter_out1_reg(0),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(1),
      Q => HDL_Counter_out1_reg(1),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(2),
      Q => HDL_Counter_out1_reg(2),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(3),
      Q => HDL_Counter_out1_reg(3),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(4),
      Q => HDL_Counter_out1_reg(4),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(5),
      Q => HDL_Counter_out1_reg(5),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(6),
      Q => HDL_Counter_out1_reg(6),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(7),
      Q => HDL_Counter_out1_reg(7),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(8),
      Q => HDL_Counter_out1_reg(8),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
\HDL_Counter_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => \HDL_Counter_out1_reg[9]_1\(0),
      D => \p_0_in__4\(9),
      Q => HDL_Counter_out1_reg(9),
      R => \HDL_Counter_out1_reg[9]_0\(0)
    );
PipelineDelay1_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => Detect_Fall_Nonpositive2_out1,
      Q => \^pipelinedelay1_out1_4\,
      R => reset_x
    );
s4_out_INST_0_i_10: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(0),
      I1 => HDL_Counter_out1_reg(0),
      I2 => HDL_Counter_out1_reg(1),
      I3 => Q(1),
      I4 => HDL_Counter_out1_reg(2),
      I5 => Q(2),
      O => s4_out_INST_0_i_10_n_0
    );
s4_out_INST_0_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"45"
    )
        port map (
      I0 => s4_out_INST_0_i_4_n_0,
      I1 => \^pipelinedelay1_out1_4\,
      I2 => Delay2_delOut,
      O => \^pipelinedelay1_out1_reg_0\
    );
s4_out_INST_0_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04000004"
    )
        port map (
      I0 => s4_out_INST_0_i_8_n_0,
      I1 => s4_out_INST_0_i_9_n_0,
      I2 => s4_out_INST_0_i_10_n_0,
      I3 => HDL_Counter_out1_reg(9),
      I4 => Q(9),
      O => s4_out_INST_0_i_4_n_0
    );
s4_out_INST_0_i_8: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6FF6FFFFFFFF6FF6"
    )
        port map (
      I0 => Q(3),
      I1 => HDL_Counter_out1_reg(3),
      I2 => HDL_Counter_out1_reg(4),
      I3 => Q(4),
      I4 => HDL_Counter_out1_reg(5),
      I5 => Q(5),
      O => s4_out_INST_0_i_8_n_0
    );
s4_out_INST_0_i_9: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => HDL_Counter_out1_reg(7),
      I1 => Q(7),
      I2 => HDL_Counter_out1_reg(8),
      I3 => Q(8),
      I4 => Q(6),
      I5 => HDL_Counter_out1_reg(6),
      O => s4_out_INST_0_i_9_n_0
    );
s5_out_INST_0: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8AAA8A8A20002020"
    )
        port map (
      I0 => s5_out_0,
      I1 => \^pipelinedelay1_out1_reg_0\,
      I2 => S5,
      I3 => s5_out_1,
      I4 => S4,
      I5 => PipeDelay_out1,
      O => s5_out
    );
u_Detect_Fall_Nonpositive2: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_Detect_Fall_Nonpositive2
     port map (
      Detect_Fall_Nonpositive2_out1 => Detect_Fall_Nonpositive2_out1,
      IPCORE_CLK => IPCORE_CLK,
      S5 => S5,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module is
  port (
    out_valid_reg : out STD_LOGIC;
    AXI4_RLAST : out STD_LOGIC;
    soft_reset : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \axi4_raddr_reg[2]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_ARREADY : out STD_LOGIC;
    AXI4_AWREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    \wdata_reg[9]_0\ : out STD_LOGIC_VECTOR ( 9 downto 0 );
    \wdata_reg[0]_0\ : out STD_LOGIC;
    \wdata_reg[0]_1\ : out STD_LOGIC;
    \wdata_reg[0]_2\ : out STD_LOGIC;
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_BID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_ACLK : in STD_LOGIC;
    AXI4_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    \data_int_reg[1]\ : in STD_LOGIC_VECTOR ( 9 downto 0 );
    read_reg_axi_fb_enable : in STD_LOGIC;
    read_reg_axi_fb_InverseBotSwitch : in STD_LOGIC;
    read_reg_ip_timestamp : in STD_LOGIC_VECTOR ( 0 to 0 );
    AXI4_RREADY : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_BREADY : in STD_LOGIC;
    AXI4_ARVALID : in STD_LOGIC;
    AXI4_WVALID : in STD_LOGIC;
    AXI4_WLAST : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_ARLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_ARBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_AWBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    write_axi_enable : in STD_LOGIC;
    axi_EnableOutput : in STD_LOGIC;
    axi_InverseBotSwitch : in STD_LOGIC;
    AXI4_WDATA : in STD_LOGIC_VECTOR ( 9 downto 0 );
    AXI4_ARID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_AWID : in STD_LOGIC_VECTOR ( 11 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module : entity is "uz_interlockDeadtime2L_axi4_module";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module is
  signal \^q\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal axi4_awtransfer : STD_LOGIC;
  signal axi4_awtransfer_next : STD_LOGIC;
  signal \axi4_raddr[10]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[11]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[12]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[13]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[14]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[15]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[15]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_raddr[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[3]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[4]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[5]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[6]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[7]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[8]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_raddr[9]_i_1_n_0\ : STD_LOGIC;
  signal axi4_raddr_inc : STD_LOGIC_VECTOR ( 2 to 2 );
  signal \axi4_raddr_inc[2]_i_1_n_0\ : STD_LOGIC;
  signal axi4_raddr_inc_next : STD_LOGIC;
  signal \axi4_raddr_reg[15]_i_3_n_3\ : STD_LOGIC;
  signal \axi4_raddr_reg[15]_i_3_n_4\ : STD_LOGIC;
  signal \axi4_raddr_reg[15]_i_3_n_5\ : STD_LOGIC;
  signal \axi4_raddr_reg[15]_i_3_n_6\ : STD_LOGIC;
  signal \axi4_raddr_reg[15]_i_3_n_7\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_1\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_2\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_3\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_4\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_5\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_6\ : STD_LOGIC;
  signal \axi4_raddr_reg[9]_i_2_n_7\ : STD_LOGIC;
  signal axi4_rd_active_i_1_n_0 : STD_LOGIC;
  signal axi4_rd_active_next : STD_LOGIC;
  signal axi4_rid_1 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal axi4_rlast_1 : STD_LOGIC;
  signal axi4_rlast_1_i_2_n_0 : STD_LOGIC;
  signal axi4_rlen : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \axi4_rlen[0]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[1]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[3]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[3]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_rlen[4]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[4]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_rlen[5]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[5]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_rlen[6]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_rlen[7]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_rlen[7]_i_3_n_0\ : STD_LOGIC;
  signal axi4_rstate : STD_LOGIC_VECTOR ( 2 downto 1 );
  signal axi4_rstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal axi4_waddr : STD_LOGIC_VECTOR ( 15 downto 2 );
  signal \axi4_waddr[10]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[11]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[12]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[13]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[14]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[15]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[15]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_waddr[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[3]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[4]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[5]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[6]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[7]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[8]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr[9]_i_1_n_0\ : STD_LOGIC;
  signal axi4_waddr_inc : STD_LOGIC_VECTOR ( 2 to 2 );
  signal \axi4_waddr_inc[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi4_waddr_reg[15]_i_3_n_3\ : STD_LOGIC;
  signal \axi4_waddr_reg[15]_i_3_n_4\ : STD_LOGIC;
  signal \axi4_waddr_reg[15]_i_3_n_5\ : STD_LOGIC;
  signal \axi4_waddr_reg[15]_i_3_n_6\ : STD_LOGIC;
  signal \axi4_waddr_reg[15]_i_3_n_7\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_0\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_1\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_2\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_3\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_4\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_5\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_6\ : STD_LOGIC;
  signal \axi4_waddr_reg[9]_i_2_n_7\ : STD_LOGIC;
  signal axi4_wid_next : STD_LOGIC;
  signal axi4_wstate_next : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal axi4_wtransfer : STD_LOGIC;
  signal axi4_wtransfer_i_1_n_0 : STD_LOGIC;
  signal axi4_wtransfer_next : STD_LOGIC;
  signal \data_reg_axi_DelayCycles_1_1[9]_i_2_n_0\ : STD_LOGIC;
  signal \data_reg_axi_DelayCycles_1_1[9]_i_4_n_0\ : STD_LOGIC;
  signal \data_reg_axi_DelayCycles_1_1[9]_i_5_n_0\ : STD_LOGIC;
  signal \data_reg_axi_DelayCycles_1_1[9]_i_6_n_0\ : STD_LOGIC;
  signal data_reg_axi_EnableOutput_1_1_i_2_n_0 : STD_LOGIC;
  signal data_reg_axi_EnableOutput_1_1_i_3_n_0 : STD_LOGIC;
  signal data_reg_axi_EnableOutput_1_1_i_4_n_0 : STD_LOGIC;
  signal data_reg_axi_InverseBotSwitch_1_1_i_2_n_0 : STD_LOGIC;
  signal data_reg_axi_InverseBotSwitch_1_1_i_3_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_2_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_3_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_4_n_0 : STD_LOGIC;
  signal data_reg_axi_enable_1_1_i_5_n_0 : STD_LOGIC;
  signal in7 : STD_LOGIC_VECTOR ( 15 downto 2 );
  signal in8 : STD_LOGIC_VECTOR ( 15 downto 2 );
  signal raddr_r : STD_LOGIC_VECTOR ( 15 downto 2 );
  signal rd_active : STD_LOGIC;
  signal reset_x : STD_LOGIC;
  signal sel0 : STD_LOGIC_VECTOR ( 13 downto 0 );
  signal \^soft_reset\ : STD_LOGIC;
  signal soft_reset_i_1_n_0 : STD_LOGIC;
  signal soft_reset_i_4_n_0 : STD_LOGIC;
  signal top_rd_enb : STD_LOGIC;
  signal top_wr_enb : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_10 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_11 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_2 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_3 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_4 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9 : STD_LOGIC;
  signal w_transfer_and_wstrb : STD_LOGIC;
  signal waddr_r : STD_LOGIC_VECTOR ( 15 downto 2 );
  signal wdata_int : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^wdata_reg[9]_0\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \wstrb_reduce__0\ : STD_LOGIC;
  signal wstrb_reduce_reg : STD_LOGIC;
  signal \NLW_axi4_raddr_reg[15]_i_3_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal \NLW_axi4_raddr_reg[15]_i_3_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 6 );
  signal \NLW_axi4_raddr_reg[9]_i_2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \NLW_axi4_waddr_reg[15]_i_3_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 5 );
  signal \NLW_axi4_waddr_reg[15]_i_3_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 6 );
  signal \NLW_axi4_waddr_reg[9]_i_2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 0 to 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of AXI4_ARREADY_INST_0 : label is "soft_lutpair81";
  attribute SOFT_HLUTNM of AXI4_AWREADY_INST_0 : label is "soft_lutpair82";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi4_rstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi4_rstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi4_rstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of \FSM_onehot_axi4_wstate[0]_i_1\ : label is "soft_lutpair81";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi4_wstate_reg[0]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi4_wstate_reg[1]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_axi4_wstate_reg[2]\ : label is "iSTATE:010,iSTATE0:100,iSTATE1:001";
  attribute SOFT_HLUTNM of axi4_awtransfer_i_1 : label is "soft_lutpair82";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \axi4_raddr_reg[15]_i_3\ : label is 35;
  attribute ADDER_THRESHOLD of \axi4_raddr_reg[9]_i_2\ : label is 35;
  attribute SOFT_HLUTNM of \axi4_rlen[4]_i_2\ : label is "soft_lutpair83";
  attribute SOFT_HLUTNM of \axi4_rlen[5]_i_2\ : label is "soft_lutpair83";
  attribute SOFT_HLUTNM of \axi4_waddr[15]_i_2\ : label is "soft_lutpair84";
  attribute ADDER_THRESHOLD of \axi4_waddr_reg[15]_i_3\ : label is 35;
  attribute ADDER_THRESHOLD of \axi4_waddr_reg[9]_i_2\ : label is 35;
  attribute SOFT_HLUTNM of axi4_wtransfer_i_2 : label is "soft_lutpair84";
  attribute SOFT_HLUTNM of data_reg_axi_EnableOutput_1_1_i_2 : label is "soft_lutpair80";
  attribute SOFT_HLUTNM of data_reg_axi_EnableOutput_1_1_i_4 : label is "soft_lutpair79";
  attribute SOFT_HLUTNM of data_reg_axi_InverseBotSwitch_1_1_i_2 : label is "soft_lutpair85";
  attribute SOFT_HLUTNM of data_reg_axi_InverseBotSwitch_1_1_i_3 : label is "soft_lutpair85";
  attribute SOFT_HLUTNM of data_reg_axi_enable_1_1_i_3 : label is "soft_lutpair80";
  attribute SOFT_HLUTNM of data_reg_axi_enable_1_1_i_5 : label is "soft_lutpair79";
begin
  Q(1 downto 0) <= \^q\(1 downto 0);
  soft_reset <= \^soft_reset\;
  \wdata_reg[9]_0\(9 downto 0) <= \^wdata_reg[9]_0\(9 downto 0);
AXI4_ARREADY_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => axi4_wid_next,
      I2 => AXI4_AWVALID,
      O => AXI4_ARREADY
    );
AXI4_AWREADY_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => axi4_raddr_inc_next,
      O => AXI4_AWREADY
    );
\FSM_onehot_axi4_rstate[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"44F4444444444444"
    )
        port map (
      I0 => axi4_rlast_1,
      I1 => axi4_rstate(1),
      I2 => axi4_wid_next,
      I3 => AXI4_AWVALID,
      I4 => AXI4_ARVALID,
      I5 => axi4_raddr_inc_next,
      O => axi4_rstate_next(1)
    );
\FSM_onehot_axi4_rstate_reg[0]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_rstate_next(0),
      Q => axi4_raddr_inc_next,
      S => reset_x
    );
\FSM_onehot_axi4_rstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_rstate_next(1),
      Q => axi4_rstate(1),
      R => reset_x
    );
\FSM_onehot_axi4_rstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_rstate_next(2),
      Q => axi4_rstate(2),
      R => reset_x
    );
\FSM_onehot_axi4_wstate[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"D5FFC0C0"
    )
        port map (
      I0 => AXI4_AWVALID,
      I1 => AXI4_BREADY,
      I2 => \^q\(1),
      I3 => axi4_raddr_inc_next,
      I4 => axi4_wid_next,
      O => axi4_wstate_next(0)
    );
\FSM_onehot_axi4_wstate[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"80FFFFFF80808080"
    )
        port map (
      I0 => AXI4_AWVALID,
      I1 => axi4_wid_next,
      I2 => axi4_raddr_inc_next,
      I3 => AXI4_WVALID,
      I4 => AXI4_WLAST,
      I5 => \^q\(0),
      O => axi4_wstate_next(1)
    );
\FSM_onehot_axi4_wstate[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"80FF8080"
    )
        port map (
      I0 => AXI4_WLAST,
      I1 => AXI4_WVALID,
      I2 => \^q\(0),
      I3 => AXI4_BREADY,
      I4 => \^q\(1),
      O => axi4_wstate_next(2)
    );
\FSM_onehot_axi4_wstate_reg[0]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_wstate_next(0),
      Q => axi4_wid_next,
      S => reset_x
    );
\FSM_onehot_axi4_wstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_wstate_next(1),
      Q => \^q\(0),
      R => reset_x
    );
\FSM_onehot_axi4_wstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_wstate_next(2),
      Q => \^q\(1),
      R => reset_x
    );
axi4_ar_transfer_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_11,
      Q => top_rd_enb,
      R => reset_x
    );
axi4_awtransfer_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FF808080"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => axi4_wid_next,
      I2 => AXI4_AWVALID,
      I3 => \^q\(0),
      I4 => AXI4_WVALID,
      O => axi4_awtransfer_next
    );
axi4_awtransfer_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer_i_1_n_0,
      D => axi4_awtransfer_next,
      Q => axi4_awtransfer,
      R => reset_x
    );
\axi4_raddr[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(8),
      I2 => axi4_rstate(1),
      I3 => in8(10),
      O => \axi4_raddr[10]_i_1_n_0\
    );
\axi4_raddr[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(9),
      I2 => axi4_rstate(1),
      I3 => in8(11),
      O => \axi4_raddr[11]_i_1_n_0\
    );
\axi4_raddr[12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(10),
      I2 => axi4_rstate(1),
      I3 => in8(12),
      O => \axi4_raddr[12]_i_1_n_0\
    );
\axi4_raddr[13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(11),
      I2 => axi4_rstate(1),
      I3 => in8(13),
      O => \axi4_raddr[13]_i_1_n_0\
    );
\axi4_raddr[14]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(12),
      I2 => axi4_rstate(1),
      I3 => in8(14),
      O => \axi4_raddr[14]_i_1_n_0\
    );
\axi4_raddr[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => axi4_rstate(1),
      I1 => top_rd_enb,
      I2 => axi4_raddr_inc_next,
      O => \axi4_raddr[15]_i_1_n_0\
    );
\axi4_raddr[15]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(13),
      I2 => axi4_rstate(1),
      I3 => in8(15),
      O => \axi4_raddr[15]_i_2_n_0\
    );
\axi4_raddr[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88F8F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(0),
      I2 => axi4_rstate(1),
      I3 => raddr_r(2),
      I4 => axi4_raddr_inc(2),
      O => \axi4_raddr[2]_i_1_n_0\
    );
\axi4_raddr[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(1),
      I2 => axi4_rstate(1),
      I3 => in8(3),
      O => \axi4_raddr[3]_i_1_n_0\
    );
\axi4_raddr[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(2),
      I2 => axi4_rstate(1),
      I3 => in8(4),
      O => \axi4_raddr[4]_i_1_n_0\
    );
\axi4_raddr[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(3),
      I2 => axi4_rstate(1),
      I3 => in8(5),
      O => \axi4_raddr[5]_i_1_n_0\
    );
\axi4_raddr[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(4),
      I2 => axi4_rstate(1),
      I3 => in8(6),
      O => \axi4_raddr[6]_i_1_n_0\
    );
\axi4_raddr[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(5),
      I2 => axi4_rstate(1),
      I3 => in8(7),
      O => \axi4_raddr[7]_i_1_n_0\
    );
\axi4_raddr[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(6),
      I2 => axi4_rstate(1),
      I3 => in8(8),
      O => \axi4_raddr[8]_i_1_n_0\
    );
\axi4_raddr[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARADDR(7),
      I2 => axi4_rstate(1),
      I3 => in8(9),
      O => \axi4_raddr[9]_i_1_n_0\
    );
\axi4_raddr[9]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => raddr_r(2),
      I1 => axi4_raddr_inc(2),
      O => in8(2)
    );
\axi4_raddr_inc[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EFE0"
    )
        port map (
      I0 => AXI4_ARBURST(0),
      I1 => AXI4_ARBURST(1),
      I2 => axi4_raddr_inc_next,
      I3 => axi4_raddr_inc(2),
      O => \axi4_raddr_inc[2]_i_1_n_0\
    );
\axi4_raddr_inc_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \axi4_raddr_inc[2]_i_1_n_0\,
      Q => axi4_raddr_inc(2),
      R => reset_x
    );
\axi4_raddr_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[10]_i_1_n_0\,
      Q => raddr_r(10),
      R => reset_x
    );
\axi4_raddr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[11]_i_1_n_0\,
      Q => raddr_r(11),
      R => reset_x
    );
\axi4_raddr_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[12]_i_1_n_0\,
      Q => raddr_r(12),
      R => reset_x
    );
\axi4_raddr_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[13]_i_1_n_0\,
      Q => raddr_r(13),
      R => reset_x
    );
\axi4_raddr_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[14]_i_1_n_0\,
      Q => raddr_r(14),
      R => reset_x
    );
\axi4_raddr_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[15]_i_2_n_0\,
      Q => raddr_r(15),
      R => reset_x
    );
\axi4_raddr_reg[15]_i_3\: unisim.vcomponents.CARRY8
     port map (
      CI => \axi4_raddr_reg[9]_i_2_n_0\,
      CI_TOP => '0',
      CO(7 downto 5) => \NLW_axi4_raddr_reg[15]_i_3_CO_UNCONNECTED\(7 downto 5),
      CO(4) => \axi4_raddr_reg[15]_i_3_n_3\,
      CO(3) => \axi4_raddr_reg[15]_i_3_n_4\,
      CO(2) => \axi4_raddr_reg[15]_i_3_n_5\,
      CO(1) => \axi4_raddr_reg[15]_i_3_n_6\,
      CO(0) => \axi4_raddr_reg[15]_i_3_n_7\,
      DI(7 downto 5) => B"000",
      DI(4 downto 0) => raddr_r(14 downto 10),
      O(7 downto 6) => \NLW_axi4_raddr_reg[15]_i_3_O_UNCONNECTED\(7 downto 6),
      O(5 downto 0) => in8(15 downto 10),
      S(7 downto 6) => B"00",
      S(5 downto 0) => raddr_r(15 downto 10)
    );
\axi4_raddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[2]_i_1_n_0\,
      Q => raddr_r(2),
      R => reset_x
    );
\axi4_raddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[3]_i_1_n_0\,
      Q => raddr_r(3),
      R => reset_x
    );
\axi4_raddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[4]_i_1_n_0\,
      Q => raddr_r(4),
      R => reset_x
    );
\axi4_raddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[5]_i_1_n_0\,
      Q => raddr_r(5),
      R => reset_x
    );
\axi4_raddr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[6]_i_1_n_0\,
      Q => raddr_r(6),
      R => reset_x
    );
\axi4_raddr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[7]_i_1_n_0\,
      Q => raddr_r(7),
      R => reset_x
    );
\axi4_raddr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[8]_i_1_n_0\,
      Q => raddr_r(8),
      R => reset_x
    );
\axi4_raddr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_raddr[15]_i_1_n_0\,
      D => \axi4_raddr[9]_i_1_n_0\,
      Q => raddr_r(9),
      R => reset_x
    );
\axi4_raddr_reg[9]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \axi4_raddr_reg[9]_i_2_n_0\,
      CO(6) => \axi4_raddr_reg[9]_i_2_n_1\,
      CO(5) => \axi4_raddr_reg[9]_i_2_n_2\,
      CO(4) => \axi4_raddr_reg[9]_i_2_n_3\,
      CO(3) => \axi4_raddr_reg[9]_i_2_n_4\,
      CO(2) => \axi4_raddr_reg[9]_i_2_n_5\,
      CO(1) => \axi4_raddr_reg[9]_i_2_n_6\,
      CO(0) => \axi4_raddr_reg[9]_i_2_n_7\,
      DI(7 downto 0) => raddr_r(9 downto 2),
      O(7 downto 1) => in8(9 downto 3),
      O(0) => \NLW_axi4_raddr_reg[9]_i_2_O_UNCONNECTED\(0),
      S(7 downto 1) => raddr_r(9 downto 3),
      S(0) => in8(2)
    );
axi4_rd_active_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"202000FF20200000"
    )
        port map (
      I0 => AXI4_ARVALID,
      I1 => AXI4_AWVALID,
      I2 => axi4_wid_next,
      I3 => axi4_rstate(2),
      I4 => axi4_raddr_inc_next,
      I5 => rd_active,
      O => axi4_rd_active_i_1_n_0
    );
axi4_rd_active_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => axi4_rd_active_i_1_n_0,
      Q => rd_active,
      R => reset_x
    );
\axi4_rid_1[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0800"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARVALID,
      I2 => AXI4_AWVALID,
      I3 => axi4_wid_next,
      O => axi4_rd_active_next
    );
\axi4_rid_1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(0),
      Q => axi4_rid_1(0),
      R => reset_x
    );
\axi4_rid_1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(10),
      Q => axi4_rid_1(10),
      R => reset_x
    );
\axi4_rid_1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(11),
      Q => axi4_rid_1(11),
      R => reset_x
    );
\axi4_rid_1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(1),
      Q => axi4_rid_1(1),
      R => reset_x
    );
\axi4_rid_1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(2),
      Q => axi4_rid_1(2),
      R => reset_x
    );
\axi4_rid_1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(3),
      Q => axi4_rid_1(3),
      R => reset_x
    );
\axi4_rid_1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(4),
      Q => axi4_rid_1(4),
      R => reset_x
    );
\axi4_rid_1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(5),
      Q => axi4_rid_1(5),
      R => reset_x
    );
\axi4_rid_1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(6),
      Q => axi4_rid_1(6),
      R => reset_x
    );
\axi4_rid_1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(7),
      Q => axi4_rid_1(7),
      R => reset_x
    );
\axi4_rid_1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(8),
      Q => axi4_rid_1(8),
      R => reset_x
    );
\axi4_rid_1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_rd_active_next,
      D => AXI4_ARID(9),
      Q => axi4_rid_1(9),
      R => reset_x
    );
axi4_rlast_1_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0100"
    )
        port map (
      I0 => axi4_rlen(7),
      I1 => axi4_rlen(6),
      I2 => axi4_rlast_1,
      I3 => axi4_rstate(1),
      O => axi4_rlast_1_i_2_n_0
    );
axi4_rlast_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_10,
      Q => axi4_rlast_1,
      R => reset_x
    );
\axi4_rlen[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(0),
      I2 => axi4_rlen(0),
      I3 => axi4_rstate(1),
      O => \axi4_rlen[0]_i_1_n_0\
    );
\axi4_rlen[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F88F8888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(1),
      I2 => axi4_rlen(0),
      I3 => axi4_rlen(1),
      I4 => axi4_rstate(1),
      O => \axi4_rlen[1]_i_1_n_0\
    );
\axi4_rlen[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF8888F88888888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(2),
      I2 => axi4_rlen(1),
      I3 => axi4_rlen(0),
      I4 => axi4_rlen(2),
      I5 => axi4_rstate(1),
      O => \axi4_rlen[2]_i_1_n_0\
    );
\axi4_rlen[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F88F8888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(3),
      I2 => \axi4_rlen[3]_i_2_n_0\,
      I3 => axi4_rlen(3),
      I4 => axi4_rstate(1),
      O => \axi4_rlen[3]_i_1_n_0\
    );
\axi4_rlen[3]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => axi4_rlen(1),
      I1 => axi4_rlen(0),
      I2 => axi4_rlen(2),
      O => \axi4_rlen[3]_i_2_n_0\
    );
\axi4_rlen[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F88F8888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(4),
      I2 => \axi4_rlen[4]_i_2_n_0\,
      I3 => axi4_rlen(4),
      I4 => axi4_rstate(1),
      O => \axi4_rlen[4]_i_1_n_0\
    );
\axi4_rlen[4]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => axi4_rlen(2),
      I1 => axi4_rlen(0),
      I2 => axi4_rlen(1),
      I3 => axi4_rlen(3),
      O => \axi4_rlen[4]_i_2_n_0\
    );
\axi4_rlen[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F88F8888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(5),
      I2 => \axi4_rlen[5]_i_2_n_0\,
      I3 => axi4_rlen(5),
      I4 => axi4_rstate(1),
      O => \axi4_rlen[5]_i_1_n_0\
    );
\axi4_rlen[5]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => axi4_rlen(3),
      I1 => axi4_rlen(1),
      I2 => axi4_rlen(0),
      I3 => axi4_rlen(2),
      I4 => axi4_rlen(4),
      O => \axi4_rlen[5]_i_2_n_0\
    );
\axi4_rlen[6]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F88F8888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(6),
      I2 => \axi4_rlen[7]_i_3_n_0\,
      I3 => axi4_rlen(6),
      I4 => axi4_rstate(1),
      O => \axi4_rlen[6]_i_1_n_0\
    );
\axi4_rlen[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFF8888F88888888"
    )
        port map (
      I0 => axi4_raddr_inc_next,
      I1 => AXI4_ARLEN(7),
      I2 => axi4_rlen(6),
      I3 => \axi4_rlen[7]_i_3_n_0\,
      I4 => axi4_rlen(7),
      I5 => axi4_rstate(1),
      O => \axi4_rlen[7]_i_2_n_0\
    );
\axi4_rlen[7]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => axi4_rlen(4),
      I1 => axi4_rlen(2),
      I2 => axi4_rlen(0),
      I3 => axi4_rlen(1),
      I4 => axi4_rlen(3),
      I5 => axi4_rlen(5),
      O => \axi4_rlen[7]_i_3_n_0\
    );
\axi4_rlen_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[0]_i_1_n_0\,
      Q => axi4_rlen(0),
      R => reset_x
    );
\axi4_rlen_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[1]_i_1_n_0\,
      Q => axi4_rlen(1),
      R => reset_x
    );
\axi4_rlen_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[2]_i_1_n_0\,
      Q => axi4_rlen(2),
      R => reset_x
    );
\axi4_rlen_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[3]_i_1_n_0\,
      Q => axi4_rlen(3),
      R => reset_x
    );
\axi4_rlen_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[4]_i_1_n_0\,
      Q => axi4_rlen(4),
      R => reset_x
    );
\axi4_rlen_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[5]_i_1_n_0\,
      Q => axi4_rlen(5),
      R => reset_x
    );
\axi4_rlen_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[6]_i_1_n_0\,
      Q => axi4_rlen(6),
      R => reset_x
    );
\axi4_rlen_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      D => \axi4_rlen[7]_i_2_n_0\,
      Q => axi4_rlen(7),
      R => reset_x
    );
\axi4_waddr[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(8),
      I2 => \^q\(0),
      I3 => in7(10),
      O => \axi4_waddr[10]_i_1_n_0\
    );
\axi4_waddr[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(9),
      I2 => \^q\(0),
      I3 => in7(11),
      O => \axi4_waddr[11]_i_1_n_0\
    );
\axi4_waddr[12]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(10),
      I2 => \^q\(0),
      I3 => in7(12),
      O => \axi4_waddr[12]_i_1_n_0\
    );
\axi4_waddr[13]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(11),
      I2 => \^q\(0),
      I3 => in7(13),
      O => \axi4_waddr[13]_i_1_n_0\
    );
\axi4_waddr[14]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(12),
      I2 => \^q\(0),
      I3 => in7(14),
      O => \axi4_waddr[14]_i_1_n_0\
    );
\axi4_waddr[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F8"
    )
        port map (
      I0 => \^q\(0),
      I1 => AXI4_WVALID,
      I2 => axi4_wid_next,
      O => \axi4_waddr[15]_i_1_n_0\
    );
\axi4_waddr[15]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(13),
      I2 => \^q\(0),
      I3 => in7(15),
      O => \axi4_waddr[15]_i_2_n_0\
    );
\axi4_waddr[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88F8F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(0),
      I2 => \^q\(0),
      I3 => axi4_waddr(2),
      I4 => axi4_waddr_inc(2),
      O => \axi4_waddr[2]_i_1_n_0\
    );
\axi4_waddr[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(1),
      I2 => \^q\(0),
      I3 => in7(3),
      O => \axi4_waddr[3]_i_1_n_0\
    );
\axi4_waddr[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(2),
      I2 => \^q\(0),
      I3 => in7(4),
      O => \axi4_waddr[4]_i_1_n_0\
    );
\axi4_waddr[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(3),
      I2 => \^q\(0),
      I3 => in7(5),
      O => \axi4_waddr[5]_i_1_n_0\
    );
\axi4_waddr[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(4),
      I2 => \^q\(0),
      I3 => in7(6),
      O => \axi4_waddr[6]_i_1_n_0\
    );
\axi4_waddr[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(5),
      I2 => \^q\(0),
      I3 => in7(7),
      O => \axi4_waddr[7]_i_1_n_0\
    );
\axi4_waddr[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(6),
      I2 => \^q\(0),
      I3 => in7(8),
      O => \axi4_waddr[8]_i_1_n_0\
    );
\axi4_waddr[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F888"
    )
        port map (
      I0 => axi4_wid_next,
      I1 => AXI4_AWADDR(7),
      I2 => \^q\(0),
      I3 => in7(9),
      O => \axi4_waddr[9]_i_1_n_0\
    );
\axi4_waddr[9]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => axi4_waddr(2),
      I1 => axi4_waddr_inc(2),
      O => in7(2)
    );
\axi4_waddr_inc[2]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => AXI4_AWBURST(0),
      I1 => AXI4_AWBURST(1),
      O => \axi4_waddr_inc[2]_i_1_n_0\
    );
\axi4_waddr_inc_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => \axi4_waddr_inc[2]_i_1_n_0\,
      Q => axi4_waddr_inc(2),
      R => reset_x
    );
\axi4_waddr_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[10]_i_1_n_0\,
      Q => axi4_waddr(10),
      R => reset_x
    );
\axi4_waddr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[11]_i_1_n_0\,
      Q => axi4_waddr(11),
      R => reset_x
    );
\axi4_waddr_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[12]_i_1_n_0\,
      Q => axi4_waddr(12),
      R => reset_x
    );
\axi4_waddr_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[13]_i_1_n_0\,
      Q => axi4_waddr(13),
      R => reset_x
    );
\axi4_waddr_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[14]_i_1_n_0\,
      Q => axi4_waddr(14),
      R => reset_x
    );
\axi4_waddr_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[15]_i_2_n_0\,
      Q => axi4_waddr(15),
      R => reset_x
    );
\axi4_waddr_reg[15]_i_3\: unisim.vcomponents.CARRY8
     port map (
      CI => \axi4_waddr_reg[9]_i_2_n_0\,
      CI_TOP => '0',
      CO(7 downto 5) => \NLW_axi4_waddr_reg[15]_i_3_CO_UNCONNECTED\(7 downto 5),
      CO(4) => \axi4_waddr_reg[15]_i_3_n_3\,
      CO(3) => \axi4_waddr_reg[15]_i_3_n_4\,
      CO(2) => \axi4_waddr_reg[15]_i_3_n_5\,
      CO(1) => \axi4_waddr_reg[15]_i_3_n_6\,
      CO(0) => \axi4_waddr_reg[15]_i_3_n_7\,
      DI(7 downto 5) => B"000",
      DI(4 downto 0) => axi4_waddr(14 downto 10),
      O(7 downto 6) => \NLW_axi4_waddr_reg[15]_i_3_O_UNCONNECTED\(7 downto 6),
      O(5 downto 0) => in7(15 downto 10),
      S(7 downto 6) => B"00",
      S(5 downto 0) => axi4_waddr(15 downto 10)
    );
\axi4_waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[2]_i_1_n_0\,
      Q => axi4_waddr(2),
      R => reset_x
    );
\axi4_waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[3]_i_1_n_0\,
      Q => axi4_waddr(3),
      R => reset_x
    );
\axi4_waddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[4]_i_1_n_0\,
      Q => axi4_waddr(4),
      R => reset_x
    );
\axi4_waddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[5]_i_1_n_0\,
      Q => axi4_waddr(5),
      R => reset_x
    );
\axi4_waddr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[6]_i_1_n_0\,
      Q => axi4_waddr(6),
      R => reset_x
    );
\axi4_waddr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[7]_i_1_n_0\,
      Q => axi4_waddr(7),
      R => reset_x
    );
\axi4_waddr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[8]_i_1_n_0\,
      Q => axi4_waddr(8),
      R => reset_x
    );
\axi4_waddr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => \axi4_waddr[15]_i_1_n_0\,
      D => \axi4_waddr[9]_i_1_n_0\,
      Q => axi4_waddr(9),
      R => reset_x
    );
\axi4_waddr_reg[9]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \axi4_waddr_reg[9]_i_2_n_0\,
      CO(6) => \axi4_waddr_reg[9]_i_2_n_1\,
      CO(5) => \axi4_waddr_reg[9]_i_2_n_2\,
      CO(4) => \axi4_waddr_reg[9]_i_2_n_3\,
      CO(3) => \axi4_waddr_reg[9]_i_2_n_4\,
      CO(2) => \axi4_waddr_reg[9]_i_2_n_5\,
      CO(1) => \axi4_waddr_reg[9]_i_2_n_6\,
      CO(0) => \axi4_waddr_reg[9]_i_2_n_7\,
      DI(7 downto 0) => axi4_waddr(9 downto 2),
      O(7 downto 1) => in7(9 downto 3),
      O(0) => \NLW_axi4_waddr_reg[9]_i_2_O_UNCONNECTED\(0),
      S(7 downto 1) => axi4_waddr(9 downto 3),
      S(0) => in7(2)
    );
\axi4_wid_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(0),
      Q => AXI4_BID(0),
      R => reset_x
    );
\axi4_wid_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(10),
      Q => AXI4_BID(10),
      R => reset_x
    );
\axi4_wid_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(11),
      Q => AXI4_BID(11),
      R => reset_x
    );
\axi4_wid_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(1),
      Q => AXI4_BID(1),
      R => reset_x
    );
\axi4_wid_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(2),
      Q => AXI4_BID(2),
      R => reset_x
    );
\axi4_wid_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(3),
      Q => AXI4_BID(3),
      R => reset_x
    );
\axi4_wid_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(4),
      Q => AXI4_BID(4),
      R => reset_x
    );
\axi4_wid_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(5),
      Q => AXI4_BID(5),
      R => reset_x
    );
\axi4_wid_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(6),
      Q => AXI4_BID(6),
      R => reset_x
    );
\axi4_wid_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(7),
      Q => AXI4_BID(7),
      R => reset_x
    );
\axi4_wid_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(8),
      Q => AXI4_BID(8),
      R => reset_x
    );
\axi4_wid_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wid_next,
      D => AXI4_AWID(9),
      Q => AXI4_BID(9),
      R => reset_x
    );
axi4_wtransfer_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FE"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      I2 => axi4_wid_next,
      O => axi4_wtransfer_i_1_n_0
    );
axi4_wtransfer_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => AXI4_WVALID,
      I1 => \^q\(0),
      O => axi4_wtransfer_next
    );
axi4_wtransfer_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer_i_1_n_0,
      D => axi4_wtransfer_next,
      Q => axi4_wtransfer,
      R => reset_x
    );
\data_reg_axi_DelayCycles_1_1[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF80000000"
    )
        port map (
      I0 => \data_reg_axi_DelayCycles_1_1[9]_i_2_n_0\,
      I1 => raddr_r(2),
      I2 => raddr_r(4),
      I3 => top_wr_enb,
      I4 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_4,
      I5 => \data_reg_axi_DelayCycles_1_1[9]_i_4_n_0\,
      O => \axi4_raddr_reg[2]_0\(0)
    );
\data_reg_axi_DelayCycles_1_1[9]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"02000000"
    )
        port map (
      I0 => \data_reg_axi_DelayCycles_1_1[9]_i_5_n_0\,
      I1 => raddr_r(6),
      I2 => raddr_r(5),
      I3 => rd_active,
      I4 => \data_reg_axi_DelayCycles_1_1[9]_i_6_n_0\,
      O => \data_reg_axi_DelayCycles_1_1[9]_i_2_n_0\
    );
\data_reg_axi_DelayCycles_1_1[9]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2000000000000000"
    )
        port map (
      I0 => sel0(6),
      I1 => sel0(1),
      I2 => top_wr_enb,
      I3 => sel0(2),
      I4 => sel0(0),
      I5 => data_reg_axi_EnableOutput_1_1_i_3_n_0,
      O => \data_reg_axi_DelayCycles_1_1[9]_i_4_n_0\
    );
\data_reg_axi_DelayCycles_1_1[9]_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => raddr_r(11),
      I1 => raddr_r(10),
      I2 => raddr_r(9),
      I3 => raddr_r(7),
      O => \data_reg_axi_DelayCycles_1_1[9]_i_5_n_0\
    );
\data_reg_axi_DelayCycles_1_1[9]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => raddr_r(15),
      I1 => raddr_r(14),
      I2 => raddr_r(13),
      I3 => raddr_r(12),
      O => \data_reg_axi_DelayCycles_1_1[9]_i_6_n_0\
    );
data_reg_axi_EnableOutput_1_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AABFBFBFAA808080"
    )
        port map (
      I0 => \^wdata_reg[9]_0\(0),
      I1 => \data_reg_axi_DelayCycles_1_1[9]_i_2_n_0\,
      I2 => data_reg_axi_EnableOutput_1_1_i_2_n_0,
      I3 => data_reg_axi_EnableOutput_1_1_i_3_n_0,
      I4 => data_reg_axi_EnableOutput_1_1_i_4_n_0,
      I5 => axi_EnableOutput,
      O => \wdata_reg[0]_1\
    );
data_reg_axi_EnableOutput_1_1_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00400000"
    )
        port map (
      I0 => raddr_r(2),
      I1 => raddr_r(4),
      I2 => top_wr_enb,
      I3 => raddr_r(3),
      I4 => raddr_r(8),
      O => data_reg_axi_EnableOutput_1_1_i_2_n_0
    );
data_reg_axi_EnableOutput_1_1_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00001000"
    )
        port map (
      I0 => sel0(3),
      I1 => sel0(4),
      I2 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6,
      I3 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5,
      I4 => rd_active,
      O => data_reg_axi_EnableOutput_1_1_i_3_n_0
    );
data_reg_axi_EnableOutput_1_1_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00400000"
    )
        port map (
      I0 => sel0(0),
      I1 => sel0(2),
      I2 => top_wr_enb,
      I3 => sel0(1),
      I4 => sel0(6),
      O => data_reg_axi_EnableOutput_1_1_i_4_n_0
    );
data_reg_axi_InverseBotSwitch_1_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AABFBFBFAA808080"
    )
        port map (
      I0 => \^wdata_reg[9]_0\(0),
      I1 => data_reg_axi_enable_1_1_i_2_n_0,
      I2 => data_reg_axi_InverseBotSwitch_1_1_i_2_n_0,
      I3 => data_reg_axi_enable_1_1_i_4_n_0,
      I4 => data_reg_axi_InverseBotSwitch_1_1_i_3_n_0,
      I5 => axi_InverseBotSwitch,
      O => \wdata_reg[0]_2\
    );
data_reg_axi_InverseBotSwitch_1_1_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => top_wr_enb,
      I1 => raddr_r(8),
      I2 => raddr_r(3),
      O => data_reg_axi_InverseBotSwitch_1_1_i_2_n_0
    );
data_reg_axi_InverseBotSwitch_1_1_i_3: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => top_wr_enb,
      I1 => sel0(6),
      I2 => sel0(1),
      O => data_reg_axi_InverseBotSwitch_1_1_i_3_n_0
    );
data_reg_axi_enable_1_1_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AABFBFBFAA808080"
    )
        port map (
      I0 => \^wdata_reg[9]_0\(0),
      I1 => data_reg_axi_enable_1_1_i_2_n_0,
      I2 => data_reg_axi_enable_1_1_i_3_n_0,
      I3 => data_reg_axi_enable_1_1_i_4_n_0,
      I4 => data_reg_axi_enable_1_1_i_5_n_0,
      I5 => write_axi_enable,
      O => \wdata_reg[0]_0\
    );
data_reg_axi_enable_1_1_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_3,
      I1 => raddr_r(2),
      O => data_reg_axi_enable_1_1_i_2_n_0
    );
data_reg_axi_enable_1_1_i_3: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => raddr_r(8),
      I1 => top_wr_enb,
      I2 => raddr_r(3),
      O => data_reg_axi_enable_1_1_i_3_n_0
    );
data_reg_axi_enable_1_1_i_4: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_2,
      I1 => sel0(0),
      O => data_reg_axi_enable_1_1_i_4_n_0
    );
data_reg_axi_enable_1_1_i_5: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => sel0(6),
      I1 => top_wr_enb,
      I2 => sel0(1),
      O => data_reg_axi_enable_1_1_i_5_n_0
    );
reset_pipe_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => IPCORE_RESETN,
      I1 => \^soft_reset\,
      I2 => AXI4_ARESETN,
      O => reset_in
    );
soft_reset_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5,
      I1 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6,
      I2 => sel0(4),
      I3 => sel0(3),
      I4 => sel0(0),
      I5 => soft_reset_i_4_n_0,
      O => soft_reset_i_1_n_0
    );
soft_reset_i_4: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0002000000000000"
    )
        port map (
      I0 => \^wdata_reg[9]_0\(0),
      I1 => sel0(6),
      I2 => sel0(1),
      I3 => sel0(2),
      I4 => top_wr_enb,
      I5 => AXI4_ARESETN,
      O => soft_reset_i_4_n_0
    );
soft_reset_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => soft_reset_i_1_n_0,
      Q => \^soft_reset\,
      R => '0'
    );
u_uz_interlockDeadtime2L_rdfifo_data_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_data
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_ARESETN => AXI4_ARESETN,
      AXI4_ARVALID => AXI4_ARVALID,
      AXI4_AWVALID => AXI4_AWVALID,
      AXI4_RDATA(31 downto 0) => AXI4_RDATA(31 downto 0),
      AXI4_RREADY => AXI4_RREADY,
      D(1) => axi4_rstate_next(2),
      D(0) => axi4_rstate_next(0),
      E(0) => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_9,
      \FSM_onehot_axi4_rstate_reg[0]\(2 downto 1) => axi4_rstate(2 downto 1),
      \FSM_onehot_axi4_rstate_reg[0]\(0) => axi4_raddr_inc_next,
      \FSM_onehot_axi4_rstate_reg[0]_0\(0) => axi4_wid_next,
      \FSM_onehot_axi4_rstate_reg[1]\ => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_10,
      Q(13 downto 0) => sel0(13 downto 0),
      SR(0) => reset_x,
      \axi4_raddr_reg[8]\ => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_4,
      axi4_rd_active_reg => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_2,
      axi4_rd_active_reg_0 => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_3,
      axi4_rlast_1 => axi4_rlast_1,
      axi4_rlast_1_reg => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_11,
      axi4_rlast_1_reg_0 => \axi4_rlen[7]_i_3_n_0\,
      axi4_rlast_1_reg_1 => axi4_rlast_1_i_2_n_0,
      \data_int_reg[1]\(9 downto 0) => \data_int_reg[1]\(9 downto 0),
      \data_reg_axi_DelayCycles_1_1_reg[9]\(5) => raddr_r(8),
      \data_reg_axi_DelayCycles_1_1_reg[9]\(4 downto 0) => raddr_r(6 downto 2),
      data_reg_axi_enable_1_1_i_2 => \data_reg_axi_DelayCycles_1_1[9]_i_6_n_0\,
      data_reg_axi_enable_1_1_i_2_0 => \data_reg_axi_DelayCycles_1_1[9]_i_5_n_0\,
      out_valid_reg_0 => out_valid_reg,
      rd_active => rd_active,
      read_reg_axi_fb_InverseBotSwitch => read_reg_axi_fb_InverseBotSwitch,
      read_reg_axi_fb_enable => read_reg_axi_fb_enable,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(0),
      top_rd_enb => top_rd_enb,
      \waddr_reg[11]\ => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_6,
      \waddr_reg[15]\ => u_uz_interlockDeadtime2L_rdfifo_data_inst_n_5
    );
u_uz_interlockDeadtime2L_rdfifo_last_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_last
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_ARESETN => AXI4_ARESETN,
      AXI4_RLAST => AXI4_RLAST,
      AXI4_RREADY => AXI4_RREADY,
      SR(0) => reset_x,
      axi4_rlast_1 => axi4_rlast_1,
      top_rd_enb => top_rd_enb
    );
u_uz_interlockDeadtime2L_rdfifo_rid_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_rdfifo_rid
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_ARESETN => AXI4_ARESETN,
      AXI4_RID(11 downto 0) => AXI4_RID(11 downto 0),
      AXI4_RREADY => AXI4_RREADY,
      Q(11 downto 0) => axi4_rid_1(11 downto 0),
      SR(0) => reset_x,
      top_rd_enb => top_rd_enb
    );
\waddr_r_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(10),
      Q => waddr_r(10),
      R => reset_x
    );
\waddr_r_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(11),
      Q => waddr_r(11),
      R => reset_x
    );
\waddr_r_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(12),
      Q => waddr_r(12),
      R => reset_x
    );
\waddr_r_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(13),
      Q => waddr_r(13),
      R => reset_x
    );
\waddr_r_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(14),
      Q => waddr_r(14),
      R => reset_x
    );
\waddr_r_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(15),
      Q => waddr_r(15),
      R => reset_x
    );
\waddr_r_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(2),
      Q => waddr_r(2),
      R => reset_x
    );
\waddr_r_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(3),
      Q => waddr_r(3),
      R => reset_x
    );
\waddr_r_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(4),
      Q => waddr_r(4),
      R => reset_x
    );
\waddr_r_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(5),
      Q => waddr_r(5),
      R => reset_x
    );
\waddr_r_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(6),
      Q => waddr_r(6),
      R => reset_x
    );
\waddr_r_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(7),
      Q => waddr_r(7),
      R => reset_x
    );
\waddr_r_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(8),
      Q => waddr_r(8),
      R => reset_x
    );
\waddr_r_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_awtransfer,
      D => axi4_waddr(9),
      Q => waddr_r(9),
      R => reset_x
    );
\waddr_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(10),
      Q => sel0(8),
      R => reset_x
    );
\waddr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(11),
      Q => sel0(9),
      R => reset_x
    );
\waddr_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(12),
      Q => sel0(10),
      R => reset_x
    );
\waddr_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(13),
      Q => sel0(11),
      R => reset_x
    );
\waddr_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(14),
      Q => sel0(12),
      R => reset_x
    );
\waddr_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(15),
      Q => sel0(13),
      R => reset_x
    );
\waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(2),
      Q => sel0(0),
      R => reset_x
    );
\waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(3),
      Q => sel0(1),
      R => reset_x
    );
\waddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(4),
      Q => sel0(2),
      R => reset_x
    );
\waddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(5),
      Q => sel0(3),
      R => reset_x
    );
\waddr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(6),
      Q => sel0(4),
      R => reset_x
    );
\waddr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(7),
      Q => sel0(5),
      R => reset_x
    );
\waddr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(8),
      Q => sel0(6),
      R => reset_x
    );
\waddr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => waddr_r(9),
      Q => sel0(7),
      R => reset_x
    );
\wdata_int_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(0),
      Q => wdata_int(0),
      R => reset_x
    );
\wdata_int_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(1),
      Q => wdata_int(1),
      R => reset_x
    );
\wdata_int_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(2),
      Q => wdata_int(2),
      R => reset_x
    );
\wdata_int_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(3),
      Q => wdata_int(3),
      R => reset_x
    );
\wdata_int_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(4),
      Q => wdata_int(4),
      R => reset_x
    );
\wdata_int_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(5),
      Q => wdata_int(5),
      R => reset_x
    );
\wdata_int_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(6),
      Q => wdata_int(6),
      R => reset_x
    );
\wdata_int_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(7),
      Q => wdata_int(7),
      R => reset_x
    );
\wdata_int_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(8),
      Q => wdata_int(8),
      R => reset_x
    );
\wdata_int_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => AXI4_WDATA(9),
      Q => wdata_int(9),
      R => reset_x
    );
\wdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(0),
      Q => \^wdata_reg[9]_0\(0),
      R => reset_x
    );
\wdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(1),
      Q => \^wdata_reg[9]_0\(1),
      R => reset_x
    );
\wdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(2),
      Q => \^wdata_reg[9]_0\(2),
      R => reset_x
    );
\wdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(3),
      Q => \^wdata_reg[9]_0\(3),
      R => reset_x
    );
\wdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(4),
      Q => \^wdata_reg[9]_0\(4),
      R => reset_x
    );
\wdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(5),
      Q => \^wdata_reg[9]_0\(5),
      R => reset_x
    );
\wdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(6),
      Q => \^wdata_reg[9]_0\(6),
      R => reset_x
    );
\wdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(7),
      Q => \^wdata_reg[9]_0\(7),
      R => reset_x
    );
\wdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(8),
      Q => \^wdata_reg[9]_0\(8),
      R => reset_x
    );
\wdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => axi4_wtransfer,
      D => wdata_int(9),
      Q => \^wdata_reg[9]_0\(9),
      R => reset_x
    );
wr_enb_1_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => wstrb_reduce_reg,
      I1 => axi4_wtransfer,
      O => w_transfer_and_wstrb
    );
wr_enb_1_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => w_transfer_and_wstrb,
      Q => top_wr_enb,
      R => reset_x
    );
wstrb_reduce: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => AXI4_WSTRB(1),
      I1 => AXI4_WSTRB(0),
      I2 => AXI4_WSTRB(3),
      I3 => AXI4_WSTRB(2),
      O => \wstrb_reduce__0\
    );
wstrb_reduce_reg_reg: unisim.vcomponents.FDRE
     port map (
      C => AXI4_ACLK,
      CE => '1',
      D => \wstrb_reduce__0\,
      Q => wstrb_reduce_reg,
      R => reset_x
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L is
  port (
    Delay_out1_reg_0 : out STD_LOGIC;
    Delay3_out1 : out STD_LOGIC;
    PipelineDelay1_out1 : out STD_LOGIC;
    PipelineDelay1_out1_0 : out STD_LOGIC;
    PipelineDelay1_out1_1 : out STD_LOGIC;
    PipelineDelay1_out1_2 : out STD_LOGIC;
    PipelineDelay1_out1_3 : out STD_LOGIC;
    PipelineDelay1_out1_4 : out STD_LOGIC;
    s1_out : out STD_LOGIC;
    s0_out : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 9 downto 0 );
    s3_out : out STD_LOGIC;
    s2_out : out STD_LOGIC;
    s5_out : out STD_LOGIC;
    s4_out : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    axi_EnableOutput : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    axi_InverseBotSwitch : in STD_LOGIC;
    Delay2_delOut_reg : in STD_LOGIC;
    S0 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 9 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_2\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_3\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_4\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_5\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_6\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_7\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_8\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L : entity is "uz_interlockDeadtime2L_src_uz_interlockDeadtime2L";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L is
  signal \^delay3_out1\ : STD_LOGIC;
  signal \^delay_out1_reg_0\ : STD_LOGIC;
  signal \GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1\ : STD_LOGIC;
  signal \GEN_LABEL3[0].u_DeadtimeModule_n_2\ : STD_LOGIC;
  signal \GEN_LABEL3[1].u_DeadtimeModule_n_2\ : STD_LOGIC;
  signal \GEN_LABEL3[2].u_DeadtimeModule_n_2\ : STD_LOGIC;
  signal \GEN_LABEL3[3].u_DeadtimeModule_n_2\ : STD_LOGIC;
  signal \GEN_LABEL3[4].u_DeadtimeModule_n_2\ : STD_LOGIC;
  signal \GEN_LABEL3[5].u_DeadtimeModule_n_2\ : STD_LOGIC;
  signal \^q\ : STD_LOGIC_VECTOR ( 9 downto 0 );
begin
  Delay3_out1 <= \^delay3_out1\;
  Delay_out1_reg_0 <= \^delay_out1_reg_0\;
  Q(9 downto 0) <= \^q\(9 downto 0);
\Delay2_out1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(0),
      Q => \^q\(0),
      R => reset_x
    );
\Delay2_out1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(1),
      Q => \^q\(1),
      R => reset_x
    );
\Delay2_out1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(2),
      Q => \^q\(2),
      R => reset_x
    );
\Delay2_out1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(3),
      Q => \^q\(3),
      R => reset_x
    );
\Delay2_out1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(4),
      Q => \^q\(4),
      R => reset_x
    );
\Delay2_out1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(5),
      Q => \^q\(5),
      R => reset_x
    );
\Delay2_out1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(6),
      Q => \^q\(6),
      R => reset_x
    );
\Delay2_out1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(7),
      Q => \^q\(7),
      R => reset_x
    );
\Delay2_out1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(8),
      Q => \^q\(8),
      R => reset_x
    );
\Delay2_out1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => D(9),
      Q => \^q\(9),
      R => reset_x
    );
Delay3_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => axi_InverseBotSwitch,
      Q => \^delay3_out1\,
      R => reset_x
    );
Delay_out1_reg: unisim.vcomponents.FDRE
     port map (
      C => IPCORE_CLK,
      CE => write_axi_enable,
      D => axi_EnableOutput,
      Q => \^delay_out1_reg_0\,
      R => reset_x
    );
\GEN_LABEL1[0].u_InverseBotSwitchModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_InverseBotSwitchModule
     port map (
      Delay3_out1 => \^delay3_out1\,
      IPCORE_CLK => IPCORE_CLK,
      PipeDelay_out1 => \GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1\,
      reset_x => reset_x,
      write_axi_enable => write_axi_enable
    );
\GEN_LABEL3[0].u_DeadtimeModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule
     port map (
      Delay2_delOut_reg_0 => Delay2_delOut_reg,
      E(0) => E(0),
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay1_out1 => PipelineDelay1_out1,
      PipelineDelay1_out1_reg_0 => \GEN_LABEL3[0].u_DeadtimeModule_n_2\,
      Q(9 downto 0) => \^q\(9 downto 0),
      S0 => S0,
      S1 => S1,
      SR(0) => SR(0),
      reset_x => reset_x,
      s0_out => s0_out,
      s0_out_0 => \^delay_out1_reg_0\,
      s0_out_1 => \GEN_LABEL3[1].u_DeadtimeModule_n_2\,
      write_axi_enable => write_axi_enable
    );
\GEN_LABEL3[1].u_DeadtimeModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_0
     port map (
      Delay2_delOut_reg_0 => Delay2_delOut_reg,
      \HDL_Counter_out1_reg[9]_0\(0) => \HDL_Counter_out1_reg[9]\(0),
      \HDL_Counter_out1_reg[9]_1\(0) => \HDL_Counter_out1_reg[9]_0\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipeDelay_out1 => \GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1\,
      PipelineDelay1_out1_0 => PipelineDelay1_out1_0,
      PipelineDelay1_out1_reg_0 => \GEN_LABEL3[1].u_DeadtimeModule_n_2\,
      Q(9 downto 0) => \^q\(9 downto 0),
      S0 => S0,
      S1 => S1,
      reset_x => reset_x,
      s1_out => s1_out,
      s1_out_0 => \^delay_out1_reg_0\,
      s1_out_1 => \GEN_LABEL3[0].u_DeadtimeModule_n_2\,
      write_axi_enable => write_axi_enable
    );
\GEN_LABEL3[2].u_DeadtimeModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_1
     port map (
      Delay2_delOut_reg_0 => Delay2_delOut_reg,
      \HDL_Counter_out1_reg[9]_0\(0) => \HDL_Counter_out1_reg[9]_1\(0),
      \HDL_Counter_out1_reg[9]_1\(0) => \HDL_Counter_out1_reg[9]_2\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay1_out1_1 => PipelineDelay1_out1_1,
      PipelineDelay1_out1_reg_0 => \GEN_LABEL3[2].u_DeadtimeModule_n_2\,
      Q(9 downto 0) => \^q\(9 downto 0),
      S2 => S2,
      S3 => S3,
      reset_x => reset_x,
      s2_out => s2_out,
      s2_out_0 => \^delay_out1_reg_0\,
      s2_out_1 => \GEN_LABEL3[3].u_DeadtimeModule_n_2\,
      write_axi_enable => write_axi_enable
    );
\GEN_LABEL3[3].u_DeadtimeModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_2
     port map (
      Delay2_delOut_reg_0 => Delay2_delOut_reg,
      \HDL_Counter_out1_reg[9]_0\(0) => \HDL_Counter_out1_reg[9]_3\(0),
      \HDL_Counter_out1_reg[9]_1\(0) => \HDL_Counter_out1_reg[9]_4\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipeDelay_out1 => \GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1\,
      PipelineDelay1_out1_2 => PipelineDelay1_out1_2,
      PipelineDelay1_out1_reg_0 => \GEN_LABEL3[3].u_DeadtimeModule_n_2\,
      Q(9 downto 0) => \^q\(9 downto 0),
      S2 => S2,
      S3 => S3,
      reset_x => reset_x,
      s3_out => s3_out,
      s3_out_0 => \^delay_out1_reg_0\,
      s3_out_1 => \GEN_LABEL3[2].u_DeadtimeModule_n_2\,
      write_axi_enable => write_axi_enable
    );
\GEN_LABEL3[4].u_DeadtimeModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_3
     port map (
      Delay2_delOut_reg_0 => Delay2_delOut_reg,
      \HDL_Counter_out1_reg[9]_0\(0) => \HDL_Counter_out1_reg[9]_5\(0),
      \HDL_Counter_out1_reg[9]_1\(0) => \HDL_Counter_out1_reg[9]_6\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay1_out1_3 => PipelineDelay1_out1_3,
      PipelineDelay1_out1_reg_0 => \GEN_LABEL3[4].u_DeadtimeModule_n_2\,
      Q(9 downto 0) => \^q\(9 downto 0),
      S4 => S4,
      S5 => S5,
      reset_x => reset_x,
      s4_out => s4_out,
      s4_out_0 => \^delay_out1_reg_0\,
      s4_out_1 => \GEN_LABEL3[5].u_DeadtimeModule_n_2\,
      write_axi_enable => write_axi_enable
    );
\GEN_LABEL3[5].u_DeadtimeModule\: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_DeadtimeModule_4
     port map (
      Delay2_delOut_reg_0 => Delay2_delOut_reg,
      \HDL_Counter_out1_reg[9]_0\(0) => \HDL_Counter_out1_reg[9]_7\(0),
      \HDL_Counter_out1_reg[9]_1\(0) => \HDL_Counter_out1_reg[9]_8\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipeDelay_out1 => \GEN_LABEL1[2].u_InverseBotSwitchModule/PipeDelay_out1\,
      PipelineDelay1_out1_4 => PipelineDelay1_out1_4,
      PipelineDelay1_out1_reg_0 => \GEN_LABEL3[5].u_DeadtimeModule_n_2\,
      Q(9 downto 0) => \^q\(9 downto 0),
      S4 => S4,
      S5 => S5,
      reset_x => reset_x,
      s5_out => s5_out,
      s5_out_0 => \^delay_out1_reg_0\,
      s5_out_1 => \GEN_LABEL3[4].u_DeadtimeModule_n_2\,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4 is
  port (
    out_valid_reg : out STD_LOGIC;
    write_axi_enable : out STD_LOGIC;
    axi_EnableOutput : out STD_LOGIC;
    axi_InverseBotSwitch : out STD_LOGIC;
    AXI4_RLAST : out STD_LOGIC;
    soft_reset : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_ARREADY : out STD_LOGIC;
    AXI4_AWREADY : out STD_LOGIC;
    reset_in : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_4 : out STD_LOGIC;
    data_reg_axi_enable_1_1_reg_5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_8 : out STD_LOGIC_VECTOR ( 0 to 0 );
    data_reg_axi_enable_1_1_reg_9 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \data_reg_axi_DelayCycles_1_1_reg[9]\ : out STD_LOGIC_VECTOR ( 9 downto 0 );
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_BID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_ACLK : in STD_LOGIC;
    reset_x : in STD_LOGIC;
    Delay3_out1 : in STD_LOGIC;
    read_reg_axi_fb_enable_reg : in STD_LOGIC;
    AXI4_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_RREADY : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_BREADY : in STD_LOGIC;
    AXI4_ARVALID : in STD_LOGIC;
    AXI4_WVALID : in STD_LOGIC;
    AXI4_WLAST : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_ARLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S0 : in STD_LOGIC;
    PipelineDelay1_out1 : in STD_LOGIC;
    PipelineDelay1_out1_0 : in STD_LOGIC;
    PipelineDelay1_out1_1 : in STD_LOGIC;
    PipelineDelay1_out1_2 : in STD_LOGIC;
    PipelineDelay1_out1_3 : in STD_LOGIC;
    PipelineDelay1_out1_4 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    AXI4_ARBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_AWBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_WDATA : in STD_LOGIC_VECTOR ( 9 downto 0 );
    \read_reg_axi_fb_DelayCycles_reg[9]\ : in STD_LOGIC_VECTOR ( 9 downto 0 );
    AXI4_ARID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_AWID : in STD_LOGIC_VECTOR ( 11 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4 : entity is "uz_interlockDeadtime2L_axi4";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4 is
  signal \^axi_enableoutput\ : STD_LOGIC;
  signal \^axi_inversebotswitch\ : STD_LOGIC;
  signal read_reg_axi_fb_DelayCycles : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal read_reg_axi_fb_InverseBotSwitch : STD_LOGIC;
  signal read_reg_axi_fb_enable : STD_LOGIC;
  signal read_reg_ip_timestamp : STD_LOGIC_VECTOR ( 29 to 29 );
  signal reg_enb_axi_DelayCycles_1_1 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_10 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_11 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_12 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_13 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_14 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_15 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_16 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_17 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_18 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_19 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_20 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_21 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_module_inst_n_9 : STD_LOGIC;
  signal \^write_axi_enable\ : STD_LOGIC;
begin
  axi_EnableOutput <= \^axi_enableoutput\;
  axi_InverseBotSwitch <= \^axi_inversebotswitch\;
  write_axi_enable <= \^write_axi_enable\;
u_uz_interlockDeadtime2L_addr_decoder_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_addr_decoder
     port map (
      AXI4_ACLK => AXI4_ACLK,
      Delay3_out1 => Delay3_out1,
      E(0) => E(0),
      PipelineDelay1_out1 => PipelineDelay1_out1,
      PipelineDelay1_out1_0 => PipelineDelay1_out1_0,
      PipelineDelay1_out1_1 => PipelineDelay1_out1_1,
      PipelineDelay1_out1_2 => PipelineDelay1_out1_2,
      PipelineDelay1_out1_3 => PipelineDelay1_out1_3,
      PipelineDelay1_out1_4 => PipelineDelay1_out1_4,
      Q(9) => u_uz_interlockDeadtime2L_axi4_module_inst_n_9,
      Q(8) => u_uz_interlockDeadtime2L_axi4_module_inst_n_10,
      Q(7) => u_uz_interlockDeadtime2L_axi4_module_inst_n_11,
      Q(6) => u_uz_interlockDeadtime2L_axi4_module_inst_n_12,
      Q(5) => u_uz_interlockDeadtime2L_axi4_module_inst_n_13,
      Q(4) => u_uz_interlockDeadtime2L_axi4_module_inst_n_14,
      Q(3) => u_uz_interlockDeadtime2L_axi4_module_inst_n_15,
      Q(2) => u_uz_interlockDeadtime2L_axi4_module_inst_n_16,
      Q(1) => u_uz_interlockDeadtime2L_axi4_module_inst_n_17,
      Q(0) => u_uz_interlockDeadtime2L_axi4_module_inst_n_18,
      S0 => S0,
      S1 => S1,
      S2 => S2,
      S3 => S3,
      S4 => S4,
      S5 => S5,
      SR(0) => SR(0),
      axi_EnableOutput => \^axi_enableoutput\,
      axi_InverseBotSwitch => \^axi_inversebotswitch\,
      \data_reg_axi_DelayCycles_1_1_reg[9]_0\(9 downto 0) => \data_reg_axi_DelayCycles_1_1_reg[9]\(9 downto 0),
      \data_reg_axi_DelayCycles_1_1_reg[9]_1\(0) => reg_enb_axi_DelayCycles_1_1,
      data_reg_axi_EnableOutput_1_1_reg_0 => u_uz_interlockDeadtime2L_axi4_module_inst_n_20,
      data_reg_axi_InverseBotSwitch_1_1_reg_0 => u_uz_interlockDeadtime2L_axi4_module_inst_n_21,
      data_reg_axi_enable_1_1_reg_0 => \^write_axi_enable\,
      data_reg_axi_enable_1_1_reg_1(0) => data_reg_axi_enable_1_1_reg(0),
      data_reg_axi_enable_1_1_reg_10(0) => data_reg_axi_enable_1_1_reg_8(0),
      data_reg_axi_enable_1_1_reg_11(0) => data_reg_axi_enable_1_1_reg_9(0),
      data_reg_axi_enable_1_1_reg_12 => u_uz_interlockDeadtime2L_axi4_module_inst_n_19,
      data_reg_axi_enable_1_1_reg_2(0) => data_reg_axi_enable_1_1_reg_0(0),
      data_reg_axi_enable_1_1_reg_3(0) => data_reg_axi_enable_1_1_reg_1(0),
      data_reg_axi_enable_1_1_reg_4(0) => data_reg_axi_enable_1_1_reg_2(0),
      data_reg_axi_enable_1_1_reg_5(0) => data_reg_axi_enable_1_1_reg_3(0),
      data_reg_axi_enable_1_1_reg_6 => data_reg_axi_enable_1_1_reg_4,
      data_reg_axi_enable_1_1_reg_7(0) => data_reg_axi_enable_1_1_reg_5(0),
      data_reg_axi_enable_1_1_reg_8(0) => data_reg_axi_enable_1_1_reg_6(0),
      data_reg_axi_enable_1_1_reg_9(0) => data_reg_axi_enable_1_1_reg_7(0),
      \read_reg_axi_fb_DelayCycles_reg[9]_0\(9 downto 0) => read_reg_axi_fb_DelayCycles(9 downto 0),
      \read_reg_axi_fb_DelayCycles_reg[9]_1\(9 downto 0) => \read_reg_axi_fb_DelayCycles_reg[9]\(9 downto 0),
      read_reg_axi_fb_InverseBotSwitch => read_reg_axi_fb_InverseBotSwitch,
      read_reg_axi_fb_enable => read_reg_axi_fb_enable,
      read_reg_axi_fb_enable_reg_0 => read_reg_axi_fb_enable_reg,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(29),
      reset_x => reset_x
    );
u_uz_interlockDeadtime2L_axi4_module_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4_module
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_ARADDR(13 downto 0) => AXI4_ARADDR(13 downto 0),
      AXI4_ARBURST(1 downto 0) => AXI4_ARBURST(1 downto 0),
      AXI4_ARESETN => AXI4_ARESETN,
      AXI4_ARID(11 downto 0) => AXI4_ARID(11 downto 0),
      AXI4_ARLEN(7 downto 0) => AXI4_ARLEN(7 downto 0),
      AXI4_ARREADY => AXI4_ARREADY,
      AXI4_ARVALID => AXI4_ARVALID,
      AXI4_AWADDR(13 downto 0) => AXI4_AWADDR(13 downto 0),
      AXI4_AWBURST(1 downto 0) => AXI4_AWBURST(1 downto 0),
      AXI4_AWID(11 downto 0) => AXI4_AWID(11 downto 0),
      AXI4_AWREADY => AXI4_AWREADY,
      AXI4_AWVALID => AXI4_AWVALID,
      AXI4_BID(11 downto 0) => AXI4_BID(11 downto 0),
      AXI4_BREADY => AXI4_BREADY,
      AXI4_RDATA(31 downto 0) => AXI4_RDATA(31 downto 0),
      AXI4_RID(11 downto 0) => AXI4_RID(11 downto 0),
      AXI4_RLAST => AXI4_RLAST,
      AXI4_RREADY => AXI4_RREADY,
      AXI4_WDATA(9 downto 0) => AXI4_WDATA(9 downto 0),
      AXI4_WLAST => AXI4_WLAST,
      AXI4_WSTRB(3 downto 0) => AXI4_WSTRB(3 downto 0),
      AXI4_WVALID => AXI4_WVALID,
      IPCORE_RESETN => IPCORE_RESETN,
      Q(1 downto 0) => Q(1 downto 0),
      \axi4_raddr_reg[2]_0\(0) => reg_enb_axi_DelayCycles_1_1,
      axi_EnableOutput => \^axi_enableoutput\,
      axi_InverseBotSwitch => \^axi_inversebotswitch\,
      \data_int_reg[1]\(9 downto 0) => read_reg_axi_fb_DelayCycles(9 downto 0),
      out_valid_reg => out_valid_reg,
      read_reg_axi_fb_InverseBotSwitch => read_reg_axi_fb_InverseBotSwitch,
      read_reg_axi_fb_enable => read_reg_axi_fb_enable,
      read_reg_ip_timestamp(0) => read_reg_ip_timestamp(29),
      reset_in => reset_in,
      soft_reset => soft_reset,
      \wdata_reg[0]_0\ => u_uz_interlockDeadtime2L_axi4_module_inst_n_19,
      \wdata_reg[0]_1\ => u_uz_interlockDeadtime2L_axi4_module_inst_n_20,
      \wdata_reg[0]_2\ => u_uz_interlockDeadtime2L_axi4_module_inst_n_21,
      \wdata_reg[9]_0\(9) => u_uz_interlockDeadtime2L_axi4_module_inst_n_9,
      \wdata_reg[9]_0\(8) => u_uz_interlockDeadtime2L_axi4_module_inst_n_10,
      \wdata_reg[9]_0\(7) => u_uz_interlockDeadtime2L_axi4_module_inst_n_11,
      \wdata_reg[9]_0\(6) => u_uz_interlockDeadtime2L_axi4_module_inst_n_12,
      \wdata_reg[9]_0\(5) => u_uz_interlockDeadtime2L_axi4_module_inst_n_13,
      \wdata_reg[9]_0\(4) => u_uz_interlockDeadtime2L_axi4_module_inst_n_14,
      \wdata_reg[9]_0\(3) => u_uz_interlockDeadtime2L_axi4_module_inst_n_15,
      \wdata_reg[9]_0\(2) => u_uz_interlockDeadtime2L_axi4_module_inst_n_16,
      \wdata_reg[9]_0\(1) => u_uz_interlockDeadtime2L_axi4_module_inst_n_17,
      \wdata_reg[9]_0\(0) => u_uz_interlockDeadtime2L_axi4_module_inst_n_18,
      write_axi_enable => \^write_axi_enable\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut is
  port (
    Delay_out1_reg : out STD_LOGIC;
    Delay3_out1 : out STD_LOGIC;
    PipelineDelay1_out1 : out STD_LOGIC;
    PipelineDelay1_out1_0 : out STD_LOGIC;
    PipelineDelay1_out1_1 : out STD_LOGIC;
    PipelineDelay1_out1_2 : out STD_LOGIC;
    PipelineDelay1_out1_3 : out STD_LOGIC;
    PipelineDelay1_out1_4 : out STD_LOGIC;
    s1_out : out STD_LOGIC;
    s0_out : out STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 9 downto 0 );
    s3_out : out STD_LOGIC;
    s2_out : out STD_LOGIC;
    s5_out : out STD_LOGIC;
    s4_out : out STD_LOGIC;
    reset_x : in STD_LOGIC;
    write_axi_enable : in STD_LOGIC;
    axi_EnableOutput : in STD_LOGIC;
    IPCORE_CLK : in STD_LOGIC;
    axi_InverseBotSwitch : in STD_LOGIC;
    Delay2_delOut_reg : in STD_LOGIC;
    S0 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 9 downto 0 );
    SR : in STD_LOGIC_VECTOR ( 0 to 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_2\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_3\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_4\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_5\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_6\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_7\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \HDL_Counter_out1_reg[9]_8\ : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut : entity is "uz_interlockDeadtime2L_dut";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut is
begin
u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L
     port map (
      D(9 downto 0) => D(9 downto 0),
      Delay2_delOut_reg => Delay2_delOut_reg,
      Delay3_out1 => Delay3_out1,
      Delay_out1_reg_0 => Delay_out1_reg,
      E(0) => E(0),
      \HDL_Counter_out1_reg[9]\(0) => \HDL_Counter_out1_reg[9]\(0),
      \HDL_Counter_out1_reg[9]_0\(0) => \HDL_Counter_out1_reg[9]_0\(0),
      \HDL_Counter_out1_reg[9]_1\(0) => \HDL_Counter_out1_reg[9]_1\(0),
      \HDL_Counter_out1_reg[9]_2\(0) => \HDL_Counter_out1_reg[9]_2\(0),
      \HDL_Counter_out1_reg[9]_3\(0) => \HDL_Counter_out1_reg[9]_3\(0),
      \HDL_Counter_out1_reg[9]_4\(0) => \HDL_Counter_out1_reg[9]_4\(0),
      \HDL_Counter_out1_reg[9]_5\(0) => \HDL_Counter_out1_reg[9]_5\(0),
      \HDL_Counter_out1_reg[9]_6\(0) => \HDL_Counter_out1_reg[9]_6\(0),
      \HDL_Counter_out1_reg[9]_7\(0) => \HDL_Counter_out1_reg[9]_7\(0),
      \HDL_Counter_out1_reg[9]_8\(0) => \HDL_Counter_out1_reg[9]_8\(0),
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay1_out1 => PipelineDelay1_out1,
      PipelineDelay1_out1_0 => PipelineDelay1_out1_0,
      PipelineDelay1_out1_1 => PipelineDelay1_out1_1,
      PipelineDelay1_out1_2 => PipelineDelay1_out1_2,
      PipelineDelay1_out1_3 => PipelineDelay1_out1_3,
      PipelineDelay1_out1_4 => PipelineDelay1_out1_4,
      Q(9 downto 0) => Q(9 downto 0),
      S0 => S0,
      S1 => S1,
      S2 => S2,
      S3 => S3,
      S4 => S4,
      S5 => S5,
      SR(0) => SR(0),
      axi_EnableOutput => axi_EnableOutput,
      axi_InverseBotSwitch => axi_InverseBotSwitch,
      reset_x => reset_x,
      s0_out => s0_out,
      s1_out => s1_out,
      s2_out => s2_out,
      s3_out => s3_out,
      s4_out => s4_out,
      s5_out => s5_out,
      write_axi_enable => write_axi_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L is
  port (
    AXI4_BVALID : out STD_LOGIC;
    AXI4_WREADY : out STD_LOGIC;
    enableFB : out STD_LOGIC;
    out_valid_reg : out STD_LOGIC;
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_BID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_ARREADY : out STD_LOGIC;
    AXI4_AWREADY : out STD_LOGIC;
    s1_out : out STD_LOGIC;
    s0_out : out STD_LOGIC;
    s3_out : out STD_LOGIC;
    s2_out : out STD_LOGIC;
    s5_out : out STD_LOGIC;
    s4_out : out STD_LOGIC;
    AXI4_RLAST : out STD_LOGIC;
    AXI4_ACLK : in STD_LOGIC;
    AXI4_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IPCORE_CLK : in STD_LOGIC;
    AXI4_WDATA : in STD_LOGIC_VECTOR ( 9 downto 0 );
    AXI4_ARID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_AWID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_ARADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_AWADDR : in STD_LOGIC_VECTOR ( 13 downto 0 );
    AXI4_RREADY : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_BREADY : in STD_LOGIC;
    AXI4_ARVALID : in STD_LOGIC;
    AXI4_WVALID : in STD_LOGIC;
    AXI4_WLAST : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_ARLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    S0 : in STD_LOGIC;
    S1 : in STD_LOGIC;
    S2 : in STD_LOGIC;
    S3 : in STD_LOGIC;
    S4 : in STD_LOGIC;
    S5 : in STD_LOGIC;
    AXI4_ARBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_AWBURST : in STD_LOGIC_VECTOR ( 1 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L : entity is "uz_interlockDeadtime2L";
end zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L is
  signal Delay2_out1 : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal Delay3_out1 : STD_LOGIC;
  signal axi_DelayCycles : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal axi_EnableOutput : STD_LOGIC;
  signal axi_InverseBotSwitch : STD_LOGIC;
  signal \^enablefb\ : STD_LOGIC;
  signal reset_in : STD_LOGIC;
  signal reset_x : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_12 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_13 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_14 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_15 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_16 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_17 : STD_LOGIC;
  signal u_uz_interlockDeadtime2L_axi4_inst_n_18 : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_axi4_module_inst/soft_reset\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/PipelineDelay1_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/PipelineDelay1_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/PipelineDelay1_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/PipelineDelay1_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/PipelineDelay1_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/HDL_Counter_out1\ : STD_LOGIC;
  signal \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/PipelineDelay1_out1\ : STD_LOGIC;
  signal write_axi_enable : STD_LOGIC;
begin
  enableFB <= \^enablefb\;
u_uz_interlockDeadtime2L_axi4_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_axi4
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_ARADDR(13 downto 0) => AXI4_ARADDR(13 downto 0),
      AXI4_ARBURST(1 downto 0) => AXI4_ARBURST(1 downto 0),
      AXI4_ARESETN => AXI4_ARESETN,
      AXI4_ARID(11 downto 0) => AXI4_ARID(11 downto 0),
      AXI4_ARLEN(7 downto 0) => AXI4_ARLEN(7 downto 0),
      AXI4_ARREADY => AXI4_ARREADY,
      AXI4_ARVALID => AXI4_ARVALID,
      AXI4_AWADDR(13 downto 0) => AXI4_AWADDR(13 downto 0),
      AXI4_AWBURST(1 downto 0) => AXI4_AWBURST(1 downto 0),
      AXI4_AWID(11 downto 0) => AXI4_AWID(11 downto 0),
      AXI4_AWREADY => AXI4_AWREADY,
      AXI4_AWVALID => AXI4_AWVALID,
      AXI4_BID(11 downto 0) => AXI4_BID(11 downto 0),
      AXI4_BREADY => AXI4_BREADY,
      AXI4_RDATA(31 downto 0) => AXI4_RDATA(31 downto 0),
      AXI4_RID(11 downto 0) => AXI4_RID(11 downto 0),
      AXI4_RLAST => AXI4_RLAST,
      AXI4_RREADY => AXI4_RREADY,
      AXI4_WDATA(9 downto 0) => AXI4_WDATA(9 downto 0),
      AXI4_WLAST => AXI4_WLAST,
      AXI4_WSTRB(3 downto 0) => AXI4_WSTRB(3 downto 0),
      AXI4_WVALID => AXI4_WVALID,
      Delay3_out1 => Delay3_out1,
      E(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/HDL_Counter_out1\,
      IPCORE_RESETN => IPCORE_RESETN,
      PipelineDelay1_out1 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_0 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_1 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_2 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_3 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_4 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/PipelineDelay1_out1\,
      Q(1) => AXI4_BVALID,
      Q(0) => AXI4_WREADY,
      S0 => S0,
      S1 => S1,
      S2 => S2,
      S3 => S3,
      S4 => S4,
      S5 => S5,
      SR(0) => u_uz_interlockDeadtime2L_axi4_inst_n_12,
      axi_EnableOutput => axi_EnableOutput,
      axi_InverseBotSwitch => axi_InverseBotSwitch,
      \data_reg_axi_DelayCycles_1_1_reg[9]\(9 downto 0) => axi_DelayCycles(9 downto 0),
      data_reg_axi_enable_1_1_reg(0) => u_uz_interlockDeadtime2L_axi4_inst_n_13,
      data_reg_axi_enable_1_1_reg_0(0) => u_uz_interlockDeadtime2L_axi4_inst_n_14,
      data_reg_axi_enable_1_1_reg_1(0) => u_uz_interlockDeadtime2L_axi4_inst_n_15,
      data_reg_axi_enable_1_1_reg_2(0) => u_uz_interlockDeadtime2L_axi4_inst_n_16,
      data_reg_axi_enable_1_1_reg_3(0) => u_uz_interlockDeadtime2L_axi4_inst_n_17,
      data_reg_axi_enable_1_1_reg_4 => u_uz_interlockDeadtime2L_axi4_inst_n_18,
      data_reg_axi_enable_1_1_reg_5(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/HDL_Counter_out1\,
      data_reg_axi_enable_1_1_reg_6(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/HDL_Counter_out1\,
      data_reg_axi_enable_1_1_reg_7(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/HDL_Counter_out1\,
      data_reg_axi_enable_1_1_reg_8(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/HDL_Counter_out1\,
      data_reg_axi_enable_1_1_reg_9(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/HDL_Counter_out1\,
      out_valid_reg => out_valid_reg,
      \read_reg_axi_fb_DelayCycles_reg[9]\(9 downto 0) => Delay2_out1(9 downto 0),
      read_reg_axi_fb_enable_reg => \^enablefb\,
      reset_in => reset_in,
      reset_x => reset_x,
      soft_reset => \u_uz_interlockDeadtime2L_axi4_module_inst/soft_reset\,
      write_axi_enable => write_axi_enable
    );
u_uz_interlockDeadtime2L_dut_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_dut
     port map (
      D(9 downto 0) => axi_DelayCycles(9 downto 0),
      Delay2_delOut_reg => u_uz_interlockDeadtime2L_axi4_inst_n_18,
      Delay3_out1 => Delay3_out1,
      Delay_out1_reg => \^enablefb\,
      E(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/HDL_Counter_out1\,
      \HDL_Counter_out1_reg[9]\(0) => u_uz_interlockDeadtime2L_axi4_inst_n_13,
      \HDL_Counter_out1_reg[9]_0\(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/HDL_Counter_out1\,
      \HDL_Counter_out1_reg[9]_1\(0) => u_uz_interlockDeadtime2L_axi4_inst_n_14,
      \HDL_Counter_out1_reg[9]_2\(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/HDL_Counter_out1\,
      \HDL_Counter_out1_reg[9]_3\(0) => u_uz_interlockDeadtime2L_axi4_inst_n_15,
      \HDL_Counter_out1_reg[9]_4\(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/HDL_Counter_out1\,
      \HDL_Counter_out1_reg[9]_5\(0) => u_uz_interlockDeadtime2L_axi4_inst_n_16,
      \HDL_Counter_out1_reg[9]_6\(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/HDL_Counter_out1\,
      \HDL_Counter_out1_reg[9]_7\(0) => u_uz_interlockDeadtime2L_axi4_inst_n_17,
      \HDL_Counter_out1_reg[9]_8\(0) => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/HDL_Counter_out1\,
      IPCORE_CLK => IPCORE_CLK,
      PipelineDelay1_out1 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[0].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_0 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[1].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_1 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[2].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_2 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[3].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_3 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[4].u_DeadtimeModule/PipelineDelay1_out1\,
      PipelineDelay1_out1_4 => \u_uz_interlockDeadtime2L_src_uz_interlockDeadtime2L/GEN_LABEL3[5].u_DeadtimeModule/PipelineDelay1_out1\,
      Q(9 downto 0) => Delay2_out1(9 downto 0),
      S0 => S0,
      S1 => S1,
      S2 => S2,
      S3 => S3,
      S4 => S4,
      S5 => S5,
      SR(0) => u_uz_interlockDeadtime2L_axi4_inst_n_12,
      axi_EnableOutput => axi_EnableOutput,
      axi_InverseBotSwitch => axi_InverseBotSwitch,
      reset_x => reset_x,
      s0_out => s0_out,
      s1_out => s1_out,
      s2_out => s2_out,
      s3_out => s3_out,
      s4_out => s4_out,
      s5_out => s5_out,
      write_axi_enable => write_axi_enable
    );
u_uz_interlockDeadtime2L_reset_sync_inst: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L_reset_sync
     port map (
      AXI4_ARESETN => AXI4_ARESETN,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      reset_in => reset_in,
      reset_x => reset_x,
      soft_reset => \u_uz_interlockDeadtime2L_axi4_module_inst/soft_reset\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_uz_interlockDeadtime_0_0 is
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
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_uz_interlockDeadtime_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_uz_interlockDeadtime_0_0 : entity is "zusys_uz_interlockDeadtime_0_0,uz_interlockDeadtime2L,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_uz_interlockDeadtime_0_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of zusys_uz_interlockDeadtime_0_0 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of zusys_uz_interlockDeadtime_0_0 : entity is "uz_interlockDeadtime2L,Vivado 2020.1.1";
end zusys_uz_interlockDeadtime_0_0;

architecture STRUCTURE of zusys_uz_interlockDeadtime_0_0 is
  signal \<const0>\ : STD_LOGIC;
  attribute x_interface_info : string;
  attribute x_interface_info of AXI4_ACLK : signal is "xilinx.com:signal:clock:1.0 AXI4_signal_clock CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of AXI4_ACLK : signal is "XIL_INTERFACENAME AXI4_signal_clock, ASSOCIATED_BUSIF AXI4, ASSOCIATED_RESET AXI4_ARESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of AXI4_ARESETN : signal is "xilinx.com:signal:reset:1.0 AXI4_signal_reset RST";
  attribute x_interface_parameter of AXI4_ARESETN : signal is "XIL_INTERFACENAME AXI4_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of AXI4_ARLOCK : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARLOCK";
  attribute x_interface_info of AXI4_ARREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARREADY";
  attribute x_interface_info of AXI4_ARVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARVALID";
  attribute x_interface_info of AXI4_AWLOCK : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWLOCK";
  attribute x_interface_info of AXI4_AWREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWREADY";
  attribute x_interface_info of AXI4_AWVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWVALID";
  attribute x_interface_info of AXI4_BREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4 BREADY";
  attribute x_interface_info of AXI4_BVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4 BVALID";
  attribute x_interface_info of AXI4_RLAST : signal is "xilinx.com:interface:aximm:1.0 AXI4 RLAST";
  attribute x_interface_info of AXI4_RREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4 RREADY";
  attribute x_interface_info of AXI4_RVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4 RVALID";
  attribute x_interface_info of AXI4_WLAST : signal is "xilinx.com:interface:aximm:1.0 AXI4 WLAST";
  attribute x_interface_info of AXI4_WREADY : signal is "xilinx.com:interface:aximm:1.0 AXI4 WREADY";
  attribute x_interface_info of AXI4_WVALID : signal is "xilinx.com:interface:aximm:1.0 AXI4 WVALID";
  attribute x_interface_info of IPCORE_CLK : signal is "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK";
  attribute x_interface_parameter of IPCORE_CLK : signal is "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  attribute x_interface_info of IPCORE_RESETN : signal is "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST";
  attribute x_interface_parameter of IPCORE_RESETN : signal is "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of AXI4_ARADDR : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARADDR";
  attribute x_interface_info of AXI4_ARBURST : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARBURST";
  attribute x_interface_info of AXI4_ARCACHE : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARCACHE";
  attribute x_interface_info of AXI4_ARID : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARID";
  attribute x_interface_info of AXI4_ARLEN : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARLEN";
  attribute x_interface_info of AXI4_ARPROT : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARPROT";
  attribute x_interface_info of AXI4_ARSIZE : signal is "xilinx.com:interface:aximm:1.0 AXI4 ARSIZE";
  attribute x_interface_info of AXI4_AWADDR : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWADDR";
  attribute x_interface_info of AXI4_AWBURST : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWBURST";
  attribute x_interface_info of AXI4_AWCACHE : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWCACHE";
  attribute x_interface_info of AXI4_AWID : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWID";
  attribute x_interface_parameter of AXI4_AWID : signal is "XIL_INTERFACENAME AXI4, DATA_WIDTH 32, PROTOCOL AXI4, FREQ_HZ 100000000, ID_WIDTH 12, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 1, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 1, NUM_READ_OUTSTANDING 2, NUM_WRITE_OUTSTANDING 2, MAX_BURST_LENGTH 256, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute x_interface_info of AXI4_AWLEN : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWLEN";
  attribute x_interface_info of AXI4_AWPROT : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWPROT";
  attribute x_interface_info of AXI4_AWSIZE : signal is "xilinx.com:interface:aximm:1.0 AXI4 AWSIZE";
  attribute x_interface_info of AXI4_BID : signal is "xilinx.com:interface:aximm:1.0 AXI4 BID";
  attribute x_interface_info of AXI4_BRESP : signal is "xilinx.com:interface:aximm:1.0 AXI4 BRESP";
  attribute x_interface_info of AXI4_RDATA : signal is "xilinx.com:interface:aximm:1.0 AXI4 RDATA";
  attribute x_interface_info of AXI4_RID : signal is "xilinx.com:interface:aximm:1.0 AXI4 RID";
  attribute x_interface_info of AXI4_RRESP : signal is "xilinx.com:interface:aximm:1.0 AXI4 RRESP";
  attribute x_interface_info of AXI4_WDATA : signal is "xilinx.com:interface:aximm:1.0 AXI4 WDATA";
  attribute x_interface_info of AXI4_WSTRB : signal is "xilinx.com:interface:aximm:1.0 AXI4 WSTRB";
begin
  AXI4_BRESP(1) <= \<const0>\;
  AXI4_BRESP(0) <= \<const0>\;
  AXI4_RRESP(1) <= \<const0>\;
  AXI4_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.zusys_uz_interlockDeadtime_0_0_uz_interlockDeadtime2L
     port map (
      AXI4_ACLK => AXI4_ACLK,
      AXI4_ARADDR(13 downto 0) => AXI4_ARADDR(15 downto 2),
      AXI4_ARBURST(1 downto 0) => AXI4_ARBURST(1 downto 0),
      AXI4_ARESETN => AXI4_ARESETN,
      AXI4_ARID(11 downto 0) => AXI4_ARID(11 downto 0),
      AXI4_ARLEN(7 downto 0) => AXI4_ARLEN(7 downto 0),
      AXI4_ARREADY => AXI4_ARREADY,
      AXI4_ARVALID => AXI4_ARVALID,
      AXI4_AWADDR(13 downto 0) => AXI4_AWADDR(15 downto 2),
      AXI4_AWBURST(1 downto 0) => AXI4_AWBURST(1 downto 0),
      AXI4_AWID(11 downto 0) => AXI4_AWID(11 downto 0),
      AXI4_AWREADY => AXI4_AWREADY,
      AXI4_AWVALID => AXI4_AWVALID,
      AXI4_BID(11 downto 0) => AXI4_BID(11 downto 0),
      AXI4_BREADY => AXI4_BREADY,
      AXI4_BVALID => AXI4_BVALID,
      AXI4_RDATA(31 downto 0) => AXI4_RDATA(31 downto 0),
      AXI4_RID(11 downto 0) => AXI4_RID(11 downto 0),
      AXI4_RLAST => AXI4_RLAST,
      AXI4_RREADY => AXI4_RREADY,
      AXI4_WDATA(9 downto 0) => AXI4_WDATA(9 downto 0),
      AXI4_WLAST => AXI4_WLAST,
      AXI4_WREADY => AXI4_WREADY,
      AXI4_WSTRB(3 downto 0) => AXI4_WSTRB(3 downto 0),
      AXI4_WVALID => AXI4_WVALID,
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      S0 => S0,
      S1 => S1,
      S2 => S2,
      S3 => S3,
      S4 => S4,
      S5 => S5,
      enableFB => enableFB,
      out_valid_reg => AXI4_RVALID,
      s0_out => s0_out,
      s1_out => s1_out,
      s2_out => s2_out,
      s3_out => s3_out,
      s4_out => s4_out,
      s5_out => s5_out
    );
end STRUCTURE;
