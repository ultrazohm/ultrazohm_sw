#pragma once

struct PWM_3L{
    uint32_t base_address;
    uint32_t carrier_freq;
    float phase_shift;
    float u1;
    float switchStates [3][4]; //[phase][switch] (is float because of Javascope
    float carrier;
};

typedef struct PWM_3L_GUI_Inputs_t {
    float input_freq;
    float input_duty_cycle;
    float mode;
    float samplePoint;
    float deadTime_ns;
    float minPulseWidth_ns;
} PWM_3L_GUI_Inputs;

