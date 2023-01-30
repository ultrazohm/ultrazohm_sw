.. _dig_optical:

=================================
Digital Optical
=================================

Source
------

- `Digital optical repository <https://bitbucket.org/ultrazohm/uz_d_optical/src/master/>`_


..	toctree::
	:maxdepth: 1
	:caption: Revisions
   
	optical_16tx_v2
	optical_18tx_14tx4rx_v3
	optical_14tx4rx_rev06


.. _dig_optical_soldering:

Soldering instructions
----------------------

In the following, it is explained how to solder in up to 18 

- transmitters (Tx) **Broadcom HFBR-1521Z** or 
- receivers (Rx) **Broadcom HFBR-2521Z**.

In this example, 14Tx und 4Rx are soldered in.

1. Click the optical transmitter and receiver together before soldering them

.. image:: optical_soldering/optical_solder1.jpg
   
.. image:: optical_soldering/optical_solder2.jpg

.. image:: optical_soldering/optical_solder3.jpg

.. image:: optical_soldering/optical_solder4.jpg

2. Solder the transmitter/receivers on the top side of the PCB first

.. image:: optical_soldering/optical_solder5.jpg

.. image:: optical_soldering/optical_solder6.jpg

3. After soldering the top side, shorten all the through-hole pins of the transmitter/receivers that now stick out on the bottom side of the PCB.

.. image:: optical_soldering/optical_solder7.jpg

4. Click together the Rx and Tx for the bottom side, equivalent to step 1

5. Cut the two pins, that are close to where the cable is plugged in, as short as possible. The referred pin is also cut in the picuture below. 

.. image:: optical_soldering/optical_solder8.jpg

5. Solder the transmitter/receivers on the bottom side. The shortened through-hole pins (in the schematic pin 5 and 8) are covered by the components on the top side. This is no problem, they do not have to be soldered, since they do not carry any electrical signal. 

.. image:: optical_soldering/optical_solder11.jpg
