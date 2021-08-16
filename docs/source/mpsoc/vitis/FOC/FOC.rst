.. _uz_FOC:

============================
Field Oriented Control (FOC)
============================

Toolbox for a standard FOC with parallel :ref:`PI-Controllers <uz_piController>`, :ref:`linear decoupling <uz_lineardecoupling>` and a :ref:`space vector limitation <uz_spacevectorlimiation>`. 

Setup
=====

.. _uz_FOC_config:

Configuration
-------------

In order to configure the FOC, multiple configuration structs have to be initialized.

.. doxygenstruct:: uz_FOC_config
  :members:
    
Example
^^^^^^^
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz/uz_FOC/uz_FOC.h"
  int main(void) {
     struct uz_lin_decoupling_config config_lin_Decoup = {
        .Ld_Henry = 0.0001f,
        .Lq_Henry = 0.0002f, 
        .Psi_PM_Vs = 0.008f
      };
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
     struct uz_FOC_config config_FOC = {
        .config_lin_decoupling = config_lin_Decoup,
        .config_id = config_id,
        .config_iq = config_iq
     };
  }

Description
^^^^^^^^^^^
    
With this config struct one can customize the FOC and the included :ref:`PI-Controller <uz_piController>` and :ref:`linear decoupling <uz_lineardecoupling>`.
Each of the two PI-Controller need their own :ref:`config struct <uz_piController_config>`.
One for the id-Controller and the other one for the iq-Controller. 

.. _uz_FOC_init:

Init function
-------------

.. doxygentypedef:: uz_FOC
.. doxygenfunction:: uz_FOC_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a FOC instance. ``config_FOC`` according to :ref:`configuration section<uz_FOC_config>`

  int main(void) {
     uz_FOC* FOC_instance = uz_FOC_init(config_FOC);
  }

Description
^^^^^^^^^^^

Allocates the memory for the FOC instance and the included PI-Controller instances. 
Furthermore the input values of the configuration structs are asserted. 

.. _uz_FOC_reset:

Reset
-----

.. doxygenfunction:: uz_FOC_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the FOC. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     uz_FOC_reset(FOC_instance);
  }

Description
^^^^^^^^^^^

Resets the FOC and the integrated PI-Controller. The initial condition for the integrator after the reset is 0.0f.

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *