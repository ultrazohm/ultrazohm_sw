.. _uz_pmsmModel:

==========
PMSM Model
==========

- IP-Core of a PMSM model
- Simulates a PMSM on the FPGA
- Intended for HIL/SIL/xIL on the UltraZohm
- Time discrete transformation is done by *zero order hold* transformation
- Sample time of the integrator is :math:`T_s=\frac{1}{1\,MHz}`
- IP-Core clock frequency **must** be :math:`f_{clk}=100\,MHz`!
- IP-Core has single precision AXI ports
- All calculations in the IP-Core are done in double precision!

System description
==================

Electriclal System
------------------

The model assumes a symmetric machine with sinusoidal input voltage as well as the common assumptions for the dq-transformation (neglecting the zero-component).
Small letter values indicate time dependency without explicitly stating.
The PMSM model is based on its differential equation using the flux-linkage as state values in the dq-plane [[#Schroeder_Regelung]_, p. 1092]:

.. math:: 

    \frac{d \psi_d}{dt} &= u_d - R_1 i_d + \omega_{el} \psi_q

    \frac{d \psi_q}{dt} &= u_q - R_1 i_q - \omega_{el} \psi_d

The flux-linkages of the direct and quadrature axis are given by [[#Schroeder_Regelung]_, p. 1092]:

.. math::

    \psi_d &= \psi_{pm} + L_d i_d

    \psi_q &= L_q i_q

Rearranging to calculate the current from the flux-linkage:

.. math::

    i_d &= \frac{\psi_d - \psi_{pm}}{L_d}

    i_q &= \frac{\psi_q}{L_q}

With the rotational speed linked to the electrical rotation speed in dq-coordinates by the number of pole pairs [[#Schroeder_Regelung]_, p. 1092]:

.. math::

    \omega_{el}=p \cdot \omega_{mech}

The PMSM generates an inner torque :math:`M_I` according to:

.. math::

    M_I=\frac{3}{2}p(\psi_d i_q - \psi_q i_d)

This can be rearranged to the following equation [[#Schroeder_Regelung]_, p. 1092]. Note that the flux-based equation above is implemented in the model.

.. math::

    M_I=\frac{3}{2} p \big(i_q \psi_{pm} + i_d i_q (L_d -L_q) \big)

Mechanical system
-----------------

The mechanical system is modeled by the following equations.
The inertia of the complete system is summed into the inertia :math:`J_{sum}`, i.e., rigid coupling of the system is assumed.

.. math::

  \frac{d \omega_{mech}}{dt} = \frac{ M_I - M_F - M_L }{J_{sum}}


.. tikz:: Block diagram of mechanical system 
  :libs: shapes, arrows

  \begin{tikzpicture}[auto, node distance=1.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, minimum height=3em, minimum width=3em]
  \node[name=Mi]{$M_I$};
  \node[draw,circle,name=torque_sum,right of=Mi] {};
  \node[name=load_torque,above of=torque_sum] {$M_L$};
  \node[block,name=inertia,right of=torque_sum] {$\frac{1}{J_{sum}}$};
  \node[block,name=integrator,right of=inertia] {$\frac{1}{s}$};
  \node[block,name=friction,below of=integrator] {$M_F(\omega)$ };
  \node[fill=black,circle,inner sep=1pt,name=output_node,right of=integrator] {};
  \node[name=output,right of=output_node] {};
  
  \draw[->] (Mi) -- (torque_sum);
  \draw[->] (torque_sum) -- (inertia);
  \draw[->] (inertia) -- (integrator);
  \draw[-] (output_node) |- (friction);
  \draw[->] (friction) -| node[pos=0.9,right] {$-$} (torque_sum);
  \draw[->] (load_torque) -- node[pos=0.9] {$-$} (torque_sum);
  \draw[-] (integrator) -- (output_node);
  \draw[->] (output_node) -- node {$\omega_{mech}$} (output);
  \end{tikzpicture}

Friction
^^^^^^^^

The friction :math:`M_F(\omega)`  [ [#ZurModellierungReibung]_, p. 12 ff] is implemented with the simplified viscous friction model:

.. math::

  M_F = sign(\omega_{mech}) \cdot M_c + \sigma \omega_{mech}

With the constant coulomb friction :math:`M_c`, and the friction coefficient :math:`\sigma`.

.. tikz:: Friction model [ [#ZurModellierungReibung]_, p. 13]
  :libs: 

  \begin{tikzpicture}
  \draw[->] (0,-2) -- node[above left,very near end] {$M_F$}(0,2);
  \draw[->] (-2,0) -- node[below right, near end] {$\omega_{mech}$} (2,0);
  \draw[-,thick] (-2,-2) -- (0,-1) -- (0,1) -- node[below right, near end] {$\sigma \omega_{mech}$} (2,2);
  \draw[->,dashed] (-0.1,0) -- node[left] {$M_C$} (-0.1,1);
  \end{tikzpicture}

IP-Core overview
================

.. tikz:: Block diagram of IP-Core
  :libs: shapes, arrows, positioning, calc

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, minimum height=3em, minimum width=3em]
  \node[name=ud]{$u_d$};
  \node[name=uq,below = 0.5cm of ud]{$u_q$};
  \node[draw,rectangle,fill=black!10,name=electrical,label=Electrical,below right= -1.0cm and 0.2cm of ud, minimum height=6em, minimum width=3em] {};
  \node[draw,rectangle,fill=black!10,name=torque,label=Torque, right of=electrical,minimum height=6em, minimum width=3em] {};
  \node[draw,rectangle,fill=black!10,name=mechanical,label=Mechanical, right of=torque,minimum height=6em, minimum width=3em] {};
  \node[inner sep=0 pt, name=output, right of= mechanical] {};
  \node[inner sep=0pt, name=ghostnode, below of=mechanical] {};
  \draw[->] (ud.east) -- ([yshift=0.5 cm]electrical.west);
  \draw[->] (uq.east) -- ([yshift=-0.55 cm]electrical.west);
  \draw[->] ([yshift=0.9 cm]electrical.east) --  node[] {$i_d$} ([yshift=0.9 cm]torque.west);
  \draw[->] ([yshift=0.3 cm]electrical.east) --  node[] {$i_q$} ([yshift=0.3 cm]torque.west);
  \draw[->] ([yshift=-0.3 cm]electrical.east) -- node[] {$\psi_d$} ([yshift=-0.3 cm]torque.west);
  \draw[->] ([yshift=-0.9 cm]electrical.east) -- node[] {$\psi_q$} ([yshift=-0.9 cm]torque.west);
  \draw[->] (torque) -- node[name=mi] {$M_I$}(mechanical);
  \node[name=ml,below= 0.2cm of mi] {$M_L$};
  \draw[->] (ml) -- ([yshift=-0.5 cm]mechanical.west);
  \draw[->] (mechanical) -- node {$\omega_{mech}$}(output);
  \draw[-, dashed] (mechanical) -- (ghostnode);
  \draw[->, dashed] (ghostnode) -| node {$\omega_{mech}$} (electrical);
  \end{tikzpicture}

All time dependent variables are either inputs or outputs that are written/read by AXI4-full.
That is, :math:`u_d`, :math:`u_q`, :math:`\omega_{mech}`, and :math:`M_L` are inputs.
Furthermore, :math:`i_d`, :math:`i_q`, :math:`M_I`, and :math:`\omega_{mech}` are outputs.
Note that :math:`\omega_{mech}` is an input as well as an output.
The IP-Core has two modes regarding the rotational speed :math:`\omega_{mech}`:

1. Simulate the mechanical system and calcualte :math:`\omega_{mech}` according to the equations in `Friction`_.
2. Use the rotational frequency :math:`\omega_{mech}` that is written as an input (written by AXI).
   
When the flag ``simulate_mechanical_system`` is true, the rotational speed in the output struct is calculated by the IP-Core and the input value of the rotational speed has no effect.
When the flag ``simulate_mechanical_system`` is false, the rotational speed in the output struct is equal to the rotational speed of the input.
This behavior is implemented in the hardware of the IP-Core with switches.
The input and output values are intended to be written and read in a periodical function, e.g., the ISR.

In addition to the time dependent values, the PMSM model parameters are configured by AXI.

Driver reference
================

.. doxygentypedef:: uz_pmsmModel_t

.. doxygenstruct:: uz_pmsmModel_config_t
  :members:

.. doxygenstruct:: uz_pmsmModel_outputs_t
  :members:

.. doxygenstruct:: uz_pmsmModel_inputs_t
  :members:  
  
.. doxygenfunction:: uz_pmsmModel_init

.. doxygenfunction:: uz_pmsmModel_set_inputs

.. doxygenfunction:: uz_pmsmModel_get_outputs

.. doxygenfunction:: uz_pmsmModel_reset


Sources
-------

.. [#ZurModellierungReibung] Zur Modellierung und Kompensationdynamischer Reibung in Aktuatorsystemen, Michael Ruderman, Dissertation, 2012, TU Dortmund
.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Springer, 2015, 4. Edition