#ifndef UZ_MYIP_H
#define UZ_MYIP_H
#include <stdint.h>

typedef struct uz_myIP2 uz_myIP2;

uz_myIP2* uz_myIP2_init(uz_myIP2* self);
int32_t uz_myIP2_multiply(uz_myIP2* self, int32_t A, int32_t B);

#endif // UZ_MYIP_H