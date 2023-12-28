// "Copyright [year] <Copyright Owner>"
#ifdef TEST  // NOLINT
#include <stdint.h>

#include "unity.h"

#include "uz_EnDat.h"
#include "test_assert_with_exception.h"  // NOLINT
#include "mock_uz_EnDat_hw.h"  // Mock the _hw functions to isolate testing


#define TEST_BASE_ADDRESS 0xE00F00A
#define TEST_IP_CORE_FRQ 100000000U


void setUp(void) {
}

void tearDown(void) {
}

void test_uz_EnDat_fail_assert_if_base_address_is_zero(void) {
    struct uz_EnDat_config_t config = {
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config));
}

void test_uz_EnDat_fail_assert_if_ip_frequency_is_zero(void) {
    struct uz_EnDat_config_t config = {
        .base_address = TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config));
}


void test_uz_EnDat_fail_assert_if_write_control_and_divider_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_control_and_divider(NULL, 0, 0));
}

void test_uz_EnDat_fail_assert_if_write_control_and_divider_from_object_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_control_and_divider_from_object(NULL));
}

void test_uz_EnDat_fail_assert_if_write_factor_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_factor(NULL, 0, 0));
}



void test_uz_EnDat_fail_assert_if_read_statusword_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_statusword(NULL));
}


void test_uz_EnDat_fail_assert_if_read_pos_tx_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_pos(NULL, 0));
}

void test_uz_EnDat_fail_assert_if_read_crc_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_crc(NULL));
}

void test_uz_EnDat_fail_assert_if_write_default_values_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_write_default_values(NULL));
}


void test_uz_EnDat_factor_converter_float_to_special_int_100(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_factor_converter(1.00f), 100U);
}
void test_uz_EnDat_factor_converter_float_to_special_int_150(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_factor_converter(1.50f), 150U);
}

void test_uz_EnDat_factor_converter_float_to_special_int_050(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_factor_converter(0.50f), 50U);
}

void test_uz_EnDat_frequency_to_divider_expansion_12500kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_12500000Hz), 0);
}

void test_uz_EnDat_frequency_to_divider_expansion_6250kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_6250000Hz), 1);
}


void test_uz_EnDat_frequency_to_divider_expansion_3125kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_3125000Hz), 2);
}


void test_uz_EnDat_frequency_to_divider_expansion_1562kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_1562500Hz), 3);
}

void test_uz_EnDat_frequency_to_divider_expansion_781kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_781250Hz), 4);
}

void test_uz_EnDat_frequency_to_divider_expansion_390kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_390625Hz), 5);
}

void test_uz_EnDat_frequency_to_divider_expansion_195kHz(void) {
    TEST_ASSERT_EQUAL_INT(uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_195312Hz), 6);
}

void test_uz_EnDat_posconv_lsb_to_2pi(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_pos_to_rad_converter(1U, uz_EnDat_23_bit), 7.490141458742299498504682322773e-7f);
}

void test_uz_EnDat_posconv_msb_to_2pi(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_pos_to_rad_converter(4194304U, uz_EnDat_23_bit), 3.1415930280968661755776183085136f);
}

void test_uz_EnDat_posconv_max_to_2pi(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_pos_to_rad_converter(8388607U, uz_EnDat_23_bit), 6.283185307179586476925286766559f);
}

void test_uz_EnDat_posconv_rnd_to_2pi(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_pos_to_rad_converter(5592405U, uz_EnDat_23_bit), 4.1887904544577729426935077945287f);
}



void test_uz_EnDat_fail_assert_if_uz_EnDat_read_time_elapsed_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_read_time_elapsed(NULL, uz_EnDat_elapsed_t0_t1));
}

void test_uz_EnDat_time_elapsed_ns_to_s_converter_1(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_time_elapsed_ns_to_s_converter(1000000000U), 1.0f);
}

void test_uz_EnDat_time_elapsed_ns_to_s_converter_0_5(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_time_elapsed_ns_to_s_converter(500000000U), 0.5f);
}

void test_uz_EnDat_time_elapsed_ns_to_s_converter_1_5(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_time_elapsed_ns_to_s_converter(1500000000U), 1.5f);
}

void test_uz_EnDat_time_elapsed_ns_to_s_converter_msb(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_time_elapsed_ns_to_s_converter(3999999000U), 3.999999f);
}

void test_uz_EnDat_time_elapsed_ns_to_s_converter_lsb(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_time_elapsed_ns_to_s_converter(1U), 0.000000001f);
}

void test_uz_EnDat_calc_revs_from_pos_delta_and_time_15upm(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_calc_revs_from_pos_delta_and_time(0, (ENDAT_23_BIT_MAX_VALUE/4), 1.0f, 0U, uz_EnDat_23_bit, 1U), 15.0f);
}

void test_uz_EnDat_calc_revs_from_pos_delta_and_time_15kupm(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_calc_revs_from_pos_delta_and_time(0, (ENDAT_23_BIT_MAX_VALUE/4), 0.001f, 0U, uz_EnDat_23_bit, 1U), 15000.0f);
}

void test_uz_EnDat_calc_revs_from_pos_delta_and_time_negative_15upm(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_calc_revs_from_pos_delta_and_time((ENDAT_23_BIT_MAX_VALUE/4), 0, 1.0f, 0U, uz_EnDat_23_bit, 1U), -15.0f);
}

void test_uz_EnDat_calc_revs_from_pos_delta_and_time_negative_15kupm(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_calc_revs_from_pos_delta_and_time((ENDAT_23_BIT_MAX_VALUE/4), 0, 0.001f, 0U, uz_EnDat_23_bit, 1U), -15000.0f);
}

void test_uz_EnDat_rpm_to_rad_per_second_converter_positive(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_rpm_to_rad_per_second_converter(100.0f), 10.471975);
}

void test_uz_EnDat_rpm_to_rad_per_second_converter_negative(void) {
    TEST_ASSERT_EQUAL_FLOAT(uz_EnDat_rpm_to_rad_per_second_converter(-100.0f), -10.471975);
}

void test_uz_EnDat_set_output_enable_in_controlword(void) {
    controlword test = 0x0ABC;
    
    TEST_ASSERT_EQUAL_INT(0x1ABCU , uz_EnDat_set_output_enable_in_controlword(test));
}

void test_uz_EnDat_reset_output_enable_in_controlword(void) {
    controlword test = 0xBBCD;
    
    TEST_ASSERT_EQUAL_INT(0xABCDU , uz_EnDat_reset_output_enable_in_controlword(test));
}

void test_uz_EnDat_enable_config_evaluation_in_IP(void) {
    controlword test = 0x0ABC;
    
    TEST_ASSERT_EQUAL_INT(0x8ABCU , uz_EnDat_enable_config_evaluation_in_IP(test));
}

void test_uz_EnDat_disable_config_evaluation_in_IP(void) {
    controlword test = 0xFBCD;
    
    TEST_ASSERT_EQUAL_INT(0x7BCDU , uz_EnDat_disable_config_evaluation_in_IP(test));
}

void test_uz_EnDat_set_sensor_precision_in_controlword_19_bit(void) {
    controlword test = 0xAF87;
    
    TEST_ASSERT_EQUAL_INT(0xA087 , uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_19_bit));
}

void test_uz_EnDat_set_sensor_precision_in_controlword_21_bit(void) {
    controlword test = 0xAF87;
    
    TEST_ASSERT_EQUAL_INT(0xA107 , uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_21_bit));
}

void test_uz_EnDat_set_sensor_precision_in_controlword_23_bit(void) {
    controlword test = 0xAF87;
    
    TEST_ASSERT_EQUAL_INT(0xA207 , uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_23_bit));
}

void test_uz_EnDat_set_sensor_precision_in_controlword_25_bit(void) {
    controlword test = 0xAF87;
    
    TEST_ASSERT_EQUAL_INT(0xA407 , uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_25_bit));
}

void test_uz_EnDat_set_sensor_precision_in_controlword_27_bit(void) {
    controlword test = 0xAF87;
    
    TEST_ASSERT_EQUAL_INT(0xA807 , uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_27_bit));
}

void test_uz_EnDat_fetch_sensor_precision_from_controlword_19_bit(void) {
    controlword test = 0xAF87;
    test = uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_19_bit);
    TEST_ASSERT_EQUAL_INT(uz_EnDat_19_bit , uz_EnDat_fetch_sensor_precision_from_controlword(test));
}

void test_uz_EnDat_fetch_sensor_precision_from_controlword_21_bit(void) {
    controlword test = 0xAF87;
    test = uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_21_bit);
    TEST_ASSERT_EQUAL_INT(uz_EnDat_21_bit , uz_EnDat_fetch_sensor_precision_from_controlword(test));
}

void test_uz_EnDat_fetch_sensor_precision_from_controlword_23_bit(void) {
    controlword test = 0xAF87;
    test = uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_23_bit);
    TEST_ASSERT_EQUAL_INT(uz_EnDat_23_bit , uz_EnDat_fetch_sensor_precision_from_controlword(test));
}
void test_uz_EnDat_fetch_sensor_precision_from_controlword_25_bit(void) {
    controlword test = 0xAF87;
    test = uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_25_bit);
    TEST_ASSERT_EQUAL_INT(uz_EnDat_25_bit , uz_EnDat_fetch_sensor_precision_from_controlword(test));
}
void test_uz_EnDat_fetch_sensor_precision_from_controlword_27_bit(void) {
    controlword test = 0xAF87;
    test = uz_EnDat_set_sensor_precision_in_controlword(test, uz_EnDat_27_bit);
    TEST_ASSERT_EQUAL_INT(uz_EnDat_27_bit , uz_EnDat_fetch_sensor_precision_from_controlword(test));
}
void test_uz_EnDat_fail_assert_if_fetch_sensor_precision_from_EnDat_object_is_called_with_NULL_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_fetch_sensor_precision_from_EnDat_object(NULL));
}
void test_uz_EnDat_set_operation_mode_000111(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x7 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values));
}

void test_uz_EnDat_set_operation_mode_111000(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x38 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values_with_additional_data));
}

void test_uz_EnDat_set_operation_mode_001110(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0xE , uz_EnDat_set_operation_mode(test, uz_EnDat_Selection_of_memory_area));
}

void test_uz_EnDat_set_operation_mode_001001(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x9 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values_and_selection_of_memory_area_or_of_the_additional_data));
}

void test_uz_EnDat_set_operation_mode_100011(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x23 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_parameters));
}

void test_uz_EnDat_set_operation_mode_100100(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x24 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values_and_send_parameter));
}

void test_uz_EnDat_set_operation_mode_011100(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x1C , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_receive_parameters));
}

void test_uz_EnDat_set_operation_mode_011011(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x1B , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values_and_receive_parameter));
}

void test_uz_EnDat_set_operation_mode_101010(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x2A , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_receive_reset));
}
void test_uz_EnDat_set_operation_mode_101101(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x2D , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values_and_receive_error_reset));
}
void test_uz_EnDat_set_operation_mode_110001(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x31 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_receive_test_command));
}
void test_uz_EnDat_set_operation_mode_110110(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x36 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_position_values_and_receive_test_command));
}

void test_uz_EnDat_set_operation_mode_010101(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x15 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_send_test_values));
}

void test_uz_EnDat_set_operation_mode_010010(void) {
    controlword test = 0x0;
        TEST_ASSERT_EQUAL_INT(0x12 , uz_EnDat_set_operation_mode(test, uz_EnDat_Encoder_receive_communication_command));
}
#endif  // TEST
