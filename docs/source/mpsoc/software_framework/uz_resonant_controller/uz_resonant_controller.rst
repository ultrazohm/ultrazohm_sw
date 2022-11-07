.. _uz_resonant_controller:

===================
Resonant controller
===================

Toolbox for a standard resonant controller.
The ideal transfer function is:

.. math::

  \frac{Y(s)}{E(s)}= K_R \cdot \frac{s}{s^2 + \omega_R^2}

with the resonant frequency :math:`\omega_R` [[#DiscPaper]_].

The implemented discrete time transfer function is created by impulse invariant discretization with delay compensation [[#DiscPaper]_ p. 1700] and is:

.. math::

    G_R(s) = K_R T_{s} \frac{\cos(2\omega_R T_{s}) - z^{-1}\cos(\omega_R T_{s}) }{1-2 z^{-1} \cos(\omega_R T_{s} )+ z^{-2} }

The resonant frequency is specified by :math:`\omega_R = h \cdot \omega_{el}`, with the order of the harmonic :math:`h` to be controlled and the fundamental frequency :math:`\omega_{el}`.
This method of discretization is chosen, as it is the most optimal among the methods discussed in [[#DiscPaper]_ p. 1710 f.] with reduced phase lag, improved stability and accurate location of the resonant peaks even for high frequencies.


Resonant-Controller
-------------------

.. doxygentypedef:: uz_resonantController_t


Description
^^^^^^^^^^^

Struct to create a resonant controller instance.


.. doxygenstruct:: uz_resonantController_config
  :members:

Description
^^^^^^^^^^^

Struct for the configuration of the resonant controller.


Init function
-------------

.. doxygenfunction:: uz_resonantController_init


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example to create and initialize a resonant controller instance.

  int main(void) {
    
    const struct uz_resonantController_config config_R = {
        .sampling_time = 0.0001f,
        .gain = 52.5f,
        .harmonic_order = 2.0f,
        .fundamental_frequency = 10.0f,
        .lower_limit = -4.0f,
        .upper_limit = 4.0f,
        .antiwindup_gain = 10.0f,
        .in_reference_value = 0.0f,
        .in_measured_value = 0.0f,
    };
    uz_resonantController_t* R_controller_instance= uz_resonantController_init(config_R);
  }



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



Get output function
-------------------

.. doxygenfunction:: uz_resonantController_get_output

Description
^^^^^^^^^^^

Function to get the output of the resonant controller after each step.



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


Saturation and Anti-Windup
--------------------------
The output of the controller is limited by the input values ``upper_limit`` and ``lower_limit``.
As an anti-windup strategy the back calculation method is used.
The gain of the anti-windup feedback is given by the input value ``antiwindup_gain``.
To disable the anti-windup strategy the feedback can be set to 0.








Sources
-------

.. [#DiscPaper] G. Yepes, F. D. Freijedo, J. Doval-Gandoy, Ó. López, J. Malvar, and P. Fernandez-Domesaña , "Effects on Discretization Methods on the Performance of Resonant Controllers," IEEE Transactions on Power Electronics, vol. 25, no. 7, pp. 1692-1712, Jul. 2010
