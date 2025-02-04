.. _uz_CurrentControl_set_Kp_Ki_opt:

===============================================
Set Ki or Kp according to optimisation criteria 
===============================================

.. doxygenfunction:: uz_CurrentControl_tune_magnitude_optimum

.. doxygenfunction:: uz_CurrentControl_tune_symmetric_optimum

.. doxygenfunction:: uz_CurrentControl_tune_bandwidth

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to set Kp and Ki parameters. 

  int main(void) {
     struct uz_PMSM_t config_PMSM = {
      .Ld_Henry = 0.0001f,
      .Lq_Henry = 0.0002f,
      .R_ph_Ohm = 0.008f
     };
     float tau_sigma_sec = 0.0001;
     float bandwidth_rad_per_sec = 2500;
     uz_CurrentControl_tune_magnitude_optimum(uz_CurrentControl_t *self, float tau_sigma_sec);
     uz_CurrentControl_tune_symmetric_optimum(uz_CurrentControl_t *self, float tau_sigma_sec);
     uz_CurrentControl_tune_bandwidth(uz_CurrentControl_t *self, float bandwidth_rad_per_sec);     
  }

Description
===========

This only works for a ``UZ_PI_PARALLEL`` PI-controller configuration.
Calculates the values of ``Kp`` and ``Ki`` according to different optimization criteria and the parameters of the PMSM. 
The magnitude optimum provides a good compromise between a fast response to a step change in the reference variable with low overshoot and good disturbance behaviour [[#Gemaßmer]_] (p.94). 
The controlled system is simplified to a PT2 system consisting of the respective current control loop (PT1 system) and an additional PT1 system representing the dead time due to the measuring process and actuator: 

.. math::

  G_S(s) = \frac{1}{R} \cdot \frac{1}{1 + \tau_{d/q} \cdot s} \cdot \frac{1}{1 + \tau_{\sigma} \cdot s}

With the respective time constants:

.. math::

  \tau_{d/q} = \frac{L_{d/q}}{R}, \qquad \tau_{\sigma} = 1...2 \cdot T_{ISR}

:math:`T_{ISR}` represents the selected period of the ISR. This time must be multiplied by a factor between 1 and 2 to obtain the real dead time. [[#Gemaßmer]_] (p.98), for example, selects a factor of 1.5. 
The transfer function of the current controller can be expressed as follows:

.. math::
  G_R(s) = V_R \cdot \frac{1 + T_n \cdot s}{T_n \cdot s}

According to the magnitude optimum, the controller settings for a controlled system of the form 

.. math::

  G_S(s) = \frac{V_S}{1 + T_1 \cdot s} \cdot \frac{1}{1 + T_{\sigma} \cdot s} 

have to be selected as follows:

.. math::

  T_n = T_1 \quad and \quad V_R = \frac{T_1}{2 V_S T_{\sigma}}

Where :math:`T_1` is the larger time constant.
Comparing this to the real transfer function :math:`G_S` from above and noting that :math:`\tau_{d/q}` is the larger time constant, the following tuning rules are obtained:

.. math::

  T_n = \tau_{d/q}, \qquad V_R = R \cdot \frac{\tau_{d/q}}{2 \cdot \tau_{\sigma}}

With this, the controller parameters of a parallel PI-controller can be determined:

.. math::

  G_R(s) &= R \cdot \frac{\tau_{d/q}}{2 \cdot \tau_{\sigma}} \cdot \frac{1 + \tau_{d/q} \cdot s}{\tau_{d/q} \cdot s}\\
        &= \frac{L_{d/q}}{2 \cdot \tau_{\sigma}} \cdot \frac{1 + \tau_{d/q} \cdot s}{\tau_{d/q} \cdot s}\\
        &= \frac{L_{d/q}}{2 \cdot \tau_{\sigma}} + \frac{L_{d/q}}{2 \cdot \tau_{\sigma} \cdot \tau_{d/q}} \cdot \frac{1}{s}\\
        &= \frac{L_{d/q}}{2 \cdot \tau_{\sigma}} + \frac{R}{2 \cdot \tau_{\sigma}} \cdot \frac{1}{s}\\

.. math::

  K_{p,d/q} = \frac{L_{d/q}}{2 \cdot \tau_{\sigma}}, \qquad K_{i,d/q} = \frac{R}{2 \cdot \tau_{\sigma}}

For controlled systems with an integrating component or when optimisation by the magnitude optimum is difficult due to unfavourable time constants, the symmetrical optimum can be used [[#Schroeder]_] (p.81).
In this case, the controller settings must be selected differently:

.. math::

  T_n = 4 T_{\sigma}, \qquad V_R = \frac{T_1}{2 V_S T_{\sigma}}

For the parallel PI controller, the following formulas result accordingly:

.. math::

  G_R(s) &= \frac{T_1}{2 V_S T_{\sigma}} \cdot \frac{1 + 4 T_{\sigma} \cdot s}{4 T_{\sigma} \cdot s}\\
         &= \frac{\tau_{d/q}}{2 \frac{1}{R} \tau_{\sigma}} \cdot \frac{1 + 4 \tau_{\sigma} \cdot s}{4 \tau_{\sigma} \cdot s}\\
         &= \frac{L_{d/q}}{2 \tau_{\sigma}} \cdot \frac{1 + 4 \tau_{\sigma} \cdot s}{4 \tau_{\sigma} \cdot s}\\
         &= \frac{L_{d/q}}{2 \tau_{\sigma}} + \frac{L_{d/q}}{8 \tau_{\sigma}^2} \cdot \frac{1}{s}

.. math::

  K_{p,d/q} = \frac{L_{d/q}}{2 \cdot \tau_{\sigma}}, \qquad K_{i,d/q} = \frac{L_{d/q}}{8 \tau_{\sigma}^2}

As a third option, the current controllers can be adjusted according to a desired bandwidth. 
The corresponding formulas are based on pole placement:

.. math::

  K_{p,d/q} = \frac{R}{L_{d/q}}, \qquad K_{i,d/q} = R \cdot Bandwidth (rad/sec)

For a detailed explanation of how these formulae are derived, please refer to [[#TexasI]_] (p.406).

Example calculation
===================

Consider a PMSM with the maschine data from above:

.. math::

  L_d &= 0.0001 H\\
  L_q &= 0.0002 H\\
  R &= 0.008 \Omega

In this case a ISR frequency of :math:`f_{ISR} = 10kHz` is chosen. 
See also :ref:`uz_mux_axi` to determine the value of :math:`f_{ISR}`.
The controller settings are calculated according to the magnitude optimum as follows:

.. math::

  K_{p,d} &= \frac{L_{d}}{2 \cdot \tau_{sigma}} = \frac{0.0001 H}{2 \cdot 1.5 \cdot \frac{1}{10000 Hz}} = 0.0003\\  
  K_{i,d} &= \frac{R}{2 \cdot \tau_{sigma}} = \frac{0.008 \Omega}{2 \cdot 1.5 \cdot \frac{1}{10000 Hz}} = 26.67\\
  K_{p,q} &= \frac{L_{q}}{2 \cdot \tau_{sigma}} = \frac{0.0002 H}{2 \cdot 1.5 \cdot \frac{1}{10000 Hz}} = 0.0006\\
  K_{i,q} &= \frac{R}{2 \cdot \tau_{sigma}} = \frac{0.008 \Omega}{2 \cdot 1.5 \cdot \frac{1}{10000 Hz}} = 26.67

For the symmetric optimum:

.. math::

  K_{p,d} &= \frac{L_{d}}{2 \cdot \tau_{sigma}} = \frac{0.0001 H}{2 \cdot 1.5 \cdot \frac{1}{10000 Hz}} = 0.0003\\  
  K_{i,d} &= \frac{L_{d}}{8 \tau_{sigma}^2} = \frac{0.0001 H}{8 \cdot \frac{1}{10000 Hz}^2} = 1.25\\
  K_{p,q} &= \frac{L_{q}}{2 \cdot \tau_{sigma}} = \frac{0.0002 H}{2 \cdot 1.5 \cdot \frac{1}{10000 Hz}} = 0.0006\\
  K_{i,q} &= \frac{L_{q}}{8 \tau_{sigma}^2} = \frac{0.0002 H}{8 \cdot \frac{1}{10000 Hz}^2} = 2.5

Note that here the ISR time has been multiplied by 1.5. As mentioned above, this factor can be chosen by the user. 
For optimisation based on a desired bandwidth of :math:`2500 rad/s`, the controller parameters are calculated as follows:

.. math::

  K_{p,d} &= \frac{R}{L_{d}} = \frac{0.008 \Omega}{0.0001 H} = 80\\
  K_{i,d} &= R \cdot Bandwidth = 0.008 \Omega \cdot 2500 \frac{rad}{s} = 20\\
  K_{p,q} &= \frac{R}{L_{q}} = \frac{0.008 \Omega}{0.0002 H} = 40\\
  K_{i,q} &= R \cdot Bandwidth = 0.008 \Omega \cdot 2500 \frac{rad}{s} = 20

Sources
=======

.. [#Schroeder] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Springer, ISBN 978-3-642-30095-0
.. [#TexasI] "InstaSPIN-FOC™ and InstaSPIN-MOTION™ Users Guide-0", Texas Instruments, https://www.ti.com/lit/ug/spruhj1i/spruhj1i.pdf?ts=1686841737437
.. [#Gemaßmer] Effiziente und dynamische Drehmomenteinprägung in hoch ausgenutzten Synchronmaschinen mit eingebetteten Magneten, Tobias Gemaßmer, ISBN 978-3-7315-0366-8