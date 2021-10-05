.. _cil:

======================
Controller in the Loop
======================

Controller in the loop (CIL) refers to a setup in which the implementation of a control algorithm is tested with a plant model that is implemented on the UltraZohm.
This is useful to make sure that implemented algorithms work as intended before testing on real hardware.
There are multiple possibilities to implement on-chip CIL on the UltraZohm are shown in the following.

.. _cil_plant_in_ps:

.. tikz:: Plant model in PS, Control algorithm in PL
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(mpsoc) {MPSoC};
  \node[name=ps, below = 0.1cm of mpsoc] {PS};
  \node[block,name=plant, below = 0.2cm of ps,drop shadow] {Plant model};
  \node[block,name=controller, below of=plant,drop shadow] {Controller};
  \node[name=pl, below = 0.1cm of controller] {PL};
  \begin{scope}[on background layer]
    \node[draw,fill=blue!10,rounded corners,fit=(mpsoc) (pl),inner sep=5pt,minimum width=3.5cm] {};
    \node[draw,fill=yellow!20,rounded corners,fit=(pl) (controller),inner sep=5pt,minimum width=2.5cm] {};
    \node[draw,fill=green!10,rounded corners,fit=(ps) (plant),inner sep=5pt,minimum width=2.5cm] {};
  \end{scope}
  \draw[->] ([xshift=-0.3cm]controller.north) -- ([xshift=-0.3cm]plant.south);
  \draw[<-] ([xshift=0.3cm]controller.north) -- ([xshift=0.3cm]plant.south);
  \end{tikzpicture}

Implementing the plant model in the PS and the control algorithm in the PL [#KLK20]_ is depicted in Fig. Fig. :numref:`cil_plant_in_ps`.
This approach offers easy implementation of discretized plant models in C code.
However, the sample time is limited to the range of kilohertz.
The PS has to handle the interrupt, read from PL registers, and write back to them, resulting in an overhead of approximately :math:`1 \mu s` [#WGL19]_. 
Furthermore, the calculation time of the plant model increases for more complex or multiple plant models.
Thus, this approach is favorable if the plant model is simple or the required sampling frequency does not exceed :math:`f_s=100 kHz`.
  
.. _cil_plant_in_pl:

.. tikz:: Plant in PS, Control algorithm in PL
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(mpsoc) {MPSoC};
  \node[name=ps, below = 0.1cm of mpsoc] {PS};
  \node[block,name=plant, below = 0.2cm of ps,drop shadow] {Controller};
  \node[block,name=controller, below of=plant,drop shadow] {Plant model};
  \node[name=pl, below = 0.1cm of controller] {PL};
  \begin{scope}[on background layer]
    \node[draw,fill=blue!10,rounded corners,fit=(mpsoc) (pl),inner sep=5pt,minimum width=3.5cm] {};
    \node[draw,fill=yellow!20,rounded corners,fit=(pl) (controller),inner sep=5pt,minimum width=2.5cm] {};
    \node[draw,fill=green!10,rounded corners,fit=(ps) (plant),inner sep=5pt,minimum width=2.5cm] {};
  \end{scope}
  \draw[->] ([xshift=-0.3cm]controller.north) -- ([xshift=-0.3cm]plant.south);
  \draw[<-] ([xshift=0.3cm]controller.north) -- ([xshift=0.3cm]plant.south);
  \end{tikzpicture}

Fig. :numref:`cil_plant_in_pl` shows the scheme that is recommended, which implements the plant model in the PL.
Moving the plant model to the PL allows for higher sampling frequencies, frees the processor from calculating the model, and enables the emulation of more complex as well as multiple parallel plant models.
Implementing IP-Cores on the FPGA is generally thought of as more challenging compared to writing code for the CPU.
This is mitigated by using aMATLAB HDL Coder, allowing easy integration into the UltraZohm FPGA design.


.. _cil_controller_in_both:

.. tikz:: Control algorithm in PS and PL, Plant model in PL
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(mpsoc) {MPSoC};
  \node[name=ps, below = 0.1cm of mpsoc] {PS};
  \node[block,name=controller_ps, below = 0.2cm of ps,drop shadow] {Controller};
  \node[block,name=controller, below = 1cm of controller_ps,drop shadow] {Controller};
  \node[block,name=plant_pl, right of=controller,drop shadow] {Plant};
  \node[name=pl, below = 0.1cm of controller] {PL};
  \begin{scope}[on background layer]
    \node[draw,fill=blue!10,rounded corners,fit=(mpsoc) (pl) (plant_pl),inner sep=5pt,minimum width=5.5cm] {};
    \node[draw,fill=yellow!20,rounded corners,fit=(pl) (controller) (plant_pl),inner sep=5pt,minimum width=2.5cm] {};
    \node[draw,fill=green!10,rounded corners,fit=(ps) (controller_ps),inner sep=5pt,minimum width=2.5cm] {};
  \end{scope}
  \draw[->] ([xshift=-0.3cm]controller.north) -- ([xshift=-0.3cm]controller_ps.south);
  \draw[<-] ([xshift=0.3cm]controller.north) -- ([xshift=0.3cm]controller_ps.south);
  \draw[->] ([yshift=-0.2cm]controller.east) -- ([yshift=-0.2cm]plant_pl.west);
  \draw[<-] ([yshift=0.2cm]controller.east) -- ([yshift=0.2cm]plant_pl.west);
  \draw[->] ([xshift=-0.2cm]plant_pl.north) |- ([yshift=-0.2cm]controller_ps.east);
  \draw[<-] ([xshift=0.2cm]plant_pl.north) |- ([yshift=0.2cm]controller_ps.east);
  \end{tikzpicture}

Simulating the plant model in the PL can also be used for control algorithms which are mapped to the PS as well as the PL to improve the usable computational performance, as shown in Fig. :numref:`cil_controller_in_both`.

Implemented PL Plant models
---------------------------

The following IP-Cores are intended to be used for CIL:

- :ref:`uz_pmsmModel`
- :ref:`uz_plantModel_pt1`

Sources
-------

.. [#KLK20] S. A. Bin Khalid and E. Liegmann and P. Karamanakos and R. {Kennel, High-Level Synthesis of a Long Horizon Model Predictive Control Algorithm for an FPGA, PCIM, 2020
.. [#WGL19] S. Wendel and A. Geiger and E. Liegmann et al., UltraZohm - A powerful real-time computation platform for MPC and multi-level inverters, PRECEDE, 2019