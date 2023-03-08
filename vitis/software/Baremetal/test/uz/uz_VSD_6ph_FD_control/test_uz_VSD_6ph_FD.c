#ifdef TEST

#include "unity.h"

#include "uz_VSD_6ph_FD.h"
#include "uz_Transformation.h"
#include "uz_signals.h"
#include "uz_movingAverageFilter.h"


void test_uz_vsd_opf_6ph_fault_indices_calculation(void)
{
    uz_6phFD_indices indices = {0};
    uz_6ph_alphabeta_t currents = {0};

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices.R1);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices.R2);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices.R3);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices.R4);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices.R5);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices.R6);

    currents.alpha = 1.0f;
    currents.beta = 2.0f;
    currents.x = 0.0f;
    currents.y = 1.0f;
    currents.z1 = 0.0f;
    currents.z2 = 0.0f;

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents);

    TEST_ASSERT_FLOAT_WITHIN(0.0f -0.001f, 0.0f +0.001f, indices.R1);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.7029f, indices.R2);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.3880f, indices.R3);
    TEST_ASSERT_FLOAT_WITHIN(-0.2679f -0.001f, -0.2679f +0.001f, indices.R4);
    TEST_ASSERT_FLOAT_WITHIN(-3.7321f -0.001f, -3.7321f +0.001f, indices.R5);
    TEST_ASSERT_FLOAT_WITHIN( -0.5f -0.001f, -0.5f +0.001f, indices.R6);

}


void test_uz_vsd_opf_6ph_no_fault(void)
{

    uz_6ph_dq_t dq_values={
        .d=-1.0f,
        .q=10.0f,
        .x=0.0f,
        .y=0.0f,
        .z1=0.0f,
        .z2=0.0f        
    };
    float theta=2.0f;

    uz_6ph_abc_t currents_abc=uz_transformation_asym30deg_6ph_dq_to_abc(dq_values,theta); // Get valid abc currents without fault
    // Potentially add an error by setting a phase current to 0


    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={0};

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R1,indices.R1);
    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R2,indices.R2);
    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R3,indices.R3);
    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R4,indices.R4);
    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R5,indices.R5);
    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R6,indices.R6);
}


uz_6ph_abc_t get_vaild_abcdef_currents_without_fault(float d, float q, float theta){
    uz_6ph_dq_t dq_values={
        .d=d,
        .q=q,
        .x=0.0f,
        .y=0.0f,
        .z1=0.0f,
        .z2=0.0f        
    };
    return uz_transformation_asym30deg_6ph_dq_to_abc(dq_values,theta); // Get valid abc currents without fault
}


void test_uz_vsd_opf_6ph_fault_on_phase_1(void)
{
    uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(-1.0f, 10.0f, 2.0f);

    // Potentially add an error by setting a phase current to 0
    currents_abc.a1=0.0f; // open phase fault one phase 1

    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={
        .R1=1.0f,
        .R2=0.0f,
        .R3=0.0f,
        .R4=0.0f,
        .R5=0.0f,
        .R6=0.0f
    };

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R1,indices.R1);
}


void test_uz_vsd_opf_6ph_fault_on_phase_2(void)
{
    uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(-1.0f, 10.0f, 2.0f);

    // Potentially add an error by setting a phase current to 0
    currents_abc.b1=0.0f; // open phase fault one phase 2

    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={
        .R1=0.0f,
        .R2=1.0f,
        .R3=0.0f,
        .R4=0.0f,
        .R5=0.0f,
        .R6=0.0f
    };

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R2,indices.R2);
}

void test_uz_vsd_opf_6ph_fault_on_phase_3(void)
{
    uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(-1.0f, 10.0f, 2.0f);

    // Potentially add an error by setting a phase current to 0
    currents_abc.c1=0.0f; // open phase fault one phase 3

    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={
        .R1=0.0f,
        .R2=0.0f,
        .R3=1.0f,
        .R4=0.0f,
        .R5=0.0f,
        .R6=0.0f
    };

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R3,indices.R3);
}


void test_uz_vsd_opf_6ph_fault_on_phase_4(void)
{
    uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(-1.0f, 10.0f, 2.0f);

    // Potentially add an error by setting a phase current to 0
    currents_abc.a2=0.0f; // open phase fault one phase 4

    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={
        .R1=0.0f,
        .R2=0.0f,
        .R3=0.0f,
        .R4=1.0f,
        .R5=0.0f,
        .R6=0.0f
    };

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R4,indices.R4);
}


void test_uz_vsd_opf_6ph_fault_on_phase_5(void)
{
    uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(-1.0f, 10.0f, 2.0f);

    // Potentially add an error by setting a phase current to 0
    currents_abc.b2=0.0f; // open phase fault one phase 5

    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={
        .R1=0.0f,
        .R2=0.0f,
        .R3=0.0f,
        .R4=0.0f,
        .R5=1.0f,
        .R6=0.0f
    };

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R5,indices.R5);
}


void test_uz_vsd_opf_6ph_fault_on_phase_6(void)
{
    uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(-1.0f, 10.0f, 2.0f);

    // Potentially add an error by setting a phase current to 0
    currents_abc.c2=0.0f; // open phase fault one phase 6

    uz_6ph_alphabeta_t currents_ab = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
    uz_6phFD_indices indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);

    indices = uz_vsd_opf_6ph_fault_indices_calculation(currents_ab);
    uz_6phFD_indices expected_indices={
        .R1=0.0f,
        .R2=0.0f,
        .R3=0.0f,
        .R4=0.0f,
        .R5=0.0f,
        .R6=1.0f
    };

    TEST_ASSERT_FLOAT_WITHIN(0.001,expected_indices.R6,indices.R6);
}



void test_uz_vsd_fd_hysteresis_filter(void)
{
    uz_6phFD_indices indices_filtered = {0};
    uz_6phFD_indices indices_input = {0};
    float lowerlimit = 0.9f;
    float upperlimit = 1.1f;

    indices_input.R1 = 4.0f;
    indices_input.R2 = 1.1f;
    indices_input.R3 = 1.2f;
    indices_input.R4 = 0.4f;
    indices_input.R5 = 0.1f;
    indices_input.R6 = 0.92f;

    indices_filtered = uz_vsd_fd_hysteresis_filter(indices_input, lowerlimit, upperlimit);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices_filtered.R1);
    TEST_ASSERT_EQUAL_FLOAT(indices_input.R2, indices_filtered.R2);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices_filtered.R3);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices_filtered.R4);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, indices_filtered.R5);
    TEST_ASSERT_EQUAL_FLOAT(indices_input.R6, indices_filtered.R6);
}


void test_uz_vsd_fd_evaluation(void)
{
    uz_6phFD_indices indices_evaluated = {0};
    uz_6phFD_indices indices_input = {0};
    float threshold = 0.4f;

    indices_input.R1 = 0.7f;
    indices_input.R2 = 0.3f;
    indices_evaluated = uz_vsd_fd_evaluation(indices_input, threshold);

    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R1, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R2, 0.0f);

    threshold = 0.8f;

    indices_evaluated = uz_vsd_fd_evaluation(indices_input, threshold);

    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R1, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R2, 0.0f);
}




void test_uz_vsd_opf_6ph_faultdetection(void){

struct uz_movingAverageFilter_config movAvF_config = {
    .filterLength = 300U
};

uz_movingAverageFilter_t* movAvFilter_R1;
uz_movingAverageFilter_t* movAvFilter_R2;
uz_movingAverageFilter_t* movAvFilter_R3;
uz_movingAverageFilter_t* movAvFilter_R4;
uz_movingAverageFilter_t* movAvFilter_R5;
uz_movingAverageFilter_t* movAvFilter_R6;

float dataR1 [500] = {0};
uz_array_float_t circularBuffer_R1 = {
   .length = UZ_ARRAY_SIZE(dataR1),
   .data = &dataR1[0]
};
float dataR2 [500] = {0};
uz_array_float_t circularBuffer_R2 = {
   .length = UZ_ARRAY_SIZE(dataR2),
   .data = &dataR2[0]
};
float dataR3 [500] = {0};
uz_array_float_t circularBuffer_R3 = {
   .length = UZ_ARRAY_SIZE(dataR3),
   .data = &dataR3[0]
};
float dataR4 [500] = {0};
uz_array_float_t circularBuffer_R4 = {
   .length = UZ_ARRAY_SIZE(dataR4),
   .data = &dataR4[0]
};
float dataR5 [500] = {0};
uz_array_float_t circularBuffer_R5 = {
   .length = UZ_ARRAY_SIZE(dataR5),
   .data = &dataR5[0]
};
float dataR6 [500] = {0};
uz_array_float_t circularBuffer_R6 = {
   .length = UZ_ARRAY_SIZE(dataR6),
   .data = &dataR6[0]
};

movAvFilter_R1 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R1);
movAvFilter_R2 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R2);
movAvFilter_R3 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R3);
movAvFilter_R4 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R4);
movAvFilter_R5 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R5);
movAvFilter_R6 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R6);

uz_6phFD_indices output = {0};
uz_6ph_abc_t currents_abc = get_vaild_abcdef_currents_without_fault(0.5f, 5.4f, 0.3f);
uz_6ph_alphabeta_t vsdcurrents = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
float upperlimit = 1.1f;
float lowerlimit = 0.9f;
float threshold = 0.4f;
uint32_t mov_average_filter_length = 500;
float sample_frequency_Hz = 1000;
float percent_of_el_period = 0.4f;
float omega_el_rad_per_sec = 100.0f;

output = uz_vsd_opf_6ph_faultdetection(vsdcurrents, upperlimit, lowerlimit, threshold, mov_average_filter_length, sample_frequency_Hz, percent_of_el_period, omega_el_rad_per_sec, movAvFilter_R1, movAvFilter_R2, movAvFilter_R3, movAvFilter_R4, movAvFilter_R5, movAvFilter_R6 );

TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R1);
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R5);

currents_abc.b2=0.0f; // open phase fault one phase 2

vsdcurrents = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);

output = uz_vsd_opf_6ph_faultdetection(vsdcurrents, upperlimit, lowerlimit, threshold, mov_average_filter_length, sample_frequency_Hz, percent_of_el_period, omega_el_rad_per_sec, movAvFilter_R1, movAvFilter_R2, movAvFilter_R3, movAvFilter_R4, movAvFilter_R5, movAvFilter_R6 );

TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R1);
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R5);
int i = 0;
for(i = 0; i<10; i++){
    output = uz_vsd_opf_6ph_faultdetection(vsdcurrents, upperlimit, lowerlimit, threshold, mov_average_filter_length, sample_frequency_Hz, percent_of_el_period, omega_el_rad_per_sec, movAvFilter_R1, movAvFilter_R2, movAvFilter_R3, movAvFilter_R4, movAvFilter_R5, movAvFilter_R6 );
}
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R1);
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R2);
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R3);
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R4);
TEST_ASSERT_EQUAL_FLOAT(1.0f, output.R5);
TEST_ASSERT_EQUAL_FLOAT(0.0f, output.R6);
}





#endif // TEST
