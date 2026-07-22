.. _frontpanel_can:

========================
D-Sub connectors for CAN
========================

The front panel for ≥Rev05 carriers (cf. right-hand side of :ref:`frontpanel-photos`) comes with two 9-pin D-Sub connectors.
Each of them

- connects to one of the PS CAN controllers,
- provides one isolated interface (ISO1042) and
- optionally connects termination resistors.

Pinout (front view):

.. figure:: img/can.jpg

NB:

- Ensure that the termination switch ``SW1x`` is set according to your application
- Ground on pin 3 depends on ``R9x`` being populated
- Details of the board can be found in the `'uz_frontpanel_firstfloor' repository <https://bitbucket.org/ultrazohm/uz_frontpanel_firstfloor>`_

On the software side, please refer to

- ``vitis/software/FreeRTOS/uz/uz_can`` for the driver HAL and
- ``vitis/software/FreeRTOS/sw/can.c`` for a usage example.
