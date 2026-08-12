#ifndef WOLFSPEED_INVERTER_TEMPERATURE_H
#define WOLFSPEED_INVERTER_TEMPERATURE_H

/**
 * Convert a duty-cycle ratio to the documented NTC temperature.
 * Returns NAN outside the valid, inclusive duty-cycle range 0.05 to 0.95.
 */
float wolfspeed_inverter_temperature_from_duty_ratio(float duty_ratio);

#endif
