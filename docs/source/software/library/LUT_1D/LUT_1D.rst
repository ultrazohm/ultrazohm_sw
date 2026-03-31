.. _uz_LUT_1D:

======
LUT_1D
======

Description
===========

The ``uz_LUT_1D`` module provides a 1D look-up table with binary search, linear interpolation and value clamping.
It uses the ``uz_array_float_t`` type from the :ref:`uz_array` lib for breakpoints and data storage. 
The breakpoints array must be in ascending order and have the same length as the data array. 
The data array must also be in ascending order. 
This module is PS only.

When the input is below the first breakpoint, the first data value is returned.
When the input is above the last breakpoint, the last data value is returned.
When the input is between two breakpoints, the output is linearly interpolated between the two nearest points.

.. code-block:: c
  :caption: Example to initialize the configuration struct

    //Arrays for LUTs
    static float LUT_breakpoints_array[6] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    static float LUT_data_array[6] = {0.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f};

    //Create uz_arrays
    uz_array_float_t LUT_breakpoints = {
		  .length = UZ_ARRAY_SIZE(LUT_breakpoints_array),
		  .data = &LUT_breakpoints_array[0]
    };
    uz_array_float_t LUT_data = {
		  .length = UZ_ARRAY_SIZE(LUT_data_array),
		  .data = &LUT_data_array[0]
    };

    uz_LUT_1D_t* lut_instance = uz_LUT_1D_init(&LUT_breakpoints, &LUT_data, 6U);
    float input = 2.5f; 
    float output = uz_LUT_1D_get_value(lut_instance, input);



Reference
=========

.. doxygentypedef:: uz_LUT_1D_t

.. doxygenfunction:: uz_LUT_1D_init

.. doxygenfunction:: uz_LUT_1D_get_value