Step function
-------------

.. doxygenfunction:: uz_resonantController_step


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to step the resonant controller once

  int main(void) {
    // step once
    output = uz_resonantController_step(R_controller_instance, in_ref_value, in_measured_value, fundamental_fequency);
  }

Description
^^^^^^^^^^^

Steps the resonant-controller. First the input values of the controller for the current time-step have to been set.
With the step-function the new output value is calculated.

.. warning::

   The step-function has to be called with the same sample time as specified in the input-struct of the resonant controller.

