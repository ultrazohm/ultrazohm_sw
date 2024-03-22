/*
 * File Name:         hdl_prj\ipcore\uz_pred_error_v1_0\include\uz_pred_error_addr.h
 * Description:       C Header File
 * Created:           2024-03-22 17:09:05
*/

#ifndef UZ_PRED_ERROR_H_
#define UZ_PRED_ERROR_H_

#define  IPCore_Reset_uz_pred_error       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_pred_error      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_pred_error   0x8  //contains unique IP timestamp (yymmddHHMM): 2403221708
#define  ed_pred_AXI_Data_uz_pred_error   0x100  //data register for Outport ed_pred_AXI
#define  eq_pred_AXI_Data_uz_pred_error   0x104  //data register for Outport eq_pred_AXI

#endif /* UZ_PRED_ERROR_H_ */
