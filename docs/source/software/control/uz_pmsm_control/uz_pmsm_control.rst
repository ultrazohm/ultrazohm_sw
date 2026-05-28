.. _uz_pmsm_control:

============
PMSM Control
============

Description
-----------

The PMSM control module combines speed control, setpoint generation, current control,
coordinate transformations, and modulation to provide a complete control pipeline for a permanent magnet synchronous machine.
It supports direct dq-voltage output and direct duty-cycle output,
including setpoint limiting and safe operating region monitoring.

API Reference
-------------

Configuration and data types
============================

.. doxygenenum:: uz_pmsm_control_safe_operating_region_violation

.. doxygenstruct:: uz_limits_t
	:members:

.. doxygenstruct:: uz_pmsm_setpoint_limits_t
	:members:

.. doxygenstruct:: uz_pmsm_safe_operating_region_t
	:members:

.. doxygenstruct:: uz_pmsm_control_configuration_t
	:members:

.. doxygenstruct:: uz_pmsm_measurement_values
	:members:

.. doxygenstruct:: uz_pmsm_actual_data
	:members:

.. doxygenstruct:: uz_pmsm_reference_values
	:members:

Object and functions
====================

.. doxygentypedef:: uz_pmsm_control_t

.. doxygenfunction:: uz_pmsm_control_init

.. doxygenfunction:: uz_pmsm_control_get_actual_data

.. doxygenfunction:: uz_pmsm_control_get_reference_values

.. doxygenfunction:: uz_pmsm_control_get_pmsm_measurement_values

.. doxygenfunction:: uz_pmsm_control_enable

.. doxygenfunction:: uz_pmsm_control_sample_duty

.. doxygenfunction:: uz_pmsm_control_sample_dq

.. doxygenfunction:: uz_pmsm_control_reset

.. doxygenfunction:: uz_pmsm_control_enable_speed_control

.. doxygenfunction:: uz_pmsm_control_acknowledge_and_reset_error

.. doxygenfunction:: uz_pmsm_control_get_safe_operating_area_violation

.. doxygenfunction:: uz_pmsm_control_set_theta_offset

.. doxygenfunction:: uz_pmsm_control_get_pointer_to_theta_offset

.. doxygenfunction:: uz_pmsm_control_current_control_tune_magnitude_optimum

.. doxygenfunction:: uz_pmsm_control_current_control_tune_symmetric_optimum

.. doxygenfunction:: uz_pmsm_control_current_control_tune_bandwidth

.. doxygenfunction:: uz_pmsm_control_current_control_set_Kp_iq

.. doxygenfunction:: uz_pmsm_control_current_control_set_Ki_iq

.. doxygenfunction:: uz_pmsm_control_current_control_set_Kp_id

.. doxygenfunction:: uz_pmsm_control_current_control_set_Ki_id

.. doxygenfunction:: uz_pmsm_control_speed_control_set_Kp_speed

.. doxygenfunction:: uz_pmsm_control_speed_control_set_Ki_speed
