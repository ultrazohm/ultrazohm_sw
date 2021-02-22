.. UltraZohm documentation master file, created by
   sphinx-quickstart on Tue Feb  4 21:12:00 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Documentation of the UltraZohm
==============================

.. image:: https://docs.ultrazohm.com/_images/front_lowres.png
  :width: 500
  :align: center

The UltraZohm is a powerful real-time computation platform for research, development, and rapid-control prototyping of power electronics and drive systems.
Development is driven by researchers for researches to accelerate research by establishing a common control platform.
Having a common platform enables the active research community to focus on publication and results, while the platform development is a shared effort. 

- **High Computational power**: Four ARM A53, two ARM R5, and a large FPGA provided by a Xilinx Zynq UltraScale+ MPSoC.
- **Hard real-time**: Designed to meet modern control systems' timing requirements for power electronics.
- **Open Source**: Platform with no black-boxes and no barriers for your research. Adapt to your needs and use as you like.
- **Modularity**: Extend the platform with your own hardware (adapter cards), IP-Cores and software components.
- **Usability**: Novice friendly with tutorials and existing codebase. Expert friendly with access *to the last bit*.
- **Community**: Connect to other researchers working on the same platform and solve infrastructure problems only once!
- **Documentation**: Comprehensive and ever-growing documentation for the Ultrazohm on `docs.ultrazohm.com <https://docs.ultrazohm.com/>`_.
- **Funded**: Project development is funded by the `BMBF with the research grant KI-Power <https://elektronikforschung.de/projekte/ki-power>`_.

Getting-started
---------------

- How to get an UltraZohm? Please shoot us a Mail at info@ultrazohm.com
- More information on `ultrazohm.com <https://ultrazohm.com/>`_

Research
--------

The primary use of the UltraZohm is the research of modern control algorithms for power electronics and drive systems:

- Model predictive control of electric drives
- Model predictive control of power electronics systems
- Renewable energy systems
- Multilevel converter including Modular Multilevel Converter (MMC)
- Multi-phase motors (m>3)
- Special electric motor designs (e.g., transverse flux machine, synchronous reluctance motor)
- Machine Learning in drive systems

License
-------

The project is licensed under the Apache 2.0 license. See LICENSE for details.


Syllabus
--------

.. toctree::
    :maxdepth: 2
    :caption: Getting-Started

    getting_started/toolchain/index
    getting_started/quickstart/index
    getting_started/tutorials/index

.. toctree::
    :maxdepth: 2
    :caption: General

    general/overview
    general/project_structure
    general/bitbucket
    general/contribution_workflow
    general/tcl_scripts
    general/ci_pipeline
    general/howToDocs/howToDocs
    general/useCases/useCases

.. toctree::
    :maxdepth: 2
    :caption: MPSoC Platform

    mpsoc/vivado/index
    mpsoc/ip_cores/index
    mpsoc/vitis/vitis
    mpsoc/CPLD/index

.. toctree::
   :maxdepth: 2
   :caption: User Software

   software/gui/index

.. toctree::
   :maxdepth: 2
   :caption: Codegeneration

   code_generation/hdl_coder/index
   code_generation/vivado_hls/index
   code_generation/embedded_coder/index

.. toctree::
   :maxdepth: 2
   :caption: Hardware

   hardware/carrier_board/index
   hardware/adapter_boards/index
   hardware/altium/altium

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
