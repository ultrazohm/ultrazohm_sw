#ifndef UZ_TRANSFORMATION_H
#define UZ_TRANSFORMATION_H

/**
 * @brief Struct for the variables of a dq0-System
 */
struct uz_dq_t{
    float d;        /**< Amplitude of the direct axis component */ 
    float q;        /**< Amplitude of the quadrature axis component */ 
    float zero;     /**< Amplitude of the zero component */ 
};

/**
 * @brief Struct for the variables of a alpha-beta-gamma-System
 * 
 */
struct uz_alphabeta_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float gamma;        /**< Amplitude of the gamma component */ 
};

/**
 * @brief Struct for the variables of a three-phase-System
 * 
 */
struct uz_UVW_t{
    float U;        /**< Amplitude of the U phase */ 
    float V;        /**< Amplitude of the V phase */ 
    float W;        /**< Amplitude of the W phase */ 
};

/**
 * @brief Calculates the dq0-components from the UVW-Phases
 * 
 * @param input uz_UVW struct
 * @param theta_el_rad electrical theta in rad
 * @return struct uz_dq_t Outputs the calculated dq0-components
 */
struct uz_dq_t uz_dq_transformation(struct uz_UVW_t input, float theta_el_rad);

/**
 * @brief Calculates the UVW-Phases from the dq0-components  
 * 
 * @param input uz_dq struct
 * @param theta_el_rad electrical theta in rad
 * @return struct uz_UVW_t Outputs the calculated UVW-phases
 */
struct uz_UVW_t uz_dq_inverse_transformation(struct uz_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta-gamma-components from the UVW-phases
 * 
 * @param input uz_UVW struct
 * @return struct uz_alphabeta Outputs the calculated alpha-beta-gamma-components
 */
struct uz_alphabeta_t uz_clarke_transformation(struct uz_UVW_t input);

/**
 * @brief Calculates the UVW-phases from the alpha-beta-gamma-components
 * 
 * @param input uz_alphabeta struct
 * @return struct uz_UVW_t Outputs the calculated UVW-phases
 */
struct uz_UVW_t uz_clarke_inverse_transformation(struct uz_alphabeta_t input);
#endif // UZ_TRANSFORMATION_H
