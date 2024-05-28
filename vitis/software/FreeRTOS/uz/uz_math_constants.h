#pragma once

// This header has defines that provide common mathematical constants based on math.h
// However, math.h from gcc only provides these constants as float values
// https://www.gnu.org/software/libc/manual/html_node/Mathematical-Constants.html
// "All values are of type double."
// The makros append the type with a lower case, i.e., UZ_PId is PI as a double while UZ_PIf is PI as a float value

#include <math.h>

#define UZ_PIf (float)M_PI
#define UZ_PId (double)M_PI
