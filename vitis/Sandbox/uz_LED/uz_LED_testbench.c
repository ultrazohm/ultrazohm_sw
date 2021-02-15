#include <stdio.h>
#include "uz_HAL.h"

#include "uz_LED.h"

int main() {
    uz_assert(TARGET_SANDBOX);
    printf("a\n");
    uz_assert(1);
    uz_StatusLed testled;
    uz_led_init(&testled);
    uz_assert(testled.isReady); // An initialized LED is ready
    
}
