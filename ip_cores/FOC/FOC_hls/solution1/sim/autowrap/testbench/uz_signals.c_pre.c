# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.c" 2
# 18 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.c"
# 1 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h" 1
# 12 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h"
float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold);







float uz_signals_get_sign_of_value(float input);
# 30 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.h"
float uz_signals_saturation(float input, float upper_limit, float lower_limit);
# 19 "C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/FOC/foc/uz_signals.c" 2


float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold) {
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
 if (input < 0.0f){
  sign = -1.0f;
 }
 else if (input > 0.0f) {
  sign = 1.0f;
 } else {
  sign = 0.0f;
 }
 return (sign);
}
float uz_signals_saturation(float input, float upper_limit, float lower_limit) {
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
