.. _uz_svm_6ph:

===========================
Space vector Modulation 6ph
===========================

General
=======

This module implements a space vector modulation for asymmetrical six-phase machine with isolated neutral points (2N).
The implementation is adaptable to 1N and described in the references.

Usage
=====

Function references
-------------------

.. doxygenstruct:: uz_svm_asym_6ph_CSVPWM24_out
  :members:

.. doxygenfunction:: uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta

.. doxygenfunction:: uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_dq

Minimum code example
--------------------

A minimal code example is given in the following.
The SVM not only calculates Duty Cycles, it also yields phase shifts for the PWM IP-Cores.
Applying them to the modules is vital.
Additionally, the output struct contains two flags, indicating that either the :math:`\alpha\beta`- or :math:`xy`-setpoints or both have been limited.
They can be used for a clamping feature, inhibiting integrators in the control algorithm to overflow.
In this example, they are not used.

.. code-block:: c
  :caption: Changes in ``isr.c`` (R5)

  // declarations
  #include "../uz/uz_Space_Vector_Modulation_6ph/uz_Space_Vector_Modulation_6ph.h"
  uz_6ph_dq_t u_ref_6ph = {0};
  uz_3ph_dq_t u_ref_3ph = {0};
  uz_3ph_dq_t cc_setpoint = {0};
  struct uz_svm_asym_6ph_CSVPWM24_out svm_out = {0};
  ...
  // in isr
  if (current_state==control_state)
  {
    // example current control
    u_ref_3ph = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, cc_setpoint, Global_Data.av.actual_3ph_dq, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
    u_ref_6ph.d = u_ref_3ph.d;
    u_ref_6ph.q = u_ref_3ph.q;
  }

  // Modulation
  svm_out = uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_dq(u_ref_6ph, Global_Data.av.theta_elec, Global_Data.av.v_dc1);
  // PWM phase shift
  uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_0_to_5, svm_out.shift_system1, svm_out.shift_system1, svm_out.shift_system1);
  uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_6_to_11, svm_out.shift_system2, svm_out.shift_system2, svm_out.shift_system2);
  // assign Duty Cycles
  uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, svm_out.Duty_Cycle.system1.DutyCycle_A, svm_out.Duty_Cycle.system1.DutyCycle_B, svm_out.Duty_Cycle.system1.DutyCycle_C);
  uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, svm_out.Duty_Cycle.system2.DutyCycle_A, svm_out.Duty_Cycle.system2.DutyCycle_B, svm_out.Duty_Cycle.system2.DutyCycle_C);


Theoretical details
===================

Limitation
----------

The 6ph SVM uses two setpoint limitations.
Both of them limit the absolute value (length) of the space vector (SV), while leaving the phase angle untouched.
Th checks for the limitations are executed in the listed order below:

The :math:`xy`-SV must not be longer than 10% of the :math:`\alpha\beta`-SV.
As can be seen from [[#Eldeeb_diss]_] Fig. 3.3, a large :math:`\alpha\beta`-SV represents a small :math:`xy`-SV and vice versa.
Therefore if the :math:`\alpha\beta`-SV is near the maximum, the :math:`xy`-SV can only be small.
Although a general limitation can not achieve maximum usage in all operating points, with this rule an overall good performance can be expected.

Since the maximum voltage is given by the DC-Bus-Voltage and the modulation index :math:`m_i=\frac{1}{\sqrt{3}}` (determined in simulation), the combined length of the space vectors has to be limited.
Therefore both lengths are added and if the exceed the maximum allowed voltage, they will be shortened in their existing relations.
Since the :math:`xy`-SV limitation is executed before and the relation of the :math:`\alpha\beta`-SV and :math:`xy`-SV are kept the same, the previous limitation will not be violated.

Space vectors
-------------

From the existing :math:`2^6` SVs in a six-phase system, not all of them are used.
Instead, the selected sequences of [[#Eldeeb_diss]_] Tab. 3.III are used.
Please note that the decimal notation of [[#Eldeeb_paper]_] and [[#other_paper]_] are used.
Therefore, the binary values of [[#Eldeeb_diss]_] must be mirrored, making the switch a1 being represented by the LSB and c2 by the MSB.

.. csv-table:: Space vectors
   :file: sequences_6ph.csv
   :widths: 10 50
   :header-rows: 1


Offline calculations
--------------------

Verification
============

Limitation
----------

To test the limitation, a list of :math:`\alpha\beta`-SVs and :math:`xy`-SVs was created with :math:`k \cdot e^{i \cdot \phi}` and :math:`k=0, 0.001, ... 1` und :math:`\phi=0, 0.001, ... 2\pi`.
Each :math:`\alpha\beta`-SV was combined with each :math:`xy`-SV and applied to the SVM.
Using no limitation, the SVM threw an error for a Duty Cycle out of range (negative or greater 1).
Using the limitation, no error occured and the relative limit of :math:`xy`-SV to :math:`\alpha\beta`-SV could even be raised up to 50% without causing an invalid Duty Cycle.

Closed loop simulation
----------------------

Closed loop testbench
---------------------



Literature
==========

.. [#Eldeeb_diss] H. Eldeeb, "Modelling, Control and Post-Fault Operation of Dual Three-phase Drives for Airborne Wind Energy," Diss., Technische Universität München, München, 2019
.. [#Eldeeb_paper] H. Eldeeb, C. Hackl, M. Abdelrahem and A. S. Abdel-Khalik, "A unified SVPWM realization for minimizing circulating currents of dual three phase machines," 2017 IEEE 12th International Conference on Power Electronics and Drive Systems (PEDS), Honolulu, HI, USA, 2017, pp. 925-931, doi: 10.1109/PEDS.2017.8289127.
.. [#other_paper] C. Wang, K. Wang, and X. You, “Research on synchronized svpwm strategies under low switching frequency for six-phase vsi-fed asymmetrical dual stator induction machine,” IEEE Trans. on Ind. Electron., vol. 63, no. 11, pp. 6767–6776, Nov. 2016