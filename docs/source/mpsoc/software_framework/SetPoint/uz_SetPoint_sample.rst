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
     uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
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
  \node[block,name=input1, below left = -7cm and 0.75cm of SetPoint,drop shadow,minimum width=2cm, align=center] {$\omega_{m}$\\ \tiny{float}};
  \node[block,name=input2, below = 0.5cm of input1,drop shadow,minimum width=2cm, align=center] {$M_{ref}$\\ \tiny{float}};
  \node[block,name=input4, below = 0.5cm of input2,drop shadow,minimum width=2cm, align=center] { $V_{DC}$\\ \tiny{float}};
  \node[block,name=input5, above =1cm of SetPoint,drop shadow,minimum width=2cm, align=center] { instance\\ \tiny{uz\_SetPoint\_t}};
  \node[block,name=input6, left = 1cm of input5,drop shadow,minimum width=2cm, align=center] {config\\ \tiny{struct  uz\_SetPoint\_config}};
  \node[block,name=output, below right= -5.5cm and 0.75cm of SetPoint,drop shadow,minimum width=2cm, align=center] {output\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,fill=orange!20,name=Controller, right=0.5 cm of output,drop shadow,minimum height=4cm,align=center] {independent\\external\\current\\control};
  \draw[->](input5.south) -- (SetPoint.north);
  \draw[<-](output.west) -- (SetPoint.east |- output.west);
  \draw[->](output.east) -- (Controller.west);
  \draw[->](input1.east) -- (SetPoint.west |- input1.east);
  \draw[->](input2.east) -- (SetPoint.west |- input2.east);
  \draw[->](input4.east) -- (SetPoint.west |- input4.east);
  \draw[->](input6.east) -- (input5.west);
  \end{tikzpicture}

Calculates the reference currents depending on the user selection. 
Either an MTPA or a field-weakening is active, depending on the operating condition of the machine.
The reference currents are always limited to the max. allowed current. 
I.e. if :math:`I_{max} = 15A`, in all cases :math:`\sqrt{i_{d,ref}^2 + i_{q,ref}^2}` will be lower than the max allowed current.
If a manual :math:`i_{d,ref}` is set in the MPTA state, this current overwrites the calculated :math:`i_{d,MTPA}` current.
In MTPA operation the :math:`i_q` will get priority, whilst in the field-weakening case :math:`i_d` will get priority.
The cut-off rotational speed for the field-weakening is calculated like the following[[#Wilfling]_].:

.. math::

  V_{SV,max} &= \sqrt{\frac{V_{DC}}{\sqrt{3}}} - R_{ph} \cdot I_{max}\\
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

I-PMSM[[#Schroeder]_ S.1095ff.][[#matlab]_]
-------------------------------------------

.. warning::

  :math:`L_d \neq L_q` is necessary and will be checked.

.. note::

  To ensure proper operation in the case, that a manual user input instead of a SpeedController is used to set :math:`M_{ref}`, an assumption about the :math:`i_q` current has to be made. 
  This assumption minimally distorts the MTPA currents.

.. math::

  i_{m,ref} &= \frac{M_{ref}}{\frac{3}{2} \cdot p \cdot \psi_{PM}}\\
  i_{d,MTPA} &= \frac{-\psi_{PM}}{2 \cdot (L_d - L_q)} - \sqrt{\frac{\psi_{PM}^2}{4 \cdot (L_d - L_q)^2} + i_{m,ref}^2} \ \ \ for \ \ (L_d < L_q)\\
  i_{d,MTPA} &= \frac{-\psi_{PM}}{2 \cdot (L_d - L_q)} + \sqrt{\frac{\psi_{PM}^2}{4 \cdot (L_d - L_q)^2} + i_{m,ref}^2} \ \ \ for \ \ (L_q < L_d)\\
  i_{q,MTPA} &= \frac{M_{ref} \cdot 2}{3 \cdot p \cdot (\psi_{PM} + (L_d - L_q) \cdot i_{d,MTPA})}\\

for :math:`\omega_{el} > \omega_c\\`:

.. math::

  i_{d,fw} &= \frac{-\psi_{PM} \cdot L_d + \sqrt{(\psi_{PM} \cdot L_d)^2 - (L_d^2 - L_q^2) \cdot (\psi_{PM}^2 + L_q^2 \cdot I_{max}^2 - \frac{V_{SV,max}^2}{\omega_{el}^2} )} }{L_d^2 - L_q^2}\\
  i_{q,fw} &= i_{q,MTPA}\\
  i_{q,fw,max} &= \sqrt{I_{max}^2 - i_{d,fw}^2}

General notes:
--------------

If the machine is not in the field weakening territory, the input ``id_ref_Ampere`` current will be used, if it is :math:`\neq 0`. 
If the machine is inside the field weakening territory, the input ``id_ref_Ampere`` will only be used, if it's value is lower than the required ``id_fw`` current from the field weakening (i.e. ``id_ref_Ampere=-5`` and ``id_fw=-2`` will result in ``id_output=-5``).
The max. current limit will still be respected in this case.

Sources
=======

.. [#Wilfling] T. Wilfling, "Regelung eines Synchronaußenläufermotors und Optimierung der Rotorstruktur zur Drehmomentsteigerung", 2021
.. [#Schroeder] D. Schröder, "Elektrische Antriebe - Regelung von Antriebssystemen", Berlin, Springer 2015
.. [#matlab] `MTPA Control Reference, Mathworks <https://de.mathworks.com/help/mcb/ref/mtpacontrolreference.html>`_