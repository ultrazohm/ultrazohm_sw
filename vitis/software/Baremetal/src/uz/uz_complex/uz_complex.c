#include "uz_complex.h"
#include "../uz_HAL.h"


uz_complex_cartesian_t uz_complex_multiplication(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2)
{
    uz_complex_cartesian_t out;
    out.real = arg1.real*arg2.real - arg1.imag*arg2.imag;
    out.imag = arg1.real*arg2.imag + arg1.imag*arg2.real;
    return out;
}

uz_complex_cartesian_t uz_complex_addition(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2)
{
    uz_complex_cartesian_t out;
    out.real = arg1.real + arg2.real;
    out.imag = arg1.imag + arg2.imag;
    return out;  
}

uz_complex_cartesian_t uz_complex_subtraction(uz_complex_cartesian_t subtrahend, uz_complex_cartesian_t minuend)
{
    uz_complex_cartesian_t out;
    out.real = subtrahend.real - minuend.real;
    out.imag = subtrahend.imag - minuend.imag;
    return out; 
}

uz_complex_cartesian_t uz_complex_division(uz_complex_cartesian_t dividend, uz_complex_cartesian_t divisor)
{
    uz_assert(divisor.real!=0.0f && divisor.imag!=0.0f);
    uz_complex_cartesian_t out;
    out.real = (dividend.real*divisor.real + dividend.imag*divisor.imag)/(divisor.real*divisor.real + divisor.imag*divisor.imag);
    out.imag = (dividend.imag*divisor.real - dividend.real*divisor.imag)/(divisor.real*divisor.real + divisor.imag*divisor.imag);
    return out;
}

uz_complex_polar_t uz_complex_cartesian_to_polar(uz_complex_cartesian_t in)
{
    uz_complex_polar_t out;
    out.abs = sqrtf(in.real*in.real+in.imag*in.imag);
    out.angle = atan2f(in.imag,in.real);
    return out;
}

uz_complex_cartesian_t uz_complex_polar_to_cartesian(uz_complex_polar_t in)
{
    uz_complex_cartesian_t out;
    out.real = in.abs * cosf(in.angle);
    out.imag = in.abs * sinf(in.angle);
    return out;
}