#!/usr/bin/env python3
"""Boot the generated Pyodide app in Chromium and exercise its actual runtime.

Run gen_web.py first, then install Playwright and its Chromium browser. Set
UZ_BROWSER_EXECUTABLE to use an existing Chromium/Chrome installation.
"""

from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import os
import threading

from playwright.sync_api import sync_playwright


def main():
    directory = Path(__file__).resolve().parents[1] / "web"
    handler = partial(SimpleHTTPRequestHandler, directory=str(directory))
    server = ThreadingHTTPServer(("127.0.0.1", 0), handler)
    thread = threading.Thread(target=server.serve_forever, daemon=True)
    thread.start()
    try:
        with sync_playwright() as playwright:
            browser = playwright.chromium.launch(
                executable_path=os.environ.get("UZ_BROWSER_EXECUTABLE"),
                args=["--enable-unsafe-swiftshader"],
            )
            page = browser.new_page()
            errors = []
            page.on("pageerror", lambda error: errors.append(str(error)))
            page.goto(f"http://127.0.0.1:{server.server_port}/")
            page.wait_for_function(
                'document.getElementById("loader") === null',
                timeout=180_000,
            )
            page.locator("#uzFileInput").set_input_files(
                {
                    "name": "smoke.csv",
                    "mimeType": "text/csv",
                    "buffer": (
                        "time,a\n" + "".join(f"{i / 64},{i % 8}\n" for i in range(64))
                    ).encode(),
                }
            )
            page.wait_for_function(
                'pyodide.runPython("len(_app.state.registry)") === 1'
            )
            result = page.evaluate("""() => pyodide.runPython(`
from uz_dataviewer import session, api
from uz_dataviewer.sampling import require_matching_time, regular_sample_interval
import numpy as np
from pathlib import Path
# Exercise numerical guards with the browser's separately pinned NumPy runtime.
try:
    api.math((np.arange(8.), np.array([1., 2.])), op="integral")
except ValueError:
    pass
else:
    raise AssertionError("Malformed integral input accepted")
t = 1.7e9 + np.arange(8) * 1e-6
for validate in (lambda: require_matching_time(t, t + 1e-6),
                 lambda: regular_sample_interval(t, "FFT")):
    try:
        validate()
    except ValueError:
        pass
    else:
        raise AssertionError("Unsafe timestamp precision accepted")
large = api.fft(np.arange(8.), np.full(8, 1e38, np.float32),
                remove_dc=False, window=False)
assert large.ok and np.isfinite(large.mag).all()
np.testing.assert_allclose(large.mag[0], 1e38, rtol=1e-6)
s = _app.state
run = s.registry.runs[0]
assert run.n_rows == 64 and not run.reloadable
assert not Path(run.path).exists()
s.commands.execute(s, "add_signal", [1, run.id, "a"])
s.commands.execute(s, "set_x_lim", [1, 0, .5])
s.commands.execute(s, "fft_source", [run.id, "a"])
s.commands.execute(s, "fft", [])
s.commands.execute(s, "node_source", [run.id, "a"])
s.commands.execute(s, "node_add", ["fft"])
s.commands.execute(s, "node_link", [1, 2])
s.commands.execute(s, "node_eval", [])
assert s.registry.get(s.nodes.get(2).out_run_id).axis_domain == "frequency"
session.export_data(s, 0, "/tmp/smoke.csv")
assert len(Path("/tmp/smoke.csv").read_text().splitlines()) == 34
# Streamed browser columns carry the same JavaScope precision as file loads.
from uz_dataviewer import webbridge
from uz_dataviewer.analysis import compute_signal_fft
t = np.rint(np.arange(6000) / 30000 * 1e8) / 1e8
y = np.sin(2 * np.pi * 1000 * t)
webbridge.load_columns("quantized.csv", ["CH1=1)ia"], [y], t)
quantized = s.registry.runs[-1]
assert quantized.timestamp_resolution == 1e-8
assert compute_signal_fft(quantized, "ia", t[0], t[-1]).ok
assert not api.fft(t, y).ok
True
`)""")
            assert result is True
            # Let real render frames consume the resulting plot/analysis state.
            page.wait_for_function(
                'pyodide.runPython("_app.fft._computed_key is not None")',
                timeout=30_000,
            )
            assert not errors, errors
            page.evaluate("""() => pyodide.runPython("_app.state.shutdown()")""")
            browser.close()
        print(
            "Browser smoke test passed: boot, upload, plot, FFT, graph and CSV export"
        )
    finally:
        server.shutdown()
        server.server_close()
        thread.join()


if __name__ == "__main__":
    main()
