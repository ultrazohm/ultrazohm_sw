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

Electrical System
------------------

The model assumes a symmetric machine with a sinusoidal input voltage as well as the common assumptions for the dq-transformation (neglecting the zero-component).
Small letter values indicate time dependency without explicitly stating it.
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

All time-dependent variables are either inputs or outputs that are written/read by AXI4-full.
That is, :math:`u_d`, :math:`u_q`, :math:`\omega_{mech}`, and :math:`M_L` are inputs.
Furthermore, :math:`i_d`, :math:`i_q`, :math:`M_I`, and :math:`\omega_{mech}` are outputs.
Note that :math:`\omega_{mech}` is an input as well as an output.
The IP-Core has two modes regarding the rotational speed :math:`\omega_{mech}`:

1. Simulate the mechanical system and calcualte :math:`\omega_{mech}` according to the equations in `Friction`_.
2. Use the rotational frequency :math:`\omega_{mech}` that is written as an input (written by AXI).
   
When the flag ``simulate_mechanical_system`` is true, the rotational speed in the output struct is calculated by the IP-Core, and the input value of the rotational speed has no effect.
When the flag ``simulate_mechanical_system`` is false, the rotational speed in the output struct is equal to the rotational speed of the input.
This behavior is implemented in the hardware of the IP-Core with switches.
The input and output values are intended to be written and read in a periodical function, e.g., the ISR.

In addition to the time-dependent values, the PMSM model parameters are configured by AXI.

IP-Core Hardware
----------------

.. figure:: pmsm_model.svg
  :width: 800
  :align: center

  Test bench of PMSM plant model

.. figure:: pmsm_model_inside.svg
  :width: 800
  :align: center

  Overview of PMSM IP-Core

.. figure:: pmsm_model_inside_pmsm.svg
  :width: 800
  :align: center

  Calculation of PMSM subsystem

.. figure:: pmsm_model_inside_torque.svg
  :width: 800
  :align: center

  Torque calculation subsystem

.. figure:: pmsm_model_inside_mechanical.svg
  :width: 800
  :align: center

  Mechanical calculation subsystem

- The module takes all inputs and converts them from single precision to double precision.
- The output is converted from double precision to single precision (using rounding to the nearest value in both cases).
- All input values are adjustable at run-time
- The sample time is fixed!
- The IP-Core uses `Native Floating Point of the HDL-Coder <https://de.mathworks.com/help/hdlcoder/native-floating-point.html>`_
- Several parameters are written as their reciprocal to the AXI register to make the calculations on hardware simple (handled by the driver!)
- The IP-Core uses an oversampling factor of 100

Example usage
=============

Vivado
------

- Add IP-Core to Vivado and connect to AXI (smartconnect)
- Source IPCORE_CLK with a :math:`100\,MHz` clock!
- Connect other ports accordingly
- Assign address to IP-Core
- Build bitstream, export .xsa, update Vitis platform

.. figure:: pmsm_vivado.png
   :width: 800
   :align: center

   Example connection of PMSM IP-Core


Vitis
-----

- Initialize the driver in main and couple the base address with the driver instance

.. code-block:: c
  :caption: Changes in ``main.c`` (R5)

  #include "IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
  #include "xparameters.h"
  uz_pmsmModel_t *pmsm=NULL;

  int main(void) {
  // other code...
  struct uz_plantPT1_config_t config={
    .base_address=XPAR_UZ_PLANTMODEL_PT1_0_BASEADDR,
    .ip_core_frequency_Hz=100000000U,
    .time_constant=1.0f,
    .gain=1.0f
  };
  pt1=uz_plantPT1_init(config);
  uz_plantPT1_set_input(pt1,intput);
  
  struct uz_pmsmModel_config_t pmsm_config={
    .base_address=XPAR_UZ_PMSM_MODEL_0_BASEADDR,
    .ip_core_frequency_Hz=100000000,
      .simulate_mechanical_system = true,
      .r_1 = 2.1f,
      .L_d = 0.03f,
      .L_q = 0.05f,
      .psi_pm = 0.05f,
      .polepairs = 2.0f,
      .inertia = 0.001,
      .coulomb_friction_constant = 0.01f,
      .friction_coefficient = 0.001f};
  
  pmsm=uz_pmsmModel_init(pmsm_config);
  // before ISR Init!
  // more code of main

- Read and write the inputs in ``isr.c``
- Add before ISR with global scope to use the driver and :ref:`wave_generator`:

.. code-block:: c
  :caption: Changes in ``isr.c``

  #include "../uz/uz_wavegen/uz_wavegen.h"
  #include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
  extern uz_pmsmModel_t *pmsm;

  float i_d_soll=0.0f;
  float i_q_soll=0.0f;
  struct uz_pmsmModel_inputs_t pmsm_inputs={
      .omega_mech_1_s=0.0f,
      .u_d_V=0.0f,
      .u_q_V=0.0f,
      .load_torque=0.0f
  };
  
  struct uz_pmsmModel_outputs_t pmsm_outputs={
      .i_d_A=0.0f,
      .i_q_A=0.0f,
      .torque_Nm=0.0f,
      .omega_mech_1_s=0.0f
  };

  void ISR_Control(void *data){
  // other code
  pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);
  pmsm_inputs.u_q_V=uz_wavegen_pulse(10.0f, 0.10f, 0.5f);
  pmsm_inputs.u_d_V=-pmsm_inputs.u_q_V;
  uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);
  // [...]
  }


- Change the Javascope  ``enum`` to transfer the required measurement data

.. code-block:: c
  :caption: Adjust ``JS_OberservableData`` enum in ``javascope.h`` (R5) to measure pmsm_outputs

  // Do not change the first (zero) and last (end) entries.
  enum JS_OberservableData {
    JSO_ZEROVALUE=0,
    JSO_i_q,
    JSO_i_d,
    JSO_omega,
    JSO_u_d,
    JSO_ENDMARKER
  };

- Configure the Javascope to transmit the pmsm output data:

.. code-block:: c
  :caption: Adjust ``JavaScope_initalize`` function in ``javascope.c`` (R5) to measure pmsm_outputs
    
    #include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
    extern struct uz_pmsmModel_outputs_t pmsm_outputs;
    extern struct uz_pmsmModel_inputs_t pmsm_inputs;

    int JavaScope_initalize(DS_Data* data){
    // existing code
    // [...]
    // Store every observable signal into the Pointer-Array.
    // With the JavaScope, 4 signals can be displayed simultaneously
    // Changing between the observable signals is possible at runtime in the JavaScope.
    // the addresses in Global_Data do not change during runtime, this can be done in the init
    js_ptr_arr[JSO_i_q] = &pmsm_outputs.i_d_A;
    js_ptr_arr[JSO_i_d] = &pmsm_outputs.omega_mech_1_s;
    js_ptr_arr[JSO_omega] = &pmsm_outputs.i_q_A;
    js_ptr_arr[JSO_u_d] = &pmsm_inputs.u_d_V;
    return Status;
    }

Javascope
---------

- Copy your ``javascope.h`` file (of the R5) into your Javascope folder


Comparison between reference and IP-Core
----------------------------------------

- Program UltraZohm with included PMSM IP-Core and software as described above
- Start Javascope
- Measure and log data
- Copy measured ``.csv`` data to ``ultrazohm_sw/ip-cores/uz_pmsm_model``
- Rename it to ``measurment_with_speed.csv``
- Run ``compare_simulation_to_measurement.m`` in ``ultrazohm_sw/ip-cores/uz_pmsm_model``

.. figure:: referance_ip_core_measurment_comparision.svg
   :width: 800
   :align: center

   Comparison of step response between the reference model and IP-Core implementation measured by Javascope


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

.. [#ZurModellierungReibung] Zur Modellierung und Kompensationdynamischer Reibung in Aktuatorsystemen, Michael Ruderman, Dissertation, 2012, TU Dortmund (German)
.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Springer, 2015, 4. Edition (German)