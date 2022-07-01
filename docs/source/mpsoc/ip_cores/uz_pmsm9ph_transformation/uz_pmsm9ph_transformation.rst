.. _uz_pmsm9ph_transformation:

============================================
Ninephase VSD and Park tranformation IP-Core
============================================

- Applies ninephase VSD transformation to input and Park transformation to only alpha and beta values
- Performs also respective inverse transformation
- Input interface is PL-only
- Transformation can only be triggered by a PL signal, but not by the software driver
- Output is supplied to PL-ports as well as AXI
- Inputs have to be fixed point
- The outputs are refreshed at each rising edge of the input ``trigger_new_values``

.. csv-table:: Interface of Transformation IP-Core
   :file: ipCore_tranformation_interfaces.csv
   :widths: 50 40 60 50 60 210
   :header-rows: 1

VSD and Park tranformation
==========================

For the tranformation the values will be put in via the ``x_abc1_ll_pl``, ``x_abc2_ll_pl`` and ``x_abc3_ll_pl``.
The values must be put in as line-to-line values because a transformation towards star values is applied before applying the VSD transformation.
The line-to-line to star value transformation is realized by applying the Clarke transformation to each threephase subset, deviding the amplitudes by :math:`\sqrt{3}` and rotating the pointers by -30° before applying the inverse Clarke tranformation.
Although the naming "x" suggests, any values can be used as input, the intention is to use line-to-line voltages as input.
After the transformation to the stationary reference frame, the Park transformation is applied to the alpha and beta values only, yielding the following output vector:

.. math::

  \begin{bmatrix} X_{d} \\ X_{q} \\ X_{x_1} \\ X_{y_1} \\ X_{x_2} \\ X_{y_2} \\ X_{x_3} \\ X_{y_3} \\ X_{zero} \end{bmatrix}

Note that the min and max values of the output vector are significantly smaller than the ones of the input values and must be taken into account when using the IP-core.
The IP-core uses the following VSD matrix to transform the phase variables to the stationary reference frame: 

.. math::
  
  \begin{bmatrix} C \end{bmatrix}=
    \frac{2}{9}
    \begin{bmatrix}
      cos(1\cdot 0\cdot\frac{\pi}{9}) & cos(1\cdot 6\cdot\frac{\pi}{9}) & cos(1\cdot 12\cdot\frac{\pi}{9}) & cos(1\cdot 1\cdot\frac{\pi}{9}) & cos(1\cdot 7\cdot\frac{\pi}{9}) & cos(1\cdot 13\cdot\frac{\pi}{9}) & cos(1\cdot 2\cdot\frac{\pi}{9}) & cos(1\cdot 8\cdot\frac{\pi}{9}) & cos(1\cdot 14\cdot\frac{\pi}{9}) &\\
      sin(1\cdot 0\cdot\frac{\pi}{9}) & sin(1\cdot 6\cdot\frac{\pi}{9}) & sin(1\cdot 12\cdot\frac{\pi}{9}) & sin(1\cdot 1\cdot\frac{\pi}{9}) & sin(1\cdot 7\cdot\frac{\pi}{9}) & sin(1\cdot 13\cdot\frac{\pi}{9}) & sin(1\cdot 2\cdot\frac{\pi}{9}) & sin(1\cdot 8\cdot\frac{\pi}{9}) & sin(1\cdot 14\cdot\frac{\pi}{9}) \\
      cos(3\cdot 0\cdot\frac{\pi}{9}) & cos(3\cdot 6\cdot\frac{\pi}{9}) & cos(3\cdot 12\cdot\frac{\pi}{9}) & cos(3\cdot 1\cdot\frac{\pi}{9}) & cos(3\cdot 7\cdot\frac{\pi}{9}) & cos(3\cdot 13\cdot\frac{\pi}{9}) & cos(3\cdot 2\cdot\frac{\pi}{9}) & cos(3\cdot 8\cdot\frac{\pi}{9}) & cos(3\cdot 14\cdot\frac{\pi}{9}) \\
      sin(3\cdot 0\cdot\frac{\pi}{9}) & sin(3\cdot 6\cdot\frac{\pi}{9}) & sin(3\cdot 12\cdot\frac{\pi}{9}) & sin(3\cdot 1\cdot\frac{\pi}{9}) & sin(3\cdot 7\cdot\frac{\pi}{9}) & sin(3\cdot 13\cdot\frac{\pi}{9}) & sin(3\cdot 2\cdot\frac{\pi}{9}) & sin(3\cdot 8\cdot\frac{\pi}{9}) & sin(3\cdot 14\cdot\frac{\pi}{9}) \\
      cos(5\cdot 0\cdot\frac{\pi}{9}) & cos(5\cdot 6\cdot\frac{\pi}{9}) & cos(5\cdot 12\cdot\frac{\pi}{9}) & cos(5\cdot 1\cdot\frac{\pi}{9}) & cos(5\cdot 7\cdot\frac{\pi}{9}) & cos(5\cdot 13\cdot\frac{\pi}{9}) & cos(5\cdot 2\cdot\frac{\pi}{9}) & cos(5\cdot 8\cdot\frac{\pi}{9}) & cos(5\cdot 14\cdot\frac{\pi}{9}) \\
      sin(5\cdot 0\cdot\frac{\pi}{9}) & sin(5\cdot 6\cdot\frac{\pi}{9}) & sin(5\cdot 12\cdot\frac{\pi}{9}) & sin(5\cdot 1\cdot\frac{\pi}{9}) & sin(5\cdot 7\cdot\frac{\pi}{9}) & sin(5\cdot 13\cdot\frac{\pi}{9}) & sin(5\cdot 2\cdot\frac{\pi}{9}) & sin(5\cdot 8\cdot\frac{\pi}{9}) & sin(5\cdot 14\cdot\frac{\pi}{9}) \\
      cos(7\cdot 0\cdot\frac{\pi}{9}) & cos(7\cdot 6\cdot\frac{\pi}{9}) & cos(7\cdot 12\cdot\frac{\pi}{9}) & cos(7\cdot 1\cdot\frac{\pi}{9}) & cos(7\cdot 7\cdot\frac{\pi}{9}) & cos(7\cdot 13\cdot\frac{\pi}{9}) & cos(7\cdot 2\cdot\frac{\pi}{9}) & cos(7\cdot 8\cdot\frac{\pi}{9}) & cos(7\cdot 14\cdot\frac{\pi}{9}) \\
      sin(7\cdot 0\cdot\frac{\pi}{9}) & sin(7\cdot 6\cdot\frac{\pi}{9}) & sin(7\cdot 12\cdot\frac{\pi}{9}) & sin(7\cdot 1\cdot\frac{\pi}{9}) & sin(7\cdot 7\cdot\frac{\pi}{9}) & sin(7\cdot 13\cdot\frac{\pi}{9}) & sin(7\cdot 2\cdot\frac{\pi}{9}) & sin(7\cdot 8\cdot\frac{\pi}{9}) & sin(7\cdot 14\cdot\frac{\pi}{9}) \\
      \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} \\
    \end{bmatrix}

Transformation matrix according to [[#Rockhill_gerneral]_][[#Rockhill_ninephase]_].

Inverse VSD and Park tranformation
==================================

The input ``x_in_dq`` is used for the inverse tranformation.
The d and q values are transformed to alpha and beta with the inverse Park transformation.
Afterwards the inverse VSD transformation is applied which yields the phase variables.
The phase variables are output as star values and not line-to-line values!

Vitis
=====

The main usage of the IP-core is in the PL.
Therefore the usage in the PS is only limited to reading out theta electric and the results from the inverse tranformation.

.. doxygentypedef:: uz_pmsm9ph_transformation_t

.. doxygenstruct:: uz_pmsm9ph_config_t

.. doxygenfunction:: uz_pmsm9ph_transformation_init

.. doxygenfunction:: uz_pmsm9ph_transformation_get_currents

.. doxygenfunction:: uz_pmsm9ph_transformation_get_theta_el



Vivado
======

The following setup is used to test the IP-cores's functionality:

.. figure:: vivado_test_setup.jpg

   Test setup for IP-core in Vivado

To test the IP-core, random values have been selected for the inputs (values are the same for all three subsets):

.. csv-table:: Test values for IP-core
   :file: ipCore_tranformation_test_val.csv
   :widths: 50 50 50
   :header-rows: 1

The transformed output values from ``x_out_dq`` are fed back to the input ``x_in_dq``.
Because of the different fixed point datatypes of the port, a special datatype transformation IP-core was created, which is also present as an out-commented subsystem in the Simulink model of the main IP-core.
The values of the inverse transformation are read out in the PS and are similar to the input values, after applying the line-to-line to star conversion to them.
The output values from UZ and Simulink match and are shown in the following table.

.. csv-table:: Test resulsts for IP-core
   :file: ipCore_tranformation_test_result.csv
   :widths: 50 50
   :header-rows: 1

Sources
=======

.. [#Rockhill_gerneral] A. A. Rockhill and T. A. Lipo, "A generalized transformation methodology for polyphase electric machines and networks," 2015 IEEE International Electric Machines & Drives Conference (IEMDC), 2015, pp. 27-34, doi: 10.1109/IEMDC.2015.7409032.
.. [#Rockhill_ninephase] A. A. Rockhill and T. A. Lipo, "A simplified model of a nine phase synchronous machine using vector space decomposition," 2009 IEEE Power Electronics and Machines in Wind Applications, 2009, pp. 1-5, doi: 10.1109/PEMWA.2009.5208335.