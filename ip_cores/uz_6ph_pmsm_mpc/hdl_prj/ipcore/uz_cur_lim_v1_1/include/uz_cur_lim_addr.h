/*
 * File Name:         hdl_prj\ipcore\uz_cur_lim_v1_1\include\uz_cur_lim_addr.h
 * Description:       C Header File
 * Created:           2023-10-18 16:24:05
*/

#ifndef UZ_CUR_LIM_H_
#define UZ_CUR_LIM_H_

#define  IPCore_Reset_uz_cur_lim                      0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_cur_lim                     0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_cur_lim                  0x8  //contains unique IP timestamp (yymmddHHMM): 2310181624
#define  i_max_ampere_AXI_Data_uz_cur_lim             0x100  //data register for Inport i_max_ampere_AXI
#define  reset_violation_AXI_Data_uz_cur_lim          0x104  //data register for Inport reset_violation_AXI
#define  current_limit_violated_AXI_Data_uz_cur_lim   0x108  //data register for Outport current_limit_violated_AXI

#endif /* UZ_CUR_LIM_H_ */
