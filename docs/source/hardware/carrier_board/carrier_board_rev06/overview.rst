.. _carrier_board_rev6_overview:

========
Overview
========

These pages document Rev06 of the UltraZohm carrier.
This revision only features minor changes compared to Rev05 as described :ref:`below <carrier_board_rev6_summary>`.

An overview about the interfaces of pre-Rev04 systems is shown in chapter :ref:`label_carrier_board_overview`, whilst the additions of Rev04 and Rev05 are documented :ref:`here <carrier_board_rev04_features>` and :ref:`here <carrier_board_rev5_summary>`.

Please note that the

- :ref:`carrier_board_rev5_whatsdifferent` and
- :ref:`carrier_board_rev5_hints`

sections from :ref:`Rev05 <carrier_board_rev5_overview>` remain valid for Rev06.


.. _carrier_board_rev6_summary:

Summary of new Features and Changes
-----------------------------------

* The per-slot current limiting (with error signaling to S3C / CPLDs) has been extended (from VIN) to 5V_PER and 3V3_PER
* The shared error signal of the A slots has been renamed (previously ANL_VIN_FLT, now ANL_RailF̅A̅U̅L̅T̅ to match the above)
* Furthermore, individual slots (i.e., their three supply rails) can now be disabled on a per-slot basis if not required
	* This simplifies error handling (on S3C / CPLDs) and
	* can be controlled via I²C from either S3C or uz_sw.
* :ref:`Rev02 of the updated front panel (FP) <frontpanelmainboard_rev02>` with improved **Isolated IOs** ("isoIOs") for
	* a higher output current on ``X6`` for external devices, and
	* individually current-limited in- and external supply rails.
* The ANL_S3C.P54_Legacy signal (cf. ANL_Pin55_Legacy in :ref:`Rev05 <carrier_board_rev5_summary>`) now is buffered for improved clock distribution via a LMK1C1104 (U14)
* Fixes :ref:`carrier_known_issues_rev05a` by means of the per-slot disable feature of the three A slots (cf. above) and :ref:`carrier_known_issues_rev05b`
* Various production-related optimizations (functions unchanged)


Downloads
---------

:download:`Schematic Rev06 <altium_output/SCH_UZ_CarrierBoard_Rev06Batch00_06.pdf>`
