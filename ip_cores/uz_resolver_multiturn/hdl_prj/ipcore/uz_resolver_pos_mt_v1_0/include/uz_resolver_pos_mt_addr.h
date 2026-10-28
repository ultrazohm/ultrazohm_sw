/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CB\ip_cores\uz_resolver_multiturn\hdl_prj\ipcore\uz_resolver_pos_mt_v1_0\include\uz_resolver_pos_mt_addr.h
 * Description:       C Header File
 * Created:           2026-10-27 22:05:24
*/

#ifndef UZ_RESOLVER_POS_MT_H_
#define UZ_RESOLVER_POS_MT_H_

#define  IPCore_Reset_uz_resolver_pos_mt                0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_resolver_pos_mt               0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_resolver_pos_mt            0x8  //contains unique IP timestamp (yymmddHHMM): 2610272205
#define  reset_Data_uz_resolver_pos_mt                  0x100  //data register for Inport reset
#define  load_position_Data_uz_resolver_pos_mt          0x104  //data register for Inport load_position
#define  pos_mt_preset_Data_uz_resolver_pos_mt          0x108  //data register for Inport pos_mt_preset. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x10C.
#define  pos_mt_preset_Strobe_uz_resolver_pos_mt        0x110  //strobe register for port pos_mt_preset
#define  turns_cnt_Data_uz_resolver_pos_mt              0x114  //data register for Outport turns_cnt
#define  multiturn_position_Data_uz_resolver_pos_mt     0x118  //data register for Outport multiturn_position. Data width is wider than the register width, so data is split into 2 32-bit sections.. Register is split across a total of 2 addresses, last address is 0x11C.
#define  multiturn_position_Strobe_uz_resolver_pos_mt   0x120  //strobe register for port multiturn_position
#define  pos_mt_valid_Data_uz_resolver_pos_mt           0x124  //data register for Outport pos_mt_valid

#endif /* UZ_RESOLVER_POS_MT_H_ */
