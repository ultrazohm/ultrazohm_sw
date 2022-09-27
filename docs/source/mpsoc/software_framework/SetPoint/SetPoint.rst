.. _uz_SetPoint:

=========
Set Point
=========

Toolbox for a standard set-point module. The input is a reference torque. This will then be converted, depending on the machine type selection, into d- and q-reference currents.
It currently supports surface-mounted (SMPMSM) and interior (IPMSM) permanent magnet synchronous machines. IPMSM with a positive and negative saliency ratio are both supported.
The output currents will, depending on the operating condition of the machine, either be calculated via MTPA or field-weakening.
It can not control a machine on its own. 

.. tikz:: Schematic overview of the SetPoint module
  :align: center
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows,  patterns

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=2em]
  \node(STP) {\Large{SetPoint}};
  %Exist on the background solely to be able to wrap the MTPA and FW around the machines
  \node[block,fill=yellow!0,name=IPMSM00, below =  1.25cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!2,name=SMPMSM00, below =0.25cm of IPMSM00,drop shadow,align=center] {SM-PMSM};
  \node[block,fill=yellow!0,name=IPMSM01, below =  5.5cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!0,name=SMPMSM01, below =0.25cm of IPMSM01,drop shadow,align=center] {SM-PMSM};
  \node[name=temp, below = 0.5 of STP]{\large{MTPA}};
  \node[name=temp2, below = 4.75cm of STP]{\large{Field- \\ Weakening}};
  %Normal nodes
  \node[block,fill=green!10,name=MTPA, drop shadow,fit=(SMPMSM00)(IPMSM00)(temp) ,minimum height=2cm,minimum width=3.3cm] {};
  \node[name=MTPA_Text, below = 0.5 of STP]{\large{MTPA}};
  \node[block,fill=yellow!20,name=IPMSM1, below =  1.25cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!20,name=SMPMSM1, below =0.25cm of IPMSM1,drop shadow,align=center] {SM-PMSM}; 
  \node[block,fill=green!10,name=FW, fit=(SMPMSM01)(IPMSM01)(temp2),drop shadow,minimum height=2cm,minimum width=3.3cm] {};
  \node[name=FW_Text, below = 4.75cm of STP, ]{\large{Field- \\ Weakening}};
  \node[block,fill=yellow!20,name=IPMSM2, below =   5.5cm of STP,drop shadow,align=center] {I-PMSM};
  \node[block,fill=yellow!20,name=SMPMSM2, below =0.25cm of IPMSM2,drop shadow,align=center] {SM-PMSM};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=SetPoint,rounded corners,fit=(STP) (MTPA)(FW) ,inner sep=5pt,minimum width=5cm] {};
  \end{scope}
  \node[block,name=input1, below left = -8cm and 0.75cm of SetPoint,drop shadow,minimum width=2cm, align=center] {$\omega_{m}$\\ \tiny{float}};
  \node[block,name=input2, below = 0.5cm of input1,drop shadow,minimum width=2cm, align=center] {$M_{ref}$\\ \tiny{float}};
  \node[block,name=input4, below = 0.5cm of input2,drop shadow,minimum width=2cm, align=center] { $V_{DC}$\\ \tiny{float}};
  \node[block,name=input7, below = 0.5cm of input4,drop shadow,minimum width=2cm, align=center] { $i_{meas}$\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,name=input5, above =1cm of SetPoint,drop shadow,minimum width=2cm, align=center] { instance\\ \tiny{uz\_SetPoint\_t}};
  \node[block,name=input6, left = 1cm of input5,drop shadow,minimum width=2cm, align=center] {config\\ \tiny{struct  uz\_SetPoint\_config}};
  \node[block,name=output, below right= -5.5cm and 0.75cm of SetPoint,drop shadow,minimum width=2cm, align=center] {$I_{ref}$\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,fill=orange!20,name=Controller, right=0.5 cm of output,drop shadow,minimum height=4cm,align=center] {independent\\external\\current\\control};
  \draw[->](input5.south) -- (SetPoint.north);
  \draw[<-](output.west) -- (SetPoint.east |- output.west);
  \draw[->](output.east) -- (Controller.west);
  \draw[->](input1.east) -- (SetPoint.west |- input1.east);
  \draw[->](input2.east) -- (SetPoint.west |- input2.east);
  \draw[->](input4.east) -- (SetPoint.west |- input4.east);
  \draw[->](input6.east) -- (input5.west);
  \draw[->](input7.east) -- (SetPoint.west |- input7.east);
  \draw[->]($(FW.north)+(0.5,0)$) -- ($(MTPA.south)+(0.5,0)$) ;
  \draw[<-]($(FW.north)+(-0.5,0)$) -- ($(MTPA.south)+(-0.5,0)$) ;
  \node[name=omega_cut, below = 0cm of MTPA]{$\omega_{cut}$};
  \end{tikzpicture}


Setup
=====

.. doxygentypedef:: uz_SetPoint_t

.. _uz_SetPoint_config:

Configuration
-------------

.. doxygenenum:: uz_Setpoint_motor_type

.. doxygenenum:: uz_Setpoint_control_type
  
.. doxygenstruct:: uz_SetPoint_config
  :members:

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_setpoint/uz_setpoint.h"
  int main(void) {
     struct uz_SetPoint_config config = {
        .config_PMSM.I_max_Ampere = 15.0f,
        .config_PMSM.Ld_Henry = 0.0003f,
        .config_PMSM.Lq_Henry = 0.0003f,
        .config_PMSM.R_ph_Ohm = 0.1f,
        .config_PMSM.polePairs = 4.0f,
        .config_PMSM.Psi_PM_Vs = 0.0075f,
        .control_type = FOC,
        .motor_type = SMPMSM,
        .is_field_weakening_enabled = false,
        .id_ref_Ampere = 0.0f
     };
  }

.. _uz_SetPoint_init:

Init function
-------------

.. doxygenfunction:: uz_SetPoint_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init the SpeedController for the SpeedControl. ``config`` according to :ref:`configuration section<uz_SetPoint_config>`
  
  int main(void) {
     uz_SetPoint_t* instance = uz_SetPoint_init(config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the SetPoint instance. 
Furthermore the input values of the configuration struct are asserted. 

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *