.. _viavdo_build_tcl:

========================
Vivado build tcl scripts
========================

The default Vivado project (see :ref:`default_vivado_project`) can be generated using the ``build.tcl`` script.
Additionally, there are some helper scripts to facilitate the update of the ``build.tcl`` script after changes to the Vivado project are done.
Since these scripts are coupled with the paths in the ``ultrazohm_sw/vivado`` folder, they are not included in ``tcl_scripts`` (see :ref:`tcl_scripts`) but located in ``ultrazohm_sw/vivado``.

build.tcl
---------

Generates the UltraZohm Vivado project (``ultrazohm.xpr``).
Usage:

#. Open Vivado
#. Click on ``Window`` -> ``Tcl Console``
#. A window on the bottom of Vivado appears (*Tcl Console*)
#. Navigate to the location of the ``ultrazohm_sw`` repository on your local file system using ``cd`` in the tcl console
#. Navigate to ``ultrazohm_sw/vivado`` in the tcl console
#. Call build.tcl with:

.. code-block::

    source build.tcl

Calling the script leads to Vivado generating the project.

.. figure:: vivado_build_tcl.gif

  Call build.tcl to build the Vivado project

.. note:: The ``build.tcl`` script assumes that the UltraZohm is equipped with for the TE0808 SoM with an UltraScale 9EG.
          This is true for all standard UltraZohm systems, i.e., only special development systems at TH Nürnberg and TU München use other SoMs.

update_tcl_scripts_for_vc.tcl
-----------------------------

This script has to be called to incorporate changes to the default Vivado project into the ``build.tcl`` script.

.. warning:: Only call ``update_tcl_scripts_for_vc.tcl`` if the project use changed was build using ``build.tcl``.
             Do not use it if you used another project or a project that was generated using ``build_selected_target.tcl``!

Workflow:

#. Build Vivado project using ``build.tcl``
#. Make changes to Vivado Project
#. Save project
#. call ``update_tcl_scripts_for_vc.tcl``
#. Commit the changes

.. code-block::
   :caption: Changed files after ``update_tcl_scripts_for_vc.tcl`` is called.

   modified:   ip_cores/vv_index.xml
   modified:   vivado/_build.tcl
   modified:   vivado/bd/_zusys.tcl
   modified:   vivado/bd/zusys.tcl
   modified:   vivado/build.tcl
   modified:   vivado/project/ultrazohm.xpr
   modified:   vivado/project/zusys/zusys.bd


.. figure:: make_vivado_change_with_tcl_script.gif

  Make a change in the Vivado default project and save it using **update_tcl_scripts_for_vc**. Note that this is just an example change.

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


build_selected_target.tcl
-------------------------

Generates the UltraZohm Vivado project (``ultrazohm.xpr``) for a specified System-on-a-Module.
Tested are TE0803 with 2EG (``"trenz.biz:te0803_2eg_1e:part0:1.0"``) and 3EG (``"trenz.biz:te0803_3eg_1e:part0:1.0"``).
build_selected_target.tcl
Before calling ``build_selected_target.tcl``, the ``board_part`` has to be changed to the desired SoM:

.. code-block::

    set board_part "trenz.biz:te0803_2eg_1e:part0:1.0"

Implementation details
======================

process_xdc.py
--------------

