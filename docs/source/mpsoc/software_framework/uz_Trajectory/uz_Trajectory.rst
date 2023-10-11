.. _uz_Trajectory:

====================
Trajectory Generator
====================

Makes some Treajectories!


Setup
=====

.. doxygentypedef:: uz_Trajectory_t

.. _uz_Trajectory_config:

Configuration
-------------

.. doxygenenum:: uz_Trajectory_interpolation_selection

.. doxygenenum:: uz_Trajectory_YTicks_selection
    
.. doxygenenum:: uz_Trajectory_Repeat_selection
    
.. doxygenenum:: uz_Trajectory_Stop_Output_selection
  
.. doxygenstruct:: uz_Trajectory_config
  :members:

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_setpoint/uz_setpoint.h"
  int main(void) {
     struct uz_SetPoint_config SP_config = {
        .config_PMSM.I_max_Ampere = 15.0f,
        .config_PMSM.Ld_Henry = 0.0003f,
        .config_PMSM.Lq_Henry = 0.0003f,
        .config_PMSM.R_ph_Ohm = 0.1f,
        .config_PMSM.polePairs = 4.0f,
        .config_PMSM.Psi_PM_Vs = 0.0075f,
        .control_type = FOC,
        .motor_type = SMPMSM,
        .is_field_weakening_enabled = false,
        .id_ref_Ampere = 0.0f
        .relative_torque_tolerance = 0.001f;
     };
  }

.. _uz_Trajectory_init:

Init function
-------------

.. doxygenfunction:: uz_Trajectory_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init the SpeedController for the SpeedControl. ``config`` according to :ref:`configuration section<uz_SetPoint_config>`
  
  int main(void) {
     uz_Trajectory_t* Traj_instance = uz_Trajectory_init(Traj_config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the SetPoint instance. 
Furthermore the input values of the configuration struct are asserted. 

Functions
=========

.. doxygenfunction:: uz_Trajectory_Start

.. doxygenfunction:: uz_Trajectory_Stop
    
.. doxygenfunction:: uz_Trajectory_Reset

.. doxygenfunction:: uz_Trajectory_Step
