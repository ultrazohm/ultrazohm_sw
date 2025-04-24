/*
 * File Name:         hdl_prj\ipcore\uz_ssi_interface_v1_8\include\uz_ssi_interface_addr.h
 * Description:       C Header File
 * Created:           2025-04-24 10:36:52
*/

#ifndef UZ_SSI_INTERFACE_H_
#define UZ_SSI_INTERFACE_H_

#define  IPCore_Reset_uz_ssi_interface                         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_ssi_interface                        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_ssi_interface                     0x8  //contains unique IP timestamp (yymmddHHMM): 2504241036
#define  ssi_clk_divider_AXI_Data_uz_ssi_interface             0x100  //data register for Inport ssi_clk_divider_AXI
#define  ssi_encoder_bit_width_AXI_Data_uz_ssi_interface       0x104  //data register for Inport ssi_encoder_bit_width_AXI
#define  delay_first_clk_on_off_AXI_Data_uz_ssi_interface      0x108  //data register for Inport delay_first_clk_on_off_AXI
#define  reciprocal_bit_width_AXI_Data_uz_ssi_interface        0x10C  //data register for Inport reciprocal_bit_width_AXI
#define  t_sample_AXI_Data_uz_ssi_interface                    0x110  //data register for Inport t_sample_AXI
#define  kp_pll_AXI_Data_uz_ssi_interface                      0x114  //data register for Inport kp_pll_AXI
#define  debug_off_on_AXI_Data_uz_ssi_interface                0x118  //data register for Inport debug_off_on_AXI
#define  ki_pll_AXI_Data_uz_ssi_interface                      0x11C  //data register for Inport ki_pll_AXI
#define  position_mech_SI_debug_in_AXI_Data_uz_ssi_interface   0x120  //data register for Inport position_mech_SI_debug_in_AXI
#define  position_raw_AXI_Data_uz_ssi_interface                0x124  //data register for Outport position_raw_AXI
#define  position_mech_SI_AXI_Data_uz_ssi_interface            0x128  //data register for Outport position_mech_SI_AXI
#define  speed_mech_SI_AXI_Data_uz_ssi_interface               0x12C  //data register for Outport speed_mech_SI_AXI

#endif /* UZ_SSI_INTERFACE_H_ */
