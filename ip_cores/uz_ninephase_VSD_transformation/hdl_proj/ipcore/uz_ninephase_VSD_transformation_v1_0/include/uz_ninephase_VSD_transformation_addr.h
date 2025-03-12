/*
 * File Name:         C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_ninephase_VSD_transformation\hdl_proj\ipcore\uz_ninephase_VSD_transformation_v1_0\include\uz_ninephase_VSD_transformation_addr.h
 * Description:       C Header File
 * Created:           2022-10-17 11:05:18
*/

#ifndef UZ_NINEPHASE_VSD_TRANSFORMATION_H_
#define UZ_NINEPHASE_VSD_TRANSFORMATION_H_

#define  IPCore_Reset_uz_ninephase_VSD_transformation           0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_ninephase_VSD_transformation          0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_ninephase_VSD_transformation       0x8  //contains unique IP timestamp (yymmddHHMM): 2210171105
#define  theta_el_axi_Data_uz_ninephase_VSD_transformation      0x100  //data register for Outport theta_el_axi
#define  x_abc_out_axi_Data_uz_ninephase_VSD_transformation     0x140  //data register for Outport x_abc_out_axi, vector with 9 elements, address ends at 0x160
#define  x_abc_out_axi_Strobe_uz_ninephase_VSD_transformation   0x180  //strobe register for port x_abc_out_axi

#endif /* UZ_NINEPHASE_VSD_TRANSFORMATION_H_ */
