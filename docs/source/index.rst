Documentation of the UltraZohm
==============================

.. image:: https://docs.ultrazohm.com/_images/front_lowres.png
  :width: 500
  :align: center

The UltraZohm is a powerful real-time computation platform for research, development, and rapid-control prototyping of power electronics and drive systems.
Development is driven by researchers for researches to establishing a common control platform.
Having a common platform enables the active research community to focus on publication and results, while the platform development is a shared effort. 

- **High Computational power**

    The UltraZohm is based on a  Xilinx Zynq UltraScale+ MPSoC. Four ARM A53, two ARM R5, and a large FPGA provided by a (ZU9EG).

- **Hard real-time**: Designed to meet modern control systems' timing requirements for power electronics.
- **Open Source**: Platform with no black-boxes and no barriers for your research. Adapt to your needs and use as you like. The project is licensed by Apache 2.0, the hardware is licensed under CERN-OHL-P. See :ref:`license_target`.
- **Modularity**: Extend the platform with your own hardware, adapter cards, IP-Cores and software components.
- **Usability**: Novice friendly with tutorials and existing codebase. Expert friendly with access *to the last bit*.
- **Community**: Connect to other researchers working on the same platform and solve infrastructure problems only once!
- **Documentation**: Comprehensive and ever-growing documentation for the Ultrazohm on `docs.ultrazohm.com <https://docs.ultrazohm.com/>`_.
- **Funded**: Project development is funded by the `BMBF with the research grant KI-Power <https://elektronikforschung.de/projekte/ki-power>`_.

Getting-started
---------------

- How to get an UltraZohm? Please shoot us a Mail at info@ultrazohm.com
- Join the `UltraZohm Slack <https://join.slack.com/t/ultrazohm/shared_invite/zt-l6mbbef6-2HNXR21vT_5TRT4l2J1pNw>`_ 
- More information on `ultrazohm.com <https://ultrazohm.com/>`_
- `Open in Gitpod <https://gitpod.io/#https://bitbucket.org/ultrazohm/ultrazohm_sw/src/main/>`_


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

.. _license_target:

License
-------


The project is licensed under the Apache 2.0 license.
See `LICENSE <https://bitbucket.org/ultrazohm/ultrazohm_sw/src/main/LICENSE>`_ for details.
The source of the documentation is located in `ultrazohm_sw/docs <https://bitbucket.org/ultrazohm/ultrazohm_sw/src/main/docs/>`_.

The hardware is documented in :ref:`carrier_board` and :ref:`adapter_cards` including schematics and assembly files.
Additionally, the source files of the PCBs is available in the `PCB-Design project <https://bitbucket.org/ultrazohm/workspace/projects/PCB>`_.
Note that due to specifics of Bitbucket, this project is only visible for users that are part of the UltraZohm workspace.
The individual repositories of the PCB projects can be accessed directly if one is not part of the Ultrazohm workspace, e.g. `DAC-Card repository <https://bitbucket.org/ultrazohm/uz_a_dac8831/>`_.
The documentation pages of the PCB links to their respective repository.
The preferred license for hardware within the UltraZohm project is the `CERN Open Hardware License Version 2 - Permissive <https://ohwr.org/cern_ohl_p_v2.pdf>`_ (CERN-OHL-P).
The UltraZohm project uses :ref:`altium` for PCB design.


Syllabus
--------

.. toctree::
   :hidden:
   :caption: Repository

    ultrazohm_sw <https://bitbucket.org/ultrazohm/ultrazohm_sw>

.. toctree::
    :maxdepth: 2
    :caption: Getting-Started
    
    getting_started/onboarding/onboarding
    getting_started/toolchain/index
    getting_started/ultrazohm_setup/ultrazohm_setup
    getting_started/tutorials/index

.. toctree::
    :maxdepth: 2
    :caption: General

    general/system_overview
    general/project_structure/project_structure
    general/infrastructure/infrastructure
    general/how_to_guides/how_to_guides
    general/useCases/useCases

.. toctree::
    :maxdepth: 2
    :caption: MPSoC Platform

    mpsoc/platform_architecture/platform_architecture
    mpsoc/rpu_software/rpu_software
    mpsoc/apu_software/apu_software
    mpsoc/software_framework/software_framework
    mpsoc/vivado_framework/vivado_framework
    mpsoc/ip_cores/ip_cores
    mpsoc/CPLD/index

.. toctree::
   :maxdepth: 2
   :caption: User Software

   software/gui/index

.. toctree::
   :maxdepth: 2
   :caption: Codegeneration

   code_generation/hdl_coder/hdl_coder
   code_generation/vivado_hls/index
   code_generation/embedded_coder/embedded_coder

.. toctree::
   :maxdepth: 2
   :caption: Hardware

   hardware/carrier_board/carrier_board
   hardware/adapter_cards/adapter_cards
   hardware/interface_powerelectronics/interface_powerelectronics
   hardware/altium/altium

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
