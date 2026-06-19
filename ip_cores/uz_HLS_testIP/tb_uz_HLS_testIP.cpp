#include <stdio.h>
#include <stdint.h>

void uz_HLS_testIP(int32_t a, int32_t b, int32_t *result);

int main() {
   int32_t a = 5;
   int32_t b = 7;
   int32_t result;

   uz_HLS_testIP(a, b, &result);

   printf("Multiplication result: %d\n", result);

   return 0;
}
