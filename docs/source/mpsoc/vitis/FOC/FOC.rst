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

FOC config
^^^^^^^^^^

In order to configure the FOC, multiple steps have to be made. The following config structs have to be initialized.

.. doxygenstruct:: uz_FOC_config
  :members:
    
Example
"""""""
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz_FOC.h"
  int main(void) {
     uz_FOC_config config_FOC = {
        .iq_ref_Ampere = 2.0f,
        .id_ref_Ampere = 3.0f,
        .n_ref_rpm = 1000.0f,
        .FOC_Select = 1U,
        .polePairs = 4.0f
     };
  }

Description
"""""""""""
    
With this config struct one can customize the FOC. 
Reference speed ``n_ref_rpm`` can be left at 0.0f, if only the CurrentControl is used.
If the SpeedControl is used, ``iq_ref_Ampere`` will be overwritten.

PI-Controller config
^^^^^^^^^^^^^^^^^^^^

Three different :ref:`config structs <uz_piController_config>` for the :ref:`PI-Controller <uz_piController>` have to be initialized. 

Example
"""""""
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz/uz_piController/uz_piController.h"
  int main(void) {
     uz_PI_Controller_config config_id = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00002f,
        .upper_limit = 10.0f,
        .lower_limit = -10.0f
     };
     uz_PI_Controller_config config_iq = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00002f,
        .upper_limit = 10.0f,
        .lower_limit = -10.0f
     };
     uz_PI_Controller_config config_n = {
        .Kp = 5.0f,
        .Ki = 5.0f,
        .samplingTime_sec = 0.00002f,
        .upper_limit = 20.0f,
        .lower_limit = -20.0f
     };
     //If FOC_Select == 1(CurrentControl)
     uz_PI_Controller_config config_n = {0};
  }

Description
"""""""""""
One of the three PI-Controller config structs is for the id-Controller, one for the iq-Controller and the last one for the n-Controller. 
If the CurrentControl is selected, the n-Controller config struct can be initialized with 0.

Linear decoupling config
^^^^^^^^^^^^^^^^^^^^^^^^

Lastly, the linear decoupling config struct has to be initialized.

Example
"""""""

.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz_linear_decoupling.h"
  int main(void) {
     uz_lin_decoupling_config config_lin_Decoup = {
     .Ld_Henry = 0.0001f, 
     .Lq_Henry = 0.0002f, 
     .Psi_PM_Vs = 0.008f};
  }

Description
"""""""""""

For reference look up :ref:`uz_lineardecoupling`. If all values are set to 0.0f, the linear decoupling is deactivated.

.. _uz_FOC_init:

Init function
-------------

.. doxygentypedef:: uz_FOC
.. doxygenfunction:: uz_FOC_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a FOC instance. Config according to :ref:`configuration section<uz_FOC_config>`

  #include "uz/uz_FOC/uz_FOC.h"
  int main(void) {
     uz_FOC* FOC_instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
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