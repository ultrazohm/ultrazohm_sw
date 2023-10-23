.. _uz_ElectricalID_6ph:

================
ElectricalID 6ph
================

Description
===========

This states is based on :ref:`uz_ElectricalID` and expanded to six-phase PMSM.
It includes the identification of the offset angle :math:`\theta_{offset}` of an angular position sensor either with a basic or a more advanced method.
Furthermore, stator resistance :math:`R_s`, direct inductance :math:`L_d`, quadrature inductance :math:`L_q`, and additional system inductances (:math:`L_{x1},L_{y1},L_{z1},L_{z2}`) will be determined. 
For the permanent magnet flux :math:`\psi_{PM}` either only the fundamental component can be identified or additionally the third, fifth, seventh and ninth orders if a prime mover is available.
On top, the inertia :math:`J` can be identified.
The control parameters of a FOC will be calculated with the identified parameters and are therefore tuned for the used machine. 

The effictiveness of the identification methods is researched in [[#param_ID_paper_SF]_] and [[#hoppe_pab2]_].

Depending on the parameters to determine, this state may require some sort of speed control or an external machine to drive the machine under testing.

This state does require multiple ACCEPT flags to continue since, for the identification of :math:`L_q`, manual operation on the motor is required. 

User Options
============

The user has to make several settings, which are explained in the following table.

.. csv-table:: User Settings
   :file: uz_ElectricalID_6ph_set.csv
   :widths: 50 20 20 150
   :header-rows: 1


Furthermore, the user has several path options for the stateflow (see also stateflow overview chart).
The options are chosen via buttons:

``IdentLq``: If :math:`L_q` should be identified, the user has to lock the rotor during this time. Otherwise (e.g. if no rotor brake is available), :math:`L_q=L_d` will be assumed.

``ExtendedPsi``: If no load machine is connected, the machine will drive itself up to speed, to determine :math:`\psi_{PM,1}`. If the button is active, the ParameterID will ask the user to set the machine to a specific speed for it to make an FFT. With that, :math:`\psi_{PM1,3,5,7,9}` can be determined. Since usually a filtered voltage measurement is used, the filters's details have to be given to the ParameterID at initialization in order to compensate for them.

``ExtendedOffset``: While an initial offset angle will always be determined with simple voltage steps, the user can activate this option to employ the :ref:`uz_encoder_offset_estimation` for a better result.

Stateflow Overview
==================

.. tikz:: Stateflow overview
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
	\tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
	\node(PID) {\Large{\textbf{ElectricalID}}};
	\node[block,fill=green!20,name=entry, below = 0.5cm of PID,drop shadow,align=center] {Entry of state\\\textbf{ACCEPT}};
	\node[block,fill=yellow!20,name=state1, below right = 0.5cm and 1cm of entry,drop shadow,align=center] {Automatic DutyCycle \\determination\\ \textbf{110}};
	\node[block,fill=yellow!20,name=state2, below = 2.5cm of entry,drop shadow,align=center] {Align rotor to d-axis \\Identify $\theta_\mathrm{offset}$\\ \textbf{120/121}};
	%all step responses
	\node[block,fill=yellow!20,name=state3, below = 5cm of state2,drop shadow,align=center] {Identify $L_\textrm{d},L_\textrm{X},L_\textrm{Y}$,\\$L_\textrm{Z+}L_\textrm{Z-}$\\ and respective $R$\\via step response\\ \textbf{131/133-136}};
	%Lock rotor
	\node[block,fill=red!20,name=state7, below right = 0.5cm and 1cm of state2,drop shadow,align=center] {Lock rotor\\ in position };
	%ident LQ
	\node[block,fill=yellow!20,name=state8, below = 1cm of state7,drop shadow,align=center] {Identify $L_\mathrm q$\\via step response\\ \textbf{132}};
	%calc FOC params
	\node[block,fill=yellow!20,name=state9, below = 1cm of state3,drop shadow,align=center] {Calculate FOC-\\parameters\\ \textbf{148}};
	%ident psiPM speedcontrol
	\node[block,fill=yellow!20,name=state12, below = 1cm of state9,drop shadow,align=center] {Identify $\psi_\mathrm {PM,1}$\\with speedcontroller\\ \textbf{150}};
	%set external speed
	\node[block,fill=red!20,name=state10, right = 1cm of state9,drop shadow,align=center] {Set load\\ machine speed \\ \textbf{155}};
	%ident psiPM external
	\node[block,fill=yellow!20,name=state11, below = 1cm of state10,drop shadow,align=center] {Identify $\psi_\mathrm {PM,1,3,5,7,9}$\\with prime mover\\ \textbf{156}};	
	%ident J
	\node[block,fill=yellow!20,name=state13, below = 1cm of state12,drop shadow,align=center] {Identify $J$ via\\ sine excitation\\ \textbf{160/161}};
	%extended Theta
	\node[block,fill=yellow!20,name=state15, below right = 1cm  and 1cm of state13,drop shadow,align=center] {Extended offset\\ estimation\\ \textbf{165/166}};
	%End
	\node[block,fill=yellow!20,name=state14, below = 3cm of state13,drop shadow,align=center] {Recalculate FOC- \\parameters\\ \textbf{170}};
	\node[block,fill=green!20,name=exit, below = 0.5cm of state14,drop shadow,align=center] {Exit of state};
	\begin{scope}[on background layer]
		\node[draw,fill=blue!10,name=ParameterID,rounded corners,fit=(PID) (exit)(state1)(state2),inner sep=5pt,minimum width=7cm] {};
	\end{scope}
	\draw[->](entry.east) -| (state1.north);
	\path ([xshift=-2.3cm,yshift=1cm]entry.east) -- (state1.north) node[midway, align=center] (DC1){DutyCycle == 0.0};
	%\path ([xshift=-2.3cm,yshift=1cm]state2.east) -- (state5.north) node[midway, align=center] (DC2){DutyCycle == 0.0};
	\draw[->](state1.south) |- ([yshift=0.5cm]state2.east);
	\draw[->](entry.south) -- (state2.north);
	\path (state2.north) -- (entry.south) node[midway,align=center] (DC1) {DutyCycle \\!= 0.0};
	\draw[->](state8.south) |- (state3.east);
	\draw[->]([yshift=-0.5cm] state2.east)-| (state7.north);
	\path([xshift=-2cm, yshift=0.3cm]state2.east) -- (state7.north) node [midway, align=center] (LQ1) {IdentLq == 1};
	\path(state3.north) -- (state2.south) node [midway, align=center] (LQ0) {IdentLq \\== 0\\};
	\draw[->] (state2.south) -- (state3.north);
	\draw[->](state7.south) -- (state8.north);
	\path (state7.south) -- (state8.north) node [midway, align=center] (ACPT1){\textbf{ACCEPT}};
	\draw[->](state3.south) -- (state9.north);
	%around Psi
	\draw[->](state9.south) -- node[align=center, xshift=-2cm,yshift=-0.2cm]{Extended$\Psi$\\==0\\} (state12.north);
	\draw[->](state9.east) -- node[align=center,yshift=-2cm]{Extended$\Psi$\\==1\\} (state10.west);
	\draw[->](state10.south) -- node[]{\textbf{ACCEPT}} (state11.north);
	\node[name=help1,below = of state10]{};
	\draw[->](state11.south) |- node[align=center]{free rotor\\\textbf{ACCEPT}} ([yshift=0.5cm]state13.east);
	\draw[->](state12.south) -- (state13.north);
	%around J
	\draw[->](state13.south) --  node[align=center,xshift=-2cm]{Extended$\theta$\\==0\\} (state14.north);
	\draw[->](state15.south) |- (state14.east);
	\draw[->]([yshift=-0.5cm]state13.east) -| node[align=center,yshift=-0.7cm]{Extended$\theta$\\==1\\} (state15.north);
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
* theta_el


Function Reference
==================

Structs
-------

.. doxygentypedef:: uz_ParaID_ElectricalID_6ph_t


The config and output structs are both shared with the 3ph ElectricalID.

:ref:`uz_ParaID_ElectricalIDConfig`

:ref:`uz_ParaID_ElectricalIDoutput`



.. doxygenstruct:: uz_ParaID_ElectricalID_fft_in_t
  :members: 

.. doxygenstruct:: uz_ParaID_ElectricalID_offset_estimation_t
  :members: 


General functions
-----------------

.. doxygenfunction:: uz_ElectricalID_6ph_init
.. doxygenfunction:: uz_ElectricalID_6ph_step

Set functions
-------------

.. doxygenfunction:: uz_ElectricalID_6ph_set_Config
.. doxygenfunction:: uz_ElectricalID_6ph_set_ActualValues
.. doxygenfunction:: uz_ElectricalID_6ph_set_GlobalConfig
.. doxygenfunction:: uz_ElectricalID_6ph_set_ControlFlags
.. doxygenfunction:: uz_ElectricalID_6ph_set_FFT_in
.. doxygenfunction:: uz_ElectricalID_6ph_set_Offset_Estimation

Get functions
-------------

.. doxygenfunction:: uz_ElectricalID_6ph_get_fft_out
.. doxygenfunction:: uz_ElectricalID_6ph_get_finished_voltage_measurement
.. doxygenfunction:: uz_ElectricalID_6ph_get_entered
.. doxygenfunction:: uz_ElectricalID_6ph_get_finished
.. doxygenfunction:: uz_ElectricalID_6ph_get_FOCoutput
.. doxygenfunction:: uz_ElectricalID_6ph_get_output

Sources
=======

.. [#param_ID_paper_SF] M. Hoerner, V. Hoppe, T. Wilfling, A. Dietz, P. Karamanakos and R. Kennel, "Parameter Identification Methods for Multi-Phase Permanent Magnet Synchronous Machines," 2023 IEEE International Electric Machines & Drives Conference (IEMDC), San Francisco, CA, USA, 2023, pp. 1-7, doi: 10.1109/IEMDC55163.2023.10238936.
.. [#hoppe_pab2] "Automated Parameter Identification for Asymmetrical Six-Phase PermanentMagnet Synchronous Machines", Valentin Hoppe, TH Nürnberg Institute ELSYS, 2023