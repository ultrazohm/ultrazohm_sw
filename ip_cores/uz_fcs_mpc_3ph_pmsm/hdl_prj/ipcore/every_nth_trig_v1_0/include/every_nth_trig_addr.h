/*
 * File Name:         hdl_prj\ipcore\every_nth_trig_v1_0\include\every_nth_trig_addr.h
 * Description:       C Header File
 * Created:           2024-03-28 11:06:09
*/

#ifndef EVERY_NTH_TRIG_H_
#define EVERY_NTH_TRIG_H_

#define  IPCore_Reset_every_nth_trig         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_every_nth_trig        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_every_nth_trig     0x8  //contains unique IP timestamp (yymmddHHMM): 2403281105
#define  every_nth_AXI_Data_every_nth_trig   0x100  //data register for Inport every_nth_AXI

#endif /* EVERY_NTH_TRIG_H_ */
