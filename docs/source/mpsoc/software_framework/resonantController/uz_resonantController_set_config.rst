Set-Config function
-------------------

.. doxygenfunction:: uz_resonantController_set_config

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example to change the config of the resonant controller.

  int main(void) {
    config.lower_limit = -10.0f;
    config.upper_limit = 10.0f;
    config.harmonic_order= 7.0f;

	  uz_resonantController_set_config(R_controller_instance, config);
  }

Description
^^^^^^^^^^^

Function to change the configuration of the resonant controller by passing a new or changed config struct to the controller.