.. _upgrades_rev04:


========
Upgrades
========

Standalone isoJTAG Module
-------------------------

In order to increase usability and user-friendliness, an upgrade for the JTAG module is available since early 2024 and is already fitted as standard (i.e., ex works) in some systems based on :ref:`carrier_board_rev04`.
On this page, a step-by-step upgrade from the original `Trenz TE0790 <https://wiki.trenz-electronic.de/download/attachments/43680347/TE0790-02%20top-numbered.png?version=1&modificationDate=1507707618000&api=v2>`_ to the :ref:`uz_per_jtag` is provided.

Components
^^^^^^^^^^

For the upgrade, different components are needed:

- :ref:`uz_per_jtag`
- Ribbon cable with IDC connectors, length 0.3m: `FC12300-0 <https://www.tme.eu/de/details/fc12300-0/flachbandkabel-mit-idc-steckverbinder/amphenol/>`_
- Plug extension: `ESQ-106-23-G-D <https://www.digikey.de/en/products/detail/samtec-inc/ESQ-106-23-G-D/7090456>`_
- Spacer consisting of `spacer bolt Ettinger 005.13.041 <https://www.ettinger.de/p/abstandsbolzen-stahl-verzinkt-i/a-sw5-5x4-i-m3x2-5-a-m3x6-m.-freistich/005.13.041>`_, `spring washer RS pro 276-847 <https://de.rs-online.com/web/p/unterlegscheiben/0276847>`_ and `2 spacer bolts Ettinger 005.13.101 <https://www.ettinger.de/p/abstandsbolzen-stahl-verzinkt-i/a-sw5-5x10-i-m3x7-a-m3x6-m.-freistich/005.13.101>`_

Upgrade procedure
^^^^^^^^^^^^^^^^^

1. Remove base, bottom and rear cover for better accessibility of the JTAG module.

2. Dismount old JTAG module `Trenz TE0790 <https://wiki.trenz-electronic.de/download/attachments/43680347/TE0790-02%20top-numbered.png?version=1&modificationDate=1507707618000&api=v2>`_.

   .. image:: upgrades/removejtag.jpg
       :width: 500

3. Insert spacer and plug extension.

   .. image:: upgrades/addspacer.jpg
       :width: 500

4. Connect ribbon cable on carrier near slot D4.

   .. image:: upgrades/mountcable.jpg
       :width: 500

5. Connect ribbon cable on JTAG module.

   .. image:: upgrades/mountjtag.jpg
       :width: 500

6. Fasten cable on lower rail with cable ties.

   .. image:: upgrades/zipcable.jpg
       :width: 500

7. Reconnect the USB cable between the front panel and the JTAG module. It is ready now for programming the CPLDs (in addition to the Zynq-SoM as before).

   .. image:: upgrades/readymountedjtag.jpg
       :width: 500

8. Program the CPLDs according to :ref:`label_cpld_programming`.
