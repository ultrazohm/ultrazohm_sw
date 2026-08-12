#include "../include/wolfspeed_inverter_temperature.h"
#include "../uz/uz_HAL.h"
#include <math.h>

#define WOLFSPEED_TEMPERATURE_DUTY_MIN 0.05f
#define WOLFSPEED_TEMPERATURE_DUTY_MAX 0.95f

float wolfspeed_inverter_temperature_from_duty_ratio(float duty_ratio)
{
    /*
     * CRD25DA12N-FMC V2.0 + UltraZohm Wolfspeed adapter Rev04
     *
     * Signal chain:
     *
     * NTC
     *   -> analog NTC_ISO on inverter
     *   -> /2 voltage divider on adapter
     *   -> LTC6992-2 analog-to-PWM
     *   -> duty_ratio
     *
     * LTC6992-2 nominal usable range:
     * 5 % ... 95 % duty cycle.
     *
     * Below/above these limits the PWM is clamped and therefore
     * does not contain an unambiguous temperature value.
     */
    /* Outside the unclamped PWM range no valid temperature is available. */
    if (!isfinite(duty_ratio) ||
        (duty_ratio < WOLFSPEED_TEMPERATURE_DUTY_MIN) ||
        (duty_ratio > WOLFSPEED_TEMPERATURE_DUTY_MAX))
    {
        return NAN;
    }
    /*
     * LTC6992-2:
     *
     * duty = (0.9 - V_MOD) / 0.8
     *
     * Adapter:
     * V_MOD = V_NTC_ISO / 2
     *
     * therefore:
     *
     * V_NTC_ISO = 1.8 - 1.6 * duty
     */
    const float v_ntc_iso = 1.8f - 1.6f * duty_ratio;
    /*
     * Wolfspeed inverter Rev2.0 NTC network:
     *
     * 5 V
     *  |
     * 2.2 kOhm
     *  |
     * +---- NTC
     * |
     * 1.8 kOhm
     * |
     * GND
     *
     * NTC and 1.8 kOhm are in parallel.
     *
     * Inverted divider equation:
     *
     * R_NTC = 3960 * V_NTC_ISO / (9 - 4 * V_NTC_ISO)
     */
    const float r_ntc_ohm =
        (3960.0f * v_ntc_iso)
        / (9.0f - 4.0f * v_ntc_iso);

    /*
     * WolfPACK NTC approximation:
     *
     * R25 = 5 kOhm
     * beta_25_100 ~= 3523 K
     */
    const float r_25_ohm = 5000.0f;
    const float beta_K = 3523.0f;
    const float t_25_K = 298.15f;
    const float inverse_temperature_K =
        (1.0f / t_25_K)
        + (logf(r_ntc_ohm / r_25_ohm) / beta_K);

    const float temperature_K = 1.0f / inverse_temperature_K;
    return temperature_K - 273.15f;
};
