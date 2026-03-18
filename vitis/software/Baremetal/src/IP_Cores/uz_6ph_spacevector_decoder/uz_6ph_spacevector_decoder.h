#ifndef UZ_6PH_SPACEVECTOR_DECODER_H
#define UZ_6PH_SPACEVECTOR_DECODER_H


#include <stdint.h>

/**
 * @brief Object data type definition of the IP-Core driver
 *
 */
typedef struct uz_6ph_spacevector_decoder_t uz_6ph_spacevector_decoder_t;

struct uz_6ph_spacevector_decoder_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz;
};

typedef struct {
    unsigned int sv1;
    unsigned int sv2;
    unsigned int sv3;
    unsigned int sv4;
    unsigned int sv5;
    unsigned int sv6;
    unsigned int sv7;
    unsigned int sv8;
    unsigned int sv9;
    unsigned int sv10;
    unsigned int sv11;
    unsigned int sv12;
    unsigned int sv13;
    unsigned int sv14;
} spacevector_decoder_output;

/**
 * @brief Initialize an instance of the driver for the IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_count_switching_IPCore_t* Pointer to an initialized instance of the driver
 */
uz_6ph_spacevector_decoder_t* uz_6ph_spacevector_decoder_init(struct uz_6ph_spacevector_decoder_config_t config);


/**
 * @brief Read 
 *
 * @param self Pointer to driver instance
 * @return uint32_t
 */
uint32_t uz_6ph_spacevector_decoder_get_spacevector_num(uz_6ph_spacevector_decoder_t* self, unsigned int num);

/**
 * @brief Read 
 *
 * @param self Pointer to driver instance
 * @return uint32_t
 */
spacevector_decoder_output uz_6ph_spacevector_decoder_get_all_spacevectors(uz_6ph_spacevector_decoder_t* self);


#endif // UZ_6PH_SPACEVECTOR_DECODER_H
