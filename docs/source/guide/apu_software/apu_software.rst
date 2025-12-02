.. _apu_software:


============
APU Software
============

The APU runs FreeRTOS to read and write data to/from RPU and transfer it to a host PC using Ethernet.
Furthermore, it -- optionally (as of early 2024) -- may rely on the UltraZohm Platform (UZP) framework to identify its execution environment (i.e., the revision of the carrier card and revision, models and serials of the adapter cards populated).

..	toctree::
    :maxdepth: 1
    :caption: APU Software

    datamover_a53
    uzp_a53
    a53_accelerator
