#ifndef UZ_FIXEDPOINT_H
#define UZ_FIXEDPOINT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Configuration struct for the fixed point data type 
 * 
 */
struct uz_fixedpoint_definition_t{
    const bool is_signed; /**< Determines if the fixed point value is signed or unsigned */
    const int32_t fractional_bits; /**< Number of bits for the the fraction */
    const int32_t integer_bits; /**< Number of bits for the integer part */
};

typedef struct uz_fixedpoint_definition_t uz_fixedpoint_definition_t;

/**
 * @brief Reads a fixed-point data type from AXI and converts it to float given the fixed-point definition
 * 
 * @param memory_address Address of the AXI register
 * @param fixedpoint_definition Definition of fixedpoint data type
 * @return float 
 */
float uz_fixedpoint_axi_read(uint32_t memory_address, struct uz_fixedpoint_definition_t fixedpoint_definition);

/**
 * @brief Converts the input data to a fixedpoint data type, rounds to nearest integer, and writes it to AXI
 * 
 * @param memory_address Address of the AXI register
 * @param data Data that is written to AXI
 * @param fixedpoint_definition Definition of fixedpoint data type
 */
void uz_fixedpoint_axi_write(uint32_t memory_address,float data, uz_fixedpoint_definition_t fixedpoint_definition);

/**
 * @brief Checks that the data is within the min/max that is representable by the fixed-point data type
 * 
 * @param data Data that is checked
 * @param fixedpoint_definition Definition of fixedpoint data type
 */
void uz_fixedpoint_check_limits(float data, struct uz_fixedpoint_definition_t fixedpoint_definition);

/**
 * @brief Calculates the precision of the specified data type
 * 
 * @param input Definition of fixed-point data type
 * @return float 
 */
float uz_fixedpoint_get_precision(struct uz_fixedpoint_definition_t input);

/**
 * @brief Calculates the biggest representable value of the given data type definition
 * 
 * @param input Definition of fixed-point data type
 * @return float 
 */
float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_definition_t input);

/**
 * @brief Calculates the smallest representable valueof the given data type definition
 * 
 * @param input Definition of fixed-point data type
 * @return float 
 */
float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_definition_t input);

// Utility / helper functions
float uz_fixedpoint_convert_unsigned_to_float(uint32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition);
float uz_fixedpoint_convert_signed_to_float(int32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition);
uint32_t uz_fixedpoint_convert_to_unsigned_fixed(float data, struct uz_fixedpoint_definition_t fixed_data);
int32_t uz_fixedpoint_convert_to_signed_fixed(float data, struct uz_fixedpoint_definition_t fixed_data);

#endif // UZ_FIXEDPOINT_H
