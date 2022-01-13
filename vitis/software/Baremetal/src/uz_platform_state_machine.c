#include "uz_platform_state_machine.h"
#include "uz/uz_SystemTime/uz_SystemTime.h"
#include "uz/uz_LED/uz_LED_facade.h"
#include "include/gpio_axi.h"
#include "stdbool.h"

typedef enum
{
    setup_assertions,
    initialize_platform,
    initialize_ip_cores,
    initialize_interrupt,
    idle,
    running,
    control,
    error
} platform_state_t;

struct ultrazohm_state_t
{
    platform_state_t current_state;
    bool event_handled;
    bool entry;
    bool enable_system;
    bool enable_control;
    bool stop;
    bool error;
};

struct ultrazohm_state_t ultrazohm_state = {
    .current_state = setup_assertions,
    .event_handled = true,
    .entry = true};

void ultrazohm_state_machine_set_enable_system(bool enable_system);
void ultrazohm_state_machine_set_enable_control(bool enable_control);
void ultrazohm_state_machine_set_stop(bool stop);
void ultrazohm_state_machine_set_error(bool error);
bool ultrazohm_state_machine_is_control_state(void);

void poll_buttons(void);

void ultrazohm_state_machine_switch_to_state(platform_state_t new_state);
void ultrazohm_state_machine_switch_to_state(platform_state_t new_state)
{
    uz_assert(ultrazohm_state.event_handled);
    ultrazohm_state.event_handled = false;
    ultrazohm_state.entry = true;
}

void ultrazohm_state_machine_event_handled(void);
static void ready_LED_blink_slow(void);
static void ready_LED_blink_fast(void);

void ultrazohm_state_machine_event_handled(void)
{
    ultrazohm_state.event_handled = true;
    ultrazohm_state.entry = false;
}

void ultrazohm_state_machine(void)
{

    switch (ultrazohm_state.current_state)
    {
    case setup_assertions:
        if (ultrazohm_state.entry)
        {
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here

        ultrazohm_state_machine_switch_to_state(initialize_platform);
        break;

    case initialize_platform:
        if (ultrazohm_state.entry)
        {
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here

        ultrazohm_state_machine_switch_to_state(initialize_ip_cores);
        break;

    case initialize_ip_cores:
        if (ultrazohm_state.entry)
        {
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here

        ultrazohm_state_machine_switch_to_state(initialize_interrupt);
        break;

    case initialize_interrupt:
        /* code */
        if (ultrazohm_state.entry)
        {
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here

        ultrazohm_state_machine_switch_to_state(idle);
        break;

    case idle:
        /* code */
        if (ultrazohm_state.entry)
        {
            uz_led_set_errorLED_off();
            uz_led_set_runningLED_off();
            uz_led_set_userLED_off();
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here
        ready_LED_blink_slow();
        poll_buttons();
        if (ultrazohm_state.enable_system & (!ultrazohm_state.error) & (!ultrazohm_state.stop))
        {
            ultrazohm_state_machine_switch_to_state(running);
        }
        if (ultrazohm_state.error)
        {
            ultrazohm_state_machine_switch_to_state(error);
        }
        break;

    case running:
        if (ultrazohm_state.entry)
        {
            uz_led_set_errorLED_off();
            uz_led_set_runningLED_off();
            uz_led_set_userLED_off();
            uz_axigpio_enable_pwm_and_power_electronics();
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here
        ready_LED_blink_fast();
        poll_buttons();

        if (ultrazohm_state.error)
        {
            ultrazohm_state_machine_switch_to_state(error);
        }
        if (ultrazohm_state.stop & (!ultrazohm_state.error))
        {
            ultrazohm_state_machine_switch_to_state(idle);
        }
        if (ultrazohm_state.enable_control & (!ultrazohm_state.error) & (!ultrazohm_state.stop))
        {
            ultrazohm_state_machine_switch_to_state(control);
        }
        break;

    case control:
        if (ultrazohm_state.entry)
        {
            uz_led_set_errorLED_off();
            uz_led_set_runningLED_on();
            uz_led_set_userLED_off();
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        // Code that is executed while in the state goes here
        ready_LED_blink_fast();
        poll_buttons();

        if (ultrazohm_state.error)
        {
            ultrazohm_state_machine_switch_to_state(error);
        }
        if (ultrazohm_state.stop & (!ultrazohm_state.error))
        {
            ultrazohm_state_machine_switch_to_state(idle);
        }
        break;

    case error:
        if (ultrazohm_state.entry)
        {
        uz_axigpio_disable_pwm_and_power_electronics();
        uz_led_set_errorLED_on();
        uz_led_set_runningLED_off();
        uz_led_set_userLED_off();
        uz_led_set_readyLED_off();
        break;
            // Stuff that happens on entering the state goes here
            ultrazohm_state_machine_event_handled();
        }
        poll_buttons();
        break;
    default:
        break;
    }
}

static void ready_LED_blink_fast(void)
{
    uint32_t uptime_ms = uz_SystemTime_GetUptimeInMs();
    if ((uptime_ms % 200) > 100)
    {
        uz_led_set_readyLED_on();
    }
    else
    {
        uz_led_set_readyLED_off();
    }
}

static void ready_LED_blink_slow(void)
{
    uint32_t uptime_sec = uz_SystemTime_GetUptimeInSec();
    if (uptime_sec % 2)
    {
        uz_led_set_readyLED_on();
    }
    else
    {
        uz_led_set_readyLED_off();
    }
}

void poll_buttons(void)
{
#if (UZ_HARDWARE_VERSION > 2U) // in CarrierBoard_v2 there are no buttons, therefore SW_stop is always zero/false
    ultrazohm_state.enable_system = uz_GetPushButtonEnableSystem();
    ultrazohm_state.enable_control = uz_GetPushButtonEnableControl();
    ultrazohm_state.stop = !(uz_GetPushButtonStop()); // If 0, stop is pressed
#endif
}

bool ultrazohm_state_machine_is_control_state(void)
{
    return (ultrazohm_state.current_state == control);
}

void ultrazohm_state_machine_set_enable_system(bool enable_system)
{
    ultrazohm_state.enable_system = enable_system;
}

void ultrazohm_state_machine_set_enable_control(bool enable_control)
{
    ultrazohm_state.enable_control = enable_control;
}

void ultrazohm_state_machine_set_stop(bool stop)
{
    ultrazohm_state.stop = stop;
}

void ultrazohm_state_machine_set_error(bool error)
{
    ultrazohm_state.error = error;
}
