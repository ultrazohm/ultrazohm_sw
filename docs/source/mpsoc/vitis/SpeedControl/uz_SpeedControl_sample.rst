.. _uz_SpeedControl_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_SpeedControl_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the SpeedControl output. PI-Instance via :ref:`init-function <uz_SpeedControl_init>`

  int main(void) {
     float omega_el_rad_per_sec = 1.5f;
     float n_ref_rpm = 500.0f;
     bool ext_clamping = false;
     float id_ref_Ampere = 2.0f;
     float polePairs = 4.0f;
     struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, id_ref_Ampere, polePairs, ext_clamping);
  }

Description
===========

Calculates the reference speed into angular frequency and calculates the latest sample of the n-PI-Controller.
Furthermore, it has an input port for an external clamping signal.
The id-reference current will be passed straight through into the ``uz_dq_t`` return struct without any changes.

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`configuration struct <uz_piController_config>`.

.. tikz:: PI-Controller
  :align: left
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows,  patterns

  \begin{scope}[shift={(0,0)}]
  \node[draw, rectangle, minimum height=4.3cm, minimum width = 15cm,  fill=white, draw opacity = 0.0] (FOC_speed) at (0,0) {};
  \node[draw, rectangle, minimum height=4.3cm, minimum width = 15cm,  fill=red, fill opacity=0.2] (white1) at (0,0) {};
  \node[font=\footnotesize] (CC_dq_output) at ($(FOC_speed.east)+(-0.6,0.5)$) {uz\_dq\_t};
  \node[font=\footnotesize] (SC_ref) at ($(FOC_speed.west)+(0.9,-0.4)$) {n\_ref\_rpm};
  \node[font=\footnotesize] (SC_pole) at ($(FOC_speed.west)+(0.9,-1)$) {polePairs};
  \node[font=\footnotesize] (CC_uz_PI) at ($(FOC_speed.west)+(1.5,1.4)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] (CC_ext) at ($(FOC_speed.west)+(1.13,0.8)$) {ext\_clamping};
  \node[font=\footnotesize] (SC_actual) at ($(FOC_speed.west)+(1.8,0.2)$) {omega\_el\_rad\_per\_sec};
  \node[font=\footnotesize] (SC_id) at ($(FOC_speed.west)+(1.3,-1.6)$) {id\_ref\_Ampere};
  \node[] at ($(FOC_speed.south)+(0.0,-0.3)$) {uz\_SpeedControl\_sample};
  \begin{scope}[shift={(4,0.5)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (n_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.35,0.9)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(n_PIController.west)+(0.96,-0.3)$) {actualValue};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.16,-0.9)$) {referenceValue};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.08,0.3)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(n_PIController.east)+(-0.6,0)$) {output};
  \node[] at (0,-1.4) {uz\_PI\_Controller\_sample};
  \end{scope}
  \node[isosceles triangle, isosceles triangle apex angle=15,draw,minimum size =0.5cm,font=\tiny] (gain) at ($(FOC_speed.west)+(4,-0.4)$) {$(2\cdot\pi\cdot p)/60$};
  \draw[-latex](CC_uz_PI.east) -- ($(n_PIController.west)+(0,0.9)$);
  \draw[-latex](CC_ext.east) -- ($(n_PIController.west)+(0,0.3)$);
  \draw[-latex](gain.east) -- ($(n_PIController.west)+(0,-0.9)$);
  \draw[-latex](SC_actual.east) -- ($(n_PIController.west)+(0,-0.3)$);
  \draw[-latex](SC_id.east) -| (CC_dq_output.south);
  \draw[-latex](n_PIController.east) -- (CC_dq_output.west);
  \draw[-latex](SC_ref.east) -- (gain.west);
  \draw[-latex](SC_pole.east) -| (gain.south);
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(FOC_speed.east)+(2,0.5)$) (output){output}; 
  \draw[-latex]($(FOC_speed.east)+(0,0.5)$) -- (output.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(CC_uz_PI.west)+(-3,0)$) (input_PI){PI-Controller* instance};
  \draw[-latex](input_PI.east) -- ($(CC_uz_PI.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(CC_ext.west)+(-3,0)$) (input_ext){ext\_clamping};
  \draw[-latex](input_ext.east) -- ($(CC_ext.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_ref.west)+(-3,0)$) (input_ref){n\_ref\_rpm};
  \draw[-latex](input_ref.east) -- ($(SC_ref.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_pole.west)+(-3,0)$) (input_pole){polePairs};
  \draw[-latex](input_pole.east) -- ($(SC_pole.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_actual.west)+(-3,0)$) (input_actual){omega\_el\_rad\_per\_sec};
  \draw[-latex](input_actual.east) -- ($(SC_actual.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_id.west)+(-3,0)$) (input_id){id\_ref\_Ampere};
  \draw[-latex](input_id.east) -- ($(SC_id.west)+(-0.15,0)$);
