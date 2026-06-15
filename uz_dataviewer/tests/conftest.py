import numpy as np
import pytest


@pytest.fixture
def sample_signal():
    """1 s of 10 kHz data: 50 Hz / 1 V sine plus 1 kHz / 0.2 V sine."""
    sample_rate = 10_000
    time = np.arange(sample_rate) / sample_rate
    values = 1.0 * np.sin(2 * np.pi * 50 * time) + 0.2 * np.sin(2 * np.pi * 1000 * time)
    return time, values, sample_rate


@pytest.fixture
def javascope_csv(tmp_path, sample_signal):
    """CSV in javascope format: ';' separated, trailing separator per line."""
    time, values, _ = sample_signal
    path = tmp_path / "log.csv"
    with open(path, "w") as f:
        f.write("time;ch1;ch2;\n")
        for t, v in zip(time[:1000], values[:1000]):
            f.write(f"{t:.9f};{v:.9f};{2 * v:.9f};\n")
    return str(path)


@pytest.fixture
def javascope_parquet(tmp_path, sample_signal):
    import pyarrow as pa
    import pyarrow.parquet as papq

    time, values, _ = sample_signal
    table = pa.table({"time": time, "ch1": values, "ch2": 2 * values})
    path = tmp_path / "log.parquet"
    papq.write_table(table, str(path))
    return str(path)
