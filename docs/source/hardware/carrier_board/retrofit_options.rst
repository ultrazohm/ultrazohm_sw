.. _carrier_retrofits:

===========================
Feature Extension Retrofits
===========================

This page documents helpful PCB retrofits that add new functionalities to existing carrier boards.
As of 2024, there is exactly one such retrofit (cf. below); all other retrofits aim at fixing bugs, as documented in :ref:`carrier_known_issues`.


.. _carrier_retrofits_cardid:

Adapter card identification retrofit
------------------------------------

.. note::
	This retrofit *only* applies to UltraZohm carrier cards **Rev04 and older**.
	Newer revisions of the carrier are going to implement this feature by default and thus *are not subject* to the instructions below.
	Furthermore, Rev04 UltraZohm systems (currently) shipped by `Zohm Control GmbH <https://zohm-control.com/>`_ already include this retrofit, if in doubt please get in touch before proceeding.

**Feature description**

This retrofit adds address pins to the A and D connectors between the UltraZohm carrier card and its various A and D adapter cards.
By doing so, the EEPROMs on current and future adapter cards become reachable, which enables the :ref:`uzpA53` (running on the PS CPUs) to fetch the card identification (model, revision and serial) and hand it over to the user.
The user then may rely on this to, e.g., select/apply any card-specific calibration datasets as required during system initialization, for instance on ADC or DAC cards to compensate for part-based offsets or other analog differences.

**Prerequisites and preparation**

You need: Screwdrivers, soldering iron, tin solder and thin enameled (copper) wire *aka* magnet wire, plus

... $some time -- The soldering itself takes less than ten minutes; the mechanics are the more tedious bit.

.. warning::
	Given the sensitive nature of some of the electronics on the carrier board, please deploy the usual ESD prevention methods during disassembly, soldering and reassembly.

To perform the retrofit, the carrier card has to be extracted from the UltraZohm chassis.
Depending on exact chassis type, build date etc., this may be a five-minute operation -- or take considerably longer (according to those who built these systems).
The UltraZohm maintainers welcome additions to this page by users who performed the retrofit on their system to inform others about their experience.

**Step-by-step PCB instructions**

The goal of this retrofit is to add slot-specific voltage levels to two/three predefined connector pins (A and D slots, respectively) for the (up to) eight adapter cards that can be connected to the UltraZohm carrier.
Due to the design of this feature, selected connector pins have to be connected to only ground (GND), not to any other signal.
Given that all slots on the carrier are "surrounded" by GND, this greatly simplifies the retrofit (as newly added wires can be kept quite short and do not have to reach any supply rail).

Important aspects:

* For A slots, between one and two connector pins (per slot) shall be connected to GND
* For D slots, between zero and two connector pins (per slot) shall be connected to GND
* For both types of slots, the connector pins in question are easily accessed by means of test pads close to the connector
* GND is readily available by means of a large plane surrounding all connectors and "made accessible" by carefully removing the solder mask layer on top
* Connections between the individual test pads and the -- potentially shared -- "GND spot" shall be made using enameled wire

The following image shows the individual test pads that have to be connected to GND:

.. image:: pictures/adretro2d.png

They are

* TP46A and TP56A at slot A1,
* TP56B at slot A2 (not labelled on the overlay silkscreen -- orange label above added for clarity),
* TP46C at slot A3,
* TP58A at slot D1,
* TP57B and TP67B at slot D2,
* TP67C at slot D3,
* TP57D at slot D4, and
* (none) at slot D5.

The following 3D rendering shows the affected slots and test pads (NB: slot D5 thus not shown here):

.. image:: pictures/adretro3d.png

To connect the above pads to GND,

* select a suitable "GND spot" close to the pad(s), i.e.,

  * one left of A1, A2 and A3 each,
  * one between D1 and D2, and
  * one left of D3 and D4 each;

* carefully remove the solder mask layer on top;
* apply soldering iron and (tin) solder to blank copper until some solder has been deposited;
* pre-solder the test pad(s) affected on the particular slot;
* solder some enameled wire to the pre-soldered test pad(s); and
* solder the enameled wire(s) to the GND point created before.

The :ref:`adretro-photos` below exemplify the above steps by means of the shared GND point between slots D1 and D2.

.. _adretro-photos:
.. list-table:: soldering step-by-step photos
   :header-rows: 1
   :align: center

   * - Remove GND solder mask
     - Pre-solder GND point
     - Pre-solder test pad(s)
     - Add enameled wire(s)
     - Connect wire(s) to GND
   * - .. image :: pictures/adretrostep1.jpg
     - .. image :: pictures/adretrostep2.jpg
     - .. image :: pictures/adretrostep3.jpg
     - .. image :: pictures/adretrostep4.jpg
     - .. image :: pictures/adretrostep5.jpg

Please refer to :ref:`uzpA53` for a description of the software API that helps to retrieve the per-card identification data on the APU.

**Further reading**

For those curious, please refer to

* `Issue #6 ("Add I²C EEPROM") <https://bitbucket.org/ultrazohm/uz_d_template/issues/6/add-i-c-eeprom>`_ in the ``UZ_D_Template`` repository for more information on the design ideas (and history) of the adapter card identification feature and on how to add an EEPROM to an existing adapter card

   * The established Altium template repositories now include an EEPROM for both `analog <https://bitbucket.org/ultrazohm/uz_a_template/src/master/>`_ and `digital <https://bitbucket.org/ultrazohm/uz_d_template/src/master/>`_ adapter cards
   * `This table <https://bitbucket.org/ultrazohm/uz_d_template/issues/6/add-i-c-eeprom#comment-66183759>`_ lists all the signal connections required (between the adapter card's edge connector and its EEPROM)

* `Pull Request #444 ("[APU/FreeRTOS+Linux] Extend UZP framework to support reading the identity of adapter cards [...]") <https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/444>`_ in the ``ultrazohm_sw`` repository for the software changes behind this feature
* `Pull Request #400 ("Add PlatformDetectHAL (aka "UZ Platform", UZP)") <https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/400>`_ in the ``ultrazohm_sw`` repository for requirements of the UltraZohm Platform framework (that the adapter ID feature is based on)
