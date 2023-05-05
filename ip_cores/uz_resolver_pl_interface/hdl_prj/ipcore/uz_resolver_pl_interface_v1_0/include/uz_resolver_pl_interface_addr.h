/*
 * File Name:         hdl_prj\ipcore\uz_resolver_pl_interface_v1_0\include\uz_resolver_pl_interface_addr.h
 * Description:       C Header File
 * Created:           2023-04-19 20:07:07
*/

#ifndef UZ_RESOLVER_PL_INTERFACE_H_
#define UZ_RESOLVER_PL_INTERFACE_H_

#define  IPCore_Reset_uz_resolver_pl_interface                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_resolver_pl_interface                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_resolver_pl_interface              0x8  //contains unique IP timestamp (yymmddHHMM): 2304192007
#define  resolver_polepairs_AXI_Data_uz_resolver_pl_interface   0x100  //data register for Inport resolver_polepairs_AXI
#define  cnt_reset_AXI_Data_uz_resolver_pl_interface            0x104  //data register for Inport cnt_reset_AXI
#define  position_intmax_AXI_Data_uz_resolver_pl_interface      0x108  //data register for Inport position_intmax_AXI
#define  machine_polepairs_AXI_Data_uz_resolver_pl_interface    0x10C  //data register for Inport machine_polepairs_AXI
#define  bitToRPS_Factor_AXI_Data_uz_resolver_pl_interface      0x110  //data register for Inport bitToRPS_Factor_AXI
#define  theta_m_offset_rad_AXI_Data_uz_resolver_pl_interface   0x114  //data register for Inport theta_m_offset_rad_AXI
#define  position_mech_2pi_AXI_Data_uz_resolver_pl_interface    0x118  //data register for Outport position_mech_2pi_AXI
#define  position_el_2pi_AXI_Data_uz_resolver_pl_interface      0x11C  //data register for Outport position_el_2pi_AXI
#define  omega_mech_rad_s_AXI_Data_uz_resolver_pl_interface     0x120  //data register for Outport omega_mech_rad_s_AXI
#define  cnt_AXI_Data_uz_resolver_pl_interface                  0x124  //data register for Outport cnt_AXI
#define  n_mech_rpm_AXI_Data_uz_resolver_pl_interface           0x128  //data register for Outport n_mech_rpm_AXI

#endif /* UZ_RESOLVER_PL_INTERFACE_H_ */
