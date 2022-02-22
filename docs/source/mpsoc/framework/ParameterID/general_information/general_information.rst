.. _uz_PID_general_information:

=================================================
Explanation of the ParamterID stateflow structure
=================================================

This page explains the general structure of the ParamterID and how to use it. 

.. _PID_overview:

Overwiew
========

.. tikz:: Schematic overview of the ParameterID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(PID) {ParameterID};
  \node[block,fill=green!10,name=ControlS, below left= 0.2cm and -1cm of PID,drop shadow,minimum height=4cm] {ControlState};
  \node[block,fill=yellow!20,name=state1, above right = -1.25cm and 1cm of ControlS,drop shadow,align=center] {Identification\\state 1};
  \node[block,fill=yellow!20,name=state2, right =1cm of ControlS,drop shadow,align=center] {Identification\\state 2};
  \node[block,fill=yellow!20,name=state3, below right =-1.25cm and 1cm of ControlS,drop shadow,align=center] {Identification\\state \textbf{X}};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (ControlS) (state3),inner sep=5pt,minimum width=7cm] {};
  \end{scope}
  \node[block,name=input, left= 1.5cm of ControlS,drop shadow,minimum width=2cm, align=center] {input\\ \tiny{uz\_ParameterID\_Data\_t}};
  \node[block,name=output, right= 1.5cm of state2,drop shadow,minimum width=2cm, align=center] {output\\ \tiny{uz\_ParameterID\_Data\_t}};
  \draw[->] ([yshift=-0.3cm]state1.west) -- ([yshift=1.081cm]ControlS.east);
  \draw[<-] ([yshift=0.3cm]state1.west) -- ([yshift=1.681cm]ControlS.east);
  \draw[->] ([yshift=-0.3cm]state2.west) -- ([yshift=-0.3cm]ControlS.east);
  \draw[<-] ([yshift=0.3cm]state2.west) -- ([yshift=0.3cm]ControlS.east);
  \draw[->] ([yshift=-1.681cm]ControlS.east) -- ([yshift=-0.3cm]state3.west);
  \draw[<-] ([yshift=-1.081cm]ControlS.east) -- ([yshift=0.3cm]state3.west);
  \draw[->](input.east) -- (ControlS.west);
  \draw[-](state1.east) -| ([xshift=0.2cm]state2.east);
  \draw[-](state3.east) -| ([xshift=0.2cm]state2.east);
  \draw[->](state2.east) -- (output.west);
  \node [circle,fill,inner sep=1pt] at ($(state2.east)+(0.2cm,0)$){};
  \end{tikzpicture}

The ParameterID encapsules a ``ControlState`` and all subsequent ``Identification-states`` (short ``ID-states``). 
The ``ControlState`` is the brain of the ParameterID and controls the system, by determining which ``ID-state`` is entered next, based on the user-request and the acknowledgement flags of other states.
The individual ``ID-states`` are completely independent of each other. They only directly communicate with the ``ControlState``. 
The :ref:`uz_ParameterID_Data_t struct<uz_ParameterID_Data_struct>` is used to communicate with the ParameterID. It includes all necessary in- and outputs.  

.. _PID_signalflow:

Signalflow in the ParameterID
=============================