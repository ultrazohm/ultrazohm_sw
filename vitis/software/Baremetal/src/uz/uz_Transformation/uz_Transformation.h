#ifndef UZ_TRANSFORMATION_H
#define UZ_TRANSFORMATION_H

/**
 * @brief Struct for the variables of a dq0-System
 */
typedef struct uz_dq_t{
    float d;        /**< Amplitude of the direct axis component */ 
    float q;        /**< Amplitude of the quadrature axis component */ 
    float zero;     /**< Amplitude of the zero component */ 
}uz_dq_t;

/**
 * @brief Struct for the variables of a alpha-beta-gamma-System
 * 
 */
typedef struct uz_alphabeta_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float gamma;        /**< Amplitude of the gamma component */ 
}uz_alphabeta_t;

/**
 * @brief Struct for the variables of a three-phase-System
 * 
 */
typedef struct uz_UVW_t{
    float U;        /**< Amplitude of the U phase */ 
    float V;        /**< Amplitude of the V phase */ 
    float W;        /**< Amplitude of the W phase */ 
}uz_UVW_t;

/**
 * @brief Calculates the dq0-components from the UVW-Phases
 * 
 * @param input uz_UVW struct
 * @param theta_el_rad electrical theta in rad
 * @return uz_dq_t Outputs the calculated dq0-components
 */
uz_dq_t uz_dq_transformation(uz_UVW_t input, float theta_el_rad);

/**
 * @brief Calculates the UVW-Phases from the dq0-components  
 * 
 * @param input uz_dq struct
 * @param theta_el_rad electrical theta in rad
 * @return uz_UVW_t Outputs the calculated UVW-phases
 */
uz_UVW_t uz_dq_inverse_transformation(uz_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta-gamma-components from the UVW-phases
 * 
 * @param input uz_UVW struct
 * @return uz_alphabeta Outputs the calculated alpha-beta-gamma-components
 */
uz_alphabeta_t uz_clarke_transformation(uz_UVW_t input);

/**
 * @brief Calculates the UVW-phases from the alpha-beta-gamma-components
 * 
 * @param input uz_alphabeta struct
 * @return uz_UVW_t Outputs the calculated UVW-phases
 */
uz_UVW_t uz_clarke_inverse_transformation(uz_alphabeta_t input);
#endif // UZ_TRANSFORMATION_H
