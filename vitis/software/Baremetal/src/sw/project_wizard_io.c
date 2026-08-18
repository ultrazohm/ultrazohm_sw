/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */
#include "../include/project_wizard_io.h"

#include <stddef.h>

#include "../globalData.h"
#include "../IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

extern DS_Data Global_Data;

static uz_axi_gpio_t* project_wizard_io_slot_to_gpio(project_wizard_axi_gpio_slot_t slot)
{
    switch (slot) {
    case AXI_GPIO_SLOT_D1:
        return Global_Data.objects.axi_gpio_d1;
    case AXI_GPIO_SLOT_D2:
        return Global_Data.objects.axi_gpio_d2;
    case AXI_GPIO_SLOT_D3:
        return Global_Data.objects.axi_gpio_d3;
    default:
        return NULL;
    }
}

bool project_wizard_io_read(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin)
{
    uz_axi_gpio_t* gpio = project_wizard_io_slot_to_gpio(slot);
    if (gpio == NULL) {
        return false;
    }
    return uz_axi_gpio_read_pin_zero_based(gpio, (uint32_t)pin);
}

void project_wizard_io_write(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin, project_wizard_io_level_t level)
{
    uz_axi_gpio_t* gpio = project_wizard_io_slot_to_gpio(slot);
    if (gpio == NULL) {
        return;
    }
    uz_axi_gpio_write_pin_zero_based(gpio, (uint32_t)pin, level == HIGH);
}

void project_wizard_io_set(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin)
{
    project_wizard_io_write(slot, pin, HIGH);
}

void project_wizard_io_clear(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin)
{
    project_wizard_io_write(slot, pin, LOW);
}
