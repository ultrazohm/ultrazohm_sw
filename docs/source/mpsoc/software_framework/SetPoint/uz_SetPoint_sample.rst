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
     float id_ref_Ampere = 0.0f;
     float V_DC_Volts = 24.0f;
     uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, id_ref_Ampere, V_DC_Volts);
  }

Description
===========

Calculates the reference currents depending on the user selection. 
Either an MTPA or a field-weakening is active, depending on the operating condition of the machine.
The reference currents are always limited to the max. allowed current. 
I.e. if :math:`I_{max} = 15A`, in all cases :math:`\sqrt{i_{d,ref}^2 + i_{q,ref}^2}` will be lower than the max allowed current.
If a manual :math:`i_{d,ref}` is set in the MPTA state, this current overwrites the calculated :math:`i_{d,MTPA}` current.
In MTPA operation the :math:`i_q` will get priority, whilst in the field-weakening case :math:`i_d` will get priority.
The cut-off rotational speed for the field-weakening is calculated like the following[[#Wilfling]_].:

.. math::

  V_{SV,max} &= \sqrt{\frac{V_{DC}}{\sqrt{3}}}\cdot 0.94\\
  \omega_c &= \frac{-R_{ph} \cdot \psi_{PM} \cdot I_{max}}{I_{max}^2 \cdot L_q^2 + \psi_{PM}^2} 
  + \sqrt{\frac{R_{ph}^2 \cdot \psi_{PM}^2 \cdot I_{max}^2 }{(I_{max}^2 \cdot L_q^2 + \psi_{PM}^2)^2} -    \frac{(I_{max}^2 - R_{ph}^2) - V_{SV,max}^2}{I_{max}^2 \cdot L_q^2 + \psi_{PM}^2}}\\

SM-PMSM[[#matlab]_]
-------------------

.. math::

  i_{d,MTPA} &= 0\\
  i_{q,MTPA} &= \frac{M_{ref}}{\frac{3}{2} \cdot p \cdot \psi_{PM}}\\


for :math:`\omega_{el} > \omega_c\\`:

.. math::

  i_{d,fw} &= \frac{\psi_{PM}}{L_d}\cdot(1- \frac{\omega_c}{\omega_{el}})\\
  i_{q,fw} &= i_{q,MTPA}\\
  i_{q,fw,max} &= \sqrt{I_{max}^2 - i_{d,fw}^2}

I-PMSM[[#matlab]_]
------------------

.. warning::

  :math:`L_d \neq L_q` is necessary and will be checked.

.. math::

  i_{m,ref} &= \frac{M_{ref}}{\frac{3}{2} \cdot p \cdot \psi_{PM}}\\
  i_{d,MTPA} &= \frac{\psi_{PM}}{4 \cdot (L_q - L_d)} - \sqrt{\frac{\psi_{PM}^2}{16 \cdot (L_q - L_d)^2} + \frac{i_{m,ref}^2}{2}}\\
  i_{q,MTPA} &= \sqrt{i_{m,ref}^2 - i_{d,MTPA}^2}\\

for :math:`\omega_{el} > \omega_c\\`:

.. math::

  i_{d,fw} &= \frac{-\psi_{PM} \cdot L_d + \sqrt{(\psi_{PM} \cdot L_d)^2 - (L_d^2 - L_q^2) \cdot (\psi_{PM}^2 + L_q^2 \cdot I_{max}^2 - \frac{V_{SV,max}^2}{\omega_{el}^2} )} }{L_d^2 - L_q^2}\\
  i_{q,fw} &= i_{q,MTPA}\\
  i_{q,fw,max} &= \sqrt{I_{max}^2 - i_{d,fw}^2}

Sources
=======

.. [#Wilfling] T. Wilfling, "Regelung eines Synchronaußenläufermotors und Optimierung der Rotorstruktur zur Drehmomentsteigerung", 2021
.. [#matlab] `MTPA Control Reference, Mathworks <https://de.mathworks.com/help/mcb/ref/mtpacontrolreference.html>`_