.. _uz_CurrentControl_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_CurrentControl_sample

.. doxygenfunction:: uz_CurrentControl_sample_abc

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the CurrentControl output. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     float V_dc_volts = 24.0f;
     float omega_el_rad_per_sec = 125.1f;
     float theta_el_rad = 1.2f;
     struct uz_3ph_dq_t i_actual_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_3ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_3ph_dq_t v_dq_Volts = uz_CurrentControl_sample(CurrentControl_instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
     //Alternatively the sample function can output the UVW-values
     struct uz_3ph_abc_t v_abc_Volts = uz_CurrentControl_sample_abc(CurrentControl_instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad);
  }

Description
===========

Calculates one sample of the CurrentControl.
A space vector output limitation and a linear decoupling function are integrated. 
The decoupling function can be deactivated in the :ref:`CurrentControl configuration struct <uz_CurrentControl_config>`.

.. note::

  Either use the ``uz_CurrentControl_sample`` function to get the output voltages in the dq0-frame or use the ``uz_CurrentControl_sample_UVW`` function to get the output voltages in the UVW-system. 

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`PI-Controller configuration struct <uz_piController_config>`.

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