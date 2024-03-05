/*
 * File Name:         hdl_prj\ipcore\uz_sel_trigger_v1_0\include\uz_sel_trigger_addr.h
 * Description:       C Header File
 * Created:           2023-10-20 14:13:15
*/

#ifndef UZ_SEL_TRIGGER_H_
#define UZ_SEL_TRIGGER_H_

#define  IPCore_Reset_uz_sel_trigger             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_sel_trigger            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_sel_trigger         0x8  //contains unique IP timestamp (yymmddHHMM): 2310201413
#define  right_or_left_AXI_Data_uz_sel_trigger   0x124  //data register for Inport right_or_left_AXI

#endif /* UZ_SEL_TRIGGER_H_ */
