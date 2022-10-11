===================
Resonant-Controller
===================

Toolbox for a standard Resonant-Controller. The ideal transfer function is:

.. math::

  \frac{Y(s)}{E(s)}= K_R \cdot \frac{s}{s^2 + \omega_R^2}

with the resonant frequency :math:`\omega_R`.

The implemented discrete time transfer function is created by impulseinvariant discretization with delay compensation [[#DiscPaper]_] and is:

.. math::
    	G_R(s) = K_R T_{s} \frac{\cos(2\omega_R T_{s}) - z^{-1}\cos(\omega_R T_{s}) }{1-2 z^{-1} \cos(\omega_R T_{s} )+ z^{-2} }


The resonant frequency is specified by :math:`\omega_R = h \cdot \omega_{el}`, with the order h of the harmonic to be controlled and the fundamental frequency :math:`\omega_{el}`.

Resonant-Controller
-------------------

.. doxygenstruct:: uz_resonantController
  :members:

Description
^^^^^^^^^^^

Struct to create a resonant controller instance.


Init function
-------------


.. doxygenfunction:: uz_resonantController_init




Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example create and init a resonant-Controller instance.

  int main(void) {
    uz_resonantController R_controller_instance;
    uz_resonantController_init(&R_controller_instance);
  }


Input struct
------------

.. doxygenstruct:: ExtU_Resonant_Controller_T
  :members:

Description
^^^^^^^^^^^

Struct containing all the inputs of the resonant controller.

Output struct
-------------
.. doxygenstruct:: ExtY_Resonant_Controller_T
  :members:

.. doxygentypedef:: real_T

Description
^^^^^^^^^^^

Struct containing the output of the resonant controller.

 


Step function
-------------

.. doxygenfunction:: uz_resonantController_step

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to step the resonant controller.

  int main(void) {
    R_controller_instance.input.T_sw = 0.0001;
    R_controller_instance.input.VR = 160;
    R_controller_instance.input.h = 2.0;
    R_controller_instance.input.omega_el = omega_el_rad_per_sec;
    R_controller_instance.input.lower_limit = -2.0;
    R_controller_instance.input.upper_limit = 2.0;
    R_controller_instance.input.Klim = 1.0;
    R_controller_instance.input.in_ref = d_current_ref;
    R_controller_instance.input.in_m = d_current_m;

    uz_resonantController_step(&R_controller_instance);

    output = R_controller_instance.output.out;
    
  }

Description
^^^^^^^^^^^

Steps the resonant-controller. First the input values of the controller for the current time-step have to been set.
With the step-function the new output value is calculated.
The step-function has to be called with the same sample time as specified in the input-struct of the resonant controller.

Reset function
--------------

.. doxygenfunction:: uz_resonantController_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the resonant controller.

  int main(void) {
     uz_resonantController_reset(&R_controller_instance);
  }

Description
^^^^^^^^^^^

Resets the Resonant-Controller. The initial condition for the integrator and the output after the reset is 0.0f.
Alternatively, the reset input of the controller can be set to 1 will calling the step-function.



Saturation and Anti-Windup
--------------------------
The output of the controller is limited by the inputvalues ``upper_limit`` and ``lower_limit``.
As an anti-windup strategy teh difference between the unsaturated and by the limits saturated outputvalue is fed back to the input of the controller.
The gain of the anti-windup feedback is given by the inputvalue ``Klim``.
To disable the Anti-Windup strategie the feedback can be set to 0.




Sources
-------

.. [#DiscPaper] G. Yepes, F. D. Freijedo, J. Doval-Gandoy, Ó. López, J. Malvar, and P. Fernandez-Domesaña , "Effects on Discretization Methods on the Performance of Resonant Controllers," IEEE Transactions on Power Electronics, vol. 25, no. 7, pp. 1692-1712, Jul. 2010
