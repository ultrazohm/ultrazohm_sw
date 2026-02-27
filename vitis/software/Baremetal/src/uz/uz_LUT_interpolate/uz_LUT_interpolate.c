
#include "uz_LUT_interpolate.h"
#include <math.h>


float uz_interp1_uniform(float x_min, float x_max, int xN, const float *y, float x)
{
	// x outside of x_min and x_max
    if (x <= x_min) return y[0];
    if (x >= x_max) return y[xN-1];

    // stepwidth of x
    float dx = (x_max - x_min) / (xN - 1);

    // index of left value
    int i = (int)((x - x_min) / dx);

    //
    float t = (x - (x_min + i*dx)) / dx;

    // interpolation
    return y[i] + t * (y[i+1] - y[i]);
}



float uz_interp2_uniform(float x_min, float x_max, int Nx, float y_min, float y_max, int Ny, const float z[Ny][Nx], float x, float y)
{
    // Clamping
    if (x < x_min) x = x_min;
    if (x > x_max) x = x_max;
    if (y < y_min) y = y_min;
    if (y > y_max) y = y_max;

    // Stepwidth
    float dx = (x_max - x_min) / (Nx - 1);
    float dy = (y_max - y_min) / (Ny - 1);

    // index lower left grid position
    int ix = (int)((x - x_min) / dx);
    int iy = (int)((y - y_min) / dy);

    // check limits
    if (ix >= Nx-1) ix = Nx-2;
    if (iy >= Ny-1) iy = Ny-2;

    // relative position in grid
    float tx = (x - (x_min + ix*dx)) / dx;
    float ty = (y - (y_min + iy*dy)) / dy;

    // Bilinear-Interpolation
    float f00 = z[iy][ix];
    float f10 = z[iy][ix+1];
    float f01 = z[iy+1][ix];
    float f11 = z[iy+1][ix+1];

    return (1-tx)*(1-ty)*f00 + tx*(1-ty)*f10 + (1-tx)*ty*f01 + tx*ty*f11;
}


