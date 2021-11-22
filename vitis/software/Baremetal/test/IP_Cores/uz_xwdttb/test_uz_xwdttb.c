#ifdef TEST

#include "unity.h"

#include "uz_xwdttb.h"

// Driver level to be mocked (from XILINX)
#include "mock_xwdttb.h"
#include "mock_xscugic.h"
//#include "mock_xil_exception.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_xwdttb_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_xwdttb");
}

void test_uz_xwdttb_initialization(void)
{
    
    XWdtTb_Config *Config;
    XWdtTb WdtTbInst;
    int Status;
    XWdtTb_LookupConfig_ExpectAndReturn(WDTTB_DEVICE_ID, Config);
    //XWdtTb_CfgInitialize_ExpectAndReturn(&WdtTbIns,Config,0,Status);
    WdtTbInit(0);
}

#endif // TEST
