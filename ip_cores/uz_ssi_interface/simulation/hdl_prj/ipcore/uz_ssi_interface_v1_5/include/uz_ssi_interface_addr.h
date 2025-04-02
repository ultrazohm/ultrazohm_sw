/*
 * File Name:         hdl_prj\ipcore\uz_ssi_interface_v1_5\include\uz_ssi_interface_addr.h
 * Description:       C Header File
 * Created:           2025-04-02 15:31:28
*/

#ifndef UZ_SSI_INTERFACE_H_
#define UZ_SSI_INTERFACE_H_

#define  IPCore_Reset_uz_ssi_interface                                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_ssi_interface                                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_ssi_interface                             0x8  //contains unique IP timestamp (yymmddHHMM): 2504021531
#define  ssi_clk_divider_AXI_Data_uz_ssi_interface                     0x100  //data register for Inport ssi_clk_divider_AXI
#define  ssi_encoder_bit_width_AXI_Data_uz_ssi_interface               0x104  //data register for Inport ssi_encoder_bit_width_AXI
#define  delay_first_clk_on_off_AXI_Data_uz_ssi_interface              0x108  //data register for Inport delay_first_clk_on_off_AXI
#define  position_SI_float_AXI_Data_uz_ssi_interface                   0x10C  //data register for Outport position_SI_float_AXI
#define  reciprocal_bit_width_times_two_pi_AXI_Data_uz_ssi_interface   0x110  //data register for Inport reciprocal_bit_width_times_two_pi_AXI
#define  position_raw_AXI_Data_uz_ssi_interface                        0x114  //data register for Outport position_raw_AXI

#endif /* UZ_SSI_INTERFACE_H_ */
