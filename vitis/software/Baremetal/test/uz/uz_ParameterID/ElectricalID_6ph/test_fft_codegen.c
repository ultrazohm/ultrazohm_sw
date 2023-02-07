#ifdef TEST

#include "unity.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "FFTRecordedVoltage.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fft(void)
{
    float data[10000];
    float sampletime = 1.0f/10000.0f;
    float frequencies[5001];
    float amplitudes[5001];
    float angles[5001];
    FFTRecordedVoltage(data, sampletime, frequencies, amplitudes, angles);
    TEST_ASSERT_EQUAL_FLOAT(0.0f,frequencies[0]);
}

#endif // TEST
