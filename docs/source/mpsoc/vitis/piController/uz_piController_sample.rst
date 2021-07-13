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
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-4.25)}](actual){actualValue};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-1.75)}](Ki){Ki};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-3)}](ref){referenceValue};
  \begin{scope}[shift={(-24.4,-3)}]
  \node[minimum size=0.7cm, draw, circle] (add) at (0,0) {};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[draw, rectangle, minimum height=1.3cm] (Multiply1) at (-22.5,-2.6) {~~~\,\large{x}\,\,~~~};
  \draw[-latex](ref.east)--(add.west);
  \draw[-latex](actual.east)-|(add.south);
  \draw(Ki.east)-|($(Multiply1.west)+(-1.3,0.3)$);
  \draw[-latex]($(Multiply1.west)+(-1.3,0.3)$) to ($(Multiply1.west)+(0,0.3)$);
  \draw[-latex](add.east) to ($(Multiply1.west)+(0,-0.4)$);  
  \begin{scope}[shift={(-12.5,-2.2)}]
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
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-22.5,1.2)}](ext){ext\_clamping};
  \draw[-latex] (ext.east)--($(OR.west)+(0,0.7)$);
  \node[draw, rectangle, minimum height=1.1cm] (delay) at (-16,0.5) {~~~\,\large{$\frac{1}{z}$}\,\,~~~};
  \draw[-latex](OR.east)--(delay.west);
  \draw(delay.east)-| ($(Switch1.west)+(-1.5,0)$);
  \draw[-latex]($(Switch1.west)+(-1.5,0)$) -- (Switch1.west);
  \node[draw, rectangle, minimum height=1.1cm] (Constant2) at (-14,0.5) {~~~\,0\,\,~~~};
  \draw[-latex](Constant2.south) |- ($(Switch1.west)+(0,0.4)$);
  \begin{scope}[shift={(-4,-1.8)}]
  \node[minimum size=0.7cm, draw, circle] (add1) at (0,0) {};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(0.5,-1.8)}](out){output};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-9.5)}](Kp){Kp};
  \node[draw, rectangle, minimum height=1.1cm] (Multiply2) at (-22.5,-9.2) {~~~\,\large{x}\,\,~~~};
  \draw[-latex](Kp.east)--($(Multiply2.west)+(0,-0.3)$);
  \draw[-latex]($(add.east)+(0.4,0)$)|-($(Multiply2.west)+(0,0.3)$);
  \node [circle,fill,inner sep=1pt] at ($(add.east)+(0.4,0)$){};
  \begin{scope}[shift={(-18.3,-8.8)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch2) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex](Multiply2.east)--($(Switch2.west)+(0,-0.4)$);
  \node[draw, rectangle, minimum height=1.1cm] (Constant1) at (-20.5,-8) {~~~\,0\,\,~~~};
  \draw(Constant1.east)-|($(Switch2.west)+(-0.3,0.4)$);
  \draw[-latex]($(Switch2.west)+(-0.3,0.4)$)--($(Switch2.west)+(0,0.4)$);
  \draw[-latex](Switch2.east)-|(add1.south);
  \node [circle,fill,inner sep=1pt] at (-18,-2.6){};
  \draw[-latex]($(Clamping.east)+(12.2,0)$) -- (Clamping.east);
  \draw[-, bend angle=45, bend left]($(Clamping.east)+(12.2,0)$)to node[below,align=center]{}($(Clamping.east)+(12.7,0)$);
  \draw($(Clamping.east)+(12.7,0)$) -| ($(add1.west)+(1,0)$);
  \node [circle,fill,inner sep=1pt] at ($(add1.west)+(1,0)$) {};
  \node[draw, rectangle, minimum height=1.1cm] (delay2) at (-6,-1.8) {~~~\,\large{$\frac{1}{z}$}\,\,~~~}; 
  \begin{scope}[shift={(-10.5,-2.2)}]
  \node[minimum size=0.7cm, draw, circle] at (0,0) (add3){};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \draw[-latex](Switch1.east)--(add3.west);
  \draw[-latex](delay2.east)--(add1.west);
  \draw($(delay2.east)+(0.5,0)$)|-($(add3.south)+(0,-1)$);
  \draw[-latex]($(add3.south)+(0,-1)$)--(add3.south);
  \node [circle,fill,inner sep=1pt] at ($(delay2.east)+(0.5,0)$) {};
  \begin{scope}[shift={(-8.3,-1.8)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch3) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex](add3.east)--($(Switch3.west)+(0,-0.4)$);
  \draw[-latex](Switch3.east)--(delay2.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-12.5,-6)}](Reset){Reset};
  \draw(Reset.east)--($(Reset.east)+(0.75,0)$);
  \draw($(Reset.east)+(0.75,0)$)|-($(Reset.east)+(-9.6,-1)$);
  \draw[-latex]($(Reset.east)+(-9.6,-1)$)|-(Switch2.west);
  \node [circle,fill,inner sep=1pt] at ($(Reset.east)+(0.75,0)$){};
  \draw($(Reset.east)+(0.75,0)$)--($(Reset.east)+(0.75,1.3)$);
  \draw[-, bend angle=45, bend left]($(Reset.east)+(0.75,1.3)$)to node[below,align=center]{}($(Reset.east)+(0.75,1.8)$);
  \draw($(Reset.east)+(0.75,1.8)$)--($(Reset.east)+(0.75,3.5)$);
  \draw[-, bend angle=45, bend left]($(Reset.east)+(0.75,3.5)$)to node[below,align=center]{}($(Reset.east)+(0.75,4)$);
  \draw[-latex]($(Reset.east)+(0.75,4)$)|-(Switch3.west);
  \draw[-latex]($(Switch3.west)+(-4.7,0.4)$)--($(Switch3.west)+(0,0.4)$);
  \node [circle,fill,inner sep=1pt] at ($(Switch3.west)+(-4.7,0.4)$){};
  \begin{scope}[shift={(-2,-1.8)}]
  \node [draw, rectangle, minimum height=1.1cm] (Limit) at (0,0) {~~~~~~\,~~~};
  \draw[color=lightgray](-0.35,0) -- (0.35,0);
  \draw[color=lightgray](0,-0.27) -- (0,0.27);
  \draw(Limit.south)[draw, color=black, thick]{(-0.35,-0.25) -- ++(0.2,0) -- ++(0.3,0.5)-- ++(0.2,0)};
  \node[below, font=\footnotesize] at (0,-0.5) {Limitation};
  \end{scope}
  \draw[-latex](add1.east)--(Limit.west);
  \draw[-latex](Limit.east)--(out.west);
