"""Exclusive file publication never replaces existing files."""

import threading

import pytest

from ultrazohm_dataviewer.user_paths import publish_new


def test_exclusive_publication_fallback_preserves_existing_file(tmp_path, monkeypatch):
    source, target = tmp_path / "temporary", tmp_path / "complete"
    source.write_text("new")
    target.write_text("existing")
    monkeypatch.setattr(
        "os.link", lambda *args: (_ for _ in ()).throw(OSError("unsupported"))
    )
    with pytest.raises(FileExistsError):
        publish_new(source, target)
    assert target.read_text() == "existing"
    target.unlink()
    publish_new(source, target)
    assert target.read_text() == "new"


def test_publication_race_has_exactly_one_winner(tmp_path, monkeypatch):
    import os
    from concurrent.futures import ThreadPoolExecutor

    source_a, source_b, target = (tmp_path / name for name in ("a", "b", "target"))
    source_a.write_text("a")
    source_b.write_text("b")
    monkeypatch.setattr(
        os, "link", lambda *args: (_ for _ in ()).throw(OSError("unsupported"))
    )
    # Expose the former check-then-rename race deterministically. Exclusive OS
    # publication needs no check and never enters this replacing rename on POSIX.
    rename = os.rename
    barrier = threading.Barrier(2)

    def racing_rename(source, destination):
        barrier.wait(timeout=2)
        rename(source, destination)

    monkeypatch.setattr(os, "rename", racing_rename)

    def publish(source):
        try:
            publish_new(source, target)
            return source.name
        except FileExistsError:
            return None

    with ThreadPoolExecutor(max_workers=2) as executor:
        winners = list(executor.map(publish, [source_a, source_b]))
    winners = [winner for winner in winners if winner is not None]
    assert len(winners) == 1
    assert target.read_text() == winners[0]
