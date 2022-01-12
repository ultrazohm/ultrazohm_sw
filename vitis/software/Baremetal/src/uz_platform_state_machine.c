#include "uz_platform_state_machine.h"

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

platform_state_t ultrazohm_state = setup_assertions;

void ultrazohm_state_machine(void)
{

    switch (ultrazohm_state)
    {
    case setup_assertions:
        /* code */
        ultrazohm_state=initialize_platform;
        break;

    case initialize_platform:
        /* code */
        ultrazohm_state=initialize_ip_cores;
        break;

    case initialize_ip_cores:
        /* code */
        ultrazohm_state=initialize_interrupt;
        break;

    case initialize_interrupt:
        /* code */

        ultrazohm_state=idle;
        break;

    case idle:
        /* code */
        break;

    case running:
        /* code */
        break;

    case control:
        /* code */
        break;

    case error:
        /* code */

        break;

    default:
        break;
    }
}
