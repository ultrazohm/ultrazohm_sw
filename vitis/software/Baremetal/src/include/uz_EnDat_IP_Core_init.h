#pragma once
#include  "../IP_Cores/uz_EnDat/uz_EnDat.h"
uz_EnDat_t* uz_EnDat_IP_core_init(void);
uz_EnDat_t* uz_EnDat_IP_core_custom_init(void);
uz_EnDat_t* uz_EnDat_IP_core_init_helper(uint32_t baseaddress, uint32_t ipcorefreq);
uz_EnDat_t* uz_EnDat_IP_core_expert_init(uint32_t baseaddress, uint32_t ipcorefreq, int16_t fct1, int16_t fct2, int16_t fct3, int16_t fct4, int16_t fct5, int16_t fct6, int16_t fct7, controlword ctrl, uint8_t dvder);



   
