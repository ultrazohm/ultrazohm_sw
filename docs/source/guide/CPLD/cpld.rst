====
CPLD 
====

The Carrier Board has one CPLD for each digital interface slot, D1-D5 (``D-slot CPLDs``).
They are used to shift the voltage level from 1.8V (FPGA) to 3.3V (Adapter Boards).
For each adapter board the appropriate CPLD program must be programmed into the CPLD, 
which basically sets the signal directions and pins.
If needed, additional safety can be implemented, e.g. checking switch combinations or ensuring dead time. 
UltraZohms with carrier board Rev05 or higher have an additional ``System Supply and Safety Controller - S3C``. 
It controls basic system functions such as power up sequencing, power rail monitoring, etc. . 
If the user has to deal with the CPLDs, it is most likely that it is about the ``D-slot`` CPLDs and their 
respective programs. Most users will never have to deal with the ``S3C``.

The following diagrams are intended to guide the user to the appropriate part of this docs section, depending 
on the use case, where the second diagram is only relevant when dealing with the ``S3C``.
For example, if you want to know how to program an existing CPLD program into one of the ``D-slot CPLDs``, 
you would follow the diagram below: CPLD - D-slot CPLDs - Programming the CPLD. So you would 
go to the :ref:`label_cpld_programming` section and continue from there. 

.. mermaid::
    :align: center
    :caption: Use cases for interaction with the CPLDs

    flowchart TD;
    A[CPLD] -->|Digital adapter board slots|B[D-Slot CPLDs];
    A -->|System Supply and Safety Controller|C[S3C];
    style C fill:#f9f
    B -->|Program CPLD with existing bitstream to use it with an existing adapter board|D[Programming the CPLD];
    D -->|Carrier Rev04 and before|H[LA4128V or LC4256V];
    D -->|Carrier Rev05 and after|I[MachXO2 LCMXO2-2000HC];
    B -->|New CPLD program needed|E[Create a CPLD program...];
    E -->|Carrier Rev04 and before|F[...using ABEL];
    E -->|Carrier Rev05 and after|G[...using Lattice Diamond];

If you need to change things for the ``S3C``, proceed as shown in the diagram below.

.. mermaid::
    :align: center
    :caption: Interaction with S3C

    flowchart TD;
    A[S3C] -->|Program S3C with existing bitstream|B[Programming the CPLD];
    style A fill:#f9f
    A -->|New S3C program needed|C[Create a CPLD program using Lattice Diamond];

Types of CPLDs used in different revisions of the UltraZohm
***********************************************************

As already mentioned in the diagrams above, there are different types of CPLDs 
in the different revisions of the UltraZohm. 
Below is a rough overview.

*****************************************************
ispMACH series (:ref:`carrier_board_rev4` and before)
*****************************************************

UltraZohms :math:`\leq` ``Rev04`` are equipped with CPLDs of the ispMACH series (LA4128V or LC4256V).

****************************************************
MachXO2 series (:ref:`carrier_board_rev5` and later)
****************************************************

UltraZohms :math:`\geq` ``Rev05`` and later are equipped with CPLDs of MachXO2 series. The D-Slots employ the type ``LCMXO2-2000HC-4TG100C``, 
whereas the S3C CPLD for overall system control is of type ``LCMXO2-4000HC-4TG144C``.

..	toctree::
    cpld_create_program
    cpld_programming
    lattice_toolchain    
    diamond_create_program
 