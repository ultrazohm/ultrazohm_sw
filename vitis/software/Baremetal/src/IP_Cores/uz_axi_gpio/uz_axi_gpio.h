#ifndef UZ_AXI_GPIO_H
#define UZ_AXI_GPIO_H

#include <stdbool.h>
#include <stdint.h>

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

#define UZ_AXI_GPIO_MAX_PIN_NUMBER 30U

typedef enum uz_axi_gpio_pin_state_t
{
    LOW = false,
    HIGH = true,
} uz_axi_gpio_pin_state_t;

typedef enum uz_axi_gpio_digital_pin_t
{
    DIG_00 = 0U,
    DIG_01 = 1U,
    DIG_02 = 2U,
    DIG_03 = 3U,
    DIG_04 = 4U,
    DIG_05 = 5U,
    DIG_06 = 6U,
    DIG_07 = 7U,
    DIG_08 = 8U,
    DIG_09 = 9U,
    DIG_10 = 10U,
    DIG_11 = 11U,
    DIG_12 = 12U,
    DIG_13 = 13U,
    DIG_14 = 14U,
    DIG_15 = 15U,
    DIG_16 = 16U,
    DIG_17 = 17U,
    DIG_18 = 18U,
    DIG_19 = 19U,
    DIG_20 = 20U,
    DIG_21 = 21U,
    DIG_22 = 22U,
    DIG_23 = 23U,
    DIG_24 = 24U,
    DIG_25 = 25U,
    DIG_26 = 26U,
    DIG_27 = 27U,
    DIG_28 = 28U,
    DIG_29 = 29U,
} uz_axi_gpio_digital_pin_t;

#define UZ_AXI_GPIO_PIN_00 (1U << 0)
#define UZ_AXI_GPIO_PIN_01 (1U << 1)
#define UZ_AXI_GPIO_PIN_02 (1U << 2)
#define UZ_AXI_GPIO_PIN_03 (1U << 3)
#define UZ_AXI_GPIO_PIN_04 (1U << 4)
#define UZ_AXI_GPIO_PIN_05 (1U << 5)
#define UZ_AXI_GPIO_PIN_06 (1U << 6)
#define UZ_AXI_GPIO_PIN_07 (1U << 7)
#define UZ_AXI_GPIO_PIN_08 (1U << 8)
#define UZ_AXI_GPIO_PIN_09 (1U << 9)
#define UZ_AXI_GPIO_PIN_10 (1U << 10)
#define UZ_AXI_GPIO_PIN_11 (1U << 11)
#define UZ_AXI_GPIO_PIN_12 (1U << 12)
#define UZ_AXI_GPIO_PIN_13 (1U << 13)
#define UZ_AXI_GPIO_PIN_14 (1U << 14)
#define UZ_AXI_GPIO_PIN_15 (1U << 15)
#define UZ_AXI_GPIO_PIN_16 (1U << 16)
#define UZ_AXI_GPIO_PIN_17 (1U << 17)
#define UZ_AXI_GPIO_PIN_18 (1U << 18)
#define UZ_AXI_GPIO_PIN_19 (1U << 19)
#define UZ_AXI_GPIO_PIN_20 (1U << 20)
#define UZ_AXI_GPIO_PIN_21 (1U << 21)
#define UZ_AXI_GPIO_PIN_22 (1U << 22)
#define UZ_AXI_GPIO_PIN_23 (1U << 23)
#define UZ_AXI_GPIO_PIN_24 (1U << 24)
#define UZ_AXI_GPIO_PIN_25 (1U << 25)
#define UZ_AXI_GPIO_PIN_26 (1U << 26)
#define UZ_AXI_GPIO_PIN_27 (1U << 27)
#define UZ_AXI_GPIO_PIN_28 (1U << 28)
#define UZ_AXI_GPIO_PIN_29 (1U << 29)

/**
 * @brief Config struct for driver instance of AXI GPIO
 *
 */
struct uz_axi_gpio_config_t
{
    uint32_t base_address;      /**< Base address of the IP-Core instance to which the driver is coupled */
    uint16_t device_id;         /**< Device ID of the IP-Core instance to which the driver is coupled*/
    uint32_t number_of_pins;    /**< Number of I/O pins of the AXI GPIO instance between 1-30*/
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
 * @brief Immediately sets the state of the specified pin_number to true (high) or false (low)
 *
 * Updates the internal output shadow and flushes it to the AXI GPIO hardware.
 *
 * @param self Pointer to driver instance
 * @param pin_number Number of the pin to be set (zero-based)
 * @param value State of the pin
 */
void uz_axi_gpio_write_pin_zero_based(uz_axi_gpio_t *self, uint32_t pin_number, bool value);

/**
 * @brief Sets a single pin in the output shadow without writing to hardware
 *
 * Call uz_axi_gpio_flush_outputs to write the changed shadow to the AXI GPIO hardware.
 *
 * @param self Pointer to driver instance
 * @param pin_number Number of the pin to be set (zero-based)
 */
void uz_axi_gpio_set_output_pin(uz_axi_gpio_t *self, uint32_t pin_number);

/**
 * @brief Clears a single pin in the output shadow without writing to hardware
 *
 * Call uz_axi_gpio_flush_outputs to write the changed shadow to the AXI GPIO hardware.
 *
 * @param self Pointer to driver instance
 * @param pin_number Number of the pin to be cleared (zero-based)
 */
void uz_axi_gpio_clear_output_pin(uz_axi_gpio_t *self, uint32_t pin_number);

/**
 * @brief Sets a single pin in the output shadow to the specified value without writing to hardware
 *
 * Call uz_axi_gpio_flush_outputs to write the changed shadow to the AXI GPIO hardware.
 *
 * @param self Pointer to driver instance
 * @param pin_number Number of the pin to be set (zero-based)
 * @param value State of the pin
 */
void uz_axi_gpio_set_output_pin_to(uz_axi_gpio_t *self, uint32_t pin_number, bool value);

/**
 * @brief Sets all bits from set_mask in the output shadow without writing to hardware
 *
 * Bits configured as input pins are ignored during the next flush.
 *
 * @param self Pointer to driver instance
 * @param set_mask Bitmask of output pins to set
 */
void uz_axi_gpio_set_output_bitmask(uz_axi_gpio_t *self, uint32_t set_mask);

/**
 * @brief Clears all bits from clear_mask in the output shadow without writing to hardware
 *
 * Bits configured as input pins are ignored during the next flush.
 *
 * @param self Pointer to driver instance
 * @param clear_mask Bitmask of output pins to clear
 */
void uz_axi_gpio_clear_output_bitmask(uz_axi_gpio_t *self, uint32_t clear_mask);

/**
 * @brief Replaces the complete output shadow without writing to hardware
 *
 * Bits configured as input pins are ignored during the next flush.
 *
 * @param self Pointer to driver instance
 * @param bitmask New output shadow bitmask
 */
void uz_axi_gpio_set_output_shadow(uz_axi_gpio_t *self, uint32_t bitmask);

/**
 * @brief Returns the current output shadow
 *
 * @param self Pointer to driver instance
 * @return uint32_t Current output shadow bitmask
 */
uint32_t uz_axi_gpio_get_output_shadow(uz_axi_gpio_t *self);

/**
 * @brief Writes the current output shadow to the AXI GPIO hardware
 *
 * This performs one AXI4-Lite write transaction for all output pins.
 *
 * @param self Pointer to driver instance
 */
void uz_axi_gpio_flush_outputs(uz_axi_gpio_t *self);

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
 * @brief Immediately writes the state of all IOs of the AXI GPIO core using a bitmask
 *
 * Updates the internal output shadow and flushes it to the AXI GPIO hardware.
 *
 * @param self
 * @param bitmask Bitmask to be written indicating true (high) or false (low)
 */
void uz_axi_gpio_write_bitmask(uz_axi_gpio_t *self, uint32_t bitmask);

/**
 * @brief Reads the state of all IOs of the AXI GPIO core and returns them with true (high) or false (low) as a bitmask
 *
 * @param self Pointer to driver instance
 * @return uint32_t
 */
uint32_t uz_axi_gpio_read_bitmask(uz_axi_gpio_t *self);

#ifdef TEST
void uz_axi_gpio_reset_allocation(void);
#endif

#endif // UZ_AXI_GPIO_H
