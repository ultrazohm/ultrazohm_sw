#ifndef UZ_FILTER_CUMULATIVEAVG_H
#define UZ_FILTER_CUMULATIVEAVG_H

typedef struct uz_filter_cumulativeavg_t uz_filter_cumulativeavg_t; 

uz_filter_cumulativeavg_t* uz_filter_cumulativeavg_init(void);
float uz_filter_cumulativeavg_step(uz_filter_cumulativeavg_t *self, float current_value);
void uz_filter_cumulativeavg_reset(uz_filter_cumulativeavg_t *self);


#endif // UZ_FILTER_CUMULATIVEAVG_H
