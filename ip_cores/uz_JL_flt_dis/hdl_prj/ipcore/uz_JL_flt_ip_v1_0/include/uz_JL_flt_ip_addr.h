/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CB\ip_cores\uz_JL_flt_dis\hdl_prj\ipcore\uz_JL_flt_ip_v1_0\include\uz_JL_flt_ip_addr.h
 * Description:       C Header File
 * Created:           2026-10-27 01:46:51
*/

#ifndef UZ_JL_FLT_IP_H_
#define UZ_JL_FLT_IP_H_

#define  IPCore_Reset_uz_JL_flt_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_flt_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_flt_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2610270146
#define  FLT_PS_Data_uz_JL_flt_ip        0x100  //data register for Inport FLT_PS
#define  FLT_RST_Data_uz_JL_flt_ip       0x104  //data register for Inport FLT_RST
#define  use_flt_dis_Data_uz_JL_flt_ip   0x108  //data register for Inport use_flt_dis
#define  FLT_ps_Data_uz_JL_flt_ip        0x10C  //data register for Outport FLT_ps

#endif /* UZ_JL_FLT_IP_H_ */
