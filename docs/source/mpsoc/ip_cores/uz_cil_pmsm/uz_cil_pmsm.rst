.. _uz_cil_pmsm:

========
CIL PMSM
========

General description
===================

To use the CIL method for controller development for PMSM, as described in [[#uz_cil_paper1]_][[#uz_cil_paper2]_], several IP-Cores have been created.
A general overview over the available IP-Cores is given here.
Links to the individual Docs pages can be found below, as well as examples for the usage.
Models are available for sixphase and ninephase PMSM.

General setup
=============

.. tikz:: Block diagram of IP-Core
  \begin{tikzpicture}
  \tikzstyle{big} = [rectangle, rounded corners, minimum width=2.5cm, minimum height=5cm,text centered, draw=black, fill=gray!30, align=center]
  \tikzstyle{small} = [rectangle, rounded corners, minimum width=2.5cm, minimum height=1cm,text centered, draw=black, fill=gray!30, align=center]
  \node (inverter1) [small, yshift=2cm] {Three-phase\\inverter};
  \node (inverter2) [small,] {Three-phase\\inverter};
  \node (inverterplaceholder) [yshift=-2cm, xshift=1.5cm] {...};
  \node (transformation) [big, xshift=5cm] {uz\_Xphase\_\\VSD\_trans\\formation};
  \node (fliflop) [small, xshift=5cm, yshift=-4cm] {uz\_rs\_flip\_flop};
  \node (pmsm) [big, xshift=10cm] {uz\_pmsm\_\\model\_\\Xph\_dq};
  \draw[->] ([yshift=0.25cm]inverter1.east) -- node[yshift=0.25cm] {$v_{abc,1}$} ([yshift=2.25cm]transformation.west);
  \draw[->] ([yshift=1.75cm]transformation.west) -- node[yshift=0.25cm] {$i_{abc,1}$} ([yshift=-0.25cm]inverter1.east);
  \draw[->] ([yshift=0.25cm]inverter2.east) -- node[yshift=0.25cm] {$v_{abc,2}$} ([yshift=0.25cm]transformation.west);
  \draw[->] ([yshift=-0.25cm]transformation.west) -- node[yshift=0.25cm] {$i_{abc,2}$} ([yshift=-0.25cm]inverter2.east);
  \draw[->] ([xshift=-0.25cm]fliflop.north) -- node[xshift=-0.5cm] {ff\_out} ([xshift=-0.25cm]transformation.south);
  \draw[->] ([xshift=0.25cm]transformation.south) -- node[xshift=0.55cm] {ff\_reset} ([xshift=0.25cm]fliflop.north);
  \draw[->] (1cm,-4cm) -- node[yshift=0.25cm] {ext: ff\_set} (fliflop.west);              
  \draw[->] ([yshift=1.5cm]transformation.east) -- node[text width=1cm, align=center, yshift=0.25cm] {$v_{dq}$} ([yshift=1.5cm]pmsm.west);
  \draw[->] ([yshift=0]pmsm.west) -- node[text width=1cm, align=center, yshift=0.25cm] {$i_{dq}$} ([yshift=0]transformation.east);
  \draw[->] ([yshift=-1.5cm]pmsm.west) -- node[text width=1cm, align=center,yshift=0.25cm] {$\vartheta{el}$} ([yshift=-1.5cm]transformation.east);	
  \end{tikzpicture}


The "X" for the transfromation and pmsm IP-Core serves as placeholder and the respective IP-Cores for the amount of phases should be used.
Individual documentation of the IP-Cores is linked below.

..  toctree::
    :maxdepth: 1
    :glob:
    
    uz_pmsm_model_9ph_dq/uz_pmsm_model_9ph_dq
    uz_vsd_transformation/uz_vsd_transformation
    ../uz_inverter_3ph/uz_inverter_3ph
    ../uz_rs_flip_flop/uz_rs_flip_flop

Examples
========

Insert Links to extra docs pages with examples including vivado screenshots and vitis code, for example:

threephase CIL

Multiphase CIL

incl. init files

References
==========

.. [#uz_cil_paper1] E. Liegmann, T. Schindler, P. Karamanakos, A. Dietz and R. Kennel, "UltraZohm—An Open-Source Rapid Control Prototyping Platform for Power Electronic Systems," 2021 International Aegean Conference on Electrical Machines and Power Electronics (ACEMP) & 2021 International Conference on Optimization of Electrical and Electronic Equipment (OPTIM), 2021, pp. 445-450, doi: 10.1109/OPTIM-ACEMP50812.2021.9590016.
.. [#uz_cil_paper2] V. Hoppe, T. Schindler, M. Hoerner, A. Dietz and R. Kennel, "On-Chip Simulation of a Nine-Phase Electrical Drive and Power Electronics for Rapid Control Prototyping Applications," 2022