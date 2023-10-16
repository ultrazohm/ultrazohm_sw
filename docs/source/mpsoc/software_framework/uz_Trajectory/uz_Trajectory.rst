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

.. _uz_Trajectory_Samples_define:

Inside the ``uz_Trajectory.h`` is a define , which limits the maximum number of samples.
This must first be set to the desired number of data points before the module can be configured.

.. doxygendefine:: Max_Trajectory_Samples

Struct
------

Struct to store the desired configuration.

.. doxygentypedef:: uz_Trajectory_t

.. _uz_Trajectory_config:

Configuration
-------------

The trajectory generator is able to use different interpolation algorithms between the single data points.
Currently, only no interpolation (zero-order hold) or linear interpolation is implemented.

.. doxygenenum:: uz_Trajectory_interpolation_selection

Select the unit of the time base.
The values for time are durations, so only values greater than zero will result in correct behavior.

.. doxygenenum:: uz_Trajectory_XTicks_selection

Switch to force the generator to repeat the sequence infinitely or a specified number of times.
    
.. doxygenenum:: uz_Trajectory_Repeat_selection

Switch for setting the output behavior.
It is possible to hold the last value or a defined zero point when the trajectory has stopped or passed through.
    
.. doxygenenum:: uz_Trajectory_Stop_Output_selection

Config struct to create the trajectory generator
  
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

Allocates the memory for the trajectory generator instance. 
Furthermore the input values of the configuration struct are asserted. 

Functions
=========

Predefined functions are available for easier operation.
The Start, Stop and Reset functions can be called directly from the ``ipc_ARM.c`` file and should be used to control the trajectory generator.

.. _uz_Trajectory_Start_func:

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

.. _uz_Trajectory_Stop_func:

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
    case (My_Button_3):
      ultrazohm_state_machine_set_userLED(false);
      uz_Trajectory_Stop(Global_Data.objects.TraceGen_1);
      break;
    ...
  }

.. _uz_Trajectory_Reset_func:

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
    case (My_Button_4):
      ultrazohm_state_machine_set_userLED(false);
      uz_Trajectory_Reset(Global_Data.objects.TraceGen_1);
      break;
    ...
  }


The Step-function should be called from the ISR inside the file ``isr.c``.

.. _uz_Trajectory_Step_func:

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

Usecase
=======

To create a trajectory with the generator module and use it in operation, the following steps must be followed:

#. Define the needed trajectory and determine the grid points.
#. Define the Samples inside the :ref:`uz_trajectory.h<uz_Trajectory_Samples_define>`.
#. Write the :ref:`configuration<uz_Trajectory_config>` and create the trajectory generator object.

   * If the complete trajectory is to be played back, the value ``config.Number_Sample_Points`` can be set to the define ``Max_Trajectory_Samples``. Otherwise, the first X grid points can be played with the value ``config.Number_Sample_Points``.  

#. Add the functions :ref:`uz_Trajectory_Start<uz_Trajectory_Start_func>`, :ref:`uz_Trajectory_Stop<uz_Trajectory_Stop_func>` and :ref:`uz_Trajectory_Reset<uz_Trajectory_Reset_func>` to the IPC-Handler.
  
   * It is recommended to define some buttons of the JavaScope to control the trajectory generator and to label the buttons according to the programmed functionality.

#. Add the function :ref:`uz_Trajectory_Step<uz_Trajectory_Step_func>` to the ISR and create a variable for the trajectory inside the `Global_Data`.
#. Add the Output of the trajectory generator to the Global_Data and the JavaScope.
#. Compile the Code and Start the UltraZohm.

After you set up the trajectory generator, you can control the behavior using the JavaScope buttons and play your own trajectories.
To do this, first call the start function.
The generator will start playing the trajectory until the termination condition is reached or continue doing so indefinitely. 
The trajectory can be stopped with the Stop function.
If the trajectory is to be continued, the start function must be called up again.
When the end of the trajectory is reached in repeat mode, the generator locks automatically to prevent an accidental second run.
If a second run is desired, the trajectory must first be unlocked with the Reset function. 

Designed by 
-----------

Robert Zipprich (Universität Kassel / EMA) in 10/2023
