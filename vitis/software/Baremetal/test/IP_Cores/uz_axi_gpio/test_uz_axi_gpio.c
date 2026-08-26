#ifdef TEST

#include "unity.h"

#include "uz_axi_gpio.h"
#include "test_assert_with_exception.h"

#include "mock_xgpio.h"
#include "mock_xstatus.h"
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0A0AFFFF
#define TEST_DEVICE_ID 0

void setUp(void)
{
    uz_axi_gpio_reset_allocation();
}

void test_uz_axi_gpio_configuration_with_max_outputs(void)
{
    // Instance that the _Expect functions point to, not actually used
    XGpio xinstance = {
        .BaseAddress = TEST_BASE_ADDRESS,
        .InterruptPresent = false,
        .IsDual = false,
        .IsReady = false};
    struct uz_axi_gpio_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .device_id = TEST_DEVICE_ID,
        .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
        .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};

    // Notice that it is not possible to test that the driver actually calls XGpio_Initialize with the correct pointer, i.e., the pointer that points to the correct config
    // The test just tests that "some" pointer is passed but tests for the correct device ic
    // Regarding ReturnThruPtr, see: https://github.com/ThrowTheSwitch/CMock/issues/105
    XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 1);
    XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
    XGpio_Initialize_IgnoreArg_InstancePtr();
    XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
    uz_axi_gpio_init(config);
}

void test_uz_axi_gpio_configuration_with_max_inputs(void)
{
    XGpio xinstance = {
        .BaseAddress = TEST_BASE_ADDRESS,
        .InterruptPresent = false,
        .IsDual = false,
        .IsReady = false};
    struct uz_axi_gpio_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .device_id = TEST_DEVICE_ID,
        .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
        .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};
    XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
    XGpio_Initialize_IgnoreArg_InstancePtr();
    XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
    XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_INPUT);
    uz_axi_gpio_init(config);
}

void test_uz_axi_gpio_configuration_with_more_than_adapter_card_pins_fails(void)
{
    struct uz_axi_gpio_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .device_id = TEST_DEVICE_ID,
        .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER + 1U,
        .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};

    TEST_ASSERT_FAIL_ASSERT(uz_axi_gpio_init(config));
}

void test_uz_axi_gpio_write_mask_to_outputs(void)
{
    XGpio xinstance = {
        .BaseAddress = TEST_BASE_ADDRESS,
        .InterruptPresent = false,
        .IsDual = false,
        .IsReady = false};
    struct uz_axi_gpio_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .device_id = TEST_DEVICE_ID,
        .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
        .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
    XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
    XGpio_Initialize_IgnoreArg_InstancePtr();
    XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
    XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
    uz_axi_gpio_t* test_instance= uz_axi_gpio_init(config);

    uint32_t test_bitmask = 0xF0F0F0F0U;
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, 0x30F0F0F0U);
     uz_axi_gpio_write_bitmask(test_instance,test_bitmask);
}

void test_uz_axi_gpio_read_mask_from_inputs(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_INPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uint32_t test_bitmask = 0xF0F0F0F0U;
     XGpio_DiscreteRead_ExpectAndReturn(&xinstance, 1U, test_bitmask);
     uint32_t returned_bitmask=uz_axi_gpio_read_bitmask(test_instance);
     TEST_ASSERT_EQUAL_UINT32(test_bitmask,returned_bitmask);
}

void test_uz_axi_gpio_read_pin_4(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance,1U, UZ_AXI_GPIO_DIRECTION_ALL_INPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uint32_t test_bitmask = 0xF0F0F0F0U;
     //  Bit mask 11110000111100001111000011110000
     //Pin number                       9876543210    
     // Read out the state of pin 4 (zero indexed!) which is 0
     XGpio_DiscreteRead_ExpectAndReturn(&xinstance, 1U, test_bitmask);

     bool returned_value = uz_axi_gpio_read_pin_zero_based(test_instance, 4U);
     TEST_ASSERT_TRUE(returned_value); // returned value has to be true, as bit 5 is 1=true
}

void test_uz_axi_gpio_read_pin_3(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_INPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uint32_t test_bitmask = 0xF0F0F0F0U;
     //  Bit mask  11110000111100001111000011110000
     // Pin number                       9876543210
     // Read out the state of pin 3 (zero indexed!) which is 0
     XGpio_DiscreteRead_ExpectAndReturn(&xinstance, 1U, test_bitmask);

     bool returned_value = uz_axi_gpio_read_pin_zero_based(test_instance, 3U);
     TEST_ASSERT_FALSE(returned_value); // returned value has to be true, as bit 5 is 1=true
}

void test_uz_axi_gpio_read_pin_that_does_not_exist(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = 16,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_INPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

    // Assertion has to trigger since pin 25 is not existent as the config states that only 16 pins are present
     TEST_ASSERT_FAIL_ASSERT(uz_axi_gpio_read_pin_zero_based(test_instance, 25U));
}

void test_uz_axi_gpio_write_pin_4(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uint32_t test_bitmask = 0xF0F0F0F0U;
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, 0x30F0F0F0U);
     uz_axi_gpio_write_bitmask(test_instance, test_bitmask);

     // 00110000111100001111000011100000 is now the expected bitmask as bit 4 (zero based) is changed from 1 to 0
     uint32_t expected_write_bitmask = 0x30F0F0E0;
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, expected_write_bitmask);
     uz_axi_gpio_write_pin_zero_based(test_instance, 4U,false);
}

void test_uz_axi_gpio_write_pin_3(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uint32_t test_bitmask = 0xF0F0F0F0U;
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, 0x30F0F0F0U);
     uz_axi_gpio_write_bitmask(test_instance, test_bitmask);

     // 00110000111100001111000011111000 is now the expected bitmask as bit 3 (zero based) is changed from 0 to 1
     uint32_t expected_write_bitmask = 0x30F0F0F8;
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, expected_write_bitmask);
     uz_axi_gpio_write_pin_zero_based(test_instance, 3U, true);
}

void test_uz_axi_gpio_shadow_pin_updates_are_deferred_until_flush(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uz_axi_gpio_set_output_pin(test_instance, 3U);
     uz_axi_gpio_set_output_pin(test_instance, 4U);
     uz_axi_gpio_clear_output_pin(test_instance, 3U);

     TEST_ASSERT_EQUAL_UINT32(UZ_AXI_GPIO_PIN_04, uz_axi_gpio_get_output_shadow(test_instance));
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, UZ_AXI_GPIO_PIN_04);
     uz_axi_gpio_flush_outputs(test_instance);
}

void test_uz_axi_gpio_shadow_bitmask_updates_are_deferred_until_flush(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uz_axi_gpio_set_output_bitmask(test_instance, UZ_AXI_GPIO_PIN_03 | UZ_AXI_GPIO_PIN_04);
     uz_axi_gpio_clear_output_bitmask(test_instance, UZ_AXI_GPIO_PIN_03);

     TEST_ASSERT_EQUAL_UINT32(UZ_AXI_GPIO_PIN_04, uz_axi_gpio_get_output_shadow(test_instance));
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, UZ_AXI_GPIO_PIN_04);
     uz_axi_gpio_flush_outputs(test_instance);
}

void test_uz_axi_gpio_immediate_write_keeps_shadow_coherent(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     XGpio_DiscreteWrite_Expect(&xinstance, 1U, UZ_AXI_GPIO_PIN_03);
     uz_axi_gpio_write_pin_zero_based(test_instance, 3U, true);
     TEST_ASSERT_EQUAL_UINT32(UZ_AXI_GPIO_PIN_03, uz_axi_gpio_get_output_shadow(test_instance));

     uz_axi_gpio_set_output_pin(test_instance, 4U);
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, UZ_AXI_GPIO_PIN_03 | UZ_AXI_GPIO_PIN_04);
     uz_axi_gpio_flush_outputs(test_instance);
}

void test_uz_axi_gpio_input_pins_are_masked_from_output_shadow(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = UZ_AXI_GPIO_MAX_PIN_NUMBER,
         .direction_of_pins = UZ_AXI_GPIO_PIN_03};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_PIN_03);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     uz_axi_gpio_set_output_bitmask(test_instance, UZ_AXI_GPIO_PIN_03 | UZ_AXI_GPIO_PIN_04);
     TEST_ASSERT_EQUAL_UINT32(UZ_AXI_GPIO_PIN_04, uz_axi_gpio_get_output_shadow(test_instance));
     XGpio_DiscreteWrite_Expect(&xinstance, 1U, UZ_AXI_GPIO_PIN_04);
     uz_axi_gpio_flush_outputs(test_instance);
}

void test_uz_axi_gpio_write_pin_that_does_not_exist(void)
{
     XGpio xinstance = {
         .BaseAddress = TEST_BASE_ADDRESS,
         .InterruptPresent = false,
         .IsDual = false,
         .IsReady = false};
     struct uz_axi_gpio_config_t config = {
         .base_address = TEST_BASE_ADDRESS,
         .device_id = TEST_DEVICE_ID,
         .number_of_pins = 16,
         .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};
     XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 0);
     XGpio_Initialize_IgnoreArg_InstancePtr();
     XGpio_Initialize_ReturnThruPtr_InstancePtr(&xinstance);
     XGpio_SetDataDirection_Expect(&xinstance, 1U, UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT);
     uz_axi_gpio_t *test_instance = uz_axi_gpio_init(config);

     TEST_ASSERT_FAIL_ASSERT(uz_axi_gpio_write_pin_zero_based(test_instance, 16U, true));
}

#endif // TEST
