#ifdef TEST

#include "unity.h"

#include "uz_xwdttb.h"

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

/*****************************************************************************/

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_xwdttb_initialization(void)
{  
    XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID,&conf);
    XWdtTb_CfgInitialize_IgnoreAndReturn(XST_SUCCESS);
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
    uz_WdtTb_init();
  
}

void test_uz_xwdttb_start(void)
{
    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
	    .IsReady = XIL_COMPONENT_IS_READY,		/**< Device is initialized and ready */
    };

    XWdtTb_SetRegSpaceAccessMode_Expect(&testWdtTb, 1);
    XWdtTb_AlwaysEnable_Expect(&testWdtTb);
    XWdtTb_EnableExtraProtection_Expect(&testWdtTb);
    XWdtTb_Start_Expect(&testWdtTb);
    XWdtTb_SetRegSpaceAccessMode_Expect(&testWdtTb, 1);                                             
    // Invoke the function to test if it does whats Expected                                     
    WdtTb_Start(&testWdtTb);
}

void test_uz_xwdttb_start_fail_assert_if_not_ready(void)
{

    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
    };

    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(WdtTb_Start(&testWdtTb));
}

void test_uz_xwdttb_start_fail_assert_if_null(void)
{
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(WdtTb_Start(NULL));
}

void test_uz_xwdttb_restart(void)
{
    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
	    .IsReady = XIL_COMPONENT_IS_READY,		/**< Device is initialized and ready */
    };
  
    XWdtTb_RestartWdt_Expect(&testWdtTb);
                                            
    // Invoke the function to test if it does whats Expected                                     
    WdtTb_Restart(&testWdtTb);
}

void test_uz_xwdttb_restart_fail_assert_if_not_ready(void)
{

    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
    };
    
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(WdtTb_Restart(&testWdtTb));
}

void test_uz_xwdttb_restart_fail_assert_if_null(void)
{
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(WdtTb_Restart(NULL));
}

void test_uz_xwdttb_WdtTbIntrHandler_goodevent(void)
{
    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
	    .IsReady = XIL_COMPONENT_IS_READY,		/**< Device is initialized and ready */
    };
  
    XWdtTb_RestartWdt_Expect(&testWdtTb);
    XWdtTb_IntrClear_Expect(&testWdtTb);
    XWdtTb_GetLastEvent_ExpectAndReturn(&testWdtTb, XWDTTB_NO_BAD_EVENT); 

    // Invoke the function to test if it does whats Expected                                     
    WdtTbIntrHandler(&testWdtTb);
}

void test_uz_xwdttb_WdtTbIntrHandler_badevent(void)
{
    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
	    .IsReady = XIL_COMPONENT_IS_READY,		/**< Device is initialized and ready */
    };
  
    XWdtTb_RestartWdt_Expect(&testWdtTb);
    XWdtTb_IntrClear_Expect(&testWdtTb);
    XWdtTb_GetLastEvent_ExpectAndReturn(&testWdtTb, XWDTTB_SEC_WIN_EVENT); // BAD EVENT
    XWdtTb_Stop_ExpectAndReturn(&testWdtTb, XST_SUCCESS);

    // Invoke the function to test if it does whats Expected                                     
    WdtTbIntrHandler(&testWdtTb);
}

void test_uz_xwdttb_WdtTbIntrHandler_fail_assert_if_not_ready(void)
{

    XWdtTb testWdtTb = {
        .Config = conf,	/**< Hardware Configuration */
    };
    
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(WdtTbIntrHandler(&testWdtTb));
}

void test_uz_xwdttb_WdtTbIntrHandler_fail_assert_if_null(void)
{
    // Invoke the function to test if it does whats Expected                                     
    TEST_ASSERT_FAIL_ASSERT(WdtTbIntrHandler(NULL));
}

#endif // TEST
