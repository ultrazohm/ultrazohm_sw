#ifndef UZ_TRANSFORMATION_H
#define UZ_TRANSFORMATION_H

struct uz_dq{
    float d;
    float q;
    float zero;
};

struct uz_alphabeta{
    float alpha;
    float beta;
    float gamma;
};

struct uz_UVW{
    float U;
    float V;
    float W;
};

struct uz_dq uz_dq_Transformation(struct uz_UVW input, float theta_el);
struct uz_UVW uz_inverse_dq_Transformation(struct uz_dq input, float theta_el);
struct uz_alphabeta uz_clarke_Transformation(struct uz_UVW input);
struct uz_UVW uz_inverse_clarke_Transformation(struct uz_alphabeta input);
#endif // UZ_TRANSFORMATION_H
