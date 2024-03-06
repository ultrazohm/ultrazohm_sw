/*
 * File Name:         hdl_prj\ipcore\pu_omega_m_v1_1\include\pu_omega_m_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:45:59
*/

#ifndef PU_OMEGA_M_H_
#define PU_OMEGA_M_H_

#define  IPCore_Reset_pu_omega_m          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_pu_omega_m         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_pu_omega_m      0x8  //contains unique IP timestamp (yymmddHHMM): 2310041545
#define  AXI_pu_conv_in_Data_pu_omega_m   0x17C  //data register for Inport AXI_pu_conv_in
#define  out1_AXI_Data_pu_omega_m         0x1FC  //data register for Outport out1_AXI

#endif /* PU_OMEGA_M_H_ */
