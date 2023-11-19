#ifndef UZ_ENDAT_H
#define UZ_ENDAT_H

//Useful Values to begin with

#define FKT_DEF 100
#define FKTENUM 5
#define CTRLWORD_DEF 0xA807
#define DIVIDER_DEF 3

#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>



typedef bool ctrlwrd_expanded[15];


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



int uz_EnDat_write_control_and_divider (uz_EnDat_t* self, uint16_t ctrlword, uint8_t divider);

int uz_EnDat_write_factor(uz_EnDat_t* self, uint16_t factor, uint8_t num);

uint16_t uz_EnDat_read_statusword(uz_EnDat_t* self);

uint32_t uz_EnDat_read_pos(uz_EnDat_t* self, uint8_t num);

int uz_EnDat_set_default_values (uz_EnDat_t* self);

uint16_t uz_EnDat_factor_converter(float in);
uint16_t uz_EnDat_ctrlword_builder(ctrlwrd_expanded inp);
/**
 * @brief 12,5 Mhz = 0; 192,5 Khz = 6, 3 (1,5 Mhz is tested)
 *
 *
 */
uint16_t uz_EnDat_set_clk_frequency_divider(uint8_t div);

#endif // UZ_ENDAT_H
