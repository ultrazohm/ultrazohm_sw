.. _uz_FluxMapID:

=========
FluxMapID
=========

Description
===========

This state includes an process for FluxMap identification. 
It is based on [[#Hoerner_Masterthesis]_] and has been modified to fit into the ParameterID library of the UltraZohm.
The desired range of the identified flux maps can be set in the d- and q-axis, with an input for the stepsize as well. 
From these input parameters, this state will create a rectangular grid. 
Each point of this grid will be set and reference currents will be given to an external current controller. 
This state needs some sort of current controller to work properly. 
It does NOT measure the needed signals to calculate the flux maps in each point. 
It only controls the triggering of the operating points. 
The necessary measurement vales can either be captured via the :ref:`JavaScope` or an external measurement device.
For this purpose a trigger (when ``activeState = 403``) signals the point of time, at which the measurement of this operating point can take place. 

During operation, it is possible to automatically determine the current winding temperature, via identifying the current stator resistance and comparing it to a reference value at a set temperature.
This guarantees that the measurements are only recorded when the motor has the same winding temperature. This can be turned off. The ``ID-state`` simply assumes then, that the winding temperature is constant. 

.. tikz:: Schematic overview of the FluxMapID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {\Large{\textbf{FluxMapID}}};
  \node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state\\\textbf{ACCEPT}};
  \node[block,fill=red!20,name=state8, below = 0.5cm of entry,drop shadow,align=center] {Set load machine\\ to fixed speed };
  \node[block,fill=yellow!20,name=state1, below = 0.5cm of state8,drop shadow,align=center] {Calculate all\\different operating\\points \\\textbf{401}};
  \node[block,fill=yellow!20,name=state2, below = 0.5cm of state1,drop shadow,align=center] {Set new \\reference point\\ \textbf{402}};
  \node[block,fill=yellow!20,name=state3, below = 0.5cm of state2,drop shadow,align=center] {Collect data\\ \textbf{403}};
  \node[block,fill=yellow!20,name=state4, below = 0.5cm of state3,drop shadow,align=center] {Wait for collection \\to finish\\\textbf{404}};
  \node[block,fill=yellow!20,name=state5, below = 0.5cm of state4,drop shadow,align=center] {Reset integrators \\\textbf{450}};
  \node[block,fill=yellow!20,name=state6, right = 1.5cm of state2,drop shadow,align=center] {Cooling the machine \\ $i_d, i_q = 0A$\\\textbf{410}};
  \node[block,fill=yellow!20,name=state7, below = 0.5cm of state6,drop shadow,align=center] {Heating the machine \\$i_d, i_q = max$\\\textbf{420}};
  \node[block,fill=green!20,name=exit, below = 0.5cm of state5,drop shadow,align=center] {Exit of state};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state3)(state7),inner sep=5pt,minimum width=12cm] {};
  \end{scope}
  \draw[->](state1.south) -- (state2.north);
  \draw[->](entry.south) -- (state8.north);
  \draw[->](state8.south) -- (state1.north);
  \node[name=ACPT,above right = -0.0cm and -1.5cm of state1, align=center]{start\_FM\_ID == true \&\& \textbf{ACCEPT}}; 
  \draw[->](state2.south) -- (state3.north);
  \draw[->](state3.south) -- (state4.north);
  \draw[->](state5.south) -- (exit.north);
  \draw[->](state4.east) -| (state7.south);
  \draw[->](state4.east) -| ($(state6.east)+(1cm,0cm)$) -- (state6.east);
  \draw[->](state6.west) -- (state2.east);
  \draw[-](state7.west) -| ($(state2.east)+(1cm,0cm)$) -- (state2.east);
  \draw[->](state4.west) -| ($(state2.west)-(1.3cm,0cm)$) -- (state2.west);
  \draw[->](state4.south) -- (state5.north);
  \node[name=identR1,below right = -1.35cm and 0.25cm of state4, align=center]{identR == 1}; 
  \node[name=identR0,above left = 0.5cm and -0.5cm of state4, align=center]{identR \\== 0}; 
  \end{tikzpicture}

Necessary measurement values
============================

* i_dq
* v_dq

.. _uz_PID_FluxMapID_object:

FluxMapID object
================

.. doxygentypedef:: uz_PID_FluxMapID_t

.. _uz_PID_FluxMapIDConfig:

FluxMapID config
================

.. doxygenstruct:: uz_PID_FluxMapIDConfig_t
  :members: 

.. _uz_PID_FluxMapIDoutput:

FluxMapID output
================

.. doxygenstruct:: uz_PID_FluxMapID_output_t
  :members: 

.. _uz_PID_FluxMapID_functions:

FluxMapID functions
===================

.. doxygenfunction:: uz_FluxMapID_init
.. doxygenfunction:: uz_FluxMapID_step

Sources
-------

.. [#Hoerner_Masterthesis] Automatisierte Identifikation nichtlinearer Flusskennfelder permanenterregter Synchronmaschinen, Michael Hoerner, 2018