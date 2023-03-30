.. _uz_OnlineID:

========
OnlineID
========

Description
===========

This stateflow is used to detect special transient states and to gather measuring data in these states. 
It is based on [[#Gebhardt_Masterthesis]_ , [#Hufnagel_Masterthesis]_ ] and has been modified to fit into the ParameterID library of the UltraZohm.
It functions as an indefinite loop and continuously identifies its parameters. 
This is done to identify the parameters of the linear pmsm model. 
This includes the stator resistance :math:`R_s`, direct inductance :math:`L_d`, quadrature inductance :math:`L_q` and permanent magnet flux :math:`\psi_{PM}`. The flux maps :math:`\psi_d` and :math:`\psi_q` can be identified aswell. 
With each new operating point the relevant signals are measured and the flux in the specific operating point is calculated. 
Up to 100 unique values will be stored in an array, which will later be cleaned up with external functions. 
In contrast to the FluxMapID state, this state does not actively control the machine via reference currents(except the addition of a injection signal with low amplitude/frequency on top of the reference d-axis current).
Thus it measures and calculates the flux in the operating points. 

To assist the identification of the flux maps an :ref:`uz_AutoRefCurrents` does exist. It is an external stateflow purposefully designed for the OnlineID state. 
It gives out reference currents of a circular determined current map to quickly cycle through different operating points and therefore identify flux map values over a wide operating point.

.. tikz:: Schematic overview of the FrictionID
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}
  \tikzstyle{block} = [rectangle, draw, fill=yellow!20, align=center,
    text width=5em, text centered, rounded corners, drop shadow, minimum height=8em]
  \node [block, minimum width=9.52in,align=center,minimum height=5.3in,fill=blue!10](Online) {};
  \node[below,align=center]at(Online.north){\textbf{\LARGE{OnlineID}}};
  \node[block,below right=8em and 0.5em of Online.north west,minimum height= 3.4in, minimum width=1.5in](steady){};
  \node[below,align=center]at(steady.north)(eval){Evaluation of\\ steady states};
  \node[block,above=5em of eval,align=center, name=entry,anchor=north, minimum height=1em, text width=1.25in,fill=green!20] {Entry of state\\\textbf{ACCEPT}};
  \node[above,align=center]at(steady.south){\textbf{501}};
  \node[block,below left=9em and 0em of eval.north, align=center, anchor=north, minimum height=1em, text width=1.25in,fill=green!20](buffer){Save actual   values of\\ $i_\mathrm q$, $i_\mathrm d$, $u_\mathrm d$, $u_\mathrm q$ \& $\omega_\mathrm {el}$ in shift registers};
  \node[block,above=1em of buffer.north, align=center, minimum height=5.3em, text width=1.25in,fill=green!20](Drehzahl){Evaluation, if \\ $ n \geq n_\mathrm{lim}$};
  \node[block,below=1em of buffer,align=center, anchor=north, minimum height=1em, text width=1.25in,fill=green!20](switcher){Shift registry by one entry};
  \draw[->]($(switcher.north)+(1em,0)$)to node[right,align=left]{}($(buffer.south)+(1em,0)$);
  \draw[<-]($(switcher.north)-(1em,0)$)to node[right,align=left]{}($(buffer.south)-(1em,0)$);
  \draw[->]($(buffer.north)+(1em,0em)$)to node[right,align=left]{}($(Drehzahl.south)+(1em,0em)$);
  \draw[<-]($(buffer.north)-(1em,0em)$)to node[right,align=left]{}($(Drehzahl.south)-(1em,0em)$);
  \node[block,text width=7.5em,minimum width=1.0in,right=10em of steady.north east, anchor=north west ](Stromgrenze){Evaluation, if \\ $  \sqrt{i_\mathrm d^2+i_\mathrm q^2} \leq I_\mathrm{lim}$};
  \draw[->](steady.east|-Stromgrenze)to node[above, align=center]{For \\steady state\\ condition}(Stromgrenze);
  \node[block,below right=0.0em and 10em of Stromgrenze.north east, minimum width=3.05in](linParablock){};
  \node[block,above right=-2.8em and 10.45em of Stromgrenze.east,fill=green!20,text width=1.25in, minimum height=0.75in](inject){Inject\\ rectangle- \\signal $i_*{d,rec}$};
  \node[block,below right=5.65em and 1em of linParablock.south,text width=1.25in ,fill=yellow!20](linear){Identify $R_\mathrm s$, $L_\mathrm d$, $L_\mathrm q$, $\psi_\mathrm {PM}$ through measurement values from the signal injection \\  \textbf{502}};
  \node[below,align=center]at(linParablock.north){\textbf{502}};
  \node[block,right=1em of inject.east, text width=1.25in, minimum height=0.75in,fill=green!20 ](check){Evaluation, if\\steady state  \\has been left};
  \draw[->]($(inject.east)+(0em,1em)$)to node[right,align=left]{}($(check.west)+(0em,1em)$);
  \draw[<-]($(inject.east)-(0em,1em)$)to node[right,align=left]{}($(check.west)-(0em,1em)$);
  \draw[->, bend angle=20, bend right](linParablock.north)to node[below,align=center]{Steady state \\ has been left}(steady.north east);
  \draw[->](Stromgrenze.east)to node[above,align=left]{fulfilled}(linParablock.west);
  \draw[->](linParablock.south-|linear)to node[right,align=center]{Sucessfully\\injected}(linear.north);
  \draw[->](Stromgrenze.south west)to node[above,align=center]{Not fulfilled}(steady.south east|-Stromgrenze.south);
  \node[block, left=10em of linear.west,text width=1.25in ](flux){Calculate $\psi_\mathrm d$ and $\psi_\mathrm q$ from shift-\\registervalues  and fill $\Psi$ \\\textbf{503}};
  \draw[->](linear.west)to node[above,align=center]{Identification\\inside the\\ current limit}(flux.east);
  \draw[->](Stromgrenze.south east)to node[above,align=center]{After\\defined\\time }(linParablock.south west);
  \draw[->](linear.north west) |- (steady.east)node[below right=0em and 13em,align=center]{Identification outside \\the current limit};
  \node[block,left=3em of flux, anchor=east, ](Diff){Calulate $\vartheta_W $ and \\fill $\Delta \Psi$\\\textbf{504}};
  \draw[->](flux.west)to node[below,align=left]{ }(Diff.east);
  \node[block,left=3em of Diff, anchor=east, ](Entf){Delete shift-\\register\\values};
  \draw[->](Diff.west)to node[below,align=left]{ }(Entf.east);
  \draw[<-](steady.east|-Entf)to node[below,align=left]{}(Entf.west);
  \draw[->](entry.south) -- (eval.north);
  \end{tikzpicture}

Necessary measurement values
============================

* i_dq
* v_dq
* omega_m
* omega_el

.. _uz_ParaID_OnlineID_object:

OnlineID object
===============

.. doxygentypedef:: uz_ParaID_OnlineID_t

.. _uz_ParaID_OnlineIDConfig:

OnlineID config
===============

.. doxygenstruct:: uz_ParaID_OnlineIDConfig_t
  :members: 

.. _uz_ParaID_OnlineIDoutput:

OnlineID output
===============

.. doxygenstruct:: uz_ParaID_OnlineID_output_t
  :members: 

.. _uz_ParaID_OnlineID_functions:

OnlineID functions
==================

.. doxygenfunction:: uz_OnlineID_init
.. doxygenfunction:: uz_OnlineID_step
.. doxygenfunction:: uz_OnlineID_CleanPsiArray
.. doxygenfunction:: uz_OnlineID_CalcFluxMaps
.. doxygenfunction:: uz_OnlineID_AutoRefCurrents_step
.. doxygenfunction:: uz_OnlineID_set_Config
.. doxygenfunction:: uz_OnlineID_set_ActualValues
.. doxygenfunction:: uz_OnlineID_set_GlobalConfig
.. doxygenfunction:: uz_OnlineID_set_ControlFlags
.. doxygenfunction:: uz_OnlineID_set_cleaned_psi_array
.. doxygenfunction:: uz_OnlineID_set_AutoRefCurrents_Config
.. doxygenfunction:: uz_OnlineID_set_AutoRefCurrents_GlobalConfig
.. doxygenfunction:: uz_OnlineID_set_AutoRefCurrents_ControlFlags
.. doxygenfunction:: uz_OnlineID_get_InterpMeshGrid_FluxMapData
.. doxygenfunction:: uz_OnlineID_get_enteredOnlineID
.. doxygenfunction:: uz_OnlineID_get_output

Sources
-------

.. [#Gebhardt_Masterthesis] Automatisierte Online-Identifikation von Systemparametern permanenterregter Synchronmaschinen zur Nachführung im geregelten Betrieb, Philipp Gebhardt, 2020
.. [#Hufnagel_Masterthesis] Optimierte Online-Identifizierung von Flusskennfeldernbei nichtlinearen PMSM über einen weiten Betriebsbereich, Dennis Hufnagel, 2021