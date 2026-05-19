.. _uz_LUT_1D:

======
LUT_1D
======

Description
===========

The ``uz_LUT_1D`` module provides a 1D look-up table with binary search, linear interpolation and value clamping.
It uses the ``uz_array_float_t`` type from :ref:`uz_array` for breakpoints and data storage. 
The breakpoints array must be **strictly increasing** (no duplicates), have the same length as the data array,
and contain at least two entries.
The data array may take arbitrary values as long as it has the same length as the breakpoints array and at least two entries.

When the input is below the first breakpoint, the first data value is returned.
When the input is above the last breakpoint, the last data value is returned.
When the input is between two breakpoints, the output is linearly interpolated between the two nearest points.

.. code-block:: c
  :caption: Example initialization of the configuration struct

    //Arrays for LUTs
    static float LUT_breakpoints_array[6] = {0.0f, 1.0f, 2.0f,  3.0f,  4.0f,  5.0f};
    static float LUT_data_array[6]        = {0.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f};

    //Create uz_arrays
    uz_array_float_t LUT_breakpoints = {
		  .length = UZ_ARRAY_SIZE(LUT_breakpoints_array),
		  .data = &LUT_breakpoints_array[0]
    };
    uz_array_float_t LUT_data = {
		  .length = UZ_ARRAY_SIZE(LUT_data_array),
		  .data = &LUT_data_array[0]
    };

    uz_LUT_1D_t* lut_instance = uz_LUT_1D_init(&LUT_breakpoints, &LUT_data);
    float input = 2.5f; 
    float output = uz_LUT_1D_get_value(lut_instance, input);

The following plot shows the example LUT defined by ``LUT_breakpoints_array`` and ``LUT_data_array``.

.. tikz:: Example LUT defined by ``LUT_breakpoints_array`` and ``LUT_data_array`` approximating :math:`f(x)` where :math:`x` are the breakpoints. The input :math:`x=2.5` is passed to ``uz_LUT_1D_get_value``, which returns :math:`f(2.5)=12.5`.
  :align: center

  \begin{tikzpicture}
    \begin{axis}[
      width=12cm,
      height=7cm,
      xlabel={LUT\_breakpoints\_array},
      ylabel={LUT\_data\_array},
      xmin=-0.25,
      xmax=5.25,
      ymin=-1,
      ymax=26,
      xtick={0,1,2,3,4,5},
      ytick={0,5,10,15,20,25},
      grid=major,
      enlargelimits=false,
      legend style={draw=none, fill=none, at={(0.02,0.98)}, anchor=north west}
    ]
      \addplot[
        color=blue,
        thick,
        dashed,
        mark=*,
        mark size=2.5pt
      ] coordinates {
        (0,0)
        (1,5)
        (2,10)
        (3,15)
        (4,20)
        (5,25)
      };
            \addplot[
        color=red,
        thick,
        mark=x,
        mark size=4pt
      ] coordinates {
        (2.5,12.5)
      };
      \addlegendentry{LUT support points}
      \addlegendentry{Interpolation point}
    \end{axis}
  \end{tikzpicture}



Reference
=========

.. doxygentypedef:: uz_LUT_1D_t

.. doxygenfunction:: uz_LUT_1D_init

.. doxygenfunction:: uz_LUT_1D_get_value