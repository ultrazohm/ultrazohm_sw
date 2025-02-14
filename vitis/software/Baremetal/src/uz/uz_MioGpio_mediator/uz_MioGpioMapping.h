#include "../uz_global_configuration.h"
#define OUTPUT_PIN 1 // This Pin is an Output
#define INPUT_PIN 0  // This Pin is an Input

#define ENABLE_PIN 1  // This Pin is enabled
#define DISABLE_PIN 0 // This Pin is disabled

#define GPIO_CHANNEL 1 /* GPIO port for GPIOs */

#define UZ_REV_3_PS_DIG_GPIO_01 	30
#define UZ_REV_3_PS_DIG_GPIO_02 	31
#define UZ_REV_3_PS_ANL_GPIO_01 	44
#define UZ_REV_3_PS_ANL_GPIO_02 	45
#define UZ_REV_3_EXT_GPIO_1 		13
#define UZ_REV_3_EXT_GPIO_2 		33
#define UZ_REV_3_EXT_GPIO_3 		34
#define UZ_REV_3_EXT_GPIO_4 		39
#define UZ_REV_3_EXT_GPIO_5 		40
#define UZ_REV_3_EXT_GPIO_6 		52
#define UZ_REV_3_EXT_GPIO_7 		53

// Page 24 of carrier board v4, mapping of MIO GPIO to LEDs
#define UZ_REV_3_FrontPanel_LED1 UZ_REV_3_EXT_GPIO_1
#define UZ_REV_3_FrontPanel_LED2 UZ_REV_3_EXT_GPIO_2
#define UZ_REV_3_FrontPanel_LED3 UZ_REV_3_EXT_GPIO_3
#define UZ_REV_3_FrontPanel_LED4 UZ_REV_3_EXT_GPIO_4

#define UZ_REV_3_FrontPanel_switch5 UZ_REV_3_EXT_GPIO_5
#define UZ_REV_3_FrontPanel_switch6 UZ_REV_3_EXT_GPIO_6
#define UZ_REV_3_FrontPanel_switch7 UZ_REV_3_EXT_GPIO_7

// Names of LED on frontpanel - carrier v4 X18, schematic sheet 24
#define UZ_REV_3_LED_ready 	UZ_REV_3_FrontPanel_LED1
#define UZ_REV_3_LED_running UZ_REV_3_FrontPanel_LED2
#define UZ_REV_3_LED_error 	UZ_REV_3_FrontPanel_LED3
#define UZ_REV_3_LED_user 	UZ_REV_3_FrontPanel_LED4

#define UZ_REV_3_SW_system 			UZ_REV_3_FrontPanel_switch6
#define UZ_REV_3_SW_control 			UZ_REV_3_FrontPanel_switch7
#define UZ_REV_3_SW_stop 			UZ_REV_3_FrontPanel_switch5
#define UZ_REV_3_SW_external_stop 	UZ_REV_3_FrontPanel_switch7


// Defines for PS_GPIO mapping based on carrier board v4 - schematic page 5
#define UZ_REV_4_PS_1V8_GPIO1 	13
#define UZ_REV_4_PS_1V8_GPIO2 	33
#define UZ_REV_4_PS_1V8_GPIO3 	34
#define UZ_REV_4_PS_1V8_GPIO4 	39
#define UZ_REV_4_PS_1V8_GPIO5 	40
#define UZ_REV_4_PS_1V8_GPIO6 	44
#define UZ_REV_4_PS_1V8_GPIO7 	30
#define UZ_REV_4_MIO31 			31

// Page 24 of carrier board v4, mapping of MIO GPIO to LEDs
#define UZ_REV_4_FrontPanel_LED1 UZ_REV_4_PS_1V8_GPIO1
#define UZ_REV_4_FrontPanel_LED2 UZ_REV_4_PS_1V8_GPIO2
#define UZ_REV_4_FrontPanel_LED3 UZ_REV_4_PS_1V8_GPIO3
#define UZ_REV_4_FrontPanel_LED4 UZ_REV_4_PS_1V8_GPIO4

#define UZ_REV_4_FrontPanel_switch5 UZ_REV_4_PS_1V8_GPIO5
#define UZ_REV_4_FrontPanel_switch6 UZ_REV_4_PS_1V8_GPIO6
#define UZ_REV_4_FrontPanel_switch7 UZ_REV_4_PS_1V8_GPIO7
#define UZ_REV_4_FrontPanel_switch8 UZ_REV_4_MIO31

// Names of LED on frontpanel - carrier v4 X18, schematic sheet 24
#define UZ_REV_4_LED_ready 	UZ_REV_4_FrontPanel_LED1
#define UZ_REV_4_LED_running UZ_REV_4_FrontPanel_LED2
#define UZ_REV_4_LED_error 	UZ_REV_4_FrontPanel_LED3
#define UZ_REV_4_LED_user 	UZ_REV_4_FrontPanel_LED4

#define UZ_REV_4_SW_system	UZ_REV_4_FrontPanel_switch6
#define UZ_REV_4_SW_control	UZ_REV_4_FrontPanel_switch7
#define UZ_REV_4_SW_stop 	UZ_REV_4_FrontPanel_switch5
#define UZ_REV_4_SW_external_stop 	UZ_REV_4_FrontPanel_switch8


// Defines for GPIO mapping based on carrier board v5 (harness "UsrFP-MIOs" on schematic sheet J3)
#define UZ_REV_5_FrontPanel_LED1 13
#define UZ_REV_5_FrontPanel_LED2 56
#define UZ_REV_5_FrontPanel_LED3 57
#define UZ_REV_5_FrontPanel_LED4 58

#define UZ_REV_5_FrontPanel_switch3 60
#define UZ_REV_5_FrontPanel_switch1 44
#define UZ_REV_5_FrontPanel_switch2 59
#define UZ_REV_5_FrontPanel_switchS 61

// Names of LEDs on frontpanel - fp-ff v1 (schematic sheet TopSheet)
#define UZ_REV_5_LED_ready 	UZ_REV_5_FrontPanel_LED1
#define UZ_REV_5_LED_running UZ_REV_5_FrontPanel_LED2
#define UZ_REV_5_LED_error 	UZ_REV_5_FrontPanel_LED3
#define UZ_REV_5_LED_user 	UZ_REV_5_FrontPanel_LED4

// Names of buttons on frontpanel - fp-bb v1 (TopSheet) and fp-main v1 (PCB-ButtonBoard)
#define UZ_REV_5_SW_system	UZ_REV_5_FrontPanel_switch1
#define UZ_REV_5_SW_control	UZ_REV_5_FrontPanel_switch2
#define UZ_REV_5_SW_stop 	UZ_REV_5_FrontPanel_switch3

// External STOP input - fp-main v1 (FPC-isoIOs)
#define UZ_REV_5_SW_external_stop UZ_REV_5_FrontPanel_switchS

