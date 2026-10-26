#pragma once

#ifdef TEST
#ifdef UNITY_LINE_TYPE
#define UZ_CEXCEPTION_UNITY_LINE_TYPE UNITY_LINE_TYPE
#else
#define UZ_CEXCEPTION_UNITY_LINE_TYPE unsigned long
#endif

void UnityFail(const char *message, const UZ_CEXCEPTION_UNITY_LINE_TYPE line);

#define CEXCEPTION_NO_CATCH_HANDLER(id) UnityFail("Unexpected uz_assert; wrap expected assertions in TEST_ASSERT_FAIL_ASSERT", (UZ_CEXCEPTION_UNITY_LINE_TYPE)(id))
#endif
