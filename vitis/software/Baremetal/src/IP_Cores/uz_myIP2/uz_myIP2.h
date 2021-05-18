#ifndef UZ_MYIP_H
#define UZ_MYIP_H
#include <stdint.h>

typedef struct uz_myIP2 uz_myIP2;

/**
 * @brief Initializes an instance of the IP-Core
 * 
 * @param self 
 * @return uz_myIP2* 
 */
uz_myIP2* uz_myIP2_init(uz_myIP2* self);

/**
 * @brief Calculates C=A*B
 * 
 * @param self Pointer to IP-Core instance that was initialized with init function
 * @param A First value
 * @param B Second value
 * @return int32_t Result
 */
int32_t uz_myIP2_multiply(uz_myIP2* self, int32_t A, int32_t B);

#endif // UZ_MYIP_H