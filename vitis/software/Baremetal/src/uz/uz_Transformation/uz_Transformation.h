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
 * @brief Struct for the variables of an alpha-beta nine-phase system
 * 
 */
typedef struct uz_9ph_alphabeta_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float z1;           /**< Amplitude of the z1 component */ 
    float z2;           /**< Amplitude of the z2 component */
    float x1;           /**< Amplitude of the x1 component */
    float y1;           /**< Amplitude of the y1 component */
    float x2;           /**< Amplitude of the x2 component */
    float y2;           /**< Amplitude of the y2 component */
    float z3;           /**< Amplitude of the z3 component */
}uz_9ph_alphabeta_t;

/**
 * @brief Struct for the variables of an alpha-beta six-phase system
 * 
 */
typedef struct uz_6ph_alphabeta_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float z1;           /**< Amplitude of the z1 component */ 
    float z2;           /**< Amplitude of the z2 component */
    float x1;           /**< Amplitude of the x1 component */
    float y1;           /**< Amplitude of the y1 component */
}uz_6ph_alphabeta_t;

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
typedef struct uz_6ph_abc_t{
    float a1;        /**< Amplitude of the a1 phase */ 
    float b1;        /**< Amplitude of the b1 phase */ 
    float c1;        /**< Amplitude of the c1 phase */ 
    float a2;        /**< Amplitude of the a2 phase */ 
    float b2;        /**< Amplitude of the b2 phase */ 
    float c2;        /**< Amplitude of the c2 phase */ 
}uz_6ph_abc_t;

/**
 * @brief Calculates the dq0-components from the UVW-Phases
 * 
 * @param input uz_UVW struct
 * @param theta_el_rad electrical theta in rad
 * @return uz_dq_t Outputs the calculated dq0-components
 */
uz_3ph_dq_t uz_transformation_3ph_abc_to_dq(uz_3ph_abc_t input, float theta_el_rad);

/**
 * @brief Calculates the UVW-Phases from the dq0-components  
 * 
 * @param input uz_dq struct
 * @param theta_el_rad electrical theta in rad
 * @return uz_UVW_t Outputs the calculated UVW-phases
 */
uz_3ph_abc_t uz_transformation_3ph_dq_to_abc(uz_3ph_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta-gamma-components from the UVW-phases
 * 
 * @param input uz_UVW struct
 * @return uz_alphabeta Outputs the calculated alpha-beta-gamma-components
 */
uz_3ph_alphabeta_t uz_transformation_3ph_abc_to_alphabeta(uz_3ph_abc_t input);

/**
 * @brief Calculates the UVW-phases from the alpha-beta-gamma-components
 * 
 * @param input uz_alphabeta struct
 * @return uz_UVW_t Outputs the calculated UVW-phases
 */
uz_3ph_abc_t uz_transformation_3ph_alphabeta_to_abc(uz_3ph_alphabeta_t input);



/**
 * @brief Calculates the dq-components from the alpha-beta components
 * 
 * @param input uz_alphabeta_t struct
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_dq_t outputs the calculated dq-components
 */
uz_3ph_dq_t uz_transformation_3ph_alphabeta_to_dq(uz_3ph_alphabeta_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta components from the dq-components
 * 
 * @param input uz_dq struct
 * @param theta_el_rad electrical theta in rad
 * @return uz_alphabeta_t outputs the calculated alpha/beta values
 */
uz_3ph_alphabeta_t uz_transformation_3ph_dq_to_alphabeta(uz_3ph_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta-gamma-components from the nine phase abc-phases
 * 
 * @param input uz_abc_9ph_t
 * @return uz_alphabeta_9ph_t Outputs the calculated stationary reference frame components
 */
uz_9ph_alphabeta_t uz_transformation_9ph_abc_to_alphabeta(uz_9ph_abc_t input);

/**
 * @brief Calculates the abc-phases from the stationary reference frame components
 * 
 * @param input uz_alphabeta_9ph_t struct
 * @return struct uz_Uabc_t Outputs the calculated abc-phases
 */
uz_9ph_abc_t uz_transformation_9ph_alphabeta_to_abc(uz_9ph_alphabeta_t input);

/**
 * @brief Calculates the alpha-beta-gamma-components from the six phase abc-phases
 * 
 * @param input uz_abc_6ph_t
 * @return struct uz_alphabeta_9ph_t Outputs the calculated stationary reference frame components
 */
uz_6ph_alphabeta_t uz_transformation_6ph_abc_to_alphabeta(uz_6ph_abc_t input);

/**
 * @brief Calculates the abc-phases from the stationary reference frame components
 * 
 * @param input uz_alphabeta_6ph_t struct
 * @return struct uz_abc_t Outputs the calculated abc-phases
 */
uz_6ph_abc_t uz_transformation_6ph_alphabeta_to_abc(uz_6ph_alphabeta_t input);


#endif // UZ_TRANSFORMATION_H
