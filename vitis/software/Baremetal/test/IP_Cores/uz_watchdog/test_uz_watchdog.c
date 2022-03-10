#ifdef TEST

#include "unity.h"

#include "uz_watchdog.h"

// Driver level to be mocked (from XILINX)
#include "mock_xwdttb.h"
//#include "mock_xscugic.h"
//#include "mock_xil_exception.h"

#include "test_assert_with_exception.h"

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
    .WdtTbDeviceId=WDTTB_DEVICE_ID
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

// // Private function declaration
// void expected_init_functions(void);
// // Private function definition
// inline void expected_init_functions(void)
// {  
//     XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID,&conf);
//     XWdtTb_CfgInitialize_IgnoreAndReturn(XST_SUCCESS);
//     XWdtTb_ConfigureWDTMode_IgnoreAndReturn(XST_SUCCESS);
//     XWdtTb_SelfTest_IgnoreAndReturn(XST_SUCCESS);
//     XWdtTb_SetRegSpaceAccessMode_Ignore();
//     XWdtTb_SetWindowCount_Ignore();
//     XWdtTb_SetByteCount_Ignore();
//     XWdtTb_SetByteSegment_Ignore();
//     XWdtTb_DisableSst_Ignore();
//     XWdtTb_DisablePsm_Ignore();
//     XWdtTb_DisableFailCounter_Ignore(); 
// }

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
        .WdtTbDeviceId=WDTTB_DEVICE_ID
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
