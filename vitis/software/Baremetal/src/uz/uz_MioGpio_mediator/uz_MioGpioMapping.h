#include "../uz_global_configuration.h"
#define OUTPUT_PIN							1 								//This Pin is an Output
#define INPUT_PIN							0 								//This Pin is an Input

#define ENABLE_PIN							1 								//This Pin is enabled
#define DISABLE_PIN							0 								//This Pin is disabled

#define GPIO_CHANNEL 						1								/* GPIO port for GPIOs */


// Defines that map the number of the MIO PIN of the PS to the signal name of the signal on the carrier board (X13)
#define PS_DIG_GPIO_01	30
#define PS_DIG_GPIO_02	31
#define PS_ANL_GPIO_01	44
#define PS_ANL_GPIO_02	45
#define EXT_GPIO_1 		13
#define EXT_GPIO_2 		33
#define EXT_GPIO_3 		34
#define EXT_GPIO_4 		39
#define EXT_GPIO_5 		40

#if UZ_HARDWARE_VERSION < 4U
#define EXT_GPIO_6        52 // Rev. 2 and 3
#define EXT_GPIO_7        53 // Rev. 2 and 3
#endif
#if UZ_HARDWARE_VERSION > 3U
#define EXT_GPIO_6 44 // Rev.04
#define EXT_GPIO_7 30 // Rev.04
#define EXT_GPIO_8 31 // Rev.04
#endif

//#define EXT_GPIO_8 		55

// LED on carrier board and frontpanel
#define LED_1								EXT_GPIO_1
#define LED_2								EXT_GPIO_2
#define LED_3								EXT_GPIO_3
#define LED_4								EXT_GPIO_4

// Names of LED on frontpanel
#define LED_ready 	LED_1
#define LED_running LED_2
#define LED_error 	LED_3
#define LED_user 	LED_4

// Switches on frontpanel
#define SW_1 EXT_GPIO_6
#define SW_2 EXT_GPIO_7
#define SW_3 EXT_GPIO_5
#define External_STOP EXT_GPIO_8

#define SW_system           SW_1
#define SW_control          SW_2
#define SW_stop             SW_3
#define SW_external_stop    External_STOP
