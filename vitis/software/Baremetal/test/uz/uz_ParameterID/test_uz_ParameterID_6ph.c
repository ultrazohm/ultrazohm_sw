#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_ParameterID_6ph.c"
#include "uz_ParameterID_6ph.h"

#include "uz_ParaID_ControlState.h"
#include "ControlState_codegen.h"
#include "uz_ParaID_TwoMassID.h"
#include "TwoMassID_codegen.h"
#include "uz_ParaID_FrictionID.h"
#include "FrictionID_codegen.h"

#include "uz_ParaID_ElectricalID_6ph.h"
#include "ElectricalID_6ph_codegen.h"

uz_ParameterID_Data_t Data_struct;


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_ParameterID_6ph_init(void)
{
    uz_ParameterID_6ph_t* ParameterID_6ph_obj = uz_ParameterID_6ph_init(&Data_struct);
    uz_assert_not_zero_int(ParameterID_6ph_obj->is_ready);
    TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj->ControlState);
    TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj->ElectricalID);
    TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj->TwoMassID);
    TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj->FrictionID);
    //TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj->FluxMapID);
    //TEST_ASSERT_NOT_NULL(ParameterID_6ph_obj->OnlineID);
}

#endif