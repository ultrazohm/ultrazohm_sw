#ifndef UZ_MYIP_H
#define UZ_MYIP_H
#include <stdint.h>

typedef struct uz_myIP uz_myIP;

uz_myIP* uz_myIP_init(uz_myIP* self);
int32_t uz_myIP_multiply(uz_myIP* self, int32_t A, int32_t B);

#endif // UZ_MYIP_H