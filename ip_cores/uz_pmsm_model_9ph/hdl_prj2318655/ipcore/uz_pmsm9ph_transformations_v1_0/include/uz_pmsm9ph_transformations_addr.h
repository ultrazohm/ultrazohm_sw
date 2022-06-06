/*
 * File Name:         hdl_prj2318655/ipcore/uz_pmsm9ph_transformations_v1_0/include/uz_pmsm9ph_transformations_addr.h
 * Description:       C Header File
 * Created:           2022-06-05 21:48:04
*/

#ifndef UZ_PMSM9PH_TRANSFORMATIONS_H_
#define UZ_PMSM9PH_TRANSFORMATIONS_H_

#define  IPCore_Reset_uz_pmsm9ph_transformations       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pmsm9ph_transformations      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pmsm9ph_transformations   0x8  //contains unique IP timestamp (yymmddHHMM): 2206052147
#define  Out2_Data_uz_pmsm9ph_transformations          0x100  //data register for Outport Out2, vector with 9 elements, address ends at 0x120
#define  Out2_Strobe_uz_pmsm9ph_transformations        0x140  //strobe register for port Out2

#endif /* UZ_PMSM9PH_TRANSFORMATIONS_H_ */
