#ifndef UZ_D_GAN_INVERTER_HW_H
#define UZ_D_GAN_INVERTER_HW_H
#include <stdint.h>

void uz_d_gan_inverter_hw_set_PWM_EN(uint32_t base_address, uint32_t PWM_on_off);
void uz_d_gan_inverter_hw_write_PWM_on_off(uint32_t base_address,uint32_t PWM_on_off);
uint32_t uz_d_gan_inverter_hw_read_PWM_on_off(uint32_t base_address);

#endif // UZ_D_GAN_INVERTER_HW_H
