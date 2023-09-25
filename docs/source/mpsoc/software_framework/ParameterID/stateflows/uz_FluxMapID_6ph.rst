.. _uz_FluxMapID_6ph:

=============
FluxMapID 6ph
=============

Description
===========

This state can be used to measure flux linkage maps.
Since the 6ph machine has three subsystems, flux linkage maps can be measured for each of them.
The desired range of the identified flux maps can be set in the d- and q-axis, with an input for the stepsize as well. 
From these input parameters, this state will create a rectangular grid. 
Each point of this grid will be set and reference currents will be given to an external current controller. 
This state needs some a current controller to set the reference currents and controllers to suppress undesired currents in the other systems.

During operation, it is possible to automatically determine the current winding temperature, via identifying the current stator resistance and comparing it to a reference value at a set temperature.
This guarantees that the measurements are only recorded when the motor has the same winding temperature. This can be turned off. The ``ID-state`` simply assumes then, that the winding temperature is constant. 
Alternatively a temperature measurement can be used.

Stateflow
=========

To start the FM ID, the desired subsystem has to be selected and confirmed with ``ACCEPT``.
Current control with zero setpoints is now active and the load machine can be set to the fixed speed.
To use the logging, select ``Log SlowData`` and ``allow ext. logging``.
The measurement is started by clicking ``Start FM ID``.

After finishing or to cancel the measurement, unselect ``Start FM ID``.
Now the current control is set to zero again.
The load machine can be stopped and after it is at standstill and all currents are zero, unselect the subsystem.
Now the ID state in back in idle and a new subsystem to identify can be selected.

.. tikz:: Schematic overview of the FluxMapID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
	\node(PID) {\Large{\textbf{FluxMapID}}};
	\node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state\\ \textbf{400}};
	\node[block,fill=red!20,name=state01, below = 0.5cm of entry,drop shadow,align=center] {Select subsystem to identify\\ \textbf{dq, xy, zero} then\\ \textbf{ACCEPT}};
	\node[block,fill=red!20,name=state8, below = 0.5cm of state01,drop shadow,align=center] {Set load machine\\ to fixed speed\\ \textbf{start FM ID} };
	\node[block,fill=yellow!20,name=state1, below = 0.5cm of state8,drop shadow,align=center] {Calculate all\\different operating\\points \\\textbf{401}};
	\node[block,fill=yellow!20,name=state2, below = 0.5cm of state1,drop shadow,align=center] {Set new \\reference point\\ \textbf{402}};
	\node[block,fill=yellow!20,name=state3, below = 0.5cm of state2,drop shadow,align=center] {Collect data\\ \textbf{403}};
	\node[block,fill=yellow!20,name=state4, below = 0.5cm of state3,drop shadow,align=center] {Wait for collection \\to finish\\\textbf{404}};
	\node[block,fill=yellow!20,name=state5, below = 0.5cm of state4,drop shadow,align=center] {Wait exit\\\textbf{405}};
	\node[block,fill=yellow!20,name=state6, right = 1.5cm of state2,drop shadow,align=center] {Cooling the machine \\ $i_\mathrm d, i_\mathrm q = 0A$\\\textbf{410}};
	\node[block,fill=yellow!20,name=state7, below = 0.5cm of state6,drop shadow,align=center] {Heating the machine \\$i_\mathrm d, i_\mathrm q = max$\\\textbf{420}};
	\node[block,fill=red!20,name=exit1, below = 0.5cm of state5,drop shadow,align=center] {unselect \textbf{start FM ID}};
	\node[block,fill=red!20,name=exit2, below = 0.5cm of exit1,drop shadow,align=center] {set load machine\\to zero};
	\node[block,fill=red!20,name=exit3, below = 0.5cm of exit2,drop shadow,align=center] {unselect \textbf{dq, xy, zero}};
	\draw[->](state1.south) -- (state2.north);
	\draw[->](entry.south) -- (state01.north);
	\draw[->](state01.south) -- (state8.north);
	\draw[->](state8.south) -- (state1.north);
	\draw[->](state2.south) -- (state3.north);
	\draw[->](state3.south) -- (state4.north);
	\draw[->](state4.east) -| (state7.south);
	\draw[->](state4.east) -| ($(state6.east)+(1cm,0cm)$) -- (state6.east);
	\draw[->](state6.west) -- (state2.east);
	\draw[-](state7.west) -| ($(state2.east)+(1cm,0cm)$) -- (state2.east);
	\draw[->](state4.west) -| ($(state2.west)-(1.3cm,0cm)$) -- (state2.west);
	\draw[->](state4.south) -- (state5.north);
	\draw[->](state5.south) -- (exit1.north);
	\draw[->](exit1.south) -- (exit2.north);
	\draw[->](exit2.south) -- (exit3.north);
	\node[name=identR1,below right = -1.35cm and 0.25cm of state4, align=center]{identR == 1}; 
	\path([xshift=-2cm,yshift=-1cm]state2.west) -- (state4.west) node [midway, align=center] (identR1) {identR \\== 0};
	\draw[->](exit3.west)-| ($(state3.west)+(-2cm,0cm)$) |- (entry.west);
	\begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit3)(state3)(state7),inner sep=5pt,minimum width=12cm] {};
  \end{scope}
  \end{tikzpicture}

Winding configuration
=====================

For the identification of the subsystems ``dq`` and ``xy``, the machine should be connected in 2N configuration to avoid zero system currents.
To identify ``zero`` system, connect the windings as follows and provide the voltage measurements between the phase ``a`` and ``c`` terminals of both subsets.

.. figure:: zero_system_connection.png
   :width: 800px
   :align: center

   Zero system connection


Necessary measurement values
============================

* i_dq_6ph
* v_dq_6ph
* theta_el
* u_a1c1 (zero system)
* u_a2c2 (zero system)


Function references
===================

Structs
-------

.. doxygentypedef:: uz_ParaID_FluxMapID_6ph_t

The config and output structs are shared.

:ref:`uz_ParaID_FluxMapIDConfig`

:ref:`uz_ParaID_FluxMapIDoutput`

Functions
---------

.. doxygenfunction:: uz_FluxMapID_6ph_init
.. doxygenfunction:: uz_FluxMapID_6ph_step
.. doxygenfunction:: uz_get_FluxMapID_6ph_finished
.. doxygenfunction:: uz_get_FluxMapID_6ph_entered
.. doxygenfunction:: uz_get_FluxMapID_6ph_FOCoutput
.. doxygenfunction:: uz_get_FluxMapID_6ph_output

Sources
=======
