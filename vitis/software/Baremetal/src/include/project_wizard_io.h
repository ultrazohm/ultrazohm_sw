/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    LOW = false,
    HIGH = true
} project_wizard_io_level_t;

typedef enum {
    DIG_00 = 0U,
    DIG_01 = 1U,
    DIG_02 = 2U,
    DIG_03 = 3U,
    DIG_04 = 4U,
    DIG_05 = 5U,
    DIG_06 = 6U,
    DIG_07 = 7U,
    DIG_08 = 8U,
    DIG_09 = 9U,
    DIG_10 = 10U,
    DIG_11 = 11U,
    DIG_12 = 12U,
    DIG_13 = 13U,
    DIG_14 = 14U,
    DIG_15 = 15U,
    DIG_16 = 16U,
    DIG_17 = 17U,
    DIG_18 = 18U,
    DIG_19 = 19U,
    DIG_20 = 20U,
    DIG_21 = 21U,
    DIG_22 = 22U,
    DIG_23 = 23U,
    DIG_24 = 24U,
    DIG_25 = 25U,
    DIG_26 = 26U,
    DIG_27 = 27U,
    DIG_28 = 28U,
    DIG_29 = 29U
} project_wizard_dig_pin_t;

typedef enum {
    AXI_GPIO_SLOT_NONE = 0
} project_wizard_axi_gpio_slot_t;

bool project_wizard_io_read(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin);
void project_wizard_io_write(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin, project_wizard_io_level_t level);
void project_wizard_io_set(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin);
void project_wizard_io_clear(project_wizard_axi_gpio_slot_t slot, project_wizard_dig_pin_t pin);
