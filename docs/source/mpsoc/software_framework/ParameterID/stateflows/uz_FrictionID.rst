.. _uz_FrictionID:

==========
FrictionID
==========

Description
===========

This state includes an automated identification process for different friction/torque parameters. 
It is based on [[#Gebhardt_ProjectReport1]_] and has been modified to fit into the ParameterID library of the UltraZohm.
The breakaway torque :math:`M_{break}`, coloumb torque :math:`M_{coul}` and viscous friction torque :math:`d_{fric}` will be identified. 
This state requires some sort of speed control. 

.. tikz:: Schematic overview of the FrictionID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {\Large{\textbf{FrictionID}}};
  \node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state\\\textbf{ACCEPT}};
  \node[block,fill=yellow!20,name=state1, below = 0.5cm of entry,drop shadow,align=center] {Determine $M_{break}$\\by contionously\\increasing the torque \\\textbf{310/311/312}};
  \node[block,fill=yellow!20,name=state2, below = 0.5cm of state1,drop shadow,align=center] {Reset integrators\\Switch to SpeedControl\\ \textbf{320}};
  \node[block,fill=yellow!20,name=state3, below = 0.5cm of state2,drop shadow,align=center] {Identify $M_{coul}, d_{fric}$\\by cycling through\\different speeds\\ \textbf{330/331/332}};
  \node[block,fill=yellow!20,name=state4, below = 0.5cm of state3,drop shadow,align=center] {Reset integrators \\Transmit friction curve\\\textbf{340}};
  \node[block,fill=yellow!20,name=state5, below = 0.5cm of state4,drop shadow,align=center] {Wait for transmisstion\\to finish \\\textbf{341}};
  \node[block,fill=green!20,name=exit, below = 0.5cm of state5,drop shadow,align=center] {Exit of state};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state3),inner sep=5pt,minimum width=7cm] {};
  \end{scope}
  \draw[->](state1.south) -- (state2.north);
  \draw[->](entry.south) -- (state1.north);
  \draw[->](state2.south) -- (state3.north);
  \draw[->](state3.south) -- (state4.north);
  \draw[->](state4.south) -- (state5.north);
  \draw[->](state5.south) -- (exit.north);
  \end{tikzpicture}

Necessary measurement values
============================

* i_dq
* omega_m


.. _uz_PID_FrictionID_object:

FrictionID object
=================

.. doxygentypedef:: uz_PID_FrictionID_t

.. _uz_PID_FrictionIDConfig:

FrictionID config
=================

.. doxygenstruct:: uz_PID_FrictionIDConfig_t
  :members: 

.. _uz_PID_FrictionIDoutput:

FrictionID output
=================

.. doxygenstruct:: uz_PID_FrictionID_output_t
  :members: 

.. _uz_PID_FrictionID_functions:

FrictionID functions
====================

.. doxygenfunction:: uz_FrictionID_init
.. doxygenfunction:: uz_FrictionID_step

Sources
-------

.. [#Gebhardt_ProjectReport1] Automatic identification of the frictional behaviour of permanent magnet synchronous machines, Philipp Gebhardt, 2018