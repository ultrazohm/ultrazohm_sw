.. _uz_ElectricalID:

============
ElectricalID
============

Description
===========

This state includes an automated identification process for typical parameters of a PMSM. 
It is based on [[#Hoerner_ProjectReport2]_] and has been modified to fit into the ParameterID library of the UltraZohm.
This includes the identification of the theta_offset :math:`\theta_{offset}` of an incremental encoder, stator resistance :math:`R_s`, 
direct inductance :math:`L_d`, quadrature inductance :math:`L_q`, permanent magnet flux :math:`\psi_{PM}` and the inertia :math:`J`. 
The control parameters of a FOC will be calculated with the identified parameters and are therefore tuned for the used machine. 
This state requires some sort of speed control.

This state does require multiple ACCEPT flags to continue, since for the identification of :math:`L_q` a manual operation on the motor has to be done.

.. tikz:: Schematic overview of the ElectricalID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {\Large{\textbf{ElectricalID}}};
  \node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state\\\textbf{ACCEPT}};
  \node[block,fill=yellow!20,name=state1, below right = 0.5cm and 1cm of entry,drop shadow,align=center] {Automatic DutyCycle \\determination\\ \textbf{110}};
  \node[block,fill=yellow!20,name=state2, below = 2.5cm of entry,drop shadow,align=center] {Align rotor to d-axis \\Identify $\theta_\mathrm{offset}$\\ \textbf{120/121}};
  \node[block,fill=yellow!20,name=state4, below = 0.5cm of state2,drop shadow,align=center] {Realign rotor to d-axis \\\textbf{125/126}};
  \node[block,fill=yellow!20,name=state5, below right = 0.5cm and 1cm of state4,drop shadow,align=center] {Automatic DutyCycle \\determination for \\step response\\ \textbf{130/131}};
  \node[block,fill=yellow!20,name=state6, below = 2.5cm of state4,drop shadow,align=center] {Identify $L_\mathrm d, R_\mathrm S$\\via step response\\ \textbf{140/141}};
  \node[block,fill=red!20,name=state7, below right = 0.5cm and 1cm of state6,drop shadow,align=center] {Lock rotor\\ in position };
  \node[block,fill=yellow!20,name=state8, below = 1cm of state7,drop shadow,align=center] {Identify $L_\mathrm q$\\via step response\\ \textbf{142/143}};
  \node[block,fill=red!20,name=state9, below = 0.5cm of state8,drop shadow,align=center] {Unlock rotor};
  \node[block,fill=red!20,name=state10, below = 2.7cm of state6,drop shadow,align=center] {Treat $L_\mathrm q = L_\mathrm d$};
  \node[block,fill=yellow!20,name=state11, below = 2.2cm of state10,drop shadow,align=center] {Calculate FOC-\\parameters\\ \textbf{144}};
  \node[block,fill=yellow!20,name=state12, below = 0.5cm of state11,drop shadow,align=center] {Identify $\psi_\mathrm {PM}$\\ \textbf{150/151}};
  \node[block,fill=yellow!20,name=state13, below = 0.5cm of state12,drop shadow,align=center] {Identify $J$ via\\ sine excitation\\ \textbf{160/161}};
  \node[block,fill=yellow!20,name=state14, below = 0.5cm of state13,drop shadow,align=center] {Recalculate FOC- \\parameters\\ \textbf{170}};
  \node[block,fill=green!20,name=exit, below = 0.5cm of state14,drop shadow,align=center] {Exit of state};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state5)(state4),inner sep=5pt,minimum width=7cm] {};
  \end{scope}
  \draw[->](entry.east) -| (state1.north);
  \path ([xshift=-2.3cm,yshift=1cm]entry.east) -- (state1.north) node[midway, align=center] (DC1){DutyCycle == 0.0};
  \path ([xshift=-2.3cm,yshift=1cm]state4.east) -- (state5.north) node[midway, align=center] (DC2){DutyCycle == 0.0};
  \draw[->](state1.south) |- (state2.east);
  \draw[->](entry.south) -- (state2.north);
  \path (state2.north) -- (entry.south) node[midway,align=center] (DC1) {DutyCycle \\!= 0.0};
  \draw[->](state2.south) -- (state4.north);
  \draw[->](state4.east) -| (state5.north);
  \draw[->] (state5.south) |- ([yshift=0.35cm] state6.east);
  \draw[->](state4.south) -- (state6.north);
  \path (state6.north) -- (state4.south) node[midway,align=center] (DC4) {DutyCycle \\!= 0.0};
  \draw[->](state6.south) -- (state10.north);
  \draw[->]([yshift=-0.35cm] state6.east)-| (state7.north);
  \path([xshift=-2cm, yshift=0.3cm]state6.east) -- (state7.north) node [midway, align=center] (LQ1) {IdentLq == 1};
  \path(state10.north) -- (state6.south) node [midway, align=center] (LQ0) {IdentLq \\== 0\\\textbf{ACCEPT}};
  \draw[->](state7.south) -- (state8.north);
  \path (state7.south) -- (state8.north) node [midway, align=center] (ACPT1){\textbf{ACCEPT}};
  \draw[->](state8.south) -- (state9.north);
  \draw[->](state10.south) -- (state11.north);
  \draw[->](state9.south) |- (state11.east);
  \path (state9.south) -- ([yshift=-2cm]state9.north) node [midway, align=center] (ACPT2) {\textbf{ACCEPT}}; 
  \draw[->](state11.south) -- (state12.north);
  \draw[->](state12.south) -- (state13.north);
  \draw[->](state13.south) -- (state14.north);
  \draw[->](state14.south) -- (exit.north);
  \end{tikzpicture}

Necessary measurement values
============================

* V_abc
* I_abc
* i_dq
* v_dq
* omega_m
* omega_el
* theta_m

.. _uz_ParaID_ElectricalID_object:

ElectricalID object
====================

.. doxygentypedef:: uz_ParaID_ElectricalID_t

.. _uz_ParaID_ElectricalIDConfig:

ElectricalID config
===================

.. doxygenstruct:: uz_ParaID_ElectricalIDConfig_t
  :members: 

.. _uz_ParaID_ElectricalIDoutput:

ElectricalID output
===================

.. doxygenstruct:: uz_ParaID_ElectricalID_output_t
  :members: 

.. _uz_ParaID_ElectricalID_functions:

ElectricalID functions
======================

.. doxygenfunction:: uz_ElectricalID_init
.. doxygenfunction:: uz_ElectricalID_step
.. doxygenfunction:: uz_ElectricalID_set_Config
.. doxygenfunction:: uz_ElectricalID_set_ActualValues
.. doxygenfunction:: uz_ElectricalID_set_GlobalConfig
.. doxygenfunction:: uz_ElectricalID_set_ControlFlags
.. doxygenfunction:: uz_ElectricalID_get_enteredElectricalID
.. doxygenfunction:: uz_ElectricalID_get_finishedElectricalID
.. doxygenfunction:: uz_ElectricalID_get_FOC_output
.. doxygenfunction:: uz_ElectricalID_get_output

Sources
-------

.. [#Hoerner_ProjectReport2] Automated parameter identification of fractional horsepower permanent magnet synchronous motors, Michael Hoerner, 2017