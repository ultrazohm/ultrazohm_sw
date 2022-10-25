#ifndef UZ_EXP_SMOOTH_H
#define UZ_EXP_SMOOTH_H

typedef struct UZ_EXP_SMOOTH_t UZ_EXP_SMOOTH_t;
UZ_EXP_SMOOTH_t* UZ_EXP_SMOOTH_init(float alpha);
float uz_EXP_SMOOTH_sample(UZ_EXP_SMOOTH_t* self, float input);



#endif // UZ_EXP_SMOOTH_H
