// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.c" 2
# 17 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.h" 1


# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_Transformation.h" 1






struct uz_dq_t{
    float d;
    float q;
    float zero;
};





struct uz_alphabeta_t{
    float alpha;
    float beta;
    float gamma;
};





struct uz_UVW_t{
    float U;
    float V;
    float W;
};
# 40 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_Transformation.h"
struct uz_dq_t uz_dq_transformation(struct uz_UVW_t input, float theta_el_rad);
# 49 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_Transformation.h"
struct uz_UVW_t uz_dq_inverse_transformation(struct uz_dq_t input, float theta_el_rad);







struct uz_alphabeta_t uz_clarke_transformation(struct uz_UVW_t input);







struct uz_UVW_t uz_clarke_inverse_transformation(struct uz_alphabeta_t input);
# 4 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.h" 2

struct uz_PMSM_t{
    float R_ph_Ohm;
    float Ld_Henry;
    float Lq_Henry;
    float Psi_PM_Vs;
    float polePairs;
    float J_kg_m_squared;
    float I_max_Ampere;
};
# 23 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.h"
struct uz_dq_t uz_FOC_linear_decoupling(struct uz_PMSM_t config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec);
# 18 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_linear_decoupling.c" 2


struct uz_dq_t uz_FOC_linear_decoupling(struct uz_PMSM_t config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec) {



 struct uz_dq_t u_dq_vor_Volts = {0};
 u_dq_vor_Volts.d = i_actual_Ampere.q * -1.0f * config.Lq_Henry * omega_el_rad_per_sec;
 u_dq_vor_Volts.q = ( (i_actual_Ampere.d* config.Ld_Henry) + config.Psi_PM_Vs) * omega_el_rad_per_sec;
 return (u_dq_vor_Volts);
}
