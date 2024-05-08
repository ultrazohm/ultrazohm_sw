/*
 * File Name:         hdl_prj\ipcore\MPC_incr_encoder_conversion_v1_0\include\MPC_incr_encoder_conversion_addr.h
 * Description:       C Header File
 * Created:           2024-04-26 14:46:21
*/

#ifndef MPC_INCR_ENCODER_CONVERSION_H_
#define MPC_INCR_ENCODER_CONVERSION_H_

#define  IPCore_Reset_MPC_incr_encoder_conversion       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_MPC_incr_encoder_conversion      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_MPC_incr_encoder_conversion   0x8  //contains unique IP timestamp (yymmddHHMM): 2404261446
#define  out1_AXI_Data_MPC_incr_encoder_conversion      0x1FC  //data register for Outport out1_AXI

#endif /* MPC_INCR_ENCODER_CONVERSION_H_ */
