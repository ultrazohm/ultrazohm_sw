/*
 * File Name:         hdl_prj\ipcore\ref_distributor_v1_0\include\ref_distributor_addr.h
 * Description:       C Header File
 * Created:           2025-01-21 10:23:58
*/

#ifndef REF_DISTRIBUTOR_H_
#define REF_DISTRIBUTOR_H_

#define  IPCore_Reset_ref_distributor         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_ref_distributor        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_ref_distributor     0x8  //contains unique IP timestamp (yymmddHHMM): 2501211023
#define  id_ref_pu_AXI_Data_ref_distributor   0x100  //data register for Inport id_ref_pu_AXI
#define  iq_ref_pu_AXI_Data_ref_distributor   0x104  //data register for Inport iq_ref_pu_AXI
#define  iX_ref_pu_AXI_Data_ref_distributor   0x108  //data register for Inport iX_ref_pu_AXI
#define  iY_ref_pu_AXI_Data_ref_distributor   0x10C  //data register for Inport iY_ref_pu_AXI

#endif /* REF_DISTRIBUTOR_H_ */
