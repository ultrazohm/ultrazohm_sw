.. _uz_d_absolute_encoder:

========================
Digital Absolute Encoder
========================

The ``uz_d_absolute_encoder`` adapter card provides absolute encoder interfaces.
The board is intended to connect EnDat and SSI encoders to the UltraZohm digital adapter card slots.

Use this page as the entry point and select the page that matches the hardware revision in use.

Revisions
=========

.. toctree::
   :maxdepth: 1

   uz_d_abs_encoder_v1/uz_d_abs_encoder_v1
   uz_d_abs_encoder_v2/uz_d_abs_encoder_v2

General Notes
=============

* Check the exact hardware revision before connecting an encoder.
* Verify encoder supply voltage and connector pinout against the schematic of the used revision.
* Program the CPLD for the selected digital adapter slot with the program ``uz_d_abs_encoder``, see :ref:`label_cpld_programming` for the programming procedure.
* Software support for the EnDat IP core is documented in :ref:`uz_endat_interface`.
* Software support for the SSI IP core is *coming soon*.

Revision History
================

.. list-table::
   :header-rows: 1
   :widths: 20 30 50

   * - Revision
     - Date
     - Notes
   * - Rev01
     - Jan 2025
     - Initial hardware revision.
   * - Rev02
     - May 2025
     - Added manual switch for selecting encoder supply voltage 5V or 24V
