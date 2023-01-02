/*
 * File Name:         hdl_prj\ipcore\uz_typeconv_multi_v1_0\include\uz_typeconv_multi_addr.h
 * Description:       C Header File
 * Created:           2023-01-02 15:35:21
*/

#ifndef UZ_TYPECONV_MULTI_H_
#define UZ_TYPECONV_MULTI_H_

#define  IPCore_Reset_uz_typeconv_multi                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_typeconv_multi                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_typeconv_multi                  0x8  //contains unique IP timestamp (yymmddHHMM): 2301021535
#define  omega_B_inv_AXI_ufix18En18_Data_uz_typeconv_multi   0x100  //data register for Inport omega_B_inv_AXI_ufix18En18

#endif /* UZ_TYPECONV_MULTI_H_ */
