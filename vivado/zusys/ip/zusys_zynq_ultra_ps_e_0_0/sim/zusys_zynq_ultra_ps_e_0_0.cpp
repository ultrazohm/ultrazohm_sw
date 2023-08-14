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


#include "zusys_zynq_ultra_ps_e_0_0_sc.h"

#include "zusys_zynq_ultra_ps_e_0_0.h"

#include "zynq_ultra_ps_e_tlm.h"

#include <map>
#include <string>





#ifdef XILINX_SIMULATOR
zusys_zynq_ultra_ps_e_0_0::zusys_zynq_ultra_ps_e_0_0(const sc_core::sc_module_name& nm) : zusys_zynq_ultra_ps_e_0_0_sc(nm), maxihpm0_lpd_aclk("maxihpm0_lpd_aclk"), maxigp2_awid("maxigp2_awid"), maxigp2_awaddr("maxigp2_awaddr"), maxigp2_awlen("maxigp2_awlen"), maxigp2_awsize("maxigp2_awsize"), maxigp2_awburst("maxigp2_awburst"), maxigp2_awlock("maxigp2_awlock"), maxigp2_awcache("maxigp2_awcache"), maxigp2_awprot("maxigp2_awprot"), maxigp2_awvalid("maxigp2_awvalid"), maxigp2_awuser("maxigp2_awuser"), maxigp2_awready("maxigp2_awready"), maxigp2_wdata("maxigp2_wdata"), maxigp2_wstrb("maxigp2_wstrb"), maxigp2_wlast("maxigp2_wlast"), maxigp2_wvalid("maxigp2_wvalid"), maxigp2_wready("maxigp2_wready"), maxigp2_bid("maxigp2_bid"), maxigp2_bresp("maxigp2_bresp"), maxigp2_bvalid("maxigp2_bvalid"), maxigp2_bready("maxigp2_bready"), maxigp2_arid("maxigp2_arid"), maxigp2_araddr("maxigp2_araddr"), maxigp2_arlen("maxigp2_arlen"), maxigp2_arsize("maxigp2_arsize"), maxigp2_arburst("maxigp2_arburst"), maxigp2_arlock("maxigp2_arlock"), maxigp2_arcache("maxigp2_arcache"), maxigp2_arprot("maxigp2_arprot"), maxigp2_arvalid("maxigp2_arvalid"), maxigp2_aruser("maxigp2_aruser"), maxigp2_arready("maxigp2_arready"), maxigp2_rid("maxigp2_rid"), maxigp2_rdata("maxigp2_rdata"), maxigp2_rresp("maxigp2_rresp"), maxigp2_rlast("maxigp2_rlast"), maxigp2_rvalid("maxigp2_rvalid"), maxigp2_rready("maxigp2_rready"), maxigp2_awqos("maxigp2_awqos"), maxigp2_arqos("maxigp2_arqos"), saxi_lpd_aclk("saxi_lpd_aclk"), saxigp6_aruser("saxigp6_aruser"), saxigp6_awuser("saxigp6_awuser"), saxigp6_awid("saxigp6_awid"), saxigp6_awaddr("saxigp6_awaddr"), saxigp6_awlen("saxigp6_awlen"), saxigp6_awsize("saxigp6_awsize"), saxigp6_awburst("saxigp6_awburst"), saxigp6_awlock("saxigp6_awlock"), saxigp6_awcache("saxigp6_awcache"), saxigp6_awprot("saxigp6_awprot"), saxigp6_awvalid("saxigp6_awvalid"), saxigp6_awready("saxigp6_awready"), saxigp6_wdata("saxigp6_wdata"), saxigp6_wstrb("saxigp6_wstrb"), saxigp6_wlast("saxigp6_wlast"), saxigp6_wvalid("saxigp6_wvalid"), saxigp6_wready("saxigp6_wready"), saxigp6_bid("saxigp6_bid"), saxigp6_bresp("saxigp6_bresp"), saxigp6_bvalid("saxigp6_bvalid"), saxigp6_bready("saxigp6_bready"), saxigp6_arid("saxigp6_arid"), saxigp6_araddr("saxigp6_araddr"), saxigp6_arlen("saxigp6_arlen"), saxigp6_arsize("saxigp6_arsize"), saxigp6_arburst("saxigp6_arburst"), saxigp6_arlock("saxigp6_arlock"), saxigp6_arcache("saxigp6_arcache"), saxigp6_arprot("saxigp6_arprot"), saxigp6_arvalid("saxigp6_arvalid"), saxigp6_arready("saxigp6_arready"), saxigp6_rid("saxigp6_rid"), saxigp6_rdata("saxigp6_rdata"), saxigp6_rresp("saxigp6_rresp"), saxigp6_rlast("saxigp6_rlast"), saxigp6_rvalid("saxigp6_rvalid"), saxigp6_rready("saxigp6_rready"), saxigp6_awqos("saxigp6_awqos"), saxigp6_arqos("saxigp6_arqos"), pl_ps_irq0("pl_ps_irq0"), pl_resetn0("pl_resetn0"), pl_clk0("pl_clk0")
{

  // initialize pins
  mp_impl->maxihpm0_lpd_aclk(maxihpm0_lpd_aclk);
  mp_impl->saxi_lpd_aclk(saxi_lpd_aclk);
  mp_impl->pl_ps_irq0(pl_ps_irq0);
  mp_impl->pl_resetn0(pl_resetn0);
  mp_impl->pl_clk0(pl_clk0);

  // initialize transactors
  mp_M_AXI_HPM0_LPD_transactor = NULL;
  mp_S_AXI_LPD_transactor = NULL;
  mp_saxigp6_aruser_converter = NULL;
  mp_saxigp6_awuser_converter = NULL;

  // initialize socket stubs

}

void zusys_zynq_ultra_ps_e_0_0::before_end_of_elaboration()
{
  // configure 'M_AXI_HPM0_LPD' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "M_AXI_HPM0_LPD_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M_AXI_HPM0_LPD' transactor parameters
    xsc::common_cpp::properties M_AXI_HPM0_LPD_transactor_param_props;
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("DATA_WIDTH", "128");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ID_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    M_AXI_HPM0_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    M_AXI_HPM0_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M_AXI_HPM0_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M_AXI_HPM0_LPD_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,16,16,1,1,16,1>("M_AXI_HPM0_LPD_transactor", M_AXI_HPM0_LPD_transactor_param_props);

    // M_AXI_HPM0_LPD' transactor ports

    mp_M_AXI_HPM0_LPD_transactor->AWID(maxigp2_awid);
    mp_M_AXI_HPM0_LPD_transactor->AWADDR(maxigp2_awaddr);
    mp_M_AXI_HPM0_LPD_transactor->AWLEN(maxigp2_awlen);
    mp_M_AXI_HPM0_LPD_transactor->AWSIZE(maxigp2_awsize);
    mp_M_AXI_HPM0_LPD_transactor->AWBURST(maxigp2_awburst);
    mp_M_AXI_HPM0_LPD_transactor->AWLOCK(maxigp2_awlock);
    mp_M_AXI_HPM0_LPD_transactor->AWCACHE(maxigp2_awcache);
    mp_M_AXI_HPM0_LPD_transactor->AWPROT(maxigp2_awprot);
    mp_M_AXI_HPM0_LPD_transactor->AWVALID(maxigp2_awvalid);
    mp_M_AXI_HPM0_LPD_transactor->AWUSER(maxigp2_awuser);
    mp_M_AXI_HPM0_LPD_transactor->AWREADY(maxigp2_awready);
    mp_M_AXI_HPM0_LPD_transactor->WDATA(maxigp2_wdata);
    mp_M_AXI_HPM0_LPD_transactor->WSTRB(maxigp2_wstrb);
    mp_M_AXI_HPM0_LPD_transactor->WLAST(maxigp2_wlast);
    mp_M_AXI_HPM0_LPD_transactor->WVALID(maxigp2_wvalid);
    mp_M_AXI_HPM0_LPD_transactor->WREADY(maxigp2_wready);
    mp_M_AXI_HPM0_LPD_transactor->BID(maxigp2_bid);
    mp_M_AXI_HPM0_LPD_transactor->BRESP(maxigp2_bresp);
    mp_M_AXI_HPM0_LPD_transactor->BVALID(maxigp2_bvalid);
    mp_M_AXI_HPM0_LPD_transactor->BREADY(maxigp2_bready);
    mp_M_AXI_HPM0_LPD_transactor->ARID(maxigp2_arid);
    mp_M_AXI_HPM0_LPD_transactor->ARADDR(maxigp2_araddr);
    mp_M_AXI_HPM0_LPD_transactor->ARLEN(maxigp2_arlen);
    mp_M_AXI_HPM0_LPD_transactor->ARSIZE(maxigp2_arsize);
    mp_M_AXI_HPM0_LPD_transactor->ARBURST(maxigp2_arburst);
    mp_M_AXI_HPM0_LPD_transactor->ARLOCK(maxigp2_arlock);
    mp_M_AXI_HPM0_LPD_transactor->ARCACHE(maxigp2_arcache);
    mp_M_AXI_HPM0_LPD_transactor->ARPROT(maxigp2_arprot);
    mp_M_AXI_HPM0_LPD_transactor->ARVALID(maxigp2_arvalid);
    mp_M_AXI_HPM0_LPD_transactor->ARUSER(maxigp2_aruser);
    mp_M_AXI_HPM0_LPD_transactor->ARREADY(maxigp2_arready);
    mp_M_AXI_HPM0_LPD_transactor->RID(maxigp2_rid);
    mp_M_AXI_HPM0_LPD_transactor->RDATA(maxigp2_rdata);
    mp_M_AXI_HPM0_LPD_transactor->RRESP(maxigp2_rresp);
    mp_M_AXI_HPM0_LPD_transactor->RLAST(maxigp2_rlast);
    mp_M_AXI_HPM0_LPD_transactor->RVALID(maxigp2_rvalid);
    mp_M_AXI_HPM0_LPD_transactor->RREADY(maxigp2_rready);
    mp_M_AXI_HPM0_LPD_transactor->AWQOS(maxigp2_awqos);
    mp_M_AXI_HPM0_LPD_transactor->ARQOS(maxigp2_arqos);
    mp_M_AXI_HPM0_LPD_transactor->CLK(maxihpm0_lpd_aclk);
    m_M_AXI_HPM0_LPD_transactor_rst_signal.write(1);
    mp_M_AXI_HPM0_LPD_transactor->RST(m_M_AXI_HPM0_LPD_transactor_rst_signal);

    // M_AXI_HPM0_LPD' transactor sockets

    mp_impl->M_AXI_HPM0_LPD_rd_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_impl->M_AXI_HPM0_LPD_wr_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
  }

  // configure 'S_AXI_LPD' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "S_AXI_LPD_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'S_AXI_LPD' transactor parameters
    xsc::common_cpp::properties S_AXI_LPD_transactor_param_props;
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("DATA_WIDTH", "32");
    S_AXI_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S_AXI_LPD_transactor_param_props.addLong("ID_WIDTH", "6");
    S_AXI_LPD_transactor_param_props.addLong("ADDR_WIDTH", "49");
    S_AXI_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    S_AXI_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    S_AXI_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    S_AXI_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    S_AXI_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S_AXI_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S_AXI_LPD_transactor = new xtlm::xaximm_pin2xtlm_t<32,49,6,1,1,1,1,1>("S_AXI_LPD_transactor", S_AXI_LPD_transactor_param_props);

    // S_AXI_LPD' transactor ports

    mp_saxigp6_aruser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_aruser_converter");
    mp_saxigp6_aruser_converter->scalar_in(saxigp6_aruser);
    mp_saxigp6_aruser_converter->vector_out(m_saxigp6_aruser_converter_signal);
    mp_S_AXI_LPD_transactor->ARUSER(m_saxigp6_aruser_converter_signal);
    mp_saxigp6_awuser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_awuser_converter");
    mp_saxigp6_awuser_converter->scalar_in(saxigp6_awuser);
    mp_saxigp6_awuser_converter->vector_out(m_saxigp6_awuser_converter_signal);
    mp_S_AXI_LPD_transactor->AWUSER(m_saxigp6_awuser_converter_signal);
    mp_S_AXI_LPD_transactor->AWID(saxigp6_awid);
    mp_S_AXI_LPD_transactor->AWADDR(saxigp6_awaddr);
    mp_S_AXI_LPD_transactor->AWLEN(saxigp6_awlen);
    mp_S_AXI_LPD_transactor->AWSIZE(saxigp6_awsize);
    mp_S_AXI_LPD_transactor->AWBURST(saxigp6_awburst);
    mp_S_AXI_LPD_transactor->AWLOCK(saxigp6_awlock);
    mp_S_AXI_LPD_transactor->AWCACHE(saxigp6_awcache);
    mp_S_AXI_LPD_transactor->AWPROT(saxigp6_awprot);
    mp_S_AXI_LPD_transactor->AWVALID(saxigp6_awvalid);
    mp_S_AXI_LPD_transactor->AWREADY(saxigp6_awready);
    mp_S_AXI_LPD_transactor->WDATA(saxigp6_wdata);
    mp_S_AXI_LPD_transactor->WSTRB(saxigp6_wstrb);
    mp_S_AXI_LPD_transactor->WLAST(saxigp6_wlast);
    mp_S_AXI_LPD_transactor->WVALID(saxigp6_wvalid);
    mp_S_AXI_LPD_transactor->WREADY(saxigp6_wready);
    mp_S_AXI_LPD_transactor->BID(saxigp6_bid);
    mp_S_AXI_LPD_transactor->BRESP(saxigp6_bresp);
    mp_S_AXI_LPD_transactor->BVALID(saxigp6_bvalid);
    mp_S_AXI_LPD_transactor->BREADY(saxigp6_bready);
    mp_S_AXI_LPD_transactor->ARID(saxigp6_arid);
    mp_S_AXI_LPD_transactor->ARADDR(saxigp6_araddr);
    mp_S_AXI_LPD_transactor->ARLEN(saxigp6_arlen);
    mp_S_AXI_LPD_transactor->ARSIZE(saxigp6_arsize);
    mp_S_AXI_LPD_transactor->ARBURST(saxigp6_arburst);
    mp_S_AXI_LPD_transactor->ARLOCK(saxigp6_arlock);
    mp_S_AXI_LPD_transactor->ARCACHE(saxigp6_arcache);
    mp_S_AXI_LPD_transactor->ARPROT(saxigp6_arprot);
    mp_S_AXI_LPD_transactor->ARVALID(saxigp6_arvalid);
    mp_S_AXI_LPD_transactor->ARREADY(saxigp6_arready);
    mp_S_AXI_LPD_transactor->RID(saxigp6_rid);
    mp_S_AXI_LPD_transactor->RDATA(saxigp6_rdata);
    mp_S_AXI_LPD_transactor->RRESP(saxigp6_rresp);
    mp_S_AXI_LPD_transactor->RLAST(saxigp6_rlast);
    mp_S_AXI_LPD_transactor->RVALID(saxigp6_rvalid);
    mp_S_AXI_LPD_transactor->RREADY(saxigp6_rready);
    mp_S_AXI_LPD_transactor->AWQOS(saxigp6_awqos);
    mp_S_AXI_LPD_transactor->ARQOS(saxigp6_arqos);
    mp_S_AXI_LPD_transactor->CLK(saxi_lpd_aclk);
    m_S_AXI_LPD_transactor_rst_signal.write(1);
    mp_S_AXI_LPD_transactor->RST(m_S_AXI_LPD_transactor_rst_signal);

    // S_AXI_LPD' transactor sockets

    mp_impl->S_AXI_LPD_rd_socket->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_impl->S_AXI_LPD_wr_socket->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
  }

}

#endif // XILINX_SIMULATOR




#ifdef XM_SYSTEMC
zusys_zynq_ultra_ps_e_0_0::zusys_zynq_ultra_ps_e_0_0(const sc_core::sc_module_name& nm) : zusys_zynq_ultra_ps_e_0_0_sc(nm), maxihpm0_lpd_aclk("maxihpm0_lpd_aclk"), maxigp2_awid("maxigp2_awid"), maxigp2_awaddr("maxigp2_awaddr"), maxigp2_awlen("maxigp2_awlen"), maxigp2_awsize("maxigp2_awsize"), maxigp2_awburst("maxigp2_awburst"), maxigp2_awlock("maxigp2_awlock"), maxigp2_awcache("maxigp2_awcache"), maxigp2_awprot("maxigp2_awprot"), maxigp2_awvalid("maxigp2_awvalid"), maxigp2_awuser("maxigp2_awuser"), maxigp2_awready("maxigp2_awready"), maxigp2_wdata("maxigp2_wdata"), maxigp2_wstrb("maxigp2_wstrb"), maxigp2_wlast("maxigp2_wlast"), maxigp2_wvalid("maxigp2_wvalid"), maxigp2_wready("maxigp2_wready"), maxigp2_bid("maxigp2_bid"), maxigp2_bresp("maxigp2_bresp"), maxigp2_bvalid("maxigp2_bvalid"), maxigp2_bready("maxigp2_bready"), maxigp2_arid("maxigp2_arid"), maxigp2_araddr("maxigp2_araddr"), maxigp2_arlen("maxigp2_arlen"), maxigp2_arsize("maxigp2_arsize"), maxigp2_arburst("maxigp2_arburst"), maxigp2_arlock("maxigp2_arlock"), maxigp2_arcache("maxigp2_arcache"), maxigp2_arprot("maxigp2_arprot"), maxigp2_arvalid("maxigp2_arvalid"), maxigp2_aruser("maxigp2_aruser"), maxigp2_arready("maxigp2_arready"), maxigp2_rid("maxigp2_rid"), maxigp2_rdata("maxigp2_rdata"), maxigp2_rresp("maxigp2_rresp"), maxigp2_rlast("maxigp2_rlast"), maxigp2_rvalid("maxigp2_rvalid"), maxigp2_rready("maxigp2_rready"), maxigp2_awqos("maxigp2_awqos"), maxigp2_arqos("maxigp2_arqos"), saxi_lpd_aclk("saxi_lpd_aclk"), saxigp6_aruser("saxigp6_aruser"), saxigp6_awuser("saxigp6_awuser"), saxigp6_awid("saxigp6_awid"), saxigp6_awaddr("saxigp6_awaddr"), saxigp6_awlen("saxigp6_awlen"), saxigp6_awsize("saxigp6_awsize"), saxigp6_awburst("saxigp6_awburst"), saxigp6_awlock("saxigp6_awlock"), saxigp6_awcache("saxigp6_awcache"), saxigp6_awprot("saxigp6_awprot"), saxigp6_awvalid("saxigp6_awvalid"), saxigp6_awready("saxigp6_awready"), saxigp6_wdata("saxigp6_wdata"), saxigp6_wstrb("saxigp6_wstrb"), saxigp6_wlast("saxigp6_wlast"), saxigp6_wvalid("saxigp6_wvalid"), saxigp6_wready("saxigp6_wready"), saxigp6_bid("saxigp6_bid"), saxigp6_bresp("saxigp6_bresp"), saxigp6_bvalid("saxigp6_bvalid"), saxigp6_bready("saxigp6_bready"), saxigp6_arid("saxigp6_arid"), saxigp6_araddr("saxigp6_araddr"), saxigp6_arlen("saxigp6_arlen"), saxigp6_arsize("saxigp6_arsize"), saxigp6_arburst("saxigp6_arburst"), saxigp6_arlock("saxigp6_arlock"), saxigp6_arcache("saxigp6_arcache"), saxigp6_arprot("saxigp6_arprot"), saxigp6_arvalid("saxigp6_arvalid"), saxigp6_arready("saxigp6_arready"), saxigp6_rid("saxigp6_rid"), saxigp6_rdata("saxigp6_rdata"), saxigp6_rresp("saxigp6_rresp"), saxigp6_rlast("saxigp6_rlast"), saxigp6_rvalid("saxigp6_rvalid"), saxigp6_rready("saxigp6_rready"), saxigp6_awqos("saxigp6_awqos"), saxigp6_arqos("saxigp6_arqos"), pl_ps_irq0("pl_ps_irq0"), pl_resetn0("pl_resetn0"), pl_clk0("pl_clk0")
{

  // initialize pins
  mp_impl->maxihpm0_lpd_aclk(maxihpm0_lpd_aclk);
  mp_impl->saxi_lpd_aclk(saxi_lpd_aclk);
  mp_impl->pl_ps_irq0(pl_ps_irq0);
  mp_impl->pl_resetn0(pl_resetn0);
  mp_impl->pl_clk0(pl_clk0);

  // initialize transactors
  mp_M_AXI_HPM0_LPD_transactor = NULL;
  mp_S_AXI_LPD_transactor = NULL;
  mp_saxigp6_aruser_converter = NULL;
  mp_saxigp6_awuser_converter = NULL;

  // initialize socket stubs

}

void zusys_zynq_ultra_ps_e_0_0::before_end_of_elaboration()
{
  // configure 'M_AXI_HPM0_LPD' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "M_AXI_HPM0_LPD_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M_AXI_HPM0_LPD' transactor parameters
    xsc::common_cpp::properties M_AXI_HPM0_LPD_transactor_param_props;
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("DATA_WIDTH", "128");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ID_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    M_AXI_HPM0_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    M_AXI_HPM0_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M_AXI_HPM0_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M_AXI_HPM0_LPD_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,16,16,1,1,16,1>("M_AXI_HPM0_LPD_transactor", M_AXI_HPM0_LPD_transactor_param_props);

    // M_AXI_HPM0_LPD' transactor ports

    mp_M_AXI_HPM0_LPD_transactor->AWID(maxigp2_awid);
    mp_M_AXI_HPM0_LPD_transactor->AWADDR(maxigp2_awaddr);
    mp_M_AXI_HPM0_LPD_transactor->AWLEN(maxigp2_awlen);
    mp_M_AXI_HPM0_LPD_transactor->AWSIZE(maxigp2_awsize);
    mp_M_AXI_HPM0_LPD_transactor->AWBURST(maxigp2_awburst);
    mp_M_AXI_HPM0_LPD_transactor->AWLOCK(maxigp2_awlock);
    mp_M_AXI_HPM0_LPD_transactor->AWCACHE(maxigp2_awcache);
    mp_M_AXI_HPM0_LPD_transactor->AWPROT(maxigp2_awprot);
    mp_M_AXI_HPM0_LPD_transactor->AWVALID(maxigp2_awvalid);
    mp_M_AXI_HPM0_LPD_transactor->AWUSER(maxigp2_awuser);
    mp_M_AXI_HPM0_LPD_transactor->AWREADY(maxigp2_awready);
    mp_M_AXI_HPM0_LPD_transactor->WDATA(maxigp2_wdata);
    mp_M_AXI_HPM0_LPD_transactor->WSTRB(maxigp2_wstrb);
    mp_M_AXI_HPM0_LPD_transactor->WLAST(maxigp2_wlast);
    mp_M_AXI_HPM0_LPD_transactor->WVALID(maxigp2_wvalid);
    mp_M_AXI_HPM0_LPD_transactor->WREADY(maxigp2_wready);
    mp_M_AXI_HPM0_LPD_transactor->BID(maxigp2_bid);
    mp_M_AXI_HPM0_LPD_transactor->BRESP(maxigp2_bresp);
    mp_M_AXI_HPM0_LPD_transactor->BVALID(maxigp2_bvalid);
    mp_M_AXI_HPM0_LPD_transactor->BREADY(maxigp2_bready);
    mp_M_AXI_HPM0_LPD_transactor->ARID(maxigp2_arid);
    mp_M_AXI_HPM0_LPD_transactor->ARADDR(maxigp2_araddr);
    mp_M_AXI_HPM0_LPD_transactor->ARLEN(maxigp2_arlen);
    mp_M_AXI_HPM0_LPD_transactor->ARSIZE(maxigp2_arsize);
    mp_M_AXI_HPM0_LPD_transactor->ARBURST(maxigp2_arburst);
    mp_M_AXI_HPM0_LPD_transactor->ARLOCK(maxigp2_arlock);
    mp_M_AXI_HPM0_LPD_transactor->ARCACHE(maxigp2_arcache);
    mp_M_AXI_HPM0_LPD_transactor->ARPROT(maxigp2_arprot);
    mp_M_AXI_HPM0_LPD_transactor->ARVALID(maxigp2_arvalid);
    mp_M_AXI_HPM0_LPD_transactor->ARUSER(maxigp2_aruser);
    mp_M_AXI_HPM0_LPD_transactor->ARREADY(maxigp2_arready);
    mp_M_AXI_HPM0_LPD_transactor->RID(maxigp2_rid);
    mp_M_AXI_HPM0_LPD_transactor->RDATA(maxigp2_rdata);
    mp_M_AXI_HPM0_LPD_transactor->RRESP(maxigp2_rresp);
    mp_M_AXI_HPM0_LPD_transactor->RLAST(maxigp2_rlast);
    mp_M_AXI_HPM0_LPD_transactor->RVALID(maxigp2_rvalid);
    mp_M_AXI_HPM0_LPD_transactor->RREADY(maxigp2_rready);
    mp_M_AXI_HPM0_LPD_transactor->AWQOS(maxigp2_awqos);
    mp_M_AXI_HPM0_LPD_transactor->ARQOS(maxigp2_arqos);
    mp_M_AXI_HPM0_LPD_transactor->CLK(maxihpm0_lpd_aclk);
    m_M_AXI_HPM0_LPD_transactor_rst_signal.write(1);
    mp_M_AXI_HPM0_LPD_transactor->RST(m_M_AXI_HPM0_LPD_transactor_rst_signal);

    // M_AXI_HPM0_LPD' transactor sockets

    mp_impl->M_AXI_HPM0_LPD_rd_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_impl->M_AXI_HPM0_LPD_wr_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
  }

  // configure 'S_AXI_LPD' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "S_AXI_LPD_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'S_AXI_LPD' transactor parameters
    xsc::common_cpp::properties S_AXI_LPD_transactor_param_props;
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("DATA_WIDTH", "32");
    S_AXI_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S_AXI_LPD_transactor_param_props.addLong("ID_WIDTH", "6");
    S_AXI_LPD_transactor_param_props.addLong("ADDR_WIDTH", "49");
    S_AXI_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    S_AXI_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    S_AXI_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    S_AXI_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    S_AXI_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S_AXI_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S_AXI_LPD_transactor = new xtlm::xaximm_pin2xtlm_t<32,49,6,1,1,1,1,1>("S_AXI_LPD_transactor", S_AXI_LPD_transactor_param_props);

    // S_AXI_LPD' transactor ports

    mp_saxigp6_aruser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_aruser_converter");
    mp_saxigp6_aruser_converter->scalar_in(saxigp6_aruser);
    mp_saxigp6_aruser_converter->vector_out(m_saxigp6_aruser_converter_signal);
    mp_S_AXI_LPD_transactor->ARUSER(m_saxigp6_aruser_converter_signal);
    mp_saxigp6_awuser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_awuser_converter");
    mp_saxigp6_awuser_converter->scalar_in(saxigp6_awuser);
    mp_saxigp6_awuser_converter->vector_out(m_saxigp6_awuser_converter_signal);
    mp_S_AXI_LPD_transactor->AWUSER(m_saxigp6_awuser_converter_signal);
    mp_S_AXI_LPD_transactor->AWID(saxigp6_awid);
    mp_S_AXI_LPD_transactor->AWADDR(saxigp6_awaddr);
    mp_S_AXI_LPD_transactor->AWLEN(saxigp6_awlen);
    mp_S_AXI_LPD_transactor->AWSIZE(saxigp6_awsize);
    mp_S_AXI_LPD_transactor->AWBURST(saxigp6_awburst);
    mp_S_AXI_LPD_transactor->AWLOCK(saxigp6_awlock);
    mp_S_AXI_LPD_transactor->AWCACHE(saxigp6_awcache);
    mp_S_AXI_LPD_transactor->AWPROT(saxigp6_awprot);
    mp_S_AXI_LPD_transactor->AWVALID(saxigp6_awvalid);
    mp_S_AXI_LPD_transactor->AWREADY(saxigp6_awready);
    mp_S_AXI_LPD_transactor->WDATA(saxigp6_wdata);
    mp_S_AXI_LPD_transactor->WSTRB(saxigp6_wstrb);
    mp_S_AXI_LPD_transactor->WLAST(saxigp6_wlast);
    mp_S_AXI_LPD_transactor->WVALID(saxigp6_wvalid);
    mp_S_AXI_LPD_transactor->WREADY(saxigp6_wready);
    mp_S_AXI_LPD_transactor->BID(saxigp6_bid);
    mp_S_AXI_LPD_transactor->BRESP(saxigp6_bresp);
    mp_S_AXI_LPD_transactor->BVALID(saxigp6_bvalid);
    mp_S_AXI_LPD_transactor->BREADY(saxigp6_bready);
    mp_S_AXI_LPD_transactor->ARID(saxigp6_arid);
    mp_S_AXI_LPD_transactor->ARADDR(saxigp6_araddr);
    mp_S_AXI_LPD_transactor->ARLEN(saxigp6_arlen);
    mp_S_AXI_LPD_transactor->ARSIZE(saxigp6_arsize);
    mp_S_AXI_LPD_transactor->ARBURST(saxigp6_arburst);
    mp_S_AXI_LPD_transactor->ARLOCK(saxigp6_arlock);
    mp_S_AXI_LPD_transactor->ARCACHE(saxigp6_arcache);
    mp_S_AXI_LPD_transactor->ARPROT(saxigp6_arprot);
    mp_S_AXI_LPD_transactor->ARVALID(saxigp6_arvalid);
    mp_S_AXI_LPD_transactor->ARREADY(saxigp6_arready);
    mp_S_AXI_LPD_transactor->RID(saxigp6_rid);
    mp_S_AXI_LPD_transactor->RDATA(saxigp6_rdata);
    mp_S_AXI_LPD_transactor->RRESP(saxigp6_rresp);
    mp_S_AXI_LPD_transactor->RLAST(saxigp6_rlast);
    mp_S_AXI_LPD_transactor->RVALID(saxigp6_rvalid);
    mp_S_AXI_LPD_transactor->RREADY(saxigp6_rready);
    mp_S_AXI_LPD_transactor->AWQOS(saxigp6_awqos);
    mp_S_AXI_LPD_transactor->ARQOS(saxigp6_arqos);
    mp_S_AXI_LPD_transactor->CLK(saxi_lpd_aclk);
    m_S_AXI_LPD_transactor_rst_signal.write(1);
    mp_S_AXI_LPD_transactor->RST(m_S_AXI_LPD_transactor_rst_signal);

    // S_AXI_LPD' transactor sockets

    mp_impl->S_AXI_LPD_rd_socket->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_impl->S_AXI_LPD_wr_socket->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
  }

}

#endif // XM_SYSTEMC




#ifdef RIVIERA
zusys_zynq_ultra_ps_e_0_0::zusys_zynq_ultra_ps_e_0_0(const sc_core::sc_module_name& nm) : zusys_zynq_ultra_ps_e_0_0_sc(nm), maxihpm0_lpd_aclk("maxihpm0_lpd_aclk"), maxigp2_awid("maxigp2_awid"), maxigp2_awaddr("maxigp2_awaddr"), maxigp2_awlen("maxigp2_awlen"), maxigp2_awsize("maxigp2_awsize"), maxigp2_awburst("maxigp2_awburst"), maxigp2_awlock("maxigp2_awlock"), maxigp2_awcache("maxigp2_awcache"), maxigp2_awprot("maxigp2_awprot"), maxigp2_awvalid("maxigp2_awvalid"), maxigp2_awuser("maxigp2_awuser"), maxigp2_awready("maxigp2_awready"), maxigp2_wdata("maxigp2_wdata"), maxigp2_wstrb("maxigp2_wstrb"), maxigp2_wlast("maxigp2_wlast"), maxigp2_wvalid("maxigp2_wvalid"), maxigp2_wready("maxigp2_wready"), maxigp2_bid("maxigp2_bid"), maxigp2_bresp("maxigp2_bresp"), maxigp2_bvalid("maxigp2_bvalid"), maxigp2_bready("maxigp2_bready"), maxigp2_arid("maxigp2_arid"), maxigp2_araddr("maxigp2_araddr"), maxigp2_arlen("maxigp2_arlen"), maxigp2_arsize("maxigp2_arsize"), maxigp2_arburst("maxigp2_arburst"), maxigp2_arlock("maxigp2_arlock"), maxigp2_arcache("maxigp2_arcache"), maxigp2_arprot("maxigp2_arprot"), maxigp2_arvalid("maxigp2_arvalid"), maxigp2_aruser("maxigp2_aruser"), maxigp2_arready("maxigp2_arready"), maxigp2_rid("maxigp2_rid"), maxigp2_rdata("maxigp2_rdata"), maxigp2_rresp("maxigp2_rresp"), maxigp2_rlast("maxigp2_rlast"), maxigp2_rvalid("maxigp2_rvalid"), maxigp2_rready("maxigp2_rready"), maxigp2_awqos("maxigp2_awqos"), maxigp2_arqos("maxigp2_arqos"), saxi_lpd_aclk("saxi_lpd_aclk"), saxigp6_aruser("saxigp6_aruser"), saxigp6_awuser("saxigp6_awuser"), saxigp6_awid("saxigp6_awid"), saxigp6_awaddr("saxigp6_awaddr"), saxigp6_awlen("saxigp6_awlen"), saxigp6_awsize("saxigp6_awsize"), saxigp6_awburst("saxigp6_awburst"), saxigp6_awlock("saxigp6_awlock"), saxigp6_awcache("saxigp6_awcache"), saxigp6_awprot("saxigp6_awprot"), saxigp6_awvalid("saxigp6_awvalid"), saxigp6_awready("saxigp6_awready"), saxigp6_wdata("saxigp6_wdata"), saxigp6_wstrb("saxigp6_wstrb"), saxigp6_wlast("saxigp6_wlast"), saxigp6_wvalid("saxigp6_wvalid"), saxigp6_wready("saxigp6_wready"), saxigp6_bid("saxigp6_bid"), saxigp6_bresp("saxigp6_bresp"), saxigp6_bvalid("saxigp6_bvalid"), saxigp6_bready("saxigp6_bready"), saxigp6_arid("saxigp6_arid"), saxigp6_araddr("saxigp6_araddr"), saxigp6_arlen("saxigp6_arlen"), saxigp6_arsize("saxigp6_arsize"), saxigp6_arburst("saxigp6_arburst"), saxigp6_arlock("saxigp6_arlock"), saxigp6_arcache("saxigp6_arcache"), saxigp6_arprot("saxigp6_arprot"), saxigp6_arvalid("saxigp6_arvalid"), saxigp6_arready("saxigp6_arready"), saxigp6_rid("saxigp6_rid"), saxigp6_rdata("saxigp6_rdata"), saxigp6_rresp("saxigp6_rresp"), saxigp6_rlast("saxigp6_rlast"), saxigp6_rvalid("saxigp6_rvalid"), saxigp6_rready("saxigp6_rready"), saxigp6_awqos("saxigp6_awqos"), saxigp6_arqos("saxigp6_arqos"), pl_ps_irq0("pl_ps_irq0"), pl_resetn0("pl_resetn0"), pl_clk0("pl_clk0")
{

  // initialize pins
  mp_impl->maxihpm0_lpd_aclk(maxihpm0_lpd_aclk);
  mp_impl->saxi_lpd_aclk(saxi_lpd_aclk);
  mp_impl->pl_ps_irq0(pl_ps_irq0);
  mp_impl->pl_resetn0(pl_resetn0);
  mp_impl->pl_clk0(pl_clk0);

  // initialize transactors
  mp_M_AXI_HPM0_LPD_transactor = NULL;
  mp_S_AXI_LPD_transactor = NULL;
  mp_saxigp6_aruser_converter = NULL;
  mp_saxigp6_awuser_converter = NULL;

  // initialize socket stubs

}

void zusys_zynq_ultra_ps_e_0_0::before_end_of_elaboration()
{
  // configure 'M_AXI_HPM0_LPD' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "M_AXI_HPM0_LPD_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'M_AXI_HPM0_LPD' transactor parameters
    xsc::common_cpp::properties M_AXI_HPM0_LPD_transactor_param_props;
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("DATA_WIDTH", "128");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ID_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    M_AXI_HPM0_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    M_AXI_HPM0_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M_AXI_HPM0_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M_AXI_HPM0_LPD_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,16,16,1,1,16,1>("M_AXI_HPM0_LPD_transactor", M_AXI_HPM0_LPD_transactor_param_props);

    // M_AXI_HPM0_LPD' transactor ports

    mp_M_AXI_HPM0_LPD_transactor->AWID(maxigp2_awid);
    mp_M_AXI_HPM0_LPD_transactor->AWADDR(maxigp2_awaddr);
    mp_M_AXI_HPM0_LPD_transactor->AWLEN(maxigp2_awlen);
    mp_M_AXI_HPM0_LPD_transactor->AWSIZE(maxigp2_awsize);
    mp_M_AXI_HPM0_LPD_transactor->AWBURST(maxigp2_awburst);
    mp_M_AXI_HPM0_LPD_transactor->AWLOCK(maxigp2_awlock);
    mp_M_AXI_HPM0_LPD_transactor->AWCACHE(maxigp2_awcache);
    mp_M_AXI_HPM0_LPD_transactor->AWPROT(maxigp2_awprot);
    mp_M_AXI_HPM0_LPD_transactor->AWVALID(maxigp2_awvalid);
    mp_M_AXI_HPM0_LPD_transactor->AWUSER(maxigp2_awuser);
    mp_M_AXI_HPM0_LPD_transactor->AWREADY(maxigp2_awready);
    mp_M_AXI_HPM0_LPD_transactor->WDATA(maxigp2_wdata);
    mp_M_AXI_HPM0_LPD_transactor->WSTRB(maxigp2_wstrb);
    mp_M_AXI_HPM0_LPD_transactor->WLAST(maxigp2_wlast);
    mp_M_AXI_HPM0_LPD_transactor->WVALID(maxigp2_wvalid);
    mp_M_AXI_HPM0_LPD_transactor->WREADY(maxigp2_wready);
    mp_M_AXI_HPM0_LPD_transactor->BID(maxigp2_bid);
    mp_M_AXI_HPM0_LPD_transactor->BRESP(maxigp2_bresp);
    mp_M_AXI_HPM0_LPD_transactor->BVALID(maxigp2_bvalid);
    mp_M_AXI_HPM0_LPD_transactor->BREADY(maxigp2_bready);
    mp_M_AXI_HPM0_LPD_transactor->ARID(maxigp2_arid);
    mp_M_AXI_HPM0_LPD_transactor->ARADDR(maxigp2_araddr);
    mp_M_AXI_HPM0_LPD_transactor->ARLEN(maxigp2_arlen);
    mp_M_AXI_HPM0_LPD_transactor->ARSIZE(maxigp2_arsize);
    mp_M_AXI_HPM0_LPD_transactor->ARBURST(maxigp2_arburst);
    mp_M_AXI_HPM0_LPD_transactor->ARLOCK(maxigp2_arlock);
    mp_M_AXI_HPM0_LPD_transactor->ARCACHE(maxigp2_arcache);
    mp_M_AXI_HPM0_LPD_transactor->ARPROT(maxigp2_arprot);
    mp_M_AXI_HPM0_LPD_transactor->ARVALID(maxigp2_arvalid);
    mp_M_AXI_HPM0_LPD_transactor->ARUSER(maxigp2_aruser);
    mp_M_AXI_HPM0_LPD_transactor->ARREADY(maxigp2_arready);
    mp_M_AXI_HPM0_LPD_transactor->RID(maxigp2_rid);
    mp_M_AXI_HPM0_LPD_transactor->RDATA(maxigp2_rdata);
    mp_M_AXI_HPM0_LPD_transactor->RRESP(maxigp2_rresp);
    mp_M_AXI_HPM0_LPD_transactor->RLAST(maxigp2_rlast);
    mp_M_AXI_HPM0_LPD_transactor->RVALID(maxigp2_rvalid);
    mp_M_AXI_HPM0_LPD_transactor->RREADY(maxigp2_rready);
    mp_M_AXI_HPM0_LPD_transactor->AWQOS(maxigp2_awqos);
    mp_M_AXI_HPM0_LPD_transactor->ARQOS(maxigp2_arqos);
    mp_M_AXI_HPM0_LPD_transactor->CLK(maxihpm0_lpd_aclk);
    m_M_AXI_HPM0_LPD_transactor_rst_signal.write(1);
    mp_M_AXI_HPM0_LPD_transactor->RST(m_M_AXI_HPM0_LPD_transactor_rst_signal);

    // M_AXI_HPM0_LPD' transactor sockets

    mp_impl->M_AXI_HPM0_LPD_rd_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_impl->M_AXI_HPM0_LPD_wr_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
  }

  // configure 'S_AXI_LPD' transactor

  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "S_AXI_LPD_TLM_MODE") != 1)
  {
    // Instantiate Socket Stubs

  // 'S_AXI_LPD' transactor parameters
    xsc::common_cpp::properties S_AXI_LPD_transactor_param_props;
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("DATA_WIDTH", "32");
    S_AXI_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S_AXI_LPD_transactor_param_props.addLong("ID_WIDTH", "6");
    S_AXI_LPD_transactor_param_props.addLong("ADDR_WIDTH", "49");
    S_AXI_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    S_AXI_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    S_AXI_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    S_AXI_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    S_AXI_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S_AXI_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S_AXI_LPD_transactor = new xtlm::xaximm_pin2xtlm_t<32,49,6,1,1,1,1,1>("S_AXI_LPD_transactor", S_AXI_LPD_transactor_param_props);

    // S_AXI_LPD' transactor ports

    mp_saxigp6_aruser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_aruser_converter");
    mp_saxigp6_aruser_converter->scalar_in(saxigp6_aruser);
    mp_saxigp6_aruser_converter->vector_out(m_saxigp6_aruser_converter_signal);
    mp_S_AXI_LPD_transactor->ARUSER(m_saxigp6_aruser_converter_signal);
    mp_saxigp6_awuser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_awuser_converter");
    mp_saxigp6_awuser_converter->scalar_in(saxigp6_awuser);
    mp_saxigp6_awuser_converter->vector_out(m_saxigp6_awuser_converter_signal);
    mp_S_AXI_LPD_transactor->AWUSER(m_saxigp6_awuser_converter_signal);
    mp_S_AXI_LPD_transactor->AWID(saxigp6_awid);
    mp_S_AXI_LPD_transactor->AWADDR(saxigp6_awaddr);
    mp_S_AXI_LPD_transactor->AWLEN(saxigp6_awlen);
    mp_S_AXI_LPD_transactor->AWSIZE(saxigp6_awsize);
    mp_S_AXI_LPD_transactor->AWBURST(saxigp6_awburst);
    mp_S_AXI_LPD_transactor->AWLOCK(saxigp6_awlock);
    mp_S_AXI_LPD_transactor->AWCACHE(saxigp6_awcache);
    mp_S_AXI_LPD_transactor->AWPROT(saxigp6_awprot);
    mp_S_AXI_LPD_transactor->AWVALID(saxigp6_awvalid);
    mp_S_AXI_LPD_transactor->AWREADY(saxigp6_awready);
    mp_S_AXI_LPD_transactor->WDATA(saxigp6_wdata);
    mp_S_AXI_LPD_transactor->WSTRB(saxigp6_wstrb);
    mp_S_AXI_LPD_transactor->WLAST(saxigp6_wlast);
    mp_S_AXI_LPD_transactor->WVALID(saxigp6_wvalid);
    mp_S_AXI_LPD_transactor->WREADY(saxigp6_wready);
    mp_S_AXI_LPD_transactor->BID(saxigp6_bid);
    mp_S_AXI_LPD_transactor->BRESP(saxigp6_bresp);
    mp_S_AXI_LPD_transactor->BVALID(saxigp6_bvalid);
    mp_S_AXI_LPD_transactor->BREADY(saxigp6_bready);
    mp_S_AXI_LPD_transactor->ARID(saxigp6_arid);
    mp_S_AXI_LPD_transactor->ARADDR(saxigp6_araddr);
    mp_S_AXI_LPD_transactor->ARLEN(saxigp6_arlen);
    mp_S_AXI_LPD_transactor->ARSIZE(saxigp6_arsize);
    mp_S_AXI_LPD_transactor->ARBURST(saxigp6_arburst);
    mp_S_AXI_LPD_transactor->ARLOCK(saxigp6_arlock);
    mp_S_AXI_LPD_transactor->ARCACHE(saxigp6_arcache);
    mp_S_AXI_LPD_transactor->ARPROT(saxigp6_arprot);
    mp_S_AXI_LPD_transactor->ARVALID(saxigp6_arvalid);
    mp_S_AXI_LPD_transactor->ARREADY(saxigp6_arready);
    mp_S_AXI_LPD_transactor->RID(saxigp6_rid);
    mp_S_AXI_LPD_transactor->RDATA(saxigp6_rdata);
    mp_S_AXI_LPD_transactor->RRESP(saxigp6_rresp);
    mp_S_AXI_LPD_transactor->RLAST(saxigp6_rlast);
    mp_S_AXI_LPD_transactor->RVALID(saxigp6_rvalid);
    mp_S_AXI_LPD_transactor->RREADY(saxigp6_rready);
    mp_S_AXI_LPD_transactor->AWQOS(saxigp6_awqos);
    mp_S_AXI_LPD_transactor->ARQOS(saxigp6_arqos);
    mp_S_AXI_LPD_transactor->CLK(saxi_lpd_aclk);
    m_S_AXI_LPD_transactor_rst_signal.write(1);
    mp_S_AXI_LPD_transactor->RST(m_S_AXI_LPD_transactor_rst_signal);

    // S_AXI_LPD' transactor sockets

    mp_impl->S_AXI_LPD_rd_socket->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_impl->S_AXI_LPD_wr_socket->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
  }

}

#endif // RIVIERA




#ifdef VCSSYSTEMC
zusys_zynq_ultra_ps_e_0_0::zusys_zynq_ultra_ps_e_0_0(const sc_core::sc_module_name& nm) : zusys_zynq_ultra_ps_e_0_0_sc(nm),  maxihpm0_lpd_aclk("maxihpm0_lpd_aclk"), maxigp2_awid("maxigp2_awid"), maxigp2_awaddr("maxigp2_awaddr"), maxigp2_awlen("maxigp2_awlen"), maxigp2_awsize("maxigp2_awsize"), maxigp2_awburst("maxigp2_awburst"), maxigp2_awlock("maxigp2_awlock"), maxigp2_awcache("maxigp2_awcache"), maxigp2_awprot("maxigp2_awprot"), maxigp2_awvalid("maxigp2_awvalid"), maxigp2_awuser("maxigp2_awuser"), maxigp2_awready("maxigp2_awready"), maxigp2_wdata("maxigp2_wdata"), maxigp2_wstrb("maxigp2_wstrb"), maxigp2_wlast("maxigp2_wlast"), maxigp2_wvalid("maxigp2_wvalid"), maxigp2_wready("maxigp2_wready"), maxigp2_bid("maxigp2_bid"), maxigp2_bresp("maxigp2_bresp"), maxigp2_bvalid("maxigp2_bvalid"), maxigp2_bready("maxigp2_bready"), maxigp2_arid("maxigp2_arid"), maxigp2_araddr("maxigp2_araddr"), maxigp2_arlen("maxigp2_arlen"), maxigp2_arsize("maxigp2_arsize"), maxigp2_arburst("maxigp2_arburst"), maxigp2_arlock("maxigp2_arlock"), maxigp2_arcache("maxigp2_arcache"), maxigp2_arprot("maxigp2_arprot"), maxigp2_arvalid("maxigp2_arvalid"), maxigp2_aruser("maxigp2_aruser"), maxigp2_arready("maxigp2_arready"), maxigp2_rid("maxigp2_rid"), maxigp2_rdata("maxigp2_rdata"), maxigp2_rresp("maxigp2_rresp"), maxigp2_rlast("maxigp2_rlast"), maxigp2_rvalid("maxigp2_rvalid"), maxigp2_rready("maxigp2_rready"), maxigp2_awqos("maxigp2_awqos"), maxigp2_arqos("maxigp2_arqos"), saxi_lpd_aclk("saxi_lpd_aclk"), saxigp6_aruser("saxigp6_aruser"), saxigp6_awuser("saxigp6_awuser"), saxigp6_awid("saxigp6_awid"), saxigp6_awaddr("saxigp6_awaddr"), saxigp6_awlen("saxigp6_awlen"), saxigp6_awsize("saxigp6_awsize"), saxigp6_awburst("saxigp6_awburst"), saxigp6_awlock("saxigp6_awlock"), saxigp6_awcache("saxigp6_awcache"), saxigp6_awprot("saxigp6_awprot"), saxigp6_awvalid("saxigp6_awvalid"), saxigp6_awready("saxigp6_awready"), saxigp6_wdata("saxigp6_wdata"), saxigp6_wstrb("saxigp6_wstrb"), saxigp6_wlast("saxigp6_wlast"), saxigp6_wvalid("saxigp6_wvalid"), saxigp6_wready("saxigp6_wready"), saxigp6_bid("saxigp6_bid"), saxigp6_bresp("saxigp6_bresp"), saxigp6_bvalid("saxigp6_bvalid"), saxigp6_bready("saxigp6_bready"), saxigp6_arid("saxigp6_arid"), saxigp6_araddr("saxigp6_araddr"), saxigp6_arlen("saxigp6_arlen"), saxigp6_arsize("saxigp6_arsize"), saxigp6_arburst("saxigp6_arburst"), saxigp6_arlock("saxigp6_arlock"), saxigp6_arcache("saxigp6_arcache"), saxigp6_arprot("saxigp6_arprot"), saxigp6_arvalid("saxigp6_arvalid"), saxigp6_arready("saxigp6_arready"), saxigp6_rid("saxigp6_rid"), saxigp6_rdata("saxigp6_rdata"), saxigp6_rresp("saxigp6_rresp"), saxigp6_rlast("saxigp6_rlast"), saxigp6_rvalid("saxigp6_rvalid"), saxigp6_rready("saxigp6_rready"), saxigp6_awqos("saxigp6_awqos"), saxigp6_arqos("saxigp6_arqos"), pl_ps_irq0("pl_ps_irq0"), pl_resetn0("pl_resetn0"), pl_clk0("pl_clk0")
{
  // initialize pins
  mp_impl->maxihpm0_lpd_aclk(maxihpm0_lpd_aclk);
  mp_impl->saxi_lpd_aclk(saxi_lpd_aclk);
  mp_impl->pl_ps_irq0(pl_ps_irq0);
  mp_impl->pl_resetn0(pl_resetn0);
  mp_impl->pl_clk0(pl_clk0);

  // initialize transactors
  mp_M_AXI_HPM0_LPD_transactor = NULL;
  mp_S_AXI_LPD_transactor = NULL;
  mp_saxigp6_aruser_converter = NULL;
  mp_saxigp6_awuser_converter = NULL;
  // Instantiate Socket Stubs

  // configure M_AXI_HPM0_LPD_transactor
    xsc::common_cpp::properties M_AXI_HPM0_LPD_transactor_param_props;
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("DATA_WIDTH", "128");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ID_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    M_AXI_HPM0_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    M_AXI_HPM0_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M_AXI_HPM0_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M_AXI_HPM0_LPD_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,16,16,1,1,16,1>("M_AXI_HPM0_LPD_transactor", M_AXI_HPM0_LPD_transactor_param_props);
  mp_M_AXI_HPM0_LPD_transactor->AWID(maxigp2_awid);
  mp_M_AXI_HPM0_LPD_transactor->AWADDR(maxigp2_awaddr);
  mp_M_AXI_HPM0_LPD_transactor->AWLEN(maxigp2_awlen);
  mp_M_AXI_HPM0_LPD_transactor->AWSIZE(maxigp2_awsize);
  mp_M_AXI_HPM0_LPD_transactor->AWBURST(maxigp2_awburst);
  mp_M_AXI_HPM0_LPD_transactor->AWLOCK(maxigp2_awlock);
  mp_M_AXI_HPM0_LPD_transactor->AWCACHE(maxigp2_awcache);
  mp_M_AXI_HPM0_LPD_transactor->AWPROT(maxigp2_awprot);
  mp_M_AXI_HPM0_LPD_transactor->AWVALID(maxigp2_awvalid);
  mp_M_AXI_HPM0_LPD_transactor->AWUSER(maxigp2_awuser);
  mp_M_AXI_HPM0_LPD_transactor->AWREADY(maxigp2_awready);
  mp_M_AXI_HPM0_LPD_transactor->WDATA(maxigp2_wdata);
  mp_M_AXI_HPM0_LPD_transactor->WSTRB(maxigp2_wstrb);
  mp_M_AXI_HPM0_LPD_transactor->WLAST(maxigp2_wlast);
  mp_M_AXI_HPM0_LPD_transactor->WVALID(maxigp2_wvalid);
  mp_M_AXI_HPM0_LPD_transactor->WREADY(maxigp2_wready);
  mp_M_AXI_HPM0_LPD_transactor->BID(maxigp2_bid);
  mp_M_AXI_HPM0_LPD_transactor->BRESP(maxigp2_bresp);
  mp_M_AXI_HPM0_LPD_transactor->BVALID(maxigp2_bvalid);
  mp_M_AXI_HPM0_LPD_transactor->BREADY(maxigp2_bready);
  mp_M_AXI_HPM0_LPD_transactor->ARID(maxigp2_arid);
  mp_M_AXI_HPM0_LPD_transactor->ARADDR(maxigp2_araddr);
  mp_M_AXI_HPM0_LPD_transactor->ARLEN(maxigp2_arlen);
  mp_M_AXI_HPM0_LPD_transactor->ARSIZE(maxigp2_arsize);
  mp_M_AXI_HPM0_LPD_transactor->ARBURST(maxigp2_arburst);
  mp_M_AXI_HPM0_LPD_transactor->ARLOCK(maxigp2_arlock);
  mp_M_AXI_HPM0_LPD_transactor->ARCACHE(maxigp2_arcache);
  mp_M_AXI_HPM0_LPD_transactor->ARPROT(maxigp2_arprot);
  mp_M_AXI_HPM0_LPD_transactor->ARVALID(maxigp2_arvalid);
  mp_M_AXI_HPM0_LPD_transactor->ARUSER(maxigp2_aruser);
  mp_M_AXI_HPM0_LPD_transactor->ARREADY(maxigp2_arready);
  mp_M_AXI_HPM0_LPD_transactor->RID(maxigp2_rid);
  mp_M_AXI_HPM0_LPD_transactor->RDATA(maxigp2_rdata);
  mp_M_AXI_HPM0_LPD_transactor->RRESP(maxigp2_rresp);
  mp_M_AXI_HPM0_LPD_transactor->RLAST(maxigp2_rlast);
  mp_M_AXI_HPM0_LPD_transactor->RVALID(maxigp2_rvalid);
  mp_M_AXI_HPM0_LPD_transactor->RREADY(maxigp2_rready);
  mp_M_AXI_HPM0_LPD_transactor->AWQOS(maxigp2_awqos);
  mp_M_AXI_HPM0_LPD_transactor->ARQOS(maxigp2_arqos);
  mp_M_AXI_HPM0_LPD_transactor->CLK(maxihpm0_lpd_aclk);
  m_M_AXI_HPM0_LPD_transactor_rst_signal.write(1);
  mp_M_AXI_HPM0_LPD_transactor->RST(m_M_AXI_HPM0_LPD_transactor_rst_signal);

  // configure S_AXI_LPD_transactor
    xsc::common_cpp::properties S_AXI_LPD_transactor_param_props;
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("DATA_WIDTH", "32");
    S_AXI_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S_AXI_LPD_transactor_param_props.addLong("ID_WIDTH", "6");
    S_AXI_LPD_transactor_param_props.addLong("ADDR_WIDTH", "49");
    S_AXI_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    S_AXI_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    S_AXI_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    S_AXI_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    S_AXI_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S_AXI_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S_AXI_LPD_transactor = new xtlm::xaximm_pin2xtlm_t<32,49,6,1,1,1,1,1>("S_AXI_LPD_transactor", S_AXI_LPD_transactor_param_props);
  mp_saxigp6_aruser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_aruser_converter");
  mp_saxigp6_aruser_converter->scalar_in(saxigp6_aruser);
  mp_saxigp6_aruser_converter->vector_out(m_saxigp6_aruser_converter_signal);
  mp_S_AXI_LPD_transactor->ARUSER(m_saxigp6_aruser_converter_signal);
  mp_saxigp6_awuser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_awuser_converter");
  mp_saxigp6_awuser_converter->scalar_in(saxigp6_awuser);
  mp_saxigp6_awuser_converter->vector_out(m_saxigp6_awuser_converter_signal);
  mp_S_AXI_LPD_transactor->AWUSER(m_saxigp6_awuser_converter_signal);
  mp_S_AXI_LPD_transactor->AWID(saxigp6_awid);
  mp_S_AXI_LPD_transactor->AWADDR(saxigp6_awaddr);
  mp_S_AXI_LPD_transactor->AWLEN(saxigp6_awlen);
  mp_S_AXI_LPD_transactor->AWSIZE(saxigp6_awsize);
  mp_S_AXI_LPD_transactor->AWBURST(saxigp6_awburst);
  mp_S_AXI_LPD_transactor->AWLOCK(saxigp6_awlock);
  mp_S_AXI_LPD_transactor->AWCACHE(saxigp6_awcache);
  mp_S_AXI_LPD_transactor->AWPROT(saxigp6_awprot);
  mp_S_AXI_LPD_transactor->AWVALID(saxigp6_awvalid);
  mp_S_AXI_LPD_transactor->AWREADY(saxigp6_awready);
  mp_S_AXI_LPD_transactor->WDATA(saxigp6_wdata);
  mp_S_AXI_LPD_transactor->WSTRB(saxigp6_wstrb);
  mp_S_AXI_LPD_transactor->WLAST(saxigp6_wlast);
  mp_S_AXI_LPD_transactor->WVALID(saxigp6_wvalid);
  mp_S_AXI_LPD_transactor->WREADY(saxigp6_wready);
  mp_S_AXI_LPD_transactor->BID(saxigp6_bid);
  mp_S_AXI_LPD_transactor->BRESP(saxigp6_bresp);
  mp_S_AXI_LPD_transactor->BVALID(saxigp6_bvalid);
  mp_S_AXI_LPD_transactor->BREADY(saxigp6_bready);
  mp_S_AXI_LPD_transactor->ARID(saxigp6_arid);
  mp_S_AXI_LPD_transactor->ARADDR(saxigp6_araddr);
  mp_S_AXI_LPD_transactor->ARLEN(saxigp6_arlen);
  mp_S_AXI_LPD_transactor->ARSIZE(saxigp6_arsize);
  mp_S_AXI_LPD_transactor->ARBURST(saxigp6_arburst);
  mp_S_AXI_LPD_transactor->ARLOCK(saxigp6_arlock);
  mp_S_AXI_LPD_transactor->ARCACHE(saxigp6_arcache);
  mp_S_AXI_LPD_transactor->ARPROT(saxigp6_arprot);
  mp_S_AXI_LPD_transactor->ARVALID(saxigp6_arvalid);
  mp_S_AXI_LPD_transactor->ARREADY(saxigp6_arready);
  mp_S_AXI_LPD_transactor->RID(saxigp6_rid);
  mp_S_AXI_LPD_transactor->RDATA(saxigp6_rdata);
  mp_S_AXI_LPD_transactor->RRESP(saxigp6_rresp);
  mp_S_AXI_LPD_transactor->RLAST(saxigp6_rlast);
  mp_S_AXI_LPD_transactor->RVALID(saxigp6_rvalid);
  mp_S_AXI_LPD_transactor->RREADY(saxigp6_rready);
  mp_S_AXI_LPD_transactor->AWQOS(saxigp6_awqos);
  mp_S_AXI_LPD_transactor->ARQOS(saxigp6_arqos);
  mp_S_AXI_LPD_transactor->CLK(saxi_lpd_aclk);
  m_S_AXI_LPD_transactor_rst_signal.write(1);
  mp_S_AXI_LPD_transactor->RST(m_S_AXI_LPD_transactor_rst_signal);


  // initialize transactors stubs
  M_AXI_HPM0_LPD_transactor_initiator_wr_socket_stub = nullptr;
  M_AXI_HPM0_LPD_transactor_initiator_rd_socket_stub = nullptr;
  S_AXI_LPD_transactor_target_wr_socket_stub = nullptr;
  S_AXI_LPD_transactor_target_rd_socket_stub = nullptr;

}

void zusys_zynq_ultra_ps_e_0_0::before_end_of_elaboration()
{
  // configure 'M_AXI_HPM0_LPD' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "M_AXI_HPM0_LPD_TLM_MODE") != 1)
  {
    mp_impl->M_AXI_HPM0_LPD_rd_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_impl->M_AXI_HPM0_LPD_wr_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
  }
  else
  {
    M_AXI_HPM0_LPD_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M_AXI_HPM0_LPD_transactor_initiator_wr_socket_stub->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
    M_AXI_HPM0_LPD_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M_AXI_HPM0_LPD_transactor_initiator_rd_socket_stub->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_M_AXI_HPM0_LPD_transactor->disable_transactor();
  }

  // configure 'S_AXI_LPD' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "S_AXI_LPD_TLM_MODE") != 1)
  {
    mp_impl->S_AXI_LPD_rd_socket->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_impl->S_AXI_LPD_wr_socket->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
  }
  else
  {
    S_AXI_LPD_transactor_target_wr_socket_stub = new xtlm::xtlm_aximm_target_stub("wr_socket",0);
    S_AXI_LPD_transactor_target_wr_socket_stub->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
    S_AXI_LPD_transactor_target_rd_socket_stub = new xtlm::xtlm_aximm_target_stub("rd_socket",0);
    S_AXI_LPD_transactor_target_rd_socket_stub->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_S_AXI_LPD_transactor->disable_transactor();
  }

}

#endif // VCSSYSTEMC




#ifdef MTI_SYSTEMC
zusys_zynq_ultra_ps_e_0_0::zusys_zynq_ultra_ps_e_0_0(const sc_core::sc_module_name& nm) : zusys_zynq_ultra_ps_e_0_0_sc(nm),  maxihpm0_lpd_aclk("maxihpm0_lpd_aclk"), maxigp2_awid("maxigp2_awid"), maxigp2_awaddr("maxigp2_awaddr"), maxigp2_awlen("maxigp2_awlen"), maxigp2_awsize("maxigp2_awsize"), maxigp2_awburst("maxigp2_awburst"), maxigp2_awlock("maxigp2_awlock"), maxigp2_awcache("maxigp2_awcache"), maxigp2_awprot("maxigp2_awprot"), maxigp2_awvalid("maxigp2_awvalid"), maxigp2_awuser("maxigp2_awuser"), maxigp2_awready("maxigp2_awready"), maxigp2_wdata("maxigp2_wdata"), maxigp2_wstrb("maxigp2_wstrb"), maxigp2_wlast("maxigp2_wlast"), maxigp2_wvalid("maxigp2_wvalid"), maxigp2_wready("maxigp2_wready"), maxigp2_bid("maxigp2_bid"), maxigp2_bresp("maxigp2_bresp"), maxigp2_bvalid("maxigp2_bvalid"), maxigp2_bready("maxigp2_bready"), maxigp2_arid("maxigp2_arid"), maxigp2_araddr("maxigp2_araddr"), maxigp2_arlen("maxigp2_arlen"), maxigp2_arsize("maxigp2_arsize"), maxigp2_arburst("maxigp2_arburst"), maxigp2_arlock("maxigp2_arlock"), maxigp2_arcache("maxigp2_arcache"), maxigp2_arprot("maxigp2_arprot"), maxigp2_arvalid("maxigp2_arvalid"), maxigp2_aruser("maxigp2_aruser"), maxigp2_arready("maxigp2_arready"), maxigp2_rid("maxigp2_rid"), maxigp2_rdata("maxigp2_rdata"), maxigp2_rresp("maxigp2_rresp"), maxigp2_rlast("maxigp2_rlast"), maxigp2_rvalid("maxigp2_rvalid"), maxigp2_rready("maxigp2_rready"), maxigp2_awqos("maxigp2_awqos"), maxigp2_arqos("maxigp2_arqos"), saxi_lpd_aclk("saxi_lpd_aclk"), saxigp6_aruser("saxigp6_aruser"), saxigp6_awuser("saxigp6_awuser"), saxigp6_awid("saxigp6_awid"), saxigp6_awaddr("saxigp6_awaddr"), saxigp6_awlen("saxigp6_awlen"), saxigp6_awsize("saxigp6_awsize"), saxigp6_awburst("saxigp6_awburst"), saxigp6_awlock("saxigp6_awlock"), saxigp6_awcache("saxigp6_awcache"), saxigp6_awprot("saxigp6_awprot"), saxigp6_awvalid("saxigp6_awvalid"), saxigp6_awready("saxigp6_awready"), saxigp6_wdata("saxigp6_wdata"), saxigp6_wstrb("saxigp6_wstrb"), saxigp6_wlast("saxigp6_wlast"), saxigp6_wvalid("saxigp6_wvalid"), saxigp6_wready("saxigp6_wready"), saxigp6_bid("saxigp6_bid"), saxigp6_bresp("saxigp6_bresp"), saxigp6_bvalid("saxigp6_bvalid"), saxigp6_bready("saxigp6_bready"), saxigp6_arid("saxigp6_arid"), saxigp6_araddr("saxigp6_araddr"), saxigp6_arlen("saxigp6_arlen"), saxigp6_arsize("saxigp6_arsize"), saxigp6_arburst("saxigp6_arburst"), saxigp6_arlock("saxigp6_arlock"), saxigp6_arcache("saxigp6_arcache"), saxigp6_arprot("saxigp6_arprot"), saxigp6_arvalid("saxigp6_arvalid"), saxigp6_arready("saxigp6_arready"), saxigp6_rid("saxigp6_rid"), saxigp6_rdata("saxigp6_rdata"), saxigp6_rresp("saxigp6_rresp"), saxigp6_rlast("saxigp6_rlast"), saxigp6_rvalid("saxigp6_rvalid"), saxigp6_rready("saxigp6_rready"), saxigp6_awqos("saxigp6_awqos"), saxigp6_arqos("saxigp6_arqos"), pl_ps_irq0("pl_ps_irq0"), pl_resetn0("pl_resetn0"), pl_clk0("pl_clk0")
{
  // initialize pins
  mp_impl->maxihpm0_lpd_aclk(maxihpm0_lpd_aclk);
  mp_impl->saxi_lpd_aclk(saxi_lpd_aclk);
  mp_impl->pl_ps_irq0(pl_ps_irq0);
  mp_impl->pl_resetn0(pl_resetn0);
  mp_impl->pl_clk0(pl_clk0);

  // initialize transactors
  mp_M_AXI_HPM0_LPD_transactor = NULL;
  mp_S_AXI_LPD_transactor = NULL;
  mp_saxigp6_aruser_converter = NULL;
  mp_saxigp6_awuser_converter = NULL;
  // Instantiate Socket Stubs

  // configure M_AXI_HPM0_LPD_transactor
    xsc::common_cpp::properties M_AXI_HPM0_LPD_transactor_param_props;
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "8");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("DATA_WIDTH", "128");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ID_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ADDR_WIDTH", "40");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "16");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "4");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    M_AXI_HPM0_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    M_AXI_HPM0_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    M_AXI_HPM0_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    M_AXI_HPM0_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    M_AXI_HPM0_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_M_AXI_HPM0_LPD_transactor = new xtlm::xaximm_xtlm2pin_t<128,40,16,16,1,1,16,1>("M_AXI_HPM0_LPD_transactor", M_AXI_HPM0_LPD_transactor_param_props);
  mp_M_AXI_HPM0_LPD_transactor->AWID(maxigp2_awid);
  mp_M_AXI_HPM0_LPD_transactor->AWADDR(maxigp2_awaddr);
  mp_M_AXI_HPM0_LPD_transactor->AWLEN(maxigp2_awlen);
  mp_M_AXI_HPM0_LPD_transactor->AWSIZE(maxigp2_awsize);
  mp_M_AXI_HPM0_LPD_transactor->AWBURST(maxigp2_awburst);
  mp_M_AXI_HPM0_LPD_transactor->AWLOCK(maxigp2_awlock);
  mp_M_AXI_HPM0_LPD_transactor->AWCACHE(maxigp2_awcache);
  mp_M_AXI_HPM0_LPD_transactor->AWPROT(maxigp2_awprot);
  mp_M_AXI_HPM0_LPD_transactor->AWVALID(maxigp2_awvalid);
  mp_M_AXI_HPM0_LPD_transactor->AWUSER(maxigp2_awuser);
  mp_M_AXI_HPM0_LPD_transactor->AWREADY(maxigp2_awready);
  mp_M_AXI_HPM0_LPD_transactor->WDATA(maxigp2_wdata);
  mp_M_AXI_HPM0_LPD_transactor->WSTRB(maxigp2_wstrb);
  mp_M_AXI_HPM0_LPD_transactor->WLAST(maxigp2_wlast);
  mp_M_AXI_HPM0_LPD_transactor->WVALID(maxigp2_wvalid);
  mp_M_AXI_HPM0_LPD_transactor->WREADY(maxigp2_wready);
  mp_M_AXI_HPM0_LPD_transactor->BID(maxigp2_bid);
  mp_M_AXI_HPM0_LPD_transactor->BRESP(maxigp2_bresp);
  mp_M_AXI_HPM0_LPD_transactor->BVALID(maxigp2_bvalid);
  mp_M_AXI_HPM0_LPD_transactor->BREADY(maxigp2_bready);
  mp_M_AXI_HPM0_LPD_transactor->ARID(maxigp2_arid);
  mp_M_AXI_HPM0_LPD_transactor->ARADDR(maxigp2_araddr);
  mp_M_AXI_HPM0_LPD_transactor->ARLEN(maxigp2_arlen);
  mp_M_AXI_HPM0_LPD_transactor->ARSIZE(maxigp2_arsize);
  mp_M_AXI_HPM0_LPD_transactor->ARBURST(maxigp2_arburst);
  mp_M_AXI_HPM0_LPD_transactor->ARLOCK(maxigp2_arlock);
  mp_M_AXI_HPM0_LPD_transactor->ARCACHE(maxigp2_arcache);
  mp_M_AXI_HPM0_LPD_transactor->ARPROT(maxigp2_arprot);
  mp_M_AXI_HPM0_LPD_transactor->ARVALID(maxigp2_arvalid);
  mp_M_AXI_HPM0_LPD_transactor->ARUSER(maxigp2_aruser);
  mp_M_AXI_HPM0_LPD_transactor->ARREADY(maxigp2_arready);
  mp_M_AXI_HPM0_LPD_transactor->RID(maxigp2_rid);
  mp_M_AXI_HPM0_LPD_transactor->RDATA(maxigp2_rdata);
  mp_M_AXI_HPM0_LPD_transactor->RRESP(maxigp2_rresp);
  mp_M_AXI_HPM0_LPD_transactor->RLAST(maxigp2_rlast);
  mp_M_AXI_HPM0_LPD_transactor->RVALID(maxigp2_rvalid);
  mp_M_AXI_HPM0_LPD_transactor->RREADY(maxigp2_rready);
  mp_M_AXI_HPM0_LPD_transactor->AWQOS(maxigp2_awqos);
  mp_M_AXI_HPM0_LPD_transactor->ARQOS(maxigp2_arqos);
  mp_M_AXI_HPM0_LPD_transactor->CLK(maxihpm0_lpd_aclk);
  m_M_AXI_HPM0_LPD_transactor_rst_signal.write(1);
  mp_M_AXI_HPM0_LPD_transactor->RST(m_M_AXI_HPM0_LPD_transactor_rst_signal);

  // configure S_AXI_LPD_transactor
    xsc::common_cpp::properties S_AXI_LPD_transactor_param_props;
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_OUTSTANDING", "16");
    S_AXI_LPD_transactor_param_props.addLong("DATA_WIDTH", "32");
    S_AXI_LPD_transactor_param_props.addLong("FREQ_HZ", "100000000");
    S_AXI_LPD_transactor_param_props.addLong("ID_WIDTH", "6");
    S_AXI_LPD_transactor_param_props.addLong("ADDR_WIDTH", "49");
    S_AXI_LPD_transactor_param_props.addLong("AWUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("ARUSER_WIDTH", "1");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("BUSER_WIDTH", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BURST", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_LOCK", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_PROT", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_CACHE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_QOS", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_REGION", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_WSTRB", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_BRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RRESP", "1");
    S_AXI_LPD_transactor_param_props.addLong("SUPPORTS_NARROW_BURST", "0");
    S_AXI_LPD_transactor_param_props.addLong("MAX_BURST_LENGTH", "256");
    S_AXI_LPD_transactor_param_props.addLong("NUM_READ_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("NUM_WRITE_THREADS", "1");
    S_AXI_LPD_transactor_param_props.addLong("RUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("WUSER_BITS_PER_BYTE", "0");
    S_AXI_LPD_transactor_param_props.addLong("HAS_SIZE", "1");
    S_AXI_LPD_transactor_param_props.addLong("HAS_RESET", "0");
    S_AXI_LPD_transactor_param_props.addFloat("PHASE", "0.000");
    S_AXI_LPD_transactor_param_props.addString("PROTOCOL", "AXI4");
    S_AXI_LPD_transactor_param_props.addString("READ_WRITE_MODE", "READ_WRITE");
    S_AXI_LPD_transactor_param_props.addString("CLK_DOMAIN", "zusys_zynq_ultra_ps_e_0_0_pl_clk0");

    mp_S_AXI_LPD_transactor = new xtlm::xaximm_pin2xtlm_t<32,49,6,1,1,1,1,1>("S_AXI_LPD_transactor", S_AXI_LPD_transactor_param_props);
  mp_saxigp6_aruser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_aruser_converter");
  mp_saxigp6_aruser_converter->scalar_in(saxigp6_aruser);
  mp_saxigp6_aruser_converter->vector_out(m_saxigp6_aruser_converter_signal);
  mp_S_AXI_LPD_transactor->ARUSER(m_saxigp6_aruser_converter_signal);
  mp_saxigp6_awuser_converter = new xsc::common::scalar2vectorN_converter<1>("saxigp6_awuser_converter");
  mp_saxigp6_awuser_converter->scalar_in(saxigp6_awuser);
  mp_saxigp6_awuser_converter->vector_out(m_saxigp6_awuser_converter_signal);
  mp_S_AXI_LPD_transactor->AWUSER(m_saxigp6_awuser_converter_signal);
  mp_S_AXI_LPD_transactor->AWID(saxigp6_awid);
  mp_S_AXI_LPD_transactor->AWADDR(saxigp6_awaddr);
  mp_S_AXI_LPD_transactor->AWLEN(saxigp6_awlen);
  mp_S_AXI_LPD_transactor->AWSIZE(saxigp6_awsize);
  mp_S_AXI_LPD_transactor->AWBURST(saxigp6_awburst);
  mp_S_AXI_LPD_transactor->AWLOCK(saxigp6_awlock);
  mp_S_AXI_LPD_transactor->AWCACHE(saxigp6_awcache);
  mp_S_AXI_LPD_transactor->AWPROT(saxigp6_awprot);
  mp_S_AXI_LPD_transactor->AWVALID(saxigp6_awvalid);
  mp_S_AXI_LPD_transactor->AWREADY(saxigp6_awready);
  mp_S_AXI_LPD_transactor->WDATA(saxigp6_wdata);
  mp_S_AXI_LPD_transactor->WSTRB(saxigp6_wstrb);
  mp_S_AXI_LPD_transactor->WLAST(saxigp6_wlast);
  mp_S_AXI_LPD_transactor->WVALID(saxigp6_wvalid);
  mp_S_AXI_LPD_transactor->WREADY(saxigp6_wready);
  mp_S_AXI_LPD_transactor->BID(saxigp6_bid);
  mp_S_AXI_LPD_transactor->BRESP(saxigp6_bresp);
  mp_S_AXI_LPD_transactor->BVALID(saxigp6_bvalid);
  mp_S_AXI_LPD_transactor->BREADY(saxigp6_bready);
  mp_S_AXI_LPD_transactor->ARID(saxigp6_arid);
  mp_S_AXI_LPD_transactor->ARADDR(saxigp6_araddr);
  mp_S_AXI_LPD_transactor->ARLEN(saxigp6_arlen);
  mp_S_AXI_LPD_transactor->ARSIZE(saxigp6_arsize);
  mp_S_AXI_LPD_transactor->ARBURST(saxigp6_arburst);
  mp_S_AXI_LPD_transactor->ARLOCK(saxigp6_arlock);
  mp_S_AXI_LPD_transactor->ARCACHE(saxigp6_arcache);
  mp_S_AXI_LPD_transactor->ARPROT(saxigp6_arprot);
  mp_S_AXI_LPD_transactor->ARVALID(saxigp6_arvalid);
  mp_S_AXI_LPD_transactor->ARREADY(saxigp6_arready);
  mp_S_AXI_LPD_transactor->RID(saxigp6_rid);
  mp_S_AXI_LPD_transactor->RDATA(saxigp6_rdata);
  mp_S_AXI_LPD_transactor->RRESP(saxigp6_rresp);
  mp_S_AXI_LPD_transactor->RLAST(saxigp6_rlast);
  mp_S_AXI_LPD_transactor->RVALID(saxigp6_rvalid);
  mp_S_AXI_LPD_transactor->RREADY(saxigp6_rready);
  mp_S_AXI_LPD_transactor->AWQOS(saxigp6_awqos);
  mp_S_AXI_LPD_transactor->ARQOS(saxigp6_arqos);
  mp_S_AXI_LPD_transactor->CLK(saxi_lpd_aclk);
  m_S_AXI_LPD_transactor_rst_signal.write(1);
  mp_S_AXI_LPD_transactor->RST(m_S_AXI_LPD_transactor_rst_signal);


  // initialize transactors stubs
  M_AXI_HPM0_LPD_transactor_initiator_wr_socket_stub = nullptr;
  M_AXI_HPM0_LPD_transactor_initiator_rd_socket_stub = nullptr;
  S_AXI_LPD_transactor_target_wr_socket_stub = nullptr;
  S_AXI_LPD_transactor_target_rd_socket_stub = nullptr;

}

void zusys_zynq_ultra_ps_e_0_0::before_end_of_elaboration()
{
  // configure 'M_AXI_HPM0_LPD' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "M_AXI_HPM0_LPD_TLM_MODE") != 1)
  {
    mp_impl->M_AXI_HPM0_LPD_rd_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_impl->M_AXI_HPM0_LPD_wr_socket->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
  }
  else
  {
    M_AXI_HPM0_LPD_transactor_initiator_wr_socket_stub = new xtlm::xtlm_aximm_initiator_stub("wr_socket",0);
    M_AXI_HPM0_LPD_transactor_initiator_wr_socket_stub->bind(*(mp_M_AXI_HPM0_LPD_transactor->wr_socket));
    M_AXI_HPM0_LPD_transactor_initiator_rd_socket_stub = new xtlm::xtlm_aximm_initiator_stub("rd_socket",0);
    M_AXI_HPM0_LPD_transactor_initiator_rd_socket_stub->bind(*(mp_M_AXI_HPM0_LPD_transactor->rd_socket));
    mp_M_AXI_HPM0_LPD_transactor->disable_transactor();
  }

  // configure 'S_AXI_LPD' transactor
  if (xsc::utils::xsc_sim_manager::getInstanceParameterInt("zusys_zynq_ultra_ps_e_0_0", "S_AXI_LPD_TLM_MODE") != 1)
  {
    mp_impl->S_AXI_LPD_rd_socket->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_impl->S_AXI_LPD_wr_socket->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
  }
  else
  {
    S_AXI_LPD_transactor_target_wr_socket_stub = new xtlm::xtlm_aximm_target_stub("wr_socket",0);
    S_AXI_LPD_transactor_target_wr_socket_stub->bind(*(mp_S_AXI_LPD_transactor->wr_socket));
    S_AXI_LPD_transactor_target_rd_socket_stub = new xtlm::xtlm_aximm_target_stub("rd_socket",0);
    S_AXI_LPD_transactor_target_rd_socket_stub->bind(*(mp_S_AXI_LPD_transactor->rd_socket));
    mp_S_AXI_LPD_transactor->disable_transactor();
  }

}

#endif // MTI_SYSTEMC




zusys_zynq_ultra_ps_e_0_0::~zusys_zynq_ultra_ps_e_0_0()
{
  delete mp_M_AXI_HPM0_LPD_transactor;

  delete mp_S_AXI_LPD_transactor;
  delete mp_saxigp6_aruser_converter;
  delete mp_saxigp6_awuser_converter;

}

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(zusys_zynq_ultra_ps_e_0_0);
#endif

#ifdef XM_SYSTEMC
XMSC_MODULE_EXPORT(zusys_zynq_ultra_ps_e_0_0);
#endif

#ifdef RIVIERA
SC_MODULE_EXPORT(zusys_zynq_ultra_ps_e_0_0);
SC_REGISTER_BV(128);
#endif

