#ifndef UZ_FIXEDPOINT_H
#define UZ_FIXEDPOINT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type definition for the fixed point definition
 * 
 */
struct uz_fixedpoint_definition_t{
    const bool is_signed;
    const uint32_t fractional_bits;
    const uint32_t integer_bits;
};

/**
 * @brief Reads a fixed point variable from AXI
 * 
 * @param memory_address Absolute address that is read
 * @param fixedpoint_definition Definition of the fixed point data that is read
 * @return float 
 */
float uz_fixedpoint_axi_read(uint32_t memory_address, struct uz_fixedpoint_definition_t fixedpoint_definition);

/**
 * @brief Writes a fixed point variable to AXI
 * 
 * @param memory_address Absolute address that is written to
 * @param data Data that is written
 * @param fixedpoint_definition Fixed point definition of the data
 */
void uz_fixedpoint_axi_write(uint32_t memory_address,float data, struct uz_fixedpoint_definition_t fixedpoint_definition);

/**
 * @brief Checks if the input data is within the min/max limits of the fixed point data type
 * 
 * @param data input data
 * @param fixedpoint_definition fixed point data definition 
 */
void uz_fixedpoint_check_limits(float data, struct uz_fixedpoint_definition_t fixedpoint_definition);

/**
 * @brief Returns the precision (smalles representable difference between two values) of the fixed point data type
 * 
 * @param input Fixed point data definition
 * @return float 
 */
float uz_fixedpoint_get_precision(struct uz_fixedpoint_definition_t input);

/**
 * @brief Returns the largest number that the given fixed point definition can represent
 * 
 * @param input Fixed point data definition
 * @return float 
 */
float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_definition_t input);

/**
 * @brief Returns the smallest number that the given fixed point definition can represent (accounts for sign)
 * 
 * @param input Fixed point data definition
 * @return float 
 */
float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_definition_t input);


#endif // UZ_FIXEDPOINT_H
