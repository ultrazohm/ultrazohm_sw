/*
 * File Name:         C:\Users\jonat\Documents\MA_JL_HIL\ip_cores\uz_JL_SDDemod\ipcore\uz_JL_SDDemod_v1_0\include\uz_JL_SDDemod_addr.h
 * Description:       C Header File
 * Created:           2026-06-08 18:15:50
*/

#ifndef UZ_JL_SDDEMOD_H_
#define UZ_JL_SDDEMOD_H_

#define  IPCore_Reset_uz_JL_SDDemod       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_JL_SDDemod      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_JL_SDDemod   0x8  //contains unique IP timestamp (yymmddHHMM): 2606081815
#define  R_axi_Data_uz_JL_SDDemod         0x100  //data register for Inport R_axi
#define  data_out_ps_Data_uz_JL_SDDemod   0x104  //data register for Outport data_out_ps

#endif /* UZ_JL_SDDEMOD_H_ */
