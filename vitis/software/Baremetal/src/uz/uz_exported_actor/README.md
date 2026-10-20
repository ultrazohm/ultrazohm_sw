# Actors exported by `_pmsm`

This adapter consumes **generated C configuration and CSV parameters**, not JSON
at runtime. It targets the software `uz_nn` implementation on `feature/uz_motors`.
No ISR, FPGA IP core, allocation from the heap, Python, or JSON parser is required
on the target. The checked-in examples are trained/exported fixtures, not manually
transcribed weights.

## Export and compile

In the `rliable_drives` checkout, export a selected trained actor with
`pmsm-agents export ... --format uz-c --outdir NEW_DIRECTORY`. This produces
`actor_config.c`, `actor_config.h`, the layer CSVs, `manifest.json`, and
`firmware_manifest.json`, alongside the usual selection/configuration metadata.
The default `pmsm-agents` format remains CSV + manifest.

For an existing CSV export, choose a distinct C prefix for each actor:

```sh
JAX_PLATFORMS=cpu python -m prototyping_pmsm.inference.uz_c \
  --input exports/selected_actor --outdir exports/firmware_actor --name my_actor
```

After installing the updated Python package, `pmsm-export-c` provides the same
command. Copy the **whole** resulting directory beneath the application's source
tree. Compile `my_actor_config.c` together with `uz_exported_actor.c`, `uz_nn`,
`uz_nn_layer`, `uz_nn_activation_functions`, and `uz_matrix`. The parameter CSVs
are C initializer includes, so the weights become part of the ELF. Keep the CSVs
beside the generated C file. The build must find `uz_exported_actor.h` on its
include path.

Enable sufficient `UZ_NN_MAX_INSTANCES` and `UZ_NN_LAYER_MAX_INSTANCES` in the
non-test `uz_global_configuration.h`. They default to zero on this branch.
`firmware_manifest.json` records the required instance counts and adapter ABI.
Ceedling's test configuration already enables these modules.

```c
#include "my_actor_config.h"
static uz_exported_actor_t actor;
/* Once, with the real scheduler's frequency: */
uz_exported_actor_init(&actor, &my_actor_config, 10000.0f);
/* Each tick, supplying physical measurements and reference: */
struct uz_exported_actor_signals signals = {
    .output = measured_pt1_output, .reference = {reference, 0.0f}
};
uz_exported_actor_sample(&actor, signals);
float u = actor.applied[0];
```

For PMSM use `current[2]`, `reference[2]`, and **mechanical** `speed_rpm`.
`requested`, `limited`, and `applied` are physical voltages in d/q order.
The adapter owns its previous applied-voltage observation and delay queue; the
caller does not populate that observation. Do not add the exported delay a second
time in a hardware scheduler. This software adapter's configured queue reproduces
training semantics; integrating it into an ISR requires mapping that assumption
to the actual sample/actuation timing.

Initialize each generated configuration once. Its `uz_nn` arrays are static and
shared: calls must be serialized and it is not a reentrant configuration for
multiple concurrent controllers. `uz_exported_actor_reset(actor, NULL)` resets
conditioning, feedback, and queue to declared defaults; pass an explicit
`uz_exported_actor_state` for nonzero initial conditions. Plant reset is separate.

## What the manifest generates

- Layer dimensions, weights/biases, ReLU/tanh/linear activations.
- Continuous bounded actions or DQN first-index argmax and the discrete table.
- Validated observation expressions and physical signal units/order.
- Integral initial values, update expressions, and saturation hold.
- Physical action scaling, axis-priority/radial limiting, and measured/reference
  q-current selection (including zero-sign behavior).
- Sample frequency, zero/one/two-step actuator delay, and contract SHA-256.

The Python generator validates the CSV checksums and contract, rejects unsupported
signal semantics, action mappings, state, or layers, and atomically publishes a
new directory. `uz_nn` on this branch accepts 2–9 layers including the output.
The firmware checks the adapter ABI and supplied control frequency. Do not use
`-ffast-math`: finite checks and expression arithmetic are part of the contract.
The generator supports the shipped PT1 and PMSM signal interfaces, not arbitrary
registered Python environments or native-only checkpoints. It does not silently
translate this contract into the older `uz_rlcc` observation semantics.

The controller manifest does **not** configure a physical motor. The example
reproduction script separately generates the software-model configuration from
the resolved training configuration. In the PMSM fixture mechanical dynamics
are disabled; the software model's required positive inertia is set to 1 and is
unused. Never treat these simulation parameters as a hardware commissioning file.

## Run the examples

Use Ceedling **1.1.9**, as pinned in the dev-container Dockerfile.
From `vitis/software/Baremetal`:

```sh
ceedling test:pt1_dqn_export test:pt1_ddpg_export test:pmsm_td3_export test:uz_exported_actor
```

- **PT1 DQN and DDPG:** `_pmsm` workshop configurations, 50,000 CPU training steps,
  2→32→32→3/1 networks, gain 1, time constant 2 ms, 10 kHz. Six references and
  500 ticks per reference; C observations, network outputs, actions, and the
  closed-loop plant trace are checked against Python.
- **PMSM TD3:** 250,000 CPU training steps, Beckhoff linear preset, 9→32→32→2,
  Heun with four substeps, one queued control step, reference-current limiter.
  A 200-tick profile reverses reference current and speed. Tests separately check
  controller replay against Python, software-model replay against Python, and
  a complete closed loop with repeatable reset, finite/bounded currents, delay
  ordering, voltage limiting, observation feedback, and integrator clamping.
- **Adapter edge cases:** DQN ties, wrong frequency, measured/reference priority,
  zero-sign behavior, radial limiting, two-step queue, and reset.

The PMSM controller replay uses identical input/state at each tick, and the
model replay uses identical applied voltages. These are strict numerical parity
checks. A saturated feedback loop can amplify C/JAX rounding differences until
its later samples differ substantially; the full closed-loop test therefore
checks behavior and repeatability, not long-horizon sample equality. The fixture
is an integration example and not a claim of optimal tracking or hardware tuning.

## PT1 evaluation CSV logs

Running the PT1 Ceedling tests writes these files, relative to `vitis/software/Baremetal`:

- `build/artifacts/test-data/uz_exported_actor/pt1_dqn_eval.csv`
- `build/artifacts/test-data/uz_exported_actor/pt1_ddpg_eval.csv`

Each file contains the actual C evaluation trajectory: six episodes of 500 steps.
Files are overwritten on each test run; a failed parity check leaves a partial
trace. Set `UZ_TEST_DATA_DIR` to change the output root (prefer an absolute path).
For example, `UZ_TEST_DATA_DIR=/tmp/actor-logs ceedling _1.1.9_ test:pt1_dqn_export`
writes `/tmp/actor-logs/uz_exported_actor/pt1_dqn_eval.csv`.

The semicolon-separated columns match the `workshop_vv_dqn` evaluation logs.
`time` is the global zero-based step counter, `episode` starts at one, and
`episode_k` starts at zero. `y` and `error` describe the pre-step observation;
`reward` is the negative squared post-step tracking error. DQN additionally logs
all three Q values and the greedy action. Evaluation has zero exploration,
`terminated=0`, and `truncated=done=1` only at each episode's final step.

## Reproduce the trained fixtures

From `rliable_drives`:

```sh
JAX_PLATFORMS=cpu python -m prototyping_pmsm.examples.ultrazohm \
  --uz-root ultrazohm_sw --workdir /tmp/new-ultrazohm-training
```

This trains all three TOMLs, exports through `pmsm-agents`' Python selection path,
loads the CSV manifest, generates C, and copies complete actor directories and
Python-generated trace headers into this checkout. Use `--only pt1_dqn`,
`--only pt1_ddpg`, or `--only pmsm_td3` to regenerate a subset. It refuses existing
work directories or generated destinations. Before regeneration, move the
corresponding `examples/<name>/` and
`test/uz/uz_exported_actor/fixtures/<name>_trace.h` aside. Handwritten adapter,
example wrappers, and tests are not overwritten. Saved `configuration.json` and
`selection.json` identify the training settings and chosen checkpoint; neural
training is not guaranteed bitwise reproducible across JAX/compiler versions.

## Diagnose preprocessing failures

A missing `build/test/preprocess/.../directives_only/raw/test_*.c` is a missing
**generated** file, not a source file to copy into the repository. The exception
alone does not identify why preprocessing failed. The examples are validated
with Ceedling 1.1.9; upgrading Ceedling is not required.

Run this in the dev-container terminal from `vitis/software/Baremetal`, without
another Ceedling build or cleanup running concurrently. Choose a fresh diagnostic
build directory if the one below already exists:

```sh
ceedling _1.1.9_ --mixin '=project: {build_root: build_actor_diagnostic, compile_threads: 1, test_threads: 1}' \
  --verbosity=debug test:uz_exported_actor > ceedling-actor-debug.log 2>&1
```

This leaves the normal `build/` directory intact. If it fails, collect
`ceedling version`, `gcc --version`, and the log section containing
`default_test_file_directives_only_preprocessor`, its full command, stdout,
stderr, and exit status. If this succeeds but the editor's test runner fails,
compare its project directory, Ceedling executable, and build settings with the
terminal invocation before changing controller code.
