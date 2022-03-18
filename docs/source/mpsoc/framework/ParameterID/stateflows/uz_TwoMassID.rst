.. _uz_TwoMassID:

=========
TwoMassID
=========

This state includes an automated identification process for typical parameters of a two mass system. 
This state is based on [[#Gebhardt_ProjectReport2]_], but has been modified slightly to fit into the ParameterID library of the UltraZohm.
This includes the inertia of the motor and load side, as well as the stiffness and damping of the system. 
This state requires some sort of speed control. 

.. tikz:: Schematic overview of the TwoMassID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {\Large{\textbf{FluxMapID}}};
  \node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state};
  \node[block,fill=yellow!20,name=state1, below = 0.5cm of entry,drop shadow,align=center] {Setting \\reference speed \\\textbf{210}};
  \node[block,fill=yellow!20,name=state2, below = 0.5cm of state1,drop shadow,align=center] {Excitation via a \\PRBS sequence\\ \textbf{220}};
  \node[block,fill=yellow!20,name=state3, below = 0.5cm of state2,drop shadow,align=center] {Calculating results\\Reseting the integrator\\ \textbf{230}};
  \node[block,fill=green!20,name=exit, below = 0.5cm of state3,drop shadow,align=center] {Exit of state};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state3),inner sep=5pt,minimum width=7cm] {};
  \end{scope}
  \draw[->](state1.south) -- (state2.north);
  \draw[->](entry.south) -- (state1.north);
  \draw[->](state2.south) -- (state3.north);
  \draw[->](state3.south) -- (exit.north);
  \end{tikzpicture}

.. _uz_PID_TwoMassID_object:

TwoMassID object
================

.. doxygentypedef:: uz_PID_TwoMassID_t

.. _uz_PID_TwoMassIDConfig:

TwoMassID config
================

.. doxygenstruct:: uz_PID_TwoMassIDConfig_t
  :members: 

.. _uz_PID_TwoMassIDoutput:

TwoMassID output
================

.. doxygenstruct:: uz_PID_TwoMassID_output_t
  :members: 

.. _uz_PID_TwoMassID_functions:

TwoMassID functions
===================

.. doxygenfunction:: uz_TwoMassID_init
.. doxygenfunction:: uz_TwoMassID_step

Sources
-------

.. [#Gebhardt_ProjectReport2] Automatisierte Identifikation mechanischer Parameter in elektrisch angetriebenen Antriebssträngen, Philipp Gebhardt, 2019