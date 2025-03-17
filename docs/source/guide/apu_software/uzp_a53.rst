.. _uzpA53:

==================
Platform Framework
==================

.. warning:: The UltraZohm Platform Framework requires UltraZohm revision 5 or revision 4 including the IIC/SSD extension board for the automatic identification of the platform versions. For other systems, the hardware revision is passed by using the ``UZ_HARDWARE_VERSION`` define in ``uz_global_configuration.h`` (see :ref:`global_configuration`). Additionally, identification of adapter cards in A- and D-Slot is only possible for adapter cards that feature an EEPROM. For older adapter cards, the identification is not possible.

Overview
--------

The UltraZohm Platform Framework (or, in short, UZP) is a subsystem that aims to make the current I/O HAL *dynamically* aware of the underlying hardware platform during runtime.
In other words, its various functions can route the desired operation to whatever I/O device/pin based on which hardware (carrier, revision, etc.) the code is *currently* running.
This simplifies, e.g., writing to an output pin "RST_PHY" during the bring-up of, in this case, the Ethernet PHY,  which is connected to an I²C or GPIO, depending on the hardware revision.
It thus loosens the need to precisely specify the underlying platform *during compile time* and thus, eventually, will make the CPU binaries independent of, e.g., the exact revision of the carrier card they are loaded to.

For this and beyond, it adds the following functionalities for UltraZohm Rev04 with IIC/SSD Extension Board, UltraZohm Rev05, and newer systems:

* a platform information dataset containing model, revision, serial number, and other details about the underlying hardware platform, i.e., the UltraZohm carrier card
* per-slot adapter card identification from a (pre-)programmed EEPROM that is included on newer adapter cards
* per-carrier, per-port Ethernet MAC addresses (so that multiple UltraZohm systems can coexist on one network segment without a manual tweak)
* pulsing the emergency stop's ring LED on the front panel (due to popular demand)

Prerequisites and activation
----------------------------

The UZP behaves differently depending on the UltraZohm version:

- Rev04 or older

  - UZP features are not available, the UZP uses a default version set by the ``UZ_HARDWARE_VERSION`` define in ``uz_global_configuration.h`` (see :ref:`global_configuration`)

- Rev04 build before *2024* with IIC/SSD extension board

  - UZP features are available but depend on the external IIC/SSD Extension Board
  - Adapter card identification feature depends on the PCB tweak described in :ref:`carrier_retrofits_cardid`

- Rev04 build in *2024* with IIC/SSD extension board

  - UZP features a re fully available but depend on the external IIC/SSD Extension Board

- Rev05 or newer

  - UZP features are fully available


Given these dependencies, the adapter card identification UZP is disabled by default and has to be activated manually (cf. below).
The other UZP features are enabled by default but depend on ``UZ_HARDWARE_VERSION`` define in ``uz_global_configuration.h`` (see :ref:`global_configuration`) for systems that have no full UZP features available (see list above).

WIP text:

On Rev04 UltraZohm systems and older, the UZP relies on the external "I²C/SSD Extension Board" (either in Rev02 with `EEPROM retrofit <https://bitbucket.org/ultrazohm/uz_per_rtc_mac/issues/10/>`_ or in Rev03 ff.).
If such older systems are used without the external board (i.e., as shipped), the software defaults to the revision hard-coded in the RPU software, i.e., the known integer value ``UZ_HARDWARE_VERSION`` in ``/Baremetal/src/uz/uz_global_configuration.h``.
On newer UltraZohm systems, no external hardware is (going to be) needed, as the various EEPROMs, SSD etc. are part of the `Rev05 changeset <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/128/changeset-for-rev05>`_.

.. note::
 As of early 2025, the extension board is not publicly available.
 Please get in touch on the :ref:`uzslack` for the current state of this matter and the (already existing) short-term options for early access.

Furthermore, only for Rev04 UltraZohm systems and older versions, the adapter card identification feature depends on the PCB tweak described in :ref:`carrier_retrofits_cardid`, which users can apply themselves.
Please note that Rev04 UltraZohm *systems built in 2024 already have been retrofitted* before shipping -- Please get in touch to determine whether the retrofit is needed on your system(s).


If the adapter card identification feature is enabled on a non-retrofitted UltraZohm system, it will yield incorrect results due to address collisions.

API functions and data types
----------------------------

Initialization
""""""""""""""

The framework is automatically initialized on the APU by a call to ``uz_platform_init()`` before FreeRTOS threading starts in ``main()``.
The activation of the adapter card identification depends on the ``UZ_PLATFORM_CARDID`` ``#define`` in ``/FreeRTOS/src/uz/uz_PLATFORM/uz_platform.h``:

* In all cases, ``uz_platform_init()`` is called at bootup to

 * initialize the I²C bus to the extension board (and, optionally, initialize the I²C bus between carrier and adapter cards),
 * retrieve the platform identification from the external EEPROM,
 * communicates the result (or, in case of no EEPROM, the RPU default) to the RPU (cf. states ``init_assertions`` on the RPU and ``initialization_handshake`` on the APU),
 * initialize internal data structures (for instance, the I/O map for the given platform), and
 * configure internal (e.g., the GPIO controllers of the PS) and external (e.g., the I²C port expander on the extension board) I/O controllers according to the I/O map.
 * Note that earlier software revisions relied on ``UZ_PLATFORM_ENABLE`` to enable the then disabled-by-default framework

* ``UZ_PLATFORM_CARDID``: If set, ``uz_platform_cardread()`` is made available to the user, and a small demo in ``main()`` performs adapter card identification that shows card model, revision, and serial for each slot on the serial console.

.. note::
 Please take care to increase ``UZ_IIC_MAX_BUSINSTANCES`` in ``/FreeRTOS/src/uz/uz_IIC/uz_iic.c`` to at least ``2`` when enabling the adapter card identification functionality using ``UZ_PLATFORM_CARDID``.
 Otherwise, the IIC subsystem will ``assert()`` during initialization due to a lack of available bus instances.

Adapter Card Identification
"""""""""""""""""""""""""""

If enabled (cf. ``UZ_PLATFORM_CARDID`` above), the following API is available to retrieve and interpret information on the adapter cards currently plugged into the UltraZohm carrier/system (as demonstrated by the example included in ``main()`` and also reprinted below).

* ``uz_platform_cardread(uint8_t slot, uz_platform_eeprom_group000models_t* model_p, int* revision_p, int* serial_p)`` accesses the EEPROM on the adapter card in the given ``slot`` (where values 0 to 2 refer to slots A1 to A3 whilst values 3 to 7 pertain to slots D1 to D5).

 If successful, it populates

 * the enum identified by ``model_p`` with the (integer-encoded) model number,
 * the integer behind ``revision_p`` with the revision number, and
 * the integer pointed to by ``serial_p`` with the serial  of the adapter card selected.

* The model number is encoded as an enum of type ``uz_platform_eeprom_group000models_t`` and (as of early 2024) may have one of the following values

 * ``UZP_HWGROUP_ADCARD_LTC2311``,
 * ``UZP_HWGROUP_ADCARD_DIGVOLT``,
 * ``UZP_HWGROUP_ADCARD_DIGOPT``,
 * ``UZP_HWGROUP_ADCARD_DIGRES``,
 * ``UZP_HWGROUP_ADCARD_DIGENC``,
 * ``UZP_HWGROUP_ADCARD_MAX11331C``,
 * ``UZP_HWGROUP_ADCARD_MAX11331CD``,
 * ``UZP_HWGROUP_ADCARD_MAX11331``,
 * ``UZP_HWGROUP_ADCARD_LTC2983``,
 * ``UZP_HWGROUP_ADCARD_DIGINV``, or
 * ``UZP_HWGROUP_ADCARD_DAC8831``

 that should be used in comparisons.
 Note that the underlying definitions can be found in ``/shared/uz_platform_cardeeprom.h``.

 Furthermore, an "enum-to-string" helper (``uz_platform_eeprom_group000models_enum2label(uz_platform_eeprom_group000models_t model)``) is available to convert the enum integer into a user-readable string in case such functionality is required.

Example in ``main()``:

.. code-block:: c

  const uint8_t card_slots = UZ_PLATFORM_I2CADDR_CARDEEPROM_LAST - UZ_PLATFORM_I2CADDR_CARDEEPROM_BASE + 1;

  for (int i=0; i<card_slots; i++) {
    uz_platform_eeprom_group000models_t model;
    int revision, serial;

    if ( UZ_SUCCESS == uz_platform_cardread(i, &model, &revision, &serial) ) {
      uz_printf("Board model/revision/serial of adapter card in slot %i: %03i/%02i/%04i)\r\n", i, model, revision, serial);
 } else {
      uz_printf("Identification of adapter card in slot %i failed (no card or EEPROM)\r\n", i);
 }

    uz_printf("\r\n");
 }

GPIO
""""

The UZP supports configuring and driving GPIO pins connected to PS-GPIOs and I²C-controlled expanders.
API data types and I/O mappings for inputs are also defined, although the actual functionality has not yet been implemented.

Supported outputs on an UltraZohm Rev04 with I²C/SSD extension (enum ``uz_platform_gpo_id``):

* ``I2CLED_FP1RDY`` (frontpanel LED1 "Ready")
* ``I2CLED_FP2RUN`` (frontpanel LED2 "Running")
* ``I2CLED_FP3ERR`` (frontpanel LED3 "Error")
* ``I2CLED_FP4USR`` (frontpanel LED4 "User")
* ``I2CLED_FPRING`` (frontpanel LED of the emergency stop button)
* ``RST_PHY0`` (reset signal of PHY0)
* ``RST_PHY1`` (reset signal of PHY1)

Interaction with outputs relies on output operations per enum ``uz_platform_gpo_op``, e.g.,

* ``UZP_GPO_ENABLE2PUSHPULLED`` to enable an output,
* ``UZP_GPO_ASSERT`` to assert the output pin (to high, cf. below),
* ``UZP_GPO_TOGGLE`` to toggle the output pin, with
* corresponding ``_QUEUED`` variants of most operations to enable synchronized, low-bus-traffic updates,

and a single-function setter: ``uz_platform_gposet(enum uz_platform_gpo_id uzpgpo_id, enum uz_platform_gpo_op uzpgpo_op)``

Examples:

* ``uz_platform_gposet(I2CLED_FPRING, UZP_GPO_ENABLE2PUSHPULLED);`` to enable an output,
* ``uz_platform_gposet(I2CLED_FPRING, UZP_GPO_TOGGLE_QUEUED);`` to toggle the output on the next update,
* ``uz_platform_gpoupdate();`` to flush all queued output changes to hardware.

Predefined inputs on an UltraZohm Rev04 with IIC/SSD extension (enum ``uz_platform_gpi_id``:

* ``I2CKEY_FP5ENABLESYS``
* ``I2CKEY_FP6ENABLECTL``
* ``I2CKEY_FP7EMERGENCYSTOP``
* ``I2CKEY_FP8``

NB:

* Currently, the GPIO functionality lacks support for inverted I/Os, i.e., an output state "assert" always implies "pin driven to high" (even if the signal is inverted on the electrical level)
* Similarly, no function to read from inputs is implemented, although the framework's pre-populated I/O maps already cater to all existing input pins

Ethernet MAC addresses
""""""""""""""""""""""

MAC addresses are accessible by means of ``uz_platform_macread(uint8_t eeprom, uint8_t *addrbuf_p)`` and ``uz_platform_macread_primary(uint8_t *addrbuf_p)``, although for neither there is any necessity for the user to use these functions explicitly.


See also
--------

* the `uz_per_rtc_mac <https://bitbucket.org/ultrazohm/uz_per_rtc_mac/src/master/>`_ repository for the I²C/SSD extension board, and
* the :ref:`carrier_retrofits_cardid` for modifying pre-Rev05 carrier boards to support the adapter card identification feature.
