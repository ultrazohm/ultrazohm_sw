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
 * @brief Struct for the variables of an alpha-beta 9 phase system
 * 
 */
struct uz_alphabeta_9ph_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float o1;           /**< Amplitude of the o1 component */ 
    float o2;           /**< Amplitude of the o2 component */
    float x1;           /**< Amplitude of the x1 component */
    float y1;           /**< Amplitude of the y1 component */
    float x2;           /**< Amplitude of the x2 component */
    float y2;           /**< Amplitude of the y2 component */
    float zero;         /**< Amplitude of the zero component */
};

/**
 * @brief Struct for the variables of an alpha-beta 6 phase system
 * 
 */
struct uz_alphabeta_6ph_t{
    float alpha;        /**< Amplitude of the alpha component */ 
    float beta;         /**< Amplitude of the beta component */ 
    float o1;           /**< Amplitude of the o1 component */ 
    float o2;           /**< Amplitude of the o2 component */
    float x1;           /**< Amplitude of the x1 component */
    float y1;           /**< Amplitude of the y1 component */
};

/**
 * @brief Struct for the variables of a nine-phase-System
 * 
 */
struct uz_abc_9ph_t{
    float a1;        /**< Amplitude of the a1 phase */ 
    float b1;        /**< Amplitude of the b1 phase */ 
    float c1;        /**< Amplitude of the c1 phase */ 
    float a2;        /**< Amplitude of the a2 phase */ 
    float b2;        /**< Amplitude of the b2 phase */ 
    float c2;        /**< Amplitude of the c2 phase */ 
    float a3;        /**< Amplitude of the a3 phase */ 
    float b3;        /**< Amplitude of the b3 phase */ 
    float c3;        /**< Amplitude of the c3 phase */ 
};

/**
 * @brief Struct for the variables of a six-phase-System
 * 
 */
struct uz_abc_6ph_t{
    float a1;        /**< Amplitude of the a1 phase */ 
    float b1;        /**< Amplitude of the b1 phase */ 
    float c1;        /**< Amplitude of the c1 phase */ 
    float a2;        /**< Amplitude of the a2 phase */ 
    float b2;        /**< Amplitude of the b2 phase */ 
    float c2;        /**< Amplitude of the c2 phase */ 
};

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

/**
 * @brief Calculates the dq0-components from the alpha-beta components
 * 
 * @param matrixval linematrix containing the values of the transformation matrix
 * @param electricval electrical values (either alpha bete or abc) input as array
 * @return float that is the return value for alpha beta transformation or inverse transformation depending on linematrix
 */
float uz_9ph_arraymul(int line, float matrixval[9][9], float electricval[9]);

/**
 * @brief Calculates the dq0-components from the alpha-beta components
 * 
 * @param input uz_alphabeta_t struct where gamma is unused
 * @param theta_el_rad electrical theta in rad
 * @return struct uz_dq_t Outputs the calculated dq0-components
 */
uz_dq_t uz_ab_to_dq_transformation(uz_alphabeta_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta components from the dq0-components, ignoring the zero component
 * 
 * @param input uz_dq struct
 * @param theta_el_rad electrical theta in rad
 * @return struct uz_alphabeta_t Outputs the calculated UVW-phases
 */
uz_alphabeta_t uz_dq_to_ab_inverse_transformation(uz_dq_t input, float theta_el_rad);

/**
 * @brief Calculates the alpha-beta-gamma-components from the nine phase abc-phases
 * 
 * @param input uz_abc_9ph_t
 * @return struct uz_alphabeta_9ph_t Outputs the calculated alpha-beta-gamma-components
 */
struct uz_alphabeta_9ph_t uz_9ph_clarke_transformation(struct uz_abc_9ph_t input);

/**
 * @brief Calculates the abc-phases from the alpha-beta-gamma-components
 * 
 * @param input uz_alphabeta_9ph_t struct
 * @return struct uz_Uabc_t Outputs the calculated abc-phases
 */
struct uz_abc_9ph_t uz_9ph_clarke_inverse_transformation(struct uz_alphabeta_9ph_t input);

/**
 * @brief Calculates the alpha-beta-gamma-components from the six phase abc-phases
 * 
 * @param input uz_abc_6ph_t
 * @return struct uz_alphabeta_9ph_t Outputs the calculated alpha-beta-gamma-components
 */
struct uz_alphabeta_6ph_t uz_6ph_clarke_transformation(struct uz_abc_6ph_t input);

/**
 * @brief Calculates the abc-phases from the alpha-beta-gamma-components
 * 
 * @param input uz_alphabeta_6ph_t struct
 * @return struct uz_abc_t Outputs the calculated abc-phases
 */
struct uz_abc_6ph_t uz_6ph_clarke_inverse_transformation(struct uz_alphabeta_6ph_t input);


#endif // UZ_TRANSFORMATION_H
