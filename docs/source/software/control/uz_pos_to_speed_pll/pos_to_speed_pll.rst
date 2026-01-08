.. _pos_to_speed_pll:

=====================
Position to Speed PLL
=====================

.. tip::
  Huge thanks to the Department of Power Electronics and Electrical Drives, Paderborn University for providing their implementation as a basis for this software module. 
  The respective literature reference is listed at the bottom of this page.

Description
===========

The Position to Speed PLL calculates a rotational speed from a rotor position. 
The calculation is based on a phase-locked loop (PLL). 
Rotor position sensors often only provide the position signal, but information about the mechanical and electrical rotational speed is also required for control purposes. 
This software module offers a possible solution for this task. 
Below, :ref:`simulink_source_pos_to_speed_pll` shows a schematic diagram of the software module with its inputs and outputs.

.. _simulink_source_pos_to_speed_pll:

.. figure:: pos_to_speed_pll.png
   :width: 100%
   :align: center

   Simulink source of ``uz_pos_to_speed_pll``


Interfaces
==========

Table :ref:`pos_to_speed_pll_interface_table` lists all input and output variables.

.. _pos_to_speed_pll_interface_table:

.. csv-table:: Interfaces of uz_pos_to_speed_pll module
   :file: uz_pos_to_speed_pll_interfaces.csv
   :widths: 50 80 80 50 200
   :header-rows: 1

It is important to note that the input signal for the position, ``position_mech_SI``, must be in **rad** and must be in the range :math:`0...2\pi`. 
Furthermore, the ``pole_pairs`` and ``sampling_time_seconds`` must not be :math:`0`.

Example configuration
=====================

Only a few parameters are necessary to configure the module.
The ``machine_polepairs`` parameter must be set according to the electrical machine for which the rotational speed is to be calculated. 
The sampling time with which the software module is called must be entered for ``sampling_time_in_seconds``.
For a sampling frequency of 10 kHz, e.g., this is 0.0001 seconds.
The parameters ``kp_pll`` and ``ki_pll`` have more degrees of freedom and must be adjusted according to the application. 
They can be calculated as follows:

.. math::
  k_{p,pll} &= 2 \cdot d \cdot 2\pi \cdot f_n,\\
  k_{i,pll} &= (2\pi \cdot f_n)^2,

where :math:`d` is the damping factor and :math:`f_n` is the nominal closed-loop frequency in Hz of the PLL.
Useful starting values are :math:`d=1` and :math:`f_n=50`, resulting in :math:`k_{p,pll}=628.3185` and :math:`k_{i,pll}=98696`. 
If the stability or dynamics of the PLL are insufficient, the user must adjust the values to the requirements of the application. 
The following steps are necessary to use the software module in the ``ultrazohm_sw`` framework:

1. Allow at least one instance of the uz_pos_to_speed_pll software module in ``uz_global_configuration.h``:

.. code-block:: c
  :linenos:
  :caption: uz_global_configuration.h

  // Configuration defines for the number of used instance
  ..
  #define UZ_POS_TO_SPEED_PLL_MAX_INSTANCES               1U
  ..
  #endif

2. Create a header file ``pll_init.h`` in the ``include`` folder:

.. code-block:: c
  :linenos:
  :caption: pll_init.h

  #pragma once
  #include "../uz/uz_pos_to_speed_pll/uz_pos_to_speed_pll.h"

  uz_pos_to_speed_pll_t* pll_0_init(void);

3. Create a source file ``pll_init.c`` in the ``sw`` folder:

.. code-block:: c
  :linenos:
  :caption: pll_init.c

  #include "../include/pll_init.h"

  struct uz_pos_to_speed_pll_config_t pll_config = {
		.machine_polepairs=2.0f,
		.kp_pll=628.3185f,
		.ki_pll=98696.0f,
		.sampling_time_in_seconds=0.0001f
  };

  uz_pos_to_speed_pll_t* pll_0_init(void) {
	  return(uz_pos_to_speed_pll_init(pll_config));
  }

4. Add the following code lines to ``globalData.h``:

.. code-block:: c
  :linenos:
  :caption: globalData.h

  #include "uz/uz_pos_to_speed_pll/uz_pos_to_speed_pll.h"

  typedef struct{
   ..
   uz_pos_to_speed_pll_t* pll_0;
   ..
  }object_pointers_t;

5. Initialize the instance in ``main.c``:
   
.. code-block:: c
  :linenos:
  :caption: main.c

  case init_software:
    ..
    Global_Data.objects.pll_0 = pll_0_init();
    ..
    initialization_chain = init_ip_cores;
   break;

6. Use the instance in ``isr.c`` by calling the step-function and assigning an existing mechanical rotor position signal to the module. 
Be reminded that the range of the position signal has to be within :math:`0...2\pi`. 
Afterwards read out the electrical and the mechanical speed and assign it to a variable of your choice for further usage:

.. code-block:: c
  :linenos:
  :caption: isr.c
    
    ..
    uz_pos_to_speed_pll_step(Global_Data.objects.pll_0, encoder_mechanical_rotor_position_signal);
    Global_Data.av.mechanicalRotorSpeed = uz_pos_to_speed_pll_get_omega_mech_si(Global_Data.objects.pll_0);
    Global_Data.av.electricalRotorSpeed = uz_pos_to_speed_pll_get_omega_el_si(Global_Data.objects.pll_0);
    ..

The figure below shows the resulting output mechanical rotational speed in rad/s (green) for an artificial input rotational position signal (blue) at an input step from 1 Hz to 10 Hz:

.. _pll_test:

.. figure:: pll_test.png
   :width: 100%
   :align: center

   Result of a test scenario with an artificial input signal to the ``uz_post_to_speed_pll``

References
==========


Driver references
-----------------

.. doxygenstruct:: uz_pos_to_speed_pll_config_t
  :members:

.. doxygenstruct:: uz_pos_to_speed_pll_t
  :members:  

.. doxygentypedef:: uz_pos_to_speed_pll_t

.. doxygenfunction:: uz_pos_to_speed_pll_init

.. doxygenfunction:: uz_pos_to_speed_pll_set_config

.. doxygenfunction:: uz_pos_to_speed_pll_step

.. doxygenfunction:: uz_pos_to_speed_pll_get_omega_mech_si

.. doxygenfunction:: uz_pos_to_speed_pll_get_omega_el_si


Literature References
---------------------
* :download:`Technical Report on Reinforcement Learning Control on the Lucas-Nulle Inverted Pendulum <https://arxiv.org/pdf/2412.02264>`