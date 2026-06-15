import numpy as np
import pytest

from uz_dataviewer.analysis import fft


def test_detects_sine_frequencies_and_amplitudes(sample_signal):
    time, values, sample_rate = sample_signal
    result = fft.compute_fft(time, values, window="hann")
    assert result is not None
    assert result.sample_rate == pytest.approx(sample_rate, rel=1e-6)

    peak_50 = np.argmin(np.abs(result.frequencies - 50.0))
    peak_1k = np.argmin(np.abs(result.frequencies - 1000.0))
    assert result.amplitudes[peak_50] == pytest.approx(1.0, rel=0.05)
    assert result.amplitudes[peak_1k] == pytest.approx(0.2, rel=0.05)


def test_region_selection(sample_signal):
    time, values, _ = sample_signal
    result = fft.compute_fft(time, values, t_start=0.25, t_stop=0.75)
    assert result is not None
    assert result.t_start == pytest.approx(0.25, abs=1e-3)
    assert result.t_stop == pytest.approx(0.75, abs=1e-3)
    assert result.n_samples == pytest.approx(5000, abs=2)


def test_dc_removal():
    time = np.arange(1000) / 1000.0
    values = 5.0 + np.sin(2 * np.pi * 10 * time)
    result = fft.compute_fft(time, values, remove_dc=True, window="rectangular")
    assert result.amplitudes[0] == pytest.approx(0.0, abs=1e-9)
    result_dc = fft.compute_fft(time, values, remove_dc=False, window="rectangular")
    assert result_dc.amplitudes[0] == pytest.approx(5.0, rel=1e-6)


def test_too_few_samples_returns_none():
    time = np.arange(4) / 4.0
    values = np.ones(4)
    assert fft.compute_fft(time, values) is None


def test_region_without_samples_returns_none(sample_signal):
    time, values, _ = sample_signal
    assert fft.compute_fft(time, values, t_start=5.0, t_stop=6.0) is None


def test_nan_handling(sample_signal):
    time, values, _ = sample_signal
    values = values.copy()
    values[100:110] = np.nan
    result = fft.compute_fft(time, values)
    assert result is not None
    assert np.isfinite(result.amplitudes).all()
