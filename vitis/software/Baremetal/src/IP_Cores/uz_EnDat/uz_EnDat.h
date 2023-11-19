// "Copyright [year] <Copyright Owner>"
#ifndef UZ_ENDAT_H  // NOLINT
#define UZ_ENDAT_H

// Useful Values to begin with

#define FACTOR_DEFAULT 100
#define AMOUNT_OF_FACTORS 5
#define CONTROLWORD_DEFAULT 0xA807
#define DIVIDER_DEFAULT 3

#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>



typedef bool ctrlwrd_expanded[16];


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



int uz_EnDat_write_control_and_divider(uz_EnDat_t *self, uint16_t ctrlword, uint8_t divider);
/**
 * @param num means which Factor you want to write 
 * @param factor value that you want to write 100 (e.g. 1.00 is default)
 * @brief The following factors are available as of now;
 * @brief 1 = adjusts the data flow change timing;
 * @brief 2 = adjusts the recovery time after a telegramm;
 * @brief 3 = adjusts the initial silence period length;
 * @brief 4 = adjusts the data to clock resync interval;
 * @brief 5 = adjusts the length of the telegram;
 */
int uz_EnDat_write_factor(uz_EnDat_t *self, uint16_t factor, uint8_t num);

uint16_t uz_EnDat_read_statusword(uz_EnDat_t *self);
/**
 * @param num  means which value you would like to fetch. 0 = t0 recent, 4 = t-4 value
 *
 */
uint32_t uz_EnDat_read_pos(uz_EnDat_t *self, uint8_t num);

int uz_EnDat_set_default_values(uz_EnDat_t *self);

uint16_t uz_EnDat_factor_converter(float in);
uint16_t uz_EnDat_ctrlword_builder(ctrlwrd_expanded inp);
/**
 * @brief 12,5 Mhz = 0; 192,5 Khz = 6, 3 (1,5 Mhz is tested)
 *
 *
 */
uint16_t uz_EnDat_set_clk_frequency_divider(uint8_t div);

uint8_t uz_EnDat_read_crc(uz_EnDat_t* self);

// void uz_EnDat_set_mode_


#endif  // UZ_ENDAT_H  // NOLINT
