#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
#include "../IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../globalData.h"


// ADC defines
#define PHASE_CURRENT_CONV	16.75f
#define DC_VOLT_CONV		140.27f

// Function declarations
void uz_ADC_currents(DS_Data* Data);
void uz_ADC_voltages(DS_Data* Data);
void uz_TempCard_Measurement(DS_Data* Data);
void uz_PWM_duty_freq_detection(DS_Data* Data);
void uz_transformations(uz_9ph_abc_t abc_in, uz_9ph_dq_t* full_dq, uz_3ph_dq_t* dq, uz_3ph_alphabeta_t* XY1, uz_3ph_alphabeta_t* XY2, uz_3ph_alphabeta_t* XY3, float theta);
void uz_duty_cycles_to_rasv(DS_Data* Data, struct uz_DutyCycle_3x3ph_t duty_cycle);
void uz_set_DC_zero(DS_Data* Data);
