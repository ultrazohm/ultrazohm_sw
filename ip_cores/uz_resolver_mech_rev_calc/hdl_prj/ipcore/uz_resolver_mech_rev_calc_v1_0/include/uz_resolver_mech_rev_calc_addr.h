/*
 * File Name:         hdl_prj\ipcore\uz_resolver_mech_rev_calc_v1_0\include\uz_resolver_mech_rev_calc_addr.h
 * Description:       C Header File
 * Created:           2023-01-18 10:32:45
*/

#ifndef UZ_RESOLVER_MECH_REV_CALC_H_
#define UZ_RESOLVER_MECH_REV_CALC_H_

#define  IPCore_Reset_uz_resolver_mech_rev_calc                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_resolver_mech_rev_calc                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_resolver_mech_rev_calc              0x8  //contains unique IP timestamp (yymmddHHMM): 2301181032
#define  resolver_polepairs_AXI_Data_uz_resolver_mech_rev_calc   0x100  //data register for Inport resolver_polepairs_AXI
#define  cnt_reset_AXI_Data_uz_resolver_mech_rev_calc            0x104  //data register for Inport cnt_reset_AXI
#define  position_intmax_AXI_Data_uz_resolver_mech_rev_calc      0x108  //data register for Inport position_intmax_AXI
#define  machine_polepairs_AXI_Data_uz_resolver_mech_rev_calc    0x10C  //data register for Inport machine_polepairs_AXI
#define  bitToRPS_Factor_AXI_Data_uz_resolver_mech_rev_calc      0x110  //data register for Inport bitToRPS_Factor_AXI
#define  position_mech_2pi_AXI_Data_uz_resolver_mech_rev_calc    0x114  //data register for Outport position_mech_2pi_AXI
#define  position_el_2pi_AXI_Data_uz_resolver_mech_rev_calc      0x118  //data register for Outport position_el_2pi_AXI

#endif /* UZ_RESOLVER_MECH_REV_CALC_H_ */
