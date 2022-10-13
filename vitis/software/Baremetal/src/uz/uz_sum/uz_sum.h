#ifndef UZ_SUM_H
#define UZ_SUM_H

typedef struct uz_sum_t uz_sum_t;
uz_sum_t* uz_sum_init(void);

void uz_sum_step(uz_sum_t* self, float a, float b, float c);
float uz_sum_get_sum(uz_sum_t* self);
float uz_sum_get_integral_over_sum(uz_sum_t* self);


#endif // UZ_SUM_H
