.. _uz_TwoMassID:

=========
TwoMassID
=========

Description
===========

This state includes an automated identification process for typical parameters of a two mass system. 
This state is based on [[#Gebhardt_ProjectReport2]_], but has been modified slightly to fit into the ParameterID library of the UltraZohm.
This includes the inertia of the motor and load side, as well as the stiffness and damping of the system. 
This state requires some sort of speed control. 

.. tikz:: Schematic overview of the TwoMassID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {\Large{\textbf{TwoMassID}}};
  \node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state\\\textbf{ACCEPT}};
  \node[block,fill=yellow!20,name=state1, below = 0.5cm of entry,drop shadow,align=center] {Setting \\reference speed \\\textbf{210}};
  \node[block,fill=yellow!20,name=state2, below = 0.5cm of state1,drop shadow,align=center] {Excitation via a \\PRBS sequence\\ \textbf{220}};
  \node[block,fill=yellow!20,name=state3, below = 0.5cm of state2,drop shadow,align=center] {Calculating $J, d, c$\\Reseting the integrator\\ \textbf{230}};
  \node[block,fill=green!20,name=exit, below = 0.5cm of state3,drop shadow,align=center] {Exit of state};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state3),inner sep=5pt,minimum width=7cm] {};
  \end{scope}
  \draw[->](state1.south) -- (state2.north);
  \draw[->](entry.south) -- (state1.north);
  \draw[->](state2.south) -- (state3.north);
  \draw[->](state3.south) -- (exit.north);
  \end{tikzpicture}

Necessary measurement values
============================

* i_dq
* omega_m

.. _uz_ParaID_TwoMassID_object:

TwoMassID object
================

.. doxygentypedef:: uz_ParaID_TwoMassID_t

.. _uz_ParaID_TwoMassIDConfig:

TwoMassID config
================

.. doxygenstruct:: uz_ParaID_TwoMassIDConfig_t
  :members: 

.. _uz_ParaID_TwoMassIDoutput:

TwoMassID output
================

.. doxygenstruct:: uz_ParaID_TwoMassID_output_t
  :members: 

.. _uz_ParaID_TwoMassID_functions:

TwoMassID functions
===================

.. doxygenfunction:: uz_TwoMassID_init
.. doxygenfunction:: uz_TwoMassID_step
.. doxygenfunction:: uz_TwoMassID_set_Config
.. doxygenfunction:: uz_TwoMassID_set_ActualValues
.. doxygenfunction:: uz_TwoMassID_set_GlobalConfig
.. doxygenfunction:: uz_TwoMassID_set_ControlFlags
.. doxygenfunction:: uz_TwoMassID_get_enteredTwoMassID
.. doxygenfunction:: uz_TwoMassID_get_finishedTwoMassID
.. doxygenfunction:: uz_TwoMassID_get_FOC_output
.. doxygenfunction:: uz_TwoMassID_get_output

Sources
-------

.. [#Gebhardt_ProjectReport2] Automatisierte Identifikation mechanischer Parameter in elektrisch angetriebenen Antriebssträngen, Philipp Gebhardt, 2019