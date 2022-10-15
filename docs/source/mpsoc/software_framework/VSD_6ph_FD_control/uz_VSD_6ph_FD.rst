==============================
VSD Open-phase-fault detection
==============================

This module provides functions for open phase fault (OPF) detection based on Vector-Space-Decompositon (VSD) für an asymmetric six phase machine.
The detection is based on six fault indices, one for each phase of the machine.
The fault indices are calculated based on the measured VSD-currents with the following equations.

.. math::

	{R_{a1}} =-\frac{i_x}{i_\alpha+i_{01}} 

.. math::

	R_{b1} =\frac{i_x}{-i_\alpha+\sqrt3\ i_\beta-\sqrt3\ i_y+2\ i_{01}}\\

.. math::

	R_{c1} =\frac{i_x}{-i_\alpha-\sqrt3\ i_\beta+\sqrt3\ i_y+2\ i_{01}}\\

.. math::

	R_{a2} =\frac{i_x}{i_\alpha+\frac{1}{\sqrt3}\ i_\beta+\frac{1}{\sqrt3}\ i_y+\frac{2}{\sqrt3}\ i_{02}}\\

.. math::

	R_{b2} = \frac{i_x}{i_\alpha-\frac{1}{\sqrt3}\ i_\beta-\frac{1}{\sqrt3}\ i_y-\frac{2}{\sqrt3}\ i_{02}}\\

.. math::

	R_{c2} =-\frac{i_y}{i\beta-i_{02}}\\

The fault indices are in pre-fault operation zero. If there is an error in one phase, the corresponding fault index becomes one.
Because of disturbances extensive filtering of the fault indices is necessary, for example with an hysteresis band filter followed by an moving average filter. [[#DuranGonzalez]_]

The following module contains functions for calculating the fault indices, applying hysteresis band filtering and evaluating the filtered fault indices.
A moving average filter is not included. The obtained results of the evaluated fault indices can be used for an control scheme during OPF.




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

Function for calculating the fault indices from the six VSD-currents of the machine. 


Hysteresis Filter
-----------------

.. doxygenfunction:: uz_vsd_fd_hysteresis_filter


Description
^^^^^^^^^^^

Function for filtering the raw fault indices calculated by ``uz_vsd_opf_6ph_faultdetection`` with a hysteresis band specified by the input values. 


Fault indices evaluation
------------------------

.. doxygenfunction:: uz_vsd_fd_evaluation



Description
^^^^^^^^^^^

Function for evaluating the filtered fault indices with a threshold value, deciding if a fault index indicates an open phase fault or not. 


Example of complete open phase fault detection
----------------------------------------------

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





