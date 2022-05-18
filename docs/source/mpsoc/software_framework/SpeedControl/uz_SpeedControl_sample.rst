.. _uz_SpeedControl_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_SpeedControl_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the SpeedControl output. SpeedControl-Instance via :ref:`init-function <uz_SpeedControl_init>`

  int main(void) {
     float omega_m_rad_per_sec = 1.5f;
     float n_ref_rpm = 500.0f;
     float V_dc_volts = 24.0f;
     float id_ref_Ampere = 2.0f;
     struct uz_3ph_dq_t output = uz_SpeedControl_sample(instance, omega_m_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere);
  }

Description
===========

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`configuration struct <uz_piController_config>`.

Calculates the reference speed into angular frequency and calculates the latest sample of the n-PI-Controller.
Furthermore, an external clamping signal can be set via a dedicated :ref:`set function <uz_SpeedControl_set_ext_clamping>`.
This function includes a field weakening calculator, which can be turned on or off. 
If the field weakening is turned off, the input ``id_ref_Ampere`` will be given out. 
The ``id_ref`` current therefore will be calculated according to the following formulas.

.. math::

  V_{SV,max} &= \sqrt{\frac{V_{DC}}{\sqrt{3}}}\cdot 0.95\\
  \omega_c &= \frac{-R_{ph} \cdot \psi_{PM} \cdot I_{max} + \sqrt{R_{ph}^2 \cdot \psi_{PM}^2 \cdot I_{max}^2- (I_{max}^2 - R_{ph}^2) - V_{SV,max}^2}}{I_{max}^2 \cdot L_q^2 + \psi_{PM}^2}\\
  I_d &= \frac{\psi_{PM}}{L_d}\cdot(1- \frac{\omega_c}{\omega_{el}})\\
  a &= R_{ph}^2 + \omega_{el}^2 \cdot L_q^2\\
  b &= 2 \cdot R_{ph}^2 \omega_{el}^2 \cdot \psi_{PM}^2\\
  c &= I_d^2 \cdot R_{ph}^2 - V_{DC,max}^2 + \omega_{el}^2 \cdot (\psi_{PM}^2 + L_d^2 \cdot I_d^2 + 2\cdot \psi_{PM} \cdot L_d \cdot I_d)\\
  I_{q,limit} &= \frac{-b + \sqrt{b^2 - 4\cdot a \cdot c}}{2\cdot a}

If the machine is not in the field weakening territory, the input ``id_ref_Ampere`` current will be used. 
If the machine is inside the field weakening territory, the input ``id_ref_Ampere`` will only be used, if it's value is lower than the required ``id_fw`` current from the field weakening (i.e. ``id_ref_Ampere=-5`` and ``id_fw=-2`` will result in ``id_output=-5``).
The limits of the saturation inside the include PI-Controller will be adjusted with the calculated ``iq_limit`` value for each time step.

.. tikz:: PI-Controller
  :align: left
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows,  patterns

  \begin{scope}[shift={(0,0)}]
  \node[ rectangle, minimum height=6.8cm, minimum width = 15cm] (FOC_speed) at (0,0) {};
  \node[font=\footnotesize] (CC_dq_output) at ($(FOC_speed.east)+(-0,-1.75)$) {uz\_3ph\_dq\_t};
  \node[font=\footnotesize] (SC_ref) at ($(FOC_speed.west)+(1.06,-0.85)$) {n\_ref\_rpm};
  \node[font=\footnotesize] (SC_pole) at ($(FOC_speed.west)+(1.06,+1.2)$) {config\_PMSM};
  \node[font=\footnotesize] (CC_uz_PI) at ($(FOC_speed.west)+(1.06,-1.45)$) {uz\_PI\_Controller*};
  \node[font=\footnotesize] (CC_ext) at ($(FOC_speed.west)+(1.06,-2.65)$) {ext\_clamping};
  \node[font=\footnotesize] (SC_actual) at ($(FOC_speed.west)+(1.56,-2.05)$) {omega\_m\_rad\_per\_sec};
  \node[font=\footnotesize] (SC_id) at ($(FOC_speed.west)+(1.06,1.8)$) {id\_ref\_Ampere};
  \node[font=\footnotesize] (SC_Uzk) at ($(FOC_speed.west)+(1.06,2.4)$) {U\_zk\_Volts};
  \node[font=\footnotesize] (SC_EnableFW) at ($(FOC_speed.west)+(1.85,3.4)$) {is\_field\_weakening\_active};
  \node[](sample_label) at ($(FOC_speed.south)+(0.0,-0.2)$) {uz\_SpeedControl\_sample};
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
  \node[font=\footnotesize] at ($(FW.west)+(1.7,-0.9)$) {omega\_m\_rad\_per\_sec};
  \node[font=\footnotesize] at ($(FW.west)+(1.08,0.9)$) {U\_zk\_Volts};
  \node[font=\footnotesize] at ($(FW.west)+(1.2,0.3)$) {id\_ref\_Ampere};
  \node[font=\footnotesize] at ($(FW.east)+(-0.6,0.3)$) {id\_fw};
  \node[font=\footnotesize] at ($(FW.east)+(-0.6,-0.3)$) {iq\_limit};
  \node[] at (0,1.3) {uz\_SpeedControl\_field\_weakening};
  \end{scope}
  \begin{scope}[shift={(0.5,-1.45)}]
  \node[draw, rectangle, minimum height=0.8cm, minimum width =2.3cm, fill=lightgray] (limits) {};
  \node[font=\tiny,align=center] at (0,0) {change saturation \\ limits};
  \end{scope}
  \begin{scope}[shift={(7.5,0)},rotate=-90]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm,transform shape] (Switch1) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,-0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \node[font=\footnotesize,rotate=90] (SC_id2) at ($(FW.east)+(1.9,1.8)$) {id\_ref\_Ampere};
  \draw[-latex](SC_id2.west) -- ($(Switch1.west)+(0.4,0)$);
  \draw[-latex](Switch1.east) -- (CC_dq_output.north);
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
  \draw[-latex]($(n_PIController.west)+(-3,-0.3)$) |- ($(FW.west)+(0,-0.9)$);
  \node [circle,fill,inner sep=1pt] at ($(n_PIController.west)+(-3,-0.3)$){};
  \draw[-latex](SC_pole.east) -- ($(FW.west)+(0,-0.3)$);
  \draw[-latex]($(FW.east)+(0,0.3)$) -| ($(Switch1.west)+(-0.4,0)$) ;
  \draw($(FW.east)+(0,-0.3)$) -| ($(FW.east)+(0.5,-1.75)$);
  \draw[-latex]($(FW.east)+(0.5,-1.75)$) -| (limits.north);
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm] at ($(FOC_speed.east)+(2.5,-1.75)$) (output){output}; 
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(CC_uz_PI.west)+(-3,0)$) (input_PI){PI-Controller* instance};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_ref.west)+(-2.8,0)$) (input_ref){n\_ref\_rpm};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_actual.west)+(-3,0)$) (input_actual){omega\_m\_rad\_per\_sec};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_id.west)+(-2.8,0)$) (input_id){id\_ref\_Ampere};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.4cm,font=\footnotesize] at ($(SC_Uzk.west)+(-2.8,0)$) (input_Uzk){U\_zk\_Volts};
  \begin{scope}[on background layer]
  \node[draw, rectangle, minimum width=16.5cm, fit=(SC_EnableFW) (SC_id2)(Switch1)(sample_label) (n_PIController),fill=red, fill opacity=0.2] (Block) at (0,0) {};
  \end{scope}
  \draw[-latex]($(CC_uz_PI.west)+(-0,0)$) |- (SC_pole.west);
  \draw[-latex]($(CC_uz_PI.west)+(-0,0)$) |- (SC_EnableFW.west);
  \draw[-latex]($(CC_uz_PI.west)+(-0,0)$) |- (CC_ext.west);
  \node [circle,fill,inner sep=1pt] at ($(CC_uz_PI.west)+(-0,0)$) {};
  \draw[-latex]($(FOC_speed.east)+(0.8,-1.75)$) -- (output.west);
  \draw[-latex](input_PI.east) -- ($(Block.west)+(0,-1.45)$);
  \draw[-latex](input_ref.east) --  ($(Block.west)+(0,-0.85)$);
  \draw[-latex](input_actual.east) --  ($(Block.west)+(0,-2.05)$);
  \draw[-latex](input_id.east) --  ($(Block.west)+(0,1.8)$);
  \draw[-latex](input_Uzk.east) --  ($(Block.west)+(0,2.4)$);
  \draw[-latex](SC_EnableFW.east)  -| (Switch1.west);
