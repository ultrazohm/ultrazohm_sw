Changeset
=========

The upcoming "2025 edition" of the UltraZohm implements various system- and component-level changes.
Particularly to track the former ones, this page aggregates hyperlinks to the individual issues in the various repositories (that hold affected parts).
As of 2024Q2, all this (obviously) still is work in progress...


Associated Repositories w/ toplevel issues
------------------------------------------

* `CarrierBoard <https://bitbucket.org/ultrazohm/uz_carrierboard/issues?status=new&status=open&status=submitted&is_spam=!spam>`_

  * `Issue #128 (Changeset for Rev05) <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/128/changeset-for-rev05>`_: Detailed overview of (mostly electric?) changes that are scheduled for Rev05 of the carrier board
  * For technical details, please refer to above link or :ref:`changeset_rev05uzc`

* `FrontPanel (aka FP) <https://bitbucket.org/ultrazohm/uz_frontpanel/issues?status=new&status=open&status=submitted&is_spam=!spam>`_: "Z" PCB with assemblies
* `Housing (aka H) <https://bitbucket.org/ultrazohm/housing/issues?status=new&status=open&status=submitted&is_spam=!spam>`_: 3U/6U chassis, slot blinds, etc.
* `CPLD_Lattice <https://bitbucket.org/ultrazohm/cpld_lattice/issues?status=new&status=open&status=submitted&is_spam=!spam>`_
* `Assembly_and_Commissioning <https://bitbucket.org/ultrazohm/assembly_and_commissioning/src/master/>`_ (no longer active?)


Overview of Change Issues vs. Repositories
------------------------------------------

.. list-table:: Changeset Rev05-UZC
   :name: changeset_rev05uzc
   :widths: 5 1 1
   :header-rows: 2

   * - Bugfix/
     -  Issue #
     -  Further
   * - Tagline
     -  carrier
     -  issue #s
   * - Fix/Extend supply sequencing (towards dig. 5V cards)
     - `117 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/117/>`_
     - `36 (dVlt) <https://bitbucket.org/ultrazohm/uz_d_voltage/issues/36/>`_
   * - Optimize DC/DC converters of CAN & SPI (w.r.t. costs)
     - `121 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/121/>`_
     -
   * - Implement resets of Ethernet PHYs
     - `122 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/122/>`_
     -
   * - Improve onboard I²Cs (add mux, unify with MZ, ...)
     - `123 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/123/>`_, `126 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/126/>`_
     -
   * - Add support for adapter card identification [including detection of signal directions on dig. volt. (dVlt) cards]
     - `138 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/138/>`_ and `uz_sw PR444 <https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/444>`_
     - `6 (D slot templ.) <https://bitbucket.org/ultrazohm/uz_d_template/issues/6/>`_, `[37 dVlt] <https://bitbucket.org/ultrazohm/uz_d_voltage/issues/37/>`_
   * - Integrate SSD, EEPROMs, frontpanel GPIO, PCIe, etc.
     - `124 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/124/>`_
     - `5 (lilac board) <https://bitbucket.org/ultrazohm/uz_per_rtc_mac/issues/5/overall-design-plan-for-v2#comment-64818326>`_
   * - Integrated isolated dual-JTAG solution
     - 
     - 
   * - Replace (D slot) CPLDs
     - `127 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/127/>`_
     -
   * - Redesign front (and back?) panel
     - `130 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/130/>`_, `141 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/141/>`_
     - `FP8 <https://bitbucket.org/ultrazohm/uz_frontpanel/issues/8/>`_ / `9 <https://bitbucket.org/ultrazohm/uz_frontpanel/issues/9/>`_ / `10 <https://bitbucket.org/ultrazohm/uz_frontpanel/issues/10/>`_, `H16 <https://bitbucket.org/ultrazohm/housing/issues/16/>`_
   * - Add system fan (connectors)
     -
     - `H17 <https://bitbucket.org/ultrazohm/housing/issues/17/>`_
   * - Redesign isoGPIOs and make them available on panel
     - `134 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/134/>`_
     - 
   * - Remap ``PS_ANL_shared`` to/and fix CD of the µSD card
     - `128 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/128/#comment-66486138>`_, `135 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/135/>`_
     -
   * - (Migrate SoM from TE0808 to TE0818
     - `131 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/131/>`_)
     -
   * - Add System&Safety CPLD
     - `143 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/143/>`_, `132 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/132/>`_
     -
   * - Move PSU to far-right corner of chassis
     - `136 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/136/>`_
     - `branch H repo <https://bitbucket.org/ultrazohm/housing/branch/feature/redesign_rev05>`_
   * - Protect the VIn, 5V and 3V3 rails at the slots (cf. :ref:`spec <carrier_board_rev3_slotpower>`)
     - `146 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/146/>`_
     -
   * - Make PL MGT transceivers usable
     - `133 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/133/>`_
     -

