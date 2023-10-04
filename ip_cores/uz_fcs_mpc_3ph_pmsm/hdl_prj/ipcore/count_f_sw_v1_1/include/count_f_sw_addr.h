/*
 * File Name:         hdl_prj\ipcore\count_f_sw_v1_1\include\count_f_sw_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 16:04:39
*/

#ifndef COUNT_F_SW_H_
#define COUNT_F_SW_H_

#define  IPCore_Reset_count_f_sw          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_count_f_sw         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_count_f_sw      0x8  //contains unique IP timestamp (yymmddHHMM): 2310041604
#define  bResetAXI_Data_count_f_sw        0x100  //data register for Inport bResetAXI
#define  switchNumb_AXI_Data_count_f_sw   0x104  //data register for Outport switchNumb_AXI

#endif /* COUNT_F_SW_H_ */
