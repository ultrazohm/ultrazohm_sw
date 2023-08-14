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


#include "zusys_smartconnect_0_0_sc.h"

#include "zusys_smartconnect_0_0.h"

#include "smartconnect.h"

#include <map>
#include <string>





#ifdef XILINX_SIMULATOR
zusys_smartconnect_0_0::zusys_smartconnect_0_0(const sc_core::sc_module_name& nm) : zusys_smartconnect_0_0_sc(nm), aclk("aclk"), aclk1("aclk1"), aclk2("aclk2"), aresetn("aresetn"), S00_AXI_awid("S00_AXI_awid"), S00_AXI_awaddr("S00_AXI_awaddr"), S00_AXI_awlen("S00_AXI_awlen"), S00_AXI_awsize("S00_AXI_awsize"), S00_AXI_awburst("S00_AXI_awburst"), S00_AXI_awlock("S00_AXI_awlock"), S00_AXI_awcache("S00_AXI_awcache"), S00_AXI_awprot("S00_AXI_awprot"), S00_AXI_awqos("S00_AXI_awqos"), S00_AXI_awuser("S00_AXI_awuser"), S00_AXI_awvalid("S00_AXI_awvalid"), S00_AXI_awready("S00_AXI_awready"), S00_AXI_wdata("S00_AXI_wdata"), S00_AXI_wstrb("S00_AXI_wstrb"), S00_AXI_wlast("S00_AXI_wlast"), S00_AXI_wvalid("S00_AXI_wvalid"), S00_AXI_wready("S00_AXI_wready"), S00_AXI_bid("S00_AXI_bid"), S00_AXI_bresp("S00_AXI_bresp"), S00_AXI_bvalid("S00_AXI_bvalid"), S00_AXI_bready("S00_AXI_bready"), S00_AXI_arid("S00_AXI_arid"), S00_AXI_araddr("S00_AXI_araddr"), S00_AXI_arlen("S00_AXI_arlen"), S00_AXI_arsize("S00_AXI_arsize"), S00_AXI_arburst("S00_AXI_arburst"), S00_AXI_arlock("S00_AXI_arlock"), S00_AXI_arcache("S00_AXI_arcache"), S00_AXI_arprot("S00_AXI_arprot"), S00_AXI_arqos("S00_AXI_arqos"), S00_AXI_aruser("S00_AXI_aruser"), S00_AXI_arvalid("S00_AXI_arvalid"), S00_AXI_arready("S00_AXI_arready"), S00_AXI_rid("S00_AXI_rid"), S00_AXI_rdata("S00_AXI_rdata"), S00_AXI_rresp("S00_AXI_rresp"), S00_AXI_rlast("S00_AXI_rlast"), S00_AXI_rvalid("S00_AXI_rvalid"), S00_AXI_rready("S00_AXI_rready"), M00_AXI_awaddr("M00_AXI_awaddr"), M00_AXI_awprot("M00_AXI_awprot"), M00_AXI_awvalid("M00_AXI_awvalid"), M00_AXI_awready("M00_AXI_awready"), M00_AXI_wdata("M00_AXI_wdata"), M00_AXI_wstrb("M00_AXI_wstrb"), M00_AXI_wvalid("M00_AXI_wvalid"), M00_AXI_wready("M00_AXI_wready"), M00_AXI_bresp("M00_AXI_bresp"), M00_AXI_bvalid("M00_AXI_bvalid"), M00_AXI_bready("M00_AXI_bready"), M00_AXI_araddr("M00_AXI_araddr"), M00_AXI_arprot("M00_AXI_arprot"), M00_AXI_arvalid("M00_AXI_arvalid"), M00_AXI_arready("M00_AXI_arready"), M00_AXI_rdata("M00_AXI_rdata"), M00_AXI_rresp("M00_AXI_rresp"), M00_AXI_rvalid("M00_AXI_rvalid"), M00_AXI_rready("M00_AXI_rready"), M01_AXI_awaddr("M01_AXI_awaddr"), M01_AXI_awprot("M01_AXI_awprot"), M01_AXI_awvalid("M01_AXI_awvalid"), M01_AXI_awready("M01_AXI_awready"), M01_AXI_wdata("M01_AXI_wdata"), M01_AXI_wstrb("M01_AXI_wstrb"), M01_AXI_wvalid("M01_AXI_wvalid"), M01_AXI_wready("M01_AXI_wready"), M01_AXI_bresp("M01_AXI_bresp"), M01_AXI_bvalid("M01_AXI_bvalid"), M01_AXI_bready("M01_AXI_bready"), M01_AXI_araddr("M01_AXI_araddr"), M01_AXI_arprot("M01_AXI_arprot"), M01_AXI_arvalid("M01_AXI_arvalid"), M01_AXI_arready("M01_AXI_arready"), M01_AXI_rdata("M01_AXI_rdata"), M01_AXI_rresp("M01_AXI_rresp"), M01_AXI_rvalid("M01_AXI_rvalid"), M01_AXI_rready("M01_AXI_rready"), M02_AXI_awaddr("M02_AXI_awaddr"), M02_AXI_awprot("M02_AXI_awprot"), M02_AXI_awvalid("M02_AXI_awvalid"), M02_AXI_awready("M02_AXI_awready"), M02_AXI_wdata("M02_AXI_wdata"), M02_AXI_wstrb("M02_AXI_wstrb"), M02_AXI_wvalid("M02_AXI_wvalid"), M02_AXI_wready("M02_AXI_wready"), M02_AXI_bresp("M02_AXI_bresp"), M02_AXI_bvalid("M02_AXI_bvalid"), M02_AXI_bready("M02_AXI_bready"), M02_AXI_araddr("M02_AXI_araddr"), M02_AXI_arprot("M02_AXI_arprot"), M02_AXI_arvalid("M02_AXI_arvalid"), M02_AXI_arready("M02_AXI_arready"), M02_AXI_rdata("M02_AXI_rdata"), M02_AXI_rresp("M02_AXI_rresp"), M02_AXI_rvalid("M02_AXI_rvalid"), M02_AXI_rready("M02_AXI_rready"), M03_AXI_awaddr("M03_AXI_awaddr"), M03_AXI_awprot("M03_AXI_awprot"), M03_AXI_awvalid("M03_AXI_awvalid"), M03_AXI_awready("M03_AXI_awready"), M03_AXI_wdata("M03_AXI_wdata"), M03_AXI_wstrb("M03_AXI_wstrb"), M03_AXI_wvalid("M03_AXI_wvalid"), M03_AXI_wready("M03_AXI_wready"), M03_AXI_bresp("M03_AXI_bresp"), M03_AXI_bvalid("M03_AXI_bvalid"), M03_AXI_bready("M03_AXI_bready"), M03_AXI_araddr("M03_AXI_araddr"), M03_AXI_arprot("M03_AXI_arprot"), M03_AXI_arvalid("M03_AXI_arvalid"), M03_AXI_arready("M03_AXI_arready"), M03_AXI_rdata("M03_AXI_rdata"), M03_AXI_rresp("M03_AXI_rresp"), M03_AXI_rvalid("M03_AXI_rvalid"), M03_AXI_rready("M03_AXI_rready"), M04_AXI_awaddr("M04_AXI_awaddr"), M04_AXI_awprot("M04_AXI_awprot"), M04_AXI_awvalid("M04_AXI_awvalid"), M04_AXI_awready("M04_AXI_awready"), M04_AXI_wdata("M04_AXI_wdata"), M04_AXI_wstrb("M04_AXI_wstrb"), M04_AXI_wvalid("M04_AXI_wvalid"), M04_AXI_wready("M04_AXI_wready"), M04_AXI_bresp("M04_AXI_bresp"), M04_AXI_bvalid("M04_AXI_bvalid"), M04_AXI_bready("M04_AXI_bready"), M04_AXI_araddr("M04_AXI_araddr"), M04_AXI_arprot("M04_AXI_arprot"), M04_AXI_arvalid("M04_AXI_arvalid"), M04_AXI_arready("M04_AXI_arready"), M04_AXI_rdata("M04_AXI_rdata"), M04_AXI_rresp("M04_AXI_rresp"), M04_AXI_rvalid("M04_AXI_rvalid"), M04_AXI_rready("M04_AXI_rready"), M05_AXI_awaddr("M05_AXI_awaddr"), M05_AXI_awprot("M05_AXI_awprot"), M05_AXI_awvalid("M05_AXI_awvalid"), M05_AXI_awready("M05_AXI_awready"), M05_AXI_wdata("M05_AXI_wdata"), M05_AXI_wstrb("M05_AXI_wstrb"), M05_AXI_wvalid("M05_AXI_wvalid"), M05_AXI_wready("M05_AXI_wready"), M05_AXI_bresp("M05_AXI_bresp"), M05_AXI_bvalid("M05_AXI_bvalid"), M05_AXI_bready("M05_AXI_bready"), M05_AXI_araddr("M05_AXI_araddr"), M05_AXI_arprot("M05_AXI_arprot"), M05_AXI_arvalid("M05_AXI_arvalid"), M05_AXI_arready("M05_AXI_arready"), M05_AXI_rdata("M05_AXI_rdata"), M05_AXI_rresp("M05_AXI_rresp"), M05_AXI_rvalid("M05_AXI_rvalid"), M05_AXI_rready("M05_AXI_rready"), M06_AXI_awaddr("M06_AXI_awaddr"), M06_AXI_awprot("M06_AXI_awprot"), M06_AXI_awvalid("M06_AXI_awvalid"), M06_AXI_awready("M06_AXI_awready"), M06_AXI_wdata("M06_AXI_wdata"), M06_AXI_wstrb("M06_AXI_wstrb"), M06_AXI_wvalid("M06_AXI_wvalid"), M06_AXI_wready("M06_AXI_wready"), M06_AXI_bresp("M06_AXI_bresp"), M06_AXI_bvalid("M06_AXI_bvalid"), M06_AXI_bready("M06_AXI_bready"), M06_AXI_araddr("M06_AXI_araddr"), M06_AXI_arprot("M06_AXI_arprot"), M06_AXI_arvalid("M06_AXI_arvalid"), M06_AXI_arready("M06_AXI_arready"), M06_AXI_rdata("M06_AXI_rdata"), M06_AXI_rresp("M06_AXI_rresp"), M06_AXI_rvalid("M06_AXI_rvalid"), M06_AXI_rready("M06_AXI_rready"), M07_AXI_awaddr("M07_AXI_awaddr"), M07_AXI_awlen("M07_AXI_awlen"), M07_AXI_awsize("M07_AXI_awsize"), M07_AXI_awburst("M07_AXI_awburst"), M07_AXI_awlock("M07_AXI_awlock"), M07_AXI_awcache("M07_AXI_awcache"), M07_AXI_awprot("M07_AXI_awprot"), M07_AXI_awqos("M07_AXI_awqos"), M07_AXI_awuser("M07_AXI_awuser"), M07_AXI_awvalid("M07_AXI_awvalid"), M07_AXI_awready("M07_AXI_awready"), M07_AXI_wdata("M07_AXI_wdata"), M07_AXI_wstrb("M07_AXI_wstrb"), M07_AXI_wlast("M07_AXI_wlast"), M07_AXI_wvalid("M07_AXI_wvalid"), M07_AXI_wready("M07_AXI_wready"), M07_AXI_bresp("M07_AXI_bresp"), M07_AXI_bvalid("M07_AXI_bvalid"), M07_AXI_bready("M07_AXI_bready"), M07_AXI_araddr("M07_AXI_araddr"), M07_AXI_arlen("M07_AXI_arlen"), M07_AXI_arsize("M07_AXI_arsize"), M07_AXI_arburst("M07_AXI_arburst"), M07_AXI_arlock("M07_AXI_arlock"), M07_AXI_arcache("M07_AXI_arcache"), M07_AXI_arprot("M07_AXI_arprot"), M07_AXI_arqos("M07_AXI_arqos"), M07_AXI_aruser("M07_AXI_aruser"), M07_AXI_arvalid("M07_AXI_arvalid"), M07_AXI_arready("M07_AXI_arready"), M07_AXI_rdata("M07_AXI_rdata"), M07_AXI_rresp("M07_AXI_rresp"), M07_AXI_rlast("M07_AXI_rlast"), M07_AXI_rvalid("M07_AXI_rvalid"), M07_AXI_rready("M07_AXI_rready"), M08_AXI_awaddr("M08_AXI_awaddr"), M08_AXI_awprot("M08_AXI_awprot"), M08_AXI_awvalid("M08_AXI_awvalid"), M08_AXI_awready("M08_AXI_awready"), M08_AXI_wdata("M08_AXI_wdata"), M08_AXI_wstrb("M08_AXI_wstrb"), M08_AXI_wvalid("M08_AXI_wvalid"), M08_AXI_wready("M08_AXI_wready"), M08_AXI_bresp("M08_AXI_bresp"), M08_AXI_bvalid("M08_AXI_bvalid"), M08_AXI_bready("M08_AXI_bready"), M08_AXI_araddr("M08_AXI_araddr"), M08_AXI_arprot("M08_AXI_arprot"), M08_AXI_arvalid("M08_AXI_arvalid"), M08_AXI_arready("M08_AXI_arready"), M08_AXI_rdata("M08_AXI_rdata"), M08_AXI_rresp("M08_AXI_rresp"), M08_AXI_rvalid("M08_AXI_rvalid"), M08_AXI_rready("M08_AXI_rready"), M09_AXI_awaddr("M09_AXI_awaddr"), M09_AXI_awprot("M09_AXI_awprot"), M09_AXI_awvalid("M09_AXI_awvalid"), M09_AXI_awready("M09_AXI_awready"), M09_AXI_wdata("M09_AXI_wdata"), M09_AXI_wstrb("M09_AXI_wstrb"), M09_AXI_wvalid("M09_AXI_wvalid"), M09_AXI_wready("M09_AXI_wready"), M09_AXI_bresp("M09_AXI_bresp"), M09_AXI_bvalid("M09_AXI_bvalid"), M09_AXI_bready("M09_AXI_bready"), M09_AXI_araddr("M09_AXI_araddr"), M09_AXI_arprot("M09_AXI_arprot"), M09_AXI_arvalid("M09_AXI_arvalid"), M09_AXI_arready("M09_AXI_arready"), M09_AXI_rdata("M09_AXI_rdata"), M09_AXI_rresp("M09_AXI_rresp"), M09_AXI_rvalid("M09_AXI_rvalid"), M09_AXI_rready("M09_AXI_rready"), M10_AXI_awid("M10_AXI_awid"), M10_AXI_awaddr("M10_AXI_awaddr"), M10_AXI_awlen("M10_AXI_awlen"), M10_AXI_awsize("M10_AXI_awsize"), M10_AXI_awburst("M10_AXI_awburst"), M10_AXI_awlock("M10_AXI_awlock"), M10_AXI_awcache("M10_AXI_awcache"), M10_AXI_awprot("M10_AXI_awprot"), M10_AXI_awqos("M10_AXI_awqos"), M10_AXI_awuser("M10_AXI_awuser"), M10_AXI_awvalid("M10_AXI_awvalid"), M10_AXI_awready("M10_AXI_awready"), M10_AXI_wdata("M10_AXI_wdata"), M10_AXI_wstrb("M10_AXI_wstrb"), M10_AXI_wlast("M10_AXI_wlast"), M10_AXI_wuser("M10_AXI_wuser"), M10_AXI_wvalid("M10_AXI_wvalid"), M10_AXI_wready("M10_AXI_wready"), M10_AXI_bid("M10_AXI_bid"), M10_AXI_bresp("M10_AXI_bresp"), M10_AXI_buser("M10_AXI_buser"), M10_AXI_bvalid("M10_AXI_bvalid"), M10_AXI_bready("M10_AXI_bready"), M10_AXI_arid("M10_AXI_arid"), M10_AXI_araddr("M10_AXI_araddr"), M10_AXI_arlen("M10_AXI_arlen"), M10_AXI_arsize("M10_AXI_arsize"), M10_AXI_arburst("M10_AXI_arburst"), M10_AXI_arlock("M10_AXI_arlock"), M10_AXI_arcache("M10_AXI_arcache"), M10_AXI_arprot("M10_AXI_arprot"), M10_AXI_arqos("M10_AXI_arqos"), M10_AXI_aruser("M10_AXI_aruser"), M10_AXI_arvalid("M10_AXI_arvalid"), M10_AXI_arready("M10_AXI_arready"), M10_AXI_rid("M10_AXI_rid"), M10_AXI_rdata("M10_AXI_rdata"), M10_AXI_rresp("M10_AXI_rresp"), M10_AXI_rlast("M10_AXI_rlast"), M10_AXI_ruser("M10_AXI_ruser"), M10_AXI_rvalid("M10_AXI_rvalid"), M10_AXI_rready("M10_AXI_rready"), M11_AXI_awaddr("M11_AXI_awaddr"), M11_AXI_awprot("M11_AXI_awprot"), M11_AXI_awvalid("M11_AXI_awvalid"), M11_AXI_awready("M11_AXI_awready"), M11_AXI_wdata("M11_AXI_wdata"), M11_AXI_wstrb("M11_AXI_wstrb"), M11_AXI_wvalid("M11_AXI_wvalid"), M11_AXI_wready("M11_AXI_wready"), M11_AXI_bresp("M11_AXI_bresp"), M11_AXI_bvalid("M11_AXI_bvalid"), M11_AXI_bready("M11_AXI_bready"), M11_AXI_araddr("M11_AXI_araddr"), M11_AXI_arprot("M11_AXI_arprot"), M11_AXI_arvalid("M11_AXI_arvalid"), M11_AXI_arready("M11_AXI_arready"), M11_AXI_rdata("M11_AXI_rdata"), M11_AXI_rresp("M11_AXI_rresp"), M11_AXI_rvalid("M11_AXI_rvalid"), M11_AXI_rready("M11_AXI_rready"), M12_AXI_awaddr("M12_AXI_awaddr"), M12_AXI_awprot("M12_AXI_awprot"), M12_AXI_awvalid("M12_AXI_awvalid"), M12_AXI_awready("M12_AXI_awready"), M12_AXI_wdata("M12_AXI_wdata"), M12_AXI_wstrb("M12_AXI_wstrb"), M12_AXI_wvalid("M12_AXI_wvalid"), M12_AXI_wready("M12_AXI_wready"), M12_AXI_bresp("M12_AXI_bresp"), M12_AXI_bvalid("M12_AXI_bvalid"), M12_AXI_bready("M12_AXI_bready"), M12_AXI_araddr("M12_AXI_araddr"), M12_AXI_arprot("M12_AXI_arprot"), M12_AXI_arvalid("M12_AXI_arvalid"), M12_AXI_arready("M12_AXI_arready"), M12_AXI_rdata("M12_AXI_rdata"), M12_AXI_rresp("M12_AXI_rresp"), M12_AXI_rvalid("M12_AXI_rvalid"), M12_AXI_rready("M12_AXI_rready"), M13_AXI_awaddr("M13_AXI_awaddr"), M13_AXI_awprot("M13_AXI_awprot"), M13_AXI_awvalid("M13_AXI_awvalid"), M13_AXI_awready("M13_AXI_awready"), M13_AXI_wdata("M13_AXI_wdata"), M13_AXI_wstrb("M13_AXI_wstrb"), M13_AXI_wvalid("M13_AXI_wvalid"), M13_AXI_wready("M13_AXI_wready"), M13_AXI_bresp("M13_AXI_bresp"), M13_AXI_bvalid("M13_AXI_bvalid"), M13_AXI_bready("M13_AXI_bready"), M13_AXI_araddr("M13_AXI_araddr"), M13_AXI_arprot("M13_AXI_arprot"), M13_AXI_arvalid("M13_AXI_arvalid"), M13_AXI_arready("M13_AXI_arready"), M13_AXI_rdata("M13_AXI_rdata"), M13_AXI_rresp("M13_AXI_rresp"), M13_AXI_rvalid("M13_AXI_rvalid"), M13_AXI_rready("M13_AXI_rready"), M14_AXI_awaddr("M14_AXI_awaddr"), M14_AXI_awprot("M14_AXI_awprot"), M14_AXI_awvalid("M14_AXI_awvalid"), M14_AXI_awready("M14_AXI_awready"), M14_AXI_wdata("M14_AXI_wdata"), M14_AXI_wstrb("M14_AXI_wstrb"), M14_AXI_wvalid("M14_AXI_wvalid"), M14_AXI_wready("M14_AXI_wready"), M14_AXI_bresp("M14_AXI_bresp"), M14_AXI_bvalid("M14_AXI_bvalid"), M14_AXI_bready("M14_AXI_bready"), M14_AXI_araddr("M14_AXI_araddr"), M14_AXI_arprot("M14_AXI_arprot"), M14_AXI_arvalid("M14_AXI_arvalid"), M14_AXI_arready("M14_AXI_arready"), M14_AXI_rdata("M14_AXI_rdata"), M14_AXI_rresp("M14_AXI_rresp"), M14_AXI_rvalid("M14_AXI_rvalid"), M14_AXI_rready("M14_AXI_rready")
{

  // initialize pins
  mp_impl->aclk(aclk);
  mp_impl->aclk1(aclk1);
  mp_impl->aclk2(aclk2);
  mp_impl->aresetn(aresetn);

  // initialize transactors
  mp_S00_AXI_transactor = NULL;
  mp_S00_AXI_awlock_converter = NULL;
  mp_S00_AXI_arlock_converter = NULL;
  mp_M00_AXI_transactor = NULL;
  mp_M01_AXI_transactor = NULL;
  mp_M02_AXI_transactor = NULL;
  mp_M03_AXI_transactor = NULL;
  mp_M04_AXI_transactor = NULL;
  mp_M05_AXI_transactor = NULL;
  mp_M06_AXI_transactor = NULL;
  mp_M07_AXI_transactor = NULL;
  mp_M07_AXI_awlock_converter = NULL;
  mp_M07_AXI_arlock_converter = NULL;
  mp_M08_AXI_transactor = NULL;
  mp_M09_AXI_transactor = NULL;
  mp_M10_AXI_transactor = NULL;
  mp_M10_AXI_awlock_converter = NULL;
  mp_M10_AXI_arlock_converter = NULL;
  mp_M11_AXI_transactor = NULL;
  mp_M12_AXI_transactor = NULL;
  mp_M13_AXI_transactor = NULL;
  mp_M14_AXI_transactor = NULL;

  // initialize socket stubs

}

void zusys_smartconnect_0_0::before_end_of_elaboration()
{
  // configure 'S00_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "S00_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'S00_AXI' transactor parameters
    xsc::common_cpp::properties S00_AXI_transactor_param_props;
    S00_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    S00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S00_AXI_transactor_param_props.addLong("ID_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    S00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    S00_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    S00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    S00_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    S00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    S00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    S00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    S00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    S00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    S00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    S00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    S00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S00_AXI_transactor = new xtlm::xaximm_pin2xtlm_t<128,40,16,16,1,1,16,1>("S00_AXI_transactor", S00_AXI_transactor_param_props);

    // S00_AXI' transactor ports

    mp_S00_AXI_transactor->AWID(S00_AXI_awid);
    mp_S00_AXI_transactor->AWADDR(S00_AXI_awaddr);
    mp_S00_AXI_transactor->AWLEN(S00_AXI_awlen);
    mp_S00_AXI_transactor->AWSIZE(S00_AXI_awsize);
    mp_S00_AXI_transactor->AWBURST(S00_AXI_awburst);
    mp_S00_AXI_awlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_awlock_converter");
    mp_S00_AXI_awlock_converter->vector_in(S00_AXI_awlock);
    mp_S00_AXI_awlock_converter->scalar_out(m_S00_AXI_awlock_converter_signal);
    mp_S00_AXI_transactor->AWLOCK(m_S00_AXI_awlock_converter_signal);
    mp_S00_AXI_transactor->AWCACHE(S00_AXI_awcache);
    mp_S00_AXI_transactor->AWPROT(S00_AXI_awprot);
    mp_S00_AXI_transactor->AWQOS(S00_AXI_awqos);
    mp_S00_AXI_transactor->AWUSER(S00_AXI_awuser);
    mp_S00_AXI_transactor->AWVALID(S00_AXI_awvalid);
    mp_S00_AXI_transactor->AWREADY(S00_AXI_awready);
    mp_S00_AXI_transactor->WDATA(S00_AXI_wdata);
    mp_S00_AXI_transactor->WSTRB(S00_AXI_wstrb);
    mp_S00_AXI_transactor->WLAST(S00_AXI_wlast);
    mp_S00_AXI_transactor->WVALID(S00_AXI_wvalid);
    mp_S00_AXI_transactor->WREADY(S00_AXI_wready);
    mp_S00_AXI_transactor->BID(S00_AXI_bid);
    mp_S00_AXI_transactor->BRESP(S00_AXI_bresp);
    mp_S00_AXI_transactor->BVALID(S00_AXI_bvalid);
    mp_S00_AXI_transactor->BREADY(S00_AXI_bready);
    mp_S00_AXI_transactor->ARID(S00_AXI_arid);
    mp_S00_AXI_transactor->ARADDR(S00_AXI_araddr);
    mp_S00_AXI_transactor->ARLEN(S00_AXI_arlen);
    mp_S00_AXI_transactor->ARSIZE(S00_AXI_arsize);
    mp_S00_AXI_transactor->ARBURST(S00_AXI_arburst);
    mp_S00_AXI_arlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_arlock_converter");
    mp_S00_AXI_arlock_converter->vector_in(S00_AXI_arlock);
    mp_S00_AXI_arlock_converter->scalar_out(m_S00_AXI_arlock_converter_signal);
    mp_S00_AXI_transactor->ARLOCK(m_S00_AXI_arlock_converter_signal);
    mp_S00_AXI_transactor->ARCACHE(S00_AXI_arcache);
    mp_S00_AXI_transactor->ARPROT(S00_AXI_arprot);
    mp_S00_AXI_transactor->ARQOS(S00_AXI_arqos);
    mp_S00_AXI_transactor->ARUSER(S00_AXI_aruser);
    mp_S00_AXI_transactor->ARVALID(S00_AXI_arvalid);
    mp_S00_AXI_transactor->ARREADY(S00_AXI_arready);
    mp_S00_AXI_transactor->RID(S00_AXI_rid);
    mp_S00_AXI_transactor->RDATA(S00_AXI_rdata);
    mp_S00_AXI_transactor->RRESP(S00_AXI_rresp);
    mp_S00_AXI_transactor->RLAST(S00_AXI_rlast);
    mp_S00_AXI_transactor->RVALID(S00_AXI_rvalid);
    mp_S00_AXI_transactor->RREADY(S00_AXI_rready);
    mp_S00_AXI_transactor->CLK(aclk);
    mp_S00_AXI_transactor->RST(aresetn);

    // S00_AXI' transactor sockets

    mp_impl->S00_AXI_tlm_aximm_read_socket->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_impl->S00_AXI_tlm_aximm_write_socket->bind(*(mp_S00_AXI_transactor->wr_socket));
  }

  // configure 'M00_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M00_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M00_AXI' transactor parameters
    xsc::common_cpp::properties M00_AXI_transactor_param_props;
    M00_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M00_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M00_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M00_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M00_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M00_AXI_transactor", M00_AXI_transactor_param_props);

    // M00_AXI' transactor ports

    mp_M00_AXI_transactor->AWADDR(M00_AXI_awaddr);
    mp_M00_AXI_transactor->AWPROT(M00_AXI_awprot);
    mp_M00_AXI_transactor->AWVALID(M00_AXI_awvalid);
    mp_M00_AXI_transactor->AWREADY(M00_AXI_awready);
    mp_M00_AXI_transactor->WDATA(M00_AXI_wdata);
    mp_M00_AXI_transactor->WSTRB(M00_AXI_wstrb);
    mp_M00_AXI_transactor->WVALID(M00_AXI_wvalid);
    mp_M00_AXI_transactor->WREADY(M00_AXI_wready);
    mp_M00_AXI_transactor->BRESP(M00_AXI_bresp);
    mp_M00_AXI_transactor->BVALID(M00_AXI_bvalid);
    mp_M00_AXI_transactor->BREADY(M00_AXI_bready);
    mp_M00_AXI_transactor->ARADDR(M00_AXI_araddr);
    mp_M00_AXI_transactor->ARPROT(M00_AXI_arprot);
    mp_M00_AXI_transactor->ARVALID(M00_AXI_arvalid);
    mp_M00_AXI_transactor->ARREADY(M00_AXI_arready);
    mp_M00_AXI_transactor->RDATA(M00_AXI_rdata);
    mp_M00_AXI_transactor->RRESP(M00_AXI_rresp);
    mp_M00_AXI_transactor->RVALID(M00_AXI_rvalid);
    mp_M00_AXI_transactor->RREADY(M00_AXI_rready);
    mp_M00_AXI_transactor->CLK(aclk);
    mp_M00_AXI_transactor->RST(aresetn);

    // M00_AXI' transactor sockets

    mp_impl->M00_AXI_tlm_aximm_read_socket->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_impl->M00_AXI_tlm_aximm_write_socket->bind(*(mp_M00_AXI_transactor->wr_socket));
  }

  // configure 'M01_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M01_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M01_AXI' transactor parameters
    xsc::common_cpp::properties M01_AXI_transactor_param_props;
    M01_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M01_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M01_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M01_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M01_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M01_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M01_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M01_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M01_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M01_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M01_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M01_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M01_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M01_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M01_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M01_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M01_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M01_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M01_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M01_AXI_transactor", M01_AXI_transactor_param_props);

    // M01_AXI' transactor ports

    mp_M01_AXI_transactor->AWADDR(M01_AXI_awaddr);
    mp_M01_AXI_transactor->AWPROT(M01_AXI_awprot);
    mp_M01_AXI_transactor->AWVALID(M01_AXI_awvalid);
    mp_M01_AXI_transactor->AWREADY(M01_AXI_awready);
    mp_M01_AXI_transactor->WDATA(M01_AXI_wdata);
    mp_M01_AXI_transactor->WSTRB(M01_AXI_wstrb);
    mp_M01_AXI_transactor->WVALID(M01_AXI_wvalid);
    mp_M01_AXI_transactor->WREADY(M01_AXI_wready);
    mp_M01_AXI_transactor->BRESP(M01_AXI_bresp);
    mp_M01_AXI_transactor->BVALID(M01_AXI_bvalid);
    mp_M01_AXI_transactor->BREADY(M01_AXI_bready);
    mp_M01_AXI_transactor->ARADDR(M01_AXI_araddr);
    mp_M01_AXI_transactor->ARPROT(M01_AXI_arprot);
    mp_M01_AXI_transactor->ARVALID(M01_AXI_arvalid);
    mp_M01_AXI_transactor->ARREADY(M01_AXI_arready);
    mp_M01_AXI_transactor->RDATA(M01_AXI_rdata);
    mp_M01_AXI_transactor->RRESP(M01_AXI_rresp);
    mp_M01_AXI_transactor->RVALID(M01_AXI_rvalid);
    mp_M01_AXI_transactor->RREADY(M01_AXI_rready);
    mp_M01_AXI_transactor->CLK(aclk);
    mp_M01_AXI_transactor->RST(aresetn);

    // M01_AXI' transactor sockets

    mp_impl->M01_AXI_tlm_aximm_read_socket->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_impl->M01_AXI_tlm_aximm_write_socket->bind(*(mp_M01_AXI_transactor->wr_socket));
  }

  // configure 'M02_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M02_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M02_AXI' transactor parameters
    xsc::common_cpp::properties M02_AXI_transactor_param_props;
    M02_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M02_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M02_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M02_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M02_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M02_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M02_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M02_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M02_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M02_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M02_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M02_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M02_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M02_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M02_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M02_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M02_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M02_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M02_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M02_AXI_transactor", M02_AXI_transactor_param_props);

    // M02_AXI' transactor ports

    mp_M02_AXI_transactor->AWADDR(M02_AXI_awaddr);
    mp_M02_AXI_transactor->AWPROT(M02_AXI_awprot);
    mp_M02_AXI_transactor->AWVALID(M02_AXI_awvalid);
    mp_M02_AXI_transactor->AWREADY(M02_AXI_awready);
    mp_M02_AXI_transactor->WDATA(M02_AXI_wdata);
    mp_M02_AXI_transactor->WSTRB(M02_AXI_wstrb);
    mp_M02_AXI_transactor->WVALID(M02_AXI_wvalid);
    mp_M02_AXI_transactor->WREADY(M02_AXI_wready);
    mp_M02_AXI_transactor->BRESP(M02_AXI_bresp);
    mp_M02_AXI_transactor->BVALID(M02_AXI_bvalid);
    mp_M02_AXI_transactor->BREADY(M02_AXI_bready);
    mp_M02_AXI_transactor->ARADDR(M02_AXI_araddr);
    mp_M02_AXI_transactor->ARPROT(M02_AXI_arprot);
    mp_M02_AXI_transactor->ARVALID(M02_AXI_arvalid);
    mp_M02_AXI_transactor->ARREADY(M02_AXI_arready);
    mp_M02_AXI_transactor->RDATA(M02_AXI_rdata);
    mp_M02_AXI_transactor->RRESP(M02_AXI_rresp);
    mp_M02_AXI_transactor->RVALID(M02_AXI_rvalid);
    mp_M02_AXI_transactor->RREADY(M02_AXI_rready);
    mp_M02_AXI_transactor->CLK(aclk);
    mp_M02_AXI_transactor->RST(aresetn);

    // M02_AXI' transactor sockets

    mp_impl->M02_AXI_tlm_aximm_read_socket->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_impl->M02_AXI_tlm_aximm_write_socket->bind(*(mp_M02_AXI_transactor->wr_socket));
  }

  // configure 'M03_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M03_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M03_AXI' transactor parameters
    xsc::common_cpp::properties M03_AXI_transactor_param_props;
    M03_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M03_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M03_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M03_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M03_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M03_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M03_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M03_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M03_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M03_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M03_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M03_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M03_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M03_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M03_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M03_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M03_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M03_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M03_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M03_AXI_transactor", M03_AXI_transactor_param_props);

    // M03_AXI' transactor ports

    mp_M03_AXI_transactor->AWADDR(M03_AXI_awaddr);
    mp_M03_AXI_transactor->AWPROT(M03_AXI_awprot);
    mp_M03_AXI_transactor->AWVALID(M03_AXI_awvalid);
    mp_M03_AXI_transactor->AWREADY(M03_AXI_awready);
    mp_M03_AXI_transactor->WDATA(M03_AXI_wdata);
    mp_M03_AXI_transactor->WSTRB(M03_AXI_wstrb);
    mp_M03_AXI_transactor->WVALID(M03_AXI_wvalid);
    mp_M03_AXI_transactor->WREADY(M03_AXI_wready);
    mp_M03_AXI_transactor->BRESP(M03_AXI_bresp);
    mp_M03_AXI_transactor->BVALID(M03_AXI_bvalid);
    mp_M03_AXI_transactor->BREADY(M03_AXI_bready);
    mp_M03_AXI_transactor->ARADDR(M03_AXI_araddr);
    mp_M03_AXI_transactor->ARPROT(M03_AXI_arprot);
    mp_M03_AXI_transactor->ARVALID(M03_AXI_arvalid);
    mp_M03_AXI_transactor->ARREADY(M03_AXI_arready);
    mp_M03_AXI_transactor->RDATA(M03_AXI_rdata);
    mp_M03_AXI_transactor->RRESP(M03_AXI_rresp);
    mp_M03_AXI_transactor->RVALID(M03_AXI_rvalid);
    mp_M03_AXI_transactor->RREADY(M03_AXI_rready);
    mp_M03_AXI_transactor->CLK(aclk);
    mp_M03_AXI_transactor->RST(aresetn);

    // M03_AXI' transactor sockets

    mp_impl->M03_AXI_tlm_aximm_read_socket->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_impl->M03_AXI_tlm_aximm_write_socket->bind(*(mp_M03_AXI_transactor->wr_socket));
  }

  // configure 'M04_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M04_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M04_AXI' transactor parameters
    xsc::common_cpp::properties M04_AXI_transactor_param_props;
    M04_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M04_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M04_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M04_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M04_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M04_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M04_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M04_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M04_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M04_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M04_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M04_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M04_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M04_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M04_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M04_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M04_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M04_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M04_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M04_AXI_transactor", M04_AXI_transactor_param_props);

    // M04_AXI' transactor ports

    mp_M04_AXI_transactor->AWADDR(M04_AXI_awaddr);
    mp_M04_AXI_transactor->AWPROT(M04_AXI_awprot);
    mp_M04_AXI_transactor->AWVALID(M04_AXI_awvalid);
    mp_M04_AXI_transactor->AWREADY(M04_AXI_awready);
    mp_M04_AXI_transactor->WDATA(M04_AXI_wdata);
    mp_M04_AXI_transactor->WSTRB(M04_AXI_wstrb);
    mp_M04_AXI_transactor->WVALID(M04_AXI_wvalid);
    mp_M04_AXI_transactor->WREADY(M04_AXI_wready);
    mp_M04_AXI_transactor->BRESP(M04_AXI_bresp);
    mp_M04_AXI_transactor->BVALID(M04_AXI_bvalid);
    mp_M04_AXI_transactor->BREADY(M04_AXI_bready);
    mp_M04_AXI_transactor->ARADDR(M04_AXI_araddr);
    mp_M04_AXI_transactor->ARPROT(M04_AXI_arprot);
    mp_M04_AXI_transactor->ARVALID(M04_AXI_arvalid);
    mp_M04_AXI_transactor->ARREADY(M04_AXI_arready);
    mp_M04_AXI_transactor->RDATA(M04_AXI_rdata);
    mp_M04_AXI_transactor->RRESP(M04_AXI_rresp);
    mp_M04_AXI_transactor->RVALID(M04_AXI_rvalid);
    mp_M04_AXI_transactor->RREADY(M04_AXI_rready);
    mp_M04_AXI_transactor->CLK(aclk);
    mp_M04_AXI_transactor->RST(aresetn);

    // M04_AXI' transactor sockets

    mp_impl->M04_AXI_tlm_aximm_read_socket->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_impl->M04_AXI_tlm_aximm_write_socket->bind(*(mp_M04_AXI_transactor->wr_socket));
  }

  // configure 'M05_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M05_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M05_AXI' transactor parameters
    xsc::common_cpp::properties M05_AXI_transactor_param_props;
    M05_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M05_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M05_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M05_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M05_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M05_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M05_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M05_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M05_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M05_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M05_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M05_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M05_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M05_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M05_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M05_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M05_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M05_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M05_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M05_AXI_transactor", M05_AXI_transactor_param_props);

    // M05_AXI' transactor ports

    mp_M05_AXI_transactor->AWADDR(M05_AXI_awaddr);
    mp_M05_AXI_transactor->AWPROT(M05_AXI_awprot);
    mp_M05_AXI_transactor->AWVALID(M05_AXI_awvalid);
    mp_M05_AXI_transactor->AWREADY(M05_AXI_awready);
    mp_M05_AXI_transactor->WDATA(M05_AXI_wdata);
    mp_M05_AXI_transactor->WSTRB(M05_AXI_wstrb);
    mp_M05_AXI_transactor->WVALID(M05_AXI_wvalid);
    mp_M05_AXI_transactor->WREADY(M05_AXI_wready);
    mp_M05_AXI_transactor->BRESP(M05_AXI_bresp);
    mp_M05_AXI_transactor->BVALID(M05_AXI_bvalid);
    mp_M05_AXI_transactor->BREADY(M05_AXI_bready);
    mp_M05_AXI_transactor->ARADDR(M05_AXI_araddr);
    mp_M05_AXI_transactor->ARPROT(M05_AXI_arprot);
    mp_M05_AXI_transactor->ARVALID(M05_AXI_arvalid);
    mp_M05_AXI_transactor->ARREADY(M05_AXI_arready);
    mp_M05_AXI_transactor->RDATA(M05_AXI_rdata);
    mp_M05_AXI_transactor->RRESP(M05_AXI_rresp);
    mp_M05_AXI_transactor->RVALID(M05_AXI_rvalid);
    mp_M05_AXI_transactor->RREADY(M05_AXI_rready);
    mp_M05_AXI_transactor->CLK(aclk);
    mp_M05_AXI_transactor->RST(aresetn);

    // M05_AXI' transactor sockets

    mp_impl->M05_AXI_tlm_aximm_read_socket->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_impl->M05_AXI_tlm_aximm_write_socket->bind(*(mp_M05_AXI_transactor->wr_socket));
  }

  // configure 'M06_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M06_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M06_AXI' transactor parameters
    xsc::common_cpp::properties M06_AXI_transactor_param_props;
    M06_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M06_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M06_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ADDR_WIDTH", "9");
    M06_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M06_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M06_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M06_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M06_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M06_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M06_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M06_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M06_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M06_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M06_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M06_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M06_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M06_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M06_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M06_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,9,1,1,1,1,1,1>("M06_AXI_transactor", M06_AXI_transactor_param_props);

    // M06_AXI' transactor ports

    mp_M06_AXI_transactor->AWADDR(M06_AXI_awaddr);
    mp_M06_AXI_transactor->AWPROT(M06_AXI_awprot);
    mp_M06_AXI_transactor->AWVALID(M06_AXI_awvalid);
    mp_M06_AXI_transactor->AWREADY(M06_AXI_awready);
    mp_M06_AXI_transactor->WDATA(M06_AXI_wdata);
    mp_M06_AXI_transactor->WSTRB(M06_AXI_wstrb);
    mp_M06_AXI_transactor->WVALID(M06_AXI_wvalid);
    mp_M06_AXI_transactor->WREADY(M06_AXI_wready);
    mp_M06_AXI_transactor->BRESP(M06_AXI_bresp);
    mp_M06_AXI_transactor->BVALID(M06_AXI_bvalid);
    mp_M06_AXI_transactor->BREADY(M06_AXI_bready);
    mp_M06_AXI_transactor->ARADDR(M06_AXI_araddr);
    mp_M06_AXI_transactor->ARPROT(M06_AXI_arprot);
    mp_M06_AXI_transactor->ARVALID(M06_AXI_arvalid);
    mp_M06_AXI_transactor->ARREADY(M06_AXI_arready);
    mp_M06_AXI_transactor->RDATA(M06_AXI_rdata);
    mp_M06_AXI_transactor->RRESP(M06_AXI_rresp);
    mp_M06_AXI_transactor->RVALID(M06_AXI_rvalid);
    mp_M06_AXI_transactor->RREADY(M06_AXI_rready);
    mp_M06_AXI_transactor->CLK(aclk);
    mp_M06_AXI_transactor->RST(aresetn);

    // M06_AXI' transactor sockets

    mp_impl->M06_AXI_tlm_aximm_read_socket->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_impl->M06_AXI_tlm_aximm_write_socket->bind(*(mp_M06_AXI_transactor->wr_socket));
  }

  // configure 'M07_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M07_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M07_AXI' transactor parameters
    xsc::common_cpp::properties M07_AXI_transactor_param_props;
    M07_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M07_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M07_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M07_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M07_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M07_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M07_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M07_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M07_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M07_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M07_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M07_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M07_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M07_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M07_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M07_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M07_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,16,1,1,16,1>("M07_AXI_transactor", M07_AXI_transactor_param_props);

    // M07_AXI' transactor ports

    mp_M07_AXI_transactor->AWADDR(M07_AXI_awaddr);
    mp_M07_AXI_transactor->AWLEN(M07_AXI_awlen);
    mp_M07_AXI_transactor->AWSIZE(M07_AXI_awsize);
    mp_M07_AXI_transactor->AWBURST(M07_AXI_awburst);
    mp_M07_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_awlock_converter");
    mp_M07_AXI_awlock_converter->scalar_in(m_M07_AXI_awlock_converter_signal);
    mp_M07_AXI_awlock_converter->vector_out(M07_AXI_awlock);
    mp_M07_AXI_transactor->AWLOCK(m_M07_AXI_awlock_converter_signal);
    mp_M07_AXI_transactor->AWCACHE(M07_AXI_awcache);
    mp_M07_AXI_transactor->AWPROT(M07_AXI_awprot);
    mp_M07_AXI_transactor->AWQOS(M07_AXI_awqos);
    mp_M07_AXI_transactor->AWUSER(M07_AXI_awuser);
    mp_M07_AXI_transactor->AWVALID(M07_AXI_awvalid);
    mp_M07_AXI_transactor->AWREADY(M07_AXI_awready);
    mp_M07_AXI_transactor->WDATA(M07_AXI_wdata);
    mp_M07_AXI_transactor->WSTRB(M07_AXI_wstrb);
    mp_M07_AXI_transactor->WLAST(M07_AXI_wlast);
    mp_M07_AXI_transactor->WVALID(M07_AXI_wvalid);
    mp_M07_AXI_transactor->WREADY(M07_AXI_wready);
    mp_M07_AXI_transactor->BRESP(M07_AXI_bresp);
    mp_M07_AXI_transactor->BVALID(M07_AXI_bvalid);
    mp_M07_AXI_transactor->BREADY(M07_AXI_bready);
    mp_M07_AXI_transactor->ARADDR(M07_AXI_araddr);
    mp_M07_AXI_transactor->ARLEN(M07_AXI_arlen);
    mp_M07_AXI_transactor->ARSIZE(M07_AXI_arsize);
    mp_M07_AXI_transactor->ARBURST(M07_AXI_arburst);
    mp_M07_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_arlock_converter");
    mp_M07_AXI_arlock_converter->scalar_in(m_M07_AXI_arlock_converter_signal);
    mp_M07_AXI_arlock_converter->vector_out(M07_AXI_arlock);
    mp_M07_AXI_transactor->ARLOCK(m_M07_AXI_arlock_converter_signal);
    mp_M07_AXI_transactor->ARCACHE(M07_AXI_arcache);
    mp_M07_AXI_transactor->ARPROT(M07_AXI_arprot);
    mp_M07_AXI_transactor->ARQOS(M07_AXI_arqos);
    mp_M07_AXI_transactor->ARUSER(M07_AXI_aruser);
    mp_M07_AXI_transactor->ARVALID(M07_AXI_arvalid);
    mp_M07_AXI_transactor->ARREADY(M07_AXI_arready);
    mp_M07_AXI_transactor->RDATA(M07_AXI_rdata);
    mp_M07_AXI_transactor->RRESP(M07_AXI_rresp);
    mp_M07_AXI_transactor->RLAST(M07_AXI_rlast);
    mp_M07_AXI_transactor->RVALID(M07_AXI_rvalid);
    mp_M07_AXI_transactor->RREADY(M07_AXI_rready);
    mp_M07_AXI_transactor->CLK(aclk);
    mp_M07_AXI_transactor->RST(aresetn);

    // M07_AXI' transactor sockets

    mp_impl->M07_AXI_tlm_aximm_read_socket->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_impl->M07_AXI_tlm_aximm_write_socket->bind(*(mp_M07_AXI_transactor->wr_socket));
  }

  // configure 'M08_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M08_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M08_AXI' transactor parameters
    xsc::common_cpp::properties M08_AXI_transactor_param_props;
    M08_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M08_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M08_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M08_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M08_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M08_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M08_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M08_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M08_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M08_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M08_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M08_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M08_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M08_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M08_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M08_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M08_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M08_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M08_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M08_AXI_transactor", M08_AXI_transactor_param_props);

    // M08_AXI' transactor ports

    mp_M08_AXI_transactor->AWADDR(M08_AXI_awaddr);
    mp_M08_AXI_transactor->AWPROT(M08_AXI_awprot);
    mp_M08_AXI_transactor->AWVALID(M08_AXI_awvalid);
    mp_M08_AXI_transactor->AWREADY(M08_AXI_awready);
    mp_M08_AXI_transactor->WDATA(M08_AXI_wdata);
    mp_M08_AXI_transactor->WSTRB(M08_AXI_wstrb);
    mp_M08_AXI_transactor->WVALID(M08_AXI_wvalid);
    mp_M08_AXI_transactor->WREADY(M08_AXI_wready);
    mp_M08_AXI_transactor->BRESP(M08_AXI_bresp);
    mp_M08_AXI_transactor->BVALID(M08_AXI_bvalid);
    mp_M08_AXI_transactor->BREADY(M08_AXI_bready);
    mp_M08_AXI_transactor->ARADDR(M08_AXI_araddr);
    mp_M08_AXI_transactor->ARPROT(M08_AXI_arprot);
    mp_M08_AXI_transactor->ARVALID(M08_AXI_arvalid);
    mp_M08_AXI_transactor->ARREADY(M08_AXI_arready);
    mp_M08_AXI_transactor->RDATA(M08_AXI_rdata);
    mp_M08_AXI_transactor->RRESP(M08_AXI_rresp);
    mp_M08_AXI_transactor->RVALID(M08_AXI_rvalid);
    mp_M08_AXI_transactor->RREADY(M08_AXI_rready);
    mp_M08_AXI_transactor->CLK(aclk);
    mp_M08_AXI_transactor->RST(aresetn);

    // M08_AXI' transactor sockets

    mp_impl->M08_AXI_tlm_aximm_read_socket->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_impl->M08_AXI_tlm_aximm_write_socket->bind(*(mp_M08_AXI_transactor->wr_socket));
  }

  // configure 'M09_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M09_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M09_AXI' transactor parameters
    xsc::common_cpp::properties M09_AXI_transactor_param_props;
    M09_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M09_AXI_transactor_param_props.addLong("FREQ_HZ", "50000000");
    M09_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M09_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M09_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M09_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M09_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M09_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M09_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M09_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M09_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M09_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M09_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M09_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M09_AXI_transactor_param_props.addFloat("PHASE", "0.0");
    M09_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M09_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M09_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_clk_wiz_0_0_clk_50MHz");

    mp_M09_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M09_AXI_transactor", M09_AXI_transactor_param_props);

    // M09_AXI' transactor ports

    mp_M09_AXI_transactor->AWADDR(M09_AXI_awaddr);
    mp_M09_AXI_transactor->AWPROT(M09_AXI_awprot);
    mp_M09_AXI_transactor->AWVALID(M09_AXI_awvalid);
    mp_M09_AXI_transactor->AWREADY(M09_AXI_awready);
    mp_M09_AXI_transactor->WDATA(M09_AXI_wdata);
    mp_M09_AXI_transactor->WSTRB(M09_AXI_wstrb);
    mp_M09_AXI_transactor->WVALID(M09_AXI_wvalid);
    mp_M09_AXI_transactor->WREADY(M09_AXI_wready);
    mp_M09_AXI_transactor->BRESP(M09_AXI_bresp);
    mp_M09_AXI_transactor->BVALID(M09_AXI_bvalid);
    mp_M09_AXI_transactor->BREADY(M09_AXI_bready);
    mp_M09_AXI_transactor->ARADDR(M09_AXI_araddr);
    mp_M09_AXI_transactor->ARPROT(M09_AXI_arprot);
    mp_M09_AXI_transactor->ARVALID(M09_AXI_arvalid);
    mp_M09_AXI_transactor->ARREADY(M09_AXI_arready);
    mp_M09_AXI_transactor->RDATA(M09_AXI_rdata);
    mp_M09_AXI_transactor->RRESP(M09_AXI_rresp);
    mp_M09_AXI_transactor->RVALID(M09_AXI_rvalid);
    mp_M09_AXI_transactor->RREADY(M09_AXI_rready);
    mp_M09_AXI_transactor->CLK(aclk2);
    mp_M09_AXI_transactor->RST(aresetn);

    // M09_AXI' transactor sockets

    mp_impl->M09_AXI_tlm_aximm_read_socket->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_impl->M09_AXI_tlm_aximm_write_socket->bind(*(mp_M09_AXI_transactor->wr_socket));
  }

  // configure 'M10_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M10_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M10_AXI' transactor parameters
    xsc::common_cpp::properties M10_AXI_transactor_param_props;
    M10_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    M10_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M10_AXI_transactor_param_props.addLong("ID_WIDTH", "3");
    M10_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M10_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("WUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("RUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("BUSER_WIDTH", "114");
    M10_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M10_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M10_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M10_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M10_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M10_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M10_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M10_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M10_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M10_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M10_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M10_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M10_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M10_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M10_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,3,130,14,114,130,14>("M10_AXI_transactor", M10_AXI_transactor_param_props);

    // M10_AXI' transactor ports

    mp_M10_AXI_transactor->AWID(M10_AXI_awid);
    mp_M10_AXI_transactor->AWADDR(M10_AXI_awaddr);
    mp_M10_AXI_transactor->AWLEN(M10_AXI_awlen);
    mp_M10_AXI_transactor->AWSIZE(M10_AXI_awsize);
    mp_M10_AXI_transactor->AWBURST(M10_AXI_awburst);
    mp_M10_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_awlock_converter");
    mp_M10_AXI_awlock_converter->scalar_in(m_M10_AXI_awlock_converter_signal);
    mp_M10_AXI_awlock_converter->vector_out(M10_AXI_awlock);
    mp_M10_AXI_transactor->AWLOCK(m_M10_AXI_awlock_converter_signal);
    mp_M10_AXI_transactor->AWCACHE(M10_AXI_awcache);
    mp_M10_AXI_transactor->AWPROT(M10_AXI_awprot);
    mp_M10_AXI_transactor->AWQOS(M10_AXI_awqos);
    mp_M10_AXI_transactor->AWUSER(M10_AXI_awuser);
    mp_M10_AXI_transactor->AWVALID(M10_AXI_awvalid);
    mp_M10_AXI_transactor->AWREADY(M10_AXI_awready);
    mp_M10_AXI_transactor->WDATA(M10_AXI_wdata);
    mp_M10_AXI_transactor->WSTRB(M10_AXI_wstrb);
    mp_M10_AXI_transactor->WLAST(M10_AXI_wlast);
    mp_M10_AXI_transactor->WUSER(M10_AXI_wuser);
    mp_M10_AXI_transactor->WVALID(M10_AXI_wvalid);
    mp_M10_AXI_transactor->WREADY(M10_AXI_wready);
    mp_M10_AXI_transactor->BID(M10_AXI_bid);
    mp_M10_AXI_transactor->BRESP(M10_AXI_bresp);
    mp_M10_AXI_transactor->BUSER(M10_AXI_buser);
    mp_M10_AXI_transactor->BVALID(M10_AXI_bvalid);
    mp_M10_AXI_transactor->BREADY(M10_AXI_bready);
    mp_M10_AXI_transactor->ARID(M10_AXI_arid);
    mp_M10_AXI_transactor->ARADDR(M10_AXI_araddr);
    mp_M10_AXI_transactor->ARLEN(M10_AXI_arlen);
    mp_M10_AXI_transactor->ARSIZE(M10_AXI_arsize);
    mp_M10_AXI_transactor->ARBURST(M10_AXI_arburst);
    mp_M10_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_arlock_converter");
    mp_M10_AXI_arlock_converter->scalar_in(m_M10_AXI_arlock_converter_signal);
    mp_M10_AXI_arlock_converter->vector_out(M10_AXI_arlock);
    mp_M10_AXI_transactor->ARLOCK(m_M10_AXI_arlock_converter_signal);
    mp_M10_AXI_transactor->ARCACHE(M10_AXI_arcache);
    mp_M10_AXI_transactor->ARPROT(M10_AXI_arprot);
    mp_M10_AXI_transactor->ARQOS(M10_AXI_arqos);
    mp_M10_AXI_transactor->ARUSER(M10_AXI_aruser);
    mp_M10_AXI_transactor->ARVALID(M10_AXI_arvalid);
    mp_M10_AXI_transactor->ARREADY(M10_AXI_arready);
    mp_M10_AXI_transactor->RID(M10_AXI_rid);
    mp_M10_AXI_transactor->RDATA(M10_AXI_rdata);
    mp_M10_AXI_transactor->RRESP(M10_AXI_rresp);
    mp_M10_AXI_transactor->RLAST(M10_AXI_rlast);
    mp_M10_AXI_transactor->RUSER(M10_AXI_ruser);
    mp_M10_AXI_transactor->RVALID(M10_AXI_rvalid);
    mp_M10_AXI_transactor->RREADY(M10_AXI_rready);
    mp_M10_AXI_transactor->CLK(aclk);
    mp_M10_AXI_transactor->RST(aresetn);

    // M10_AXI' transactor sockets

    mp_impl->M10_AXI_tlm_aximm_read_socket->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_impl->M10_AXI_tlm_aximm_write_socket->bind(*(mp_M10_AXI_transactor->wr_socket));
  }

  // configure 'M11_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M11_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M11_AXI' transactor parameters
    xsc::common_cpp::properties M11_AXI_transactor_param_props;
    M11_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M11_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M11_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M11_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M11_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M11_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M11_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M11_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M11_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M11_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M11_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M11_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M11_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M11_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M11_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M11_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M11_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M11_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M11_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M11_AXI_transactor", M11_AXI_transactor_param_props);

    // M11_AXI' transactor ports

    mp_M11_AXI_transactor->AWADDR(M11_AXI_awaddr);
    mp_M11_AXI_transactor->AWPROT(M11_AXI_awprot);
    mp_M11_AXI_transactor->AWVALID(M11_AXI_awvalid);
    mp_M11_AXI_transactor->AWREADY(M11_AXI_awready);
    mp_M11_AXI_transactor->WDATA(M11_AXI_wdata);
    mp_M11_AXI_transactor->WSTRB(M11_AXI_wstrb);
    mp_M11_AXI_transactor->WVALID(M11_AXI_wvalid);
    mp_M11_AXI_transactor->WREADY(M11_AXI_wready);
    mp_M11_AXI_transactor->BRESP(M11_AXI_bresp);
    mp_M11_AXI_transactor->BVALID(M11_AXI_bvalid);
    mp_M11_AXI_transactor->BREADY(M11_AXI_bready);
    mp_M11_AXI_transactor->ARADDR(M11_AXI_araddr);
    mp_M11_AXI_transactor->ARPROT(M11_AXI_arprot);
    mp_M11_AXI_transactor->ARVALID(M11_AXI_arvalid);
    mp_M11_AXI_transactor->ARREADY(M11_AXI_arready);
    mp_M11_AXI_transactor->RDATA(M11_AXI_rdata);
    mp_M11_AXI_transactor->RRESP(M11_AXI_rresp);
    mp_M11_AXI_transactor->RVALID(M11_AXI_rvalid);
    mp_M11_AXI_transactor->RREADY(M11_AXI_rready);
    mp_M11_AXI_transactor->CLK(aclk);
    mp_M11_AXI_transactor->RST(aresetn);

    // M11_AXI' transactor sockets

    mp_impl->M11_AXI_tlm_aximm_read_socket->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_impl->M11_AXI_tlm_aximm_write_socket->bind(*(mp_M11_AXI_transactor->wr_socket));
  }

  // configure 'M12_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M12_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M12_AXI' transactor parameters
    xsc::common_cpp::properties M12_AXI_transactor_param_props;
    M12_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M12_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M12_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M12_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M12_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M12_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M12_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M12_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M12_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M12_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M12_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M12_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M12_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M12_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M12_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M12_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M12_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M12_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M12_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M12_AXI_transactor", M12_AXI_transactor_param_props);

    // M12_AXI' transactor ports

    mp_M12_AXI_transactor->AWADDR(M12_AXI_awaddr);
    mp_M12_AXI_transactor->AWPROT(M12_AXI_awprot);
    mp_M12_AXI_transactor->AWVALID(M12_AXI_awvalid);
    mp_M12_AXI_transactor->AWREADY(M12_AXI_awready);
    mp_M12_AXI_transactor->WDATA(M12_AXI_wdata);
    mp_M12_AXI_transactor->WSTRB(M12_AXI_wstrb);
    mp_M12_AXI_transactor->WVALID(M12_AXI_wvalid);
    mp_M12_AXI_transactor->WREADY(M12_AXI_wready);
    mp_M12_AXI_transactor->BRESP(M12_AXI_bresp);
    mp_M12_AXI_transactor->BVALID(M12_AXI_bvalid);
    mp_M12_AXI_transactor->BREADY(M12_AXI_bready);
    mp_M12_AXI_transactor->ARADDR(M12_AXI_araddr);
    mp_M12_AXI_transactor->ARPROT(M12_AXI_arprot);
    mp_M12_AXI_transactor->ARVALID(M12_AXI_arvalid);
    mp_M12_AXI_transactor->ARREADY(M12_AXI_arready);
    mp_M12_AXI_transactor->RDATA(M12_AXI_rdata);
    mp_M12_AXI_transactor->RRESP(M12_AXI_rresp);
    mp_M12_AXI_transactor->RVALID(M12_AXI_rvalid);
    mp_M12_AXI_transactor->RREADY(M12_AXI_rready);
    mp_M12_AXI_transactor->CLK(aclk);
    mp_M12_AXI_transactor->RST(aresetn);

    // M12_AXI' transactor sockets

    mp_impl->M12_AXI_tlm_aximm_read_socket->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_impl->M12_AXI_tlm_aximm_write_socket->bind(*(mp_M12_AXI_transactor->wr_socket));
  }

  // configure 'M13_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M13_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M13_AXI' transactor parameters
    xsc::common_cpp::properties M13_AXI_transactor_param_props;
    M13_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M13_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M13_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M13_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M13_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M13_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M13_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M13_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M13_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M13_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M13_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M13_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M13_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M13_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M13_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M13_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M13_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M13_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M13_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M13_AXI_transactor", M13_AXI_transactor_param_props);

    // M13_AXI' transactor ports

    mp_M13_AXI_transactor->AWADDR(M13_AXI_awaddr);
    mp_M13_AXI_transactor->AWPROT(M13_AXI_awprot);
    mp_M13_AXI_transactor->AWVALID(M13_AXI_awvalid);
    mp_M13_AXI_transactor->AWREADY(M13_AXI_awready);
    mp_M13_AXI_transactor->WDATA(M13_AXI_wdata);
    mp_M13_AXI_transactor->WSTRB(M13_AXI_wstrb);
    mp_M13_AXI_transactor->WVALID(M13_AXI_wvalid);
    mp_M13_AXI_transactor->WREADY(M13_AXI_wready);
    mp_M13_AXI_transactor->BRESP(M13_AXI_bresp);
    mp_M13_AXI_transactor->BVALID(M13_AXI_bvalid);
    mp_M13_AXI_transactor->BREADY(M13_AXI_bready);
    mp_M13_AXI_transactor->ARADDR(M13_AXI_araddr);
    mp_M13_AXI_transactor->ARPROT(M13_AXI_arprot);
    mp_M13_AXI_transactor->ARVALID(M13_AXI_arvalid);
    mp_M13_AXI_transactor->ARREADY(M13_AXI_arready);
    mp_M13_AXI_transactor->RDATA(M13_AXI_rdata);
    mp_M13_AXI_transactor->RRESP(M13_AXI_rresp);
    mp_M13_AXI_transactor->RVALID(M13_AXI_rvalid);
    mp_M13_AXI_transactor->RREADY(M13_AXI_rready);
    mp_M13_AXI_transactor->CLK(aclk);
    mp_M13_AXI_transactor->RST(aresetn);

    // M13_AXI' transactor sockets

    mp_impl->M13_AXI_tlm_aximm_read_socket->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_impl->M13_AXI_tlm_aximm_write_socket->bind(*(mp_M13_AXI_transactor->wr_socket));
  }

  // configure 'M14_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M14_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M14_AXI' transactor parameters
    xsc::common_cpp::properties M14_AXI_transactor_param_props;
    M14_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M14_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M14_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M14_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M14_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M14_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M14_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M14_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M14_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M14_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M14_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M14_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M14_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M14_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M14_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M14_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M14_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M14_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M14_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M14_AXI_transactor", M14_AXI_transactor_param_props);

    // M14_AXI' transactor ports

    mp_M14_AXI_transactor->AWADDR(M14_AXI_awaddr);
    mp_M14_AXI_transactor->AWPROT(M14_AXI_awprot);
    mp_M14_AXI_transactor->AWVALID(M14_AXI_awvalid);
    mp_M14_AXI_transactor->AWREADY(M14_AXI_awready);
    mp_M14_AXI_transactor->WDATA(M14_AXI_wdata);
    mp_M14_AXI_transactor->WSTRB(M14_AXI_wstrb);
    mp_M14_AXI_transactor->WVALID(M14_AXI_wvalid);
    mp_M14_AXI_transactor->WREADY(M14_AXI_wready);
    mp_M14_AXI_transactor->BRESP(M14_AXI_bresp);
    mp_M14_AXI_transactor->BVALID(M14_AXI_bvalid);
    mp_M14_AXI_transactor->BREADY(M14_AXI_bready);
    mp_M14_AXI_transactor->ARADDR(M14_AXI_araddr);
    mp_M14_AXI_transactor->ARPROT(M14_AXI_arprot);
    mp_M14_AXI_transactor->ARVALID(M14_AXI_arvalid);
    mp_M14_AXI_transactor->ARREADY(M14_AXI_arready);
    mp_M14_AXI_transactor->RDATA(M14_AXI_rdata);
    mp_M14_AXI_transactor->RRESP(M14_AXI_rresp);
    mp_M14_AXI_transactor->RVALID(M14_AXI_rvalid);
    mp_M14_AXI_transactor->RREADY(M14_AXI_rready);
    mp_M14_AXI_transactor->CLK(aclk);
    mp_M14_AXI_transactor->RST(aresetn);

    // M14_AXI' transactor sockets

    mp_impl->M14_AXI_tlm_aximm_read_socket->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_impl->M14_AXI_tlm_aximm_write_socket->bind(*(mp_M14_AXI_transactor->wr_socket));
  }

}

#endif // XILINX_SIMULATOR




#ifdef XM_SYSTEMC
zusys_smartconnect_0_0::zusys_smartconnect_0_0(const sc_core::sc_module_name& nm) : zusys_smartconnect_0_0_sc(nm), aclk("aclk"), aclk1("aclk1"), aclk2("aclk2"), aresetn("aresetn"), S00_AXI_awid("S00_AXI_awid"), S00_AXI_awaddr("S00_AXI_awaddr"), S00_AXI_awlen("S00_AXI_awlen"), S00_AXI_awsize("S00_AXI_awsize"), S00_AXI_awburst("S00_AXI_awburst"), S00_AXI_awlock("S00_AXI_awlock"), S00_AXI_awcache("S00_AXI_awcache"), S00_AXI_awprot("S00_AXI_awprot"), S00_AXI_awqos("S00_AXI_awqos"), S00_AXI_awuser("S00_AXI_awuser"), S00_AXI_awvalid("S00_AXI_awvalid"), S00_AXI_awready("S00_AXI_awready"), S00_AXI_wdata("S00_AXI_wdata"), S00_AXI_wstrb("S00_AXI_wstrb"), S00_AXI_wlast("S00_AXI_wlast"), S00_AXI_wvalid("S00_AXI_wvalid"), S00_AXI_wready("S00_AXI_wready"), S00_AXI_bid("S00_AXI_bid"), S00_AXI_bresp("S00_AXI_bresp"), S00_AXI_bvalid("S00_AXI_bvalid"), S00_AXI_bready("S00_AXI_bready"), S00_AXI_arid("S00_AXI_arid"), S00_AXI_araddr("S00_AXI_araddr"), S00_AXI_arlen("S00_AXI_arlen"), S00_AXI_arsize("S00_AXI_arsize"), S00_AXI_arburst("S00_AXI_arburst"), S00_AXI_arlock("S00_AXI_arlock"), S00_AXI_arcache("S00_AXI_arcache"), S00_AXI_arprot("S00_AXI_arprot"), S00_AXI_arqos("S00_AXI_arqos"), S00_AXI_aruser("S00_AXI_aruser"), S00_AXI_arvalid("S00_AXI_arvalid"), S00_AXI_arready("S00_AXI_arready"), S00_AXI_rid("S00_AXI_rid"), S00_AXI_rdata("S00_AXI_rdata"), S00_AXI_rresp("S00_AXI_rresp"), S00_AXI_rlast("S00_AXI_rlast"), S00_AXI_rvalid("S00_AXI_rvalid"), S00_AXI_rready("S00_AXI_rready"), M00_AXI_awaddr("M00_AXI_awaddr"), M00_AXI_awprot("M00_AXI_awprot"), M00_AXI_awvalid("M00_AXI_awvalid"), M00_AXI_awready("M00_AXI_awready"), M00_AXI_wdata("M00_AXI_wdata"), M00_AXI_wstrb("M00_AXI_wstrb"), M00_AXI_wvalid("M00_AXI_wvalid"), M00_AXI_wready("M00_AXI_wready"), M00_AXI_bresp("M00_AXI_bresp"), M00_AXI_bvalid("M00_AXI_bvalid"), M00_AXI_bready("M00_AXI_bready"), M00_AXI_araddr("M00_AXI_araddr"), M00_AXI_arprot("M00_AXI_arprot"), M00_AXI_arvalid("M00_AXI_arvalid"), M00_AXI_arready("M00_AXI_arready"), M00_AXI_rdata("M00_AXI_rdata"), M00_AXI_rresp("M00_AXI_rresp"), M00_AXI_rvalid("M00_AXI_rvalid"), M00_AXI_rready("M00_AXI_rready"), M01_AXI_awaddr("M01_AXI_awaddr"), M01_AXI_awprot("M01_AXI_awprot"), M01_AXI_awvalid("M01_AXI_awvalid"), M01_AXI_awready("M01_AXI_awready"), M01_AXI_wdata("M01_AXI_wdata"), M01_AXI_wstrb("M01_AXI_wstrb"), M01_AXI_wvalid("M01_AXI_wvalid"), M01_AXI_wready("M01_AXI_wready"), M01_AXI_bresp("M01_AXI_bresp"), M01_AXI_bvalid("M01_AXI_bvalid"), M01_AXI_bready("M01_AXI_bready"), M01_AXI_araddr("M01_AXI_araddr"), M01_AXI_arprot("M01_AXI_arprot"), M01_AXI_arvalid("M01_AXI_arvalid"), M01_AXI_arready("M01_AXI_arready"), M01_AXI_rdata("M01_AXI_rdata"), M01_AXI_rresp("M01_AXI_rresp"), M01_AXI_rvalid("M01_AXI_rvalid"), M01_AXI_rready("M01_AXI_rready"), M02_AXI_awaddr("M02_AXI_awaddr"), M02_AXI_awprot("M02_AXI_awprot"), M02_AXI_awvalid("M02_AXI_awvalid"), M02_AXI_awready("M02_AXI_awready"), M02_AXI_wdata("M02_AXI_wdata"), M02_AXI_wstrb("M02_AXI_wstrb"), M02_AXI_wvalid("M02_AXI_wvalid"), M02_AXI_wready("M02_AXI_wready"), M02_AXI_bresp("M02_AXI_bresp"), M02_AXI_bvalid("M02_AXI_bvalid"), M02_AXI_bready("M02_AXI_bready"), M02_AXI_araddr("M02_AXI_araddr"), M02_AXI_arprot("M02_AXI_arprot"), M02_AXI_arvalid("M02_AXI_arvalid"), M02_AXI_arready("M02_AXI_arready"), M02_AXI_rdata("M02_AXI_rdata"), M02_AXI_rresp("M02_AXI_rresp"), M02_AXI_rvalid("M02_AXI_rvalid"), M02_AXI_rready("M02_AXI_rready"), M03_AXI_awaddr("M03_AXI_awaddr"), M03_AXI_awprot("M03_AXI_awprot"), M03_AXI_awvalid("M03_AXI_awvalid"), M03_AXI_awready("M03_AXI_awready"), M03_AXI_wdata("M03_AXI_wdata"), M03_AXI_wstrb("M03_AXI_wstrb"), M03_AXI_wvalid("M03_AXI_wvalid"), M03_AXI_wready("M03_AXI_wready"), M03_AXI_bresp("M03_AXI_bresp"), M03_AXI_bvalid("M03_AXI_bvalid"), M03_AXI_bready("M03_AXI_bready"), M03_AXI_araddr("M03_AXI_araddr"), M03_AXI_arprot("M03_AXI_arprot"), M03_AXI_arvalid("M03_AXI_arvalid"), M03_AXI_arready("M03_AXI_arready"), M03_AXI_rdata("M03_AXI_rdata"), M03_AXI_rresp("M03_AXI_rresp"), M03_AXI_rvalid("M03_AXI_rvalid"), M03_AXI_rready("M03_AXI_rready"), M04_AXI_awaddr("M04_AXI_awaddr"), M04_AXI_awprot("M04_AXI_awprot"), M04_AXI_awvalid("M04_AXI_awvalid"), M04_AXI_awready("M04_AXI_awready"), M04_AXI_wdata("M04_AXI_wdata"), M04_AXI_wstrb("M04_AXI_wstrb"), M04_AXI_wvalid("M04_AXI_wvalid"), M04_AXI_wready("M04_AXI_wready"), M04_AXI_bresp("M04_AXI_bresp"), M04_AXI_bvalid("M04_AXI_bvalid"), M04_AXI_bready("M04_AXI_bready"), M04_AXI_araddr("M04_AXI_araddr"), M04_AXI_arprot("M04_AXI_arprot"), M04_AXI_arvalid("M04_AXI_arvalid"), M04_AXI_arready("M04_AXI_arready"), M04_AXI_rdata("M04_AXI_rdata"), M04_AXI_rresp("M04_AXI_rresp"), M04_AXI_rvalid("M04_AXI_rvalid"), M04_AXI_rready("M04_AXI_rready"), M05_AXI_awaddr("M05_AXI_awaddr"), M05_AXI_awprot("M05_AXI_awprot"), M05_AXI_awvalid("M05_AXI_awvalid"), M05_AXI_awready("M05_AXI_awready"), M05_AXI_wdata("M05_AXI_wdata"), M05_AXI_wstrb("M05_AXI_wstrb"), M05_AXI_wvalid("M05_AXI_wvalid"), M05_AXI_wready("M05_AXI_wready"), M05_AXI_bresp("M05_AXI_bresp"), M05_AXI_bvalid("M05_AXI_bvalid"), M05_AXI_bready("M05_AXI_bready"), M05_AXI_araddr("M05_AXI_araddr"), M05_AXI_arprot("M05_AXI_arprot"), M05_AXI_arvalid("M05_AXI_arvalid"), M05_AXI_arready("M05_AXI_arready"), M05_AXI_rdata("M05_AXI_rdata"), M05_AXI_rresp("M05_AXI_rresp"), M05_AXI_rvalid("M05_AXI_rvalid"), M05_AXI_rready("M05_AXI_rready"), M06_AXI_awaddr("M06_AXI_awaddr"), M06_AXI_awprot("M06_AXI_awprot"), M06_AXI_awvalid("M06_AXI_awvalid"), M06_AXI_awready("M06_AXI_awready"), M06_AXI_wdata("M06_AXI_wdata"), M06_AXI_wstrb("M06_AXI_wstrb"), M06_AXI_wvalid("M06_AXI_wvalid"), M06_AXI_wready("M06_AXI_wready"), M06_AXI_bresp("M06_AXI_bresp"), M06_AXI_bvalid("M06_AXI_bvalid"), M06_AXI_bready("M06_AXI_bready"), M06_AXI_araddr("M06_AXI_araddr"), M06_AXI_arprot("M06_AXI_arprot"), M06_AXI_arvalid("M06_AXI_arvalid"), M06_AXI_arready("M06_AXI_arready"), M06_AXI_rdata("M06_AXI_rdata"), M06_AXI_rresp("M06_AXI_rresp"), M06_AXI_rvalid("M06_AXI_rvalid"), M06_AXI_rready("M06_AXI_rready"), M07_AXI_awaddr("M07_AXI_awaddr"), M07_AXI_awlen("M07_AXI_awlen"), M07_AXI_awsize("M07_AXI_awsize"), M07_AXI_awburst("M07_AXI_awburst"), M07_AXI_awlock("M07_AXI_awlock"), M07_AXI_awcache("M07_AXI_awcache"), M07_AXI_awprot("M07_AXI_awprot"), M07_AXI_awqos("M07_AXI_awqos"), M07_AXI_awuser("M07_AXI_awuser"), M07_AXI_awvalid("M07_AXI_awvalid"), M07_AXI_awready("M07_AXI_awready"), M07_AXI_wdata("M07_AXI_wdata"), M07_AXI_wstrb("M07_AXI_wstrb"), M07_AXI_wlast("M07_AXI_wlast"), M07_AXI_wvalid("M07_AXI_wvalid"), M07_AXI_wready("M07_AXI_wready"), M07_AXI_bresp("M07_AXI_bresp"), M07_AXI_bvalid("M07_AXI_bvalid"), M07_AXI_bready("M07_AXI_bready"), M07_AXI_araddr("M07_AXI_araddr"), M07_AXI_arlen("M07_AXI_arlen"), M07_AXI_arsize("M07_AXI_arsize"), M07_AXI_arburst("M07_AXI_arburst"), M07_AXI_arlock("M07_AXI_arlock"), M07_AXI_arcache("M07_AXI_arcache"), M07_AXI_arprot("M07_AXI_arprot"), M07_AXI_arqos("M07_AXI_arqos"), M07_AXI_aruser("M07_AXI_aruser"), M07_AXI_arvalid("M07_AXI_arvalid"), M07_AXI_arready("M07_AXI_arready"), M07_AXI_rdata("M07_AXI_rdata"), M07_AXI_rresp("M07_AXI_rresp"), M07_AXI_rlast("M07_AXI_rlast"), M07_AXI_rvalid("M07_AXI_rvalid"), M07_AXI_rready("M07_AXI_rready"), M08_AXI_awaddr("M08_AXI_awaddr"), M08_AXI_awprot("M08_AXI_awprot"), M08_AXI_awvalid("M08_AXI_awvalid"), M08_AXI_awready("M08_AXI_awready"), M08_AXI_wdata("M08_AXI_wdata"), M08_AXI_wstrb("M08_AXI_wstrb"), M08_AXI_wvalid("M08_AXI_wvalid"), M08_AXI_wready("M08_AXI_wready"), M08_AXI_bresp("M08_AXI_bresp"), M08_AXI_bvalid("M08_AXI_bvalid"), M08_AXI_bready("M08_AXI_bready"), M08_AXI_araddr("M08_AXI_araddr"), M08_AXI_arprot("M08_AXI_arprot"), M08_AXI_arvalid("M08_AXI_arvalid"), M08_AXI_arready("M08_AXI_arready"), M08_AXI_rdata("M08_AXI_rdata"), M08_AXI_rresp("M08_AXI_rresp"), M08_AXI_rvalid("M08_AXI_rvalid"), M08_AXI_rready("M08_AXI_rready"), M09_AXI_awaddr("M09_AXI_awaddr"), M09_AXI_awprot("M09_AXI_awprot"), M09_AXI_awvalid("M09_AXI_awvalid"), M09_AXI_awready("M09_AXI_awready"), M09_AXI_wdata("M09_AXI_wdata"), M09_AXI_wstrb("M09_AXI_wstrb"), M09_AXI_wvalid("M09_AXI_wvalid"), M09_AXI_wready("M09_AXI_wready"), M09_AXI_bresp("M09_AXI_bresp"), M09_AXI_bvalid("M09_AXI_bvalid"), M09_AXI_bready("M09_AXI_bready"), M09_AXI_araddr("M09_AXI_araddr"), M09_AXI_arprot("M09_AXI_arprot"), M09_AXI_arvalid("M09_AXI_arvalid"), M09_AXI_arready("M09_AXI_arready"), M09_AXI_rdata("M09_AXI_rdata"), M09_AXI_rresp("M09_AXI_rresp"), M09_AXI_rvalid("M09_AXI_rvalid"), M09_AXI_rready("M09_AXI_rready"), M10_AXI_awid("M10_AXI_awid"), M10_AXI_awaddr("M10_AXI_awaddr"), M10_AXI_awlen("M10_AXI_awlen"), M10_AXI_awsize("M10_AXI_awsize"), M10_AXI_awburst("M10_AXI_awburst"), M10_AXI_awlock("M10_AXI_awlock"), M10_AXI_awcache("M10_AXI_awcache"), M10_AXI_awprot("M10_AXI_awprot"), M10_AXI_awqos("M10_AXI_awqos"), M10_AXI_awuser("M10_AXI_awuser"), M10_AXI_awvalid("M10_AXI_awvalid"), M10_AXI_awready("M10_AXI_awready"), M10_AXI_wdata("M10_AXI_wdata"), M10_AXI_wstrb("M10_AXI_wstrb"), M10_AXI_wlast("M10_AXI_wlast"), M10_AXI_wuser("M10_AXI_wuser"), M10_AXI_wvalid("M10_AXI_wvalid"), M10_AXI_wready("M10_AXI_wready"), M10_AXI_bid("M10_AXI_bid"), M10_AXI_bresp("M10_AXI_bresp"), M10_AXI_buser("M10_AXI_buser"), M10_AXI_bvalid("M10_AXI_bvalid"), M10_AXI_bready("M10_AXI_bready"), M10_AXI_arid("M10_AXI_arid"), M10_AXI_araddr("M10_AXI_araddr"), M10_AXI_arlen("M10_AXI_arlen"), M10_AXI_arsize("M10_AXI_arsize"), M10_AXI_arburst("M10_AXI_arburst"), M10_AXI_arlock("M10_AXI_arlock"), M10_AXI_arcache("M10_AXI_arcache"), M10_AXI_arprot("M10_AXI_arprot"), M10_AXI_arqos("M10_AXI_arqos"), M10_AXI_aruser("M10_AXI_aruser"), M10_AXI_arvalid("M10_AXI_arvalid"), M10_AXI_arready("M10_AXI_arready"), M10_AXI_rid("M10_AXI_rid"), M10_AXI_rdata("M10_AXI_rdata"), M10_AXI_rresp("M10_AXI_rresp"), M10_AXI_rlast("M10_AXI_rlast"), M10_AXI_ruser("M10_AXI_ruser"), M10_AXI_rvalid("M10_AXI_rvalid"), M10_AXI_rready("M10_AXI_rready"), M11_AXI_awaddr("M11_AXI_awaddr"), M11_AXI_awprot("M11_AXI_awprot"), M11_AXI_awvalid("M11_AXI_awvalid"), M11_AXI_awready("M11_AXI_awready"), M11_AXI_wdata("M11_AXI_wdata"), M11_AXI_wstrb("M11_AXI_wstrb"), M11_AXI_wvalid("M11_AXI_wvalid"), M11_AXI_wready("M11_AXI_wready"), M11_AXI_bresp("M11_AXI_bresp"), M11_AXI_bvalid("M11_AXI_bvalid"), M11_AXI_bready("M11_AXI_bready"), M11_AXI_araddr("M11_AXI_araddr"), M11_AXI_arprot("M11_AXI_arprot"), M11_AXI_arvalid("M11_AXI_arvalid"), M11_AXI_arready("M11_AXI_arready"), M11_AXI_rdata("M11_AXI_rdata"), M11_AXI_rresp("M11_AXI_rresp"), M11_AXI_rvalid("M11_AXI_rvalid"), M11_AXI_rready("M11_AXI_rready"), M12_AXI_awaddr("M12_AXI_awaddr"), M12_AXI_awprot("M12_AXI_awprot"), M12_AXI_awvalid("M12_AXI_awvalid"), M12_AXI_awready("M12_AXI_awready"), M12_AXI_wdata("M12_AXI_wdata"), M12_AXI_wstrb("M12_AXI_wstrb"), M12_AXI_wvalid("M12_AXI_wvalid"), M12_AXI_wready("M12_AXI_wready"), M12_AXI_bresp("M12_AXI_bresp"), M12_AXI_bvalid("M12_AXI_bvalid"), M12_AXI_bready("M12_AXI_bready"), M12_AXI_araddr("M12_AXI_araddr"), M12_AXI_arprot("M12_AXI_arprot"), M12_AXI_arvalid("M12_AXI_arvalid"), M12_AXI_arready("M12_AXI_arready"), M12_AXI_rdata("M12_AXI_rdata"), M12_AXI_rresp("M12_AXI_rresp"), M12_AXI_rvalid("M12_AXI_rvalid"), M12_AXI_rready("M12_AXI_rready"), M13_AXI_awaddr("M13_AXI_awaddr"), M13_AXI_awprot("M13_AXI_awprot"), M13_AXI_awvalid("M13_AXI_awvalid"), M13_AXI_awready("M13_AXI_awready"), M13_AXI_wdata("M13_AXI_wdata"), M13_AXI_wstrb("M13_AXI_wstrb"), M13_AXI_wvalid("M13_AXI_wvalid"), M13_AXI_wready("M13_AXI_wready"), M13_AXI_bresp("M13_AXI_bresp"), M13_AXI_bvalid("M13_AXI_bvalid"), M13_AXI_bready("M13_AXI_bready"), M13_AXI_araddr("M13_AXI_araddr"), M13_AXI_arprot("M13_AXI_arprot"), M13_AXI_arvalid("M13_AXI_arvalid"), M13_AXI_arready("M13_AXI_arready"), M13_AXI_rdata("M13_AXI_rdata"), M13_AXI_rresp("M13_AXI_rresp"), M13_AXI_rvalid("M13_AXI_rvalid"), M13_AXI_rready("M13_AXI_rready"), M14_AXI_awaddr("M14_AXI_awaddr"), M14_AXI_awprot("M14_AXI_awprot"), M14_AXI_awvalid("M14_AXI_awvalid"), M14_AXI_awready("M14_AXI_awready"), M14_AXI_wdata("M14_AXI_wdata"), M14_AXI_wstrb("M14_AXI_wstrb"), M14_AXI_wvalid("M14_AXI_wvalid"), M14_AXI_wready("M14_AXI_wready"), M14_AXI_bresp("M14_AXI_bresp"), M14_AXI_bvalid("M14_AXI_bvalid"), M14_AXI_bready("M14_AXI_bready"), M14_AXI_araddr("M14_AXI_araddr"), M14_AXI_arprot("M14_AXI_arprot"), M14_AXI_arvalid("M14_AXI_arvalid"), M14_AXI_arready("M14_AXI_arready"), M14_AXI_rdata("M14_AXI_rdata"), M14_AXI_rresp("M14_AXI_rresp"), M14_AXI_rvalid("M14_AXI_rvalid"), M14_AXI_rready("M14_AXI_rready")
{

  // initialize pins
  mp_impl->aclk(aclk);
  mp_impl->aclk1(aclk1);
  mp_impl->aclk2(aclk2);
  mp_impl->aresetn(aresetn);

  // initialize transactors
  mp_S00_AXI_transactor = NULL;
  mp_S00_AXI_awlock_converter = NULL;
  mp_S00_AXI_arlock_converter = NULL;
  mp_M00_AXI_transactor = NULL;
  mp_M01_AXI_transactor = NULL;
  mp_M02_AXI_transactor = NULL;
  mp_M03_AXI_transactor = NULL;
  mp_M04_AXI_transactor = NULL;
  mp_M05_AXI_transactor = NULL;
  mp_M06_AXI_transactor = NULL;
  mp_M07_AXI_transactor = NULL;
  mp_M07_AXI_awlock_converter = NULL;
  mp_M07_AXI_arlock_converter = NULL;
  mp_M08_AXI_transactor = NULL;
  mp_M09_AXI_transactor = NULL;
  mp_M10_AXI_transactor = NULL;
  mp_M10_AXI_awlock_converter = NULL;
  mp_M10_AXI_arlock_converter = NULL;
  mp_M11_AXI_transactor = NULL;
  mp_M12_AXI_transactor = NULL;
  mp_M13_AXI_transactor = NULL;
  mp_M14_AXI_transactor = NULL;

  // initialize socket stubs

}

void zusys_smartconnect_0_0::before_end_of_elaboration()
{
  // configure 'S00_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "S00_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'S00_AXI' transactor parameters
    xsc::common_cpp::properties S00_AXI_transactor_param_props;
    S00_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    S00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S00_AXI_transactor_param_props.addLong("ID_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    S00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    S00_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    S00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    S00_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    S00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    S00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    S00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    S00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    S00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    S00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    S00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    S00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S00_AXI_transactor = new xtlm::xaximm_pin2xtlm_t<128,40,16,16,1,1,16,1>("S00_AXI_transactor", S00_AXI_transactor_param_props);

    // S00_AXI' transactor ports

    mp_S00_AXI_transactor->AWID(S00_AXI_awid);
    mp_S00_AXI_transactor->AWADDR(S00_AXI_awaddr);
    mp_S00_AXI_transactor->AWLEN(S00_AXI_awlen);
    mp_S00_AXI_transactor->AWSIZE(S00_AXI_awsize);
    mp_S00_AXI_transactor->AWBURST(S00_AXI_awburst);
    mp_S00_AXI_awlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_awlock_converter");
    mp_S00_AXI_awlock_converter->vector_in(S00_AXI_awlock);
    mp_S00_AXI_awlock_converter->scalar_out(m_S00_AXI_awlock_converter_signal);
    mp_S00_AXI_transactor->AWLOCK(m_S00_AXI_awlock_converter_signal);
    mp_S00_AXI_transactor->AWCACHE(S00_AXI_awcache);
    mp_S00_AXI_transactor->AWPROT(S00_AXI_awprot);
    mp_S00_AXI_transactor->AWQOS(S00_AXI_awqos);
    mp_S00_AXI_transactor->AWUSER(S00_AXI_awuser);
    mp_S00_AXI_transactor->AWVALID(S00_AXI_awvalid);
    mp_S00_AXI_transactor->AWREADY(S00_AXI_awready);
    mp_S00_AXI_transactor->WDATA(S00_AXI_wdata);
    mp_S00_AXI_transactor->WSTRB(S00_AXI_wstrb);
    mp_S00_AXI_transactor->WLAST(S00_AXI_wlast);
    mp_S00_AXI_transactor->WVALID(S00_AXI_wvalid);
    mp_S00_AXI_transactor->WREADY(S00_AXI_wready);
    mp_S00_AXI_transactor->BID(S00_AXI_bid);
    mp_S00_AXI_transactor->BRESP(S00_AXI_bresp);
    mp_S00_AXI_transactor->BVALID(S00_AXI_bvalid);
    mp_S00_AXI_transactor->BREADY(S00_AXI_bready);
    mp_S00_AXI_transactor->ARID(S00_AXI_arid);
    mp_S00_AXI_transactor->ARADDR(S00_AXI_araddr);
    mp_S00_AXI_transactor->ARLEN(S00_AXI_arlen);
    mp_S00_AXI_transactor->ARSIZE(S00_AXI_arsize);
    mp_S00_AXI_transactor->ARBURST(S00_AXI_arburst);
    mp_S00_AXI_arlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_arlock_converter");
    mp_S00_AXI_arlock_converter->vector_in(S00_AXI_arlock);
    mp_S00_AXI_arlock_converter->scalar_out(m_S00_AXI_arlock_converter_signal);
    mp_S00_AXI_transactor->ARLOCK(m_S00_AXI_arlock_converter_signal);
    mp_S00_AXI_transactor->ARCACHE(S00_AXI_arcache);
    mp_S00_AXI_transactor->ARPROT(S00_AXI_arprot);
    mp_S00_AXI_transactor->ARQOS(S00_AXI_arqos);
    mp_S00_AXI_transactor->ARUSER(S00_AXI_aruser);
    mp_S00_AXI_transactor->ARVALID(S00_AXI_arvalid);
    mp_S00_AXI_transactor->ARREADY(S00_AXI_arready);
    mp_S00_AXI_transactor->RID(S00_AXI_rid);
    mp_S00_AXI_transactor->RDATA(S00_AXI_rdata);
    mp_S00_AXI_transactor->RRESP(S00_AXI_rresp);
    mp_S00_AXI_transactor->RLAST(S00_AXI_rlast);
    mp_S00_AXI_transactor->RVALID(S00_AXI_rvalid);
    mp_S00_AXI_transactor->RREADY(S00_AXI_rready);
    mp_S00_AXI_transactor->CLK(aclk);
    mp_S00_AXI_transactor->RST(aresetn);

    // S00_AXI' transactor sockets

    mp_impl->S00_AXI_tlm_aximm_read_socket->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_impl->S00_AXI_tlm_aximm_write_socket->bind(*(mp_S00_AXI_transactor->wr_socket));
  }

  // configure 'M00_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M00_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M00_AXI' transactor parameters
    xsc::common_cpp::properties M00_AXI_transactor_param_props;
    M00_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M00_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M00_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M00_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M00_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M00_AXI_transactor", M00_AXI_transactor_param_props);

    // M00_AXI' transactor ports

    mp_M00_AXI_transactor->AWADDR(M00_AXI_awaddr);
    mp_M00_AXI_transactor->AWPROT(M00_AXI_awprot);
    mp_M00_AXI_transactor->AWVALID(M00_AXI_awvalid);
    mp_M00_AXI_transactor->AWREADY(M00_AXI_awready);
    mp_M00_AXI_transactor->WDATA(M00_AXI_wdata);
    mp_M00_AXI_transactor->WSTRB(M00_AXI_wstrb);
    mp_M00_AXI_transactor->WVALID(M00_AXI_wvalid);
    mp_M00_AXI_transactor->WREADY(M00_AXI_wready);
    mp_M00_AXI_transactor->BRESP(M00_AXI_bresp);
    mp_M00_AXI_transactor->BVALID(M00_AXI_bvalid);
    mp_M00_AXI_transactor->BREADY(M00_AXI_bready);
    mp_M00_AXI_transactor->ARADDR(M00_AXI_araddr);
    mp_M00_AXI_transactor->ARPROT(M00_AXI_arprot);
    mp_M00_AXI_transactor->ARVALID(M00_AXI_arvalid);
    mp_M00_AXI_transactor->ARREADY(M00_AXI_arready);
    mp_M00_AXI_transactor->RDATA(M00_AXI_rdata);
    mp_M00_AXI_transactor->RRESP(M00_AXI_rresp);
    mp_M00_AXI_transactor->RVALID(M00_AXI_rvalid);
    mp_M00_AXI_transactor->RREADY(M00_AXI_rready);
    mp_M00_AXI_transactor->CLK(aclk);
    mp_M00_AXI_transactor->RST(aresetn);

    // M00_AXI' transactor sockets

    mp_impl->M00_AXI_tlm_aximm_read_socket->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_impl->M00_AXI_tlm_aximm_write_socket->bind(*(mp_M00_AXI_transactor->wr_socket));
  }

  // configure 'M01_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M01_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M01_AXI' transactor parameters
    xsc::common_cpp::properties M01_AXI_transactor_param_props;
    M01_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M01_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M01_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M01_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M01_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M01_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M01_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M01_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M01_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M01_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M01_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M01_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M01_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M01_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M01_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M01_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M01_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M01_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M01_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M01_AXI_transactor", M01_AXI_transactor_param_props);

    // M01_AXI' transactor ports

    mp_M01_AXI_transactor->AWADDR(M01_AXI_awaddr);
    mp_M01_AXI_transactor->AWPROT(M01_AXI_awprot);
    mp_M01_AXI_transactor->AWVALID(M01_AXI_awvalid);
    mp_M01_AXI_transactor->AWREADY(M01_AXI_awready);
    mp_M01_AXI_transactor->WDATA(M01_AXI_wdata);
    mp_M01_AXI_transactor->WSTRB(M01_AXI_wstrb);
    mp_M01_AXI_transactor->WVALID(M01_AXI_wvalid);
    mp_M01_AXI_transactor->WREADY(M01_AXI_wready);
    mp_M01_AXI_transactor->BRESP(M01_AXI_bresp);
    mp_M01_AXI_transactor->BVALID(M01_AXI_bvalid);
    mp_M01_AXI_transactor->BREADY(M01_AXI_bready);
    mp_M01_AXI_transactor->ARADDR(M01_AXI_araddr);
    mp_M01_AXI_transactor->ARPROT(M01_AXI_arprot);
    mp_M01_AXI_transactor->ARVALID(M01_AXI_arvalid);
    mp_M01_AXI_transactor->ARREADY(M01_AXI_arready);
    mp_M01_AXI_transactor->RDATA(M01_AXI_rdata);
    mp_M01_AXI_transactor->RRESP(M01_AXI_rresp);
    mp_M01_AXI_transactor->RVALID(M01_AXI_rvalid);
    mp_M01_AXI_transactor->RREADY(M01_AXI_rready);
    mp_M01_AXI_transactor->CLK(aclk);
    mp_M01_AXI_transactor->RST(aresetn);

    // M01_AXI' transactor sockets

    mp_impl->M01_AXI_tlm_aximm_read_socket->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_impl->M01_AXI_tlm_aximm_write_socket->bind(*(mp_M01_AXI_transactor->wr_socket));
  }

  // configure 'M02_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M02_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M02_AXI' transactor parameters
    xsc::common_cpp::properties M02_AXI_transactor_param_props;
    M02_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M02_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M02_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M02_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M02_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M02_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M02_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M02_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M02_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M02_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M02_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M02_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M02_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M02_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M02_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M02_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M02_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M02_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M02_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M02_AXI_transactor", M02_AXI_transactor_param_props);

    // M02_AXI' transactor ports

    mp_M02_AXI_transactor->AWADDR(M02_AXI_awaddr);
    mp_M02_AXI_transactor->AWPROT(M02_AXI_awprot);
    mp_M02_AXI_transactor->AWVALID(M02_AXI_awvalid);
    mp_M02_AXI_transactor->AWREADY(M02_AXI_awready);
    mp_M02_AXI_transactor->WDATA(M02_AXI_wdata);
    mp_M02_AXI_transactor->WSTRB(M02_AXI_wstrb);
    mp_M02_AXI_transactor->WVALID(M02_AXI_wvalid);
    mp_M02_AXI_transactor->WREADY(M02_AXI_wready);
    mp_M02_AXI_transactor->BRESP(M02_AXI_bresp);
    mp_M02_AXI_transactor->BVALID(M02_AXI_bvalid);
    mp_M02_AXI_transactor->BREADY(M02_AXI_bready);
    mp_M02_AXI_transactor->ARADDR(M02_AXI_araddr);
    mp_M02_AXI_transactor->ARPROT(M02_AXI_arprot);
    mp_M02_AXI_transactor->ARVALID(M02_AXI_arvalid);
    mp_M02_AXI_transactor->ARREADY(M02_AXI_arready);
    mp_M02_AXI_transactor->RDATA(M02_AXI_rdata);
    mp_M02_AXI_transactor->RRESP(M02_AXI_rresp);
    mp_M02_AXI_transactor->RVALID(M02_AXI_rvalid);
    mp_M02_AXI_transactor->RREADY(M02_AXI_rready);
    mp_M02_AXI_transactor->CLK(aclk);
    mp_M02_AXI_transactor->RST(aresetn);

    // M02_AXI' transactor sockets

    mp_impl->M02_AXI_tlm_aximm_read_socket->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_impl->M02_AXI_tlm_aximm_write_socket->bind(*(mp_M02_AXI_transactor->wr_socket));
  }

  // configure 'M03_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M03_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M03_AXI' transactor parameters
    xsc::common_cpp::properties M03_AXI_transactor_param_props;
    M03_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M03_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M03_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M03_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M03_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M03_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M03_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M03_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M03_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M03_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M03_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M03_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M03_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M03_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M03_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M03_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M03_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M03_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M03_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M03_AXI_transactor", M03_AXI_transactor_param_props);

    // M03_AXI' transactor ports

    mp_M03_AXI_transactor->AWADDR(M03_AXI_awaddr);
    mp_M03_AXI_transactor->AWPROT(M03_AXI_awprot);
    mp_M03_AXI_transactor->AWVALID(M03_AXI_awvalid);
    mp_M03_AXI_transactor->AWREADY(M03_AXI_awready);
    mp_M03_AXI_transactor->WDATA(M03_AXI_wdata);
    mp_M03_AXI_transactor->WSTRB(M03_AXI_wstrb);
    mp_M03_AXI_transactor->WVALID(M03_AXI_wvalid);
    mp_M03_AXI_transactor->WREADY(M03_AXI_wready);
    mp_M03_AXI_transactor->BRESP(M03_AXI_bresp);
    mp_M03_AXI_transactor->BVALID(M03_AXI_bvalid);
    mp_M03_AXI_transactor->BREADY(M03_AXI_bready);
    mp_M03_AXI_transactor->ARADDR(M03_AXI_araddr);
    mp_M03_AXI_transactor->ARPROT(M03_AXI_arprot);
    mp_M03_AXI_transactor->ARVALID(M03_AXI_arvalid);
    mp_M03_AXI_transactor->ARREADY(M03_AXI_arready);
    mp_M03_AXI_transactor->RDATA(M03_AXI_rdata);
    mp_M03_AXI_transactor->RRESP(M03_AXI_rresp);
    mp_M03_AXI_transactor->RVALID(M03_AXI_rvalid);
    mp_M03_AXI_transactor->RREADY(M03_AXI_rready);
    mp_M03_AXI_transactor->CLK(aclk);
    mp_M03_AXI_transactor->RST(aresetn);

    // M03_AXI' transactor sockets

    mp_impl->M03_AXI_tlm_aximm_read_socket->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_impl->M03_AXI_tlm_aximm_write_socket->bind(*(mp_M03_AXI_transactor->wr_socket));
  }

  // configure 'M04_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M04_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M04_AXI' transactor parameters
    xsc::common_cpp::properties M04_AXI_transactor_param_props;
    M04_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M04_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M04_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M04_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M04_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M04_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M04_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M04_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M04_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M04_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M04_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M04_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M04_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M04_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M04_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M04_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M04_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M04_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M04_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M04_AXI_transactor", M04_AXI_transactor_param_props);

    // M04_AXI' transactor ports

    mp_M04_AXI_transactor->AWADDR(M04_AXI_awaddr);
    mp_M04_AXI_transactor->AWPROT(M04_AXI_awprot);
    mp_M04_AXI_transactor->AWVALID(M04_AXI_awvalid);
    mp_M04_AXI_transactor->AWREADY(M04_AXI_awready);
    mp_M04_AXI_transactor->WDATA(M04_AXI_wdata);
    mp_M04_AXI_transactor->WSTRB(M04_AXI_wstrb);
    mp_M04_AXI_transactor->WVALID(M04_AXI_wvalid);
    mp_M04_AXI_transactor->WREADY(M04_AXI_wready);
    mp_M04_AXI_transactor->BRESP(M04_AXI_bresp);
    mp_M04_AXI_transactor->BVALID(M04_AXI_bvalid);
    mp_M04_AXI_transactor->BREADY(M04_AXI_bready);
    mp_M04_AXI_transactor->ARADDR(M04_AXI_araddr);
    mp_M04_AXI_transactor->ARPROT(M04_AXI_arprot);
    mp_M04_AXI_transactor->ARVALID(M04_AXI_arvalid);
    mp_M04_AXI_transactor->ARREADY(M04_AXI_arready);
    mp_M04_AXI_transactor->RDATA(M04_AXI_rdata);
    mp_M04_AXI_transactor->RRESP(M04_AXI_rresp);
    mp_M04_AXI_transactor->RVALID(M04_AXI_rvalid);
    mp_M04_AXI_transactor->RREADY(M04_AXI_rready);
    mp_M04_AXI_transactor->CLK(aclk);
    mp_M04_AXI_transactor->RST(aresetn);

    // M04_AXI' transactor sockets

    mp_impl->M04_AXI_tlm_aximm_read_socket->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_impl->M04_AXI_tlm_aximm_write_socket->bind(*(mp_M04_AXI_transactor->wr_socket));
  }

  // configure 'M05_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M05_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M05_AXI' transactor parameters
    xsc::common_cpp::properties M05_AXI_transactor_param_props;
    M05_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M05_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M05_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M05_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M05_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M05_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M05_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M05_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M05_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M05_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M05_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M05_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M05_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M05_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M05_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M05_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M05_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M05_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M05_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M05_AXI_transactor", M05_AXI_transactor_param_props);

    // M05_AXI' transactor ports

    mp_M05_AXI_transactor->AWADDR(M05_AXI_awaddr);
    mp_M05_AXI_transactor->AWPROT(M05_AXI_awprot);
    mp_M05_AXI_transactor->AWVALID(M05_AXI_awvalid);
    mp_M05_AXI_transactor->AWREADY(M05_AXI_awready);
    mp_M05_AXI_transactor->WDATA(M05_AXI_wdata);
    mp_M05_AXI_transactor->WSTRB(M05_AXI_wstrb);
    mp_M05_AXI_transactor->WVALID(M05_AXI_wvalid);
    mp_M05_AXI_transactor->WREADY(M05_AXI_wready);
    mp_M05_AXI_transactor->BRESP(M05_AXI_bresp);
    mp_M05_AXI_transactor->BVALID(M05_AXI_bvalid);
    mp_M05_AXI_transactor->BREADY(M05_AXI_bready);
    mp_M05_AXI_transactor->ARADDR(M05_AXI_araddr);
    mp_M05_AXI_transactor->ARPROT(M05_AXI_arprot);
    mp_M05_AXI_transactor->ARVALID(M05_AXI_arvalid);
    mp_M05_AXI_transactor->ARREADY(M05_AXI_arready);
    mp_M05_AXI_transactor->RDATA(M05_AXI_rdata);
    mp_M05_AXI_transactor->RRESP(M05_AXI_rresp);
    mp_M05_AXI_transactor->RVALID(M05_AXI_rvalid);
    mp_M05_AXI_transactor->RREADY(M05_AXI_rready);
    mp_M05_AXI_transactor->CLK(aclk);
    mp_M05_AXI_transactor->RST(aresetn);

    // M05_AXI' transactor sockets

    mp_impl->M05_AXI_tlm_aximm_read_socket->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_impl->M05_AXI_tlm_aximm_write_socket->bind(*(mp_M05_AXI_transactor->wr_socket));
  }

  // configure 'M06_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M06_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M06_AXI' transactor parameters
    xsc::common_cpp::properties M06_AXI_transactor_param_props;
    M06_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M06_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M06_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ADDR_WIDTH", "9");
    M06_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M06_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M06_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M06_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M06_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M06_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M06_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M06_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M06_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M06_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M06_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M06_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M06_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M06_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M06_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M06_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,9,1,1,1,1,1,1>("M06_AXI_transactor", M06_AXI_transactor_param_props);

    // M06_AXI' transactor ports

    mp_M06_AXI_transactor->AWADDR(M06_AXI_awaddr);
    mp_M06_AXI_transactor->AWPROT(M06_AXI_awprot);
    mp_M06_AXI_transactor->AWVALID(M06_AXI_awvalid);
    mp_M06_AXI_transactor->AWREADY(M06_AXI_awready);
    mp_M06_AXI_transactor->WDATA(M06_AXI_wdata);
    mp_M06_AXI_transactor->WSTRB(M06_AXI_wstrb);
    mp_M06_AXI_transactor->WVALID(M06_AXI_wvalid);
    mp_M06_AXI_transactor->WREADY(M06_AXI_wready);
    mp_M06_AXI_transactor->BRESP(M06_AXI_bresp);
    mp_M06_AXI_transactor->BVALID(M06_AXI_bvalid);
    mp_M06_AXI_transactor->BREADY(M06_AXI_bready);
    mp_M06_AXI_transactor->ARADDR(M06_AXI_araddr);
    mp_M06_AXI_transactor->ARPROT(M06_AXI_arprot);
    mp_M06_AXI_transactor->ARVALID(M06_AXI_arvalid);
    mp_M06_AXI_transactor->ARREADY(M06_AXI_arready);
    mp_M06_AXI_transactor->RDATA(M06_AXI_rdata);
    mp_M06_AXI_transactor->RRESP(M06_AXI_rresp);
    mp_M06_AXI_transactor->RVALID(M06_AXI_rvalid);
    mp_M06_AXI_transactor->RREADY(M06_AXI_rready);
    mp_M06_AXI_transactor->CLK(aclk);
    mp_M06_AXI_transactor->RST(aresetn);

    // M06_AXI' transactor sockets

    mp_impl->M06_AXI_tlm_aximm_read_socket->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_impl->M06_AXI_tlm_aximm_write_socket->bind(*(mp_M06_AXI_transactor->wr_socket));
  }

  // configure 'M07_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M07_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M07_AXI' transactor parameters
    xsc::common_cpp::properties M07_AXI_transactor_param_props;
    M07_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M07_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M07_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M07_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M07_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M07_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M07_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M07_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M07_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M07_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M07_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M07_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M07_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M07_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M07_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M07_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M07_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,16,1,1,16,1>("M07_AXI_transactor", M07_AXI_transactor_param_props);

    // M07_AXI' transactor ports

    mp_M07_AXI_transactor->AWADDR(M07_AXI_awaddr);
    mp_M07_AXI_transactor->AWLEN(M07_AXI_awlen);
    mp_M07_AXI_transactor->AWSIZE(M07_AXI_awsize);
    mp_M07_AXI_transactor->AWBURST(M07_AXI_awburst);
    mp_M07_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_awlock_converter");
    mp_M07_AXI_awlock_converter->scalar_in(m_M07_AXI_awlock_converter_signal);
    mp_M07_AXI_awlock_converter->vector_out(M07_AXI_awlock);
    mp_M07_AXI_transactor->AWLOCK(m_M07_AXI_awlock_converter_signal);
    mp_M07_AXI_transactor->AWCACHE(M07_AXI_awcache);
    mp_M07_AXI_transactor->AWPROT(M07_AXI_awprot);
    mp_M07_AXI_transactor->AWQOS(M07_AXI_awqos);
    mp_M07_AXI_transactor->AWUSER(M07_AXI_awuser);
    mp_M07_AXI_transactor->AWVALID(M07_AXI_awvalid);
    mp_M07_AXI_transactor->AWREADY(M07_AXI_awready);
    mp_M07_AXI_transactor->WDATA(M07_AXI_wdata);
    mp_M07_AXI_transactor->WSTRB(M07_AXI_wstrb);
    mp_M07_AXI_transactor->WLAST(M07_AXI_wlast);
    mp_M07_AXI_transactor->WVALID(M07_AXI_wvalid);
    mp_M07_AXI_transactor->WREADY(M07_AXI_wready);
    mp_M07_AXI_transactor->BRESP(M07_AXI_bresp);
    mp_M07_AXI_transactor->BVALID(M07_AXI_bvalid);
    mp_M07_AXI_transactor->BREADY(M07_AXI_bready);
    mp_M07_AXI_transactor->ARADDR(M07_AXI_araddr);
    mp_M07_AXI_transactor->ARLEN(M07_AXI_arlen);
    mp_M07_AXI_transactor->ARSIZE(M07_AXI_arsize);
    mp_M07_AXI_transactor->ARBURST(M07_AXI_arburst);
    mp_M07_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_arlock_converter");
    mp_M07_AXI_arlock_converter->scalar_in(m_M07_AXI_arlock_converter_signal);
    mp_M07_AXI_arlock_converter->vector_out(M07_AXI_arlock);
    mp_M07_AXI_transactor->ARLOCK(m_M07_AXI_arlock_converter_signal);
    mp_M07_AXI_transactor->ARCACHE(M07_AXI_arcache);
    mp_M07_AXI_transactor->ARPROT(M07_AXI_arprot);
    mp_M07_AXI_transactor->ARQOS(M07_AXI_arqos);
    mp_M07_AXI_transactor->ARUSER(M07_AXI_aruser);
    mp_M07_AXI_transactor->ARVALID(M07_AXI_arvalid);
    mp_M07_AXI_transactor->ARREADY(M07_AXI_arready);
    mp_M07_AXI_transactor->RDATA(M07_AXI_rdata);
    mp_M07_AXI_transactor->RRESP(M07_AXI_rresp);
    mp_M07_AXI_transactor->RLAST(M07_AXI_rlast);
    mp_M07_AXI_transactor->RVALID(M07_AXI_rvalid);
    mp_M07_AXI_transactor->RREADY(M07_AXI_rready);
    mp_M07_AXI_transactor->CLK(aclk);
    mp_M07_AXI_transactor->RST(aresetn);

    // M07_AXI' transactor sockets

    mp_impl->M07_AXI_tlm_aximm_read_socket->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_impl->M07_AXI_tlm_aximm_write_socket->bind(*(mp_M07_AXI_transactor->wr_socket));
  }

  // configure 'M08_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M08_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M08_AXI' transactor parameters
    xsc::common_cpp::properties M08_AXI_transactor_param_props;
    M08_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M08_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M08_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M08_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M08_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M08_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M08_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M08_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M08_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M08_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M08_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M08_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M08_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M08_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M08_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M08_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M08_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M08_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M08_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M08_AXI_transactor", M08_AXI_transactor_param_props);

    // M08_AXI' transactor ports

    mp_M08_AXI_transactor->AWADDR(M08_AXI_awaddr);
    mp_M08_AXI_transactor->AWPROT(M08_AXI_awprot);
    mp_M08_AXI_transactor->AWVALID(M08_AXI_awvalid);
    mp_M08_AXI_transactor->AWREADY(M08_AXI_awready);
    mp_M08_AXI_transactor->WDATA(M08_AXI_wdata);
    mp_M08_AXI_transactor->WSTRB(M08_AXI_wstrb);
    mp_M08_AXI_transactor->WVALID(M08_AXI_wvalid);
    mp_M08_AXI_transactor->WREADY(M08_AXI_wready);
    mp_M08_AXI_transactor->BRESP(M08_AXI_bresp);
    mp_M08_AXI_transactor->BVALID(M08_AXI_bvalid);
    mp_M08_AXI_transactor->BREADY(M08_AXI_bready);
    mp_M08_AXI_transactor->ARADDR(M08_AXI_araddr);
    mp_M08_AXI_transactor->ARPROT(M08_AXI_arprot);
    mp_M08_AXI_transactor->ARVALID(M08_AXI_arvalid);
    mp_M08_AXI_transactor->ARREADY(M08_AXI_arready);
    mp_M08_AXI_transactor->RDATA(M08_AXI_rdata);
    mp_M08_AXI_transactor->RRESP(M08_AXI_rresp);
    mp_M08_AXI_transactor->RVALID(M08_AXI_rvalid);
    mp_M08_AXI_transactor->RREADY(M08_AXI_rready);
    mp_M08_AXI_transactor->CLK(aclk);
    mp_M08_AXI_transactor->RST(aresetn);

    // M08_AXI' transactor sockets

    mp_impl->M08_AXI_tlm_aximm_read_socket->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_impl->M08_AXI_tlm_aximm_write_socket->bind(*(mp_M08_AXI_transactor->wr_socket));
  }

  // configure 'M09_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M09_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M09_AXI' transactor parameters
    xsc::common_cpp::properties M09_AXI_transactor_param_props;
    M09_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M09_AXI_transactor_param_props.addLong("FREQ_HZ", "50000000");
    M09_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M09_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M09_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M09_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M09_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M09_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M09_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M09_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M09_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M09_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M09_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M09_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M09_AXI_transactor_param_props.addFloat("PHASE", "0.0");
    M09_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M09_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M09_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_clk_wiz_0_0_clk_50MHz");

    mp_M09_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M09_AXI_transactor", M09_AXI_transactor_param_props);

    // M09_AXI' transactor ports

    mp_M09_AXI_transactor->AWADDR(M09_AXI_awaddr);
    mp_M09_AXI_transactor->AWPROT(M09_AXI_awprot);
    mp_M09_AXI_transactor->AWVALID(M09_AXI_awvalid);
    mp_M09_AXI_transactor->AWREADY(M09_AXI_awready);
    mp_M09_AXI_transactor->WDATA(M09_AXI_wdata);
    mp_M09_AXI_transactor->WSTRB(M09_AXI_wstrb);
    mp_M09_AXI_transactor->WVALID(M09_AXI_wvalid);
    mp_M09_AXI_transactor->WREADY(M09_AXI_wready);
    mp_M09_AXI_transactor->BRESP(M09_AXI_bresp);
    mp_M09_AXI_transactor->BVALID(M09_AXI_bvalid);
    mp_M09_AXI_transactor->BREADY(M09_AXI_bready);
    mp_M09_AXI_transactor->ARADDR(M09_AXI_araddr);
    mp_M09_AXI_transactor->ARPROT(M09_AXI_arprot);
    mp_M09_AXI_transactor->ARVALID(M09_AXI_arvalid);
    mp_M09_AXI_transactor->ARREADY(M09_AXI_arready);
    mp_M09_AXI_transactor->RDATA(M09_AXI_rdata);
    mp_M09_AXI_transactor->RRESP(M09_AXI_rresp);
    mp_M09_AXI_transactor->RVALID(M09_AXI_rvalid);
    mp_M09_AXI_transactor->RREADY(M09_AXI_rready);
    mp_M09_AXI_transactor->CLK(aclk2);
    mp_M09_AXI_transactor->RST(aresetn);

    // M09_AXI' transactor sockets

    mp_impl->M09_AXI_tlm_aximm_read_socket->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_impl->M09_AXI_tlm_aximm_write_socket->bind(*(mp_M09_AXI_transactor->wr_socket));
  }

  // configure 'M10_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M10_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M10_AXI' transactor parameters
    xsc::common_cpp::properties M10_AXI_transactor_param_props;
    M10_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    M10_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M10_AXI_transactor_param_props.addLong("ID_WIDTH", "3");
    M10_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M10_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("WUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("RUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("BUSER_WIDTH", "114");
    M10_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M10_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M10_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M10_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M10_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M10_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M10_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M10_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M10_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M10_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M10_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M10_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M10_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M10_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M10_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,3,130,14,114,130,14>("M10_AXI_transactor", M10_AXI_transactor_param_props);

    // M10_AXI' transactor ports

    mp_M10_AXI_transactor->AWID(M10_AXI_awid);
    mp_M10_AXI_transactor->AWADDR(M10_AXI_awaddr);
    mp_M10_AXI_transactor->AWLEN(M10_AXI_awlen);
    mp_M10_AXI_transactor->AWSIZE(M10_AXI_awsize);
    mp_M10_AXI_transactor->AWBURST(M10_AXI_awburst);
    mp_M10_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_awlock_converter");
    mp_M10_AXI_awlock_converter->scalar_in(m_M10_AXI_awlock_converter_signal);
    mp_M10_AXI_awlock_converter->vector_out(M10_AXI_awlock);
    mp_M10_AXI_transactor->AWLOCK(m_M10_AXI_awlock_converter_signal);
    mp_M10_AXI_transactor->AWCACHE(M10_AXI_awcache);
    mp_M10_AXI_transactor->AWPROT(M10_AXI_awprot);
    mp_M10_AXI_transactor->AWQOS(M10_AXI_awqos);
    mp_M10_AXI_transactor->AWUSER(M10_AXI_awuser);
    mp_M10_AXI_transactor->AWVALID(M10_AXI_awvalid);
    mp_M10_AXI_transactor->AWREADY(M10_AXI_awready);
    mp_M10_AXI_transactor->WDATA(M10_AXI_wdata);
    mp_M10_AXI_transactor->WSTRB(M10_AXI_wstrb);
    mp_M10_AXI_transactor->WLAST(M10_AXI_wlast);
    mp_M10_AXI_transactor->WUSER(M10_AXI_wuser);
    mp_M10_AXI_transactor->WVALID(M10_AXI_wvalid);
    mp_M10_AXI_transactor->WREADY(M10_AXI_wready);
    mp_M10_AXI_transactor->BID(M10_AXI_bid);
    mp_M10_AXI_transactor->BRESP(M10_AXI_bresp);
    mp_M10_AXI_transactor->BUSER(M10_AXI_buser);
    mp_M10_AXI_transactor->BVALID(M10_AXI_bvalid);
    mp_M10_AXI_transactor->BREADY(M10_AXI_bready);
    mp_M10_AXI_transactor->ARID(M10_AXI_arid);
    mp_M10_AXI_transactor->ARADDR(M10_AXI_araddr);
    mp_M10_AXI_transactor->ARLEN(M10_AXI_arlen);
    mp_M10_AXI_transactor->ARSIZE(M10_AXI_arsize);
    mp_M10_AXI_transactor->ARBURST(M10_AXI_arburst);
    mp_M10_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_arlock_converter");
    mp_M10_AXI_arlock_converter->scalar_in(m_M10_AXI_arlock_converter_signal);
    mp_M10_AXI_arlock_converter->vector_out(M10_AXI_arlock);
    mp_M10_AXI_transactor->ARLOCK(m_M10_AXI_arlock_converter_signal);
    mp_M10_AXI_transactor->ARCACHE(M10_AXI_arcache);
    mp_M10_AXI_transactor->ARPROT(M10_AXI_arprot);
    mp_M10_AXI_transactor->ARQOS(M10_AXI_arqos);
    mp_M10_AXI_transactor->ARUSER(M10_AXI_aruser);
    mp_M10_AXI_transactor->ARVALID(M10_AXI_arvalid);
    mp_M10_AXI_transactor->ARREADY(M10_AXI_arready);
    mp_M10_AXI_transactor->RID(M10_AXI_rid);
    mp_M10_AXI_transactor->RDATA(M10_AXI_rdata);
    mp_M10_AXI_transactor->RRESP(M10_AXI_rresp);
    mp_M10_AXI_transactor->RLAST(M10_AXI_rlast);
    mp_M10_AXI_transactor->RUSER(M10_AXI_ruser);
    mp_M10_AXI_transactor->RVALID(M10_AXI_rvalid);
    mp_M10_AXI_transactor->RREADY(M10_AXI_rready);
    mp_M10_AXI_transactor->CLK(aclk);
    mp_M10_AXI_transactor->RST(aresetn);

    // M10_AXI' transactor sockets

    mp_impl->M10_AXI_tlm_aximm_read_socket->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_impl->M10_AXI_tlm_aximm_write_socket->bind(*(mp_M10_AXI_transactor->wr_socket));
  }

  // configure 'M11_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M11_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M11_AXI' transactor parameters
    xsc::common_cpp::properties M11_AXI_transactor_param_props;
    M11_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M11_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M11_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M11_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M11_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M11_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M11_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M11_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M11_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M11_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M11_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M11_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M11_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M11_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M11_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M11_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M11_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M11_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M11_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M11_AXI_transactor", M11_AXI_transactor_param_props);

    // M11_AXI' transactor ports

    mp_M11_AXI_transactor->AWADDR(M11_AXI_awaddr);
    mp_M11_AXI_transactor->AWPROT(M11_AXI_awprot);
    mp_M11_AXI_transactor->AWVALID(M11_AXI_awvalid);
    mp_M11_AXI_transactor->AWREADY(M11_AXI_awready);
    mp_M11_AXI_transactor->WDATA(M11_AXI_wdata);
    mp_M11_AXI_transactor->WSTRB(M11_AXI_wstrb);
    mp_M11_AXI_transactor->WVALID(M11_AXI_wvalid);
    mp_M11_AXI_transactor->WREADY(M11_AXI_wready);
    mp_M11_AXI_transactor->BRESP(M11_AXI_bresp);
    mp_M11_AXI_transactor->BVALID(M11_AXI_bvalid);
    mp_M11_AXI_transactor->BREADY(M11_AXI_bready);
    mp_M11_AXI_transactor->ARADDR(M11_AXI_araddr);
    mp_M11_AXI_transactor->ARPROT(M11_AXI_arprot);
    mp_M11_AXI_transactor->ARVALID(M11_AXI_arvalid);
    mp_M11_AXI_transactor->ARREADY(M11_AXI_arready);
    mp_M11_AXI_transactor->RDATA(M11_AXI_rdata);
    mp_M11_AXI_transactor->RRESP(M11_AXI_rresp);
    mp_M11_AXI_transactor->RVALID(M11_AXI_rvalid);
    mp_M11_AXI_transactor->RREADY(M11_AXI_rready);
    mp_M11_AXI_transactor->CLK(aclk);
    mp_M11_AXI_transactor->RST(aresetn);

    // M11_AXI' transactor sockets

    mp_impl->M11_AXI_tlm_aximm_read_socket->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_impl->M11_AXI_tlm_aximm_write_socket->bind(*(mp_M11_AXI_transactor->wr_socket));
  }

  // configure 'M12_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M12_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M12_AXI' transactor parameters
    xsc::common_cpp::properties M12_AXI_transactor_param_props;
    M12_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M12_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M12_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M12_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M12_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M12_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M12_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M12_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M12_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M12_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M12_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M12_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M12_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M12_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M12_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M12_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M12_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M12_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M12_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M12_AXI_transactor", M12_AXI_transactor_param_props);

    // M12_AXI' transactor ports

    mp_M12_AXI_transactor->AWADDR(M12_AXI_awaddr);
    mp_M12_AXI_transactor->AWPROT(M12_AXI_awprot);
    mp_M12_AXI_transactor->AWVALID(M12_AXI_awvalid);
    mp_M12_AXI_transactor->AWREADY(M12_AXI_awready);
    mp_M12_AXI_transactor->WDATA(M12_AXI_wdata);
    mp_M12_AXI_transactor->WSTRB(M12_AXI_wstrb);
    mp_M12_AXI_transactor->WVALID(M12_AXI_wvalid);
    mp_M12_AXI_transactor->WREADY(M12_AXI_wready);
    mp_M12_AXI_transactor->BRESP(M12_AXI_bresp);
    mp_M12_AXI_transactor->BVALID(M12_AXI_bvalid);
    mp_M12_AXI_transactor->BREADY(M12_AXI_bready);
    mp_M12_AXI_transactor->ARADDR(M12_AXI_araddr);
    mp_M12_AXI_transactor->ARPROT(M12_AXI_arprot);
    mp_M12_AXI_transactor->ARVALID(M12_AXI_arvalid);
    mp_M12_AXI_transactor->ARREADY(M12_AXI_arready);
    mp_M12_AXI_transactor->RDATA(M12_AXI_rdata);
    mp_M12_AXI_transactor->RRESP(M12_AXI_rresp);
    mp_M12_AXI_transactor->RVALID(M12_AXI_rvalid);
    mp_M12_AXI_transactor->RREADY(M12_AXI_rready);
    mp_M12_AXI_transactor->CLK(aclk);
    mp_M12_AXI_transactor->RST(aresetn);

    // M12_AXI' transactor sockets

    mp_impl->M12_AXI_tlm_aximm_read_socket->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_impl->M12_AXI_tlm_aximm_write_socket->bind(*(mp_M12_AXI_transactor->wr_socket));
  }

  // configure 'M13_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M13_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M13_AXI' transactor parameters
    xsc::common_cpp::properties M13_AXI_transactor_param_props;
    M13_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M13_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M13_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M13_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M13_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M13_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M13_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M13_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M13_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M13_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M13_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M13_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M13_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M13_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M13_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M13_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M13_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M13_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M13_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M13_AXI_transactor", M13_AXI_transactor_param_props);

    // M13_AXI' transactor ports

    mp_M13_AXI_transactor->AWADDR(M13_AXI_awaddr);
    mp_M13_AXI_transactor->AWPROT(M13_AXI_awprot);
    mp_M13_AXI_transactor->AWVALID(M13_AXI_awvalid);
    mp_M13_AXI_transactor->AWREADY(M13_AXI_awready);
    mp_M13_AXI_transactor->WDATA(M13_AXI_wdata);
    mp_M13_AXI_transactor->WSTRB(M13_AXI_wstrb);
    mp_M13_AXI_transactor->WVALID(M13_AXI_wvalid);
    mp_M13_AXI_transactor->WREADY(M13_AXI_wready);
    mp_M13_AXI_transactor->BRESP(M13_AXI_bresp);
    mp_M13_AXI_transactor->BVALID(M13_AXI_bvalid);
    mp_M13_AXI_transactor->BREADY(M13_AXI_bready);
    mp_M13_AXI_transactor->ARADDR(M13_AXI_araddr);
    mp_M13_AXI_transactor->ARPROT(M13_AXI_arprot);
    mp_M13_AXI_transactor->ARVALID(M13_AXI_arvalid);
    mp_M13_AXI_transactor->ARREADY(M13_AXI_arready);
    mp_M13_AXI_transactor->RDATA(M13_AXI_rdata);
    mp_M13_AXI_transactor->RRESP(M13_AXI_rresp);
    mp_M13_AXI_transactor->RVALID(M13_AXI_rvalid);
    mp_M13_AXI_transactor->RREADY(M13_AXI_rready);
    mp_M13_AXI_transactor->CLK(aclk);
    mp_M13_AXI_transactor->RST(aresetn);

    // M13_AXI' transactor sockets

    mp_impl->M13_AXI_tlm_aximm_read_socket->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_impl->M13_AXI_tlm_aximm_write_socket->bind(*(mp_M13_AXI_transactor->wr_socket));
  }

  // configure 'M14_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M14_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M14_AXI' transactor parameters
    xsc::common_cpp::properties M14_AXI_transactor_param_props;
    M14_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M14_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M14_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M14_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M14_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M14_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M14_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M14_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M14_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M14_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M14_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M14_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M14_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M14_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M14_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M14_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M14_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M14_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M14_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M14_AXI_transactor", M14_AXI_transactor_param_props);

    // M14_AXI' transactor ports

    mp_M14_AXI_transactor->AWADDR(M14_AXI_awaddr);
    mp_M14_AXI_transactor->AWPROT(M14_AXI_awprot);
    mp_M14_AXI_transactor->AWVALID(M14_AXI_awvalid);
    mp_M14_AXI_transactor->AWREADY(M14_AXI_awready);
    mp_M14_AXI_transactor->WDATA(M14_AXI_wdata);
    mp_M14_AXI_transactor->WSTRB(M14_AXI_wstrb);
    mp_M14_AXI_transactor->WVALID(M14_AXI_wvalid);
    mp_M14_AXI_transactor->WREADY(M14_AXI_wready);
    mp_M14_AXI_transactor->BRESP(M14_AXI_bresp);
    mp_M14_AXI_transactor->BVALID(M14_AXI_bvalid);
    mp_M14_AXI_transactor->BREADY(M14_AXI_bready);
    mp_M14_AXI_transactor->ARADDR(M14_AXI_araddr);
    mp_M14_AXI_transactor->ARPROT(M14_AXI_arprot);
    mp_M14_AXI_transactor->ARVALID(M14_AXI_arvalid);
    mp_M14_AXI_transactor->ARREADY(M14_AXI_arready);
    mp_M14_AXI_transactor->RDATA(M14_AXI_rdata);
    mp_M14_AXI_transactor->RRESP(M14_AXI_rresp);
    mp_M14_AXI_transactor->RVALID(M14_AXI_rvalid);
    mp_M14_AXI_transactor->RREADY(M14_AXI_rready);
    mp_M14_AXI_transactor->CLK(aclk);
    mp_M14_AXI_transactor->RST(aresetn);

    // M14_AXI' transactor sockets

    mp_impl->M14_AXI_tlm_aximm_read_socket->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_impl->M14_AXI_tlm_aximm_write_socket->bind(*(mp_M14_AXI_transactor->wr_socket));
  }

}

#endif // XM_SYSTEMC




#ifdef RIVIERA
zusys_smartconnect_0_0::zusys_smartconnect_0_0(const sc_core::sc_module_name& nm) : zusys_smartconnect_0_0_sc(nm), aclk("aclk"), aclk1("aclk1"), aclk2("aclk2"), aresetn("aresetn"), S00_AXI_awid("S00_AXI_awid"), S00_AXI_awaddr("S00_AXI_awaddr"), S00_AXI_awlen("S00_AXI_awlen"), S00_AXI_awsize("S00_AXI_awsize"), S00_AXI_awburst("S00_AXI_awburst"), S00_AXI_awlock("S00_AXI_awlock"), S00_AXI_awcache("S00_AXI_awcache"), S00_AXI_awprot("S00_AXI_awprot"), S00_AXI_awqos("S00_AXI_awqos"), S00_AXI_awuser("S00_AXI_awuser"), S00_AXI_awvalid("S00_AXI_awvalid"), S00_AXI_awready("S00_AXI_awready"), S00_AXI_wdata("S00_AXI_wdata"), S00_AXI_wstrb("S00_AXI_wstrb"), S00_AXI_wlast("S00_AXI_wlast"), S00_AXI_wvalid("S00_AXI_wvalid"), S00_AXI_wready("S00_AXI_wready"), S00_AXI_bid("S00_AXI_bid"), S00_AXI_bresp("S00_AXI_bresp"), S00_AXI_bvalid("S00_AXI_bvalid"), S00_AXI_bready("S00_AXI_bready"), S00_AXI_arid("S00_AXI_arid"), S00_AXI_araddr("S00_AXI_araddr"), S00_AXI_arlen("S00_AXI_arlen"), S00_AXI_arsize("S00_AXI_arsize"), S00_AXI_arburst("S00_AXI_arburst"), S00_AXI_arlock("S00_AXI_arlock"), S00_AXI_arcache("S00_AXI_arcache"), S00_AXI_arprot("S00_AXI_arprot"), S00_AXI_arqos("S00_AXI_arqos"), S00_AXI_aruser("S00_AXI_aruser"), S00_AXI_arvalid("S00_AXI_arvalid"), S00_AXI_arready("S00_AXI_arready"), S00_AXI_rid("S00_AXI_rid"), S00_AXI_rdata("S00_AXI_rdata"), S00_AXI_rresp("S00_AXI_rresp"), S00_AXI_rlast("S00_AXI_rlast"), S00_AXI_rvalid("S00_AXI_rvalid"), S00_AXI_rready("S00_AXI_rready"), M00_AXI_awaddr("M00_AXI_awaddr"), M00_AXI_awprot("M00_AXI_awprot"), M00_AXI_awvalid("M00_AXI_awvalid"), M00_AXI_awready("M00_AXI_awready"), M00_AXI_wdata("M00_AXI_wdata"), M00_AXI_wstrb("M00_AXI_wstrb"), M00_AXI_wvalid("M00_AXI_wvalid"), M00_AXI_wready("M00_AXI_wready"), M00_AXI_bresp("M00_AXI_bresp"), M00_AXI_bvalid("M00_AXI_bvalid"), M00_AXI_bready("M00_AXI_bready"), M00_AXI_araddr("M00_AXI_araddr"), M00_AXI_arprot("M00_AXI_arprot"), M00_AXI_arvalid("M00_AXI_arvalid"), M00_AXI_arready("M00_AXI_arready"), M00_AXI_rdata("M00_AXI_rdata"), M00_AXI_rresp("M00_AXI_rresp"), M00_AXI_rvalid("M00_AXI_rvalid"), M00_AXI_rready("M00_AXI_rready"), M01_AXI_awaddr("M01_AXI_awaddr"), M01_AXI_awprot("M01_AXI_awprot"), M01_AXI_awvalid("M01_AXI_awvalid"), M01_AXI_awready("M01_AXI_awready"), M01_AXI_wdata("M01_AXI_wdata"), M01_AXI_wstrb("M01_AXI_wstrb"), M01_AXI_wvalid("M01_AXI_wvalid"), M01_AXI_wready("M01_AXI_wready"), M01_AXI_bresp("M01_AXI_bresp"), M01_AXI_bvalid("M01_AXI_bvalid"), M01_AXI_bready("M01_AXI_bready"), M01_AXI_araddr("M01_AXI_araddr"), M01_AXI_arprot("M01_AXI_arprot"), M01_AXI_arvalid("M01_AXI_arvalid"), M01_AXI_arready("M01_AXI_arready"), M01_AXI_rdata("M01_AXI_rdata"), M01_AXI_rresp("M01_AXI_rresp"), M01_AXI_rvalid("M01_AXI_rvalid"), M01_AXI_rready("M01_AXI_rready"), M02_AXI_awaddr("M02_AXI_awaddr"), M02_AXI_awprot("M02_AXI_awprot"), M02_AXI_awvalid("M02_AXI_awvalid"), M02_AXI_awready("M02_AXI_awready"), M02_AXI_wdata("M02_AXI_wdata"), M02_AXI_wstrb("M02_AXI_wstrb"), M02_AXI_wvalid("M02_AXI_wvalid"), M02_AXI_wready("M02_AXI_wready"), M02_AXI_bresp("M02_AXI_bresp"), M02_AXI_bvalid("M02_AXI_bvalid"), M02_AXI_bready("M02_AXI_bready"), M02_AXI_araddr("M02_AXI_araddr"), M02_AXI_arprot("M02_AXI_arprot"), M02_AXI_arvalid("M02_AXI_arvalid"), M02_AXI_arready("M02_AXI_arready"), M02_AXI_rdata("M02_AXI_rdata"), M02_AXI_rresp("M02_AXI_rresp"), M02_AXI_rvalid("M02_AXI_rvalid"), M02_AXI_rready("M02_AXI_rready"), M03_AXI_awaddr("M03_AXI_awaddr"), M03_AXI_awprot("M03_AXI_awprot"), M03_AXI_awvalid("M03_AXI_awvalid"), M03_AXI_awready("M03_AXI_awready"), M03_AXI_wdata("M03_AXI_wdata"), M03_AXI_wstrb("M03_AXI_wstrb"), M03_AXI_wvalid("M03_AXI_wvalid"), M03_AXI_wready("M03_AXI_wready"), M03_AXI_bresp("M03_AXI_bresp"), M03_AXI_bvalid("M03_AXI_bvalid"), M03_AXI_bready("M03_AXI_bready"), M03_AXI_araddr("M03_AXI_araddr"), M03_AXI_arprot("M03_AXI_arprot"), M03_AXI_arvalid("M03_AXI_arvalid"), M03_AXI_arready("M03_AXI_arready"), M03_AXI_rdata("M03_AXI_rdata"), M03_AXI_rresp("M03_AXI_rresp"), M03_AXI_rvalid("M03_AXI_rvalid"), M03_AXI_rready("M03_AXI_rready"), M04_AXI_awaddr("M04_AXI_awaddr"), M04_AXI_awprot("M04_AXI_awprot"), M04_AXI_awvalid("M04_AXI_awvalid"), M04_AXI_awready("M04_AXI_awready"), M04_AXI_wdata("M04_AXI_wdata"), M04_AXI_wstrb("M04_AXI_wstrb"), M04_AXI_wvalid("M04_AXI_wvalid"), M04_AXI_wready("M04_AXI_wready"), M04_AXI_bresp("M04_AXI_bresp"), M04_AXI_bvalid("M04_AXI_bvalid"), M04_AXI_bready("M04_AXI_bready"), M04_AXI_araddr("M04_AXI_araddr"), M04_AXI_arprot("M04_AXI_arprot"), M04_AXI_arvalid("M04_AXI_arvalid"), M04_AXI_arready("M04_AXI_arready"), M04_AXI_rdata("M04_AXI_rdata"), M04_AXI_rresp("M04_AXI_rresp"), M04_AXI_rvalid("M04_AXI_rvalid"), M04_AXI_rready("M04_AXI_rready"), M05_AXI_awaddr("M05_AXI_awaddr"), M05_AXI_awprot("M05_AXI_awprot"), M05_AXI_awvalid("M05_AXI_awvalid"), M05_AXI_awready("M05_AXI_awready"), M05_AXI_wdata("M05_AXI_wdata"), M05_AXI_wstrb("M05_AXI_wstrb"), M05_AXI_wvalid("M05_AXI_wvalid"), M05_AXI_wready("M05_AXI_wready"), M05_AXI_bresp("M05_AXI_bresp"), M05_AXI_bvalid("M05_AXI_bvalid"), M05_AXI_bready("M05_AXI_bready"), M05_AXI_araddr("M05_AXI_araddr"), M05_AXI_arprot("M05_AXI_arprot"), M05_AXI_arvalid("M05_AXI_arvalid"), M05_AXI_arready("M05_AXI_arready"), M05_AXI_rdata("M05_AXI_rdata"), M05_AXI_rresp("M05_AXI_rresp"), M05_AXI_rvalid("M05_AXI_rvalid"), M05_AXI_rready("M05_AXI_rready"), M06_AXI_awaddr("M06_AXI_awaddr"), M06_AXI_awprot("M06_AXI_awprot"), M06_AXI_awvalid("M06_AXI_awvalid"), M06_AXI_awready("M06_AXI_awready"), M06_AXI_wdata("M06_AXI_wdata"), M06_AXI_wstrb("M06_AXI_wstrb"), M06_AXI_wvalid("M06_AXI_wvalid"), M06_AXI_wready("M06_AXI_wready"), M06_AXI_bresp("M06_AXI_bresp"), M06_AXI_bvalid("M06_AXI_bvalid"), M06_AXI_bready("M06_AXI_bready"), M06_AXI_araddr("M06_AXI_araddr"), M06_AXI_arprot("M06_AXI_arprot"), M06_AXI_arvalid("M06_AXI_arvalid"), M06_AXI_arready("M06_AXI_arready"), M06_AXI_rdata("M06_AXI_rdata"), M06_AXI_rresp("M06_AXI_rresp"), M06_AXI_rvalid("M06_AXI_rvalid"), M06_AXI_rready("M06_AXI_rready"), M07_AXI_awaddr("M07_AXI_awaddr"), M07_AXI_awlen("M07_AXI_awlen"), M07_AXI_awsize("M07_AXI_awsize"), M07_AXI_awburst("M07_AXI_awburst"), M07_AXI_awlock("M07_AXI_awlock"), M07_AXI_awcache("M07_AXI_awcache"), M07_AXI_awprot("M07_AXI_awprot"), M07_AXI_awqos("M07_AXI_awqos"), M07_AXI_awuser("M07_AXI_awuser"), M07_AXI_awvalid("M07_AXI_awvalid"), M07_AXI_awready("M07_AXI_awready"), M07_AXI_wdata("M07_AXI_wdata"), M07_AXI_wstrb("M07_AXI_wstrb"), M07_AXI_wlast("M07_AXI_wlast"), M07_AXI_wvalid("M07_AXI_wvalid"), M07_AXI_wready("M07_AXI_wready"), M07_AXI_bresp("M07_AXI_bresp"), M07_AXI_bvalid("M07_AXI_bvalid"), M07_AXI_bready("M07_AXI_bready"), M07_AXI_araddr("M07_AXI_araddr"), M07_AXI_arlen("M07_AXI_arlen"), M07_AXI_arsize("M07_AXI_arsize"), M07_AXI_arburst("M07_AXI_arburst"), M07_AXI_arlock("M07_AXI_arlock"), M07_AXI_arcache("M07_AXI_arcache"), M07_AXI_arprot("M07_AXI_arprot"), M07_AXI_arqos("M07_AXI_arqos"), M07_AXI_aruser("M07_AXI_aruser"), M07_AXI_arvalid("M07_AXI_arvalid"), M07_AXI_arready("M07_AXI_arready"), M07_AXI_rdata("M07_AXI_rdata"), M07_AXI_rresp("M07_AXI_rresp"), M07_AXI_rlast("M07_AXI_rlast"), M07_AXI_rvalid("M07_AXI_rvalid"), M07_AXI_rready("M07_AXI_rready"), M08_AXI_awaddr("M08_AXI_awaddr"), M08_AXI_awprot("M08_AXI_awprot"), M08_AXI_awvalid("M08_AXI_awvalid"), M08_AXI_awready("M08_AXI_awready"), M08_AXI_wdata("M08_AXI_wdata"), M08_AXI_wstrb("M08_AXI_wstrb"), M08_AXI_wvalid("M08_AXI_wvalid"), M08_AXI_wready("M08_AXI_wready"), M08_AXI_bresp("M08_AXI_bresp"), M08_AXI_bvalid("M08_AXI_bvalid"), M08_AXI_bready("M08_AXI_bready"), M08_AXI_araddr("M08_AXI_araddr"), M08_AXI_arprot("M08_AXI_arprot"), M08_AXI_arvalid("M08_AXI_arvalid"), M08_AXI_arready("M08_AXI_arready"), M08_AXI_rdata("M08_AXI_rdata"), M08_AXI_rresp("M08_AXI_rresp"), M08_AXI_rvalid("M08_AXI_rvalid"), M08_AXI_rready("M08_AXI_rready"), M09_AXI_awaddr("M09_AXI_awaddr"), M09_AXI_awprot("M09_AXI_awprot"), M09_AXI_awvalid("M09_AXI_awvalid"), M09_AXI_awready("M09_AXI_awready"), M09_AXI_wdata("M09_AXI_wdata"), M09_AXI_wstrb("M09_AXI_wstrb"), M09_AXI_wvalid("M09_AXI_wvalid"), M09_AXI_wready("M09_AXI_wready"), M09_AXI_bresp("M09_AXI_bresp"), M09_AXI_bvalid("M09_AXI_bvalid"), M09_AXI_bready("M09_AXI_bready"), M09_AXI_araddr("M09_AXI_araddr"), M09_AXI_arprot("M09_AXI_arprot"), M09_AXI_arvalid("M09_AXI_arvalid"), M09_AXI_arready("M09_AXI_arready"), M09_AXI_rdata("M09_AXI_rdata"), M09_AXI_rresp("M09_AXI_rresp"), M09_AXI_rvalid("M09_AXI_rvalid"), M09_AXI_rready("M09_AXI_rready"), M10_AXI_awid("M10_AXI_awid"), M10_AXI_awaddr("M10_AXI_awaddr"), M10_AXI_awlen("M10_AXI_awlen"), M10_AXI_awsize("M10_AXI_awsize"), M10_AXI_awburst("M10_AXI_awburst"), M10_AXI_awlock("M10_AXI_awlock"), M10_AXI_awcache("M10_AXI_awcache"), M10_AXI_awprot("M10_AXI_awprot"), M10_AXI_awqos("M10_AXI_awqos"), M10_AXI_awuser("M10_AXI_awuser"), M10_AXI_awvalid("M10_AXI_awvalid"), M10_AXI_awready("M10_AXI_awready"), M10_AXI_wdata("M10_AXI_wdata"), M10_AXI_wstrb("M10_AXI_wstrb"), M10_AXI_wlast("M10_AXI_wlast"), M10_AXI_wuser("M10_AXI_wuser"), M10_AXI_wvalid("M10_AXI_wvalid"), M10_AXI_wready("M10_AXI_wready"), M10_AXI_bid("M10_AXI_bid"), M10_AXI_bresp("M10_AXI_bresp"), M10_AXI_buser("M10_AXI_buser"), M10_AXI_bvalid("M10_AXI_bvalid"), M10_AXI_bready("M10_AXI_bready"), M10_AXI_arid("M10_AXI_arid"), M10_AXI_araddr("M10_AXI_araddr"), M10_AXI_arlen("M10_AXI_arlen"), M10_AXI_arsize("M10_AXI_arsize"), M10_AXI_arburst("M10_AXI_arburst"), M10_AXI_arlock("M10_AXI_arlock"), M10_AXI_arcache("M10_AXI_arcache"), M10_AXI_arprot("M10_AXI_arprot"), M10_AXI_arqos("M10_AXI_arqos"), M10_AXI_aruser("M10_AXI_aruser"), M10_AXI_arvalid("M10_AXI_arvalid"), M10_AXI_arready("M10_AXI_arready"), M10_AXI_rid("M10_AXI_rid"), M10_AXI_rdata("M10_AXI_rdata"), M10_AXI_rresp("M10_AXI_rresp"), M10_AXI_rlast("M10_AXI_rlast"), M10_AXI_ruser("M10_AXI_ruser"), M10_AXI_rvalid("M10_AXI_rvalid"), M10_AXI_rready("M10_AXI_rready"), M11_AXI_awaddr("M11_AXI_awaddr"), M11_AXI_awprot("M11_AXI_awprot"), M11_AXI_awvalid("M11_AXI_awvalid"), M11_AXI_awready("M11_AXI_awready"), M11_AXI_wdata("M11_AXI_wdata"), M11_AXI_wstrb("M11_AXI_wstrb"), M11_AXI_wvalid("M11_AXI_wvalid"), M11_AXI_wready("M11_AXI_wready"), M11_AXI_bresp("M11_AXI_bresp"), M11_AXI_bvalid("M11_AXI_bvalid"), M11_AXI_bready("M11_AXI_bready"), M11_AXI_araddr("M11_AXI_araddr"), M11_AXI_arprot("M11_AXI_arprot"), M11_AXI_arvalid("M11_AXI_arvalid"), M11_AXI_arready("M11_AXI_arready"), M11_AXI_rdata("M11_AXI_rdata"), M11_AXI_rresp("M11_AXI_rresp"), M11_AXI_rvalid("M11_AXI_rvalid"), M11_AXI_rready("M11_AXI_rready"), M12_AXI_awaddr("M12_AXI_awaddr"), M12_AXI_awprot("M12_AXI_awprot"), M12_AXI_awvalid("M12_AXI_awvalid"), M12_AXI_awready("M12_AXI_awready"), M12_AXI_wdata("M12_AXI_wdata"), M12_AXI_wstrb("M12_AXI_wstrb"), M12_AXI_wvalid("M12_AXI_wvalid"), M12_AXI_wready("M12_AXI_wready"), M12_AXI_bresp("M12_AXI_bresp"), M12_AXI_bvalid("M12_AXI_bvalid"), M12_AXI_bready("M12_AXI_bready"), M12_AXI_araddr("M12_AXI_araddr"), M12_AXI_arprot("M12_AXI_arprot"), M12_AXI_arvalid("M12_AXI_arvalid"), M12_AXI_arready("M12_AXI_arready"), M12_AXI_rdata("M12_AXI_rdata"), M12_AXI_rresp("M12_AXI_rresp"), M12_AXI_rvalid("M12_AXI_rvalid"), M12_AXI_rready("M12_AXI_rready"), M13_AXI_awaddr("M13_AXI_awaddr"), M13_AXI_awprot("M13_AXI_awprot"), M13_AXI_awvalid("M13_AXI_awvalid"), M13_AXI_awready("M13_AXI_awready"), M13_AXI_wdata("M13_AXI_wdata"), M13_AXI_wstrb("M13_AXI_wstrb"), M13_AXI_wvalid("M13_AXI_wvalid"), M13_AXI_wready("M13_AXI_wready"), M13_AXI_bresp("M13_AXI_bresp"), M13_AXI_bvalid("M13_AXI_bvalid"), M13_AXI_bready("M13_AXI_bready"), M13_AXI_araddr("M13_AXI_araddr"), M13_AXI_arprot("M13_AXI_arprot"), M13_AXI_arvalid("M13_AXI_arvalid"), M13_AXI_arready("M13_AXI_arready"), M13_AXI_rdata("M13_AXI_rdata"), M13_AXI_rresp("M13_AXI_rresp"), M13_AXI_rvalid("M13_AXI_rvalid"), M13_AXI_rready("M13_AXI_rready"), M14_AXI_awaddr("M14_AXI_awaddr"), M14_AXI_awprot("M14_AXI_awprot"), M14_AXI_awvalid("M14_AXI_awvalid"), M14_AXI_awready("M14_AXI_awready"), M14_AXI_wdata("M14_AXI_wdata"), M14_AXI_wstrb("M14_AXI_wstrb"), M14_AXI_wvalid("M14_AXI_wvalid"), M14_AXI_wready("M14_AXI_wready"), M14_AXI_bresp("M14_AXI_bresp"), M14_AXI_bvalid("M14_AXI_bvalid"), M14_AXI_bready("M14_AXI_bready"), M14_AXI_araddr("M14_AXI_araddr"), M14_AXI_arprot("M14_AXI_arprot"), M14_AXI_arvalid("M14_AXI_arvalid"), M14_AXI_arready("M14_AXI_arready"), M14_AXI_rdata("M14_AXI_rdata"), M14_AXI_rresp("M14_AXI_rresp"), M14_AXI_rvalid("M14_AXI_rvalid"), M14_AXI_rready("M14_AXI_rready")
{

  // initialize pins
  mp_impl->aclk(aclk);
  mp_impl->aclk1(aclk1);
  mp_impl->aclk2(aclk2);
  mp_impl->aresetn(aresetn);

  // initialize transactors
  mp_S00_AXI_transactor = NULL;
  mp_S00_AXI_awlock_converter = NULL;
  mp_S00_AXI_arlock_converter = NULL;
  mp_M00_AXI_transactor = NULL;
  mp_M01_AXI_transactor = NULL;
  mp_M02_AXI_transactor = NULL;
  mp_M03_AXI_transactor = NULL;
  mp_M04_AXI_transactor = NULL;
  mp_M05_AXI_transactor = NULL;
  mp_M06_AXI_transactor = NULL;
  mp_M07_AXI_transactor = NULL;
  mp_M07_AXI_awlock_converter = NULL;
  mp_M07_AXI_arlock_converter = NULL;
  mp_M08_AXI_transactor = NULL;
  mp_M09_AXI_transactor = NULL;
  mp_M10_AXI_transactor = NULL;
  mp_M10_AXI_awlock_converter = NULL;
  mp_M10_AXI_arlock_converter = NULL;
  mp_M11_AXI_transactor = NULL;
  mp_M12_AXI_transactor = NULL;
  mp_M13_AXI_transactor = NULL;
  mp_M14_AXI_transactor = NULL;

  // initialize socket stubs

}

void zusys_smartconnect_0_0::before_end_of_elaboration()
{
  // configure 'S00_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "S00_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'S00_AXI' transactor parameters
    xsc::common_cpp::properties S00_AXI_transactor_param_props;
    S00_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    S00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S00_AXI_transactor_param_props.addLong("ID_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    S00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    S00_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    S00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    S00_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    S00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    S00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    S00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    S00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    S00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    S00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    S00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    S00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S00_AXI_transactor = new xtlm::xaximm_pin2xtlm_t<128,40,16,16,1,1,16,1>("S00_AXI_transactor", S00_AXI_transactor_param_props);

    // S00_AXI' transactor ports

    mp_S00_AXI_transactor->AWID(S00_AXI_awid);
    mp_S00_AXI_transactor->AWADDR(S00_AXI_awaddr);
    mp_S00_AXI_transactor->AWLEN(S00_AXI_awlen);
    mp_S00_AXI_transactor->AWSIZE(S00_AXI_awsize);
    mp_S00_AXI_transactor->AWBURST(S00_AXI_awburst);
    mp_S00_AXI_awlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_awlock_converter");
    mp_S00_AXI_awlock_converter->vector_in(S00_AXI_awlock);
    mp_S00_AXI_awlock_converter->scalar_out(m_S00_AXI_awlock_converter_signal);
    mp_S00_AXI_transactor->AWLOCK(m_S00_AXI_awlock_converter_signal);
    mp_S00_AXI_transactor->AWCACHE(S00_AXI_awcache);
    mp_S00_AXI_transactor->AWPROT(S00_AXI_awprot);
    mp_S00_AXI_transactor->AWQOS(S00_AXI_awqos);
    mp_S00_AXI_transactor->AWUSER(S00_AXI_awuser);
    mp_S00_AXI_transactor->AWVALID(S00_AXI_awvalid);
    mp_S00_AXI_transactor->AWREADY(S00_AXI_awready);
    mp_S00_AXI_transactor->WDATA(S00_AXI_wdata);
    mp_S00_AXI_transactor->WSTRB(S00_AXI_wstrb);
    mp_S00_AXI_transactor->WLAST(S00_AXI_wlast);
    mp_S00_AXI_transactor->WVALID(S00_AXI_wvalid);
    mp_S00_AXI_transactor->WREADY(S00_AXI_wready);
    mp_S00_AXI_transactor->BID(S00_AXI_bid);
    mp_S00_AXI_transactor->BRESP(S00_AXI_bresp);
    mp_S00_AXI_transactor->BVALID(S00_AXI_bvalid);
    mp_S00_AXI_transactor->BREADY(S00_AXI_bready);
    mp_S00_AXI_transactor->ARID(S00_AXI_arid);
    mp_S00_AXI_transactor->ARADDR(S00_AXI_araddr);
    mp_S00_AXI_transactor->ARLEN(S00_AXI_arlen);
    mp_S00_AXI_transactor->ARSIZE(S00_AXI_arsize);
    mp_S00_AXI_transactor->ARBURST(S00_AXI_arburst);
    mp_S00_AXI_arlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_arlock_converter");
    mp_S00_AXI_arlock_converter->vector_in(S00_AXI_arlock);
    mp_S00_AXI_arlock_converter->scalar_out(m_S00_AXI_arlock_converter_signal);
    mp_S00_AXI_transactor->ARLOCK(m_S00_AXI_arlock_converter_signal);
    mp_S00_AXI_transactor->ARCACHE(S00_AXI_arcache);
    mp_S00_AXI_transactor->ARPROT(S00_AXI_arprot);
    mp_S00_AXI_transactor->ARQOS(S00_AXI_arqos);
    mp_S00_AXI_transactor->ARUSER(S00_AXI_aruser);
    mp_S00_AXI_transactor->ARVALID(S00_AXI_arvalid);
    mp_S00_AXI_transactor->ARREADY(S00_AXI_arready);
    mp_S00_AXI_transactor->RID(S00_AXI_rid);
    mp_S00_AXI_transactor->RDATA(S00_AXI_rdata);
    mp_S00_AXI_transactor->RRESP(S00_AXI_rresp);
    mp_S00_AXI_transactor->RLAST(S00_AXI_rlast);
    mp_S00_AXI_transactor->RVALID(S00_AXI_rvalid);
    mp_S00_AXI_transactor->RREADY(S00_AXI_rready);
    mp_S00_AXI_transactor->CLK(aclk);
    mp_S00_AXI_transactor->RST(aresetn);

    // S00_AXI' transactor sockets

    mp_impl->S00_AXI_tlm_aximm_read_socket->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_impl->S00_AXI_tlm_aximm_write_socket->bind(*(mp_S00_AXI_transactor->wr_socket));
  }

  // configure 'M00_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M00_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M00_AXI' transactor parameters
    xsc::common_cpp::properties M00_AXI_transactor_param_props;
    M00_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M00_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M00_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M00_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M00_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M00_AXI_transactor", M00_AXI_transactor_param_props);

    // M00_AXI' transactor ports

    mp_M00_AXI_transactor->AWADDR(M00_AXI_awaddr);
    mp_M00_AXI_transactor->AWPROT(M00_AXI_awprot);
    mp_M00_AXI_transactor->AWVALID(M00_AXI_awvalid);
    mp_M00_AXI_transactor->AWREADY(M00_AXI_awready);
    mp_M00_AXI_transactor->WDATA(M00_AXI_wdata);
    mp_M00_AXI_transactor->WSTRB(M00_AXI_wstrb);
    mp_M00_AXI_transactor->WVALID(M00_AXI_wvalid);
    mp_M00_AXI_transactor->WREADY(M00_AXI_wready);
    mp_M00_AXI_transactor->BRESP(M00_AXI_bresp);
    mp_M00_AXI_transactor->BVALID(M00_AXI_bvalid);
    mp_M00_AXI_transactor->BREADY(M00_AXI_bready);
    mp_M00_AXI_transactor->ARADDR(M00_AXI_araddr);
    mp_M00_AXI_transactor->ARPROT(M00_AXI_arprot);
    mp_M00_AXI_transactor->ARVALID(M00_AXI_arvalid);
    mp_M00_AXI_transactor->ARREADY(M00_AXI_arready);
    mp_M00_AXI_transactor->RDATA(M00_AXI_rdata);
    mp_M00_AXI_transactor->RRESP(M00_AXI_rresp);
    mp_M00_AXI_transactor->RVALID(M00_AXI_rvalid);
    mp_M00_AXI_transactor->RREADY(M00_AXI_rready);
    mp_M00_AXI_transactor->CLK(aclk);
    mp_M00_AXI_transactor->RST(aresetn);

    // M00_AXI' transactor sockets

    mp_impl->M00_AXI_tlm_aximm_read_socket->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_impl->M00_AXI_tlm_aximm_write_socket->bind(*(mp_M00_AXI_transactor->wr_socket));
  }

  // configure 'M01_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M01_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M01_AXI' transactor parameters
    xsc::common_cpp::properties M01_AXI_transactor_param_props;
    M01_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M01_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M01_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M01_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M01_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M01_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M01_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M01_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M01_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M01_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M01_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M01_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M01_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M01_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M01_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M01_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M01_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M01_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M01_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M01_AXI_transactor", M01_AXI_transactor_param_props);

    // M01_AXI' transactor ports

    mp_M01_AXI_transactor->AWADDR(M01_AXI_awaddr);
    mp_M01_AXI_transactor->AWPROT(M01_AXI_awprot);
    mp_M01_AXI_transactor->AWVALID(M01_AXI_awvalid);
    mp_M01_AXI_transactor->AWREADY(M01_AXI_awready);
    mp_M01_AXI_transactor->WDATA(M01_AXI_wdata);
    mp_M01_AXI_transactor->WSTRB(M01_AXI_wstrb);
    mp_M01_AXI_transactor->WVALID(M01_AXI_wvalid);
    mp_M01_AXI_transactor->WREADY(M01_AXI_wready);
    mp_M01_AXI_transactor->BRESP(M01_AXI_bresp);
    mp_M01_AXI_transactor->BVALID(M01_AXI_bvalid);
    mp_M01_AXI_transactor->BREADY(M01_AXI_bready);
    mp_M01_AXI_transactor->ARADDR(M01_AXI_araddr);
    mp_M01_AXI_transactor->ARPROT(M01_AXI_arprot);
    mp_M01_AXI_transactor->ARVALID(M01_AXI_arvalid);
    mp_M01_AXI_transactor->ARREADY(M01_AXI_arready);
    mp_M01_AXI_transactor->RDATA(M01_AXI_rdata);
    mp_M01_AXI_transactor->RRESP(M01_AXI_rresp);
    mp_M01_AXI_transactor->RVALID(M01_AXI_rvalid);
    mp_M01_AXI_transactor->RREADY(M01_AXI_rready);
    mp_M01_AXI_transactor->CLK(aclk);
    mp_M01_AXI_transactor->RST(aresetn);

    // M01_AXI' transactor sockets

    mp_impl->M01_AXI_tlm_aximm_read_socket->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_impl->M01_AXI_tlm_aximm_write_socket->bind(*(mp_M01_AXI_transactor->wr_socket));
  }

  // configure 'M02_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M02_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M02_AXI' transactor parameters
    xsc::common_cpp::properties M02_AXI_transactor_param_props;
    M02_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M02_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M02_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M02_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M02_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M02_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M02_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M02_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M02_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M02_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M02_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M02_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M02_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M02_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M02_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M02_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M02_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M02_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M02_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M02_AXI_transactor", M02_AXI_transactor_param_props);

    // M02_AXI' transactor ports

    mp_M02_AXI_transactor->AWADDR(M02_AXI_awaddr);
    mp_M02_AXI_transactor->AWPROT(M02_AXI_awprot);
    mp_M02_AXI_transactor->AWVALID(M02_AXI_awvalid);
    mp_M02_AXI_transactor->AWREADY(M02_AXI_awready);
    mp_M02_AXI_transactor->WDATA(M02_AXI_wdata);
    mp_M02_AXI_transactor->WSTRB(M02_AXI_wstrb);
    mp_M02_AXI_transactor->WVALID(M02_AXI_wvalid);
    mp_M02_AXI_transactor->WREADY(M02_AXI_wready);
    mp_M02_AXI_transactor->BRESP(M02_AXI_bresp);
    mp_M02_AXI_transactor->BVALID(M02_AXI_bvalid);
    mp_M02_AXI_transactor->BREADY(M02_AXI_bready);
    mp_M02_AXI_transactor->ARADDR(M02_AXI_araddr);
    mp_M02_AXI_transactor->ARPROT(M02_AXI_arprot);
    mp_M02_AXI_transactor->ARVALID(M02_AXI_arvalid);
    mp_M02_AXI_transactor->ARREADY(M02_AXI_arready);
    mp_M02_AXI_transactor->RDATA(M02_AXI_rdata);
    mp_M02_AXI_transactor->RRESP(M02_AXI_rresp);
    mp_M02_AXI_transactor->RVALID(M02_AXI_rvalid);
    mp_M02_AXI_transactor->RREADY(M02_AXI_rready);
    mp_M02_AXI_transactor->CLK(aclk);
    mp_M02_AXI_transactor->RST(aresetn);

    // M02_AXI' transactor sockets

    mp_impl->M02_AXI_tlm_aximm_read_socket->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_impl->M02_AXI_tlm_aximm_write_socket->bind(*(mp_M02_AXI_transactor->wr_socket));
  }

  // configure 'M03_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M03_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M03_AXI' transactor parameters
    xsc::common_cpp::properties M03_AXI_transactor_param_props;
    M03_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M03_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M03_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M03_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M03_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M03_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M03_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M03_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M03_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M03_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M03_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M03_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M03_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M03_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M03_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M03_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M03_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M03_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M03_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M03_AXI_transactor", M03_AXI_transactor_param_props);

    // M03_AXI' transactor ports

    mp_M03_AXI_transactor->AWADDR(M03_AXI_awaddr);
    mp_M03_AXI_transactor->AWPROT(M03_AXI_awprot);
    mp_M03_AXI_transactor->AWVALID(M03_AXI_awvalid);
    mp_M03_AXI_transactor->AWREADY(M03_AXI_awready);
    mp_M03_AXI_transactor->WDATA(M03_AXI_wdata);
    mp_M03_AXI_transactor->WSTRB(M03_AXI_wstrb);
    mp_M03_AXI_transactor->WVALID(M03_AXI_wvalid);
    mp_M03_AXI_transactor->WREADY(M03_AXI_wready);
    mp_M03_AXI_transactor->BRESP(M03_AXI_bresp);
    mp_M03_AXI_transactor->BVALID(M03_AXI_bvalid);
    mp_M03_AXI_transactor->BREADY(M03_AXI_bready);
    mp_M03_AXI_transactor->ARADDR(M03_AXI_araddr);
    mp_M03_AXI_transactor->ARPROT(M03_AXI_arprot);
    mp_M03_AXI_transactor->ARVALID(M03_AXI_arvalid);
    mp_M03_AXI_transactor->ARREADY(M03_AXI_arready);
    mp_M03_AXI_transactor->RDATA(M03_AXI_rdata);
    mp_M03_AXI_transactor->RRESP(M03_AXI_rresp);
    mp_M03_AXI_transactor->RVALID(M03_AXI_rvalid);
    mp_M03_AXI_transactor->RREADY(M03_AXI_rready);
    mp_M03_AXI_transactor->CLK(aclk);
    mp_M03_AXI_transactor->RST(aresetn);

    // M03_AXI' transactor sockets

    mp_impl->M03_AXI_tlm_aximm_read_socket->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_impl->M03_AXI_tlm_aximm_write_socket->bind(*(mp_M03_AXI_transactor->wr_socket));
  }

  // configure 'M04_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M04_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M04_AXI' transactor parameters
    xsc::common_cpp::properties M04_AXI_transactor_param_props;
    M04_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M04_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M04_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M04_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M04_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M04_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M04_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M04_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M04_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M04_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M04_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M04_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M04_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M04_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M04_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M04_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M04_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M04_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M04_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M04_AXI_transactor", M04_AXI_transactor_param_props);

    // M04_AXI' transactor ports

    mp_M04_AXI_transactor->AWADDR(M04_AXI_awaddr);
    mp_M04_AXI_transactor->AWPROT(M04_AXI_awprot);
    mp_M04_AXI_transactor->AWVALID(M04_AXI_awvalid);
    mp_M04_AXI_transactor->AWREADY(M04_AXI_awready);
    mp_M04_AXI_transactor->WDATA(M04_AXI_wdata);
    mp_M04_AXI_transactor->WSTRB(M04_AXI_wstrb);
    mp_M04_AXI_transactor->WVALID(M04_AXI_wvalid);
    mp_M04_AXI_transactor->WREADY(M04_AXI_wready);
    mp_M04_AXI_transactor->BRESP(M04_AXI_bresp);
    mp_M04_AXI_transactor->BVALID(M04_AXI_bvalid);
    mp_M04_AXI_transactor->BREADY(M04_AXI_bready);
    mp_M04_AXI_transactor->ARADDR(M04_AXI_araddr);
    mp_M04_AXI_transactor->ARPROT(M04_AXI_arprot);
    mp_M04_AXI_transactor->ARVALID(M04_AXI_arvalid);
    mp_M04_AXI_transactor->ARREADY(M04_AXI_arready);
    mp_M04_AXI_transactor->RDATA(M04_AXI_rdata);
    mp_M04_AXI_transactor->RRESP(M04_AXI_rresp);
    mp_M04_AXI_transactor->RVALID(M04_AXI_rvalid);
    mp_M04_AXI_transactor->RREADY(M04_AXI_rready);
    mp_M04_AXI_transactor->CLK(aclk);
    mp_M04_AXI_transactor->RST(aresetn);

    // M04_AXI' transactor sockets

    mp_impl->M04_AXI_tlm_aximm_read_socket->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_impl->M04_AXI_tlm_aximm_write_socket->bind(*(mp_M04_AXI_transactor->wr_socket));
  }

  // configure 'M05_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M05_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M05_AXI' transactor parameters
    xsc::common_cpp::properties M05_AXI_transactor_param_props;
    M05_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M05_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M05_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M05_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M05_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M05_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M05_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M05_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M05_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M05_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M05_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M05_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M05_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M05_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M05_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M05_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M05_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M05_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M05_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M05_AXI_transactor", M05_AXI_transactor_param_props);

    // M05_AXI' transactor ports

    mp_M05_AXI_transactor->AWADDR(M05_AXI_awaddr);
    mp_M05_AXI_transactor->AWPROT(M05_AXI_awprot);
    mp_M05_AXI_transactor->AWVALID(M05_AXI_awvalid);
    mp_M05_AXI_transactor->AWREADY(M05_AXI_awready);
    mp_M05_AXI_transactor->WDATA(M05_AXI_wdata);
    mp_M05_AXI_transactor->WSTRB(M05_AXI_wstrb);
    mp_M05_AXI_transactor->WVALID(M05_AXI_wvalid);
    mp_M05_AXI_transactor->WREADY(M05_AXI_wready);
    mp_M05_AXI_transactor->BRESP(M05_AXI_bresp);
    mp_M05_AXI_transactor->BVALID(M05_AXI_bvalid);
    mp_M05_AXI_transactor->BREADY(M05_AXI_bready);
    mp_M05_AXI_transactor->ARADDR(M05_AXI_araddr);
    mp_M05_AXI_transactor->ARPROT(M05_AXI_arprot);
    mp_M05_AXI_transactor->ARVALID(M05_AXI_arvalid);
    mp_M05_AXI_transactor->ARREADY(M05_AXI_arready);
    mp_M05_AXI_transactor->RDATA(M05_AXI_rdata);
    mp_M05_AXI_transactor->RRESP(M05_AXI_rresp);
    mp_M05_AXI_transactor->RVALID(M05_AXI_rvalid);
    mp_M05_AXI_transactor->RREADY(M05_AXI_rready);
    mp_M05_AXI_transactor->CLK(aclk);
    mp_M05_AXI_transactor->RST(aresetn);

    // M05_AXI' transactor sockets

    mp_impl->M05_AXI_tlm_aximm_read_socket->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_impl->M05_AXI_tlm_aximm_write_socket->bind(*(mp_M05_AXI_transactor->wr_socket));
  }

  // configure 'M06_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M06_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M06_AXI' transactor parameters
    xsc::common_cpp::properties M06_AXI_transactor_param_props;
    M06_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M06_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M06_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ADDR_WIDTH", "9");
    M06_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M06_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M06_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M06_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M06_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M06_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M06_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M06_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M06_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M06_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M06_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M06_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M06_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M06_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M06_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M06_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,9,1,1,1,1,1,1>("M06_AXI_transactor", M06_AXI_transactor_param_props);

    // M06_AXI' transactor ports

    mp_M06_AXI_transactor->AWADDR(M06_AXI_awaddr);
    mp_M06_AXI_transactor->AWPROT(M06_AXI_awprot);
    mp_M06_AXI_transactor->AWVALID(M06_AXI_awvalid);
    mp_M06_AXI_transactor->AWREADY(M06_AXI_awready);
    mp_M06_AXI_transactor->WDATA(M06_AXI_wdata);
    mp_M06_AXI_transactor->WSTRB(M06_AXI_wstrb);
    mp_M06_AXI_transactor->WVALID(M06_AXI_wvalid);
    mp_M06_AXI_transactor->WREADY(M06_AXI_wready);
    mp_M06_AXI_transactor->BRESP(M06_AXI_bresp);
    mp_M06_AXI_transactor->BVALID(M06_AXI_bvalid);
    mp_M06_AXI_transactor->BREADY(M06_AXI_bready);
    mp_M06_AXI_transactor->ARADDR(M06_AXI_araddr);
    mp_M06_AXI_transactor->ARPROT(M06_AXI_arprot);
    mp_M06_AXI_transactor->ARVALID(M06_AXI_arvalid);
    mp_M06_AXI_transactor->ARREADY(M06_AXI_arready);
    mp_M06_AXI_transactor->RDATA(M06_AXI_rdata);
    mp_M06_AXI_transactor->RRESP(M06_AXI_rresp);
    mp_M06_AXI_transactor->RVALID(M06_AXI_rvalid);
    mp_M06_AXI_transactor->RREADY(M06_AXI_rready);
    mp_M06_AXI_transactor->CLK(aclk);
    mp_M06_AXI_transactor->RST(aresetn);

    // M06_AXI' transactor sockets

    mp_impl->M06_AXI_tlm_aximm_read_socket->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_impl->M06_AXI_tlm_aximm_write_socket->bind(*(mp_M06_AXI_transactor->wr_socket));
  }

  // configure 'M07_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M07_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M07_AXI' transactor parameters
    xsc::common_cpp::properties M07_AXI_transactor_param_props;
    M07_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M07_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M07_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M07_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M07_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M07_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M07_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M07_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M07_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M07_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M07_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M07_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M07_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M07_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M07_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M07_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M07_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,16,1,1,16,1>("M07_AXI_transactor", M07_AXI_transactor_param_props);

    // M07_AXI' transactor ports

    mp_M07_AXI_transactor->AWADDR(M07_AXI_awaddr);
    mp_M07_AXI_transactor->AWLEN(M07_AXI_awlen);
    mp_M07_AXI_transactor->AWSIZE(M07_AXI_awsize);
    mp_M07_AXI_transactor->AWBURST(M07_AXI_awburst);
    mp_M07_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_awlock_converter");
    mp_M07_AXI_awlock_converter->scalar_in(m_M07_AXI_awlock_converter_signal);
    mp_M07_AXI_awlock_converter->vector_out(M07_AXI_awlock);
    mp_M07_AXI_transactor->AWLOCK(m_M07_AXI_awlock_converter_signal);
    mp_M07_AXI_transactor->AWCACHE(M07_AXI_awcache);
    mp_M07_AXI_transactor->AWPROT(M07_AXI_awprot);
    mp_M07_AXI_transactor->AWQOS(M07_AXI_awqos);
    mp_M07_AXI_transactor->AWUSER(M07_AXI_awuser);
    mp_M07_AXI_transactor->AWVALID(M07_AXI_awvalid);
    mp_M07_AXI_transactor->AWREADY(M07_AXI_awready);
    mp_M07_AXI_transactor->WDATA(M07_AXI_wdata);
    mp_M07_AXI_transactor->WSTRB(M07_AXI_wstrb);
    mp_M07_AXI_transactor->WLAST(M07_AXI_wlast);
    mp_M07_AXI_transactor->WVALID(M07_AXI_wvalid);
    mp_M07_AXI_transactor->WREADY(M07_AXI_wready);
    mp_M07_AXI_transactor->BRESP(M07_AXI_bresp);
    mp_M07_AXI_transactor->BVALID(M07_AXI_bvalid);
    mp_M07_AXI_transactor->BREADY(M07_AXI_bready);
    mp_M07_AXI_transactor->ARADDR(M07_AXI_araddr);
    mp_M07_AXI_transactor->ARLEN(M07_AXI_arlen);
    mp_M07_AXI_transactor->ARSIZE(M07_AXI_arsize);
    mp_M07_AXI_transactor->ARBURST(M07_AXI_arburst);
    mp_M07_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_arlock_converter");
    mp_M07_AXI_arlock_converter->scalar_in(m_M07_AXI_arlock_converter_signal);
    mp_M07_AXI_arlock_converter->vector_out(M07_AXI_arlock);
    mp_M07_AXI_transactor->ARLOCK(m_M07_AXI_arlock_converter_signal);
    mp_M07_AXI_transactor->ARCACHE(M07_AXI_arcache);
    mp_M07_AXI_transactor->ARPROT(M07_AXI_arprot);
    mp_M07_AXI_transactor->ARQOS(M07_AXI_arqos);
    mp_M07_AXI_transactor->ARUSER(M07_AXI_aruser);
    mp_M07_AXI_transactor->ARVALID(M07_AXI_arvalid);
    mp_M07_AXI_transactor->ARREADY(M07_AXI_arready);
    mp_M07_AXI_transactor->RDATA(M07_AXI_rdata);
    mp_M07_AXI_transactor->RRESP(M07_AXI_rresp);
    mp_M07_AXI_transactor->RLAST(M07_AXI_rlast);
    mp_M07_AXI_transactor->RVALID(M07_AXI_rvalid);
    mp_M07_AXI_transactor->RREADY(M07_AXI_rready);
    mp_M07_AXI_transactor->CLK(aclk);
    mp_M07_AXI_transactor->RST(aresetn);

    // M07_AXI' transactor sockets

    mp_impl->M07_AXI_tlm_aximm_read_socket->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_impl->M07_AXI_tlm_aximm_write_socket->bind(*(mp_M07_AXI_transactor->wr_socket));
  }

  // configure 'M08_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M08_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M08_AXI' transactor parameters
    xsc::common_cpp::properties M08_AXI_transactor_param_props;
    M08_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M08_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M08_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M08_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M08_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M08_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M08_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M08_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M08_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M08_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M08_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M08_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M08_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M08_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M08_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M08_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M08_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M08_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M08_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M08_AXI_transactor", M08_AXI_transactor_param_props);

    // M08_AXI' transactor ports

    mp_M08_AXI_transactor->AWADDR(M08_AXI_awaddr);
    mp_M08_AXI_transactor->AWPROT(M08_AXI_awprot);
    mp_M08_AXI_transactor->AWVALID(M08_AXI_awvalid);
    mp_M08_AXI_transactor->AWREADY(M08_AXI_awready);
    mp_M08_AXI_transactor->WDATA(M08_AXI_wdata);
    mp_M08_AXI_transactor->WSTRB(M08_AXI_wstrb);
    mp_M08_AXI_transactor->WVALID(M08_AXI_wvalid);
    mp_M08_AXI_transactor->WREADY(M08_AXI_wready);
    mp_M08_AXI_transactor->BRESP(M08_AXI_bresp);
    mp_M08_AXI_transactor->BVALID(M08_AXI_bvalid);
    mp_M08_AXI_transactor->BREADY(M08_AXI_bready);
    mp_M08_AXI_transactor->ARADDR(M08_AXI_araddr);
    mp_M08_AXI_transactor->ARPROT(M08_AXI_arprot);
    mp_M08_AXI_transactor->ARVALID(M08_AXI_arvalid);
    mp_M08_AXI_transactor->ARREADY(M08_AXI_arready);
    mp_M08_AXI_transactor->RDATA(M08_AXI_rdata);
    mp_M08_AXI_transactor->RRESP(M08_AXI_rresp);
    mp_M08_AXI_transactor->RVALID(M08_AXI_rvalid);
    mp_M08_AXI_transactor->RREADY(M08_AXI_rready);
    mp_M08_AXI_transactor->CLK(aclk);
    mp_M08_AXI_transactor->RST(aresetn);

    // M08_AXI' transactor sockets

    mp_impl->M08_AXI_tlm_aximm_read_socket->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_impl->M08_AXI_tlm_aximm_write_socket->bind(*(mp_M08_AXI_transactor->wr_socket));
  }

  // configure 'M09_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M09_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M09_AXI' transactor parameters
    xsc::common_cpp::properties M09_AXI_transactor_param_props;
    M09_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M09_AXI_transactor_param_props.addLong("FREQ_HZ", "50000000");
    M09_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M09_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M09_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M09_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M09_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M09_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M09_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M09_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M09_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M09_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M09_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M09_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M09_AXI_transactor_param_props.addFloat("PHASE", "0.0");
    M09_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M09_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M09_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_clk_wiz_0_0_clk_50MHz");

    mp_M09_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M09_AXI_transactor", M09_AXI_transactor_param_props);

    // M09_AXI' transactor ports

    mp_M09_AXI_transactor->AWADDR(M09_AXI_awaddr);
    mp_M09_AXI_transactor->AWPROT(M09_AXI_awprot);
    mp_M09_AXI_transactor->AWVALID(M09_AXI_awvalid);
    mp_M09_AXI_transactor->AWREADY(M09_AXI_awready);
    mp_M09_AXI_transactor->WDATA(M09_AXI_wdata);
    mp_M09_AXI_transactor->WSTRB(M09_AXI_wstrb);
    mp_M09_AXI_transactor->WVALID(M09_AXI_wvalid);
    mp_M09_AXI_transactor->WREADY(M09_AXI_wready);
    mp_M09_AXI_transactor->BRESP(M09_AXI_bresp);
    mp_M09_AXI_transactor->BVALID(M09_AXI_bvalid);
    mp_M09_AXI_transactor->BREADY(M09_AXI_bready);
    mp_M09_AXI_transactor->ARADDR(M09_AXI_araddr);
    mp_M09_AXI_transactor->ARPROT(M09_AXI_arprot);
    mp_M09_AXI_transactor->ARVALID(M09_AXI_arvalid);
    mp_M09_AXI_transactor->ARREADY(M09_AXI_arready);
    mp_M09_AXI_transactor->RDATA(M09_AXI_rdata);
    mp_M09_AXI_transactor->RRESP(M09_AXI_rresp);
    mp_M09_AXI_transactor->RVALID(M09_AXI_rvalid);
    mp_M09_AXI_transactor->RREADY(M09_AXI_rready);
    mp_M09_AXI_transactor->CLK(aclk2);
    mp_M09_AXI_transactor->RST(aresetn);

    // M09_AXI' transactor sockets

    mp_impl->M09_AXI_tlm_aximm_read_socket->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_impl->M09_AXI_tlm_aximm_write_socket->bind(*(mp_M09_AXI_transactor->wr_socket));
  }

  // configure 'M10_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M10_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M10_AXI' transactor parameters
    xsc::common_cpp::properties M10_AXI_transactor_param_props;
    M10_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    M10_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M10_AXI_transactor_param_props.addLong("ID_WIDTH", "3");
    M10_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M10_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("WUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("RUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("BUSER_WIDTH", "114");
    M10_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M10_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M10_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M10_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M10_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M10_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M10_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M10_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M10_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M10_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M10_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M10_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M10_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M10_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M10_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,3,130,14,114,130,14>("M10_AXI_transactor", M10_AXI_transactor_param_props);

    // M10_AXI' transactor ports

    mp_M10_AXI_transactor->AWID(M10_AXI_awid);
    mp_M10_AXI_transactor->AWADDR(M10_AXI_awaddr);
    mp_M10_AXI_transactor->AWLEN(M10_AXI_awlen);
    mp_M10_AXI_transactor->AWSIZE(M10_AXI_awsize);
    mp_M10_AXI_transactor->AWBURST(M10_AXI_awburst);
    mp_M10_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_awlock_converter");
    mp_M10_AXI_awlock_converter->scalar_in(m_M10_AXI_awlock_converter_signal);
    mp_M10_AXI_awlock_converter->vector_out(M10_AXI_awlock);
    mp_M10_AXI_transactor->AWLOCK(m_M10_AXI_awlock_converter_signal);
    mp_M10_AXI_transactor->AWCACHE(M10_AXI_awcache);
    mp_M10_AXI_transactor->AWPROT(M10_AXI_awprot);
    mp_M10_AXI_transactor->AWQOS(M10_AXI_awqos);
    mp_M10_AXI_transactor->AWUSER(M10_AXI_awuser);
    mp_M10_AXI_transactor->AWVALID(M10_AXI_awvalid);
    mp_M10_AXI_transactor->AWREADY(M10_AXI_awready);
    mp_M10_AXI_transactor->WDATA(M10_AXI_wdata);
    mp_M10_AXI_transactor->WSTRB(M10_AXI_wstrb);
    mp_M10_AXI_transactor->WLAST(M10_AXI_wlast);
    mp_M10_AXI_transactor->WUSER(M10_AXI_wuser);
    mp_M10_AXI_transactor->WVALID(M10_AXI_wvalid);
    mp_M10_AXI_transactor->WREADY(M10_AXI_wready);
    mp_M10_AXI_transactor->BID(M10_AXI_bid);
    mp_M10_AXI_transactor->BRESP(M10_AXI_bresp);
    mp_M10_AXI_transactor->BUSER(M10_AXI_buser);
    mp_M10_AXI_transactor->BVALID(M10_AXI_bvalid);
    mp_M10_AXI_transactor->BREADY(M10_AXI_bready);
    mp_M10_AXI_transactor->ARID(M10_AXI_arid);
    mp_M10_AXI_transactor->ARADDR(M10_AXI_araddr);
    mp_M10_AXI_transactor->ARLEN(M10_AXI_arlen);
    mp_M10_AXI_transactor->ARSIZE(M10_AXI_arsize);
    mp_M10_AXI_transactor->ARBURST(M10_AXI_arburst);
    mp_M10_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_arlock_converter");
    mp_M10_AXI_arlock_converter->scalar_in(m_M10_AXI_arlock_converter_signal);
    mp_M10_AXI_arlock_converter->vector_out(M10_AXI_arlock);
    mp_M10_AXI_transactor->ARLOCK(m_M10_AXI_arlock_converter_signal);
    mp_M10_AXI_transactor->ARCACHE(M10_AXI_arcache);
    mp_M10_AXI_transactor->ARPROT(M10_AXI_arprot);
    mp_M10_AXI_transactor->ARQOS(M10_AXI_arqos);
    mp_M10_AXI_transactor->ARUSER(M10_AXI_aruser);
    mp_M10_AXI_transactor->ARVALID(M10_AXI_arvalid);
    mp_M10_AXI_transactor->ARREADY(M10_AXI_arready);
    mp_M10_AXI_transactor->RID(M10_AXI_rid);
    mp_M10_AXI_transactor->RDATA(M10_AXI_rdata);
    mp_M10_AXI_transactor->RRESP(M10_AXI_rresp);
    mp_M10_AXI_transactor->RLAST(M10_AXI_rlast);
    mp_M10_AXI_transactor->RUSER(M10_AXI_ruser);
    mp_M10_AXI_transactor->RVALID(M10_AXI_rvalid);
    mp_M10_AXI_transactor->RREADY(M10_AXI_rready);
    mp_M10_AXI_transactor->CLK(aclk);
    mp_M10_AXI_transactor->RST(aresetn);

    // M10_AXI' transactor sockets

    mp_impl->M10_AXI_tlm_aximm_read_socket->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_impl->M10_AXI_tlm_aximm_write_socket->bind(*(mp_M10_AXI_transactor->wr_socket));
  }

  // configure 'M11_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M11_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M11_AXI' transactor parameters
    xsc::common_cpp::properties M11_AXI_transactor_param_props;
    M11_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M11_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M11_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M11_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M11_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M11_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M11_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M11_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M11_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M11_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M11_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M11_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M11_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M11_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M11_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M11_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M11_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M11_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M11_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M11_AXI_transactor", M11_AXI_transactor_param_props);

    // M11_AXI' transactor ports

    mp_M11_AXI_transactor->AWADDR(M11_AXI_awaddr);
    mp_M11_AXI_transactor->AWPROT(M11_AXI_awprot);
    mp_M11_AXI_transactor->AWVALID(M11_AXI_awvalid);
    mp_M11_AXI_transactor->AWREADY(M11_AXI_awready);
    mp_M11_AXI_transactor->WDATA(M11_AXI_wdata);
    mp_M11_AXI_transactor->WSTRB(M11_AXI_wstrb);
    mp_M11_AXI_transactor->WVALID(M11_AXI_wvalid);
    mp_M11_AXI_transactor->WREADY(M11_AXI_wready);
    mp_M11_AXI_transactor->BRESP(M11_AXI_bresp);
    mp_M11_AXI_transactor->BVALID(M11_AXI_bvalid);
    mp_M11_AXI_transactor->BREADY(M11_AXI_bready);
    mp_M11_AXI_transactor->ARADDR(M11_AXI_araddr);
    mp_M11_AXI_transactor->ARPROT(M11_AXI_arprot);
    mp_M11_AXI_transactor->ARVALID(M11_AXI_arvalid);
    mp_M11_AXI_transactor->ARREADY(M11_AXI_arready);
    mp_M11_AXI_transactor->RDATA(M11_AXI_rdata);
    mp_M11_AXI_transactor->RRESP(M11_AXI_rresp);
    mp_M11_AXI_transactor->RVALID(M11_AXI_rvalid);
    mp_M11_AXI_transactor->RREADY(M11_AXI_rready);
    mp_M11_AXI_transactor->CLK(aclk);
    mp_M11_AXI_transactor->RST(aresetn);

    // M11_AXI' transactor sockets

    mp_impl->M11_AXI_tlm_aximm_read_socket->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_impl->M11_AXI_tlm_aximm_write_socket->bind(*(mp_M11_AXI_transactor->wr_socket));
  }

  // configure 'M12_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M12_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M12_AXI' transactor parameters
    xsc::common_cpp::properties M12_AXI_transactor_param_props;
    M12_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M12_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M12_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M12_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M12_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M12_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M12_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M12_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M12_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M12_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M12_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M12_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M12_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M12_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M12_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M12_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M12_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M12_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M12_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M12_AXI_transactor", M12_AXI_transactor_param_props);

    // M12_AXI' transactor ports

    mp_M12_AXI_transactor->AWADDR(M12_AXI_awaddr);
    mp_M12_AXI_transactor->AWPROT(M12_AXI_awprot);
    mp_M12_AXI_transactor->AWVALID(M12_AXI_awvalid);
    mp_M12_AXI_transactor->AWREADY(M12_AXI_awready);
    mp_M12_AXI_transactor->WDATA(M12_AXI_wdata);
    mp_M12_AXI_transactor->WSTRB(M12_AXI_wstrb);
    mp_M12_AXI_transactor->WVALID(M12_AXI_wvalid);
    mp_M12_AXI_transactor->WREADY(M12_AXI_wready);
    mp_M12_AXI_transactor->BRESP(M12_AXI_bresp);
    mp_M12_AXI_transactor->BVALID(M12_AXI_bvalid);
    mp_M12_AXI_transactor->BREADY(M12_AXI_bready);
    mp_M12_AXI_transactor->ARADDR(M12_AXI_araddr);
    mp_M12_AXI_transactor->ARPROT(M12_AXI_arprot);
    mp_M12_AXI_transactor->ARVALID(M12_AXI_arvalid);
    mp_M12_AXI_transactor->ARREADY(M12_AXI_arready);
    mp_M12_AXI_transactor->RDATA(M12_AXI_rdata);
    mp_M12_AXI_transactor->RRESP(M12_AXI_rresp);
    mp_M12_AXI_transactor->RVALID(M12_AXI_rvalid);
    mp_M12_AXI_transactor->RREADY(M12_AXI_rready);
    mp_M12_AXI_transactor->CLK(aclk);
    mp_M12_AXI_transactor->RST(aresetn);

    // M12_AXI' transactor sockets

    mp_impl->M12_AXI_tlm_aximm_read_socket->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_impl->M12_AXI_tlm_aximm_write_socket->bind(*(mp_M12_AXI_transactor->wr_socket));
  }

  // configure 'M13_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M13_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M13_AXI' transactor parameters
    xsc::common_cpp::properties M13_AXI_transactor_param_props;
    M13_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M13_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M13_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M13_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M13_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M13_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M13_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M13_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M13_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M13_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M13_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M13_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M13_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M13_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M13_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M13_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M13_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M13_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M13_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M13_AXI_transactor", M13_AXI_transactor_param_props);

    // M13_AXI' transactor ports

    mp_M13_AXI_transactor->AWADDR(M13_AXI_awaddr);
    mp_M13_AXI_transactor->AWPROT(M13_AXI_awprot);
    mp_M13_AXI_transactor->AWVALID(M13_AXI_awvalid);
    mp_M13_AXI_transactor->AWREADY(M13_AXI_awready);
    mp_M13_AXI_transactor->WDATA(M13_AXI_wdata);
    mp_M13_AXI_transactor->WSTRB(M13_AXI_wstrb);
    mp_M13_AXI_transactor->WVALID(M13_AXI_wvalid);
    mp_M13_AXI_transactor->WREADY(M13_AXI_wready);
    mp_M13_AXI_transactor->BRESP(M13_AXI_bresp);
    mp_M13_AXI_transactor->BVALID(M13_AXI_bvalid);
    mp_M13_AXI_transactor->BREADY(M13_AXI_bready);
    mp_M13_AXI_transactor->ARADDR(M13_AXI_araddr);
    mp_M13_AXI_transactor->ARPROT(M13_AXI_arprot);
    mp_M13_AXI_transactor->ARVALID(M13_AXI_arvalid);
    mp_M13_AXI_transactor->ARREADY(M13_AXI_arready);
    mp_M13_AXI_transactor->RDATA(M13_AXI_rdata);
    mp_M13_AXI_transactor->RRESP(M13_AXI_rresp);
    mp_M13_AXI_transactor->RVALID(M13_AXI_rvalid);
    mp_M13_AXI_transactor->RREADY(M13_AXI_rready);
    mp_M13_AXI_transactor->CLK(aclk);
    mp_M13_AXI_transactor->RST(aresetn);

    // M13_AXI' transactor sockets

    mp_impl->M13_AXI_tlm_aximm_read_socket->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_impl->M13_AXI_tlm_aximm_write_socket->bind(*(mp_M13_AXI_transactor->wr_socket));
  }

  // configure 'M14_AXI' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M14_AXI_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M14_AXI' transactor parameters
    xsc::common_cpp::properties M14_AXI_transactor_param_props;
    M14_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M14_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M14_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M14_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M14_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M14_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M14_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M14_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M14_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M14_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M14_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M14_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M14_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M14_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M14_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M14_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M14_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M14_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M14_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M14_AXI_transactor", M14_AXI_transactor_param_props);

    // M14_AXI' transactor ports

    mp_M14_AXI_transactor->AWADDR(M14_AXI_awaddr);
    mp_M14_AXI_transactor->AWPROT(M14_AXI_awprot);
    mp_M14_AXI_transactor->AWVALID(M14_AXI_awvalid);
    mp_M14_AXI_transactor->AWREADY(M14_AXI_awready);
    mp_M14_AXI_transactor->WDATA(M14_AXI_wdata);
    mp_M14_AXI_transactor->WSTRB(M14_AXI_wstrb);
    mp_M14_AXI_transactor->WVALID(M14_AXI_wvalid);
    mp_M14_AXI_transactor->WREADY(M14_AXI_wready);
    mp_M14_AXI_transactor->BRESP(M14_AXI_bresp);
    mp_M14_AXI_transactor->BVALID(M14_AXI_bvalid);
    mp_M14_AXI_transactor->BREADY(M14_AXI_bready);
    mp_M14_AXI_transactor->ARADDR(M14_AXI_araddr);
    mp_M14_AXI_transactor->ARPROT(M14_AXI_arprot);
    mp_M14_AXI_transactor->ARVALID(M14_AXI_arvalid);
    mp_M14_AXI_transactor->ARREADY(M14_AXI_arready);
    mp_M14_AXI_transactor->RDATA(M14_AXI_rdata);
    mp_M14_AXI_transactor->RRESP(M14_AXI_rresp);
    mp_M14_AXI_transactor->RVALID(M14_AXI_rvalid);
    mp_M14_AXI_transactor->RREADY(M14_AXI_rready);
    mp_M14_AXI_transactor->CLK(aclk);
    mp_M14_AXI_transactor->RST(aresetn);

    // M14_AXI' transactor sockets

    mp_impl->M14_AXI_tlm_aximm_read_socket->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_impl->M14_AXI_tlm_aximm_write_socket->bind(*(mp_M14_AXI_transactor->wr_socket));
  }

}

#endif // RIVIERA




#ifdef VCSSYSTEMC
zusys_smartconnect_0_0::zusys_smartconnect_0_0(const sc_core::sc_module_name& nm) : zusys_smartconnect_0_0_sc(nm),  aclk("aclk"), aclk1("aclk1"), aclk2("aclk2"), aresetn("aresetn"), S00_AXI_awid("S00_AXI_awid"), S00_AXI_awaddr("S00_AXI_awaddr"), S00_AXI_awlen("S00_AXI_awlen"), S00_AXI_awsize("S00_AXI_awsize"), S00_AXI_awburst("S00_AXI_awburst"), S00_AXI_awlock("S00_AXI_awlock"), S00_AXI_awcache("S00_AXI_awcache"), S00_AXI_awprot("S00_AXI_awprot"), S00_AXI_awqos("S00_AXI_awqos"), S00_AXI_awuser("S00_AXI_awuser"), S00_AXI_awvalid("S00_AXI_awvalid"), S00_AXI_awready("S00_AXI_awready"), S00_AXI_wdata("S00_AXI_wdata"), S00_AXI_wstrb("S00_AXI_wstrb"), S00_AXI_wlast("S00_AXI_wlast"), S00_AXI_wvalid("S00_AXI_wvalid"), S00_AXI_wready("S00_AXI_wready"), S00_AXI_bid("S00_AXI_bid"), S00_AXI_bresp("S00_AXI_bresp"), S00_AXI_bvalid("S00_AXI_bvalid"), S00_AXI_bready("S00_AXI_bready"), S00_AXI_arid("S00_AXI_arid"), S00_AXI_araddr("S00_AXI_araddr"), S00_AXI_arlen("S00_AXI_arlen"), S00_AXI_arsize("S00_AXI_arsize"), S00_AXI_arburst("S00_AXI_arburst"), S00_AXI_arlock("S00_AXI_arlock"), S00_AXI_arcache("S00_AXI_arcache"), S00_AXI_arprot("S00_AXI_arprot"), S00_AXI_arqos("S00_AXI_arqos"), S00_AXI_aruser("S00_AXI_aruser"), S00_AXI_arvalid("S00_AXI_arvalid"), S00_AXI_arready("S00_AXI_arready"), S00_AXI_rid("S00_AXI_rid"), S00_AXI_rdata("S00_AXI_rdata"), S00_AXI_rresp("S00_AXI_rresp"), S00_AXI_rlast("S00_AXI_rlast"), S00_AXI_rvalid("S00_AXI_rvalid"), S00_AXI_rready("S00_AXI_rready"), M00_AXI_awaddr("M00_AXI_awaddr"), M00_AXI_awprot("M00_AXI_awprot"), M00_AXI_awvalid("M00_AXI_awvalid"), M00_AXI_awready("M00_AXI_awready"), M00_AXI_wdata("M00_AXI_wdata"), M00_AXI_wstrb("M00_AXI_wstrb"), M00_AXI_wvalid("M00_AXI_wvalid"), M00_AXI_wready("M00_AXI_wready"), M00_AXI_bresp("M00_AXI_bresp"), M00_AXI_bvalid("M00_AXI_bvalid"), M00_AXI_bready("M00_AXI_bready"), M00_AXI_araddr("M00_AXI_araddr"), M00_AXI_arprot("M00_AXI_arprot"), M00_AXI_arvalid("M00_AXI_arvalid"), M00_AXI_arready("M00_AXI_arready"), M00_AXI_rdata("M00_AXI_rdata"), M00_AXI_rresp("M00_AXI_rresp"), M00_AXI_rvalid("M00_AXI_rvalid"), M00_AXI_rready("M00_AXI_rready"), M01_AXI_awaddr("M01_AXI_awaddr"), M01_AXI_awprot("M01_AXI_awprot"), M01_AXI_awvalid("M01_AXI_awvalid"), M01_AXI_awready("M01_AXI_awready"), M01_AXI_wdata("M01_AXI_wdata"), M01_AXI_wstrb("M01_AXI_wstrb"), M01_AXI_wvalid("M01_AXI_wvalid"), M01_AXI_wready("M01_AXI_wready"), M01_AXI_bresp("M01_AXI_bresp"), M01_AXI_bvalid("M01_AXI_bvalid"), M01_AXI_bready("M01_AXI_bready"), M01_AXI_araddr("M01_AXI_araddr"), M01_AXI_arprot("M01_AXI_arprot"), M01_AXI_arvalid("M01_AXI_arvalid"), M01_AXI_arready("M01_AXI_arready"), M01_AXI_rdata("M01_AXI_rdata"), M01_AXI_rresp("M01_AXI_rresp"), M01_AXI_rvalid("M01_AXI_rvalid"), M01_AXI_rready("M01_AXI_rready"), M02_AXI_awaddr("M02_AXI_awaddr"), M02_AXI_awprot("M02_AXI_awprot"), M02_AXI_awvalid("M02_AXI_awvalid"), M02_AXI_awready("M02_AXI_awready"), M02_AXI_wdata("M02_AXI_wdata"), M02_AXI_wstrb("M02_AXI_wstrb"), M02_AXI_wvalid("M02_AXI_wvalid"), M02_AXI_wready("M02_AXI_wready"), M02_AXI_bresp("M02_AXI_bresp"), M02_AXI_bvalid("M02_AXI_bvalid"), M02_AXI_bready("M02_AXI_bready"), M02_AXI_araddr("M02_AXI_araddr"), M02_AXI_arprot("M02_AXI_arprot"), M02_AXI_arvalid("M02_AXI_arvalid"), M02_AXI_arready("M02_AXI_arready"), M02_AXI_rdata("M02_AXI_rdata"), M02_AXI_rresp("M02_AXI_rresp"), M02_AXI_rvalid("M02_AXI_rvalid"), M02_AXI_rready("M02_AXI_rready"), M03_AXI_awaddr("M03_AXI_awaddr"), M03_AXI_awprot("M03_AXI_awprot"), M03_AXI_awvalid("M03_AXI_awvalid"), M03_AXI_awready("M03_AXI_awready"), M03_AXI_wdata("M03_AXI_wdata"), M03_AXI_wstrb("M03_AXI_wstrb"), M03_AXI_wvalid("M03_AXI_wvalid"), M03_AXI_wready("M03_AXI_wready"), M03_AXI_bresp("M03_AXI_bresp"), M03_AXI_bvalid("M03_AXI_bvalid"), M03_AXI_bready("M03_AXI_bready"), M03_AXI_araddr("M03_AXI_araddr"), M03_AXI_arprot("M03_AXI_arprot"), M03_AXI_arvalid("M03_AXI_arvalid"), M03_AXI_arready("M03_AXI_arready"), M03_AXI_rdata("M03_AXI_rdata"), M03_AXI_rresp("M03_AXI_rresp"), M03_AXI_rvalid("M03_AXI_rvalid"), M03_AXI_rready("M03_AXI_rready"), M04_AXI_awaddr("M04_AXI_awaddr"), M04_AXI_awprot("M04_AXI_awprot"), M04_AXI_awvalid("M04_AXI_awvalid"), M04_AXI_awready("M04_AXI_awready"), M04_AXI_wdata("M04_AXI_wdata"), M04_AXI_wstrb("M04_AXI_wstrb"), M04_AXI_wvalid("M04_AXI_wvalid"), M04_AXI_wready("M04_AXI_wready"), M04_AXI_bresp("M04_AXI_bresp"), M04_AXI_bvalid("M04_AXI_bvalid"), M04_AXI_bready("M04_AXI_bready"), M04_AXI_araddr("M04_AXI_araddr"), M04_AXI_arprot("M04_AXI_arprot"), M04_AXI_arvalid("M04_AXI_arvalid"), M04_AXI_arready("M04_AXI_arready"), M04_AXI_rdata("M04_AXI_rdata"), M04_AXI_rresp("M04_AXI_rresp"), M04_AXI_rvalid("M04_AXI_rvalid"), M04_AXI_rready("M04_AXI_rready"), M05_AXI_awaddr("M05_AXI_awaddr"), M05_AXI_awprot("M05_AXI_awprot"), M05_AXI_awvalid("M05_AXI_awvalid"), M05_AXI_awready("M05_AXI_awready"), M05_AXI_wdata("M05_AXI_wdata"), M05_AXI_wstrb("M05_AXI_wstrb"), M05_AXI_wvalid("M05_AXI_wvalid"), M05_AXI_wready("M05_AXI_wready"), M05_AXI_bresp("M05_AXI_bresp"), M05_AXI_bvalid("M05_AXI_bvalid"), M05_AXI_bready("M05_AXI_bready"), M05_AXI_araddr("M05_AXI_araddr"), M05_AXI_arprot("M05_AXI_arprot"), M05_AXI_arvalid("M05_AXI_arvalid"), M05_AXI_arready("M05_AXI_arready"), M05_AXI_rdata("M05_AXI_rdata"), M05_AXI_rresp("M05_AXI_rresp"), M05_AXI_rvalid("M05_AXI_rvalid"), M05_AXI_rready("M05_AXI_rready"), M06_AXI_awaddr("M06_AXI_awaddr"), M06_AXI_awprot("M06_AXI_awprot"), M06_AXI_awvalid("M06_AXI_awvalid"), M06_AXI_awready("M06_AXI_awready"), M06_AXI_wdata("M06_AXI_wdata"), M06_AXI_wstrb("M06_AXI_wstrb"), M06_AXI_wvalid("M06_AXI_wvalid"), M06_AXI_wready("M06_AXI_wready"), M06_AXI_bresp("M06_AXI_bresp"), M06_AXI_bvalid("M06_AXI_bvalid"), M06_AXI_bready("M06_AXI_bready"), M06_AXI_araddr("M06_AXI_araddr"), M06_AXI_arprot("M06_AXI_arprot"), M06_AXI_arvalid("M06_AXI_arvalid"), M06_AXI_arready("M06_AXI_arready"), M06_AXI_rdata("M06_AXI_rdata"), M06_AXI_rresp("M06_AXI_rresp"), M06_AXI_rvalid("M06_AXI_rvalid"), M06_AXI_rready("M06_AXI_rready"), M07_AXI_awaddr("M07_AXI_awaddr"), M07_AXI_awlen("M07_AXI_awlen"), M07_AXI_awsize("M07_AXI_awsize"), M07_AXI_awburst("M07_AXI_awburst"), M07_AXI_awlock("M07_AXI_awlock"), M07_AXI_awcache("M07_AXI_awcache"), M07_AXI_awprot("M07_AXI_awprot"), M07_AXI_awqos("M07_AXI_awqos"), M07_AXI_awuser("M07_AXI_awuser"), M07_AXI_awvalid("M07_AXI_awvalid"), M07_AXI_awready("M07_AXI_awready"), M07_AXI_wdata("M07_AXI_wdata"), M07_AXI_wstrb("M07_AXI_wstrb"), M07_AXI_wlast("M07_AXI_wlast"), M07_AXI_wvalid("M07_AXI_wvalid"), M07_AXI_wready("M07_AXI_wready"), M07_AXI_bresp("M07_AXI_bresp"), M07_AXI_bvalid("M07_AXI_bvalid"), M07_AXI_bready("M07_AXI_bready"), M07_AXI_araddr("M07_AXI_araddr"), M07_AXI_arlen("M07_AXI_arlen"), M07_AXI_arsize("M07_AXI_arsize"), M07_AXI_arburst("M07_AXI_arburst"), M07_AXI_arlock("M07_AXI_arlock"), M07_AXI_arcache("M07_AXI_arcache"), M07_AXI_arprot("M07_AXI_arprot"), M07_AXI_arqos("M07_AXI_arqos"), M07_AXI_aruser("M07_AXI_aruser"), M07_AXI_arvalid("M07_AXI_arvalid"), M07_AXI_arready("M07_AXI_arready"), M07_AXI_rdata("M07_AXI_rdata"), M07_AXI_rresp("M07_AXI_rresp"), M07_AXI_rlast("M07_AXI_rlast"), M07_AXI_rvalid("M07_AXI_rvalid"), M07_AXI_rready("M07_AXI_rready"), M08_AXI_awaddr("M08_AXI_awaddr"), M08_AXI_awprot("M08_AXI_awprot"), M08_AXI_awvalid("M08_AXI_awvalid"), M08_AXI_awready("M08_AXI_awready"), M08_AXI_wdata("M08_AXI_wdata"), M08_AXI_wstrb("M08_AXI_wstrb"), M08_AXI_wvalid("M08_AXI_wvalid"), M08_AXI_wready("M08_AXI_wready"), M08_AXI_bresp("M08_AXI_bresp"), M08_AXI_bvalid("M08_AXI_bvalid"), M08_AXI_bready("M08_AXI_bready"), M08_AXI_araddr("M08_AXI_araddr"), M08_AXI_arprot("M08_AXI_arprot"), M08_AXI_arvalid("M08_AXI_arvalid"), M08_AXI_arready("M08_AXI_arready"), M08_AXI_rdata("M08_AXI_rdata"), M08_AXI_rresp("M08_AXI_rresp"), M08_AXI_rvalid("M08_AXI_rvalid"), M08_AXI_rready("M08_AXI_rready"), M09_AXI_awaddr("M09_AXI_awaddr"), M09_AXI_awprot("M09_AXI_awprot"), M09_AXI_awvalid("M09_AXI_awvalid"), M09_AXI_awready("M09_AXI_awready"), M09_AXI_wdata("M09_AXI_wdata"), M09_AXI_wstrb("M09_AXI_wstrb"), M09_AXI_wvalid("M09_AXI_wvalid"), M09_AXI_wready("M09_AXI_wready"), M09_AXI_bresp("M09_AXI_bresp"), M09_AXI_bvalid("M09_AXI_bvalid"), M09_AXI_bready("M09_AXI_bready"), M09_AXI_araddr("M09_AXI_araddr"), M09_AXI_arprot("M09_AXI_arprot"), M09_AXI_arvalid("M09_AXI_arvalid"), M09_AXI_arready("M09_AXI_arready"), M09_AXI_rdata("M09_AXI_rdata"), M09_AXI_rresp("M09_AXI_rresp"), M09_AXI_rvalid("M09_AXI_rvalid"), M09_AXI_rready("M09_AXI_rready"), M10_AXI_awid("M10_AXI_awid"), M10_AXI_awaddr("M10_AXI_awaddr"), M10_AXI_awlen("M10_AXI_awlen"), M10_AXI_awsize("M10_AXI_awsize"), M10_AXI_awburst("M10_AXI_awburst"), M10_AXI_awlock("M10_AXI_awlock"), M10_AXI_awcache("M10_AXI_awcache"), M10_AXI_awprot("M10_AXI_awprot"), M10_AXI_awqos("M10_AXI_awqos"), M10_AXI_awuser("M10_AXI_awuser"), M10_AXI_awvalid("M10_AXI_awvalid"), M10_AXI_awready("M10_AXI_awready"), M10_AXI_wdata("M10_AXI_wdata"), M10_AXI_wstrb("M10_AXI_wstrb"), M10_AXI_wlast("M10_AXI_wlast"), M10_AXI_wuser("M10_AXI_wuser"), M10_AXI_wvalid("M10_AXI_wvalid"), M10_AXI_wready("M10_AXI_wready"), M10_AXI_bid("M10_AXI_bid"), M10_AXI_bresp("M10_AXI_bresp"), M10_AXI_buser("M10_AXI_buser"), M10_AXI_bvalid("M10_AXI_bvalid"), M10_AXI_bready("M10_AXI_bready"), M10_AXI_arid("M10_AXI_arid"), M10_AXI_araddr("M10_AXI_araddr"), M10_AXI_arlen("M10_AXI_arlen"), M10_AXI_arsize("M10_AXI_arsize"), M10_AXI_arburst("M10_AXI_arburst"), M10_AXI_arlock("M10_AXI_arlock"), M10_AXI_arcache("M10_AXI_arcache"), M10_AXI_arprot("M10_AXI_arprot"), M10_AXI_arqos("M10_AXI_arqos"), M10_AXI_aruser("M10_AXI_aruser"), M10_AXI_arvalid("M10_AXI_arvalid"), M10_AXI_arready("M10_AXI_arready"), M10_AXI_rid("M10_AXI_rid"), M10_AXI_rdata("M10_AXI_rdata"), M10_AXI_rresp("M10_AXI_rresp"), M10_AXI_rlast("M10_AXI_rlast"), M10_AXI_ruser("M10_AXI_ruser"), M10_AXI_rvalid("M10_AXI_rvalid"), M10_AXI_rready("M10_AXI_rready"), M11_AXI_awaddr("M11_AXI_awaddr"), M11_AXI_awprot("M11_AXI_awprot"), M11_AXI_awvalid("M11_AXI_awvalid"), M11_AXI_awready("M11_AXI_awready"), M11_AXI_wdata("M11_AXI_wdata"), M11_AXI_wstrb("M11_AXI_wstrb"), M11_AXI_wvalid("M11_AXI_wvalid"), M11_AXI_wready("M11_AXI_wready"), M11_AXI_bresp("M11_AXI_bresp"), M11_AXI_bvalid("M11_AXI_bvalid"), M11_AXI_bready("M11_AXI_bready"), M11_AXI_araddr("M11_AXI_araddr"), M11_AXI_arprot("M11_AXI_arprot"), M11_AXI_arvalid("M11_AXI_arvalid"), M11_AXI_arready("M11_AXI_arready"), M11_AXI_rdata("M11_AXI_rdata"), M11_AXI_rresp("M11_AXI_rresp"), M11_AXI_rvalid("M11_AXI_rvalid"), M11_AXI_rready("M11_AXI_rready"), M12_AXI_awaddr("M12_AXI_awaddr"), M12_AXI_awprot("M12_AXI_awprot"), M12_AXI_awvalid("M12_AXI_awvalid"), M12_AXI_awready("M12_AXI_awready"), M12_AXI_wdata("M12_AXI_wdata"), M12_AXI_wstrb("M12_AXI_wstrb"), M12_AXI_wvalid("M12_AXI_wvalid"), M12_AXI_wready("M12_AXI_wready"), M12_AXI_bresp("M12_AXI_bresp"), M12_AXI_bvalid("M12_AXI_bvalid"), M12_AXI_bready("M12_AXI_bready"), M12_AXI_araddr("M12_AXI_araddr"), M12_AXI_arprot("M12_AXI_arprot"), M12_AXI_arvalid("M12_AXI_arvalid"), M12_AXI_arready("M12_AXI_arready"), M12_AXI_rdata("M12_AXI_rdata"), M12_AXI_rresp("M12_AXI_rresp"), M12_AXI_rvalid("M12_AXI_rvalid"), M12_AXI_rready("M12_AXI_rready"), M13_AXI_awaddr("M13_AXI_awaddr"), M13_AXI_awprot("M13_AXI_awprot"), M13_AXI_awvalid("M13_AXI_awvalid"), M13_AXI_awready("M13_AXI_awready"), M13_AXI_wdata("M13_AXI_wdata"), M13_AXI_wstrb("M13_AXI_wstrb"), M13_AXI_wvalid("M13_AXI_wvalid"), M13_AXI_wready("M13_AXI_wready"), M13_AXI_bresp("M13_AXI_bresp"), M13_AXI_bvalid("M13_AXI_bvalid"), M13_AXI_bready("M13_AXI_bready"), M13_AXI_araddr("M13_AXI_araddr"), M13_AXI_arprot("M13_AXI_arprot"), M13_AXI_arvalid("M13_AXI_arvalid"), M13_AXI_arready("M13_AXI_arready"), M13_AXI_rdata("M13_AXI_rdata"), M13_AXI_rresp("M13_AXI_rresp"), M13_AXI_rvalid("M13_AXI_rvalid"), M13_AXI_rready("M13_AXI_rready"), M14_AXI_awaddr("M14_AXI_awaddr"), M14_AXI_awprot("M14_AXI_awprot"), M14_AXI_awvalid("M14_AXI_awvalid"), M14_AXI_awready("M14_AXI_awready"), M14_AXI_wdata("M14_AXI_wdata"), M14_AXI_wstrb("M14_AXI_wstrb"), M14_AXI_wvalid("M14_AXI_wvalid"), M14_AXI_wready("M14_AXI_wready"), M14_AXI_bresp("M14_AXI_bresp"), M14_AXI_bvalid("M14_AXI_bvalid"), M14_AXI_bready("M14_AXI_bready"), M14_AXI_araddr("M14_AXI_araddr"), M14_AXI_arprot("M14_AXI_arprot"), M14_AXI_arvalid("M14_AXI_arvalid"), M14_AXI_arready("M14_AXI_arready"), M14_AXI_rdata("M14_AXI_rdata"), M14_AXI_rresp("M14_AXI_rresp"), M14_AXI_rvalid("M14_AXI_rvalid"), M14_AXI_rready("M14_AXI_rready")
{
  // initialize pins
  mp_impl->aclk(aclk);
  mp_impl->aclk1(aclk1);
  mp_impl->aclk2(aclk2);
  mp_impl->aresetn(aresetn);

  // initialize transactors
  mp_S00_AXI_transactor = NULL;
  mp_S00_AXI_awlock_converter = NULL;
  mp_S00_AXI_arlock_converter = NULL;
  mp_M00_AXI_transactor = NULL;
  mp_M01_AXI_transactor = NULL;
  mp_M02_AXI_transactor = NULL;
  mp_M03_AXI_transactor = NULL;
  mp_M04_AXI_transactor = NULL;
  mp_M05_AXI_transactor = NULL;
  mp_M06_AXI_transactor = NULL;
  mp_M07_AXI_transactor = NULL;
  mp_M07_AXI_awlock_converter = NULL;
  mp_M07_AXI_arlock_converter = NULL;
  mp_M08_AXI_transactor = NULL;
  mp_M09_AXI_transactor = NULL;
  mp_M10_AXI_transactor = NULL;
  mp_M10_AXI_awlock_converter = NULL;
  mp_M10_AXI_arlock_converter = NULL;
  mp_M11_AXI_transactor = NULL;
  mp_M12_AXI_transactor = NULL;
  mp_M13_AXI_transactor = NULL;
  mp_M14_AXI_transactor = NULL;
  // Instantiate Socket Stubs

  // configure S00_AXI_transactor
    xsc::common_cpp::properties S00_AXI_transactor_param_props;
    S00_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    S00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S00_AXI_transactor_param_props.addLong("ID_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    S00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    S00_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    S00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    S00_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    S00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    S00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    S00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    S00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    S00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    S00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    S00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    S00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S00_AXI_transactor = new xtlm::xaximm_pin2xtlm_t<128,40,16,16,1,1,16,1>("S00_AXI_transactor", S00_AXI_transactor_param_props);
  mp_S00_AXI_transactor->AWID(S00_AXI_awid);
  mp_S00_AXI_transactor->AWADDR(S00_AXI_awaddr);
  mp_S00_AXI_transactor->AWLEN(S00_AXI_awlen);
  mp_S00_AXI_transactor->AWSIZE(S00_AXI_awsize);
  mp_S00_AXI_transactor->AWBURST(S00_AXI_awburst);
  mp_S00_AXI_awlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_awlock_converter");
  mp_S00_AXI_awlock_converter->vector_in(S00_AXI_awlock);
  mp_S00_AXI_awlock_converter->scalar_out(m_S00_AXI_awlock_converter_signal);
  mp_S00_AXI_transactor->AWLOCK(m_S00_AXI_awlock_converter_signal);
  mp_S00_AXI_transactor->AWCACHE(S00_AXI_awcache);
  mp_S00_AXI_transactor->AWPROT(S00_AXI_awprot);
  mp_S00_AXI_transactor->AWQOS(S00_AXI_awqos);
  mp_S00_AXI_transactor->AWUSER(S00_AXI_awuser);
  mp_S00_AXI_transactor->AWVALID(S00_AXI_awvalid);
  mp_S00_AXI_transactor->AWREADY(S00_AXI_awready);
  mp_S00_AXI_transactor->WDATA(S00_AXI_wdata);
  mp_S00_AXI_transactor->WSTRB(S00_AXI_wstrb);
  mp_S00_AXI_transactor->WLAST(S00_AXI_wlast);
  mp_S00_AXI_transactor->WVALID(S00_AXI_wvalid);
  mp_S00_AXI_transactor->WREADY(S00_AXI_wready);
  mp_S00_AXI_transactor->BID(S00_AXI_bid);
  mp_S00_AXI_transactor->BRESP(S00_AXI_bresp);
  mp_S00_AXI_transactor->BVALID(S00_AXI_bvalid);
  mp_S00_AXI_transactor->BREADY(S00_AXI_bready);
  mp_S00_AXI_transactor->ARID(S00_AXI_arid);
  mp_S00_AXI_transactor->ARADDR(S00_AXI_araddr);
  mp_S00_AXI_transactor->ARLEN(S00_AXI_arlen);
  mp_S00_AXI_transactor->ARSIZE(S00_AXI_arsize);
  mp_S00_AXI_transactor->ARBURST(S00_AXI_arburst);
  mp_S00_AXI_arlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_arlock_converter");
  mp_S00_AXI_arlock_converter->vector_in(S00_AXI_arlock);
  mp_S00_AXI_arlock_converter->scalar_out(m_S00_AXI_arlock_converter_signal);
  mp_S00_AXI_transactor->ARLOCK(m_S00_AXI_arlock_converter_signal);
  mp_S00_AXI_transactor->ARCACHE(S00_AXI_arcache);
  mp_S00_AXI_transactor->ARPROT(S00_AXI_arprot);
  mp_S00_AXI_transactor->ARQOS(S00_AXI_arqos);
  mp_S00_AXI_transactor->ARUSER(S00_AXI_aruser);
  mp_S00_AXI_transactor->ARVALID(S00_AXI_arvalid);
  mp_S00_AXI_transactor->ARREADY(S00_AXI_arready);
  mp_S00_AXI_transactor->RID(S00_AXI_rid);
  mp_S00_AXI_transactor->RDATA(S00_AXI_rdata);
  mp_S00_AXI_transactor->RRESP(S00_AXI_rresp);
  mp_S00_AXI_transactor->RLAST(S00_AXI_rlast);
  mp_S00_AXI_transactor->RVALID(S00_AXI_rvalid);
  mp_S00_AXI_transactor->RREADY(S00_AXI_rready);
  mp_S00_AXI_transactor->CLK(aclk);
  mp_S00_AXI_transactor->RST(aresetn);

  // configure M00_AXI_transactor
    xsc::common_cpp::properties M00_AXI_transactor_param_props;
    M00_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M00_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M00_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M00_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M00_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M00_AXI_transactor", M00_AXI_transactor_param_props);
  mp_M00_AXI_transactor->AWADDR(M00_AXI_awaddr);
  mp_M00_AXI_transactor->AWPROT(M00_AXI_awprot);
  mp_M00_AXI_transactor->AWVALID(M00_AXI_awvalid);
  mp_M00_AXI_transactor->AWREADY(M00_AXI_awready);
  mp_M00_AXI_transactor->WDATA(M00_AXI_wdata);
  mp_M00_AXI_transactor->WSTRB(M00_AXI_wstrb);
  mp_M00_AXI_transactor->WVALID(M00_AXI_wvalid);
  mp_M00_AXI_transactor->WREADY(M00_AXI_wready);
  mp_M00_AXI_transactor->BRESP(M00_AXI_bresp);
  mp_M00_AXI_transactor->BVALID(M00_AXI_bvalid);
  mp_M00_AXI_transactor->BREADY(M00_AXI_bready);
  mp_M00_AXI_transactor->ARADDR(M00_AXI_araddr);
  mp_M00_AXI_transactor->ARPROT(M00_AXI_arprot);
  mp_M00_AXI_transactor->ARVALID(M00_AXI_arvalid);
  mp_M00_AXI_transactor->ARREADY(M00_AXI_arready);
  mp_M00_AXI_transactor->RDATA(M00_AXI_rdata);
  mp_M00_AXI_transactor->RRESP(M00_AXI_rresp);
  mp_M00_AXI_transactor->RVALID(M00_AXI_rvalid);
  mp_M00_AXI_transactor->RREADY(M00_AXI_rready);
  mp_M00_AXI_transactor->CLK(aclk);
  mp_M00_AXI_transactor->RST(aresetn);

  // configure M01_AXI_transactor
    xsc::common_cpp::properties M01_AXI_transactor_param_props;
    M01_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M01_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M01_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M01_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M01_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M01_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M01_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M01_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M01_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M01_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M01_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M01_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M01_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M01_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M01_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M01_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M01_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M01_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M01_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M01_AXI_transactor", M01_AXI_transactor_param_props);
  mp_M01_AXI_transactor->AWADDR(M01_AXI_awaddr);
  mp_M01_AXI_transactor->AWPROT(M01_AXI_awprot);
  mp_M01_AXI_transactor->AWVALID(M01_AXI_awvalid);
  mp_M01_AXI_transactor->AWREADY(M01_AXI_awready);
  mp_M01_AXI_transactor->WDATA(M01_AXI_wdata);
  mp_M01_AXI_transactor->WSTRB(M01_AXI_wstrb);
  mp_M01_AXI_transactor->WVALID(M01_AXI_wvalid);
  mp_M01_AXI_transactor->WREADY(M01_AXI_wready);
  mp_M01_AXI_transactor->BRESP(M01_AXI_bresp);
  mp_M01_AXI_transactor->BVALID(M01_AXI_bvalid);
  mp_M01_AXI_transactor->BREADY(M01_AXI_bready);
  mp_M01_AXI_transactor->ARADDR(M01_AXI_araddr);
  mp_M01_AXI_transactor->ARPROT(M01_AXI_arprot);
  mp_M01_AXI_transactor->ARVALID(M01_AXI_arvalid);
  mp_M01_AXI_transactor->ARREADY(M01_AXI_arready);
  mp_M01_AXI_transactor->RDATA(M01_AXI_rdata);
  mp_M01_AXI_transactor->RRESP(M01_AXI_rresp);
  mp_M01_AXI_transactor->RVALID(M01_AXI_rvalid);
  mp_M01_AXI_transactor->RREADY(M01_AXI_rready);
  mp_M01_AXI_transactor->CLK(aclk);
  mp_M01_AXI_transactor->RST(aresetn);

  // configure M02_AXI_transactor
    xsc::common_cpp::properties M02_AXI_transactor_param_props;
    M02_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M02_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M02_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M02_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M02_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M02_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M02_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M02_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M02_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M02_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M02_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M02_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M02_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M02_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M02_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M02_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M02_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M02_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M02_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M02_AXI_transactor", M02_AXI_transactor_param_props);
  mp_M02_AXI_transactor->AWADDR(M02_AXI_awaddr);
  mp_M02_AXI_transactor->AWPROT(M02_AXI_awprot);
  mp_M02_AXI_transactor->AWVALID(M02_AXI_awvalid);
  mp_M02_AXI_transactor->AWREADY(M02_AXI_awready);
  mp_M02_AXI_transactor->WDATA(M02_AXI_wdata);
  mp_M02_AXI_transactor->WSTRB(M02_AXI_wstrb);
  mp_M02_AXI_transactor->WVALID(M02_AXI_wvalid);
  mp_M02_AXI_transactor->WREADY(M02_AXI_wready);
  mp_M02_AXI_transactor->BRESP(M02_AXI_bresp);
  mp_M02_AXI_transactor->BVALID(M02_AXI_bvalid);
  mp_M02_AXI_transactor->BREADY(M02_AXI_bready);
  mp_M02_AXI_transactor->ARADDR(M02_AXI_araddr);
  mp_M02_AXI_transactor->ARPROT(M02_AXI_arprot);
  mp_M02_AXI_transactor->ARVALID(M02_AXI_arvalid);
  mp_M02_AXI_transactor->ARREADY(M02_AXI_arready);
  mp_M02_AXI_transactor->RDATA(M02_AXI_rdata);
  mp_M02_AXI_transactor->RRESP(M02_AXI_rresp);
  mp_M02_AXI_transactor->RVALID(M02_AXI_rvalid);
  mp_M02_AXI_transactor->RREADY(M02_AXI_rready);
  mp_M02_AXI_transactor->CLK(aclk);
  mp_M02_AXI_transactor->RST(aresetn);

  // configure M03_AXI_transactor
    xsc::common_cpp::properties M03_AXI_transactor_param_props;
    M03_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M03_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M03_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M03_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M03_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M03_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M03_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M03_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M03_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M03_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M03_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M03_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M03_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M03_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M03_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M03_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M03_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M03_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M03_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M03_AXI_transactor", M03_AXI_transactor_param_props);
  mp_M03_AXI_transactor->AWADDR(M03_AXI_awaddr);
  mp_M03_AXI_transactor->AWPROT(M03_AXI_awprot);
  mp_M03_AXI_transactor->AWVALID(M03_AXI_awvalid);
  mp_M03_AXI_transactor->AWREADY(M03_AXI_awready);
  mp_M03_AXI_transactor->WDATA(M03_AXI_wdata);
  mp_M03_AXI_transactor->WSTRB(M03_AXI_wstrb);
  mp_M03_AXI_transactor->WVALID(M03_AXI_wvalid);
  mp_M03_AXI_transactor->WREADY(M03_AXI_wready);
  mp_M03_AXI_transactor->BRESP(M03_AXI_bresp);
  mp_M03_AXI_transactor->BVALID(M03_AXI_bvalid);
  mp_M03_AXI_transactor->BREADY(M03_AXI_bready);
  mp_M03_AXI_transactor->ARADDR(M03_AXI_araddr);
  mp_M03_AXI_transactor->ARPROT(M03_AXI_arprot);
  mp_M03_AXI_transactor->ARVALID(M03_AXI_arvalid);
  mp_M03_AXI_transactor->ARREADY(M03_AXI_arready);
  mp_M03_AXI_transactor->RDATA(M03_AXI_rdata);
  mp_M03_AXI_transactor->RRESP(M03_AXI_rresp);
  mp_M03_AXI_transactor->RVALID(M03_AXI_rvalid);
  mp_M03_AXI_transactor->RREADY(M03_AXI_rready);
  mp_M03_AXI_transactor->CLK(aclk);
  mp_M03_AXI_transactor->RST(aresetn);

  // configure M04_AXI_transactor
    xsc::common_cpp::properties M04_AXI_transactor_param_props;
    M04_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M04_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M04_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M04_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M04_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M04_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M04_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M04_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M04_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M04_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M04_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M04_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M04_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M04_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M04_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M04_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M04_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M04_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M04_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M04_AXI_transactor", M04_AXI_transactor_param_props);
  mp_M04_AXI_transactor->AWADDR(M04_AXI_awaddr);
  mp_M04_AXI_transactor->AWPROT(M04_AXI_awprot);
  mp_M04_AXI_transactor->AWVALID(M04_AXI_awvalid);
  mp_M04_AXI_transactor->AWREADY(M04_AXI_awready);
  mp_M04_AXI_transactor->WDATA(M04_AXI_wdata);
  mp_M04_AXI_transactor->WSTRB(M04_AXI_wstrb);
  mp_M04_AXI_transactor->WVALID(M04_AXI_wvalid);
  mp_M04_AXI_transactor->WREADY(M04_AXI_wready);
  mp_M04_AXI_transactor->BRESP(M04_AXI_bresp);
  mp_M04_AXI_transactor->BVALID(M04_AXI_bvalid);
  mp_M04_AXI_transactor->BREADY(M04_AXI_bready);
  mp_M04_AXI_transactor->ARADDR(M04_AXI_araddr);
  mp_M04_AXI_transactor->ARPROT(M04_AXI_arprot);
  mp_M04_AXI_transactor->ARVALID(M04_AXI_arvalid);
  mp_M04_AXI_transactor->ARREADY(M04_AXI_arready);
  mp_M04_AXI_transactor->RDATA(M04_AXI_rdata);
  mp_M04_AXI_transactor->RRESP(M04_AXI_rresp);
  mp_M04_AXI_transactor->RVALID(M04_AXI_rvalid);
  mp_M04_AXI_transactor->RREADY(M04_AXI_rready);
  mp_M04_AXI_transactor->CLK(aclk);
  mp_M04_AXI_transactor->RST(aresetn);

  // configure M05_AXI_transactor
    xsc::common_cpp::properties M05_AXI_transactor_param_props;
    M05_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M05_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M05_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M05_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M05_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M05_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M05_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M05_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M05_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M05_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M05_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M05_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M05_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M05_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M05_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M05_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M05_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M05_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M05_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M05_AXI_transactor", M05_AXI_transactor_param_props);
  mp_M05_AXI_transactor->AWADDR(M05_AXI_awaddr);
  mp_M05_AXI_transactor->AWPROT(M05_AXI_awprot);
  mp_M05_AXI_transactor->AWVALID(M05_AXI_awvalid);
  mp_M05_AXI_transactor->AWREADY(M05_AXI_awready);
  mp_M05_AXI_transactor->WDATA(M05_AXI_wdata);
  mp_M05_AXI_transactor->WSTRB(M05_AXI_wstrb);
  mp_M05_AXI_transactor->WVALID(M05_AXI_wvalid);
  mp_M05_AXI_transactor->WREADY(M05_AXI_wready);
  mp_M05_AXI_transactor->BRESP(M05_AXI_bresp);
  mp_M05_AXI_transactor->BVALID(M05_AXI_bvalid);
  mp_M05_AXI_transactor->BREADY(M05_AXI_bready);
  mp_M05_AXI_transactor->ARADDR(M05_AXI_araddr);
  mp_M05_AXI_transactor->ARPROT(M05_AXI_arprot);
  mp_M05_AXI_transactor->ARVALID(M05_AXI_arvalid);
  mp_M05_AXI_transactor->ARREADY(M05_AXI_arready);
  mp_M05_AXI_transactor->RDATA(M05_AXI_rdata);
  mp_M05_AXI_transactor->RRESP(M05_AXI_rresp);
  mp_M05_AXI_transactor->RVALID(M05_AXI_rvalid);
  mp_M05_AXI_transactor->RREADY(M05_AXI_rready);
  mp_M05_AXI_transactor->CLK(aclk);
  mp_M05_AXI_transactor->RST(aresetn);

  // configure M06_AXI_transactor
    xsc::common_cpp::properties M06_AXI_transactor_param_props;
    M06_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M06_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M06_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ADDR_WIDTH", "9");
    M06_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M06_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M06_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M06_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M06_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M06_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M06_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M06_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M06_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M06_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M06_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M06_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M06_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M06_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M06_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M06_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,9,1,1,1,1,1,1>("M06_AXI_transactor", M06_AXI_transactor_param_props);
  mp_M06_AXI_transactor->AWADDR(M06_AXI_awaddr);
  mp_M06_AXI_transactor->AWPROT(M06_AXI_awprot);
  mp_M06_AXI_transactor->AWVALID(M06_AXI_awvalid);
  mp_M06_AXI_transactor->AWREADY(M06_AXI_awready);
  mp_M06_AXI_transactor->WDATA(M06_AXI_wdata);
  mp_M06_AXI_transactor->WSTRB(M06_AXI_wstrb);
  mp_M06_AXI_transactor->WVALID(M06_AXI_wvalid);
  mp_M06_AXI_transactor->WREADY(M06_AXI_wready);
  mp_M06_AXI_transactor->BRESP(M06_AXI_bresp);
  mp_M06_AXI_transactor->BVALID(M06_AXI_bvalid);
  mp_M06_AXI_transactor->BREADY(M06_AXI_bready);
  mp_M06_AXI_transactor->ARADDR(M06_AXI_araddr);
  mp_M06_AXI_transactor->ARPROT(M06_AXI_arprot);
  mp_M06_AXI_transactor->ARVALID(M06_AXI_arvalid);
  mp_M06_AXI_transactor->ARREADY(M06_AXI_arready);
  mp_M06_AXI_transactor->RDATA(M06_AXI_rdata);
  mp_M06_AXI_transactor->RRESP(M06_AXI_rresp);
  mp_M06_AXI_transactor->RVALID(M06_AXI_rvalid);
  mp_M06_AXI_transactor->RREADY(M06_AXI_rready);
  mp_M06_AXI_transactor->CLK(aclk);
  mp_M06_AXI_transactor->RST(aresetn);

  // configure M07_AXI_transactor
    xsc::common_cpp::properties M07_AXI_transactor_param_props;
    M07_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M07_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M07_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M07_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M07_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M07_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M07_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M07_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M07_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M07_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M07_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M07_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M07_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M07_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M07_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M07_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M07_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,16,1,1,16,1>("M07_AXI_transactor", M07_AXI_transactor_param_props);
  mp_M07_AXI_transactor->AWADDR(M07_AXI_awaddr);
  mp_M07_AXI_transactor->AWLEN(M07_AXI_awlen);
  mp_M07_AXI_transactor->AWSIZE(M07_AXI_awsize);
  mp_M07_AXI_transactor->AWBURST(M07_AXI_awburst);
  mp_M07_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_awlock_converter");
  mp_M07_AXI_awlock_converter->scalar_in(m_M07_AXI_awlock_converter_signal);
  mp_M07_AXI_awlock_converter->vector_out(M07_AXI_awlock);
  mp_M07_AXI_transactor->AWLOCK(m_M07_AXI_awlock_converter_signal);
  mp_M07_AXI_transactor->AWCACHE(M07_AXI_awcache);
  mp_M07_AXI_transactor->AWPROT(M07_AXI_awprot);
  mp_M07_AXI_transactor->AWQOS(M07_AXI_awqos);
  mp_M07_AXI_transactor->AWUSER(M07_AXI_awuser);
  mp_M07_AXI_transactor->AWVALID(M07_AXI_awvalid);
  mp_M07_AXI_transactor->AWREADY(M07_AXI_awready);
  mp_M07_AXI_transactor->WDATA(M07_AXI_wdata);
  mp_M07_AXI_transactor->WSTRB(M07_AXI_wstrb);
  mp_M07_AXI_transactor->WLAST(M07_AXI_wlast);
  mp_M07_AXI_transactor->WVALID(M07_AXI_wvalid);
  mp_M07_AXI_transactor->WREADY(M07_AXI_wready);
  mp_M07_AXI_transactor->BRESP(M07_AXI_bresp);
  mp_M07_AXI_transactor->BVALID(M07_AXI_bvalid);
  mp_M07_AXI_transactor->BREADY(M07_AXI_bready);
  mp_M07_AXI_transactor->ARADDR(M07_AXI_araddr);
  mp_M07_AXI_transactor->ARLEN(M07_AXI_arlen);
  mp_M07_AXI_transactor->ARSIZE(M07_AXI_arsize);
  mp_M07_AXI_transactor->ARBURST(M07_AXI_arburst);
  mp_M07_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_arlock_converter");
  mp_M07_AXI_arlock_converter->scalar_in(m_M07_AXI_arlock_converter_signal);
  mp_M07_AXI_arlock_converter->vector_out(M07_AXI_arlock);
  mp_M07_AXI_transactor->ARLOCK(m_M07_AXI_arlock_converter_signal);
  mp_M07_AXI_transactor->ARCACHE(M07_AXI_arcache);
  mp_M07_AXI_transactor->ARPROT(M07_AXI_arprot);
  mp_M07_AXI_transactor->ARQOS(M07_AXI_arqos);
  mp_M07_AXI_transactor->ARUSER(M07_AXI_aruser);
  mp_M07_AXI_transactor->ARVALID(M07_AXI_arvalid);
  mp_M07_AXI_transactor->ARREADY(M07_AXI_arready);
  mp_M07_AXI_transactor->RDATA(M07_AXI_rdata);
  mp_M07_AXI_transactor->RRESP(M07_AXI_rresp);
  mp_M07_AXI_transactor->RLAST(M07_AXI_rlast);
  mp_M07_AXI_transactor->RVALID(M07_AXI_rvalid);
  mp_M07_AXI_transactor->RREADY(M07_AXI_rready);
  mp_M07_AXI_transactor->CLK(aclk);
  mp_M07_AXI_transactor->RST(aresetn);

  // configure M08_AXI_transactor
    xsc::common_cpp::properties M08_AXI_transactor_param_props;
    M08_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M08_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M08_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M08_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M08_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M08_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M08_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M08_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M08_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M08_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M08_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M08_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M08_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M08_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M08_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M08_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M08_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M08_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M08_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M08_AXI_transactor", M08_AXI_transactor_param_props);
  mp_M08_AXI_transactor->AWADDR(M08_AXI_awaddr);
  mp_M08_AXI_transactor->AWPROT(M08_AXI_awprot);
  mp_M08_AXI_transactor->AWVALID(M08_AXI_awvalid);
  mp_M08_AXI_transactor->AWREADY(M08_AXI_awready);
  mp_M08_AXI_transactor->WDATA(M08_AXI_wdata);
  mp_M08_AXI_transactor->WSTRB(M08_AXI_wstrb);
  mp_M08_AXI_transactor->WVALID(M08_AXI_wvalid);
  mp_M08_AXI_transactor->WREADY(M08_AXI_wready);
  mp_M08_AXI_transactor->BRESP(M08_AXI_bresp);
  mp_M08_AXI_transactor->BVALID(M08_AXI_bvalid);
  mp_M08_AXI_transactor->BREADY(M08_AXI_bready);
  mp_M08_AXI_transactor->ARADDR(M08_AXI_araddr);
  mp_M08_AXI_transactor->ARPROT(M08_AXI_arprot);
  mp_M08_AXI_transactor->ARVALID(M08_AXI_arvalid);
  mp_M08_AXI_transactor->ARREADY(M08_AXI_arready);
  mp_M08_AXI_transactor->RDATA(M08_AXI_rdata);
  mp_M08_AXI_transactor->RRESP(M08_AXI_rresp);
  mp_M08_AXI_transactor->RVALID(M08_AXI_rvalid);
  mp_M08_AXI_transactor->RREADY(M08_AXI_rready);
  mp_M08_AXI_transactor->CLK(aclk);
  mp_M08_AXI_transactor->RST(aresetn);

  // configure M09_AXI_transactor
    xsc::common_cpp::properties M09_AXI_transactor_param_props;
    M09_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M09_AXI_transactor_param_props.addLong("FREQ_HZ", "50000000");
    M09_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M09_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M09_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M09_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M09_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M09_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M09_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M09_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M09_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M09_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M09_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M09_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M09_AXI_transactor_param_props.addFloat("PHASE", "0.0");
    M09_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M09_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M09_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_clk_wiz_0_0_clk_50MHz");

    mp_M09_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M09_AXI_transactor", M09_AXI_transactor_param_props);
  mp_M09_AXI_transactor->AWADDR(M09_AXI_awaddr);
  mp_M09_AXI_transactor->AWPROT(M09_AXI_awprot);
  mp_M09_AXI_transactor->AWVALID(M09_AXI_awvalid);
  mp_M09_AXI_transactor->AWREADY(M09_AXI_awready);
  mp_M09_AXI_transactor->WDATA(M09_AXI_wdata);
  mp_M09_AXI_transactor->WSTRB(M09_AXI_wstrb);
  mp_M09_AXI_transactor->WVALID(M09_AXI_wvalid);
  mp_M09_AXI_transactor->WREADY(M09_AXI_wready);
  mp_M09_AXI_transactor->BRESP(M09_AXI_bresp);
  mp_M09_AXI_transactor->BVALID(M09_AXI_bvalid);
  mp_M09_AXI_transactor->BREADY(M09_AXI_bready);
  mp_M09_AXI_transactor->ARADDR(M09_AXI_araddr);
  mp_M09_AXI_transactor->ARPROT(M09_AXI_arprot);
  mp_M09_AXI_transactor->ARVALID(M09_AXI_arvalid);
  mp_M09_AXI_transactor->ARREADY(M09_AXI_arready);
  mp_M09_AXI_transactor->RDATA(M09_AXI_rdata);
  mp_M09_AXI_transactor->RRESP(M09_AXI_rresp);
  mp_M09_AXI_transactor->RVALID(M09_AXI_rvalid);
  mp_M09_AXI_transactor->RREADY(M09_AXI_rready);
  mp_M09_AXI_transactor->CLK(aclk2);
  mp_M09_AXI_transactor->RST(aresetn);

  // configure M10_AXI_transactor
    xsc::common_cpp::properties M10_AXI_transactor_param_props;
    M10_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    M10_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M10_AXI_transactor_param_props.addLong("ID_WIDTH", "3");
    M10_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M10_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("WUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("RUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("BUSER_WIDTH", "114");
    M10_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M10_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M10_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M10_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M10_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M10_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M10_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M10_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M10_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M10_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M10_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M10_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M10_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M10_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M10_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,3,130,14,114,130,14>("M10_AXI_transactor", M10_AXI_transactor_param_props);
  mp_M10_AXI_transactor->AWID(M10_AXI_awid);
  mp_M10_AXI_transactor->AWADDR(M10_AXI_awaddr);
  mp_M10_AXI_transactor->AWLEN(M10_AXI_awlen);
  mp_M10_AXI_transactor->AWSIZE(M10_AXI_awsize);
  mp_M10_AXI_transactor->AWBURST(M10_AXI_awburst);
  mp_M10_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_awlock_converter");
  mp_M10_AXI_awlock_converter->scalar_in(m_M10_AXI_awlock_converter_signal);
  mp_M10_AXI_awlock_converter->vector_out(M10_AXI_awlock);
  mp_M10_AXI_transactor->AWLOCK(m_M10_AXI_awlock_converter_signal);
  mp_M10_AXI_transactor->AWCACHE(M10_AXI_awcache);
  mp_M10_AXI_transactor->AWPROT(M10_AXI_awprot);
  mp_M10_AXI_transactor->AWQOS(M10_AXI_awqos);
  mp_M10_AXI_transactor->AWUSER(M10_AXI_awuser);
  mp_M10_AXI_transactor->AWVALID(M10_AXI_awvalid);
  mp_M10_AXI_transactor->AWREADY(M10_AXI_awready);
  mp_M10_AXI_transactor->WDATA(M10_AXI_wdata);
  mp_M10_AXI_transactor->WSTRB(M10_AXI_wstrb);
  mp_M10_AXI_transactor->WLAST(M10_AXI_wlast);
  mp_M10_AXI_transactor->WUSER(M10_AXI_wuser);
  mp_M10_AXI_transactor->WVALID(M10_AXI_wvalid);
  mp_M10_AXI_transactor->WREADY(M10_AXI_wready);
  mp_M10_AXI_transactor->BID(M10_AXI_bid);
  mp_M10_AXI_transactor->BRESP(M10_AXI_bresp);
  mp_M10_AXI_transactor->BUSER(M10_AXI_buser);
  mp_M10_AXI_transactor->BVALID(M10_AXI_bvalid);
  mp_M10_AXI_transactor->BREADY(M10_AXI_bready);
  mp_M10_AXI_transactor->ARID(M10_AXI_arid);
  mp_M10_AXI_transactor->ARADDR(M10_AXI_araddr);
  mp_M10_AXI_transactor->ARLEN(M10_AXI_arlen);
  mp_M10_AXI_transactor->ARSIZE(M10_AXI_arsize);
  mp_M10_AXI_transactor->ARBURST(M10_AXI_arburst);
  mp_M10_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_arlock_converter");
  mp_M10_AXI_arlock_converter->scalar_in(m_M10_AXI_arlock_converter_signal);
  mp_M10_AXI_arlock_converter->vector_out(M10_AXI_arlock);
  mp_M10_AXI_transactor->ARLOCK(m_M10_AXI_arlock_converter_signal);
  mp_M10_AXI_transactor->ARCACHE(M10_AXI_arcache);
  mp_M10_AXI_transactor->ARPROT(M10_AXI_arprot);
  mp_M10_AXI_transactor->ARQOS(M10_AXI_arqos);
  mp_M10_AXI_transactor->ARUSER(M10_AXI_aruser);
  mp_M10_AXI_transactor->ARVALID(M10_AXI_arvalid);
  mp_M10_AXI_transactor->ARREADY(M10_AXI_arready);
  mp_M10_AXI_transactor->RID(M10_AXI_rid);
  mp_M10_AXI_transactor->RDATA(M10_AXI_rdata);
  mp_M10_AXI_transactor->RRESP(M10_AXI_rresp);
  mp_M10_AXI_transactor->RLAST(M10_AXI_rlast);
  mp_M10_AXI_transactor->RUSER(M10_AXI_ruser);
  mp_M10_AXI_transactor->RVALID(M10_AXI_rvalid);
  mp_M10_AXI_transactor->RREADY(M10_AXI_rready);
  mp_M10_AXI_transactor->CLK(aclk);
  mp_M10_AXI_transactor->RST(aresetn);

  // configure M11_AXI_transactor
    xsc::common_cpp::properties M11_AXI_transactor_param_props;
    M11_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M11_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M11_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M11_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M11_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M11_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M11_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M11_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M11_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M11_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M11_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M11_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M11_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M11_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M11_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M11_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M11_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M11_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M11_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M11_AXI_transactor", M11_AXI_transactor_param_props);
  mp_M11_AXI_transactor->AWADDR(M11_AXI_awaddr);
  mp_M11_AXI_transactor->AWPROT(M11_AXI_awprot);
  mp_M11_AXI_transactor->AWVALID(M11_AXI_awvalid);
  mp_M11_AXI_transactor->AWREADY(M11_AXI_awready);
  mp_M11_AXI_transactor->WDATA(M11_AXI_wdata);
  mp_M11_AXI_transactor->WSTRB(M11_AXI_wstrb);
  mp_M11_AXI_transactor->WVALID(M11_AXI_wvalid);
  mp_M11_AXI_transactor->WREADY(M11_AXI_wready);
  mp_M11_AXI_transactor->BRESP(M11_AXI_bresp);
  mp_M11_AXI_transactor->BVALID(M11_AXI_bvalid);
  mp_M11_AXI_transactor->BREADY(M11_AXI_bready);
  mp_M11_AXI_transactor->ARADDR(M11_AXI_araddr);
  mp_M11_AXI_transactor->ARPROT(M11_AXI_arprot);
  mp_M11_AXI_transactor->ARVALID(M11_AXI_arvalid);
  mp_M11_AXI_transactor->ARREADY(M11_AXI_arready);
  mp_M11_AXI_transactor->RDATA(M11_AXI_rdata);
  mp_M11_AXI_transactor->RRESP(M11_AXI_rresp);
  mp_M11_AXI_transactor->RVALID(M11_AXI_rvalid);
  mp_M11_AXI_transactor->RREADY(M11_AXI_rready);
  mp_M11_AXI_transactor->CLK(aclk);
  mp_M11_AXI_transactor->RST(aresetn);

  // configure M12_AXI_transactor
    xsc::common_cpp::properties M12_AXI_transactor_param_props;
    M12_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M12_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M12_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M12_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M12_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M12_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M12_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M12_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M12_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M12_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M12_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M12_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M12_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M12_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M12_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M12_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M12_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M12_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M12_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M12_AXI_transactor", M12_AXI_transactor_param_props);
  mp_M12_AXI_transactor->AWADDR(M12_AXI_awaddr);
  mp_M12_AXI_transactor->AWPROT(M12_AXI_awprot);
  mp_M12_AXI_transactor->AWVALID(M12_AXI_awvalid);
  mp_M12_AXI_transactor->AWREADY(M12_AXI_awready);
  mp_M12_AXI_transactor->WDATA(M12_AXI_wdata);
  mp_M12_AXI_transactor->WSTRB(M12_AXI_wstrb);
  mp_M12_AXI_transactor->WVALID(M12_AXI_wvalid);
  mp_M12_AXI_transactor->WREADY(M12_AXI_wready);
  mp_M12_AXI_transactor->BRESP(M12_AXI_bresp);
  mp_M12_AXI_transactor->BVALID(M12_AXI_bvalid);
  mp_M12_AXI_transactor->BREADY(M12_AXI_bready);
  mp_M12_AXI_transactor->ARADDR(M12_AXI_araddr);
  mp_M12_AXI_transactor->ARPROT(M12_AXI_arprot);
  mp_M12_AXI_transactor->ARVALID(M12_AXI_arvalid);
  mp_M12_AXI_transactor->ARREADY(M12_AXI_arready);
  mp_M12_AXI_transactor->RDATA(M12_AXI_rdata);
  mp_M12_AXI_transactor->RRESP(M12_AXI_rresp);
  mp_M12_AXI_transactor->RVALID(M12_AXI_rvalid);
  mp_M12_AXI_transactor->RREADY(M12_AXI_rready);
  mp_M12_AXI_transactor->CLK(aclk);
  mp_M12_AXI_transactor->RST(aresetn);

  // configure M13_AXI_transactor
    xsc::common_cpp::properties M13_AXI_transactor_param_props;
    M13_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M13_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M13_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M13_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M13_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M13_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M13_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M13_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M13_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M13_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M13_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M13_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M13_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M13_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M13_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M13_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M13_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M13_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M13_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M13_AXI_transactor", M13_AXI_transactor_param_props);
  mp_M13_AXI_transactor->AWADDR(M13_AXI_awaddr);
  mp_M13_AXI_transactor->AWPROT(M13_AXI_awprot);
  mp_M13_AXI_transactor->AWVALID(M13_AXI_awvalid);
  mp_M13_AXI_transactor->AWREADY(M13_AXI_awready);
  mp_M13_AXI_transactor->WDATA(M13_AXI_wdata);
  mp_M13_AXI_transactor->WSTRB(M13_AXI_wstrb);
  mp_M13_AXI_transactor->WVALID(M13_AXI_wvalid);
  mp_M13_AXI_transactor->WREADY(M13_AXI_wready);
  mp_M13_AXI_transactor->BRESP(M13_AXI_bresp);
  mp_M13_AXI_transactor->BVALID(M13_AXI_bvalid);
  mp_M13_AXI_transactor->BREADY(M13_AXI_bready);
  mp_M13_AXI_transactor->ARADDR(M13_AXI_araddr);
  mp_M13_AXI_transactor->ARPROT(M13_AXI_arprot);
  mp_M13_AXI_transactor->ARVALID(M13_AXI_arvalid);
  mp_M13_AXI_transactor->ARREADY(M13_AXI_arready);
  mp_M13_AXI_transactor->RDATA(M13_AXI_rdata);
  mp_M13_AXI_transactor->RRESP(M13_AXI_rresp);
  mp_M13_AXI_transactor->RVALID(M13_AXI_rvalid);
  mp_M13_AXI_transactor->RREADY(M13_AXI_rready);
  mp_M13_AXI_transactor->CLK(aclk);
  mp_M13_AXI_transactor->RST(aresetn);

  // configure M14_AXI_transactor
    xsc::common_cpp::properties M14_AXI_transactor_param_props;
    M14_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M14_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M14_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M14_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M14_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M14_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M14_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M14_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M14_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M14_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M14_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M14_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M14_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M14_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M14_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M14_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M14_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M14_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M14_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M14_AXI_transactor", M14_AXI_transactor_param_props);
  mp_M14_AXI_transactor->AWADDR(M14_AXI_awaddr);
  mp_M14_AXI_transactor->AWPROT(M14_AXI_awprot);
  mp_M14_AXI_transactor->AWVALID(M14_AXI_awvalid);
  mp_M14_AXI_transactor->AWREADY(M14_AXI_awready);
  mp_M14_AXI_transactor->WDATA(M14_AXI_wdata);
  mp_M14_AXI_transactor->WSTRB(M14_AXI_wstrb);
  mp_M14_AXI_transactor->WVALID(M14_AXI_wvalid);
  mp_M14_AXI_transactor->WREADY(M14_AXI_wready);
  mp_M14_AXI_transactor->BRESP(M14_AXI_bresp);
  mp_M14_AXI_transactor->BVALID(M14_AXI_bvalid);
  mp_M14_AXI_transactor->BREADY(M14_AXI_bready);
  mp_M14_AXI_transactor->ARADDR(M14_AXI_araddr);
  mp_M14_AXI_transactor->ARPROT(M14_AXI_arprot);
  mp_M14_AXI_transactor->ARVALID(M14_AXI_arvalid);
  mp_M14_AXI_transactor->ARREADY(M14_AXI_arready);
  mp_M14_AXI_transactor->RDATA(M14_AXI_rdata);
  mp_M14_AXI_transactor->RRESP(M14_AXI_rresp);
  mp_M14_AXI_transactor->RVALID(M14_AXI_rvalid);
  mp_M14_AXI_transactor->RREADY(M14_AXI_rready);
  mp_M14_AXI_transactor->CLK(aclk);
  mp_M14_AXI_transactor->RST(aresetn);


  // initialize transactors stubs
  S00_AXI_transactor_target_wr_socket_stub = nullptr;
  S00_AXI_transactor_target_rd_socket_stub = nullptr;
  M00_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M00_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M01_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M01_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M02_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M02_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M03_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M03_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M04_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M04_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M05_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M05_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M06_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M06_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M07_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M07_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M08_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M08_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M09_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M09_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M10_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M10_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M11_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M11_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M12_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M12_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M13_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M13_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M14_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M14_AXI_transactor_initiator_rd_socket_stub = nullptr;

}

void zusys_smartconnect_0_0::before_end_of_elaboration()
{
  // configure 'S00_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "S00_AXI_TLM_MODE") != 1)
  {
    mp_impl->S00_AXI_tlm_aximm_read_socket->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_impl->S00_AXI_tlm_aximm_write_socket->bind(*(mp_S00_AXI_transactor->wr_socket));
  }
  else
  {
    S00_AXI_transactor_target_wr_socket_stub = new xtlm::xtlm_aximm_target_stub("wr_socket",0);
    S00_AXI_transactor_target_wr_socket_stub->bind(*(mp_S00_AXI_transactor->wr_socket));
    S00_AXI_transactor_target_rd_socket_stub = new xtlm::xtlm_aximm_target_stub("rd_socket",0);
    S00_AXI_transactor_target_rd_socket_stub->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_S00_AXI_transactor->disable_transactor();
  }

  // configure 'M00_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M00_AXI_TLM_MODE") != 1)
  {
    mp_impl->M00_AXI_tlm_aximm_read_socket->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_impl->M00_AXI_tlm_aximm_write_socket->bind(*(mp_M00_AXI_transactor->wr_socket));
  }
  else
  {
    M00_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M00_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M00_AXI_transactor->wr_socket));
    M00_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M00_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_M00_AXI_transactor->disable_transactor();
  }

  // configure 'M01_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M01_AXI_TLM_MODE") != 1)
  {
    mp_impl->M01_AXI_tlm_aximm_read_socket->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_impl->M01_AXI_tlm_aximm_write_socket->bind(*(mp_M01_AXI_transactor->wr_socket));
  }
  else
  {
    M01_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M01_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M01_AXI_transactor->wr_socket));
    M01_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M01_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_M01_AXI_transactor->disable_transactor();
  }

  // configure 'M02_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M02_AXI_TLM_MODE") != 1)
  {
    mp_impl->M02_AXI_tlm_aximm_read_socket->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_impl->M02_AXI_tlm_aximm_write_socket->bind(*(mp_M02_AXI_transactor->wr_socket));
  }
  else
  {
    M02_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M02_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M02_AXI_transactor->wr_socket));
    M02_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M02_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_M02_AXI_transactor->disable_transactor();
  }

  // configure 'M03_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M03_AXI_TLM_MODE") != 1)
  {
    mp_impl->M03_AXI_tlm_aximm_read_socket->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_impl->M03_AXI_tlm_aximm_write_socket->bind(*(mp_M03_AXI_transactor->wr_socket));
  }
  else
  {
    M03_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M03_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M03_AXI_transactor->wr_socket));
    M03_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M03_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_M03_AXI_transactor->disable_transactor();
  }

  // configure 'M04_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M04_AXI_TLM_MODE") != 1)
  {
    mp_impl->M04_AXI_tlm_aximm_read_socket->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_impl->M04_AXI_tlm_aximm_write_socket->bind(*(mp_M04_AXI_transactor->wr_socket));
  }
  else
  {
    M04_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M04_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M04_AXI_transactor->wr_socket));
    M04_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M04_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_M04_AXI_transactor->disable_transactor();
  }

  // configure 'M05_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M05_AXI_TLM_MODE") != 1)
  {
    mp_impl->M05_AXI_tlm_aximm_read_socket->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_impl->M05_AXI_tlm_aximm_write_socket->bind(*(mp_M05_AXI_transactor->wr_socket));
  }
  else
  {
    M05_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M05_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M05_AXI_transactor->wr_socket));
    M05_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M05_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_M05_AXI_transactor->disable_transactor();
  }

  // configure 'M06_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M06_AXI_TLM_MODE") != 1)
  {
    mp_impl->M06_AXI_tlm_aximm_read_socket->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_impl->M06_AXI_tlm_aximm_write_socket->bind(*(mp_M06_AXI_transactor->wr_socket));
  }
  else
  {
    M06_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M06_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M06_AXI_transactor->wr_socket));
    M06_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M06_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_M06_AXI_transactor->disable_transactor();
  }

  // configure 'M07_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M07_AXI_TLM_MODE") != 1)
  {
    mp_impl->M07_AXI_tlm_aximm_read_socket->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_impl->M07_AXI_tlm_aximm_write_socket->bind(*(mp_M07_AXI_transactor->wr_socket));
  }
  else
  {
    M07_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M07_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M07_AXI_transactor->wr_socket));
    M07_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M07_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_M07_AXI_transactor->disable_transactor();
  }

  // configure 'M08_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M08_AXI_TLM_MODE") != 1)
  {
    mp_impl->M08_AXI_tlm_aximm_read_socket->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_impl->M08_AXI_tlm_aximm_write_socket->bind(*(mp_M08_AXI_transactor->wr_socket));
  }
  else
  {
    M08_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M08_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M08_AXI_transactor->wr_socket));
    M08_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M08_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_M08_AXI_transactor->disable_transactor();
  }

  // configure 'M09_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M09_AXI_TLM_MODE") != 1)
  {
    mp_impl->M09_AXI_tlm_aximm_read_socket->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_impl->M09_AXI_tlm_aximm_write_socket->bind(*(mp_M09_AXI_transactor->wr_socket));
  }
  else
  {
    M09_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M09_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M09_AXI_transactor->wr_socket));
    M09_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M09_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_M09_AXI_transactor->disable_transactor();
  }

  // configure 'M10_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M10_AXI_TLM_MODE") != 1)
  {
    mp_impl->M10_AXI_tlm_aximm_read_socket->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_impl->M10_AXI_tlm_aximm_write_socket->bind(*(mp_M10_AXI_transactor->wr_socket));
  }
  else
  {
    M10_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M10_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M10_AXI_transactor->wr_socket));
    M10_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M10_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_M10_AXI_transactor->disable_transactor();
  }

  // configure 'M11_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M11_AXI_TLM_MODE") != 1)
  {
    mp_impl->M11_AXI_tlm_aximm_read_socket->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_impl->M11_AXI_tlm_aximm_write_socket->bind(*(mp_M11_AXI_transactor->wr_socket));
  }
  else
  {
    M11_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M11_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M11_AXI_transactor->wr_socket));
    M11_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M11_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_M11_AXI_transactor->disable_transactor();
  }

  // configure 'M12_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M12_AXI_TLM_MODE") != 1)
  {
    mp_impl->M12_AXI_tlm_aximm_read_socket->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_impl->M12_AXI_tlm_aximm_write_socket->bind(*(mp_M12_AXI_transactor->wr_socket));
  }
  else
  {
    M12_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M12_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M12_AXI_transactor->wr_socket));
    M12_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M12_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_M12_AXI_transactor->disable_transactor();
  }

  // configure 'M13_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M13_AXI_TLM_MODE") != 1)
  {
    mp_impl->M13_AXI_tlm_aximm_read_socket->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_impl->M13_AXI_tlm_aximm_write_socket->bind(*(mp_M13_AXI_transactor->wr_socket));
  }
  else
  {
    M13_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M13_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M13_AXI_transactor->wr_socket));
    M13_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M13_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_M13_AXI_transactor->disable_transactor();
  }

  // configure 'M14_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M14_AXI_TLM_MODE") != 1)
  {
    mp_impl->M14_AXI_tlm_aximm_read_socket->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_impl->M14_AXI_tlm_aximm_write_socket->bind(*(mp_M14_AXI_transactor->wr_socket));
  }
  else
  {
    M14_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M14_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M14_AXI_transactor->wr_socket));
    M14_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M14_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_M14_AXI_transactor->disable_transactor();
  }

}

#endif // VCSSYSTEMC




#ifdef MTI_SYSTEMC
zusys_smartconnect_0_0::zusys_smartconnect_0_0(const sc_core::sc_module_name& nm) : zusys_smartconnect_0_0_sc(nm),  aclk("aclk"), aclk1("aclk1"), aclk2("aclk2"), aresetn("aresetn"), S00_AXI_awid("S00_AXI_awid"), S00_AXI_awaddr("S00_AXI_awaddr"), S00_AXI_awlen("S00_AXI_awlen"), S00_AXI_awsize("S00_AXI_awsize"), S00_AXI_awburst("S00_AXI_awburst"), S00_AXI_awlock("S00_AXI_awlock"), S00_AXI_awcache("S00_AXI_awcache"), S00_AXI_awprot("S00_AXI_awprot"), S00_AXI_awqos("S00_AXI_awqos"), S00_AXI_awuser("S00_AXI_awuser"), S00_AXI_awvalid("S00_AXI_awvalid"), S00_AXI_awready("S00_AXI_awready"), S00_AXI_wdata("S00_AXI_wdata"), S00_AXI_wstrb("S00_AXI_wstrb"), S00_AXI_wlast("S00_AXI_wlast"), S00_AXI_wvalid("S00_AXI_wvalid"), S00_AXI_wready("S00_AXI_wready"), S00_AXI_bid("S00_AXI_bid"), S00_AXI_bresp("S00_AXI_bresp"), S00_AXI_bvalid("S00_AXI_bvalid"), S00_AXI_bready("S00_AXI_bready"), S00_AXI_arid("S00_AXI_arid"), S00_AXI_araddr("S00_AXI_araddr"), S00_AXI_arlen("S00_AXI_arlen"), S00_AXI_arsize("S00_AXI_arsize"), S00_AXI_arburst("S00_AXI_arburst"), S00_AXI_arlock("S00_AXI_arlock"), S00_AXI_arcache("S00_AXI_arcache"), S00_AXI_arprot("S00_AXI_arprot"), S00_AXI_arqos("S00_AXI_arqos"), S00_AXI_aruser("S00_AXI_aruser"), S00_AXI_arvalid("S00_AXI_arvalid"), S00_AXI_arready("S00_AXI_arready"), S00_AXI_rid("S00_AXI_rid"), S00_AXI_rdata("S00_AXI_rdata"), S00_AXI_rresp("S00_AXI_rresp"), S00_AXI_rlast("S00_AXI_rlast"), S00_AXI_rvalid("S00_AXI_rvalid"), S00_AXI_rready("S00_AXI_rready"), M00_AXI_awaddr("M00_AXI_awaddr"), M00_AXI_awprot("M00_AXI_awprot"), M00_AXI_awvalid("M00_AXI_awvalid"), M00_AXI_awready("M00_AXI_awready"), M00_AXI_wdata("M00_AXI_wdata"), M00_AXI_wstrb("M00_AXI_wstrb"), M00_AXI_wvalid("M00_AXI_wvalid"), M00_AXI_wready("M00_AXI_wready"), M00_AXI_bresp("M00_AXI_bresp"), M00_AXI_bvalid("M00_AXI_bvalid"), M00_AXI_bready("M00_AXI_bready"), M00_AXI_araddr("M00_AXI_araddr"), M00_AXI_arprot("M00_AXI_arprot"), M00_AXI_arvalid("M00_AXI_arvalid"), M00_AXI_arready("M00_AXI_arready"), M00_AXI_rdata("M00_AXI_rdata"), M00_AXI_rresp("M00_AXI_rresp"), M00_AXI_rvalid("M00_AXI_rvalid"), M00_AXI_rready("M00_AXI_rready"), M01_AXI_awaddr("M01_AXI_awaddr"), M01_AXI_awprot("M01_AXI_awprot"), M01_AXI_awvalid("M01_AXI_awvalid"), M01_AXI_awready("M01_AXI_awready"), M01_AXI_wdata("M01_AXI_wdata"), M01_AXI_wstrb("M01_AXI_wstrb"), M01_AXI_wvalid("M01_AXI_wvalid"), M01_AXI_wready("M01_AXI_wready"), M01_AXI_bresp("M01_AXI_bresp"), M01_AXI_bvalid("M01_AXI_bvalid"), M01_AXI_bready("M01_AXI_bready"), M01_AXI_araddr("M01_AXI_araddr"), M01_AXI_arprot("M01_AXI_arprot"), M01_AXI_arvalid("M01_AXI_arvalid"), M01_AXI_arready("M01_AXI_arready"), M01_AXI_rdata("M01_AXI_rdata"), M01_AXI_rresp("M01_AXI_rresp"), M01_AXI_rvalid("M01_AXI_rvalid"), M01_AXI_rready("M01_AXI_rready"), M02_AXI_awaddr("M02_AXI_awaddr"), M02_AXI_awprot("M02_AXI_awprot"), M02_AXI_awvalid("M02_AXI_awvalid"), M02_AXI_awready("M02_AXI_awready"), M02_AXI_wdata("M02_AXI_wdata"), M02_AXI_wstrb("M02_AXI_wstrb"), M02_AXI_wvalid("M02_AXI_wvalid"), M02_AXI_wready("M02_AXI_wready"), M02_AXI_bresp("M02_AXI_bresp"), M02_AXI_bvalid("M02_AXI_bvalid"), M02_AXI_bready("M02_AXI_bready"), M02_AXI_araddr("M02_AXI_araddr"), M02_AXI_arprot("M02_AXI_arprot"), M02_AXI_arvalid("M02_AXI_arvalid"), M02_AXI_arready("M02_AXI_arready"), M02_AXI_rdata("M02_AXI_rdata"), M02_AXI_rresp("M02_AXI_rresp"), M02_AXI_rvalid("M02_AXI_rvalid"), M02_AXI_rready("M02_AXI_rready"), M03_AXI_awaddr("M03_AXI_awaddr"), M03_AXI_awprot("M03_AXI_awprot"), M03_AXI_awvalid("M03_AXI_awvalid"), M03_AXI_awready("M03_AXI_awready"), M03_AXI_wdata("M03_AXI_wdata"), M03_AXI_wstrb("M03_AXI_wstrb"), M03_AXI_wvalid("M03_AXI_wvalid"), M03_AXI_wready("M03_AXI_wready"), M03_AXI_bresp("M03_AXI_bresp"), M03_AXI_bvalid("M03_AXI_bvalid"), M03_AXI_bready("M03_AXI_bready"), M03_AXI_araddr("M03_AXI_araddr"), M03_AXI_arprot("M03_AXI_arprot"), M03_AXI_arvalid("M03_AXI_arvalid"), M03_AXI_arready("M03_AXI_arready"), M03_AXI_rdata("M03_AXI_rdata"), M03_AXI_rresp("M03_AXI_rresp"), M03_AXI_rvalid("M03_AXI_rvalid"), M03_AXI_rready("M03_AXI_rready"), M04_AXI_awaddr("M04_AXI_awaddr"), M04_AXI_awprot("M04_AXI_awprot"), M04_AXI_awvalid("M04_AXI_awvalid"), M04_AXI_awready("M04_AXI_awready"), M04_AXI_wdata("M04_AXI_wdata"), M04_AXI_wstrb("M04_AXI_wstrb"), M04_AXI_wvalid("M04_AXI_wvalid"), M04_AXI_wready("M04_AXI_wready"), M04_AXI_bresp("M04_AXI_bresp"), M04_AXI_bvalid("M04_AXI_bvalid"), M04_AXI_bready("M04_AXI_bready"), M04_AXI_araddr("M04_AXI_araddr"), M04_AXI_arprot("M04_AXI_arprot"), M04_AXI_arvalid("M04_AXI_arvalid"), M04_AXI_arready("M04_AXI_arready"), M04_AXI_rdata("M04_AXI_rdata"), M04_AXI_rresp("M04_AXI_rresp"), M04_AXI_rvalid("M04_AXI_rvalid"), M04_AXI_rready("M04_AXI_rready"), M05_AXI_awaddr("M05_AXI_awaddr"), M05_AXI_awprot("M05_AXI_awprot"), M05_AXI_awvalid("M05_AXI_awvalid"), M05_AXI_awready("M05_AXI_awready"), M05_AXI_wdata("M05_AXI_wdata"), M05_AXI_wstrb("M05_AXI_wstrb"), M05_AXI_wvalid("M05_AXI_wvalid"), M05_AXI_wready("M05_AXI_wready"), M05_AXI_bresp("M05_AXI_bresp"), M05_AXI_bvalid("M05_AXI_bvalid"), M05_AXI_bready("M05_AXI_bready"), M05_AXI_araddr("M05_AXI_araddr"), M05_AXI_arprot("M05_AXI_arprot"), M05_AXI_arvalid("M05_AXI_arvalid"), M05_AXI_arready("M05_AXI_arready"), M05_AXI_rdata("M05_AXI_rdata"), M05_AXI_rresp("M05_AXI_rresp"), M05_AXI_rvalid("M05_AXI_rvalid"), M05_AXI_rready("M05_AXI_rready"), M06_AXI_awaddr("M06_AXI_awaddr"), M06_AXI_awprot("M06_AXI_awprot"), M06_AXI_awvalid("M06_AXI_awvalid"), M06_AXI_awready("M06_AXI_awready"), M06_AXI_wdata("M06_AXI_wdata"), M06_AXI_wstrb("M06_AXI_wstrb"), M06_AXI_wvalid("M06_AXI_wvalid"), M06_AXI_wready("M06_AXI_wready"), M06_AXI_bresp("M06_AXI_bresp"), M06_AXI_bvalid("M06_AXI_bvalid"), M06_AXI_bready("M06_AXI_bready"), M06_AXI_araddr("M06_AXI_araddr"), M06_AXI_arprot("M06_AXI_arprot"), M06_AXI_arvalid("M06_AXI_arvalid"), M06_AXI_arready("M06_AXI_arready"), M06_AXI_rdata("M06_AXI_rdata"), M06_AXI_rresp("M06_AXI_rresp"), M06_AXI_rvalid("M06_AXI_rvalid"), M06_AXI_rready("M06_AXI_rready"), M07_AXI_awaddr("M07_AXI_awaddr"), M07_AXI_awlen("M07_AXI_awlen"), M07_AXI_awsize("M07_AXI_awsize"), M07_AXI_awburst("M07_AXI_awburst"), M07_AXI_awlock("M07_AXI_awlock"), M07_AXI_awcache("M07_AXI_awcache"), M07_AXI_awprot("M07_AXI_awprot"), M07_AXI_awqos("M07_AXI_awqos"), M07_AXI_awuser("M07_AXI_awuser"), M07_AXI_awvalid("M07_AXI_awvalid"), M07_AXI_awready("M07_AXI_awready"), M07_AXI_wdata("M07_AXI_wdata"), M07_AXI_wstrb("M07_AXI_wstrb"), M07_AXI_wlast("M07_AXI_wlast"), M07_AXI_wvalid("M07_AXI_wvalid"), M07_AXI_wready("M07_AXI_wready"), M07_AXI_bresp("M07_AXI_bresp"), M07_AXI_bvalid("M07_AXI_bvalid"), M07_AXI_bready("M07_AXI_bready"), M07_AXI_araddr("M07_AXI_araddr"), M07_AXI_arlen("M07_AXI_arlen"), M07_AXI_arsize("M07_AXI_arsize"), M07_AXI_arburst("M07_AXI_arburst"), M07_AXI_arlock("M07_AXI_arlock"), M07_AXI_arcache("M07_AXI_arcache"), M07_AXI_arprot("M07_AXI_arprot"), M07_AXI_arqos("M07_AXI_arqos"), M07_AXI_aruser("M07_AXI_aruser"), M07_AXI_arvalid("M07_AXI_arvalid"), M07_AXI_arready("M07_AXI_arready"), M07_AXI_rdata("M07_AXI_rdata"), M07_AXI_rresp("M07_AXI_rresp"), M07_AXI_rlast("M07_AXI_rlast"), M07_AXI_rvalid("M07_AXI_rvalid"), M07_AXI_rready("M07_AXI_rready"), M08_AXI_awaddr("M08_AXI_awaddr"), M08_AXI_awprot("M08_AXI_awprot"), M08_AXI_awvalid("M08_AXI_awvalid"), M08_AXI_awready("M08_AXI_awready"), M08_AXI_wdata("M08_AXI_wdata"), M08_AXI_wstrb("M08_AXI_wstrb"), M08_AXI_wvalid("M08_AXI_wvalid"), M08_AXI_wready("M08_AXI_wready"), M08_AXI_bresp("M08_AXI_bresp"), M08_AXI_bvalid("M08_AXI_bvalid"), M08_AXI_bready("M08_AXI_bready"), M08_AXI_araddr("M08_AXI_araddr"), M08_AXI_arprot("M08_AXI_arprot"), M08_AXI_arvalid("M08_AXI_arvalid"), M08_AXI_arready("M08_AXI_arready"), M08_AXI_rdata("M08_AXI_rdata"), M08_AXI_rresp("M08_AXI_rresp"), M08_AXI_rvalid("M08_AXI_rvalid"), M08_AXI_rready("M08_AXI_rready"), M09_AXI_awaddr("M09_AXI_awaddr"), M09_AXI_awprot("M09_AXI_awprot"), M09_AXI_awvalid("M09_AXI_awvalid"), M09_AXI_awready("M09_AXI_awready"), M09_AXI_wdata("M09_AXI_wdata"), M09_AXI_wstrb("M09_AXI_wstrb"), M09_AXI_wvalid("M09_AXI_wvalid"), M09_AXI_wready("M09_AXI_wready"), M09_AXI_bresp("M09_AXI_bresp"), M09_AXI_bvalid("M09_AXI_bvalid"), M09_AXI_bready("M09_AXI_bready"), M09_AXI_araddr("M09_AXI_araddr"), M09_AXI_arprot("M09_AXI_arprot"), M09_AXI_arvalid("M09_AXI_arvalid"), M09_AXI_arready("M09_AXI_arready"), M09_AXI_rdata("M09_AXI_rdata"), M09_AXI_rresp("M09_AXI_rresp"), M09_AXI_rvalid("M09_AXI_rvalid"), M09_AXI_rready("M09_AXI_rready"), M10_AXI_awid("M10_AXI_awid"), M10_AXI_awaddr("M10_AXI_awaddr"), M10_AXI_awlen("M10_AXI_awlen"), M10_AXI_awsize("M10_AXI_awsize"), M10_AXI_awburst("M10_AXI_awburst"), M10_AXI_awlock("M10_AXI_awlock"), M10_AXI_awcache("M10_AXI_awcache"), M10_AXI_awprot("M10_AXI_awprot"), M10_AXI_awqos("M10_AXI_awqos"), M10_AXI_awuser("M10_AXI_awuser"), M10_AXI_awvalid("M10_AXI_awvalid"), M10_AXI_awready("M10_AXI_awready"), M10_AXI_wdata("M10_AXI_wdata"), M10_AXI_wstrb("M10_AXI_wstrb"), M10_AXI_wlast("M10_AXI_wlast"), M10_AXI_wuser("M10_AXI_wuser"), M10_AXI_wvalid("M10_AXI_wvalid"), M10_AXI_wready("M10_AXI_wready"), M10_AXI_bid("M10_AXI_bid"), M10_AXI_bresp("M10_AXI_bresp"), M10_AXI_buser("M10_AXI_buser"), M10_AXI_bvalid("M10_AXI_bvalid"), M10_AXI_bready("M10_AXI_bready"), M10_AXI_arid("M10_AXI_arid"), M10_AXI_araddr("M10_AXI_araddr"), M10_AXI_arlen("M10_AXI_arlen"), M10_AXI_arsize("M10_AXI_arsize"), M10_AXI_arburst("M10_AXI_arburst"), M10_AXI_arlock("M10_AXI_arlock"), M10_AXI_arcache("M10_AXI_arcache"), M10_AXI_arprot("M10_AXI_arprot"), M10_AXI_arqos("M10_AXI_arqos"), M10_AXI_aruser("M10_AXI_aruser"), M10_AXI_arvalid("M10_AXI_arvalid"), M10_AXI_arready("M10_AXI_arready"), M10_AXI_rid("M10_AXI_rid"), M10_AXI_rdata("M10_AXI_rdata"), M10_AXI_rresp("M10_AXI_rresp"), M10_AXI_rlast("M10_AXI_rlast"), M10_AXI_ruser("M10_AXI_ruser"), M10_AXI_rvalid("M10_AXI_rvalid"), M10_AXI_rready("M10_AXI_rready"), M11_AXI_awaddr("M11_AXI_awaddr"), M11_AXI_awprot("M11_AXI_awprot"), M11_AXI_awvalid("M11_AXI_awvalid"), M11_AXI_awready("M11_AXI_awready"), M11_AXI_wdata("M11_AXI_wdata"), M11_AXI_wstrb("M11_AXI_wstrb"), M11_AXI_wvalid("M11_AXI_wvalid"), M11_AXI_wready("M11_AXI_wready"), M11_AXI_bresp("M11_AXI_bresp"), M11_AXI_bvalid("M11_AXI_bvalid"), M11_AXI_bready("M11_AXI_bready"), M11_AXI_araddr("M11_AXI_araddr"), M11_AXI_arprot("M11_AXI_arprot"), M11_AXI_arvalid("M11_AXI_arvalid"), M11_AXI_arready("M11_AXI_arready"), M11_AXI_rdata("M11_AXI_rdata"), M11_AXI_rresp("M11_AXI_rresp"), M11_AXI_rvalid("M11_AXI_rvalid"), M11_AXI_rready("M11_AXI_rready"), M12_AXI_awaddr("M12_AXI_awaddr"), M12_AXI_awprot("M12_AXI_awprot"), M12_AXI_awvalid("M12_AXI_awvalid"), M12_AXI_awready("M12_AXI_awready"), M12_AXI_wdata("M12_AXI_wdata"), M12_AXI_wstrb("M12_AXI_wstrb"), M12_AXI_wvalid("M12_AXI_wvalid"), M12_AXI_wready("M12_AXI_wready"), M12_AXI_bresp("M12_AXI_bresp"), M12_AXI_bvalid("M12_AXI_bvalid"), M12_AXI_bready("M12_AXI_bready"), M12_AXI_araddr("M12_AXI_araddr"), M12_AXI_arprot("M12_AXI_arprot"), M12_AXI_arvalid("M12_AXI_arvalid"), M12_AXI_arready("M12_AXI_arready"), M12_AXI_rdata("M12_AXI_rdata"), M12_AXI_rresp("M12_AXI_rresp"), M12_AXI_rvalid("M12_AXI_rvalid"), M12_AXI_rready("M12_AXI_rready"), M13_AXI_awaddr("M13_AXI_awaddr"), M13_AXI_awprot("M13_AXI_awprot"), M13_AXI_awvalid("M13_AXI_awvalid"), M13_AXI_awready("M13_AXI_awready"), M13_AXI_wdata("M13_AXI_wdata"), M13_AXI_wstrb("M13_AXI_wstrb"), M13_AXI_wvalid("M13_AXI_wvalid"), M13_AXI_wready("M13_AXI_wready"), M13_AXI_bresp("M13_AXI_bresp"), M13_AXI_bvalid("M13_AXI_bvalid"), M13_AXI_bready("M13_AXI_bready"), M13_AXI_araddr("M13_AXI_araddr"), M13_AXI_arprot("M13_AXI_arprot"), M13_AXI_arvalid("M13_AXI_arvalid"), M13_AXI_arready("M13_AXI_arready"), M13_AXI_rdata("M13_AXI_rdata"), M13_AXI_rresp("M13_AXI_rresp"), M13_AXI_rvalid("M13_AXI_rvalid"), M13_AXI_rready("M13_AXI_rready"), M14_AXI_awaddr("M14_AXI_awaddr"), M14_AXI_awprot("M14_AXI_awprot"), M14_AXI_awvalid("M14_AXI_awvalid"), M14_AXI_awready("M14_AXI_awready"), M14_AXI_wdata("M14_AXI_wdata"), M14_AXI_wstrb("M14_AXI_wstrb"), M14_AXI_wvalid("M14_AXI_wvalid"), M14_AXI_wready("M14_AXI_wready"), M14_AXI_bresp("M14_AXI_bresp"), M14_AXI_bvalid("M14_AXI_bvalid"), M14_AXI_bready("M14_AXI_bready"), M14_AXI_araddr("M14_AXI_araddr"), M14_AXI_arprot("M14_AXI_arprot"), M14_AXI_arvalid("M14_AXI_arvalid"), M14_AXI_arready("M14_AXI_arready"), M14_AXI_rdata("M14_AXI_rdata"), M14_AXI_rresp("M14_AXI_rresp"), M14_AXI_rvalid("M14_AXI_rvalid"), M14_AXI_rready("M14_AXI_rready")
{
  // initialize pins
  mp_impl->aclk(aclk);
  mp_impl->aclk1(aclk1);
  mp_impl->aclk2(aclk2);
  mp_impl->aresetn(aresetn);

  // initialize transactors
  mp_S00_AXI_transactor = NULL;
  mp_S00_AXI_awlock_converter = NULL;
  mp_S00_AXI_arlock_converter = NULL;
  mp_M00_AXI_transactor = NULL;
  mp_M01_AXI_transactor = NULL;
  mp_M02_AXI_transactor = NULL;
  mp_M03_AXI_transactor = NULL;
  mp_M04_AXI_transactor = NULL;
  mp_M05_AXI_transactor = NULL;
  mp_M06_AXI_transactor = NULL;
  mp_M07_AXI_transactor = NULL;
  mp_M07_AXI_awlock_converter = NULL;
  mp_M07_AXI_arlock_converter = NULL;
  mp_M08_AXI_transactor = NULL;
  mp_M09_AXI_transactor = NULL;
  mp_M10_AXI_transactor = NULL;
  mp_M10_AXI_awlock_converter = NULL;
  mp_M10_AXI_arlock_converter = NULL;
  mp_M11_AXI_transactor = NULL;
  mp_M12_AXI_transactor = NULL;
  mp_M13_AXI_transactor = NULL;
  mp_M14_AXI_transactor = NULL;
  // Instantiate Socket Stubs

  // configure S00_AXI_transactor
    xsc::common_cpp::properties S00_AXI_transactor_param_props;
    S00_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    S00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S00_AXI_transactor_param_props.addLong("ID_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    S00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    S00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S00_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    S00_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    S00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    S00_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    S00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    S00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    S00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    S00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    S00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    S00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    S00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S00_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    S00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    S00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    S00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    S00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S00_AXI_transactor = new xtlm::xaximm_pin2xtlm_t<128,40,16,16,1,1,16,1>("S00_AXI_transactor", S00_AXI_transactor_param_props);
  mp_S00_AXI_transactor->AWID(S00_AXI_awid);
  mp_S00_AXI_transactor->AWADDR(S00_AXI_awaddr);
  mp_S00_AXI_transactor->AWLEN(S00_AXI_awlen);
  mp_S00_AXI_transactor->AWSIZE(S00_AXI_awsize);
  mp_S00_AXI_transactor->AWBURST(S00_AXI_awburst);
  mp_S00_AXI_awlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_awlock_converter");
  mp_S00_AXI_awlock_converter->vector_in(S00_AXI_awlock);
  mp_S00_AXI_awlock_converter->scalar_out(m_S00_AXI_awlock_converter_signal);
  mp_S00_AXI_transactor->AWLOCK(m_S00_AXI_awlock_converter_signal);
  mp_S00_AXI_transactor->AWCACHE(S00_AXI_awcache);
  mp_S00_AXI_transactor->AWPROT(S00_AXI_awprot);
  mp_S00_AXI_transactor->AWQOS(S00_AXI_awqos);
  mp_S00_AXI_transactor->AWUSER(S00_AXI_awuser);
  mp_S00_AXI_transactor->AWVALID(S00_AXI_awvalid);
  mp_S00_AXI_transactor->AWREADY(S00_AXI_awready);
  mp_S00_AXI_transactor->WDATA(S00_AXI_wdata);
  mp_S00_AXI_transactor->WSTRB(S00_AXI_wstrb);
  mp_S00_AXI_transactor->WLAST(S00_AXI_wlast);
  mp_S00_AXI_transactor->WVALID(S00_AXI_wvalid);
  mp_S00_AXI_transactor->WREADY(S00_AXI_wready);
  mp_S00_AXI_transactor->BID(S00_AXI_bid);
  mp_S00_AXI_transactor->BRESP(S00_AXI_bresp);
  mp_S00_AXI_transactor->BVALID(S00_AXI_bvalid);
  mp_S00_AXI_transactor->BREADY(S00_AXI_bready);
  mp_S00_AXI_transactor->ARID(S00_AXI_arid);
  mp_S00_AXI_transactor->ARADDR(S00_AXI_araddr);
  mp_S00_AXI_transactor->ARLEN(S00_AXI_arlen);
  mp_S00_AXI_transactor->ARSIZE(S00_AXI_arsize);
  mp_S00_AXI_transactor->ARBURST(S00_AXI_arburst);
  mp_S00_AXI_arlock_converter = new xsc::common::vectorN2scalar_converter<1>("S00_AXI_arlock_converter");
  mp_S00_AXI_arlock_converter->vector_in(S00_AXI_arlock);
  mp_S00_AXI_arlock_converter->scalar_out(m_S00_AXI_arlock_converter_signal);
  mp_S00_AXI_transactor->ARLOCK(m_S00_AXI_arlock_converter_signal);
  mp_S00_AXI_transactor->ARCACHE(S00_AXI_arcache);
  mp_S00_AXI_transactor->ARPROT(S00_AXI_arprot);
  mp_S00_AXI_transactor->ARQOS(S00_AXI_arqos);
  mp_S00_AXI_transactor->ARUSER(S00_AXI_aruser);
  mp_S00_AXI_transactor->ARVALID(S00_AXI_arvalid);
  mp_S00_AXI_transactor->ARREADY(S00_AXI_arready);
  mp_S00_AXI_transactor->RID(S00_AXI_rid);
  mp_S00_AXI_transactor->RDATA(S00_AXI_rdata);
  mp_S00_AXI_transactor->RRESP(S00_AXI_rresp);
  mp_S00_AXI_transactor->RLAST(S00_AXI_rlast);
  mp_S00_AXI_transactor->RVALID(S00_AXI_rvalid);
  mp_S00_AXI_transactor->RREADY(S00_AXI_rready);
  mp_S00_AXI_transactor->CLK(aclk);
  mp_S00_AXI_transactor->RST(aresetn);

  // configure M00_AXI_transactor
    xsc::common_cpp::properties M00_AXI_transactor_param_props;
    M00_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M00_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M00_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M00_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M00_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M00_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M00_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M00_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M00_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M00_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M00_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M00_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M00_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M00_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M00_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M00_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M00_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M00_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M00_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M00_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M00_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M00_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M00_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M00_AXI_transactor", M00_AXI_transactor_param_props);
  mp_M00_AXI_transactor->AWADDR(M00_AXI_awaddr);
  mp_M00_AXI_transactor->AWPROT(M00_AXI_awprot);
  mp_M00_AXI_transactor->AWVALID(M00_AXI_awvalid);
  mp_M00_AXI_transactor->AWREADY(M00_AXI_awready);
  mp_M00_AXI_transactor->WDATA(M00_AXI_wdata);
  mp_M00_AXI_transactor->WSTRB(M00_AXI_wstrb);
  mp_M00_AXI_transactor->WVALID(M00_AXI_wvalid);
  mp_M00_AXI_transactor->WREADY(M00_AXI_wready);
  mp_M00_AXI_transactor->BRESP(M00_AXI_bresp);
  mp_M00_AXI_transactor->BVALID(M00_AXI_bvalid);
  mp_M00_AXI_transactor->BREADY(M00_AXI_bready);
  mp_M00_AXI_transactor->ARADDR(M00_AXI_araddr);
  mp_M00_AXI_transactor->ARPROT(M00_AXI_arprot);
  mp_M00_AXI_transactor->ARVALID(M00_AXI_arvalid);
  mp_M00_AXI_transactor->ARREADY(M00_AXI_arready);
  mp_M00_AXI_transactor->RDATA(M00_AXI_rdata);
  mp_M00_AXI_transactor->RRESP(M00_AXI_rresp);
  mp_M00_AXI_transactor->RVALID(M00_AXI_rvalid);
  mp_M00_AXI_transactor->RREADY(M00_AXI_rready);
  mp_M00_AXI_transactor->CLK(aclk);
  mp_M00_AXI_transactor->RST(aresetn);

  // configure M01_AXI_transactor
    xsc::common_cpp::properties M01_AXI_transactor_param_props;
    M01_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M01_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M01_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M01_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M01_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M01_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M01_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M01_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M01_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M01_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M01_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M01_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M01_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M01_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M01_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M01_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M01_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M01_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M01_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M01_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M01_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M01_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M01_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M01_AXI_transactor", M01_AXI_transactor_param_props);
  mp_M01_AXI_transactor->AWADDR(M01_AXI_awaddr);
  mp_M01_AXI_transactor->AWPROT(M01_AXI_awprot);
  mp_M01_AXI_transactor->AWVALID(M01_AXI_awvalid);
  mp_M01_AXI_transactor->AWREADY(M01_AXI_awready);
  mp_M01_AXI_transactor->WDATA(M01_AXI_wdata);
  mp_M01_AXI_transactor->WSTRB(M01_AXI_wstrb);
  mp_M01_AXI_transactor->WVALID(M01_AXI_wvalid);
  mp_M01_AXI_transactor->WREADY(M01_AXI_wready);
  mp_M01_AXI_transactor->BRESP(M01_AXI_bresp);
  mp_M01_AXI_transactor->BVALID(M01_AXI_bvalid);
  mp_M01_AXI_transactor->BREADY(M01_AXI_bready);
  mp_M01_AXI_transactor->ARADDR(M01_AXI_araddr);
  mp_M01_AXI_transactor->ARPROT(M01_AXI_arprot);
  mp_M01_AXI_transactor->ARVALID(M01_AXI_arvalid);
  mp_M01_AXI_transactor->ARREADY(M01_AXI_arready);
  mp_M01_AXI_transactor->RDATA(M01_AXI_rdata);
  mp_M01_AXI_transactor->RRESP(M01_AXI_rresp);
  mp_M01_AXI_transactor->RVALID(M01_AXI_rvalid);
  mp_M01_AXI_transactor->RREADY(M01_AXI_rready);
  mp_M01_AXI_transactor->CLK(aclk);
  mp_M01_AXI_transactor->RST(aresetn);

  // configure M02_AXI_transactor
    xsc::common_cpp::properties M02_AXI_transactor_param_props;
    M02_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M02_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M02_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ADDR_WIDTH", "6");
    M02_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M02_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M02_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M02_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M02_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M02_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M02_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M02_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M02_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M02_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M02_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M02_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M02_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M02_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M02_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M02_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M02_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M02_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M02_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M02_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,6,1,1,1,1,1,1>("M02_AXI_transactor", M02_AXI_transactor_param_props);
  mp_M02_AXI_transactor->AWADDR(M02_AXI_awaddr);
  mp_M02_AXI_transactor->AWPROT(M02_AXI_awprot);
  mp_M02_AXI_transactor->AWVALID(M02_AXI_awvalid);
  mp_M02_AXI_transactor->AWREADY(M02_AXI_awready);
  mp_M02_AXI_transactor->WDATA(M02_AXI_wdata);
  mp_M02_AXI_transactor->WSTRB(M02_AXI_wstrb);
  mp_M02_AXI_transactor->WVALID(M02_AXI_wvalid);
  mp_M02_AXI_transactor->WREADY(M02_AXI_wready);
  mp_M02_AXI_transactor->BRESP(M02_AXI_bresp);
  mp_M02_AXI_transactor->BVALID(M02_AXI_bvalid);
  mp_M02_AXI_transactor->BREADY(M02_AXI_bready);
  mp_M02_AXI_transactor->ARADDR(M02_AXI_araddr);
  mp_M02_AXI_transactor->ARPROT(M02_AXI_arprot);
  mp_M02_AXI_transactor->ARVALID(M02_AXI_arvalid);
  mp_M02_AXI_transactor->ARREADY(M02_AXI_arready);
  mp_M02_AXI_transactor->RDATA(M02_AXI_rdata);
  mp_M02_AXI_transactor->RRESP(M02_AXI_rresp);
  mp_M02_AXI_transactor->RVALID(M02_AXI_rvalid);
  mp_M02_AXI_transactor->RREADY(M02_AXI_rready);
  mp_M02_AXI_transactor->CLK(aclk);
  mp_M02_AXI_transactor->RST(aresetn);

  // configure M03_AXI_transactor
    xsc::common_cpp::properties M03_AXI_transactor_param_props;
    M03_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M03_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M03_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M03_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M03_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M03_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M03_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M03_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M03_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M03_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M03_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M03_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M03_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M03_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M03_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M03_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M03_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M03_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M03_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M03_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M03_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M03_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M03_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M03_AXI_transactor", M03_AXI_transactor_param_props);
  mp_M03_AXI_transactor->AWADDR(M03_AXI_awaddr);
  mp_M03_AXI_transactor->AWPROT(M03_AXI_awprot);
  mp_M03_AXI_transactor->AWVALID(M03_AXI_awvalid);
  mp_M03_AXI_transactor->AWREADY(M03_AXI_awready);
  mp_M03_AXI_transactor->WDATA(M03_AXI_wdata);
  mp_M03_AXI_transactor->WSTRB(M03_AXI_wstrb);
  mp_M03_AXI_transactor->WVALID(M03_AXI_wvalid);
  mp_M03_AXI_transactor->WREADY(M03_AXI_wready);
  mp_M03_AXI_transactor->BRESP(M03_AXI_bresp);
  mp_M03_AXI_transactor->BVALID(M03_AXI_bvalid);
  mp_M03_AXI_transactor->BREADY(M03_AXI_bready);
  mp_M03_AXI_transactor->ARADDR(M03_AXI_araddr);
  mp_M03_AXI_transactor->ARPROT(M03_AXI_arprot);
  mp_M03_AXI_transactor->ARVALID(M03_AXI_arvalid);
  mp_M03_AXI_transactor->ARREADY(M03_AXI_arready);
  mp_M03_AXI_transactor->RDATA(M03_AXI_rdata);
  mp_M03_AXI_transactor->RRESP(M03_AXI_rresp);
  mp_M03_AXI_transactor->RVALID(M03_AXI_rvalid);
  mp_M03_AXI_transactor->RREADY(M03_AXI_rready);
  mp_M03_AXI_transactor->CLK(aclk);
  mp_M03_AXI_transactor->RST(aresetn);

  // configure M04_AXI_transactor
    xsc::common_cpp::properties M04_AXI_transactor_param_props;
    M04_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M04_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M04_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M04_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M04_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M04_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M04_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M04_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M04_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M04_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M04_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M04_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M04_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M04_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M04_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M04_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M04_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M04_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M04_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M04_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M04_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M04_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M04_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M04_AXI_transactor", M04_AXI_transactor_param_props);
  mp_M04_AXI_transactor->AWADDR(M04_AXI_awaddr);
  mp_M04_AXI_transactor->AWPROT(M04_AXI_awprot);
  mp_M04_AXI_transactor->AWVALID(M04_AXI_awvalid);
  mp_M04_AXI_transactor->AWREADY(M04_AXI_awready);
  mp_M04_AXI_transactor->WDATA(M04_AXI_wdata);
  mp_M04_AXI_transactor->WSTRB(M04_AXI_wstrb);
  mp_M04_AXI_transactor->WVALID(M04_AXI_wvalid);
  mp_M04_AXI_transactor->WREADY(M04_AXI_wready);
  mp_M04_AXI_transactor->BRESP(M04_AXI_bresp);
  mp_M04_AXI_transactor->BVALID(M04_AXI_bvalid);
  mp_M04_AXI_transactor->BREADY(M04_AXI_bready);
  mp_M04_AXI_transactor->ARADDR(M04_AXI_araddr);
  mp_M04_AXI_transactor->ARPROT(M04_AXI_arprot);
  mp_M04_AXI_transactor->ARVALID(M04_AXI_arvalid);
  mp_M04_AXI_transactor->ARREADY(M04_AXI_arready);
  mp_M04_AXI_transactor->RDATA(M04_AXI_rdata);
  mp_M04_AXI_transactor->RRESP(M04_AXI_rresp);
  mp_M04_AXI_transactor->RVALID(M04_AXI_rvalid);
  mp_M04_AXI_transactor->RREADY(M04_AXI_rready);
  mp_M04_AXI_transactor->CLK(aclk);
  mp_M04_AXI_transactor->RST(aresetn);

  // configure M05_AXI_transactor
    xsc::common_cpp::properties M05_AXI_transactor_param_props;
    M05_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M05_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M05_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M05_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M05_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M05_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M05_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M05_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M05_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M05_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M05_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M05_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M05_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M05_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M05_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M05_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M05_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M05_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M05_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M05_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M05_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M05_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M05_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M05_AXI_transactor", M05_AXI_transactor_param_props);
  mp_M05_AXI_transactor->AWADDR(M05_AXI_awaddr);
  mp_M05_AXI_transactor->AWPROT(M05_AXI_awprot);
  mp_M05_AXI_transactor->AWVALID(M05_AXI_awvalid);
  mp_M05_AXI_transactor->AWREADY(M05_AXI_awready);
  mp_M05_AXI_transactor->WDATA(M05_AXI_wdata);
  mp_M05_AXI_transactor->WSTRB(M05_AXI_wstrb);
  mp_M05_AXI_transactor->WVALID(M05_AXI_wvalid);
  mp_M05_AXI_transactor->WREADY(M05_AXI_wready);
  mp_M05_AXI_transactor->BRESP(M05_AXI_bresp);
  mp_M05_AXI_transactor->BVALID(M05_AXI_bvalid);
  mp_M05_AXI_transactor->BREADY(M05_AXI_bready);
  mp_M05_AXI_transactor->ARADDR(M05_AXI_araddr);
  mp_M05_AXI_transactor->ARPROT(M05_AXI_arprot);
  mp_M05_AXI_transactor->ARVALID(M05_AXI_arvalid);
  mp_M05_AXI_transactor->ARREADY(M05_AXI_arready);
  mp_M05_AXI_transactor->RDATA(M05_AXI_rdata);
  mp_M05_AXI_transactor->RRESP(M05_AXI_rresp);
  mp_M05_AXI_transactor->RVALID(M05_AXI_rvalid);
  mp_M05_AXI_transactor->RREADY(M05_AXI_rready);
  mp_M05_AXI_transactor->CLK(aclk);
  mp_M05_AXI_transactor->RST(aresetn);

  // configure M06_AXI_transactor
    xsc::common_cpp::properties M06_AXI_transactor_param_props;
    M06_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M06_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M06_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ADDR_WIDTH", "9");
    M06_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M06_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M06_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M06_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M06_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M06_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M06_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M06_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M06_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M06_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M06_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M06_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M06_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M06_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M06_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M06_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M06_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M06_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M06_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M06_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,9,1,1,1,1,1,1>("M06_AXI_transactor", M06_AXI_transactor_param_props);
  mp_M06_AXI_transactor->AWADDR(M06_AXI_awaddr);
  mp_M06_AXI_transactor->AWPROT(M06_AXI_awprot);
  mp_M06_AXI_transactor->AWVALID(M06_AXI_awvalid);
  mp_M06_AXI_transactor->AWREADY(M06_AXI_awready);
  mp_M06_AXI_transactor->WDATA(M06_AXI_wdata);
  mp_M06_AXI_transactor->WSTRB(M06_AXI_wstrb);
  mp_M06_AXI_transactor->WVALID(M06_AXI_wvalid);
  mp_M06_AXI_transactor->WREADY(M06_AXI_wready);
  mp_M06_AXI_transactor->BRESP(M06_AXI_bresp);
  mp_M06_AXI_transactor->BVALID(M06_AXI_bvalid);
  mp_M06_AXI_transactor->BREADY(M06_AXI_bready);
  mp_M06_AXI_transactor->ARADDR(M06_AXI_araddr);
  mp_M06_AXI_transactor->ARPROT(M06_AXI_arprot);
  mp_M06_AXI_transactor->ARVALID(M06_AXI_arvalid);
  mp_M06_AXI_transactor->ARREADY(M06_AXI_arready);
  mp_M06_AXI_transactor->RDATA(M06_AXI_rdata);
  mp_M06_AXI_transactor->RRESP(M06_AXI_rresp);
  mp_M06_AXI_transactor->RVALID(M06_AXI_rvalid);
  mp_M06_AXI_transactor->RREADY(M06_AXI_rready);
  mp_M06_AXI_transactor->CLK(aclk);
  mp_M06_AXI_transactor->RST(aresetn);

  // configure M07_AXI_transactor
    xsc::common_cpp::properties M07_AXI_transactor_param_props;
    M07_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M07_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M07_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M07_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M07_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M07_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M07_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M07_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M07_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M07_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M07_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M07_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M07_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M07_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M07_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M07_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M07_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M07_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M07_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M07_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M07_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M07_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M07_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,16,1,1,16,1>("M07_AXI_transactor", M07_AXI_transactor_param_props);
  mp_M07_AXI_transactor->AWADDR(M07_AXI_awaddr);
  mp_M07_AXI_transactor->AWLEN(M07_AXI_awlen);
  mp_M07_AXI_transactor->AWSIZE(M07_AXI_awsize);
  mp_M07_AXI_transactor->AWBURST(M07_AXI_awburst);
  mp_M07_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_awlock_converter");
  mp_M07_AXI_awlock_converter->scalar_in(m_M07_AXI_awlock_converter_signal);
  mp_M07_AXI_awlock_converter->vector_out(M07_AXI_awlock);
  mp_M07_AXI_transactor->AWLOCK(m_M07_AXI_awlock_converter_signal);
  mp_M07_AXI_transactor->AWCACHE(M07_AXI_awcache);
  mp_M07_AXI_transactor->AWPROT(M07_AXI_awprot);
  mp_M07_AXI_transactor->AWQOS(M07_AXI_awqos);
  mp_M07_AXI_transactor->AWUSER(M07_AXI_awuser);
  mp_M07_AXI_transactor->AWVALID(M07_AXI_awvalid);
  mp_M07_AXI_transactor->AWREADY(M07_AXI_awready);
  mp_M07_AXI_transactor->WDATA(M07_AXI_wdata);
  mp_M07_AXI_transactor->WSTRB(M07_AXI_wstrb);
  mp_M07_AXI_transactor->WLAST(M07_AXI_wlast);
  mp_M07_AXI_transactor->WVALID(M07_AXI_wvalid);
  mp_M07_AXI_transactor->WREADY(M07_AXI_wready);
  mp_M07_AXI_transactor->BRESP(M07_AXI_bresp);
  mp_M07_AXI_transactor->BVALID(M07_AXI_bvalid);
  mp_M07_AXI_transactor->BREADY(M07_AXI_bready);
  mp_M07_AXI_transactor->ARADDR(M07_AXI_araddr);
  mp_M07_AXI_transactor->ARLEN(M07_AXI_arlen);
  mp_M07_AXI_transactor->ARSIZE(M07_AXI_arsize);
  mp_M07_AXI_transactor->ARBURST(M07_AXI_arburst);
  mp_M07_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M07_AXI_arlock_converter");
  mp_M07_AXI_arlock_converter->scalar_in(m_M07_AXI_arlock_converter_signal);
  mp_M07_AXI_arlock_converter->vector_out(M07_AXI_arlock);
  mp_M07_AXI_transactor->ARLOCK(m_M07_AXI_arlock_converter_signal);
  mp_M07_AXI_transactor->ARCACHE(M07_AXI_arcache);
  mp_M07_AXI_transactor->ARPROT(M07_AXI_arprot);
  mp_M07_AXI_transactor->ARQOS(M07_AXI_arqos);
  mp_M07_AXI_transactor->ARUSER(M07_AXI_aruser);
  mp_M07_AXI_transactor->ARVALID(M07_AXI_arvalid);
  mp_M07_AXI_transactor->ARREADY(M07_AXI_arready);
  mp_M07_AXI_transactor->RDATA(M07_AXI_rdata);
  mp_M07_AXI_transactor->RRESP(M07_AXI_rresp);
  mp_M07_AXI_transactor->RLAST(M07_AXI_rlast);
  mp_M07_AXI_transactor->RVALID(M07_AXI_rvalid);
  mp_M07_AXI_transactor->RREADY(M07_AXI_rready);
  mp_M07_AXI_transactor->CLK(aclk);
  mp_M07_AXI_transactor->RST(aresetn);

  // configure M08_AXI_transactor
    xsc::common_cpp::properties M08_AXI_transactor_param_props;
    M08_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M08_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M08_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M08_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M08_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M08_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M08_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M08_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M08_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M08_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M08_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M08_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M08_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M08_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M08_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M08_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M08_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M08_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M08_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M08_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M08_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M08_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M08_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M08_AXI_transactor", M08_AXI_transactor_param_props);
  mp_M08_AXI_transactor->AWADDR(M08_AXI_awaddr);
  mp_M08_AXI_transactor->AWPROT(M08_AXI_awprot);
  mp_M08_AXI_transactor->AWVALID(M08_AXI_awvalid);
  mp_M08_AXI_transactor->AWREADY(M08_AXI_awready);
  mp_M08_AXI_transactor->WDATA(M08_AXI_wdata);
  mp_M08_AXI_transactor->WSTRB(M08_AXI_wstrb);
  mp_M08_AXI_transactor->WVALID(M08_AXI_wvalid);
  mp_M08_AXI_transactor->WREADY(M08_AXI_wready);
  mp_M08_AXI_transactor->BRESP(M08_AXI_bresp);
  mp_M08_AXI_transactor->BVALID(M08_AXI_bvalid);
  mp_M08_AXI_transactor->BREADY(M08_AXI_bready);
  mp_M08_AXI_transactor->ARADDR(M08_AXI_araddr);
  mp_M08_AXI_transactor->ARPROT(M08_AXI_arprot);
  mp_M08_AXI_transactor->ARVALID(M08_AXI_arvalid);
  mp_M08_AXI_transactor->ARREADY(M08_AXI_arready);
  mp_M08_AXI_transactor->RDATA(M08_AXI_rdata);
  mp_M08_AXI_transactor->RRESP(M08_AXI_rresp);
  mp_M08_AXI_transactor->RVALID(M08_AXI_rvalid);
  mp_M08_AXI_transactor->RREADY(M08_AXI_rready);
  mp_M08_AXI_transactor->CLK(aclk);
  mp_M08_AXI_transactor->RST(aresetn);

  // configure M09_AXI_transactor
    xsc::common_cpp::properties M09_AXI_transactor_param_props;
    M09_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M09_AXI_transactor_param_props.addLong("FREQ_HZ", "50000000");
    M09_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M09_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M09_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M09_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M09_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M09_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M09_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M09_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M09_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M09_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M09_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M09_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M09_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M09_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M09_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M09_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M09_AXI_transactor_param_props.addFloat("PHASE", "0.0");
    M09_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M09_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M09_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_clk_wiz_0_0_clk_50MHz");

    mp_M09_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M09_AXI_transactor", M09_AXI_transactor_param_props);
  mp_M09_AXI_transactor->AWADDR(M09_AXI_awaddr);
  mp_M09_AXI_transactor->AWPROT(M09_AXI_awprot);
  mp_M09_AXI_transactor->AWVALID(M09_AXI_awvalid);
  mp_M09_AXI_transactor->AWREADY(M09_AXI_awready);
  mp_M09_AXI_transactor->WDATA(M09_AXI_wdata);
  mp_M09_AXI_transactor->WSTRB(M09_AXI_wstrb);
  mp_M09_AXI_transactor->WVALID(M09_AXI_wvalid);
  mp_M09_AXI_transactor->WREADY(M09_AXI_wready);
  mp_M09_AXI_transactor->BRESP(M09_AXI_bresp);
  mp_M09_AXI_transactor->BVALID(M09_AXI_bvalid);
  mp_M09_AXI_transactor->BREADY(M09_AXI_bready);
  mp_M09_AXI_transactor->ARADDR(M09_AXI_araddr);
  mp_M09_AXI_transactor->ARPROT(M09_AXI_arprot);
  mp_M09_AXI_transactor->ARVALID(M09_AXI_arvalid);
  mp_M09_AXI_transactor->ARREADY(M09_AXI_arready);
  mp_M09_AXI_transactor->RDATA(M09_AXI_rdata);
  mp_M09_AXI_transactor->RRESP(M09_AXI_rresp);
  mp_M09_AXI_transactor->RVALID(M09_AXI_rvalid);
  mp_M09_AXI_transactor->RREADY(M09_AXI_rready);
  mp_M09_AXI_transactor->CLK(aclk2);
  mp_M09_AXI_transactor->RST(aresetn);

  // configure M10_AXI_transactor
    xsc::common_cpp::properties M10_AXI_transactor_param_props;
    M10_AXI_transactor_param_props.addLong("DATA_WIDTH", "128");
    M10_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M10_AXI_transactor_param_props.addLong("ID_WIDTH", "3");
    M10_AXI_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M10_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "130");
    M10_AXI_transactor_param_props.addLong("WUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("RUSER_WIDTH", "14");
    M10_AXI_transactor_param_props.addLong("BUSER_WIDTH", "114");
    M10_AXI_transactor_param_props.addLong("HAS_BURST", "1");
    M10_AXI_transactor_param_props.addLong("HAS_LOCK", "1");
    M10_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M10_AXI_transactor_param_props.addLong("HAS_CACHE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_QOS", "1");
    M10_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M10_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M10_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M10_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M10_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M10_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M10_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M10_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M10_AXI_transactor_param_props.addLong("HAS_SIZE", "1");
    M10_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M10_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M10_AXI_transactor_param_props.addString("PROTOCOL", "AXI4");
    M10_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M10_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M10_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,3,130,14,114,130,14>("M10_AXI_transactor", M10_AXI_transactor_param_props);
  mp_M10_AXI_transactor->AWID(M10_AXI_awid);
  mp_M10_AXI_transactor->AWADDR(M10_AXI_awaddr);
  mp_M10_AXI_transactor->AWLEN(M10_AXI_awlen);
  mp_M10_AXI_transactor->AWSIZE(M10_AXI_awsize);
  mp_M10_AXI_transactor->AWBURST(M10_AXI_awburst);
  mp_M10_AXI_awlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_awlock_converter");
  mp_M10_AXI_awlock_converter->scalar_in(m_M10_AXI_awlock_converter_signal);
  mp_M10_AXI_awlock_converter->vector_out(M10_AXI_awlock);
  mp_M10_AXI_transactor->AWLOCK(m_M10_AXI_awlock_converter_signal);
  mp_M10_AXI_transactor->AWCACHE(M10_AXI_awcache);
  mp_M10_AXI_transactor->AWPROT(M10_AXI_awprot);
  mp_M10_AXI_transactor->AWQOS(M10_AXI_awqos);
  mp_M10_AXI_transactor->AWUSER(M10_AXI_awuser);
  mp_M10_AXI_transactor->AWVALID(M10_AXI_awvalid);
  mp_M10_AXI_transactor->AWREADY(M10_AXI_awready);
  mp_M10_AXI_transactor->WDATA(M10_AXI_wdata);
  mp_M10_AXI_transactor->WSTRB(M10_AXI_wstrb);
  mp_M10_AXI_transactor->WLAST(M10_AXI_wlast);
  mp_M10_AXI_transactor->WUSER(M10_AXI_wuser);
  mp_M10_AXI_transactor->WVALID(M10_AXI_wvalid);
  mp_M10_AXI_transactor->WREADY(M10_AXI_wready);
  mp_M10_AXI_transactor->BID(M10_AXI_bid);
  mp_M10_AXI_transactor->BRESP(M10_AXI_bresp);
  mp_M10_AXI_transactor->BUSER(M10_AXI_buser);
  mp_M10_AXI_transactor->BVALID(M10_AXI_bvalid);
  mp_M10_AXI_transactor->BREADY(M10_AXI_bready);
  mp_M10_AXI_transactor->ARID(M10_AXI_arid);
  mp_M10_AXI_transactor->ARADDR(M10_AXI_araddr);
  mp_M10_AXI_transactor->ARLEN(M10_AXI_arlen);
  mp_M10_AXI_transactor->ARSIZE(M10_AXI_arsize);
  mp_M10_AXI_transactor->ARBURST(M10_AXI_arburst);
  mp_M10_AXI_arlock_converter = new xsc::common::scalar2vectorN_converter<1>("M10_AXI_arlock_converter");
  mp_M10_AXI_arlock_converter->scalar_in(m_M10_AXI_arlock_converter_signal);
  mp_M10_AXI_arlock_converter->vector_out(M10_AXI_arlock);
  mp_M10_AXI_transactor->ARLOCK(m_M10_AXI_arlock_converter_signal);
  mp_M10_AXI_transactor->ARCACHE(M10_AXI_arcache);
  mp_M10_AXI_transactor->ARPROT(M10_AXI_arprot);
  mp_M10_AXI_transactor->ARQOS(M10_AXI_arqos);
  mp_M10_AXI_transactor->ARUSER(M10_AXI_aruser);
  mp_M10_AXI_transactor->ARVALID(M10_AXI_arvalid);
  mp_M10_AXI_transactor->ARREADY(M10_AXI_arready);
  mp_M10_AXI_transactor->RID(M10_AXI_rid);
  mp_M10_AXI_transactor->RDATA(M10_AXI_rdata);
  mp_M10_AXI_transactor->RRESP(M10_AXI_rresp);
  mp_M10_AXI_transactor->RLAST(M10_AXI_rlast);
  mp_M10_AXI_transactor->RUSER(M10_AXI_ruser);
  mp_M10_AXI_transactor->RVALID(M10_AXI_rvalid);
  mp_M10_AXI_transactor->RREADY(M10_AXI_rready);
  mp_M10_AXI_transactor->CLK(aclk);
  mp_M10_AXI_transactor->RST(aresetn);

  // configure M11_AXI_transactor
    xsc::common_cpp::properties M11_AXI_transactor_param_props;
    M11_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M11_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M11_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ADDR_WIDTH", "5");
    M11_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M11_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M11_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M11_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M11_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M11_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M11_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M11_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M11_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M11_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M11_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M11_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M11_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M11_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M11_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M11_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M11_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M11_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M11_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M11_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,5,1,1,1,1,1,1>("M11_AXI_transactor", M11_AXI_transactor_param_props);
  mp_M11_AXI_transactor->AWADDR(M11_AXI_awaddr);
  mp_M11_AXI_transactor->AWPROT(M11_AXI_awprot);
  mp_M11_AXI_transactor->AWVALID(M11_AXI_awvalid);
  mp_M11_AXI_transactor->AWREADY(M11_AXI_awready);
  mp_M11_AXI_transactor->WDATA(M11_AXI_wdata);
  mp_M11_AXI_transactor->WSTRB(M11_AXI_wstrb);
  mp_M11_AXI_transactor->WVALID(M11_AXI_wvalid);
  mp_M11_AXI_transactor->WREADY(M11_AXI_wready);
  mp_M11_AXI_transactor->BRESP(M11_AXI_bresp);
  mp_M11_AXI_transactor->BVALID(M11_AXI_bvalid);
  mp_M11_AXI_transactor->BREADY(M11_AXI_bready);
  mp_M11_AXI_transactor->ARADDR(M11_AXI_araddr);
  mp_M11_AXI_transactor->ARPROT(M11_AXI_arprot);
  mp_M11_AXI_transactor->ARVALID(M11_AXI_arvalid);
  mp_M11_AXI_transactor->ARREADY(M11_AXI_arready);
  mp_M11_AXI_transactor->RDATA(M11_AXI_rdata);
  mp_M11_AXI_transactor->RRESP(M11_AXI_rresp);
  mp_M11_AXI_transactor->RVALID(M11_AXI_rvalid);
  mp_M11_AXI_transactor->RREADY(M11_AXI_rready);
  mp_M11_AXI_transactor->CLK(aclk);
  mp_M11_AXI_transactor->RST(aresetn);

  // configure M12_AXI_transactor
    xsc::common_cpp::properties M12_AXI_transactor_param_props;
    M12_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M12_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M12_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M12_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M12_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M12_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M12_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M12_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M12_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M12_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M12_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M12_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M12_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M12_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M12_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M12_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M12_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M12_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M12_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M12_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M12_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M12_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M12_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M12_AXI_transactor", M12_AXI_transactor_param_props);
  mp_M12_AXI_transactor->AWADDR(M12_AXI_awaddr);
  mp_M12_AXI_transactor->AWPROT(M12_AXI_awprot);
  mp_M12_AXI_transactor->AWVALID(M12_AXI_awvalid);
  mp_M12_AXI_transactor->AWREADY(M12_AXI_awready);
  mp_M12_AXI_transactor->WDATA(M12_AXI_wdata);
  mp_M12_AXI_transactor->WSTRB(M12_AXI_wstrb);
  mp_M12_AXI_transactor->WVALID(M12_AXI_wvalid);
  mp_M12_AXI_transactor->WREADY(M12_AXI_wready);
  mp_M12_AXI_transactor->BRESP(M12_AXI_bresp);
  mp_M12_AXI_transactor->BVALID(M12_AXI_bvalid);
  mp_M12_AXI_transactor->BREADY(M12_AXI_bready);
  mp_M12_AXI_transactor->ARADDR(M12_AXI_araddr);
  mp_M12_AXI_transactor->ARPROT(M12_AXI_arprot);
  mp_M12_AXI_transactor->ARVALID(M12_AXI_arvalid);
  mp_M12_AXI_transactor->ARREADY(M12_AXI_arready);
  mp_M12_AXI_transactor->RDATA(M12_AXI_rdata);
  mp_M12_AXI_transactor->RRESP(M12_AXI_rresp);
  mp_M12_AXI_transactor->RVALID(M12_AXI_rvalid);
  mp_M12_AXI_transactor->RREADY(M12_AXI_rready);
  mp_M12_AXI_transactor->CLK(aclk);
  mp_M12_AXI_transactor->RST(aresetn);

  // configure M13_AXI_transactor
    xsc::common_cpp::properties M13_AXI_transactor_param_props;
    M13_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M13_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M13_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M13_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M13_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M13_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M13_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M13_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M13_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M13_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M13_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M13_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M13_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M13_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M13_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M13_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M13_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M13_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M13_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M13_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M13_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M13_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M13_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M13_AXI_transactor", M13_AXI_transactor_param_props);
  mp_M13_AXI_transactor->AWADDR(M13_AXI_awaddr);
  mp_M13_AXI_transactor->AWPROT(M13_AXI_awprot);
  mp_M13_AXI_transactor->AWVALID(M13_AXI_awvalid);
  mp_M13_AXI_transactor->AWREADY(M13_AXI_awready);
  mp_M13_AXI_transactor->WDATA(M13_AXI_wdata);
  mp_M13_AXI_transactor->WSTRB(M13_AXI_wstrb);
  mp_M13_AXI_transactor->WVALID(M13_AXI_wvalid);
  mp_M13_AXI_transactor->WREADY(M13_AXI_wready);
  mp_M13_AXI_transactor->BRESP(M13_AXI_bresp);
  mp_M13_AXI_transactor->BVALID(M13_AXI_bvalid);
  mp_M13_AXI_transactor->BREADY(M13_AXI_bready);
  mp_M13_AXI_transactor->ARADDR(M13_AXI_araddr);
  mp_M13_AXI_transactor->ARPROT(M13_AXI_arprot);
  mp_M13_AXI_transactor->ARVALID(M13_AXI_arvalid);
  mp_M13_AXI_transactor->ARREADY(M13_AXI_arready);
  mp_M13_AXI_transactor->RDATA(M13_AXI_rdata);
  mp_M13_AXI_transactor->RRESP(M13_AXI_rresp);
  mp_M13_AXI_transactor->RVALID(M13_AXI_rvalid);
  mp_M13_AXI_transactor->RREADY(M13_AXI_rready);
  mp_M13_AXI_transactor->CLK(aclk);
  mp_M13_AXI_transactor->RST(aresetn);

  // configure M14_AXI_transactor
    xsc::common_cpp::properties M14_AXI_transactor_param_props;
    M14_AXI_transactor_param_props.addLong("DATA_WIDTH", "32");
    M14_AXI_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M14_AXI_transactor_param_props.addLong("ID_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ADDR_WIDTH", "16");
    M14_AXI_transactor_param_props.addLong("AWUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("ARUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M14_AXI_transactor_param_props.addLong("HAS_BURST", "0");
    M14_AXI_transactor_param_props.addLong("HAS_LOCK", "0");
    M14_AXI_transactor_param_props.addLong("HAS_PROT", "1");
    M14_AXI_transactor_param_props.addLong("HAS_CACHE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_QOS", "0");
    M14_AXI_transactor_param_props.addLong("HAS_REGION", "0");
    M14_AXI_transactor_param_props.addLong("HAS_WSTRB", "1");
    M14_AXI_transactor_param_props.addLong("HAS_BRESP", "1");
    M14_AXI_transactor_param_props.addLong("HAS_RRESP", "1");
    M14_AXI_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    M14_AXI_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M14_AXI_transactor_param_props.addLong("MAX_BURST_LENGTH", "1");
    M14_AXI_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    M14_AXI_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_SIZE", "0");
    M14_AXI_transactor_param_props.addLong("HAS_RESET", "1");
    M14_AXI_transactor_param_props.addFloat("PHASE", "0.000");
    M14_AXI_transactor_param_props.addString("PROTOCOL", "AXI4LITE");
    M14_AXI_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M14_AXI_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M14_AXI_transactor = new xtlm::xaximm_xtlm2pin_t<32,16,1,1,1,1,1,1>("M14_AXI_transactor", M14_AXI_transactor_param_props);
  mp_M14_AXI_transactor->AWADDR(M14_AXI_awaddr);
  mp_M14_AXI_transactor->AWPROT(M14_AXI_awprot);
  mp_M14_AXI_transactor->AWVALID(M14_AXI_awvalid);
  mp_M14_AXI_transactor->AWREADY(M14_AXI_awready);
  mp_M14_AXI_transactor->WDATA(M14_AXI_wdata);
  mp_M14_AXI_transactor->WSTRB(M14_AXI_wstrb);
  mp_M14_AXI_transactor->WVALID(M14_AXI_wvalid);
  mp_M14_AXI_transactor->WREADY(M14_AXI_wready);
  mp_M14_AXI_transactor->BRESP(M14_AXI_bresp);
  mp_M14_AXI_transactor->BVALID(M14_AXI_bvalid);
  mp_M14_AXI_transactor->BREADY(M14_AXI_bready);
  mp_M14_AXI_transactor->ARADDR(M14_AXI_araddr);
  mp_M14_AXI_transactor->ARPROT(M14_AXI_arprot);
  mp_M14_AXI_transactor->ARVALID(M14_AXI_arvalid);
  mp_M14_AXI_transactor->ARREADY(M14_AXI_arready);
  mp_M14_AXI_transactor->RDATA(M14_AXI_rdata);
  mp_M14_AXI_transactor->RRESP(M14_AXI_rresp);
  mp_M14_AXI_transactor->RVALID(M14_AXI_rvalid);
  mp_M14_AXI_transactor->RREADY(M14_AXI_rready);
  mp_M14_AXI_transactor->CLK(aclk);
  mp_M14_AXI_transactor->RST(aresetn);


  // initialize transactors stubs
  S00_AXI_transactor_target_wr_socket_stub = nullptr;
  S00_AXI_transactor_target_rd_socket_stub = nullptr;
  M00_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M00_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M01_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M01_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M02_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M02_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M03_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M03_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M04_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M04_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M05_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M05_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M06_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M06_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M07_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M07_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M08_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M08_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M09_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M09_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M10_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M10_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M11_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M11_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M12_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M12_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M13_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M13_AXI_transactor_initiator_rd_socket_stub = nullptr;
  M14_AXI_transactor_initiator_wr_socket_stub = nullptr;
  M14_AXI_transactor_initiator_rd_socket_stub = nullptr;

}

void zusys_smartconnect_0_0::before_end_of_elaboration()
{
  // configure 'S00_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "S00_AXI_TLM_MODE") != 1)
  {
    mp_impl->S00_AXI_tlm_aximm_read_socket->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_impl->S00_AXI_tlm_aximm_write_socket->bind(*(mp_S00_AXI_transactor->wr_socket));
  }
  else
  {
    S00_AXI_transactor_target_wr_socket_stub = new xtlm::xtlm_aximm_target_stub("wr_socket",0);
    S00_AXI_transactor_target_wr_socket_stub->bind(*(mp_S00_AXI_transactor->wr_socket));
    S00_AXI_transactor_target_rd_socket_stub = new xtlm::xtlm_aximm_target_stub("rd_socket",0);
    S00_AXI_transactor_target_rd_socket_stub->bind(*(mp_S00_AXI_transactor->rd_socket));
    mp_S00_AXI_transactor->disable_transactor();
  }

  // configure 'M00_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M00_AXI_TLM_MODE") != 1)
  {
    mp_impl->M00_AXI_tlm_aximm_read_socket->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_impl->M00_AXI_tlm_aximm_write_socket->bind(*(mp_M00_AXI_transactor->wr_socket));
  }
  else
  {
    M00_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M00_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M00_AXI_transactor->wr_socket));
    M00_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M00_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M00_AXI_transactor->rd_socket));
    mp_M00_AXI_transactor->disable_transactor();
  }

  // configure 'M01_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M01_AXI_TLM_MODE") != 1)
  {
    mp_impl->M01_AXI_tlm_aximm_read_socket->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_impl->M01_AXI_tlm_aximm_write_socket->bind(*(mp_M01_AXI_transactor->wr_socket));
  }
  else
  {
    M01_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M01_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M01_AXI_transactor->wr_socket));
    M01_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M01_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M01_AXI_transactor->rd_socket));
    mp_M01_AXI_transactor->disable_transactor();
  }

  // configure 'M02_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M02_AXI_TLM_MODE") != 1)
  {
    mp_impl->M02_AXI_tlm_aximm_read_socket->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_impl->M02_AXI_tlm_aximm_write_socket->bind(*(mp_M02_AXI_transactor->wr_socket));
  }
  else
  {
    M02_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M02_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M02_AXI_transactor->wr_socket));
    M02_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M02_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M02_AXI_transactor->rd_socket));
    mp_M02_AXI_transactor->disable_transactor();
  }

  // configure 'M03_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M03_AXI_TLM_MODE") != 1)
  {
    mp_impl->M03_AXI_tlm_aximm_read_socket->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_impl->M03_AXI_tlm_aximm_write_socket->bind(*(mp_M03_AXI_transactor->wr_socket));
  }
  else
  {
    M03_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M03_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M03_AXI_transactor->wr_socket));
    M03_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M03_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M03_AXI_transactor->rd_socket));
    mp_M03_AXI_transactor->disable_transactor();
  }

  // configure 'M04_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M04_AXI_TLM_MODE") != 1)
  {
    mp_impl->M04_AXI_tlm_aximm_read_socket->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_impl->M04_AXI_tlm_aximm_write_socket->bind(*(mp_M04_AXI_transactor->wr_socket));
  }
  else
  {
    M04_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M04_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M04_AXI_transactor->wr_socket));
    M04_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M04_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M04_AXI_transactor->rd_socket));
    mp_M04_AXI_transactor->disable_transactor();
  }

  // configure 'M05_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M05_AXI_TLM_MODE") != 1)
  {
    mp_impl->M05_AXI_tlm_aximm_read_socket->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_impl->M05_AXI_tlm_aximm_write_socket->bind(*(mp_M05_AXI_transactor->wr_socket));
  }
  else
  {
    M05_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M05_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M05_AXI_transactor->wr_socket));
    M05_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M05_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M05_AXI_transactor->rd_socket));
    mp_M05_AXI_transactor->disable_transactor();
  }

  // configure 'M06_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M06_AXI_TLM_MODE") != 1)
  {
    mp_impl->M06_AXI_tlm_aximm_read_socket->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_impl->M06_AXI_tlm_aximm_write_socket->bind(*(mp_M06_AXI_transactor->wr_socket));
  }
  else
  {
    M06_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M06_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M06_AXI_transactor->wr_socket));
    M06_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M06_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M06_AXI_transactor->rd_socket));
    mp_M06_AXI_transactor->disable_transactor();
  }

  // configure 'M07_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M07_AXI_TLM_MODE") != 1)
  {
    mp_impl->M07_AXI_tlm_aximm_read_socket->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_impl->M07_AXI_tlm_aximm_write_socket->bind(*(mp_M07_AXI_transactor->wr_socket));
  }
  else
  {
    M07_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M07_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M07_AXI_transactor->wr_socket));
    M07_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M07_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M07_AXI_transactor->rd_socket));
    mp_M07_AXI_transactor->disable_transactor();
  }

  // configure 'M08_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M08_AXI_TLM_MODE") != 1)
  {
    mp_impl->M08_AXI_tlm_aximm_read_socket->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_impl->M08_AXI_tlm_aximm_write_socket->bind(*(mp_M08_AXI_transactor->wr_socket));
  }
  else
  {
    M08_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M08_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M08_AXI_transactor->wr_socket));
    M08_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M08_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M08_AXI_transactor->rd_socket));
    mp_M08_AXI_transactor->disable_transactor();
  }

  // configure 'M09_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M09_AXI_TLM_MODE") != 1)
  {
    mp_impl->M09_AXI_tlm_aximm_read_socket->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_impl->M09_AXI_tlm_aximm_write_socket->bind(*(mp_M09_AXI_transactor->wr_socket));
  }
  else
  {
    M09_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M09_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M09_AXI_transactor->wr_socket));
    M09_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M09_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M09_AXI_transactor->rd_socket));
    mp_M09_AXI_transactor->disable_transactor();
  }

  // configure 'M10_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M10_AXI_TLM_MODE") != 1)
  {
    mp_impl->M10_AXI_tlm_aximm_read_socket->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_impl->M10_AXI_tlm_aximm_write_socket->bind(*(mp_M10_AXI_transactor->wr_socket));
  }
  else
  {
    M10_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M10_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M10_AXI_transactor->wr_socket));
    M10_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M10_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M10_AXI_transactor->rd_socket));
    mp_M10_AXI_transactor->disable_transactor();
  }

  // configure 'M11_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M11_AXI_TLM_MODE") != 1)
  {
    mp_impl->M11_AXI_tlm_aximm_read_socket->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_impl->M11_AXI_tlm_aximm_write_socket->bind(*(mp_M11_AXI_transactor->wr_socket));
  }
  else
  {
    M11_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M11_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M11_AXI_transactor->wr_socket));
    M11_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M11_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M11_AXI_transactor->rd_socket));
    mp_M11_AXI_transactor->disable_transactor();
  }

  // configure 'M12_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M12_AXI_TLM_MODE") != 1)
  {
    mp_impl->M12_AXI_tlm_aximm_read_socket->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_impl->M12_AXI_tlm_aximm_write_socket->bind(*(mp_M12_AXI_transactor->wr_socket));
  }
  else
  {
    M12_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M12_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M12_AXI_transactor->wr_socket));
    M12_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M12_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M12_AXI_transactor->rd_socket));
    mp_M12_AXI_transactor->disable_transactor();
  }

  // configure 'M13_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M13_AXI_TLM_MODE") != 1)
  {
    mp_impl->M13_AXI_tlm_aximm_read_socket->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_impl->M13_AXI_tlm_aximm_write_socket->bind(*(mp_M13_AXI_transactor->wr_socket));
  }
  else
  {
    M13_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M13_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M13_AXI_transactor->wr_socket));
    M13_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M13_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M13_AXI_transactor->rd_socket));
    mp_M13_AXI_transactor->disable_transactor();
  }

  // configure 'M14_AXI' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_smartconnect_0_0", "M14_AXI_TLM_MODE") != 1)
  {
    mp_impl->M14_AXI_tlm_aximm_read_socket->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_impl->M14_AXI_tlm_aximm_write_socket->bind(*(mp_M14_AXI_transactor->wr_socket));
  }
  else
  {
    M14_AXI_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M14_AXI_transactor_initiator_wr_socket_stub->bind(*(mp_M14_AXI_transactor->wr_socket));
    M14_AXI_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M14_AXI_transactor_initiator_rd_socket_stub->bind(*(mp_M14_AXI_transactor->rd_socket));
    mp_M14_AXI_transactor->disable_transactor();
  }

}

#endif // MTI_SYSTEMC




zusys_smartconnect_0_0::~zusys_smartconnect_0_0()
{
  delete mp_S00_AXI_transactor;
  delete mp_S00_AXI_awlock_converter;
  delete mp_S00_AXI_arlock_converter;

  delete mp_M00_AXI_transactor;

  delete mp_M01_AXI_transactor;

  delete mp_M02_AXI_transactor;

  delete mp_M03_AXI_transactor;

  delete mp_M04_AXI_transactor;

  delete mp_M05_AXI_transactor;

  delete mp_M06_AXI_transactor;

  delete mp_M07_AXI_transactor;
  delete mp_M07_AXI_awlock_converter;
  delete mp_M07_AXI_arlock_converter;

  delete mp_M08_AXI_transactor;

  delete mp_M09_AXI_transactor;

  delete mp_M10_AXI_transactor;
  delete mp_M10_AXI_awlock_converter;
  delete mp_M10_AXI_arlock_converter;

  delete mp_M11_AXI_transactor;

  delete mp_M12_AXI_transactor;

  delete mp_M13_AXI_transactor;

  delete mp_M14_AXI_transactor;

}

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(zusys_smartconnect_0_0);
#endif

#ifdef XM_SYSTEMC
XMSC_MODULE_EXPORT(zusys_smartconnect_0_0);
#endif

#ifdef RIVIERA
SC_MODULE_EXPORT(zusys_smartconnect_0_0);
SC_REGISTER_BV(130);
#endif

