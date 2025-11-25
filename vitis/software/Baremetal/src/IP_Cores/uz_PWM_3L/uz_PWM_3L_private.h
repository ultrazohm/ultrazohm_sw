#pragma once

struct PWM_3L{
    uint32_t base_address;
    uint32_t carrier_freq;
    float phase_shift;
    float u1;
    float switchStates [3][4]; //[phase][switch] (is float because of Javascope
};


