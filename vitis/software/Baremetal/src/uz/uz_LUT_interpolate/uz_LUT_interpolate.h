#ifndef UZ_LUT_INTERPOLATE_H
#define UZ_LUT_INTERPOLATE_H



/**
 * @brief function for linear interpolation in an evenly distributed array
 * @param x_min minimum value of x grid
 * @param x_max maximum value of x grid
 * @param xN number of equally distributed x values
 * @param *y pointer to array of corresponding y values
 * @param x x value for interpolation
 */
float uz_interp1_uniform(float x_min, float x_max, int xN, const float *y, float x);



/**
 * @brief function for linear interpolation in an evenly distributed 2D-grid
 * @param x_min minimum value of x grid
 * @param x_max maximum value of x grid
 * @param xN number of equally distributed x values
 * @param x_min minimum value of y grid
 * @param x_max maximum value of y grid
 * @param yN number of equally distributed y values
 * @param z pointer to array of corresponding z values
 * @param x x value for interpolation
 * @param y y value for interpolation
 */
float uz_interp2_uniform(float x_min, float x_max, int Nx, float y_min, float y_max, int Ny, const float z[Ny][Nx], float x, float y);




#endif // UZ_LUT_INTERPOLATE_H
