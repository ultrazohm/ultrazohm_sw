#include "../include/uz_platform_state_machine.h"

#include "../uz/uz_global_configuration.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../uz/uz_LED/uz_LED_facade.h"
#include "../uz/uz_PushButton/uz_PushButton_facade.h"
#include "../include/gpio_axi.h"
#include "../include/uz_assertion_configuration.h"

typedef enum
{
    idle_state = 0, // _state is used here to prevent name duplication with the flags
    running_state,
    control_state,
    error_state
} platform_state_t;

typedef struct
{
    platform_state_t current_state;
    bool event_handled;
    bool entry;
    bool enable_system;
    bool enable_control;
    bool stop_flag;
    bool error_flag;
} ultrazohm_state_t;

ultrazohm_state_t ultrazohm_state = {
    .current_state = idle_state,
    .event_handled = true,
    .entry = true
};

static void poll_buttons(void);
static void ultrazohm_state_machine_switch_to_state(platform_state_t new_state);
static void ultrazohm_state_machine_event_handled(void);
static void ready_LED_blink_slow(void);
static void ready_LED_blink_fast(void);

static void idle_entry(void);
static void running_entry(void);
static void control_entry(void);
static void error_entry(void);
static void idle_during(void);
static void running_during(void);
static void control_during(void);

void ultrazohm_state_machine_step(void)
{
    poll_buttons();
    switch (ultrazohm_state.current_state)
    {
    case idle_state:
        idle_entry();
        idle_during();
        break;
    case running_state:
        running_entry();
        running_during();
        break;
    case control_state:
        control_entry();
        control_during();
        break;
    case error_state:
        error_entry();
        break;
    default:
        break;
    }
}

bool ultrazohm_state_machine_is_control_state(void)
{
    return (ultrazohm_state.current_state == control_state);
}

bool ultrazohm_state_machine_get_enable_system(void)
{
    return ultrazohm_state.enable_system;
}

bool ultrazohm_state_machine_get_enable_control(void)
{
    return ultrazohm_state.enable_control;
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
    ultrazohm_state.stop_flag = stop;
}

void ultrazohm_state_machine_set_error(bool error)
{
	if(error){
	    ultrazohm_state.current_state = error_state; // if the error is set to true, directly change the current state to error and skip everything in the state machine
	}
	ultrazohm_state.error_flag=error;

    ultrazohm_state_machine_step(); // If the error bit is changed, execute the state machine again to enter the error state
}

static void idle_entry(void)
{
    if (ultrazohm_state.entry)
    {
    	uz_axigpio_disable_pwm_and_power_electronics();
        uz_led_set_errorLED_off();
        uz_led_set_runningLED_off();
        uz_led_set_userLED_off();
        ultrazohm_state_machine_event_handled();
    }
}

static void running_entry(void)
{
    if (ultrazohm_state.entry)
    {
        uz_led_set_errorLED_off();
        uz_led_set_runningLED_off();
        uz_led_set_userLED_off();
        uz_axigpio_enable_pwm_and_power_electronics();
        ultrazohm_state_machine_event_handled();
    }
}

static void control_entry(void)
{
    if (ultrazohm_state.entry)
    {
        uz_led_set_errorLED_off();
        uz_led_set_runningLED_on();
        uz_led_set_userLED_off();
        ultrazohm_state_machine_event_handled();
    }
}

static void error_entry(void)
{
    if (ultrazohm_state.entry)
    {
        uz_axigpio_disable_pwm_and_power_electronics();
        uz_led_set_errorLED_on();
        uz_led_set_runningLED_off();
        uz_led_set_userLED_off();
        uz_led_set_readyLED_off();
        ultrazohm_state_machine_event_handled();
    }
}

static void idle_during(void)
{
    ready_LED_blink_slow();
    if (ultrazohm_state.enable_system & (!ultrazohm_state.error_flag) & (!ultrazohm_state.stop_flag))
    {
        ultrazohm_state_machine_switch_to_state(running_state);
    }
    if (ultrazohm_state.error_flag)
    {
        ultrazohm_state_machine_switch_to_state(error_state);
    }
}

static void running_during(void)
{
    ready_LED_blink_fast();
    if (ultrazohm_state.error_flag)
    {
        ultrazohm_state_machine_switch_to_state(error_state);
    }
    if (ultrazohm_state.stop_flag & (!ultrazohm_state.error_flag))
    {
        ultrazohm_state_machine_switch_to_state(idle_state);
    }
    if (ultrazohm_state.enable_control & (!ultrazohm_state.error_flag) & (!ultrazohm_state.stop_flag))
    {
        ultrazohm_state_machine_switch_to_state(control_state);
    }
}

static void control_during(void)
{
    ready_LED_blink_fast();
    if (ultrazohm_state.error_flag)
    {
        ultrazohm_state_machine_switch_to_state(error_state);
    }
    if (ultrazohm_state.stop_flag & (!ultrazohm_state.error_flag))
    {
        ultrazohm_state_machine_switch_to_state(idle_state);
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
#ifndef UZ_HARDWARE_VERSION
#error Hardware version of the UltraZohm is not defined!
#else
#if (UZ_HARDWARE_VERSION > 2U) // in CarrierBoard_v2 there are no buttons, therefore they are not polled.
    ultrazohm_state.enable_system = uz_GetPushButtonEnableSystem();
    ultrazohm_state.enable_control = uz_GetPushButtonEnableControl();
    ultrazohm_state.stop_flag = !(uz_GetPushButtonStop()); // If 0, stop is pressed
#endif
#endif
}

static void ultrazohm_state_machine_event_handled(void)
{
    ultrazohm_state.event_handled = true;
    ultrazohm_state.entry = false;
}

static void ultrazohm_state_machine_switch_to_state(platform_state_t new_state)
{
    uz_assert(ultrazohm_state.event_handled);
    ultrazohm_state.event_handled = false;
    ultrazohm_state.entry = true;
    ultrazohm_state.current_state = new_state;
}
