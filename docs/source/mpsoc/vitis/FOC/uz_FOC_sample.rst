.. _uz_FOC_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_FOC_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the FOC output. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float U_zk_Volts = 24.0f;
     float omega_el_rad_per_sec = 125.1f;
     struct uz_dq_t i_dq_meas_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_dq_t u_dq_ref_Volts = uz_FOC_sample(FOC_instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
  }

Description
===========

Calculates one sample of the FOC.
A space vector output limitation and a linear decoupling function are integrated. 
It returns the reference voltages in an ``uz_dq_t`` struct. 

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`PI-Controller configuration struct <uz_piController_config>`.

.. tikz:: FOC (``->`` represent the arrow operator in C)
  :align: left

  \usetikzlibrary{shapes,arrows, patterns,calc};
  \begin{scope}[shift={(12,1)}]
  \node[draw, rectangle, minimum height=15.8cm, minimum width = 35cm, fill=blue, fill opacity=0.2] (FOC_sample) at (0,1) {};
  \node[font=\footnotesize] (input_dq) at ($(FOC_sample.west)+(0.7,5.0)$) {uz\_dq\_t};
  \node[font=\footnotesize] (input_omega) at ($(FOC_sample.west)+(0.7,-1.75)$) {$\omega_{el}$};
  \node[font=\footnotesize] (input_Uzk) at ($(FOC_sample.west)+(0.7,3)$) {$U_{zk}$};
  \node[font=\footnotesize] (input_FOC) at ($(FOC_sample.west)+(0.75,1.1)$) {uz\_FOC*};
  \node[font=\large] at ($(FOC_sample.south)+(0,-0.5)$) {uz\_FOC\_sample};
  \begin{scope}[shift={(-2,4)}]
  \node[draw, rectangle, minimum height=8.3cm, minimum width = 10cm,  fill=white, draw opacity = 0.0] (FOC_current) at (0,0) {};
  \node[draw, rectangle, minimum height=8.3cm, minimum width = 10cm,  fill=green, fill opacity=0.2] (white1) at (0,0) {};
  \node[font=\footnotesize] (CC_dq_output) at ($(FOC_current.east)+(-0.6,0)$) {uz\_dq\_t};
  \node[font=\footnotesize] (CC_uz_FOC) at ($(FOC_current.west)+(0.65,-2.3)$) {uz\_FOC*};
  \node[font=\footnotesize] (CC_uz_dq) at ($(FOC_current.west)+(0.65,2)$) {uz\_dq\_t};
  \node[] at ($(FOC_current.south)+(0.0,0.3)$) {uz\_FOC\_CurrentControl};
  \begin{scope}[shift={(1.5,2)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (iq_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(1.2,0.3)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(0.86,0.9)$) {actualValue};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(1.06,-0.3)$) {referenceValue};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(0.98,-0.9)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(iq_PIController.east)+(-0.5,0)$) {output};
  \node[] at (0,1.4) {$i_q$-Controller};
  \node[] at (0,-1.4) {uz\_PI\_Controller\_sample};
  \end{scope}
  \begin{scope}[shift={(1.5,-2)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (id_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(id_PIController.west)+(1.2,0.3)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(id_PIController.west)+(0.86,0.9)$) {actualValue};
  \node[font=\footnotesize] at ($(id_PIController.west)+(1.06,-0.3)$) {referenceValue};
  \node[font=\footnotesize] at ($(id_PIController.west)+(0.98,-0.9)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(id_PIController.east)+(-0.5,0)$) {output};
  \node[] at (0,1.4) {$i_d$-Controller};
  \node[] at (0,-1.4) {uz\_PI\_Controller\_sample};
  \end{scope}
  \draw[-latex](CC_uz_dq.north) |- ($(iq_PIController.west)+(0,0.9)$);
  \draw[-latex](CC_uz_dq.south) |- ($(id_PIController.west)+(0,0.9)$);
  \draw[-latex](iq_PIController.east) -| ($(FOC_current.east)+(-0.5,0.2)$);
  \draw[-latex](id_PIController.east) -| ($(FOC_current.east)+(-0.5,-0.2)$);
  \draw($(FOC_current.west)+(1.3,-2.3)$) -- ($(FOC_current.west)+(3.2,-2.3)$);
  \draw[-latex]($(FOC_current.west)+(3.2,-2)$) |- ($(iq_PIController.west)+(0,0.3)$);
  \draw[-latex]($(FOC_current.west)+(3.2,-2)$) |- ($(iq_PIController.west)+(0,-0.3)$);
  \draw[-latex]($(FOC_current.west)+(3.2,-2)$) |- ($(iq_PIController.west)+(0,-0.9)$);
  \draw[-latex]($(FOC_current.west)+(3.2,-2)$) |- ($(id_PIController.west)+(0,0.3)$);
  \draw[-latex]($(FOC_current.west)+(3.2,-2)$) |- ($(id_PIController.west)+(0,-0.3)$);
  \draw[-latex]($(FOC_current.west)+(3.2,-2)$) |- ($(id_PIController.west)+(0,-0.9)$);
  \node [circle,fill,inner sep=1pt] at ($(iq_PIController.west)+(-1.3,-0.9)$) {};
  \node [circle,fill,inner sep=1pt] at ($(iq_PIController.west)+(-1.3,-0.3)$) {};
  \node [circle,fill,inner sep=1pt] at ($(id_PIController.west)+(-1.3,0.3)$) {};
  \node [circle,fill,inner sep=1pt] at ($(id_PIController.west)+(-1.3,-0.3)$) {};
  \end{scope}
  \begin{scope}[shift={(-2,-4.1)}]
  \node[draw, rectangle, minimum height=4.3cm, minimum width = 10cm,  fill=white, draw opacity = 0.0] (FOC_speed) at (0,0) {};
  \node[draw, rectangle, minimum height=4.3cm, minimum width = 10cm,  fill=red, fill opacity=0.2] (white1) at (0,0) {};
  \node[font=\footnotesize] (SC_uz_FOC_output) at ($(FOC_speed.east)+(-0.6,0)$) {uz\_FOC*};
  \node[font=\footnotesize] (SC_uz_FOC) at ($(FOC_speed.west)+(0.65,0.9)$) {uz\_FOC*};
  \node[] at ($(FOC_speed.south)+(0.0,0.3)$) {uz\_FOC\_SpeedControl};
    \node[font=\footnotesize] (SC_omega) at ($(FOC_speed.west)+(0.5,-0.9)$) {$\omega_{el}$};
  \begin{scope}[shift={(1.5,0)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (n_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.2,0.3)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(n_PIController.west)+(0.86,-0.9)$) {actualValue};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.06,-0.3)$) {referenceValue};
  \node[font=\footnotesize] at ($(n_PIController.west)+(0.98,0.9)$) {ext\_clamping};
  \node[font=\footnotesize] (PI_n_output) at ($(n_PIController.east)+(-0.5,0)$) {output};
  \node[] at (0,1.4) {$n$-Controller};
  \node[] at (0,-1.4) {uz\_PI\_Controller\_sample};
  \draw[-latex](SC_omega.east) -- ($(n_PIController.west)+(0,-0.9)$);
  \draw[-latex](SC_uz_FOC.east) -- ($(n_PIController.west)+(0,0.9)$);
  \draw[-latex]($(n_PIController.west)+(-1.3,0.9)$) |- ($(n_PIController.west)+(0,-0.3)$);
  \draw[-latex]($(n_PIController.west)+(-1.3,0.3)$) -- ($(n_PIController.west)+(0,0.3)$);
  \node [circle,fill,inner sep=1pt] at ($(n_PIController.west)+(-1.3,0.9)$) {};
  \node [circle,fill,inner sep=1pt] at ($(n_PIController.west)+(-1.3,0.3)$) {};
  \draw[-latex](PI_n_output.east) -- (SC_uz_FOC_output.west);
  \end{scope}
  \end{scope}
  \begin{scope}[shift={(8,-4)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=cyan, fill opacity=0.2] (linearDecouppling) at (-0.5,5.5) {};
  \node[font=\footnotesize] at ($(linearDecouppling.west)+(0.6,-0.6)$) {config};
  \node[font=\footnotesize] at ($(linearDecouppling.west)+(0.6,0.6)$) {uz\_dq\_t};
  \node[font=\footnotesize] at ($(linearDecouppling.west)+(0.6,0.0)$) {$\omega_{el}$};
  \node[font=\footnotesize] at ($(linearDecouppling.east)+(-0.6,0)$) {uz\_dq\_t};
  \node[] at (-0.5,7) {linear Decouppling};
  \node[] at (-0.5,4) {uz\_FOC\_linear\_decouppling};
  \end{scope}
  \begin{scope}[shift={(13.5,-3.05)}]
  \node[draw, rectangle, minimum height=3.3cm, minimum width = 5cm, fill=magenta, fill opacity=0.2] (SVL) at (0,0) {};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,1.05)$) {uz\_dq\_t};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,-1)$) {uz\_dq\_t};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,-0.3)$) {$\omega_{el}$};
  \node[font=\footnotesize] at ($(SVL.west)+(0.95,0.4)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(SVL.east)+(-0.5,0.6)$) {uz\_dq};
  \node[font=\footnotesize] at ($(SVL.east)+(-0.95,-0.6)$) {ext\_clamping};
  \node[] at (0,2) {Space Vector Limitation};
  \node[] at (0,-2) {uz\_FOC\_SpaceVector\_Limitation};
  \end{scope}
  \begin{scope}[shift={(10,4.)}]
  \node[minimum size=0.7cm, draw, circle, fill=white] (add1) at (0,0) {};
  \node[] at (0,-0.25) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[font=\footnotesize] at ($(FOC_sample.east)+(-0.6,-3.45)$) {uz\_dq\_t};
  \draw[-latex](linearDecouppling.east) -| (add1.south);
  \draw(add1.east) -| ($(SVL.west)+(-0.3,1.05)$);
  \draw[-latex]($(SVL.west)+(-0.3,1.05)$) -- ($(SVL.west)+(0,1.05)$);
  \draw[-latex](FOC_current.east) -- (add1.west);
  \draw[-latex]($(SVL.east)+(0,0.6)$) -- ($(FOC_sample.east)+(-1.1,-3.45)$);
  \begin{scope}[shift={(-9.5,1.7)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm, fill=white] (Switch1) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \begin{scope}[shift={(-11,0.25)}]
  \node[minimum size=0.7cm, draw, circle, fill=white] (add2) at (0,0) {};
  \node[] at (0,0) {-$>$};
  \end{scope}
  \begin{scope}[shift={(-15,2.1)}]
  \node[minimum size=0.7cm, draw, circle, fill=white] (add4) at (0,0) {};
  \node[] at (0,0) {-$>$};
  \end{scope}
  \draw(FOC_speed.east)-|($(FOC_speed.east)+(0.5,-2.4)$);
  \draw[-latex]($(FOC_speed.east)+(0.5,-2.4)$) -| (add2.south);
  \draw[-latex]($(add4.east)+(1,0)$) |- (add2.west);
  \node [circle,fill,inner sep=1pt] at ($(add4.east)+(1,0)$) {};
  \node[font=\footnotesize] at ($(FOC_sample.west)+(5,-1)$) {-$>$iq\_ref\_Ampere};
  \node [circle,fill,inner sep=1pt] at ($(add4.east)+(1,-0.4)$) {};
  \draw[-latex](add2.north) |- ($(Switch1.west)+(0,-0.4)$);
  \draw[-latex](input_dq.east) -- ($(FOC_current.west)+(0,2)$);
  \draw[-latex](input_omega.south) |- ($(FOC_speed.west)+(0,-0.9)$);
  \draw($(SVL.east)+(0,-0.6)$) -| ($(SVL.east)+(1,-3.65)$);
  \draw[-latex]($(SVL.east)+(1,-3.65)$) -| (add4.south);
  \draw[-latex]($(Switch1.east)+(0.5,0)$) |- ($(FOC_speed.west)+(0,0.9)$);
  \draw[-latex](Switch1.east) |- ($(FOC_current.west)+(0.0,-2.3)$);
  \draw[-latex]($(FOC_sample.west)+(1.3,1.1)$) -- (add4.west);
  \node [circle,fill,inner sep=1pt] at ($(Switch1.east)+(0.5,0)$) {};
  \draw[-latex](add4.east) -- ($(Switch1.west)+(0,0.4)$);
  \draw[-latex]($(add4.east)+(1,-0.4)$) |- (Switch1.west);
  \node[font=\footnotesize] at ($(FOC_sample.west)+(5,0.5)$) {-$>$FOC\_Select};
  \node [circle,fill,inner sep=1pt] at ($(Switch1.east)+(0.5,-3.4)$) {};
  \draw($(Switch1.east)+(0.5,-3.4)$) -- ($(Switch1.east)+(13.1,-3.4)$);
  \draw($(input_omega.south)+(0,-0.35)$) -- ($(Switch1.east)+(12.8,-3.0)$);
  \node [circle,fill,inner sep=1pt] at ($(input_omega.south)+(0,-0.35)$) {};
  \draw($(FOC_current.west)+(-0.5,2)$) |-  ($(Switch1.east)+(12.5,-2.6)$);
  \node [circle,fill,inner sep=1pt] at ($(FOC_current.west)+(-0.5,2)$) {};
  \draw[-latex]($(Switch1.east)+(12.5,-2.6)$) |- ($(linearDecouppling.west)+(0,0.6)$);
  \draw[-latex]($(Switch1.east)+(12.8,-3)$) |- ($(linearDecouppling.west)+(0,0)$);
  \draw[-latex]($(Switch1.east)+(13.1,-3.4)$) |- ($(linearDecouppling.west)+(0,-0.6)$);
  \node [circle,fill,inner sep=1pt] at ($(Switch1.east)+(12.5,-2.6)$) {};
  \node [circle,fill,inner sep=1pt] at ($(Switch1.east)+(12.8,-3)$) {};
  \node [circle,fill,inner sep=1pt] at ($(Switch1.east)+(13.1,-3.4)$) {};
  \node[font=\scriptsize, rotate=90] at ($(linearDecouppling.west)+(-0.6,-2)$) {-$>$conifg\_lin\_Decoup};
  \draw[-latex]($(Switch1.east)+(12.5,-2.6)$) |- ($(SVL.west)+(0,-1)$);
  \draw[-latex]($(Switch1.east)+(12.8,-3)$) |- ($(SVL.west)+(0,-0.3)$);
  \draw[-latex]($(Switch1.east)+(13.1,-3.4)$) |- ($(SVL.west)+(0,0.4)$);
  \node[font=\scriptsize] at ($(SVL.west)+(-3,0.65)$) {-$>$ext\_clamping};
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(FOC_sample.east)+(2,-3.45)$) (output){output}; 
  \draw[-latex]($(FOC_sample.east)+(0,-3.45)$) -- (output.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_dq.west)+(-3,0)$) (input_dq2){input-dq-currents};
  \draw[-latex](input_dq2.east) -- ($(FOC_sample.west)+(0,5)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_Uzk.west)+(-3,0)$) (input_Uzk2){input-$U_{zk}$};
  \draw[-latex](input_Uzk2.east) -- ($(FOC_sample.west)+(0,3)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_omega.west)+(-3,0)$) (input_omega2){input-$\omega_{el}$};
  \draw[-latex](input_omega2.east) -- ($(FOC_sample.west)+(0,-1.75)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_FOC.west)+(-2.6,0)$) (input_uz_FOC2){input-uz\_FOC*};
  \draw[-latex](input_uz_FOC2.east) -- ($(FOC_sample.west)+(0,1.1)$);