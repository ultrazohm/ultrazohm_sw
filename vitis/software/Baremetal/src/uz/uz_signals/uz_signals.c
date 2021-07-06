#include "uz_signals.h"
#include "../uz_HAL.h"

float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold) {
	uz_assert(upper_threshold > lower_threshold);
    float output=0.0f;
	if ( (input >= lower_threshold) && (input <= upper_threshold) ) {
		output = 0.0f;
	} else if (input > upper_threshold) {
		output = input - upper_threshold;
	} else {
		output = input - lower_threshold;
	}
	return (output);
}

float uz_signals_get_sign_of_value(float input) {
	float sign=0.0f;
	if (input < 0.0f)
		sign = -1.0f;
	else if (input > 0.0f) {
		sign = 1.0f;
	} else {
		sign = 0.0f;
	}
	return (sign);
}
float uz_signals_saturation(float input, float upper_limit, float lower_limit) {
	uz_assert(upper_limit > lower_limit);
	float output=0.0f;
	if (input > upper_limit) {
		output = upper_limit;
	} else if (input < lower_limit) {
		output = lower_limit;
	} else{
		output=input;
	}
	return (output);
}