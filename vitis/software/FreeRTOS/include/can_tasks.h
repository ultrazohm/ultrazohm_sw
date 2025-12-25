#ifndef CAN_TASKS_H
#define CAN_TASKS_H

#include <stdint.h>
//#include "../shared_memory.h"   /* shared_CAN_Data */

/* Initializes CAN-Tasks (RX and 1/10/100ms TX-Tasks).
   Functions will be called as long as hal_can_init() was executed successfully. */
void CAN_app_init(void);

#endif /* CAN_TASKS_H */
