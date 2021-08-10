.. _uz_piController:

=============
PI-Controller
=============

Toolbox for a standard PI-Controller in parallel form. It's transfer function is:

.. math::

  \frac{Y(s)}{E(s)}=K_p +\frac{K_i}{s}

.. _uz_piController_config:

It has a configurable output limitation with internal clamping to prevent the integrator from rising further if the output limitation is active.
An input port for an external clamping signal is available as well.  

Setup
=====

Configuration
-------------

.. doxygenstruct:: uz_PI_Controller_config
  :members:
    
Example
^^^^^^^
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz_piController.h"
  int main(void) {
     struct uz_PI_Controller_config config = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00002f,
        .upper_limit = 10.0f,
        .lower_limit = -10.0f
     };
  }
    
Description
^^^^^^^^^^^
    
With this config struct one can customize the PI-Controller variables.
It has to be initialized before the :ref:`init-function <uz_piController_init>` is called.
    
.. _uz_piController_init:

Init function
-------------

.. doxygentypedef:: uz_PI_Controller
.. doxygenfunction:: uz_PI_Controller_init


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a PI-Controller instance. Config according to :ref:`configuration section<uz_piController_config>`

  #include "uz/uz_piController/uz_piController.h"
  int main(void) {
     uz_PI_Controller *PI_instance = uz_PI_Controller_init(config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the PI-Controller instance and asserts the input values of the configuration struct. 

Reset
-----

.. doxygenfunction:: uz_PI_Controller_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the PI-Controller output. PI-Instance via :ref:`init-function <uz_piController_init>`

  int main(void) {
     uz_PI_Controller_reset(PI_instance);
  }

Description
^^^^^^^^^^^

Resets the PI-Controller. The initial condition for the integrator after the reset is 0.0f.


Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *