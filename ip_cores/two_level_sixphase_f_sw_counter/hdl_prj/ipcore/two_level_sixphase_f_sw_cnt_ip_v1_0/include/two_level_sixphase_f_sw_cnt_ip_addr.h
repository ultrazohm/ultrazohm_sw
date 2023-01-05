/*
 * File Name:         hdl_prj\ipcore\two_level_sixphase_f_sw_cnt_ip_v1_0\include\two_level_sixphase_f_sw_cnt_ip_addr.h
 * Description:       C Header File
 * Created:           2023-01-05 11:03:35
*/

#ifndef TWO_LEVEL_SIXPHASE_F_SW_CNT_IP_H_
#define TWO_LEVEL_SIXPHASE_F_SW_CNT_IP_H_

#define  IPCore_Reset_two_level_sixphase_f_sw_cnt_ip          0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_two_level_sixphase_f_sw_cnt_ip         0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_two_level_sixphase_f_sw_cnt_ip      0x8  //contains unique IP timestamp (yymmddHHMM): 2301051103
#define  bResetAXI_Data_two_level_sixphase_f_sw_cnt_ip        0x100  //data register for Inport bResetAXI
#define  switchNumb_AXI_Data_two_level_sixphase_f_sw_cnt_ip   0x104  //data register for Outport switchNumb_AXI

#endif /* TWO_LEVEL_SIXPHASE_F_SW_CNT_IP_H_ */
