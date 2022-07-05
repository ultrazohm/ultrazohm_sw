#ifndef UZ_TRANSFORMATION_H
#define UZ_TRANSFORMATION_H

/**
 * @brief Struct for the variables of a dq0-System
 */
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

/**
 * @brief struct for variables of an alpha-beta-system six-phase-system
 * 
 */
typedef struct uz_6ph_alphabeta_t{
    float alpha;    /**< Amplitude of the alpha component */
    float beta;     /**< Amplitude of the beta component */
    float x;        /**< Amplitude of the x component */
    float y;        /**< Amplitude of the y component */
    float z1;       /**< Amplitude of the z1 component */
    float z2;       /**< Amplitude of the z2 component */
}uz_6ph_alphabeta_t;

/**
 * @brief struct for variables of an abc six-phase-system
 * 
 */
typedef struct uz_6ph_abc_t{
    float a1;   /**< Amplitude of the a1 phase */
    float b1;   /**< Amplitude of the b1 phase */
    float c1;   /**< Amplitude of the c1 phase */
    float a2;   /**< Amplitude of the a2 phase */
    float b2;   /**< Amplitude of the b2 phase */
    float c2;   /**< Amplitude of the c2 phase */
}uz_6ph_abc_t;


/**
 * @brief Struct for the variables of an alpha-beta nine-phase system
 * 
 */
typedef struct uz_9ph_alphabeta_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float x1;           /**< Amplitude of the x1 component */ 
    float y1;           /**< Amplitude of the y1 component */
    float x2;           /**< Amplitude of the x2 component */
    float y2;           /**< Amplitude of the y2 component */
    float x3;           /**< Amplitude of the x3 component */
    float y3;           /**< Amplitude of the y3 component */
    float zero;         /**< Amplitude of the zero component */
}uz_9ph_alphabeta_t;

/**
 * @brief Struct for the variable of an rotating dq-frame for nine-phase systems
 * 
 */
typedef struct uz_9ph_dq_t{
    float d;    /**< Amplitude of the d component */
    float q;    /**< Amplitude of the q component */
    float x1;   /**< Amplitude of the x1 component */
    float y1;   /**< Amplitude of the y1 component */
    float x2;   /**< Amplitude of the x2 component */
    float y2;   /**< Amplitude of the y2 component */
    float x3;   /**< Amplitude of the x3 component */
    float y3;   /**< Amplitude of the y3 component */
    float zero; /**< Amplitude of the zero component */
}uz_9ph_dq_t;

/**
 * @brief Struct for the natural variables of a nine-phase system
 * 
 */
typedef struct uz_9ph_abc_t{
    float a1;        /**< Amplitude of the a1 phase */ 
    float b1;        /**< Amplitude of the b1 phase */ 
    float c1;        /**< Amplitude of the c1 phase */ 
    float a2;        /**< Amplitude of the a2 phase */ 
    float b2;        /**< Amplitude of the b2 phase */ 
    float c2;        /**< Amplitude of the c2 phase */ 
    float a3;        /**< Amplitude of the a3 phase */ 
    float b3;        /**< Amplitude of the b3 phase */ 
    float c3;        /**< Amplitude of the c3 phase */ 
}uz_9ph_abc_t;

/**
 * @brief Struct for the natural variables of a six-phase system
 * 
 */

/**
 * @brief Calculates the dq0-components from the abc-Phases
 * 
 * @param input uz_3ph_abc_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_3ph_dq_t Outputs the calculated dq0-components
 */
uz_3ph_dq_t uz_transformation_3ph_abc_to_dq(uz_3ph_abc_t input, float theta_el_rad);

/**
 * @brief Calculates the abc-phases from the dq0-components  
 * 
 * @param input uz_3ph_dq_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_3ph_abc_t Outputs the calculated abc-phases
 */
uz_3ph_abc_t uz_transformation_3ph_dq_to_abc(uz_3ph_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta-gamma-components from the abc-phases
 * 
 * @param input uz_3ph_abc_t struct
 * @return uz_3ph_alphabeta_t Outputs the calculated alpha-beta-gamma-components
 */
uz_3ph_alphabeta_t uz_transformation_3ph_abc_to_alphabeta(uz_3ph_abc_t input);

/**
 * @brief Calculates the abc-phases from the alpha-beta-gamma-components
 * 
 * @param input uz_3ph_alphabeta_t struct
 * @return uz_3ph_abc_t Outputs the calculated abc-phases
 */
uz_3ph_abc_t uz_transformation_3ph_alphabeta_to_abc(uz_3ph_alphabeta_t input);

/**
 * @brief Calculates the dq0-components from the alpha-beta-gamma-components
 * 
 * @param input uz_3ph_alphabeta_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_3ph_dq_t outputs the calculated dq-components
 */
uz_3ph_dq_t uz_transformation_3ph_alphabeta_to_dq(uz_3ph_alphabeta_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta components from the dq-components
 * 
 * @param input uz_3ph_dq_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_3ph_alphabeta_t outputs the calculated alpha-beta-gamma-components
 */
uz_3ph_alphabeta_t uz_transformation_3ph_dq_to_alphabeta(uz_3ph_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the 6-phase alpha-beta components from the phase-amplitudes of an asymmetric (30 degree) six phase system
 * 
 * @param input uz_6ph_abc_t input of the phase amplitudes
 * @return uz_6ph_alphabeta_t outputs the calculated six-phase alpha-beta components
 */
uz_6ph_alphabeta_t uz_transformation_asym30deg_6ph_abc_to_alphabeta(uz_6ph_abc_t input);

/**
 * @brief Calculates the abc-phases from the alphabeta components of an asymmetric (30 degree) six phase system
 * 
 * @param input uz_6ph_alphabeta_t struct
 * @return uz_6ph_abc_t outputs the calculated abc-phases
 */
uz_6ph_abc_t uz_transformation_asym30deg_6ph_alphabeta_to_abc(uz_6ph_alphabeta_t input);

/**
 * @brief Calculates the stationary reference frame values from abc-phases using the ninephase VSD Transformation
 * 
 * @param input uz_9ph_abc_t
 * @return uz_9ph_alphabeta_t Outputs the calculated stationary reference frame components
 */
uz_9ph_alphabeta_t uz_transformation_9ph_abc_to_alphabeta(uz_9ph_abc_t input);

/**
 * @brief Calculates the abc frame values from the stationary reference frame values using the inverse ninephase VSD Transformation
 * 
 * @param input uz_9ph_alphabeta_t struct
 * @return uz_9ph_abc_t Outputs the calculated abc-phases
 */
uz_9ph_abc_t uz_transformation_9ph_alphabeta_to_abc(uz_9ph_alphabeta_t input);

/**
 * @brief Calculates the dq components from alpha and beta and leaves the additional systems untouched
 * 
 * @param input uz_9ph_alphabeta_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_9ph_dq_t Outputs the calculated stationary and rotating reference frame values
 */
uz_9ph_dq_t uz_transformation_9ph_alphabeta_to_dq(uz_9ph_alphabeta_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha and beta components from the dq values and leaves the additional systems untouched
 * 
 * @param input uz_9ph_dq_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_9ph_alphabeta_t Outputs the calculated stationary reference frame values
 */
uz_9ph_alphabeta_t uz_transformation_9ph_dq_to_alphabeta(uz_9ph_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the stationary reference frame values from the phase values using the VSD transformation. Afterwards calculates the dq components from alpha and beta only while leaving the additional stationary reference frame components untouched.
 * 
 * @param input uz_9ph_abc_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_9ph_dq_t Outputs the calculated stationary and rotating reference frame values
 */
uz_9ph_dq_t uz_transformation_9ph_abc_to_dq(uz_9ph_abc_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha beta components from the dq components. Uses the stationary reference frame values to calculate the the abc values with the inverse VSD transformation.
 * 
 * @param input uz_9ph_dq_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_9ph_abc_t Outputs the calculated abc-phases
 */
uz_9ph_abc_t uz_transformation_9ph_dq_to_abc(uz_9ph_dq_t input, float theta_el_rad);

#endif // UZ_TRANSFORMATION_H
