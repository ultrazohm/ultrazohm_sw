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
Depending on the operating condition of the machine, either an MTPA or a field-weakening is active.
The reference currents are always limited to the max. allowed current. 
I.e. if :math:`I_{max} = 15A`, in all cases :math:`\sqrt{I_{d,ref}^2 + I_{q,ref}^2}` will be lower than the max allowed current.
If a manual :math:`I_{d,manual}` input current is set in the MPTA state, this current will be added on top of the :math:`I_{d,MTPA}` current.
In FW operation, the :math:`I_{d,manual}` input will be ignored.
The cut-off rotational speed for the field-weakening is calculated based on the max possible field excitation :math:`V_{FE,max}` and the measured total current :math:`I_1` [[#Wilfling]_].:

.. math::

  V_{FE,max} &= \sqrt{\frac{V_{DC}}{\sqrt{3}}} - R_{ph}  I_{max}\\
  I_1 &= \sqrt{i_{q,meas}^2 + i_{d,meas}^2}\\
  \omega_c &= \frac{-R_{ph}  \psi_{PM}  I_1}{I_1^2  L_q^2 + \psi_{PM}^2} 
  + \sqrt{\frac{R_{ph}^2  \psi_{PM}^2  I_1^2 }{(I_1^2  L_q^2 + \psi_{PM}^2)^2} -    \frac{(I_1^2 - R_{ph}^2) - V_{FE,max}^2}{I_1^2  L_q^2 + \psi_{PM}^2}}\\

SM-PMSM[[#matlab]_]
-------------------

.. math::

  I_{q,MTPA} &= \frac{M_{ref}}{\frac{3}{2}  p  \psi_{PM}}\\
  I_{d,MTPA} &= I_{d,manual}\\


for :math:`\omega_{el} > \omega_c\\`:

.. math::

  I_{d,fw} &= \frac{\psi_{PM}}{L_d}(\frac{\omega_c}{\omega_{el}}-1)\\
  I_{q,fw} &= I_{q,MTPA}\\
  I_{q,fw,max} &= \sqrt{I_{max}^2 - I_{d,fw}^2}

I-PMSM[[#Schroeder]_ S.1095ff.]
-------------------------------

.. warning::

  :math:`L_d \neq L_q` is necessary and will be checked.

.. math::
  M_{ref} &= \frac{3}{2}  p  \left(\psi_{PM}  I_{q,MTPA} + \frac{1}{2}  \left(-\psi_{PM} - \sqrt{\psi_{PM}^2 + 4  (L_d - L_q)^2  I_{q,MTPA}^2}\right)\right)\\
  0 &= I_{q,MTPA}^4 + \frac{2 M_{ref}  \psi_{PM}}{3 (L_d - L_q)^2  p}  I_{q,MTPA} - \frac{4 M_{ref}^2}{9 (L_d - L_q)^2  p^2} \\

This 4th order polynomial will be solved using the :ref:`uz_newton_raphson`, with the initial guess being:

.. math::

  I_{q,init} &= \frac{M_{ref}}{\frac{3}{2}  p  \psi_{PM}}\\

The d-current, depending on the saliency ratio, will be calculated like the following:

.. math::

  I_{d,MTPA} &= \left(\frac{-\psi_{PM}}{2  (L_d - L_q)} - \sqrt{\frac{\psi_{PM}^2}{4  (L_d - L_q)^2} + I_{q,MTPA}^2}\right) + I_{d,manual}\ \ \ for \ \ (L_q > L_d)\\
  I_{d,MTPA} &= \left(\frac{-\psi_{PM}}{2  (L_d - L_q)} + \sqrt{\frac{\psi_{PM}^2}{4  (L_d - L_q)^2} + I_{q,MTPA}^2}\right) + I_{d,manual}\ \ \ for \ \ (L_q < L_d)\\

for :math:`\omega_{el} > \omega_c\\`:

.. math::

  M_{ref} &= \frac{3}{2}  p  \left(\psi_{PM}  I_{q,FW} + \frac{(L_d - L_q)}{L_d}  \left(-\psi_{PM} \pm \sqrt{\frac{V_{FE,max}^2}{\omega_{el}^2} - L_q^2  I_{q,FW}^2}\right)I_{q,FW}\right)\\
  0 &= I_{q,FW}^4 + a_2 I_{q,FW}^2 + a_1 I_{q,FW} + a_0  \\ 

This 4th order polynomial will be solved using the :ref:`uz_newton_raphson`, with the initial guess and the coefficients being:

.. math::

  I_{q,init} &= \frac{I_{max}}{2}\\
  a_2 &= \frac{\psi_{PM}^2 L_q^2 - (L_d - L_q)^2 \frac{V_{FE,max}^2}{\omega_{el}^2}}{L_q^2 (L_d - L_q)^2}\\
  a_1 &= \frac{-4 M_{ref} L_d L_q \psi_{PM}}{3 L_q^2 p (L_d - L_q)^2}\\
  a_0 &= \frac{4 (M_{ref} L_d)^2}{9 L_q^2 p^2 (L_d - L_q)^2}\\

  I_{d,FW} = \frac{-\psi_{PM}}{L_d} + \frac{1}{L_d} \sqrt{\left(\frac{V_{FE,max}}{\omega_{el}}\right)^2 - (L_q I_{q,FW})^2}\\

General notes:
--------------

If the machine is in the MTPA state, the input ``id_ref_Ampere`` current will be added to the calculated :math:`I_{d,MTPA}` current. 
If the machine is inside the field weakening territory, the input ``id_ref_Ampere`` will be ignored.

Sources
=======

.. [#Wilfling] T. Wilfling, "Regelung eines Synchronaußenläufermotors und Optimierung der Rotorstruktur zur Drehmomentsteigerung", 2021
.. [#Schroeder] D. Schröder, "Elektrische Antriebe - Regelung von Antriebssystemen", Berlin, Springer 2015
.. [#matlab] `MTPA Control Reference, Mathworks <https://de.mathworks.com/help/mcb/ref/mtpacontrolreference.html>`_