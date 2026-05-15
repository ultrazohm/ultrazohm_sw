/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CIL\ip_cores\uz_JL_invModel_PT1\hdl_prj\ipcore\uz_JL_InvModel_PT1_v1_0\include\uz_JL_InvModel_PT1_addr.h
 * Description:       C Header File
 * Created:           2026-05-11 15:32:57
*/

#ifndef UZ_JL_INVMODEL_PT1_H_
#define UZ_JL_INVMODEL_PT1_H_

#define  IPCore_Reset_uz_JL_InvModel_PT1       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_InvModel_PT1      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_InvModel_PT1   0x8  //contains unique IP timestamp (yymmddHHMM): 2605111532
#define  Ualpha_Data_uz_JL_InvModel_PT1        0x100  //data register for Inport Ualpha
#define  Ubeta_Data_uz_JL_InvModel_PT1         0x104  //data register for Inport Ubeta
#define  PT1_Gain_Data_uz_JL_InvModel_PT1      0x108  //data register for Inport PT1_Gain
#define  PT1_Ts_Data_uz_JL_InvModel_PT1        0x10C  //data register for Inport PT1_Ts
#define  PT1_reset_Data_uz_JL_InvModel_PT1     0x110  //data register for Inport PT1_reset
#define  InvOut_PS_Data_uz_JL_InvModel_PT1     0x150  //data register for Outport InvOut_PS. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x158.
#define  InvOut_PS_Strobe_uz_JL_InvModel_PT1   0x160  //strobe register for port InvOut_PS

#endif /* UZ_JL_INVMODEL_PT1_H_ */
