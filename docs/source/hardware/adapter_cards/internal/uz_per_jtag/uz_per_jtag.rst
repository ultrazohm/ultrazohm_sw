.. _uz_per_jtag:

===============
IsoJTAG_Adapter
===============


.. image:: UZ_isoJTAG_Adapter_3D_View_Top_Rev01.png
   :height: 200

Source
******

- `UZ IsoJTAG Adapter repository <https://bitbucket.org/ultrazohm/uz_per_jtag/>`_

Functionality
-------------

This is a dual-JTAG adapter module, which enables the programming of the CPLDs without changing the physical setup of the UltraZohm.
It does so by featuring two independent JTAG channels (and a UART), where one JTAG (and the UART) connect to the Zynq-SoM and the other JTAG programs the CPLDs.


Known issues
------------

None (as currently shipped).
The first batch of Rev01 boards lacked a 0R resistor towards the CPLDs' supply rail, but this has been fixed manually for all boards.

Compatibility
-------------

Rev01 is designed to be applied to the CarrierBoard to replace the  `Trenz TE0790 <https://wiki.trenz-electronic.de/download/attachments/43680347/TE0790-02%20top-numbered.png?version=1&modificationDate=1507707618000&api=v2>`_, see tutorial :ref:`upgrades_rev04`.

Downloads
"""""""""

* :download:`Assembly Rev01 <ASM_UZ_isoJTAG_Adapter_Rev01.pdf>`
* :download:`Schematic Rev01 <SCH_UZ_isoJTAG_Adapter_Default_Rev01.pdf>`


Designed by
"""""""""""

Andreas Geiger, 01/2024
