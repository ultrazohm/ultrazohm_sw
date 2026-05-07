/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_CIL\ip_cores\uz_JL_invModel_ideal\hdl_prj\ipcore\uz_JL_invModel_ideal_v1_0\include\uz_JL_invModel_ideal_addr.h
 * Description:       C Header File
 * Created:           2026-05-04 16:05:16
*/

#ifndef UZ_JL_INVMODEL_IDEAL_H_
#define UZ_JL_INVMODEL_IDEAL_H_

#define  IPCore_Reset_uz_JL_invModel_ideal                  0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_invModel_ideal                 0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_invModel_ideal              0x8  //contains unique IP timestamp (yymmddHHMM): 2605041605
#define  Bus_Conf_Inv_SwitchInv_Data_uz_JL_invModel_ideal   0x100  //data register for Inport Bus_Conf_Inv_SwitchInv
#define  Bus_Conf_Inv_Udc_Data_uz_JL_invModel_ideal         0x104  //data register for Inport Bus_Conf_Inv_Udc
#define  Bus_Conf_Inv_PT1_Gain_Data_uz_JL_invModel_ideal    0x108  //data register for Inport Bus_Conf_Inv_PT1_Gain
#define  Bus_Conf_Inv_PT1_Ts_Data_uz_JL_invModel_ideal      0x10C  //data register for Inport Bus_Conf_Inv_PT1_Ts
#define  Bus_Conf_Inv_PT1_reset_Data_uz_JL_invModel_ideal   0x110  //data register for Inport Bus_Conf_Inv_PT1_reset

#endif /* UZ_JL_INVMODEL_IDEAL_H_ */
