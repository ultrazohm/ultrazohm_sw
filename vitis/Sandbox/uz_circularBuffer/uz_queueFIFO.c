#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define UZ_QUEUE_MAX_LENGTH 20

typedef struct uz_queue_ {
   int data;
   int head;
   int tail;
   int maxSize;
   bool full;
   void (*WriteVariable) (struct testDriver_hw_ *p, int foo);

}uz_queue;

typedef uz_queue* uz_queue_handle;

uz_queue_handle uz_queue(uint32_t buffer, int maxSize);