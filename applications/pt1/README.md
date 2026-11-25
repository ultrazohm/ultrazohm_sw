# PT1 hardware recordings and comparison

With this branch's `UZ_PT1_REPLAY=1` firmware running at 10 kHz, close other
device clients and enter the shared repository environment with `./uz shell local`
(build this checkout) or `./uz shell stable` (install the published release).
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
