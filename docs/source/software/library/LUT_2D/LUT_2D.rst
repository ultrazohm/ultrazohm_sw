.. _uz_LUT_2D:

======
LUT_2D
======

Description
===========

The ``uz_LUT_2D`` module provides a 2D look-up table with binary search, bilinear interpolation and value clamping.
It uses the ``uz_array_float_t`` type from :ref:`uz_array` for both breakpoint vectors and flattened data storage.
The breakpoint arrays for x-axis and y-axis must both be **strictly increasing** (no duplicates) and contain at least two entries.
The flattened data array must be in **row-major order** (x-index changes fastest), and must have
``breakpoints_x.length * breakpoints_y.length`` entries.

Data indexing of the flattened array follows:

.. math::

	 i = y_{idx} \cdot N_x + x_{idx}

where :math:`N_x` is the number of x-axis breakpoints.

If ``input_x`` or ``input_y`` is outside the breakpoint range, it is clamped to the nearest breakpoint.
The return value is then computed with bilinear interpolation.
If either input is ``NaN``, the return value is also ``NaN``.

.. code-block:: c
	:caption: Example initialization of the 2D LUT configuration

		// Axis breakpoints
		static float LUT_breakpoints_x_array[3] = {0.0f, 1.0f, 2.0f};
		static float LUT_breakpoints_y_array[3] = {0.0f, 1.0f, 2.0f};

		// Flattened data in row-major order:
		// row y=0: {0, 1, 2}
		// row y=1: {10, 11, 12}
		// row y=2: {20, 21, 22}
		static float LUT_data_array[9] = {
				0.0f, 1.0f, 2.0f,
				10.0f, 11.0f, 12.0f,
				20.0f, 21.0f, 22.0f
		};

		uz_array_float_t LUT_breakpoints_x = {
				.length = UZ_ARRAY_SIZE(LUT_breakpoints_x_array),
				.data = &LUT_breakpoints_x_array[0]
		};
		uz_array_float_t LUT_breakpoints_y = {
				.length = UZ_ARRAY_SIZE(LUT_breakpoints_y_array),
				.data = &LUT_breakpoints_y_array[0]
		};
		uz_array_float_t LUT_data = {
				.length = UZ_ARRAY_SIZE(LUT_data_array),
				.data = &LUT_data_array[0]
		};

		uz_LUT_2D_t *lut_instance = uz_LUT_2D_init(&LUT_breakpoints_x, &LUT_breakpoints_y, &LUT_data);
		float input_x = 0.5f;
		float input_y = 0.5f;
		float output = uz_LUT_2D_get_value(lut_instance, input_x, input_y); // output = 5.5

The following plot shows the LUT support points and one interpolation point.

.. tikz:: Example 2D LUT support grid for ``LUT_data_array``. The red marker indicates :math:`(x,y)=(0.5,0.5)` with bilinear interpolation result :math:`f(0.5,0.5)=5.5`.
	:align: center

	\begin{tikzpicture}
		\begin{axis}[
			width=11cm,
			height=7cm,
			view={45}{35},
			xlabel={x breakpoints},
			ylabel={y breakpoints},
			zlabel={LUT value},
			grid=major,
			xmin=-0.1, xmax=2.1,
			ymin=-0.1, ymax=2.1,
			zmin=0, zmax=22,
			legend style={draw=none, fill=none, at={(0.02,0.98)}, anchor=north west}
		]
			\addplot3[
				only marks,
				mark=*,
				mark size=2pt,
				color=blue
			] coordinates {
				(0,0,0) (1,0,1) (2,0,2)
				(0,1,10) (1,1,11) (2,1,12)
				(0,2,20) (1,2,21) (2,2,22)
			};
			\addplot3[
				only marks,
				mark=x,
				mark size=4pt,
				color=red,
				thick
			] coordinates {
				(0.5,0.5,5.5)
			};
			\addlegendentry{LUT support points}
			\addlegendentry{Interpolation point}
		\end{axis}
	\end{tikzpicture}


Reference
=========

.. doxygentypedef:: uz_LUT_2D_t

.. doxygenfunction:: uz_LUT_2D_init

.. doxygenfunction:: uz_LUT_2D_get_value