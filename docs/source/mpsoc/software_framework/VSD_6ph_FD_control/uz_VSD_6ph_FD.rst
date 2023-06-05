==============================
VSD Open-phase-fault detection
==============================

This module provides functions for open phase fault (OPF) detection based on Vector Space Decompositon (VSD) for an asymmetric six phase machine.
The stator of an asymmetric six phase phase machine consists of two three-phase windig sets shifted by :math:`\gamma = \pi/6`.
Since the VSD transformation can be used for both PMSM and asynchronous machines, this module can be used for both machine types.
The OPF detection can be extended to other stator arrangements, eg. symmetrical six phase machines or 5 and 9 phase machines.
However, this is not included in this module, since the underlying equations for the fault indices have to be adjusted for it according to the stator arrangement.

The fault detection is based on six fault indices, one for each phase of the machine.
The fault indices are calculated based on the measured VSD-currents with the following equations.
:math:`{R_{1}}, {R_{2}}, {R_{3}}, {R_{4}}, {R_{5}}, {R_{6}}` are the fault indices for the phases 1 to 6 in the order :math:`a_1, b_1, c_1, a_2, b_2, c_2`.

:math:`i_\alpha, i_\beta, i_x, i_y, i_{01}, i_{02}` are the VSD-currents calculated with the :ref:`VSD-Transformation <6ph_abc_to_alphabeta>`.

.. _fault_indices:

.. math::

	{R_{1}} =-\frac{i_x}{i_\alpha+i_{01}} 

.. math::

	R_{2} =\frac{i_x}{-i_\alpha+\sqrt3\ i_\beta-\sqrt3\ i_y+2\ i_{01}}\\

.. math::

	R_{3} =\frac{i_x}{-i_\alpha-\sqrt3\ i_\beta+\sqrt3\ i_y+2\ i_{01}}\\

.. math::

	R_{4} =\frac{i_x}{i_\alpha+\frac{1}{\sqrt3}\ i_\beta+\frac{1}{\sqrt3}\ i_y+\frac{2}{\sqrt3}\ i_{02}}\\

.. math::

	R_{5} = \frac{i_x}{i_\alpha-\frac{1}{\sqrt3}\ i_\beta-\frac{1}{\sqrt3}\ i_y-\frac{2}{\sqrt3}\ i_{02}}\\

.. math::

	R_{6} =-\frac{i_y}{i_\beta-i_{02}}\\

The fault indices are in pre-fault operation zero. 
After a phase failure, the fault indices are no longer zero.
The fault index of the faulted phase is on average one.
The remaining fault indices follow different non-zero functions depending on the fault scenario.

By filtering the fault indices, they can be converted so that only the fault indices of the faulted phases are constant one, while all other fault indices are zero.
For the filtering an hysteresis band filter followed by an moving average filter is used. 
After the filtering the fault indices have two possible states and are either 0 (no fault in the corresponding phase) or 1 (fault in the corresponding phase) and can therefore be used for OPF detection.

The open phase fault detection is described in detail in [[#DuranGonzalez]_].

The following module contains functions for calculating the fault indices, applying hysteresis band and moving average filtering and evaluating the filtered fault indices.
The obtained results of the evaluated fault indices can be used for an control scheme during OPF.






.. _uz_6phFD_indices:

Fault indices
-------------

.. doxygenstruct:: uz_6phFD_indices
   :members:

Description
^^^^^^^^^^^

Struct for 6 fault indices, each indicating if the corresponding phase of the machine is under open phase fault.


.. _uz_vsd_opf_6ph_faultdetection:


Fault detection
---------------

.. doxygenfunction:: uz_vsd_opf_6ph_faultdetection


Description
^^^^^^^^^^^

Function for using the complete open-phase-fault detection.
This function includes the calculation of the fault indices, filtering with a hysteresis band filter and moving average filter and finally the evaluation of the filtered fault indices.
The individual substeps of this function are available in the following functions ``_uz_vsd_opf_6ph_fault_indices_calculation``, ``_uz_vsd_fd_hysteresis_filter`` and ``_uz_vsd_fd_evaluation``.


.. _uz_vsd_opf_6ph_fault_indices_calculation:


Calculation of the fault indices
--------------------------------

.. doxygenfunction:: uz_vsd_opf_6ph_fault_indices_calculation


Description
^^^^^^^^^^^

Function for calculating the raw fault indices from the six VSD-currents of the machine according to the :ref:`equations <fault_indices>`. 


.. _uz_vsd_fd_hysteresis_filter:

Hysteresis Filter
-----------------

.. doxygenfunction:: uz_vsd_fd_hysteresis_filter


Description
^^^^^^^^^^^

Function for filtering the raw fault indices calculated by ``_uz_vsd_opf_6ph_fault_indices_calculation`` with a hysteresis band specified by the input values. 
The fault indices are set to zero if they are outside the hysteresis band bounded by the upper and lower limit.


.. _uz_vsd_fd_evaluation:

Fault indices evaluation
------------------------

.. doxygenfunction:: uz_vsd_fd_evaluation



Description
^^^^^^^^^^^

Function for evaluating the filtered fault indices with a threshold value, deciding if a fault index indicates an open phase fault or not. 
A open phase fault is detected when a fault index is above the set threshold value.

Example of complete open phase fault detection
----------------------------------------------

.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault detection.

  int main(void) {

    // config for moving average filter
    struct uz_movingAverageFilter_config movAvF_config = {
        .filterLength = 300U
    };

    // moving average filter for 6 phases
    uz_movingAverageFilter_t* movAvFilter_R1;
    uz_movingAverageFilter_t* movAvFilter_R2;
    uz_movingAverageFilter_t* movAvFilter_R3;
    uz_movingAverageFilter_t* movAvFilter_R4;
    uz_movingAverageFilter_t* movAvFilter_R5;
    uz_movingAverageFilter_t* movAvFilter_R6;

    // circular Buffers for 6 moving average filters
    float dataR1 [500] = {0};
    uz_array_float_t circularBuffer_R1 = {
      .length = UZ_ARRAY_SIZE(dataR1),
      .data = &dataR1[0]
    };
    float dataR2 [500] = {0};
    uz_array_float_t circularBuffer_R2 = {
      .length = UZ_ARRAY_SIZE(dataR2),
      .data = &dataR2[0]
    };
    float dataR3 [500] = {0};
    uz_array_float_t circularBuffer_R3 = {
      .length = UZ_ARRAY_SIZE(dataR3),
      .data = &dataR3[0]
    };
    float dataR4 [500] = {0};
    uz_array_float_t circularBuffer_R4 = {
      .length = UZ_ARRAY_SIZE(dataR4),
      .data = &dataR4[0]
    };
    float dataR5 [500] = {0};
    uz_array_float_t circularBuffer_R5 = {
      .length = UZ_ARRAY_SIZE(dataR5),
      .data = &dataR5[0]
    };
    float dataR6 [500] = {0};
    uz_array_float_t circularBuffer_R6 = {
      .length = UZ_ARRAY_SIZE(dataR6),
      .data = &dataR6[0]
    };

    // initialize moving average filter
    movAvFilter_R1 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R1);
    movAvFilter_R2 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R2);
    movAvFilter_R3 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R3);
    movAvFilter_R4 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R4);
    movAvFilter_R5 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R5);
    movAvFilter_R6 =  uz_movingAverageFilter_init(movAvF_config, circularBuffer_R6);

    // initialize fault detection
    float upperlimit = 1.1f;
    float lowerlimit = 0.9f;
    float threshold = 0.4f;
    uint32_t mov_average_filter_length = 500;
    float sample_frequency_Hz = 1000;
    float percent_of_el_period = 0.4f;

    float omega_el_rad_per_sec = 0.0f;
    uz_6ph_abc_t currents_abc = {0};
    uz_6ph_alphabeta_t vsdcurrents = {0};
    uz_6phFD_indices faultindices = {0};

    // open phase fault detection (in ISR) called with sample_frequency_Hz
    while(1){
      // current omega el
      omega_el_rad_per_sec = 100.0f;
      // current vsd-currents
      vsdcurrents = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_abc);
      // calculate fault indices
      faultindices = uz_vsd_opf_6ph_faultdetection(vsdcurrents, upperlimit, lowerlimit, threshold, mov_average_filter_length, sample_frequency_Hz, percent_of_el_period, omega_el_rad_per_sec, movAvFilter_R1, movAvFilter_R2, movAvFilter_R3, movAvFilter_R4, movAvFilter_R5, movAvFilter_R6 );
    }

  }


Example of using the individual functions for open phase fault detection
------------------------------------------------------------------------

.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault detection.

  int main(void) {

    uz_6ph_alphabeta_t m_6ph_alphabeta_currents;    // measured vsd-currents

    uz_6phFD_indices R_indices = {0};            // fault indices unfiltered values
    uz_6phFD_indices R_indices_Filt = {0};       // fault indices filtered values
    uz_6phFD_indices R_indices_eval = {0};       // fault indices evaluated values

    float upper_limit = 1.1f;
    float lower_limit = 0.9f;
    float threshold = 0.4f;

    // calculate fault indices
    R_indices = uz_vsd_opf_6ph_faultdetection(m_6ph_alphabeta_currents);

    // use hysteresis filer on faultindices
    R_indices_Filt = uz_vsd_fd_hysteresis_filter(R_indices, lower_limit, upper_limit);

    // use further filters e.g. moving average filter or lowpass filter on fault indices (not included in this module)

    // evaluate fault indices with threshold value
    R_indices_eval = uz_fsd_fd_evaluation(R_indices_Filt, threshold);
    
  }

.. [#DuranGonzalez] M. J. Duran, I. Gonzalez-Prieto, N. Rios-Garcia, and F. Barrero, "A Simple, Fast, and Robust Open-Phase Fault Detection Technique for Six-Phase Induction Motor Drives," IEEE Transaction on Power Electronics, vol. 33, no. 1, pp. 547-557, 2018. 





