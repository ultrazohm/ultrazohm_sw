.. _uz_Trajectory:

====================
Trajectory Generator
====================

To ensure repeatability of measurements, trajectories are a fundamental tool.
The present software module can generate setvalues based on defined grid points and simplify the operational management of the system. 
Various interpolation methodologies, generation options and start/stop behaviors are available to customize operation control.

.. figure:: Example_Trajectory.png

   ``Example-Trajectory`` Example-Trajectories on the JavaScope - Linear interpolation red . Zero-Order-Hold orange
  
.. _uz_Trajectory_Example:

Setup
=====

Defines
-------

Inside the 'uz_Trajectory.h' is a define , which limits the maximum number of samples.
This must first be set to the desired number of data points before the module can be configured.

.. doxygendefine:: Max_Trajectory_Samples

Struct
------

Struct to store the desired configuration.

.. doxygentypedef:: uz_Trajectory_t

.. _uz_Trajectory_config:

Configuration
-------------

The Trajectory Generator is capable to use different interpolation algorythm between each data point.
At the current time only no interpolation (Zero-Order-Hold) oder linear interpolation is implemented.

.. doxygenenum:: uz_Trajectory_interpolation_selection

Choose the unit of the time base.
The values for the time are durations, so only values greater zero will lead to correct behavior.

.. doxygenenum:: uz_Trajectory_YTicks_selection

Switch to force the generator to repeat the sequence infinite or an specified amount of repeats.
    
.. doxygenenum:: uz_Trajectory_Repeat_selection

Switch to set the output-behavior.
It is possible to hold the last value or a defined zero when the trajectory has stopped or run through.
    
.. doxygenenum:: uz_Trajectory_Stop_Output_selection

Config struct to create the Trajectory Generator
  
.. doxygenstruct:: uz_Trajectory_config
  :members:

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example configuration for the red Trajectory
  
  #include "uz/uz_Trajectory/uz_Trajectory.h"
  int main(void) {
    struct uz_Trajectory_config Trace1_Config = {
      .selection_interpolation = Linear,
      .selection_YAxis = MilliSeconds,
      .StopStyle = HoldLast,
      .RepeatStyle = Repeat_Times,
      .Number_Sample_Points = 11.0f,
      .Sample_Amplitude_Y = {0.0f, 4.0f, 6.0f, 7.0f, 7.5f, 9.0f, 20.0f, 20.0f, -20.0f, 20.0f, 20.0f},
      .Sample_Duration_X = {1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f , 1000.0f},
      .Repeats = 2,
      .Stepwidth_ISR = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor)
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
  :caption: Example function call to init the Trajectory Generator. ``config`` according to :ref:`configuration section<uz_Trajectory_config>`
  
  int main(void) {
    uz_Trajectory_t* Traj_instance = uz_Trajectory_init(Traj_config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the Trajectory Generator instance. 
Furthermore the input values of the configuration struct are asserted. 

Functions
=========

Predefined functions are available for easier operation.
The Functions Start, Stop and Reset can be called directly from the file 'ipc_ARM.c'

Start
-----

.. doxygenfunction:: uz_Trajectory_Start

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for a Trajectory-Start
  
  #include "uz/uz_Trajectory/uz_Trajectory.h"
  void ipc_Control_func(uint32_t msgId, float value, DS_Data *data){
    ...
    case (My_Button_2):
      ultrazohm_state_machine_set_userLED(true);
      uz_Trajectory_Start(Global_Data.objects.TraceGen_1);
      break;
    ...
  }

Stop
----- 

.. doxygenfunction:: uz_Trajectory_Stop

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for a Trajectory-Stop
  
  #include "uz/uz_Trajectory/uz_Trajectory.h"
  void ipc_Control_func(uint32_t msgId, float value, DS_Data *data){
    ...
    case (My_Button_2):
      ultrazohm_state_machine_set_userLED(false);
      uz_Trajectory_Stop(Global_Data.objects.TraceGen_1);
      break;
    ...
  }

Reset
-----
    
.. doxygenfunction:: uz_Trajectory_Reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for a Trajectory-Reset
  
  #include "uz/uz_Trajectory/uz_Trajectory.h"
  void ipc_Control_func(uint32_t msgId, float value, DS_Data *data){
    ...
    case (My_Button_2):
      ultrazohm_state_machine_set_userLED(false);
      uz_Trajectory_Reset(Global_Data.objects.TraceGen_1);
      break;
    ...
  }


The Step-function should be called from the ISR inside the file 'isr.c'.

Step
-----

.. doxygenfunction:: uz_Trajectory_Step

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for a Trajectory-Step
  
  #include "uz/uz_Trajectory/uz_Trajectory.h"
  void ISR_Control(void *data){
    ...
    // Generate Trajectorie
    Global_Data.av.Traj_1 = uz_Trajectory_Step(Global_Data.objects.TraceGen_1);
    ...
  }