==============================
VSD Open-phase-fault detection
==============================

This module provides functions for open phase fault (OPF) detection based on Vector Space Decompositon (VSD) for an asymmetric six phase machine.
Since the VSD transformation can be used for both PMSM and asynchronous machines, this module can be used for both machine types.
The OPF detection can be extended to other stator arrangements, eg. symmetrical six phase machines or 5 and 9 phase machines.
However, this is not included in this module, since the underlying equations for the fault indices have to be adjusted for it according to the stator arrangement.

The open phase fault detection for asymmetric six phase machines is described in detail in [[#DuranGonzalez]_].

The fault detection is based on six fault indices, one for each phase of the machine.
The fault indices are calculated based on the measured VSD-currents with the following equations.
:math:`{R_{1}}, {R_{2}}, {R_{3}}, {R_{4}}, {R_{5}}, {R_{6}}` are the fault indices for the phases 1 to 6 in the order :math:`a_1, b_1, c_1, a_2, b_2, c_2`.
:math:`i_\alpha, i_\beta, i_x, i_y, i_{0^+}, i_{0^-}` are the VSD-currents calculated from the measured phasecurrent with the :ref:`VSD-Transformation <6ph_abc_to_alphabeta>`.

.. _fault_indices:

.. math::

	{R_{1}} =-\frac{i_x}{i_\alpha+i_{0^+}} 

.. math::

	R_{2} =\frac{i_x}{-i_\alpha+\sqrt3\ i_\beta-\sqrt3\ i_y+2\ i_{0^+}}\\

.. math::

	R_{3} =\frac{i_x}{-i_\alpha-\sqrt3\ i_\beta+\sqrt3\ i_y+2\ i_{0^+}}\\

.. math::

	R_{4} =\frac{i_x}{i_\alpha+\frac{1}{\sqrt3}\ i_\beta+\frac{1}{\sqrt3}\ i_y+\frac{2}{\sqrt3}\ i_{0^-}}\\

.. math::

	R_{5} = \frac{i_x}{i_\alpha-\frac{1}{\sqrt3}\ i_\beta-\frac{1}{\sqrt3}\ i_y-\frac{2}{\sqrt3}\ i_{0^-}}\\

.. math::

	R_{6} =-\frac{i_y}{i_\beta-i_{0^+}}\\

The fault indices are in pre-fault operation zero as the torque producing currents are mapped only into the :math:`\alpha\beta`-plane while into the :math:`xy`- and :math:`0^+0^-`-planes only currents because of asymmetries and some harmonics are mapped, which are close to zero, especially if a proper control system is used and if the PMSM contains few harmonic and asymmetric components.
After a phase failure, the fault indices are no longer zero as now significant current components occur in the :math:`xy`- and :math:`0^+0^-`-system as the three subsystems are no longer uncoupled.
The fault index of the faulted phase is on average one.
The remaining fault indices follow different non-zero functions depending on the fault scenario.

By filtering the fault indices, they can be converted so that only the fault indices of the faulted phases are constant one, while all other fault indices are zero.
For the filtering an hysteresis band filter followed by an moving average filter is used.
The hysteresis band filter set the value of a fault index to zero if the value is not in a narrow band around one defined by an upper and lower hysteresis band limit.
The moving average smoothes the fault indices so that short disturbances do not affect the fault detection.
The length of the smoothing intervall is defined as a portion of one electrical period of the phase currents.
The filtered fault indices are evaluated by a threshold value.
A phase detected as faulted if its fault index exceeds this threshold.

After the filtering the fault indices have two possible states and are either 0 (no fault in the corresponding phase) or 1 (fault in the corresponding phase) and can therefore be used for OPF detection.



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


Fault detection module
----------------------

.. doxygentypedef:: uz_VSD_6ph_FD_t

.. doxygenstruct:: uz_VSD_6ph_FD_config
  :members:

.. doxygenfunction:: uz_VSD_6ph_FD_init


Fault detection
---------------

.. doxygenfunction:: uz_vsd_opf_6ph_faultdetection_step


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

    // config for OPF fault detection
    struct uz_VSD_6ph_FD_config OPF_FD_config = {
        .upperlimit = 1.1f,
        .lowerlimit = 0.9f,
        .threshold = 0.4f,
        .mov_average_filter_length = 500,
        .sample_frequency_Hz = 1000,
        .percent_of_el_period = 0.4f,
        .movingAverageFilter_R1 = movAvFilter_R1,
        .movingAverageFilter_R2 = movAvFilter_R2,
        .movingAverageFilter_R3 = movAvFilter_R3,
        .movingAverageFilter_R4 = movAvFilter_R4,
        .movingAverageFilter_R5 = movAvFilter_R5,
        .movingAverageFilter_R6 = movAvFilter_R6,
    };

    // fault detection module
    uz_VSD_6ph_FD_t* OPF_FD = uz_VSD_6ph_FD_init(OPF_FD_config);

    float omega_el_rad_per_sec = 0.0f;
    uz_6ph_abc_t currents_abc = {0};
    uz_6ph_alphabeta_t vsdcurrents = {0};
    uz_6phFD_indices faultindices = {0};

    // open phase fault detection (in ISR) called with sample_frequency_Hz
    while(1){
      // current omega el from measurement
      omega_el_rad_per_sec = 100.0f;
      // current vsd-currents
      vsdcurrents = uz_transformation_asym30deg_6ph_abc_to_alphabeta(currents_i_abc);
      // calculate fault indices
      faultindices = uz_vsd_opf_6ph_faultdetection_step(OPF_FD, vsdcurrents, omega_el_rad_per_sec);
    }

  }




.. [#DuranGonzalez] M. J. Duran, I. Gonzalez-Prieto, N. Rios-Garcia, and F. Barrero, "A Simple, Fast, and Robust Open-Phase Fault Detection Technique for Six-Phase Induction Motor Drives," IEEE Transaction on Power Electronics, vol. 33, no. 1, pp. 547-557, 2018. 





