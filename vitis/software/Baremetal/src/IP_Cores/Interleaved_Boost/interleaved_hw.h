#ifndef INTERLEAVED_HW_H
#define INTERLEAVED_HW_H
#include <stdint.h>
#include <stdbool.h>

#define INTERLEAVED_BOOST_NUM_FRACTIONAL_BITS	17

void interleaved_set_i1(uint32_t base_address, float i);
void interleaved_set_i2(uint32_t base_address, float i);
void interleaved_set_vout(uint32_t base_address, float v);

bool interleaved_get_u1(uint32_t base_address);
bool interleaved_get_u2(uint32_t base_address);

#endif // INTERLEAVED_HW_H
