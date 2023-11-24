#include <stdio.h>
#include <stdint.h>

void MatrixMultiplication(float *A_input, float *B_input, float *C_output, uint_fast32_t A_rows, uint_fast32_t B_rows, uint_fast32_t B_columns);

#define A_rows 1
#define B_rows 4
#define B_columns 4

int main() {
   float A[A_rows * B_rows] = {1,2,3,4};
   float B[B_rows * B_columns] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   float C_out[A_rows * B_columns] = {0};
   float expected[A_rows * B_columns]={130,140,150,160};
   MatrixMultiplication(&A[0], &B[0], &C_out[0], A_rows, B_rows, B_columns);
   bool result=false;

   for (uint_fast32_t i=0;i<4; i++) {
	   if ((C_out[i] == expected[i])) {
		   result = true;
	   } else {
		   result = false;
	   }
	   if(!result){
		   break;
	   }
   }
   if(result){
	   printf("Matrix Multiplication Passed");
   } else {
	   printf("Matrix Multiplication Failed");
   }

   return 0;
}
