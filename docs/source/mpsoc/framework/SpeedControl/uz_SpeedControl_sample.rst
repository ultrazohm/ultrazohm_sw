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
     float U_zk_Volts = 24.0f;
     bool ext_clamping = false;
     float id_ref_Ampere = 2.0f;
     struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, U_zk_Volts, id_ref_Ampere, config_PMSM, ext_clamping);
  }

Description
===========

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`configuration struct <uz_piController_config>`.

Calculates the reference speed into angular frequency and calculates the latest sample of the n-PI-Controller.
Furthermore, it has an input port for an external clamping signal.
This function includes a field weakening calculator. The ``id_ref`` current therefore will be calculated according to the following formulas.

.. math::

  U_{SV,max} &= \sqrt{\frac{U_{zk}}{\sqrt{3}}}\cdot 0.95\\
  \omega_c &= \frac{-R_{ph} \cdot \psi_{PM} \cdot I_{max} + \sqrt{R_{ph}^2 \cdot \psi_{PM}^2 \cdot I_{max}^2- (I_{max}^2 - R_{ph}^2) - U_{SV,max}^2}}{I_{max}^2 \cdot L_q^2 + \psi_{PM}^2}\\
  I_d &= \frac{\psi_{PM}}{L_d}\cdot(1- \frac{\omega_c}{\omega_{el}})\\
  a &= R_{ph}^2 + \omega_{el}^2 \cdot L_q^2\\
  b &= 2 \cdot R_{ph}^2 \omega_{el}^2 \cdot \psi_{PM}^2\\
  c &= I_d^2 \cdot R_{ph}^2 - U_{SV,max}^2 + \omega_{el}^2 \cdot (\psi_{PM}^2 + L_d^2 \cdot I_d^2 + 2\cdot \psi_{PM} \cdot L_d \cdot I_d)\\
  I_{q,limit} &= \frac{-b + \sqrt{b^2 - 4\cdot a \cdot c}}{2\cdot a}

If the machine is not in the field weakening territory, the input ``id_ref_Ampere`` current will be used. 
If the machine is inside the field weakening territory, the input ``id_ref_Ampere`` will only be used, if it's value is lower than the required ``id_fw`` current from the field weakening (i.e. ``id_ref_Ampere=-5`` and ``id_fw=-2`` will result in ``id_output=-5``).
The limits of the saturation inside the include PI-Controller will be adjusted with the calculated ``iq_limit`` value for each time step.

.. tikz:: PI-Controller
  :align: left
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows,  patterns

  \begin{scope}[shift={(0,0)}]
  \node[draw, rectangle, minimum height=6.8cm, minimum width = 15cm,  fill=white, draw opacity = 0.0] (FOC_speed) at (0,0) {};
  \node[draw, rectangle, minimum height=6.8cm, minimum width = 15cm,  fill=red, fill opacity=0.2] (white1) at (0,0) {};
  \node[font=\footnotesize] (CC_dq_output) at ($(FOC_speed.east)+(-0.6,-1.75)$) {uz\_dq\_t};
  \node[font=\footnotesize] (SC_ref) at ($(FOC_speed.west)+(0.9,-0.85)$) {n\_ref\_rpm};
  \node[font=\footnotesize] (SC_pole) at ($(FOC_speed.west)+(1.1,-0)$) {config\_PMSM};
  \node[font=\footnotesize] (CC_uz_PI) at ($(FOC_speed.west)+(1.5,-1.45)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] (CC_ext) at ($(FOC_speed.west)+(1.13,-2.65)$) {ext\_clamping};
  \node[font=\footnotesize] (SC_actual) at ($(FOC_speed.west)+(1.8,-2.05)$) {omega\_el\_rad\_per\_sec};
  \node[font=\footnotesize] (SC_id) at ($(FOC_speed.west)+(1.3,1.8)$) {id\_ref\_Ampere};
  \node[font=\footnotesize] (SC_Uzk) at ($(FOC_speed.west)+(1.06,2.4)$) {U\_zk\_Volts};
  \node[] at ($(FOC_speed.south)+(0.0,-0.3)$) {uz\_SpeedControl\_sample};
  \begin{scope}[shift={(4,-1.75)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (n_PIController) at (0,0) {};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.35,0.3)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] at ($(n_PIController.west)+(0.96,-0.3)$) {actualValue};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.16,0.9)$) {referenceValue};
  \node[font=\footnotesize] at ($(n_PIController.west)+(1.08,-0.9)$) {ext\_clamping};
  \node[font=\footnotesize] at ($(n_PIController.east)+(-0.6,0)$) {output};
  \node[] at (0,-1.38) {uz\_PI\_Controller\_sample};
  \end{scope}
  \begin{scope}[shift={(4,1.5)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 4cm, fill=lightgray] (FW) at (0,0) {};
  \node[font=\footnotesize] at ($(FW.west)+(1.1,-0.3)$) {config\_PMSM};
  \node[font=\footnotesize] at ($(FW.west)+(1.7,-0.9)$) {omega\_el\_rad\_per\_sec};
  \node[font=\footnotesize] at ($(FW.west)+(1.08,0.9)$) {U\_zk\_Volts};
  \node[font=\footnotesize] at ($(FW.west)+(1.2,0.3)$) {id\_ref\_Ampere};
  \node[font=\footnotesize] at ($(FW.east)+(-0.6,0.3)$) {id\_fw};
  \node[font=\footnotesize] at ($(FW.east)+(-0.6,-0.3)$) {iq\_limit};
  \node[] at (0,1.3) {uz\_SpeedControll\_field\_weakening};
  \end{scope}
  \begin{scope}[shift={(0.5,-1.45)}]
  \node[draw, rectangle, minimum height=0.8cm, minimum width =2.3cm, fill=lightgray] (limits) {};
  \node[font=\tiny,align=center] at (0,0) {change saturation \\ limits};
  \end{scope}
  \node[isosceles triangle, isosceles triangle apex angle=18,draw,minimum size =0.5cm,font=\tiny] (gain) at ($(FOC_speed.west)+(4,-0.85)$) {$(2\cdot\pi\cdot p)/60$};
  \draw[-latex](CC_uz_PI.east) -- (limits.west);
  \draw[-latex](limits.east) -- ($(n_PIController.west)+(0,0.3)$);
  \draw[-latex](CC_ext.east) -- ($(n_PIController.west)+(0,-0.9)$);
  \draw[-latex](gain.east) -- ($(n_PIController.west)+(0,0.9)$);
  \draw[-latex](SC_actual.east) -- ($(n_PIController.west)+(0,-0.3)$);
  \draw[-latex](SC_id.east) -- ($(FW.west)+(0,0.3)$);
  \draw[-latex](SC_Uzk.east) -- ($(FW.west)+(0,0.9)$);
  \draw[-latex](n_PIController.east) -- (CC_dq_output.west);
  \draw[-latex](SC_ref.east) -- (gain.west);
  \draw[-latex](SC_pole.east) -| (gain.north);
  \draw[-latex]($(n_PIController.west)+(-3,-0.3)$) |- ($(FW.west)+(0,-0.9)$);
  \node [circle,fill,inner sep=1pt] at ($(n_PIController.west)+(-3,-0.3)$){};
  \draw[-latex](SC_pole.north) |- ($(FW.west)+(0,-0.3)$);
  \node[font=\scriptsize] at ($(SC_pole.east)+(1,0.15)$) {.polePairs};
  \draw[-latex]($(FW.east)+(0,0.3)$) -| (CC_dq_output.north);
  \draw($(FW.east)+(0,-0.3)$) -| ($(FW.east)+(0.5,-1.75)$);
  \draw[-latex]($(FW.east)+(0.5,-1.75)$) -| (limits.north);
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(FOC_speed.east)+(2,-1.75)$) (output){output}; 
  \draw[-latex]($(FOC_speed.east)+(0,-1.75)$) -- (output.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(CC_uz_PI.west)+(-3,0)$) (input_PI){PI-Controller* instance};
  \draw[-latex](input_PI.east) -- ($(CC_uz_PI.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(CC_ext.west)+(-3,0)$) (input_ext){ext\_clamping};
  \draw[-latex](input_ext.east) -- ($(CC_ext.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_ref.west)+(-3,0)$) (input_ref){n\_ref\_rpm};
  \draw[-latex](input_ref.east) -- ($(SC_ref.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_pole.west)+(-3,0)$) (input_pole){uz\_PMSM\_t config};
  \draw[-latex](input_pole.east) -- ($(SC_pole.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_actual.west)+(-3,0)$) (input_actual){omega\_el\_rad\_per\_sec};
  \draw[-latex](input_actual.east) -- ($(SC_actual.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_id.west)+(-3,0)$) (input_id){id\_ref\_Ampere};
  \draw[-latex](input_id.east) -- ($(SC_id.west)+(-0.15,0)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_Uzk.west)+(-3,0)$) (input_Uzk){U\_zk\_Volts};
  \draw[-latex](input_Uzk.east) -- ($(SC_Uzk.west)+(-0.15,0)$);
