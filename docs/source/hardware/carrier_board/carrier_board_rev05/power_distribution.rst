=======================
Power Distribution
=======================

.. warning::
	Please note that in Rev05 the :ref:`carrier_board_rev5_s3c` is responsible for the Powersequence of the Carrierboard. If the configuration is changed this graph is no longer valid.


Power Distribution Dependency
"""""""""""""""""""""""""""""

The following diagram shows in which flow the rails (equals with signal names in the schematic) of the carrier board are powered. 

.. mermaid::

	graph LR
	A(X14, X14B) -->|Rush In Current Lim, Fuse, <br>Reverse Polarity,<br>Overvoltage Protection| VIN{VIN}
	X14 -->|Fuse F2, Diode D7| VIN_S3C
	VIN -->|Diode D6| VIN_S3C
    VIN --> X15
	VIN_S3C --> |U23C| 3V3_S3C
	S3C((S3C))
    3V3_S3C --> S3C
    S3C -->|Enable CarrierPwrOn| 3V3_MOD
	VIN -->|U10, 3.3 V,<br>5.0 A max| 3V3_MOD
    VIN -->|U11, 3.3 V,<br>5.0 A max| 3V3_PER
    VIN -->|U12, 5.0 V,<br>5.0 A max| 5V_PER
    PG_Module --> |Enable|1V8_MOD
    PG_Module --> |Enable|1V8_PER
	VIN -->|U23A, 1.8 V,<br>2.5 A max| 1V8_MOD 
	VIN -->|U23A, 1.8 V,<br>2.5 A max| 1V8_MOD
    1V8_MOD -->|Jumper R128| VCCO_47
    1V8_MOD -->|Jumper R129| VCCO_48
    1V8_MOD -->|Jumper R133| VCCO_64
    1V8_MOD -->|Jumper R131| VCCO_65
    1V8_MOD -->|Jumper R136| VCCO_66
	VCCO_47 -.-> SoM((SoM))
	VCCO_48 -.-> SoM
	VCCO_64 -.-> SoM
	VCCO_65 -.-> SoM
	VCCO_66 -.-> SoM
	3V3_MOD -.-> SoM

Power-On Sequence
"""""""""""""""""

There is a recommended sequence of powering up the Xilinx Zynq UltraScale+ MPSoC power domains. The SoM cares about the power-on sequence of their components such as Low-Power Domain, Full-Power Domain and memory.
For more information see `TE0808 Rechnical Reference Manual <https://wiki.trenz-electronic.de/display/PD/TE0808+TRM#TE0808TRM-Power-OnSequenceDiagram>`_.
The carrier board differs between power-on the Processing System (PS) and Programical Logig (PL) part of the SoM. The PS has to be powered-up before PL.
Sequence *Stage 1* starts with applying the 24 V power supply at X14 to rail *VIN*. Thus it powers up the SoM after *3V3_MOD* is available (*Stage 2*).
The SoM feedbacks with a "power good" signal *PG_Module* to enable the power supply for the PL (through *1V8_MOD*).

.. mermaid::

	sequenceDiagram
		participant VIN
		participant VIN_S3C
		participant 3V3_MOD
		participant 3V3_PER
		participant 5V_PER
		participant 1V8_MOD
		participant 1V8_PER
		participant SoM
		VIN->>+VIN_S3C: Stage 1
        VIN_S3C->>+3V3_MOD: Enable
		3V3_MOD->>+3V3_PER: Stage 2
		3V3_PER->>+5V_PER: Stage 3
		3V3_MOD->>+SoM: Stage 2
		SoM->>+1V8_MOD: PG_Module
		SoM->>+1V8_PER: PG_Module
		1V8_MOD->>+SoM: Stage 4
