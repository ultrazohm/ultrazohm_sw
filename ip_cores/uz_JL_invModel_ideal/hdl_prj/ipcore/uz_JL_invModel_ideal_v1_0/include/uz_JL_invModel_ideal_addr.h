/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CIL\ip_cores\uz_JL_invModel_ideal\hdl_prj\ipcore\uz_JL_invModel_ideal_v1_0\include\uz_JL_invModel_ideal_addr.h
 * Description:       C Header File
 * Created:           2026-05-26 13:14:48
*/

#ifndef UZ_JL_INVMODEL_IDEAL_H_
#define UZ_JL_INVMODEL_IDEAL_H_

#define  IPCore_Reset_uz_JL_invModel_ideal       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_invModel_ideal      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_invModel_ideal   0x8  //contains unique IP timestamp (yymmddHHMM): 2605261314
#define  Udc_Data_uz_JL_invModel_ideal           0x100  //data register for Inport Udc
#define  InvOut_PS_Data_uz_JL_invModel_ideal     0x110  //data register for Outport InvOut_PS. Vector with 3 elements. Register is split across a total of 3 addresses, last address is 0x118.
#define  InvOut_PS_Strobe_uz_JL_invModel_ideal   0x120  //strobe register for port InvOut_PS

#endif /* UZ_JL_INVMODEL_IDEAL_H_ */
