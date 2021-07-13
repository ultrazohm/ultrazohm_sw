.. _uz_piController_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_PI_Controller_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the PI-Controller output. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
     float referenceValue = 1.5f;
     float actualValue = 1.1f;
     bool ext_clamping = false;
     float output = uz_PI_Controller_sample(PI_instance, referenceValue, actualValue, ext_clamping);
  }

Description
===========

Calculates the last sample of the PI-Controller. Has an integrated clamping circuit and an input port for an external
clamping signal. The error between the reference and actual value will be calculated inside the function. 

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`configuration struct <uz_piController_config>`.

.. tikz:: PI-Controller
  :align: left

  \usetikzlibrary{calc};
  \draw[rounded corners=6pt] (-26,-4.5) rectangle (-28,-4){};
  \node[font=\footnotesize] at (-27,-4.25) {actualValue};
  \draw[rounded corners=6pt] (-26.5,-2) rectangle (-27.5,-1.5){};
  \node[font=\footnotesize] at (-27,-1.75) {Ki};
  \draw[rounded corners=6pt] (-25.8,-3.25) rectangle (-28.2,-2.75){};
  \node[font=\footnotesize] at (-27,-3) {referenceValue};
  \begin{scope}[shift={(-24.4,-3)}]
  \draw (0,0) circle (10pt);
  \node[] at (0,-0.25) {-};
  \node at (-0.18,0) {\footnotesize{+}};
  \end{scope}
  \draw[-latex] (-25.8,-3) to (-24.72,-3);
  \draw[-latex] (-26,-4.25) -| (-24.42,-3.34);
  \node[draw, rectangle, minimum height=1.3cm] (Multiply1) at (-22.5,-2.6) {~~~\,\large{x}\,\,~~~};
  \draw(-26.5,-1.75) -| (-24.42,-2.3);
  \draw[-latex](-24.42,-2.3) to ($(Multiply1.west)+(0,0.3)$);
  \draw[-latex](-24.05,-3) to ($(Multiply1.west)+(0,-0.4)$);  
  \begin{scope}[shift={(-10.85,-2.2)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch1) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex] (Multiply1.east) to ($(Switch1.west)+(0,-0.4)$);
  \begin{scope}[shift={(-18,-4.5)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 3cm, fill=lightgray] (Clamping) at (0,0) {};
  \node[font=\footnotesize,rotate=90] at (0,0) {preIntegrator};
  \node[font=\footnotesize] at (0.9,0) {preSat};
  \node[font=\footnotesize] at (-0.9,0) {Clamp};
  \node[font=\footnotesize] at (0,-1.5) {Clamping circuit};
  \end{scope}
  \node[draw, rectangle, minimum height = 2.5cm] (OR) at (-18,0.5) {~~~\,OR\,\,~~~};
  \draw[-latex] ($(Clamping.north)+(0,0.75)$)--(Clamping.north);
  \draw[-](Clamping.west) -| ($(Clamping.west)+(-1,1.7)$);
  \draw[-, bend angle=45, bend left]($(Clamping.west)+(-1,1.7)$)to node[below,align=center]{}($(Clamping.west)+(-1,2.1)$);
  \draw[-]($(Clamping.west)+(-1,2.1)$) -- ($(Clamping.west)+(-1,4.3)$);
  \draw[-latex]($(Clamping.west)+(-1,4.3)$) -- ($(OR.west)+(0,-0.7)$);
  \draw[rounded corners=6pt] (-23.6,0.95) rectangle (-21.4,1.45){};
  \node[font=\footnotesize] at (-22.5,1.2) {ext\_clamping};
  \draw[-latex] ($(OR.west)+(-2.5,0.7)$)--($(OR.west)+(0,0.7)$);
  \node[draw, rectangle, minimum height=1.1cm] (delay) at (-15.5,0.5) {~~~\,\large{$\frac{1}{z}$}\,\,~~~};
  \draw[-latex](OR.east)--(delay.west);
  \draw(delay.east)-| ($(Switch1.west)+(-2.5,0)$);
  \draw[-latex]($(Switch1.west)+(-2.5,0)$) -- (Switch1.west);
  \node[draw, rectangle, minimum height=1.1cm] (Constant2) at (-13,0.5) {~~~\,0\,\,~~~};
  \draw[-latex](Constant2.south) |- ($(Switch1.west)+(0,0.4)$);
  \begin{scope}[shift={(-7.1,-2.78)}]
  \node[draw, rectangle, minimum height=2.5cm, minimum width = 2cm] (Discrete) at (0,0) {\large{$\frac{K~Ts}{z-1}$}};
  \draw(-0.9,-0.75) -| (-0.8,-0.5);  
  \draw(-0.8,-0.5) to (-0.7,-0.5);
  \draw(-0.7,-0.5) |- (-0.6,-0.75);
  \end{scope}
  \draw[-latex](Switch1.east) -- ($(Discrete.west)+(0,0.58)$);
  \draw[rounded corners=6pt] (-11.3,-3.65) rectangle (-10.3,-3.15){};
  \node[font=\footnotesize] at (-10.8,-3.4) {Reset};
  \draw[-latex]($(Discrete.west)+(-2.2,-0.58)$) -- ($(Discrete.west)+(0,-0.58)$); 
  \begin{scope}[shift={(-3.8,-2.78)}]
  \node[minimum size=0.7cm, draw, circle] at (0,0) (add1){};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \draw[-latex] (Discrete.east) -- (add1.west);
  \draw[rounded corners=6pt] (-0.4,-3) rectangle (-1.6,-2.5){};
  \node[font=\footnotesize] at (-1,-2.75) {ref\_out};
  \draw[-latex](add1.east)--($(add1.east)+(1.85,0)$);
  \draw[rounded corners=6pt] (-26.5,-9.75) rectangle (-27.5,-9.25){};
  \node[font=\footnotesize] at (-27,-9.5) {Kp};
  \node[draw, rectangle, minimum height=1.1cm] (Multiply2) at (-22.5,-9.2) {~~~\,\large{x}\,\,~~~};
  \draw[-latex]($(Multiply2.west)+(-3.25,-0.3)$)--($(Multiply2.west)+(0,-0.3)$);
  \draw[-latex]($(Multiply2.west)+(-0.5,6.2)$)|-($(Multiply2.west)+(0,0.3)$);
  \begin{scope}[shift={(-18.3,-8.8)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch1) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex](Multiply2.east)--($(Switch1.west)+(0,-0.4)$);
  \node[draw, rectangle, minimum height=1.1cm] (Constant1) at (-20.5,-8) {~~~\,0\,\,~~~};
  \draw(Constant1.east)-|($(Switch1.west)+(-0.3,0.4)$);
  \draw[-latex]($(Switch1.west)+(-0.3,0.4)$)--($(Switch1.west)+(0,0.4)$);
  \draw($(Switch1.west)+(10,5.44)$)|-($(Switch1.west)+(-2.2,1.7)$);
  \draw[-latex]($(Switch1.west)+(-2.2,1.7)$) |-(Switch1.west);
  \draw[-latex](Switch1.east)-|(add1.south);
  \node [circle,fill,inner sep=1pt] at (-9.31,-3.36){};
  \node [circle,fill,inner sep=1pt] at (-23.75,-3){};
  \node [circle,fill,inner sep=1pt] at (-18,-2.6){};
  \draw[-latex]($(Clamping.east)+(6.9,0)$) -- (Clamping.east);
  \draw[-, bend angle=45, bend left]($(Clamping.east)+(6.9,0)$)to node[below,align=center]{}($(Clamping.east)+(7.4,0)$);
  \draw[-]($(Clamping.east)+(7.4,0)$) -- ($(Clamping.east)+(12.4,0)$);
  \draw[-, bend angle=45, bend left]($(Clamping.east)+(12.4,0)$)to node[below,align=center]{}($(Clamping.east)+(12.9,0)$);
  \draw($(Clamping.east)+(12.9,0)$)-|($(Clamping.east)+(14,1.72)$);
  \node [circle,fill,inner sep=1pt] at (-2.5,-2.77){};
