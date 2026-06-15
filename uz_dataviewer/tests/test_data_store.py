import time as time_module

from uz_dataviewer.core.console import Console, LogLevel
from uz_dataviewer.core.data_store import DataStore, SignalRef


def _wait_for_loads(store, timeout=10.0):
    deadline = time_module.time() + timeout
    while time_module.time() < deadline:
        store.poll()
        if not store.loading:
            return
        time_module.sleep(0.02)
    raise TimeoutError("loading did not finish")


def test_async_load_and_poll(javascope_csv, javascope_parquet):
    store = DataStore(Console())
    store.load_files_async([javascope_csv, javascope_parquet])
    _wait_for_loads(store)
    assert len(store.runs) == 2
    names = {run.name for run in store.runs.values()}
    assert names == {"log.csv", "log.parquet"}
    store.shutdown()


def test_load_error_goes_to_console(tmp_path):
    console = Console()
    store = DataStore(console)
    store.load_files_async([str(tmp_path / "does_not_exist.csv")])
    _wait_for_loads(store)
    assert len(store.runs) == 0
    errors = console.entries(LogLevel.ERROR)
    assert errors and "does_not_exist" in errors[0].message
    store.shutdown()


def test_payload_roundtrip(javascope_csv):
    store = DataStore(Console())
    store.load_files_async([javascope_csv])
    _wait_for_loads(store)
    run_id = next(iter(store.runs))
    ref = SignalRef(run_id, "ch1")
    payload_id = store.payload_id(ref)
    assert store.payload_id(ref) == payload_id  # stable
    assert store.resolve_payload(payload_id) == ref
    run, time, values = store.get_signal(ref)
    assert len(time) == len(values) == 1000
    store.shutdown()


def test_remove_run(javascope_csv):
    store = DataStore(Console())
    store.load_files_async([javascope_csv])
    _wait_for_loads(store)
    run_id = next(iter(store.runs))
    revision = store.revision
    store.remove_run(run_id)
    assert not store.runs
    assert store.revision > revision
    assert store.get_signal(SignalRef(run_id, "ch1")) is None
    store.shutdown()
