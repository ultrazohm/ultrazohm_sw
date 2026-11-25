"""Continuous display requests and background file validation."""

import threading
import time

import pytest

from ultrazohm_dataviewer.requests import Requests


def test_continuous_display_publishes_before_producer_stops():
    requests = Requests()
    started, release, release_next = (threading.Event() for _ in range(3))

    def compute(cancel):
        started.set()
        release.wait(2)
        return "first"

    try:
        requests.request("plot", 1, "recording", compute, continuous=True)
        assert started.wait(2)
        requests.request(
            "plot", 2, "recording", lambda cancel: release_next.wait(2), continuous=True
        )
        release.set()
        deadline = time.monotonic() + 2
        while not requests.results and time.monotonic() < deadline:
            time.sleep(0.005)
        assert requests.results["plot"] == (1, "recording", "first")
    finally:
        release.set()
        release_next.set()
        requests.close()


def test_gui_file_validation_is_background_but_raw_validation_is_strict(
    tmp_path, monkeypatch
):
    from ultrazohm_dataviewer.sources import FileIdentity, validation_error

    path = tmp_path / "recording"
    path.write_text("original")
    identity = FileIdentity.capture(path)
    jobs = Requests()
    entered, release = threading.Event(), threading.Event()
    original = FileIdentity._validate

    def slow_validate(self):
        entered.set()
        assert release.wait(2)
        original(self)

    monkeypatch.setattr(FileIdentity, "_validate", slow_validate)
    try:
        assert validation_error([identity], jobs) is None
        assert entered.wait(2)
        path.write_text("changed recording")
        release.set()
        deadline = time.monotonic() + 2
        while not jobs.results and time.monotonic() < deadline:
            time.sleep(0.005)
        assert "Source changed" in validation_error([identity], jobs)
        with pytest.raises(ValueError, match="Source changed"):
            identity.validate()
    finally:
        release.set()
        jobs.close()


@pytest.mark.parametrize("forget", [False, True])
def test_continuous_display_discards_canceled_identity(forget):
    jobs = Requests()
    entered, release, next_entered, next_release = (threading.Event() for _ in range(4))

    def old(cancel):
        entered.set()
        assert release.wait(2)
        return "obsolete"

    def new(cancel):
        next_entered.set()
        assert next_release.wait(2)
        return "current"

    try:
        jobs.request("plot", 1, "old", old, continuous=True)
        assert entered.wait(2)
        if forget:
            jobs.forget("plot")
        jobs.request("plot", 2, "new", new, continuous=True)
        release.set()
        assert next_entered.wait(2)
        assert not jobs.results
    finally:
        release.set()
        next_release.set()
        jobs.close()
