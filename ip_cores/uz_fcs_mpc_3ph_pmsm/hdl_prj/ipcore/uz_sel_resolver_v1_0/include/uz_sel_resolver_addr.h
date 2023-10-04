/*
 * File Name:         hdl_prj\ipcore\uz_sel_resolver_v1_0\include\uz_sel_resolver_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 17:27:06
*/

#ifndef UZ_SEL_RESOLVER_H_
#define UZ_SEL_RESOLVER_H_

#define  IPCore_Reset_uz_sel_resolver             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_sel_resolver            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_sel_resolver         0x8  //contains unique IP timestamp (yymmddHHMM): 2310041727
#define  right_or_left_AXI_Data_uz_sel_resolver   0x124  //data register for Inport right_or_left_AXI

#endif /* UZ_SEL_RESOLVER_H_ */
