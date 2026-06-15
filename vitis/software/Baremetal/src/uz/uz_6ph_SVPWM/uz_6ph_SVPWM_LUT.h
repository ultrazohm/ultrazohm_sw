#ifndef UZ_6PH_SVPWM_LUT_H
#define UZ_6PH_SVPWM_LUT_H

#include <stdint.h>
#include <stddef.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

typedef struct {
    float u_z1;
    float u_z2;
} u_z1z2;

#define NUM_METHODS_6PH_SVPWM_METHODS_5_ACTIVE_SV   16
#define NUM_SECTORS_24   24
#define NUM_SV_5_ACTIVE    7

typedef enum {
    CSVPWM_24_2L_1ML_2M_M13_SV_SEQUENCE,
    CSVPWM_24_2L_1ML_2M_M24_SV_SEQUENCE,
    CSVPWM_24_2L_1ML_2M_M23_SV_SEQUENCE,
    CSVPWM_24_3L_2M_M12_SV_SEQUENCE,
    CSVPWM_24_3L_2M_M34_SV_SEQUENCE,
    CSVPWM_24_3L_2M_M32_SV_SEQUENCE,
    CSVPWM_24_2L_1ML_2M_L13_M13_SV_SEQUENCE,
    CSVPWM_24_2L_1ML_2M_L23_M12_SV_SEQUENCE,
    CSVPWM_24_2L_3M_L13_M123_SV_SEQUENCE,
    CSVPWM_24_2L_3M_M214_SV_SEQUENCE,
    CSVPWM_24_2L_3M_M314_SV_SEQUENCE,
    CSVPWM_24_1L_1ML_3M_L2_M132_SV_SEQUENCE,
    CSVPWM_24_1ML_4M_M1432_SV_SEQUENCE,
    CSVPWM_24_1L_4M_L1_M3214_SV_SEQUENCE,
    CSVPWM_24_1L_4M_L2_M4132_SV_SEQUENCE,
    CSVPWM_24_1L_4M_L3_M3241_SV_SEQUENCE
} svpwm_5active_2zero_24sector_SV_sequence_t;

extern const uint8_t svpwm_5active_2zero_24sector_SV_sequence[NUM_METHODS_6PH_SVPWM_METHODS_5_ACTIVE_SV][NUM_SECTORS_24][NUM_SV_5_ACTIVE];


#define NUM_METHODS_6PH_SVPWM_METHODS_4_ACTIVE_SV   18
#define NUM_SECTORS_24        24
#define NUM_SV_4_ACTIVE    6

typedef enum {
    CSVPWM_24_2L_1ML_1M_M2_SV_SEQUENCE,
    CSVPWM_24_2L_1ML_1M_M3_SV_SEQUENCE,
    CSVPWM_24_2L_2M_M24_SV_SEQUENCE,
    CSVPWM_24_2L_2M_M34_SV_SEQUENCE,
    CSVPWM_24_3L_1M_M2_SV_SEQUENCE,
    CSVPWM_24_3L_1M_M3_SV_SEQUENCE,
    CSVPWM_24_1L_3M_L1_M314_SV_SEQUENCE,
    CSVPWM_24_1L_3M_L2_M214_SV_SEQUENCE,
    CSVPWM_24_1L_3M_L3_M123_SV_SEQUENCE,
    CSVPWM_24_1ML_3M_M123_SV_SEQUENCE,
    CSVPWM_24_1L_1ML_2M_M13_SV_SEQUENCE,
    CSVPWM_24_1L_1ML_2M_L2_M12_SV_SEQUENCE,
    CSVPWM_24_2L_2M_L13_M13_SV_SEQUENCE,
    CSVPWM_24_2L_2M_L23_M12_SV_SEQUENCE,
    CSVPWM_24_4M_M3241_A_SV_SEQUENCE,
    CSVPWM_24_4M_M4132_B_SV_SEQUENCE,
    CSVPWM_24_4M_M3214_C_SV_SEQUENCE,
    CSVPWM_24_4M_M1432_D_SV_SEQUENCE
} svpwm_4active_2zero_24sector_SV_sequence_t;

extern const uint8_t svpwm_4active_2zero_24sector_SV_sequence[NUM_METHODS_6PH_SVPWM_METHODS_4_ACTIVE_SV][NUM_SECTORS_24][NUM_SV_4_ACTIVE];


const float (*get_inv_T_tv_Matrix_4active_sector_24(svpwm_4active_2zero_24sector_SV_sequence_t version, uint8_t sector24))[4];
//	const float (*matrix)[4] = get_T_tv_Matrix_sector_24(1,1);
//	float a = matrix[0][0];

const float (*get_inv_T_tv_Matrix_5active_sector_24(svpwm_5active_2zero_24sector_SV_sequence_t version, uint8_t sector24))[4];


int find_nearest_index(const float *arr, size_t n, float value);

typedef enum {
    CONTINIOUS,
    DISCONTINIOUS1,
    DISCONTINIOUS2
} C_D1_D2;



float return_svpwm_4active_opt_d(svpwm_4active_2zero_24sector_SV_sequence_t version, float theta, float kappa, float M);


u_z1z2 return_svpwm_4active_optz1z2(svpwm_4active_2zero_24sector_SV_sequence_t version, float theta, float kappa, float M, int sector_24, float V_DC_Volts);

u_z1z2 return_svpwm_4active_optz1z2_scaled(svpwm_4active_2zero_24sector_SV_sequence_t version, float theta, float M, int sector_24, float V_DC_Volts);

u_z1z2 return_svpwm_5active_optz1z2_D1(svpwm_5active_2zero_24sector_SV_sequence_t version, float theta, float kappa, float M, int sector_24, float V_DC_Volts);

u_z1z2 return_svpwm_5active_optz1z2_D2(svpwm_5active_2zero_24sector_SV_sequence_t version, float theta, float kappa, float M, int sector_24, float V_DC_Volts);

u_z1z2 return_svpwm_5active_optz1z2(svpwm_5active_2zero_24sector_SV_sequence_t version, float theta, float kappa, float M, int sector_24, float V_DC_Volts);

u_z1z2 return_svpwm_5active_optz1z2_scaled(svpwm_5active_2zero_24sector_SV_sequence_t version, float theta, float kappa, float M, int sector_24, float V_DC_Volts);





#endif //UZ_6PH_SVPWM_LUT_H
