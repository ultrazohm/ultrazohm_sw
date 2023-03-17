.. _uz_CurrentControl:

==============
CurrentControl
==============

Toolbox for a standard CurrentControl with parallel :ref:`PI-Controllers <uz_piController>`, :ref:`linear decoupling <uz_lineardecoupling>` and a :ref:`space vector limitation <uz_spacevectorlimiation>`. 
A space vector output limitation and a linear decoupling function are integrated. 
The decoupling function can be deactivated in the :ref:`CurrentControl configuration struct <uz_CurrentControl_config>`.

.. tikz:: CurrentControl schematic
  :align: center

  \usetikzlibrary{shapes, arrows, positioning, calc,fit, backgrounds, shadows}  
  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=2em]
  \node(CC) {\Large{CurrentControl}};
  %Exist on the background solely to be able to wrap the PI-Controller around the machines
  \node[block,fill=yellow!0,name=PI00, below left=  1.25cm and 1.4cm of CC,drop shadow,align=center] {uz\_PI\_Controller};
  \node[block,fill=yellow!0,name=PI01, below left=  3.75cm and 1.4cm of CC,drop shadow,align=center] {uz\_PI\_Controller};
  \node[name=temp3, below =  1cm of CC]{\large{decoupling}};
  \node[block,fill=yellow!20,name=NO_DECOUP00, below =  0.25cm of temp3,drop shadow,align=center] {no decoupling};
  \node[block,fill=yellow!20,name=LIN_DECOUP00, below =  0.25cm of NO_DECOUP00,drop shadow,align=center] {linear decoupling};
  \node[name=temp, below  left = 0.5cm and 1.5cm of CC]{\large{$i_d$-Controller}};
  \node[name=temp2, below left= 3.2cm and 1.5cm of CC]{\large{$i_q$-Controller}};
  %Normal nodes
  \node[block,fill=green!10,name=IDC, drop shadow,fit=(PI00)(temp) ,minimum height=2cm,minimum width=3.3cm] {};
  \node[name=IDC_Text, below left= 0.5cm and 1.5cm of CC]{\large{$i_d$-Controller}};
  \node[block,fill=yellow!20,name=PI1, below =  0cm of IDC_Text,drop shadow,align=center] {uz\_PI\_Controller};
  \node[block,fill=green!10,name=IQC, fit=(PI01)(temp2),drop shadow,minimum height=2cm,minimum width=3.3cm] {};
  \node[name=IQC_Text, below left= 3cm and 1.5cm  of CC, ]{\large{$i_q$-Controller}};
  \node[block,fill=yellow!20,name=PI2, below =   -0.1cm of IQC_Text,drop shadow,align=center] {uz\_PI\_Controller};
  \node[block,fill=orange!20,name=DECOUP ,fit=(LIN_DECOUP00)(NO_DECOUP00)(temp3),drop shadow,minimum height=4cm,align=center] {};
  \node[name=DECOUP_Text, below = 1cm of CC, ]{\large{decoupling}};
  \node[block,fill=yellow!20,name=NO_DECOUP, below =  0.25cm of DECOUP_Text,drop shadow,align=center] {no decoupling};
  \node[block,fill=yellow!20,name=LIN_DECOUP, below =  0.25cm of NO_DECOUP,drop shadow,align=center] {linear decoupling};
  \node[block,fill=purple!20,name=SVL, right =  1cm of DECOUP,drop shadow,align=center, minimum height=3cm, minimum width=3cm] {\large{Space} \\ \large{Vector} \\ \large{Limitation}};
  \begin{scope}[on background layer]
  \node[draw,fill=blue!10,name=CurrentControl,rounded corners,fit=(CC) (IDC)(IQC)(DECOUP) (SVL),inner sep=5pt,minimum width=5cm] {};
  \end{scope}
  \node[block,name=input1, below left = -6.4cm and 0.75cm of CurrentControl,drop shadow,minimum width=2cm, align=center] {$\omega_{el}$\\ \tiny{float}};
  \node[block,name=input2, below = 0.5cm of input1,drop shadow,minimum width=2cm, align=center] {$i_{dq,meas}$\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,name=input3, below = 0.5cm of input2,drop shadow,minimum width=2cm, align=center] { $i_{dq,ref}$\\ \tiny{uz\_3ph\_dq\_t}};
  \node[block,name=input4, below = 0.5cm of input3,drop shadow,minimum width=2cm, align=center] { $V_{DC}$\\ \tiny{float}};
  \node[block,name=input5, above =1cm of CurrentControl,drop shadow,minimum width=2cm, align=center] { instance\\ \tiny{uz\_CurrentControl\_t}};
  \node[block,name=input6, left = 1cm of input5,drop shadow,minimum width=2cm, align=center] {config\\ \tiny{struct  uz\_CurrentControl\_config}};
  \node[block,name=output,  right= 0.75cm of CurrentControl,drop shadow,minimum width=2cm, align=center] {output\\\tiny{uz\_3ph\_dq\_t}};
  \draw[-](IDC.east) -| ($(DECOUP.west)-(1cm,0cm)$);
  \draw[-](IQC.east) -| ($(DECOUP.west)-(1cm,0cm)$);
  \draw[->]($(DECOUP.west)-(1cm,0cm)$) -- (DECOUP.west);
  \draw[->](DECOUP.east) -- (SVL.west);
  \draw[->](input5.south) -- (CurrentControl.north);
  \draw[<-](output.west) -- (CurrentControl.east |- output.west);
  \draw[->](input1.east) -- (CurrentControl.west |- input1.east);
  \draw[->](input2.east) -- (CurrentControl.west |- input2.east);
  \draw[->](input3.east) -- (CurrentControl.west |- input3.east);
  \draw[->](input4.east) -- (CurrentControl.west |- input4.east);
  \draw[->](input6.east) -- (input5.west);
  \end{tikzpicture}

Setup
=====

.. _uz_CurrentControl_config:

Configuration
-------------

In order to configure the CurrentControl, multiple configuration structs have to be initialized.

.. doxygenenum:: uz_CurrentControl_decoupling_select 

.. doxygenstruct:: uz_CurrentControl_config
  :members: 
   
Example
^^^^^^^
    
.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct
    
  #include "uz/uz_CurrentControl/uz_CurrentControl.h"
  int main(void) {
     struct uz_PMSM_t config_PMSM = {
        .Ld_Henry = 0.0001f,
        .Lq_Henry = 0.0002f, 
        .Psi_PM_Vs = 0.008f
      };//these parameters are only needed if linear decoupling is selected
      struct uz_PI_Controller_config config_id = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00005f,
     };
     struct uz_PI_Controller_config config_iq = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00005f,
     };
     struct uz_CurrentControl_config CC_config = {
        .decoupling_select = linear_decoupling,
        .config_PMSM = config_PMSM,
        .config_id = config_id,
        .config_iq = config_iq
     };
  }

.. note::

  The limitation of the internal PI-Controllers are deactivated, since only the :ref:`uz_spacevectorlimiation` will be used. The limits can be left at 0 in the config.  


Description
^^^^^^^^^^^
    
With these config structs one can customize the CurrentControl and the included :ref:`PI-Controller <uz_piController>` and :ref:`PMSM config <uz_PMSM_config>`. 
It is possible to use the CurrentControl with or without the :ref:`linear decoupling <uz_lineardecoupling>` via the CurrentControl_config member ``decoupling_select``. 
If no decoupling is selected, no variables for the ``struct uz_PMSM_t`` have to be configured and can be left 0.
Each of the two PI-Controller need their own :ref:`config struct <uz_piController_config>`.
One for the id-Controller and the other one for the iq-Controller. 

.. _uz_CurrentControl_init:

Init function
-------------

.. doxygentypedef:: uz_CurrentControl_t
.. doxygenfunction:: uz_CurrentControl_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a CurrentControl instance. ``config_CurrentControl`` according to :ref:`configuration section<uz_CurrentControl_config>`

  int main(void) {
     uz_CurrentControl_t* CC_instance = uz_CurrentControl_init(CC_config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the CurrentControl instance and the included PI-Controller instances. 
Furthermore the input values of the configuration structs are asserted. 

.. _uz_CurrentControl_reset:

Reset
-----

.. doxygenfunction:: uz_CurrentControl_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the CurrentControl. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     uz_CurrentControl_reset(CC_instance);
  }

Description
^^^^^^^^^^^

Resets the CurrentControl and the integrated PI-Controller. The initial condition for the integrator after the reset is 0.0f.

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *