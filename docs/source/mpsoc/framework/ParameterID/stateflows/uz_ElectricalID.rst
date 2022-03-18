.. _uz_ElectricalID:

============
ElectricalID
============

This state includes an automated identification process for typical parameters of a PMSM. 
It is based on [[#Hoerner_ProjectReport2]_] and has been modified to fit into the ParameterID library of the UltraZohm.
This includes the identification of the polepairs :math:`p`, theta_offset :math:`\theta_{offset}` of an incremental encoder, stator resistance :math:`R_s`, direct inductance :math:`L_d`, quadrature inductance :math:`L_q`, permanent magnet flux :math:`\psi_{PM}` and the inertia :math:`J`. 
The control parameters of a FOC will be calculated with the identified parameters and are therefore tuned for the used machine. 
This state requires some sort of speed control.

This state does require multiple ACCEPT flags to continue, since for the identification of Lq a manual operation on the motor has to be done.

.. tikz:: Schematic overview of the ElectricalID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {\Large{\textbf{ElectricalID}}};
  \node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state};
  \node[block,fill=yellow!20,name=state1, below right = 0.5cm and 1cm of entry,drop shadow,align=center] {Automatic DutyCycle \\determination\\ \textbf{110}};
  \node[block,fill=yellow!20,name=state2, below = 2.5cm of entry,drop shadow,align=center] {Align rotor to d-axis \\Identify thetaOffset\\ \textbf{120/121}};
  \node[block,fill=yellow!20,name=state3, below = 0.5cm of state2,drop shadow,align=center] {Align rotor to q-axis \\Identify polepairs\\ \textbf{123/124}};
  \node[block,fill=yellow!20,name=state4, below = 0.5cm of state3,drop shadow,align=center] {Realign rotor to d-axis \\\textbf{125/126}};
  \node[block,fill=yellow!20,name=state5, below right = 0.5cm and 1cm of state4,drop shadow,align=center] {Automatic DutyCycle \\determination for \\step response\\ \textbf{130}};
  \node[block,fill=yellow!20,name=state6, below = 2.5cm of state4,drop shadow,align=center] {Identify $L_d, R_S$\\via step response\\ \textbf{140/141}};
  \node[block,fill=red!20,name=state7, below right = 0.5cm and 1cm of state6,drop shadow,align=center] {Lock rotor\\ in position };
  \node[block,fill=yellow!20,name=state8, below = 1cm of state7,drop shadow,align=center] {Identify $L_q$\\via step response\\ \textbf{142/143}};
  \node[block,fill=red!20,name=state9, below = 0.5cm of state8,drop shadow,align=center] {Unlock rotor};
  \node[block,fill=red!20,name=state10, below = 2.7cm of state6,drop shadow,align=center] {Treat $L_q = L_d$};
  \node[block,fill=yellow!20,name=state11, below = 2.2cm of state10,drop shadow,align=center] {Calculate FOC-\\parameters\\ \textbf{144}};
  \node[block,fill=yellow!20,name=state12, below = 0.5cm of state11,drop shadow,align=center] {Identify $\psi_{PM}$\\ \textbf{150/151}};
  \node[block,fill=yellow!20,name=state13, below = 0.5cm of state12,drop shadow,align=center] {Identify $J$ via\\ sine excitation\\ \textbf{160/161}};
  \node[block,fill=yellow!20,name=state14, below = 0.5cm of state13,drop shadow,align=center] {Recalculate FOC- \\parameters\\ \textbf{170}};
  \node[block,fill=green!20,name=exit, below = 0.5cm of state14,drop shadow,align=center] {Exit of state};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state5)(state4),inner sep=5pt,minimum width=7cm] {};
  \end{scope}
  \draw[->](entry.east) -| (state1.north);
  \node[name=DC1,above right = -0.6cm and 0.25cm of entry, align=center]{DutyCycle == 0.0}; 
  \draw[->](state1.south) |- (state2.east);
  \draw[->](entry.south) -- (state2.north);
  \node[name=DC1,below left = 0.6cm and -1.25cm of entry, align=center]{DutyCycle \\!= 0.0}; 
  \draw[->](state2.south) -- (state3.north);
  \draw[->](state3.south) -- (state4.north);
  \draw[->](state4.east) -| (state5.north);
  \node[name=DC3,above right = -0.6cm and 0.25cm of state4, align=center]{DutyCycle == 0.0}; 
  \draw[->](state5.south) |- ($(state6.east)+(0cm,0.35cm)$);
  \draw[->](state4.south) -- (state6.north);
  \node[name=DC4,below left = 0.6cm and -1.9cm of state4, align=center]{DutyCycle \\!= 0.0}; 
  \draw[->](state6.south) -- (state10.north);
  \draw[->]($(state6.east)+(0cm,-0.35cm)$) -| (state7.north);
  \node[name=LQ1,above right = -1.2cm and 0.0cm of state6, align=center]{IdentLq == 1}; 
  \node[name=LQ0,below left = 0.6cm and -1.5cm of state6, align=center]{IdentLq \\== 0\\ACCEPT}; 
  \draw[->](state7.south) -- (state8.north);
  \node[name=ACPT1,below right = 0.25cm and -0.75cm of state7, align=center]{ACCEPT}; 
  \draw[->](state8.south) -- (state9.north);
  \draw[->](state10.south) -- (state11.north);
  \draw[->](state9.south) |- (state11.east);
  \node[name=ACPT1,below right = 0.25cm and -0.75cm of state9, align=center]{ACCEPT}; 
  \draw[->](state11.south) -- (state12.north);
  \draw[->](state12.south) -- (state13.north);
  \draw[->](state13.south) -- (state14.north);
  \draw[->](state14.south) -- (exit.north);
  \end{tikzpicture}

.. _uz_PID_ElectricalID_object:

ElectricalID object
====================

.. doxygentypedef:: uz_PID_ElectricalID_t

.. _uz_PID_ElectricalIDConfig:

ElectricalID config
===================

.. doxygenstruct:: uz_PID_ElectricalIDConfig_t
  :members: 

.. _uz_PID_ElectricalIDoutput:

ElectricalID output
===================

.. doxygenstruct:: uz_PID_ElectricalID_output_t
  :members: 

.. _uz_PID_ElectricalID_functions:

ElectricalID functions
======================

.. doxygenfunction:: uz_ElectricalID_init
.. doxygenfunction:: uz_ElectricalID_step

Sources
-------

.. [#Hoerner_ProjectReport2] Automated parameter identification of fractional horsepower permanent magnet synchronous motors, Michael Hoerner, 2017