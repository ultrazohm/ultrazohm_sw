/*
 * File Name:         hdl_prj\ipcore\uz_ssi_interface_v2_8\include\uz_ssi_interface_addr.h
 * Description:       C Header File
 * Created:           2025-11-19 16:16:52
*/

#ifndef UZ_SSI_INTERFACE_H_
#define UZ_SSI_INTERFACE_H_

#define  IPCore_Reset_uz_ssi_interface                                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_ssi_interface                                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_ssi_interface                             0x8  //contains unique IP timestamp (yymmddHHMM): 2511191609: 2511191616
#define  ssi_clk_divider_AXI_Data_uz_ssi_interface                     0x100  //data register for Inport ssi_clk_divider_AXI
#define  ssi_encoder_bit_width_single_turn_AXI_Data_uz_ssi_interface   0x104  //data register for Inport ssi_encoder_bit_width_single_turn_AXI
#define  ssi_encoder_bit_width_multi_turn_AXI_Data_uz_ssi_interface    0x108  //data register for Inport ssi_encoder_bit_width_multi_turn_AXI
#define  ssi_encoder_number_of_status_bits_AXI_Data_uz_ssi_interface   0x10C  //data register for Inport ssi_encoder_number_of_status_bits_AXI
#define  delay_first_clk_on_off_AXI_Data_uz_ssi_interface              0x110  //data register for Inport delay_first_clk_on_off_AXI
#define  pos_is_binary_or_gray_AXI_Data_uz_ssi_interface               0x114  //data register for Inport pos_is_binary_or_gray_AXI
#define  ssi_com_enable_AXI_Data_uz_ssi_interface                      0x118  //data register for Inport ssi_com_enable_AXI
#define  reciprocal_bit_width_single_turn_AXI_Data_uz_ssi_interface    0x11C  //data register for Inport reciprocal_bit_width_single_turn_AXI
#define  t_sample_AXI_Data_uz_ssi_interface                            0x120  //data register for Inport t_sample_AXI
#define  kp_pll_AXI_Data_uz_ssi_interface                              0x124  //data register for Inport kp_pll_AXI
#define  ki_pll_AXI_Data_uz_ssi_interface                              0x128  //data register for Inport ki_pll_AXI
#define  debug_off_on_AXI_Data_uz_ssi_interface                        0x12C  //data register for Inport debug_off_on_AXI
#define  position_mech_SI_debug_in_AXI_Data_uz_ssi_interface           0x130  //data register for Inport position_mech_SI_debug_in_AXI
#define  machine_polepairs_AXI_Data_uz_ssi_interface                   0x134  //data register for Inport machine_polepairs_AXI
#define  position_mech_offset_ticks_AXI_Data_uz_ssi_interface          0x138  //data register for Inport position_mech_offset_ticks_AXI
#define  sampling_delay_clk_ticks_AXI_Data_uz_ssi_interface            0x13C  //data register for Inport sampling_delay_clk_ticks_AXI
#define  position_raw_single_turn_AXI_Data_uz_ssi_interface            0x140  //data register for Outport position_raw_single_turn_AXI
#define  position_raw_multi_turn_AXI_Data_uz_ssi_interface             0x144  //data register for Outport position_raw_multi_turn_AXI
#define  status_raw_AXI_Data_uz_ssi_interface                          0x148  //data register for Outport status_raw_AXI
#define  position_mech_SI_single_turn_AXI_Data_uz_ssi_interface        0x14C  //data register for Outport position_mech_SI_single_turn_AXI
#define  position_el_SI_AXI_Data_uz_ssi_interface                      0x150  //data register for Outport position_el_SI_AXI
#define  position_multi_turn_AXI_Data_uz_ssi_interface                 0x154  //data register for Outport position_multi_turn_AXI
#define  speed_mech_SI_AXI_Data_uz_ssi_interface                       0x158  //data register for Outport speed_mech_SI_AXI
#define  speed_el_SI_AXI_Data_uz_ssi_interface                         0x15C  //data register for Outport speed_el_SI_AXI
#define  speed_mech_rpm_AXI_Data_uz_ssi_interface                      0x160  //data register for Outport speed_mech_rpm_AXI

#endif /* UZ_SSI_INTERFACE_H_ */
