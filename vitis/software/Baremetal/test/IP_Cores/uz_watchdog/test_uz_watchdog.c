#ifdef TEST

#include "unity.h"

#include "uz_watchdog.h"
#include "mock_xwdttb.h"

#include "test_assert_with_exception.h"

/* How to set the second Window Size and the Interruption Point.
 * ------------------------------------------------------------
 * WIN_WDT_SW_COUNT		Second Window Size (Initial counter value)
 * WIN_WDT_BSS_COUNT	Byte selected of the counter. Possible values: 0,1,2,3
 * WIN_WDT_SBC_COUNT	Value to the selected byte. When selected byte of the counter equals this value and the rest of bits are 0, the INT is activated.
 *
 * With the next values we have:
 * 0x2710 = 10.000 clock ticks => 100 microsec to launch the Interruption
 * We establish the interruption point in the value of the counter: 0x0000FF00
 * to have enough time execute the handler function (and restart the WD timer inside the Second Win if we wan to resume normal execution)
 *
 * so we add the clocks needed to the int point: 0x0000FF00 + 0x2710 =  0x00012610 Total Second Window Size
 * */
#define WIN_WDT_SW_COUNT	0x00012610	/**< INITIAL COUNTER VALUE*/
/* FROM FILE xparameters.h*/
#define WDTTB_DEVICE_ID 0U
#define XPAR_WDTTB_0_DEVICE_ID 0U
#define XPAR_WDTTB_0_BASEADDR 0x80110000U
#define XPAR_WDTTB_0_HIGHADDR 0x8011FFFFU
#define XPAR_WDTTB_0_ENABLE_WINDOW_WDT 1U
#define XPAR_WDTTB_0_MAX_COUNT_WIDTH 32U
#define XPAR_WDTTB_0_SST_COUNT_WIDTH 30U
#define XPAR_WDTTB_0_IS_PL 1U

/************************** Variable Definitions *****************************/
XWdtTb_Config conf =
{
    XPAR_WDTTB_0_DEVICE_ID,
    XPAR_WDTTB_0_BASEADDR,
    XPAR_WDTTB_0_ENABLE_WINDOW_WDT,
    XPAR_WDTTB_0_MAX_COUNT_WIDTH,
    XPAR_WDTTB_0_SST_COUNT_WIDTH,
    XPAR_WDTTB_0_IS_PL
};

XWdtTb testWdtTb = {
.Config = {XPAR_WDTTB_0_DEVICE_ID,
    XPAR_WDTTB_0_BASEADDR,
    XPAR_WDTTB_0_ENABLE_WINDOW_WDT,
    XPAR_WDTTB_0_MAX_COUNT_WIDTH,
    XPAR_WDTTB_0_SST_COUNT_WIDTH,
    XPAR_WDTTB_0_IS_PL},        /**< Hardware Configuration */
.IsReady = XIL_COMPONENT_IS_READY,          /**< Device is initialized and ready */
};

struct uz_watchdog_ip_config_t config={
    .CounterValue=WIN_WDT_SW_COUNT,
    .device_id=WDTTB_DEVICE_ID
};

//Initialize the WDTTB structure
uz_watchdog_ip_t *WdtTbInstancePtr;



/*****************************************************************************/

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_watchdog_initialization(void)
{  
    // expected_init_functions();
    XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID,&conf);

    XWdtTb_CfgInitialize_ExpectAndReturn(&testWdtTb,&conf,conf.BaseAddr,0);
    XWdtTb_CfgInitialize_IgnoreArg_InstancePtr();
    XWdtTb_CfgInitialize_ReturnThruPtr_InstancePtr(&testWdtTb);

    XWdtTb_ConfigureWDTMode_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SelfTest_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SetRegSpaceAccessMode_Ignore();
    XWdtTb_SetWindowCount_Ignore();
    XWdtTb_SetByteCount_Ignore();
    XWdtTb_SetByteSegment_Ignore();
    XWdtTb_DisableSst_Ignore();
    XWdtTb_DisablePsm_Ignore();
    XWdtTb_DisableFailCounter_Ignore();
    // Invoke the function to test if it does whats Expected 
	WdtTbInstancePtr = uz_watchdog_ip_init(config); 
}

void test_uz_watchdog_fail_assert_if_window_size_is_zero(void)
{
    struct uz_watchdog_ip_config_t bad_config={
        .device_id=WDTTB_DEVICE_ID
    };
    TEST_ASSERT_FAIL_ASSERT(uz_watchdog_ip_init(bad_config) );
}

void test_uz_watchdog_start(void)
{
//    expected_init_functions();
    XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID,&conf);

    XWdtTb_CfgInitialize_ExpectAndReturn(&testWdtTb,&conf,conf.BaseAddr,0);
    XWdtTb_CfgInitialize_IgnoreArg_InstancePtr();
    XWdtTb_CfgInitialize_ReturnThruPtr_InstancePtr(&testWdtTb);

    XWdtTb_ConfigureWDTMode_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SelfTest_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SetRegSpaceAccessMode_Ignore();
    XWdtTb_SetWindowCount_Ignore();
    XWdtTb_SetByteCount_Ignore();
    XWdtTb_SetByteSegment_Ignore();
    XWdtTb_DisableSst_Ignore();
    XWdtTb_DisablePsm_Ignore();
    XWdtTb_DisableFailCounter_Ignore();
    WdtTbInstancePtr = uz_watchdog_ip_init(config);

    XWdtTb_SetRegSpaceAccessMode_Expect(&testWdtTb, 1);

    // XWdtTb_AlwaysEnable_Expect(&testWdtTb);
    // XWdtTb_EnableExtraProtection_Expect(&testWdtTb);

    XWdtTb_Start_Expect(&testWdtTb);

    XWdtTb_SetRegSpaceAccessMode_Expect(&testWdtTb, 1);                     
    // Invoke the function to test if it does whats Expected                                     
    uz_watchdog_ip_start(WdtTbInstancePtr);
}

void test_uz_watchdog_start_fail_assert_if_null(void)
{
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(uz_watchdog_ip_start(NULL));
}

void test_uz_watchdog_restart(void)
{
    // expected_init_functions();
    XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID,&conf);

    XWdtTb_CfgInitialize_ExpectAndReturn(&testWdtTb,&conf,conf.BaseAddr,0);
    XWdtTb_CfgInitialize_IgnoreArg_InstancePtr();
    XWdtTb_CfgInitialize_ReturnThruPtr_InstancePtr(&testWdtTb);

    XWdtTb_ConfigureWDTMode_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SelfTest_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SetRegSpaceAccessMode_Ignore();
    XWdtTb_SetWindowCount_Ignore();
    XWdtTb_SetByteCount_Ignore();
    XWdtTb_SetByteSegment_Ignore();
    XWdtTb_DisableSst_Ignore();
    XWdtTb_DisablePsm_Ignore();
    XWdtTb_DisableFailCounter_Ignore();
    WdtTbInstancePtr = uz_watchdog_ip_init(config);
  
    XWdtTb_RestartWdt_Expect(&testWdtTb);
                                            
    // Invoke the function to test if it does whats Expected                                     
    uz_watchdog_ip_restart(WdtTbInstancePtr);
}

void test_uz_watchdog_restart_fail_assert_if_null(void)
{
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(uz_watchdog_ip_restart(NULL));
}


void test_uz_watchdog_WdtTbIntrHandler_badevent(void)
{
    // expected_init_functions();
    XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID,&conf);

    XWdtTb_CfgInitialize_ExpectAndReturn(&testWdtTb,&conf,conf.BaseAddr,0);
    XWdtTb_CfgInitialize_IgnoreArg_InstancePtr();
    XWdtTb_CfgInitialize_ReturnThruPtr_InstancePtr(&testWdtTb);

    XWdtTb_ConfigureWDTMode_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SelfTest_IgnoreAndReturn(XST_SUCCESS);
    XWdtTb_SetRegSpaceAccessMode_Ignore();
    XWdtTb_SetWindowCount_Ignore();
    XWdtTb_SetByteCount_Ignore();
    XWdtTb_SetByteSegment_Ignore();
    XWdtTb_DisableSst_Ignore();
    XWdtTb_DisablePsm_Ignore();
    XWdtTb_DisableFailCounter_Ignore();
    WdtTbInstancePtr = uz_watchdog_ip_init(config);
  
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(uz_watchdog_IntrHandler(WdtTbInstancePtr));
}

void test_uz_watchdog_WdtTbIntrHandler_fail_assert_if_null(void)
{
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(uz_watchdog_IntrHandler(NULL));
}

#endif // TEST
