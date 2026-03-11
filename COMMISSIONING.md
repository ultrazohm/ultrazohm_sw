# Commissioning Guide — UltraZohm Induction Motor FOC

Branch: `feature/wolfspeed_inverter_adapterboard`
Firmware: Wolfspeed adapter board, 25 kHz ISR, 3-phase 2-level inverter

---

## 1. New Motor Checklist

**Edit one file only:** [`vitis/software/Baremetal/src/include/motor_config.h`](vitis/software/Baremetal/src/include/motor_config.h)

> **All parameters are star-equivalent (per-phase, referred to neutral).**
> The firmware measures line currents and drives line-to-neutral voltages;
> the Clarke/Park transforms and observer operate in the star-equivalent domain.
>
> | Motor winding | Rs / Rr | Lm / Lsigma | Psi_rated |
> |---------------|---------|-------------|-----------|
> | Star (Y) | use nameplate directly | use nameplate directly | V_L-L / (√3 · 2π · f_rated) |
> | Delta (Δ) | nameplate ÷ 3 | nameplate ÷ 3 | V_L-L / (√3 · 2π · f_rated) |
>
> If parameters come from `identify_motor_params.py` (log-based): the result is
> already star-equivalent regardless of motor winding — no conversion needed.

### Step 1 — Add a new configuration block

```c
/* Add your machine constant at the top */
#define MOTOR_CONFIG_MY_MACHINE   2

/* Change the active selection */
#define MOTOR_CONFIG_SELECT   MOTOR_CONFIG_MY_MACHINE

/* Add a new #if block with all parameters */
#if (MOTOR_CONFIG_SELECT == MOTOR_CONFIG_MY_MACHINE)
  #define MOTOR_Rs_Ohm              ???    /* stator resistance [Ω] */
  #define MOTOR_Rr_Ohm              ???    /* rotor resistance [Ω] */
  #define MOTOR_Lm_H                ???    /* magnetizing inductance [H] */
  #define MOTOR_Lsigma_s_H          ???    /* stator leakage inductance [H] */
  #define MOTOR_Lsigma_r_H          ???    /* rotor leakage inductance [H] — if unknown, set equal to Lsigma_s */
  #define MOTOR_PolePairs           ???    /* pole pairs (integer: 1, 2, 3, ...) */
  #define MOTOR_J_kgm2              ???    /* rotor inertia [kg·m²] — only needed for speed ctrl */
  #define MOTOR_Psi_rated_Vs        ???    /* rated rotor flux magnitude [Vs] ≈ V_phase / (2π·f_rated) */
  #define MOTOR_I_max_A             ???    /* max phase current for observer / speed ctrl limit [A] */
  /* Protection — set to hardware limits, not motor nameplate */
  #define MOTOR_Vdc_max_V           800.0f
  #define MOTOR_Iphase_max_A        ???    /* trip threshold [A] — typically 2× rated */
  #define MOTOR_Speed_max_rpm       ???    /* trip threshold [RPM] — typically 1.2× rated */
  /* Control tuning — start with these, adjust after first run */
  #define MOTOR_Current_Kp_scale    0.1f   /* reduce if current overshoots */
  #define MOTOR_Current_Ki_scale    0.2f
  #define MOTOR_Speed_Kp            0.01f
  #define MOTOR_Speed_Ki            0.50f
  #define MOTOR_Resonant_gain_scale 0.3f   /* 6th harmonic resonant controller gain / current PI kp */
  /* KF noise — start with these defaults, tune with tune_kf.py */
  #define MOTOR_KF_Q_i              1.0e-5f
  #define MOTOR_KF_Q_psi            1.0e-7f
  #define MOTOR_KF_R_i              5.0e-2f
#endif
```

### Step 2 — Check hardware settings in [`uz_global_configuration.h`](vitis/software/Baremetal/src/uz/uz_global_configuration.h)

| Define | Default | Meaning |
|--------|---------|---------|
| `UZ_PWM_FREQUENCY` | 25 000 Hz | PWM / ISR rate — do not change without re-tuning PI gains |
| `UZ_D5_INCREMENTAL_ENCODER_RESOLUTION` | 1024 | Encoder lines per revolution (counts/rev before ×4 decoding) |
| `UZ_D5_MOTOR_POLE_PAIR_NUMBER` | 1 | Must match `MOTOR_PolePairs` |
| `INVERTER_DEADTIME_US` | 0.3 µs | Hardware deadtime of Wolfspeed adapter board — do not change |
| `UZ_MIN_PULSE_WIDTH` | 0.01 | Minimum duty cycle clamped by PWM IP |

### Step 3 — Identify unknown machine parameters

Use [`javascope/analysis/identify_motor_params.py`](javascope/analysis/identify_motor_params.py):
```bash
# Step 1 — get the properties.ini channel preset for each test:
python identify_motor_params.py --print-channels all

# Step 2 — run the test logs through the script:
python identify_motor_params.py --Rs <standstill_log.csv> \
                                --Lm <noload_log.csv>     \
                                --Rr <loaded_log.csv>
```
The script reads `motor_config.h` automatically for sigma_Ls / Lr corrections.
See the script's `--help` for per-test setup instructions.

---

## 2. Hardware Wiring

### ADC channel assignment (Wolfspeed adapter board)

| ADC channel | Signal | Firmware variable |
|-------------|--------|-------------------|
| A1 (ADC_A1) | Phase current I_U | `av->I_U` |
| A2 (ADC_A2) | Phase current I_V | `av->I_V` |
| A3 (ADC_A3) | Phase current I_W | `av->I_W` |
| A4 (ADC_A4) | DC-link voltage U_DC | `av->U_DC` |

U_DC raw offset is subtracted during calibration (`measurement_calibration_u_dc_offset = 2.5f` in `isr.c`).

### Encoder

Connected to D5 connector. Set `UZ_D5_INCREMENTAL_ENCODER_RESOLUTION` to the encoder's lines-per-revolution. Speed is computed in RPM and available as `av->mechanicalRotorSpeed_filtered`.

### Inverter enable signal

`halfBridge7DutyCycle = 0.0f` enables the inverter gate driver; `= 1.0f` disables it.

---

## 3. Startup Sequence

> **Safety rule:** Always start in `idle_state`. Verify currents are ≈ 0 before enabling the inverter.

### Step 1 — Boot
1. Power on UltraZohm and DC supply (do **not** enable output yet)
2. Connect JavaScope GUI (see Section 4)
3. Verify `lifecheck` channel is incrementing → R5 is running

### Step 2 — Calibration (automatic, ~0.4 s)
- Happens automatically after pressing **Start** (enter `running_state`)
- The ISR averages 10 000 samples of I_U/I_V/I_W at standstill to compute zero-current offsets
- **Motor must be stationary during calibration**
- `SLOWDAT_DISPLAY[7]` shows the calibration counter; when it reaches 10 000, calibration is done
- After calibration: verify `ia`, `ib`, `ic` read ≈ 0 A with no current applied

### Step 3 — V/f open-loop verification
1. Press **Run** to enter `control_state` (FOC is off by default)
2. Set SF1 (frequency setpoint) to 2–5 Hz — low enough to see the motor barely rotate
3. Verify sinusoidal currents on channels `ia`/`ib`/`ic` — amplitude ∝ frequency
4. Verify `Speed_rpm` is non-zero and consistent with frequency setpoint
5. Gradually increase SF1 up to ~20 Hz — check for smooth acceleration
6. Watch `U_DC` — should stay stable (no oscillation > ±5 V)
7. Set SF1 = 0.0 to stop; verify currents return to ≈ 0

### Step 4 — Set flux current reference
1. Compute the rated d-axis current: `id_ref = Psi_rated / Lm`
   - Pre-computed automatically in firmware; check SLOWDAT channel for the value
2. Set SF2 (Id_Ref) to `id_ref` value (e.g., 2.43 A for Lindner 3 kW)
3. Set SF3 (Iq_Ref) = 0 A (no torque)

### Step 5 — Enable FOC (MB4)
1. Press **MB4** to toggle FOC on
2. Observe `id` tracks `id_cmd` (JSO 12 vs 25)
3. Observe `psi_r_mag` (JSO 28) rises to rated value within ~5× tau_r seconds
4. If currents oscillate or overshoot: reduce `MOTOR_Current_Kp_scale` in `motor_config.h`

### Step 6 — Speed control (MB5, optional)
1. Ensure FOC is stable at rated flux first
2. Set SF4 (Speed_Ref) to a safe low speed (e.g., 300 RPM)
3. Press **MB5** to enable speed controller
4. Increase speed gradually, checking `id` stays near `id_cmd`

---

## 4. JavaScope Quick Start

### Recommended channel assignments for commissioning

| Channel | JSO # | Signal | What to watch |
|---------|-------|--------|---------------|
| CH1 | 8 | `ia` | Phase current — must be sinusoidal |
| CH2 | 9 | `ib` | |
| CH3 | 10 | `ic` | |
| CH4 | 12 | `id` | Measured d-axis current — should track id_cmd |
| CH5 | 14 | `id_est` | Observer-estimated id (differs from id only with KF) |
| CH6 | 25 | `id_cmd` | D-axis reference |
| CH7 | 28 | `psi_r_mag` | Flux magnitude — should reach Psi_rated at steady state |
| CH8 | 20 | `Theta_el` | Flux angle — should ramp smoothly (no jumps) |
| CH9 | 18 | `Speed_rpm` | Mechanical speed |
| CH10 | 11 | `U_DC` | DC-link voltage |

### Key diagnostics during commissioning

| Channel | JSO # | Purpose |
|---------|-------|---------|
| `omega_s_rad_s` | 29 | Stator frequency — use to verify slip estimate |
| `omega_slip` | 42 | Slip = omega_s − omega_el (check ≈ Rr/Lr × iq/id) |
| `ud_pi` / `uq_pi` | 38/39 | PI outputs — `ud_pi` DC offset ≈ Rs×id at steady state |
| `kf_innov_alpha/beta` | 30/31 | KF innovation — should be white noise when tuned |

---

## 5. Control Mode Buttons & Send Fields

### My Buttons

| Button | Function | Default |
|--------|----------|---------|
| MB4 | Toggle FOC on/off (off = V/f mode) | OFF |
| MB5 | Toggle speed controller | OFF |
| MB6 | Toggle KF observer (off = deterministic observer) | OFF |
| MB7 | Toggle deadtime compensation | OFF |
| MB8 | Toggle resonant 6th-harmonic controller | OFF |

### Send Fields

| SF | Signal | Units | Notes |
|----|--------|-------|-------|
| SF1 | `vf_frequency_setpoint_Hz` | Hz | V/f mode frequency setpoint |
| SF2 | `id_ref_A` | A | D-axis current reference (set to Psi_rated/Lm) |
| SF3 | `iq_ref_A` | A | Q-axis current reference (torque) |
| SF4 | `speed_ref_rpm` | RPM | Speed setpoint (only active when MB5 on) |
| SF7 | `kf_q_psi` | — | KF process noise — rotor flux states |
| SF8 | `kf_r_i` | — | KF measurement noise — stator current |
| SF9 | `kf_q_i` | — | KF process noise — stator current states |

SF7/SF8/SF9 accept **absolute values** (not multipliers); must be > 0.

---

## 6. KF Tuning Procedure

The Kalman Filter improves flux angle and current estimation at the cost of Q/R tuning. Start with the defaults in `motor_config.h`; tune only if needed.

### Quick-check: is the KF working?

1. Enable KF: press **MB6**
2. Check `kf_innov_alpha` and `kf_innov_beta` (JSO 30/31):
   - Should be **small amplitude white noise** ≈ current measurement noise level
   - If large oscillations at 6×f_el: increase Q_i (SF9) or enable resonant controller
   - If slow drift: decrease Q_i

### Tuning with `tune_kf.py`

```bash
# Get the channel preset for the KF tuning log:
python tune_kf.py --print-channels

# Log a steady-state run with KF active, then analyse:
python tune_kf.py my_log.csv
```

The script reads Q/R defaults from `motor_config.h` automatically.
It computes the innovation autocorrelation AC(1) and suggests new values.
Enter the suggested values into SF9/SF7/SF8 and repeat until AC(1) < 0.1.

### Starting points for an unknown machine

| Parameter | Starting value | Increase if... | Decrease if... |
|-----------|---------------|----------------|----------------|
| `Q_i` (SF9) | `1e-5` | innovations are correlated (AC(1) > 0.3) | innovations are noisy / K drifts |
| `Q_psi` (SF7) | `1e-7` | psi_r estimate drifts slowly | — |
| `R_i` (SF8) | `5e-2` | current noise → noisy theta estimate | flux angle lags measurements |

Typical converged K[0][0] ≈ 0.03–0.05 for 10 A machines at 25 kHz.

---

## 7. Control Gains Tuning

Use [`javascope/analysis/calc_pi_gains.py`](javascope/analysis/calc_pi_gains.py) to compute starting gains from motor parameters:

```bash
python calc_pi_gains.py
```

The script reads `motor_config.h` automatically and prints `MOTOR_Current_Kp_scale`, `MOTOR_Current_Ki_scale`, `MOTOR_Speed_Kp`, `MOTOR_Speed_Ki` values to paste into `motor_config.h`.

**Current PI:** Based on symmetric optimum. Reduce `MOTOR_Current_Kp_scale` if overcurrent trips occur on FOC enable (typical: start at 0.05–0.1).

**Speed PI:** Based on asymmetric optimum. Requires accurate J. Start with Kp=0.01 and increase slowly while watching for speed oscillations.

---

## 8. Known Issues & Limitations

### psi_r overestimation at high speed
- Observed: +27% overestimation at 2604 RPM with Lindner 3 kW motor
- Cause: 6th-harmonic id ripple inflates the RMS magnitude `sqrt(psi_α² + psi_β²)`; possibly also incorrect Rr at temperature
- Effect: ud_pi DC offset grows with speed (decoupling feedforward over-compensates)
- Mitigation: enable resonant controller (MB8) to suppress 6th-harmonic ripple; re-identify Rr at operating temperature

### 6th harmonic (deadtime-induced) ripple
- Amplitude grows with speed: 0.107 A at 1001 RPM → 0.238 A at 2604 RPM
- Resonant controller (MB8) reduces this significantly at steady speed
- Resonant controller requires ~5–10 electrical cycles to settle after a speed change

### Deterministic observer vs KF
- Deterministic observer: simple, fast to tune, but accumulates error at high speed due to parameter uncertainty
- KF: better noise rejection, but requires Q/R tuning; innovations not fully white due to unmodeled 5th/7th harmonics (expected behavior)
- Recommendation: commission with deterministic observer first, switch to KF only after motor parameters are confirmed

### Deadtime compensation (MB7)
- Currently disabled by default (found to cause worse behavior for this hardware)
- INVERTER_DEADTIME_US = 0.3 µs is the adapter board hardware deadtime

---

## 9. Python Analysis Scripts

All scripts in [`javascope/analysis/`](javascope/analysis/) read motor parameters directly from
`motor_config.h` (auto-detected from the relative path; override with `--motor-config <path>`).

| Script | Purpose | Usage |
|--------|---------|-------|
| `analyze_im.py` | FOC + observer quality analysis | `python analyze_im.py <log.csv>` |
| `identify_motor_params.py` | Extract Rs, Lm, Rr from test logs | `python identify_motor_params.py --help` |
| `calc_pi_gains.py` | Compute PI gains from motor_config.h | `python calc_pi_gains.py` |
| `tune_kf.py` | Iterative KF Q/R tuning | `python tune_kf.py <log.csv>` |
| `jso_channels.py` | List JSO enum and generate ini presets | `python jso_channels.py` |
| `parse_motor_config.py` | Parse motor_config.h (library + CLI) | `python parse_motor_config.py` |

**Channel presets for properties.ini** — each script can print the correct channel preselection:
```bash
python analyze_im.py --print-channels          # commissioning / FOC analysis
python tune_kf.py --print-channels             # KF tuning log
python identify_motor_params.py --print-channels all   # all three ID tests
```
