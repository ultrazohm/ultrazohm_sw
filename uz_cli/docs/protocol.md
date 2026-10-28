# Current JavaScope protocol and API v1

## Evidence and scope

Baseline: repository commit `6b04d018fc11898247ef8c4ce3dc6fde7adaecca`.
The adapter targets this firmware, without changing Baremetal or FreeRTOS.

Authoritative sources, relative to the repository root:

- `vitis/software/shared/APU_RPU_shared.h`: shared-memory sample and command structs; 20 channels.
- `vitis/software/Baremetal/src/include/javascope.h`: observable, slow-data and button enums; commented GUI labels.
- `vitis/software/Baremetal/src/sw/javascope.c`: actual pointer assignments, slow-data rotation, shared memory and IPI.
- `vitis/software/Baremetal/src/sw/ipc_ARM.c`: command dispatch and status bits.
- `vitis/software/Baremetal/src/hw_init/uz_platform_state_machine.c`: enable/stop transitions, physical inputs and LEDs.
- `vitis/software/FreeRTOS/main.h`, `defines.h`, `sw/ethernet.c`, `sw/isr.c`: framing, TCP ownership, queues and command delivery.
- `javascope/src/UZ_GUI/Transmitter.java`, `SendController.java`, `Start.java`: Java encoding, receive geometry, idle replies and command scheduling.
- `JavascopeHeaderParser.java`, `ReceiveController.java`, `ScopeRingBuffer.java`: local names, slow-data decoding, derived time, logging and GUI history.

Other JavaScope components include generated Swing views/forms and image assets,
ParameterID extensions for custom firmware, build/NetBeans files, the Dash offline
viewer and historical HTML/Python experiments, CSV conversion, MATLAB plotting,
and lifecheck analysis. They do not define an additional device wire protocol.
ParameterID names used by the GUI are absent from the current firmware enum;
they are not advertised as supported device operations here.

Historical branch references were inspected through available local Git refs:

- `origin/feature/javascope_python`, `299760539fdfe977bd117b0b9ded3e0cebb2ace8`:
  `uz_scope`, `uz_scope2`, and `uz_scopec`. The Python protocol correctly separates
  column-major frames and command encoding. Its client includes ACK pacing and
  reconnect logic, but its comment that TCP commands must not coalesce reflects
  the old test server, not a TCP guarantee. This implementation handles stream
  fragmentation and never automatically replays control commands.
- `origin/feature/javascope_more_channels`, `52f3b97147d9b0323046315123211c4cf67e3ab7`:
  experimental 1000-channel/80-sample geometry and different firmware structs.
  That layout is incompatible with current firmware. It is not auto-detected or
  silently enabled by changing a channel count.

## Transport

Device: TCP port **1000**, little-endian; no handshake, authentication, protocol
version, length prefix, magic, checksum, sequence number, or device schema.
The latest accepted client replaces the previous client. Never run JavaScope
and the acquisition service against the same device simultaneously.
A new connection purges queued samples and control commands but does not reset
selected signal pointers or send-field values in the R5.

Host to device: exactly **8 bytes per command**, repeated in a TCP byte stream.

| Offset | Type | Meaning |
|---|---|---|
| 0 | uint32 LE | Command ID |
| 4 | IEEE-754 float32 LE | Command value, including observable selection IDs |

Examples: stop is `03 00 00 00 00 00 00 00`; select lifecheck into CH1 is
`c9 00 00 00 00 00 40 40`. The eight-byte all-zero command is a no-op.
Commands can span TCP reads or multiple commands can share one read.

FreeRTOS accumulates trailing bytes and queues all complete commands in a
256-entry queue. A full queue drops commands with a UART diagnostic only.
The A53 IPI ISR consumes at most one command per invocation and sends an
explicit no-op if empty. R5 reads the response and calls `ipc_Control_func`.
There is no per-command acknowledgment, rejection response or variable readback.
TCP success means bytes were accepted by the host socket, not applied by R5.
Do not blindly retry enable, button or set operations after a timeout.

Device to host: **1324 bytes** with the checked-in 15 samples per frame:
`4 + (20 + 2) * 15 * 4`. All arrays are column-major, not interleaved rows.

| Byte offset | Type/count | Meaning |
|---|---|---|
| 0 | uint32 | Status of the last sample in the frame |
| 4 | float32[15] | Slow-data content |
| 64 | float32[20][15] | CH1 through CH20 |
| 1264 | float32[15] | Slow-data IDs, numerically encoded integers |

The channel mapping may specify a different samples-per-packet value when that matches
`JS_SAMPLES_PER_PACKET` of the deployed firmware. It must still have 20 channels.
There is no reliable automatic geometry negotiation. Invalid slow IDs cause
acquisition to fail rather than attempt speculative resynchronization.

The firmware queues up to 1,000,000 samples. On overflow it purges the backlog
and discards any pending transmit buffer; if a partial frame was already sent,
this can break framing. The host can reject implausible slow IDs but cannot
prove alignment or detect every gap. A future firmware header is needed for
strong integrity guarantees. No host-only layer can repair this limitation.

## Commands and meaning

| ID | Name | Current effect |
|---|---|---|
| 0 | GUI_BTN_ZEROVALUE | No-op; also historically called zero ACK |
| 1 | Enable_System | Set one-shot system-enable request |
| 2 | Enable_Control | Set one-shot control-enable request |
| 3 | Stop | Set one-shot stop request |
| 4..23 | Set_Send_Field_1..20 | Write float to `data->av.snd_fld[1..20]` |
| 24 | My_Button_1 | Request error state |
| 25 | My_Button_2 | User LED on |
| 26 | My_Button_3 | User LED off |
| 27..31 | My_Button_4..8 | Empty cases in current firmware |
| 32 | Error_Reset | Empty case in current firmware |
| 201..220 | Channel selection | Set CH1..20 pointer using float observable index |
| 65535 | Startup sentinel | Ignored |
| Other | Unknown | Ignored by current default case |

**Error_Reset is 32, not 33.** Its enum index follows eight buttons after the
20 send fields. Neither ID performs a reset in the current firmware.

Enable system transitions idle → running; enable control is accepted only when
already in running, after its entry action. Running state enables power
electronics but the running LED indicates **control** state. Stop takes priority
over enables and returns to idle, including from error. Physical stop/error
conditions also participate. These are requests, not synchronous transitions.
A caller must not infer enable-system completion from a blinking ready LED.

`set_variable(name, value)` resolves only registered writable send fields.
Arbitrary C variable access, memory writes, observable writes and variable
readback are unsupported. Actual send-field meaning depends on application
firmware; the supplied channel mapping deliberately uses `send_field_1` etc., not invented
speed/torque aliases. Aliases may be added explicitly to a copied channel mapping.

`set_observable(name, channel)` selects a read-only observable into a **1-based**
streaming channel. It does not set the measured value. Names accept the exact
`JSO_...` identifier or the suffix. IDs come from the deployed header/channel mapping.
Firmware truncates fractional selection values; API v1 avoids them entirely.

## Signals and status

Run `ultrazohm channel-mapping` in the checkout for the current numeric enum tables. Enum membership
alone does not imply that a pointer has been assigned. All fast and slow pointers
start at a shared zero value; all selected channels initially point to zero.

Assigned fast IDs: 1..16 and 20. In particular, `JSO_theta_mech` (4) is assigned,
while distinct `JSO_Theta_mech` (21) is not. IDs 17..19 and 21..28 return zero in
the checked-in implementation. Assigned slow IDs: 1, 2, 3, 5, 8, 9, 10, 11, 12.
Other slow slots, including Error_Code (7) and torque (13), return zero.
Slow IDs rotate once per sample from zero through 16. Sparse measurements are
not simultaneous values; the logger preserves one ID/value pair per sample.

Status bits 0..3: Ready, Running, Error, User LEDs. Bits 4..11 carry custom
button feedback; bit 12 is the external logging trigger. The default firmware
explicitly clears bits 4..12 in `ipc_Control_func()`. To enable a hook, replace
its `false` assignment with the application condition and assign the return
value of `uz_javascope_set_status_bit()` back to `js_status_BareToRTOS`. Do not
leave a later default assignment that clears the same bit.
ParameterID GUI extensions inspect bits 13..19 that current firmware does not set.
Bits 31:30 encode the explicit platform state: `00` idle, `01` running (system
enabled), `10` control (control enabled), `11` error. There is no validity flag.
Baremetal samples the state when copying status into the outgoing JavaScope data;
LED bits retain their existing behavior, including Ready blinking. JavaScope reads
all 32 bits unsigned into a `long`, masks individual indicator bits, and displays
all 32 bits in its binary status label. The new field does not change its indicators.
CLI/Python status exposes `state.platform_state` as `idle`, `running`, `control`,
or `error`, alongside the raw `state.status`. The active channel mapping supplies
these labels through `platform_state.values`, indexed by `(status & mask) >> shift`
using `platform_state.mask` and `platform_state.shift`. The default mask is
3221225472 (`0xC0000000`), the shift is 30, and codes 0..3 name the four states. It is null before the first frame
and after disconnection; while connected it describes the latest received frame,
not a command acknowledgment or proof of fresh data.
Status is sampled only once per frame and must not be treated as per-sample
transition timing.

`lifecheck` is ISR interrupt counter modulo 1000, not a transport sequence.
`time` is a derived host sample index times a **configured** sample period.
It is not a hardware timestamp and compresses unknown device-side gaps.
Packet arrival rate is not a trustworthy measurement clock.

## Zero ACK policy

JavaScope normally writes one queued command or all-zero command after a frame.
`sendZeroAckCommand=0` suppresses idle zero replies; it does not suppress actual
commands. The current FreeRTOS worker services receive and transmit independently
and **does not require** application zero ACKs. These are unrelated to TCP ACKs.

API `send_ack(true)` enables one background no-op per complete received frame;
`false` disables them. User commands are sent immediately through a serialized
writer regardless of this setting. Enabling from off also sends one immediate
zero to resume a legacy peer that is waiting. The setting belongs to the persistent
service, survives CLI exit and lasts until shutdown. Default: off for this firmware.

## Versioned local API

CLI and native Python bindings call the same Rust control client. Current local
control is one bounded JSON request/response per loopback TCP connection, newline
terminated, maximum 64 KiB. Requests and responses carry `api_version: 1`.
The live-snapshot and range-query operations additionally return a length-delimited binary Arrow
body after its JSON response header, as specified below.
This is a small local command transport, not a decision on future viewer IPC.
The endpoint is restricted to numeric loopback addresses and has no multi-user
authentication. Local users with access to it can control the attached device;
remote/cloud control requires a separate authenticated boundary.

```json
{"api_version":1,"command":{"op":"set_variable","name":"send_field_1","value":12.5}}
```

Success: `{"api_version":1,"ok":true,"outcome":"sent_unconfirmed"}` for wire
commands, or `applied_locally` for ACK policy/shutdown. Errors have `ok:false`
and an `error` string; CLI exits nonzero and Python raises RuntimeError.
Status returns counters, last status word, ACK policy, terminal error and
`logging.fast` / `logging.slow` with phase, Parquet path and recording error.
Operations: connect, status, observables, stop, enable_system, enable_control, error_reset,
set_variable, set_observable, button, send_ack, start_logging, stop_logging,
start_logging_slow_data, stop_logging_slow_data, shutdown.
Unknown operations/fields and unsupported versions fail without sending bytes.

`stop` affects the device; `shutdown` requests acquisition shutdown; the logger drains, merges Parquet segments
and optionally exports CSV before the service exits.
Shutdown does not implicitly send Stop. Loss of the client connection is not an
emergency stop. No automatic reconnect/replay occurs; a new service run starts
new metadata and new log files.

## Explicit recording control

Connection alone does not log. `start_logging` starts fast data;
`start_logging_slow_data` starts slow data. Each requires the session output directory
configured at startup. Matching stop operations detach their stream and finalize
in the background. Replies include current logging states. Wait for `complete`;
`shutdown` / Python `close()` waits for all finalizers. Files are numbered on each
restart, never appended or overwritten. Fast and slow starts/stops are independent.

`set_observable` fails locally with "setting observable is not possible when logging
is active; stop fast and slow logging first" whenever either stream is recording.
No device command is sent. `set_variable` and ordinary device control remain allowed.
Stopping the device is independent of stopping acquisition or either logger.

## Channel assignment query

`{"api_version":1,"command":{"op":"observables"}}` returns `channels`, an ordered
array of 20 objects with `channel` (1..20), `name`, `id`, and `state`. Known entries
use the canonical name and ID from the active channel mapping with state
`sent_unconfirmed`. Untouched channels have null name/ID and state `unknown`.
The reply includes `source: "service_requested_assignments"` and
`device_readback: false`. It reads only service state; there is no legacy firmware
readback command. Each connection applies the runtime profile's initial channels
before becoming ready; unspecified channels start unknown. Only
successful socket writes for accepted selections update it, never rejected requests.

## Configuration files and startup selection

`--profile` loads runtime `schema_version: 1`, name, configured sample period, and
`initial_channels` (1-based channel keys to observable names). `--channel-mapping`
loads firmware `api_version: 1`, mapping name, repository name/commit, channel count,
samples per packet, numeric ID maps, and the required `platform_state` object.
Its mask must select two adjacent bits at shift 0..30, and its `values` object
must name all four codes (`"0"` through `"3"`) with nonempty strings. Older custom
mappings must add this object; invalid mappings are rejected before device access. Both flags also exist as Python constructor
arguments `profile` and `channel_mapping`. The standard profile is embedded;
firmware mappings are generated from checkout headers when omitted. Outside the
checkout, pass a previously header-generated mapping explicitly.

Default initial channels select IDs 1..20 into slots 1..20. All channel/name pairs
are validated before device access. Connection initialization emits their ordinary 201..220 wire
commands in channel order before accepting API commands. Successful writes populate
`observables`, increment command counters, and appear as `initial_channels` events
in the audit. No enable or logging operation is implicit. Writes remain unconfirmed;
there is no device-side mapping acknowledgment or guaranteed backlog-clearing delay.
A custom empty initial map opts out, and partial maps leave other slots untouched.
Repository provenance is user-supplied mapping metadata, not device discovery.

## Connection lifecycle

Without `serve --device IP:PORT`, the control endpoint starts offline. The request
`{"api_version":1,"command":{"op":"connect","ip":"192.168.1.233","port":1000}}`
opens the device connection and applies configured initial observables. CLI and
Python helpers supply these defaults; the JSON operation requires both fields.
IP must be numeric IPv4/IPv6 and port must be 1..65535. A failed attempt returns an
error and leaves the service available for another attempt. Connecting again
while already connected is rejected. After a successful connection, transport
failure retains the existing behavior: terminate acquisition and finalize logs.

`status.state.connected` indicates transport connection state; `state.device`
is null until connected and then retains the device address. Before connecting,
`observables` reports unknown assignments, and device commands and logging starts
are rejected. ACK policy can be configured offline and takes effect on connection.
The service reserves the output directory at startup, even offline. `run.json`
contains the optional startup device; later connection requests are in
`commands.jsonl`, and `end.json` includes the final device address. Sample time
starts with acquisition, excluding time spent waiting offline.

## Local live snapshot operation

`{"api_version":1,"command":{"op":"get_live_data","last_n_samples":500}}`
requests an independent fast-data snapshot from the connected service's RAM ring.
It does not send a device command or enable either logger. Counts must be positive
and no greater than retained availability. Canonical selected names are deduplicated
by observable ID; unknown channels are omitted. Time is nominal acquisition time;
status is the frame's last-sample word repeated over its rows, as for recording.

Unlike other local operations, success returns one JSON header line containing
`api_version`, `ok`, `rows`, `arrow_bytes`, and `mapping_confirmed:false`, followed
by exactly `arrow_bytes` bytes containing an Arrow IPC stream. The header is still
subject to the 64 KiB control-message limit; the binary body is limited to 128 MiB.
Errors use the ordinary JSON error line without a binary body. Receivers must read
the advertised byte count, preserving bytes already received after the newline.
Python uses the native binary client rather than the JSON-only request helper.
Snapshots preserve Float32 NaN/Inf and UInt32 status values.

Service configuration is exposed in `status.data_options`: positive `buffer_samples`
(default computed as `ceil(30_000_000 / sample_period_us)`), `segment_rows` (1,000,000), and `flush_interval_ms` (60,000).
Logging flushes at the first of the row or elapsed-time thresholds and on stop.
Each logger also has an independent bounded 2,048-frame queue; it is not configured
by `buffer_samples`. Queue and write delays can extend the publication interval.
`status.buffer_available_samples` reports retained rows. Observable changes clear
history; the legacy firmware does not acknowledge the exact selection boundary.
There is no live subscription or query into recording history in this operation.

## Generating a mapping from firmware headers

`create-json-from-javascope-h` reads the repository's `javascope.h` enum sections
and commented send-field names, `javascope_status.h` platform-state masks/codes,
and the shared/FreeRTOS packet-size constants. It emits the same channel-mapping
schema consumed by `--channel-mapping` and Python `channel_mapping`.
By default the output is `artifacts/channel_mappings/javascope.json` beneath the
repository root; `--repo` and `--output` override discovery and destination.
Unsupported expressions and ambiguous names are errors. Existing output is not
touched on parse/validation failure. See the README for supported header syntax.

## Range queries and recording backend handles

The local API adds `recordings`, `data_info` and `read_data`. `data_info` takes
`source: {"stream":"fast"|"slow", "recording":null|positive_integer}`. Null selects
the recent RAM ring; a number selects a recording, including pending data and
older indexed chunks. `recordings` lists all sources in this service run.

```json
{"api_version":1,"command":{"op":"read_data","query":{"source":{"stream":"fast","recording":1},"selection":{"kind":"range","start":100,"stop":200},"channels":["JSO_lifecheck"]}}}
```

Selection alternatives are `{"kind":"tail","count":500}` and
`{"kind":"since","cursor":null,"limit":10000}`. Range positions are absolute
received-sample indices, half-open. A since response returns an opaque cursor
containing run/source/generation identity and the next position. Supply that
object unchanged on the next since call. Expired or mismatched cursors fail.
A source with no samples returns an empty page and an unset cursor position.

Success returns a JSON line with `info`, `cursor`, actual `start`/`stop`, `rows`,
`arrow_bytes`, and `mapping_confirmed:false`, followed by exactly that many bytes
of Arrow IPC. The 128 MiB body cap and ordinary JSON-only errors apply. `info`
contains available accepted range, `persisted_stop`, `complete`, schema/layout,
and nominal sample period. Pending data is part of a recording's available range
before flush. Read failures return an error without terminating acquisition.

Slow range queries preserve one original slow ID/value update per received sample;
wide slow Parquet/CSV exports are a distinct derived representation. Durable
`*.recording.json` handles identify the backend, schema, ordered immutable chunks
and successfully committed ranges. They remain readable independently of service
finalization and require no device connection.

### Service catalog

`catalog` returns `{api_version, ok, profile, device_readback: false}`. `profile`
contains the validated firmware mapping and runtime settings loaded by this service:
observable, slow-signal, variable and command names/IDs, channel geometry, initial
assignments, nominal sample period and platform-state decoding. Native viewers use
it to populate selectors instead of maintaining a second mapping. It is service
configuration, not firmware readback. Python: `Client.catalog()`; CLI: `ultrazohm catalog`.

### Unified shutdown

`shutdown` sends device Stop when connected, then ends acquisition, finalizes all
active recordings, and exits the service. The reply acknowledges acceptance, not
completed finalization. Process exit and `end.json` report completion/failure.
Ctrl-C, interactive EOF, and embedded `Acquisition.close()` use the same cleanup
sequence. A Stop transmission failure is recorded; logging still finalizes.
