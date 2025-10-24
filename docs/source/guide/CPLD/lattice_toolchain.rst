.. _install_lattice:

================================
Install Lattice Toolchain (CPLD)
================================

You need different tools depending on 
whether you want to program an existing 
bitstream to a CPLD or create a custom CPLD program. 
The diagram below will guide you to the right tool.
You will need to create a free Lattice account to download the tools.

.. mermaid::
    :align: center
    :caption: Lattice tool guide 

    flowchart TD;
    A[Program existing bitstream to CPLD] -->|ispMACH and MACHXO2 CPLDs|B[Diamond Programmer <br> Standalone];
    B -->H[Programming the CPLD];
    C[Create a custom CPLD program] -->|ispMACH LA4128V and LC4256V CPLDs|D[ispLEVER Classic];
    C -->|MACHXO2 CPLDs|E[Lattice Diamond];
    D -->F[Create a CPLD program <br> using ABEL];
    E -->G[Create a CPLD program <br >using Lattice Diamond];

Diamond Programmer Standalone
-----------------------------
To program CPLDs, please download and install the Lattice Diamond Programmer Standalone.

* `Lattice Diamond Programmer Standalone download <https://www.latticesemi.com/latticediamond>`_

.. warning::

    Make sure you scroll down and select the **Programmer Standalone**, it is roughly 50-60 MB

.. image:: ./images_lattice/lattice_programmer_standalone.jpg
  


ispLEVER Classic
----------------

To create a new program for ispMACH ``LA4128V`` or ``LC4256V`` CPLDs, you need ispLEVER Classic.

* `ispLEVER Classic download <https://www.latticesemi.com/ispleverclassic>`_
* Make sure you scroll down and select the **ispLEVER Classic Base Module**, it is roughly 700-800 MB
* You will need a license, for academic use it can be requested by `writing an email <mailto:lic_admn@latticesemi.com>`_ stating 
    
  - your ispLEVER Classic version and 
  - the MAC address of your computer. 


Lattice Diamond
---------------

To create a new program for ``MACHXO2`` series CPLDs, you need Lattice Diamond.

* `Lattice Diamond download <https://www.latticesemi.com/latticediamond>`_

.. warning::

    Make sure you scroll down and select the **Diamond x.xx 64-bit for...**, it is roughly 1.6-2.1 GB.

.. image:: ./images_lattice/lattice_diamond.png