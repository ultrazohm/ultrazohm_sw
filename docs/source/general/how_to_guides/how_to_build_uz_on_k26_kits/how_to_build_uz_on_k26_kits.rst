.. _how_to_build_uz_on_k26_kits:

============================================================
Building the UZ-Framework for the Kria Kits with TCL-Scripts
============================================================

To speed up the implementation of the UZ project on K26 kits, using tcl scripts can be helpful. 
The purpose of this how-to guide is to provide instructions for building the existing UltraZohm project on K26 kits in order to create a HiL (Hardware-in-the-Loop) environment. 
Once you have completed the getting-started flow and porting the UZ-Framework flow, you can use this guide. 
The flow structure includes the implementation of the Vivado project, generation of the Vitis workspace, and usage of the UltraZohm project.

Prerequisites
=============

#. Getting-Started and Porting the UZ-Framework for the Kria Kits completed and understood
#. An evaluation kit to use

    *  A `KR260 <https://www.xilinx.com/products/som/kria/kr260-robotics-starter-kit.html>`_ evaluation kit 
    *  A `KV260 <https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit.html>`_ evaluation kit 

#. Install Vitis and Vivado **2022.2**, download `here <https://www.xilinx.com/support/download.html>`_
#. Basic knowledge of the used tools.

Vivado
======

The default Vivado project (see :ref:`default_vivado_project`) can be generated using the ``build.tcl`` (see :ref:`vivado_build_tcl`) script.
Based on this, you can implement the default Vivado project (as a HiL version) on K26 kits by using the ``build_kria.tcl`` script.
Since these scripts are coupled with the paths in the ultrazohm_sw/vivado folder, they are not included in tcl_scripts (see Tcl Scripts) but located in ultrazohm_sw/vivado.

build_kria
----------

Generates the UltraZohm Vivado project (``ultrazohm.xpr``).
Usage: 

#. Open ``ultrazohm_sw/vivado`` repository on your local file system
#. Edit build_kria.tcl (line: 41 - 53) according to your K26 kit and save 
#. Open Vivado
#. Click on ``Window`` -> ``Tcl Console``
#. A window on the bottom of Vivado appears (*Tcl Console*)
#. Navigate to the location of the ``ultrazohm_sw`` repository on your local file system using ``cd`` in the tcl console
#. Navigate to ``ultrazohm_sw/vivado`` in the tcl console
#. Call build_kria.tcl with:

.. code-block::

    source build_kria.tcl