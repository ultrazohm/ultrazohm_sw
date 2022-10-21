Reset function
--------------

.. doxygenfunction:: uz_resonantController_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the resonant controller.

  int main(void) {
     uz_resonantController_reset(R_controller_instance);
  }

Description
^^^^^^^^^^^

Resets the Resonant-Controller. The initial condition for the integrator and the output after the reset is 0.0f.