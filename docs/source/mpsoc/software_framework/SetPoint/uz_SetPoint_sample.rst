.. _uz_SetPoint_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_SetPoint_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to use the SetPoint module. SetPoint-Instance via :ref:`init-function <uz_SetPoint_init>`

  int main(void) {
     float omega_m_rad_per_sec = 1.5f;
     float M_ref_Nm = 0.0045f;
     float V_DC_Volts = 24.0f;
     uz_3ph_dq_t actual_currents_Ampere = {1.0f, 2.0f, 0.0f};
     uz_3ph_dq_t output = uz_SetPoint_sample(SP_instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, actual_currents_Ampere);
  }

Description
===========

Calculates the reference currents based on the user selection. 
Depending on the operating condition of the machine, either an MTPA or a field weakening is active.
The reference currents are always limited to the max. admissible current. 
I.e. if :math:`I_{max} = 15A`, in all cases :math:`\sqrt{I_{d,ref}^2 + I_{q,ref}^2}` will be lower than the max allowed current.
To ensure that the resulting set-currents after solving the polynomials for the MTPA and FW approximate with a sufficient degree of accuracy the reference torque, a comparison between the reference torque and the actual torque via the resulting set-currents is made.
If the difference between these two variables exceeds a user-configurable threshold, an assertion is triggered.
The cut-off rotational speed for the field-weakening is calculated based on the max possible stator voltage :math:`V_{max}`, which depends on the max modulation index :math:`m_\mathrm{max}`. 
A safety buffer of 5% is implemented:


.. math::

  V_\mathrm{max} &= V_\mathrm{dc} m_\mathrm{max} 0.95\,.\\


This leads to

.. math::
  V_\mathrm{max} = \sqrt{v_d^2 + v_q^2} = \sqrt{(R_s i_d - \omega_c L_q i_q)^2 + (R_s i_q + \omega_c (\psi_{PM} + L_d i_d))^2}\,.\\

Solving for :math:`\omega_c` leads to

.. math::
  
  a &= L_q^2 i_q^2 + \psi_{PM}^2 + L_d i_d (2\psi_{PM} + L_d i_d)\\
  b &= 2 R_s i_q(i_d (L_d - L_q) + \psi_{PM})\\
  c &= R_s^2 (i_d^2 + i_q^2) - V_\mathrm{max}^2\\

and finally

.. math::
  
  \omega_c = \frac{-b + \sqrt{b^2 - 4ac}}{2a}\,.


SM-PMSM[[#Schroeder]_]
----------------------

.. math::

  I_{q,MTPA} &= \frac{M_{ref}}{\frac{3}{2}  p  \psi_{PM}}\\
  I_{d,MTPA} &= 0\\


for :math:`\omega_{el} > \omega_c`:

.. math::

  I_{q,FW} &= I_{q,MTPA}\\
  I_{d,FW} &= \frac{-\psi_{PM}}{L_d} + \frac{1}{L_d} \sqrt{\left(\frac{V_\mathrm{FE,max}}{\omega_{el}}\right)^2 - (L_q I_{q,FW})^2}\\

with 

.. math::

  V_\mathrm{FE,max} &= (V_\mathrm{max} - R_s I_1) 0.95\,,\\

and

.. math::

  I_1 &= \sqrt{i_d^2 + i_q^2}\,.\\

I-PMSM[[#Schroeder]_ S.1095ff.]
-------------------------------

.. warning::

  :math:`L_d \neq L_q` is necessary and will be checked.

.. math::
  M_{ref} &= \frac{3}{2}  p I_{q,MTPA} \left(\psi_{PM} + \frac{1}{2}  \left(-\psi_{PM} - \sqrt{\psi_{PM}^2 + 4  (L_d - L_q)^2  I_{q,MTPA}^2}\right)\right)\\
  0 &= I_{q,MTPA}^4 + \frac{2 M_{ref}  \psi_{PM}}{3 (L_d - L_q)^2  p}  I_{q,MTPA} - \frac{4 M_{ref}^2}{9 (L_d - L_q)^2  p^2} \\

This 4th order polynomial will be solved using the :ref:`uz_newton_raphson`, with the initial guess being:

.. math::

  I_{q,init} &= \frac{M_{ref}}{\frac{3}{2}  p  \psi_{PM}}\\

The d-current, depending on the saliency ratio, will be calculated like the following:

.. math::

  I_{d,MTPA} &= \left(\frac{-\psi_{PM}}{2  (L_d - L_q)} - \sqrt{\frac{\psi_{PM}^2}{4  (L_d - L_q)^2} + I_{q,MTPA}^2}\right)\ \ \ for \ \ (L_q > L_d)\\
  I_{d,MTPA} &= \left(\frac{-\psi_{PM}}{2  (L_d - L_q)} + \sqrt{\frac{\psi_{PM}^2}{4  (L_d - L_q)^2} + I_{q,MTPA}^2}\right)\ \ \ for \ \ (L_q < L_d)\\

for :math:`\omega_{el} > \omega_c`:

.. math::

  M_{ref} &= \frac{3}{2}  p  \left(\psi_{PM}  I_{q,FW} + \frac{(L_d - L_q)}{L_d}  \left(-\psi_{PM} \pm \sqrt{\frac{V_{FE,max}^2}{\omega_{el}^2} - L_q^2  I_{q,FW}^2}\right)I_{q,FW}\right)\\
  0 &= I_{q,FW}^4 + a_2 I_{q,FW}^2 + a_1 I_{q,FW} + a_0  \\ 

This 4th order polynomial will be solved using the :ref:`uz_newton_raphson`, with the initial guess and the coefficients being:

.. math::

  I_{q,init} &= \frac{I_{max}}{2}\\
  a_2 &= \frac{\psi_{PM}^2 L_q^2 - (L_d - L_q)^2 \frac{V_{FE,max}^2}{\omega_{el}^2}}{L_q^2 (L_d - L_q)^2}\\
  a_1 &= \frac{-4 M_{ref} L_d L_q \psi_{PM}}{3 L_q^2 p (L_d - L_q)^2}\\
  a_0 &= \frac{4 (M_{ref} L_d)^2}{9 L_q^2 p^2 (L_d - L_q)^2}\\
  I_{d,FW} &= \frac{-\psi_{PM}}{L_d} + \frac{1}{L_d} \sqrt{\left(\frac{V_{FE,max}}{\omega_{el}}\right)^2 - (L_q I_{q,FW})^2}\\


Sources
=======

.. [#Schroeder] D. Schröder, "Elektrische Antriebe - Regelung von Antriebssystemen", Berlin, Springer 2015