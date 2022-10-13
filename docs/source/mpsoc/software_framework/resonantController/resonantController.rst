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


The resonant frequency is specified by :math:`\omega_R = h \cdot \omega_{el}`, with the order :math:`h` of the harmonic to be controlled and the fundamental frequency :math:`\omega_{el}`.

Resonant-Controller
-------------------

.. doxygenstruct:: uz_resonantController_t


Description
^^^^^^^^^^^

Struct to create a resonant controller instance.


.. doxygenstruct:: uz_resonantController_config
  :members:

Description
^^^^^^^^^^^

Struct for the configuration of the resonant controller


Init function
-------------

.. doxygenfunction:: uz_resonantController_init


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example to create and initialize a resonant-Controller instance.

  int main(void) {
    uz_resonantController_t* R_controller_instance;

    const struct uz_resonantController_config config_R = {
		.T_sw = 0.0001f,
		.VR = 52.5f,
		.h = 2.0f,
		.omega_el = 10.0f,
		.lower_limit = -4.0f,
		.upper_limit = 4.0f,
		.Klim = 10.0f,
		.in_ref = 0.0f,
		.in_m = 0.0f,
		.Reset = 0.0f
    };

    R_controller_instance = uz_resonantController_init(config_R);
  }

Set input function
------------------

.. doxygenfunction:: uz_resonantController_set_input

Description
^^^^^^^^^^^

Function to set the input of the resonant controller before each step.

Get output function
-------------------

.. doxygenfunction:: uz_resonantController_get_output

Description
^^^^^^^^^^^

Function to get the output of the resonant controller after each step.



Step function
-------------

.. doxygenfunction:: uz_resonantController_step


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to step the resonant controller once

  int main(void) {

    // set inputs
    uz_resonantController_set_input(R_controller_instance, in_ref, in_m, omega_el_rad_per_sec);
    // step once
    uz_resonantController_step(R_controller_instance);
    //read output
    output = uz_resonantController_get_output(R_controller_instance);
    
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
     uz_resonantController_reset(R_controller_instance);
  }

Description
^^^^^^^^^^^

Resets the Resonant-Controller. The initial condition for the integrator and the output after the reset is 0.0f.


Config function
---------------

.. doxygenfunction:: uz_resonantController_set_config

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example to change the config of the resonant controller.

  int main(void) {
    config.lower_limit = -10.0f;
    config.upper_limit = 10.0f;
    config.h = 7.0f;
	  uz_resonantController_config(R_controller_instance, config);
  }

Description
^^^^^^^^^^^

Function to change the configuration of the resonant controller by passing a new or changed config struct to the controller.



Saturation and Anti-Windup
--------------------------
The output of the controller is limited by the inputvalues ``upper_limit`` and ``lower_limit``.
As an anti-windup strategy the back calculation method is used.
The gain of the anti-windup feedback is given by the inputvalue ``Klim``.
To disable the Anti-Windup strategy the feedback can be set to 0.




Sources
-------

.. [#DiscPaper] G. Yepes, F. D. Freijedo, J. Doval-Gandoy, Ó. López, J. Malvar, and P. Fernandez-Domesaña , "Effects on Discretization Methods on the Performance of Resonant Controllers," IEEE Transactions on Power Electronics, vol. 25, no. 7, pp. 1692-1712, Jul. 2010
