// (c) Copyright 1995-2022 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:ip:sc_switchboard:1.0
// IP Revision: 6

`timescale 1ns/1ps

(* DowngradeIPIdentifiedWarnings = "yes" *)
module bd_2abc_awsw_0 (
  aclk,
  aclken,
  s_sc_send,
  s_sc_req,
  s_sc_info,
  s_sc_payld,
  s_sc_recv,
  m_sc_recv,
  m_sc_send,
  m_sc_req,
  m_sc_info,
  m_sc_payld
);

(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME aclk, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, ASSOCIATED_BUSIF M00_SC:M01_SC:M02_SC:M03_SC:M04_SC:M05_SC:M06_SC:M07_SC:M08_SC:M09_SC:M10_SC:M11_SC:M12_SC:M13_SC:M14_SC:M15_SC:S00_SC:S01_SC:S02_SC:S03_SC:S04_SC:S05_SC:S06_SC:S07_SC:S08_SC:S09_SC:S10_SC:S11_SC:S12_SC:S13_SC:S14_SC:S15_SC, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 aclk CLK" *)
input wire aclk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME aclken, POLARITY ACTIVE_LOW" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clockenable:1.0 aclken CE" *)
input wire aclken;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 S00_SC SEND" *)
input wire [14 : 0] s_sc_send;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 S00_SC REQ" *)
input wire [14 : 0] s_sc_req;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 S00_SC INFO" *)
input wire [14 : 0] s_sc_info;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 S00_SC PAYLD" *)
input wire [178 : 0] s_sc_payld;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S00_SC, BRIDGES M00_SC:M01_SC:M02_SC:M03_SC:M04_SC:M05_SC:M06_SC:M07_SC:M08_SC:M09_SC:M10_SC:M11_SC:M12_SC:M13_SC:M14_SC:M15_SC" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 S00_SC RECV" *)
output wire [14 : 0] s_sc_recv;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 M00_SC RECV [0:0] [0:0], xilinx.com:interface:sc:1.0 M01_SC RECV [0:0] [1:1], xilinx.com:interface:sc:1.0 M02_SC RECV [0:0] [2:2], xilinx.com:interface:sc:1.0 M03_SC RECV [0:0] [3:3], xilinx.com:interface:sc:1.0 M04_SC RECV [0:0] [4:4], xilinx.com:interface:sc:1.0 M05_SC RECV [0:0] [5:5], xilinx.com:interface:sc:1.0 M06_SC RECV [0:0] [6:6], xilinx.com:interface:sc:1.0 M07_SC RECV [0:0] [7:7], xilinx.com:interface:sc:1.0 M08_SC RECV [0:0] [8:8], xilinx.com:interface:sc\
:1.0 M09_SC RECV [0:0] [9:9], xilinx.com:interface:sc:1.0 M10_SC RECV [0:0] [10:10], xilinx.com:interface:sc:1.0 M11_SC RECV [0:0] [11:11], xilinx.com:interface:sc:1.0 M12_SC RECV [0:0] [12:12], xilinx.com:interface:sc:1.0 M13_SC RECV [0:0] [13:13], xilinx.com:interface:sc:1.0 M14_SC RECV [0:0] [14:14]" *)
input wire [14 : 0] m_sc_recv;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 M00_SC SEND [0:0] [0:0], xilinx.com:interface:sc:1.0 M01_SC SEND [0:0] [1:1], xilinx.com:interface:sc:1.0 M02_SC SEND [0:0] [2:2], xilinx.com:interface:sc:1.0 M03_SC SEND [0:0] [3:3], xilinx.com:interface:sc:1.0 M04_SC SEND [0:0] [4:4], xilinx.com:interface:sc:1.0 M05_SC SEND [0:0] [5:5], xilinx.com:interface:sc:1.0 M06_SC SEND [0:0] [6:6], xilinx.com:interface:sc:1.0 M07_SC SEND [0:0] [7:7], xilinx.com:interface:sc:1.0 M08_SC SEND [0:0] [8:8], xilinx.com:interface:sc\
:1.0 M09_SC SEND [0:0] [9:9], xilinx.com:interface:sc:1.0 M10_SC SEND [0:0] [10:10], xilinx.com:interface:sc:1.0 M11_SC SEND [0:0] [11:11], xilinx.com:interface:sc:1.0 M12_SC SEND [0:0] [12:12], xilinx.com:interface:sc:1.0 M13_SC SEND [0:0] [13:13], xilinx.com:interface:sc:1.0 M14_SC SEND [0:0] [14:14]" *)
output wire [14 : 0] m_sc_send;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 M00_SC REQ [0:0] [0:0], xilinx.com:interface:sc:1.0 M01_SC REQ [0:0] [1:1], xilinx.com:interface:sc:1.0 M02_SC REQ [0:0] [2:2], xilinx.com:interface:sc:1.0 M03_SC REQ [0:0] [3:3], xilinx.com:interface:sc:1.0 M04_SC REQ [0:0] [4:4], xilinx.com:interface:sc:1.0 M05_SC REQ [0:0] [5:5], xilinx.com:interface:sc:1.0 M06_SC REQ [0:0] [6:6], xilinx.com:interface:sc:1.0 M07_SC REQ [0:0] [7:7], xilinx.com:interface:sc:1.0 M08_SC REQ [0:0] [8:8], xilinx.com:interface:sc:1.0 M09_\
SC REQ [0:0] [9:9], xilinx.com:interface:sc:1.0 M10_SC REQ [0:0] [10:10], xilinx.com:interface:sc:1.0 M11_SC REQ [0:0] [11:11], xilinx.com:interface:sc:1.0 M12_SC REQ [0:0] [12:12], xilinx.com:interface:sc:1.0 M13_SC REQ [0:0] [13:13], xilinx.com:interface:sc:1.0 M14_SC REQ [0:0] [14:14]" *)
output wire [14 : 0] m_sc_req;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 M00_SC INFO [0:0] [0:0], xilinx.com:interface:sc:1.0 M01_SC INFO [0:0] [1:1], xilinx.com:interface:sc:1.0 M02_SC INFO [0:0] [2:2], xilinx.com:interface:sc:1.0 M03_SC INFO [0:0] [3:3], xilinx.com:interface:sc:1.0 M04_SC INFO [0:0] [4:4], xilinx.com:interface:sc:1.0 M05_SC INFO [0:0] [5:5], xilinx.com:interface:sc:1.0 M06_SC INFO [0:0] [6:6], xilinx.com:interface:sc:1.0 M07_SC INFO [0:0] [7:7], xilinx.com:interface:sc:1.0 M08_SC INFO [0:0] [8:8], xilinx.com:interface:sc\
:1.0 M09_SC INFO [0:0] [9:9], xilinx.com:interface:sc:1.0 M10_SC INFO [0:0] [10:10], xilinx.com:interface:sc:1.0 M11_SC INFO [0:0] [11:11], xilinx.com:interface:sc:1.0 M12_SC INFO [0:0] [12:12], xilinx.com:interface:sc:1.0 M13_SC INFO [0:0] [13:13], xilinx.com:interface:sc:1.0 M14_SC INFO [0:0] [14:14]" *)
output wire [14 : 0] m_sc_info;
(* X_INTERFACE_INFO = "xilinx.com:interface:sc:1.0 M00_SC PAYLD [178:0] [178:0], xilinx.com:interface:sc:1.0 M01_SC PAYLD [178:0] [357:179], xilinx.com:interface:sc:1.0 M02_SC PAYLD [178:0] [536:358], xilinx.com:interface:sc:1.0 M03_SC PAYLD [178:0] [715:537], xilinx.com:interface:sc:1.0 M04_SC PAYLD [178:0] [894:716], xilinx.com:interface:sc:1.0 M05_SC PAYLD [178:0] [1073:895], xilinx.com:interface:sc:1.0 M06_SC PAYLD [178:0] [1252:1074], xilinx.com:interface:sc:1.0 M07_SC PAYLD [178:0] [1431:1253], xilinx.com:interf\
ace:sc:1.0 M08_SC PAYLD [178:0] [1610:1432], xilinx.com:interface:sc:1.0 M09_SC PAYLD [178:0] [1789:1611], xilinx.com:interface:sc:1.0 M10_SC PAYLD [178:0] [1968:1790], xilinx.com:interface:sc:1.0 M11_SC PAYLD [178:0] [2147:1969], xilinx.com:interface:sc:1.0 M12_SC PAYLD [178:0] [2326:2148], xilinx.com:interface:sc:1.0 M13_SC PAYLD [178:0] [2505:2327], xilinx.com:interface:sc:1.0 M14_SC PAYLD [178:0] [2684:2506]" *)
output wire [2684 : 0] m_sc_payld;

  sc_switchboard_v1_0_6_top #(
    .C_PAYLD_WIDTH(179),
    .K_MAX_INFO_WIDTH(1),
    .C_S_PIPELINES(0),
    .C_M_PIPELINES(1),
    .C_S_LATENCY(0),
    .C_NUM_SI(1),
    .C_NUM_MI(15),
    .C_TESTING_MODE(0),
    .C_CONNECTIVITY(15'B011111111111111)
  ) inst (
    .aclk(aclk),
    .aclken(aclken),
    .connectivity(15'B011111111111111),
    .s_sc_send(s_sc_send),
    .s_sc_req(s_sc_req),
    .s_sc_info(s_sc_info),
    .s_sc_payld(s_sc_payld),
    .s_sc_recv(s_sc_recv),
    .m_sc_recv(m_sc_recv),
    .m_sc_send(m_sc_send),
    .m_sc_req(m_sc_req),
    .m_sc_info(m_sc_info),
    .m_sc_payld(m_sc_payld)
  );
endmodule
