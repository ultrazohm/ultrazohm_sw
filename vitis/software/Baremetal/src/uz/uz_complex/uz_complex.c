#include "uz_complex.h"
#include "../uz_HAL.h"


uz_complex_cartesian_t uz_complex_multiplication(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2)
{
    uz_complex_cartesian_t out;
    out.real = arg1.real*arg2.real - arg1.imaginary*arg2.imaginary;
    out.imaginary = arg1.real*arg2.imaginary + arg1.imaginary*arg2.real;
    return out;
}

uz_complex_cartesian_t uz_complex_addition(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2)
{
    uz_complex_cartesian_t out;
    out.real = arg1.real + arg2.real;
    out.imaginary = arg1.imaginary + arg2.imaginary;
    return out;  
}

uz_complex_cartesian_t uz_complex_subtraction(uz_complex_cartesian_t subtrahend, uz_complex_cartesian_t minuend)
{
    uz_complex_cartesian_t out;
    out.real = subtrahend.real - minuend.real;
    out.imaginary = subtrahend.imaginary - minuend.imaginary;
    return out; 
}

uz_complex_cartesian_t uz_complex_division(uz_complex_cartesian_t dividend, uz_complex_cartesian_t divisor)
{
    uz_assert(divisor.real!=0.0f && divisor.imaginary!=0.0f);
    uz_complex_cartesian_t out;
    out.real = (dividend.real*divisor.real + dividend.imaginary*divisor.imaginary)/(powf(divisor.real,2.0f) + powf(divisor.imaginary,2.0f));
    out.imaginary = (dividend.imaginary*divisor.real - dividend.real*divisor.imaginary)/(powf(divisor.real,2.0f) + powf(divisor.imaginary,2.0f));
    return out;
}

uz_complex_exponential_t uz_complex_cartesian_to_exponential(uz_complex_cartesian_t in)
{
    uz_complex_exponential_t out;
    out.absolute = sqrtf(powf(in.real,2.0f)+powf(in.imaginary,2.0f));
    out.phase = atan2f(in.imaginary,in.real);
    return out;
}

uz_complex_cartesian_t uz_complex_exponential_to_cartesian(uz_complex_exponential_t in)
{
    uz_complex_cartesian_t out;
    out.real = in.absolute * cosf(in.phase);
    out.imaginary = in.absolute * sinf(in.phase);
    return out;
}