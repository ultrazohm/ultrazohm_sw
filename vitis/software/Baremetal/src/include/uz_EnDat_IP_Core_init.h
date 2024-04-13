#pragma once
#include  "../IP_Cores/uz_EnDat/uz_EnDat.h"
/**
 * @brief Initializes an instance of the EnDat driver
 * @return Pointer to initialized instance
 */
uz_EnDat_t* uz_EnDat_IP_core_init(void);
/**
 * @brief Initializes an instance of the EnDat driver with source code customizable factors 
 * @return Pointer to initialized instance
 */
uz_EnDat_t* uz_EnDat_IP_core_custom_init(void);
uz_EnDat_t* uz_EnDat_IP_core_init_helper(uint32_t baseaddress, uint32_t ipcorefreq);
/**
 * @brief Initializes an instance of the EnDat driver with fully custom factors
 *
 * @param baseaddress Address of the EnDat IP-Core Instance
 * @param ipcorefreq Operating frequency of the IP-Core (should be 100 MHz)
 * @param fct1 Factor 1 adjusting dataflow
 * @param fct2 Factor 2 adjusting recoverytime post telegramm
 * @param fct3 Factor 3 adjusting the initialoff time
 * @param fct4 Factor 4 adjusting DATA to CLK phase shift
 * @param fct5 Factor 5 adjusting telegramlength
 * @param fct6 Factor 6 adjusting reponse to CLK phase shift
 * @param fct7 Factor 7 changing bit shift behaviour of position
 * @param ctrl Controlword to IP-Core
 * @param dvder Clockdivider to IP-Core 
 * 
 * @return Pointer to initialized instance
 */
uz_EnDat_t* uz_EnDat_IP_core_expert_init(uint32_t baseaddress, uint32_t ipcorefreq, int16_t fct1, int16_t fct2, int16_t fct3, int16_t fct4, int16_t fct5, int16_t fct6, int16_t fct7, controlword ctrl, uint8_t dvder);



   
