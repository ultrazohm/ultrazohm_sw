.. _uz_IM_protection:

========================
Drive protection and errors
========================

The software protection layer evaluates measured DC-link voltage, phase
currents, mechanical speed and numerical validity. Detected errors are encoded
as bits in the latched ``error_reason`` mask.

Configuration
=============

.. doxygenstruct:: error_checks_config_t
   :members:

The IM limits originate from the selected IM motor configuration. VA limits are
independent hardware limits. Protection thresholds must be chosen below the
absolute ratings of the inverter, sensors and machine.

Error bits
==========

The public ``ERR_*`` definitions distinguish:

* IM DC-link under- and overvoltage,
* IM phase U/V/W overcurrent,
* IM overspeed,
* VA DC-link overvoltage,
* VA phase U/V/W overcurrent,
* invalid measurements,
* invalid observer calculations.

Evaluation and reporting
========================

.. doxygenfunction:: error_checks_step

.. doxygenfunction:: error_checks_report

``error_checks_step`` is called before control execution. Observer modules can
call ``error_checks_report`` later in the same ISR. A second trip check before
PWM output ensures that these numerical observer faults are handled within the
same control period.

Latch and reset
===============

.. doxygenfunction:: error_checks_trip_pending

.. doxygenfunction:: error_checks_reset

Reporting an error ORs its bits into ``error_reason``, updates JavaScope
diagnostic latches and requests the platform error state. The ISR then disables
both controllers, sets both PWM groups to tristate and writes neutral duty
cycles. Errors remain latched until the explicit reset command is processed.

Software checks complement rather than replace independent hardware protection
in the programmable logic and gate drivers.
