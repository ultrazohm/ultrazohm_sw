#ifndef UZ_ENDAT_H
#define UZ_ENDAT_H

//Useful Values to begin with

#define FKT1_DEF 100
#define FKT2_DEF 100
#define FKT3_DEF 100
#define FKT4_DEF 100
#define FKT5_DEF 100
#define CTRLWORD_DEF 0xA807
#define DIVIDER_DEF 3

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Data type for object EnDat
 *
 */
typedef struct uz_EnDat_t uz_EnDat_t;

/**
 * @brief Configuration struct for EnDat
 *
 */
struct uz_EnDat_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initializes an instance of the EnDat driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_EnDat_t* uz_EnDat_init(struct uz_EnDat_config_t config);



void uz_EnDat_write_control_and_divider (uz_EnDat_t* self, uint16_t ctrlword, uint8_t divider);



#endif // UZ_ENDAT_H
