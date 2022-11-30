#include "ap_fixed.h"

typedef struct uz_3ph_dq_t{
    float d;        /**< Amplitude of the direct axis component */
    float q;        /**< Amplitude of the quadrature axis component */
    float zero;     /**< Amplitude of the zero component */
}uz_3ph_dq_t;

/**
 * @brief Struct for the variables of a alpha-beta-gamma-System
 *
 */
typedef struct uz_3ph_alphabeta_t{
    float alpha;        /**< Amplitude of the alpha component */
    float beta;         /**< Amplitude of the beta component */
    float gamma;        /**< Amplitude of the gamma component */
}uz_3ph_alphabeta_t;

/**
 * @brief Struct for the variables of a three-phase-System
 *
 */
typedef struct uz_3ph_abc_t{
    float a;        /**< Amplitude of the a phase (U) */
    float b;        /**< Amplitude of the b phase (V) */
    float c;        /**< Amplitude of the c phase (W) */
}uz_3ph_abc_t;

uz_3ph_dq_t uz_transformation_3ph_abc_to_dq(uz_3ph_abc_t input, float theta_el_rad);
