# Scope 2 usage

## Connect and acquire signals

Set the device IP and frame geometry in Control, then connect. Scope 2 reads observable and command names from the firmware `javascope.h`.

The Signals panel separates firmware observables from acquired signals. Search the available list, then double-click, use the context menu, or drag an observable into Acquired. Scope 2 assigns the first free hardware slot automatically. Drag an acquired signal into any subplot.

Changing or releasing a slot closes the old signal segment at the exact sample index. Its plotted data remains available until the bounded raw ring evicts it, so a remap never relabels old samples. Acquisition changes are disabled while logging to keep log columns stable.

## Plot windows and tools

The first plot window is docked. Use **+ Plot window** for additional movable windows. Each window independently supports:

- 1x1, 1x2, 2x1, 2x2, 1x3, and 3x1 grids
- linked or independent X navigation
- line, scatter, stairs, and XY plots
- left and right Y axes
- raw-sample markers
- two measurement cursors with delta-time/frequency readout
- a draggable spy rectangle and zoom inset

Manual pan or zoom detaches only that window from live following. Use **Resume live** to reattach it. A trigger capture navigates windows that are still following; normal and single modes hold the capture, while auto mode resumes rolling after the capture becomes stale.

Plot legend context menus move a signal between Y axes or remove it. The Signals list can also drag retained, inactive segments back into a plot while their samples remain resident.

## Console commands

GUI actions use the same command registry as the console and replay scripts. Useful examples:

```text
acquire(speed_rpm)
add_observable(window_1, plot_1, speed_rpm)
set_grid(window_1, 2, 1)
set_plot_type(window_1, plot_2, XY)
set_xy_observable(window_1, plot_2, current_d)
set_axis_observable(window_1, plot_1, torque, right)
show_samples(window_1, plot_1, true)
cursors(window_1, plot_1, true)
spy(window_1, plot_1, true)
follow_live(window_1, true)
export_data(window_1, plot_1, visible.csv, false)
```

Signal and observable names depend on the loaded firmware header. Enter `help` in the console for the complete command list.

## Sessions and export

`save_state(path.json)` stores connection/configuration settings and the complete plot workspace. Plot assignments are persisted by observable identity rather than temporary segment IDs. `load_state(path.json)` requires the scope to be disconnected and logging stopped.

`export_script(path.uzscript)` writes a replayable command script. Scripts intentionally do not connect automatically.

`export_data` writes undecimated raw samples from the current visible time range to CSV. Use its final boolean argument for relative time. Trigger captures can still be exported through the capture export command and opened in `uz_dataviewer`.

## History limits

Full-resolution data is bounded by `ring_seconds` and `max_ring_bytes`. The optional RAM min/max pyramid stays under `history_limit` and supports wide zoom views without retaining an unbounded raw stream. There is no disk-backed history mode; durable acquisition is provided by Logging.
