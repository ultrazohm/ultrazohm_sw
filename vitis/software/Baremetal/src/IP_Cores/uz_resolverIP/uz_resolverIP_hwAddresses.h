#pragma once

#ifndef UZ_RESOLVER_IP_ADDR
#define UZ_RESOLVER_IP_ADDR

#define  IPCore_Reset_uz_axi_testIP       0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_axi_testIP      0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_axi_testIP   0x8U  //contains unique IP timestamp (yymmddHHMM): 2104181321

#define  RESCON_Data_uz_resolverIP        0x00U  //data register for RESCON
#define  RESDAT_Data_uz_resolverIP        0x04U  //data register for RESDAT
#define  RESADR_Data_uz_resolverIP        0x08U  //data register for RESADR
#define  RESRDA_Data_uz_resolverIP        0x0CU  //data register for RESADR




#endif /* UZ_RESOLVER_IP_ADDR */
