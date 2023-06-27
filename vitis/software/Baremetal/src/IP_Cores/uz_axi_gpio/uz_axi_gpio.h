#ifndef UZ_AXI_GPIO_H
#define UZ_AXI_GPIO_H

#include <stdbool.h>

typedef struct uz_axi_gpio_t uz_axi_gpio_t;

/**
 * @brief Define to set all I/O of the AXI-GPIO IP-Core to OUTPUT direction
 *
 */
#define UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT 0x00000000U

/**
 * @brief Define to set all I/O of the AXI-GPIO IP-Core to INPUT direction
 *
 */
#define UZ_AXI_GPIO_DIRECTION_ALL_INPUT 0xFFFFFFFFU

/**
 * @brief Config struct for driver instance of AXI GPIO
 *
 */
struct uz_axi_gpio_config_t
{
    uint32_t base_address;      /**< Base address of the IP-Core instance to which the driver is coupled */
    uint16_t device_id;         /**< Device ID of the IP-Core instance to which the driver is coupled*/
    uint32_t number_of_pins;    /**< Number of I/O pins of the AXI GPIO instance between 1-32*/
    uint32_t direction_of_pins; /**< Bitmask for the direction of the GPIO. 1 is input, and 0 is output. Use UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT and UZ_AXI_GPIO_DIRECTION_ALL_INPUT defines.*/
};

/**
 * @brief Initializes an instance of the AXI GPIO driver
 *
 * @param config Config struct for the AXI GPIO
 * @return uz_axi_gpio_t* Pointer to an instance of the driver
 */
uz_axi_gpio_t *uz_axi_gpio_init(struct uz_axi_gpio_config_t config);

/**
 * @brief Set the state of the specified pin_number to true (high) or false (low)
 *
 * @param self Pointer to driver instance
 * @param pin_number Number of the pin to be set (zero-based)
 * @param value State of the pin
 */
void uz_axi_gpio_write_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number, bool value);

/**
 * @brief Reads the state of the specified pin_number and returns them with true (high) or false (low)
 *
 * @param self Pointer to driver instance
 * @param pin_number Number of the pin to be set (zero-based)
 * @return true
 * @return false
 */
bool uz_axi_gpio_read_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number);

/**
 * @brief Writes the state of all IOs of the AXI GPIO core using a bitmask
 *
 * @param self
 * @param bitmask Bitmask to be written indicating true (high) or false (low)
 */
void uz_axi_gpio_write_bitmask(uz_axi_gpio_t *self, uint32_t bitmask); // write to all pins at once with bitmask

/**
 * @brief Reads the state of all IOs of the AXI GPIO core and returns them with true (high) or false (low) as a bitmask
 *
 * @param self Pointer to driver instance
 * @return uint32_t
 */
uint32_t uz_axi_gpio_read_bitmask(uz_axi_gpio_t *self); // read one pin

#endif // UZ_AXI_GPIO_H
