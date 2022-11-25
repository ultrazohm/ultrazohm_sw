#include "test.h"
#include "hls_math.h"

static uz_3ph_alphabeta_t uz_transformation_3ph_abc_to_alphabeta(uz_3ph_abc_t input);
uz_3ph_dq_t uz_transformation_3ph_alphabeta_to_dq(uz_3ph_alphabeta_t input, float theta_el_rad);

uz_3ph_dq_t uz_transformation_3ph_abc_to_dq(uz_3ph_abc_t input, float theta_el_rad)
{
    uz_3ph_alphabeta_t ab = uz_transformation_3ph_abc_to_alphabeta(input);
    uz_3ph_dq_t output= uz_transformation_3ph_alphabeta_to_dq(ab,theta_el_rad);
    return (output);
}

uz_3ph_alphabeta_t uz_transformation_3ph_abc_to_alphabeta(uz_3ph_abc_t input)
{
    uz_3ph_alphabeta_t output = {
        .alpha = 0.66f * (input.a - 0.5f*((input.b) - (input.c)) ),
        .beta = 0.66f* ((input.b *0.866f) - (input.c * (0.866f))),
        .gamma = 0.33f* (input.a + input.b + input.c)};
    return (output);
}

uz_3ph_dq_t uz_transformation_3ph_alphabeta_to_dq(uz_3ph_alphabeta_t input, float theta_el_rad)
{
    float sin_coefficient = 0.0f;
    float cos_coefficient = 0.0f;
    sincosf(theta_el_rad,&sin_coefficient, &cos_coefficient);
    uz_3ph_dq_t output = {
        .d = (cos_coefficient * input.alpha) + (sin_coefficient * input.beta),
        .q = (-sin_coefficient * input.alpha) + (cos_coefficient * input.beta),
        .zero = input.gamma};
    return (output);
}







