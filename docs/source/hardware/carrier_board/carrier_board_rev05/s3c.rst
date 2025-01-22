.. _carrier_board_rev5_s3c:

============================
System Supply & Safety $CPLD
============================


General
-------

- Device: Lattice Mach XO2
- Part: LCMXO2-4000HC-4TG144C
- Designator: U19
- Supplied by 3V3_S3C, 3V3_PER, 1V8_PER and (if needed) 1V8_S3C
- Integrated Flash memory for configuration storage (bitstream)
- Programmable via JTAG, SPI (PS-SPI0) and I²C (PS-I2C1)
- No external clock source integrated on carrier

Unlike in previous revisions of the UltraZohm,
	- the frontpanel no longer comes with a red power switch (previously located between the 24V power supply and the carrier), and
	- the various on-board supplies (derived from the incoming 24V) no longer power up automatically after the 24V are switched on.

Instead, there now are
	- a "first-level" power *switch* on the backpanel (as part of the line-supply connector assembly), and
	- a "second-level" power *button* on the frontpanel (that replaces the aforementioned red switch).

When the backpanel-side switch is on, the PSU's 24V only power up a newly-added supply rail dedicated to the S³C (3V3_S3C).
All other rails are ramped up as soon as the user presses the frontpanel-side power button, which is monitored by the S³C.
Then, the well-known ramp-up sequence of previous carrier boards is started by enabling the now-default-off 3V3_MOD (U10).


.. _carrier_board_rev5_s3cfsm:

Statemachine for S³C
--------------------


.. mermaid::

	stateDiagram-v2

	state UZ {	
	[*] --> Waiting_for_Powerbutton_pressed
	Waiting_for_Powerbutton_pressed --> Waiting_for_Powerbutton_released
	Waiting_for_Powerbutton_released --> Wait_State
	Wait_State --> EthernetPhy_Reset
	EthernetPhy_Reset--> Ready_State
	Waiting_for_Powerbutton_pressed_2sec --> Ready_State
	Waiting_for_Powerbutton_pressed_2sec --> SoftError
	Waiting_for_Powerbutton_pressed_2sec --> Warning
	Operation --> Waiting_for_Powerbutton_pressed_2sec
		state Operation {
		Ready_State --> Warning
		Ready_State --> SoftError
		Warning --> SoftError
		SoftError --> Warning
		SoftError --> Ready_State
		Warning --> Ready_State
		}
	Waiting_for_Powerbutton_pressed_2sec --> Waitingfordslotdown
	Waitingfordslotdown --> Waiting_for_Powerbutton_released2
	Waiting_for_Powerbutton_released2 --> Waiting_for_Powerbutton_pressed
	}
	UZ --> HardError
	HardError --> Acknowledge_Error
	Acknowledge_Error --> Waiting_for_Powerbutton_released2


.. _carrier_board_rev5_s3cpwr:

Powerbutton Functionality
-------------------------

The Power button interacts with the S3C statemachine, and its LED coloring indicates in which state the safety controller currently is.

.. list-table::
   :align: center
   :widths: 25 75

   * - .. figure:: img/230v_off.jpg
          :align: center
          :scale: 25%
     - In case the 230V are switched off (via the switch on the backside), the frontpanel will look as shown on the left.

   * - .. figure:: img/systemoff.png
          :align: center
          :scale: 50%
     - When enabling the 230V on the backside of the UZ with the switch, the S3C is supplied and the Power button indicates this with a blue ring.

   * - .. figure:: img/powering_up.png
          :align: center
          :scale: 50%
     - The user has to press the button for the system to turn on.
       This state is indicated by a purple ring.
       After releasing the button, the system goes into a sequenced power-up procedure.

   * - .. figure:: img/system_on.png
          :align: center
          :scale: 50%
     - From now on, the system is fully powered on, and the Powerbutton ring is green and the stop button ring is (flashing) red.

       **At this stage, the system can be programmed in Vitis and used in the usual manner.**

       .. warning::
           At this stage, the Javascope GUI and the physical frontpanel buttons are not synchronized.

       	If the user decides to just use the GUI to enable/control the system and then pushes the stop button there, the behavior will be different to pushing the hardware buttons directly.
       	Only the hardware buttons affect (i.e., set and reset) the hardware release (i.e., are able to return the S3C statemachine from soft errors or warnings back to the ready state), which drives the output enables of the level shifters on new D adapter cards.

       	It thus is not recommended to mix physical control using the buttons on the frontpanel with control via the GUI.
       	E.g., if the control was stopped with the frontpanel's physical button and the system is then enabled with the GUI, the hardware is not released - Yielding an inoperative state.

   * - .. figure:: img/system_stopped.png
          :align: center
          :scale: 50%
     - The user can push the stop button and the Power ring will indicate white.

   * - .. figure:: img/enable_again.png
          :align: center
          :scale: 50%
     - This means that the safety controller commands all five digital slots into their respective safe state.
       To re-enable the digital slots, there are two possibilities:

       1. Press the Enable System button

   * - .. figure:: img/enable_via_powerbutton.png
          :align: center
          :scale: 50%
     - Or:

       2. Press the Power button

   * - .. figure:: img/error.png
          :align: center
          :scale: 50%
     - An external emergency can be communicated to the S3C via the external stop connector.
       The Power button indicates a red light and the S3C brings the system in a safe state.

   * - .. figure:: img/error_to_be_confirmed.png
          :align: center
          :scale: 50%
     - Once the system is in this state, the user has to acknowledge this error with the Power button.

   * - .. figure:: img/error_confirm_by_user.png
          :align: center
          :scale: 50%
     - The S3C gets back into the initial state and the user can power it on as described above.

   * - .. figure:: img/poweron_user.png
          :align: center
          :scale: 50%
     - Regular power off is realized with the Power button.
       It has to be pushed at least 2 seconds to power off.


Functions (partially draft-level)
---------------------------------

- Default routes of "pass-through signals"
	- ``FrontpanelIO.ExternalSTOP`` -debounce-> ``FlexMIOs.61_ExternalSTOP`` (add latch functionality? reset by power cycle?)
	- ``FlexMIOs.52_PCIe-R̅S̅T̅`` -> ``FrontpanelIO.FlexMIO52_PCIe-R̅S̅T̅`` (depending on PS configuration, an inversion might be required)
	- [*do not implement* until supported by the configuration of the PS!] ``SD0_CD`` (and, later, ``SD1_CD``, if implemented) -> ``FlexMIOs.45_SD-CD`` (depending on PS configuration, an inversion might be required)
	- [*do not implement* until supported by the configuration of the PS!] ``FrontpanelIO.isoCtrl.I̅N̅T̅`` -> ``FlexMIOs.54_I2C0-SharedI̅R̅Q̅``
- Other defaults
	- ``SD_SEL``: For the time being, this signal shall be driven to ``'0'``
	- ``FrontpanelIO.isoCtrl.R̅S̅T̅``: For the time being, this signal shall be driven to ``'1'``
- Power sequencing
	- On power-on of the S³C, drive ``Carrier_PwrOn`` low and keep it there, then check whether ``SysSW_Pwr_NC`` is high (delay required, probably)
	- On a (debounced, cf. above) falling edge on ``SysSW_Pwr_NC``, initiate the power sequencing (*hem*) sequence by
		- asserting ``Carrier_PwrOn``,
		- waiting for ``PG_Module`` to (de?)assert, and then, after some ms-range delay,
		- switching ``Carrier_PG_1V8`` (cf. below) from ``'Z'`` to ``'0'`` for some time and releasing it again (to ``'Z'``).
		- Of course, various LEDs are available to signal this process to the user ;-)
	- For the time being, power-off shall be initiated by a second-long low signal level on ``SysSW_Pwr_NC``, i.e., holding the power button. For any future versions of this bitstream (on the S³C) and ``uz_sw`` (on RPU and APU), a notification to software shall be added (in particular when logging to the SSD is used).
	- Current usage of power good (aka not-reset) signals
		- ``Carrier_PG_1V8``: Connected to ``RESETn`` of the two Ethernet PHYs (carrier and frontpanel-main, 10k pullup on carrier)
		- ``Carrier_PG_3V3``: Enables the DC/DC converter of the isoIO island's 3V3 rail (on frontpanel-main, no pullup/down R)
- To-be-discussed functionalities
	- "Request Safe State" signal from S³C to D slots: Potential triggers are supply rail monitors, ``FP_UsrSW3``, ``FrontpanelIO.ExternalSTOP``, ...


I/Os
----

- Static system-level I/O assignment
	- Inputs
		- Power sequencing and monitoring: ``PWRMON.PG_VIN``, ``PWRMON.P̅P̅_VIN``, ``THERMAL_DATA.S̅H̅D̅N̅``, ``THERMAL_DATA.F̅F̅/F̅S̅``, ``THERMAL_DATA.A̅L̅E̅R̅T̅``, ``PG_Module``
		- Frontpanel: ``FP_UsrSW[1-3]``, ``SysSW_Pwr_NC`` (power button), ``FrontpanelIO.ExternalSTOP``
		- Other system functions: ``SD[01]_CD``, ``FlexMIOs.52_PCIe-R̅S̅T̅``
		- isoIOs: ``FrontpanelIO.isoCtrl.I̅N̅T̅``
		- Slots: ``ANL_S3C.SlotOK[1-3]``, ``DIG_S3C.SlotD[1-5].ReqOE``, ``DIG_S3C.SlotD[1-5].SlotOK``
	- Outputs
		- Power sequencing and monitoring: ``Carrier_PG_1V8`` and ``_3V3``, ``Carrier_PwrOn``
		- Frontpanel: ``FP_SysLED[rgb]`` (RGB LED of power button), ``FP_SysLEDs`` (red LED of stop button), ``FP_UsrLED[1-4]``
		- Other system functions: ``SD_SEL``, ``FlexMIOs.45_SD-CD``, ``FrontpanelIO.FlexMIO52_PCIe-R̅S̅T̅``, ``FlexMIOs.54_I2C0-SharedI̅R̅Q̅``, ``FlexMIOs.61_ExternalSTOP``
		- isoIOs: ``FrontpanelIO.isoCtrl.R̅S̅T̅``
		- Slots: ``ANL_S3C.CarrierReady``, ``ANL_S3C.P54_Legacy``, ``DIG_S3C.Shared.CarrierReady``, ``DIG_S3C.SlotD[1-5].SlotOE``, ``DIG_S3C.Shared.ReqSafeState``
	- Special functions
		- ``JTAGENB`` (see `this post in issue 127 <https://bitbucket.org/ultrazohm/uz_carrierboard/issues/127/#comment-66977261>`_ for required config. option)
		- Pins 126/125 (primary I²C)
		- Pins 105/106 (secondary I²C)
- Dynamic application-level I/O assignment
	- ``FrontpanelIO.isoSigs.FlexIO0[1-5]`` can be used to drive the last five isoIOs (i.e., from ``IO09`` onwards) as 2x output, 2x input and 1x output (in that order) -- So the signal directions are fixed, but function is freely programmable
	- The six ``FlexLIOs[0-5]`` (flexible logic/PL IOs) are available between the S³C (and thus everything reachable from it) and the Zynq's PL
	- The S³C's twelve ``DIG5_S3C`` signals (00-05, 24-29) complement the SoM's 18 signals that interface slot D5
- Input-specific processing requirements
	- Debounce filtering: ``SysSW_Pwr_NC``, ``FP_UsrSW[1-3]``, ``FrontpanelIO.ExternalSTOP`` -- Note that all the above signals are low-active, i.e., high as long as the corresponding button is not pressed
- Output-specific processing requirements
	- Set to ``'Z'`` unless UZ is switched on (i.e., ``Carrier_PwrOn`` is asserted): ``FrontpanelIO.isoSigs.FlexIO0[1-5]``, ``FrontpanelIO.isoCtrl.R̅S̅T̅``, ``FrontpanelIO.FlexMIO52_PCIe-R̅S̅T̅`` -- Note that the above list will get considerably longer if R44 is populated (instead of R43). In that case, care has to be taken w.r.t. S³C bank 2 (i.e., U19C) driving current into powered-off components!
