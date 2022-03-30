.. _viavdo_build_tcl:

========================
Vivado build tcl scripts
========================

Since these scripts are coupled with the paths in the ``ultrazohm_sw/vivado`` folder, they are not included in ``tcl_scripts`` (see :ref:`tcl_scripts`).

.. _vivado_build_tcl_compatibility:

Compatibility with TE0803
=========================

The default Vivado project is compatible with TE0808 (default with 9EG).
Additionally, TE0803 can be used.
Both SoM are mostly pin compatible but some positive and negative pairs of differential signals that are used as LVDS for A1, A2, and A3 are swapped.
To achieve compatibility, and external IOBUF is used instead of the internal IOBUF of the :ref:`ipCore_LTC2311_v3`.
Depending on the board version, some of the signals are inverted using a magic constant (``A1_inv_Input``) that is set when generating the Vivado project according to the selected SoM (by ``build_selected_target.tcl``).

.. _adc_io_buff_compatibility:

.. figure:: adc_input_buffer.png

  External IOBUF for ADC IP-Core and constant to invert signals depending on SoM (TE0808 or TE0803).

Implementation details
======================

build.tcl
---------

Generates the UltraZohm Vivado project (``ultrazohm.xpr``) for the TE0808 SoM with an UltraScale 9EG.

build_selected_target.tcl
-------------------------

Generates the UltraZohm Vivado project (``ultrazohm.xpr``) for a specified System-on-a-Module.
Tested are TE0803 with 2EG (``"trenz.biz:te0803_2eg_1e:part0:1.0"``) and 3EG (``"trenz.biz:te0803_3eg_1e:part0:1.0"``).
build_selected_target.tcl
Before calling ``, the ``board_part`` has to be changed to the desired SoM:

.. code-block::

    set board_part "trenz.biz:te0803_2eg_1e:part0:1.0"


update_tcl_scripts_for_vc.tcl
-----------------------------

This script has to be called to incorporate changes to the default Vivado project into the ``build.tcl`` script.


process_xdc.py
--------------

