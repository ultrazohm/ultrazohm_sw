#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_HarmonicCurrentInjection.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include <math.h>
#include <stdbool.h> 
#include "../uz_HAL.h"
TEST_FILE("uz_signals_iir_filter.c")

struct uz_HarmonicCurrentInjection_config config = { 0 };

void setUp(void)
{
    config.order_harmonic = -5.0f;
    config.selection = abc_to_dq;
    config.config_currentcontroller.decoupling_select = no_decoupling;
    config.config_currentcontroller.config_id.Kp = 0.05f;
    config.config_currentcontroller.config_id.Ki = 10.0f;
    config.config_currentcontroller.config_id.samplingTime_sec = 0.001f;
    config.config_currentcontroller.config_id.upper_limit = 10.0f;
    config.config_currentcontroller.config_id.lower_limit = -10.0f;
    config.config_currentcontroller.config_iq.Kp = 0.05f;
    config.config_currentcontroller.config_iq.Ki = 10.0f;
    config.config_currentcontroller.config_iq.samplingTime_sec = 0.001f;
    config.config_currentcontroller.config_iq.upper_limit = 10.0f;
    config.config_currentcontroller.config_iq.lower_limit = -10.0f;
    config.config_currentcontroller.max_modulation_index = 1.0f / sqrtf(3.0f);
    config.config_bandpass_abc.selection = BandPass_second_order;
    config.config_bandpass_abc.pass_frequency_Hz = 300.0f;
    config.config_bandpass_abc.damping = 0.05f;
    config.config_bandpass_abc.sample_frequency_Hz = 1000.0f;
    config.config_bandpass_dq.selection = BandPass_second_order;
    config.config_bandpass_dq.pass_frequency_Hz = 360.0f;
    config.config_bandpass_dq.damping = 0.05f;
    config.config_bandpass_dq.sample_frequency_Hz = 1000.0f;
    config.config_lowpass_dq.selection = LowPass_first_order;
    config.config_lowpass_dq.cutoff_frequency_Hz = 60.0f/10.0f;
    config.config_lowpass_dq.sample_frequency_Hz = 1000.0f;  
}

void test_uz_HarmonicCurrentInjection_harmonic_order_assert(void){
    config.order_harmonic = 1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_HarmonicCurrentInjection_init(config));
}

void test_uz_HarmonicCurrentInjection_sample_abc_negative_order(void){
    uz_HarmonicCurrentInjection_t* instance = uz_HarmonicCurrentInjection_init(config);
    uz_3ph_abc_t i_abc_actual_Ampere = { 0 };
    uz_3ph_dq_t i_ref_harmonic_Ampere = { 0 };
    uz_3ph_abc_t HCI_abc = { 0 }; 
    float omega_el_rad_per_sec = 377.0f;
    float V_dc_volts = 48.0f;
    float phase_current[3][20] = { 
        { 0.5000f, 1.6861f, 3.0182f, 4.9286f, 5.1446f,
          4.2553f, 4.0071f, 2.8133f, 0.2222f,-1.3980f, 
         -2.4389f,-4.3761f,-5.3159f,-4.5069f,-4.0671f,
         -3.4389f,-1.0889f, 1.0312f, 2.0043f, 3.6981f},
        {-4.5801f,-5.2809f,-4.4111f,-4.0535f,-3.2560f,
         -0.7896f, 1.1684f, 2.1334f, 3.9304f, 5.3049f,
          4.7226f, 4.0965f, 3.7239f, 1.6966f,-0.6985f,
         -1.7837f,-3.2378f,-5.0661f,-5.0512f,-4.1973f},
        { 4.0801f, 3.5948f, 1.3929f,-0.8752f,-1.8886f,
         -3.4657f,-5.1755f,-4.9466f,-4.1525f,-3.9069f,
         -2.2837f, 0.2797f, 1.5921f, 2.8103f, 4.7656f,
          5.2226f, 4.3267f, 4.0349f, 3.0469f, 0.4993f}
        };
    float HCI_phase_expected[3][20] = {
        { 0.5000f, 1.6611f, 3.3009f, 4.7723f, 4.8889f, 
          4.6111f, 4.0780f, 2.3585f, 0.4369f,-1.0309f,
         -2.9157f,-4.4661f,-4.7355f,-4.7895f,-4.5132f,
         -2.8423f,-0.9930f, 0.3276f, 2.3503f, 4.2277f},
        {-4.5801f,-5.0519f,-4.5987f,-4.2298f,-2.9049f,
         -0.8068f, 0.7679f, 2.4149f, 4.1981f, 4.8138f,
          4.7489f, 4.6207f, 3.3501f, 1.3678f,-0.0766f,
         -1.8296f,-3.8798f,-4.6062f,-4.6571f,-4.9350f},
        { 4.0801f, 3.3908f, 1.2978f,-0.5425f,-1.9841f,
         -3.8043f,-4.8460f,-4.7734f,-4.6350f,-3.7829f,
         -1.8332f,-0.1546f, 1.3854f, 3.4216f, 4.5898f,
          4.6718f, 4.8728f, 4.2786f, 2.3069f, 0.7073f}
    };
    float theta_el_rad[20] = { 0.0000f, 0.3770f, 0.7540f, 1.1310f, 1.5080f, 
                               1.8850f, 2.2619f, 2.6389f, 3.0159f, 3.3929f,
                               3.7699f, 4.1469f, 4.5239f, 4.9009f, 5.2779f,
                               5.6549f, 6.0319f, 6.4088f, 6.7858f, 7.1628f};
    for (int i = 0; i < (int)(sizeof(theta_el_rad) / sizeof(float)); i++)
    {
        i_abc_actual_Ampere.a = phase_current[0][i] + HCI_abc.a;
        i_abc_actual_Ampere.b = phase_current[1][i] + HCI_abc.b;
        i_abc_actual_Ampere.c = phase_current[2][i] + HCI_abc.c;
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[0][i], i_abc_actual_Ampere.a);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[1][i], i_abc_actual_Ampere.b);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[2][i], i_abc_actual_Ampere.c);
        uz_3ph_dq_t HCI_dq = uz_HarmonicCurrentInjection_sample(instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad[i]);
        HCI_abc = uz_transformation_3ph_dq_to_abc(HCI_dq, theta_el_rad[i]);
    }
}

void test_uz_HarmonicCurrentInjection_sample_abc_positive_order(void){
    config.order_harmonic = 7.0f;
    config.config_bandpass_abc.pass_frequency_Hz = 420.0f;
    uz_HarmonicCurrentInjection_t* instance = uz_HarmonicCurrentInjection_init(config);
    uz_3ph_abc_t i_abc_actual_Ampere = { 0 };
    uz_3ph_dq_t i_ref_harmonic_Ampere = { 0 };
    uz_3ph_abc_t HCI_abc = { 0 }; 
    float omega_el_rad_per_sec = 377.0f;
    float V_dc_volts = 48.0f;
    float phase_current[3][20] = { 
        { 0.5000f, 1.4025f, 3.6906f, 4.4927f, 4.7772f, 
          5.1598f, 3.3565f, 2.8737f, 0.3080f,-1.1498f,
         -2.7844f,-4.5861f,-4.4271f,-5.3957f,-3.8572f,
         -3.0934f,-1.3371f, 0.9454f, 1.9439f, 4.3486f}, 
        {-4.5801f,-4.5187f,-5.3675f,-3.6579f,-3.0523f,
         -0.9873f, 1.0276f, 2.1983f, 4.4756f, 4.3436f,
          5.3072f, 4.3168f, 3.1326f, 1.9942f,-0.6880f,
         -1.5446f,-3.9509f,-4.4350f,-4.9259f,-4.9887f},
        { 4.0801f, 3.1162f, 1.6768f,-0.8348f,-1.7249f, 
         -4.1725f,-4.3841f,-5.0719f,-4.7836f,-3.1939f,
         -2.5228f, 0.2693f, 1.2945f, 3.4016f, 4.5452f,
          4.6380f, 5.2880f, 3.4897f, 2.9820f, 0.6401f}
        };
    float HCI_phase_expected[3][20] = {
        { 0.5000f, 1.3775f, 3.5735f, 4.7541f, 4.4246f,
          5.5174f, 3.0888f, 2.9664f, 0.4465f,-1.5200f,
         -2.2538f,-5.1463f,-3.9868f,-5.5926f,-3.9710f,
         -2.6736f,-1.9815f, 1.6646f, 1.3339f, 4.6821f},
        {-4.5801f,-4.2897f,-5.5353f,-3.6296f,-2.9098f,
         -1.2859f, 1.4324f, 1.7701f, 4.8129f, 4.2129f,
          5.1637f, 4.7203f, 2.5599f, 2.6015f,-1.1823f,
         -1.2969f,-3.8635f,-4.8644f,-4.2453f,-5.7532f},
        { 4.0801f, 2.9122f, 1.9618f,-1.1245f,-1.5148f,
         -4.2315f,-4.5212f,-4.7365f,-5.2594f,-2.6929f,
         -2.9099f, 0.4260f, 1.4269f, 2.9911f, 5.1533f,
          3.9705f, 5.8450f, 3.1998f, 2.9114f, 1.0711f}
    };
    float theta_el_rad[20] = { 0.0000f, 0.3770f, 0.7540f, 1.1310f, 1.5080f, 
                               1.8850f, 2.2619f, 2.6389f, 3.0159f, 3.3929f,
                               3.7699f, 4.1469f, 4.5239f, 4.9009f, 5.2779f,
                               5.6549f, 6.0319f, 6.4088f, 6.7858f, 7.1628f};
    for (int i = 0; i < (int)(sizeof(theta_el_rad) / sizeof(float)); i++)
    {
        i_abc_actual_Ampere.a = phase_current[0][i] + HCI_abc.a;
        i_abc_actual_Ampere.b = phase_current[1][i] + HCI_abc.b;
        i_abc_actual_Ampere.c = phase_current[2][i] + HCI_abc.c;
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[0][i], i_abc_actual_Ampere.a);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[1][i], i_abc_actual_Ampere.b);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[2][i], i_abc_actual_Ampere.c);
        uz_3ph_dq_t HCI_dq = uz_HarmonicCurrentInjection_sample(instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad[i]);
        HCI_abc = uz_transformation_3ph_dq_to_abc(HCI_dq, theta_el_rad[i]);
    }
}

void test_uz_HarmonicCurrentInjection_sample_dq_negative_order(void){
    config.selection = dq_to_dqn;
    uz_HarmonicCurrentInjection_t* instance = uz_HarmonicCurrentInjection_init(config);
    uz_3ph_abc_t i_abc_actual_Ampere = { 0 };
    uz_3ph_dq_t i_ref_harmonic_Ampere = { 0 };
    uz_3ph_abc_t HCI_abc = { 0 }; 
    float omega_el_rad_per_sec = 377.0f;
    float V_dc_volts = 48.0f;
    float phase_current[3][20] = { 
        { 0.5000f, 1.6861f, 3.0182f, 4.9286f, 5.1446f,
          4.2553f, 4.0071f, 2.8133f, 0.2222f,-1.3980f, 
         -2.4389f,-4.3761f,-5.3159f,-4.5069f,-4.0671f,
         -3.4389f,-1.0889f, 1.0312f, 2.0043f, 3.6981f},
        {-4.5801f,-5.2809f,-4.4111f,-4.0535f,-3.2560f,
         -0.7896f, 1.1684f, 2.1334f, 3.9304f, 5.3049f,
          4.7226f, 4.0965f, 3.7239f, 1.6966f,-0.6985f,
         -1.7837f,-3.2378f,-5.0661f,-5.0512f,-4.1973f},
        { 4.0801f, 3.5948f, 1.3929f,-0.8752f,-1.8886f,
         -3.4657f,-5.1755f,-4.9466f,-4.1525f,-3.9069f,
         -2.2837f, 0.2797f, 1.5921f, 2.8103f, 4.7656f,
          5.2226f, 4.3267f, 4.0349f, 3.0469f, 0.4993f}
        };
    float HCI_phase_expected[3][20] = {
        { 0.5000f, 1.6611f, 3.3009f, 4.7798f, 4.8893f,
          4.5977f, 4.0766f, 2.3749f, 0.4414f,-1.0478f,
         -2.9243f,-4.4505f,-4.7243f,-4.8030f,-4.5242f,
         -2.8329f,-0.9850f, 0.3247f, 2.3459f, 4.2233f},
        {-4.5801f,-5.0519f,-4.5987f,-4.2333f,-2.9071f,
         -0.8043f, 0.7752f, 2.4157f, 4.1846f, 4.8109f,
          4.7673f, 4.6238f, 3.3316f, 1.3658f,-0.0633f,
         -1.8278f,-3.8849f,-4.6099f,-4.6604f,-4.9281f},
        { 4.0801f, 3.3908f, 1.2978f,-0.5465f,-1.9822f,
         -3.7934f,-4.8518f,-4.7905f,-4.6260f,-3.7632f,
         -1.8430f,-0.1734f, 1.3928f, 3.4372f, 4.5875f,
          4.6607f, 4.8699f, 4.2852f, 2.3145f, 0.7049f}
    };
    float theta_el_rad[20] = { 0.0000f, 0.3770f, 0.7540f, 1.1310f, 1.5080f, 
                               1.8850f, 2.2619f, 2.6389f, 3.0159f, 3.3929f,
                               3.7699f, 4.1469f, 4.5239f, 4.9009f, 5.2779f,
                               5.6549f, 6.0319f, 6.4088f, 6.7858f, 7.1628f};
    for (int i = 0; i < (int)(sizeof(theta_el_rad) / sizeof(float)); i++)
    {
        i_abc_actual_Ampere.a = phase_current[0][i] + HCI_abc.a;
        i_abc_actual_Ampere.b = phase_current[1][i] + HCI_abc.b;
        i_abc_actual_Ampere.c = phase_current[2][i] + HCI_abc.c;
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[0][i], i_abc_actual_Ampere.a);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[1][i], i_abc_actual_Ampere.b);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[2][i], i_abc_actual_Ampere.c);
        uz_3ph_dq_t HCI_dq = uz_HarmonicCurrentInjection_sample(instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad[i]);
        HCI_abc = uz_transformation_3ph_dq_to_abc(HCI_dq, theta_el_rad[i]);
    }
}

void test_uz_HarmonicCurrentInjection_sample_dq_positive_order(void){
    config.order_harmonic = 7.0f;
    config.selection = dq_to_dqn;
    uz_HarmonicCurrentInjection_t* instance = uz_HarmonicCurrentInjection_init(config);
    uz_3ph_abc_t i_abc_actual_Ampere = { 0 };
    uz_3ph_dq_t i_ref_harmonic_Ampere = { 0 };
    uz_3ph_abc_t HCI_abc = { 0 }; 
    float omega_el_rad_per_sec = 377.0f;
    float V_dc_volts = 48.0f;
    float phase_current[3][20] = { 
        { 0.5000f, 1.4025f, 3.6906f, 4.4927f, 4.7772f, 
          5.1598f, 3.3565f, 2.8737f, 0.3080f,-1.1498f,
         -2.7844f,-4.5861f,-4.4271f,-5.3957f,-3.8572f,
         -3.0934f,-1.3371f, 0.9454f, 1.9439f, 4.3486f}, 
        {-4.5801f,-4.5187f,-5.3675f,-3.6579f,-3.0523f,
         -0.9873f, 1.0276f, 2.1983f, 4.4756f, 4.3436f,
          5.3072f, 4.3168f, 3.1326f, 1.9942f,-0.6880f,
         -1.5446f,-3.9509f,-4.4350f,-4.9259f,-4.9887f},
        { 4.0801f, 3.1162f, 1.6768f,-0.8348f,-1.7249f, 
         -4.1725f,-4.3841f,-5.0719f,-4.7836f,-3.1939f,
         -2.5228f, 0.2693f, 1.2945f, 3.4016f, 4.5452f,
          4.6380f, 5.2880f, 3.4897f, 2.9820f, 0.6401f}
        };
    float HCI_phase_expected[3][20] = {
        { 0.5000f, 1.3775f, 3.5735f, 4.7597f, 4.4189f,
          5.5175f, 3.0921f, 2.9597f, 0.4538f,-1.5196f,
         -2.2626f,-5.1453f,-3.9777f,-5.5971f,-3.9781f,
         -2.6623f,-1.9881f, 1.6629f, 1.3418f, 4.6771f},
        {-4.5801f,-4.2897f,-5.5353f,-3.6277f,-2.9107f,
         -1.2945f, 1.4441f, 1.7741f, 4.7969f, 4.2186f,
          5.1728f, 4.7131f, 2.5552f, 2.6127f,-1.1886f,
         -1.3041f,-3.8485f,-4.8710f,-4.2510f,-5.7484f},
        { 4.0801f, 2.9122f, 1.9618f,-1.1320f,-1.5082f,
         -4.2230f,-4.5362f,-4.7338f,-5.2507f,-2.7000f,
         -2.9101f, 0.4322f, 1.4226f, 2.9844f, 5.1667f,
          3.9664f, 5.8366f, 3.2081f, 2.9092f, 1.0712f}
    };
    float theta_el_rad[20] = { 0.0000f, 0.3770f, 0.7540f, 1.1310f, 1.5080f, 
                               1.8850f, 2.2619f, 2.6389f, 3.0159f, 3.3929f,
                               3.7699f, 4.1469f, 4.5239f, 4.9009f, 5.2779f,
                               5.6549f, 6.0319f, 6.4088f, 6.7858f, 7.1628f};
    for (int i = 0; i < (int)(sizeof(theta_el_rad) / sizeof(float)); i++)
    {
        i_abc_actual_Ampere.a = phase_current[0][i] + HCI_abc.a;
        i_abc_actual_Ampere.b = phase_current[1][i] + HCI_abc.b;
        i_abc_actual_Ampere.c = phase_current[2][i] + HCI_abc.c;
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[0][i], i_abc_actual_Ampere.a);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[1][i], i_abc_actual_Ampere.b);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[2][i], i_abc_actual_Ampere.c);
        uz_3ph_dq_t HCI_dq = uz_HarmonicCurrentInjection_sample(instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad[i]);
        HCI_abc = uz_transformation_3ph_dq_to_abc(HCI_dq, theta_el_rad[i]);
    }
}

void test_uz_HarmonicCurrentInjection_set_filters_abc(void){
    uz_HarmonicCurrentInjection_t* instance = uz_HarmonicCurrentInjection_init(config);
    uz_3ph_abc_t i_abc_actual_Ampere = { 0 };
    uz_3ph_dq_t i_ref_harmonic_Ampere = { 0 };
    uz_3ph_abc_t HCI_abc = { 0 }; 
    float omega_el_rad_per_sec = 377.0f;
    float V_dc_volts = 48.0f;
    float phase_current[3][20] = { 
        { 0.5000f, 1.6861f, 3.0182f, 4.9286f, 5.1446f,
          4.2553f, 4.0071f, 2.8133f, 0.2222f,-1.3980f, 
         -2.4389f,-4.3761f,-5.3159f,-4.5069f,-4.0671f,
         -3.4389f,-1.0889f, 1.0312f, 2.0043f, 3.6981f},
        {-4.5801f,-5.2809f,-4.4111f,-4.0535f,-3.2560f,
         -0.7896f, 1.1684f, 2.1334f, 3.9304f, 5.3049f,
          4.7226f, 4.0965f, 3.7239f, 1.6966f,-0.6985f,
         -1.7837f,-3.2378f,-5.0661f,-5.0512f,-4.1973f},
        { 4.0801f, 3.5948f, 1.3929f,-0.8752f,-1.8886f,
         -3.4657f,-5.1755f,-4.9466f,-4.1525f,-3.9069f,
         -2.2837f, 0.2797f, 1.5921f, 2.8103f, 4.7656f,
          5.2226f, 4.3267f, 4.0349f, 3.0469f, 0.4993f}
        };
    float HCI_phase_expected[3][20] = {
        { 0.5000f, 1.6611f, 3.3009f, 4.7723f, 4.8889f,
          4.6111f, 4.0780f, 2.3585f, 0.4369f,-1.0309f,
         -2.9157f,-4.4661f,-4.7339f,-4.7888f,-4.5246f,
         -2.8389f,-0.9775f, 0.3173f, 2.3439f, 4.2433f},
        {-4.5801f,-5.0519f,-4.5987f,-4.2298f,-2.9049f,
         -0.8068f, 0.7679f, 2.4149f, 4.1981f, 4.8138f,
          4.7489f, 4.6207f, 3.3511f, 1.3586f,-0.0738f,
         -1.8166f,-3.8887f,-4.6107f,-4.6445f,-4.9460f},
        { 4.0801f, 3.3908f, 1.2978f,-0.5425f,-1.9841f,
         -3.8043f,-4.8460f,-4.7734f,-4.6350f,-3.7829f,
         -1.8332f,-0.1546f, 1.3828f, 3.4302f, 4.5984f,
          4.6555f, 4.8662f, 4.2935f, 2.3005f, 0.7026f}
    };
    float theta_el_rad[20] = { 0.0000f, 0.3770f, 0.7540f, 1.1310f, 1.5080f, 
                               1.8850f, 2.2619f, 2.6389f, 3.0159f, 3.3929f,
                               3.7699f, 4.1469f, 4.5239f, 4.9009f, 5.2779f,
                               5.6549f, 6.0319f, 6.4088f, 6.7858f, 7.1628f};
    for (int i = 0; i < (int)(sizeof(theta_el_rad) / sizeof(float)); i++)
    {
        i_abc_actual_Ampere.a = phase_current[0][i] + HCI_abc.a;
        i_abc_actual_Ampere.b = phase_current[1][i] + HCI_abc.b;
        i_abc_actual_Ampere.c = phase_current[2][i] + HCI_abc.c;
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[0][i], i_abc_actual_Ampere.a);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[1][i], i_abc_actual_Ampere.b);
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[2][i], i_abc_actual_Ampere.c);
        uz_3ph_dq_t HCI_dq = uz_HarmonicCurrentInjection_sample(instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad[i]);
        HCI_abc = uz_transformation_3ph_dq_to_abc(HCI_dq, theta_el_rad[i]);
        if (i == 10)
        {
            float omega_el_rad_per_sec = 30.0f * 2.0f * UZ_PIf;
            uz_HarmonicCurrentInjection_set_filters_abc(instance, omega_el_rad_per_sec);
        }
    }
}

void test_uz_HarmonicCurrentInjection_set_filters_dq(void){
    config.order_harmonic = 7.0f;
    config.selection = dq_to_dqn;
    uz_HarmonicCurrentInjection_t* instance = uz_HarmonicCurrentInjection_init(config);
    uz_3ph_abc_t i_abc_actual_Ampere = { 0 };
    uz_3ph_dq_t i_ref_harmonic_Ampere = { 0 };
    uz_3ph_abc_t HCI_abc = { 0 }; 
    float omega_el_rad_per_sec = 377.0f;
    float V_dc_volts = 48.0f;
    float phase_current[3][20] = { 
        { 0.5000f, 1.4025f, 3.6906f, 4.4927f, 4.7772f, 
          5.1598f, 3.3565f, 2.8737f, 0.3080f,-1.1498f,
         -2.7844f,-4.5861f,-4.4271f,-5.3957f,-3.8572f,
         -3.0934f,-1.3371f, 0.9454f, 1.9439f, 4.3486f}, 
        {-4.5801f,-4.5187f,-5.3675f,-3.6579f,-3.0523f,
         -0.9873f, 1.0276f, 2.1983f, 4.4756f, 4.3436f,
          5.3072f, 4.3168f, 3.1326f, 1.9942f,-0.6880f,
         -1.5446f,-3.9509f,-4.4350f,-4.9259f,-4.9887f},
        { 4.0801f, 3.1162f, 1.6768f,-0.8348f,-1.7249f, 
         -4.1725f,-4.3841f,-5.0719f,-4.7836f,-3.1939f,
         -2.5228f, 0.2693f, 1.2945f, 3.4016f, 4.5452f,
          4.6380f, 5.2880f, 3.4897f, 2.9820f, 0.6401f}
        };
    float HCI_phase_expected[3][20] = {
        { 0.5000f, 1.3775f, 3.5735f, 4.7597f, 4.4189f,
          5.5176f, 3.0921f, 2.9597f, 0.4539f,-1.5186f,
         -2.2626f,-5.1453f,-3.9811f,-5.6001f,-3.9680f,
         -2.6634f,-2.0005f, 1.6878f, 1.3098f, 4.7032f},
        {-4.5801f,-4.2897f,-5.5353f,-3.6277f,-2.9107f,
         -1.2945f, 1.4441f, 1.7741f, 4.7969f, 4.2186f,
          5.1728f, 4.7131f, 2.5580f, 2.6148f,-1.1964f,
         -1.2913f,-3.8605f,-4.8759f,-4.2265f,-5.7857f},
        { 4.0801f, 3.1162f, 1.6768f,-0.8348f,-1.7249f,
         -4.1725f,-4.3841f,-5.0719f,-4.7836f,-3.1939f,
         -2.5228f, 0.2693f, 1.2945f, 3.4016f, 4.5452f,
          4.6380f, 5.2880f, 3.4897f, 2.9820f, 0.6401f}
    };
    float theta_el_rad[20] = { 0.0000f, 0.3770f, 0.7540f, 1.1310f, 1.5080f, 
                               1.8850f, 2.2619f, 2.6389f, 3.0159f, 3.3929f,
                               3.7699f, 4.1469f, 4.5239f, 4.9009f, 5.2779f,
                               5.6549f, 6.0319f, 6.4088f, 6.7858f, 7.1628f};
    for (int i = 0; i < (int)(sizeof(theta_el_rad) / sizeof(float)); i++)
    {
        i_abc_actual_Ampere.a = phase_current[0][i] + HCI_abc.a;
        i_abc_actual_Ampere.b = phase_current[1][i] + HCI_abc.b;
        i_abc_actual_Ampere.c = phase_current[2][i] + HCI_abc.c;
        TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[0][i], i_abc_actual_Ampere.a);
       // TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[1][i], i_abc_actual_Ampere.b);
       // TEST_ASSERT_FLOAT_WITHIN(1e-03f, HCI_phase_expected[2][i], i_abc_actual_Ampere.c);
        uz_3ph_dq_t HCI_dq = uz_HarmonicCurrentInjection_sample(instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad[i]);
        HCI_abc = uz_transformation_3ph_dq_to_abc(HCI_dq, theta_el_rad[i]);
        if (i == 10)
        {
            float omega_el_rad_per_sec = 30.0f * 2.0f * UZ_PIf;
            uz_HarmonicCurrentInjection_set_filters_dq(instance, omega_el_rad_per_sec);
        }
    }
}

// void tearDown(void)
// {
// }

// void test_uz_HarmonicCurrentInjection_NeedToImplement(void)
// {
//     TEST_IGNORE_MESSAGE("Need to Implement uz_HarmonicCurrentInjection");
// }

#endif // TEST
