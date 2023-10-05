==============================
VSD Open-phase-fault detection
==============================

General
=======

This module provides functions for open phase fault (OPF) detection based on Vector Space Decompositon (VSD) for an asymmetric nine-phase machine.
The fault detection is based on nine fault indices, one for each phase of the machine.
The fault indices are calculated based on the measured VSD-currents with the following equations.
More details about the working principal can be found in :ref:`uz_VSD_6ph_FD_control`.

Processing
==========

The equations for the bare fault indices are listed here:

.. math::

	R_\textrm{a1} &=-\frac{i_\textrm{X1} + i_\textrm{X2} + i_\textrm{X3} + i_\textrm{Z}}{i_\alpha}\\
  R_\textrm{b1} &=-\frac{i_\textrm{X1} -0,5\cdot i_\textrm{X2} -0,8860\cdot i_\textrm{Y2} - 0,5\cdot i_\textrm{X3} + 0,8860\cdot i_\textrm{Y3} + i_\textrm{Z}}{-0,5\cdot i_\alpha+0,8860\cdot i_\beta}\\
  R_\textrm{c1} &=-\frac{i_\textrm{X1} -0,5\cdot i_\textrm{X2} +0,8860\cdot i_\textrm{Y2} - 0,5\cdot i_\textrm{X3} - 0,8860\cdot i_\textrm{Y3} + i_\textrm{Z}}{-0,5\cdot i_\alpha-0,8860\cdot i_\beta} \\
  R_\textrm{a2} &=-\frac{0.5\cdot i_\textrm{X1}+0.8660\cdot i_\textrm{Y1}-0.1736\cdot i_\textrm{X2}+0.9848\cdot i_\textrm{Y2}-0.7660\cdot  i_\textrm{X3}+0.6428\cdot i_\textrm{Y3}-i_\textrm{Z}}{0.9397\cdot i_\alpha + 0.3420\cdot i_\beta}\\
  R_\textrm{b2}&=-\frac{0.5\cdot i_\textrm{X1}+0.8660\cdot i_\textrm{Y1}+0.9397\cdot i_\textrm{X2}-0.3420\cdot i_\textrm{Y2}-0.1736i_\textrm{X3}-0.9848\cdot i_\textrm{Y3}- i_\textrm{Z}}{-0.7660\cdot i_\alpha+ 0.6428\cdot i_\beta}\\
  R_\textrm{c2}&=-\frac{0.5\cdot i_\textrm{X1}+0.8660\cdot i_\textrm{Y1}-0.7660\cdot i_\textrm{X2}-0.6428\cdot i_\textrm{Y2}+0.9397\cdot i_\textrm{X3}+0.3420\cdot i_\textrm{Y3}-i_\textrm{Z}}{-0.1736\cdot i_\alpha-0.9848\cdot i_\beta}\\
  R_\textrm{a3}&=-\frac{-0.5\cdot i_\textrm{X1}+0.8660\cdot i_\textrm{Y1}-0.9397\cdot i_\textrm{X2}-0.3420\cdot i_\textrm{Y2}+0.1736\cdot i_\textrm{X3}-0.9848\cdot i_\textrm{Y3}+i_\textrm{Z}}{0.7660\cdot i_\alpha+0.6428\cdot i_\beta}\\
  R_\textrm{b3}&=-\frac{-0.5\cdot i_\textrm{X1}+0.8660\cdot i_\textrm{Y1}+0.1736\cdot i_\textrm{X2}+   0.9848\cdot i_\textrm{Y2}+0.7660\cdot i_\textrm{X3}+0.6428 \cdot i_\textrm{Y3} + i_\textrm{Z}}{-0.9397\cdot i_\alpha +0.3420\cdot i_\beta}\\
  R_\textrm{c3}&=-\frac{-0.5\cdot i_\textrm{X1}+0.8660\cdot i_\textrm{Y1}+ 0.7660\cdot i_\textrm{X2}-0.6428\cdot i_\textrm{Y2}-0.9397\cdot i_\textrm{X3}+0.3420\cdot i_\textrm{Y3} + i_\textrm{Z} }{0.1736\cdot i_\alpha-0.9848\cdot i_\beta}

After the calculation of the indices, filtering, thresholding and hysteresis are applied to each of them.
At first, a Hystereseband is applied, which eliminates mainly large values that result of divisions by zero or very small :math:`i_\alpha` or :math:`i_\beta`.
Afterwards, a sliding average filter is applied.
The filterlength depends on the electric rotor speed and is adapted online.
To create a boolean value from the result, a threshold is used to determine the detection of an open phase fault.

.. figure:: filter_indices.jpg

    Signal flow of indices


Function references
===================

.. doxygentypedef:: uz_VSD_9ph_FD_t

.. doxygenstruct:: uz_VSD_9ph_FD_config
  :members:

.. doxygenfunction:: uz_VSD_9ph_FD_init

.. doxygenfunction:: uz_vsd_opf_9ph_faultdetection_step

.. doxygenfunction:: uz_vsd_opf_9ph_get_n_fault


Code example
============

.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault detection (init_fault_detection.h)

  #include "../uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_FD.h"
  #include "../uz/uz_global_configuration.h"
  #include "../uz/uz_movingAverageFilter/uz_movingAverageFilter.h"

  uz_VSD_9ph_FD_t* init_uz_VSD_9ph_FD(void);

.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault detection (init_fault_detection.c)

  #include "../include/init_fault_control.h"

  // config for moving average filter
  const struct uz_movingAverageFilter_config movAvF_config = {
    .filterLength = 1U
  };

  #define ARRAYSIZE 100

  // circular Buffers for 9 moving average filters
  float dataR1 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R1 = {
  .length = ARRAYSIZE,
  .data = &dataR1[0]
  };
  float dataR2 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R2 = {
  .length = ARRAYSIZE,
  .data = &dataR2[0]
  };
  float dataR3 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R3 = {
  .length = ARRAYSIZE,
  .data = &dataR3[0]
  };
  float dataR4 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R4 = {
  .length = ARRAYSIZE,
  .data = &dataR4[0]
  };
  float dataR5 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R5 = {
  .length = ARRAYSIZE,
  .data = &dataR5[0]
  };
  float dataR6 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R6 = {
  .length = ARRAYSIZE,
  .data = &dataR6[0]
  };
  float dataR7 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R7 = {
  .length = ARRAYSIZE,
  .data = &dataR7[0]
  };
  float dataR8 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R8 = {
  .length = ARRAYSIZE,
  .data = &dataR8[0]
  };
  float dataR9 [ARRAYSIZE] = {0};
  uz_array_float_t circularBuffer_R9 = {
  .length = ARRAYSIZE,
  .data = &dataR9[0]
  };


  uz_VSD_9ph_FD_t* init_uz_VSD_9ph_FD(void){
    uz_movingAverageFilter_t* movAvFilter_R1 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R1);
    uz_movingAverageFilter_t* movAvFilter_R2 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R2);
    uz_movingAverageFilter_t* movAvFilter_R3 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R3);
    uz_movingAverageFilter_t* movAvFilter_R4 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R4);
    uz_movingAverageFilter_t* movAvFilter_R5 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R5);
    uz_movingAverageFilter_t* movAvFilter_R6 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R6);
    uz_movingAverageFilter_t* movAvFilter_R7 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R7);
    uz_movingAverageFilter_t* movAvFilter_R8 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R8);
    uz_movingAverageFilter_t* movAvFilter_R9 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R9);
    struct uz_VSD_9ph_FD_config fault_detection_cfg = {
      .upperlimit = 1.1f,
      .lowerlimit = 0.9f,
      .threshold = 0.5f,
      .mov_average_filter_length = ARRAYSIZE,
      .sample_frequency_Hz = UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE,
      .percent_of_el_period = 0.5f,
      .movingAverageFilter_R1 = movAvFilter_R1,
      .movingAverageFilter_R2 = movAvFilter_R2,
      .movingAverageFilter_R3 = movAvFilter_R3,
      .movingAverageFilter_R4 = movAvFilter_R4,
      .movingAverageFilter_R5 = movAvFilter_R5,
      .movingAverageFilter_R6 = movAvFilter_R6,
      .movingAverageFilter_R7 = movAvFilter_R7,
      .movingAverageFilter_R8 = movAvFilter_R8,
      .movingAverageFilter_R9 = movAvFilter_R9};
    return uz_VSD_9ph_FD_init(fault_detection_cfg);
  }

.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault detection (main.c)

  #include "/include/init_fault_control.h"
  int main(void){
  //..
      Global_Data.objects.fault_detection = init_uz_VSD_9ph_FD();

	
.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault detection (isr.c)

  #include "../uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_FD.h"
  uz_9ph_abc_t fault_single_indices  = {0};
  int fault_n_OPF = 0;
  //..
    fault_single_indices = uz_vsd_opf_9ph_faultdetection_step(Global_Data.objects.fault_detection, Global_Data.av.currents_alphabeta, Global_Data.av.omega_el);
	  fault_n_OPF = uz_vsd_opf_9ph_get_n_fault(fault_single_indices);
	