.. _dig_si_inverter:

===========================================
MOSFET 48V Inverter (Digital adapter slot)
===========================================

Source
------
* `uz_d_inverter Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_inverter>`_

Functionality
-------------

The UltraZohm digital inverter consists of three MOSFET half-bridges. 
It is equipped with bi-directional current measurement for each phase and the DC-link current, measurements for the phase and DC-link voltages, and temperature measurement for each semiconductor.  
The voltage measurement is equipped with a 1st order low-pass filter.
The current measurement is realised with shunt resistors.
The inverter has a dedicated PWM enable pin. 
If the ``PWM_EN`` is set to false, both semiconductors of each half-bridge are disabled. 
Overcurrent protection for the three phases and the DC-link is included. 
The OCP is not designed for half-bridge shorts and will only trip if the phase or DC-link currents exceed the safe operating window. 
When triggered, the OCP will only flag a FAULT bit in the corresponding software driver. 
The inverter will not shut down automatically.
Each half-bridge is designed in a non-bootstrap configuration. 
Each voltage and current measurement signal of the three phases and the DC-link are converted from single-ended to differential transmission to reduce the susceptibility to interference.
The measured signals are transmitted over Ethernet cables and are directly compatible with the :ref:`Analog_LTC2311_16_Rev05`, :ref:`Analog_LTC2311_16_v3` and :ref:`Analog_LTC2311_16_v2` cards.
An additional heat sink can be fitted to increase heat dissipation and keep the switches cooler.
For additional information or an in-depth look at the circuit design, please refer to the schematics in the :ref:`References <dig_si_inverter_references>` section.

..	toctree::
   :caption: Revisions
   :maxdepth: 1

   Digital_SI_Inverter_rev02
   Digital_SI_Inverter_rev03
   Digital_SI_Inverter_rev04


Components
----------

.. _dig_si_inverter_all_components:

- MOSFET (100 V, 97 A, 6.0 :math:`m\Omega`) `ISC060N10NM6ATMA1 <https://www.mouser.de/datasheet/2/196/Infineon_ISC060N10NM6_DataSheet_v02_02_EN-3166722.pdf>`_
- Gate-Driver `EiceDRIVER 2EDF7275KXUMA1 <https://www.mouser.de/datasheet/2/196/Infineon_2EDF7275K_DataSheet_v02_07_EN-1731004.pdf>`_
- Isolated DC/DC Converter for gate 12V supply `PDSE1-S24-S12-M-TR <https://www.mouser.de/datasheet/2/670/pdse1_m-1596038.pdf>`_ 
- Differential operational amplifier `ADA4940-1ARZ <https://www.mouser.de/datasheet/2/609/ada4940_1_4940_2-3120247.pdf>`_ 
- Temperature measurement `LM57CISD-10/NOPB <https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=https://www.ti.com/lit/gpn/lm57>`_
- Voltage to PWM frequency converter `LTC6992HS6-4#WTRMPBF <https://www.mouser.de/datasheet/2/609/LTC6992-1-6992-2-6992-3-6992-4-1852873.pdf>`_


Heatsink
--------

The PCB is prepared for the installation of a heat sink. 
Four holes have been drilled to allow the use of maximum M3 screws.
It is intended that the heatsink will have the appropriate holes with threads into which the screws can be screwed.
For further information on the dimensions of the heatsink and the location of the screw holes, refer to the diagrams below. 
The dimensions take into account the safety margin required for the mounting rails in the UltraZohm. 
A simple passive heatsink is sufficient for operation. 
An advanced actively cooled heatsink, either air or water cooled, can also be fitted if required.
This heatsink design is different for valid for :ref:`Rev02 <dig_si_inverter_rev03>`, :ref:`Rev03 <dig_si_inverter_rev03>` and :ref:`Rev04 <dig_si_inverter_rev04>`. 

Rev02 & Rev03
=============

.. tikz:: Heatsink dimensions Rev02 & Rev03
  :align: center

  \usetikzlibrary{shapes,arrows,patterns,calc};
  \tikzset{%
    body/.style={inner sep=0pt,outer sep=0pt,shape=rectangle,draw,thick},
    dimen/.style={<->,>=latex,color=gray,every rectangle node/.style={fill=white,midway,font=\large}},
    symmetry/.style={dashed,thin},
  }
  \node [body,minimum height=9.2cm,minimum width=3.5cm,anchor=south west] (body1) at (0,0) {};
  \draw (body1.south west) -- ++(-1,0) coordinate (D1) -- +(-5pt,0);
  \draw (body1.north west) -- ++(-1,0) coordinate (D2) -- +(-5pt,0);
  \draw [dimen] (D1) -- (D2) node {92,00};
  \draw[color=gray] (body1.north west) -- ++(0,1) coordinate (D1) -- +(0,5pt);
  \draw [color=gray](body1.north east) -- ++(0,1) coordinate (D2) -- +(0,5pt);
  \draw [dimen] (D1) -- (D2) node {35,00};
  \filldraw[color=black, fill=white, thick](0.6,1.6) circle (0.3cm);
  \draw (0.6,1.95) arc[start angle=90, end angle=-180, radius=0.35];
  \draw (2.9,1.95) arc[start angle=90, end angle=-180, radius=0.35];
  \draw (0.6,7.55) arc[start angle=90, end angle=-180, radius=0.35];
  \draw (2.9,7.55) arc[start angle=90, end angle=-180, radius=0.35];
  \filldraw[color=black, fill=white, thick](2.9,1.6) circle (0.3cm);
  \filldraw[color=black, fill=white, thick](0.6,7.2) circle (0.3cm);
  \filldraw[color=black, fill=white, thick](2.9,7.2) circle (0.3cm);
  \draw [color=gray](2.9,1.6) -- ++(2.1,0) coordinate (D1) -- +(5pt,0);
  \draw [color=gray](3.5,0) -- ++(1.5,0) coordinate (D2) -- +(5pt,0);
  \draw [dimen] (D1) -- (D2) node {16,00};
  \draw [color=gray](body1.south west) -- ++(0,-1) coordinate (D1) -- +(0,-5pt);
  \draw [color=gray](0.6,1.6) -- ++(0,-2.6) coordinate (D2) -- +(0,-5pt);
  \draw [dimen,-] (D1) -- (D2) node [right=15pt] {6,00};
  \draw [dimen,<-] (D1) -- ++(-5pt,0);
  \draw [dimen,<-] (D2) -- ++(+5pt,0);
  \draw [color=gray](body1.south west) -- ++(0,-2) coordinate (D1) -- +(0,-5pt);
  \draw [color=gray](2.9,1.6) -- ++(0,-3.6) coordinate (D2) -- +(0,-5pt);
  \draw [dimen] (D1) -- (D2) node  {29,00};
  \draw [color=gray](3.5,0) -- ++(2.5,0) coordinate (D1) -- +(5pt,0);
  \draw [color=gray](2.9,7.2) -- ++(3.1,0) coordinate (D2) -- +(5pt,0);
  \draw [dimen] (D1) -- (D2) node {72,00};
  \draw[-latex,color=gray](5,9.0)--(3.15,7.35);
  \node[rotate=45,color=gray]  at (4,8.5) {4x M3};

Rev04
=====

.. note:: The heatsink in Rev04 is mounted on the bottom of the PCB.

.. tikz:: Heatsink dimensions Rev04
  :align: center

  \usetikzlibrary{shapes,arrows,patterns,calc};
  \tikzset{%
    body/.style={inner sep=0pt,outer sep=0pt,shape=rectangle,draw,thick},
    dimen/.style={<->,>=latex,color=gray,every rectangle node/.style={fill=white,midway,font=\large}},
    symmetry/.style={dashed,thin},
  }
  \node [body,minimum height=9.2cm,minimum width=3.5cm,anchor=south west] (body1) at (0,0) {};
  \draw (body1.south west) -- ++(-1,0) coordinate (D1) -- +(-5pt,0);
  \draw (body1.north west) -- ++(-1,0) coordinate (D2) -- +(-5pt,0);
  \draw [dimen] (D1) -- (D2) node {94,00};
  \draw[color=gray] (body1.north west) -- ++(0,1) coordinate (D1) -- +(0,5pt);
  \draw [color=gray](body1.north east) -- ++(0,1) coordinate (D2) -- +(0,5pt);
  \draw [dimen] (D1) -- (D2) node {35,00};
  \filldraw[color=black, fill=white, thick](0.6,1.6) circle (0.3cm);
  \draw (0.6,1.95) arc[start angle=90, end angle=-180, radius=0.35];
  \draw (2.9,1.95) arc[start angle=90, end angle=-180, radius=0.35];
  \draw (0.6,7.55) arc[start angle=90, end angle=-180, radius=0.35];
  \draw (2.9,7.55) arc[start angle=90, end angle=-180, radius=0.35];
  \filldraw[color=black, fill=white, thick](2.9,1.6) circle (0.3cm);
  \filldraw[color=black, fill=white, thick](0.6,7.2) circle (0.3cm);
  \filldraw[color=black, fill=white, thick](2.9,7.2) circle (0.3cm);
  \draw [color=gray](2.9,1.6) -- ++(2.1,0) coordinate (D1) -- +(5pt,0);
  \draw [color=gray](3.5,0) -- ++(1.5,0) coordinate (D2) -- +(5pt,0);
  \draw [dimen] (D1) -- (D2) node {20,00};
  \draw [color=gray](body1.south west) -- ++(0,-1) coordinate (D1) -- +(0,-5pt);
  \draw [color=gray](0.6,1.6) -- ++(0,-2.6) coordinate (D2) -- +(0,-5pt);
  \draw [dimen,-] (D1) -- (D2) node [right=15pt] {5,00};
  \draw [dimen,<-] (D1) -- ++(-5pt,0);
  \draw [dimen,<-] (D2) -- ++(+5pt,0);
  \draw [color=gray](body1.south west) -- ++(0,-2) coordinate (D1) -- +(0,-5pt);
  \draw [color=gray](2.9,1.6) -- ++(0,-3.6) coordinate (D2) -- +(0,-5pt);
  \draw [dimen] (D1) -- (D2) node  {25,00};
  \draw [color=gray](3.5,0) -- ++(2.5,0) coordinate (D1) -- +(5pt,0);
  \draw [color=gray](2.9,7.2) -- ++(3.1,0) coordinate (D2) -- +(5pt,0);
  \draw [dimen] (D1) -- (D2) node {74,00};
  \draw[-latex,color=gray](5,9.0)--(3.15,7.35);
  \node[rotate=45,color=gray]  at (4,8.5) {4x M3};