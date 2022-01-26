#ifndef UZ_ERRORHANDLER_HW_H
#define UZ_ERRORHANDLER_HW_H
#include <stdint.h>

void uz_errorhandler_hw_write_ERROR(uint32_t base_address,int32_t A);
void uz_errorhandler_hw_write_MASK(uint32_t base_address,int32_t B);
int32_t uz_errorhandler_hw_read_ERROR(uint32_t base_address);
int32_t uz_errorhandler_hw_read_MASK(uint32_t base_address);

#endif // UZ_ERRORHANDLER_HW_H
