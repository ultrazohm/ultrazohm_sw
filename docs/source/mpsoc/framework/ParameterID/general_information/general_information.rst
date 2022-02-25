.. _uz_PID_general_information:

=================================================
Explanation of the ParamterID stateflow structure
=================================================

This page explains the general structure of the ParamterID and how to use it. 

.. _PID_overview:

Overwiew
========

.. tikz:: Schematic overview of the ParameterID signalflow
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

On top of that the ``ID-states`` inside the ParameterID are separated into two different groups:

* OfflineID states
  
    OfflineID states represents identification stateflows, which are to be used before the general operation of the motor is started. 
    They can not be executed in parallel to the general motor operation, because they take active control of the machine. 
    They, for example, tell the external control-algorithm which reference currents or speeds it is supposed to target. 
    Thus only one OfflineID-state can be active at the same time.
  
* OnlineID states

    OnlineID states represents identification stateflows, which are used during the general operation of the motor. 
    They are designed as an observer of some sorts of the machine. 
    This means, they use all existing measurement during normal operation and identify their parameters this way. 
    They therefore don't have to actively control the machine. Thus they can operate parallel to the general operation of the motor. 



.. _PID_signalflow:

Signalflow in the ParameterID
=============================

.. tikz:: Schematic overview of the ParameterID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node[block,fill=green!10,name=ControlS,drop shadow,minimum height=6.5cm] {ControlState};
  \node[block,fill=yellow!20,name=state1, right = 6cm of ControlS,drop shadow,align=center,minimum height=6.5cm,minimum width=4cm] {Identification\\state \textbf{X}};
  \node[block,name=GlobalCin, left= 0.5cm of ControlS,drop shadow,minimum width=2cm, align=center] {GlobalConfig\_in\\ \tiny{uz\_GlobalConfig\_t}};
  \node[block,name=GlobalCout, above right= -1.25cm and 1.5cm of ControlS,drop shadow,minimum width=3.5cm, align=center] {GlobalConfig\_out\\ \tiny{uz\_GlobalConfig\_t}};
  \node[block,name=ControlFlags, above right= -3cm and 1.5cm of ControlS,drop shadow,minimum width=3.5cm, align=center] {ControlFlags\\ \tiny{uz\_ControlFlags\_t}};
  \node[block,name=ElecConfig, above right= -4.75cm and 1.5cm of ControlS,drop shadow,minimum width=3.5cm, align=center] {Individual Config\\ \tiny{uz\_StateIDConfig\_t}};
  \node[block,name=ActValues, above right= -6.5cm and 1.5cm of ControlS,drop shadow,minimum width=3.5cm, align=center] {ActualValues\\ \tiny{uz\_ActualValues\_t}};
  \node[block,name=input, left= 2cm of GlobalCin,drop shadow,minimum width=2cm, align=center] {input\\ \tiny{uz\_ParameterID\_Data\_t}};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(ControlS)(GlobalCin) (state1),inner sep=5pt,minimum width=18cm,minimum height=10.5cm] {};
  \end{scope}
  \node[block,name=output, right= 1cm of ParameterID,drop shadow,minimum width=2cm, align=center] {output\\ \tiny{uz\_ParameterID\_Data\_t}};
  \node[block,name=stateoutput, below= -5.5cm of state1,drop shadow,minimum width=2cm, align=center] {individual output\\ \tiny{uz\_StateID\_output\_t}};
  \node[block,name=FOCoutput, below= -2.5cm of state1,drop shadow,minimum width=2cm, align=center] {Controller output\\ \tiny{uz\_PID\_Controller}\\ \tiny{   \_Parameters\_output\_t}};
  \node[above  =1.2cm of GlobalCout](entered){enteredStateID};
  \node[above  =0.2cm of GlobalCout](finished){finishedStateID};
  \node[above  =0.2cm of ParameterID](finished){\large{\textbf{ParameterID}}};
  \draw[->](input.east) -- (GlobalCin.west);
  \draw[->](GlobalCin.east) -- (ControlS.west);
  \node [circle,fill,inner sep=1pt] at ([xshift=-0.5cm]GlobalCin.west){};
  \node [circle,fill,inner sep=1pt] at ([xshift=-1cm]ActValues.west) {};
  \draw[->](GlobalCout.east) |- ([yshift=2.64cm]state1.west);
  \draw[->](ControlFlags.east) |- ([yshift=0.89cm]state1.west);
  \draw[->](ElecConfig.east) |- ([yshift=-0.86cm]state1.west);
  \draw[->](ActValues.east) |- ([yshift=-2.61cm]state1.west);
  \draw[->]([yshift=2.64cm]ControlS.east) |- (GlobalCout.west);
  \draw[->]([yshift=0.89cm]ControlS.east) |- (ControlFlags.west);
  \draw[->]([xshift=-1cm]ActValues.west) |- (ElecConfig.west);
  \draw[->]([xshift=-1cm]ActValues.west) |- (ActValues.west);
  \draw[-]([xshift=-0.5cm]GlobalCin.west) |- ([xshift=-0.5cm,yshift=-4cm]GlobalCin.west) -| ([xshift=-1cm]ActValues.west);
  \draw[-](stateoutput.east) -| ([xshift=-1.5cm]output.west);
  \draw[-](FOCoutput.east) -| ([xshift=-1.5cm]output.west);
  \draw[->]([xshift=-1.5cm]output.west) -- (output.west);
  \draw[->]([xshift=-0.3cm]state1.north) |- ([xshift = -0.5cm, yshift = 3.5cm]ControlS.west) |- ([yshift = 2.5cm]ControlS.west);
  \draw[->]([xshift=0.3cm]state1.north) |- ([xshift = -1cm, yshift = 4.5cm]ControlS.west) |- ([yshift = 2cm]ControlS.west);
  \node [circle,fill,inner sep=1pt] at ([xshift=-1.5cm]output.west) {};
  \end{tikzpicture}

The ParameterID has three global structs, which are shared inputs for all identification states. For detailed information about these structs, click on the appropriate hyperlink. 
These are the following:

  * :ref:`ActualValues struct<uz_Actual_values_struct>`, which carries all the measurement values
  * :ref:`GlobalConfig struct<uz_Global_config_struct>`, which carries general configuration variables, which affect multiple or all states 
  * :ref:`ControlFlags struct<uz_Control_flags_struct>`, which carries all flags to enable and disable the individual states
   
On top of that, each unique ``ID-state`` has its own individual structs and signals:
  * ``uz_StateIDConfig_t`` (i.e. for ElectricalID :ref:`uz_ElectricalIDConfig_t<uz_PID_ElectricalIDConfig>`), which is meant for all configuration values, which are unique to this specific ``ID-state``.
  * ``uz_StateID_output_t`` (i.e. for ElectricalID :ref:`uz_ElectricalID_output_t<uz_PID_ElectricalIDoutput>`), which is meant for the identified output variables and supporting variables
  * ``enteredStateID`` flag, which signals that the state has been entered
  * ``finishedStateID`` flag, which signals that the ``ID-state`` is finished and another can be started
