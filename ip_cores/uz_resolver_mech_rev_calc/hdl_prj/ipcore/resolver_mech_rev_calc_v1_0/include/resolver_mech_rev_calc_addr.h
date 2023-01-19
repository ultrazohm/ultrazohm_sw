/*
 * File Name:         hdl_prj\ipcore\resolver_mech_rev_calc_v1_0\include\resolver_mech_rev_calc_addr.h
 * Description:       C Header File
 * Created:           2023-01-19 09:09:39
*/

#ifndef RESOLVER_MECH_REV_CALC_H_
#define RESOLVER_MECH_REV_CALC_H_

#define  IPCore_Reset_resolver_mech_rev_calc                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_resolver_mech_rev_calc                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_resolver_mech_rev_calc              0x8  //contains unique IP timestamp (yymmddHHMM): 2301190909
#define  resolver_polepairs_AXI_Data_resolver_mech_rev_calc   0x100  //data register for Inport resolver_polepairs_AXI
#define  cnt_reset_AXI_Data_resolver_mech_rev_calc            0x104  //data register for Inport cnt_reset_AXI
#define  position_intmax_AXI_Data_resolver_mech_rev_calc      0x108  //data register for Inport position_intmax_AXI
#define  machine_polepairs_AXI_Data_resolver_mech_rev_calc    0x10C  //data register for Inport machine_polepairs_AXI
#define  bitToRPS_Factor_AXI_Data_resolver_mech_rev_calc      0x110  //data register for Inport bitToRPS_Factor_AXI
#define  position_mech_2pi_AXI_Data_resolver_mech_rev_calc    0x114  //data register for Outport position_mech_2pi_AXI
#define  position_el_2pi_AXI_Data_resolver_mech_rev_calc      0x118  //data register for Outport position_el_2pi_AXI
#define  omega_mech_AXI_Data_resolver_mech_rev_calc           0x11C  //data register for Outport omega_mech_AXI
#define  rpm_mech_AXI_Data_resolver_mech_rev_calc             0x120  //data register for Outport rpm_mech_AXI

#endif /* RESOLVER_MECH_REV_CALC_H_ */
