#include <stdio.h>
#include <stdint.h>

void MatrixMultiplication(float *A_input, float *B_input, float *C_output, uint_fast32_t A_rows, uint_fast32_t B_rows, uint_fast32_t B_columns);

#define A_rows 1
#define B_rows 2
#define B_columns 16

int main() {
   float A[A_rows * B_rows] = {1,2};
   float B[B_rows * B_columns] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
   float C_out[A_rows * B_columns] = {0};
   float expected[A_rows * B_columns]={35  ,  38  ,  41  ,  44  ,  47  ,  50  ,  53  ,  56,    59   , 62  ,  65   , 68   , 71  ,  74 ,   77 ,   80};
   MatrixMultiplication(&A[0], &B[0], &C_out[0], A_rows, B_rows, B_columns);
   bool result=false;

   for (uint_fast32_t i=0;i<B_columns; i++) {
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
