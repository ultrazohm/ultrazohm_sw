.. _uz_CurrentControl:

==============
CurrentControl
==============

Toolbox for a standard CurrentControl with parallel :ref:`PI-Controllers <uz_piController>`, :ref:`linear decoupling <uz_lineardecoupling>` and a :ref:`space vector limitation <uz_spacevectorlimiation>`. 

Setup
=====

.. _uz_CurrentControl_config:

Configuration
-------------

In order to configure the CurrentControl, multiple configuration structs have to be initialized.

.. doxygenenum:: uz_CurrentControl_decoupling_select 

.. doxygenstruct:: uz_CurrentControl_config
  :members: 
   
Example
^^^^^^^
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz/uz_CurrentControl/uz_CurrentControl.h"
  int main(void) {
     struct uz_PMSM_t config_PMSM = {
        .Ld_Henry = 0.0001f,
        .Lq_Henry = 0.0002f, 
        .Psi_PM_Vs = 0.008f
      };//these parameters are only needed if linear decoupling is selected
      struct uz_PI_Controller_config config_id = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00005f,
        .upper_limit = 10.0f,
        .lower_limit = -10.0f
     };
     struct uz_PI_Controller_config config_iq = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00005f,
        .upper_limit = 10.0f,
        .lower_limit = -10.0f
     };
     struct uz_CurrentControl_config config_CurrentControl = {
        .decoupling_select = linear_decoupling,
        .config_PMSM = config_PMSM,
        .config_id = config_id,
        .config_iq = config_iq
     };
  }

Description
^^^^^^^^^^^
    
With these config structs one can customize the CurrentControl and the included :ref:`PI-Controller <uz_piController>` and :ref:`PMSM config <uz_PMSM_config>`. 
It is possible to use the CurrentControl with or without the :ref:`linear decoupling <uz_lineardecoupling>` via the CurrentControl_config member ``decoupling_select``. 
If no decoupling is selected, no variables for the ``struct uz_PMSM_t`` have to be configured and can be left 0.
Each of the two PI-Controller need their own :ref:`config struct <uz_piController_config>`.
One for the id-Controller and the other one for the iq-Controller. 

.. _uz_CurrentControl_init:

Init function
-------------

.. doxygentypedef:: uz_CurrentControl_t
.. doxygenfunction:: uz_CurrentControl_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a CurrentControl instance. ``config_CurrentControl`` according to :ref:`configuration section<uz_CurrentControl_config>`

  int main(void) {
     uz_CurrentControl_t* CurrentControl_instance = uz_CurrentControl_init(config_CurrentControl);
  }

Description
^^^^^^^^^^^

Allocates the memory for the CurrentControl instance and the included PI-Controller instances. 
Furthermore the input values of the configuration structs are asserted. 

.. _uz_CurrentControl_reset:

Reset
-----

.. doxygenfunction:: uz_CurrentControl_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the CurrentControl. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     uz_CurrentControl_reset(CurrentControl_instance);
  }

Description
^^^^^^^^^^^

Resets the CurrentControl and the integrated PI-Controller. The initial condition for the integrator after the reset is 0.0f.

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *