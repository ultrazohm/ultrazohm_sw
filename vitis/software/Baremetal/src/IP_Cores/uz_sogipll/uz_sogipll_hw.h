#ifndef UZ_SOGIPLL_HW_H
#define UZ_SOGIPLL_HW_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @file
 * @brief Raw SOGI PLL register access. Each call performs one AXI transaction.
 *
 * No completion wait or coherent snapshot of multiple outputs is provided.
 * Algorithm parameter validation belongs to the higher-level driver.
 */

/**
 * @brief Write: IP wrapper reset (writing true triggers a reset pulse).
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_ipcore_reset(uint32_t base_address, bool value);

/**
 * @brief Write: IP wrapper enable.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_ipcore_enable(uint32_t base_address, bool value);

/**
 * @brief Read: IP generation timestamp encoded as yymmddHHMM.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
uint32_t uz_sogipll_hw_read_ipcore_timestamp(uint32_t base_address);

/**
 * @brief Write: Algorithm reset input (true holds the algorithm in reset).
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_rst(uint32_t base_address, bool value);

/**
 * @brief Write: Input voltage before scaling.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_v(uint32_t base_address, float value);

/**
 * @brief Write: Feedforward angular frequency in rad/s.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_omega_ff(uint32_t base_address, float value);

/**
 * @brief Write: SOGI gain.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_k(uint32_t base_address, float value);

/**
 * @brief Write: PLL proportional gain.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_kp(uint32_t base_address, float value);

/**
 * @brief Write: PLL integral gain.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_ki(uint32_t base_address, float value);

/**
 * @brief Write: Sample period in seconds.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_t_sample(uint32_t base_address, float value);

/**
 * @brief Write: Input voltage scaling factor.
 * @param base_address Nonzero base address of the IP core.
 * @param value Register value.
 */
void uz_sogipll_hw_write_in_v_scaling(uint32_t base_address, float value);

/**
 * @brief Read: Estimated scaled voltage.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
float uz_sogipll_hw_read_out_v_est(uint32_t base_address);

/**
 * @brief Read: Estimated quadrature scaled voltage.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
float uz_sogipll_hw_read_out_qv_est(uint32_t base_address);

/**
 * @brief Read: Direct-axis scaled voltage.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
float uz_sogipll_hw_read_out_v_d(uint32_t base_address);

/**
 * @brief Read: Quadrature-axis scaled voltage.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
float uz_sogipll_hw_read_out_v_q(uint32_t base_address);

/**
 * @brief Read: Estimated phase in radians.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
float uz_sogipll_hw_read_out_theta_est(uint32_t base_address);

/**
 * @brief Read: Estimated angular frequency in rad/s.
 * @param base_address Nonzero base address of the IP core.
 * @return Register value.
 */
float uz_sogipll_hw_read_out_omega_est(uint32_t base_address);

#endif // UZ_SOGIPLL_HW_H
