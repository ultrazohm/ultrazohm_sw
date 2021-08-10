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
  \node[draw, rectangle, minimum height=11cm, minimum width = 28cm, fill=blue, fill opacity=0.2] (FOC_sample) at (0,1) {};
  \node[font=\footnotesize] (input_dq_ref) at ($(FOC_sample.west)+(0.7,1.55)$) {uz\_dq\_t};
  \node[font=\footnotesize] (input_dq_meas) at ($(FOC_sample.west)+(0.7,0.25)$) {uz\_dq\_t};
  \node[font=\footnotesize] (input_omega) at ($(FOC_sample.west)+(0.7,-4)$) {$\omega_{el}$};
  \node[font=\footnotesize] (input_Uzk) at ($(FOC_sample.west)+(0.7,-5)$) {$U_{zk}$};
  \node[font=\footnotesize] (input_FOC) at ($(FOC_sample.west)+(0.75,3.05)$) {uz\_FOC*};
    \node[font=\footnotesize] (output_dq)at ($(FOC_sample.east)+(-0.6,0.85)$) {uz\_dq\_t};
  \node[font=\large] at ($(FOC_sample.south)+(0,-0.5)$) {uz\_FOC\_sample};
  \begin{scope}[shift={(-6,1.75)}]
  \node[draw, rectangle, minimum height=8.3cm, minimum width = 10cm,  fill=white, draw opacity = 0.0] (FOC_current) at (0,0) {};
  \node[draw, rectangle, minimum height=8.3cm, minimum width = 10cm,  fill=green, fill opacity=0.2] (white1) at (0,0) {};
  \node[font=\footnotesize] (CC_dq_output) at ($(FOC_current.east)+(-0.6,2)$) {uz\_dq\_t};
  \node[font=\footnotesize] (CC_dq_ref) at ($(FOC_current.west)+(0.65,0.75)$) {uz\_dq\_t};
  \node[font=\footnotesize] (CC_uz_FOC) at ($(FOC_current.west)+(0.65,2.31)$) {uz\_FOC*};
  \node[font=\footnotesize] (CC_dq_meas) at ($(FOC_current.west)+(0.65,-0.5)$) {uz\_dq\_t};
  \node[] at ($(FOC_current.south)+(0.0,0.3)$) {uz\_FOC\_CurrentControl};
  \begin{scope}[shift={(1.5,2)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (iq_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(1.2,0.9)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(0.86,-0.9)$) {actualValue};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(1.06,-0.3)$) {referenceValue};
  \node[font=\footnotesize] at ($(iq_PIController.west)+(0.98,0.3)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(iq_PIController.east)+(-0.5,0)$) {output};
  \node[] at (0,1.4) {$i_q$-Controller};
  \node[] at (0,-1.4) {uz\_PI\_Controller\_sample};
  \end{scope}
  \begin{scope}[shift={(1.5,-2)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (id_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(id_PIController.west)+(1.2,-0.9)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(id_PIController.west)+(0.86,0.9)$) {actualValue};
  \node[font=\footnotesize] at ($(id_PIController.west)+(1.06,0.3)$) {referenceValue};
  \node[font=\footnotesize] at ($(id_PIController.west)+(0.98,-0.3)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(id_PIController.east)+(-0.5,0)$) {output};
  \node[] at (0,1.4) {$i_d$-Controller};
  \node[] at (0,-1.4) {uz\_PI\_Controller\_sample};
  \end{scope}
  \draw(CC_uz_FOC.east) -- ($(CC_uz_FOC.east)+(0.5,0)$);
  \node [circle,fill,inner sep=1pt] at ($(CC_uz_FOC.east)+(0.5,0)$) {};
  \draw[-latex]($(CC_uz_FOC.east)+(0.5,0)$) |- ($(iq_PIController.west)+(0,0.9)$);
  \draw[-latex]($(CC_uz_FOC.east)+(0.5,0)$) |- ($(id_PIController.west)+(0,-0.9)$);
  \draw[-latex]($(CC_uz_FOC.east)+(0.5,-4.6)$) -- ($(id_PIController.west)+(0,-0.3)$);
  \node [circle,fill,inner sep=1pt] at ($(CC_uz_FOC.east)+(0.5,-4.6)$){};
  \draw[-latex]($(CC_uz_FOC.east)+(0.5,0)$) -- ($(iq_PIController.west)+(0,0.3)$);
  \draw(CC_dq_ref.east) -- ($(CC_dq_ref.east)+(0.47,0)$);
  \draw[-, bend angle=45, bend left]($(CC_dq_ref.east)+(0.47,0)$)to node[below,align=center]{}($(CC_dq_ref.east)+(0.67,0)$);
  \draw[-]($(CC_dq_ref.east)+(0.67,0)$) -- ($(CC_dq_ref.east)+(0.8,0)$);
  \node [circle,fill,inner sep=1pt] at ($(CC_dq_ref.east)+(0.8,0)$){};
  \draw[-latex]($(CC_dq_ref.east)+(0.8,0)$) |- ($(iq_PIController.west)+(0,-0.3)$);
  \draw[-latex]($(CC_dq_ref.east)+(0.8,0)$) |- ($(id_PIController.west)+(0,0.3)$);
  \draw(CC_dq_meas.east) -- ($(CC_dq_meas.east)+(0.47,0)$);
  \draw[-, bend angle=45, bend left]($(CC_dq_meas.east)+(0.47,0)$)to node[below,align=center]{}($(CC_dq_meas.east)+(0.95,0)$);
  \draw[-]($(CC_dq_meas.east)+(0.95,0)$) -- ($(CC_dq_meas.east)+(1.1,0)$);
  \node [circle,fill,inner sep=1pt] at ($(CC_dq_meas.east)+(1.1,0)$){};
  \draw[-latex]($(CC_dq_meas.east)+(1.1,0)$) |- ($(iq_PIController.west)+(0,-0.9)$);
  \draw[-latex]($(CC_dq_meas.east)+(1.1,0)$) |- ($(id_PIController.west)+(0,0.9)$);
  \draw[-latex](id_PIController.east) -| (CC_dq_output.south);
  \draw[-latex](iq_PIController.east) -- (CC_dq_output.west);
  \end{scope}
  \begin{scope}[shift={(3,-3.5)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=cyan, fill opacity=0.2] (linearDecouppling) at (-0.5,5.5) {};
  \node[font=\footnotesize] at ($(linearDecouppling.west)+(0.6,-0.6)$) {config};
  \node[font=\footnotesize] at ($(linearDecouppling.west)+(0.6,0.6)$) {uz\_dq\_t};
  \node[font=\footnotesize] at ($(linearDecouppling.west)+(0.6,0.0)$) {$\omega_{el}$};
  \node[font=\footnotesize] at ($(linearDecouppling.east)+(-0.6,0)$) {uz\_dq\_t};
  \node[] at (-0.5,7) {linear Decouppling};
  \node[] at (-0.5,4) {uz\_FOC\_linear\_decouppling};
  \end{scope}
  \begin{scope}[shift={(10,2.45)}]
  \node[draw, rectangle, minimum height=3.8cm, minimum width = 5cm, fill=magenta, fill opacity=0.2] (SVL) at (0,0) {};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,1.3)$) {uz\_dq\_t};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,0.6)$) {uz\_dq\_t};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,0)$) {$\omega_{el}$};
  \node[font=\footnotesize] at ($(SVL.west)+(0.95,-0.6)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(SVL.west)+(0.6,-1.3)$) {$U_{zk}$};
  \node[font=\footnotesize] at ($(SVL.east)+(-0.5,-0.6)$) {uz\_dq};
  \node[font=\footnotesize] at ($(SVL.east)+(-0.95,0.6)$) {ext\_clamping};
  \node[] at (0,2.2) {Space Vector Limitation};
  \node[] at (0,-2.2) {uz\_FOC\_SpaceVector\_Limitation};
  \end{scope}
  \begin{scope}[shift={(5,3.75)}]
  \node[minimum size=0.7cm, draw, circle, fill=white] (add1) at (0,0) {};
  \node[] at (0,-0.25) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \draw[-latex](linearDecouppling.east) -| (add1.south);
  \draw[-latex](add1.east) -- ($(SVL.west)+(0,1.3)$);
  \draw[-latex]($(FOC_current.east)+(0,2)$) -- (add1.west);
  \draw($(input_dq_meas)+(1.5,0)$) |- ($(linearDecouppling.west)+(-1.2,-4.5)$);
  \draw[-latex]($(linearDecouppling.west)+(-1.2,-4.5)$) |- ($(linearDecouppling.west)+(0,0.6)$);
  \node [circle,fill,inner sep=1pt] at ($(linearDecouppling.west)+(-1.2,-4.5)$){};
  \node [circle,fill,inner sep=1pt] at ($(input_dq_meas)+(1.5,0)$){};
  \draw(input_omega.east) -- ($(linearDecouppling.west)+(-1,-5)$);
  \draw[-latex]($(linearDecouppling.west)+(-1,-5)$) |- (linearDecouppling.west);
  \node [circle,fill,inner sep=1pt] at ($(linearDecouppling.west)+(-1,-5)$){};
  \draw($(linearDecouppling.west)+(-1.2,-4.5)$) -- ($(linearDecouppling.west)+(5,-4.5)$);
  \draw[-latex]($(linearDecouppling.west)+(5,-4.5)$) |- ($(SVL.west)+(0,0.6)$);
  \draw($(linearDecouppling.west)+(-1,-5)$) -- ($(linearDecouppling.west)+(5.5,-5)$);
  \draw[-latex]($(linearDecouppling.west)+(5.5,-5)$) |- (SVL.west);
  \draw($(input_FOC)+(0.9,0)$) -- ($(input_FOC)+(0.9,-1.4)$);
  \draw[-, bend angle=45, bend left]($(input_FOC)+(0.9,-1.4)$) to node[below,align=center]{}($(input_FOC)+(0.9,-1.6)$);
  \draw[-]($(input_FOC)+(0.9,-1.6)$) -- ($(input_FOC)+(0.9,-2.7)$);
  \draw[-, bend angle=45, bend left]($(input_FOC)+(0.9,-2.7)$) to node[below,align=center]{}($(input_FOC)+(0.9,-2.9)$);
  \draw[-]($(input_FOC)+(0.9,-2.9)$) -- ($(input_FOC)+(0.9,-6.95)$);
  \draw[-, bend angle=45, bend left]($(input_FOC)+(0.9,-6.95)$) to node[below,align=center]{}($(input_FOC)+(0.9,-7.15)$);
  \draw[-]($(input_FOC)+(0.9,-7.15)$) |- ($(linearDecouppling.west)+(-0.8,-5.5)$);
  \node [circle,fill,inner sep=1pt] at ($(linearDecouppling.west)+(-0.8,-5.5)$){};
  \draw[-latex]($(linearDecouppling.west)+(-0.8,-5.5)$) |- ($(linearDecouppling.west)+(0,-0.6)$);
  \draw($(linearDecouppling.west)+(-0.8,-5.5)$) |- ($(linearDecouppling.west)+(6,-5.5)$);
  \draw[-latex]($(linearDecouppling.west)+(6,-5.5)$) |- ($(SVL.west)+(0,-0.6)$);
  \draw(input_Uzk.east) -- ($(linearDecouppling.west)+(6.5,-6)$);
  \draw[-latex]($(linearDecouppling.west)+(6.5,-6)$) |- ($(SVL.west)+(0,-1.3)$);
  \node[font=\scriptsize,rotate=90] at ($(SVL.west)+(-1.15,-3)$) {-$>$ext\_clamping};
  \draw[-latex]($(SVL.east)+(0,-0.6)$) -- (output_dq.west);
  \draw($(SVL.east)+(0,0.6)$) -| ($(SVL.east)+(0.5,3.65)$);
  \draw[-latex]($(SVL.east)+(0.5,3.65)$) -| ($(input_FOC.east)+(0.75,0)$);
  \node [circle,fill,inner sep=1pt] at ($(input_FOC.east)+(0.75,0)$){};
  \end{scope}
  \draw[-latex](input_FOC.east) -- ($(FOC_current.west)+(0,2.3)$);
  \draw[-latex](input_dq_ref.east) -- ($(FOC_current.west)+(0,0.8)$);
  \draw[-latex](input_dq_meas.east) -- ($(FOC_current.west)+(0,-0.5)$);
  \node[font=\scriptsize, rotate=90] at ($(linearDecouppling.west)+(-0.6,-2.6)$) {-$>$config.config\_lin\_decoupling};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(FOC_sample.east)+(2,0.85)$) (output){output}; 
  \draw[-latex]($(FOC_sample.east)+(0,0.85)$) -- (output.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_dq_ref.west)+(-3,0)$) (input_dq2){reference-dq-currents};
  \draw[-latex](input_dq2.east) -- ($(FOC_sample.west)+(0,1.55)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_dq_meas.west)+(-3,0)$) (input_dq3){input-dq-currents};
  \draw[-latex](input_dq3.east) -- ($(FOC_sample.west)+(0,0.25)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_Uzk.west)+(-3,0)$) (input_Uzk2){input-$U_{zk}$};
  \draw[-latex](input_Uzk2.east) -- ($(FOC_sample.west)+(0,-5)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_omega.west)+(-3,0)$) (input_omega2){input-$\omega_{el}$};
  \draw[-latex](input_omega2.east) -- ($(FOC_sample.west)+(0,-4)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(input_FOC.west)+(-2.6,0)$) (input_uz_FOC2){input-uz\_FOC*};
  \draw[-latex](input_uz_FOC2.east) -- ($(FOC_sample.west)+(0,3.05)$);