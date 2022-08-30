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
     uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, actual_currents_Ampere);
  }

Description
===========

.. tikz:: Schematic overview of the SetPoint module
  :align: center
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows,  patterns

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=2em]
  \node(STP) {\Large{SetPoint}};
  %Exist on the background solely to be able to wrap the MTPA and FW around the machines
  \node[block,fill=yellow!0,name=IPMSM00, below =  1.25cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!2,name=SMPMSM00, below =0.25cm of IPMSM00,drop shadow,align=center] {SM-PMSM};
  \node[block,fill=yellow!0,name=IPMSM01, below =  5.5cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!0,name=SMPMSM01, below =0.25cm of IPMSM01,drop shadow,align=center] {SM-PMSM};
  \node[name=temp, below = 0.5 of STP]{\large{MTPA}};
  \node[name=temp2, below = 4.75cm of STP]{\large{Field- \\ Weakening}};
  %Normal nodes
  \node[block,fill=green!10,name=MTPA, drop shadow,fit=(SMPMSM00)(IPMSM00)(temp) ,minimum height=2cm,minimum width=3.3cm] {};
  \node[name=MTPA_Text, below = 0.5 of STP]{\large{MTPA}};
  \node[block,fill=yellow!20,name=IPMSM1, below =  1.25cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!20,name=SMPMSM1, below =0.25cm of IPMSM1,drop shadow,align=center] {SM-PMSM}; 
  \node[block,fill=green!10,name=FW, fit=(SMPMSM01)(IPMSM01)(temp2),drop shadow,minimum height=2cm,minimum width=3.3cm] {};
  \node[name=FW_Text, below = 4.75cm of STP, ]{\large{Field- \\ Weakening}};
  \node[block,fill=yellow!20,name=IPMSM2, below =   5.5cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!20,name=SMPMSM2, below =0.25cm of IPMSM2,drop shadow,align=center] {SM-PMSM};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=SetPoint,rounded corners,fit=(STP) (MTPA)(FW) ,inner sep=5pt,minimum width=5cm] {};
  \end{scope}
  \node[block,name=input1, below left = -8cm and 0.75cm of SetPoint,drop shadow,minimum width=2cm, align=center] {$\omega_{m}$\\ \tiny{float}};
  \node[block,name=input2, below = 0.5cm of input1,drop shadow,minimum width=2cm, align=center] {$M_{ref}$\\ \tiny{float}};
  \node[block,name=input4, below = 0.5cm of input2,drop shadow,minimum width=2cm, align=center] { $V_{DC}$\\ \tiny{float}};
  \node[block,name=input7, below = 0.5cm of input4,drop shadow,minimum width=2cm, align=center] { $i_{meas}$\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,name=input5, above =1cm of SetPoint,drop shadow,minimum width=2cm, align=center] { instance\\ \tiny{uz\_SetPoint\_t}};
  \node[block,name=input6, left = 1cm of input5,drop shadow,minimum width=2cm, align=center] {config\\ \tiny{struct  uz\_SetPoint\_config}};
  \node[block,name=output, below right= -5.5cm and 0.75cm of SetPoint,drop shadow,minimum width=2cm, align=center] {$I_{ref}$\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,fill=orange!20,name=Controller, right=0.5 cm of output,drop shadow,minimum height=4cm,align=center] {independent\\external\\current\\control};
  \draw[->](input5.south) -- (SetPoint.north);
  \draw[<-](output.west) -- (SetPoint.east |- output.west);
  \draw[->](output.east) -- (Controller.west);
  \draw[->](input1.east) -- (SetPoint.west |- input1.east);
  \draw[->](input2.east) -- (SetPoint.west |- input2.east);
  \draw[->](input4.east) -- (SetPoint.west |- input4.east);
  \draw[->](input6.east) -- (input5.west);
  \draw[->](input7.east) -- (SetPoint.west |- input7.east);
  \draw[->]($(FW.north)+(0.5,0)$) -- ($(MTPA.south)+(0.5,0)$) ;
  \draw[<-]($(FW.north)+(-0.5,0)$) -- ($(MTPA.south)+(-0.5,0)$) ;
  \node[name=omega_cut, below = 0cm of MTPA]{$\omega_{cut}$};
  \end{tikzpicture}

Calculates the reference currents based on the user selection. 
Depending on the operating condition of the machine, either an MTPA or a field-weakening is active.
The reference currents are always limited to the max. allowed current. 
I.e. if :math:`I_{max} = 15A`, in all cases :math:`\sqrt{I_{d,ref}^2 + I_{q,ref}^2}` will be lower than the max allowed current.
If a manual :math:`I_{d,manual}` input current is set in the MPTA state, this current will be added on top of the :math:`I_{d,MTPA}` current.
In FW operation, the :math:`I_{d,manual}` input will be ignored.
The cut-off rotational speed for the field-weakening is calculated like the following[[#Wilfling]_].:

.. math::

  V_{SV,max} &= \sqrt{\frac{V_{DC}}{\sqrt{3}}} - R_{ph}  I_{max}\\
  I_1 &= \sqrt{i_{q,meas}^2 + i_{d,meas}^2}\\
  \omega_c &= \frac{-R_{ph}  \psi_{PM}  I_1}{I_1^2  L_q^2 + \psi_{PM}^2} 
  + \sqrt{\frac{R_{ph}^2  \psi_{PM}^2  I_1^2 }{(I_1^2  L_q^2 + \psi_{PM}^2)^2} -    \frac{(I_1^2 - R_{ph}^2) - V_{SV,max}^2}{I_1^2  L_q^2 + \psi_{PM}^2}}\\

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

  I_{d,MTPA} &= \left(\frac{-\psi_{PM}}{2  (L_d - L_q)} - \sqrt{\frac{\psi_{PM}^2}{4  (L_d - L_q)^2} + I_{m,ref}^2}\right) + I_{d,manual}\ \ \ for \ \ (L_q > L_d)\\
  I_{d,MTPA} &= \left(\frac{-\psi_{PM}}{2  (L_d - L_q)} + \sqrt{\frac{\psi_{PM}^2}{4  (L_d - L_q)^2} + I_{m,ref}^2}\right) + I_{d,manual}\ \ \ for \ \ (L_q < L_d)\\

for :math:`\omega_{el} > \omega_c\\`:

.. math::

  M_{ref} &= \frac{3}{2}  p  \left(\psi_{PM}  I_{q,FW} + \frac{(L_d - L_q)}{L_d}  \left(-\psi_{PM} \pm \sqrt{\frac{V_{SV,max}^2}{\omega_{el}^2} - L_q^2  I_{q,FW}^2}\right)I_{q,FW}\right)\\
  0 &= I_{q,FW}^4 + a_2 I_{q,FW}^2 + a_1 I_{q,FW} + a_0  \\ 

This 4th order polynomial will be solved using the :ref:`uz_newton_raphson`, with the initial guess and the coefficients being:

.. math::

  I_{q,init} &= \frac{I_{max}}{2}\\
  a_2 &= \frac{\psi_{PM}^2 L_q^2 - (L_d - L_q)^2 \frac{V_{SV,max}^2}{\omega_el^2}}{L_q^2 (L_d - L_q)^2}\\
  a_1 &= \frac{-4 M_{ref} L_d L_q \psi_{PM}}{3 L_q^2 p (L_d - L_q)^2}\\
  a_0 &= \frac{4 (M_{ref} L_d)^2}{9 L_q^2 p^2 (L_d - L_q)^2}\\


General notes:
--------------

If the machine is in the MTPA state, the input ``id_ref_Ampere`` current will be added to the calculated :math:`I_{d,MTPA}` current. 
If the machine is inside the field weakening territory, the input ``id_ref_Ampere`` will be ignored.

Sources
=======

.. [#Wilfling] T. Wilfling, "Regelung eines Synchronaußenläufermotors und Optimierung der Rotorstruktur zur Drehmomentsteigerung", 2021
.. [#Schroeder] D. Schröder, "Elektrische Antriebe - Regelung von Antriebssystemen", Berlin, Springer 2015
.. [#matlab] `MTPA Control Reference, Mathworks <https://de.mathworks.com/help/mcb/ref/mtpacontrolreference.html>`_