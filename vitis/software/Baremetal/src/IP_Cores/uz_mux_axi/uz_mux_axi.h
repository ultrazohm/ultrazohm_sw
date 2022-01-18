#ifndef UZ_MUX_AXI_H
#define UZ_MUX_AXI_H
#include <stdint.h>

/**
 * @brief Data type for object uz_mux_axi
 *
 */
typedef struct uz_mux_axi_t uz_mux_axi_t;

/**
 * @brief Configuration struct for uz_mux_axi
 *
 */
struct uz_mux_axi_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    uint32_t mux; /**< Select value for the mux */
    uint32_t n_th_interrupt; /**< Trigger ratio of adc_interrupt/isr_interrupt */
};

/**
 * @brief Initializes an instance of the uz_mux_axi driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_mux_axi_t* uz_mux_axi_init(struct uz_mux_axi_config_t config);

/**
 * @brief Sets the mux value (selects the interrupt source)
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param mux  Value of the selected mux (see uz_global_configuration.h)
 */
void uz_mux_axi_set_mux(struct uz_mux_axi_t *self, uint32_t mux);

/**
 * @brief Sets the n_th_interrupt value (sets the interrupt ratio between adc_interrupt/isr_interrupt)
 *
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param n_th_interrupt Value that sets the ratio between adc_interrupt and isr_interrupt
 */
void uz_mux_axi_set_n_th_interrupt(struct uz_mux_axi_t *self, uint32_t n_th_interrupt);

#endif // UZ_MUX_AXI_H
