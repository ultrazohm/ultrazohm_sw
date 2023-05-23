#ifdef TEST

#include "unity.h"

#include "uz_axi_gpio.h"
#include "mock_xpgio.h"
#include "mock_xstatus.h"

#define TEST_BASE_ADDRESS 0x0A0AFFFF
#define TEST_DEVICE_ID 0

// Instance that the _Expect functions point to, not actually used
XGpio xinstance;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_axi_gpio_configuration_with_32_outputs(void)
{
    struct uz_axi_gpio_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .device_id = TEST_DEVICE_ID,
        .number_of_pins = 32,
        .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT};

    // Notice that it is not possible to test that the driver actually calls XGpio_Initialize with the correct pointer, i.e., the pointer that points to the correct config
    // The test just tests that "some" pointer is passed but tests for the correct device ic
    XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 1);
    XGpio_SetDataDirection_Expect(&xinstance, 1U, 0x00000000);
    uz_axi_gpio_init(config);
}

void test_uz_axi_gpio_configuration_with_32_inputs(void)
{
    struct uz_axi_gpio_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .device_id = TEST_DEVICE_ID,
        .number_of_pins = 32,
        .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT};

    // Notice that it is not possible to test that the driver actually calls XGpio_Initialize with the correct pointer, i.e., the pointer that points to the correct config
    // The test just tests that "some" pointer is passed but tests for the correct device ic
    XGpio_Initialize_ExpectAndReturn(&xinstance, TEST_DEVICE_ID, 1);
    XGpio_SetDataDirection_Expect(&xinstance, 1U, 0xFFFFFFFF);
    uz_axi_gpio_init(config);
}

#endif // TEST
