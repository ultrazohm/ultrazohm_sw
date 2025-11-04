#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void uz_NN_acc(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_5_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_5_Bias_input, float *L_Output_Bias_input,
		volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);
#define A_rows 1
#define B1_rows 24
#define B1_columns 64
#define B2_rows 64
#define B2_columns 64
#define B3_rows 64
#define B3_columns 64
#define B4_rows 64
#define B4_columns 64
#define B5_rows 64
#define B5_columns 64
#define B6_rows 64
#define B6_columns 12

//Set how many Obs and Actions of the max are in use
#define Observations 20	 //can be max 24
#define Actions 4	//can be max 12


//test for 5 layers
int main() {
   float A[A_rows * B1_rows] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   static float B1[B1_rows * B1_columns] = {
   	#include "Matrix_B1_input.csv"
   };
   static float Bias1[A_rows*B1_columns] = {
	#include "Matrix_Bias1_output.csv"
   };
   static float B2[B2_rows * B2_columns] = {
      	#include "Matrix_B2_input.csv"
   };
   static float Bias2[A_rows*B2_columns] = {
   	#include "Matrix_Bias2_output.csv"
   };
   static float B3[B3_rows * B3_columns] = {
		#include "Matrix_B3_input.csv"
   };
   static float Bias3[A_rows*B3_columns] = {
   	#include "Matrix_Bias3_output.csv"
   };
   static float B4[B4_rows * B4_columns] = {
		#include "Matrix_B4_input.csv"
   };
   static float Bias4[A_rows*B4_columns] = {
   	#include "Matrix_Bias4_output.csv"
   };
   static float B5[B5_rows * B5_columns] = {
   	#include "Matrix_B5_input.csv"
   };
   static float Bias5[A_rows*B5_columns] = {
   	#include "Matrix_Bias5_output.csv"
   };
   static float B6[B6_rows * B6_columns] = {
    #include "Matrix_B6_input.csv"
   };
   static float Bias6[A_rows*B6_columns] = {
   	#include "Matrix_Bias6_output.csv"
   };
   float C_out[A_rows * B6_columns] = {0};
   float C_out_Dummy[A_rows * B6_columns] = {0};
   float C_out_2[A_rows * B6_columns] = {0};
   float expected[A_rows * B6_columns] = {
	#include "Matrix_C6_output.csv"
   };
   float expected_2[A_rows * B6_columns] = {
   	#include "Matrix_C6_2_output.csv"
      };
   bool copy_flag_out = 0;
   bool compute = 0;
   bool matrices_updated = 0;
   bool copy_mats_flag = true;
   //Check if compute&write out works separately
   compute=true;
   uz_NN_acc(&A[0], &B1[0], &B2[0], &B3[0], &B4[0], &B5[0], &B6[0], &C_out_Dummy[0], &Bias1[0], &Bias2[0], &Bias3[0], &Bias4[0],&Bias5[0],&Bias6[0],&copy_mats_flag, Observations, Actions, &copy_flag_out, &matrices_updated, &compute);
   compute=false;
   copy_mats_flag=false;
   uz_NN_acc(&A[0], &B1[0], &B2[0], &B3[0], &B4[0], &B5[0], &B6[0], &C_out[0], &Bias1[0], &Bias2[0], &Bias3[0], &Bias4[0],&Bias5[0],&Bias6[0],&copy_mats_flag, Observations, Actions, &copy_flag_out, &matrices_updated, &compute);
   for (uint_fast32_t i=0;i<Observations; i++) {
   	   A[i]=A[i]*A[i]*100000;
      }
   //Checks if again with different observations a different output comes out
   compute=true;
   uz_NN_acc(&A[0], &B1[0], &B2[0], &B3[0], &B4[0], &B5[0], &B6[0], &C_out_2[0], &Bias1[0], &Bias2[0], &Bias3[0], &Bias4[0],&Bias5[0],&Bias6[0],&copy_mats_flag, Observations, Actions, &copy_flag_out, &matrices_updated, &compute);

   for (uint_fast32_t i=0;i<B6_columns; i++) {

	   printf("%f \n",C_out[i]);
	   printf("expected: %f \n",expected[i]);

   }
   printf("%i", copy_flag_out);
   printf("%i", matrices_updated);
   for (uint_fast32_t i=0;i<B6_columns; i++) {

	   printf("%f \n",C_out_2[i]);
	   printf("expected: %f \n",expected_2[i]);

   }
   return 0;
}
