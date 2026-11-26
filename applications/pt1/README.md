# PT1 hardware recordings and comparison

With this branch's `UZ_PT1_REPLAY=1` firmware running at 10 kHz, close other
device clients and enter the repository development environment with `./uz_developer shell`
(after `./uz_developer setup`), or use `./uz venv` for published packages.
From the repository root, record the actors independently:

```sh
python applications/pt1/record_pt1_dqn.py --output artifacts/pt1-dqn
python applications/pt1/record_pt1_ddpg.py --output artifacts/pt1-ddpg
```

Each output directory must be new. The scripts select the PT1 channels and record
only the requested actor. Logs are in its `recording/` subdirectory, with native
Parquet/CSV, command audit and session metadata. A timeout fails the run and
retains accepted data. Acquisition cleanup sends Stop and finalizes recordings.
Use `--device IP:PORT` to override the board address.

Compare an existing recording separately after running the Ceedling PT1 export tests:

```sh
python applications/pt1/compare_pt1_logs.py dqn artifacts/pt1-dqn/recording/data.parquet
python applications/pt1/compare_pt1_logs.py ddpg artifacts/pt1-ddpg/recording/data.parquet
```

Use `--expected PATH` for a different Ceedling CSV. Comparison uses the controller
sample index, checks all 3,000 replay samples and returns a nonzero exit status
on missing samples or numerical mismatches.

To prepare a Data Viewer script that overlays one hardware recording and its
Ceedling reference:

```sh
python applications/pt1/load_pt1_logs.py dqn artifacts/pt1-dqn/recording/data.parquet --output artifacts/pt1-dqn-view
```

Open `artifacts/pt1-dqn-view/pt1_dqn_comparison.uzscript` in Data Viewer.
It clears the viewer session and loads prepared copies of both logs, with their
sample indices converted to seconds at 10 kHz. It overlays output, reference,
action and reward, plus DQN action index and Q values. Use `ddpg` for DDPG.
The generator runs in the CLI environment and leaves the source logs intact.

## Runtime parameter upload prototype

Build and load this branch's updated PT1 firmware before using this feature.
The network architecture, activations, observations, and action mapping stay
compiled into the firmware. The uploader changes weights and biases in RAM.
Firmware builds currently initialize all PT1 weights and biases to zero for
upload testing. Ceedling builds load the trained CSV values for reference tests.
A firmware restart returns the PT1 networks to zero parameters.

The trained exports available in this checkout are:

- DQN: `vitis/software/Baremetal/src/uz/uz_exported_actor/examples/pt1_dqn/`
- DDPG: `vitis/software/Baremetal/src/uz/uz_exported_actor/examples/pt1_ddpg/`

From the repository root, enter the checkout's CLI environment and upload
the bundled DQN export:

```sh
./uz venv dev
python applications/pt1/update_parameters_prototype.py dqn
```

Use `ddpg` for the bundled DDPG export. To upload a custom export, pass its directory:

```sh
python applications/pt1/update_parameters_prototype.py dqn path/to/export
python applications/pt1/update_parameters_prototype.py ddpg path/to/export
```

The directory must contain each layer's `layerN_weights.csv` and
`layerN_bias.csv`, numbered from 1. CSV values use the exporter storage order.
Use `--device IP:PORT` for another board address. Close other acquisition clients.
The script opens its own acquisition service, uploads once, and closes it.
It prints elapsed time from sending Stop through firmware confirmation of the
completed update. Acquisition startup, CSV loading, and feedback channel setup
are outside that measurement.

For a timed burst upload, close the CLI, Data Viewer, and any other clients
connected to the board, then run:

```sh
python applications/pt1/update_parameters_prototype_fast.py ddpg
```

The fast uploader gets the firmware mapping from the CLI and then opens its
own JavaScope TCP connection. It sends 32 parameters per burst by default and
waits for the R5 to confirm each burst before sending the next. Use
`--burst-size 16` or `--burst-size 48` to compare throughput. The reported time
runs from sending Stop through firmware confirmation, including feedback
channel assignment and excluding mapping generation, CSV loading, and TCP
connection setup. The controller remains stopped after the update.

For an existing acquisition service, import the helper:

```python
from ultrazohm_cli import Client
from update_parameters_prototype import (
    network_info, read_parameters_from_csv, uz_nn_update_weights,
)

uz = Client()
parameters = read_parameters_from_csv("path/to/export")
info = network_info("dqn")
try:
    uz_nn_update_weights(uz, parameters, info)
finally:
    uz.close()
```

Place the calling script alongside the helper, or add this application directory
to its Python module search path. `info` contains the target and each layer's
input and neuron counts. Custom parameters must have exactly those dimensions.
Fast and slow recording must be idle while the helper assigns feedback channels.

The helper sends Stop, selects the target, and presses **Enable-Parameter-Update**
(MyButton7). The firmware stops inference and accepts ordered writes.
Each parameter uses these send fields, in order:

| Field | Caption | Value |
|---|---|---|
| 2 | NN-Layer | Zero-based layer index |
| 3 | NN-Type | 0 for weights, 1 for bias |
| 4 | NN-Index | Zero-based index within the flattened array |
| 5 | NN-Value | Float32 value, written immediately |
| 6 | NN-Target | 1 DQN or 2 DDPG, selected before enabling updates |

Send all weights and then all biases for each layer, advancing from layer 0.
The helper paces commands at 2 ms intervals and checks the accepted count every
32 parameters. The default pacing takes about 10 seconds for DQN, plus host
and feedback overhead. It presses **Finish-Parameter-Update** (MyButton8) only after all
entries arrived, then waits for completion. The controller remains stopped.
Select PT1-DQN, PT1-DDPG, or Manual-Mode explicitly to run with the new parameters.

Feedback channels are `nn_update_active`, `nn_update_received`,
`nn_update_error`, `nn_update_target`, and `nn_update_expected`.
The helper selects them into slots 15–19. The indicator beside MyButton7 shows
update mode. Error codes are 0 OK, 1 invalid selector, 2 missing/out-of-order
fields or parameters, 3 non-finite value, 4 incomplete upload, and 5 aborted.
Errors remain visible until a new valid upload begins.

Writes modify the active arrays directly. Stop, disconnect, or interruption can
leave a partial parameter set. The affected network remains blocked until a full
upload succeeds or the firmware restarts. Beginning another upload restarts its
count at zero. This prototype uses ordered counts and paced sends, with no
checksum or rollback. It does not verify every received value by reading it back.

## Minimal host DQN training

`train_pt1_dqn.py` trains in Python while the actor **and simulated PT1 plant**
execute at 10 kHz on R5. It follows `workshop_vv_dqn:workshop/train_pt1.py`:
observations `[y, reference]`, actions `[-1, 0, 1]`, 2→32→32→3 ReLU network,
reward `-(reference - next_y)^2`, Adam at 1e-4, gamma 0.99, batch size 32,
Huber loss and gradient clipping. The small PyTorch loop replaces SB3's host
`env.step()` loop; there is no host action command on each control tick.

Build and deploy the updated `UZ_PT1_REPLAY=1` firmware first. Install the DQN
runtime dependencies into the repository's persistent `.venv` (Python 3.12):

```sh
uv pip install --python .venv/bin/python -r applications/pt1/requirements.txt
source .venv/bin/activate
```

If `.venv` does not exist, create it with `uv venv --python 3.12 .venv` first,
or use `./uz_developer setup` to build the local CLI and DataViewer. Installing
these requirements preserves an already installed local CLI build. Use this
persistent environment for training; `./uz venv` opens a separate uv cache
environment for published tools.

The requirements are `torch`, `numpy`, `polars`, and `ultrazohm_cli`. CPU-only
PyTorch is sufficient; SB3, Gymnasium and JAX are not required. `pytest` is an
optional additional dependency for the tests. With the environment active, run:

```sh
python applications/pt1/train_pt1_dqn.py --output artifacts/pt1-training --rounds 20
```

Each round uploads the current network with the existing helper, sets
`DQN-Epsilon` (send field 7), records six 500-step episodes, stops, and performs
3,000 gradient updates on the host. Collection uses the existing six fixed
references and zero initial plant state. Unlike the workshop's randomly sampled
references, this deliberately reuses the firmware replay schedule. The replay
buffer retains 100,000 transitions. The target network is copied every ten
**gradient updates**. Epsilon decreases from 1 to 0.05 over the first 10% of
rounds; R5 performs epsilon-greedy exploration with a deterministic xorshift32
stream that persists across rounds (seed 1 at firmware restart). `--seed` seeds
host initialization and replay sampling only. Epsilon defaults to zero at boot
and can only be changed while the actor is stopped.

One row contains the pre-action `y` and reference, selected action index, reward,
`next_y`, episode/step, `done`, epsilon and ISR number. `done` marks the 500-step
time limit, as in the workshop; the learner bootstraps from the explicit final
observation and never from the following reset. This contract is specific to
the PT1 simulation; a physical plant needs next-state/reward sampling on the
following ISR and a separate termination definition.

The full `uz_SystemTime_GetInterruptCounter()` value is logged as
`JSO_pt1_isr_0` … `JSO_pt1_isr_3`, least-significant 16-bit limb first:
`isr = limb0 + (limb1 << 16) + (limb2 << 32) + (limb3 << 48)`.
Each limb is exact in JavaScope's float32 protocol. The trainer rejects incomplete,
duplicate, reordered or skipped ISR data before adding anything to replay.
All 3,000 rows must arrive without decimation. Slots 1–15 carry training data;
the existing uploader temporarily assigns its feedback to slots 15–19.

Round directories contain native acquisition recordings, directly readable by
DataViewer. `network.pt` stores the latest network parameters; `export/` contains
CSV files accepted by `update_parameters_prototype.py`. The final trained network
is uploaded, epsilon is set to zero, and the controller remains stopped. Press
PT1-DQN to evaluate. Uploads take roughly ten seconds each; this prototype is a
collect/train/upload loop with pauses, not concurrent learning or a resumable
training service. No new firmware transport or DataViewer API is needed.

### Evaluate the saved agent on the host

```sh
python applications/pt1/evaluate_pt1_dqn.py artifacts/pt1-training/network.pt
```

This opens no hardware connection. It loads the saved weights into the same
network and runs greedy actions (epsilon zero) in a float32 Python PT1 simulation
with the firmware's six references, 500 steps per episode and reset to zero.
It prints episode return, tracking RMSE and final output, and creates
`host_evaluation.csv` beside the checkpoint. Use `--output PATH` for another new
CSV filename. Existing output files are not overwritten. Only NumPy and PyTorch
are required; neither SB3 nor the CLI package is needed for host evaluation.
Host and R5 floating-point inference may differ slightly, especially at action
ties; this evaluates the simulated task, not hardware timing or transport.

## Build, flash, train and watch live

`train_pt1_live.py` runs the DQN learner with a single shared CLI acquisition
service and an attached DataViewer. It first invokes CLI `flash`, which builds
the firmware and programs/runs it through JTAG. Vitis/XSCT, JTAG, Ethernet and
this checkout's training-enabled firmware configuration are required. Close
other applications connected to the board and free ports 19740 and 19741.

Build/install this checkout's CLI and DataViewer, including the new `gui --live`
startup option, then run from the repository root:

```sh
./uz_developer build linux_wheels
./uz_developer shell
python -m pip install -r applications/pt1/requirements.txt
python applications/pt1/train_pt1_live.py
```

If the environment has no pip, use `uv pip install --python "$(command -v python)" -r applications/pt1/requirements.txt`.
The developer shell uses its persistent cached environment, not `.venv`.
The launcher defaults to 20 rounds and `192.168.1.233:1000`. Options include
`--device IP:PORT`, `--xsct /path/to/Vitis/bin/xsct`, `--rounds N`,
`--gradient-steps N`, `--endpoint HOST:PORT`, `--viewer-endpoint HOST:PORT`, and
`--output NEW_DIRECTORY`. By default it creates a timestamped directory under
`artifacts/`.

Six live plots show y/reference/next_y, action value/index, reward, epsilon,
episode/step counters, and upload progress. Here y is the actual simulated plant
output; next_y is its value after the action. The 15-second live view is set up
once, then scrolls through all rounds and the final evaluation. The script does
not reset your axes or plot assignments between rounds. Channels stay fixed,
including all five upload feedback signals, so uploads do not clear the live
history. To fit the 19 assignable slots, the redundant replay sample index and
done flag are reconstructed from episode/step counters for learning; they are
not separate columns in the native log. The launcher sends PT1-DQN automatically.

The live trainer uses 0.2 ms pacing between parameter commands, retaining firmware
count checks every 32 parameters. Single hardware uploads of 1,251 DQN parameters
completed in 4.351 seconds at 0.5 ms and 2.335 seconds at 0.1 ms; 0.2 ms has not
been measured separately. These are single-run measurements, not throughput
guarantees. The standalone paced uploader still defaults to 2 ms; use
`--command-interval 0.0002` to select the same pacing as the live trainer.

To measure upload costs through the existing service after training completes:

```sh
python applications/pt1/profile_pt1_upload.py artifacts/YOUR_RUN/export
```

This uploads the supplied DQN weights three times each at 0.1 and 0.2 ms, alternating
settings, without reflashing or changing channels. The service must remain
connected with all five upload feedback signals assigned and recording idle.
Use `--intervals-ms`, `--repeats`, and `--output` to customize the measurement.
It saves raw JSONL and CSV timings under `artifacts/pt1-upload-timing-*`.
Timings separate startup commands/delays, begin confirmation, parameter API
calls, actual pacing sleeps, receipt checks, and finish confirmation. These are
host wall-clock measurements; API calls include service/transport overhead, and
feedback checks include polling sleeps. Acquisition startup, CSV loading,
parameter validation, and channel assignment are outside the measured interval.

The output contains `network.pt`, CSV `export/`, per-round `progress.jsonl`,
`settings.json`, and `dataviewer.log`. **One native `data.parquet` records the
entire run**, including uploads, collection, host-learning pauses, and evaluation.
It lives in the CLI session directory; `recording.json` in the run directory
points to its durable `data.recording.json` handle. Logging starts before the
first upload and is finalized after evaluation (or on error/interruption).
`progress.jsonl` identifies each round's half-open `[start, stop)` sample range
in that same recording. Filter `JSO_pt1_actor == 1` within each range to select
its 3,000 training transitions. Reward and loss summaries print in the terminal.

After training the final weights are uploaded and exploration is disabled. The
launcher automatically runs six 500-step evaluation episodes with no gradient
updates or replay buffer additions. `evaluation.json` contains the evaluation
range in the same recording, per-episode return, tracking RMSE (reference versus
next_y), and final output. No separate evaluation Parquet file is created.
Evaluation failure is reported as a failed run; the continuous recording remains
available with the samples accepted before the failure.

After evaluation the controller stays stopped, while DataViewer and acquisition stay open until you
close the viewer or press Ctrl-C in the terminal. `--exit-after-training` closes
both immediately. Cleanup stops the device and finalizes recordings on failure
or interruption too. This workflow trains against the R5 simulated PT1 plant.

## Firmware modes

Select modes in `uz_global_configuration.h` or with compiler definitions:

- `UZ_PT1_REPLAY=0`, `UZ_PT1_TRAINING=0`: normal ADC/encoder and control ISR.
- `UZ_PT1_REPLAY=1`, `UZ_PT1_TRAINING=0`: deterministic PT1 DQN/DDPG replay and parameter uploads.
- `UZ_PT1_REPLAY=1`, `UZ_PT1_TRAINING=1`: PT1 replay with host-training exploration and transition telemetry (current default).

Training requires replay; invalid combinations fail preprocessing. JavaScope IDs
remain stable across modes; disabled telemetry slots retain their zero values.
