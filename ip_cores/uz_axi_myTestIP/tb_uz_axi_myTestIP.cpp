#include <stdio.h>
#include <stdint.h>

void uz_axi_myTestIP(int32_t a, int32_t b, int32_t *result);

int main() {
   int32_t a = 5;
   int32_t b = 7;
   int32_t result;

   uz_axi_myTestIP(a, b, &result);

   printf("Multiplication result: %d\n", result);

   return 0;
}
