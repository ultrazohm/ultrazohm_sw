.. _uz_d_absolute_encoder:

========================
Digital Absolute Encoder
========================

The ``uz_d_absolute_encoder`` adapter card family provides digital adapter cards for absolute encoder interfaces.
These cards are intended to connect EnDat and SSI encoders to the UltraZohm digital adapter card slots.

Use this page as the entry point for common information and select the page that matches the hardware revision in use.

Revisions
=========

.. toctree::
   :maxdepth: 1

   uz_d_abs_encoder_v1/uz_d_abs_encoder_v1
   uz_d_abs_encoder_v2/uz_d_abs_encoder_v2

General Notes
=============

* Check the exact hardware revision before connecting an encoder.
* Verify encoder supply voltage, connector pinout and differential line termination against the schematic of the used revision.
* Program the CPLD for the selected digital adapter slot, see :ref:`label_cpld_programming`.
* Software support for the EnDat IP core is documented in :ref:`uz_endat_interface`.
