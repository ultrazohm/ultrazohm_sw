"""Files written by the CLI service open through the viewer's own loaders.

The viewer knows nothing about the CLI's file layout; it only reads Parquet and
CSV. This test pins that contract with real recordings from the simulator.
"""
from pathlib import Path
import socket
import subprocess
import sys

import polars as pl
import pytest

from live_support import ports, wait_for
from uz_dataviewer.loader import open_file
from uz_dataviewer.model import DataRegistry

FILES = {
    'data.parquet': (),
    'data.csv': (),
    'data_slow_data.parquet': (),
    'data_slow_data.csv': (),
    # Raw slow history: one update per sample, with the observable name as text.
    'data_slow_data.updates.parquet': ('observable',),
}


@pytest.fixture(scope='module')
def recording(tmp_path_factory):
    native = pytest.importorskip('ultrazohm_cli')
    root = Path(__file__).resolve().parents[2]
    device_port, service_port = ports()
    simulator = subprocess.Popen([sys.executable, str(root/'javascope/test_server.py'), '--host', '127.0.0.1',
                                  '--port', str(device_port), '--sample-rate', '1000'],
                                 stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    output = tmp_path_factory.mktemp('cli') / 'run'
    endpoint = f'127.0.0.1:{service_port}'
    try:
        def ready():
            try:
                with socket.create_connection(('127.0.0.1', device_port), timeout=.1):
                    return True
            except OSError:
                return False
        wait_for(ready)
        with native.Acquisition(f'127.0.0.1:{device_port}', endpoint=endpoint, output=str(output),
                                format='csv'):
            client = native.Client(endpoint)
            client.start_logging()
            client.start_logging('slow')
            wait_for(lambda: client.status()['state']['samples'] > 2000, seconds=15)
    finally:
        simulator.terminate()
        simulator.wait(timeout=5)
    return output


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
@pytest.mark.parametrize('name', list(FILES))
def test_cli_recordings_open_in_the_viewer(recording, name, mode, backend):
    path = recording / name
    reference = pl.read_parquet(path) if path.suffix == '.parquet' else pl.read_csv(path)
    assert reference.height > 0
    run = open_file(str(path), mode, backend=backend).register(DataRegistry())
    skipped = FILES[name]
    assert run.n_rows == reference.height
    assert run.skipped_columns == skipped
    assert set(run.signals) == set(reference.columns) - {'time', *skipped}
    assert run.time[0] == pytest.approx(reference['time'][0])
    assert run.time[-1] == pytest.approx(reference['time'][-1])
