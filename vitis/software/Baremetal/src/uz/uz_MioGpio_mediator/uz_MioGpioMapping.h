#include "../uz_global_configuration.h"
#define OUTPUT_PIN 1 // This Pin is an Output
#define INPUT_PIN 0  // This Pin is an Input

#define ENABLE_PIN 1  // This Pin is enabled
#define DISABLE_PIN 0 // This Pin is disabled

#define GPIO_CHANNEL 1 /* GPIO port for GPIOs */

// Defines that map the number of the MIO PIN of the PS to the signal name of the signal on the carrier board (X13)
#if UZ_HARDWARE_VERSION < 4U
#define PS_DIG_GPIO_01 	30
#define PS_DIG_GPIO_02 	31
#define PS_ANL_GPIO_01 	44
#define PS_ANL_GPIO_02 	45
#define EXT_GPIO_1 		13
#define EXT_GPIO_2 		33
#define EXT_GPIO_3 		34
#define EXT_GPIO_4 		39
#define EXT_GPIO_5 		40
#define EXT_GPIO_6 		52
#define EXT_GPIO_7 		53

// Page 24 of carrier board v4, mapping of MIO GPIO to LEDs
#define FrontPanel_LED1 EXT_GPIO_1
#define FrontPanel_LED2 EXT_GPIO_2
#define FrontPanel_LED3 EXT_GPIO_3
#define FrontPanel_LED4 EXT_GPIO_4

#define FrontPanel_switch5 EXT_GPIO_5
#define FrontPanel_switch6 EXT_GPIO_6
#define FrontPanel_switch7 EXT_GPIO_7

// Names of LED on frontpanel - carrier v4 X18, schematic sheet 24
#define LED_ready 	FrontPanel_LED1
#define LED_running FrontPanel_LED2
#define LED_error 	FrontPanel_LED3
#define LED_user 	FrontPanel_LED4

#define SW_system 			FrontPanel_switch6
#define SW_control 			FrontPanel_switch7
#define SW_stop 			FrontPanel_switch5
#define SW_external_stop 	FrontPanel_switch7
#endif

#if UZ_HARDWARE_VERSION > 3U
// Defines for PS_GPIO mapping based on carrier board v4 - schematic page 5
#define PS_1V8_GPIO1 	13
#define PS_1V8_GPIO2 	33
#define PS_1V8_GPIO3 	34
#define PS_1V8_GPIO4 	39
#define PS_1V8_GPIO5 	40
#define PS_1V8_GPIO6 	44
#define PS_1V8_GPIO7 	30
#define MIO31 			31

// Page 24 of carrier board v4, mapping of MIO GPIO to LEDs
#define FrontPanel_LED1 PS_1V8_GPIO1
#define FrontPanel_LED2 PS_1V8_GPIO2
#define FrontPanel_LED3 PS_1V8_GPIO3
#define FrontPanel_LED4 PS_1V8_GPIO4

#define FrontPanel_switch5 PS_1V8_GPIO5
#define FrontPanel_switch6 PS_1V8_GPIO6
#define FrontPanel_switch7 PS_1V8_GPIO7
#define FrontPanel_switch8 MIO31

// Names of LED on frontpanel - carrier v4 X18, schematic sheet 24
#define LED_ready 	FrontPanel_LED1
#define LED_running FrontPanel_LED2
#define LED_error 	FrontPanel_LED3
#define LED_user 	FrontPanel_LED4

#define SW_system	FrontPanel_switch6
#define SW_control	FrontPanel_switch7
#define SW_stop 	FrontPanel_switch5
#define SW_external_stop 	FrontPanel_switch8
#endif
